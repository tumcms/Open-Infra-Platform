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
#include <sstream>
#include <string>
#include "../../model/shared_ptr.h"
#include "../../model/IfcTunnelObject.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		// TYPE IfcBSplineSurfaceForm = ENUMERATION OF	(PLANE_SURF	,CYLINDRICAL_SURF	,CONICAL_SURF	,SPHERICAL_SURF	,TOROIDAL_SURF	,SURF_OF_REVOLUTION	,RULED_SURF	,GENERALISED_CONE	,QUADRIC_SURF	,SURF_OF_LINEAR_EXTRUSION	,UNSPECIFIED);
		class IfcBSplineSurfaceForm : public IfcTunnelAbstractEnum, public IfcTunnelType
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
			IfcBSplineSurfaceForm( IfcBSplineSurfaceFormEnum e ) { m_enum = e; }
			~IfcBSplineSurfaceForm();
			virtual const char* classname() const { return "IfcBSplineSurfaceForm"; }
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			static shared_ptr<IfcBSplineSurfaceForm> readStepData( std::string& arg );
			IfcBSplineSurfaceFormEnum m_enum;
		};
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform

