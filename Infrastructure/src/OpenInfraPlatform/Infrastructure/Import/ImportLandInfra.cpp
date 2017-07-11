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

#include <BlueFramework/Core/Diagnostics/log.h>

#include <QtXml>
#include <QXmlSchema.h>
#include <QUrl>
#include <QXmlSchemaValidator.h>
#include <QString>


namespace OpenInfraPlatform {
	namespace Infrastructure {

		const bool ImportLandInfra::validateHeader(const QString &header)
		{
			return true;
		}

		

		buw::ReferenceCounted<buw::AlignmentModel> LandInfraNode::toAlignmentModel()
		{
			buw::ReferenceCounted<buw::AlignmentModel> alignmentModel = buw::makeReferenceCounted<buw::AlignmentModel>();

			QDomNodeList children = childNodes();

			for (int i = 0; i < children.count(); i++) {
				QDomNode child = children.at(i);
				if (child.nodeName() == "feature") {
					LandInfraNode alignmentNode = child.firstChild();
					buw::ReferenceCounted<buw::Alignment2DBased3D> alignment = std::static_pointer_cast<buw::Alignment2DBased3D>(alignmentNode.toIAlignment3D());
					alignmentModel->addAlignment(alignment);
				}
			}
			return alignmentModel;
		}

		buw::ReferenceCounted<buw::IAlignment3D> LandInfraNode::toIAlignment3D()
		{
			if (!(nodeName() == "lia:Alignment")) {
				BLUE_LOG(error) << "Invalid lia:Alignment node. Node name is " << nodeName();
				throw buw::Exception("Invalid lia:Alignment node.");
			}

			QDomNodeList children = childNodes();

			QString name;

			for (int i = 0; i < children.count(); i++) {
				LandInfraNode child = children.at(i);
				if (child.nodeName() == "lia:alignmentID")
					name = child.firstChild().nodeValue();

				if (child.nodeName() == "lia:geometry") {
					if (child.hasChildNodes()) {
						LandInfraNode alignmentCurve = child.firstChild();
						return alignmentCurve.toAlignment2DBased3D();
					}
				}
			}
			
			throw buw::Exception("Invalid lia:Alignment node.");
		}

