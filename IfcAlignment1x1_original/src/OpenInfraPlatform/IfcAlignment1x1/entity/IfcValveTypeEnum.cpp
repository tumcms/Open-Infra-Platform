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

#include "IfcValveTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcValveTypeEnum::IfcValveTypeEnum() {}
		IfcValveTypeEnum::IfcValveTypeEnum(IfcValveTypeEnum::IfcValveTypeEnumEnum value) { m_enum = value; }
		IfcValveTypeEnum::~IfcValveTypeEnum() {}
		void IfcValveTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcValveTypeEnumEnum::ENUM_AIRRELEASE)
				{
					stream << ".AIRRELEASE.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_ANTIVACUUM)
				{
					stream << ".ANTIVACUUM.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_CHANGEOVER)
				{
					stream << ".CHANGEOVER.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_CHECK)
				{
					stream << ".CHECK.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_COMMISSIONING)
				{
					stream << ".COMMISSIONING.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_DIVERTING)
				{
					stream << ".DIVERTING.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_DRAWOFFCOCK)
				{
					stream << ".DRAWOFFCOCK.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_DOUBLECHECK)
				{
					stream << ".DOUBLECHECK.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_DOUBLEREGULATING)
				{
					stream << ".DOUBLEREGULATING.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_FAUCET)
				{
					stream << ".FAUCET.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_FLUSHING)
				{
					stream << ".FLUSHING.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_GASCOCK)
				{
					stream << ".GASCOCK.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_GASTAP)
				{
					stream << ".GASTAP.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_ISOLATING)
				{
					stream << ".ISOLATING.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_MIXING)
				{
					stream << ".MIXING.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_PRESSUREREDUCING)
				{
					stream << ".PRESSUREREDUCING.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_PRESSURERELIEF)
				{
					stream << ".PRESSURERELIEF.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_REGULATING)
				{
					stream << ".REGULATING.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_SAFETYCUTOFF)
				{
					stream << ".SAFETYCUTOFF.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_STEAMTRAP)
				{
					stream << ".STEAMTRAP.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_STOPCOCK)
				{
					stream << ".STOPCOCK.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcValveTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcValveTypeEnum> IfcValveTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcValveTypeEnum>(); }
				std::shared_ptr<IfcValveTypeEnum> type_object(new IfcValveTypeEnum() );
				if ( _stricmp( arg.c_str(), ".AIRRELEASE.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_AIRRELEASE;
				}
				else if ( _stricmp( arg.c_str(), ".ANTIVACUUM.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_ANTIVACUUM;
				}
				else if ( _stricmp( arg.c_str(), ".CHANGEOVER.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_CHANGEOVER;
				}
				else if ( _stricmp( arg.c_str(), ".CHECK.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_CHECK;
				}
				else if ( _stricmp( arg.c_str(), ".COMMISSIONING.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_COMMISSIONING;
				}
				else if ( _stricmp( arg.c_str(), ".DIVERTING.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_DIVERTING;
				}
				else if ( _stricmp( arg.c_str(), ".DRAWOFFCOCK.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_DRAWOFFCOCK;
				}
				else if ( _stricmp( arg.c_str(), ".DOUBLECHECK.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_DOUBLECHECK;
				}
				else if ( _stricmp( arg.c_str(), ".DOUBLEREGULATING.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_DOUBLEREGULATING;
				}
				else if ( _stricmp( arg.c_str(), ".FAUCET.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_FAUCET;
				}
				else if ( _stricmp( arg.c_str(), ".FLUSHING.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_FLUSHING;
				}
				else if ( _stricmp( arg.c_str(), ".GASCOCK.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_GASCOCK;
				}
				else if ( _stricmp( arg.c_str(), ".GASTAP.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_GASTAP;
				}
				else if ( _stricmp( arg.c_str(), ".ISOLATING.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_ISOLATING;
				}
				else if ( _stricmp( arg.c_str(), ".MIXING.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_MIXING;
				}
				else if ( _stricmp( arg.c_str(), ".PRESSUREREDUCING.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_PRESSUREREDUCING;
				}
				else if ( _stricmp( arg.c_str(), ".PRESSURERELIEF.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_PRESSURERELIEF;
				}
				else if ( _stricmp( arg.c_str(), ".REGULATING.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_REGULATING;
				}
				else if ( _stricmp( arg.c_str(), ".SAFETYCUTOFF.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_SAFETYCUTOFF;
				}
				else if ( _stricmp( arg.c_str(), ".STEAMTRAP.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_STEAMTRAP;
				}
				else if ( _stricmp( arg.c_str(), ".STOPCOCK.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_STOPCOCK;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcValveTypeEnum::IfcValveTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
