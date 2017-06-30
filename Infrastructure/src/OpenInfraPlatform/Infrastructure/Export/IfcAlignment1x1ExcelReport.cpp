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

#include "IfcAlignment1x1ExcelReport.h"

#include "OpenInfraPlatform/Infrastructure/Import/ImportLandXml.h"
#include "OpenInfraPlatform/Infrastructure/Import/ImportIfcAlignment1x0.h"
#include "OpenInfraPlatform/Infrastructure/Export/ExportIfcAlignment1x0.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DArc.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DLine.h"

#include "OpenInfraPlatform/IfcAlignment1x1/model/Model.h"
#include "OpenInfraPlatform/IfcAlignment1x1/model/Exception.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/IfcStepReader.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/IfcStepWriter.h"
#include "OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1Entities.h"
#include "OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1Types.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/IfcStepReader.h"
#include "OpenInfraPlatform/IfcAlignment1x1/model/UnitConverter.h"
#include "OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1EntityEnums.h"

#include <fstream>

#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxcellrange.h"
#include "xlsxworksheet.h"

using namespace OpenInfraPlatform::IfcAlignment1x1;

namespace OpenInfraPlatform 
{
	namespace Infrastructure
	{
		class IfcAlignment1x1DataBuilder
		{
		public:
			IfcAlignment1x1DataBuilder() {}

			virtual ~IfcAlignment1x1DataBuilder() {}

			virtual void createGeoreferencingOffset(const buw::Vector3d& offset) {};

			virtual void createIfcAlignment(std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment> alignment) {}

			virtual void createIfcAlignment2DHorizontal(std::shared_ptr<IfcAlignment2DHorizontal> alignment) {}

			virtual void createIfcAlignment2DVertical(std::shared_ptr<IfcAlignment2DVertical> alignment) {}

			//---------------------------------------------------------------------------//
			// Horizontal alignment
			//---------------------------------------------------------------------------//

			virtual void createIfcLineSegment2D(std::shared_ptr<IfcLineSegment2D> segment) {}

			virtual void createIfcCircularArcSegment2D(std::shared_ptr<IfcCircularArcSegment2D> segment) {}

			virtual void createIfcClothoidalArcSegment2D(std::shared_ptr<IfcClothoidalArcSegment2D> segment) {}

			//---------------------------------------------------------------------------//
			// Vertical alignment
			//---------------------------------------------------------------------------//

			virtual void createIfcAlignment2DVerSegLine(std::shared_ptr<IfcAlignment2DVerSegLine> segment) {}

			virtual void createIfcAlignment2DVerSegCircularArc(std::shared_ptr<IfcAlignment2DVerSegCircularArc> segment) {}

			virtual void createIfcAlignment2DVerSegParabolicArc(std::shared_ptr<IfcAlignment2DVerSegParabolicArc> segment) {}
		};

		class IfcAlignment1x1ImportDirector
		{
		public:
			IfcAlignment1x1ImportDirector(const char* filename, IfcAlignment1x1DataBuilder* builder) :
				builder_(builder)
			{
				shared_ptr<IfcStepReader> m_step_reader = shared_ptr<IfcStepReader>(new IfcStepReader());
				shared_ptr<IfcAlignment1x1Model> m_ifc_model(new IfcAlignment1x1Model());

				// open file
				std::ifstream infile;
				infile.open(filename, std::ifstream::in);

				if (!infile.is_open())
				{
					throw buw::FileNotFoundException("Could not open file.");
				}

				// get length of file:
				infile.seekg(0, std::ios::end);
				const int length = infile.tellg();
				infile.seekg(0, std::ios::beg);

				// allocate memory:
				std::string buffer(length, '\0');

				// read data as a block:
				infile.read(&buffer[0], length);
				infile.close();

				m_ifc_model->clearIfcModel();

				int millisecs_read_start = clock();
				m_step_reader->readStreamHeader(buffer, m_ifc_model);
				std::string file_schema_version = m_ifc_model->getFileSchema();
				std::map<int, shared_ptr<IfcAlignment1x1Entity> > map_entities;

				try
				{
					m_step_reader->readStreamData(buffer, map_entities);
				}
				catch (IfcAlignment1x1Exception & e)
				{
					throw buw::Exception(e.what());
				}

				// get offset value!
				offset_ = buw::Vector3d(0.0, 0.0, 0.0);

				for (auto it = map_entities.begin(); it != map_entities.end(); it++)
				{
					if (it->second->m_entity_enum == IFCMAPCONVERSION)
					{
						std::shared_ptr<IfcMapConversion> mapConversion = std::static_pointer_cast<IfcMapConversion>(it->second);

						BLUE_ASSERT(mapConversion->m_Eastings != nullptr, "Invalid easting.");
						BLUE_ASSERT(mapConversion->m_Northings != nullptr, "Invalid northing.");

						offset_.x() = mapConversion->m_Eastings->m_value;
						offset_.y() = mapConversion->m_Northings->m_value;

						builder_->createGeoreferencingOffset(offset_);
					}
				}

				for (auto it = map_entities.begin(); it != map_entities.end(); it++)
				{
					if (it->second->m_entity_enum == IFCALIGNMENT)
					{
						std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment> alignment = 
							std::static_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment>(it->second);

						builder_->createIfcAlignment(alignment);

						createAlignment(alignment);
					}
				}
			}

