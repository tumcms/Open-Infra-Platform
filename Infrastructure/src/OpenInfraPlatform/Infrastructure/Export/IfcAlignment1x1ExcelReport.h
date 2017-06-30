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

#pragma once
#ifndef OpenInfraPlatform_Infrastructure_ExcelReport2_c3889228_51c2_4ead_99cb_96ccb5cb735d_h
#define OpenInfraPlatform_Infrastructure_ExcelReport2_c3889228_51c2_4ead_99cb_96ccb5cb735d_h

#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"
#include <string>
#include <memory>

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		struct LandXMLHorizontalAlignmentReportSettings
		{
			LandXMLHorizontalAlignmentReportSettings()
			{
				alignmentName = true;
				type = true;
				startPosition = true;
				endPosition = true;
				centerPosition = true;
				pi = true;
				length = true;
				radius = true;
				radiusStart = true;
				radiusEnd = true;
				dirStart = true;
				dirEnd = true;
				rot = true;
				spiType = true;
			}

			// LandXML
			bool alignmentName;
			bool type;
			bool startPosition;
			bool endPosition;
			bool centerPosition;
			bool pi;
			bool length;
			bool radius;
			bool radiusStart;
			bool radiusEnd;
			bool dirStart;
			bool dirEnd;
			bool rot;
			bool spiType;
		};

		struct IfcAlignment1x0IfcHorizontalAlignmentReportSettings
		{
			IfcAlignment1x0IfcHorizontalAlignmentReportSettings()
			{
				alignmentName = true;
				type = true;
				startPosition = true;
				startDirection = true;
				segmentLength = true;
				radius = true;
				startRadius = true;
				isCcw = true;
				IsEntry = true;
				ClothoidConstant = true;
				check = true;
			}

			bool alignmentName;
			bool type;
			bool startPosition;
			bool startDirection;
			bool segmentLength;
			bool radius;
			bool startRadius;
			bool isCcw;
			bool IsEntry;
			bool ClothoidConstant;
			bool check;
		};

		struct IfcAlignment1x0VerticalAlignmentReportSettings
		{
			IfcAlignment1x0VerticalAlignmentReportSettings()
			{
				alignmentName = true;
				type = true;	
				check = true;
			}

			bool alignmentName;
			bool type;
			bool check;
		};

		class BLUEINFRASTRUCTURE_API IfcAlignment1x1ExcelReport
		{
		public:
			IfcAlignment1x1ExcelReport(
				const char* excelExportFilename, 
				const char* landXMLFilename, 
				const char* ifcP6ExportFilename);

		private:
			class ExcelReportImpl;						// Forward declaration of internal class
			std::shared_ptr<ExcelReportImpl> impl_;	// Opaque pointer to implementation
		}; // end class ExcelReport2
	} // end namespace Infrastructure
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::Infrastructure::IfcAlignment1x0VerticalAlignmentReportSettings;
	using OpenInfraPlatform::Infrastructure::LandXMLHorizontalAlignmentReportSettings;
	using OpenInfraPlatform::Infrastructure::IfcAlignment1x0IfcHorizontalAlignmentReportSettings;
	using OpenInfraPlatform::Infrastructure::IfcAlignment1x1ExcelReport;
}

#endif // end define OpenInfraPlatform_Infrastructure_ExcelReport2_c3889228_51c2_4ead_99cb_96ccb5cb735d_h
