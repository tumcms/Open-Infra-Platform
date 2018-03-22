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

#include "IfcGeometricProjectionEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcGeometricProjectionEnum::IfcGeometricProjectionEnum() {}
		IfcGeometricProjectionEnum::IfcGeometricProjectionEnum(IfcGeometricProjectionEnum::IfcGeometricProjectionEnumEnum value) { m_enum = value; }
		IfcGeometricProjectionEnum::~IfcGeometricProjectionEnum() {}
		void IfcGeometricProjectionEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcGeometricProjectionEnumEnum::ENUM_GRAPH_VIEW)
				{
					stream << ".GRAPH_VIEW.";
				}
				else if ( m_enum == IfcGeometricProjectionEnumEnum::ENUM_SKETCH_VIEW)
				{
					stream << ".SKETCH_VIEW.";
				}
				else if ( m_enum == IfcGeometricProjectionEnumEnum::ENUM_MODEL_VIEW)
				{
					stream << ".MODEL_VIEW.";
				}
				else if ( m_enum == IfcGeometricProjectionEnumEnum::ENUM_PLAN_VIEW)
				{
					stream << ".PLAN_VIEW.";
				}
				else if ( m_enum == IfcGeometricProjectionEnumEnum::ENUM_REFLECTED_PLAN_VIEW)
				{
					stream << ".REFLECTED_PLAN_VIEW.";
				}
				else if ( m_enum == IfcGeometricProjectionEnumEnum::ENUM_SECTION_VIEW)
				{
					stream << ".SECTION_VIEW.";
				}
				else if ( m_enum == IfcGeometricProjectionEnumEnum::ENUM_ELEVATION_VIEW)
				{
					stream << ".ELEVATION_VIEW.";
				}
				else if ( m_enum == IfcGeometricProjectionEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcGeometricProjectionEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcGeometricProjectionEnum> IfcGeometricProjectionEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcGeometricProjectionEnum>(); }
				std::shared_ptr<IfcGeometricProjectionEnum> type_object(new IfcGeometricProjectionEnum() );
				if ( _stricmp( arg.c_str(), ".GRAPH_VIEW.") == 0)
				{
					type_object->m_enum = IfcGeometricProjectionEnum::IfcGeometricProjectionEnumEnum::ENUM_GRAPH_VIEW;
				}
				else if ( _stricmp( arg.c_str(), ".SKETCH_VIEW.") == 0)
				{
					type_object->m_enum = IfcGeometricProjectionEnum::IfcGeometricProjectionEnumEnum::ENUM_SKETCH_VIEW;
				}
				else if ( _stricmp( arg.c_str(), ".MODEL_VIEW.") == 0)
				{
					type_object->m_enum = IfcGeometricProjectionEnum::IfcGeometricProjectionEnumEnum::ENUM_MODEL_VIEW;
				}
				else if ( _stricmp( arg.c_str(), ".PLAN_VIEW.") == 0)
				{
					type_object->m_enum = IfcGeometricProjectionEnum::IfcGeometricProjectionEnumEnum::ENUM_PLAN_VIEW;
				}
				else if ( _stricmp( arg.c_str(), ".REFLECTED_PLAN_VIEW.") == 0)
				{
					type_object->m_enum = IfcGeometricProjectionEnum::IfcGeometricProjectionEnumEnum::ENUM_REFLECTED_PLAN_VIEW;
				}
				else if ( _stricmp( arg.c_str(), ".SECTION_VIEW.") == 0)
				{
					type_object->m_enum = IfcGeometricProjectionEnum::IfcGeometricProjectionEnumEnum::ENUM_SECTION_VIEW;
				}
				else if ( _stricmp( arg.c_str(), ".ELEVATION_VIEW.") == 0)
				{
					type_object->m_enum = IfcGeometricProjectionEnum::IfcGeometricProjectionEnumEnum::ENUM_ELEVATION_VIEW;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcGeometricProjectionEnum::IfcGeometricProjectionEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcGeometricProjectionEnum::IfcGeometricProjectionEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
