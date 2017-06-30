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

#include "IfcStructuralCurveActivityTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcStructuralCurveActivityTypeEnum::IfcStructuralCurveActivityTypeEnum() {}
		IfcStructuralCurveActivityTypeEnum::IfcStructuralCurveActivityTypeEnum(IfcStructuralCurveActivityTypeEnum::IfcStructuralCurveActivityTypeEnumEnum value) { m_enum = value; }
		IfcStructuralCurveActivityTypeEnum::~IfcStructuralCurveActivityTypeEnum() {}
		void IfcStructuralCurveActivityTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcStructuralCurveActivityTypeEnumEnum::ENUM_CONST)
				{
					stream << ".CONST.";
				}
				else if ( m_enum == IfcStructuralCurveActivityTypeEnumEnum::ENUM_LINEAR)
				{
					stream << ".LINEAR.";
				}
				else if ( m_enum == IfcStructuralCurveActivityTypeEnumEnum::ENUM_POLYGONAL)
				{
					stream << ".POLYGONAL.";
				}
				else if ( m_enum == IfcStructuralCurveActivityTypeEnumEnum::ENUM_EQUIDISTANT)
				{
					stream << ".EQUIDISTANT.";
				}
				else if ( m_enum == IfcStructuralCurveActivityTypeEnumEnum::ENUM_SINUS)
				{
					stream << ".SINUS.";
				}
				else if ( m_enum == IfcStructuralCurveActivityTypeEnumEnum::ENUM_PARABOLA)
				{
					stream << ".PARABOLA.";
				}
				else if ( m_enum == IfcStructuralCurveActivityTypeEnumEnum::ENUM_DISCRETE)
				{
					stream << ".DISCRETE.";
				}
				else if ( m_enum == IfcStructuralCurveActivityTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcStructuralCurveActivityTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcStructuralCurveActivityTypeEnum> IfcStructuralCurveActivityTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcStructuralCurveActivityTypeEnum>(); }
				std::shared_ptr<IfcStructuralCurveActivityTypeEnum> type_object(new IfcStructuralCurveActivityTypeEnum() );
				if ( _stricmp( arg.c_str(), ".CONST.") == 0)
				{
					type_object->m_enum = IfcStructuralCurveActivityTypeEnum::IfcStructuralCurveActivityTypeEnumEnum::ENUM_CONST;
				}
				else if ( _stricmp( arg.c_str(), ".LINEAR.") == 0)
				{
					type_object->m_enum = IfcStructuralCurveActivityTypeEnum::IfcStructuralCurveActivityTypeEnumEnum::ENUM_LINEAR;
				}
				else if ( _stricmp( arg.c_str(), ".POLYGONAL.") == 0)
				{
					type_object->m_enum = IfcStructuralCurveActivityTypeEnum::IfcStructuralCurveActivityTypeEnumEnum::ENUM_POLYGONAL;
				}
				else if ( _stricmp( arg.c_str(), ".EQUIDISTANT.") == 0)
				{
					type_object->m_enum = IfcStructuralCurveActivityTypeEnum::IfcStructuralCurveActivityTypeEnumEnum::ENUM_EQUIDISTANT;
				}
				else if ( _stricmp( arg.c_str(), ".SINUS.") == 0)
				{
					type_object->m_enum = IfcStructuralCurveActivityTypeEnum::IfcStructuralCurveActivityTypeEnumEnum::ENUM_SINUS;
				}
				else if ( _stricmp( arg.c_str(), ".PARABOLA.") == 0)
				{
					type_object->m_enum = IfcStructuralCurveActivityTypeEnum::IfcStructuralCurveActivityTypeEnumEnum::ENUM_PARABOLA;
				}
				else if ( _stricmp( arg.c_str(), ".DISCRETE.") == 0)
				{
					type_object->m_enum = IfcStructuralCurveActivityTypeEnum::IfcStructuralCurveActivityTypeEnumEnum::ENUM_DISCRETE;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcStructuralCurveActivityTypeEnum::IfcStructuralCurveActivityTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcStructuralCurveActivityTypeEnum::IfcStructuralCurveActivityTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
