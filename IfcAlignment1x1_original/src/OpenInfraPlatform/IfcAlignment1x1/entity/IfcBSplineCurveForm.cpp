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

#include "IfcBSplineCurveForm.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcBSplineCurveForm::IfcBSplineCurveForm() {}
		IfcBSplineCurveForm::IfcBSplineCurveForm(IfcBSplineCurveForm::IfcBSplineCurveFormEnum value) { m_enum = value; }
		IfcBSplineCurveForm::~IfcBSplineCurveForm() {}
		void IfcBSplineCurveForm::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcBSplineCurveFormEnum::ENUM_POLYLINE_FORM)
				{
					stream << ".POLYLINE_FORM.";
				}
				else if ( m_enum == IfcBSplineCurveFormEnum::ENUM_CIRCULAR_ARC)
				{
					stream << ".CIRCULAR_ARC.";
				}
				else if ( m_enum == IfcBSplineCurveFormEnum::ENUM_ELLIPTIC_ARC)
				{
					stream << ".ELLIPTIC_ARC.";
				}
				else if ( m_enum == IfcBSplineCurveFormEnum::ENUM_PARABOLIC_ARC)
				{
					stream << ".PARABOLIC_ARC.";
				}
				else if ( m_enum == IfcBSplineCurveFormEnum::ENUM_HYPERBOLIC_ARC)
				{
					stream << ".HYPERBOLIC_ARC.";
				}
				else if ( m_enum == IfcBSplineCurveFormEnum::ENUM_UNSPECIFIED)
				{
					stream << ".UNSPECIFIED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcBSplineCurveForm> IfcBSplineCurveForm::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcBSplineCurveForm>(); }
				std::shared_ptr<IfcBSplineCurveForm> type_object(new IfcBSplineCurveForm() );
				if ( _stricmp( arg.c_str(), ".POLYLINE_FORM.") == 0)
				{
					type_object->m_enum = IfcBSplineCurveForm::IfcBSplineCurveFormEnum::ENUM_POLYLINE_FORM;
				}
				else if ( _stricmp( arg.c_str(), ".CIRCULAR_ARC.") == 0)
				{
					type_object->m_enum = IfcBSplineCurveForm::IfcBSplineCurveFormEnum::ENUM_CIRCULAR_ARC;
				}
				else if ( _stricmp( arg.c_str(), ".ELLIPTIC_ARC.") == 0)
				{
					type_object->m_enum = IfcBSplineCurveForm::IfcBSplineCurveFormEnum::ENUM_ELLIPTIC_ARC;
				}
				else if ( _stricmp( arg.c_str(), ".PARABOLIC_ARC.") == 0)
				{
					type_object->m_enum = IfcBSplineCurveForm::IfcBSplineCurveFormEnum::ENUM_PARABOLIC_ARC;
				}
				else if ( _stricmp( arg.c_str(), ".HYPERBOLIC_ARC.") == 0)
				{
					type_object->m_enum = IfcBSplineCurveForm::IfcBSplineCurveFormEnum::ENUM_HYPERBOLIC_ARC;
				}
				else if ( _stricmp( arg.c_str(), ".UNSPECIFIED.") == 0)
				{
					type_object->m_enum = IfcBSplineCurveForm::IfcBSplineCurveFormEnum::ENUM_UNSPECIFIED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
