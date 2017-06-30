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

#include "ImportRoadXML.h"

#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment2DBased3D.h"
#include <BlueFramework/Core/PropertySet.h>
#include <stack>
#include <QtXml>
#include <QtXmlPatterns>
#include <boost/noncopyable.hpp>

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		struct eRoadXMLParserState
		{
			enum Enum
			{
				CircleArc,
				ClothoArc,
				Segment,
				Track,
				XYCurve
			};
		};

		class QRoadXMLParser : public QXmlDefaultHandler
		{
		public:
			//! Default constructor.
			QRoadXMLParser()
			{
				alignmentModel_ = buw::makeReferenceCounted<buw::AlignmentModel>();
			}

			//! Virtual destructor.
			virtual ~QRoadXMLParser()
			{
			}

			bool startElement(const QString & /* unused */, const QString &name,
				const QString& /* unused */, const QXmlAttributes &attr)
			{
				if (name == "CircleArc")
				{
					state.push(eRoadXMLParserState::CircleArc);

					// properties
					double curvature = attr.value("curvature").toDouble();
					double length = attr.value("length").toDouble();

					CircleArcProperties.clear();
					CircleArcProperties.setDouble("curvature", curvature);
					CircleArcProperties.setDouble("length", length);
				}

				if (name == "ClothoArc")
				{
					state.push(eRoadXMLParserState::ClothoArc);

					// properties
					double length = attr.value("length").toDouble();
					double endCurvature = attr.value("endCurvature").toDouble();
					double startCurvature = attr.value("startCurvature").toDouble();

					ClothoArcProperties.clear();
					ClothoArcProperties.setDouble("length", length);
					ClothoArcProperties.setDouble("endCurvature", endCurvature);
					ClothoArcProperties.setDouble("startCurvature", startCurvature);
				}

				if (name == "Segment")
				{
					state.push(eRoadXMLParserState::Segment);

					// properties
					double length = attr.value("length").toDouble();

					SegmentProperties.clear();
					SegmentProperties.setDouble("length", length);
				}

				if (name == "Track")
				{
					state.push(eRoadXMLParserState::Track);
				}

				if (name == "XYCurve")
				{
					state.push(eRoadXMLParserState::XYCurve);

					// properties
					double x = attr.value("x").toDouble();
					double y = attr.value("y").toDouble();
					double direction = attr.value("direction").toDouble();

					XYCurveProperties.clear();
					XYCurveProperties.setDouble("x", x);
					XYCurveProperties.setDouble("y", y);
					XYCurveProperties.setDouble("direction", direction);
				}

				return true;
			}

			bool characters(const QString& ch)
			{
				return true;
			}

			bool endElement(const QString & /* unused */, const QString &name,
				const QString& /* unused */)
			{
				if (name == "CircleArc")
				{
					BLUE_ASSERT(state.top() == eRoadXMLParserState::CircleArc, "Invalid state.");
					state.pop();

					double radius = std::abs(1.0 / CircleArcProperties.getDouble("curvature"));

					bool clockwise = radius < 0 ? true : false;
					buw::Vector2d start = buw::Vector2d(XYCurveProperties.getDouble("x"), XYCurveProperties.getDouble("y"));

					//------------------------------------------------------------------------
					/*
					double e = GetEndAngle();
					double s = GetStartAngle();
					double d = e - s;

					double x = 0.0;
					double y = 0.0;
					double offset = 0.0;
					if(d < 0.0) {
					offset = PI;
					}
					x = (GetPosition().GetX() + std::cos(((s + e) / 2.0) + offset) * GetRadius());
					y = (GetPosition().GetY() + -std::sin(((s + e) / 2.0) + offset) * GetRadius());

					*/
					/*
					buw::ReferenceCounted<buw::Arc> arc = std::make_shared<buw::Arc>(
					center_,
					start_,
					end_,
					clockwise_);
					*/

					std::cout << radius << std::endl;
				}

				if (name == "ClothoArc")
				{
					BLUE_ASSERT(state.top() == eRoadXMLParserState::ClothoArc, "Invalid state.");
					state.pop();
				}

				if (name == "Segment")
				{
					BLUE_ASSERT(state.top() == eRoadXMLParserState::Segment, "Invalid state.");
					state.pop();
				}

				if (name == "Track")
				{
					BLUE_ASSERT(state.top() == eRoadXMLParserState::Track, "Invalid state.");
					state.pop();
				}

				if (name == "XYCurve")
				{
					BLUE_ASSERT(state.top() == eRoadXMLParserState::XYCurve, "Invalid state.");
					state.pop();
				}

				return true;
			}

			buw::ReferenceCounted<buw::AlignmentModel> getAlignmentModel()
			{
				return alignmentModel_;
			}

		private:
			buw::PropertySet XYCurveProperties;
			buw::PropertySet CircleArcProperties;
			buw::PropertySet SegmentProperties;
			buw::PropertySet ClothoArcProperties;

			std::stack<eRoadXMLParserState::Enum> state;
			buw::ReferenceCounted<buw::AlignmentModel> alignmentModel_;
		}; // end class QRoadXMLParser


		ImportRoadXML::ImportRoadXML(const std::string& filename) :
			Import(filename)
		{
			QRoadXMLParser parser;

			//QFile schemaFile("C:/dev/OpenInfraPlatform/schema/LandXML-1.2.xsd");
			//QXmlSchema schema;

			//XmlSchemaVerificationMessageHandler handler;
			//schema.setMessageHandler(&handler);
			//if (!schemaFile.open(QIODevice::ReadOnly))
			//	throw buw::Exception("Unable to open the XML schema!");
			//if (!schema.load(schemaFile.readAll()))
			//	throw buw::Exception("Unable to parse the XML schema!");

			//QXmlSchemaValidator validator(schema);
			QFile file(filename.c_str());
			if (!file.open(QIODevice::ReadOnly))
				throw buw::Exception("Unable to open the file.");
			//if (!validator.validate(&file))
			//	throw buw::Exception("Unable to validate the file.");

			QXmlInputSource source(&file);
			file.seek(0);
			QXmlSimpleReader reader;
			reader.setContentHandler(&parser);
			if (!reader.parse(source))
				throw buw::Exception("Unable to parse the file.");

			alignmentModel_ = parser.getAlignmentModel();
		}

	}
}