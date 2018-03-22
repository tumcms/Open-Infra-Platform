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

#include "IfcControllerTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcControllerTypeEnum::IfcControllerTypeEnum() {}
		IfcControllerTypeEnum::IfcControllerTypeEnum(IfcControllerTypeEnum::IfcControllerTypeEnumEnum value) { m_enum = value; }
		IfcControllerTypeEnum::~IfcControllerTypeEnum() {}
		void IfcControllerTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcControllerTypeEnumEnum::ENUM_FLOATING)
				{
					stream << ".FLOATING.";
				}
				else if ( m_enum == IfcControllerTypeEnumEnum::ENUM_PROGRAMMABLE)
				{
					stream << ".PROGRAMMABLE.";
				}
				else if ( m_enum == IfcControllerTypeEnumEnum::ENUM_PROPORTIONAL)
				{
					stream << ".PROPORTIONAL.";
				}
				else if ( m_enum == IfcControllerTypeEnumEnum::ENUM_MULTIPOSITION)
				{
					stream << ".MULTIPOSITION.";
				}
				else if ( m_enum == IfcControllerTypeEnumEnum::ENUM_TWOPOSITION)
				{
					stream << ".TWOPOSITION.";
				}
				else if ( m_enum == IfcControllerTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcControllerTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcControllerTypeEnum> IfcControllerTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcControllerTypeEnum>(); }
				std::shared_ptr<IfcControllerTypeEnum> type_object(new IfcControllerTypeEnum() );
				if ( _stricmp( arg.c_str(), ".FLOATING.") == 0)
				{
					type_object->m_enum = IfcControllerTypeEnum::IfcControllerTypeEnumEnum::ENUM_FLOATING;
				}
				else if ( _stricmp( arg.c_str(), ".PROGRAMMABLE.") == 0)
				{
					type_object->m_enum = IfcControllerTypeEnum::IfcControllerTypeEnumEnum::ENUM_PROGRAMMABLE;
				}
				else if ( _stricmp( arg.c_str(), ".PROPORTIONAL.") == 0)
				{
					type_object->m_enum = IfcControllerTypeEnum::IfcControllerTypeEnumEnum::ENUM_PROPORTIONAL;
				}
				else if ( _stricmp( arg.c_str(), ".MULTIPOSITION.") == 0)
				{
					type_object->m_enum = IfcControllerTypeEnum::IfcControllerTypeEnumEnum::ENUM_MULTIPOSITION;
				}
				else if ( _stricmp( arg.c_str(), ".TWOPOSITION.") == 0)
				{
					type_object->m_enum = IfcControllerTypeEnum::IfcControllerTypeEnumEnum::ENUM_TWOPOSITION;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcControllerTypeEnum::IfcControllerTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcControllerTypeEnum::IfcControllerTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
