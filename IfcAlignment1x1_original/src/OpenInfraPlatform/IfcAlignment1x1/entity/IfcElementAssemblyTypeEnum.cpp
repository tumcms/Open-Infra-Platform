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

#include "IfcElementAssemblyTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcElementAssemblyTypeEnum::IfcElementAssemblyTypeEnum() {}
		IfcElementAssemblyTypeEnum::IfcElementAssemblyTypeEnum(IfcElementAssemblyTypeEnum::IfcElementAssemblyTypeEnumEnum value) { m_enum = value; }
		IfcElementAssemblyTypeEnum::~IfcElementAssemblyTypeEnum() {}
		void IfcElementAssemblyTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcElementAssemblyTypeEnumEnum::ENUM_ACCESSORY_ASSEMBLY)
				{
					stream << ".ACCESSORY_ASSEMBLY.";
				}
				else if ( m_enum == IfcElementAssemblyTypeEnumEnum::ENUM_ARCH)
				{
					stream << ".ARCH.";
				}
				else if ( m_enum == IfcElementAssemblyTypeEnumEnum::ENUM_BEAM_GRID)
				{
					stream << ".BEAM_GRID.";
				}
				else if ( m_enum == IfcElementAssemblyTypeEnumEnum::ENUM_BRACED_FRAME)
				{
					stream << ".BRACED_FRAME.";
				}
				else if ( m_enum == IfcElementAssemblyTypeEnumEnum::ENUM_GIRDER)
				{
					stream << ".GIRDER.";
				}
				else if ( m_enum == IfcElementAssemblyTypeEnumEnum::ENUM_REINFORCEMENT_UNIT)
				{
					stream << ".REINFORCEMENT_UNIT.";
				}
				else if ( m_enum == IfcElementAssemblyTypeEnumEnum::ENUM_RIGID_FRAME)
				{
					stream << ".RIGID_FRAME.";
				}
				else if ( m_enum == IfcElementAssemblyTypeEnumEnum::ENUM_SLAB_FIELD)
				{
					stream << ".SLAB_FIELD.";
				}
				else if ( m_enum == IfcElementAssemblyTypeEnumEnum::ENUM_TRUSS)
				{
					stream << ".TRUSS.";
				}
				else if ( m_enum == IfcElementAssemblyTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcElementAssemblyTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcElementAssemblyTypeEnum> IfcElementAssemblyTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcElementAssemblyTypeEnum>(); }
				std::shared_ptr<IfcElementAssemblyTypeEnum> type_object(new IfcElementAssemblyTypeEnum() );
				if ( _stricmp( arg.c_str(), ".ACCESSORY_ASSEMBLY.") == 0)
				{
					type_object->m_enum = IfcElementAssemblyTypeEnum::IfcElementAssemblyTypeEnumEnum::ENUM_ACCESSORY_ASSEMBLY;
				}
				else if ( _stricmp( arg.c_str(), ".ARCH.") == 0)
				{
					type_object->m_enum = IfcElementAssemblyTypeEnum::IfcElementAssemblyTypeEnumEnum::ENUM_ARCH;
				}
				else if ( _stricmp( arg.c_str(), ".BEAM_GRID.") == 0)
				{
					type_object->m_enum = IfcElementAssemblyTypeEnum::IfcElementAssemblyTypeEnumEnum::ENUM_BEAM_GRID;
				}
				else if ( _stricmp( arg.c_str(), ".BRACED_FRAME.") == 0)
				{
					type_object->m_enum = IfcElementAssemblyTypeEnum::IfcElementAssemblyTypeEnumEnum::ENUM_BRACED_FRAME;
				}
				else if ( _stricmp( arg.c_str(), ".GIRDER.") == 0)
				{
					type_object->m_enum = IfcElementAssemblyTypeEnum::IfcElementAssemblyTypeEnumEnum::ENUM_GIRDER;
				}
				else if ( _stricmp( arg.c_str(), ".REINFORCEMENT_UNIT.") == 0)
				{
					type_object->m_enum = IfcElementAssemblyTypeEnum::IfcElementAssemblyTypeEnumEnum::ENUM_REINFORCEMENT_UNIT;
				}
				else if ( _stricmp( arg.c_str(), ".RIGID_FRAME.") == 0)
				{
					type_object->m_enum = IfcElementAssemblyTypeEnum::IfcElementAssemblyTypeEnumEnum::ENUM_RIGID_FRAME;
				}
				else if ( _stricmp( arg.c_str(), ".SLAB_FIELD.") == 0)
				{
					type_object->m_enum = IfcElementAssemblyTypeEnum::IfcElementAssemblyTypeEnumEnum::ENUM_SLAB_FIELD;
				}
				else if ( _stricmp( arg.c_str(), ".TRUSS.") == 0)
				{
					type_object->m_enum = IfcElementAssemblyTypeEnum::IfcElementAssemblyTypeEnumEnum::ENUM_TRUSS;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcElementAssemblyTypeEnum::IfcElementAssemblyTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcElementAssemblyTypeEnum::IfcElementAssemblyTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
