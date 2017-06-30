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

#include <sstream>
#include <limits>

#include "model/IfcTunnelException.h"
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "IfcTunnelEntityEnums.h"
#include "include/IfcIdentifier.h"
#include "include/IfcLabel.h"
#include "include/IfcLayeredItem.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcRepresentation.h"
#include "include/IfcRepresentationItem.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		// ENTITY IfcPresentationLayerAssignment 
		IfcPresentationLayerAssignment::IfcPresentationLayerAssignment() { m_entity_enum = IFCPRESENTATIONLAYERASSIGNMENT; }
		IfcPresentationLayerAssignment::IfcPresentationLayerAssignment( int id ) { m_id = id; m_entity_enum = IFCPRESENTATIONLAYERASSIGNMENT; }
		IfcPresentationLayerAssignment::~IfcPresentationLayerAssignment() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcPresentationLayerAssignment::setEntity( shared_ptr<IfcTunnelEntity> other_entity )
		{
			shared_ptr<IfcPresentationLayerAssignment> other = dynamic_pointer_cast<IfcPresentationLayerAssignment>(other_entity);
			if( !other) { return; }
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_AssignedItems = other->m_AssignedItems;
			m_Identifier = other->m_Identifier;
		}
		void IfcPresentationLayerAssignment::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCPRESENTATIONLAYERASSIGNMENT" << "(";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeTypeList( stream, m_AssignedItems, true );
			stream << ",";
			if( m_Identifier ) { m_Identifier->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcPresentationLayerAssignment::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcPresentationLayerAssignment::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcTunnelEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<4 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcPresentationLayerAssignment, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcTunnelException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>4 ){ std::cout << "Wrong parameter count for entity IfcPresentationLayerAssignment, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Name = IfcLabel::readStepData( args[0] );
			m_Description = IfcText::readStepData( args[1] );
			readSelectList( args[2], m_AssignedItems, map );
			m_Identifier = IfcIdentifier::readStepData( args[3] );
		}
		void IfcPresentationLayerAssignment::setInverseCounterparts( shared_ptr<IfcTunnelEntity> ptr_self_entity )
		{
			shared_ptr<IfcPresentationLayerAssignment> ptr_self = dynamic_pointer_cast<IfcPresentationLayerAssignment>( ptr_self_entity );
			if( !ptr_self ) { throw IfcTunnelException( "IfcPresentationLayerAssignment::setInverseCounterparts: type mismatch" ); }
			for( int i=0; i<m_AssignedItems.size(); ++i )
			{
				shared_ptr<IfcRepresentation>  AssignedItems_IfcRepresentation = dynamic_pointer_cast<IfcRepresentation>( m_AssignedItems[i] );
				if( AssignedItems_IfcRepresentation )
				{
					AssignedItems_IfcRepresentation->m_LayerAssignments_inverse.push_back( ptr_self );
				}
				shared_ptr<IfcRepresentationItem>  AssignedItems_IfcRepresentationItem = dynamic_pointer_cast<IfcRepresentationItem>( m_AssignedItems[i] );
				if( AssignedItems_IfcRepresentationItem )
				{
					AssignedItems_IfcRepresentationItem->m_LayerAssignment_inverse.push_back( ptr_self );
				}
			}
		}
		void IfcPresentationLayerAssignment::unlinkSelf()
		{
			for( int i=0; i<m_AssignedItems.size(); ++i )
			{
				shared_ptr<IfcRepresentation>  AssignedItems_IfcRepresentation = dynamic_pointer_cast<IfcRepresentation>( m_AssignedItems[i] );
				if( AssignedItems_IfcRepresentation )
				{
					std::vector<weak_ptr<IfcPresentationLayerAssignment> >& LayerAssignments_inverse = AssignedItems_IfcRepresentation->m_LayerAssignments_inverse;
					std::vector<weak_ptr<IfcPresentationLayerAssignment> >::iterator it_LayerAssignments_inverse;
					for( it_LayerAssignments_inverse = LayerAssignments_inverse.begin(); it_LayerAssignments_inverse != LayerAssignments_inverse.end(); ++it_LayerAssignments_inverse)
					{
						shared_ptr<IfcPresentationLayerAssignment> self_candidate( *it_LayerAssignments_inverse );
						if( self_candidate->getId() == this->getId() )
						{
							LayerAssignments_inverse.erase( it_LayerAssignments_inverse );
							break;
						}
					}
				}
				shared_ptr<IfcRepresentationItem>  AssignedItems_IfcRepresentationItem = dynamic_pointer_cast<IfcRepresentationItem>( m_AssignedItems[i] );
				if( AssignedItems_IfcRepresentationItem )
				{
					std::vector<weak_ptr<IfcPresentationLayerAssignment> >& LayerAssignment_inverse = AssignedItems_IfcRepresentationItem->m_LayerAssignment_inverse;
					std::vector<weak_ptr<IfcPresentationLayerAssignment> >::iterator it_LayerAssignment_inverse;
					for( it_LayerAssignment_inverse = LayerAssignment_inverse.begin(); it_LayerAssignment_inverse != LayerAssignment_inverse.end(); ++it_LayerAssignment_inverse)
					{
						shared_ptr<IfcPresentationLayerAssignment> self_candidate( *it_LayerAssignment_inverse );
						if( self_candidate->getId() == this->getId() )
						{
							LayerAssignment_inverse.erase( it_LayerAssignment_inverse );
							break;
						}
					}
				}
			}
		}
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform
