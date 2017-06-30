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
		// TYPE IfcControllerTypeEnum = ENUMERATION OF	(FLOATING	,PROPORTIONAL	,PROPORTIONALINTEGRAL	,PROPORTIONALINTEGRALDERIVATIVE	,TIMEDTWOPOSITION	,TWOPOSITION	,USERDEFINED	,NOTDEFINED);
		class IfcControllerTypeEnum : public Ifc2x3AbstractEnum, public Ifc2x3Type
		{
		public:
			enum IfcControllerTypeEnumEnum
			{
				ENUM_FLOATING,
				ENUM_PROPORTIONAL,
				ENUM_PROPORTIONALINTEGRAL,
				ENUM_PROPORTIONALINTEGRALDERIVATIVE,
				ENUM_TIMEDTWOPOSITION,
				ENUM_TWOPOSITION,
				ENUM_USERDEFINED,
				ENUM_NOTDEFINED
			};

			IfcControllerTypeEnum();
			IfcControllerTypeEnum( IfcControllerTypeEnumEnum e ) { m_enum = e; }
			~IfcControllerTypeEnum();
			virtual const char* classname() const { return "IfcControllerTypeEnum"; }
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			static shared_ptr<IfcControllerTypeEnum> readStepData( std::string& arg );
			IfcControllerTypeEnumEnum m_enum;
		};
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform

