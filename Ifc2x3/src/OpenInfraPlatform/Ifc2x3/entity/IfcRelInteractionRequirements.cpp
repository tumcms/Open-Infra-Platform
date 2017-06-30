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
#include "include/IfcCountMeasure.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcNormalisedRatioMeasure.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcRelInteractionRequirements.h"
#include "include/IfcSpaceProgram.h"
#include "include/IfcSpatialStructureElement.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcRelInteractionRequirements 
		IfcRelInteractionRequirements::IfcRelInteractionRequirements() { m_entity_enum = IFCRELINTERACTIONREQUIREMENTS; }
		IfcRelInteractionRequirements::IfcRelInteractionRequirements( int id ) { m_id = id; m_entity_enum = IFCRELINTERACTIONREQUIREMENTS; }
		IfcRelInteractionRequirements::~IfcRelInteractionRequirements() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcRelInteractionRequirements::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcRelInteractionRequirements> other = dynamic_pointer_cast<IfcRelInteractionRequirements>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_DailyInteraction = other->m_DailyInteraction;
			m_ImportanceRating = other->m_ImportanceRating;
			m_LocationOfInteraction = other->m_LocationOfInteraction;
			m_RelatedSpaceProgram = other->m_RelatedSpaceProgram;
			m_RelatingSpaceProgram = other->m_RelatingSpaceProgram;
		}
		void IfcRelInteractionRequirements::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCRELINTERACTIONREQUIREMENTS" << "(";
			if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_DailyInteraction ) { m_DailyInteraction->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ImportanceRating ) { m_ImportanceRating->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LocationOfInteraction ) { stream << "#" << m_LocationOfInteraction->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_RelatedSpaceProgram ) { stream << "#" << m_RelatedSpaceProgram->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_RelatingSpaceProgram ) { stream << "#" << m_RelatingSpaceProgram->getId(); } else { stream << "$"; }
			stream << ");";
		}
		void IfcRelInteractionRequirements::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcRelInteractionRequirements::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<9 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcRelInteractionRequirements, expecting 9, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>9 ){ std::cout << "Wrong parameter count for entity IfcRelInteractionRequirements, expecting 9, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			m_DailyInteraction = IfcCountMeasure::readStepData( args[4] );
			m_ImportanceRating = IfcNormalisedRatioMeasure::readStepData( args[5] );
			readEntityReference( args[6], m_LocationOfInteraction, map );
			readEntityReference( args[7], m_RelatedSpaceProgram, map );
			readEntityReference( args[8], m_RelatingSpaceProgram, map );
		}
		void IfcRelInteractionRequirements::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcRelConnects::setInverseCounterparts( ptr_self_entity );
			shared_ptr<IfcRelInteractionRequirements> ptr_self = dynamic_pointer_cast<IfcRelInteractionRequirements>( ptr_self_entity );
			if( !ptr_self ) { throw Ifc2x3Exception( "IfcRelInteractionRequirements::setInverseCounterparts: type mismatch" ); }
			if( m_RelatedSpaceProgram )
			{
				m_RelatedSpaceProgram->m_HasInteractionReqsFrom_inverse.push_back( ptr_self );
			}
			if( m_RelatingSpaceProgram )
			{
				m_RelatingSpaceProgram->m_HasInteractionReqsTo_inverse.push_back( ptr_self );
			}
		}
		void IfcRelInteractionRequirements::unlinkSelf()
		{
			IfcRelConnects::unlinkSelf();
			if( m_RelatedSpaceProgram )
			{
				std::vector<weak_ptr<IfcRelInteractionRequirements> >& HasInteractionReqsFrom_inverse = m_RelatedSpaceProgram->m_HasInteractionReqsFrom_inverse;
				std::vector<weak_ptr<IfcRelInteractionRequirements> >::iterator it_HasInteractionReqsFrom_inverse;
				for( it_HasInteractionReqsFrom_inverse = HasInteractionReqsFrom_inverse.begin(); it_HasInteractionReqsFrom_inverse != HasInteractionReqsFrom_inverse.end(); ++it_HasInteractionReqsFrom_inverse)
				{
					shared_ptr<IfcRelInteractionRequirements> self_candidate( *it_HasInteractionReqsFrom_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						HasInteractionReqsFrom_inverse.erase( it_HasInteractionReqsFrom_inverse );
						break;
					}
				}
			}
			if( m_RelatingSpaceProgram )
			{
				std::vector<weak_ptr<IfcRelInteractionRequirements> >& HasInteractionReqsTo_inverse = m_RelatingSpaceProgram->m_HasInteractionReqsTo_inverse;
				std::vector<weak_ptr<IfcRelInteractionRequirements> >::iterator it_HasInteractionReqsTo_inverse;
				for( it_HasInteractionReqsTo_inverse = HasInteractionReqsTo_inverse.begin(); it_HasInteractionReqsTo_inverse != HasInteractionReqsTo_inverse.end(); ++it_HasInteractionReqsTo_inverse)
				{
					shared_ptr<IfcRelInteractionRequirements> self_candidate( *it_HasInteractionReqsTo_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						HasInteractionReqsTo_inverse.erase( it_HasInteractionReqsTo_inverse );
						break;
					}
				}
			}
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
