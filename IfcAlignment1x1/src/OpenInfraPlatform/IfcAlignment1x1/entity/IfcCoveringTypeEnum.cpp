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

#include "IfcCoveringTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcCoveringTypeEnum::IfcCoveringTypeEnum() {}
		IfcCoveringTypeEnum::IfcCoveringTypeEnum(IfcCoveringTypeEnum::IfcCoveringTypeEnumEnum value) { m_enum = value; }
		IfcCoveringTypeEnum::~IfcCoveringTypeEnum() {}
		void IfcCoveringTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcCoveringTypeEnumEnum::ENUM_CEILING)
				{
					stream << ".CEILING.";
				}
				else if ( m_enum == IfcCoveringTypeEnumEnum::ENUM_FLOORING)
				{
					stream << ".FLOORING.";
				}
				else if ( m_enum == IfcCoveringTypeEnumEnum::ENUM_CLADDING)
				{
					stream << ".CLADDING.";
				}
				else if ( m_enum == IfcCoveringTypeEnumEnum::ENUM_ROOFING)
				{
					stream << ".ROOFING.";
				}
				else if ( m_enum == IfcCoveringTypeEnumEnum::ENUM_MOLDING)
				{
					stream << ".MOLDING.";
				}
				else if ( m_enum == IfcCoveringTypeEnumEnum::ENUM_SKIRTINGBOARD)
				{
					stream << ".SKIRTINGBOARD.";
				}
				else if ( m_enum == IfcCoveringTypeEnumEnum::ENUM_INSULATION)
				{
					stream << ".INSULATION.";
				}
				else if ( m_enum == IfcCoveringTypeEnumEnum::ENUM_MEMBRANE)
				{
					stream << ".MEMBRANE.";
				}
				else if ( m_enum == IfcCoveringTypeEnumEnum::ENUM_SLEEVING)
				{
					stream << ".SLEEVING.";
				}
				else if ( m_enum == IfcCoveringTypeEnumEnum::ENUM_WRAPPING)
				{
					stream << ".WRAPPING.";
				}
				else if ( m_enum == IfcCoveringTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcCoveringTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcCoveringTypeEnum> IfcCoveringTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcCoveringTypeEnum>(); }
				std::shared_ptr<IfcCoveringTypeEnum> type_object(new IfcCoveringTypeEnum() );
				if ( _stricmp( arg.c_str(), ".CEILING.") == 0)
				{
					type_object->m_enum = IfcCoveringTypeEnum::IfcCoveringTypeEnumEnum::ENUM_CEILING;
				}
				else if ( _stricmp( arg.c_str(), ".FLOORING.") == 0)
				{
					type_object->m_enum = IfcCoveringTypeEnum::IfcCoveringTypeEnumEnum::ENUM_FLOORING;
				}
				else if ( _stricmp( arg.c_str(), ".CLADDING.") == 0)
				{
					type_object->m_enum = IfcCoveringTypeEnum::IfcCoveringTypeEnumEnum::ENUM_CLADDING;
				}
				else if ( _stricmp( arg.c_str(), ".ROOFING.") == 0)
				{
					type_object->m_enum = IfcCoveringTypeEnum::IfcCoveringTypeEnumEnum::ENUM_ROOFING;
				}
				else if ( _stricmp( arg.c_str(), ".MOLDING.") == 0)
				{
					type_object->m_enum = IfcCoveringTypeEnum::IfcCoveringTypeEnumEnum::ENUM_MOLDING;
				}
				else if ( _stricmp( arg.c_str(), ".SKIRTINGBOARD.") == 0)
				{
					type_object->m_enum = IfcCoveringTypeEnum::IfcCoveringTypeEnumEnum::ENUM_SKIRTINGBOARD;
				}
				else if ( _stricmp( arg.c_str(), ".INSULATION.") == 0)
				{
					type_object->m_enum = IfcCoveringTypeEnum::IfcCoveringTypeEnumEnum::ENUM_INSULATION;
				}
				else if ( _stricmp( arg.c_str(), ".MEMBRANE.") == 0)
				{
					type_object->m_enum = IfcCoveringTypeEnum::IfcCoveringTypeEnumEnum::ENUM_MEMBRANE;
				}
				else if ( _stricmp( arg.c_str(), ".SLEEVING.") == 0)
				{
					type_object->m_enum = IfcCoveringTypeEnum::IfcCoveringTypeEnumEnum::ENUM_SLEEVING;
				}
				else if ( _stricmp( arg.c_str(), ".WRAPPING.") == 0)
				{
					type_object->m_enum = IfcCoveringTypeEnum::IfcCoveringTypeEnumEnum::ENUM_WRAPPING;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcCoveringTypeEnum::IfcCoveringTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcCoveringTypeEnum::IfcCoveringTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
