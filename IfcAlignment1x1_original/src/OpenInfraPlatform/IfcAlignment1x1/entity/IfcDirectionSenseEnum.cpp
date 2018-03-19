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

#include "IfcDirectionSenseEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcDirectionSenseEnum::IfcDirectionSenseEnum() {}
		IfcDirectionSenseEnum::IfcDirectionSenseEnum(IfcDirectionSenseEnum::IfcDirectionSenseEnumEnum value) { m_enum = value; }
		IfcDirectionSenseEnum::~IfcDirectionSenseEnum() {}
		void IfcDirectionSenseEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcDirectionSenseEnumEnum::ENUM_POSITIVE)
				{
					stream << ".POSITIVE.";
				}
				else if ( m_enum == IfcDirectionSenseEnumEnum::ENUM_NEGATIVE)
				{
					stream << ".NEGATIVE.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcDirectionSenseEnum> IfcDirectionSenseEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcDirectionSenseEnum>(); }
				std::shared_ptr<IfcDirectionSenseEnum> type_object(new IfcDirectionSenseEnum() );
				if ( _stricmp( arg.c_str(), ".POSITIVE.") == 0)
				{
					type_object->m_enum = IfcDirectionSenseEnum::IfcDirectionSenseEnumEnum::ENUM_POSITIVE;
				}
				else if ( _stricmp( arg.c_str(), ".NEGATIVE.") == 0)
				{
					type_object->m_enum = IfcDirectionSenseEnum::IfcDirectionSenseEnumEnum::ENUM_NEGATIVE;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
