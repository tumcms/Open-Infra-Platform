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

#include "OpenInfraPlatform/Ifc4/model/Ifc4Exception.h"
#include "OpenInfraPlatform/Ifc4/reader/ReaderUtil.h"
#include "OpenInfraPlatform/Ifc4/writer/WriterUtil.h"
#include "OpenInfraPlatform/Ifc4/Ifc4EntityEnums.h"
#include "include/IfcAreaMeasure.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcIdentifier.h"
#include "include/IfcLabel.h"
#include "include/IfcObjectPlacement.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcPositiveLengthMeasure.h"
#include "include/IfcProductRepresentation.h"
#include "include/IfcReinforcingBar.h"
#include "include/IfcReinforcingBarSurfaceEnum.h"
#include "include/IfcReinforcingBarTypeEnum.h"
#include "include/IfcRelAggregates.h"
#include "include/IfcRelAssigns.h"
#include "include/IfcRelAssignsToProduct.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelConnectsElements.h"
#include "include/IfcRelConnectsWithRealizingElements.h"
#include "include/IfcRelContainedInSpatialStructure.h"
#include "include/IfcRelCoversBldgElements.h"
#include "include/IfcRelDeclares.h"
#include "include/IfcRelDefinesByObject.h"
#include "include/IfcRelDefinesByProperties.h"
#include "include/IfcRelDefinesByType.h"
#include "include/IfcRelFillsElement.h"
#include "include/IfcRelInterferesElements.h"
#include "include/IfcRelNests.h"
#include "include/IfcRelProjectsElement.h"
#include "include/IfcRelReferencedInSpatialStructure.h"
#include "include/IfcRelSpaceBoundary.h"
#include "include/IfcRelVoidsElement.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace Ifc4
	{
		// ENTITY IfcReinforcingBar 
		IfcReinforcingBar::IfcReinforcingBar() { m_entity_enum = IFCREINFORCINGBAR; }
		IfcReinforcingBar::IfcReinforcingBar( int id ) { m_id = id; m_entity_enum = IFCREINFORCINGBAR; }
		IfcReinforcingBar::~IfcReinforcingBar() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcReinforcingBar::setEntity( shared_ptr<Ifc4Entity> other_entity )
		{
			shared_ptr<IfcReinforcingBar> other = dynamic_pointer_cast<IfcReinforcingBar>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_ObjectType = other->m_ObjectType;
			m_ObjectPlacement = other->m_ObjectPlacement;
			m_Representation = other->m_Representation;
			m_Tag = other->m_Tag;
			m_SteelGrade = other->m_SteelGrade;
			m_NominalDiameter = other->m_NominalDiameter;
			m_CrossSectionArea = other->m_CrossSectionArea;
			m_BarLength = other->m_BarLength;
			m_PredefinedType = other->m_PredefinedType;
			m_BarSurface = other->m_BarSurface;
		}
		void IfcReinforcingBar::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCREINFORCINGBAR" << "(";
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
			if( m_SteelGrade ) { m_SteelGrade->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_NominalDiameter ) { m_NominalDiameter->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_CrossSectionArea ) { m_CrossSectionArea->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_BarLength ) { m_BarLength->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_PredefinedType ) { m_PredefinedType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_BarSurface ) { m_BarSurface->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcReinforcingBar::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcReinforcingBar::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc4Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<14 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcReinforcingBar, expecting 14, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc4Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>14 ){ std::cout << "Wrong parameter count for entity IfcReinforcingBar, expecting 14, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			m_ObjectType = IfcLabel::readStepData( args[4] );
			readEntityReference( args[5], m_ObjectPlacement, map );
			readEntityReference( args[6], m_Representation, map );
			m_Tag = IfcIdentifier::readStepData( args[7] );
			m_SteelGrade = IfcLabel::readStepData( args[8] );
			m_NominalDiameter = IfcPositiveLengthMeasure::readStepData( args[9] );
			m_CrossSectionArea = IfcAreaMeasure::readStepData( args[10] );
			m_BarLength = IfcPositiveLengthMeasure::readStepData( args[11] );
			m_PredefinedType = IfcReinforcingBarTypeEnum::readStepData( args[12] );
			m_BarSurface = IfcReinforcingBarSurfaceEnum::readStepData( args[13] );
		}
		void IfcReinforcingBar::setInverseCounterparts( shared_ptr<Ifc4Entity> ptr_self_entity )
		{
			IfcReinforcingElement::setInverseCounterparts( ptr_self_entity );
		}
		void IfcReinforcingBar::unlinkSelf()
		{
			IfcReinforcingElement::unlinkSelf();
		}
	} // end namespace Ifc4
} // end namespace OpenInfraPlatform
