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

#include "IfcAirToAirHeatRecoveryTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcAirToAirHeatRecoveryTypeEnum::IfcAirToAirHeatRecoveryTypeEnum() {}
		IfcAirToAirHeatRecoveryTypeEnum::IfcAirToAirHeatRecoveryTypeEnum(IfcAirToAirHeatRecoveryTypeEnum::IfcAirToAirHeatRecoveryTypeEnumEnum value) { m_enum = value; }
		IfcAirToAirHeatRecoveryTypeEnum::~IfcAirToAirHeatRecoveryTypeEnum() {}
		void IfcAirToAirHeatRecoveryTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_FIXEDPLATECOUNTERFLOWEXCHANGER)
				{
					stream << ".FIXEDPLATECOUNTERFLOWEXCHANGER.";
				}
				else if ( m_enum == IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_FIXEDPLATECROSSFLOWEXCHANGER)
				{
					stream << ".FIXEDPLATECROSSFLOWEXCHANGER.";
				}
				else if ( m_enum == IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_FIXEDPLATEPARALLELFLOWEXCHANGER)
				{
					stream << ".FIXEDPLATEPARALLELFLOWEXCHANGER.";
				}
				else if ( m_enum == IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_ROTARYWHEEL)
				{
					stream << ".ROTARYWHEEL.";
				}
				else if ( m_enum == IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_RUNAROUNDCOILLOOP)
				{
					stream << ".RUNAROUNDCOILLOOP.";
				}
				else if ( m_enum == IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_HEATPIPE)
				{
					stream << ".HEATPIPE.";
				}
				else if ( m_enum == IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_TWINTOWERENTHALPYRECOVERYLOOPS)
				{
					stream << ".TWINTOWERENTHALPYRECOVERYLOOPS.";
				}
				else if ( m_enum == IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_THERMOSIPHONSEALEDTUBEHEATEXCHANGERS)
				{
					stream << ".THERMOSIPHONSEALEDTUBEHEATEXCHANGERS.";
				}
				else if ( m_enum == IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_THERMOSIPHONCOILTYPEHEATEXCHANGERS)
				{
					stream << ".THERMOSIPHONCOILTYPEHEATEXCHANGERS.";
				}
				else if ( m_enum == IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcAirToAirHeatRecoveryTypeEnum> IfcAirToAirHeatRecoveryTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcAirToAirHeatRecoveryTypeEnum>(); }
				std::shared_ptr<IfcAirToAirHeatRecoveryTypeEnum> type_object(new IfcAirToAirHeatRecoveryTypeEnum() );
				if ( _stricmp( arg.c_str(), ".FIXEDPLATECOUNTERFLOWEXCHANGER.") == 0)
				{
					type_object->m_enum = IfcAirToAirHeatRecoveryTypeEnum::IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_FIXEDPLATECOUNTERFLOWEXCHANGER;
				}
				else if ( _stricmp( arg.c_str(), ".FIXEDPLATECROSSFLOWEXCHANGER.") == 0)
				{
					type_object->m_enum = IfcAirToAirHeatRecoveryTypeEnum::IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_FIXEDPLATECROSSFLOWEXCHANGER;
				}
				else if ( _stricmp( arg.c_str(), ".FIXEDPLATEPARALLELFLOWEXCHANGER.") == 0)
				{
					type_object->m_enum = IfcAirToAirHeatRecoveryTypeEnum::IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_FIXEDPLATEPARALLELFLOWEXCHANGER;
				}
				else if ( _stricmp( arg.c_str(), ".ROTARYWHEEL.") == 0)
				{
					type_object->m_enum = IfcAirToAirHeatRecoveryTypeEnum::IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_ROTARYWHEEL;
				}
				else if ( _stricmp( arg.c_str(), ".RUNAROUNDCOILLOOP.") == 0)
				{
					type_object->m_enum = IfcAirToAirHeatRecoveryTypeEnum::IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_RUNAROUNDCOILLOOP;
				}
				else if ( _stricmp( arg.c_str(), ".HEATPIPE.") == 0)
				{
					type_object->m_enum = IfcAirToAirHeatRecoveryTypeEnum::IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_HEATPIPE;
				}
				else if ( _stricmp( arg.c_str(), ".TWINTOWERENTHALPYRECOVERYLOOPS.") == 0)
				{
					type_object->m_enum = IfcAirToAirHeatRecoveryTypeEnum::IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_TWINTOWERENTHALPYRECOVERYLOOPS;
				}
				else if ( _stricmp( arg.c_str(), ".THERMOSIPHONSEALEDTUBEHEATEXCHANGERS.") == 0)
				{
					type_object->m_enum = IfcAirToAirHeatRecoveryTypeEnum::IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_THERMOSIPHONSEALEDTUBEHEATEXCHANGERS;
				}
				else if ( _stricmp( arg.c_str(), ".THERMOSIPHONCOILTYPEHEATEXCHANGERS.") == 0)
				{
					type_object->m_enum = IfcAirToAirHeatRecoveryTypeEnum::IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_THERMOSIPHONCOILTYPEHEATEXCHANGERS;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcAirToAirHeatRecoveryTypeEnum::IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcAirToAirHeatRecoveryTypeEnum::IfcAirToAirHeatRecoveryTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
