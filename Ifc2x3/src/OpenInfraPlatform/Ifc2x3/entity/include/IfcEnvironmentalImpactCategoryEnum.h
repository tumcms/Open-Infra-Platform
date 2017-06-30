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
#include "../../model/Ifc2x3Object.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcEnvironmentalImpactCategoryEnum = ENUMERATION OF	(COMBINEDVALUE	,DISPOSAL	,EXTRACTION	,INSTALLATION	,MANUFACTURE	,TRANSPORTATION	,USERDEFINED	,NOTDEFINED);
		class IfcEnvironmentalImpactCategoryEnum : public Ifc2x3AbstractEnum, public Ifc2x3Type
		{
		public:
			enum IfcEnvironmentalImpactCategoryEnumEnum
			{
				ENUM_COMBINEDVALUE,
				ENUM_DISPOSAL,
				ENUM_EXTRACTION,
				ENUM_INSTALLATION,
				ENUM_MANUFACTURE,
				ENUM_TRANSPORTATION,
				ENUM_USERDEFINED,
				ENUM_NOTDEFINED
			};

			IfcEnvironmentalImpactCategoryEnum();
			IfcEnvironmentalImpactCategoryEnum( IfcEnvironmentalImpactCategoryEnumEnum e ) { m_enum = e; }
			~IfcEnvironmentalImpactCategoryEnum();
			virtual const char* classname() const { return "IfcEnvironmentalImpactCategoryEnum"; }
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			static shared_ptr<IfcEnvironmentalImpactCategoryEnum> readStepData( std::string& arg );
			IfcEnvironmentalImpactCategoryEnumEnum m_enum;
		};
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform

