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
#include "include/IfcAreaMeasure.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcIdentifier.h"
#include "include/IfcLabel.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcRelAssigns.h"
#include "include/IfcRelAssignsToControl.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelDecomposes.h"
#include "include/IfcRelDefines.h"
#include "include/IfcRelInteractionRequirements.h"
#include "include/IfcSpaceProgram.h"
#include "include/IfcSpatialStructureElement.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcSpaceProgram 
		IfcSpaceProgram::IfcSpaceProgram() { m_entity_enum = IFCSPACEPROGRAM; }
		IfcSpaceProgram::IfcSpaceProgram( int id ) { m_id = id; m_entity_enum = IFCSPACEPROGRAM; }
		IfcSpaceProgram::~IfcSpaceProgram() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcSpaceProgram::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcSpaceProgram> other = dynamic_pointer_cast<IfcSpaceProgram>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_ObjectType = other->m_ObjectType;
			m_SpaceProgramIdentifier = other->m_SpaceProgramIdentifier;
			m_MaxRequiredArea = other->m_MaxRequiredArea;
			m_MinRequiredArea = other->m_MinRequiredArea;
			m_RequestedLocation = other->m_RequestedLocation;
			m_StandardRequiredArea = other->m_StandardRequiredArea;
		}
		void IfcSpaceProgram::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCSPACEPROGRAM" << "(";
			if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ObjectType ) { m_ObjectType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_SpaceProgramIdentifier ) { m_SpaceProgramIdentifier->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MaxRequiredArea ) { m_MaxRequiredArea->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MinRequiredArea ) { m_MinRequiredArea->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RequestedLocation ) { stream << "#" << m_RequestedLocation->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_StandardRequiredArea ) { m_StandardRequiredArea->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcSpaceProgram::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcSpaceProgram::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<10 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcSpaceProgram, expecting 10, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>10 ){ std::cout << "Wrong parameter count for entity IfcSpaceProgram, expecting 10, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			m_ObjectType = IfcLabel::readStepData( args[4] );
			m_SpaceProgramIdentifier = IfcIdentifier::readStepData( args[5] );
			m_MaxRequiredArea = IfcAreaMeasure::readStepData( args[6] );
			m_MinRequiredArea = IfcAreaMeasure::readStepData( args[7] );
			readEntityReference( args[8], m_RequestedLocation, map );
			m_StandardRequiredArea = IfcAreaMeasure::readStepData( args[9] );
		}
		void IfcSpaceProgram::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcControl::setInverseCounterparts( ptr_self_entity );
		}
		void IfcSpaceProgram::unlinkSelf()
		{
			IfcControl::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
