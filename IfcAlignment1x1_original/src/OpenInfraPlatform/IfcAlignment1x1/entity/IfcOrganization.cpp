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
#include "OpenInfraPlatform/IfcAlignment1x1/model/Exception.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1EntityEnums.h"
#include "IfcOrganization.h"
#include "IfcIdentifier.h"
#include "IfcLabel.h"
#include "IfcText.h"
#include "IfcActorRole.h"
#include "IfcAddress.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcOrganization
			IfcOrganization::IfcOrganization() { m_entity_enum = IFCORGANIZATION;}
			IfcOrganization::IfcOrganization( int id ) { m_id = id; m_entity_enum = IFCORGANIZATION;}
			IfcOrganization::~IfcOrganization() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcOrganization::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcOrganization> other = std::dynamic_pointer_cast<IfcOrganization>(other_entity);
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
				if( m_Identification) { m_Identification->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Name) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Description) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				writeEntityList( stream, m_Roles );
				stream << ",";
				writeEntityList( stream, m_Addresses );
				stream << ");";
			}
			void IfcOrganization::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcOrganization::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<5 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcOrganization, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<5 ){ std::cout << "Wrong parameter count for entity IfcOrganization, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_Identification = IfcIdentifier::readStepData( args[0] );
				m_Name = IfcLabel::readStepData( args[1] );
				m_Description = IfcText::readStepData( args[2] );
				readEntityReferenceList( args[3], m_Roles , map);
				readEntityReferenceList( args[4], m_Addresses , map);
			}
			void IfcOrganization::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
			}
			void IfcOrganization::unlinkSelf()
			{
			}
	}
}
