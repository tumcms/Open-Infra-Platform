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
		// TYPE IfcServiceLifeFactorTypeEnum = ENUMERATION OF	(A_QUALITYOFCOMPONENTS	,B_DESIGNLEVEL	,C_WORKEXECUTIONLEVEL	,D_INDOORENVIRONMENT	,E_OUTDOORENVIRONMENT	,F_INUSECONDITIONS	,G_MAINTENANCELEVEL	,USERDEFINED	,NOTDEFINED);
		class IfcServiceLifeFactorTypeEnum : public Ifc2x3AbstractEnum, public Ifc2x3Type
		{
		public:
			enum IfcServiceLifeFactorTypeEnumEnum
			{
				ENUM_A_QUALITYOFCOMPONENTS,
				ENUM_B_DESIGNLEVEL,
				ENUM_C_WORKEXECUTIONLEVEL,
				ENUM_D_INDOORENVIRONMENT,
				ENUM_E_OUTDOORENVIRONMENT,
				ENUM_F_INUSECONDITIONS,
				ENUM_G_MAINTENANCELEVEL,
				ENUM_USERDEFINED,
				ENUM_NOTDEFINED
			};

			IfcServiceLifeFactorTypeEnum();
			IfcServiceLifeFactorTypeEnum( IfcServiceLifeFactorTypeEnumEnum e ) { m_enum = e; }
			~IfcServiceLifeFactorTypeEnum();
			virtual const char* classname() const { return "IfcServiceLifeFactorTypeEnum"; }
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			static shared_ptr<IfcServiceLifeFactorTypeEnum> readStepData( std::string& arg );
			IfcServiceLifeFactorTypeEnumEnum m_enum;
		};
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform

