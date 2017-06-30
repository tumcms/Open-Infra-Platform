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

#include "OpenInfraPlatform/IfcAlignment/model/IfcAlignmentP6Exception.h"
#include "OpenInfraPlatform/IfcAlignment/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment/writer/WriterUtil.h"
#include "OpenInfraPlatform/IfcAlignment/IfcAlignmentP6EntityEnums.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcObjectDefinition.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcRelAggregates.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment
	{
		// ENTITY IfcRelAggregates 
		IfcRelAggregates::IfcRelAggregates() { m_entity_enum = IFCRELAGGREGATES; }
		IfcRelAggregates::IfcRelAggregates( int id ) { m_id = id; m_entity_enum = IFCRELAGGREGATES; }
		IfcRelAggregates::~IfcRelAggregates() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcRelAggregates::setEntity( shared_ptr<IfcAlignmentP6Entity> other_entity )
		{
			shared_ptr<IfcRelAggregates> other = dynamic_pointer_cast<IfcRelAggregates>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_RelatingObject = other->m_RelatingObject;
			m_RelatedObjects = other->m_RelatedObjects;
		}
		void IfcRelAggregates::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCRELAGGREGATES" << "(";
			if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RelatingObject ) { stream << "#" << m_RelatingObject->getId(); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_RelatedObjects );
			stream << ");";
		}
		void IfcRelAggregates::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcRelAggregates::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignmentP6Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<6 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcRelAggregates, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignmentP6Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>6 ){ std::cout << "Wrong parameter count for entity IfcRelAggregates, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			readEntityReference( args[4], m_RelatingObject, map );
			readEntityReferenceList( args[5], m_RelatedObjects, map );
		}
		void IfcRelAggregates::setInverseCounterparts( shared_ptr<IfcAlignmentP6Entity> ptr_self_entity )
		{
			IfcRelDecomposes::setInverseCounterparts( ptr_self_entity );
			shared_ptr<IfcRelAggregates> ptr_self = dynamic_pointer_cast<IfcRelAggregates>( ptr_self_entity );
			if( !ptr_self ) { throw IfcAlignmentP6Exception( "IfcRelAggregates::setInverseCounterparts: type mismatch" ); }
			for( int i=0; i<m_RelatedObjects.size(); ++i )
			{
				if( m_RelatedObjects[i] )
				{
					m_RelatedObjects[i]->m_Decomposes_inverse.push_back( ptr_self );
				}
			}
			if( m_RelatingObject )
			{
				m_RelatingObject->m_IsDecomposedBy_inverse.push_back( ptr_self );
			}
		}
		void IfcRelAggregates::unlinkSelf()
		{
			IfcRelDecomposes::unlinkSelf();
			for( int i=0; i<m_RelatedObjects.size(); ++i )
			{
				if( m_RelatedObjects[i] )
				{
					std::vector<weak_ptr<IfcRelAggregates> >& Decomposes_inverse = m_RelatedObjects[i]->m_Decomposes_inverse;
					std::vector<weak_ptr<IfcRelAggregates> >::iterator it_Decomposes_inverse;
					for( it_Decomposes_inverse = Decomposes_inverse.begin(); it_Decomposes_inverse != Decomposes_inverse.end(); ++it_Decomposes_inverse)
					{
						shared_ptr<IfcRelAggregates> self_candidate( *it_Decomposes_inverse );
						if( self_candidate->getId() == this->getId() )
						{
							Decomposes_inverse.erase( it_Decomposes_inverse );
							break;
						}
					}
				}
			}
			if( m_RelatingObject )
			{
				std::vector<weak_ptr<IfcRelAggregates> >& IsDecomposedBy_inverse = m_RelatingObject->m_IsDecomposedBy_inverse;
				std::vector<weak_ptr<IfcRelAggregates> >::iterator it_IsDecomposedBy_inverse;
				for( it_IsDecomposedBy_inverse = IsDecomposedBy_inverse.begin(); it_IsDecomposedBy_inverse != IsDecomposedBy_inverse.end(); ++it_IsDecomposedBy_inverse)
				{
					shared_ptr<IfcRelAggregates> self_candidate( *it_IsDecomposedBy_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						IsDecomposedBy_inverse.erase( it_IsDecomposedBy_inverse );
						break;
					}
				}
			}
		}
	} // end namespace IfcAlignment
} // end namespace OpenInfraPlatform
