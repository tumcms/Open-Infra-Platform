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

#include "IfcMechanicalFastenerTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcMechanicalFastenerTypeEnum::IfcMechanicalFastenerTypeEnum() {}
		IfcMechanicalFastenerTypeEnum::IfcMechanicalFastenerTypeEnum(IfcMechanicalFastenerTypeEnum::IfcMechanicalFastenerTypeEnumEnum value) { m_enum = value; }
		IfcMechanicalFastenerTypeEnum::~IfcMechanicalFastenerTypeEnum() {}
		void IfcMechanicalFastenerTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcMechanicalFastenerTypeEnumEnum::ENUM_ANCHORBOLT)
				{
					stream << ".ANCHORBOLT.";
				}
				else if ( m_enum == IfcMechanicalFastenerTypeEnumEnum::ENUM_BOLT)
				{
					stream << ".BOLT.";
				}
				else if ( m_enum == IfcMechanicalFastenerTypeEnumEnum::ENUM_DOWEL)
				{
					stream << ".DOWEL.";
				}
				else if ( m_enum == IfcMechanicalFastenerTypeEnumEnum::ENUM_NAIL)
				{
					stream << ".NAIL.";
				}
				else if ( m_enum == IfcMechanicalFastenerTypeEnumEnum::ENUM_NAILPLATE)
				{
					stream << ".NAILPLATE.";
				}
				else if ( m_enum == IfcMechanicalFastenerTypeEnumEnum::ENUM_RIVET)
				{
					stream << ".RIVET.";
				}
				else if ( m_enum == IfcMechanicalFastenerTypeEnumEnum::ENUM_SCREW)
				{
					stream << ".SCREW.";
				}
				else if ( m_enum == IfcMechanicalFastenerTypeEnumEnum::ENUM_SHEARCONNECTOR)
				{
					stream << ".SHEARCONNECTOR.";
				}
				else if ( m_enum == IfcMechanicalFastenerTypeEnumEnum::ENUM_STAPLE)
				{
					stream << ".STAPLE.";
				}
				else if ( m_enum == IfcMechanicalFastenerTypeEnumEnum::ENUM_STUDSHEARCONNECTOR)
				{
					stream << ".STUDSHEARCONNECTOR.";
				}
				else if ( m_enum == IfcMechanicalFastenerTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcMechanicalFastenerTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcMechanicalFastenerTypeEnum> IfcMechanicalFastenerTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcMechanicalFastenerTypeEnum>(); }
				std::shared_ptr<IfcMechanicalFastenerTypeEnum> type_object(new IfcMechanicalFastenerTypeEnum() );
				if ( _stricmp( arg.c_str(), ".ANCHORBOLT.") == 0)
				{
					type_object->m_enum = IfcMechanicalFastenerTypeEnum::IfcMechanicalFastenerTypeEnumEnum::ENUM_ANCHORBOLT;
				}
				else if ( _stricmp( arg.c_str(), ".BOLT.") == 0)
				{
					type_object->m_enum = IfcMechanicalFastenerTypeEnum::IfcMechanicalFastenerTypeEnumEnum::ENUM_BOLT;
				}
				else if ( _stricmp( arg.c_str(), ".DOWEL.") == 0)
				{
					type_object->m_enum = IfcMechanicalFastenerTypeEnum::IfcMechanicalFastenerTypeEnumEnum::ENUM_DOWEL;
				}
				else if ( _stricmp( arg.c_str(), ".NAIL.") == 0)
				{
					type_object->m_enum = IfcMechanicalFastenerTypeEnum::IfcMechanicalFastenerTypeEnumEnum::ENUM_NAIL;
				}
				else if ( _stricmp( arg.c_str(), ".NAILPLATE.") == 0)
				{
					type_object->m_enum = IfcMechanicalFastenerTypeEnum::IfcMechanicalFastenerTypeEnumEnum::ENUM_NAILPLATE;
				}
				else if ( _stricmp( arg.c_str(), ".RIVET.") == 0)
				{
					type_object->m_enum = IfcMechanicalFastenerTypeEnum::IfcMechanicalFastenerTypeEnumEnum::ENUM_RIVET;
				}
				else if ( _stricmp( arg.c_str(), ".SCREW.") == 0)
				{
					type_object->m_enum = IfcMechanicalFastenerTypeEnum::IfcMechanicalFastenerTypeEnumEnum::ENUM_SCREW;
				}
				else if ( _stricmp( arg.c_str(), ".SHEARCONNECTOR.") == 0)
				{
					type_object->m_enum = IfcMechanicalFastenerTypeEnum::IfcMechanicalFastenerTypeEnumEnum::ENUM_SHEARCONNECTOR;
				}
				else if ( _stricmp( arg.c_str(), ".STAPLE.") == 0)
				{
					type_object->m_enum = IfcMechanicalFastenerTypeEnum::IfcMechanicalFastenerTypeEnumEnum::ENUM_STAPLE;
				}
				else if ( _stricmp( arg.c_str(), ".STUDSHEARCONNECTOR.") == 0)
				{
					type_object->m_enum = IfcMechanicalFastenerTypeEnum::IfcMechanicalFastenerTypeEnumEnum::ENUM_STUDSHEARCONNECTOR;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcMechanicalFastenerTypeEnum::IfcMechanicalFastenerTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcMechanicalFastenerTypeEnum::IfcMechanicalFastenerTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
