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

#include "IfcBSplineSurfaceForm.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcBSplineSurfaceForm::IfcBSplineSurfaceForm() {}
		IfcBSplineSurfaceForm::IfcBSplineSurfaceForm(IfcBSplineSurfaceForm::IfcBSplineSurfaceFormEnum value) { m_enum = value; }
		IfcBSplineSurfaceForm::~IfcBSplineSurfaceForm() {}
		void IfcBSplineSurfaceForm::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcBSplineSurfaceFormEnum::ENUM_PLANE_SURF)
				{
					stream << ".PLANE_SURF.";
				}
				else if ( m_enum == IfcBSplineSurfaceFormEnum::ENUM_CYLINDRICAL_SURF)
				{
					stream << ".CYLINDRICAL_SURF.";
				}
				else if ( m_enum == IfcBSplineSurfaceFormEnum::ENUM_CONICAL_SURF)
				{
					stream << ".CONICAL_SURF.";
				}
				else if ( m_enum == IfcBSplineSurfaceFormEnum::ENUM_SPHERICAL_SURF)
				{
					stream << ".SPHERICAL_SURF.";
				}
				else if ( m_enum == IfcBSplineSurfaceFormEnum::ENUM_TOROIDAL_SURF)
				{
					stream << ".TOROIDAL_SURF.";
				}
				else if ( m_enum == IfcBSplineSurfaceFormEnum::ENUM_SURF_OF_REVOLUTION)
				{
					stream << ".SURF_OF_REVOLUTION.";
				}
				else if ( m_enum == IfcBSplineSurfaceFormEnum::ENUM_RULED_SURF)
				{
					stream << ".RULED_SURF.";
				}
				else if ( m_enum == IfcBSplineSurfaceFormEnum::ENUM_GENERALISED_CONE)
				{
					stream << ".GENERALISED_CONE.";
				}
				else if ( m_enum == IfcBSplineSurfaceFormEnum::ENUM_QUADRIC_SURF)
				{
					stream << ".QUADRIC_SURF.";
				}
				else if ( m_enum == IfcBSplineSurfaceFormEnum::ENUM_SURF_OF_LINEAR_EXTRUSION)
				{
					stream << ".SURF_OF_LINEAR_EXTRUSION.";
				}
				else if ( m_enum == IfcBSplineSurfaceFormEnum::ENUM_UNSPECIFIED)
				{
					stream << ".UNSPECIFIED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcBSplineSurfaceForm> IfcBSplineSurfaceForm::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcBSplineSurfaceForm>(); }
				std::shared_ptr<IfcBSplineSurfaceForm> type_object(new IfcBSplineSurfaceForm() );
				if ( _stricmp( arg.c_str(), ".PLANE_SURF.") == 0)
				{
					type_object->m_enum = IfcBSplineSurfaceForm::IfcBSplineSurfaceFormEnum::ENUM_PLANE_SURF;
				}
				else if ( _stricmp( arg.c_str(), ".CYLINDRICAL_SURF.") == 0)
				{
					type_object->m_enum = IfcBSplineSurfaceForm::IfcBSplineSurfaceFormEnum::ENUM_CYLINDRICAL_SURF;
				}
				else if ( _stricmp( arg.c_str(), ".CONICAL_SURF.") == 0)
				{
					type_object->m_enum = IfcBSplineSurfaceForm::IfcBSplineSurfaceFormEnum::ENUM_CONICAL_SURF;
				}
				else if ( _stricmp( arg.c_str(), ".SPHERICAL_SURF.") == 0)
				{
					type_object->m_enum = IfcBSplineSurfaceForm::IfcBSplineSurfaceFormEnum::ENUM_SPHERICAL_SURF;
				}
				else if ( _stricmp( arg.c_str(), ".TOROIDAL_SURF.") == 0)
				{
					type_object->m_enum = IfcBSplineSurfaceForm::IfcBSplineSurfaceFormEnum::ENUM_TOROIDAL_SURF;
				}
				else if ( _stricmp( arg.c_str(), ".SURF_OF_REVOLUTION.") == 0)
				{
					type_object->m_enum = IfcBSplineSurfaceForm::IfcBSplineSurfaceFormEnum::ENUM_SURF_OF_REVOLUTION;
				}
				else if ( _stricmp( arg.c_str(), ".RULED_SURF.") == 0)
				{
					type_object->m_enum = IfcBSplineSurfaceForm::IfcBSplineSurfaceFormEnum::ENUM_RULED_SURF;
				}
				else if ( _stricmp( arg.c_str(), ".GENERALISED_CONE.") == 0)
				{
					type_object->m_enum = IfcBSplineSurfaceForm::IfcBSplineSurfaceFormEnum::ENUM_GENERALISED_CONE;
				}
				else if ( _stricmp( arg.c_str(), ".QUADRIC_SURF.") == 0)
				{
					type_object->m_enum = IfcBSplineSurfaceForm::IfcBSplineSurfaceFormEnum::ENUM_QUADRIC_SURF;
				}
				else if ( _stricmp( arg.c_str(), ".SURF_OF_LINEAR_EXTRUSION.") == 0)
				{
					type_object->m_enum = IfcBSplineSurfaceForm::IfcBSplineSurfaceFormEnum::ENUM_SURF_OF_LINEAR_EXTRUSION;
				}
				else if ( _stricmp( arg.c_str(), ".UNSPECIFIED.") == 0)
				{
					type_object->m_enum = IfcBSplineSurfaceForm::IfcBSplineSurfaceFormEnum::ENUM_UNSPECIFIED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
