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

#include <sstream>
#include <limits>
#include <map>
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "../model/shared_ptr.h"
#include "../model/Ifc2x3Exception.h"
#include "include/IfcElectricDistributionPointFunctionEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcElectricDistributionPointFunctionEnum 
		IfcElectricDistributionPointFunctionEnum::IfcElectricDistributionPointFunctionEnum() {}
		IfcElectricDistributionPointFunctionEnum::~IfcElectricDistributionPointFunctionEnum() {}
		void IfcElectricDistributionPointFunctionEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCELECTRICDISTRIBUTIONPOINTFUNCTIONENUM("; }
			if( m_enum == ENUM_ALARMPANEL )
			{
				stream << ".ALARMPANEL.";
			}
			else if( m_enum == ENUM_CONSUMERUNIT )
			{
				stream << ".CONSUMERUNIT.";
			}
			else if( m_enum == ENUM_CONTROLPANEL )
			{
				stream << ".CONTROLPANEL.";
			}
			else if( m_enum == ENUM_DISTRIBUTIONBOARD )
			{
				stream << ".DISTRIBUTIONBOARD.";
			}
			else if( m_enum == ENUM_GASDETECTORPANEL )
			{
				stream << ".GASDETECTORPANEL.";
			}
			else if( m_enum == ENUM_INDICATORPANEL )
			{
				stream << ".INDICATORPANEL.";
			}
			else if( m_enum == ENUM_MIMICPANEL )
			{
				stream << ".MIMICPANEL.";
			}
			else if( m_enum == ENUM_MOTORCONTROLCENTRE )
			{
				stream << ".MOTORCONTROLCENTRE.";
			}
			else if( m_enum == ENUM_SWITCHBOARD )
			{
				stream << ".SWITCHBOARD.";
			}
			else if( m_enum == ENUM_USERDEFINED )
			{
				stream << ".USERDEFINED.";
			}
			else if( m_enum == ENUM_NOTDEFINED )
			{
				stream << ".NOTDEFINED.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcElectricDistributionPointFunctionEnum> IfcElectricDistributionPointFunctionEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcElectricDistributionPointFunctionEnum>(); }
			shared_ptr<IfcElectricDistributionPointFunctionEnum> type_object( new IfcElectricDistributionPointFunctionEnum() );
			if( _stricmp( arg.c_str(), ".ALARMPANEL." ) == 0 )
			{
				type_object->m_enum = IfcElectricDistributionPointFunctionEnum::ENUM_ALARMPANEL;
			}
			else if( _stricmp( arg.c_str(), ".CONSUMERUNIT." ) == 0 )
			{
				type_object->m_enum = IfcElectricDistributionPointFunctionEnum::ENUM_CONSUMERUNIT;
			}
			else if( _stricmp( arg.c_str(), ".CONTROLPANEL." ) == 0 )
			{
				type_object->m_enum = IfcElectricDistributionPointFunctionEnum::ENUM_CONTROLPANEL;
			}
			else if( _stricmp( arg.c_str(), ".DISTRIBUTIONBOARD." ) == 0 )
			{
				type_object->m_enum = IfcElectricDistributionPointFunctionEnum::ENUM_DISTRIBUTIONBOARD;
			}
			else if( _stricmp( arg.c_str(), ".GASDETECTORPANEL." ) == 0 )
			{
				type_object->m_enum = IfcElectricDistributionPointFunctionEnum::ENUM_GASDETECTORPANEL;
			}
			else if( _stricmp( arg.c_str(), ".INDICATORPANEL." ) == 0 )
			{
				type_object->m_enum = IfcElectricDistributionPointFunctionEnum::ENUM_INDICATORPANEL;
			}
			else if( _stricmp( arg.c_str(), ".MIMICPANEL." ) == 0 )
			{
				type_object->m_enum = IfcElectricDistributionPointFunctionEnum::ENUM_MIMICPANEL;
			}
			else if( _stricmp( arg.c_str(), ".MOTORCONTROLCENTRE." ) == 0 )
			{
				type_object->m_enum = IfcElectricDistributionPointFunctionEnum::ENUM_MOTORCONTROLCENTRE;
			}
			else if( _stricmp( arg.c_str(), ".SWITCHBOARD." ) == 0 )
			{
				type_object->m_enum = IfcElectricDistributionPointFunctionEnum::ENUM_SWITCHBOARD;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcElectricDistributionPointFunctionEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcElectricDistributionPointFunctionEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
