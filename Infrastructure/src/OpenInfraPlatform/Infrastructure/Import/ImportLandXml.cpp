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

#include "ImportLandXml.h"

#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment3DBased3D.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DArc.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DBlossCurve.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DArbitraryCurve.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DArc.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DParabola.h"
#include "OpenInfraPlatform/Infrastructure/DigitalElevationModel/DigitalElevationModel.h"

//BLUE_DROP_COMPILER_LEVEL_TO_3
#include <QtXml>
#include <QtXmlPatterns>
//BLUE_RESTORE_COMPILER_WARNING_LEVEL

#include <algorithm>

namespace OpenInfraPlatform 
{
	namespace Infrastructure
	{
		enum class eLandXMLParserState
		{
			Alignment,
			Breakline,
			Center,
			CircCurve,
			CoordGeom,
			CrossSectPnt,
			CrossSect,
			CrossSects,
			CrossSectSurf,
			Curve,
			DesignCrossSectSurf,
			End,
			F,
			IrregularLine,
			Line,
			P,
			ParaCurve,
			PI,
			PntList2D,
			PntList3D,
			Pnts,
			ProfAlign,
			Profile,
			PVI,
			Spiral,
			Start,
			Surface,
			Undefined
		};

		struct parseElementInfo
		{
			eLandXMLParserState		state;
			buw::PropertySet		properties;
		};

		class LandXMLStateStack
		{
		public:
			LandXMLStateStack()
			{
				// the start state is "Undefined"
				parseElementInfo pei;
				pei.state = eLandXMLParserState::Undefined;
				stack_.push(pei);
			}

			virtual ~LandXMLStateStack()
			{
			}

			void push(const parseElementInfo& pei)
			{
				stack_.push(pei);
			}

			void push(const eLandXMLParserState state)
			{
				parseElementInfo pei;
				pei.state = state;
				stack_.push(pei);
			}

			buw::PropertySet& topPropertySet()
			{
				return stack_.top().properties;
			}

			const eLandXMLParserState& topParserState() const
			{
				return stack_.top().state;
			}

			parseElementInfo& top()
			{
				return stack_.top();
			}

			const parseElementInfo& top() const
			{
				return stack_.top();
			}

			void pop()
			{
				stack_.pop();
			}

			size_t size() const
			{
				return stack_.size();
			}

			void popAndMovePropertySetToParent()
			{
				parseElementInfo pei = stack_.top();
				stack_.pop();
				BLUE_ASSERT(stack_.size() > 0, "Invalid stack.");
				stack_.top().properties.add(pei.properties);
			}

			eLandXMLParserState getPredecessorState()
			{
				if (stack_.size() <= 1)
				{
					return eLandXMLParserState::Undefined;
				}

				parseElementInfo tmp = stack_.top();
				stack_.pop();
				eLandXMLParserState state = stack_.top().state;
				stack_.push(tmp);
				return state;
			}

		private:
			std::stack<parseElementInfo>			stack_;
		};

		class QLandXMLImportDirector : public QXmlDefaultHandler
		{
		public:
			typedef BlueFramework::Core::PropertySet PropertySet;

			QLandXMLImportDirector(LandXMLDataBuilder* builder) :
				builder_(builder)
			{
				BLUE_ASSERT(builder_ != nullptr, "Invalid builder.");
			}

			virtual ~QLandXMLImportDirector()
			{

			}

			bool startElement(const QString & /* unused */,
				const QString &name,
				const QString& /* unused */,
				const QXmlAttributes &attr)
			{
				if (name == "Alignment")
				{
					stack_.push(eLandXMLParserState::Alignment);

					PropertySet ps;

					// check if start station is available
					if (attr.index("staStart") != -1)
					{
						double startStation = attr.value("staStart").toDouble();

						ps.addDouble("staStart", startStation);
					}

					// check if length is available
					if (attr.index("length") != -1)
					{
						double length = attr.value("length").toDouble();

						ps.addDouble("length", length);
					}

					// read name
					std::wstring name = attr.value("name").toStdWString();
					ps.addWString("name", name);
				
					builder_->createAlignment(ps);
				}

				if (name == "Center")
				{
					stack_.push(eLandXMLParserState::Center);
				}

				if (name == "CrossSects")
				{
					stack_.push(eLandXMLParserState::CrossSects);
				}

				if (name == "CrossSect")
				{
					stack_.push(eLandXMLParserState::CrossSect);
				}

				if (name == "CrossSectSurf")
				{
					stack_.push(eLandXMLParserState::CrossSectSurf);
				}

				if (name == "DesignCrossSectSurf")
				{
					stack_.push(eLandXMLParserState::DesignCrossSectSurf);

					PropertySet ps;

					if (attr.index("name") != -1)
					{
						std::string name = attr.value("name").toStdString();

						ps.addString("name", name);
					}

					if (attr.index("area") != -1)
					{
						double area = attr.value("area").toDouble();

						ps.addDouble("area", area);
					}

					if (attr.index("side") != -1)
					{
						std::string side = attr.value("side").toStdString();

						ps.addString("side", side);
					}

					if (attr.index("closedArea") != -1)
					{
						std::string closedArea = attr.value("closedArea").toStdString();
			
						if (closedArea == std::string("true"))
						{
							ps.addBoolean("closedArea", true);
						}
						else
						{
							ps.addBoolean("closedArea", false);
						}
					}

					builder_->createDesignCrossSectSurf(ps);
				}

				if (name == "CircCurve")
				{
					stack_.push(eLandXMLParserState::CircCurve);

					readDoubleAttribute(attr, "length");
					readDoubleAttribute(attr, "radius");
				}

				if (name == "CrossSectPnt")
				{
					stack_.push(eLandXMLParserState::CrossSectPnt);

					readStringAttribute(attr, "code");
				}

				if (name == "CoordGeom")
				{
					stack_.push(eLandXMLParserState::CoordGeom);
				}

				if (name == "Curve")
				{
					stack_.push(eLandXMLParserState::Curve);
					BLUE_ASSERT(stack_.topPropertySet().getPropertyCount() == 0, "Property set not empty.");

					readDoubleAttribute(attr, "dirEnd");
					readDoubleAttribute(attr, "dirStart");
					readDoubleAttribute(attr, "length");
					readDoubleAttribute(attr, "radius");				
				}

				if (name == "End")
				{
					stack_.push(eLandXMLParserState::End);
				}

				if (name == "F")
				{
					stack_.push(eLandXMLParserState::F);
				}

				if (name == "IrregularLine")
				{
					stack_.push(eLandXMLParserState::IrregularLine);
				}

				if (name == "Line")
				{
					stack_.push(eLandXMLParserState::Line);
					BLUE_ASSERT(stack_.topPropertySet().getPropertyCount() == 0, "Property set not empty.");

					readDoubleAttribute(attr, "length");
					readDoubleAttribute(attr, "dir");
				}

				if (name == "P")
				{
					stack_.push(eLandXMLParserState::P);
					readIntegerAttribute(attr, "id");
				}

				if (name == "ParaCurve")
				{
					stack_.push(eLandXMLParserState::ParaCurve);

					readDoubleAttribute(attr, "length");
				}

				if (name == "PI")
				{
					stack_.push(eLandXMLParserState::PI);
				}

				if (name == "PntList2D")
				{
					stack_.push(eLandXMLParserState::PntList2D);
				}

				if (name == "PntList3D")
				{
					stack_.push(eLandXMLParserState::PntList3D);
				}

				if (name == "Pnts")
				{
					stack_.push(eLandXMLParserState::Pnts);
					tmpSurface_ = LandXMLSurface(); 
				}

				if (name == "ProfAlign")
				{
					stack_.push(eLandXMLParserState::ProfAlign);
				}

				if (name == "Profile")
				{
					stack_.push(eLandXMLParserState::Profile);
				}

				if (name == "PVI")
				{
					stack_.push(eLandXMLParserState::PVI);
				}

				if (name == "Spiral")
				{
					stack_.push(eLandXMLParserState::Spiral);
					BLUE_ASSERT(stack_.topPropertySet().getPropertyCount() == 0, "Property set not empty.");

					readStringAttribute(attr, "radiusEnd");
					readStringAttribute(attr, "rot");
					readDoubleAttribute(attr, "length");
					readStringAttribute(attr, "radiusStart");
					readStringAttribute(attr, "spiType");
				}

				if (name == "Start")
				{
					stack_.push(eLandXMLParserState::Start);
					BLUE_ASSERT(stack_.topPropertySet().getPropertyCount() == 0, "Property set not empty.");
				}

				if (name == "Surface")
				{
					stack_.push(eLandXMLParserState::Surface);
				}

				return true;
			}

