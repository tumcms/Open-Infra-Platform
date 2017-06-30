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
#include "include/IfcApplication.h"
#include "include/IfcIdentifier.h"
#include "include/IfcLabel.h"
#include "include/IfcOrganization.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment
	{
		// ENTITY IfcApplication 
		IfcApplication::IfcApplication() { m_entity_enum = IFCAPPLICATION; }
		IfcApplication::IfcApplication( int id ) { m_id = id; m_entity_enum = IFCAPPLICATION; }
		IfcApplication::~IfcApplication() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcApplication::setEntity( shared_ptr<IfcAlignmentP6Entity> other_entity )
		{
			shared_ptr<IfcApplication> other = dynamic_pointer_cast<IfcApplication>(other_entity);
			if( !other) { return; }
			m_ApplicationDeveloper = other->m_ApplicationDeveloper;
			m_Version = other->m_Version;
			m_ApplicationFullName = other->m_ApplicationFullName;
			m_ApplicationIdentifier = other->m_ApplicationIdentifier;
		}
		void IfcApplication::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCAPPLICATION" << "(";
			if( m_ApplicationDeveloper ) { stream << "#" << m_ApplicationDeveloper->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Version ) { m_Version->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ApplicationFullName ) { m_ApplicationFullName->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ApplicationIdentifier ) { m_ApplicationIdentifier->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcApplication::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcApplication::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignmentP6Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<4 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcApplication, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignmentP6Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>4 ){ std::cout << "Wrong parameter count for entity IfcApplication, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readEntityReference( args[0], m_ApplicationDeveloper, map );
			m_Version = IfcLabel::readStepData( args[1] );
			m_ApplicationFullName = IfcLabel::readStepData( args[2] );
			m_ApplicationIdentifier = IfcIdentifier::readStepData( args[3] );
		}
		void IfcApplication::setInverseCounterparts( shared_ptr<IfcAlignmentP6Entity> )
		{
		}
		void IfcApplication::unlinkSelf()
		{
		}
	} // end namespace IfcAlignment
} // end namespace OpenInfraPlatform
