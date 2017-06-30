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
#include "include/IfcDateAndTime.h"
#include "include/IfcLocalTime.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcDateAndTime 
		IfcDateAndTime::IfcDateAndTime() { m_entity_enum = IFCDATEANDTIME; }
		IfcDateAndTime::IfcDateAndTime( int id ) { m_id = id; m_entity_enum = IFCDATEANDTIME; }
		IfcDateAndTime::~IfcDateAndTime() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcDateAndTime::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcDateAndTime> other = dynamic_pointer_cast<IfcDateAndTime>(other_entity);
			if( !other) { return; }
			m_DateComponent = other->m_DateComponent;
			m_TimeComponent = other->m_TimeComponent;
		}
		void IfcDateAndTime::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCDATEANDTIME" << "(";
			if( m_DateComponent ) { stream << "#" << m_DateComponent->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_TimeComponent ) { stream << "#" << m_TimeComponent->getId(); } else { stream << "$"; }
			stream << ");";
		}
		void IfcDateAndTime::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcDateAndTime::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<2 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcDateAndTime, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>2 ){ std::cout << "Wrong parameter count for entity IfcDateAndTime, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readEntityReference( args[0], m_DateComponent, map );
			readEntityReference( args[1], m_TimeComponent, map );
		}
		void IfcDateAndTime::setInverseCounterparts( shared_ptr<Ifc2x3Entity> )
		{
		}
		void IfcDateAndTime::unlinkSelf()
		{
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
