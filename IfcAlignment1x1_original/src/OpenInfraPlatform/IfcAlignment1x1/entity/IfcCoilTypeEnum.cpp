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

#include "IfcCoilTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcCoilTypeEnum::IfcCoilTypeEnum() {}
		IfcCoilTypeEnum::IfcCoilTypeEnum(IfcCoilTypeEnum::IfcCoilTypeEnumEnum value) { m_enum = value; }
		IfcCoilTypeEnum::~IfcCoilTypeEnum() {}
		void IfcCoilTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcCoilTypeEnumEnum::ENUM_DXCOOLINGCOIL)
				{
					stream << ".DXCOOLINGCOIL.";
				}
				else if ( m_enum == IfcCoilTypeEnumEnum::ENUM_ELECTRICHEATINGCOIL)
				{
					stream << ".ELECTRICHEATINGCOIL.";
				}
				else if ( m_enum == IfcCoilTypeEnumEnum::ENUM_GASHEATINGCOIL)
				{
					stream << ".GASHEATINGCOIL.";
				}
				else if ( m_enum == IfcCoilTypeEnumEnum::ENUM_HYDRONICCOIL)
				{
					stream << ".HYDRONICCOIL.";
				}
				else if ( m_enum == IfcCoilTypeEnumEnum::ENUM_STEAMHEATINGCOIL)
				{
					stream << ".STEAMHEATINGCOIL.";
				}
				else if ( m_enum == IfcCoilTypeEnumEnum::ENUM_WATERCOOLINGCOIL)
				{
					stream << ".WATERCOOLINGCOIL.";
				}
				else if ( m_enum == IfcCoilTypeEnumEnum::ENUM_WATERHEATINGCOIL)
				{
					stream << ".WATERHEATINGCOIL.";
				}
				else if ( m_enum == IfcCoilTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcCoilTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcCoilTypeEnum> IfcCoilTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcCoilTypeEnum>(); }
				std::shared_ptr<IfcCoilTypeEnum> type_object(new IfcCoilTypeEnum() );
				if ( _stricmp( arg.c_str(), ".DXCOOLINGCOIL.") == 0)
				{
					type_object->m_enum = IfcCoilTypeEnum::IfcCoilTypeEnumEnum::ENUM_DXCOOLINGCOIL;
				}
				else if ( _stricmp( arg.c_str(), ".ELECTRICHEATINGCOIL.") == 0)
				{
					type_object->m_enum = IfcCoilTypeEnum::IfcCoilTypeEnumEnum::ENUM_ELECTRICHEATINGCOIL;
				}
				else if ( _stricmp( arg.c_str(), ".GASHEATINGCOIL.") == 0)
				{
					type_object->m_enum = IfcCoilTypeEnum::IfcCoilTypeEnumEnum::ENUM_GASHEATINGCOIL;
				}
				else if ( _stricmp( arg.c_str(), ".HYDRONICCOIL.") == 0)
				{
					type_object->m_enum = IfcCoilTypeEnum::IfcCoilTypeEnumEnum::ENUM_HYDRONICCOIL;
				}
				else if ( _stricmp( arg.c_str(), ".STEAMHEATINGCOIL.") == 0)
				{
					type_object->m_enum = IfcCoilTypeEnum::IfcCoilTypeEnumEnum::ENUM_STEAMHEATINGCOIL;
				}
				else if ( _stricmp( arg.c_str(), ".WATERCOOLINGCOIL.") == 0)
				{
					type_object->m_enum = IfcCoilTypeEnum::IfcCoilTypeEnumEnum::ENUM_WATERCOOLINGCOIL;
				}
				else if ( _stricmp( arg.c_str(), ".WATERHEATINGCOIL.") == 0)
				{
					type_object->m_enum = IfcCoilTypeEnum::IfcCoilTypeEnumEnum::ENUM_WATERHEATINGCOIL;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcCoilTypeEnum::IfcCoilTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcCoilTypeEnum::IfcCoilTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
