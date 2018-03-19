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

#include "IfcRoofTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcRoofTypeEnum::IfcRoofTypeEnum() {}
		IfcRoofTypeEnum::IfcRoofTypeEnum(IfcRoofTypeEnum::IfcRoofTypeEnumEnum value) { m_enum = value; }
		IfcRoofTypeEnum::~IfcRoofTypeEnum() {}
		void IfcRoofTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcRoofTypeEnumEnum::ENUM_FLAT_ROOF)
				{
					stream << ".FLAT_ROOF.";
				}
				else if ( m_enum == IfcRoofTypeEnumEnum::ENUM_SHED_ROOF)
				{
					stream << ".SHED_ROOF.";
				}
				else if ( m_enum == IfcRoofTypeEnumEnum::ENUM_GABLE_ROOF)
				{
					stream << ".GABLE_ROOF.";
				}
				else if ( m_enum == IfcRoofTypeEnumEnum::ENUM_HIP_ROOF)
				{
					stream << ".HIP_ROOF.";
				}
				else if ( m_enum == IfcRoofTypeEnumEnum::ENUM_HIPPED_GABLE_ROOF)
				{
					stream << ".HIPPED_GABLE_ROOF.";
				}
				else if ( m_enum == IfcRoofTypeEnumEnum::ENUM_GAMBREL_ROOF)
				{
					stream << ".GAMBREL_ROOF.";
				}
				else if ( m_enum == IfcRoofTypeEnumEnum::ENUM_MANSARD_ROOF)
				{
					stream << ".MANSARD_ROOF.";
				}
				else if ( m_enum == IfcRoofTypeEnumEnum::ENUM_BARREL_ROOF)
				{
					stream << ".BARREL_ROOF.";
				}
				else if ( m_enum == IfcRoofTypeEnumEnum::ENUM_RAINBOW_ROOF)
				{
					stream << ".RAINBOW_ROOF.";
				}
				else if ( m_enum == IfcRoofTypeEnumEnum::ENUM_BUTTERFLY_ROOF)
				{
					stream << ".BUTTERFLY_ROOF.";
				}
				else if ( m_enum == IfcRoofTypeEnumEnum::ENUM_PAVILION_ROOF)
				{
					stream << ".PAVILION_ROOF.";
				}
				else if ( m_enum == IfcRoofTypeEnumEnum::ENUM_DOME_ROOF)
				{
					stream << ".DOME_ROOF.";
				}
				else if ( m_enum == IfcRoofTypeEnumEnum::ENUM_FREEFORM)
				{
					stream << ".FREEFORM.";
				}
				else if ( m_enum == IfcRoofTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcRoofTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcRoofTypeEnum> IfcRoofTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcRoofTypeEnum>(); }
				std::shared_ptr<IfcRoofTypeEnum> type_object(new IfcRoofTypeEnum() );
				if ( _stricmp( arg.c_str(), ".FLAT_ROOF.") == 0)
				{
					type_object->m_enum = IfcRoofTypeEnum::IfcRoofTypeEnumEnum::ENUM_FLAT_ROOF;
				}
				else if ( _stricmp( arg.c_str(), ".SHED_ROOF.") == 0)
				{
					type_object->m_enum = IfcRoofTypeEnum::IfcRoofTypeEnumEnum::ENUM_SHED_ROOF;
				}
				else if ( _stricmp( arg.c_str(), ".GABLE_ROOF.") == 0)
				{
					type_object->m_enum = IfcRoofTypeEnum::IfcRoofTypeEnumEnum::ENUM_GABLE_ROOF;
				}
				else if ( _stricmp( arg.c_str(), ".HIP_ROOF.") == 0)
				{
					type_object->m_enum = IfcRoofTypeEnum::IfcRoofTypeEnumEnum::ENUM_HIP_ROOF;
				}
				else if ( _stricmp( arg.c_str(), ".HIPPED_GABLE_ROOF.") == 0)
				{
					type_object->m_enum = IfcRoofTypeEnum::IfcRoofTypeEnumEnum::ENUM_HIPPED_GABLE_ROOF;
				}
				else if ( _stricmp( arg.c_str(), ".GAMBREL_ROOF.") == 0)
				{
					type_object->m_enum = IfcRoofTypeEnum::IfcRoofTypeEnumEnum::ENUM_GAMBREL_ROOF;
				}
				else if ( _stricmp( arg.c_str(), ".MANSARD_ROOF.") == 0)
				{
					type_object->m_enum = IfcRoofTypeEnum::IfcRoofTypeEnumEnum::ENUM_MANSARD_ROOF;
				}
				else if ( _stricmp( arg.c_str(), ".BARREL_ROOF.") == 0)
				{
					type_object->m_enum = IfcRoofTypeEnum::IfcRoofTypeEnumEnum::ENUM_BARREL_ROOF;
				}
				else if ( _stricmp( arg.c_str(), ".RAINBOW_ROOF.") == 0)
				{
					type_object->m_enum = IfcRoofTypeEnum::IfcRoofTypeEnumEnum::ENUM_RAINBOW_ROOF;
				}
				else if ( _stricmp( arg.c_str(), ".BUTTERFLY_ROOF.") == 0)
				{
					type_object->m_enum = IfcRoofTypeEnum::IfcRoofTypeEnumEnum::ENUM_BUTTERFLY_ROOF;
				}
				else if ( _stricmp( arg.c_str(), ".PAVILION_ROOF.") == 0)
				{
					type_object->m_enum = IfcRoofTypeEnum::IfcRoofTypeEnumEnum::ENUM_PAVILION_ROOF;
				}
				else if ( _stricmp( arg.c_str(), ".DOME_ROOF.") == 0)
				{
					type_object->m_enum = IfcRoofTypeEnum::IfcRoofTypeEnumEnum::ENUM_DOME_ROOF;
				}
				else if ( _stricmp( arg.c_str(), ".FREEFORM.") == 0)
				{
					type_object->m_enum = IfcRoofTypeEnum::IfcRoofTypeEnumEnum::ENUM_FREEFORM;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcRoofTypeEnum::IfcRoofTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcRoofTypeEnum::IfcRoofTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
