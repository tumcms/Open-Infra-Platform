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
#include "../../model/shared_ptr.h"
#include "../../model/Ifc2x3Object.h"
#include "IfcControl.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		class IfcDateTimeSelect;
		class IfcTimeMeasure;
		class IfcPositiveRatioMeasure;
		class IfcRelAssignsTasks;
		//ENTITY
		class IfcScheduleTimeControl : public IfcControl
		{
		public:
			IfcScheduleTimeControl();
			IfcScheduleTimeControl( int id );
			~IfcScheduleTimeControl();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity( shared_ptr<Ifc2x3Entity> other );
			virtual void getStepLine( std::stringstream& stream ) const;
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			virtual void readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map );
			virtual void setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self );
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcScheduleTimeControl"; }


			// IfcRoot -----------------------------------------------------------
			// attributes:
			//  shared_ptr<IfcGloballyUniqueId>				m_GlobalId;
			//  shared_ptr<IfcOwnerHistory>					m_OwnerHistory;
			//  shared_ptr<IfcLabel>							m_Name;						//optional
			//  shared_ptr<IfcText>							m_Description;				//optional

			// IfcObjectDefinition -----------------------------------------------------------
			// inverse attributes:
			//  std::vector<weak_ptr<IfcRelAssigns> >		m_HasAssignments_inverse;
			//  std::vector<weak_ptr<IfcRelDecomposes> >		m_IsDecomposedBy_inverse;
			//  std::vector<weak_ptr<IfcRelDecomposes> >		m_Decomposes_inverse;
			//  std::vector<weak_ptr<IfcRelAssociates> >		m_HasAssociations_inverse;

			// IfcObject -----------------------------------------------------------
			// attributes:
			//  shared_ptr<IfcLabel>							m_ObjectType;				//optional
			// inverse attributes:
			//  std::vector<weak_ptr<IfcRelDefines> >		m_IsDefinedBy_inverse;

			// IfcControl -----------------------------------------------------------
			// inverse attributes:
			//  std::vector<weak_ptr<IfcRelAssignsToControl> >	m_Controls_inverse;

			// IfcScheduleTimeControl -----------------------------------------------------------
			// attributes:
			shared_ptr<IfcDateTimeSelect>				m_ActualStart;				//optional
			shared_ptr<IfcDateTimeSelect>				m_EarlyStart;				//optional
			shared_ptr<IfcDateTimeSelect>				m_LateStart;				//optional
			shared_ptr<IfcDateTimeSelect>				m_ScheduleStart;			//optional
			shared_ptr<IfcDateTimeSelect>				m_ActualFinish;				//optional
			shared_ptr<IfcDateTimeSelect>				m_EarlyFinish;				//optional
			shared_ptr<IfcDateTimeSelect>				m_LateFinish;				//optional
			shared_ptr<IfcDateTimeSelect>				m_ScheduleFinish;			//optional
			shared_ptr<IfcTimeMeasure>					m_ScheduleDuration;			//optional
			shared_ptr<IfcTimeMeasure>					m_ActualDuration;			//optional
			shared_ptr<IfcTimeMeasure>					m_RemainingTime;			//optional
			shared_ptr<IfcTimeMeasure>					m_FreeFloat;				//optional
			shared_ptr<IfcTimeMeasure>					m_TotalFloat;				//optional
			bool											m_IsCritical;				//optional
			shared_ptr<IfcDateTimeSelect>				m_StatusTime;				//optional
			shared_ptr<IfcTimeMeasure>					m_StartFloat;				//optional
			shared_ptr<IfcTimeMeasure>					m_FinishFloat;				//optional
			shared_ptr<IfcPositiveRatioMeasure>			m_Completion;				//optional
			// inverse attributes:
			weak_ptr<IfcRelAssignsTasks>					m_ScheduleTimeControlAssigned_inverse;
		};
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform

