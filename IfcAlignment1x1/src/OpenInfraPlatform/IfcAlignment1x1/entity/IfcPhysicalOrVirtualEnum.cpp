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

#include "IfcPhysicalOrVirtualEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcPhysicalOrVirtualEnum::IfcPhysicalOrVirtualEnum() {}
		IfcPhysicalOrVirtualEnum::IfcPhysicalOrVirtualEnum(IfcPhysicalOrVirtualEnum::IfcPhysicalOrVirtualEnumEnum value) { m_enum = value; }
		IfcPhysicalOrVirtualEnum::~IfcPhysicalOrVirtualEnum() {}
		void IfcPhysicalOrVirtualEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcPhysicalOrVirtualEnumEnum::ENUM_PHYSICAL)
				{
					stream << ".PHYSICAL.";
				}
				else if ( m_enum == IfcPhysicalOrVirtualEnumEnum::ENUM_VIRTUAL)
				{
					stream << ".VIRTUAL.";
				}
				else if ( m_enum == IfcPhysicalOrVirtualEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcPhysicalOrVirtualEnum> IfcPhysicalOrVirtualEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcPhysicalOrVirtualEnum>(); }
				std::shared_ptr<IfcPhysicalOrVirtualEnum> type_object(new IfcPhysicalOrVirtualEnum() );
				if ( _stricmp( arg.c_str(), ".PHYSICAL.") == 0)
				{
					type_object->m_enum = IfcPhysicalOrVirtualEnum::IfcPhysicalOrVirtualEnumEnum::ENUM_PHYSICAL;
				}
				else if ( _stricmp( arg.c_str(), ".VIRTUAL.") == 0)
				{
					type_object->m_enum = IfcPhysicalOrVirtualEnum::IfcPhysicalOrVirtualEnumEnum::ENUM_VIRTUAL;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcPhysicalOrVirtualEnum::IfcPhysicalOrVirtualEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
