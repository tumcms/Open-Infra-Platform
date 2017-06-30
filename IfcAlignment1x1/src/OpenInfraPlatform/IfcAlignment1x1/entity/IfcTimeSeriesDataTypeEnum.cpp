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

#include "IfcTimeSeriesDataTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcTimeSeriesDataTypeEnum::IfcTimeSeriesDataTypeEnum() {}
		IfcTimeSeriesDataTypeEnum::IfcTimeSeriesDataTypeEnum(IfcTimeSeriesDataTypeEnum::IfcTimeSeriesDataTypeEnumEnum value) { m_enum = value; }
		IfcTimeSeriesDataTypeEnum::~IfcTimeSeriesDataTypeEnum() {}
		void IfcTimeSeriesDataTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcTimeSeriesDataTypeEnumEnum::ENUM_CONTINUOUS)
				{
					stream << ".CONTINUOUS.";
				}
				else if ( m_enum == IfcTimeSeriesDataTypeEnumEnum::ENUM_DISCRETE)
				{
					stream << ".DISCRETE.";
				}
				else if ( m_enum == IfcTimeSeriesDataTypeEnumEnum::ENUM_DISCRETEBINARY)
				{
					stream << ".DISCRETEBINARY.";
				}
				else if ( m_enum == IfcTimeSeriesDataTypeEnumEnum::ENUM_PIECEWISEBINARY)
				{
					stream << ".PIECEWISEBINARY.";
				}
				else if ( m_enum == IfcTimeSeriesDataTypeEnumEnum::ENUM_PIECEWISECONSTANT)
				{
					stream << ".PIECEWISECONSTANT.";
				}
				else if ( m_enum == IfcTimeSeriesDataTypeEnumEnum::ENUM_PIECEWISECONTINUOUS)
				{
					stream << ".PIECEWISECONTINUOUS.";
				}
				else if ( m_enum == IfcTimeSeriesDataTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcTimeSeriesDataTypeEnum> IfcTimeSeriesDataTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcTimeSeriesDataTypeEnum>(); }
				std::shared_ptr<IfcTimeSeriesDataTypeEnum> type_object(new IfcTimeSeriesDataTypeEnum() );
				if ( _stricmp( arg.c_str(), ".CONTINUOUS.") == 0)
				{
					type_object->m_enum = IfcTimeSeriesDataTypeEnum::IfcTimeSeriesDataTypeEnumEnum::ENUM_CONTINUOUS;
				}
				else if ( _stricmp( arg.c_str(), ".DISCRETE.") == 0)
				{
					type_object->m_enum = IfcTimeSeriesDataTypeEnum::IfcTimeSeriesDataTypeEnumEnum::ENUM_DISCRETE;
				}
				else if ( _stricmp( arg.c_str(), ".DISCRETEBINARY.") == 0)
				{
					type_object->m_enum = IfcTimeSeriesDataTypeEnum::IfcTimeSeriesDataTypeEnumEnum::ENUM_DISCRETEBINARY;
				}
				else if ( _stricmp( arg.c_str(), ".PIECEWISEBINARY.") == 0)
				{
					type_object->m_enum = IfcTimeSeriesDataTypeEnum::IfcTimeSeriesDataTypeEnumEnum::ENUM_PIECEWISEBINARY;
				}
				else if ( _stricmp( arg.c_str(), ".PIECEWISECONSTANT.") == 0)
				{
					type_object->m_enum = IfcTimeSeriesDataTypeEnum::IfcTimeSeriesDataTypeEnumEnum::ENUM_PIECEWISECONSTANT;
				}
				else if ( _stricmp( arg.c_str(), ".PIECEWISECONTINUOUS.") == 0)
				{
					type_object->m_enum = IfcTimeSeriesDataTypeEnum::IfcTimeSeriesDataTypeEnumEnum::ENUM_PIECEWISECONTINUOUS;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcTimeSeriesDataTypeEnum::IfcTimeSeriesDataTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
