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

#include "OpenInfraPlatform/Ifc4/model/Ifc4Exception.h"
#include "OpenInfraPlatform/Ifc4/reader/ReaderUtil.h"
#include "OpenInfraPlatform/Ifc4/writer/WriterUtil.h"
#include "OpenInfraPlatform/Ifc4/Ifc4EntityEnums.h"
#include "include/IfcAnalysisTheoryTypeEnum.h"
#include "include/IfcBoolean.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcRelAggregates.h"
#include "include/IfcRelAssigns.h"
#include "include/IfcRelAssignsToGroup.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelDeclares.h"
#include "include/IfcRelDefinesByObject.h"
#include "include/IfcRelDefinesByProperties.h"
#include "include/IfcRelDefinesByType.h"
#include "include/IfcRelNests.h"
#include "include/IfcStructuralAnalysisModel.h"
#include "include/IfcStructuralLoadGroup.h"
#include "include/IfcStructuralResultGroup.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace Ifc4
	{
		// ENTITY IfcStructuralResultGroup 
		IfcStructuralResultGroup::IfcStructuralResultGroup() { m_entity_enum = IFCSTRUCTURALRESULTGROUP; }
		IfcStructuralResultGroup::IfcStructuralResultGroup( int id ) { m_id = id; m_entity_enum = IFCSTRUCTURALRESULTGROUP; }
		IfcStructuralResultGroup::~IfcStructuralResultGroup() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcStructuralResultGroup::setEntity( shared_ptr<Ifc4Entity> other_entity )
		{
			shared_ptr<IfcStructuralResultGroup> other = dynamic_pointer_cast<IfcStructuralResultGroup>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_ObjectType = other->m_ObjectType;
			m_TheoryType = other->m_TheoryType;
			m_ResultForLoadGroup = other->m_ResultForLoadGroup;
			m_IsLinear = other->m_IsLinear;
		}
		void IfcStructuralResultGroup::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCSTRUCTURALRESULTGROUP" << "(";
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
			if( m_TheoryType ) { m_TheoryType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ResultForLoadGroup ) { stream << "#" << m_ResultForLoadGroup->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_IsLinear ) { m_IsLinear->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcStructuralResultGroup::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcStructuralResultGroup::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc4Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<8 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcStructuralResultGroup, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc4Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>8 ){ std::cout << "Wrong parameter count for entity IfcStructuralResultGroup, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			m_ObjectType = IfcLabel::readStepData( args[4] );
			m_TheoryType = IfcAnalysisTheoryTypeEnum::readStepData( args[5] );
			readEntityReference( args[6], m_ResultForLoadGroup, map );
			m_IsLinear = IfcBoolean::readStepData( args[7] );
		}
		void IfcStructuralResultGroup::setInverseCounterparts( shared_ptr<Ifc4Entity> ptr_self_entity )
		{
			IfcGroup::setInverseCounterparts( ptr_self_entity );
			shared_ptr<IfcStructuralResultGroup> ptr_self = dynamic_pointer_cast<IfcStructuralResultGroup>( ptr_self_entity );
			if( !ptr_self ) { throw Ifc4Exception( "IfcStructuralResultGroup::setInverseCounterparts: type mismatch" ); }
			if( m_ResultForLoadGroup )
			{
				m_ResultForLoadGroup->m_SourceOfResultGroup_inverse.push_back( ptr_self );
			}
		}
		void IfcStructuralResultGroup::unlinkSelf()
		{
			IfcGroup::unlinkSelf();
			if( m_ResultForLoadGroup )
			{
				std::vector<weak_ptr<IfcStructuralResultGroup> >& SourceOfResultGroup_inverse = m_ResultForLoadGroup->m_SourceOfResultGroup_inverse;
				std::vector<weak_ptr<IfcStructuralResultGroup> >::iterator it_SourceOfResultGroup_inverse;
				for( it_SourceOfResultGroup_inverse = SourceOfResultGroup_inverse.begin(); it_SourceOfResultGroup_inverse != SourceOfResultGroup_inverse.end(); ++it_SourceOfResultGroup_inverse)
				{
					shared_ptr<IfcStructuralResultGroup> self_candidate( *it_SourceOfResultGroup_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						SourceOfResultGroup_inverse.erase( it_SourceOfResultGroup_inverse );
						break;
					}
				}
			}
		}
	} // end namespace Ifc4
} // end namespace OpenInfraPlatform
