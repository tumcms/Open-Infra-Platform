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
#include "IfcMetricValueSelect.h"
#include "IfcObjectReferenceSelect.h"
#include "IfcResourceObjectSelect.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		class IfcLabel;
		class IfcText;
		class IfcAppliedValueSelect;
		class IfcMeasureWithUnit;
		class IfcDate;
		class IfcDate;
		class IfcLabel;
		class IfcLabel;
		class IfcArithmeticOperatorEnum;
		class IfcAppliedValue;
		// ENTITY IfcAppliedValue
		class IfcAppliedValue : public IfcAlignment1x1Entity, public IfcMetricValueSelect
, public IfcObjectReferenceSelect
, public IfcResourceObjectSelect

		{
		public:
			IfcAppliedValue();
			IfcAppliedValue( int id );
			~IfcAppliedValue();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity(std::shared_ptr<IfcAlignment1x1Entity> other);
			virtual void getStepLine(std::stringstream& stream) const;
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			virtual void readStepData(std::vector<std::string>& args, const std::map<int, shared_ptr<IfcAlignment1x1Entity> >& map);
			virtual void setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self);
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcAppliedValue"; }

			// IfcAppliedValue -----------------------
			// attributes:
			std::shared_ptr<IfcLabel> m_Name;
			std::shared_ptr<IfcText> m_Description;
			std::shared_ptr<IfcAppliedValueSelect> m_AppliedValue;
			std::shared_ptr<IfcMeasureWithUnit> m_UnitBasis;
			std::shared_ptr<IfcDate> m_ApplicableDate;
			std::shared_ptr<IfcDate> m_FixedUntilDate;
			std::shared_ptr<IfcLabel> m_Category;
			std::shared_ptr<IfcLabel> m_Condition;
			std::shared_ptr<IfcArithmeticOperatorEnum> m_ArithmeticOperator;
			std::vector<std::shared_ptr<IfcAppliedValue>>  m_Components;
		};
	}
}
