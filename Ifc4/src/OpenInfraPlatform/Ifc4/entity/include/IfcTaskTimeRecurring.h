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

#pragma once
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include "OpenInfraPlatform/Ifc4/model/shared_ptr.h"
#include "OpenInfraPlatform/Ifc4/model/Ifc4Object.h"
#include "IfcTaskTime.h"

namespace OpenInfraPlatform
{
	namespace Ifc4
	{
		class IfcRecurrencePattern;
		//ENTITY
		class IfcTaskTimeRecurring : public IfcTaskTime
		{
		public:
			IfcTaskTimeRecurring();
			IfcTaskTimeRecurring( int id );
			~IfcTaskTimeRecurring();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity( shared_ptr<Ifc4Entity> other );
			virtual void getStepLine( std::stringstream& stream ) const;
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			virtual void readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc4Entity> >& map );
			virtual void setInverseCounterparts( shared_ptr<Ifc4Entity> ptr_self );
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcTaskTimeRecurring"; }


			// IfcSchedulingTime -----------------------------------------------------------
			// attributes:
			//  shared_ptr<IfcLabel>							m_Name;						//optional
			//  shared_ptr<IfcDataOriginEnum>				m_DataOrigin;				//optional
			//  shared_ptr<IfcLabel>							m_UserDefinedDataOrigin;	//optional

			// IfcTaskTime -----------------------------------------------------------
			// attributes:
			//  shared_ptr<IfcTaskDurationEnum>				m_DurationType;				//optional
			//  shared_ptr<IfcDuration>						m_ScheduleDuration;			//optional
			//  shared_ptr<IfcDateTime>						m_ScheduleStart;			//optional
			//  shared_ptr<IfcDateTime>						m_ScheduleFinish;			//optional
			//  shared_ptr<IfcDateTime>						m_EarlyStart;				//optional
			//  shared_ptr<IfcDateTime>						m_EarlyFinish;				//optional
			//  shared_ptr<IfcDateTime>						m_LateStart;				//optional
			//  shared_ptr<IfcDateTime>						m_LateFinish;				//optional
			//  shared_ptr<IfcDuration>						m_FreeFloat;				//optional
			//  shared_ptr<IfcDuration>						m_TotalFloat;				//optional
			//  shared_ptr<IfcBoolean>						m_IsCritical;				//optional
			//  shared_ptr<IfcDateTime>						m_StatusTime;				//optional
			//  shared_ptr<IfcDuration>						m_ActualDuration;			//optional
			//  shared_ptr<IfcDateTime>						m_ActualStart;				//optional
			//  shared_ptr<IfcDateTime>						m_ActualFinish;				//optional
			//  shared_ptr<IfcDuration>						m_RemainingTime;			//optional
			//  shared_ptr<IfcPositiveRatioMeasure>			m_Completion;				//optional

			// IfcTaskTimeRecurring -----------------------------------------------------------
			// attributes:
			shared_ptr<IfcRecurrencePattern>				m_Recurrence;
		};
	} // end namespace Ifc4
} // end namespace OpenInfraPlatform

