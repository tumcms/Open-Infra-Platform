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
#include "include/IfcConstructionProductResource.h"
#include "include/IfcConstructionProductResourceTypeEnum.h"
#include "include/IfcCostValue.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcIdentifier.h"
#include "include/IfcLabel.h"
#include "include/IfcMeasureWithUnit.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcPhysicalQuantity.h"
#include "include/IfcRelAggregates.h"
#include "include/IfcRelAssigns.h"
#include "include/IfcRelAssignsToResource.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelDeclares.h"
#include "include/IfcRelDefinesByObject.h"
#include "include/IfcRelDefinesByProperties.h"
#include "include/IfcRelDefinesByType.h"
#include "include/IfcRelNests.h"
#include "include/IfcResourceConsumptionEnum.h"
#include "include/IfcResourceCost.h"
#include "include/IfcResourceTime.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// ENTITY IfcConstructionProductResource 
		IfcConstructionProductResource::IfcConstructionProductResource() { m_entity_enum = IFCCONSTRUCTIONPRODUCTRESOURCE; }
		IfcConstructionProductResource::IfcConstructionProductResource( int id ) { m_id = id; m_entity_enum = IFCCONSTRUCTIONPRODUCTRESOURCE; }
		IfcConstructionProductResource::~IfcConstructionProductResource() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcConstructionProductResource::setEntity( shared_ptr<IfcBridgeEntity> other_entity )
		{
			shared_ptr<IfcConstructionProductResource> other = dynamic_pointer_cast<IfcConstructionProductResource>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_ObjectType = other->m_ObjectType;
			m_Identification = other->m_Identification;
			m_LongDescription = other->m_LongDescription;
			m_ResourceConsumption = other->m_ResourceConsumption;
			m_BaseQuantityConsumed = other->m_BaseQuantityConsumed;
			m_BaseQuantityProduced = other->m_BaseQuantityProduced;
			m_CostRatesConsumed = other->m_CostRatesConsumed;
			m_QuantityProduced = other->m_QuantityProduced;
			m_ResourceTime = other->m_ResourceTime;
			m_ResourceCost = other->m_ResourceCost;
			m_PredefinedType = other->m_PredefinedType;
		}
		void IfcConstructionProductResource::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCCONSTRUCTIONPRODUCTRESOURCE" << "(";
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
			if( m_Identification ) { m_Identification->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LongDescription ) { m_LongDescription->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ResourceConsumption ) { m_ResourceConsumption->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_BaseQuantityConsumed ) { stream << "#" << m_BaseQuantityConsumed->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_BaseQuantityProduced ) { stream << "#" << m_BaseQuantityProduced->getId(); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_CostRatesConsumed );
			stream << ",";
			if( m_QuantityProduced ) { stream << "#" << m_QuantityProduced->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_ResourceTime ) { stream << "#" << m_ResourceTime->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_ResourceCost ) { stream << "#" << m_ResourceCost->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_PredefinedType ) { m_PredefinedType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcConstructionProductResource::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcConstructionProductResource::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcBridgeEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<15 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcConstructionProductResource, expecting 15, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcBridgeException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>15 ){ std::cout << "Wrong parameter count for entity IfcConstructionProductResource, expecting 15, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			m_ObjectType = IfcLabel::readStepData( args[4] );
			m_Identification = IfcIdentifier::readStepData( args[5] );
			m_LongDescription = IfcText::readStepData( args[6] );
			m_ResourceConsumption = IfcResourceConsumptionEnum::readStepData( args[7] );
			readEntityReference( args[8], m_BaseQuantityConsumed, map );
			readEntityReference( args[9], m_BaseQuantityProduced, map );
			readEntityReferenceList( args[10], m_CostRatesConsumed, map );
			readEntityReference( args[11], m_QuantityProduced, map );
			readEntityReference( args[12], m_ResourceTime, map );
			readEntityReference( args[13], m_ResourceCost, map );
			m_PredefinedType = IfcConstructionProductResourceTypeEnum::readStepData( args[14] );
		}
		void IfcConstructionProductResource::setInverseCounterparts( shared_ptr<IfcBridgeEntity> ptr_self_entity )
		{
			IfcConstructionResource::setInverseCounterparts( ptr_self_entity );
		}
		void IfcConstructionProductResource::unlinkSelf()
		{
			IfcConstructionResource::unlinkSelf();
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
