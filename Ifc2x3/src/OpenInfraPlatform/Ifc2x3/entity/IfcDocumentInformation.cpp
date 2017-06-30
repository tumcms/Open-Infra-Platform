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
#include "include/IfcActorSelect.h"
#include "include/IfcCalendarDate.h"
#include "include/IfcDateAndTime.h"
#include "include/IfcDocumentConfidentialityEnum.h"
#include "include/IfcDocumentElectronicFormat.h"
#include "include/IfcDocumentInformation.h"
#include "include/IfcDocumentInformationRelationship.h"
#include "include/IfcDocumentReference.h"
#include "include/IfcDocumentStatusEnum.h"
#include "include/IfcIdentifier.h"
#include "include/IfcLabel.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcDocumentInformation 
		IfcDocumentInformation::IfcDocumentInformation() { m_entity_enum = IFCDOCUMENTINFORMATION; }
		IfcDocumentInformation::IfcDocumentInformation( int id ) { m_id = id; m_entity_enum = IFCDOCUMENTINFORMATION; }
		IfcDocumentInformation::~IfcDocumentInformation() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcDocumentInformation::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcDocumentInformation> other = dynamic_pointer_cast<IfcDocumentInformation>(other_entity);
			if( !other) { return; }
			m_DocumentId = other->m_DocumentId;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_DocumentReferences = other->m_DocumentReferences;
			m_Purpose = other->m_Purpose;
			m_IntendedUse = other->m_IntendedUse;
			m_Scope = other->m_Scope;
			m_Revision = other->m_Revision;
			m_DocumentOwner = other->m_DocumentOwner;
			m_Editors = other->m_Editors;
			m_CreationTime = other->m_CreationTime;
			m_LastRevisionTime = other->m_LastRevisionTime;
			m_ElectronicFormat = other->m_ElectronicFormat;
			m_ValidFrom = other->m_ValidFrom;
			m_ValidUntil = other->m_ValidUntil;
			m_Confidentiality = other->m_Confidentiality;
			m_Status = other->m_Status;
		}
		void IfcDocumentInformation::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCDOCUMENTINFORMATION" << "(";
			if( m_DocumentId ) { m_DocumentId->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_DocumentReferences );
			stream << ",";
			if( m_Purpose ) { m_Purpose->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_IntendedUse ) { m_IntendedUse->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Scope ) { m_Scope->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Revision ) { m_Revision->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_DocumentOwner ) { m_DocumentOwner->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			writeTypeList( stream, m_Editors, true );
			stream << ",";
			if( m_CreationTime ) { stream << "#" << m_CreationTime->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_LastRevisionTime ) { stream << "#" << m_LastRevisionTime->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_ElectronicFormat ) { stream << "#" << m_ElectronicFormat->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_ValidFrom ) { stream << "#" << m_ValidFrom->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_ValidUntil ) { stream << "#" << m_ValidUntil->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Confidentiality ) { m_Confidentiality->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Status ) { m_Status->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcDocumentInformation::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcDocumentInformation::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<17 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcDocumentInformation, expecting 17, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>17 ){ std::cout << "Wrong parameter count for entity IfcDocumentInformation, expecting 17, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_DocumentId = IfcIdentifier::readStepData( args[0] );
			m_Name = IfcLabel::readStepData( args[1] );
			m_Description = IfcText::readStepData( args[2] );
			readEntityReferenceList( args[3], m_DocumentReferences, map );
			m_Purpose = IfcText::readStepData( args[4] );
			m_IntendedUse = IfcText::readStepData( args[5] );
			m_Scope = IfcText::readStepData( args[6] );
			m_Revision = IfcLabel::readStepData( args[7] );
			m_DocumentOwner = IfcActorSelect::readStepData( args[8], map );
			readSelectList( args[9], m_Editors, map );
			readEntityReference( args[10], m_CreationTime, map );
			readEntityReference( args[11], m_LastRevisionTime, map );
			readEntityReference( args[12], m_ElectronicFormat, map );
			readEntityReference( args[13], m_ValidFrom, map );
			readEntityReference( args[14], m_ValidUntil, map );
			m_Confidentiality = IfcDocumentConfidentialityEnum::readStepData( args[15] );
			m_Status = IfcDocumentStatusEnum::readStepData( args[16] );
		}
		void IfcDocumentInformation::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			shared_ptr<IfcDocumentInformation> ptr_self = dynamic_pointer_cast<IfcDocumentInformation>( ptr_self_entity );
			if( !ptr_self ) { throw Ifc2x3Exception( "IfcDocumentInformation::setInverseCounterparts: type mismatch" ); }
			for( int i=0; i<m_DocumentReferences.size(); ++i )
			{
				if( m_DocumentReferences[i] )
				{
					m_DocumentReferences[i]->m_ReferenceToDocument_inverse.push_back( ptr_self );
				}
			}
		}
		void IfcDocumentInformation::unlinkSelf()
		{
			for( int i=0; i<m_DocumentReferences.size(); ++i )
			{
				if( m_DocumentReferences[i] )
				{
					std::vector<weak_ptr<IfcDocumentInformation> >& ReferenceToDocument_inverse = m_DocumentReferences[i]->m_ReferenceToDocument_inverse;
					std::vector<weak_ptr<IfcDocumentInformation> >::iterator it_ReferenceToDocument_inverse;
					for( it_ReferenceToDocument_inverse = ReferenceToDocument_inverse.begin(); it_ReferenceToDocument_inverse != ReferenceToDocument_inverse.end(); ++it_ReferenceToDocument_inverse)
					{
						shared_ptr<IfcDocumentInformation> self_candidate( *it_ReferenceToDocument_inverse );
						if( self_candidate->getId() == this->getId() )
						{
							ReferenceToDocument_inverse.erase( it_ReferenceToDocument_inverse );
							break;
						}
					}
				}
			}
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