			bool characters(const QString& ch)
			{
				if (stack_.topParserState() == eLandXMLParserState::Center)
				{
					buw::Vector2d position = readVector2d_yx(ch);
					stack_.topPropertySet().addVector2d("Center", position);
				}

				if (stack_.topParserState() == eLandXMLParserState::CircCurve)
				{
					buw::Vector2d position = readVector2d_yx(ch);
					stack_.topPropertySet().addVector2d("CircCurve", position);
				}

				if (stack_.topParserState() == eLandXMLParserState::CrossSectPnt)
				{
					buw::Vector2d position = readVector2d_yx(ch);
					stack_.topPropertySet().addVector2d("CrossSectPnt", position);
				}

				if (stack_.topParserState() == eLandXMLParserState::End)
				{
					if (stack_.getPredecessorState() == eLandXMLParserState::IrregularLine)
					{
						buw::Vector3d position = readVector3d_yxz(ch);
						stack_.topPropertySet().addVector3d("End", position);
					}
					else
					{
						buw::Vector2d position = readVector2d_yx(ch);
						stack_.topPropertySet().addVector2d("End", position);
					}
				}

				if (stack_.topParserState() == eLandXMLParserState::F)
				{
					buw::Vector3i indices = readVector3i_xyz(ch);
					stack_.topPropertySet().addVector3i("F", indices);
				}

				if (stack_.topParserState() == eLandXMLParserState::P)
				{
					buw::Vector3d position = readVector3d_yxz(ch);
					stack_.topPropertySet().addVector3d("P", position);
				}

				if (stack_.topParserState() == eLandXMLParserState::ParaCurve)
				{
					buw::Vector2d position = readVector2d_yx(ch);
					stack_.topPropertySet().addVector2d("ParaCurve", position);
				}

				if (stack_.topParserState() == eLandXMLParserState::PI)
				{
					buw::Vector2d position = readVector2d_yx(ch);
					stack_.topPropertySet().addVector2d("PI", position);
				}

				if (stack_.topParserState() == eLandXMLParserState::PVI)
				{
					buw::Vector2d position = readVector2d_yx(ch);
					stack_.topPropertySet().addVector2d("PVI", position);
				}

				if (stack_.topParserState() == eLandXMLParserState::PntList2D)
				{

				}

				if (stack_.topParserState() == eLandXMLParserState::Start)
				{
					if (stack_.getPredecessorState() == eLandXMLParserState::IrregularLine)
					{
						buw::Vector3d position = readVector3d_yxz(ch);
						stack_.topPropertySet().addVector3d("Start", position);
					}
					else
					{
						buw::Vector2d position = readVector2d_yx(ch);
						stack_.topPropertySet().addVector2d("Start", position);
					}	
				}

				if (stack_.topParserState() == eLandXMLParserState::PntList3D)
				{

				}

				return true;
			}

			bool endElement(const QString & /* unused */, 
				const QString &name, 
				const QString& /* unused */)
			{
				if (name == "Alignment")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::Alignment, "Invalid state.");
					stack_.pop();
				}

