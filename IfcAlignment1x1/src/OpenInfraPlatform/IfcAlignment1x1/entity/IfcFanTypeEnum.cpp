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

#include "IfcFanTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcFanTypeEnum::IfcFanTypeEnum() {}
		IfcFanTypeEnum::IfcFanTypeEnum(IfcFanTypeEnum::IfcFanTypeEnumEnum value) { m_enum = value; }
		IfcFanTypeEnum::~IfcFanTypeEnum() {}
		void IfcFanTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcFanTypeEnumEnum::ENUM_CENTRIFUGALFORWARDCURVED)
				{
					stream << ".CENTRIFUGALFORWARDCURVED.";
				}
				else if ( m_enum == IfcFanTypeEnumEnum::ENUM_CENTRIFUGALRADIAL)
				{
					stream << ".CENTRIFUGALRADIAL.";
				}
				else if ( m_enum == IfcFanTypeEnumEnum::ENUM_CENTRIFUGALBACKWARDINCLINEDCURVED)
				{
					stream << ".CENTRIFUGALBACKWARDINCLINEDCURVED.";
				}
				else if ( m_enum == IfcFanTypeEnumEnum::ENUM_CENTRIFUGALAIRFOIL)
				{
					stream << ".CENTRIFUGALAIRFOIL.";
				}
				else if ( m_enum == IfcFanTypeEnumEnum::ENUM_TUBEAXIAL)
				{
					stream << ".TUBEAXIAL.";
				}
				else if ( m_enum == IfcFanTypeEnumEnum::ENUM_VANEAXIAL)
				{
					stream << ".VANEAXIAL.";
				}
				else if ( m_enum == IfcFanTypeEnumEnum::ENUM_PROPELLORAXIAL)
				{
					stream << ".PROPELLORAXIAL.";
				}
				else if ( m_enum == IfcFanTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcFanTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcFanTypeEnum> IfcFanTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcFanTypeEnum>(); }
				std::shared_ptr<IfcFanTypeEnum> type_object(new IfcFanTypeEnum() );
				if ( _stricmp( arg.c_str(), ".CENTRIFUGALFORWARDCURVED.") == 0)
				{
					type_object->m_enum = IfcFanTypeEnum::IfcFanTypeEnumEnum::ENUM_CENTRIFUGALFORWARDCURVED;
				}
				else if ( _stricmp( arg.c_str(), ".CENTRIFUGALRADIAL.") == 0)
				{
					type_object->m_enum = IfcFanTypeEnum::IfcFanTypeEnumEnum::ENUM_CENTRIFUGALRADIAL;
				}
				else if ( _stricmp( arg.c_str(), ".CENTRIFUGALBACKWARDINCLINEDCURVED.") == 0)
				{
					type_object->m_enum = IfcFanTypeEnum::IfcFanTypeEnumEnum::ENUM_CENTRIFUGALBACKWARDINCLINEDCURVED;
				}
				else if ( _stricmp( arg.c_str(), ".CENTRIFUGALAIRFOIL.") == 0)
				{
					type_object->m_enum = IfcFanTypeEnum::IfcFanTypeEnumEnum::ENUM_CENTRIFUGALAIRFOIL;
				}
				else if ( _stricmp( arg.c_str(), ".TUBEAXIAL.") == 0)
				{
					type_object->m_enum = IfcFanTypeEnum::IfcFanTypeEnumEnum::ENUM_TUBEAXIAL;
				}
				else if ( _stricmp( arg.c_str(), ".VANEAXIAL.") == 0)
				{
					type_object->m_enum = IfcFanTypeEnum::IfcFanTypeEnumEnum::ENUM_VANEAXIAL;
				}
				else if ( _stricmp( arg.c_str(), ".PROPELLORAXIAL.") == 0)
				{
					type_object->m_enum = IfcFanTypeEnum::IfcFanTypeEnumEnum::ENUM_PROPELLORAXIAL;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcFanTypeEnum::IfcFanTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcFanTypeEnum::IfcFanTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
