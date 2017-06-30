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

#include "model/IfcBridgeException.h"
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "IfcBridgeEntityEnums.h"
#include "include/IfcConnectionGeometry.h"
#include "include/IfcConnectionTypeEnum.h"
#include "include/IfcElement.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcRelConnectsPathElements.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// ENTITY IfcRelConnectsPathElements 
		IfcRelConnectsPathElements::IfcRelConnectsPathElements() { m_entity_enum = IFCRELCONNECTSPATHELEMENTS; }
		IfcRelConnectsPathElements::IfcRelConnectsPathElements( int id ) { m_id = id; m_entity_enum = IFCRELCONNECTSPATHELEMENTS; }
		IfcRelConnectsPathElements::~IfcRelConnectsPathElements() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcRelConnectsPathElements::setEntity( shared_ptr<IfcBridgeEntity> other_entity )
		{
			shared_ptr<IfcRelConnectsPathElements> other = dynamic_pointer_cast<IfcRelConnectsPathElements>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_ConnectionGeometry = other->m_ConnectionGeometry;
			m_RelatingElement = other->m_RelatingElement;
			m_RelatedElement = other->m_RelatedElement;
			m_RelatingPriorities = other->m_RelatingPriorities;
			m_RelatedPriorities = other->m_RelatedPriorities;
			m_RelatedConnectionType = other->m_RelatedConnectionType;
			m_RelatingConnectionType = other->m_RelatingConnectionType;
		}
		void IfcRelConnectsPathElements::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCRELCONNECTSPATHELEMENTS" << "(";
			if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ConnectionGeometry ) { stream << "#" << m_ConnectionGeometry->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_RelatingElement ) { stream << "#" << m_RelatingElement->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_RelatedElement ) { stream << "#" << m_RelatedElement->getId(); } else { stream << "$"; }
			stream << ",";
			writeIntList( stream, m_RelatingPriorities );
			stream << ",";
			writeIntList( stream, m_RelatedPriorities );
			stream << ",";
			if( m_RelatedConnectionType ) { m_RelatedConnectionType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RelatingConnectionType ) { m_RelatingConnectionType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcRelConnectsPathElements::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcRelConnectsPathElements::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcBridgeEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<11 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcRelConnectsPathElements, expecting 11, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcBridgeException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>11 ){ std::cout << "Wrong parameter count for entity IfcRelConnectsPathElements, expecting 11, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			readEntityReference( args[4], m_ConnectionGeometry, map );
			readEntityReference( args[5], m_RelatingElement, map );
			readEntityReference( args[6], m_RelatedElement, map );
			readIntList(  args[7], m_RelatingPriorities );
			readIntList(  args[8], m_RelatedPriorities );
			m_RelatedConnectionType = IfcConnectionTypeEnum::readStepData( args[9] );
			m_RelatingConnectionType = IfcConnectionTypeEnum::readStepData( args[10] );
		}
		void IfcRelConnectsPathElements::setInverseCounterparts( shared_ptr<IfcBridgeEntity> ptr_self_entity )
		{
			IfcRelConnectsElements::setInverseCounterparts( ptr_self_entity );
		}
		void IfcRelConnectsPathElements::unlinkSelf()
		{
			IfcRelConnectsElements::unlinkSelf();
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
