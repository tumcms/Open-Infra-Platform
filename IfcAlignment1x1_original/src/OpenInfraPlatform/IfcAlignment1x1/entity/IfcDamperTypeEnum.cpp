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

#include "IfcDamperTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcDamperTypeEnum::IfcDamperTypeEnum() {}
		IfcDamperTypeEnum::IfcDamperTypeEnum(IfcDamperTypeEnum::IfcDamperTypeEnumEnum value) { m_enum = value; }
		IfcDamperTypeEnum::~IfcDamperTypeEnum() {}
		void IfcDamperTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcDamperTypeEnumEnum::ENUM_BACKDRAFTDAMPER)
				{
					stream << ".BACKDRAFTDAMPER.";
				}
				else if ( m_enum == IfcDamperTypeEnumEnum::ENUM_BALANCINGDAMPER)
				{
					stream << ".BALANCINGDAMPER.";
				}
				else if ( m_enum == IfcDamperTypeEnumEnum::ENUM_BLASTDAMPER)
				{
					stream << ".BLASTDAMPER.";
				}
				else if ( m_enum == IfcDamperTypeEnumEnum::ENUM_CONTROLDAMPER)
				{
					stream << ".CONTROLDAMPER.";
				}
				else if ( m_enum == IfcDamperTypeEnumEnum::ENUM_FIREDAMPER)
				{
					stream << ".FIREDAMPER.";
				}
				else if ( m_enum == IfcDamperTypeEnumEnum::ENUM_FIRESMOKEDAMPER)
				{
					stream << ".FIRESMOKEDAMPER.";
				}
				else if ( m_enum == IfcDamperTypeEnumEnum::ENUM_FUMEHOODEXHAUST)
				{
					stream << ".FUMEHOODEXHAUST.";
				}
				else if ( m_enum == IfcDamperTypeEnumEnum::ENUM_GRAVITYDAMPER)
				{
					stream << ".GRAVITYDAMPER.";
				}
				else if ( m_enum == IfcDamperTypeEnumEnum::ENUM_GRAVITYRELIEFDAMPER)
				{
					stream << ".GRAVITYRELIEFDAMPER.";
				}
				else if ( m_enum == IfcDamperTypeEnumEnum::ENUM_RELIEFDAMPER)
				{
					stream << ".RELIEFDAMPER.";
				}
				else if ( m_enum == IfcDamperTypeEnumEnum::ENUM_SMOKEDAMPER)
				{
					stream << ".SMOKEDAMPER.";
				}
				else if ( m_enum == IfcDamperTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcDamperTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcDamperTypeEnum> IfcDamperTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcDamperTypeEnum>(); }
				std::shared_ptr<IfcDamperTypeEnum> type_object(new IfcDamperTypeEnum() );
				if ( _stricmp( arg.c_str(), ".BACKDRAFTDAMPER.") == 0)
				{
					type_object->m_enum = IfcDamperTypeEnum::IfcDamperTypeEnumEnum::ENUM_BACKDRAFTDAMPER;
				}
				else if ( _stricmp( arg.c_str(), ".BALANCINGDAMPER.") == 0)
				{
					type_object->m_enum = IfcDamperTypeEnum::IfcDamperTypeEnumEnum::ENUM_BALANCINGDAMPER;
				}
				else if ( _stricmp( arg.c_str(), ".BLASTDAMPER.") == 0)
				{
					type_object->m_enum = IfcDamperTypeEnum::IfcDamperTypeEnumEnum::ENUM_BLASTDAMPER;
				}
				else if ( _stricmp( arg.c_str(), ".CONTROLDAMPER.") == 0)
				{
					type_object->m_enum = IfcDamperTypeEnum::IfcDamperTypeEnumEnum::ENUM_CONTROLDAMPER;
				}
				else if ( _stricmp( arg.c_str(), ".FIREDAMPER.") == 0)
				{
					type_object->m_enum = IfcDamperTypeEnum::IfcDamperTypeEnumEnum::ENUM_FIREDAMPER;
				}
				else if ( _stricmp( arg.c_str(), ".FIRESMOKEDAMPER.") == 0)
				{
					type_object->m_enum = IfcDamperTypeEnum::IfcDamperTypeEnumEnum::ENUM_FIRESMOKEDAMPER;
				}
				else if ( _stricmp( arg.c_str(), ".FUMEHOODEXHAUST.") == 0)
				{
					type_object->m_enum = IfcDamperTypeEnum::IfcDamperTypeEnumEnum::ENUM_FUMEHOODEXHAUST;
				}
				else if ( _stricmp( arg.c_str(), ".GRAVITYDAMPER.") == 0)
				{
					type_object->m_enum = IfcDamperTypeEnum::IfcDamperTypeEnumEnum::ENUM_GRAVITYDAMPER;
				}
				else if ( _stricmp( arg.c_str(), ".GRAVITYRELIEFDAMPER.") == 0)
				{
					type_object->m_enum = IfcDamperTypeEnum::IfcDamperTypeEnumEnum::ENUM_GRAVITYRELIEFDAMPER;
				}
				else if ( _stricmp( arg.c_str(), ".RELIEFDAMPER.") == 0)
				{
					type_object->m_enum = IfcDamperTypeEnum::IfcDamperTypeEnumEnum::ENUM_RELIEFDAMPER;
				}
				else if ( _stricmp( arg.c_str(), ".SMOKEDAMPER.") == 0)
				{
					type_object->m_enum = IfcDamperTypeEnum::IfcDamperTypeEnumEnum::ENUM_SMOKEDAMPER;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcDamperTypeEnum::IfcDamperTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcDamperTypeEnum::IfcDamperTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
