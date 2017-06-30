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
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcObject.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcRelDefinesByType.h"
#include "include/IfcText.h"
#include "include/IfcTypeObject.h"

namespace OpenInfraPlatform
{
	namespace IfcRoad
	{
		// ENTITY IfcRelDefinesByType 
		IfcRelDefinesByType::IfcRelDefinesByType() { m_entity_enum = IFCRELDEFINESBYTYPE; }
		IfcRelDefinesByType::IfcRelDefinesByType( int id ) { m_id = id; m_entity_enum = IFCRELDEFINESBYTYPE; }
		IfcRelDefinesByType::~IfcRelDefinesByType() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcRelDefinesByType::setEntity( shared_ptr<IfcRoadEntity> other_entity )
		{
			shared_ptr<IfcRelDefinesByType> other = dynamic_pointer_cast<IfcRelDefinesByType>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_RelatedObjects = other->m_RelatedObjects;
			m_RelatingType = other->m_RelatingType;
		}
		void IfcRelDefinesByType::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCRELDEFINESBYTYPE" << "(";
			if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_RelatedObjects );
			stream << ",";
			if( m_RelatingType ) { stream << "#" << m_RelatingType->getId(); } else { stream << "$"; }
			stream << ");";
		}
		void IfcRelDefinesByType::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcRelDefinesByType::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcRoadEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<6 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcRelDefinesByType, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcRoadException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>6 ){ std::cout << "Wrong parameter count for entity IfcRelDefinesByType, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			readEntityReferenceList( args[4], m_RelatedObjects, map );
			readEntityReference( args[5], m_RelatingType, map );
		}
		void IfcRelDefinesByType::setInverseCounterparts( shared_ptr<IfcRoadEntity> ptr_self_entity )
		{
			IfcRelDefines::setInverseCounterparts( ptr_self_entity );
			shared_ptr<IfcRelDefinesByType> ptr_self = dynamic_pointer_cast<IfcRelDefinesByType>( ptr_self_entity );
			if( !ptr_self ) { throw IfcRoadException( "IfcRelDefinesByType::setInverseCounterparts: type mismatch" ); }
			for( int i=0; i<m_RelatedObjects.size(); ++i )
			{
				if( m_RelatedObjects[i] )
				{
					m_RelatedObjects[i]->m_IsTypedBy_inverse.push_back( ptr_self );
				}
			}
			if( m_RelatingType )
			{
				m_RelatingType->m_Types_inverse.push_back( ptr_self );
			}
		}
		void IfcRelDefinesByType::unlinkSelf()
		{
			IfcRelDefines::unlinkSelf();
			for( int i=0; i<m_RelatedObjects.size(); ++i )
			{
				if( m_RelatedObjects[i] )
				{
					std::vector<weak_ptr<IfcRelDefinesByType> >& IsTypedBy_inverse = m_RelatedObjects[i]->m_IsTypedBy_inverse;
					std::vector<weak_ptr<IfcRelDefinesByType> >::iterator it_IsTypedBy_inverse;
					for( it_IsTypedBy_inverse = IsTypedBy_inverse.begin(); it_IsTypedBy_inverse != IsTypedBy_inverse.end(); ++it_IsTypedBy_inverse)
					{
						shared_ptr<IfcRelDefinesByType> self_candidate( *it_IsTypedBy_inverse );
						if( self_candidate->getId() == this->getId() )
						{
							IsTypedBy_inverse.erase( it_IsTypedBy_inverse );
							break;
						}
					}
				}
			}
			if( m_RelatingType )
			{
				std::vector<weak_ptr<IfcRelDefinesByType> >& Types_inverse = m_RelatingType->m_Types_inverse;
				std::vector<weak_ptr<IfcRelDefinesByType> >::iterator it_Types_inverse;
				for( it_Types_inverse = Types_inverse.begin(); it_Types_inverse != Types_inverse.end(); ++it_Types_inverse)
				{
					shared_ptr<IfcRelDefinesByType> self_candidate( *it_Types_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						Types_inverse.erase( it_Types_inverse );
						break;
					}
				}
			}
		}
	} // end namespace IfcRoad
} // end namespace OpenInfraPlatform
