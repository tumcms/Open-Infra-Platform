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
#include "include/IfcCalendarDate.h"
#include "include/IfcLabel.h"
#include "include/IfcLibraryInformation.h"
#include "include/IfcLibraryReference.h"
#include "include/IfcOrganization.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcLibraryInformation 
		IfcLibraryInformation::IfcLibraryInformation() { m_entity_enum = IFCLIBRARYINFORMATION; }
		IfcLibraryInformation::IfcLibraryInformation( int id ) { m_id = id; m_entity_enum = IFCLIBRARYINFORMATION; }
		IfcLibraryInformation::~IfcLibraryInformation() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcLibraryInformation::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcLibraryInformation> other = dynamic_pointer_cast<IfcLibraryInformation>(other_entity);
			if( !other) { return; }
			m_Name = other->m_Name;
			m_Version = other->m_Version;
			m_Publisher = other->m_Publisher;
			m_VersionDate = other->m_VersionDate;
			m_LibraryReference = other->m_LibraryReference;
		}
		void IfcLibraryInformation::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCLIBRARYINFORMATION" << "(";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Version ) { m_Version->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Publisher ) { stream << "#" << m_Publisher->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_VersionDate ) { stream << "#" << m_VersionDate->getId(); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_LibraryReference );
			stream << ");";
		}
		void IfcLibraryInformation::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcLibraryInformation::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<5 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcLibraryInformation, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>5 ){ std::cout << "Wrong parameter count for entity IfcLibraryInformation, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Name = IfcLabel::readStepData( args[0] );
			m_Version = IfcLabel::readStepData( args[1] );
			readEntityReference( args[2], m_Publisher, map );
			readEntityReference( args[3], m_VersionDate, map );
			readEntityReferenceList( args[4], m_LibraryReference, map );
		}
		void IfcLibraryInformation::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			shared_ptr<IfcLibraryInformation> ptr_self = dynamic_pointer_cast<IfcLibraryInformation>( ptr_self_entity );
			if( !ptr_self ) { throw Ifc2x3Exception( "IfcLibraryInformation::setInverseCounterparts: type mismatch" ); }
			for( int i=0; i<m_LibraryReference.size(); ++i )
			{
				if( m_LibraryReference[i] )
				{
					m_LibraryReference[i]->m_ReferenceIntoLibrary_inverse.push_back( ptr_self );
				}
			}
		}
		void IfcLibraryInformation::unlinkSelf()
		{
			for( int i=0; i<m_LibraryReference.size(); ++i )
			{
				if( m_LibraryReference[i] )
				{
					std::vector<weak_ptr<IfcLibraryInformation> >& ReferenceIntoLibrary_inverse = m_LibraryReference[i]->m_ReferenceIntoLibrary_inverse;
					std::vector<weak_ptr<IfcLibraryInformation> >::iterator it_ReferenceIntoLibrary_inverse;
					for( it_ReferenceIntoLibrary_inverse = ReferenceIntoLibrary_inverse.begin(); it_ReferenceIntoLibrary_inverse != ReferenceIntoLibrary_inverse.end(); ++it_ReferenceIntoLibrary_inverse)
					{
						shared_ptr<IfcLibraryInformation> self_candidate( *it_ReferenceIntoLibrary_inverse );
						if( self_candidate->getId() == this->getId() )
						{
							ReferenceIntoLibrary_inverse.erase( it_ReferenceIntoLibrary_inverse );
							break;
						}
					}
				}
			}
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
