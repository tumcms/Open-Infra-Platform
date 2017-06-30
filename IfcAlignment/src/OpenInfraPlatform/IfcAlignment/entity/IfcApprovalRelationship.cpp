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
#include "include/IfcApproval.h"
#include "include/IfcApprovalRelationship.h"
#include "include/IfcLabel.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment
	{
		// ENTITY IfcApprovalRelationship 
		IfcApprovalRelationship::IfcApprovalRelationship() { m_entity_enum = IFCAPPROVALRELATIONSHIP; }
		IfcApprovalRelationship::IfcApprovalRelationship( int id ) { m_id = id; m_entity_enum = IFCAPPROVALRELATIONSHIP; }
		IfcApprovalRelationship::~IfcApprovalRelationship() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcApprovalRelationship::setEntity( shared_ptr<IfcAlignmentP6Entity> other_entity )
		{
			shared_ptr<IfcApprovalRelationship> other = dynamic_pointer_cast<IfcApprovalRelationship>(other_entity);
			if( !other) { return; }
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_RelatingApproval = other->m_RelatingApproval;
			m_RelatedApprovals = other->m_RelatedApprovals;
		}
		void IfcApprovalRelationship::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCAPPROVALRELATIONSHIP" << "(";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RelatingApproval ) { stream << "#" << m_RelatingApproval->getId(); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_RelatedApprovals );
			stream << ");";
		}
		void IfcApprovalRelationship::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcApprovalRelationship::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignmentP6Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<4 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcApprovalRelationship, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignmentP6Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>4 ){ std::cout << "Wrong parameter count for entity IfcApprovalRelationship, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Name = IfcLabel::readStepData( args[0] );
			m_Description = IfcText::readStepData( args[1] );
			readEntityReference( args[2], m_RelatingApproval, map );
			readEntityReferenceList( args[3], m_RelatedApprovals, map );
		}
		void IfcApprovalRelationship::setInverseCounterparts( shared_ptr<IfcAlignmentP6Entity> ptr_self_entity )
		{
			IfcResourceLevelRelationship::setInverseCounterparts( ptr_self_entity );
			shared_ptr<IfcApprovalRelationship> ptr_self = dynamic_pointer_cast<IfcApprovalRelationship>( ptr_self_entity );
			if( !ptr_self ) { throw IfcAlignmentP6Exception( "IfcApprovalRelationship::setInverseCounterparts: type mismatch" ); }
			for( int i=0; i<m_RelatedApprovals.size(); ++i )
			{
				if( m_RelatedApprovals[i] )
				{
					m_RelatedApprovals[i]->m_IsRelatedWith_inverse.push_back( ptr_self );
				}
			}
			if( m_RelatingApproval )
			{
				m_RelatingApproval->m_Relates_inverse.push_back( ptr_self );
			}
		}
		void IfcApprovalRelationship::unlinkSelf()
		{
			IfcResourceLevelRelationship::unlinkSelf();
			for( int i=0; i<m_RelatedApprovals.size(); ++i )
			{
				if( m_RelatedApprovals[i] )
				{
					std::vector<weak_ptr<IfcApprovalRelationship> >& IsRelatedWith_inverse = m_RelatedApprovals[i]->m_IsRelatedWith_inverse;
					std::vector<weak_ptr<IfcApprovalRelationship> >::iterator it_IsRelatedWith_inverse;
					for( it_IsRelatedWith_inverse = IsRelatedWith_inverse.begin(); it_IsRelatedWith_inverse != IsRelatedWith_inverse.end(); ++it_IsRelatedWith_inverse)
					{
						shared_ptr<IfcApprovalRelationship> self_candidate( *it_IsRelatedWith_inverse );
						if( self_candidate->getId() == this->getId() )
						{
							IsRelatedWith_inverse.erase( it_IsRelatedWith_inverse );
							break;
						}
					}
				}
			}
			if( m_RelatingApproval )
			{
				std::vector<weak_ptr<IfcApprovalRelationship> >& Relates_inverse = m_RelatingApproval->m_Relates_inverse;
				std::vector<weak_ptr<IfcApprovalRelationship> >::iterator it_Relates_inverse;
				for( it_Relates_inverse = Relates_inverse.begin(); it_Relates_inverse != Relates_inverse.end(); ++it_Relates_inverse)
				{
					shared_ptr<IfcApprovalRelationship> self_candidate( *it_Relates_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						Relates_inverse.erase( it_Relates_inverse );
						break;
					}
				}
			}
		}
	} // end namespace IfcAlignment
} // end namespace OpenInfraPlatform
