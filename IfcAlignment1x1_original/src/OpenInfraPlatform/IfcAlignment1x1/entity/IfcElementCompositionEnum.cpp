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

#include "IfcElementCompositionEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcElementCompositionEnum::IfcElementCompositionEnum() {}
		IfcElementCompositionEnum::IfcElementCompositionEnum(IfcElementCompositionEnum::IfcElementCompositionEnumEnum value) { m_enum = value; }
		IfcElementCompositionEnum::~IfcElementCompositionEnum() {}
		void IfcElementCompositionEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcElementCompositionEnumEnum::ENUM_COMPLEX)
				{
					stream << ".COMPLEX.";
				}
				else if ( m_enum == IfcElementCompositionEnumEnum::ENUM_ELEMENT)
				{
					stream << ".ELEMENT.";
				}
				else if ( m_enum == IfcElementCompositionEnumEnum::ENUM_PARTIAL)
				{
					stream << ".PARTIAL.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcElementCompositionEnum> IfcElementCompositionEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcElementCompositionEnum>(); }
				std::shared_ptr<IfcElementCompositionEnum> type_object(new IfcElementCompositionEnum() );
				if ( _stricmp( arg.c_str(), ".COMPLEX.") == 0)
				{
					type_object->m_enum = IfcElementCompositionEnum::IfcElementCompositionEnumEnum::ENUM_COMPLEX;
				}
				else if ( _stricmp( arg.c_str(), ".ELEMENT.") == 0)
				{
					type_object->m_enum = IfcElementCompositionEnum::IfcElementCompositionEnumEnum::ENUM_ELEMENT;
				}
				else if ( _stricmp( arg.c_str(), ".PARTIAL.") == 0)
				{
					type_object->m_enum = IfcElementCompositionEnum::IfcElementCompositionEnumEnum::ENUM_PARTIAL;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
