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
#include "include/IfcAheadOrBehind.h"
#include "include/IfcCoordinatedUniversalTimeOffset.h"
#include "include/IfcHourInDay.h"
#include "include/IfcMinuteInHour.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcCoordinatedUniversalTimeOffset 
		IfcCoordinatedUniversalTimeOffset::IfcCoordinatedUniversalTimeOffset() { m_entity_enum = IFCCOORDINATEDUNIVERSALTIMEOFFSET; }
		IfcCoordinatedUniversalTimeOffset::IfcCoordinatedUniversalTimeOffset( int id ) { m_id = id; m_entity_enum = IFCCOORDINATEDUNIVERSALTIMEOFFSET; }
		IfcCoordinatedUniversalTimeOffset::~IfcCoordinatedUniversalTimeOffset() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcCoordinatedUniversalTimeOffset::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcCoordinatedUniversalTimeOffset> other = dynamic_pointer_cast<IfcCoordinatedUniversalTimeOffset>(other_entity);
			if( !other) { return; }
			m_HourOffset = other->m_HourOffset;
			m_MinuteOffset = other->m_MinuteOffset;
			m_Sense = other->m_Sense;
		}
		void IfcCoordinatedUniversalTimeOffset::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCCOORDINATEDUNIVERSALTIMEOFFSET" << "(";
			if( m_HourOffset ) { m_HourOffset->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MinuteOffset ) { m_MinuteOffset->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Sense ) { m_Sense->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcCoordinatedUniversalTimeOffset::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcCoordinatedUniversalTimeOffset::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<3 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcCoordinatedUniversalTimeOffset, expecting 3, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>3 ){ std::cout << "Wrong parameter count for entity IfcCoordinatedUniversalTimeOffset, expecting 3, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_HourOffset = IfcHourInDay::readStepData( args[0] );
			m_MinuteOffset = IfcMinuteInHour::readStepData( args[1] );
			m_Sense = IfcAheadOrBehind::readStepData( args[2] );
		}
		void IfcCoordinatedUniversalTimeOffset::setInverseCounterparts( shared_ptr<Ifc2x3Entity> )
		{
		}
		void IfcCoordinatedUniversalTimeOffset::unlinkSelf()
		{
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
