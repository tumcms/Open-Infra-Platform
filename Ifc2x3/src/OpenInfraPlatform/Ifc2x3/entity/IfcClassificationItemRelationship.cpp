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

#include "model/Ifc2x3Exception.h"
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "Ifc2x3EntityEnums.h"
#include "include/IfcClassificationItem.h"
#include "include/IfcClassificationItemRelationship.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcClassificationItemRelationship 
		IfcClassificationItemRelationship::IfcClassificationItemRelationship() { m_entity_enum = IFCCLASSIFICATIONITEMRELATIONSHIP; }
		IfcClassificationItemRelationship::IfcClassificationItemRelationship( int id ) { m_id = id; m_entity_enum = IFCCLASSIFICATIONITEMRELATIONSHIP; }
		IfcClassificationItemRelationship::~IfcClassificationItemRelationship() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcClassificationItemRelationship::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcClassificationItemRelationship> other = dynamic_pointer_cast<IfcClassificationItemRelationship>(other_entity);
			if( !other) { return; }
			m_RelatingItem = other->m_RelatingItem;
			m_RelatedItems = other->m_RelatedItems;
		}
		void IfcClassificationItemRelationship::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCCLASSIFICATIONITEMRELATIONSHIP" << "(";
			if( m_RelatingItem ) { stream << "#" << m_RelatingItem->getId(); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_RelatedItems );
			stream << ");";
		}
		void IfcClassificationItemRelationship::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcClassificationItemRelationship::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<2 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcClassificationItemRelationship, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>2 ){ std::cout << "Wrong parameter count for entity IfcClassificationItemRelationship, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readEntityReference( args[0], m_RelatingItem, map );
			readEntityReferenceList( args[1], m_RelatedItems, map );
		}
		void IfcClassificationItemRelationship::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			shared_ptr<IfcClassificationItemRelationship> ptr_self = dynamic_pointer_cast<IfcClassificationItemRelationship>( ptr_self_entity );
			if( !ptr_self ) { throw Ifc2x3Exception( "IfcClassificationItemRelationship::setInverseCounterparts: type mismatch" ); }
			for( int i=0; i<m_RelatedItems.size(); ++i )
			{
				if( m_RelatedItems[i] )
				{
					m_RelatedItems[i]->m_IsClassifiedItemIn_inverse.push_back( ptr_self );
				}
			}
			if( m_RelatingItem )
			{
				m_RelatingItem->m_IsClassifyingItemIn_inverse.push_back( ptr_self );
			}
		}
		void IfcClassificationItemRelationship::unlinkSelf()
		{
			for( int i=0; i<m_RelatedItems.size(); ++i )
			{
				if( m_RelatedItems[i] )
				{
					std::vector<weak_ptr<IfcClassificationItemRelationship> >& IsClassifiedItemIn_inverse = m_RelatedItems[i]->m_IsClassifiedItemIn_inverse;
					std::vector<weak_ptr<IfcClassificationItemRelationship> >::iterator it_IsClassifiedItemIn_inverse;
					for( it_IsClassifiedItemIn_inverse = IsClassifiedItemIn_inverse.begin(); it_IsClassifiedItemIn_inverse != IsClassifiedItemIn_inverse.end(); ++it_IsClassifiedItemIn_inverse)
					{
						shared_ptr<IfcClassificationItemRelationship> self_candidate( *it_IsClassifiedItemIn_inverse );
						if( self_candidate->getId() == this->getId() )
						{
							IsClassifiedItemIn_inverse.erase( it_IsClassifiedItemIn_inverse );
							break;
						}
					}
				}
			}
			if( m_RelatingItem )
			{
				std::vector<weak_ptr<IfcClassificationItemRelationship> >& IsClassifyingItemIn_inverse = m_RelatingItem->m_IsClassifyingItemIn_inverse;
				std::vector<weak_ptr<IfcClassificationItemRelationship> >::iterator it_IsClassifyingItemIn_inverse;
				for( it_IsClassifyingItemIn_inverse = IsClassifyingItemIn_inverse.begin(); it_IsClassifyingItemIn_inverse != IsClassifyingItemIn_inverse.end(); ++it_IsClassifyingItemIn_inverse)
				{
					shared_ptr<IfcClassificationItemRelationship> self_candidate( *it_IsClassifyingItemIn_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						IsClassifyingItemIn_inverse.erase( it_IsClassifyingItemIn_inverse );
						break;
					}
				}
			}
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
