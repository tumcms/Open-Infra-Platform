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
#include "IfcBoundaryCondition.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		class IfcTranslationalStiffnessSelect;
		class IfcTranslationalStiffnessSelect;
		class IfcTranslationalStiffnessSelect;
		class IfcRotationalStiffnessSelect;
		class IfcRotationalStiffnessSelect;
		class IfcRotationalStiffnessSelect;
		// ENTITY IfcBoundaryNodeCondition
		class IfcBoundaryNodeCondition : public IfcBoundaryCondition
		{
		public:
			IfcBoundaryNodeCondition();
			IfcBoundaryNodeCondition( int id );
			~IfcBoundaryNodeCondition();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity(std::shared_ptr<IfcAlignment1x1Entity> other);
			virtual void getStepLine(std::stringstream& stream) const;
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			virtual void readStepData(std::vector<std::string>& args, const std::map<int, shared_ptr<IfcAlignment1x1Entity> >& map);
			virtual void setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self);
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcBoundaryNodeCondition"; }

			// IfcBoundaryNodeCondition -----------------------
			// attributes:
			std::shared_ptr<IfcTranslationalStiffnessSelect> m_TranslationalStiffnessX;
			std::shared_ptr<IfcTranslationalStiffnessSelect> m_TranslationalStiffnessY;
			std::shared_ptr<IfcTranslationalStiffnessSelect> m_TranslationalStiffnessZ;
			std::shared_ptr<IfcRotationalStiffnessSelect> m_RotationalStiffnessX;
			std::shared_ptr<IfcRotationalStiffnessSelect> m_RotationalStiffnessY;
			std::shared_ptr<IfcRotationalStiffnessSelect> m_RotationalStiffnessZ;
		};
	}
}
