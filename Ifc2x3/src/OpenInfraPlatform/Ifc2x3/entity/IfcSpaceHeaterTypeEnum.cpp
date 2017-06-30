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
#include "include/IfcSpaceHeaterTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcSpaceHeaterTypeEnum 
		IfcSpaceHeaterTypeEnum::IfcSpaceHeaterTypeEnum() {}
		IfcSpaceHeaterTypeEnum::~IfcSpaceHeaterTypeEnum() {}
		void IfcSpaceHeaterTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCSPACEHEATERTYPEENUM("; }
			if( m_enum == ENUM_SECTIONALRADIATOR )
			{
				stream << ".SECTIONALRADIATOR.";
			}
			else if( m_enum == ENUM_PANELRADIATOR )
			{
				stream << ".PANELRADIATOR.";
			}
			else if( m_enum == ENUM_TUBULARRADIATOR )
			{
				stream << ".TUBULARRADIATOR.";
			}
			else if( m_enum == ENUM_CONVECTOR )
			{
				stream << ".CONVECTOR.";
			}
			else if( m_enum == ENUM_BASEBOARDHEATER )
			{
				stream << ".BASEBOARDHEATER.";
			}
			else if( m_enum == ENUM_FINNEDTUBEUNIT )
			{
				stream << ".FINNEDTUBEUNIT.";
			}
			else if( m_enum == ENUM_UNITHEATER )
			{
				stream << ".UNITHEATER.";
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
		shared_ptr<IfcSpaceHeaterTypeEnum> IfcSpaceHeaterTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcSpaceHeaterTypeEnum>(); }
			shared_ptr<IfcSpaceHeaterTypeEnum> type_object( new IfcSpaceHeaterTypeEnum() );
			if( _stricmp( arg.c_str(), ".SECTIONALRADIATOR." ) == 0 )
			{
				type_object->m_enum = IfcSpaceHeaterTypeEnum::ENUM_SECTIONALRADIATOR;
			}
			else if( _stricmp( arg.c_str(), ".PANELRADIATOR." ) == 0 )
			{
				type_object->m_enum = IfcSpaceHeaterTypeEnum::ENUM_PANELRADIATOR;
			}
			else if( _stricmp( arg.c_str(), ".TUBULARRADIATOR." ) == 0 )
			{
				type_object->m_enum = IfcSpaceHeaterTypeEnum::ENUM_TUBULARRADIATOR;
			}
			else if( _stricmp( arg.c_str(), ".CONVECTOR." ) == 0 )
			{
				type_object->m_enum = IfcSpaceHeaterTypeEnum::ENUM_CONVECTOR;
			}
			else if( _stricmp( arg.c_str(), ".BASEBOARDHEATER." ) == 0 )
			{
				type_object->m_enum = IfcSpaceHeaterTypeEnum::ENUM_BASEBOARDHEATER;
			}
			else if( _stricmp( arg.c_str(), ".FINNEDTUBEUNIT." ) == 0 )
			{
				type_object->m_enum = IfcSpaceHeaterTypeEnum::ENUM_FINNEDTUBEUNIT;
			}
			else if( _stricmp( arg.c_str(), ".UNITHEATER." ) == 0 )
			{
				type_object->m_enum = IfcSpaceHeaterTypeEnum::ENUM_UNITHEATER;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcSpaceHeaterTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcSpaceHeaterTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
