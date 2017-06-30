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

#include "model/Ifc2x3Exception.h"
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "Ifc2x3EntityEnums.h"
#include "include/IfcCalendarDate.h"
#include "include/IfcDayInMonthNumber.h"
#include "include/IfcMonthInYearNumber.h"
#include "include/IfcYearNumber.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcCalendarDate 
		IfcCalendarDate::IfcCalendarDate() { m_entity_enum = IFCCALENDARDATE; }
		IfcCalendarDate::IfcCalendarDate( int id ) { m_id = id; m_entity_enum = IFCCALENDARDATE; }
		IfcCalendarDate::~IfcCalendarDate() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcCalendarDate::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcCalendarDate> other = dynamic_pointer_cast<IfcCalendarDate>(other_entity);
			if( !other) { return; }
			m_DayComponent = other->m_DayComponent;
			m_MonthComponent = other->m_MonthComponent;
			m_YearComponent = other->m_YearComponent;
		}
		void IfcCalendarDate::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCCALENDARDATE" << "(";
			if( m_DayComponent ) { m_DayComponent->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MonthComponent ) { m_MonthComponent->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_YearComponent ) { m_YearComponent->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcCalendarDate::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcCalendarDate::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<3 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcCalendarDate, expecting 3, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>3 ){ std::cout << "Wrong parameter count for entity IfcCalendarDate, expecting 3, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_DayComponent = IfcDayInMonthNumber::readStepData( args[0] );
			m_MonthComponent = IfcMonthInYearNumber::readStepData( args[1] );
			m_YearComponent = IfcYearNumber::readStepData( args[2] );
		}
		void IfcCalendarDate::setInverseCounterparts( shared_ptr<Ifc2x3Entity> )
		{
		}
		void IfcCalendarDate::unlinkSelf()
		{
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
