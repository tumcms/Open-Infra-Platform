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

#include "IfcTransitionCode.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcTransitionCode::IfcTransitionCode() {}
		IfcTransitionCode::IfcTransitionCode(IfcTransitionCode::IfcTransitionCodeEnum value) { m_enum = value; }
		IfcTransitionCode::~IfcTransitionCode() {}
		void IfcTransitionCode::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcTransitionCodeEnum::ENUM_DISCONTINUOUS)
				{
					stream << ".DISCONTINUOUS.";
				}
				else if ( m_enum == IfcTransitionCodeEnum::ENUM_CONTINUOUS)
				{
					stream << ".CONTINUOUS.";
				}
				else if ( m_enum == IfcTransitionCodeEnum::ENUM_CONTSAMEGRADIENT)
				{
					stream << ".CONTSAMEGRADIENT.";
				}
				else if ( m_enum == IfcTransitionCodeEnum::ENUM_CONTSAMEGRADIENTSAMECURVATURE)
				{
					stream << ".CONTSAMEGRADIENTSAMECURVATURE.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcTransitionCode> IfcTransitionCode::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcTransitionCode>(); }
				std::shared_ptr<IfcTransitionCode> type_object(new IfcTransitionCode() );
				if ( _stricmp( arg.c_str(), ".DISCONTINUOUS.") == 0)
				{
					type_object->m_enum = IfcTransitionCode::IfcTransitionCodeEnum::ENUM_DISCONTINUOUS;
				}
				else if ( _stricmp( arg.c_str(), ".CONTINUOUS.") == 0)
				{
					type_object->m_enum = IfcTransitionCode::IfcTransitionCodeEnum::ENUM_CONTINUOUS;
				}
				else if ( _stricmp( arg.c_str(), ".CONTSAMEGRADIENT.") == 0)
				{
					type_object->m_enum = IfcTransitionCode::IfcTransitionCodeEnum::ENUM_CONTSAMEGRADIENT;
				}
				else if ( _stricmp( arg.c_str(), ".CONTSAMEGRADIENTSAMECURVATURE.") == 0)
				{
					type_object->m_enum = IfcTransitionCode::IfcTransitionCodeEnum::ENUM_CONTSAMEGRADIENTSAMECURVATURE;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
