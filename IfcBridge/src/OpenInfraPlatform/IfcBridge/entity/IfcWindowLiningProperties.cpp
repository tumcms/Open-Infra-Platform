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
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcLengthMeasure.h"
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
#include "include/IfcWindowLiningProperties.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// ENTITY IfcWindowLiningProperties 
		IfcWindowLiningProperties::IfcWindowLiningProperties() { m_entity_enum = IFCWINDOWLININGPROPERTIES; }
		IfcWindowLiningProperties::IfcWindowLiningProperties( int id ) { m_id = id; m_entity_enum = IFCWINDOWLININGPROPERTIES; }
		IfcWindowLiningProperties::~IfcWindowLiningProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcWindowLiningProperties::setEntity( shared_ptr<IfcBridgeEntity> other_entity )
		{
			shared_ptr<IfcWindowLiningProperties> other = dynamic_pointer_cast<IfcWindowLiningProperties>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_LiningDepth = other->m_LiningDepth;
			m_LiningThickness = other->m_LiningThickness;
			m_TransomThickness = other->m_TransomThickness;
			m_MullionThickness = other->m_MullionThickness;
			m_FirstTransomOffset = other->m_FirstTransomOffset;
			m_SecondTransomOffset = other->m_SecondTransomOffset;
			m_FirstMullionOffset = other->m_FirstMullionOffset;
			m_SecondMullionOffset = other->m_SecondMullionOffset;
			m_ShapeAspectStyle = other->m_ShapeAspectStyle;
			m_LiningOffset = other->m_LiningOffset;
			m_LiningToPanelOffsetX = other->m_LiningToPanelOffsetX;
			m_LiningToPanelOffsetY = other->m_LiningToPanelOffsetY;
		}
		void IfcWindowLiningProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCWINDOWLININGPROPERTIES" << "(";
			if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LiningDepth ) { m_LiningDepth->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LiningThickness ) { m_LiningThickness->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_TransomThickness ) { m_TransomThickness->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MullionThickness ) { m_MullionThickness->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_FirstTransomOffset ) { m_FirstTransomOffset->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_SecondTransomOffset ) { m_SecondTransomOffset->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_FirstMullionOffset ) { m_FirstMullionOffset->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_SecondMullionOffset ) { m_SecondMullionOffset->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ShapeAspectStyle ) { stream << "#" << m_ShapeAspectStyle->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_LiningOffset ) { m_LiningOffset->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LiningToPanelOffsetX ) { m_LiningToPanelOffsetX->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LiningToPanelOffsetY ) { m_LiningToPanelOffsetY->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcWindowLiningProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcWindowLiningProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcBridgeEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<16 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcWindowLiningProperties, expecting 16, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcBridgeException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>16 ){ std::cout << "Wrong parameter count for entity IfcWindowLiningProperties, expecting 16, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			m_LiningDepth = IfcPositiveLengthMeasure::readStepData( args[4] );
			m_LiningThickness = IfcPositiveLengthMeasure::readStepData( args[5] );
			m_TransomThickness = IfcPositiveLengthMeasure::readStepData( args[6] );
			m_MullionThickness = IfcPositiveLengthMeasure::readStepData( args[7] );
			m_FirstTransomOffset = IfcNormalisedRatioMeasure::readStepData( args[8] );
			m_SecondTransomOffset = IfcNormalisedRatioMeasure::readStepData( args[9] );
			m_FirstMullionOffset = IfcNormalisedRatioMeasure::readStepData( args[10] );
			m_SecondMullionOffset = IfcNormalisedRatioMeasure::readStepData( args[11] );
			readEntityReference( args[12], m_ShapeAspectStyle, map );
			m_LiningOffset = IfcLengthMeasure::readStepData( args[13] );
			m_LiningToPanelOffsetX = IfcLengthMeasure::readStepData( args[14] );
			m_LiningToPanelOffsetY = IfcLengthMeasure::readStepData( args[15] );
		}
		void IfcWindowLiningProperties::setInverseCounterparts( shared_ptr<IfcBridgeEntity> ptr_self_entity )
		{
			IfcPreDefinedPropertySet::setInverseCounterparts( ptr_self_entity );
		}
		void IfcWindowLiningProperties::unlinkSelf()
		{
			IfcPreDefinedPropertySet::unlinkSelf();
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
