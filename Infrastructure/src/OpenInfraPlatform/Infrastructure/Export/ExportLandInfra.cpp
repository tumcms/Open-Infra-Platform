/*
Copyright (c) 2017 Technical University of Munich
Chair of Computational Modeling and Simulation.

TUM Open Infra Platform is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License Version 3
as published by the Free Software Foundation.

TUM Open Infra Platform is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "ExportLandInfra.h"

#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DArc.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid.h"

#include <QtXml>

/*Converts the abstract buw::IAlignment3D to XML elements.*/
QDomElement convertAlignment(buw::ReferenceCounted<buw::IAlignment3D> alignment)
{
	QDomElement featureElement;
	featureElement.setTagName("feature");

	QDomElement alignmentElement;
	alignmentElement.setPrefix("lia");
	alignmentElement.setTagName("Alignment");
	alignmentElement.setAttribute("gml:id", QString(alignment->getName().toStdString().data()));

	featureElement.appendChild(alignmentElement);


	//TODO: Implementation

	return featureElement;
}

QDomElement convertAlignmentModel(buw::ReferenceCounted<buw::AlignmentModel> alignmentModel)
{
	QDomElement root;
	/*Initialize header of document.*/
	root.setTagName("LandInfraDataset");
	root.setAttribute("xmlns:gml", "http://www.opengis.net/gml/3.2");
	root.setAttribute("xmlns:xlink", "http://www.w3.org/1999/xlink");
	root.setAttribute("xmlns:li", "http://www.opengis.net/infragml/core/1.0");
	root.setAttribute("xmlns:lia", "http://www.opengis.net/infragml/alignment/1.0");
	root.setAttribute("xmlns:gmllr", "http://www.opengis.net/gml/3.3/lr");
	root.setAttribute("xmlns:gmllro", "http://www.opengis.net/gml/3.3/lro");
	root.setAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
	root.setAttribute("xsi:schemaLocation", "http://www.opengis.net/infragml/alignment/1.0 Part3Alignment0321.xsd");

	/*Iterate over all alignments and add them as child nodes.*/
	for(auto alignment : alignmentModel->getAlignments()) {
		root.appendChild(convertAlignment(alignment));
	}

	return root;
}



/*Convert a buw::Vector2d to a gml:position XML element.*/
QDomElement convertPosition2d(buw::Vector2d pos)
{
	/*Set element name and write x and y position.*/
	QDomElement gmlPosition2d;
	gmlPosition2d.setPrefix("gml");
	gmlPosition2d.setTagName("pos");
	gmlPosition2d.setNodeValue(QString::number(pos.x()) + " " + QString::number(pos.y()));
	return gmlPosition2d;
}

/*Convert a buw::Vector3d to a gml:position XML element.*/
QDomElement convertPosition3d(buw::Vector3d pos)
{	
	/*Set element name and write x, y and z position.*/
	QDomElement gmlPosition3d;
	gmlPosition3d.setPrefix("gml");
	gmlPosition3d.setTagName("pos");
	gmlPosition3d.setNodeValue(QString::number(pos.x()) + " " + QString::number(pos.y()) + " " + QString::number(pos.z()));
	return gmlPosition3d;
}

/*Convert a buw::HorizontalAlignmentElement2DLine to a */
QDomElement convertHorizontalAlignmentElement2DLine(buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> lineSegment)
{
	//TODO: Implementation
	return QDomElement();
}

OpenInfraPlatform::Infrastructure::ExportLandInfra::ExportLandInfra(buw::ReferenceCounted<buw::AlignmentModel> alignmentModel, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string & filename)
:Export(alignmentModel,dem,filename)
{
	QDomDocument doc;
	QDomProcessingInstruction header = doc.createProcessingInstruction("xml", "version=\"1.0\"");
	doc.appendChild(header);

	/*Converts the buw::HorizontalAlignmentElement2DLine to XML element segment.*/
	auto convertHorizontalAlignmentElement2DLine = 
		[&](buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> lineSegment) -> QDomElement
	{
		QDomElement segmentElement = doc.createElement("lia:segment");

		/*Simply set it to true,*/
		QDomElement tangentialContinuityElement = doc.createElement("lia:tangentialContinuity");
		tangentialContinuityElement.setNodeValue("true");
		segmentElement.appendChild(tangentialContinuityElement);

		QDomElement geometryElement = doc.createElement("lia:geometry");
		QDomElement lineSegmentElement = doc.createElement("lia:lineSegment");
		geometryElement.appendChild(lineSegmentElement);

		/*Read start and end position from line segment.*/
		QString startPosX = QString::number(lineSegment->getStartPosition().x());
		QString startPosY = QString::number(lineSegment->getStartPosition().y());
		QString endPosX = QString::number(lineSegment->getEndPosition().x());
		QString endPosY = QString::number(lineSegment->getEndPosition().y());

		QDomElement startPos = doc.createElement("gml:pos");
		startPos.setNodeValue(startPosX + " " + startPosY);
		QDomElement endPos = doc.createElement("gml:pos");
		endPos.setNodeValue(endPosX + " " + endPosY);

		lineSegmentElement.appendChild(startPos);
		lineSegmentElement.appendChild(endPos);

		return segmentElement;
	};

	/*Converts the abstract buw::IAlignment3D to XML elements.*/
	auto convertAlignment = 
		[&](buw::ReferenceCounted<buw::IAlignment3D> alignment) ->QDomElement
	{
		QDomElement featureElement = doc.createElement("feature");

		QDomElement alignmentElement = doc.createElement("lia:Alignment");
		alignmentElement.setAttribute("gml:id", QString(alignment->getName().toStdString().data()));

		featureElement.appendChild(alignmentElement);


		//TODO: Implementation

		return featureElement;
	};

	/*Converts buw::AlignmentModel to XML element.*/
	auto convertAlignmentModel = [&] (buw::ReferenceCounted<buw::AlignmentModel> alignmentModel) -> QDomElement
	{
		QDomElement root = doc.createElement("LandInfraDataset");

		/*Initialize header of document.*/
		root.setAttribute("xmlns:gml", "http://www.opengis.net/gml/3.2");
		root.setAttribute("xmlns:xlink", "http://www.w3.org/1999/xlink");
		root.setAttribute("xmlns:li", "http://www.opengis.net/infragml/core/1.0");
		root.setAttribute("xmlns:lia", "http://www.opengis.net/infragml/alignment/1.0");
		root.setAttribute("xmlns:gmllr", "http://www.opengis.net/gml/3.3/lr");
		root.setAttribute("xmlns:gmllro", "http://www.opengis.net/gml/3.3/lro");
		root.setAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
		root.setAttribute("xsi:schemaLocation", "http://www.opengis.net/infragml/alignment/1.0 Part3Alignment0321.xsd");

		/*Iterate over all alignments and add them as child nodes.*/
		for(auto alignment : alignmentModel->getAlignments()) {
			root.appendChild(convertAlignment(alignment));
		}

		return root;
	};

	if(alignmentModel) {
		doc.appendChild(convertAlignmentModel(alignmentModel));
	}

	QFile file(filename.c_str());

	if(!file.open(QIODevice::WriteOnly)) {
		throw buw::Exception("Failed opening file for writing.");
	}

	QTextStream textStream(&file);
	doc.save(textStream, 4);
	file.close();
}
