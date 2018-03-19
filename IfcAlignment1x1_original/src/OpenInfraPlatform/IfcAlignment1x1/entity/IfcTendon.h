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
#include "IfcReinforcingElement.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		class IfcTendonTypeEnum;
		class IfcPositiveLengthMeasure;
		class IfcAreaMeasure;
		class IfcForceMeasure;
		class IfcPressureMeasure;
		class IfcNormalisedRatioMeasure;
		class IfcPositiveLengthMeasure;
		class IfcPositiveLengthMeasure;
		// ENTITY IfcTendon
		class IfcTendon : public IfcReinforcingElement
		{
		public:
			IfcTendon();
			IfcTendon( int id );
			~IfcTendon();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity(std::shared_ptr<IfcAlignment1x1Entity> other);
			virtual void getStepLine(std::stringstream& stream) const;
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			virtual void readStepData(std::vector<std::string>& args, const std::map<int, shared_ptr<IfcAlignment1x1Entity> >& map);
			virtual void setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self);
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcTendon"; }

			// IfcTendon -----------------------
			// attributes:
			std::shared_ptr<IfcTendonTypeEnum> m_PredefinedType;
			std::shared_ptr<IfcPositiveLengthMeasure> m_NominalDiameter;
			std::shared_ptr<IfcAreaMeasure> m_CrossSectionArea;
			std::shared_ptr<IfcForceMeasure> m_TensionForce;
			std::shared_ptr<IfcPressureMeasure> m_PreStress;
			std::shared_ptr<IfcNormalisedRatioMeasure> m_FrictionCoefficient;
			std::shared_ptr<IfcPositiveLengthMeasure> m_AnchorageSlip;
			std::shared_ptr<IfcPositiveLengthMeasure> m_MinCurvatureRadius;
		};
	}
}
