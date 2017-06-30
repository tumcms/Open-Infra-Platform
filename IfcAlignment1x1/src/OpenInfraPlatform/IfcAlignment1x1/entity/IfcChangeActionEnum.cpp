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

#include "IfcChangeActionEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcChangeActionEnum::IfcChangeActionEnum() {}
		IfcChangeActionEnum::IfcChangeActionEnum(IfcChangeActionEnum::IfcChangeActionEnumEnum value) { m_enum = value; }
		IfcChangeActionEnum::~IfcChangeActionEnum() {}
		void IfcChangeActionEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcChangeActionEnumEnum::ENUM_NOCHANGE)
				{
					stream << ".NOCHANGE.";
				}
				else if ( m_enum == IfcChangeActionEnumEnum::ENUM_MODIFIED)
				{
					stream << ".MODIFIED.";
				}
				else if ( m_enum == IfcChangeActionEnumEnum::ENUM_ADDED)
				{
					stream << ".ADDED.";
				}
				else if ( m_enum == IfcChangeActionEnumEnum::ENUM_DELETED)
				{
					stream << ".DELETED.";
				}
				else if ( m_enum == IfcChangeActionEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcChangeActionEnum> IfcChangeActionEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcChangeActionEnum>(); }
				std::shared_ptr<IfcChangeActionEnum> type_object(new IfcChangeActionEnum() );
				if ( _stricmp( arg.c_str(), ".NOCHANGE.") == 0)
				{
					type_object->m_enum = IfcChangeActionEnum::IfcChangeActionEnumEnum::ENUM_NOCHANGE;
				}
				else if ( _stricmp( arg.c_str(), ".MODIFIED.") == 0)
				{
					type_object->m_enum = IfcChangeActionEnum::IfcChangeActionEnumEnum::ENUM_MODIFIED;
				}
				else if ( _stricmp( arg.c_str(), ".ADDED.") == 0)
				{
					type_object->m_enum = IfcChangeActionEnum::IfcChangeActionEnumEnum::ENUM_ADDED;
				}
				else if ( _stricmp( arg.c_str(), ".DELETED.") == 0)
				{
					type_object->m_enum = IfcChangeActionEnum::IfcChangeActionEnumEnum::ENUM_DELETED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcChangeActionEnum::IfcChangeActionEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
