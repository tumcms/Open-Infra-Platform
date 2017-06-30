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

#include "model/IfcTunnelException.h"
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "IfcTunnelEntityEnums.h"
#include "include/IfcDataOriginEnum.h"
#include "include/IfcDateTime.h"
#include "include/IfcDuration.h"
#include "include/IfcLabel.h"
#include "include/IfcPositiveRatioMeasure.h"
#include "include/IfcRecurrencePattern.h"
#include "include/IfcTaskDurationEnum.h"
#include "include/IfcTaskTimeRecurring.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		// ENTITY IfcTaskTimeRecurring 
		IfcTaskTimeRecurring::IfcTaskTimeRecurring() { m_entity_enum = IFCTASKTIMERECURRING; }
		IfcTaskTimeRecurring::IfcTaskTimeRecurring( int id ) { m_id = id; m_entity_enum = IFCTASKTIMERECURRING; }
		IfcTaskTimeRecurring::~IfcTaskTimeRecurring() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcTaskTimeRecurring::setEntity( shared_ptr<IfcTunnelEntity> other_entity )
		{
			shared_ptr<IfcTaskTimeRecurring> other = dynamic_pointer_cast<IfcTaskTimeRecurring>(other_entity);
			if( !other) { return; }
			m_Name = other->m_Name;
			m_DataOrigin = other->m_DataOrigin;
			m_UserDefinedDataOrigin = other->m_UserDefinedDataOrigin;
			m_DurationType = other->m_DurationType;
			m_ScheduleDuration = other->m_ScheduleDuration;
			m_ScheduleStart = other->m_ScheduleStart;
			m_ScheduleFinish = other->m_ScheduleFinish;
			m_EarlyStart = other->m_EarlyStart;
			m_EarlyFinish = other->m_EarlyFinish;
			m_LateStart = other->m_LateStart;
			m_LateFinish = other->m_LateFinish;
			m_FreeFloat = other->m_FreeFloat;
			m_TotalFloat = other->m_TotalFloat;
			m_IsCritical = other->m_IsCritical;
			m_StatusTime = other->m_StatusTime;
			m_ActualDuration = other->m_ActualDuration;
			m_ActualStart = other->m_ActualStart;
			m_ActualFinish = other->m_ActualFinish;
			m_RemainingTime = other->m_RemainingTime;
			m_Completion = other->m_Completion;
			m_Recurrance = other->m_Recurrance;
		}
		void IfcTaskTimeRecurring::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCTASKTIMERECURRING" << "(";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_DataOrigin ) { m_DataOrigin->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_UserDefinedDataOrigin ) { m_UserDefinedDataOrigin->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_DurationType ) { m_DurationType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ScheduleDuration ) { m_ScheduleDuration->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ScheduleStart ) { m_ScheduleStart->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ScheduleFinish ) { m_ScheduleFinish->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_EarlyStart ) { m_EarlyStart->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_EarlyFinish ) { m_EarlyFinish->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LateStart ) { m_LateStart->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LateFinish ) { m_LateFinish->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_FreeFloat ) { m_FreeFloat->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_TotalFloat ) { m_TotalFloat->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_IsCritical == false ) { stream << ".F."; }
			else if( m_IsCritical == true ) { stream << ".T."; }
			stream << ",";
			if( m_StatusTime ) { m_StatusTime->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ActualDuration ) { m_ActualDuration->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ActualStart ) { m_ActualStart->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ActualFinish ) { m_ActualFinish->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RemainingTime ) { m_RemainingTime->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Completion ) { m_Completion->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Recurrance ) { stream << "#" << m_Recurrance->getId(); } else { stream << "$"; }
			stream << ");";
		}
		void IfcTaskTimeRecurring::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcTaskTimeRecurring::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcTunnelEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<21 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcTaskTimeRecurring, expecting 21, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcTunnelException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>21 ){ std::cout << "Wrong parameter count for entity IfcTaskTimeRecurring, expecting 21, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Name = IfcLabel::readStepData( args[0] );
			m_DataOrigin = IfcDataOriginEnum::readStepData( args[1] );
			m_UserDefinedDataOrigin = IfcLabel::readStepData( args[2] );
			m_DurationType = IfcTaskDurationEnum::readStepData( args[3] );
			m_ScheduleDuration = IfcDuration::readStepData( args[4] );
			m_ScheduleStart = IfcDateTime::readStepData( args[5] );
			m_ScheduleFinish = IfcDateTime::readStepData( args[6] );
			m_EarlyStart = IfcDateTime::readStepData( args[7] );
			m_EarlyFinish = IfcDateTime::readStepData( args[8] );
			m_LateStart = IfcDateTime::readStepData( args[9] );
			m_LateFinish = IfcDateTime::readStepData( args[10] );
			m_FreeFloat = IfcDuration::readStepData( args[11] );
			m_TotalFloat = IfcDuration::readStepData( args[12] );
			if( _stricmp( args[13].c_str(), ".F." ) == 0 ) { m_IsCritical = false; }
			else if( _stricmp( args[13].c_str(), ".T." ) == 0 ) { m_IsCritical = true; }
			m_StatusTime = IfcDateTime::readStepData( args[14] );
			m_ActualDuration = IfcDuration::readStepData( args[15] );
			m_ActualStart = IfcDateTime::readStepData( args[16] );
			m_ActualFinish = IfcDateTime::readStepData( args[17] );
			m_RemainingTime = IfcDuration::readStepData( args[18] );
			m_Completion = IfcPositiveRatioMeasure::readStepData( args[19] );
			readEntityReference( args[20], m_Recurrance, map );
		}
		void IfcTaskTimeRecurring::setInverseCounterparts( shared_ptr<IfcTunnelEntity> ptr_self_entity )
		{
			IfcTaskTime::setInverseCounterparts( ptr_self_entity );
		}
		void IfcTaskTimeRecurring::unlinkSelf()
		{
			IfcTaskTime::unlinkSelf();
		}
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform
