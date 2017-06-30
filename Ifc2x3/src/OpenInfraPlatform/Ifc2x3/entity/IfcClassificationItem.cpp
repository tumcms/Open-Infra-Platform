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
#include "include/IfcClassification.h"
#include "include/IfcClassificationItem.h"
#include "include/IfcClassificationItemRelationship.h"
#include "include/IfcClassificationNotationFacet.h"
#include "include/IfcLabel.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcClassificationItem 
		IfcClassificationItem::IfcClassificationItem() { m_entity_enum = IFCCLASSIFICATIONITEM; }
		IfcClassificationItem::IfcClassificationItem( int id ) { m_id = id; m_entity_enum = IFCCLASSIFICATIONITEM; }
		IfcClassificationItem::~IfcClassificationItem() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcClassificationItem::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcClassificationItem> other = dynamic_pointer_cast<IfcClassificationItem>(other_entity);
			if( !other) { return; }
			m_Notation = other->m_Notation;
			m_ItemOf = other->m_ItemOf;
			m_Title = other->m_Title;
		}
		void IfcClassificationItem::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCCLASSIFICATIONITEM" << "(";
			if( m_Notation ) { stream << "#" << m_Notation->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_ItemOf ) { stream << "#" << m_ItemOf->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Title ) { m_Title->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcClassificationItem::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcClassificationItem::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<3 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcClassificationItem, expecting 3, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>3 ){ std::cout << "Wrong parameter count for entity IfcClassificationItem, expecting 3, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readEntityReference( args[0], m_Notation, map );
			readEntityReference( args[1], m_ItemOf, map );
			m_Title = IfcLabel::readStepData( args[2] );
		}
		void IfcClassificationItem::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			shared_ptr<IfcClassificationItem> ptr_self = dynamic_pointer_cast<IfcClassificationItem>( ptr_self_entity );
			if( !ptr_self ) { throw Ifc2x3Exception( "IfcClassificationItem::setInverseCounterparts: type mismatch" ); }
			if( m_ItemOf )
			{
				m_ItemOf->m_Contains_inverse.push_back( ptr_self );
			}
		}
		void IfcClassificationItem::unlinkSelf()
		{
			if( m_ItemOf )
			{
				std::vector<weak_ptr<IfcClassificationItem> >& Contains_inverse = m_ItemOf->m_Contains_inverse;
				std::vector<weak_ptr<IfcClassificationItem> >::iterator it_Contains_inverse;
				for( it_Contains_inverse = Contains_inverse.begin(); it_Contains_inverse != Contains_inverse.end(); ++it_Contains_inverse)
				{
					shared_ptr<IfcClassificationItem> self_candidate( *it_Contains_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						Contains_inverse.erase( it_Contains_inverse );
						break;
					}
				}
			}
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
