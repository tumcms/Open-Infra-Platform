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

#include <sstream>
#include <limits>
#include <map>
#include "OpenInfraPlatform/Ifc4/reader/ReaderUtil.h"
#include "OpenInfraPlatform/Ifc4/writer/WriterUtil.h"
#include "OpenInfraPlatform/Ifc4/model/shared_ptr.h"
#include "OpenInfraPlatform/Ifc4/model/Ifc4Exception.h"
#include "include/IfcBSplineCurveForm.h"

namespace OpenInfraPlatform
{
	namespace Ifc4
	{
		// TYPE IfcBSplineCurveForm 
		IfcBSplineCurveForm::IfcBSplineCurveForm() {}
		IfcBSplineCurveForm::~IfcBSplineCurveForm() {}
		void IfcBSplineCurveForm::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCBSPLINECURVEFORM("; }
			if( m_enum == ENUM_POLYLINE_FORM )
			{
				stream << ".POLYLINE_FORM.";
			}
			else if( m_enum == ENUM_CIRCULAR_ARC )
			{
				stream << ".CIRCULAR_ARC.";
			}
			else if( m_enum == ENUM_ELLIPTIC_ARC )
			{
				stream << ".ELLIPTIC_ARC.";
			}
			else if( m_enum == ENUM_PARABOLIC_ARC )
			{
				stream << ".PARABOLIC_ARC.";
			}
			else if( m_enum == ENUM_HYPERBOLIC_ARC )
			{
				stream << ".HYPERBOLIC_ARC.";
			}
			else if( m_enum == ENUM_UNSPECIFIED )
			{
				stream << ".UNSPECIFIED.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcBSplineCurveForm> IfcBSplineCurveForm::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcBSplineCurveForm>(); }
			shared_ptr<IfcBSplineCurveForm> type_object( new IfcBSplineCurveForm() );
			if( _stricmp( arg.c_str(), ".POLYLINE_FORM." ) == 0 )
			{
				type_object->m_enum = IfcBSplineCurveForm::ENUM_POLYLINE_FORM;
			}
			else if( _stricmp( arg.c_str(), ".CIRCULAR_ARC." ) == 0 )
			{
				type_object->m_enum = IfcBSplineCurveForm::ENUM_CIRCULAR_ARC;
			}
			else if( _stricmp( arg.c_str(), ".ELLIPTIC_ARC." ) == 0 )
			{
				type_object->m_enum = IfcBSplineCurveForm::ENUM_ELLIPTIC_ARC;
			}
			else if( _stricmp( arg.c_str(), ".PARABOLIC_ARC." ) == 0 )
			{
				type_object->m_enum = IfcBSplineCurveForm::ENUM_PARABOLIC_ARC;
			}
			else if( _stricmp( arg.c_str(), ".HYPERBOLIC_ARC." ) == 0 )
			{
				type_object->m_enum = IfcBSplineCurveForm::ENUM_HYPERBOLIC_ARC;
			}
			else if( _stricmp( arg.c_str(), ".UNSPECIFIED." ) == 0 )
			{
				type_object->m_enum = IfcBSplineCurveForm::ENUM_UNSPECIFIED;
			}
			return type_object;
		}
	} // end namespace Ifc4
} // end namespace OpenInfraPlatform
