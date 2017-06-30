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
#include "include/IfcExternalReferenceRelationship.h"
#include "include/IfcLengthMeasure.h"
#include "include/IfcReinforcementBarProperties.h"
#include "include/IfcReinforcingBarRoleEnum.h"
#include "include/IfcSectionProperties.h"
#include "include/IfcSectionReinforcementProperties.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		// ENTITY IfcSectionReinforcementProperties 
		IfcSectionReinforcementProperties::IfcSectionReinforcementProperties() { m_entity_enum = IFCSECTIONREINFORCEMENTPROPERTIES; }
		IfcSectionReinforcementProperties::IfcSectionReinforcementProperties( int id ) { m_id = id; m_entity_enum = IFCSECTIONREINFORCEMENTPROPERTIES; }
		IfcSectionReinforcementProperties::~IfcSectionReinforcementProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcSectionReinforcementProperties::setEntity( shared_ptr<IfcTunnelEntity> other_entity )
		{
			shared_ptr<IfcSectionReinforcementProperties> other = dynamic_pointer_cast<IfcSectionReinforcementProperties>(other_entity);
			if( !other) { return; }
			m_LongitudinalStartPosition = other->m_LongitudinalStartPosition;
			m_LongitudinalEndPosition = other->m_LongitudinalEndPosition;
			m_TransversePosition = other->m_TransversePosition;
			m_ReinforcementRole = other->m_ReinforcementRole;
			m_SectionDefinition = other->m_SectionDefinition;
			m_CrossSectionReinforcementDefinitions = other->m_CrossSectionReinforcementDefinitions;
		}
		void IfcSectionReinforcementProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCSECTIONREINFORCEMENTPROPERTIES" << "(";
			if( m_LongitudinalStartPosition ) { m_LongitudinalStartPosition->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LongitudinalEndPosition ) { m_LongitudinalEndPosition->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_TransversePosition ) { m_TransversePosition->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ReinforcementRole ) { m_ReinforcementRole->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_SectionDefinition ) { stream << "#" << m_SectionDefinition->getId(); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_CrossSectionReinforcementDefinitions );
			stream << ");";
		}
		void IfcSectionReinforcementProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcSectionReinforcementProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcTunnelEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<6 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcSectionReinforcementProperties, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcTunnelException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>6 ){ std::cout << "Wrong parameter count for entity IfcSectionReinforcementProperties, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_LongitudinalStartPosition = IfcLengthMeasure::readStepData( args[0] );
			m_LongitudinalEndPosition = IfcLengthMeasure::readStepData( args[1] );
			m_TransversePosition = IfcLengthMeasure::readStepData( args[2] );
			m_ReinforcementRole = IfcReinforcingBarRoleEnum::readStepData( args[3] );
			readEntityReference( args[4], m_SectionDefinition, map );
			readEntityReferenceList( args[5], m_CrossSectionReinforcementDefinitions, map );
		}
		void IfcSectionReinforcementProperties::setInverseCounterparts( shared_ptr<IfcTunnelEntity> ptr_self_entity )
		{
			IfcPreDefinedProperties::setInverseCounterparts( ptr_self_entity );
		}
		void IfcSectionReinforcementProperties::unlinkSelf()
		{
			IfcPreDefinedProperties::unlinkSelf();
		}
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform
