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

#include "ImportLandInfra.h"
#include <OpenInfraPlatform/DataManagement/Data.h>

#include <BlueFramework/Core/Diagnostics/log.h>


#include <QtXml>
#include <QXmlSchema.h>
#include <QUrl>
#include <QXmlSchemaValidator.h>
#include <QString>
#include <QMessageBox.h>


namespace OpenInfraPlatform {
	namespace Infrastructure {

		const bool ImportLandInfra::validateHeader(const QString &header)
		{
			//TODO: Implementation.
			return true;
		}

		buw::ReferenceCounted<buw::AlignmentModel> LandInfraNode::toAlignmentModel()
		{
			buw::ReferenceCounted<buw::AlignmentModel> alignmentModel = buw::makeReferenceCounted<buw::AlignmentModel>();
			QDomNodeList children = childNodes();

			/*Iterate over all children to add Alignment2DBased3D to alignmentModel.*/
			for(int i = 0; i < children.count(); i++) {
				QDomNode child = children.at(i);
				if(child.nodeName() == "feature") {
					LandInfraNode alignmentNode = child.firstChild();
					buw::ReferenceCounted<buw::Alignment2DBased3D> alignment = std::static_pointer_cast<buw::Alignment2DBased3D>(alignmentNode.toIAlignment3D());
					alignmentModel->addAlignment(alignment);
				}
			}

			return alignmentModel;
		}