		private:
			void createAlignment(std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment> ifcAlignment)
			{
				builder_->createIfcAlignment(ifcAlignment);
				createHorizontalAlignment(ifcAlignment);
				createVerticalAlignment(ifcAlignment);
			}

			void createHorizontalAlignment(std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment> ifcAlignment)
			{
				std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignmentCurve> ifcAlignmentCurve = 
					std::static_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAlignmentCurve>(ifcAlignment->m_Axis);

				if (ifcAlignmentCurve->m_Horizontal != nullptr)
				{
					builder_->createIfcAlignment2DHorizontal(ifcAlignmentCurve->m_Horizontal);

					for (int i = 0; i < ifcAlignmentCurve->m_Horizontal->m_Segments.size(); i++)
					{
						std::shared_ptr<IfcCurveSegment2D> curveSegment = ifcAlignmentCurve->m_Horizontal->m_Segments[i]->m_CurveGeometry;

						BLUE_ASSERT(curveSegment != nullptr, "Invalid segment.");

						if (strcmp("IfcLineSegment2D", curveSegment->classname()) == 0)
						{
							createHorizontalLine(curveSegment);
							continue;
						}

						if (strcmp("IfcCircularArcSegment2D", curveSegment->classname()) == 0)
						{
							createHorizontalArc(curveSegment);
							continue;
						}

						if (strcmp("IfcClothoidalArcSegment2D", curveSegment->classname()) == 0)
						{
							createHorizontalClothoid(curveSegment);
							continue;
						}
					}
				}
			}

			void createHorizontalLine(std::shared_ptr<IfcCurveSegment2D> curveSegment)
			{
				std::shared_ptr<IfcLineSegment2D> ifcLine = std::static_pointer_cast<IfcLineSegment2D>(curveSegment);
				builder_->createIfcLineSegment2D(ifcLine);
			}

			void createHorizontalArc(std::shared_ptr<IfcCurveSegment2D> curveSegment)
			{
				std::shared_ptr<IfcCircularArcSegment2D> ifcArc = std::static_pointer_cast<IfcCircularArcSegment2D>(curveSegment);
				builder_->createIfcCircularArcSegment2D(ifcArc);
			}

			void createHorizontalClothoid(std::shared_ptr<IfcCurveSegment2D> curveSegment)
			{
				std::shared_ptr<IfcClothoidalArcSegment2D> ifcClothoid = std::static_pointer_cast<IfcClothoidalArcSegment2D>(curveSegment);
				builder_->createIfcClothoidalArcSegment2D(ifcClothoid);
			}

			void createVerticalAlignment(std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment> ifcAlignment)
			{
				std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignmentCurve> ifcAlignmentCurve =
					std::static_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAlignmentCurve>(ifcAlignment->m_Axis);
				
				if (ifcAlignmentCurve->m_Horizontal != nullptr)
				{
					if (ifcAlignmentCurve->m_Vertical == nullptr)
						return;

					builder_->createIfcAlignment2DVertical(ifcAlignmentCurve->m_Vertical);
					
					for (int i = 0; i < ifcAlignmentCurve->m_Vertical->m_Segments.size(); i++)
					{
						shared_ptr<IfcAlignment2DVerticalSegment> vs = ifcAlignmentCurve->m_Vertical->m_Segments[i];

						BLUE_ASSERT(vs != nullptr, "Invalid vertical segment.");

						if (strcmp("IfcAlignment2DVerSegLine", vs->classname()) == 0)
						{
							createVerticalAlignmentLine(vs);
						}
						else if (strcmp("IfcAlignment2DVerSegParabolicArc", vs->classname()) == 0)
						{
							createVerticalAlignmentParabola(vs);
						}
						else if (strcmp("IfcAlignment2DVerSegCircularArc", vs->classname()) == 0)
						{
							createVerticalAlignmentSegCircularArc(vs);
						}
						else
						{
							std::string className = vs->classname();
							BLUE_ASSERT(false, "Invalid segment!");
						}
					}
				}
			}

			void createVerticalAlignmentLine(shared_ptr<IfcAlignment2DVerticalSegment> vs)
			{
				std::shared_ptr<IfcAlignment2DVerSegLine> segment = std::static_pointer_cast<IfcAlignment2DVerSegLine>(vs);
				builder_->createIfcAlignment2DVerSegLine(segment);
			}

			void createVerticalAlignmentSegCircularArc(shared_ptr<IfcAlignment2DVerticalSegment> vs)
			{
				std::shared_ptr<IfcAlignment2DVerSegCircularArc> segment = std::static_pointer_cast<IfcAlignment2DVerSegCircularArc>(vs);
				builder_->createIfcAlignment2DVerSegCircularArc(segment);
			}

			void createVerticalAlignmentParabola(shared_ptr<IfcAlignment2DVerticalSegment> vs)
			{
				std::shared_ptr<IfcAlignment2DVerSegParabolicArc> segment = std::static_pointer_cast<IfcAlignment2DVerSegParabolicArc>(vs);
				builder_->createIfcAlignment2DVerSegParabolicArc(segment);
			}
			
		private:
			buw::Vector3d				offset_;
			IfcAlignment1x1DataBuilder*	builder_;
		};

		void constructIfcAlignment1x1Data(
			const char* filename,
			IfcAlignment1x1DataBuilder* builder)
		{
			IfcAlignment1x1ImportDirector director(filename, builder);
		}
	} // end namespace Infrastructure
} // end namespace BlueFramework

class AlignmentExcelSheetReport : public buw::LandXMLDataBuilder, public OpenInfraPlatform::Infrastructure::IfcAlignment1x1DataBuilder
{
public:
	AlignmentExcelSheetReport(
		const char* excelExportFilename, 
		const OpenInfraPlatform::Infrastructure::LandXMLHorizontalAlignmentReportSettings& LandXMLSettings,
		const OpenInfraPlatform::Infrastructure::IfcAlignment1x0IfcHorizontalAlignmentReportSettings& ifcP6HorizontalAlignmentSettings,
		const OpenInfraPlatform::Infrastructure::IfcAlignment1x0VerticalAlignmentReportSettings& ifcP6VerticalAlignmentSettings) :
	excelExportFilename_(excelExportFilename),
	landXMLHorizontalAlignmentReportSettings_(LandXMLSettings),
	P6IfcHorizontalAlignmentSettings_(ifcP6HorizontalAlignmentSettings),
	P6IfcVerticalAlignmentSettings_(ifcP6VerticalAlignmentSettings)
	{
		xlsx_.addSheet("Horizontal alignment elements");
		
		writeLandXMLDataHeaderCell(1, LandXMLStartColumn_, "LandXML");

		createLandXMLHeaderRow(LandXMLSettings);

		writeIfc4x1IfcAlignmentDataHeaderCell(1, getLandXMLColumnCount() + 1, "P6 IFC Alignment");

		writeIfc4x1IfcAlignmentDataHeaderCell(1, getLandXMLColumnCount() + 3, "Georeferencing");

		writeDerivedDataHeaderHeaderCell(1, getLandXMLColumnCount() + 1 + 11, "Check");

		createIfc4x1IfcHorizontalAlignmentHeaderRow(ifcP6HorizontalAlignmentSettings);
	
		xlsx_.addSheet("Vertical alignment elements");
		createIfc4x1VerticalAlignmentHeaderRow();
		writeIfc4x1IfcAlignmentDataHeaderCell(1, 1, "P6 IFC Alignment");
		writeDerivedDataHeaderHeaderCell(1, 10, "Check");

		xlsx_.selectSheet("Horizontal alignment elements");
	}

	virtual ~AlignmentExcelSheetReport() {}

	void writeIFCOffset()
	{
		xlsx_.selectSheet("Horizontal alignment elements");
		writeP6IfcAlignmentDataCell(1, getLandXMLColumnCount() + 4, P6IfcAlignmentOffset_.x());
		writeP6IfcAlignmentDataCell(1, getLandXMLColumnCount() + 5, P6IfcAlignmentOffset_.y());
	}

	void save()
	{
		// select first sheet
		xlsx_.selectSheet("Horizontal alignment elements");
		xlsx_.saveAs(excelExportFilename_.c_str());
	}

private:
	//---------------------------------------------------------------------------//
	// IFC Alignment
	//---------------------------------------------------------------------------//

	virtual void createIfcAlignment(std::shared_ptr<IfcAlignment> alignment) override
	{
		if (alignment->m_Description != nullptr)
		{
			P6IfcAlignmentName = alignment->m_Description->m_value;
		}
		else
			P6IfcAlignmentName = "";
	}

	virtual void createIfcAlignment2DHorizontal(std::shared_ptr<IfcAlignment2DHorizontal> alignment) override 
	{
		xlsx_.selectSheet("Horizontal alignment elements");
	}

	virtual void createIfcAlignment2DVertical(std::shared_ptr<IfcAlignment2DVertical> alignment) override 
	{
		xlsx_.selectSheet("Vertical alignment elements");
	}

	virtual void createGeoreferencingOffset(const buw::Vector3d& offset) 
	{
		P6IfcAlignmentOffset_ = offset;
	}

	virtual void createIfcLineSegment2D(std::shared_ptr<IfcLineSegment2D> segment) override
	{
		int row = P6IfcHorizontalAlignmentCurrentRow_;
		int col = P6IfcHorizontalAlignmentStartColumn_;

		if (P6IfcHorizontalAlignmentSettings_.alignmentName)
		{
			writeP6IfcAlignmentDataCell(row, col, P6IfcAlignmentName.c_str());
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.type)
		{
			writeP6IfcAlignmentDataCell(row, col, "IfcLineSegment2D");
			col++;
		}
		
		if (P6IfcHorizontalAlignmentSettings_.startPosition)
		{
			double x = segment->m_StartPoint->m_Coordinates[0]->m_value;
			double y = segment->m_StartPoint->m_Coordinates[1]->m_value;

			writeP6IfcAlignmentDataCell(row, col, x);
			col++;
			writeP6IfcAlignmentDataCell(row, col, y);
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.startDirection)
		{
			double value = segment->m_StartDirection->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.segmentLength)
		{
			double value = segment->m_SegmentLength->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.radius)
		{
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.startRadius)
		{
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.isCcw)
		{
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.IsEntry)
		{
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.ClothoidConstant)
		{
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.check)
		{
			{
				std::stringstream ss;
				ss << "=U" << row << "+V1";
				writeDerivedDataCell(row, col, ss.str().c_str());
				col++;
			}

			{
				std::stringstream ss;
				ss << "=V" << row << "+W1";
				writeDerivedDataCell(row, col, ss.str().c_str());
				col++;
			}
		}

		P6IfcHorizontalAlignmentCurrentRow_++;
	}

	virtual void createIfcCircularArcSegment2D(std::shared_ptr<IfcCircularArcSegment2D> segment) override
	{
		int row = P6IfcHorizontalAlignmentCurrentRow_;
		int col = P6IfcHorizontalAlignmentStartColumn_;

		if (P6IfcHorizontalAlignmentSettings_.alignmentName)
		{
			writeP6IfcAlignmentDataCell(row, col, P6IfcAlignmentName.c_str());
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.type)
		{
			writeP6IfcAlignmentDataCell(row, col, "IfcCircularArcSegment2D");
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.startPosition)
		{
			double x = segment->m_StartPoint->m_Coordinates[0]->m_value;
			double y = segment->m_StartPoint->m_Coordinates[1]->m_value;

			writeP6IfcAlignmentDataCell(row, col, x);
			col++;
			writeP6IfcAlignmentDataCell(row, col, y);
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.startDirection)
		{
			double value = segment->m_StartDirection->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.segmentLength)
		{
			double value = segment->m_SegmentLength->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.radius)
		{
			const double value = segment->m_Radius->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.startRadius)
		{
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.isCcw)
		{
			const bool value = segment->m_IsCCW->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.IsEntry)
		{
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.ClothoidConstant)
		{
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.check)
		{
			{
				std::stringstream ss;
				ss << "=U" << row << "+V1";
				writeDerivedDataCell(row, col, ss.str().c_str());
				col++;
			}

			{
				std::stringstream ss;
				ss << "=V" << row << "+W1";
				writeDerivedDataCell(row, col, ss.str().c_str());
				col++;
			}
		}

		P6IfcHorizontalAlignmentCurrentRow_++;
	}

	virtual void createIfcClothoidalArcSegment2D(std::shared_ptr<IfcClothoidalArcSegment2D> segment) override
	{
		int row = P6IfcHorizontalAlignmentCurrentRow_;
		int col = P6IfcHorizontalAlignmentStartColumn_;

		if (P6IfcHorizontalAlignmentSettings_.alignmentName)
		{
			writeP6IfcAlignmentDataCell(row, col, P6IfcAlignmentName.c_str());
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.type)
		{
			writeP6IfcAlignmentDataCell(row, col, "IfcClothoidalArcSegment2D");
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.startPosition)
		{
			double x = segment->m_StartPoint->m_Coordinates[0]->m_value;
			double y = segment->m_StartPoint->m_Coordinates[1]->m_value;

			writeP6IfcAlignmentDataCell(row, col, x);
			col++;
			writeP6IfcAlignmentDataCell(row, col, y);
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.startDirection)
		{
			double value = segment->m_StartDirection->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.segmentLength)
		{
			double value = segment->m_SegmentLength->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.radius)
		{
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.startRadius)
		{
			if (segment->m_StartRadius == nullptr)
			{
				writeP6IfcAlignmentDataCell(row, col, "NIL");
			}
			else
			{
				const double value = segment->m_StartRadius->m_value;
				writeP6IfcAlignmentDataCell(row, col, value);
			}

			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.isCcw)
		{
			const bool value = segment->m_IsCCW->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.IsEntry)
		{
			const bool value = segment->m_IsEntry->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.ClothoidConstant)
		{
			const double value = segment->m_ClothoidConstant->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (P6IfcHorizontalAlignmentSettings_.check)
		{
			{
				std::stringstream ss;
				ss << "=U" << row << "+V1";
				writeDerivedDataCell(row, col, ss.str().c_str());
				col++;
			}

			{
				std::stringstream ss;
				ss << "=V" << row << "+W1";
				writeDerivedDataCell(row, col, ss.str().c_str());
				col++;
			}
		}

		P6IfcHorizontalAlignmentCurrentRow_++;
	}

	virtual void createIfcAlignment2DVerSegLine(std::shared_ptr<IfcAlignment2DVerSegLine> segment) override
	{
		int row = P6IfcVertcialAlignmentCurrentRow_;
		int col = 1;

		if (P6IfcVerticalAlignmentSettings_.alignmentName)
		{
			writeP6IfcAlignmentDataCell(row, col, P6IfcAlignmentName.c_str());
			col++;
		}

		if (true)
		{
			writeP6IfcAlignmentDataCell(row, col, "IfcAlignment2DVerSegLine");
			col++;
		}

		if (true)
		{
			double value = segment->m_StartDistAlong->m_value;
			writeP6IfcAlignmentDataCell(row, col, value/*"StartDistAlong"*/);
			col++;
		}

		if (true)
		{
			double value = segment->m_HorizontalLength->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (true)
		{
			double value = segment->m_StartHeight->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (true)
		{
			double value = segment->m_StartGradient->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (true)
		{
			//writeP6IfcAlignmentDataHeaderCell(row, col, "ParabolaConstant");
			col++;
		}

		if (true)
		{
			//writeP6IfcAlignmentDataHeaderCell(row, col, "IsConvex");
			col++;
		}

		if (true)
		{
			//writeP6IfcAlignmentDataCell(row, col, "radius");
			col++;
		}

		if (P6IfcVerticalAlignmentSettings_.check)
		{
			{
				std::stringstream ss;
				ss << "= D" << row << "*F" << row << " + E" << row << "";
				writeDerivedDataCell(row, col, ss.str().c_str());
				col++;
			}

			{
				std::stringstream ss;
				ss << "=IF(OR(ABS(J" << row << "-E" << (row + 1) << ")<0.001,NOT(EXACT(A" << row << ",A" << (row + 1) << "))),\"\",\"NOT VALID\")";
				writeDerivedDataCell(row, col, ss.str().c_str());
				col++;
			}

			{
				col++;
				//writeDerivedDataCell(row, col, "sc");
				col++;
			}

			{
				//writeDerivedDataCell(row, col, "zc");
				col++;
			}

			{
				//writeDerivedDataCell(row, col, "g1");
				col++;
			}
			
		}

		P6IfcVertcialAlignmentCurrentRow_++;
	}

	virtual void createIfcAlignment2DVerSegCircularArc(std::shared_ptr<IfcAlignment2DVerSegCircularArc> segment) override
	{
		int row = P6IfcVertcialAlignmentCurrentRow_;
		int col = 1;

		if (P6IfcVerticalAlignmentSettings_.alignmentName)
		{
			writeP6IfcAlignmentDataCell(row, col, P6IfcAlignmentName.c_str());
			col++;
		}

		if (true)
		{
			writeP6IfcAlignmentDataCell(row, col, "IfcAlignment2DVerSegCircularArc");
			col++;
		}

		if (true)
		{
			double value = segment->m_StartDistAlong->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (true)
		{
			double value = segment->m_HorizontalLength->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (true)
		{
			double value = segment->m_StartHeight->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (true)
		{
			double value = segment->m_StartGradient->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (true)
		{
			//writeP6IfcAlignmentDataCell(row, col, "ParabolaConstant");
			col++;
		}

		if (true)
		{
			bool value = segment->m_IsConvex->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (true)
		{
			double value = segment->m_Radius->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (P6IfcVerticalAlignmentSettings_.check)
		{
			{
				std::stringstream ss;
				ss << "=N" << row << "+SQRT(POWER(I" << row << ",2)-POWER(M" << row << "-(C" << row << "+D" << row << "),2))*IF(H" << row << ",1,-1)";
				writeDerivedDataCell(row, col, ss.str().c_str());
				col++;
			}

			{
				std::stringstream ss;
				ss << "=IF(OR(ABS(J" << row << "-E" << (row + 1) << ")<0.001,NOT(EXACT(A" << row << ",A" << (row + 1) << "))),\"\",\"NOT VALID\")";
				writeDerivedDataCell(row, col, ss.str().c_str());
				col++;
			}

			{
				col++;
				std::stringstream ss;
				ss << "=C" << row << "+I" << row << "/SQRT(1+1/POWER(F" << row << ",2))";
				writeDerivedDataCell(row, col, ss.str().c_str());
				col++;
			}

			{
				std::stringstream ss;
				ss << "=E" << row << "+I" << row << "/SQRT(1+POWER(F" << row << ",2))*IF(H" << row << ",-1,1)";
				writeDerivedDataCell(row, col, ss.str().c_str());
				col++;
			}

			{
				//writeDerivedDataCell(row, col, "g1");
				col++;
			}
		}

		P6IfcVertcialAlignmentCurrentRow_++;
	}

	virtual void createIfcAlignment2DVerSegParabolicArc(std::shared_ptr<IfcAlignment2DVerSegParabolicArc> segment) override
	{
		int row = P6IfcVertcialAlignmentCurrentRow_;
		int col = 1;

		if (P6IfcVerticalAlignmentSettings_.alignmentName)
		{
			writeP6IfcAlignmentDataCell(row, col, P6IfcAlignmentName.c_str());
			col++;
		}

		if (true)
		{
			writeP6IfcAlignmentDataCell(row, col, "IfcAlignment2DVerSegParabolicArc");
			col++;
		}

		if (true)
		{
			double value = segment->m_StartDistAlong->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (true)
		{
			double value = segment->m_HorizontalLength->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (true)
		{
			double value = segment->m_StartHeight->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (true)
		{
			double value = segment->m_StartGradient->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (true)
		{
			double value = segment->m_ParabolaConstant->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (true)
		{
			bool value = segment->m_IsConvex->m_value;
			writeP6IfcAlignmentDataCell(row, col, value);
			col++;
		}

		if (true)
		{
			//writeP6IfcAlignmentDataCell(row, col, "radius");
			col++;
		}

		if (P6IfcVerticalAlignmentSettings_.check)
		{
			{
				std::stringstream ss;
				ss << "=D" << row << "*(O" << row << "+F" << row << ")/2+E" << row << "";
				writeDerivedDataCell(row, col, ss.str().c_str());
				col++;
			}

			{
				std::stringstream ss;
				ss << "=IF(OR(ABS(J" << row << "-E" << (row + 1) << ")<0.001,NOT(EXACT(A" << row << ",A" << (row + 1) << "))),\"\",\"NOT VALID\")";
				writeDerivedDataCell(row, col, ss.str().c_str());
				col++;
			}

			{
				col++;
				//writeDerivedDataCell(row, col, "sc");
				col++;
			}

			{
				//writeDerivedDataCell(row, col, "zc");
				col++;
			}

			{
				std::stringstream ss;
				ss	<< "=IF(EXACT(H" << row << ", FALSE)," 
					<< "(D" << row << " / G" << row << ") + F" << row << ","
					<< "(D" << row << " / -G" << row << ") + F" << row << ")";

				//std::cout << ss.str().c_str() << std::endl;

				//ss << "= (D" << row << " / G" << row << ") + F" << row << "";
				writeDerivedDataCell(row, col, ss.str().c_str());
				col++;
			}
		}

		P6IfcVertcialAlignmentCurrentRow_++;
	}

	void createIfc4x1IfcHorizontalAlignmentHeaderRow(const OpenInfraPlatform::Infrastructure::IfcAlignment1x0IfcHorizontalAlignmentReportSettings& settings)
	{
		int row = P6IfcHorizontalAlignmentStartRow_;
		int col = getLandXMLColumnCount() + 1;

		if (settings.alignmentName)
		{
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "Description");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (settings.type)
		{
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "IfcCurveSegment2D type");
			xlsx_.setColumnWidth(col, 24);
			col++;
		}

		if (settings.startPosition)
		{
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "StartPoint x");
			xlsx_.setColumnWidth(col, 15);
			col++;
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "StartPoint y");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (settings.startDirection)
		{
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "StartDirection");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (settings.segmentLength)
		{
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "SegmentLength");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (settings.radius)
		{
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "Radius");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (settings.startRadius)
		{
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "StartRadius");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (settings.isCcw)
		{
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "IsCcw");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (settings.IsEntry)
		{
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "IsEntry");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}
		
		if (settings.ClothoidConstant)
		{
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "ClothoidConstant");
			xlsx_.setColumnWidth(col, 18);
			col++;
		}

		if (settings.check)
		{
			writeDerivedDataHeaderHeaderCell(row, col, "StartPoint x (global)");
			xlsx_.setColumnWidth(col, 18);
			col++;

			writeDerivedDataHeaderHeaderCell(row, col, "StartPoint y (global)");
			xlsx_.setColumnWidth(col, 18);
			col++;
		}

		P6IfcHorizontalAlignmentCurrentRow_ = row + 1;
		P6IfcHorizontalAlignmentStartColumn_ = getLandXMLColumnCount() + 1;
	}

	void createIfc4x1VerticalAlignmentHeaderRow()
	{
		int row = P6IfcHorizontalAlignmentStartRow_;
		int col = 1;

		if (P6IfcVerticalAlignmentSettings_.alignmentName)
		{
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "Description");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (P6IfcVerticalAlignmentSettings_.type)
		{
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "IfcAlignment2DVerticalSegment");
			xlsx_.setColumnWidth(col, 34);
			col++;
		}

		if (true)
		{
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "StartDistAlong");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (true)
		{
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "HorizontalLength");
			xlsx_.setColumnWidth(col, 20);
			col++;
		}

		if (true)
		{
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "StartHeight");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (true)
		{
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "StartGradient");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}
		
		if (true)
		{
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "ParabolaConstant");
			xlsx_.setColumnWidth(col, 20);
			col++;
		}

		if (true)
		{
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "IsConvex");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (true)
		{
			writeIfc4x1IfcAlignmentDataHeaderCell(row, col, "Radius");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (P6IfcVerticalAlignmentSettings_.check)
		{
			writeDerivedDataHeaderHeaderCell(row, col, "endHeight");
			xlsx_.setColumnWidth(col, 15);
			col++;

			writeDerivedDataHeaderHeaderCell(row, col, "Diff to next startHeight");
			xlsx_.setColumnWidth(col, 15);
			col++;

			col++;
			writeDerivedDataHeaderHeaderCell(row, col, "sc");
			xlsx_.setColumnWidth(col, 15);
			col++;

			writeDerivedDataHeaderHeaderCell(row, col, "zc");
			xlsx_.setColumnWidth(col, 15);
			col++;

			writeDerivedDataHeaderHeaderCell(row, col, "g1");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}
	}

	void writeDerivedDataHeaderHeaderCell(int row, int col, const QString &text)
	{
		QXlsx::Format format;
		format.setFontBold(true);
		format.setPatternBackgroundColor(QColor::fromRgb(196, 215, 155));
		xlsx_.write(row, col, text, format);
	}

	void writeIfc4x1IfcAlignmentDataHeaderCell(int row, int col, const QString &text)
	{
		QXlsx::Format format;
		format.setFontBold(true);
		format.setPatternBackgroundColor(QColor::fromRgb(255, 230, 153));
		xlsx_.write(row, col, text, format);
	}

	void writeP6IfcAlignmentDataCell(int row, int col, const QVariant &value)
	{
		QXlsx::Format format;
		format.setPatternBackgroundColor(QColor::fromRgb(255, 242, 204));
		xlsx_.write(row, col, value, format);
	}

	void writeDerivedDataCell(int row, int col, const QVariant &value)
	{
		QXlsx::Format format;
		format.setPatternBackgroundColor(QColor::fromRgb(235, 241, 222));
		xlsx_.write(row, col, value, format);
	}

	//---------------------------------------------------------------------------//
	// LandXML
	//---------------------------------------------------------------------------//

	int getLandXMLColumnCount() const
	{
		int count = 0;

		if (landXMLHorizontalAlignmentReportSettings_.alignmentName)
			count += 1;
		if (landXMLHorizontalAlignmentReportSettings_.type)
			count += 1;
		if (landXMLHorizontalAlignmentReportSettings_.startPosition)
			count += 2;
		if (landXMLHorizontalAlignmentReportSettings_.endPosition)
			count += 2;
		if (landXMLHorizontalAlignmentReportSettings_.centerPosition)
			count += 2;
		if (landXMLHorizontalAlignmentReportSettings_.pi)
			count += 2;
		if (landXMLHorizontalAlignmentReportSettings_.length)
			count += 1;
		if (landXMLHorizontalAlignmentReportSettings_.radius)
			count += 1;
		if (landXMLHorizontalAlignmentReportSettings_.radiusStart)
			count += 1;
		if (landXMLHorizontalAlignmentReportSettings_.radiusEnd)
			count += 1;
		if (landXMLHorizontalAlignmentReportSettings_.dirStart)
			count += 1;
		if (landXMLHorizontalAlignmentReportSettings_.dirEnd)
			count += 1;
		if (landXMLHorizontalAlignmentReportSettings_.rot)
			count += 1;
		if (landXMLHorizontalAlignmentReportSettings_.spiType)
			count += 1;
		
		return count;
	}

	void createLandXMLHeaderRow(const OpenInfraPlatform::Infrastructure::LandXMLHorizontalAlignmentReportSettings& settings)
	{
		int row = LandXMLStartRow_;
		int col = LandXMLStartColumn_;

		if (settings.alignmentName)
		{
			writeLandXMLDataHeaderCell(row, col, "Name");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (settings.type)
		{
			writeLandXMLDataHeaderCell(row, col, "CoordGeom type");
			xlsx_.setColumnWidth(col, 17);
			col++;
		}

		if (settings.startPosition)
		{
			writeLandXMLDataHeaderCell(row, col, "Start x");
			xlsx_.setColumnWidth(col, 15);
			col++;
			writeLandXMLDataHeaderCell(row, col, "Start y");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (settings.endPosition)
		{
			writeLandXMLDataHeaderCell(row, col, "End x");
			xlsx_.setColumnWidth(col, 15);
			col++;
			writeLandXMLDataHeaderCell(row, col, "End y");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (settings.centerPosition)
		{
			writeLandXMLDataHeaderCell(row, col, "Center x");
			xlsx_.setColumnWidth(col, 15);
			col++;
			writeLandXMLDataHeaderCell(row, col, "Center y");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (settings.pi)
		{
			writeLandXMLDataHeaderCell(row, col, "PI x");
			xlsx_.setColumnWidth(col, 15);
			col++;
			writeLandXMLDataHeaderCell(row, col, "PI y");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (settings.length)
		{
			writeLandXMLDataHeaderCell(row, col, "length");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (settings.radius)
		{
			writeLandXMLDataHeaderCell(row, col, "radius");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (settings.radiusStart)
		{
			writeLandXMLDataHeaderCell(row, col, "radiusStart");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (settings.radiusEnd)
		{
			writeLandXMLDataHeaderCell(row, col, "radiusEnd");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (settings.dirStart)
		{
			writeLandXMLDataHeaderCell(row, col, "dirStart");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (settings.dirEnd)
		{
			writeLandXMLDataHeaderCell(row, col, "dirEnd");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (settings.rot)
		{
			writeLandXMLDataHeaderCell(row, col, "rot");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		if (settings.spiType)
		{
			writeLandXMLDataHeaderCell(row, col, "spiType");
			xlsx_.setColumnWidth(col, 15);
			col++;
		}

		LandXMLCurrentRow_ = row + 1;
	}

	virtual void createAlignment(const PropertySet& parameters) 
	{
		if (parameters.contains("name"))
		{
			LandXMLAlignmentName_ = parameters.getWString("name");
		}
		else
		{
			LandXMLAlignmentName_ = L"";
		}
	}

	//! A LandXML horizontal line segment
	virtual void createLine(const PropertySet& parameters) override
	{
		writeHorizontalLandXMLElement("Line", parameters);
	}

	//! A LandXML horizontal arc segment
	virtual void createCurve(const PropertySet& parameters) override
	{
		writeHorizontalLandXMLElement("Curve", parameters);
	}

	//! A LandXML horizontal spiral
	virtual void createSpiral(const PropertySet& parameters) override
	{
		writeHorizontalLandXMLElement("Spiral", parameters);
	}

	void writeHorizontalLandXMLElement(const char* type, const PropertySet &parameters)
	{
		int row = LandXMLCurrentRow_;
		int col = LandXMLStartColumn_;

		if (landXMLHorizontalAlignmentReportSettings_.alignmentName)
		{
			std::string name = buw::String::toStdString(LandXMLAlignmentName_);

			writeLandXMLDataCell(row, col, name.c_str());
			col++;
		}

		if (landXMLHorizontalAlignmentReportSettings_.type)
		{
			writeLandXMLDataCell(row, col, type);
			col++;
		}

		if (landXMLHorizontalAlignmentReportSettings_.startPosition)
		{
			if (parameters.contains("Start"))
			{
				buw::Vector2d position = parameters.getVector2d("Start");

				writeLandXMLDataCell(row, col + 0, position.x());
				writeLandXMLDataCell(row, col + 1, position.y());
			}

			col += 2;
		}

		if (landXMLHorizontalAlignmentReportSettings_.endPosition)
		{
			if (parameters.contains("End"))
			{
				buw::Vector2d position = parameters.getVector2d("End");

				writeLandXMLDataCell(row, col + 0, position.x());
				writeLandXMLDataCell(row, col + 1, position.y());
			}

			col += 2;
		}

		if (landXMLHorizontalAlignmentReportSettings_.centerPosition)
		{
			if (parameters.contains("Center"))
			{
				buw::Vector2d position = parameters.getVector2d("Center");

				writeLandXMLDataCell(row, col + 0, position.x());
				writeLandXMLDataCell(row, col + 1, position.y());
			}

			col += 2;
		}

		if (landXMLHorizontalAlignmentReportSettings_.pi)
		{
			if (parameters.contains("PI"))
			{
				buw::Vector2d position = parameters.getVector2d("PI");

				writeLandXMLDataCell(row, col + 0, position.x());
				writeLandXMLDataCell(row, col + 1, position.y());
			}

			col += 2;
		}

		if (landXMLHorizontalAlignmentReportSettings_.length)
		{
			if (parameters.contains("length"))
			{
				double value = parameters.getDouble("length");

				writeLandXMLDataCell(row, col + 0, value);
			}

			col += 1;
		}

		if (landXMLHorizontalAlignmentReportSettings_.radius)
		{
			if (parameters.contains("radius"))
			{
				double value = parameters.getDouble("radius");

				writeLandXMLDataCell(row, col + 0, value);
			}

			col += 1;
		}

		if (landXMLHorizontalAlignmentReportSettings_.radiusStart)
		{
			if (parameters.contains("radiusStart"))
			{
				std::string value = parameters.getString("radiusStart");

				writeLandXMLDataCell(row, col + 0, value.c_str());
			}

			col += 1;
		}

		if (landXMLHorizontalAlignmentReportSettings_.radiusEnd)
		{
			if (parameters.contains("radiusEnd"))
			{
				std::string value = parameters.getString("radiusEnd");

				writeLandXMLDataCell(row, col + 0, value.c_str());
			}

			col += 1;
		}

		if (landXMLHorizontalAlignmentReportSettings_.dirStart)
		{
			if (parameters.contains("dirStart"))
			{
				double value = parameters.getDouble("dirStart");

				writeLandXMLDataCell(row, col + 0, value);
			}

			col += 1;
		}

		if (landXMLHorizontalAlignmentReportSettings_.dirEnd)
		{
			if (parameters.contains("dirEnd"))
			{
				double value = parameters.getDouble("dirEnd");

				writeLandXMLDataCell(row, col + 0, value);
			}

			col += 1;
		}

		if (landXMLHorizontalAlignmentReportSettings_.rot)
		{
			if (parameters.contains("rot"))
			{
				std::string value = parameters.getString("rot");

				writeLandXMLDataCell(row, col + 0, value.c_str());
			}

			col += 1;
		}

		if (landXMLHorizontalAlignmentReportSettings_.spiType)
		{
			if (parameters.contains("spiType"))
			{
				std::string value = parameters.getString("spiType");

				writeLandXMLDataCell(row, col + 0, value.c_str());
			}

			col += 1;
		}

		LandXMLCurrentRow_++;
	}

	void writeLandXMLDataHeaderCell(const int row, const int col, const QString &text)
	{
		QXlsx::Format format;
		format.setFontBold(true);
		format.setPatternBackgroundColor(QColor::fromRgb(204, 192, 218));
		xlsx_.write(row, col, text, format);
	}

	void writeLandXMLDataCell(const int row, const int col, const QVariant &value)
	{
		QXlsx::Format format;
		format.setPatternBackgroundColor(QColor::fromRgb(228, 223, 236));
		xlsx_.write(row, col, value, format);
	}

private:
	std::string				excelExportFilename_;

	buw::IfcAlignment1x0IfcHorizontalAlignmentReportSettings		P6IfcHorizontalAlignmentSettings_;
	buw::IfcAlignment1x0VerticalAlignmentReportSettings		P6IfcVerticalAlignmentSettings_;
	int						P6IfcHorizontalAlignmentCurrentRow_ = 2;
	int						P6IfcHorizontalAlignmentStartRow_ = 2;
	int						P6IfcHorizontalAlignmentStartColumn_ = 1;
	int						P6IfcVertcialAlignmentCurrentRow_ = 3;
	buw::Vector3d			P6IfcAlignmentOffset_;
	std::string				P6IfcAlignmentName;

	buw::LandXMLHorizontalAlignmentReportSettings	landXMLHorizontalAlignmentReportSettings_;
	std::wstring			LandXMLAlignmentName_;
	int						LandXMLCurrentRow_ = 2;
	int						LandXMLStartRow_ = 2;
	int						LandXMLStartColumn_ = 1;

	QXlsx::Document			xlsx_;
};

class OpenInfraPlatform::Infrastructure::IfcAlignment1x1ExcelReport::ExcelReportImpl
{
public:
	ExcelReportImpl(
		const char* excelExportFilename,
		const char* landXMLFilename,
		const char* ifcP6ExportFilename)
	{
		LandXMLHorizontalAlignmentReportSettings settings;
		IfcAlignment1x0IfcHorizontalAlignmentReportSettings ifcHSettings;
		IfcAlignment1x0VerticalAlignmentReportSettings ifcVSettings;
		AlignmentExcelSheetReport esk(excelExportFilename, settings, ifcHSettings, ifcVSettings);
		OpenInfraPlatform::Infrastructure::constructLandXMLData(landXMLFilename, &esk);
		OpenInfraPlatform::Infrastructure::constructIfcAlignment1x1Data(ifcP6ExportFilename, &esk);
		esk.writeIFCOffset();
		esk.save();
	}
};

OpenInfraPlatform::Infrastructure::IfcAlignment1x1ExcelReport::IfcAlignment1x1ExcelReport(
	const char* excelExportFilename,
	const char* landXMLFilename,
	const char* ifcP6ExportFilename) :
impl_(new ExcelReportImpl(excelExportFilename, landXMLFilename, ifcP6ExportFilename))
{

}
