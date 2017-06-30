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
#include "include/IfcAppliedValue.h"
#include "include/IfcDocumentSelect.h"
#include "include/IfcLabel.h"
#include "include/IfcReferencesValueDocument.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcReferencesValueDocument 
		IfcReferencesValueDocument::IfcReferencesValueDocument() { m_entity_enum = IFCREFERENCESVALUEDOCUMENT; }
		IfcReferencesValueDocument::IfcReferencesValueDocument( int id ) { m_id = id; m_entity_enum = IFCREFERENCESVALUEDOCUMENT; }
		IfcReferencesValueDocument::~IfcReferencesValueDocument() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcReferencesValueDocument::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcReferencesValueDocument> other = dynamic_pointer_cast<IfcReferencesValueDocument>(other_entity);
			if( !other) { return; }
			m_ReferencedDocument = other->m_ReferencedDocument;
			m_ReferencingValues = other->m_ReferencingValues;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
		}
		void IfcReferencesValueDocument::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCREFERENCESVALUEDOCUMENT" << "(";
			if( m_ReferencedDocument ) { m_ReferencedDocument->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_ReferencingValues );
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcReferencesValueDocument::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcReferencesValueDocument::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<4 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcReferencesValueDocument, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>4 ){ std::cout << "Wrong parameter count for entity IfcReferencesValueDocument, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_ReferencedDocument = IfcDocumentSelect::readStepData( args[0], map );
			readEntityReferenceList( args[1], m_ReferencingValues, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
		}
		void IfcReferencesValueDocument::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			shared_ptr<IfcReferencesValueDocument> ptr_self = dynamic_pointer_cast<IfcReferencesValueDocument>( ptr_self_entity );
			if( !ptr_self ) { throw Ifc2x3Exception( "IfcReferencesValueDocument::setInverseCounterparts: type mismatch" ); }
			for( int i=0; i<m_ReferencingValues.size(); ++i )
			{
				if( m_ReferencingValues[i] )
				{
					m_ReferencingValues[i]->m_ValuesReferenced_inverse.push_back( ptr_self );
				}
			}
		}
		void IfcReferencesValueDocument::unlinkSelf()
		{
			for( int i=0; i<m_ReferencingValues.size(); ++i )
			{
				if( m_ReferencingValues[i] )
				{
					std::vector<weak_ptr<IfcReferencesValueDocument> >& ValuesReferenced_inverse = m_ReferencingValues[i]->m_ValuesReferenced_inverse;
					std::vector<weak_ptr<IfcReferencesValueDocument> >::iterator it_ValuesReferenced_inverse;
					for( it_ValuesReferenced_inverse = ValuesReferenced_inverse.begin(); it_ValuesReferenced_inverse != ValuesReferenced_inverse.end(); ++it_ValuesReferenced_inverse)
					{
						shared_ptr<IfcReferencesValueDocument> self_candidate( *it_ValuesReferenced_inverse );
						if( self_candidate->getId() == this->getId() )
						{
							ValuesReferenced_inverse.erase( it_ValuesReferenced_inverse );
							break;
						}
					}
				}
			}
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
