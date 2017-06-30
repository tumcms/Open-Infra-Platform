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
#include "include/IfcDoorStyle.h"
#include "include/IfcDoorStyleConstructionEnum.h"
#include "include/IfcDoorStyleOperationEnum.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcPropertySetDefinition.h"
#include "include/IfcRelAssigns.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelDecomposes.h"
#include "include/IfcRelDefinesByType.h"
#include "include/IfcRepresentationMap.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcDoorStyle 
		IfcDoorStyle::IfcDoorStyle() { m_entity_enum = IFCDOORSTYLE; }
		IfcDoorStyle::IfcDoorStyle( int id ) { m_id = id; m_entity_enum = IFCDOORSTYLE; }
		IfcDoorStyle::~IfcDoorStyle() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcDoorStyle::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcDoorStyle> other = dynamic_pointer_cast<IfcDoorStyle>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_ApplicableOccurrence = other->m_ApplicableOccurrence;
			m_HasPropertySets = other->m_HasPropertySets;
			m_RepresentationMaps = other->m_RepresentationMaps;
			m_Tag = other->m_Tag;
			m_OperationType = other->m_OperationType;
			m_ConstructionType = other->m_ConstructionType;
			m_ParameterTakesPrecedence = other->m_ParameterTakesPrecedence;
			m_Sizeable = other->m_Sizeable;
		}
		void IfcDoorStyle::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCDOORSTYLE" << "(";
			if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ApplicableOccurrence ) { m_ApplicableOccurrence->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_HasPropertySets );
			stream << ",";
			writeEntityList( stream, m_RepresentationMaps );
			stream << ",";
			if( m_Tag ) { m_Tag->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_OperationType ) { m_OperationType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ConstructionType ) { m_ConstructionType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ParameterTakesPrecedence == false ) { stream << ".F."; }
			else if( m_ParameterTakesPrecedence == true ) { stream << ".T."; }
			stream << ",";
			if( m_Sizeable == false ) { stream << ".F."; }
			else if( m_Sizeable == true ) { stream << ".T."; }
			stream << ");";
		}
		void IfcDoorStyle::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcDoorStyle::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<12 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcDoorStyle, expecting 12, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>12 ){ std::cout << "Wrong parameter count for entity IfcDoorStyle, expecting 12, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			m_ApplicableOccurrence = IfcLabel::readStepData( args[4] );
			readEntityReferenceList( args[5], m_HasPropertySets, map );
			readEntityReferenceList( args[6], m_RepresentationMaps, map );
			m_Tag = IfcLabel::readStepData( args[7] );
			m_OperationType = IfcDoorStyleOperationEnum::readStepData( args[8] );
			m_ConstructionType = IfcDoorStyleConstructionEnum::readStepData( args[9] );
			if( _stricmp( args[10].c_str(), ".F." ) == 0 ) { m_ParameterTakesPrecedence = false; }
			else if( _stricmp( args[10].c_str(), ".T." ) == 0 ) { m_ParameterTakesPrecedence = true; }
			if( _stricmp( args[11].c_str(), ".F." ) == 0 ) { m_Sizeable = false; }
			else if( _stricmp( args[11].c_str(), ".T." ) == 0 ) { m_Sizeable = true; }
		}
		void IfcDoorStyle::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcTypeProduct::setInverseCounterparts( ptr_self_entity );
		}
		void IfcDoorStyle::unlinkSelf()
		{
			IfcTypeProduct::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
