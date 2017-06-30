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

#include "model/IfcBridgeException.h"
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "IfcBridgeEntityEnums.h"
#include "include/IfcDayInMonthNumber.h"
#include "include/IfcDayInWeekNumber.h"
#include "include/IfcInteger.h"
#include "include/IfcMonthInYearNumber.h"
#include "include/IfcRecurrencePattern.h"
#include "include/IfcRecurrenceTypeEnum.h"
#include "include/IfcTimePeriod.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// ENTITY IfcRecurrencePattern 
		IfcRecurrencePattern::IfcRecurrencePattern() { m_entity_enum = IFCRECURRENCEPATTERN; }
		IfcRecurrencePattern::IfcRecurrencePattern( int id ) { m_id = id; m_entity_enum = IFCRECURRENCEPATTERN; }
		IfcRecurrencePattern::~IfcRecurrencePattern() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcRecurrencePattern::setEntity( shared_ptr<IfcBridgeEntity> other_entity )
		{
			shared_ptr<IfcRecurrencePattern> other = dynamic_pointer_cast<IfcRecurrencePattern>(other_entity);
			if( !other) { return; }
			m_RecurrenceType = other->m_RecurrenceType;
			m_DayComponent = other->m_DayComponent;
			m_WeekdayComponent = other->m_WeekdayComponent;
			m_MonthComponent = other->m_MonthComponent;
			m_Position = other->m_Position;
			m_Interval = other->m_Interval;
			m_Occurrences = other->m_Occurrences;
			m_TimePeriods = other->m_TimePeriods;
		}
		void IfcRecurrencePattern::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCRECURRENCEPATTERN" << "(";
			if( m_RecurrenceType ) { m_RecurrenceType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeTypeOfIntList( stream, m_DayComponent );
			stream << ",";
			writeTypeOfIntList( stream, m_WeekdayComponent );
			stream << ",";
			writeTypeOfIntList( stream, m_MonthComponent );
			stream << ",";
			if( m_Position ) { m_Position->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Interval ) { m_Interval->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Occurrences ) { m_Occurrences->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_TimePeriods );
			stream << ");";
		}
		void IfcRecurrencePattern::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcRecurrencePattern::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcBridgeEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<8 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcRecurrencePattern, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcBridgeException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>8 ){ std::cout << "Wrong parameter count for entity IfcRecurrencePattern, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_RecurrenceType = IfcRecurrenceTypeEnum::readStepData( args[0] );
			readTypeOfIntList( args[1], m_DayComponent );
			readTypeOfIntList( args[2], m_WeekdayComponent );
			readTypeOfIntList( args[3], m_MonthComponent );
			m_Position = IfcInteger::readStepData( args[4] );
			m_Interval = IfcInteger::readStepData( args[5] );
			m_Occurrences = IfcInteger::readStepData( args[6] );
			readEntityReferenceList( args[7], m_TimePeriods, map );
		}
		void IfcRecurrencePattern::setInverseCounterparts( shared_ptr<IfcBridgeEntity> )
		{
		}
		void IfcRecurrencePattern::unlinkSelf()
		{
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
