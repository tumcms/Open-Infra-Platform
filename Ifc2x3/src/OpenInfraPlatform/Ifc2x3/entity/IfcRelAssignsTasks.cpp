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
#include "include/IfcControl.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcObjectDefinition.h"
#include "include/IfcObjectTypeEnum.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcRelAssignsTasks.h"
#include "include/IfcScheduleTimeControl.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcRelAssignsTasks 
		IfcRelAssignsTasks::IfcRelAssignsTasks() { m_entity_enum = IFCRELASSIGNSTASKS; }
		IfcRelAssignsTasks::IfcRelAssignsTasks( int id ) { m_id = id; m_entity_enum = IFCRELASSIGNSTASKS; }
		IfcRelAssignsTasks::~IfcRelAssignsTasks() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcRelAssignsTasks::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcRelAssignsTasks> other = dynamic_pointer_cast<IfcRelAssignsTasks>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_RelatedObjects = other->m_RelatedObjects;
			m_RelatedObjectsType = other->m_RelatedObjectsType;
			m_RelatingControl = other->m_RelatingControl;
			m_TimeForTask = other->m_TimeForTask;
		}
		void IfcRelAssignsTasks::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCRELASSIGNSTASKS" << "(";
			if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_RelatedObjects );
			stream << ",";
			if( m_RelatedObjectsType ) { m_RelatedObjectsType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RelatingControl ) { stream << "#" << m_RelatingControl->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_TimeForTask ) { stream << "#" << m_TimeForTask->getId(); } else { stream << "$"; }
			stream << ");";
		}
		void IfcRelAssignsTasks::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcRelAssignsTasks::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<8 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcRelAssignsTasks, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>8 ){ std::cout << "Wrong parameter count for entity IfcRelAssignsTasks, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			readEntityReferenceList( args[4], m_RelatedObjects, map );
			m_RelatedObjectsType = IfcObjectTypeEnum::readStepData( args[5] );
			readEntityReference( args[6], m_RelatingControl, map );
			readEntityReference( args[7], m_TimeForTask, map );
		}
		void IfcRelAssignsTasks::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcRelAssignsToControl::setInverseCounterparts( ptr_self_entity );
			shared_ptr<IfcRelAssignsTasks> ptr_self = dynamic_pointer_cast<IfcRelAssignsTasks>( ptr_self_entity );
			if( !ptr_self ) { throw Ifc2x3Exception( "IfcRelAssignsTasks::setInverseCounterparts: type mismatch" ); }
			if( m_TimeForTask )
			{
				m_TimeForTask->m_ScheduleTimeControlAssigned_inverse = ptr_self;
			}
		}
		void IfcRelAssignsTasks::unlinkSelf()
		{
			IfcRelAssignsToControl::unlinkSelf();
			if( m_TimeForTask )
			{
				shared_ptr<IfcRelAssignsTasks> self_candidate( m_TimeForTask->m_ScheduleTimeControlAssigned_inverse );
				if( self_candidate->getId() == this->getId() )
				{
					weak_ptr<IfcRelAssignsTasks>& self_candidate_weak = m_TimeForTask->m_ScheduleTimeControlAssigned_inverse;
					self_candidate_weak.reset();
				}
			}
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
