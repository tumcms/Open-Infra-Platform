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
#include "include/IfcDateTimeSelect.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcPositiveRatioMeasure.h"
#include "include/IfcRelAssigns.h"
#include "include/IfcRelAssignsTasks.h"
#include "include/IfcRelAssignsToControl.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelDecomposes.h"
#include "include/IfcRelDefines.h"
#include "include/IfcScheduleTimeControl.h"
#include "include/IfcText.h"
#include "include/IfcTimeMeasure.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcScheduleTimeControl 
		IfcScheduleTimeControl::IfcScheduleTimeControl() { m_entity_enum = IFCSCHEDULETIMECONTROL; }
		IfcScheduleTimeControl::IfcScheduleTimeControl( int id ) { m_id = id; m_entity_enum = IFCSCHEDULETIMECONTROL; }
		IfcScheduleTimeControl::~IfcScheduleTimeControl() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcScheduleTimeControl::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcScheduleTimeControl> other = dynamic_pointer_cast<IfcScheduleTimeControl>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_ObjectType = other->m_ObjectType;
			m_ActualStart = other->m_ActualStart;
			m_EarlyStart = other->m_EarlyStart;
			m_LateStart = other->m_LateStart;
			m_ScheduleStart = other->m_ScheduleStart;
			m_ActualFinish = other->m_ActualFinish;
			m_EarlyFinish = other->m_EarlyFinish;
			m_LateFinish = other->m_LateFinish;
			m_ScheduleFinish = other->m_ScheduleFinish;
			m_ScheduleDuration = other->m_ScheduleDuration;
			m_ActualDuration = other->m_ActualDuration;
			m_RemainingTime = other->m_RemainingTime;
			m_FreeFloat = other->m_FreeFloat;
			m_TotalFloat = other->m_TotalFloat;
			m_IsCritical = other->m_IsCritical;
			m_StatusTime = other->m_StatusTime;
			m_StartFloat = other->m_StartFloat;
			m_FinishFloat = other->m_FinishFloat;
			m_Completion = other->m_Completion;
		}
		void IfcScheduleTimeControl::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCSCHEDULETIMECONTROL" << "(";
			if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ObjectType ) { m_ObjectType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ActualStart ) { m_ActualStart->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_EarlyStart ) { m_EarlyStart->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_LateStart ) { m_LateStart->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_ScheduleStart ) { m_ScheduleStart->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_ActualFinish ) { m_ActualFinish->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_EarlyFinish ) { m_EarlyFinish->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_LateFinish ) { m_LateFinish->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_ScheduleFinish ) { m_ScheduleFinish->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_ScheduleDuration ) { m_ScheduleDuration->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ActualDuration ) { m_ActualDuration->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RemainingTime ) { m_RemainingTime->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_FreeFloat ) { m_FreeFloat->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_TotalFloat ) { m_TotalFloat->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_IsCritical == false ) { stream << ".F."; }
			else if( m_IsCritical == true ) { stream << ".T."; }
			stream << ",";
			if( m_StatusTime ) { m_StatusTime->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_StartFloat ) { m_StartFloat->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_FinishFloat ) { m_FinishFloat->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Completion ) { m_Completion->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcScheduleTimeControl::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcScheduleTimeControl::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<23 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcScheduleTimeControl, expecting 23, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>23 ){ std::cout << "Wrong parameter count for entity IfcScheduleTimeControl, expecting 23, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			m_ObjectType = IfcLabel::readStepData( args[4] );
			m_ActualStart = IfcDateTimeSelect::readStepData( args[5], map );
			m_EarlyStart = IfcDateTimeSelect::readStepData( args[6], map );
			m_LateStart = IfcDateTimeSelect::readStepData( args[7], map );
			m_ScheduleStart = IfcDateTimeSelect::readStepData( args[8], map );
			m_ActualFinish = IfcDateTimeSelect::readStepData( args[9], map );
			m_EarlyFinish = IfcDateTimeSelect::readStepData( args[10], map );
			m_LateFinish = IfcDateTimeSelect::readStepData( args[11], map );
			m_ScheduleFinish = IfcDateTimeSelect::readStepData( args[12], map );
			m_ScheduleDuration = IfcTimeMeasure::readStepData( args[13] );
			m_ActualDuration = IfcTimeMeasure::readStepData( args[14] );
			m_RemainingTime = IfcTimeMeasure::readStepData( args[15] );
			m_FreeFloat = IfcTimeMeasure::readStepData( args[16] );
			m_TotalFloat = IfcTimeMeasure::readStepData( args[17] );
			if( _stricmp( args[18].c_str(), ".F." ) == 0 ) { m_IsCritical = false; }
			else if( _stricmp( args[18].c_str(), ".T." ) == 0 ) { m_IsCritical = true; }
			m_StatusTime = IfcDateTimeSelect::readStepData( args[19], map );
			m_StartFloat = IfcTimeMeasure::readStepData( args[20] );
			m_FinishFloat = IfcTimeMeasure::readStepData( args[21] );
			m_Completion = IfcPositiveRatioMeasure::readStepData( args[22] );
		}
		void IfcScheduleTimeControl::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcControl::setInverseCounterparts( ptr_self_entity );
		}
		void IfcScheduleTimeControl::unlinkSelf()
		{
			IfcControl::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
