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

#include "OpenInfraPlatform/IfcRoad/model/IfcRoadException.h"
#include "OpenInfraPlatform/IfcRoad/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcRoad/writer/WriterUtil.h"
#include "OpenInfraPlatform/IfcRoad/IfcRoadEntityEnums.h"
#include "include/IfcActorRole.h"
#include "include/IfcAddress.h"
#include "include/IfcIdentifier.h"
#include "include/IfcLabel.h"
#include "include/IfcOrganization.h"
#include "include/IfcOrganizationRelationship.h"
#include "include/IfcPersonAndOrganization.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace IfcRoad
	{
		// ENTITY IfcOrganization 
		IfcOrganization::IfcOrganization() { m_entity_enum = IFCORGANIZATION; }
		IfcOrganization::IfcOrganization( int id ) { m_id = id; m_entity_enum = IFCORGANIZATION; }
		IfcOrganization::~IfcOrganization() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcOrganization::setEntity( shared_ptr<IfcRoadEntity> other_entity )
		{
			shared_ptr<IfcOrganization> other = dynamic_pointer_cast<IfcOrganization>(other_entity);
			if( !other) { return; }
			m_Identification = other->m_Identification;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_Roles = other->m_Roles;
			m_Addresses = other->m_Addresses;
		}
		void IfcOrganization::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCORGANIZATION" << "(";
			if( m_Identification ) { m_Identification->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_Roles );
			stream << ",";
			writeEntityList( stream, m_Addresses );
			stream << ");";
		}
		void IfcOrganization::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcOrganization::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcRoadEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<5 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcOrganization, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcRoadException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>5 ){ std::cout << "Wrong parameter count for entity IfcOrganization, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Identification = IfcIdentifier::readStepData( args[0] );
			m_Name = IfcLabel::readStepData( args[1] );
			m_Description = IfcText::readStepData( args[2] );
			readEntityReferenceList( args[3], m_Roles, map );
			readEntityReferenceList( args[4], m_Addresses, map );
		}
		void IfcOrganization::setInverseCounterparts( shared_ptr<IfcRoadEntity> ptr_self_entity )
		{
			shared_ptr<IfcOrganization> ptr_self = dynamic_pointer_cast<IfcOrganization>( ptr_self_entity );
			if( !ptr_self ) { throw IfcRoadException( "IfcOrganization::setInverseCounterparts: type mismatch" ); }
			for( int i=0; i<m_Addresses.size(); ++i )
			{
				if( m_Addresses[i] )
				{
					m_Addresses[i]->m_OfOrganization_inverse.push_back( ptr_self );
				}
			}
		}
		void IfcOrganization::unlinkSelf()
		{
			for( int i=0; i<m_Addresses.size(); ++i )
			{
				if( m_Addresses[i] )
				{
					std::vector<weak_ptr<IfcOrganization> >& OfOrganization_inverse = m_Addresses[i]->m_OfOrganization_inverse;
					std::vector<weak_ptr<IfcOrganization> >::iterator it_OfOrganization_inverse;
					for( it_OfOrganization_inverse = OfOrganization_inverse.begin(); it_OfOrganization_inverse != OfOrganization_inverse.end(); ++it_OfOrganization_inverse)
					{
						shared_ptr<IfcOrganization> self_candidate( *it_OfOrganization_inverse );
						if( self_candidate->getId() == this->getId() )
						{
							OfOrganization_inverse.erase( it_OfOrganization_inverse );
							break;
						}
					}
				}
			}
		}
	} // end namespace IfcRoad
} // end namespace OpenInfraPlatform
