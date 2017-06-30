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

#include "model/IfcTunnelException.h"
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "IfcTunnelEntityEnums.h"
#include "include/IfcAreaMeasure.h"
#include "include/IfcBendingParameterSelect.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcIdentifier.h"
#include "include/IfcLabel.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcPositiveLengthMeasure.h"
#include "include/IfcPropertySetDefinition.h"
#include "include/IfcReinforcingBarSurfaceEnum.h"
#include "include/IfcReinforcingBarType.h"
#include "include/IfcReinforcingBarTypeEnum.h"
#include "include/IfcRelAggregates.h"
#include "include/IfcRelAssigns.h"
#include "include/IfcRelAssignsToProduct.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelDeclares.h"
#include "include/IfcRelDefinesByType.h"
#include "include/IfcRelNests.h"
#include "include/IfcRepresentationMap.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		// ENTITY IfcReinforcingBarType 
		IfcReinforcingBarType::IfcReinforcingBarType() { m_entity_enum = IFCREINFORCINGBARTYPE; }
		IfcReinforcingBarType::IfcReinforcingBarType( int id ) { m_id = id; m_entity_enum = IFCREINFORCINGBARTYPE; }
		IfcReinforcingBarType::~IfcReinforcingBarType() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcReinforcingBarType::setEntity( shared_ptr<IfcTunnelEntity> other_entity )
		{
			shared_ptr<IfcReinforcingBarType> other = dynamic_pointer_cast<IfcReinforcingBarType>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_ApplicableOccurrence = other->m_ApplicableOccurrence;
			m_HasPropertySets = other->m_HasPropertySets;
			m_RepresentationMaps = other->m_RepresentationMaps;
			m_Tag = other->m_Tag;
			m_ElementType = other->m_ElementType;
			m_PredefinedType = other->m_PredefinedType;
			m_NominalDiameter = other->m_NominalDiameter;
			m_CrossSectionArea = other->m_CrossSectionArea;
			m_BarLength = other->m_BarLength;
			m_BarSurface = other->m_BarSurface;
			m_BendingShapeCode = other->m_BendingShapeCode;
			m_BendingParameters = other->m_BendingParameters;
		}
		void IfcReinforcingBarType::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCREINFORCINGBARTYPE" << "(";
			if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ApplicableOccurrence ) { m_ApplicableOccurrence->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_HasPropertySets );
			stream << ",";
			writeEntityList( stream, m_RepresentationMaps );
			stream << ",";
			if( m_Tag ) { m_Tag->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ElementType ) { m_ElementType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_PredefinedType ) { m_PredefinedType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_NominalDiameter ) { m_NominalDiameter->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_CrossSectionArea ) { m_CrossSectionArea->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_BarLength ) { m_BarLength->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_BarSurface ) { m_BarSurface->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_BendingShapeCode ) { m_BendingShapeCode->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeTypeList( stream, m_BendingParameters, true );
			stream << ");";
		}
		void IfcReinforcingBarType::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcReinforcingBarType::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcTunnelEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<16 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcReinforcingBarType, expecting 16, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcTunnelException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>16 ){ std::cout << "Wrong parameter count for entity IfcReinforcingBarType, expecting 16, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			m_ApplicableOccurrence = IfcIdentifier::readStepData( args[4] );
			readEntityReferenceList( args[5], m_HasPropertySets, map );
			readEntityReferenceList( args[6], m_RepresentationMaps, map );
			m_Tag = IfcLabel::readStepData( args[7] );
			m_ElementType = IfcLabel::readStepData( args[8] );
			m_PredefinedType = IfcReinforcingBarTypeEnum::readStepData( args[9] );
			m_NominalDiameter = IfcPositiveLengthMeasure::readStepData( args[10] );
			m_CrossSectionArea = IfcAreaMeasure::readStepData( args[11] );
			m_BarLength = IfcPositiveLengthMeasure::readStepData( args[12] );
			m_BarSurface = IfcReinforcingBarSurfaceEnum::readStepData( args[13] );
			m_BendingShapeCode = IfcLabel::readStepData( args[14] );
			readSelectList( args[15], m_BendingParameters, map );
		}
		void IfcReinforcingBarType::setInverseCounterparts( shared_ptr<IfcTunnelEntity> ptr_self_entity )
		{
			IfcReinforcingElementType::setInverseCounterparts( ptr_self_entity );
		}
		void IfcReinforcingBarType::unlinkSelf()
		{
			IfcReinforcingElementType::unlinkSelf();
		}
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform
