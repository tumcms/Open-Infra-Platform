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
#include "include/IfcDoorPanelOperationEnum.h"
#include "include/IfcDoorPanelPositionEnum.h"
#include "include/IfcDoorPanelProperties.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcNormalisedRatioMeasure.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcPositiveLengthMeasure.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelDeclares.h"
#include "include/IfcRelDefinesByProperties.h"
#include "include/IfcRelDefinesByTemplate.h"
#include "include/IfcShapeAspect.h"
#include "include/IfcText.h"
#include "include/IfcTypeObject.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// ENTITY IfcDoorPanelProperties 
		IfcDoorPanelProperties::IfcDoorPanelProperties() { m_entity_enum = IFCDOORPANELPROPERTIES; }
		IfcDoorPanelProperties::IfcDoorPanelProperties( int id ) { m_id = id; m_entity_enum = IFCDOORPANELPROPERTIES; }
		IfcDoorPanelProperties::~IfcDoorPanelProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcDoorPanelProperties::setEntity( shared_ptr<IfcBridgeEntity> other_entity )
		{
			shared_ptr<IfcDoorPanelProperties> other = dynamic_pointer_cast<IfcDoorPanelProperties>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_PanelDepth = other->m_PanelDepth;
			m_PanelOperation = other->m_PanelOperation;
			m_PanelWidth = other->m_PanelWidth;
			m_PanelPosition = other->m_PanelPosition;
			m_ShapeAspectStyle = other->m_ShapeAspectStyle;
		}
		void IfcDoorPanelProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCDOORPANELPROPERTIES" << "(";
			if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_PanelDepth ) { m_PanelDepth->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_PanelOperation ) { m_PanelOperation->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_PanelWidth ) { m_PanelWidth->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_PanelPosition ) { m_PanelPosition->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ShapeAspectStyle ) { stream << "#" << m_ShapeAspectStyle->getId(); } else { stream << "$"; }
			stream << ");";
		}
		void IfcDoorPanelProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcDoorPanelProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcBridgeEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<9 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcDoorPanelProperties, expecting 9, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcBridgeException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>9 ){ std::cout << "Wrong parameter count for entity IfcDoorPanelProperties, expecting 9, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			m_PanelDepth = IfcPositiveLengthMeasure::readStepData( args[4] );
			m_PanelOperation = IfcDoorPanelOperationEnum::readStepData( args[5] );
			m_PanelWidth = IfcNormalisedRatioMeasure::readStepData( args[6] );
			m_PanelPosition = IfcDoorPanelPositionEnum::readStepData( args[7] );
			readEntityReference( args[8], m_ShapeAspectStyle, map );
		}
		void IfcDoorPanelProperties::setInverseCounterparts( shared_ptr<IfcBridgeEntity> ptr_self_entity )
		{
			IfcPreDefinedPropertySet::setInverseCounterparts( ptr_self_entity );
		}
		void IfcDoorPanelProperties::unlinkSelf()
		{
			IfcPreDefinedPropertySet::unlinkSelf();
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
