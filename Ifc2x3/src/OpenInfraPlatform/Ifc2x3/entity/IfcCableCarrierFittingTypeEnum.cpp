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
#include "include/IfcCableCarrierFittingTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcCableCarrierFittingTypeEnum 
		IfcCableCarrierFittingTypeEnum::IfcCableCarrierFittingTypeEnum() {}
		IfcCableCarrierFittingTypeEnum::~IfcCableCarrierFittingTypeEnum() {}
		void IfcCableCarrierFittingTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCCABLECARRIERFITTINGTYPEENUM("; }
			if( m_enum == ENUM_BEND )
			{
				stream << ".BEND.";
			}
			else if( m_enum == ENUM_CROSS )
			{
				stream << ".CROSS.";
			}
			else if( m_enum == ENUM_REDUCER )
			{
				stream << ".REDUCER.";
			}
			else if( m_enum == ENUM_TEE )
			{
				stream << ".TEE.";
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
		shared_ptr<IfcCableCarrierFittingTypeEnum> IfcCableCarrierFittingTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcCableCarrierFittingTypeEnum>(); }
			shared_ptr<IfcCableCarrierFittingTypeEnum> type_object( new IfcCableCarrierFittingTypeEnum() );
			if( _stricmp( arg.c_str(), ".BEND." ) == 0 )
			{
				type_object->m_enum = IfcCableCarrierFittingTypeEnum::ENUM_BEND;
			}
			else if( _stricmp( arg.c_str(), ".CROSS." ) == 0 )
			{
				type_object->m_enum = IfcCableCarrierFittingTypeEnum::ENUM_CROSS;
			}
			else if( _stricmp( arg.c_str(), ".REDUCER." ) == 0 )
			{
				type_object->m_enum = IfcCableCarrierFittingTypeEnum::ENUM_REDUCER;
			}
			else if( _stricmp( arg.c_str(), ".TEE." ) == 0 )
			{
				type_object->m_enum = IfcCableCarrierFittingTypeEnum::ENUM_TEE;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcCableCarrierFittingTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcCableCarrierFittingTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