		buw::ReferenceCounted<buw::Alignment2DBased3D> LandInfraNode::toAlignment2DBased3D()
		{
			buw::ReferenceCounted<buw::Alignment2DBased3D> alignment = buw::makeReferenceCounted<buw::Alignment2DBased3D>();

			if (!(nodeName() == "lia:AlignmentCurve")) {
				QString message = "Invalid lia:AlignmentCurve node. Node name is " + nodeName() + ".Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}

			QDomNodeList children = childNodes();
			for (int i = 0; i < children.count(); i++) {
				QDomNode child = children.at(i);
				if (child.nodeName() == "lia:horizontal") {
					if (child.hasChildNodes()) {
						auto horizontalAlignment = LandInfraNode(child.firstChild()).toHorizontalAlignment2D();
						alignment->setHorizontalAlignment(horizontalAlignment);
					}
					else {
						alignment->setHorizontalAlignment(buw::makeReferenceCounted<buw::HorizontalAlignment2D>());
					}
				}
				if (child.nodeName() == "lia:vertical") {
					//TODO
				}
			}			
			return alignment;
		}

		buw::ReferenceCounted<buw::HorizontalAlignment2D> LandInfraNode::toHorizontalAlignment2D()
		{
			if (!(nodeName() == "lia:Alignment2DHorizontal")) {
				QString message = "Invalid lia:Alignment2DHorizontal node. Node name is " + nodeName() + ".Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}			
			
			buw::ReferenceCounted<buw::HorizontalAlignment2D> horizontalAlignment = buw::makeReferenceCounted<buw::HorizontalAlignment2D>();

			QDomNodeList children = childNodes();
			if (!(children.count() > 3)) {
				BLUE_LOG(error) << "Invalid lia:Alignment2DHorizontal node. Alignment has no segments. " << nodeName();
				return nullptr;
			}

			/*A horizontal alignment can have an unbounded number of segments.*/
			for (int i = 3; i < children.count(); i++) {
				LandInfraNode child = children.at(i);
				auto element = child.toHorizontalAlignmentElement2D();
				horizontalAlignment->addElement(child.toHorizontalAlignmentElement2D());				
			}

			return horizontalAlignment;
		}

		buw::ReferenceCounted<buw::HorizontalAlignmentElement2D> LandInfraNode::toHorizontalAlignmentElement2D()
		{
			/*Throw if we process a wrong node.*/
			if (!(nodeName() == "lia:segment")) {
				QString message = "Invalid lia:segment node. Node name is " + nodeName() + ".Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}

			buw::ReferenceCounted<buw::HorizontalAlignmentElement2D> alignmentElement = nullptr;
			QDomNodeList children = childNodes();

			for (int i = 0; i < children.count(); i++) {
				/*Check whether we can find a geometry specification*/
				if (children.at(i).nodeName() == "lia:geometry") {
					LandInfraNode segment = children.at(i).firstChild();

					/*Check and return type of horizontal alignment element.*/
					if (segment.nodeName() == "lia:lineSegment")
						alignmentElement = segment.toHorizontalAlignmentElement2DLine();
					else if(segment.nodeName() == "lia:clothoidArcSegment")
						alignmentElement = segment.toHorizontalAlignmentElement2DClothoid();
					else if(segment.nodeName() == "lia:circularArcSegment")
						alignmentElement = segment.toHorizontalAlignmentElement2DArc();
				}
			}
			if (!(alignmentElement)) {
				BLUE_LOG(error) << "No implemented HorizontalAlignmentElement2D type found. Line: " << lineNumber();
			}
			return alignmentElement;
		}

		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> LandInfraNode::toHorizontalAlignmentElement2DLine()
		{
			if (!(nodeName() == "lia:lineSegment")) {
				QString message = "Node name is " + nodeName() + ".Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}

			/*A line segment is given by its start and end point.*/
			QDomNodeList children = childNodes();
			if (!(children.count() >= 2)) {
				QString message = "Invalid lia:lineSegment node. Node has less than 2 children. Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}
			else {
				buw::Vector2d start = LandInfraNode(children.at(0)).toVector2d();
				buw::Vector2d end = LandInfraNode(children.at(1)).toVector2d();
				return buw::makeReferenceCounted<buw::HorizontalAlignmentElement2DLine>(start, end);
			}			
		}

		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> LandInfraNode::toHorizontalAlignmentElement2DClothoid()
		{
			if (!(nodeName() == "lia:clothoidArcSegment")) {
				QString message = "Invalid lia:clothoidArcSegment Node. Node name is " + nodeName() + ".Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}

			//TODO: Implementation!
			return nullptr;
		}

		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DArc> LandInfraNode::toHorizontalAlignmentElement2DArc()
		{
			if (!(nodeName() == "lia:circularArcSegment")) {
				QString message = "Invalid lia:circularArcSegment Node. Node name is " + nodeName() + ".Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}

			if (hasChildNodes()) {
				QDomNode arcSpecification = firstChild();

				/*A circularArcByCenterPoint is given by its center, startAngle, endAngle and radius.*/
				if (arcSpecification.nodeName() == "lia:circularArcByCenterPoint") {
					/*Determine center point.*/
					LandInfraNode centerPointNode = LandInfraNode(arcSpecification.firstChild());
					buw::Vector2d centerPoint = centerPointNode.toVector2d();

					/*Determine radius.*/
					LandInfraNode radiusNode = centerPointNode.nextSibling();
					double radius = radiusNode.toElement().text().toDouble();

					/*Determine start angle.*/
					LandInfraNode startAngleNode = radiusNode.nextSibling();
					double startAngle = startAngleNode.toElement().text().toDouble();

					/*Check unit of measurement for start angle.*/
					QDomNamedNodeMap attributes = startAngleNode.attributes();
					if (attributes.contains("uom")) {
						QDomNode unitOfMeasurement = attributes.namedItem("uom");
						if (unitOfMeasurement.nodeValue() == "r")
							startAngle = buw::radianToDegree(startAngle);
					}
					else {
						/*Assume we have a degree unit of measurement, but we should report this.*/
						BLUE_LOG(warning) << "No uom attribute found, assuming degree. Line: " << lineNumber();
					}

					/*Determine end angle.*/
					LandInfraNode endAngleNode = startAngleNode.nextSibling();
					double endAngle = endAngleNode.toElement().text().toDouble();

					/*Check unit of measurement for end angle.*/
					attributes = endAngleNode.attributes();
					if (attributes.contains("uom")) {
						QDomNode unitOfMeasurement = attributes.namedItem("uom");
						if (unitOfMeasurement.nodeValue() == "r")
							startAngle = buw::radianToDegree(startAngle);
					}
					else {
						/*Assume we have a degree unit of measurement, but we should report this.*/
						BLUE_LOG(warning) << "No uom attribute found, assuming degree. Line: " << lineNumber();
					}

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
			if (!(nodeName() == "gml:pos")) {
				QString message = "Invalid gml:pos node. Node name is " + nodeName() + ".Line: " +  QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}
						
			QStringList position = toElement().text().split(' ');
			if (!(position.count() < 2)) {
				double posX = position[0].toDouble();
				double posY = position[1].toDouble();
				return buw::Vector2d(posX, posY);
			}
			else {
				QString message = "Invalid gml:pos node. Position has less than 2 dimensions. Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}
		}
		
		ImportLandInfra::ImportLandInfra(const std::string& filename) : Import(filename) {

			QFile file(filename.c_str());
			if (!file.open(QIODevice::ReadOnly))
				throw buw::Exception("Unable to open the file.");			

#ifdef _VALIDATE
			if (QFile("schema/LandInfra_Part3Alignment0321.xsd").exists()) {
				QFile landInfraSchema("schema/LandInfra_Part3Alignment0321.xsd");
				if (!landInfraSchema.open(QIODevice::ReadOnly))
						throw buw::Exception("Unable to open the file.");
				QUrl schemaUrl("file:schema/Part3Alignment0321.xsd");
				QXmlSchema schema;
				

				if(!(schema.load(&landInfraSchema, QUrl::fromLocalFile(landInfraSchema.fileName()))))
					throw buw::Exception("Failed loading schema.");


				QXmlSchemaValidator validator(schema);

				if (!(validator.validate(&file, QUrl::fromLocalFile(file.fileName()))))
					throw buw::Exception("Schema validation failed.");
				else
					file.seek(0);
			}
#endif

			QXmlInputSource source(&file);
			QDomDocument document;
			
			document.setContent(&source, false);

			BLUE_LOG(trace) << "Importing " << filename;

			QDomNode xml = document.firstChild();
			if (!(xml.nodeName() == "xml")) {
				BLUE_LOG(error) << xml.nodeName();
				throw buw::Exception("Invalid XML document.");
			}

			QStringList xmlValues = xml.nodeValue().split(' ');

			if (!(xmlValues[0].split('=')[0] == "version")) {
				BLUE_LOG(error) << xmlValues[0];
				throw buw::Exception("Invalid XML document: No version specified.");
			}
			else
				BLUE_LOG(trace) << "XML Version: " << xmlValues[0].split('=')[1];

			if (!(xmlValues[1] == "encoding=\'UTF-8\'")) {
				BLUE_LOG(error) << xmlValues[1];
				throw buw::Exception("Invalid XML document: No UTF-8 encoding.");
			}
			else
				BLUE_LOG(trace) << "XML Encoding: " << xmlValues[1].split('=')[1];

			LandInfraNode dataset = xml.nextSibling();
			while (!(dataset.nodeName() == "LandInfraDataset")) {
				if ((dataset = xml.nextSibling()).isNull())
					throw buw::Exception("Invalid XML document: No LandInfraDataset found.");
			}
			
			QString header = dataset.nodeValue();
			if (!validateHeader(header)) {
				BLUE_LOG(error) << header;
				throw new buw::Exception("Invalid LandInfraDataset header.");
			}
			
			if (!(dataset.hasChildNodes()))
				throw buw::Exception("Dataset does not contain any children.");
			
			alignmentModel_ = dataset.toAlignmentModel();			
		}		
	}
}