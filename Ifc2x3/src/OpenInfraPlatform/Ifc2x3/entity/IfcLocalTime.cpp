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
#include "include/IfcCoordinatedUniversalTimeOffset.h"
#include "include/IfcDaylightSavingHour.h"
#include "include/IfcHourInDay.h"
#include "include/IfcLocalTime.h"
#include "include/IfcMinuteInHour.h"
#include "include/IfcSecondInMinute.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcLocalTime 
		IfcLocalTime::IfcLocalTime() { m_entity_enum = IFCLOCALTIME; }
		IfcLocalTime::IfcLocalTime( int id ) { m_id = id; m_entity_enum = IFCLOCALTIME; }
		IfcLocalTime::~IfcLocalTime() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcLocalTime::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcLocalTime> other = dynamic_pointer_cast<IfcLocalTime>(other_entity);
			if( !other) { return; }
			m_HourComponent = other->m_HourComponent;
			m_MinuteComponent = other->m_MinuteComponent;
			m_SecondComponent = other->m_SecondComponent;
			m_Zone = other->m_Zone;
			m_DaylightSavingOffset = other->m_DaylightSavingOffset;
		}
		void IfcLocalTime::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCLOCALTIME" << "(";
			if( m_HourComponent ) { m_HourComponent->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MinuteComponent ) { m_MinuteComponent->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_SecondComponent ) { m_SecondComponent->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Zone ) { stream << "#" << m_Zone->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_DaylightSavingOffset ) { m_DaylightSavingOffset->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcLocalTime::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcLocalTime::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<5 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcLocalTime, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>5 ){ std::cout << "Wrong parameter count for entity IfcLocalTime, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_HourComponent = IfcHourInDay::readStepData( args[0] );
			m_MinuteComponent = IfcMinuteInHour::readStepData( args[1] );
			m_SecondComponent = IfcSecondInMinute::readStepData( args[2] );
			readEntityReference( args[3], m_Zone, map );
			m_DaylightSavingOffset = IfcDaylightSavingHour::readStepData( args[4] );
		}
		void IfcLocalTime::setInverseCounterparts( shared_ptr<Ifc2x3Entity> )
		{
		}
		void IfcLocalTime::unlinkSelf()
		{
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
