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

#include "IfcTransitionCurveType.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcTransitionCurveType::IfcTransitionCurveType() {}
		IfcTransitionCurveType::IfcTransitionCurveType(IfcTransitionCurveType::IfcTransitionCurveTypeEnum value) { m_enum = value; }
		IfcTransitionCurveType::~IfcTransitionCurveType() {}
		void IfcTransitionCurveType::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcTransitionCurveTypeEnum::ENUM_BIQUADRATICPARABOLA)
				{
					stream << ".BIQUADRATICPARABOLA.";
				}
				else if ( m_enum == IfcTransitionCurveTypeEnum::ENUM_BLOSSCURVE)
				{
					stream << ".BLOSSCURVE.";
				}
				else if ( m_enum == IfcTransitionCurveTypeEnum::ENUM_CLOTHOIDCURVE)
				{
					stream << ".CLOTHOIDCURVE.";
				}
				else if ( m_enum == IfcTransitionCurveTypeEnum::ENUM_COSINECURVE)
				{
					stream << ".COSINECURVE.";
				}
				else if ( m_enum == IfcTransitionCurveTypeEnum::ENUM_CUBICPARABOLA)
				{
					stream << ".CUBICPARABOLA.";
				}
				else if ( m_enum == IfcTransitionCurveTypeEnum::ENUM_SINECURVE)
				{
					stream << ".SINECURVE.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcTransitionCurveType> IfcTransitionCurveType::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcTransitionCurveType>(); }
				std::shared_ptr<IfcTransitionCurveType> type_object(new IfcTransitionCurveType() );
				if ( _stricmp( arg.c_str(), ".BIQUADRATICPARABOLA.") == 0)
				{
					type_object->m_enum = IfcTransitionCurveType::IfcTransitionCurveTypeEnum::ENUM_BIQUADRATICPARABOLA;
				}
				else if ( _stricmp( arg.c_str(), ".BLOSSCURVE.") == 0)
				{
					type_object->m_enum = IfcTransitionCurveType::IfcTransitionCurveTypeEnum::ENUM_BLOSSCURVE;
				}
				else if ( _stricmp( arg.c_str(), ".CLOTHOIDCURVE.") == 0)
				{
					type_object->m_enum = IfcTransitionCurveType::IfcTransitionCurveTypeEnum::ENUM_CLOTHOIDCURVE;
				}
				else if ( _stricmp( arg.c_str(), ".COSINECURVE.") == 0)
				{
					type_object->m_enum = IfcTransitionCurveType::IfcTransitionCurveTypeEnum::ENUM_COSINECURVE;
				}
				else if ( _stricmp( arg.c_str(), ".CUBICPARABOLA.") == 0)
				{
					type_object->m_enum = IfcTransitionCurveType::IfcTransitionCurveTypeEnum::ENUM_CUBICPARABOLA;
				}
				else if ( _stricmp( arg.c_str(), ".SINECURVE.") == 0)
				{
					type_object->m_enum = IfcTransitionCurveType::IfcTransitionCurveTypeEnum::ENUM_SINECURVE;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
