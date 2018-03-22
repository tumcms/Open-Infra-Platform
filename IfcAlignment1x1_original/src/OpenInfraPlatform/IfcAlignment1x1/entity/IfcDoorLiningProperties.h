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
#include "IfcPreDefinedPropertySet.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		class IfcPositiveLengthMeasure;
		class IfcNonNegativeLengthMeasure;
		class IfcPositiveLengthMeasure;
		class IfcNonNegativeLengthMeasure;
		class IfcNonNegativeLengthMeasure;
		class IfcLengthMeasure;
		class IfcLengthMeasure;
		class IfcLengthMeasure;
		class IfcPositiveLengthMeasure;
		class IfcPositiveLengthMeasure;
		class IfcShapeAspect;
		class IfcLengthMeasure;
		class IfcLengthMeasure;
		// ENTITY IfcDoorLiningProperties
		class IfcDoorLiningProperties : public IfcPreDefinedPropertySet
		{
		public:
			IfcDoorLiningProperties();
			IfcDoorLiningProperties( int id );
			~IfcDoorLiningProperties();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity(std::shared_ptr<IfcAlignment1x1Entity> other);
			virtual void getStepLine(std::stringstream& stream) const;
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			virtual void readStepData(std::vector<std::string>& args, const std::map<int, shared_ptr<IfcAlignment1x1Entity> >& map);
			virtual void setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self);
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcDoorLiningProperties"; }

			// IfcDoorLiningProperties -----------------------
			// attributes:
			std::shared_ptr<IfcPositiveLengthMeasure> m_LiningDepth;
			std::shared_ptr<IfcNonNegativeLengthMeasure> m_LiningThickness;
			std::shared_ptr<IfcPositiveLengthMeasure> m_ThresholdDepth;
			std::shared_ptr<IfcNonNegativeLengthMeasure> m_ThresholdThickness;
			std::shared_ptr<IfcNonNegativeLengthMeasure> m_TransomThickness;
			std::shared_ptr<IfcLengthMeasure> m_TransomOffset;
			std::shared_ptr<IfcLengthMeasure> m_LiningOffset;
			std::shared_ptr<IfcLengthMeasure> m_ThresholdOffset;
			std::shared_ptr<IfcPositiveLengthMeasure> m_CasingThickness;
			std::shared_ptr<IfcPositiveLengthMeasure> m_CasingDepth;
			std::shared_ptr<IfcShapeAspect> m_ShapeAspectStyle;
			std::shared_ptr<IfcLengthMeasure> m_LiningToPanelOffsetX;
			std::shared_ptr<IfcLengthMeasure> m_LiningToPanelOffsetY;
		};
	}
}
