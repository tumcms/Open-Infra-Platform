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
#include <memory>
#include <sstream>
#include <string>
#include "OpenInfraPlatform/IfcAlignment1x1/model/Object.h"
#include "IfcSchedulingTime.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		class IfcTaskDurationEnum;
		class IfcDuration;
		class IfcDateTime;
		class IfcDateTime;
		class IfcDateTime;
		class IfcDateTime;
		class IfcDateTime;
		class IfcDateTime;
		class IfcDuration;
		class IfcDuration;
		class IfcBoolean;
		class IfcDateTime;
		class IfcDuration;
		class IfcDateTime;
		class IfcDateTime;
		class IfcDuration;
		class IfcPositiveRatioMeasure;
		// ENTITY IfcTaskTime
		class IfcTaskTime : public IfcSchedulingTime
		{
		public:
			IfcTaskTime();
			IfcTaskTime( int id );
			~IfcTaskTime();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity(std::shared_ptr<IfcAlignment1x1Entity> other);
			virtual void getStepLine(std::stringstream& stream) const;
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			virtual void readStepData(std::vector<std::string>& args, const std::map<int, shared_ptr<IfcAlignment1x1Entity> >& map);
			virtual void setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self);
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcTaskTime"; }

			// IfcTaskTime -----------------------
			// attributes:
			std::shared_ptr<IfcTaskDurationEnum> m_DurationType;
			std::shared_ptr<IfcDuration> m_ScheduleDuration;
			std::shared_ptr<IfcDateTime> m_ScheduleStart;
			std::shared_ptr<IfcDateTime> m_ScheduleFinish;
			std::shared_ptr<IfcDateTime> m_EarlyStart;
			std::shared_ptr<IfcDateTime> m_EarlyFinish;
			std::shared_ptr<IfcDateTime> m_LateStart;
			std::shared_ptr<IfcDateTime> m_LateFinish;
			std::shared_ptr<IfcDuration> m_FreeFloat;
			std::shared_ptr<IfcDuration> m_TotalFloat;
			std::shared_ptr<IfcBoolean> m_IsCritical;
			std::shared_ptr<IfcDateTime> m_StatusTime;
			std::shared_ptr<IfcDuration> m_ActualDuration;
			std::shared_ptr<IfcDateTime> m_ActualStart;
			std::shared_ptr<IfcDateTime> m_ActualFinish;
			std::shared_ptr<IfcDuration> m_RemainingTime;
			std::shared_ptr<IfcPositiveRatioMeasure> m_Completion;
		};
	}
}
