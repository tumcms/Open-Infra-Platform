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

#include "IfcKnotType.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcKnotType::IfcKnotType() {}
		IfcKnotType::IfcKnotType(IfcKnotType::IfcKnotTypeEnum value) { m_enum = value; }
		IfcKnotType::~IfcKnotType() {}
		void IfcKnotType::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcKnotTypeEnum::ENUM_UNIFORM_KNOTS)
				{
					stream << ".UNIFORM_KNOTS.";
				}
				else if ( m_enum == IfcKnotTypeEnum::ENUM_QUASI_UNIFORM_KNOTS)
				{
					stream << ".QUASI_UNIFORM_KNOTS.";
				}
				else if ( m_enum == IfcKnotTypeEnum::ENUM_PIECEWISE_BEZIER_KNOTS)
				{
					stream << ".PIECEWISE_BEZIER_KNOTS.";
				}
				else if ( m_enum == IfcKnotTypeEnum::ENUM_UNSPECIFIED)
				{
					stream << ".UNSPECIFIED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcKnotType> IfcKnotType::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcKnotType>(); }
				std::shared_ptr<IfcKnotType> type_object(new IfcKnotType() );
				if ( _stricmp( arg.c_str(), ".UNIFORM_KNOTS.") == 0)
				{
					type_object->m_enum = IfcKnotType::IfcKnotTypeEnum::ENUM_UNIFORM_KNOTS;
				}
				else if ( _stricmp( arg.c_str(), ".QUASI_UNIFORM_KNOTS.") == 0)
				{
					type_object->m_enum = IfcKnotType::IfcKnotTypeEnum::ENUM_QUASI_UNIFORM_KNOTS;
				}
				else if ( _stricmp( arg.c_str(), ".PIECEWISE_BEZIER_KNOTS.") == 0)
				{
					type_object->m_enum = IfcKnotType::IfcKnotTypeEnum::ENUM_PIECEWISE_BEZIER_KNOTS;
				}
				else if ( _stricmp( arg.c_str(), ".UNSPECIFIED.") == 0)
				{
					type_object->m_enum = IfcKnotType::IfcKnotTypeEnum::ENUM_UNSPECIFIED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
