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
#include "include/IfcContext.h"
#include "include/IfcDefinitionSelect.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcObjectDefinition.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcPropertyDefinition.h"
#include "include/IfcRelDeclares.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		// ENTITY IfcRelDeclares 
		IfcRelDeclares::IfcRelDeclares() { m_entity_enum = IFCRELDECLARES; }
		IfcRelDeclares::IfcRelDeclares( int id ) { m_id = id; m_entity_enum = IFCRELDECLARES; }
		IfcRelDeclares::~IfcRelDeclares() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcRelDeclares::setEntity( shared_ptr<IfcTunnelEntity> other_entity )
		{
			shared_ptr<IfcRelDeclares> other = dynamic_pointer_cast<IfcRelDeclares>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_RelatingContext = other->m_RelatingContext;
			m_RelatedDefinitions = other->m_RelatedDefinitions;
		}
		void IfcRelDeclares::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCRELDECLARES" << "(";
			if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RelatingContext ) { stream << "#" << m_RelatingContext->getId(); } else { stream << "$"; }
			stream << ",";
			writeTypeList( stream, m_RelatedDefinitions, true );
			stream << ");";
		}
		void IfcRelDeclares::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcRelDeclares::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcTunnelEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<6 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcRelDeclares, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcTunnelException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>6 ){ std::cout << "Wrong parameter count for entity IfcRelDeclares, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			readEntityReference( args[4], m_RelatingContext, map );
			readSelectList( args[5], m_RelatedDefinitions, map );
		}
		void IfcRelDeclares::setInverseCounterparts( shared_ptr<IfcTunnelEntity> ptr_self_entity )
		{
			IfcRelationship::setInverseCounterparts( ptr_self_entity );
			shared_ptr<IfcRelDeclares> ptr_self = dynamic_pointer_cast<IfcRelDeclares>( ptr_self_entity );
			if( !ptr_self ) { throw IfcTunnelException( "IfcRelDeclares::setInverseCounterparts: type mismatch" ); }
			for( int i=0; i<m_RelatedDefinitions.size(); ++i )
			{
				shared_ptr<IfcObjectDefinition>  RelatedDefinitions_IfcObjectDefinition = dynamic_pointer_cast<IfcObjectDefinition>( m_RelatedDefinitions[i] );
				if( RelatedDefinitions_IfcObjectDefinition )
				{
					RelatedDefinitions_IfcObjectDefinition->m_HasContext_inverse.push_back( ptr_self );
				}
				shared_ptr<IfcPropertyDefinition>  RelatedDefinitions_IfcPropertyDefinition = dynamic_pointer_cast<IfcPropertyDefinition>( m_RelatedDefinitions[i] );
				if( RelatedDefinitions_IfcPropertyDefinition )
				{
					RelatedDefinitions_IfcPropertyDefinition->m_HasContext_inverse.push_back( ptr_self );
				}
			}
			if( m_RelatingContext )
			{
				m_RelatingContext->m_Declares_inverse.push_back( ptr_self );
			}
		}
		void IfcRelDeclares::unlinkSelf()
		{
			IfcRelationship::unlinkSelf();
			for( int i=0; i<m_RelatedDefinitions.size(); ++i )
			{
				shared_ptr<IfcObjectDefinition>  RelatedDefinitions_IfcObjectDefinition = dynamic_pointer_cast<IfcObjectDefinition>( m_RelatedDefinitions[i] );
				if( RelatedDefinitions_IfcObjectDefinition )
				{
					std::vector<weak_ptr<IfcRelDeclares> >& HasContext_inverse = RelatedDefinitions_IfcObjectDefinition->m_HasContext_inverse;
					std::vector<weak_ptr<IfcRelDeclares> >::iterator it_HasContext_inverse;
					for( it_HasContext_inverse = HasContext_inverse.begin(); it_HasContext_inverse != HasContext_inverse.end(); ++it_HasContext_inverse)
					{
						shared_ptr<IfcRelDeclares> self_candidate( *it_HasContext_inverse );
						if( self_candidate->getId() == this->getId() )
						{
							HasContext_inverse.erase( it_HasContext_inverse );
							break;
						}
					}
				}
				shared_ptr<IfcPropertyDefinition>  RelatedDefinitions_IfcPropertyDefinition = dynamic_pointer_cast<IfcPropertyDefinition>( m_RelatedDefinitions[i] );
				if( RelatedDefinitions_IfcPropertyDefinition )
				{
					std::vector<weak_ptr<IfcRelDeclares> >& HasContext_inverse = RelatedDefinitions_IfcPropertyDefinition->m_HasContext_inverse;
					std::vector<weak_ptr<IfcRelDeclares> >::iterator it_HasContext_inverse;
					for( it_HasContext_inverse = HasContext_inverse.begin(); it_HasContext_inverse != HasContext_inverse.end(); ++it_HasContext_inverse)
					{
						shared_ptr<IfcRelDeclares> self_candidate( *it_HasContext_inverse );
						if( self_candidate->getId() == this->getId() )
						{
							HasContext_inverse.erase( it_HasContext_inverse );
							break;
						}
					}
				}
			}
			if( m_RelatingContext )
			{
				std::vector<weak_ptr<IfcRelDeclares> >& Declares_inverse = m_RelatingContext->m_Declares_inverse;
				std::vector<weak_ptr<IfcRelDeclares> >::iterator it_Declares_inverse;
				for( it_Declares_inverse = Declares_inverse.begin(); it_Declares_inverse != Declares_inverse.end(); ++it_Declares_inverse)
				{
					shared_ptr<IfcRelDeclares> self_candidate( *it_Declares_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						Declares_inverse.erase( it_Declares_inverse );
						break;
					}
				}
			}
		}
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform
