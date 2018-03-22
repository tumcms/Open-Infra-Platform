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

#include "IfcTextPath.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcTextPath::IfcTextPath() {}
		IfcTextPath::IfcTextPath(IfcTextPath::IfcTextPathEnum value) { m_enum = value; }
		IfcTextPath::~IfcTextPath() {}
		void IfcTextPath::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcTextPathEnum::ENUM_LEFT)
				{
					stream << ".LEFT.";
				}
				else if ( m_enum == IfcTextPathEnum::ENUM_RIGHT)
				{
					stream << ".RIGHT.";
				}
				else if ( m_enum == IfcTextPathEnum::ENUM_UP)
				{
					stream << ".UP.";
				}
				else if ( m_enum == IfcTextPathEnum::ENUM_DOWN)
				{
					stream << ".DOWN.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcTextPath> IfcTextPath::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcTextPath>(); }
				std::shared_ptr<IfcTextPath> type_object(new IfcTextPath() );
				if ( _stricmp( arg.c_str(), ".LEFT.") == 0)
				{
					type_object->m_enum = IfcTextPath::IfcTextPathEnum::ENUM_LEFT;
				}
				else if ( _stricmp( arg.c_str(), ".RIGHT.") == 0)
				{
					type_object->m_enum = IfcTextPath::IfcTextPathEnum::ENUM_RIGHT;
				}
				else if ( _stricmp( arg.c_str(), ".UP.") == 0)
				{
					type_object->m_enum = IfcTextPath::IfcTextPathEnum::ENUM_UP;
				}
				else if ( _stricmp( arg.c_str(), ".DOWN.") == 0)
				{
					type_object->m_enum = IfcTextPath::IfcTextPathEnum::ENUM_DOWN;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
