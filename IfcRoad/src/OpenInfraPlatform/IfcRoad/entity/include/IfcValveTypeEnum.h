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
#include "OpenInfraPlatform/IfcRoad/model/shared_ptr.h"
#include "OpenInfraPlatform/IfcRoad/model/IfcRoadObject.h"

namespace OpenInfraPlatform
{
	namespace IfcRoad
	{
		// TYPE IfcValveTypeEnum = ENUMERATION OF	(AIRRELEASE	,ANTIVACUUM	,CHANGEOVER	,CHECK	,COMMISSIONING	,DIVERTING	,DRAWOFFCOCK	,DOUBLECHECK	,DOUBLEREGULATING	,FAUCET	,FLUSHING	,GASCOCK	,GASTAP	,ISOLATING	,MIXING	,PRESSUREREDUCING	,PRESSURERELIEF	,REGULATING	,SAFETYCUTOFF	,STEAMTRAP	,STOPCOCK	,USERDEFINED	,NOTDEFINED);
		class IfcValveTypeEnum : public IfcRoadAbstractEnum, public IfcRoadType
		{
		public:
			enum IfcValveTypeEnumEnum
			{
				ENUM_AIRRELEASE,
				ENUM_ANTIVACUUM,
				ENUM_CHANGEOVER,
				ENUM_CHECK,
				ENUM_COMMISSIONING,
				ENUM_DIVERTING,
				ENUM_DRAWOFFCOCK,
				ENUM_DOUBLECHECK,
				ENUM_DOUBLEREGULATING,
				ENUM_FAUCET,
				ENUM_FLUSHING,
				ENUM_GASCOCK,
				ENUM_GASTAP,
				ENUM_ISOLATING,
				ENUM_MIXING,
				ENUM_PRESSUREREDUCING,
				ENUM_PRESSURERELIEF,
				ENUM_REGULATING,
				ENUM_SAFETYCUTOFF,
				ENUM_STEAMTRAP,
				ENUM_STOPCOCK,
				ENUM_USERDEFINED,
				ENUM_NOTDEFINED
			};

			IfcValveTypeEnum();
			IfcValveTypeEnum( IfcValveTypeEnumEnum e ) { m_enum = e; }
			~IfcValveTypeEnum();
			virtual const char* classname() const { return "IfcValveTypeEnum"; }
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			static shared_ptr<IfcValveTypeEnum> readStepData( std::string& arg );
			IfcValveTypeEnumEnum m_enum;
		};
	} // end namespace IfcRoad
} // end namespace OpenInfraPlatform

