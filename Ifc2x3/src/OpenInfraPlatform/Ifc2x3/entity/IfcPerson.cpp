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
#include "include/IfcActorRole.h"
#include "include/IfcAddress.h"
#include "include/IfcIdentifier.h"
#include "include/IfcLabel.h"
#include "include/IfcPerson.h"
#include "include/IfcPersonAndOrganization.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcPerson 
		IfcPerson::IfcPerson() { m_entity_enum = IFCPERSON; }
		IfcPerson::IfcPerson( int id ) { m_id = id; m_entity_enum = IFCPERSON; }
		IfcPerson::~IfcPerson() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcPerson::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcPerson> other = dynamic_pointer_cast<IfcPerson>(other_entity);
			if( !other) { return; }
			m_Id = other->m_Id;
			m_FamilyName = other->m_FamilyName;
			m_GivenName = other->m_GivenName;
			m_MiddleNames = other->m_MiddleNames;
			m_PrefixTitles = other->m_PrefixTitles;
			m_SuffixTitles = other->m_SuffixTitles;
			m_Roles = other->m_Roles;
			m_Addresses = other->m_Addresses;
		}
		void IfcPerson::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCPERSON" << "(";
			if( m_Id ) { m_Id->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_FamilyName ) { m_FamilyName->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_GivenName ) { m_GivenName->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeTypeList( stream, m_MiddleNames );
			stream << ",";
			writeTypeList( stream, m_PrefixTitles );
			stream << ",";
			writeTypeList( stream, m_SuffixTitles );
			stream << ",";
			writeEntityList( stream, m_Roles );
			stream << ",";
			writeEntityList( stream, m_Addresses );
			stream << ");";
		}
		void IfcPerson::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcPerson::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<8 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcPerson, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>8 ){ std::cout << "Wrong parameter count for entity IfcPerson, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Id = IfcIdentifier::readStepData( args[0] );
			m_FamilyName = IfcLabel::readStepData( args[1] );
			m_GivenName = IfcLabel::readStepData( args[2] );
			readTypeList( args[3], m_MiddleNames );
			readTypeList( args[4], m_PrefixTitles );
			readTypeList( args[5], m_SuffixTitles );
			readEntityReferenceList( args[6], m_Roles, map );
			readEntityReferenceList( args[7], m_Addresses, map );
		}
		void IfcPerson::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			shared_ptr<IfcPerson> ptr_self = dynamic_pointer_cast<IfcPerson>( ptr_self_entity );
			if( !ptr_self ) { throw Ifc2x3Exception( "IfcPerson::setInverseCounterparts: type mismatch" ); }
			for( int i=0; i<m_Addresses.size(); ++i )
			{
				if( m_Addresses[i] )
				{
					m_Addresses[i]->m_OfPerson_inverse.push_back( ptr_self );
				}
			}
		}
		void IfcPerson::unlinkSelf()
		{
			for( int i=0; i<m_Addresses.size(); ++i )
			{
				if( m_Addresses[i] )
				{
					std::vector<weak_ptr<IfcPerson> >& OfPerson_inverse = m_Addresses[i]->m_OfPerson_inverse;
					std::vector<weak_ptr<IfcPerson> >::iterator it_OfPerson_inverse;
					for( it_OfPerson_inverse = OfPerson_inverse.begin(); it_OfPerson_inverse != OfPerson_inverse.end(); ++it_OfPerson_inverse)
					{
						shared_ptr<IfcPerson> self_candidate( *it_OfPerson_inverse );
						if( self_candidate->getId() == this->getId() )
						{
							OfPerson_inverse.erase( it_OfPerson_inverse );
							break;
						}
					}
				}
			}
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
