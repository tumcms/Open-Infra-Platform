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

#include "IfcActionSourceTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcActionSourceTypeEnum::IfcActionSourceTypeEnum() {}
		IfcActionSourceTypeEnum::IfcActionSourceTypeEnum(IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum value) { m_enum = value; }
		IfcActionSourceTypeEnum::~IfcActionSourceTypeEnum() {}
		void IfcActionSourceTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_DEAD_LOAD_G)
				{
					stream << ".DEAD_LOAD_G.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_COMPLETION_G1)
				{
					stream << ".COMPLETION_G1.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_LIVE_LOAD_Q)
				{
					stream << ".LIVE_LOAD_Q.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_SNOW_S)
				{
					stream << ".SNOW_S.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_WIND_W)
				{
					stream << ".WIND_W.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_PRESTRESSING_P)
				{
					stream << ".PRESTRESSING_P.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_SETTLEMENT_U)
				{
					stream << ".SETTLEMENT_U.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_TEMPERATURE_T)
				{
					stream << ".TEMPERATURE_T.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_EARTHQUAKE_E)
				{
					stream << ".EARTHQUAKE_E.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_FIRE)
				{
					stream << ".FIRE.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_IMPULSE)
				{
					stream << ".IMPULSE.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_IMPACT)
				{
					stream << ".IMPACT.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_TRANSPORT)
				{
					stream << ".TRANSPORT.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_ERECTION)
				{
					stream << ".ERECTION.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_PROPPING)
				{
					stream << ".PROPPING.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_SYSTEM_IMPERFECTION)
				{
					stream << ".SYSTEM_IMPERFECTION.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_SHRINKAGE)
				{
					stream << ".SHRINKAGE.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_CREEP)
				{
					stream << ".CREEP.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_LACK_OF_FIT)
				{
					stream << ".LACK_OF_FIT.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_BUOYANCY)
				{
					stream << ".BUOYANCY.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_ICE)
				{
					stream << ".ICE.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_CURRENT)
				{
					stream << ".CURRENT.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_WAVE)
				{
					stream << ".WAVE.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_RAIN)
				{
					stream << ".RAIN.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_BRAKES)
				{
					stream << ".BRAKES.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcActionSourceTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcActionSourceTypeEnum> IfcActionSourceTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcActionSourceTypeEnum>(); }
				std::shared_ptr<IfcActionSourceTypeEnum> type_object(new IfcActionSourceTypeEnum() );
				if ( _stricmp( arg.c_str(), ".DEAD_LOAD_G.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_DEAD_LOAD_G;
				}
				else if ( _stricmp( arg.c_str(), ".COMPLETION_G1.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_COMPLETION_G1;
				}
				else if ( _stricmp( arg.c_str(), ".LIVE_LOAD_Q.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_LIVE_LOAD_Q;
				}
				else if ( _stricmp( arg.c_str(), ".SNOW_S.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_SNOW_S;
				}
				else if ( _stricmp( arg.c_str(), ".WIND_W.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_WIND_W;
				}
				else if ( _stricmp( arg.c_str(), ".PRESTRESSING_P.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_PRESTRESSING_P;
				}
				else if ( _stricmp( arg.c_str(), ".SETTLEMENT_U.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_SETTLEMENT_U;
				}
				else if ( _stricmp( arg.c_str(), ".TEMPERATURE_T.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_TEMPERATURE_T;
				}
				else if ( _stricmp( arg.c_str(), ".EARTHQUAKE_E.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_EARTHQUAKE_E;
				}
				else if ( _stricmp( arg.c_str(), ".FIRE.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_FIRE;
				}
				else if ( _stricmp( arg.c_str(), ".IMPULSE.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_IMPULSE;
				}
				else if ( _stricmp( arg.c_str(), ".IMPACT.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_IMPACT;
				}
				else if ( _stricmp( arg.c_str(), ".TRANSPORT.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_TRANSPORT;
				}
				else if ( _stricmp( arg.c_str(), ".ERECTION.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_ERECTION;
				}
				else if ( _stricmp( arg.c_str(), ".PROPPING.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_PROPPING;
				}
				else if ( _stricmp( arg.c_str(), ".SYSTEM_IMPERFECTION.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_SYSTEM_IMPERFECTION;
				}
				else if ( _stricmp( arg.c_str(), ".SHRINKAGE.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_SHRINKAGE;
				}
				else if ( _stricmp( arg.c_str(), ".CREEP.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_CREEP;
				}
				else if ( _stricmp( arg.c_str(), ".LACK_OF_FIT.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_LACK_OF_FIT;
				}
				else if ( _stricmp( arg.c_str(), ".BUOYANCY.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_BUOYANCY;
				}
				else if ( _stricmp( arg.c_str(), ".ICE.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_ICE;
				}
				else if ( _stricmp( arg.c_str(), ".CURRENT.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_CURRENT;
				}
				else if ( _stricmp( arg.c_str(), ".WAVE.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_WAVE;
				}
				else if ( _stricmp( arg.c_str(), ".RAIN.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_RAIN;
				}
				else if ( _stricmp( arg.c_str(), ".BRAKES.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_BRAKES;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcActionSourceTypeEnum::IfcActionSourceTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
