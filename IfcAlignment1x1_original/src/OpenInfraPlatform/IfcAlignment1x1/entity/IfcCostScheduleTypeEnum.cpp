// Copied and modified code from "IfcPlusPlus" library.
// This library is available under the OpenSceneGraph Public License. Original copyright notice:

/* -*-c++-*- IfcPlusPlus - www.ifcplusplus.com - Copyright (C) 2011 Fabian Gerold
*
* This library is open source and may be redistributed and / or modified under
* the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
* (at your option) any later version.The full license is in LICENSE file
* included with this distribution, and on the openscenegraph.org website.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* OpenSceneGraph Public License for more details.
*/

/* This file has been automatically generated using the TUM Open Infra Platform
Early Binding EXPRESS Generator. Any changes to this file my be lost in the future. */

#include "IfcCostScheduleTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcCostScheduleTypeEnum::IfcCostScheduleTypeEnum() {}
		IfcCostScheduleTypeEnum::IfcCostScheduleTypeEnum(IfcCostScheduleTypeEnum::IfcCostScheduleTypeEnumEnum value) { m_enum = value; }
		IfcCostScheduleTypeEnum::~IfcCostScheduleTypeEnum() {}
		void IfcCostScheduleTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcCostScheduleTypeEnumEnum::ENUM_BUDGET)
				{
					stream << ".BUDGET.";
				}
				else if ( m_enum == IfcCostScheduleTypeEnumEnum::ENUM_COSTPLAN)
				{
					stream << ".COSTPLAN.";
				}
				else if ( m_enum == IfcCostScheduleTypeEnumEnum::ENUM_ESTIMATE)
				{
					stream << ".ESTIMATE.";
				}
				else if ( m_enum == IfcCostScheduleTypeEnumEnum::ENUM_TENDER)
				{
					stream << ".TENDER.";
				}
				else if ( m_enum == IfcCostScheduleTypeEnumEnum::ENUM_PRICEDBILLOFQUANTITIES)
				{
					stream << ".PRICEDBILLOFQUANTITIES.";
				}
				else if ( m_enum == IfcCostScheduleTypeEnumEnum::ENUM_UNPRICEDBILLOFQUANTITIES)
				{
					stream << ".UNPRICEDBILLOFQUANTITIES.";
				}
				else if ( m_enum == IfcCostScheduleTypeEnumEnum::ENUM_SCHEDULEOFRATES)
				{
					stream << ".SCHEDULEOFRATES.";
				}
				else if ( m_enum == IfcCostScheduleTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcCostScheduleTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcCostScheduleTypeEnum> IfcCostScheduleTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcCostScheduleTypeEnum>(); }
				std::shared_ptr<IfcCostScheduleTypeEnum> type_object(new IfcCostScheduleTypeEnum() );
				if ( _stricmp( arg.c_str(), ".BUDGET.") == 0)
				{
					type_object->m_enum = IfcCostScheduleTypeEnum::IfcCostScheduleTypeEnumEnum::ENUM_BUDGET;
				}
				else if ( _stricmp( arg.c_str(), ".COSTPLAN.") == 0)
				{
					type_object->m_enum = IfcCostScheduleTypeEnum::IfcCostScheduleTypeEnumEnum::ENUM_COSTPLAN;
				}
				else if ( _stricmp( arg.c_str(), ".ESTIMATE.") == 0)
				{
					type_object->m_enum = IfcCostScheduleTypeEnum::IfcCostScheduleTypeEnumEnum::ENUM_ESTIMATE;
				}
				else if ( _stricmp( arg.c_str(), ".TENDER.") == 0)
				{
					type_object->m_enum = IfcCostScheduleTypeEnum::IfcCostScheduleTypeEnumEnum::ENUM_TENDER;
				}
				else if ( _stricmp( arg.c_str(), ".PRICEDBILLOFQUANTITIES.") == 0)
				{
					type_object->m_enum = IfcCostScheduleTypeEnum::IfcCostScheduleTypeEnumEnum::ENUM_PRICEDBILLOFQUANTITIES;
				}
				else if ( _stricmp( arg.c_str(), ".UNPRICEDBILLOFQUANTITIES.") == 0)
				{
					type_object->m_enum = IfcCostScheduleTypeEnum::IfcCostScheduleTypeEnumEnum::ENUM_UNPRICEDBILLOFQUANTITIES;
				}
				else if ( _stricmp( arg.c_str(), ".SCHEDULEOFRATES.") == 0)
				{
					type_object->m_enum = IfcCostScheduleTypeEnum::IfcCostScheduleTypeEnumEnum::ENUM_SCHEDULEOFRATES;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcCostScheduleTypeEnum::IfcCostScheduleTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcCostScheduleTypeEnum::IfcCostScheduleTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
