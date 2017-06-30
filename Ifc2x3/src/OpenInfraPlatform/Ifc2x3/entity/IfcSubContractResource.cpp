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
#include "include/IfcActorSelect.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcIdentifier.h"
#include "include/IfcLabel.h"
#include "include/IfcMeasureWithUnit.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcRelAssigns.h"
#include "include/IfcRelAssignsToResource.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelDecomposes.h"
#include "include/IfcRelDefines.h"
#include "include/IfcResourceConsumptionEnum.h"
#include "include/IfcSubContractResource.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcSubContractResource 
		IfcSubContractResource::IfcSubContractResource() { m_entity_enum = IFCSUBCONTRACTRESOURCE; }
		IfcSubContractResource::IfcSubContractResource( int id ) { m_id = id; m_entity_enum = IFCSUBCONTRACTRESOURCE; }
		IfcSubContractResource::~IfcSubContractResource() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcSubContractResource::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcSubContractResource> other = dynamic_pointer_cast<IfcSubContractResource>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_ObjectType = other->m_ObjectType;
			m_ResourceIdentifier = other->m_ResourceIdentifier;
			m_ResourceGroup = other->m_ResourceGroup;
			m_ResourceConsumption = other->m_ResourceConsumption;
			m_BaseQuantity = other->m_BaseQuantity;
			m_SubContractor = other->m_SubContractor;
			m_JobDescription = other->m_JobDescription;
		}
		void IfcSubContractResource::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCSUBCONTRACTRESOURCE" << "(";
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
			if( m_ResourceIdentifier ) { m_ResourceIdentifier->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ResourceGroup ) { m_ResourceGroup->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ResourceConsumption ) { m_ResourceConsumption->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_BaseQuantity ) { stream << "#" << m_BaseQuantity->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_SubContractor ) { m_SubContractor->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_JobDescription ) { m_JobDescription->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcSubContractResource::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcSubContractResource::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<11 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcSubContractResource, expecting 11, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>11 ){ std::cout << "Wrong parameter count for entity IfcSubContractResource, expecting 11, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			m_ObjectType = IfcLabel::readStepData( args[4] );
			m_ResourceIdentifier = IfcIdentifier::readStepData( args[5] );
			m_ResourceGroup = IfcLabel::readStepData( args[6] );
			m_ResourceConsumption = IfcResourceConsumptionEnum::readStepData( args[7] );
			readEntityReference( args[8], m_BaseQuantity, map );
			m_SubContractor = IfcActorSelect::readStepData( args[9], map );
			m_JobDescription = IfcText::readStepData( args[10] );
		}
		void IfcSubContractResource::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcConstructionResource::setInverseCounterparts( ptr_self_entity );
		}
		void IfcSubContractResource::unlinkSelf()
		{
			IfcConstructionResource::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
