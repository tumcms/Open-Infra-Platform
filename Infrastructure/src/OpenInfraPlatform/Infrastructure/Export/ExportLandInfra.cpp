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

#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment3DBased3D.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DArc.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DBlossCurve.h"

#include <QtXml>

/*
Constructor for the exporter and only visible function. The AlignmentModel conversion itself is split into multiple
lambdas which are defined in the constructor, since the different QDomNodes or QDomElements have to be created on a document.
The lambdas can access the main document while still providing encapsulation of functionality.
*/
OpenInfraPlatform::Infrastructure::ExportLandInfra::ExportLandInfra(buw::ReferenceCounted<buw::AlignmentModel> alignmentModel, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string & filename)
:Export(alignmentModel,dem,filename)
{
	QDomDocument doc;
	QDomProcessingInstruction header = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
	doc.appendChild(header);


	/*Create a gml:pos node from buw::Vector2d.*/
	auto createNodeWithVector = [&](QString nodeName, buw::Vector2d pos) -> QDomElement {
		QDomElement position = doc.createElement(nodeName);
		QString posX = QString::number(pos.x(), 'g', 10);
		QString posY = QString::number(pos.y(), 'g', 10);
		QDomText posText = doc.createTextNode(posX + " " + posY);
		position.appendChild(posText);
		return position;
	};

	/*Shortcut for gml:pos node.*/
	auto createPosition = [&](buw::Vector2d pos) -> QDomElement {
		return createNodeWithVector("gml:pos", pos);
	};

	/*Shortcut for gml:location node.*/
	auto createLocation = [&](buw::Vector2d pos) -> QDomElement {
		return createNodeWithVector("gml:location", pos);
	};

	/*Create node with certain name holding single scalar value.*/
	auto createNodeWithScalar = [&](QString nodeName, double value) ->QDomElement {
		QDomElement element = doc.createElement(nodeName);
		QString text = QString::number(value, 'g', 10);
		QDomText elementText = doc.createTextNode(text);
		element.appendChild(elementText);
		return element;
	};

	/*Converts the buw::HorizontalAlignmentElement2DLine to XML element segment.*/
	auto convertHorizontalAlignmentElement2DLine = 
		[&](buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> lineSegment) -> QDomElement
	{
		QDomElement segmentElement = doc.createElement("lia:segment");

		/*Simply set it to true, since it can not be determined from the internal data representation.*/
		QDomElement tangentialContinuityElement = doc.createElement("lia:tangentialContinuity");
		QDomText tangentialContinuityElementString = doc.createTextNode("true");
		tangentialContinuityElement.appendChild(tangentialContinuityElementString);
		segmentElement.appendChild(tangentialContinuityElement);

		/*All lia:lineSegment etc. are surrounded by the lia:geometry environment.*/
		QDomElement geometryElement = doc.createElement("lia:geometry");
		segmentElement.appendChild(geometryElement);
		QDomElement lineSegmentElement = doc.createElement("lia:lineSegment");		

		/*Create gml:pos nodes for start and end position in the lineSegment element.*/		
		lineSegmentElement.appendChild(createPosition(lineSegment->getStartPosition()));		
		lineSegmentElement.appendChild(createPosition(lineSegment->getEndPosition()));

		geometryElement.appendChild(lineSegmentElement);

		return segmentElement;
	};

	/*
	Convert the buw::HorizontalAlignmentElement2DArc to a lia:arcSegment XML element.
	Currently only the lia:circularArcByCenterPoint is supported for export.
	*/
	auto convertHorizontalAlignmentElement2DArc =
		[&](buw::ReferenceCounted<buw::HorizontalAlignmentElement2DArc> arcSegment) ->QDomElement
	{
		QDomElement liaSegment = doc.createElement("lia:segment");

		/*Simply set it to true, since it can not be determined from the internal data representation.*/
		QDomElement liaTangentialContinuity = doc.createElement("lia:tangentialContinuity");
		QDomText liaTangentialContinuityText = doc.createTextNode("true");
		liaTangentialContinuity.appendChild(liaTangentialContinuityText);
		liaSegment.appendChild(liaTangentialContinuity);

		/*Create the lia:geometry environment and append the lia:circularArcSegment.*/
		QDomElement liaGeometry = doc.createElement("lia:geometry");
		QDomElement liaCircularArcSegment = doc.createElement("lia:circularArcSegment");
		liaGeometry.appendChild(liaCircularArcSegment);

		/*Create the lia:circularArcByCenterPoint environment and append it to lia:circularArcSegment*/
		QDomElement liaCircularArcByCenterPoint = doc.createElement("lia:circularArcByCenterPoint");
		liaCircularArcByCenterPoint.setAttribute("numArc", 1);
		liaCircularArcSegment.appendChild(liaCircularArcByCenterPoint);

		/*Read the center position from arcSegment and write it to gml:pos*/
		liaCircularArcByCenterPoint.appendChild(createPosition(arcSegment->getCenter()));

		/*Read the radius from arcSegment and write it to gml:radius*/
		QDomElement gmlRadius = createNodeWithScalar("gml:radius", arcSegment->getRadius());
		gmlRadius.setAttribute("uom", "m");
		liaCircularArcByCenterPoint.appendChild(gmlRadius);
				
		/*Calculate the start angle as the angle betweeen startPos - center and x axis.*/
		buw::Vector2d localStartPosition = arcSegment->getStartPosition() - arcSegment->getCenter();
		double startAngle = buw::calculateAngleBetweenVectors(buw::Vector2d(1.0, 0.0), localStartPosition);		
		
		/*Calculate the end angle as the angle between endPos - center and x axis.*/
		buw::Vector2d localEndPosition = arcSegment->getEndPosition() - arcSegment->getCenter();
		double endAngle = buw::calculateAngleBetweenVectors(buw::Vector2d(1.0, 0.0), localEndPosition);

		/*
		Do that to fix the thing with undecisiveness between clockwise and counter clockwise arcs.
		All arcs with endAngle > starAngle are assumed to be clockwise and endAngle < starAngle counter clockwise.
		Therefore add 2pi to either start or endangle in case this rule is violated.
		*/
		if(arcSegment->getClockWise() && endAngle < startAngle) {
			endAngle += 2.0*buw::constantsd::pi();
		} else if(!arcSegment->getClockWise() && endAngle > startAngle) {
			startAngle += 2.0*buw::constantsd::pi();
		}

		/*Write startAngle to node.*/
		QDomElement gmlStartAngle = createNodeWithScalar("gml:startAngle",startAngle);
		gmlStartAngle.setAttribute("uom", "r");
		liaCircularArcByCenterPoint.appendChild(gmlStartAngle);

		/*Write endAngle to node.*/
		QDomElement gmlEndAngle = createNodeWithScalar("gml:endAngle", endAngle);
		gmlEndAngle.setAttribute("uom", "r");
		liaCircularArcByCenterPoint.appendChild(gmlEndAngle);

		liaSegment.appendChild(liaGeometry);
		return liaSegment;
	};

	/*
	Convert a buw::HorizontalAlignmentElement2DBlossCurve to the lia:transitionSegment XML element.
	*/
	auto convertHorizontalAlignmentElement2DBlossCurve = 
		[&](buw::ReferenceCounted<buw::HorizontalAlignmentElement2DBlossCurve> transitionSegment) ->QDomElement
	{
		QDomElement liaSegment = doc.createElement("lia:segment");

		/*Simply set it to true, since it can not be determined from the internal data representation.*/
		QDomElement liaTangentialContinuity = doc.createElement("lia:tangentialContinuity");
		QDomText liaTangentialContinuityText = doc.createTextNode("true");
		liaTangentialContinuity.appendChild(liaTangentialContinuityText);
		liaSegment.appendChild(liaTangentialContinuity);

		/*Create the lia:geometry and lia:transitionSegment nodes.*/
		QDomElement liaGeometry = doc.createElement("lia:geometry");
		QDomElement liaTransitionSegment = doc.createElement("lia:transitionSegment");

		/*lia:referenceLocation has location, direction and in/out dimensions.*/
		QDomElement liaReferenceLocation = doc.createElement("lia:referenceLocation");
		
		/*Set gml:location as startPosition*/		
		QDomElement gmlLocation = createLocation(transitionSegment->getStartPosition());
		liaReferenceLocation.appendChild(gmlLocation);

		/*Retrieve startDirection from curve.*/		
		QDomElement gmlRefDirection = createNodeWithScalar("gml:refDirection", transitionSegment->getStartDirection());
		liaReferenceLocation.appendChild(gmlRefDirection);

		/*Determine the input dimension, currently fixed at 2.*/		
		QDomElement gmlInDimension = createNodeWithScalar("gml:inDimension", 2);
		liaReferenceLocation.appendChild(gmlInDimension);

		/*Determine the output dimension, currently fixed at 2.*/
		QDomElement gmlOutDimension = createNodeWithScalar("gml:outDimension", 2);
		liaReferenceLocation.appendChild(gmlOutDimension);

		liaTransitionSegment.appendChild(liaReferenceLocation);

		/*Determine and set the lia:length from getLength()*/
		QDomElement liaLength = createNodeWithScalar("lia:length", transitionSegment->getLength());
		liaLength.setAttribute("uom", "m");
		liaTransitionSegment.appendChild(liaLength);

		/*Determine startCurvature with getStartCurvature() and store it in the lia:startCurvature XML element.*/
		QDomElement liaStartCurvature = createNodeWithScalar("lia:startCurvature", transitionSegment->getStartCurvature());
		liaTransitionSegment.appendChild(liaStartCurvature);

		/*Determine endCurvature with getEndCurvature() and store it in the lia:endCurvature XML element.*/
		QDomElement liaEndCurvature = createNodeWithScalar("lia:endCurvature", transitionSegment->getEndCurvature());
		liaTransitionSegment.appendChild(liaEndCurvature);

		/*Currently only Bloss curve as transition type supported.*/
		QDomElement liaTransitionType = doc.createElement("lia:transitionType");
		liaTransitionType.setAttribute("xlink:href", "http://example.com/transitionType#bloss");
		liaTransitionType.setAttribute("xlink:title", "Bloss");
		liaTransitionSegment.appendChild(liaTransitionType);

		liaGeometry.appendChild(liaTransitionSegment);		
		liaSegment.appendChild(liaGeometry);

		return liaSegment;
	};

	/*Convert a buw::HorizontalAlignmentElement2DClothoid to a lia:segment XML element.*/
	auto convertHorizontalAlignmentElement2DClothoid =
		[&](buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> clothoidSegment) ->QDomElement
	{
		QDomElement liaSegment = doc.createElement("lia:segment");
		/*Simply set it to true, since it can not be determined from the internal data representation.*/
		QDomElement liaTangentialContinuity = doc.createElement("lia:tangentialContinuity");
		QDomText liaTangentialContinuityText = doc.createTextNode("true");
		liaTangentialContinuity.appendChild(liaTangentialContinuityText);
		liaSegment.appendChild(liaTangentialContinuity);

		/*Create lia:geometry environment and lia:clothoidArcSegment sub-environment.*/
		QDomElement liaGeometry = doc.createElement("lia:geometry");
		QDomElement liaClothoidArcSegment = doc.createElement("lia:clothoidArcSegment");

		/*A gml:ref location is a wrapper for gml:AffinePlacement which hols location, direction and in/out dims.*/
		QDomElement gmlRefLocation = doc.createElement("gml:refLocation");
		QDomElement gmlAffinePlacement = doc.createElement("gml:AffinePlacement");

		/*Set location as start location of clothoid segment*/
		QDomElement gmlLocation = createLocation(clothoidSegment->getStartPosition());
		gmlAffinePlacement.appendChild(gmlLocation);

		/*Determine refDirection from data*/
		QDomElement gmlRefDirection = createNodeWithScalar("gml:refDirection", clothoidSegment->getStartDirection());
		gmlAffinePlacement.appendChild(gmlRefDirection);

		/*Set inDimension to 2.*/
		QDomElement gmlInDimension = createNodeWithScalar("gml:inDimension", 2);
		gmlAffinePlacement.appendChild(gmlInDimension);

		/*Set outDimension to 2.*/
		QDomElement gmlOutDimension = createNodeWithScalar("gml:outDimension", 2);
		gmlAffinePlacement.appendChild(gmlOutDimension);

		gmlRefLocation.appendChild(gmlAffinePlacement);
		liaClothoidArcSegment.appendChild(gmlRefLocation);

		/*Get the clothoid constant and set it as the scaleFactor.*/
		QDomElement gmlScaleFactor = createNodeWithScalar("gml:scaleFactor", clothoidSegment->getClothoidConstant());
		liaClothoidArcSegment.appendChild(gmlScaleFactor);

		/*Get startL_ as startParameter and set it as the start parameter.*/
		QDomElement gmlStartParameter = createNodeWithScalar("gml:startParameter", clothoidSegment->getStartParameter());
		liaClothoidArcSegment.appendChild(gmlStartParameter);

		/*Get endL_ as endParameter  and set it as the endParameter.*/
		QDomElement gmlEndParameter = createNodeWithScalar("gml:endParameter", clothoidSegment->getEndParameter());
		liaClothoidArcSegment.appendChild(gmlEndParameter);
		
		liaGeometry.appendChild(liaClothoidArcSegment);
		liaSegment.appendChild(liaGeometry);
		return liaSegment;
	};

	/*Converts a HorizontalAlignment2D into the lia:horizontal XML element.*/
	auto convertHorizontalAlignment2D = 
		[&](buw::ReferenceCounted<buw::HorizontalAlignment2D> horizontalAlignment2D)->QDomElement
	{
		QDomElement liaHorizontal = doc.createElement("lia:horizontal");
		QDomElement liaAlignment2DHorizontal = doc.createElement("lia:Alignment2DHorizontal");
		liaHorizontal.appendChild(liaAlignment2DHorizontal);

		/*Set an empty id for now since it can't be determined from the internal data respresentation.*/
		liaAlignment2DHorizontal.setAttribute("gml:id", "empty");

		/*These fields are required by the specification but can't be determined fro the internal data representation.*/
		QDomElement liaLocation = doc.createElement("lia:location");
		liaAlignment2DHorizontal.appendChild(liaLocation);
		QDomElement liaDescription = doc.createElement("lia:description");
		liaAlignment2DHorizontal.appendChild(liaDescription);
		QDomElement liaState = doc.createElement("lia:state");
		liaAlignment2DHorizontal.appendChild(liaState);

		/*Iterate over all horizontal alignment segments and convert them into the correct representation.*/
		if(horizontalAlignment2D->getAlignmentElementCount() > 0) {
			for(int i = 0; i < horizontalAlignment2D->getAlignmentElementCount(); i++) {
				auto horizontalAlignmentElement2D = horizontalAlignment2D->getAlignmentElementByIndex(i);

				/*Initialize possible child element implementations.*/
				buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> lineSegment = nullptr;
				buw::ReferenceCounted<buw::HorizontalAlignmentElement2DArc> arcSegment = nullptr;
				buw::ReferenceCounted<buw::HorizontalAlignmentElement2DBlossCurve> blossSegment = nullptr;
				buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> clothoidSegment = nullptr;

				/*Convert alignment element to corresponding type depending on its eHorizontalAlignmentType.*/
				switch(horizontalAlignmentElement2D->getAlignmentType()) {
				case buw::eHorizontalAlignmentType::Line:
					lineSegment = std::static_pointer_cast<buw::HorizontalAlignmentElement2DLine>(horizontalAlignmentElement2D);
					liaAlignment2DHorizontal.appendChild(convertHorizontalAlignmentElement2DLine(lineSegment));
					break;
				case buw::eHorizontalAlignmentType::Arc:
					arcSegment = std::static_pointer_cast<buw::HorizontalAlignmentElement2DArc>(horizontalAlignmentElement2D);
					liaAlignment2DHorizontal.appendChild(convertHorizontalAlignmentElement2DArc(arcSegment));
					break;
				case buw::eHorizontalAlignmentType::Bloss:
					blossSegment = std::static_pointer_cast<buw::HorizontalAlignmentElement2DBlossCurve>(horizontalAlignmentElement2D);
					liaAlignment2DHorizontal.appendChild(convertHorizontalAlignmentElement2DBlossCurve(blossSegment));
					break;
				case buw::eHorizontalAlignmentType::Clothoid:
					clothoidSegment = std::static_pointer_cast<buw::HorizontalAlignmentElement2DClothoid>(horizontalAlignmentElement2D);
					liaAlignment2DHorizontal.appendChild(convertHorizontalAlignmentElement2DClothoid(clothoidSegment));
					break;
				default:
					QString message = "Invalid HorizontalAlignment2D, undefined segment found.";
					throw buw::Exception(message.toStdString().data());
				}
			}
		}
		else {
			QString message = "Invalid HorizontalAlignment2D, no segments found.";
			throw buw::Exception(message.toStdString().data());
		}

		return liaHorizontal;
	};

	/*Convert the VerticalAlignment2D to a lia:vertical XML element.*/
	auto convertVerticalAlignment2D = 
		[&](buw::ReferenceCounted<buw::VerticalAlignment2D> verticalAlignment2D) -> QDomElement
	{
		QDomElement liaVertical = doc.createElement("lia:vertical");
		QDomElement liaAlignment2DVertical = doc.createElement("lia:Alignment2DVertical");

		/*Set empty ID since no representation is present in the internal representation.*/
		liaAlignment2DVertical.setAttribute("gml:id", "empty");

		/*These fields are required by the specification but can't be determined fro the internal data representation.*/
		QDomElement liaLocation = doc.createElement("lia:location");
		liaAlignment2DVertical.appendChild(liaLocation);
		QDomElement liaDescription = doc.createElement("lia:description");
		liaAlignment2DVertical.appendChild(liaDescription);
		QDomElement liaState = doc.createElement("lia:state");
		liaAlignment2DVertical.appendChild(liaState);

		/*Determine the number of segments and if it is 0, throw an exception.*/
		int numSegments = verticalAlignment2D->getAlignmentElementCount();
		if(numSegments > 0) {
			/*Iterate over all segments and add them in their actual implementation*/
			//TODO: Implementation
			for(int i = 0; i < numSegments; i++) {
				auto verticalAlignmentElement2D = verticalAlignment2D->getAlignmentElementByIndex(i);
				auto type = verticalAlignmentElement2D->getAlignmentType();

				/*Determine underlying alignment type and convert to the corresponding XML representation.*/
				switch(type) {
				case buw::eVerticalAlignmentType::Line:
					//TODO: Implementation
					break;
				case buw::eVerticalAlignmentType::Arc:
					//TODO: Implementation
					break;
				case buw::eVerticalAlignmentType::Parabola:
					//TODO: Implementation
					break;
				default:
					QString message = "No implemented VerticalAlignmentElement2D type found.";
					throw buw::Exception(message.toStdString().data());
				}
			}
		}
		else {
			QString message = "Invalid VerticalAlignment2D, no segments found.";
			throw buw::Exception(message.toStdString().data());
		}

		liaVertical.appendChild(liaAlignment2DVertical);
		return liaVertical;
	};

	/*
	Converts a buw::Alignment2DBased3D and its horizontal and vertical alignment into XML elements.
	Starts the conversion of the single horizontal and vertical alignment elements.
	*/
	auto convertAlignment2DBased3D = 
		[&](buw::ReferenceCounted<buw::Alignment2DBased3D> alignment2D) ->QDomElement
	{
		QDomElement liaAlignmentCurve = doc.createElement("lia:AlignmentCurve");

		/*Convert the horizontal alignment which has to be existing, otherwise throw an exception.*/
		if(alignment2D->hasHorizontalAlignment()) {
			liaAlignmentCurve.appendChild(convertHorizontalAlignment2D(alignment2D->getHorizontalAlignment()));
		}
		else {
			QString message = "Invalid alignment, no horizontal alignment found. Node name is " + QString(alignment2D->getName().toStdString().data());
			throw buw::Exception(message.toStdString().data());
		}

		/*Convert the vertical alignments, if they don't exist just skip this part.*/
		if(alignment2D->hasVerticalAlignment()) {
			//TODO: Implement vertical alignment.
		}

		return liaAlignmentCurve;
	};

	/*
	Converts the abstract buw::IAlignment3D to either a buw::Alignment2DBased3D or Alignment3DBased3D.
	Its children are added as children to the XML element.
	*/
	auto convertAlignment = 
		[&](buw::ReferenceCounted<buw::IAlignment3D> alignment) ->QDomElement
	{
		/*An alignment is always surrounded by the feature environment.*/
		QDomElement feature = doc.createElement("feature");

		/*A lia:Alignment has an gml:id as attribute and gml:name, gml:description.*/
		QDomElement liaAlignment = doc.createElement("lia:Alignment");
		liaAlignment.setAttribute("gml:id", QString(alignment->getName().toStdString().data()));
		feature.appendChild(liaAlignment);
		
		/*Use type as description since no real description is available.*/
		QDomElement gmlDescription = doc.createElement("gml:description");
		QDomText gmlDescriptionText = doc.createTextNode(QString(buw::e3DAlignmentTypeToString(alignment->getType()).data()));
		gmlDescription.appendChild(gmlDescriptionText);
		liaAlignment.appendChild(gmlDescription);

		/*Name currently has the same value as ID since there is no real difference.*/
		QDomElement gmlName = doc.createElement("gml:name");
		QDomText gmlNameText = doc.createTextNode(QString(alignment->getName().toStdString().data()));
		gmlName.appendChild(gmlNameText);
		liaAlignment.appendChild(gmlName);

		/*An alignmentID has an identifier and a scope. Identifier is again the alignment name.*/
		QDomElement liaAlignmentID = doc.createElement("lia:alignmentID");
		QDomElement liaIdentifier = doc.createElement("lia:identifier");
		QDomText liaIdentifierText = doc.createTextNode(QString(alignment->getName().toStdString().data()));
		liaIdentifier.appendChild(liaIdentifierText);
		liaAlignmentID.appendChild(liaIdentifier);

		/*Keep empty since there is no representation in the internal file format.*/
		QDomElement liaScope = doc.createElement("lia:scope");
		liaAlignmentID.appendChild(liaScope);
		liaAlignment.appendChild(liaAlignmentID);

		QDomElement liaGeometry = doc.createElement("lia:geometry");
		liaAlignment.appendChild(liaGeometry);

		/*Create pointers for all possible implementation types*/
		buw::ReferenceCounted<buw::Alignment2DBased3D> alignment2D = nullptr;
		buw::ReferenceCounted<buw::Alignment3DBased3D> alignment3D = nullptr;

		/*Depending on the alignment type convert itself and children etc.*/
		switch(alignment->getType()) {
		case buw::e3DAlignmentType::e2DBased: 
			alignment2D = std::static_pointer_cast<buw::Alignment2DBased3D>(alignment);
			liaGeometry.appendChild(convertAlignment2DBased3D(alignment2D));
			break;
		case buw::e3DAlignmentType::e3DBased:
			//TODO: e3DBased
			alignment3D = std::static_pointer_cast<buw::Alignment3DBased3D>(alignment);
			break;
		default:
			QString message = "Invalid alignment. Node name is " + QString(alignment->getName().toStdString().data());
			throw buw::Exception(message.toStdString().data());
		}
		
		return feature;
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

	/*Convert the alignmentModel to its XML representation.*/
	if(alignmentModel) {
		doc.appendChild(convertAlignmentModel(alignmentModel));
	}

	/*Open file to write to.*/
	QFile file(filename.c_str());
	if(!file.open(QIODevice::WriteOnly)) {
		throw buw::Exception("Failed opening file for writing.");
	}

	/*Write document to file.*/
	QTextStream textStream(&file);
	doc.save(textStream, 4);
	file.close();
}
