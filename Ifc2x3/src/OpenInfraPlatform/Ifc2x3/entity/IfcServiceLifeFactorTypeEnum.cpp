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
#include "include/IfcServiceLifeFactorTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcServiceLifeFactorTypeEnum 
		IfcServiceLifeFactorTypeEnum::IfcServiceLifeFactorTypeEnum() {}
		IfcServiceLifeFactorTypeEnum::~IfcServiceLifeFactorTypeEnum() {}
		void IfcServiceLifeFactorTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCSERVICELIFEFACTORTYPEENUM("; }
			if( m_enum == ENUM_A_QUALITYOFCOMPONENTS )
			{
				stream << ".A_QUALITYOFCOMPONENTS.";
			}
			else if( m_enum == ENUM_B_DESIGNLEVEL )
			{
				stream << ".B_DESIGNLEVEL.";
			}
			else if( m_enum == ENUM_C_WORKEXECUTIONLEVEL )
			{
				stream << ".C_WORKEXECUTIONLEVEL.";
			}
			else if( m_enum == ENUM_D_INDOORENVIRONMENT )
			{
				stream << ".D_INDOORENVIRONMENT.";
			}
			else if( m_enum == ENUM_E_OUTDOORENVIRONMENT )
			{
				stream << ".E_OUTDOORENVIRONMENT.";
			}
			else if( m_enum == ENUM_F_INUSECONDITIONS )
			{
				stream << ".F_INUSECONDITIONS.";
			}
			else if( m_enum == ENUM_G_MAINTENANCELEVEL )
			{
				stream << ".G_MAINTENANCELEVEL.";
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
		shared_ptr<IfcServiceLifeFactorTypeEnum> IfcServiceLifeFactorTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcServiceLifeFactorTypeEnum>(); }
			shared_ptr<IfcServiceLifeFactorTypeEnum> type_object( new IfcServiceLifeFactorTypeEnum() );
			if( _stricmp( arg.c_str(), ".A_QUALITYOFCOMPONENTS." ) == 0 )
			{
				type_object->m_enum = IfcServiceLifeFactorTypeEnum::ENUM_A_QUALITYOFCOMPONENTS;
			}
			else if( _stricmp( arg.c_str(), ".B_DESIGNLEVEL." ) == 0 )
			{
				type_object->m_enum = IfcServiceLifeFactorTypeEnum::ENUM_B_DESIGNLEVEL;
			}
			else if( _stricmp( arg.c_str(), ".C_WORKEXECUTIONLEVEL." ) == 0 )
			{
				type_object->m_enum = IfcServiceLifeFactorTypeEnum::ENUM_C_WORKEXECUTIONLEVEL;
			}
			else if( _stricmp( arg.c_str(), ".D_INDOORENVIRONMENT." ) == 0 )
			{
				type_object->m_enum = IfcServiceLifeFactorTypeEnum::ENUM_D_INDOORENVIRONMENT;
			}
			else if( _stricmp( arg.c_str(), ".E_OUTDOORENVIRONMENT." ) == 0 )
			{
				type_object->m_enum = IfcServiceLifeFactorTypeEnum::ENUM_E_OUTDOORENVIRONMENT;
			}
			else if( _stricmp( arg.c_str(), ".F_INUSECONDITIONS." ) == 0 )
			{
				type_object->m_enum = IfcServiceLifeFactorTypeEnum::ENUM_F_INUSECONDITIONS;
			}
			else if( _stricmp( arg.c_str(), ".G_MAINTENANCELEVEL." ) == 0 )
			{
				type_object->m_enum = IfcServiceLifeFactorTypeEnum::ENUM_G_MAINTENANCELEVEL;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcServiceLifeFactorTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcServiceLifeFactorTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
