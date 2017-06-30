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

#include "OpenInfraPlatform/IfcRoad/model/IfcRoadException.h"
#include "OpenInfraPlatform/IfcRoad/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcRoad/writer/WriterUtil.h"
#include "OpenInfraPlatform/IfcRoad/IfcRoadEntityEnums.h"
#include "include/IfcTime.h"
#include "include/IfcTimePeriod.h"

namespace OpenInfraPlatform
{
	namespace IfcRoad
	{
		// ENTITY IfcTimePeriod 
		IfcTimePeriod::IfcTimePeriod() { m_entity_enum = IFCTIMEPERIOD; }
		IfcTimePeriod::IfcTimePeriod( int id ) { m_id = id; m_entity_enum = IFCTIMEPERIOD; }
		IfcTimePeriod::~IfcTimePeriod() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcTimePeriod::setEntity( shared_ptr<IfcRoadEntity> other_entity )
		{
			shared_ptr<IfcTimePeriod> other = dynamic_pointer_cast<IfcTimePeriod>(other_entity);
			if( !other) { return; }
			m_StartTime = other->m_StartTime;
			m_EndTime = other->m_EndTime;
		}
		void IfcTimePeriod::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCTIMEPERIOD" << "(";
			if( m_StartTime ) { m_StartTime->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_EndTime ) { m_EndTime->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcTimePeriod::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcTimePeriod::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcRoadEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<2 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcTimePeriod, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcRoadException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>2 ){ std::cout << "Wrong parameter count for entity IfcTimePeriod, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_StartTime = IfcTime::readStepData( args[0] );
			m_EndTime = IfcTime::readStepData( args[1] );
		}
		void IfcTimePeriod::setInverseCounterparts( shared_ptr<IfcRoadEntity> )
		{
		}
		void IfcTimePeriod::unlinkSelf()
		{
		}
	} // end namespace IfcRoad
} // end namespace OpenInfraPlatform
