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
#include "../../model/IfcBridgeObject.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// TYPE IfcRoleEnum = ENUMERATION OF	(SUPPLIER	,MANUFACTURER	,CONTRACTOR	,SUBCONTRACTOR	,ARCHITECT	,STRUCTURALENGINEER	,COSTENGINEER	,CLIENT	,BUILDINGOWNER	,BUILDINGOPERATOR	,MECHANICALENGINEER	,ELECTRICALENGINEER	,PROJECTMANAGER	,FACILITIESMANAGER	,CIVILENGINEER	,COMMISSIONINGENGINEER	,ENGINEER	,OWNER	,CONSULTANT	,CONSTRUCTIONMANAGER	,FIELDCONSTRUCTIONMANAGER	,RESELLER	,USERDEFINED);
		class IfcRoleEnum : public IfcBridgeAbstractEnum, public IfcBridgeType
		{
		public:
			enum IfcRoleEnumEnum
			{
				ENUM_SUPPLIER,
				ENUM_MANUFACTURER,
				ENUM_CONTRACTOR,
				ENUM_SUBCONTRACTOR,
				ENUM_ARCHITECT,
				ENUM_STRUCTURALENGINEER,
				ENUM_COSTENGINEER,
				ENUM_CLIENT,
				ENUM_BUILDINGOWNER,
				ENUM_BUILDINGOPERATOR,
				ENUM_MECHANICALENGINEER,
				ENUM_ELECTRICALENGINEER,
				ENUM_PROJECTMANAGER,
				ENUM_FACILITIESMANAGER,
				ENUM_CIVILENGINEER,
				ENUM_COMMISSIONINGENGINEER,
				ENUM_ENGINEER,
				ENUM_OWNER,
				ENUM_CONSULTANT,
				ENUM_CONSTRUCTIONMANAGER,
				ENUM_FIELDCONSTRUCTIONMANAGER,
				ENUM_RESELLER,
				ENUM_USERDEFINED
			};

			IfcRoleEnum();
			IfcRoleEnum( IfcRoleEnumEnum e ) { m_enum = e; }
			~IfcRoleEnum();
			virtual const char* classname() const { return "IfcRoleEnum"; }
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			static shared_ptr<IfcRoleEnum> readStepData( std::string& arg );
			IfcRoleEnumEnum m_enum;
		};
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform

