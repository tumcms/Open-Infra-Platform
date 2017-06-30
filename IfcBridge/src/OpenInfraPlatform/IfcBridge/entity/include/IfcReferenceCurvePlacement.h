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
#include "../../model/IfcBridgeObject.h"
#include "IfcReferencePlacement.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		class IfcLengthMeasure;
		class IfcDirection;
		class IfcReferenceCurvePlacementSystem;
		//ENTITY
		class IfcReferenceCurvePlacement : public IfcReferencePlacement
		{
		public:
			IfcReferenceCurvePlacement();
			IfcReferenceCurvePlacement( int id );
			~IfcReferenceCurvePlacement();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity( shared_ptr<IfcBridgeEntity> other );
			virtual void getStepLine( std::stringstream& stream ) const;
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			virtual void readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcBridgeEntity> >& map );
			virtual void setInverseCounterparts( shared_ptr<IfcBridgeEntity> ptr_self );
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcReferenceCurvePlacement"; }


			// IfcObjectPlacement -----------------------------------------------------------
			// inverse attributes:
			//  std::vector<weak_ptr<IfcProduct> >			m_PlacesObject_inverse;
			//  std::vector<weak_ptr<IfcLocalPlacement> >	m_ReferencedByPlacements_inverse;

			// IfcReferencePlacement -----------------------------------------------------------

			// IfcReferenceCurvePlacement -----------------------------------------------------------
			// attributes:
			shared_ptr<IfcLengthMeasure>					m_CurvilinearAbscissa;
			shared_ptr<IfcDirection>						m_Axis;
			shared_ptr<IfcDirection>						m_RefDirection;
			shared_ptr<IfcReferenceCurvePlacementSystem>	m_RelativeTo;
		};
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform

