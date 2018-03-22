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

#include "IfcHumidifierTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcHumidifierTypeEnum::IfcHumidifierTypeEnum() {}
		IfcHumidifierTypeEnum::IfcHumidifierTypeEnum(IfcHumidifierTypeEnum::IfcHumidifierTypeEnumEnum value) { m_enum = value; }
		IfcHumidifierTypeEnum::~IfcHumidifierTypeEnum() {}
		void IfcHumidifierTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcHumidifierTypeEnumEnum::ENUM_STEAMINJECTION)
				{
					stream << ".STEAMINJECTION.";
				}
				else if ( m_enum == IfcHumidifierTypeEnumEnum::ENUM_ADIABATICAIRWASHER)
				{
					stream << ".ADIABATICAIRWASHER.";
				}
				else if ( m_enum == IfcHumidifierTypeEnumEnum::ENUM_ADIABATICPAN)
				{
					stream << ".ADIABATICPAN.";
				}
				else if ( m_enum == IfcHumidifierTypeEnumEnum::ENUM_ADIABATICWETTEDELEMENT)
				{
					stream << ".ADIABATICWETTEDELEMENT.";
				}
				else if ( m_enum == IfcHumidifierTypeEnumEnum::ENUM_ADIABATICATOMIZING)
				{
					stream << ".ADIABATICATOMIZING.";
				}
				else if ( m_enum == IfcHumidifierTypeEnumEnum::ENUM_ADIABATICULTRASONIC)
				{
					stream << ".ADIABATICULTRASONIC.";
				}
				else if ( m_enum == IfcHumidifierTypeEnumEnum::ENUM_ADIABATICRIGIDMEDIA)
				{
					stream << ".ADIABATICRIGIDMEDIA.";
				}
				else if ( m_enum == IfcHumidifierTypeEnumEnum::ENUM_ADIABATICCOMPRESSEDAIRNOZZLE)
				{
					stream << ".ADIABATICCOMPRESSEDAIRNOZZLE.";
				}
				else if ( m_enum == IfcHumidifierTypeEnumEnum::ENUM_ASSISTEDELECTRIC)
				{
					stream << ".ASSISTEDELECTRIC.";
				}
				else if ( m_enum == IfcHumidifierTypeEnumEnum::ENUM_ASSISTEDNATURALGAS)
				{
					stream << ".ASSISTEDNATURALGAS.";
				}
				else if ( m_enum == IfcHumidifierTypeEnumEnum::ENUM_ASSISTEDPROPANE)
				{
					stream << ".ASSISTEDPROPANE.";
				}
				else if ( m_enum == IfcHumidifierTypeEnumEnum::ENUM_ASSISTEDBUTANE)
				{
					stream << ".ASSISTEDBUTANE.";
				}
				else if ( m_enum == IfcHumidifierTypeEnumEnum::ENUM_ASSISTEDSTEAM)
				{
					stream << ".ASSISTEDSTEAM.";
				}
				else if ( m_enum == IfcHumidifierTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcHumidifierTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcHumidifierTypeEnum> IfcHumidifierTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcHumidifierTypeEnum>(); }
				std::shared_ptr<IfcHumidifierTypeEnum> type_object(new IfcHumidifierTypeEnum() );
				if ( _stricmp( arg.c_str(), ".STEAMINJECTION.") == 0)
				{
					type_object->m_enum = IfcHumidifierTypeEnum::IfcHumidifierTypeEnumEnum::ENUM_STEAMINJECTION;
				}
				else if ( _stricmp( arg.c_str(), ".ADIABATICAIRWASHER.") == 0)
				{
					type_object->m_enum = IfcHumidifierTypeEnum::IfcHumidifierTypeEnumEnum::ENUM_ADIABATICAIRWASHER;
				}
				else if ( _stricmp( arg.c_str(), ".ADIABATICPAN.") == 0)
				{
					type_object->m_enum = IfcHumidifierTypeEnum::IfcHumidifierTypeEnumEnum::ENUM_ADIABATICPAN;
				}
				else if ( _stricmp( arg.c_str(), ".ADIABATICWETTEDELEMENT.") == 0)
				{
					type_object->m_enum = IfcHumidifierTypeEnum::IfcHumidifierTypeEnumEnum::ENUM_ADIABATICWETTEDELEMENT;
				}
				else if ( _stricmp( arg.c_str(), ".ADIABATICATOMIZING.") == 0)
				{
					type_object->m_enum = IfcHumidifierTypeEnum::IfcHumidifierTypeEnumEnum::ENUM_ADIABATICATOMIZING;
				}
				else if ( _stricmp( arg.c_str(), ".ADIABATICULTRASONIC.") == 0)
				{
					type_object->m_enum = IfcHumidifierTypeEnum::IfcHumidifierTypeEnumEnum::ENUM_ADIABATICULTRASONIC;
				}
				else if ( _stricmp( arg.c_str(), ".ADIABATICRIGIDMEDIA.") == 0)
				{
					type_object->m_enum = IfcHumidifierTypeEnum::IfcHumidifierTypeEnumEnum::ENUM_ADIABATICRIGIDMEDIA;
				}
				else if ( _stricmp( arg.c_str(), ".ADIABATICCOMPRESSEDAIRNOZZLE.") == 0)
				{
					type_object->m_enum = IfcHumidifierTypeEnum::IfcHumidifierTypeEnumEnum::ENUM_ADIABATICCOMPRESSEDAIRNOZZLE;
				}
				else if ( _stricmp( arg.c_str(), ".ASSISTEDELECTRIC.") == 0)
				{
					type_object->m_enum = IfcHumidifierTypeEnum::IfcHumidifierTypeEnumEnum::ENUM_ASSISTEDELECTRIC;
				}
				else if ( _stricmp( arg.c_str(), ".ASSISTEDNATURALGAS.") == 0)
				{
					type_object->m_enum = IfcHumidifierTypeEnum::IfcHumidifierTypeEnumEnum::ENUM_ASSISTEDNATURALGAS;
				}
				else if ( _stricmp( arg.c_str(), ".ASSISTEDPROPANE.") == 0)
				{
					type_object->m_enum = IfcHumidifierTypeEnum::IfcHumidifierTypeEnumEnum::ENUM_ASSISTEDPROPANE;
				}
				else if ( _stricmp( arg.c_str(), ".ASSISTEDBUTANE.") == 0)
				{
					type_object->m_enum = IfcHumidifierTypeEnum::IfcHumidifierTypeEnumEnum::ENUM_ASSISTEDBUTANE;
				}
				else if ( _stricmp( arg.c_str(), ".ASSISTEDSTEAM.") == 0)
				{
					type_object->m_enum = IfcHumidifierTypeEnum::IfcHumidifierTypeEnumEnum::ENUM_ASSISTEDSTEAM;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcHumidifierTypeEnum::IfcHumidifierTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcHumidifierTypeEnum::IfcHumidifierTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
