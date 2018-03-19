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
#include "IfcBoundedSurface.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		class IfcSurface;
		class IfcParameterValue;
		class IfcParameterValue;
		class IfcParameterValue;
		class IfcParameterValue;
		class IfcBoolean;
		class IfcBoolean;
		// ENTITY IfcRectangularTrimmedSurface
		class IfcRectangularTrimmedSurface : public IfcBoundedSurface
		{
		public:
			IfcRectangularTrimmedSurface();
			IfcRectangularTrimmedSurface( int id );
			~IfcRectangularTrimmedSurface();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity(std::shared_ptr<IfcAlignment1x1Entity> other);
			virtual void getStepLine(std::stringstream& stream) const;
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			virtual void readStepData(std::vector<std::string>& args, const std::map<int, shared_ptr<IfcAlignment1x1Entity> >& map);
			virtual void setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self);
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcRectangularTrimmedSurface"; }

			// IfcRectangularTrimmedSurface -----------------------
			// attributes:
			std::shared_ptr<IfcSurface> m_BasisSurface;
			std::shared_ptr<IfcParameterValue> m_U1;
			std::shared_ptr<IfcParameterValue> m_V1;
			std::shared_ptr<IfcParameterValue> m_U2;
			std::shared_ptr<IfcParameterValue> m_V2;
			std::shared_ptr<IfcBoolean> m_Usense;
			std::shared_ptr<IfcBoolean> m_Vsense;
		};
	}
}
