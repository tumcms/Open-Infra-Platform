/*
Copyright (c) 2021 Technical University of Munich
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

		void validateNode(const QDomNode& node, QString name)
		{
			if(!(node.nodeName() == name)) {
				QString message = "Invalid " + name + " node. Node name is " + node.nodeName() + ". Line: " + QString::number(node.lineNumber());
				throw buw::Exception(message.toStdString().data());
			}
		}

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
			validateNode(*this, "lia:Alignment");

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
			validateNode(*this, "lia:AlignmentCurve");

			buw::ReferenceCounted<buw::Alignment2DBased3D> alignment = buw::makeReferenceCounted<buw::Alignment2DBased3D>();
			QDomNodeList children = childNodes();

			/*Iterate over all children and add the horizontal alignments.*/
			for(int i = 0; i < children.size(); i++) {
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
			validateNode(*this, "lia:Alignment2DHorizontal");

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
				horizontalAlignment->addElement(element);
			}

			return horizontalAlignment;
		}

		buw::ReferenceCounted<buw::HorizontalAlignmentElement2D> LandInfraNode::toHorizontalAlignmentElement2D()
		{
			/*Cancel if node was falsely interpreted as lia:segment.*/
			validateNode(*this, "lia:segment");

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
					else if(segment.nodeName() == "lia:transitionSegment")
						alignmentElement = segment.toHorizontalAlignmentElement2DBlossCurve();
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
			validateNode(*this, "lia:lineSegment");

			/*A line segment is given by its start and end point.*/
			QDomNodeList children = childNodes();
			if(!(children.count() >= 2)) {
				QString message = "Invalid lia:lineSegment node. Node has less than 2 children. Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}
			else {
				/*Retrieve start and end points from positions and create line segment.*/
				buw::Vector2d start = LandInfraNode(children.at(0)).toVector2d();
				buw::Vector2d end   = LandInfraNode(children.at(1)).toVector2d();
				return buw::makeReferenceCounted<buw::HorizontalAlignmentElement2DLine>(start, end);
			}
		}

		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> LandInfraNode::toHorizontalAlignmentElement2DClothoid()
		{
			/*Cancel if node was falsely interpreted as lia:clothoidArcSegment.*/
			validateNode(*this, "lia:clothoidArcSegment");

			/*Expecting four child nodes, otherwise cancel.*/
			QDomNodeList children = childNodes();
			if(children.size() == 4) {
				buw::clothoidDescription desc;

				/*Read refLocation from node.*/
				QDomNode refLocation = children.at(0);
				QDomNode affinePlacement = refLocation.firstChild();

				/*Determine startPosition.*/
				QStringList location = affinePlacement.childNodes().at(0).toElement().text().split(' ');
				if(location.count() >= 2) {
					double posX = location[0].toDouble();
					double posY = location[1].toDouble();
					desc.startPosition = buw::Vector2d(posX, posY);
				}
				else {
					QString message = "Invalid location, less than 2 dimensions. Node name is " + nodeName() + ".Line: " + QString::number(lineNumber());
					throw buw::Exception(message.toStdString().data());
				}

				/*Determine start direction.*/
				double startDirection = affinePlacement.childNodes().at(1).toElement().text().toDouble();

				/*Read scaleFactor, startParameter and endParameter.*/
				double scaleFactor    = children.at(1).toElement().text().toDouble();
				double startParameter = children.at(2).toElement().text().toDouble();
				double endParameter   = children.at(3).toElement().text().toDouble();

				/*Set clothoid constant, startCurvature and length.*/
				desc.clothoidConstant = scaleFactor;
				desc.startParameter   = startParameter;
				desc.endParameter     = endParameter;
				desc.startDirection	  = startDirection;
				/*Don't know yet how to determine from the given data whether it is cw or ccw, and if it's entry or not.*/
				desc.counterClockwise = false;
				
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
			validateNode(*this, "lia:circularArcSegment");

			if(hasChildNodes()) {
				QDomNode arcSpecification = firstChild();

				/*A circularArcByCenterPoint is given by its center, startAngle, endAngle and radius.*/
				if(arcSpecification.nodeName() == "lia:circularArcByCenterPoint") {

					/*Determine center point.*/
					LandInfraNode centerPointNode = LandInfraNode(arcSpecification.firstChild());
					buw::Vector2d centerPoint     = centerPointNode.toVector2d();

					/*Determine radius.*/
					LandInfraNode radiusNode = arcSpecification.childNodes().at(1);
					double radius;
					if(radiusNode.attributes().contains("uom")) {
						if(radiusNode.attributes().namedItem("uom").nodeValue() == "m") {
							radius = radiusNode.toElement().text().toDouble();
						}
					}
					else {
						radius = radiusNode.toElement().text().toDouble();
					}

					/*Lambda for setting the angles.*/
					auto getAngle = [&](LandInfraNode angle) -> double {
						QDomNamedNodeMap attributes = angle.attributes();

						/*Check unit of measurement for start angle.*/
						if(attributes.contains("uom")) {
							QDomNode unitOfMeasurement = attributes.namedItem("uom");
							if(unitOfMeasurement.nodeValue() == "r")
								return angle.toElement().text().toDouble();
							if(unitOfMeasurement.nodeValue() == "d")
								return buw::degreeToRadian(angle.toElement().text().toDouble());
						}
						else {
							/*Assume we have a degree unit of measurement, but we should report this.*/
							BLUE_LOG(warning) << "No uom attribute found, assuming degree. Line: " << QString::number(lineNumber()).toStdString();
							return buw::degreeToRadian(angle.toElement().text().toDouble());
						}
					};

					/*Determine start angle.*/
					double startAngle = getAngle(arcSpecification.childNodes().at(2));			

					/*Determine end angle.*/
					double endAngle = getAngle(arcSpecification.childNodes().at(3));
					
					/*Convert to intern representation for HorizontalAlignmentElement2DArc: center, start, end, clockwise.*/
					buw::Vector2d center = centerPoint;

					/*Calculate point on circle at angle phi as x=cos(phi), y=sin(phi). Start position is center shifted by point on circle at startAngle.*/
					buw::Vector2d start = center + buw::Vector2d(std::cos(startAngle), std::sin(startAngle)) * radius;

					/*Calculate point on circle at angle phi as x=cos(phi), y=sin(phi). End position is center shifted by point on circle at endAngle.*/
					buw::Vector2d end = center + buw::Vector2d(std::cos(endAngle), std::sin(endAngle)) * radius;

					/*If endAngle is larger than startAngle, we have a clockwise rotation, otherwise it's counter clockwise.*/
					bool clockwise = endAngle >= startAngle ? true : false;
					return buw::makeReferenceCounted<buw::HorizontalAlignmentElement2DArc>(center, start, end, clockwise);
				}
				else if(arcSpecification.nodeName() == "lia:circularArc") {
					QDomNodeList children = arcSpecification.childNodes();

					/*Always specified by 3 positions.*/
					buw::Vector2d pos0;
					buw::Vector2d pos1;
					buw::Vector2d pos2;
					QStringList positions; //Switch statement forces initialization.

					switch(children.size()) {
					/*If there is only one node, we assume a gml:posList.*/
					case 1:
						positions = children.at(0).toElement().text().split(' ');

						/*If we have less than 6 values, throw exception.*/
						if(positions.size() == 6) {
							pos0 = buw::Vector2d(positions[0].toDouble(), positions[1].toDouble());
							pos1 = buw::Vector2d(positions[2].toDouble(), positions[3].toDouble());
							pos2 = buw::Vector2d(positions[4].toDouble(), positions[5].toDouble());
						}
						else {
							QString message = "Invalid lia:circularArcSegment Node. Not enough points specified. Line: " + QString::number(lineNumber());
							throw buw::Exception(message.toStdString().data());
						}
						break;
					/*If there are three child nodes, each of them specifies a point on the circle.*/
					case 3:
						/*Retrieve the points, assuming pos0 is start and pos2 is end.*/
						pos0 = LandInfraNode(children.at(0)).toVector2d();
						pos1 = LandInfraNode(children.at(1)).toVector2d();
						pos2 = LandInfraNode(children.at(2)).toVector2d();
						break;
					/*If we have neither 1 nor 3 children, throw exception.*/
					default:
						QString message = "Invalid lia:circularArcSegment Node. Unknown circularArc specification. Line: " + QString::number(lineNumber());
						throw buw::Exception(message.toStdString().data());
					}

					/*Formula to calculate center point from three points on a circle.*/
					auto calculateCenter = [&]() -> buw::Vector2d {
						double cx, cy;
						double ma = (pos1.y() - pos0.y()) / (pos1.x() - pos0.x());
						double mb = (pos2.y() - pos1.y()) / (pos2.x() - pos1.x());
						cx = (ma * mb * (pos0.y() - pos2.y()) + mb * (pos0.x() + pos1.x()) - ma * (pos1.x() + pos2.x())) / (2 * (mb - ma));
						cy = (-1 / ma) * (cx - (pos0.x() + pos1.x()) / 2) + (pos0.y() + pos1.y()) / 2;
						buw::Vector2d center = buw::Vector2d(cx, cy);
						return center;
					};

					/*Calculate center point.*/
					buw::Vector2d center = calculateCenter();

					/*Calculate whether the arc is clockwise or counter clockwise depending on start and end point.*/
					auto isClockwise = [&]() -> bool {
						/*Get vectors to points from center.*/
						buw::Vector2d v0 = pos0 - center;
						buw::Vector2d v1 = pos1 - center;
						buw::Vector2d v2 = pos2 - center;

						/*If the angle between start and intermediate is smaller than start and end, it's clockwise.*/
						return buw::calculateAngleBetweenVectors(v0, v1) < buw::calculateAngleBetweenVectors(v0, v2);
					};

					return buw::makeReferenceCounted<buw::HorizontalAlignmentElement2DArc>(center, pos0, pos2, isClockwise());
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

		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DBlossCurve> LandInfraNode::toHorizontalAlignmentElement2DBlossCurve()
		{
			/*Cancel if node was falsely interpreted as lia:transitionSegment.*/
			validateNode(*this, "lia:transitionSegment");

			QDomNodeList children = childNodes();
			if(children.size() == 5) {
				/*Retrieve all specifications from child nodes.*/
				QDomNode referenceLocation = children.at(0);
				QDomNode length = children.at(1);
				QDomNode startCurvature = children.at(2);
				QDomNode endCurvature = children.at(3);
				QDomNode transitionType = children.at(4);

				/*Currently only Bloss curve is supported as transition type.*/
				if(transitionType.attributes().contains("xlink:title")) {
					QDomNode title = transitionType.attributes().namedItem("xlink:title");
					if(title.nodeValue() != "Bloss") {
						BLUE_LOG(error) << "Unsupported transition type!";
					}
				}
				/*Fill in Bloss curve description, can't determine absolute position from data specification.*/
				buw::blossDescription desc;
				desc.length = length.nodeValue().toDouble();
				
				/*TODO: Get math behind calculation of radius etc., fill with dummy values by now!*/
				desc.radius = 1;
				desc.startDirection = 1;
				desc.startPosition = buw::Vector2d(1.0, 1.0);
				desc.counterClockwise = false;
				desc.entry = true;
				
				return buw::makeReferenceCounted<buw::HorizontalAlignmentElement2DBlossCurve>(desc);
			}
			else {
				QString message = "Invalid lia:transitionSegment Node. Not all required specifications found. Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}
		}

		buw::ReferenceCounted<buw::VerticalAlignment2D> LandInfraNode::toVerticalAlignment2D()
		{
			/*Cancel if node was falsely interpreted as lia:Alignment2DVertical.*/
			validateNode(*this, "lia:Alignment2DVertical");

			buw::ReferenceCounted<buw::VerticalAlignment2D> verticalAlignment = buw::makeReferenceCounted<buw::VerticalAlignment2D>();
			QDomNodeList children = childNodes();			
			int numChildren = children.size();
			if(numChildren > 4) {
				for(int i = 0; i < numChildren; i++) {
					auto child = children.at(i);
					if(child.nodeName() == "lia:location") {
						//TODO: location implementation
					}
					else if(child.nodeName() == "lia:description") {
						//TODO: description implementation
					}
					else if(child.nodeName() == "lia:state") {
						//TODO:: state implementation
					}
					else if(child.nodeName() == "lia:alignmentOffset") {
						//TODO: alignmentoffset implementation
					}
					else if(child.nodeName() == "lia:segment") {
						//TODO: segment implementation
					}
					else if(child.nodeName() == "lia:measuredAlong") {
						//TODO: implement measuredAlong
					}
					else {
						QString message = "Invalid lia:Alignment2DVertical node. Invalid child node detected. Node name is " + nodeName() + ".Line: " + QString::number(lineNumber());
						throw buw::Exception(message.toStdString().data());
					}
				}
			}
			else {
				QString message = "Invalid lia:Alignment2DVertical node. Not all necessary attributes are present. Node name is " + nodeName() + ".Line: " + QString::number(lineNumber());
				throw buw::Exception(message.toStdString().data());
			}
		}

		buw::Vector2d LandInfraNode::toVector2d() const
		{
			/*Cancel if node was falsely interpreted as gml:pos.*/
			validateNode(*this, "gml:pos");

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
