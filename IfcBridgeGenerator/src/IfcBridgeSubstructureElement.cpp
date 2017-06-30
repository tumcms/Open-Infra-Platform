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

#include <sstream>
#include <limits>

#include "OpenInfraPlatform/IfcBridge/model/IfcBridgeException.h"


#include "OpenInfraPlatform/IfcBridge/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcBridge/writer/WriterUtil.h"
#include "OpenInfraPlatform/IfcBridge/IfcBridgeEntityEnums.h"

#include "IfcBridgeSubstructureElement.h"
#include "IfcBridgeSubstructureElementType.h"

#include "OpenInfraPlatform/IfcBridge/entity/include/IfcGloballyUniqueId.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcIdentifier.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcLabel.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcObjectPlacement.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcOwnerHistory.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcProductRepresentation.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelAggregates.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelAssigns.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelAssignsToProduct.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelAssociates.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelConnectsElements.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelConnectsWithRealizingElements.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelContainedInSpatialStructure.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelDeclares.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelDefinesByObject.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelDefinesByProperties.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelDefinesByType.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelFillsElement.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelInterferesElements.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelNests.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelProjectsElement.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelReferencedInSpatialStructure.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelSpaceBoundary.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelVoidsElement.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcText.h"

using namespace OpenInfraPlatform::IfcBridge;

// ENTITY IfcBridgeSubstructureElement 
IfcBridgeSubstructureElement::IfcBridgeSubstructureElement() { m_entity_enum = IFCBRIDGEPRISMATICELEMENT /*IFCBRIDGESUBSTRUCTUREELEMENT*/; }
IfcBridgeSubstructureElement::IfcBridgeSubstructureElement( int id ) { m_id = id; m_entity_enum = IFCBRIDGEPRISMATICELEMENT /*IFCBRIDGESUBSTRUCTUREELEMENT*/; }
IfcBridgeSubstructureElement::~IfcBridgeSubstructureElement() {}

// method setEntity takes over all attributes from another instance of the class
void IfcBridgeSubstructureElement::setEntity(shared_ptr<OpenInfraPlatform::IfcBridge::IfcBridgeEntity> other_entity)
{
	shared_ptr<IfcBridgeSubstructureElement> other = dynamic_pointer_cast<IfcBridgeSubstructureElement>(other_entity);
	if( !other) { return; }
	m_GlobalId = other->m_GlobalId;
	m_OwnerHistory = other->m_OwnerHistory;
	m_Name = other->m_Name;
	m_Description = other->m_Description;
	m_ObjectType = other->m_ObjectType;
	m_ObjectPlacement = other->m_ObjectPlacement;
	m_Representation = other->m_Representation;
	m_Tag = other->m_Tag;
	m_SubstructureType = other->m_SubstructureType;
}
void IfcBridgeSubstructureElement::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "=IFCBRIDGESUBSTRUCTUREELEMENT" << "(";
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
	if( m_Tag ) { m_Tag->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_SubstructureType ) { m_SubstructureType->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcBridgeSubstructureElement::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcBridgeSubstructureElement::readStepData(std::vector<std::string>& args, const std::map<int, shared_ptr<OpenInfraPlatform::IfcBridge::IfcBridgeEntity> >& map)
{
	const int num_args = (int)args.size();
	if (num_args<9){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcBridgeSubstructureElement, expecting 9, having " << num_args << ". Object id: " << getId() << std::endl; throw OpenInfraPlatform::IfcBridge::IfcBridgeException(strserr.str().c_str()); }
	#ifdef _DEBUG
	if( num_args>9 ){ std::cout << "Wrong parameter count for entity IfcBridgeSubstructureElement, expecting 9, having " << num_args << ". Object id: " << getId() << std::endl; }
	#endif
	m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
	readEntityReference( args[1], m_OwnerHistory, map );
	m_Name = IfcLabel::readStepData( args[2] );
	m_Description = IfcText::readStepData( args[3] );
	m_ObjectType = IfcLabel::readStepData( args[4] );
	readEntityReference( args[5], m_ObjectPlacement, map );
	readEntityReference( args[6], m_Representation, map );
	m_Tag = IfcIdentifier::readStepData( args[7] );
	m_SubstructureType = IfcBridgeSubstructureElementType::readStepData( args[8] );
}
void IfcBridgeSubstructureElement::setInverseCounterparts(shared_ptr<OpenInfraPlatform::IfcBridge::IfcBridgeEntity> ptr_self_entity)
{
	IfcBridgeElement::setInverseCounterparts( ptr_self_entity );
}
void IfcBridgeSubstructureElement::unlinkSelf()
{
	IfcBridgeElement::unlinkSelf();
}
