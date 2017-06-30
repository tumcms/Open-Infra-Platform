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
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcMeasureWithUnit.h"
#include "include/IfcObjectDefinition.h"
#include "include/IfcObjectTypeEnum.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcProcess.h"
#include "include/IfcRelAssignsToProcess.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcRelAssignsToProcess 
		IfcRelAssignsToProcess::IfcRelAssignsToProcess() { m_entity_enum = IFCRELASSIGNSTOPROCESS; }
		IfcRelAssignsToProcess::IfcRelAssignsToProcess( int id ) { m_id = id; m_entity_enum = IFCRELASSIGNSTOPROCESS; }
		IfcRelAssignsToProcess::~IfcRelAssignsToProcess() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcRelAssignsToProcess::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcRelAssignsToProcess> other = dynamic_pointer_cast<IfcRelAssignsToProcess>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_RelatedObjects = other->m_RelatedObjects;
			m_RelatedObjectsType = other->m_RelatedObjectsType;
			m_RelatingProcess = other->m_RelatingProcess;
			m_QuantityInProcess = other->m_QuantityInProcess;
		}
		void IfcRelAssignsToProcess::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCRELASSIGNSTOPROCESS" << "(";
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
			if( m_RelatedObjectsType ) { m_RelatedObjectsType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RelatingProcess ) { stream << "#" << m_RelatingProcess->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_QuantityInProcess ) { stream << "#" << m_QuantityInProcess->getId(); } else { stream << "$"; }
			stream << ");";
		}
		void IfcRelAssignsToProcess::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcRelAssignsToProcess::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<8 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcRelAssignsToProcess, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>8 ){ std::cout << "Wrong parameter count for entity IfcRelAssignsToProcess, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			readEntityReferenceList( args[4], m_RelatedObjects, map );
			m_RelatedObjectsType = IfcObjectTypeEnum::readStepData( args[5] );
			readEntityReference( args[6], m_RelatingProcess, map );
			readEntityReference( args[7], m_QuantityInProcess, map );
		}
		void IfcRelAssignsToProcess::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcRelAssigns::setInverseCounterparts( ptr_self_entity );
			shared_ptr<IfcRelAssignsToProcess> ptr_self = dynamic_pointer_cast<IfcRelAssignsToProcess>( ptr_self_entity );
			if( !ptr_self ) { throw Ifc2x3Exception( "IfcRelAssignsToProcess::setInverseCounterparts: type mismatch" ); }
			if( m_RelatingProcess )
			{
				m_RelatingProcess->m_OperatesOn_inverse.push_back( ptr_self );
			}
		}
		void IfcRelAssignsToProcess::unlinkSelf()
		{
			IfcRelAssigns::unlinkSelf();
			if( m_RelatingProcess )
			{
				std::vector<weak_ptr<IfcRelAssignsToProcess> >& OperatesOn_inverse = m_RelatingProcess->m_OperatesOn_inverse;
				std::vector<weak_ptr<IfcRelAssignsToProcess> >::iterator it_OperatesOn_inverse;
				for( it_OperatesOn_inverse = OperatesOn_inverse.begin(); it_OperatesOn_inverse != OperatesOn_inverse.end(); ++it_OperatesOn_inverse)
				{
					shared_ptr<IfcRelAssignsToProcess> self_candidate( *it_OperatesOn_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						OperatesOn_inverse.erase( it_OperatesOn_inverse );
						break;
					}
				}
			}
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
