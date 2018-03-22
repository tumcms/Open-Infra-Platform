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

#pragma once

#include <vector>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include "OpenInfraPlatform/IfcAlignment1x1/model/Object.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		// TYPE IfcBSplineSurfaceForm = ENUMERATION OF(PLANE_SURFCYLINDRICAL_SURFCONICAL_SURFSPHERICAL_SURFTOROIDAL_SURFSURF_OF_REVOLUTIONRULED_SURFGENERALISED_CONEQUADRIC_SURFSURF_OF_LINEAR_EXTRUSIONUNSPECIFIED;
		class IfcBSplineSurfaceForm : public IfcAlignment1x1Type, public IfcAlignment1x1AbstractEnum
		{
		public:
			enum IfcBSplineSurfaceFormEnum
			{
				 ENUM_PLANE_SURF,
				 ENUM_CYLINDRICAL_SURF,
				 ENUM_CONICAL_SURF,
				 ENUM_SPHERICAL_SURF,
				 ENUM_TOROIDAL_SURF,
				 ENUM_SURF_OF_REVOLUTION,
				 ENUM_RULED_SURF,
				 ENUM_GENERALISED_CONE,
				 ENUM_QUADRIC_SURF,
				 ENUM_SURF_OF_LINEAR_EXTRUSION,
				 ENUM_UNSPECIFIED
			};

			IfcBSplineSurfaceForm();
			IfcBSplineSurfaceForm(IfcBSplineSurfaceFormEnum value);
			virtual ~IfcBSplineSurfaceForm();
			virtual const char* classname() const { return "IfcBSplineSurfaceForm"; }
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			static std::shared_ptr<IfcBSplineSurfaceForm> readStepData(const std::string& arg);
			IfcBSplineSurfaceFormEnum m_enum;
		}; // end class IfcBSplineSurfaceForm
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
