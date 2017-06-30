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

#include "IfcReflectanceMethodEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcReflectanceMethodEnum::IfcReflectanceMethodEnum() {}
		IfcReflectanceMethodEnum::IfcReflectanceMethodEnum(IfcReflectanceMethodEnum::IfcReflectanceMethodEnumEnum value) { m_enum = value; }
		IfcReflectanceMethodEnum::~IfcReflectanceMethodEnum() {}
		void IfcReflectanceMethodEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcReflectanceMethodEnumEnum::ENUM_BLINN)
				{
					stream << ".BLINN.";
				}
				else if ( m_enum == IfcReflectanceMethodEnumEnum::ENUM_FLAT)
				{
					stream << ".FLAT.";
				}
				else if ( m_enum == IfcReflectanceMethodEnumEnum::ENUM_GLASS)
				{
					stream << ".GLASS.";
				}
				else if ( m_enum == IfcReflectanceMethodEnumEnum::ENUM_MATT)
				{
					stream << ".MATT.";
				}
				else if ( m_enum == IfcReflectanceMethodEnumEnum::ENUM_METAL)
				{
					stream << ".METAL.";
				}
				else if ( m_enum == IfcReflectanceMethodEnumEnum::ENUM_MIRROR)
				{
					stream << ".MIRROR.";
				}
				else if ( m_enum == IfcReflectanceMethodEnumEnum::ENUM_PHONG)
				{
					stream << ".PHONG.";
				}
				else if ( m_enum == IfcReflectanceMethodEnumEnum::ENUM_PLASTIC)
				{
					stream << ".PLASTIC.";
				}
				else if ( m_enum == IfcReflectanceMethodEnumEnum::ENUM_STRAUSS)
				{
					stream << ".STRAUSS.";
				}
				else if ( m_enum == IfcReflectanceMethodEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcReflectanceMethodEnum> IfcReflectanceMethodEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcReflectanceMethodEnum>(); }
				std::shared_ptr<IfcReflectanceMethodEnum> type_object(new IfcReflectanceMethodEnum() );
				if ( _stricmp( arg.c_str(), ".BLINN.") == 0)
				{
					type_object->m_enum = IfcReflectanceMethodEnum::IfcReflectanceMethodEnumEnum::ENUM_BLINN;
				}
				else if ( _stricmp( arg.c_str(), ".FLAT.") == 0)
				{
					type_object->m_enum = IfcReflectanceMethodEnum::IfcReflectanceMethodEnumEnum::ENUM_FLAT;
				}
				else if ( _stricmp( arg.c_str(), ".GLASS.") == 0)
				{
					type_object->m_enum = IfcReflectanceMethodEnum::IfcReflectanceMethodEnumEnum::ENUM_GLASS;
				}
				else if ( _stricmp( arg.c_str(), ".MATT.") == 0)
				{
					type_object->m_enum = IfcReflectanceMethodEnum::IfcReflectanceMethodEnumEnum::ENUM_MATT;
				}
				else if ( _stricmp( arg.c_str(), ".METAL.") == 0)
				{
					type_object->m_enum = IfcReflectanceMethodEnum::IfcReflectanceMethodEnumEnum::ENUM_METAL;
				}
				else if ( _stricmp( arg.c_str(), ".MIRROR.") == 0)
				{
					type_object->m_enum = IfcReflectanceMethodEnum::IfcReflectanceMethodEnumEnum::ENUM_MIRROR;
				}
				else if ( _stricmp( arg.c_str(), ".PHONG.") == 0)
				{
					type_object->m_enum = IfcReflectanceMethodEnum::IfcReflectanceMethodEnumEnum::ENUM_PHONG;
				}
				else if ( _stricmp( arg.c_str(), ".PLASTIC.") == 0)
				{
					type_object->m_enum = IfcReflectanceMethodEnum::IfcReflectanceMethodEnumEnum::ENUM_PLASTIC;
				}
				else if ( _stricmp( arg.c_str(), ".STRAUSS.") == 0)
				{
					type_object->m_enum = IfcReflectanceMethodEnum::IfcReflectanceMethodEnumEnum::ENUM_STRAUSS;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcReflectanceMethodEnum::IfcReflectanceMethodEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