				if (name == "Center")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::Center, "Invalid state.");
					stack_.popAndMovePropertySetToParent();
				}

				if (name == "CrossSects")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::CrossSects, "Invalid state.");
					stack_.pop();
				}

				if (name == "CrossSect")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::CrossSect, "Invalid state.");
					stack_.pop();
				}

				if (name == "CrossSectSurf")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::CrossSectSurf, "Invalid state.");
					stack_.pop();
				}

				if (name == "DesignCrossSectSurf")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::DesignCrossSectSurf, "Invalid state.");
					stack_.pop();
				}

				if (name == "CircCurve")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::CircCurve, "Invalid state.");
				
					PropertySet ps = stack_.topPropertySet();
					builder_->createCircCurve(ps);

					stack_.pop();
				}

				if (name == "CrossSectPnt")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::CrossSectPnt, "Invalid state.");

					PropertySet ps = stack_.topPropertySet();
					builder_->createCrossSectPnt(ps);

					stack_.pop();
				}

				if (name == "CoordGeom")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::CoordGeom, "Invalid state.");
					stack_.pop();

					builder_->createCoordGeom();
				}

				if (name == "Curve")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::Curve, "Invalid state.");
			
					PropertySet ps = stack_.topPropertySet();
					builder_->createCurve(ps);

					stack_.pop();				
				}

				if (name == "End")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::End, "Invalid state.");
					stack_.popAndMovePropertySetToParent();
				}

				if (name == "F")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::F, "Invalid state.");

					buw::Vector3i indices = stack_.top().properties.getVector3i("F");
					tmpSurface_.addTriangle(indices);

					stack_.pop();
				}

				if (name == "IrregularLine")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::IrregularLine, "Invalid state.");
					stack_.pop();
				}

				if (name == "Line")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::Line, "Invalid state.");
			
					PropertySet ps = stack_.topPropertySet();
					builder_->createLine(ps);
				
					stack_.pop();
				}

				if (name == "P")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::P, "Invalid state.");

					LandXMLSurfacePoint p;
					p.id = stack_.top().properties.getInteger("id");
					p.position = stack_.top().properties.getVector3d("P");
					tmpSurface_.addSurfacePoint(p);

					stack_.pop();
				}

				if (name == "ParaCurve")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::ParaCurve, "Invalid state.");
				
					PropertySet ps = stack_.topPropertySet();
					builder_->createParaCurve(ps);
				
					stack_.pop();
				}

				if (name == "PI")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::PI, "Invalid state.");
					stack_.popAndMovePropertySetToParent();
				}

				if (name == "PntList2D")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::PntList2D, "Invalid state.");
					stack_.pop();
				}

				if (name == "PntList3D")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::PntList3D, "Invalid state.");
					stack_.pop();
				}

				if (name == "Pnts")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::Pnts, "Invalid state.");
					stack_.pop();
				}

				if (name == "ProfAlign")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::ProfAlign, "Invalid state.");
					stack_.pop();
				}

				if (name == "Profile")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::Profile, "Invalid state.");
					stack_.pop();
				}

				if (name == "PVI")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::PVI, "Invalid state.");
				
					PropertySet ps = stack_.topPropertySet();
					builder_->createPVI(ps);

					stack_.pop();
				}

				if (name == "Spiral")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::Spiral, "Invalid state.");

					PropertySet ps = stack_.topPropertySet();
					builder_->createSpiral(ps);

					stack_.pop();
				}

				if (name == "Start")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::Start, "Invalid state.");
					stack_.popAndMovePropertySetToParent();
				}

				if (name == "Surface")
				{
					BLUE_ASSERT(stack_.topParserState() == eLandXMLParserState::Surface, "Invalid state.");
				
					PropertySet ps = stack_.topPropertySet();
					builder_->createSurface(ps, tmpSurface_);

					stack_.pop();
				}

				return true;
			}

		private:
			buw::Vector2d readVector2d_yx(const QString& ch) const
			{
				QString qstrStartText = ch.trimmed();
				QString delimiterPattern(" ");
				QStringList positions = qstrStartText.split(delimiterPattern, QString::SkipEmptyParts);
		
				if (positions.size() != 2)
				{
					BLUE_ASSERT(positions.size() == 3, "Invalid position size."); // sometime a LandXML file contains 3 components where only 2 are needed
					BLUE_ASSERT(positions[2].toDouble() == 0, "Invalid value.");
				}
			
				buw::Vector2d ps;
				ps.x() = positions[1].toDouble(); // In LandXML the second component is the x-component
				ps.y() = positions[0].toDouble(); // In LandXML the first component is the y-component

				return ps;
			}

			buw::Vector3i readVector3i_xyz(const QString& ch) const
			{
				QString qstrStartText = ch.trimmed();
				QString delimiterPattern(" ");
				QStringList positions = qstrStartText.split(delimiterPattern, QString::SkipEmptyParts);

				BLUE_ASSERT(positions.size() == 3, "Invalid position size.");

				buw::Vector3i ps;
				ps.x() = positions[0].toInt(); // In LandXML the second component is the x-component
				ps.y() = positions[1].toInt(); // In LandXML the first component is the y-component
				ps.z() = positions[2].toInt(); // In LandXML the third component is the height-component

				return ps;
			}

			buw::Vector3d readVector3d_yxz(const QString& ch) const
			{
				QString qstrStartText = ch.trimmed();
				QString delimiterPattern(" ");
				QStringList positions = qstrStartText.split(delimiterPattern, QString::SkipEmptyParts);

				BLUE_ASSERT(positions.size() == 3, "Invalid position size.");

				buw::Vector3d ps;
				ps.x() = positions[1].toDouble(); // In LandXML the second component is the x-component
				ps.y() = positions[0].toDouble(); // In LandXML the first component is the y-component
				ps.z() = positions[2].toDouble(); // In LandXML the third component is the height-component

				return ps;
			}

			// Stack management
			void readIntegerAttribute(const QXmlAttributes &attr, const char* attributeName)
			{
				if (attr.index(attributeName) != -1)
				{
					int value = attr.value(attributeName).toInt();

					stack_.topPropertySet().addInteger(attributeName, value);
				}
			}

			void readDoubleAttribute(const QXmlAttributes &attr, const char* attributeName)
			{
				if (attr.index(attributeName) != -1)
				{
					double value = attr.value(attributeName).toDouble();

					stack_.topPropertySet().addDouble(attributeName, value);
				}
			}

			void readStringAttribute(const QXmlAttributes &attr, const char* attributeName)
			{
				if (attr.index(attributeName) != -1)
				{
					std::string value = attr.value(attributeName).toStdString();

					stack_.topPropertySet().addString(attributeName, value);
				}
			}

		private:
			LandXMLSurface			tmpSurface_;

			LandXMLStateStack		stack_;
			LandXMLDataBuilder*		builder_;
		};

		void constructLandXMLData(const std::string& filename,
			LandXMLDataBuilder* builder)
		{
			BLUE_ASSERT(builder != nullptr, "Invalid builder.");

			QLandXMLImportDirector parser(builder);

			// Schema verification fails since official LandXML 1.2 schema is invalid!
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
		}

		//! \class LandXmlParser
		//! TODO: use QLandXMLImportDirector here! Rename calls then to AlignmentLandXMLDataBuilder
		//! \brief Can read a land xml file.
		//! Problem des Parsers: keine Idee wie man feststellen kann welche Werte im LandXML vorhanden und welche Fehlen
		//! TODO: Idee: man müsste auf dem Stack nicht nur den Typ des gelesen Tags plazieren sondern auch die gelesenen Werte, den dann kann man
		//! einfach feststellen ob z. B. eine Klothoide alle Parameter bereitstellt, die von ihr benötigt werden. Vorteil dieser Strategie:
		//! Keine globalen variablen.
		//! Idee: in propertySet lesen <- dann checken ob alle nötigen daten da waren und dann konsistenz checks!
		class QLandXmlParser : public QXmlDefaultHandler
		{
		public:
			QLandXmlParser();

			bool					startElement(const QString & /* unused */,
				const QString &name,
				const QString& /* unused */,
				const QXmlAttributes &attr);

			bool					characters(const QString& ch);

			bool					endElement(const QString & /* unused */, const QString &name,
				const QString& /* unused */);

			std::vector<buw::ReferenceCounted<buw::IAlignment3D>> getAlignments();

			int						getAlignmentCount();

			std::vector<LandXMLSurface> getSurfaces();

			int						getSurfaceCount();

			const std::vector<std::vector<buw::Vector3d>>& getBreakLines() const;

		private:
			std::vector<buw::Vector2d>	readVector2dArray(const QString& ch);

			std::vector<buw::Vector3d>	readVector3dArray(const QString& ch);

			buw::Vector2d	readVector2d(const QString& ch);

			buw::Vector2d	readVector2d_yx(const QString& ch);

			buw::Vector3d	readVector3d(const QString& ch);

			buw::Vector3i	readVector3i(const QString& ch);

			void			createVerticalAlignment();

			buw::PropertySet readVectorAsPropertySet_yxz(const QString& ch);

			//----------------------------------------------------------------
			// Stack management
			//----------------------------------------------------------------

			void pushState(const eLandXMLParserState state);

			eLandXMLParserState topState();

			void popState();

			size_t stackSize();

			eLandXMLParserState getCurrentStateParent();

			void setCurrentTopPropertySet(buw::PropertySet ps);

		private:
			bool is3DBased_; // Is the alignment 3D based or is it based on a 2D approach?

			std::stack<parseElementInfo>			parseElementInfoStack;

			std::wstring							name_;
			double									startStation_;
			buw::Vector3i							indices_;

			int										id_;
			buw::Vector3d							position_;
			std::vector<buw::Vector3d>				pointList3d_;
			buw::PropertySet						centerPs_;
			buw::PropertySet						startPs_;
			buw::PropertySet						endPs_;
			buw::PropertySet						piPs_;

			buw::Vector2d							pvi_;
			double									length_;
			double									radius_;
			double									radiusStart_;
			double									radiusEnd_;
			bool									clockwise_;
			double									dirStart_;
			double									dirEnd_;
			std::string								spiType_;

			buw::ReferenceCounted<buw::CrossSectionPoint>				currentCrossSectionPoint_;
			buw::ReferenceCounted<buw::CrossSectionStatic>			currentCrossSect_;
			buw::ReferenceCounted<buw::CrossSectionProfile>			currentCrossSectSurface_;
			buw::ReferenceCounted<buw::DesignCrossSectionProfile>		currentDesignCrossSectSurface_;

			profAlignElement						currentProfAlignElement_;
			std::vector<profAlignElement>			profAlignElements_;

			LandXMLSurface							currentSurface_;
			std::vector<LandXMLSurface>				surfaces_;

			buw::ReferenceCounted<buw::HorizontalAlignment2D>			currentHorizontalAlignment_;
			buw::ReferenceCounted<buw::Alignment2DBased3D>			currentAlignment2DBased3D_;
			buw::ReferenceCounted<buw::Alignment3DBased3D>			currentAlignment3DBased3D_;
			std::vector<buw::ReferenceCounted<buw::IAlignment3D>>		alignments_;

			std::vector<std::vector<buw::Vector3d>>	breakLines_;
		};

		buw::ReferenceCounted<buw::VerticalAlignment2D> createVerticalAlignmentFromProfAlign(
			const std::vector<profAlignElement>& profAlignElements_)
		{
			buw::ReferenceCounted<buw::VerticalAlignment2D> valignment = std::make_shared<buw::VerticalAlignment2D>();

			if (profAlignElements_.size() == 0)
				return valignment;

			if (profAlignElements_.size() == 2)
			{
				profAlignElement a = profAlignElements_[0];
				profAlignElement b = profAlignElements_[1];
				valignment->addElement(std::make_shared<buw::VerticalAlignmentElement2DLine>(a.position, b.position));
				return valignment;
			}

			buw::Vector2d pvt, pvc, start, end;

			BLUE_ASSERT(profAlignElements_[0].type == eProfAlignType::PVI, "Invalid type");

			for (int i = 2; i < profAlignElements_.size(); i++)
			{
				profAlignElement a = profAlignElements_[i - 2];
				profAlignElement b = profAlignElements_[i - 1];
				profAlignElement c = profAlignElements_[i];

				if (a.type == eProfAlignType::PVI)
				{
					start = a.position;
				}
				else if (a.type == eProfAlignType::CircCurve)
				{
					start = pvt;
				}
				else
				{
					start = pvt;
				}

				if (b.type == eProfAlignType::PVI)
				{
					end = b.position;

					if (start == end)
					{
						// ignore this segment 
					}
					else
					{
						valignment->addElement(std::make_shared<buw::VerticalAlignmentElement2DLine>(start, end));
					}
				}
				else if (b.type == eProfAlignType::CircCurve)
				{
					buw::Line2d l1(a.position, b.position);
					buw::Line2d l2(b.position, c.position);

					buw::Vector2d ab = (b.position - a.position).normalized();
					buw::Vector2d bc = (c.position - b.position).normalized();

					buw::Matrix22d rotation = buw::createRotationMatrix(-buw::constantsd::pi() / 2.0);

					buw::Vector2d d1 = rotation * ab;
					buw::Vector2d d2 = rotation * bc;

					buw::Line2d l3(a.position + d1 * b.radius, b.position + d1 * b.radius);
					buw::Line2d l4(b.position + d2 * b.radius, c.position + d2 * b.radius);

					//std::cout << l1 << std::endl;
					//std::cout << l2 << std::endl;
					//std::cout << l3 << std::endl;
					//std::cout << l4 << std::endl;

					BLUE_ASSERT(std::abs(l1.getGradient() - l3.getGradient()) < 0.001, "Lines are not parallel!");
					BLUE_ASSERT(std::abs(l2.getGradient() - l4.getGradient()) < 0.001, "Lines are not parallel!");

					buw::Vector2d d;
					buw::computeIntersection(l3, l4, d);

					//std::cout << d << std::endl;

					buw::Vector2d s1 = d - d1 * b.radius;
					buw::Vector2d s2 = d - d2 * b.radius;
			
					//std::cout << s1 << std::endl;
					//std::cout << s2 << std::endl;		

					//// s1 should always be on the left side of d - s2 should be on the right side
					//// change points if this does not hold.
					//// this can occure when the raidus of an vertical arc is negative
					//if (s1.x() > s2.x())
					//{
					//	std::swap(s1, s2);
					//}

					pvc = s1;
					pvt = s2;
			
					if ((start - s1).norm() < 0.1)
					{
						//std::cout << "no line needed" << std::endl;
					}
					else
					{
						// add line
						valignment->addElement(std::make_shared<buw::VerticalAlignmentElement2DLine>(start, s1));
					}

					bool isConvex = l1.getGradient() < l2.getGradient();
					// add vertical alignment
					valignment->addElement(std::make_shared<buw::VerticalAlignmentElement2DArc>(s1, s2, std::abs(b.radius), l1.getGradient(), isConvex));
				}
				else
				{
					// type == eProfAlignType::ParaCurve
					buw::Line2d l1(a.position, b.position);
					buw::Line2d l2(b.position, c.position);
					double T = b.length / 2.0;

					pvc = l1.eval(b.position.x() - T);
					pvt = l2.eval(b.position.x() + T);

					if (start.x() > pvc.x())
					{
						double l = (start - pvc).norm();
						int i = 0;
					}

					//if (start == pvc)
					if ((start - pvc).norm() < 0.0001) // hack
					{
						// ignore element....	
						BLUE_LOG(warning) << "Detected invalid connecting element.";
					}
					else
					{
						valignment->addElement(std::make_shared<buw::VerticalAlignmentElement2DLine>(start, pvc));
					}
								
					buw::ReferenceCounted<buw::VerticalAlignmentElement2DParabola> p = std::make_shared<buw::VerticalAlignmentElement2DParabola>(pvc, pvt, l1.getGradient(), l2.getGradient());

					valignment->addElement(p);
				}
			}

			if (profAlignElements_.size() > 0)
			{
				profAlignElement c = profAlignElements_[profAlignElements_.size() - 1];

				valignment->addElement(std::make_shared<buw::VerticalAlignmentElement2DLine>(pvt, c.position));
			}

			return valignment;
		}

		std::vector<profAlignElement> createProfAlignElements(buw::ReferenceCounted<buw::VerticalAlignment2D> v)
		{
			std::vector<profAlignElement> list;

			if (v->getAlignmentElementCount() == 0)
			{
				return list;
			}

			buw::Vector2d start; 
			v->getAlignmentElementByIndex(0)->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition,
				&start);

			profAlignElement e;
			e.position = start;
			e.type = eProfAlignType::PVI;
			e.length = 0;
			list.push_back(e);

			for( int i = 0; i < v->getAlignmentElementCount()-1; i++ )
			{
				buw::ReferenceCounted<buw::VerticalAlignmentElement2D> current = v->getAlignmentElementByIndex(i);
				buw::ReferenceCounted<buw::VerticalAlignmentElement2D> next = v->getAlignmentElementByIndex(i+1);
			
				if (current->getAlignmentType() == buw::eVerticalAlignmentType::Line &&
					next->getAlignmentType() == buw::eVerticalAlignmentType::Line)
				{
					buw::Vector2d end; 
					current->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndPosition,
						&end);

					profAlignElement e;
					e.position = end;
					e.type = eProfAlignType::PVI;
					e.length = 0;
					list.push_back(e);
				}

				else if (current->getAlignmentType() == buw::eVerticalAlignmentType::Line &&
					next->getAlignmentType() == buw::eVerticalAlignmentType::Parabola)
				{
					buw::Vector2d pvi; 
					next->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::PVI,
						&pvi);
					double intersectionPointDistance = 0;
					next->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::IntersectionPointDistance,
						&intersectionPointDistance);

					profAlignElement e;
					e.position = pvi;
					e.type = eProfAlignType::ParaCurve;
					e.length = intersectionPointDistance;
					list.push_back(e);
				}
				else 
				{
					// this case can be safely ignored		
				}
			}

			buw::Vector2d end; 
			v->getAlignmentElementByIndex(v->getAlignmentElementCount()-1)->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndPosition,
				&end);

			//profAlignElement e;
			e.position = end;
			e.type = eProfAlignType::PVI;
			e.length = 0;
			list.push_back(e);

			return list;
		}

		QLandXmlParser::QLandXmlParser() :
			is3DBased_(false)
		{
			pushState(eLandXMLParserState::Undefined);
		}

		bool QLandXmlParser::startElement( const QString & /* unused */, const QString &name, const QString& /* unused */, const QXmlAttributes &attr )
		{
			if (name == "Alignment")
			{
				pushState(eLandXMLParserState::Alignment);

				startStation_ = attr.value("staStart").toDouble();
				name_ = attr.value("name").toStdWString();

				if(attr.index("desc") != -1)
				{
					std::wstring description = attr.value("description").toStdWString();

					if (!description.empty())
					{
						name_ = name_ + std::wstring(L"(") + description + std::wstring(L")");
					}
				}

				currentAlignment2DBased3D_ = std::make_shared<buw::Alignment2DBased3D>();
				currentAlignment2DBased3D_->setName(name_);

				currentAlignment3DBased3D_ = std::make_shared<buw::Alignment3DBased3D>(startStation_);
				currentAlignment3DBased3D_->setName(name_);

				is3DBased_ = false;
			}

			if (name == "Center")
			{
				pushState(eLandXMLParserState::Center);
			}	

			if (name == "Breakline")
			{
				pushState(eLandXMLParserState::Breakline);
			}

			if (name == "CrossSects")
			{
				pushState(eLandXMLParserState::CrossSects);

				name_ = attr.value("name").toStdWString();
			}

			if (name == "CrossSect")
			{
				pushState(eLandXMLParserState::CrossSect);

				currentCrossSect_ = std::make_shared<CrossSectionStatic>();
				currentCrossSect_->stationing = attr.value("sta").toDouble();
			}

			if (name == "CrossSectSurf")
			{
				pushState(eLandXMLParserState::CrossSectSurf);
				currentCrossSectSurface_=std::make_shared<CrossSectionProfile>();
			}

			if (name == "DesignCrossSectSurf")
			{
				pushState(eLandXMLParserState::DesignCrossSectSurf);
				currentDesignCrossSectSurface_=std::make_shared<DesignCrossSectionProfile>();
			
				if(attr.value("name")!="")
					currentDesignCrossSectSurface_->name=attr.value("name").toStdString();
				else
					currentDesignCrossSectSurface_->name="";

				if(attr.value("side")!="left")
					currentDesignCrossSectSurface_->name=attr.value("name").toStdString();
				else
					currentDesignCrossSectSurface_->name="";

				if(attr.value("closedArea")=="true")
					currentDesignCrossSectSurface_->closedArea = true;
				else
					currentDesignCrossSectSurface_->closedArea = false;
			}

			if (name == "CircCurve")
			{
				pushState(eLandXMLParserState::CircCurve);

				currentProfAlignElement_ = profAlignElement();

				length_ = attr.value("length").toDouble();
				radius_ = attr.value("radius").toDouble();
			}

			if (name == "CrossSectPnt")
			{
				pushState(eLandXMLParserState::CrossSectPnt);

				currentCrossSectionPoint_=std::make_shared<CrossSectionPoint>();

				//std::cout << "Code: " << attr.value("code").toStdString() << std::endl;

				currentCrossSectionPoint_->code=attr.value("code").toStdString();
			}

			if (name == "CoordGeom")
			{
				pushState(eLandXMLParserState::CoordGeom);
				currentHorizontalAlignment_ = std::make_shared<buw::HorizontalAlignment2D>(startStation_);
			}

			if (name == "Curve")
			{
				pushState(eLandXMLParserState::Curve);

				clockwise_ = true;
				if (attr.value("rot").toStdString() == "ccw")
				{
					clockwise_ = false;
				}
			}

			if (name == "End")
			{
				pushState(eLandXMLParserState::End);
			}

			if (name == "F")
			{
				pushState(eLandXMLParserState::F);
			}

			if (name == "IrregularLine")
			{
				pushState(eLandXMLParserState::IrregularLine);

				is3DBased_ = true;
			}

			if (name == "Line")
			{
				pushState(eLandXMLParserState::Line);
			}

			if (name == "P")
			{
				pushState(eLandXMLParserState::P);
				id_ = attr.value("id").toInt();
			}

			if (name == "ParaCurve")
			{
				pushState(eLandXMLParserState::ParaCurve);

				currentProfAlignElement_ = profAlignElement();

				length_ = attr.value("length").toDouble();
			}

			if (name == "PI")
			{
				pushState(eLandXMLParserState::PI);
			}

			if (name == "PntList2D")
			{
				pushState(eLandXMLParserState::PntList2D);
			}

			if (name == "PntList3D")
			{
				pushState(eLandXMLParserState::PntList3D);
			}

			if(name == "ProfAlign")
			{
				pushState(eLandXMLParserState::ProfAlign);
			}

			if(name == "Profile")
			{
				pushState(eLandXMLParserState::Profile);
			}	

			if (name == "PVI") 
			{
				pushState(eLandXMLParserState::PVI);

				currentProfAlignElement_ = profAlignElement();
			}

			if (name == "Spiral")
			{
				pushState(eLandXMLParserState::Spiral);

				clockwise_ = true;
				if (attr.value("rot").toStdString() == "ccw")
				{
					clockwise_ = false;
				}

				length_ = attr.value("length").toDouble();
				radiusStart_ = attr.value("radiusStart").toDouble();
				radiusEnd_ = attr.value("radiusEnd").toDouble();

				dirStart_ = attr.value("dirStart").toDouble();
				dirEnd_ = attr.value("dirEnd").toDouble();

				spiType_ = attr.value("spiType").toStdString();
			}

			if (name == "Start")
			{
				pushState(eLandXMLParserState::Start);
			}			

			if (name == "Surface")
			{
				if (attr.value("name") != "")
				{
					name_ = attr.value("name").toStdWString();
				}
				else
				{
					name_ = L"Surface";
				}

				pushState(eLandXMLParserState::Surface);
			}

			return true;
		}

		bool QLandXmlParser::characters( const QString& ch )
		{
			if (topState() == eLandXMLParserState::Center)
			{
				centerPs_ = readVectorAsPropertySet_yxz(ch);
			}

			if (topState() == eLandXMLParserState::CircCurve)
			{
				pvi_ = readVector2d(ch);
			}

			if (topState() == eLandXMLParserState::CrossSectPnt)
			{
				if (getCurrentStateParent() == eLandXMLParserState::DesignCrossSectSurf)
				{
					currentCrossSectionPoint_->position = readVector2dArray(ch)[0];
				}
			}

			if (topState() == eLandXMLParserState::End)
			{
				endPs_ = readVectorAsPropertySet_yxz(ch);
			}	

			if (topState() == eLandXMLParserState::F)
			{
				indices_ = readVector3i(ch);
			}

			if (topState() == eLandXMLParserState::P)
			{
				position_ = readVector3d(ch);
			}

			if (topState() == eLandXMLParserState::ParaCurve)
			{
				pvi_ = readVector2d(ch);
			}

			if (topState() == eLandXMLParserState::PI)
			{
				piPs_ = readVectorAsPropertySet_yxz(ch);
			}

			if (topState() == eLandXMLParserState::PVI)
			{
				pvi_ = readVector2d(ch);
			}

			if (topState() == eLandXMLParserState::PntList2D)
			{
				if ( getCurrentStateParent() == eLandXMLParserState::CrossSectSurf)
				{
					currentCrossSectSurface_->pntList2D = readVector2dArray(ch);
				}
			}

			if (topState() == eLandXMLParserState::Start)
			{
				startPs_ = readVectorAsPropertySet_yxz(ch);
			}

			if (topState() == eLandXMLParserState::PntList3D)
			{
				if ( getCurrentStateParent() == eLandXMLParserState::IrregularLine)
				{
					pointList3d_ = readVector3dArray(ch);
				}
				else if (getCurrentStateParent() == eLandXMLParserState::Breakline)
				{
					breakLines_.push_back(readVector3dArray(ch));
				}
			}

			return true;
		}

		bool QLandXmlParser::endElement( const QString & /* unused */, const QString &name, const QString& /* unused */ )
		{
			if (name == "Alignment")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::Alignment, "Invalid state.");
				popState();

				if (is3DBased_)
				{
					//currentAlignment3DBased3D_->sortCrossSectionsByStation();
					alignments_.push_back(currentAlignment3DBased3D_);
				}
				else
				{
					currentAlignment2DBased3D_->setHorizontalAlignment(currentHorizontalAlignment_);
					currentAlignment2DBased3D_->sortCrossSectionsByStation();
					alignments_.push_back(currentAlignment2DBased3D_);
				}

				currentHorizontalAlignment_ = nullptr;
				currentAlignment2DBased3D_ = nullptr;
				currentAlignment3DBased3D_ = nullptr;
			}

			if (name == "Breakline")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::Breakline, "Invalid state.");
				popState();
			}

			if (name == "Center")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::Center, "Invalid state.");
				popState();
			}

			if (name == "CircCurve")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::CircCurve, "Invalid state.");
				popState();

				currentProfAlignElement_.type = eProfAlignType::CircCurve;
				currentProfAlignElement_.position = pvi_;
				currentProfAlignElement_.length = length_;
				currentProfAlignElement_.radius = radius_;

				profAlignElements_.push_back(currentProfAlignElement_);
			}

			if (name == "CrossSects")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::CrossSects, "Invalid state.");
				popState();
			}

			if (name == "CrossSect")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::CrossSect, "Invalid state.");
				popState();

				currentAlignment2DBased3D_->addCrossSection(currentCrossSect_);
			}

			if (name == "CrossSectSurf")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::CrossSectSurf, "Invalid state.");
				popState();

				currentCrossSect_->addCrossSectionProfile(currentCrossSectSurface_);
			}

			if (name == "DesignCrossSectSurf")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::DesignCrossSectSurf, "Invalid state.");
				popState();

				currentCrossSect_->addDesignCrossSectionProfile(currentDesignCrossSectSurface_);
			}

			if (name == "CrossSectPnt")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::CrossSectPnt, "Invalid state.");
				popState();

				currentDesignCrossSectSurface_->crossSectionsPoints.push_back(currentCrossSectionPoint_);
			}

			if (name == "CoordGeom")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::CoordGeom, "Invalid state.");
				popState();
			}

			if (name == "Curve")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::Curve, "Invalid state.");
				popState();

				buw::Vector2d start(startPs_.getDouble("x"), startPs_.getDouble("y"));
				buw::Vector2d end(endPs_.getDouble("x"), endPs_.getDouble("y"));
				buw::Vector2d center(centerPs_.getDouble("x"), centerPs_.getDouble("y"));

				buw::ReferenceCounted<buw::HorizontalAlignmentElement2DArc> arc = std::make_shared<buw::HorizontalAlignmentElement2DArc>(
					center, 
					start, 
					end, 
					clockwise_);

				currentHorizontalAlignment_->addElement(arc);
			}

			if (name == "End")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::End, "Invalid state.");
				popState();
			}

			if (name == "F")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::F, "Invalid state.");
				popState();

				currentSurface_.addTriangle(indices_);
			}

			if (name == "IrregularLine")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::IrregularLine, "Invalid state.");
				popState();

				buw::Vector3d start(startPs_.getDouble("x"), startPs_.getDouble("y"), startPs_.getDouble("z"));
				buw::Vector3d end(endPs_.getDouble("x"), endPs_.getDouble("y"), endPs_.getDouble("z"));

				currentAlignment3DBased3D_->addPoint(start);

				for (int i = 0; i < pointList3d_.size(); i++)
				{
					currentAlignment3DBased3D_->addPoint(pointList3d_[i]);
				}

				currentAlignment3DBased3D_->addPoint(end);

				pointList3d_.clear();
			}

			if (name == "Line")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::Line, "Invalid state.");
				popState();

				buw::Vector2d start(startPs_.getDouble("x"), startPs_.getDouble("y"));
				buw::Vector2d end(endPs_.getDouble("x"), endPs_.getDouble("y"));

				buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line = std::make_shared<buw::HorizontalAlignmentElement2DLine>(
					start,
					end);

				currentHorizontalAlignment_->addElement(line);
			}

			if (name == "P")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::P, "Invalid state.");
				popState();
				LandXMLSurfacePoint p;
				p.id = id_;
				p.position = position_;
				currentSurface_.addSurfacePoint(p);
			}	

			if (name == "ParaCurve")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::ParaCurve, "Invalid state.");
				popState();

				currentProfAlignElement_.type = eProfAlignType::ParaCurve;
				currentProfAlignElement_.position = pvi_;
				currentProfAlignElement_.length = length_;

				profAlignElements_.push_back(currentProfAlignElement_);
			}	

			if (name == "PI")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::PI, "Invalid state.");
				popState();
			}

			if (name == "PntList2D")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::PntList2D, "Invalid state.");
				popState();
			}

			if (name == "PntList3D")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::PntList3D, "Invalid state.");
				popState();
			}

			if(name == "ProfAlign")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::ProfAlign, "Invalid state.");
				popState();

				createVerticalAlignment();

				profAlignElements_.clear();
			}

			if(name == "Profile")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::Profile, "Invalid state.");
				popState();
			}		

			if (name == "PVI")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::PVI, "Invalid state.");
				popState();

				currentProfAlignElement_.type = eProfAlignType::PVI;
				currentProfAlignElement_.position = pvi_;

				profAlignElements_.push_back(currentProfAlignElement_);
			}	

			if(name == "Spiral")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::Spiral, "Invalid state.");
				popState();

				buw::Vector2d start(startPs_.getDouble("x"), startPs_.getDouble("y"));
				buw::Vector2d end(endPs_.getDouble("x"), endPs_.getDouble("y"));
				buw::Vector2d pi(piPs_.getDouble("x"), piPs_.getDouble("y"));
	


				const bool bUseArbitraryCurve = false; // true; //

				if (bUseArbitraryCurve)
				{
					/*
					buw::ReferenceCounted<buw::HorizontalAlignmentElement2DArbitraryCurve>  c = std::make_shared<buw::HorizontalAlignmentElement2DArbitraryCurve>(
						start,
						end,
						pi,
						length_,
						radiusStart_,
						radiusEnd_,
						clockwise_);
					*/

					double startCurvature = 0;
					if (radiusStart_ != 0 && radiusStart_ != std::numeric_limits<double>::infinity())
						startCurvature = 1 / radiusStart_;

					double endCurvature = 0;
					if (radiusEnd_ != 0 && radiusEnd_ != std::numeric_limits<double>::infinity())
						endCurvature = 1 / radiusEnd_;

					double startDirection = buw::HorizontalAlignmentElement2DClothoid::computeStartDirection(start, pi);
					double endDirection = buw::HorizontalAlignmentElement2DClothoid::computeEndDirection(start, pi);
					double clothoidConstant = buw::HorizontalAlignmentElement2DClothoid::computeClothoidConstant(length_, startCurvature, endCurvature);
					bool entry = buw::HorizontalAlignmentElement2DClothoid::computeEntry(startCurvature, endCurvature);

					auto  c = buw::makeReferenceCounted<buw::HorizontalAlignmentElement2DIfcPLArbitraryTransitionCurve>(
						start,
						startDirection,
						startCurvature,
						!clockwise_,
						clothoidConstant,
						entry,
						length_
					);

					currentHorizontalAlignment_->addElement(c);
				}
				else
				{
					if (spiType_ == "bloss")
					{
						double radius = 0;
						bool entry;

						double startDirection = buw::HorizontalAlignmentElement2DBlossCurve::computeStartDirection(start, pi);
						double endDirection = buw::HorizontalAlignmentElement2DBlossCurve::computeEndDirection(start, pi);
						buw::HorizontalAlignmentElement2DBlossCurve::computeEntry(radiusStart_, radiusEnd_, entry, radius);

						buw::blossDescription desc(start,
							startDirection,
							!clockwise_,
							entry,
							length_,
							radius
						);

						auto b = buw::makeReferenceCounted<buw::HorizontalAlignmentElement2DBlossCurve>(desc);

						currentHorizontalAlignment_->addElement(b);
					}
					else //(spiType_ == "clothoid")
					{
						//BLUE_LOG(error) << "unrecognized spiral type";

						double startCurvature = 0;
						if (radiusStart_ != 0 && radiusStart_ != std::numeric_limits<double>::infinity())
							startCurvature = 1 / radiusStart_;

						double endCurvature = 0;
						if (radiusEnd_ != 0 && radiusEnd_ != std::numeric_limits<double>::infinity())
							endCurvature = 1 / radiusEnd_;

						double startDirection = buw::HorizontalAlignmentElement2DClothoid::computeStartDirection(start, pi);
						double endDirection = buw::HorizontalAlignmentElement2DClothoid::computeEndDirection(start, pi);
						double clothoidConstant = buw::HorizontalAlignmentElement2DClothoid::computeClothoidConstant(length_, startCurvature, endCurvature);
						bool entry = buw::HorizontalAlignmentElement2DClothoid::computeEntry(startCurvature, endCurvature);

						buw::clothoidDescription desc(start,
							startDirection,
							startCurvature,
							!clockwise_,
							clothoidConstant,
							entry,
							length_);
						auto  c = buw::makeReferenceCounted<buw::HorizontalAlignmentElement2DClothoid>(desc);

						currentHorizontalAlignment_->addElement(c);

						buw::Vector2d check = c->getPiPosition();

						double errX = abs(check.x() - pi.x());
						double errY = abs(check.y() - pi.y());
						if (errX > 0.01 || errY > 0.01)
							BLUE_LOG(error) << "clothoid is invalid";
					}
				}
			}		

			if (name == "Start")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::Start, "Invalid state.");
				popState();
			}		

			if (name == "Surface")
			{
				BLUE_ASSERT(topState() == eLandXMLParserState::Surface, "Invalid state.");
				popState();

				currentSurface_.setName(buw::String::toStdString(name_).c_str());
				surfaces_.push_back(currentSurface_);
				LandXMLSurface emptySurface;
				currentSurface_ = emptySurface;
			}

			return true;
		}

		std::vector<buw::ReferenceCounted<buw::IAlignment3D>> QLandXmlParser::getAlignments()
		{
			return alignments_;
		}

		int QLandXmlParser::getAlignmentCount()
		{
			return static_cast<int>(alignments_.size());
		}

		std::vector<LandXMLSurface> QLandXmlParser::getSurfaces()
		{
			return surfaces_;
		}

		int QLandXmlParser::getSurfaceCount()
		{
			return static_cast<int>(surfaces_.size());
		}

		const std::vector<std::vector<buw::Vector3d>>& QLandXmlParser::getBreakLines() const
		{
			return breakLines_;
		}

		std::vector<buw::Vector2d> QLandXmlParser::readVector2dArray( const QString& ch )
		{
			std::vector<buw::Vector2d> v;

			QString qstrStartText = ch.trimmed();
			QString delimiterPattern(" ");
			QStringList positions =  qstrStartText.split(delimiterPattern, QString::SkipEmptyParts);

			for (int i = 0; i < positions.size(); i+=2)
			{
				buw::Vector2d position;
				position[0] = positions[i].toDouble();
				position[1] = positions[i+1].toDouble();

				v.push_back(position);
			}

			return v;
		}

		std::vector<buw::Vector3d> QLandXmlParser::readVector3dArray( const QString& ch )
		{
			std::vector<buw::Vector3d> v;

			QString qstrStartText = ch.trimmed();
			QString delimiterPattern(" ");
			QStringList positions =  qstrStartText.split(delimiterPattern, QString::SkipEmptyParts);

			for (int i = 0; i < positions.size(); i+=3)
			{
				buw::Vector3d position;
				position[1] = positions[i].toDouble();
				position[0] = positions[i+1].toDouble();
				position[2] = positions[i+2].toDouble();

				v.push_back(position);
			}

			return v;
		}

		buw::Vector2d QLandXmlParser::readVector2d( const QString& ch )
		{
			QString qstrStartText = ch.trimmed();
			QString delimiterPattern(" ");
			QStringList positions =  qstrStartText.split(delimiterPattern, QString::SkipEmptyParts);
			BLUE_ASSERT(positions.size() == 2, "Invalid position size.");

			buw::Vector2d position;
			position[0] = positions[0].toDouble();
			position[1] = positions[1].toDouble();

			return position;
		}

		buw::Vector2d QLandXmlParser::readVector2d_yx( const QString& ch )
		{
			QString qstrStartText = ch.trimmed();
			QString delimiterPattern(" ");
			QStringList positions =  qstrStartText.split(delimiterPattern, QString::SkipEmptyParts);
			BLUE_ASSERT(positions.size() == 2, "Invalid position size.");

			// replace ',' by '.' in values
			if(positions[0].contains(","))
			{
				positions[0].replace(",",".");
			}

			if(positions[1].contains(","))
			{
				positions[1].replace(",",".");
			}

			buw::Vector2d position;
			position[0] = positions[1].toDouble(); // read LandXML easting value
			position[1] = positions[0].toDouble(); // read LandXML northing value

			return position;
		}

		buw::Vector3d QLandXmlParser::readVector3d( const QString& ch )
		{
			QString qstrStartText = ch.trimmed();
			QString delimiterPattern(" ");
			QStringList positions =  qstrStartText.split(delimiterPattern, QString::SkipEmptyParts);


			if (positions.size() != 3)
			{
				std::cout << positions[0].toStdString() << " " << positions[1].toStdString() << " " << positions[2].toStdString() << " " << positions[3].toStdString() << " " << std::endl;
				std::cout << positions.size() << std::endl;
			}

			BLUE_ASSERT(positions.size() == 3, "Invalid position size.");

			// replace ',' by '.' in values
			if(positions[0].contains(","))
			{
				positions[0].replace(",",".");
			}

			if(positions[1].contains(","))
			{
				positions[1].replace(",",".");
			}

			if(positions[2].contains(","))
			{
				positions[2].replace(",",".");
			}

			buw::Vector3d position;
			position[0] = positions[1].toDouble();
			position[1] = positions[0].toDouble();
			position[2] = positions[2].toDouble();

			return position;
		}

		buw::Vector3i QLandXmlParser::readVector3i( const QString& ch )
		{
			QString qstrStartText = ch.trimmed();
			QString delimiterPattern(" ");
			QStringList positions =  qstrStartText.split(delimiterPattern, QString::SkipEmptyParts);
			BLUE_ASSERT(positions.size() == 3, "Invalid position size.");

			buw::Vector3i position;
			position[0] = positions[0].toInt();
			position[1] = positions[1].toInt();
			position[2] = positions[2].toInt();

			return position;
		}

		void QLandXmlParser::createVerticalAlignment()
		{
			// does an vertical alignment exist already?
			if(currentAlignment2DBased3D_->getVerticalAlignment() != nullptr)
			{
				return;
			}

			if (profAlignElements_.size() > 0)
			{
				if (profAlignElements_[0].type == eProfAlignType::ParaCurve)
				{
					BLUE_LOG(warning) <<
						"Detected invalid vertical alignment - start point is ParaCurve - workaround: converting ParaCurve to PVI";

					profAlignElements_[0].type = eProfAlignType::PVI;
				}

				int lastElementIndex = profAlignElements_.size() - 1;
				
				if (profAlignElements_[lastElementIndex].type == eProfAlignType::ParaCurve)
				{
					BLUE_LOG(warning) <<
						"Detected invalid vertical alignment  - end point is ParaCurve - workaround: converting ParaCurve to PVI";

					profAlignElements_[lastElementIndex].type = eProfAlignType::PVI;
				}
			}

			buw::ReferenceCounted<buw::VerticalAlignment2D> alignment = createVerticalAlignmentFromProfAlign(profAlignElements_);

			currentAlignment2DBased3D_->setVerticalAlignment(alignment);

			profAlignElements_.clear();
		}

		buw::PropertySet QLandXmlParser::readVectorAsPropertySet_yxz( const QString& ch )
		{
			QString qstrStartText = ch.trimmed();
			QString delimiterPattern(" ");
			QStringList positions =  qstrStartText.split(delimiterPattern, QString::SkipEmptyParts);
			BLUE_ASSERT(positions.size() >= 2, "Invalid position size.");
			BLUE_ASSERT(positions.size() <= 3, "Invalid position size.");

			buw::PropertySet ps;
			ps.addDouble("x", positions[1].toDouble()); // In LandXML the second component is the x-component
			ps.addDouble("y", positions[0].toDouble()); // In LandXML the first component is the y-component

			if (positions.size() == 3)
			{
				ps.addDouble("z", positions[2].toDouble());
			}

			return ps;
		}

		void QLandXmlParser::pushState( const eLandXMLParserState state )
		{
			parseElementInfo pei;
			pei.state = state;
			parseElementInfoStack.push(pei);
		}

		eLandXMLParserState QLandXmlParser::topState()
		{
			return parseElementInfoStack.top().state;
		}

		void QLandXmlParser::popState()
		{
			parseElementInfoStack.pop();
		}

		size_t QLandXmlParser::stackSize()
		{
			return parseElementInfoStack.size();
		}

		eLandXMLParserState QLandXmlParser::getCurrentStateParent()
		{
			if ( stackSize() >= 2)
			{
				eLandXMLParserState c1 = topState();
				popState();
				eLandXMLParserState c2 = topState();
				pushState(c1);
				return c2;
			}
			else
				return eLandXMLParserState::Undefined;
		}

		void QLandXmlParser::setCurrentTopPropertySet( buw::PropertySet ps )
		{
			parseElementInfoStack.top().properties = ps;
		}

		// Handle XML schema verification errors
		class XmlSchemaVerificationMessageHandler : public QAbstractMessageHandler
		{
		public:
			void handleMessage(QtMsgType type, const QString &descr,
				const QUrl &, const QSourceLocation &loc)
			{
				const char *typeName;
				switch (type)
				{
				case QtDebugMsg: typeName = "Debug"; break;
				case QtWarningMsg: typeName = "Warning"; break;
				case QtCriticalMsg: typeName = "Critical"; break;
				case QtFatalMsg:
				default: typeName = "Fatal"; break;
				}

				/* Convert the HTML error message to plain text */
				QXmlStreamReader xml(descr);
				QString text;
				while (!xml.atEnd())
					if (xml.readNext() == QXmlStreamReader::Characters)
						text += xml.text();

				std::cerr << typeName << ": " << qPrintable(text);
				//if (!loc.isNull())
				std::cerr << " (line " << loc.line() << ", col " << loc.column() << ")";
				std::cerr << endl;
			}
		};

		class LXVertexAndIndexBufferCreator
		{
		public:
			int createVertexAndGetIndex(
				const buw::Vector3d& position)
			{
				vertices_.push_back(position);
			
				return static_cast<int>(vertices_.size() - 1);
			}

			std::vector<buw::Vector3d> getVertices()
			{
				return vertices_;
			}

		private:
			std::map<buw::Vector3d, int> map_;
			std::vector<buw::Vector3d> vertices_;
		};
			
		buw::ReferenceCounted<buw::Surface> convertLandXMLSurfaceToSurface(const LandXMLSurface& lxSurface)
		{
			buw::ReferenceCounted<buw::Surface> s = std::make_shared<buw::Surface>();

			s->setName(lxSurface.getName());

			LXVertexAndIndexBufferCreator vbc;

			// for all triangles
			for (int ti = 0; ti < lxSurface.getTriangleCount(); ti++)
			{
				buw::Vector3i triangleIndices = lxSurface.getTriangeFaces()[ti];

				buw::Vector3i newTriangleIndices;

				for (int i = 0; i < 3; i++)
				{
					buw::Vector3d p = lxSurface.getSurfacePointPositonById(triangleIndices[i]);

					newTriangleIndices[i] = vbc.createVertexAndGetIndex(p);
				}
				
				s->addTriangle(newTriangleIndices);
			}

			s->setPoints(vbc.getVertices());

			BLUE_ASSERT(s->validate(), "Invalid indices");

			return s;
		}

		ImportLandXml::ImportLandXml(const std::string& filename) :
			Import(filename)
		{
			QLandXmlParser parser;

			// Schema verification fails since official LandXML 1.2 schema is invalid!
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

			for (int i = 0; i < parser.getAlignmentCount(); i++)
			{
				buw::ReferenceCounted<buw::IAlignment3D> a = parser.getAlignments()[i];
				alignmentModel_->addAlignment(a);
			}

			// convert LandXMLSurface to Surface
			for (int i = 0; i < parser.getSurfaceCount(); i++)
			{
				buw::ReferenceCounted<buw::Surface> s = convertLandXMLSurfaceToSurface(parser.getSurfaces()[i]);

				digitalElevationModel_->addSurface(s);
			}

			for (const std::vector<buw::Vector3d>& breakLine : parser.getBreakLines())
			{
				digitalElevationModel_->addBreakLine(breakLine);
			}
		}
	} // end namespace Infrastructure
} // end namespace BlueFramework