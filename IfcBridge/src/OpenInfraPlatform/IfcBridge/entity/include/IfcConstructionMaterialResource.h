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

#pragma once
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include "../../model/shared_ptr.h"
#include "../../model/IfcBridgeObject.h"
#include "IfcConstructionResource.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		class IfcConstructionMaterialResourceTypeEnum;
		//ENTITY
		class IfcConstructionMaterialResource : public IfcConstructionResource
		{
		public:
			IfcConstructionMaterialResource();
			IfcConstructionMaterialResource( int id );
			~IfcConstructionMaterialResource();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity( shared_ptr<IfcBridgeEntity> other );
			virtual void getStepLine( std::stringstream& stream ) const;
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			virtual void readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcBridgeEntity> >& map );
			virtual void setInverseCounterparts( shared_ptr<IfcBridgeEntity> ptr_self );
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcConstructionMaterialResource"; }


			// IfcRoot -----------------------------------------------------------
			// attributes:
			//  shared_ptr<IfcGloballyUniqueId>						m_GlobalId;
			//  shared_ptr<IfcOwnerHistory>							m_OwnerHistory;				//optional
			//  shared_ptr<IfcLabel>									m_Name;						//optional
			//  shared_ptr<IfcText>									m_Description;				//optional

			// IfcObjectDefinition -----------------------------------------------------------
			// inverse attributes:
			//  std::vector<weak_ptr<IfcRelAssigns> >				m_HasAssignments_inverse;
			//  std::vector<weak_ptr<IfcRelNests> >					m_Nests_inverse;
			//  std::vector<weak_ptr<IfcRelNests> >					m_IsNestedBy_inverse;
			//  std::vector<weak_ptr<IfcRelDeclares> >				m_HasContext_inverse;
			//  std::vector<weak_ptr<IfcRelAggregates> >				m_IsDecomposedBy_inverse;
			//  std::vector<weak_ptr<IfcRelAggregates> >				m_Decomposes_inverse;
			//  std::vector<weak_ptr<IfcRelAssociates> >				m_HasAssociations_inverse;

			// IfcObject -----------------------------------------------------------
			// attributes:
			//  shared_ptr<IfcLabel>									m_ObjectType;				//optional
			// inverse attributes:
			//  std::vector<weak_ptr<IfcRelDefinesByObject> >		m_IsDeclaredBy_inverse;
			//  std::vector<weak_ptr<IfcRelDefinesByObject> >		m_Declares_inverse;
			//  std::vector<weak_ptr<IfcRelDefinesByType> >			m_IsTypedBy_inverse;
			//  std::vector<weak_ptr<IfcRelDefinesByProperties> >	m_IsDefinedBy_inverse;

			// IfcResource -----------------------------------------------------------
			// attributes:
			//  shared_ptr<IfcIdentifier>							m_Identification;			//optional
			//  shared_ptr<IfcText>									m_LongDescription;			//optional
			// inverse attributes:
			//  std::vector<weak_ptr<IfcRelAssignsToResource> >		m_ResourceOf_inverse;

			// IfcConstructionResource -----------------------------------------------------------
			// attributes:
			//  shared_ptr<IfcResourceConsumptionEnum>				m_ResourceConsumption;		//optional
			//  shared_ptr<IfcMeasureWithUnit>						m_BaseQuantityConsumed;		//optional
			//  shared_ptr<IfcMeasureWithUnit>						m_BaseQuantityProduced;		//optional
			//  std::vector<shared_ptr<IfcCostValue> >				m_CostRatesConsumed;		//optional
			//  shared_ptr<IfcPhysicalQuantity>						m_QuantityProduced;			//optional
			//  shared_ptr<IfcResourceTime>							m_ResourceTime;				//optional
			//  shared_ptr<IfcResourceCost>							m_ResourceCost;				//optional

			// IfcConstructionMaterialResource -----------------------------------------------------------
			// attributes:
			shared_ptr<IfcConstructionMaterialResourceTypeEnum>	m_PredefinedType;			//optional
		};
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform

