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

#include "IfcVoidingFeatureTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcVoidingFeatureTypeEnum::IfcVoidingFeatureTypeEnum() {}
		IfcVoidingFeatureTypeEnum::IfcVoidingFeatureTypeEnum(IfcVoidingFeatureTypeEnum::IfcVoidingFeatureTypeEnumEnum value) { m_enum = value; }
		IfcVoidingFeatureTypeEnum::~IfcVoidingFeatureTypeEnum() {}
		void IfcVoidingFeatureTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcVoidingFeatureTypeEnumEnum::ENUM_CUTOUT)
				{
					stream << ".CUTOUT.";
				}
				else if ( m_enum == IfcVoidingFeatureTypeEnumEnum::ENUM_NOTCH)
				{
					stream << ".NOTCH.";
				}
				else if ( m_enum == IfcVoidingFeatureTypeEnumEnum::ENUM_HOLE)
				{
					stream << ".HOLE.";
				}
				else if ( m_enum == IfcVoidingFeatureTypeEnumEnum::ENUM_MITER)
				{
					stream << ".MITER.";
				}
				else if ( m_enum == IfcVoidingFeatureTypeEnumEnum::ENUM_CHAMFER)
				{
					stream << ".CHAMFER.";
				}
				else if ( m_enum == IfcVoidingFeatureTypeEnumEnum::ENUM_EDGE)
				{
					stream << ".EDGE.";
				}
				else if ( m_enum == IfcVoidingFeatureTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcVoidingFeatureTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcVoidingFeatureTypeEnum> IfcVoidingFeatureTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcVoidingFeatureTypeEnum>(); }
				std::shared_ptr<IfcVoidingFeatureTypeEnum> type_object(new IfcVoidingFeatureTypeEnum() );
				if ( _stricmp( arg.c_str(), ".CUTOUT.") == 0)
				{
					type_object->m_enum = IfcVoidingFeatureTypeEnum::IfcVoidingFeatureTypeEnumEnum::ENUM_CUTOUT;
				}
				else if ( _stricmp( arg.c_str(), ".NOTCH.") == 0)
				{
					type_object->m_enum = IfcVoidingFeatureTypeEnum::IfcVoidingFeatureTypeEnumEnum::ENUM_NOTCH;
				}
				else if ( _stricmp( arg.c_str(), ".HOLE.") == 0)
				{
					type_object->m_enum = IfcVoidingFeatureTypeEnum::IfcVoidingFeatureTypeEnumEnum::ENUM_HOLE;
				}
				else if ( _stricmp( arg.c_str(), ".MITER.") == 0)
				{
					type_object->m_enum = IfcVoidingFeatureTypeEnum::IfcVoidingFeatureTypeEnumEnum::ENUM_MITER;
				}
				else if ( _stricmp( arg.c_str(), ".CHAMFER.") == 0)
				{
					type_object->m_enum = IfcVoidingFeatureTypeEnum::IfcVoidingFeatureTypeEnumEnum::ENUM_CHAMFER;
				}
				else if ( _stricmp( arg.c_str(), ".EDGE.") == 0)
				{
					type_object->m_enum = IfcVoidingFeatureTypeEnum::IfcVoidingFeatureTypeEnumEnum::ENUM_EDGE;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcVoidingFeatureTypeEnum::IfcVoidingFeatureTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcVoidingFeatureTypeEnum::IfcVoidingFeatureTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
