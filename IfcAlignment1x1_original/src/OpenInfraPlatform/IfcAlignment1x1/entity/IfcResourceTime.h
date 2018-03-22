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
		class IfcDuration;
		class IfcPositiveRatioMeasure;
		class IfcDateTime;
		class IfcDateTime;
		class IfcLabel;
		class IfcDuration;
		class IfcBoolean;
		class IfcDateTime;
		class IfcDuration;
		class IfcPositiveRatioMeasure;
		class IfcDateTime;
		class IfcDateTime;
		class IfcDuration;
		class IfcPositiveRatioMeasure;
		class IfcPositiveRatioMeasure;
		// ENTITY IfcResourceTime
		class IfcResourceTime : public IfcSchedulingTime
		{
		public:
			IfcResourceTime();
			IfcResourceTime( int id );
			~IfcResourceTime();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity(std::shared_ptr<IfcAlignment1x1Entity> other);
			virtual void getStepLine(std::stringstream& stream) const;
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			virtual void readStepData(std::vector<std::string>& args, const std::map<int, shared_ptr<IfcAlignment1x1Entity> >& map);
			virtual void setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self);
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcResourceTime"; }

			// IfcResourceTime -----------------------
			// attributes:
			std::shared_ptr<IfcDuration> m_ScheduleWork;
			std::shared_ptr<IfcPositiveRatioMeasure> m_ScheduleUsage;
			std::shared_ptr<IfcDateTime> m_ScheduleStart;
			std::shared_ptr<IfcDateTime> m_ScheduleFinish;
			std::shared_ptr<IfcLabel> m_ScheduleContour;
			std::shared_ptr<IfcDuration> m_LevelingDelay;
			std::shared_ptr<IfcBoolean> m_IsOverAllocated;
			std::shared_ptr<IfcDateTime> m_StatusTime;
			std::shared_ptr<IfcDuration> m_ActualWork;
			std::shared_ptr<IfcPositiveRatioMeasure> m_ActualUsage;
			std::shared_ptr<IfcDateTime> m_ActualStart;
			std::shared_ptr<IfcDateTime> m_ActualFinish;
			std::shared_ptr<IfcDuration> m_RemainingWork;
			std::shared_ptr<IfcPositiveRatioMeasure> m_RemainingUsage;
			std::shared_ptr<IfcPositiveRatioMeasure> m_Completion;
		};
	}
}
