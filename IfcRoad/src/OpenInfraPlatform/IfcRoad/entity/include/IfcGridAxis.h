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
#include "OpenInfraPlatform/IfcRoad/model/shared_ptr.h"
#include "OpenInfraPlatform/IfcRoad/model/IfcRoadObject.h"

namespace OpenInfraPlatform
{
	namespace IfcRoad
	{
		class IfcLabel;
		class IfcCurve;
		class IfcBoolean;
		class IfcGrid;
		class IfcVirtualGridIntersection;
		//ENTITY
		class IfcGridAxis : public IfcRoadEntity
		{
		public:
			IfcGridAxis();
			IfcGridAxis( int id );
			~IfcGridAxis();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity( shared_ptr<IfcRoadEntity> other );
			virtual void getStepLine( std::stringstream& stream ) const;
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			virtual void readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcRoadEntity> >& map );
			virtual void setInverseCounterparts( shared_ptr<IfcRoadEntity> ptr_self );
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcGridAxis"; }


			// IfcGridAxis -----------------------------------------------------------
			// attributes:
			shared_ptr<IfcLabel>									m_AxisTag;					//optional
			shared_ptr<IfcCurve>									m_AxisCurve;
			shared_ptr<IfcBoolean>								m_SameSense;
			// inverse attributes:
			std::vector<weak_ptr<IfcGrid> >						m_PartOfW_inverse;
			std::vector<weak_ptr<IfcGrid> >						m_PartOfV_inverse;
			std::vector<weak_ptr<IfcGrid> >						m_PartOfU_inverse;
			std::vector<weak_ptr<IfcVirtualGridIntersection> >	m_HasIntersections_inverse;
		};
	} // end namespace IfcRoad
} // end namespace OpenInfraPlatform

