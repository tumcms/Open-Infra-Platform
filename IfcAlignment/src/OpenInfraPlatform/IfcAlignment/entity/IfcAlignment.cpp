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
#include "include/IfcAlignment.h"
#include "include/IfcAlignment2DHorizontal.h"
#include "include/IfcAlignment2DVertical.h"
#include "include/IfcAlignmentTypeEnum.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcObjectPlacement.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcProductRepresentation.h"
#include "include/IfcRelAggregates.h"
#include "include/IfcRelAssigns.h"
#include "include/IfcRelAssignsToProduct.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelContainedInSpatialStructure.h"
#include "include/IfcRelDeclares.h"
#include "include/IfcRelDefinesByObject.h"
#include "include/IfcRelDefinesByProperties.h"
#include "include/IfcRelDefinesByType.h"
#include "include/IfcRelNests.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment
	{
		// ENTITY IfcAlignment 
		IfcAlignment::IfcAlignment() { m_entity_enum = IFCALIGNMENT; }
		IfcAlignment::IfcAlignment( int id ) { m_id = id; m_entity_enum = IFCALIGNMENT; }
		IfcAlignment::~IfcAlignment() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcAlignment::setEntity( shared_ptr<IfcAlignmentP6Entity> other_entity )
		{
			shared_ptr<IfcAlignment> other = dynamic_pointer_cast<IfcAlignment>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_ObjectType = other->m_ObjectType;
			m_ObjectPlacement = other->m_ObjectPlacement;
			m_Representation = other->m_Representation;
			m_PredefinedType = other->m_PredefinedType;
			m_Horizontal = other->m_Horizontal;
			m_Vertical = other->m_Vertical;
			m_LinearRefMethod = other->m_LinearRefMethod;
		}
		void IfcAlignment::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCALIGNMENT" << "(";
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
			if( m_ObjectPlacement ) { stream << "#" << m_ObjectPlacement->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Representation ) { stream << "#" << m_Representation->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_PredefinedType ) { m_PredefinedType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Horizontal ) { stream << "#" << m_Horizontal->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Vertical ) { stream << "#" << m_Vertical->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_LinearRefMethod ) { m_LinearRefMethod->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcAlignment::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcAlignment::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignmentP6Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<11 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcAlignment, expecting 11, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignmentP6Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>11 ){ std::cout << "Wrong parameter count for entity IfcAlignment, expecting 11, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			m_ObjectType = IfcLabel::readStepData( args[4] );
			readEntityReference( args[5], m_ObjectPlacement, map );
			readEntityReference( args[6], m_Representation, map );
			m_PredefinedType = IfcAlignmentTypeEnum::readStepData( args[7] );
			readEntityReference( args[8], m_Horizontal, map );
			readEntityReference( args[9], m_Vertical, map );
			m_LinearRefMethod = IfcLabel::readStepData( args[10] );
		}
		void IfcAlignment::setInverseCounterparts( shared_ptr<IfcAlignmentP6Entity> ptr_self_entity )
		{
			IfcPositioningElement::setInverseCounterparts( ptr_self_entity );
			shared_ptr<IfcAlignment> ptr_self = dynamic_pointer_cast<IfcAlignment>( ptr_self_entity );
			if( !ptr_self ) { throw IfcAlignmentP6Exception( "IfcAlignment::setInverseCounterparts: type mismatch" ); }
			if( m_Horizontal )
			{
				m_Horizontal->m_ToAlignment_inverse.push_back( ptr_self );
			}
			if( m_Vertical )
			{
				m_Vertical->m_ToAlignment_inverse.push_back( ptr_self );
			}
		}
		void IfcAlignment::unlinkSelf()
		{
			IfcPositioningElement::unlinkSelf();
			if( m_Horizontal )
			{
				std::vector<weak_ptr<IfcAlignment> >& ToAlignment_inverse = m_Horizontal->m_ToAlignment_inverse;
				std::vector<weak_ptr<IfcAlignment> >::iterator it_ToAlignment_inverse;
				for( it_ToAlignment_inverse = ToAlignment_inverse.begin(); it_ToAlignment_inverse != ToAlignment_inverse.end(); ++it_ToAlignment_inverse)
				{
					shared_ptr<IfcAlignment> self_candidate( *it_ToAlignment_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						ToAlignment_inverse.erase( it_ToAlignment_inverse );
						break;
					}
				}
			}
			if( m_Vertical )
			{
				std::vector<weak_ptr<IfcAlignment> >& ToAlignment_inverse = m_Vertical->m_ToAlignment_inverse;
				std::vector<weak_ptr<IfcAlignment> >::iterator it_ToAlignment_inverse;
				for( it_ToAlignment_inverse = ToAlignment_inverse.begin(); it_ToAlignment_inverse != ToAlignment_inverse.end(); ++it_ToAlignment_inverse)
				{
					shared_ptr<IfcAlignment> self_candidate( *it_ToAlignment_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						ToAlignment_inverse.erase( it_ToAlignment_inverse );
						break;
					}
				}
			}
		}
	} // end namespace IfcAlignment
} // end namespace OpenInfraPlatform
