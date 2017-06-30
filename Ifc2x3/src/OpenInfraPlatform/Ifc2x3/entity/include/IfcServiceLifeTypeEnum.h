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
		// TYPE IfcServiceLifeTypeEnum = ENUMERATION OF	(ACTUALSERVICELIFE	,EXPECTEDSERVICELIFE	,OPTIMISTICREFERENCESERVICELIFE	,PESSIMISTICREFERENCESERVICELIFE	,REFERENCESERVICELIFE);
		class IfcServiceLifeTypeEnum : public Ifc2x3AbstractEnum, public Ifc2x3Type
		{
		public:
			enum IfcServiceLifeTypeEnumEnum
			{
				ENUM_ACTUALSERVICELIFE,
				ENUM_EXPECTEDSERVICELIFE,
				ENUM_OPTIMISTICREFERENCESERVICELIFE,
				ENUM_PESSIMISTICREFERENCESERVICELIFE,
				ENUM_REFERENCESERVICELIFE
			};

			IfcServiceLifeTypeEnum();
			IfcServiceLifeTypeEnum( IfcServiceLifeTypeEnumEnum e ) { m_enum = e; }
			~IfcServiceLifeTypeEnum();
			virtual const char* classname() const { return "IfcServiceLifeTypeEnum"; }
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			static shared_ptr<IfcServiceLifeTypeEnum> readStepData( std::string& arg );
			IfcServiceLifeTypeEnumEnum m_enum;
		};
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform

