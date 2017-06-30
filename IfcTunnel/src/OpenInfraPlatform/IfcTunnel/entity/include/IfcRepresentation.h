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
#include "../../model/IfcTunnelObject.h"
#include "IfcLayeredItem.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		class IfcRepresentationContext;
		class IfcLabel;
		class IfcRepresentationItem;
		class IfcRepresentationMap;
		class IfcPresentationLayerAssignment;
		class IfcProductRepresentation;
		//ENTITY
		class IfcRepresentation : public IfcLayeredItem, public IfcTunnelEntity
		{
		public:
			IfcRepresentation();
			IfcRepresentation( int id );
			~IfcRepresentation();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity( shared_ptr<IfcTunnelEntity> other );
			virtual void getStepLine( std::stringstream& stream ) const;
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			virtual void readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcTunnelEntity> >& map );
			virtual void setInverseCounterparts( shared_ptr<IfcTunnelEntity> ptr_self );
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcRepresentation"; }


			// IfcRepresentation -----------------------------------------------------------
			// attributes:
			shared_ptr<IfcRepresentationContext>						m_ContextOfItems;
			shared_ptr<IfcLabel>										m_RepresentationIdentifier;	//optional
			shared_ptr<IfcLabel>										m_RepresentationType;		//optional
			std::vector<shared_ptr<IfcRepresentationItem> >			m_Items;
			// inverse attributes:
			std::vector<weak_ptr<IfcRepresentationMap> >				m_RepresentationMap_inverse;
			std::vector<weak_ptr<IfcPresentationLayerAssignment> >	m_LayerAssignments_inverse;
			std::vector<weak_ptr<IfcProductRepresentation> >			m_OfProductRepresentation_inverse;
		};
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform

