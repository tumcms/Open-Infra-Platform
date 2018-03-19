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

#include "IfcInterceptorTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcInterceptorTypeEnum::IfcInterceptorTypeEnum() {}
		IfcInterceptorTypeEnum::IfcInterceptorTypeEnum(IfcInterceptorTypeEnum::IfcInterceptorTypeEnumEnum value) { m_enum = value; }
		IfcInterceptorTypeEnum::~IfcInterceptorTypeEnum() {}
		void IfcInterceptorTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcInterceptorTypeEnumEnum::ENUM_CYCLONIC)
				{
					stream << ".CYCLONIC.";
				}
				else if ( m_enum == IfcInterceptorTypeEnumEnum::ENUM_GREASE)
				{
					stream << ".GREASE.";
				}
				else if ( m_enum == IfcInterceptorTypeEnumEnum::ENUM_OIL)
				{
					stream << ".OIL.";
				}
				else if ( m_enum == IfcInterceptorTypeEnumEnum::ENUM_PETROL)
				{
					stream << ".PETROL.";
				}
				else if ( m_enum == IfcInterceptorTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcInterceptorTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcInterceptorTypeEnum> IfcInterceptorTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcInterceptorTypeEnum>(); }
				std::shared_ptr<IfcInterceptorTypeEnum> type_object(new IfcInterceptorTypeEnum() );
				if ( _stricmp( arg.c_str(), ".CYCLONIC.") == 0)
				{
					type_object->m_enum = IfcInterceptorTypeEnum::IfcInterceptorTypeEnumEnum::ENUM_CYCLONIC;
				}
				else if ( _stricmp( arg.c_str(), ".GREASE.") == 0)
				{
					type_object->m_enum = IfcInterceptorTypeEnum::IfcInterceptorTypeEnumEnum::ENUM_GREASE;
				}
				else if ( _stricmp( arg.c_str(), ".OIL.") == 0)
				{
					type_object->m_enum = IfcInterceptorTypeEnum::IfcInterceptorTypeEnumEnum::ENUM_OIL;
				}
				else if ( _stricmp( arg.c_str(), ".PETROL.") == 0)
				{
					type_object->m_enum = IfcInterceptorTypeEnum::IfcInterceptorTypeEnumEnum::ENUM_PETROL;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcInterceptorTypeEnum::IfcInterceptorTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcInterceptorTypeEnum::IfcInterceptorTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