		buw::ReferenceCounted<buw::IAlignment3D> LandInfraNode::toIAlignment3D()
		{
			/*Cancel if node was falsely interpreted as lia:Alignment.*/
			if(!(nodeName() == "lia:Alignment")) {
				QString message = "Invalid lia:Alignment node. Node name is " + nodeName() + ". Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}

			QDomNodeList children = childNodes();
			QString name;

			/*Iterate over all children and add Alignment2DBased3D to alignment.*/
			for(int i = 0; i < children.count(); i++) {
				LandInfraNode child = children.at(i);

				/*Variable "name" is currently unused.*/
				if(child.nodeName() == "lia:alignmentID")
					name = child.firstChild().nodeValue();

				if(child.nodeName() == "lia:geometry") {
					if(child.hasChildNodes()) {
						LandInfraNode alignmentCurve = child.firstChild();
						return alignmentCurve.toAlignment2DBased3D();
					}
				}
			}

			throw buw::Exception("Invalid lia:Alignment node.");
		}

		buw::ReferenceCounted<buw::Alignment2DBased3D> LandInfraNode::toAlignment2DBased3D()
		{
			/*Cancel if node was falsely interpreted as lia:AlignmentCurve.*/
			if(!(nodeName() == "lia:AlignmentCurve")) {
				QString message = "Invalid lia:AlignmentCurve node. Node name is " + nodeName() + ".Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}

			buw::ReferenceCounted<buw::Alignment2DBased3D> alignment = buw::makeReferenceCounted<buw::Alignment2DBased3D>();
			QDomNodeList children = childNodes();

			/*Iterate over all children and add the horizontal alignments.*/
			for(int i = 0; i < children.count(); i++) {
				QDomNode child = children.at(i);

				/*Check whether we have a horizontal or vertical alignment.*/
				if(child.nodeName() == "lia:horizontal") {
					/*Add HorizontalAlignment2D from child to alignment if it contains one.*/
					if(child.hasChildNodes()) {
						auto horizontalAlignment = LandInfraNode(child.firstChild()).toHorizontalAlignment2D();
						alignment->setHorizontalAlignment(horizontalAlignment);
					}
					else {
						/*How to handle empty alignments?*/
						BLUE_LOG(warning) << "Empty alignment detected. Line " << QString::number(lineNumber()).toStdString();
						alignment->setHorizontalAlignment(buw::makeReferenceCounted<buw::HorizontalAlignment2D>());
					}
				}
				else if(child.nodeName() == "lia:vertical") {
					//TODO: Implementation
					throw buw::NotImplementedYetException("LandInfra vertical alignments are not yet implemented.");
				}
			}
			return alignment;
		}

		buw::ReferenceCounted<buw::HorizontalAlignment2D> LandInfraNode::toHorizontalAlignment2D()
		{
			/*Cancel if node was falsely interpreted as lia:Alignment2DHorizontal.*/
			if(!(nodeName() == "lia:Alignment2DHorizontal")) {
				QString message = "Invalid lia:Alignment2DHorizontal node. Node name is " + nodeName() + ".Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}

			buw::ReferenceCounted<buw::HorizontalAlignment2D> horizontalAlignment = buw::makeReferenceCounted<buw::HorizontalAlignment2D>();
			QDomNodeList children = childNodes();

			/*Abort if an invalid lia:Alignment2DHorizontal node is explored.*/
			if(!(children.count() > 3)) {
				QString message = "Invalid lia:Alignment2DHorizontal node. Alignment has no segments. " + nodeName() + ".Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}

			/*A horizontal alignment can have an unbounded number of segments.*/
			for(int i = 3; i < children.count(); i++) {
				LandInfraNode child = children.at(i);
				auto element = child.toHorizontalAlignmentElement2D();
				horizontalAlignment->addElement(child.toHorizontalAlignmentElement2D());
			}

			return horizontalAlignment;
		}

		buw::ReferenceCounted<buw::HorizontalAlignmentElement2D> LandInfraNode::toHorizontalAlignmentElement2D()
		{
			/*Cancel if node was falsely interpreted as lia:segment.*/
			if(!(nodeName() == "lia:segment")) {
				QString message = "Invalid lia:segment node. Node name is " + nodeName() + ".Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}

			buw::ReferenceCounted<buw::HorizontalAlignmentElement2D> alignmentElement = nullptr;
			QDomNodeList children = childNodes();

			for(int i = 0; i < children.count(); i++) {
				/*Check whether we can find a geometry specification*/
				if(children.at(i).nodeName() == "lia:geometry") {
					LandInfraNode segment = children.at(i).firstChild();

					/*Check and return type of horizontal alignment element.*/
					if(segment.nodeName() == "lia:lineSegment")
						alignmentElement = segment.toHorizontalAlignmentElement2DLine();
					else if(segment.nodeName() == "lia:clothoidArcSegment")
						alignmentElement = segment.toHorizontalAlignmentElement2DClothoid();
					else if(segment.nodeName() == "lia:circularArcSegment")
						alignmentElement = segment.toHorizontalAlignmentElement2DArc();
				}
			}
			if(!(alignmentElement)) {
				BLUE_LOG(error) << "No implemented HorizontalAlignmentElement2D type found. Line: " << QString::number(lineNumber()).toStdString();
			}
			return alignmentElement;
		}

		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> LandInfraNode::toHorizontalAlignmentElement2DLine()
		{
			/*Cancel if node was falsely interpreted as lia:lineSegment.*/
			if(!(nodeName() == "lia:lineSegment")) {
				QString message = "Node name is " + nodeName() + ".Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}

			/*A line segment is given by its start and end point.*/
			QDomNodeList children = childNodes();
			if(!(children.count() >= 2)) {
				QString message = "Invalid lia:lineSegment node. Node has less than 2 children. Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}
			else {
				buw::Vector2d start = LandInfraNode(children.at(0)).toVector2d();
				buw::Vector2d end   = LandInfraNode(children.at(1)).toVector2d();
				return buw::makeReferenceCounted<buw::HorizontalAlignmentElement2DLine>(start, end);
			}
		}

		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> LandInfraNode::toHorizontalAlignmentElement2DClothoid()
		{
			/*Cancel if node was falsely interpreted as lia:clothoidArcSegment.*/
			if(!(nodeName() == "lia:clothoidArcSegment")) {
				QString message = "Invalid lia:clothoidArcSegment Node. Node name is " + nodeName() + ".Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}

			/*Expecting four child nodes, otherwise cancel.*/
			QDomNodeList children = childNodes();
			if(children.size() == 4) {
				buw::clothoidDescription desc;

				/*Read refLocation from node.*/
				QDomNodeList refLocation = children.at(0).childNodes();

				/*Determine startPosition.*/
				QStringList location = refLocation.at(0).toElement().text().split(' ');
				if(!(location.count() == 2)) {
					double posX = location[0].toDouble();
					double posY = location[1].toDouble();
					desc.startPosition = buw::Vector2d(posX, posY);
				}

				/*Determine start direction.*/
				desc.startDirection = refLocation.at(1).toElement().text().toDouble();

				/*Read scaleFactor, startParameter and endParameter.*/
				double scaleFactor    = children.at(1).toElement().text().toDouble();
				double startParameter = children.at(2).toElement().text().toDouble();
				double endParameter   = children.at(3).toElement().text().toDouble();

				/*Set clothoid constant, startCurvature and length.*/
				desc.clothoidConstant = scaleFactor;
				desc.startCurvature   = startParameter;
				desc.length           = endParameter;

				return buw::makeReferenceCounted<buw::HorizontalAlignmentElement2DClothoid>(desc);				 
			}
			else {
				QString message = "Invalid lia:clothoidArcSegment Node. Wrong number of children. Node name is " + nodeName() + ".Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}
			throw buw::Exception("Unexpected Exception.");
		}

		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DArc> LandInfraNode::toHorizontalAlignmentElement2DArc()
		{
			/*Cancel if node was falsely interpreted as lia:circularArcSegment.*/
			if(!(nodeName() == "lia:circularArcSegment")) {
				QString message = "Invalid lia:circularArcSegment Node. Node name is " + nodeName() + ".Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}

			if(hasChildNodes()) {
				QDomNode arcSpecification = firstChild();

				/*A circularArcByCenterPoint is given by its center, startAngle, endAngle and radius.*/
				if(arcSpecification.nodeName() == "lia:circularArcByCenterPoint") {

					/*Determine center point.*/
					LandInfraNode centerPointNode = LandInfraNode(arcSpecification.firstChild());
					buw::Vector2d centerPoint     = centerPointNode.toVector2d();

					/*Determine radius.*/
					LandInfraNode radiusNode = centerPointNode.nextSibling();
					double radius            = radiusNode.toElement().text().toDouble();

					/*Lambda for setting the angles.*/
					auto getAngle = [&](LandInfraNode angle) -> double {
						QDomNamedNodeMap attributes = angle.attributes();

						/*Check unit of measurement for start angle.*/
						if(attributes.contains("uom")) {
							QDomNode unitOfMeasurement = attributes.namedItem("uom");
							if(unitOfMeasurement.nodeValue() == "r")
								return buw::radianToDegree(angle.toElement().text().toDouble());
						}
						else {
							/*Assume we have a degree unit of measurement, but we should report this.*/
							BLUE_LOG(warning) << "No uom attribute found, assuming degree. Line: " << QString::number(lineNumber()).toStdString();
							return angle.toElement().text().toDouble();
						}
					};

					/*Determine start angle.*/
					double startAngle = getAngle(radiusNode.nextSibling());			

					/*Determine end angle.*/
					double endAngle = getAngle(radiusNode.nextSibling());
					
					/*Convert to intern representation for HorizontalAlignmentElement2DArc: center, start, end, clockwise.*/
					buw::Vector2d center = centerPoint;

					/*Calculate point on circle at angle phi as x=cos(phi), y=sin(phi). Start position is center shifted by point on circle at startAngle.*/
					buw::Vector2d start = center + buw::Vector2d(std::cos(startAngle), std::sin(startAngle)) * radius;

					/*Calculate point on circle at angle phi as x=cos(phi), y=sin(phi). End position is center shifted by point on circle at endAngle.*/
					buw::Vector2d end = center + buw::Vector2d(std::cos(endAngle), std::sin(endAngle)) * radius;

					/*If endAngle is larger than startAngle, we have a clockwise rotation, otherwise it's counter clockwise.*/
					bool clockwise = endAngle > startAngle ? true : false;
					return buw::makeReferenceCounted<buw::HorizontalAlignmentElement2DArc>(center, start, end, clockwise);
				}
				else {
					/*Not all specifications are currently known or implemented.*/
					QString message = "Invalid lia:circularArcSegment Node. Unknown specification. Line: " + QString::number(lineNumber());
					throw buw::Exception(message.toStdString().data());
				}
			}
			else {
				QString message = "Invalid lia:circularArcSegment Node. Circular arc has no further specifications. Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}

		}

		buw::Vector2d LandInfraNode::toVector2d() const
		{
			/*Cancel if node was falsely interpreted as gml:pos.*/
			if(!(nodeName() == "gml:pos")) {
				QString message = "Invalid gml:pos node. Node name is " + nodeName() + ".Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}

			/*Determine x and y coordinates of given position.*/
			QStringList position = toElement().text().split(' ');
			if(!(position.count() < 2)) {
				double posX = position[0].toDouble();
				double posY = position[1].toDouble();
				return buw::Vector2d(posX, posY);
			}
			else {
				QString message = "Invalid gml:pos node. Position has less than 2 dimensions. Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}
		}

		/*Throws exceptions which are handled inside OpenInfraPlatform::AsyncJob::run().*/
		ImportLandInfra::ImportLandInfra(const std::string& filename) : Import(filename)
		{
			QFile file(filename.c_str());
			if(!file.open(QIODevice::ReadOnly))
				throw buw::Exception("Unable to open the file.");

			/*If _VALIDATE is defined, the file is validated according to the schema. Currently not working.*/
#ifdef _VALIDATE 
			if(QFile("schema/LandInfra_Part3Alignment0321.xsd").exists()) {
				QFile landInfraSchema("schema/LandInfra_Part3Alignment0321.xsd");
				if(!landInfraSchema.open(QIODevice::ReadOnly))
					throw buw::Exception("Unable to open the file.");
				QUrl schemaUrl("file:schema/Part3Alignment0321.xsd");
				QXmlSchema schema;


				if(!(schema.load(&landInfraSchema, QUrl::fromLocalFile(landInfraSchema.fileName()))))
					throw buw::Exception("Failed loading schema.");


				QXmlSchemaValidator validator(schema);

				if(!(validator.validate(&file, QUrl::fromLocalFile(file.fileName()))))
					throw buw::Exception("Schema validation failed.");
				else
					file.seek(0);
			}
#endif

			QXmlInputSource source(&file);
			QDomDocument document;

			document.setContent(&source, false);

			BLUE_LOG(trace) << "Importing " << filename;

			/*Cancel if file is no XML document.*/
			QDomNode xml = document.firstChild();
			if(!(xml.nodeName() == "xml")) {
				BLUE_LOG(error) << xml.nodeName().toStdString();
				throw buw::Exception("Invalid XML document.");
			}

			QStringList xmlValues = xml.nodeValue().split(' ');

			/*Check for valid XML version.*/
			if(!(xmlValues[0].split('=')[0] == "version")) {
				BLUE_LOG(error) << xmlValues[0].toStdString();
				throw buw::Exception("Invalid XML document: No version specified.");
			}
			else
				BLUE_LOG(trace) << "XML Version: " << xmlValues[0].split('=')[1].toStdString();

			/*Check for valid XML encoding.*/
			if(!(xmlValues[1] == "encoding=\'UTF-8\'")) {
				BLUE_LOG(error) << xmlValues[1].toStdString();
				throw buw::Exception("Invalid XML document: No UTF-8 encoding.");
			}
			else
				BLUE_LOG(trace) << "XML Encoding: " << xmlValues[1].split('=')[1].toStdString();

			/*Search for AlignmentModel specification.*/
			LandInfraNode dataset = xml.nextSibling();
			while(!(dataset.nodeName() == "LandInfraDataset")) {
				if((dataset = xml.nextSibling()).isNull())
					throw buw::Exception("Invalid XML document: No LandInfraDataset found.");
			}

			/*Check header.*/
			QString header = dataset.nodeValue();
			if(!validateHeader(header)) {
				BLUE_LOG(error) << header.toStdString();
				throw buw::Exception("Invalid LandInfraDataset header.");
			}

			/*Check for empty AlignmentModel.*/
			if(!(dataset.hasChildNodes()))
				throw buw::Exception("Dataset does not contain any children.");

			/*Read alignment model from the dataset.*/
			auto datasetModel = dataset.toAlignmentModel();
			alignmentModel_ = datasetModel;
		}
	}
}