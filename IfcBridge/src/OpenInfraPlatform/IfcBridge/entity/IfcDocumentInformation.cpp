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

#include "model/IfcBridgeException.h"
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "IfcBridgeEntityEnums.h"
#include "include/IfcActorSelect.h"
#include "include/IfcDate.h"
#include "include/IfcDateTime.h"
#include "include/IfcDocumentConfidentialityEnum.h"
#include "include/IfcDocumentElectronicFormat.h"
#include "include/IfcDocumentInformation.h"
#include "include/IfcDocumentInformationRelationship.h"
#include "include/IfcDocumentReference.h"
#include "include/IfcDocumentStatusEnum.h"
#include "include/IfcIdentifier.h"
#include "include/IfcLabel.h"
#include "include/IfcRelAssociatesDocument.h"
#include "include/IfcText.h"
#include "include/IfcURIReference.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// ENTITY IfcDocumentInformation 
		IfcDocumentInformation::IfcDocumentInformation() { m_entity_enum = IFCDOCUMENTINFORMATION; }
		IfcDocumentInformation::IfcDocumentInformation( int id ) { m_id = id; m_entity_enum = IFCDOCUMENTINFORMATION; }
		IfcDocumentInformation::~IfcDocumentInformation() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcDocumentInformation::setEntity( shared_ptr<IfcBridgeEntity> other_entity )
		{
			shared_ptr<IfcDocumentInformation> other = dynamic_pointer_cast<IfcDocumentInformation>(other_entity);
			if( !other) { return; }
			m_DocumentId = other->m_DocumentId;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
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
			m_Location = other->m_Location;
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
			if( m_CreationTime ) { m_CreationTime->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LastRevisionTime ) { m_LastRevisionTime->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ElectronicFormat ) { stream << "#" << m_ElectronicFormat->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_ValidFrom ) { m_ValidFrom->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ValidUntil ) { m_ValidUntil->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Confidentiality ) { m_Confidentiality->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Status ) { m_Status->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Location ) { m_Location->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcDocumentInformation::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcDocumentInformation::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcBridgeEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<17 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcDocumentInformation, expecting 17, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcBridgeException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>17 ){ std::cout << "Wrong parameter count for entity IfcDocumentInformation, expecting 17, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_DocumentId = IfcIdentifier::readStepData( args[0] );
			m_Name = IfcLabel::readStepData( args[1] );
			m_Description = IfcText::readStepData( args[2] );
			m_Purpose = IfcText::readStepData( args[3] );
			m_IntendedUse = IfcText::readStepData( args[4] );
			m_Scope = IfcText::readStepData( args[5] );
			m_Revision = IfcLabel::readStepData( args[6] );
			m_DocumentOwner = IfcActorSelect::readStepData( args[7], map );
			readSelectList( args[8], m_Editors, map );
			m_CreationTime = IfcDateTime::readStepData( args[9] );
			m_LastRevisionTime = IfcDateTime::readStepData( args[10] );
			readEntityReference( args[11], m_ElectronicFormat, map );
			m_ValidFrom = IfcDate::readStepData( args[12] );
			m_ValidUntil = IfcDate::readStepData( args[13] );
			m_Confidentiality = IfcDocumentConfidentialityEnum::readStepData( args[14] );
			m_Status = IfcDocumentStatusEnum::readStepData( args[15] );
			m_Location = IfcURIReference::readStepData( args[16] );
		}
		void IfcDocumentInformation::setInverseCounterparts( shared_ptr<IfcBridgeEntity> ptr_self_entity )
		{
			IfcExternalInformation::setInverseCounterparts( ptr_self_entity );
		}
		void IfcDocumentInformation::unlinkSelf()
		{
			IfcExternalInformation::unlinkSelf();
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
