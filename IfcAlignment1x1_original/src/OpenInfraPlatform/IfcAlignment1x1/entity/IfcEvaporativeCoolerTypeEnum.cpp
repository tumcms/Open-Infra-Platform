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

#include "IfcEvaporativeCoolerTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcEvaporativeCoolerTypeEnum::IfcEvaporativeCoolerTypeEnum() {}
		IfcEvaporativeCoolerTypeEnum::IfcEvaporativeCoolerTypeEnum(IfcEvaporativeCoolerTypeEnum::IfcEvaporativeCoolerTypeEnumEnum value) { m_enum = value; }
		IfcEvaporativeCoolerTypeEnum::~IfcEvaporativeCoolerTypeEnum() {}
		void IfcEvaporativeCoolerTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcEvaporativeCoolerTypeEnumEnum::ENUM_DIRECTEVAPORATIVERANDOMMEDIAAIRCOOLER)
				{
					stream << ".DIRECTEVAPORATIVERANDOMMEDIAAIRCOOLER.";
				}
				else if ( m_enum == IfcEvaporativeCoolerTypeEnumEnum::ENUM_DIRECTEVAPORATIVERIGIDMEDIAAIRCOOLER)
				{
					stream << ".DIRECTEVAPORATIVERIGIDMEDIAAIRCOOLER.";
				}
				else if ( m_enum == IfcEvaporativeCoolerTypeEnumEnum::ENUM_DIRECTEVAPORATIVESLINGERSPACKAGEDAIRCOOLER)
				{
					stream << ".DIRECTEVAPORATIVESLINGERSPACKAGEDAIRCOOLER.";
				}
				else if ( m_enum == IfcEvaporativeCoolerTypeEnumEnum::ENUM_DIRECTEVAPORATIVEPACKAGEDROTARYAIRCOOLER)
				{
					stream << ".DIRECTEVAPORATIVEPACKAGEDROTARYAIRCOOLER.";
				}
				else if ( m_enum == IfcEvaporativeCoolerTypeEnumEnum::ENUM_DIRECTEVAPORATIVEAIRWASHER)
				{
					stream << ".DIRECTEVAPORATIVEAIRWASHER.";
				}
				else if ( m_enum == IfcEvaporativeCoolerTypeEnumEnum::ENUM_INDIRECTEVAPORATIVEPACKAGEAIRCOOLER)
				{
					stream << ".INDIRECTEVAPORATIVEPACKAGEAIRCOOLER.";
				}
				else if ( m_enum == IfcEvaporativeCoolerTypeEnumEnum::ENUM_INDIRECTEVAPORATIVEWETCOIL)
				{
					stream << ".INDIRECTEVAPORATIVEWETCOIL.";
				}
				else if ( m_enum == IfcEvaporativeCoolerTypeEnumEnum::ENUM_INDIRECTEVAPORATIVECOOLINGTOWERORCOILCOOLER)
				{
					stream << ".INDIRECTEVAPORATIVECOOLINGTOWERORCOILCOOLER.";
				}
				else if ( m_enum == IfcEvaporativeCoolerTypeEnumEnum::ENUM_INDIRECTDIRECTCOMBINATION)
				{
					stream << ".INDIRECTDIRECTCOMBINATION.";
				}
				else if ( m_enum == IfcEvaporativeCoolerTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcEvaporativeCoolerTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcEvaporativeCoolerTypeEnum> IfcEvaporativeCoolerTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcEvaporativeCoolerTypeEnum>(); }
				std::shared_ptr<IfcEvaporativeCoolerTypeEnum> type_object(new IfcEvaporativeCoolerTypeEnum() );
				if ( _stricmp( arg.c_str(), ".DIRECTEVAPORATIVERANDOMMEDIAAIRCOOLER.") == 0)
				{
					type_object->m_enum = IfcEvaporativeCoolerTypeEnum::IfcEvaporativeCoolerTypeEnumEnum::ENUM_DIRECTEVAPORATIVERANDOMMEDIAAIRCOOLER;
				}
				else if ( _stricmp( arg.c_str(), ".DIRECTEVAPORATIVERIGIDMEDIAAIRCOOLER.") == 0)
				{
					type_object->m_enum = IfcEvaporativeCoolerTypeEnum::IfcEvaporativeCoolerTypeEnumEnum::ENUM_DIRECTEVAPORATIVERIGIDMEDIAAIRCOOLER;
				}
				else if ( _stricmp( arg.c_str(), ".DIRECTEVAPORATIVESLINGERSPACKAGEDAIRCOOLER.") == 0)
				{
					type_object->m_enum = IfcEvaporativeCoolerTypeEnum::IfcEvaporativeCoolerTypeEnumEnum::ENUM_DIRECTEVAPORATIVESLINGERSPACKAGEDAIRCOOLER;
				}
				else if ( _stricmp( arg.c_str(), ".DIRECTEVAPORATIVEPACKAGEDROTARYAIRCOOLER.") == 0)
				{
					type_object->m_enum = IfcEvaporativeCoolerTypeEnum::IfcEvaporativeCoolerTypeEnumEnum::ENUM_DIRECTEVAPORATIVEPACKAGEDROTARYAIRCOOLER;
				}
				else if ( _stricmp( arg.c_str(), ".DIRECTEVAPORATIVEAIRWASHER.") == 0)
				{
					type_object->m_enum = IfcEvaporativeCoolerTypeEnum::IfcEvaporativeCoolerTypeEnumEnum::ENUM_DIRECTEVAPORATIVEAIRWASHER;
				}
				else if ( _stricmp( arg.c_str(), ".INDIRECTEVAPORATIVEPACKAGEAIRCOOLER.") == 0)
				{
					type_object->m_enum = IfcEvaporativeCoolerTypeEnum::IfcEvaporativeCoolerTypeEnumEnum::ENUM_INDIRECTEVAPORATIVEPACKAGEAIRCOOLER;
				}
				else if ( _stricmp( arg.c_str(), ".INDIRECTEVAPORATIVEWETCOIL.") == 0)
				{
					type_object->m_enum = IfcEvaporativeCoolerTypeEnum::IfcEvaporativeCoolerTypeEnumEnum::ENUM_INDIRECTEVAPORATIVEWETCOIL;
				}
				else if ( _stricmp( arg.c_str(), ".INDIRECTEVAPORATIVECOOLINGTOWERORCOILCOOLER.") == 0)
				{
					type_object->m_enum = IfcEvaporativeCoolerTypeEnum::IfcEvaporativeCoolerTypeEnumEnum::ENUM_INDIRECTEVAPORATIVECOOLINGTOWERORCOILCOOLER;
				}
				else if ( _stricmp( arg.c_str(), ".INDIRECTDIRECTCOMBINATION.") == 0)
				{
					type_object->m_enum = IfcEvaporativeCoolerTypeEnum::IfcEvaporativeCoolerTypeEnumEnum::ENUM_INDIRECTDIRECTCOMBINATION;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcEvaporativeCoolerTypeEnum::IfcEvaporativeCoolerTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcEvaporativeCoolerTypeEnum::IfcEvaporativeCoolerTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
