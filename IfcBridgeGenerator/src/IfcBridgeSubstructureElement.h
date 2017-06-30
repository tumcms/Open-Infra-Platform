/*
    Copyright (c) 2017 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    TUM Open Infra Platform is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    TUM Open Infra Platform is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include "OpenInfraPlatform/IfcBridge/model/shared_ptr.h"
#include "OpenInfraPlatform/IfcBridge/model/IfcBridgeObject.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcBridgeElement.h"
class IfcBridgeSubstructureElementType;
//ENTITY
class IfcBridgeSubstructureElement : public OpenInfraPlatform::IfcBridge::IfcBridgeElement
{
public:
	IfcBridgeSubstructureElement();
	IfcBridgeSubstructureElement( int id );
	~IfcBridgeSubstructureElement();

	// method setEntity takes over all attributes from another instance of the class
	virtual void setEntity(shared_ptr<OpenInfraPlatform::IfcBridge::IfcBridgeEntity> other);
	virtual void getStepLine( std::stringstream& stream ) const;
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	virtual void readStepData(std::vector<std::string>& args, const std::map<int, shared_ptr<OpenInfraPlatform::IfcBridge::IfcBridgeEntity> >& map);
	virtual void setInverseCounterparts(shared_ptr<OpenInfraPlatform::IfcBridge::IfcBridgeEntity> ptr_self);
	virtual void unlinkSelf();
	virtual const char* classname() const { return "IfcBridgeSubstructureElement"; }


	// IfcRoot -----------------------------------------------------------
	// attributes:
	//  shared_ptr<IfcGloballyUniqueId>				m_GlobalId;
	//  shared_ptr<IfcOwnerHistory>					m_OwnerHistory;				//optional
	//  shared_ptr<IfcLabel>							m_Name;						//optional
	//  shared_ptr<IfcText>							m_Description;				//optional

	// IfcObjectDefinition -----------------------------------------------------------
	// inverse attributes:
	//  std::vector<weak_ptr<IfcRelAssigns> >		m_HasAssignments_inverse;
	//  std::vector<weak_ptr<IfcRelNests> >			m_Nests_inverse;
	//  std::vector<weak_ptr<IfcRelNests> >			m_IsNestedBy_inverse;
	//  std::vector<weak_ptr<IfcRelDeclares> >		m_HasContext_inverse;
	//  std::vector<weak_ptr<IfcRelAggregates> >		m_IsDecomposedBy_inverse;
	//  std::vector<weak_ptr<IfcRelAggregates> >		m_Decomposes_inverse;
	//  std::vector<weak_ptr<IfcRelAssociates> >		m_HasAssociations_inverse;

	// IfcObject -----------------------------------------------------------
	// attributes:
	//  shared_ptr<IfcLabel>							m_ObjectType;				//optional
	// inverse attributes:
	//  std::vector<weak_ptr<IfcRelDefinesByObject> >	m_IsDeclaredBy_inverse;
	//  std::vector<weak_ptr<IfcRelDefinesByObject> >	m_Declares_inverse;
	//  std::vector<weak_ptr<IfcRelDefinesByType> >	m_IsTypedBy_inverse;
	//  std::vector<weak_ptr<IfcRelDefinesByProperties> >	m_IsDefinedBy_inverse;

	// IfcProduct -----------------------------------------------------------
	// attributes:
	//  shared_ptr<IfcObjectPlacement>				m_ObjectPlacement;			//optional
	//  shared_ptr<IfcProductRepresentation>			m_Representation;			//optional
	// inverse attributes:
	//  std::vector<weak_ptr<IfcRelAssignsToProduct> >	m_ReferencedBy_inverse;

	// IfcElement -----------------------------------------------------------
	// attributes:
	//  shared_ptr<IfcIdentifier>					m_Tag;						//optional
	// inverse attributes:
	//  std::vector<weak_ptr<IfcRelFillsElement> >	m_FillsVoids_inverse;
	//  std::vector<weak_ptr<IfcRelConnectsElements> >	m_ConnectedTo_inverse;
	//  std::vector<weak_ptr<IfcRelInterferesElements> >	m_IsInterferedByElements_inverse;
	//  std::vector<weak_ptr<IfcRelInterferesElements> >	m_InterferesElements_inverse;
	//  std::vector<weak_ptr<IfcRelProjectsElement> >	m_HasProjections_inverse;
	//  std::vector<weak_ptr<IfcRelReferencedInSpatialStructure> >	m_ReferencedInStructures_inverse;
	//  std::vector<weak_ptr<IfcRelVoidsElement> >	m_HasOpenings_inverse;
	//  std::vector<weak_ptr<IfcRelConnectsWithRealizingElements> >	m_IsConnectionRealization_inverse;
	//  std::vector<weak_ptr<IfcRelSpaceBoundary> >	m_ProvidesBoundaries_inverse;
	//  std::vector<weak_ptr<IfcRelConnectsElements> >	m_ConnectedFrom_inverse;
	//  std::vector<weak_ptr<IfcRelContainedInSpatialStructure> >	m_ContainedInStructure_inverse;

	// IfcCivilElement -----------------------------------------------------------

	// IfcBridgeElement -----------------------------------------------------------

	// IfcBridgeSubstructureElement -----------------------------------------------------------
	// attributes:
	shared_ptr<IfcBridgeSubstructureElementType>	m_SubstructureType;			//optional
};

