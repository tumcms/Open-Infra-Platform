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

#include "OpenInfraPlatform/IfcAlignment/model/IfcAlignmentP6Exception.h"
#include "OpenInfraPlatform/IfcAlignment/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment/writer/WriterUtil.h"
#include "OpenInfraPlatform/IfcAlignment/IfcAlignmentP6EntityEnums.h"
#include "include/IfcDoorLiningProperties.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcLengthMeasure.h"
#include "include/IfcNonNegativeLengthMeasure.h"
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
	namespace IfcAlignment
	{
		// ENTITY IfcDoorLiningProperties 
		IfcDoorLiningProperties::IfcDoorLiningProperties() { m_entity_enum = IFCDOORLININGPROPERTIES; }
		IfcDoorLiningProperties::IfcDoorLiningProperties( int id ) { m_id = id; m_entity_enum = IFCDOORLININGPROPERTIES; }
		IfcDoorLiningProperties::~IfcDoorLiningProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcDoorLiningProperties::setEntity( shared_ptr<IfcAlignmentP6Entity> other_entity )
		{
			shared_ptr<IfcDoorLiningProperties> other = dynamic_pointer_cast<IfcDoorLiningProperties>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_LiningDepth = other->m_LiningDepth;
			m_LiningThickness = other->m_LiningThickness;
			m_ThresholdDepth = other->m_ThresholdDepth;
			m_ThresholdThickness = other->m_ThresholdThickness;
			m_TransomThickness = other->m_TransomThickness;
			m_TransomOffset = other->m_TransomOffset;
			m_LiningOffset = other->m_LiningOffset;
			m_ThresholdOffset = other->m_ThresholdOffset;
			m_CasingThickness = other->m_CasingThickness;
			m_CasingDepth = other->m_CasingDepth;
			m_ShapeAspectStyle = other->m_ShapeAspectStyle;
			m_LiningToPanelOffsetX = other->m_LiningToPanelOffsetX;
			m_LiningToPanelOffsetY = other->m_LiningToPanelOffsetY;
		}
		void IfcDoorLiningProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCDOORLININGPROPERTIES" << "(";
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
			if( m_ThresholdDepth ) { m_ThresholdDepth->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ThresholdThickness ) { m_ThresholdThickness->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_TransomThickness ) { m_TransomThickness->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_TransomOffset ) { m_TransomOffset->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LiningOffset ) { m_LiningOffset->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ThresholdOffset ) { m_ThresholdOffset->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_CasingThickness ) { m_CasingThickness->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_CasingDepth ) { m_CasingDepth->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ShapeAspectStyle ) { stream << "#" << m_ShapeAspectStyle->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_LiningToPanelOffsetX ) { m_LiningToPanelOffsetX->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LiningToPanelOffsetY ) { m_LiningToPanelOffsetY->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcDoorLiningProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcDoorLiningProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignmentP6Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<17 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcDoorLiningProperties, expecting 17, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignmentP6Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>17 ){ std::cout << "Wrong parameter count for entity IfcDoorLiningProperties, expecting 17, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			m_LiningDepth = IfcPositiveLengthMeasure::readStepData( args[4] );
			m_LiningThickness = IfcNonNegativeLengthMeasure::readStepData( args[5] );
			m_ThresholdDepth = IfcPositiveLengthMeasure::readStepData( args[6] );
			m_ThresholdThickness = IfcNonNegativeLengthMeasure::readStepData( args[7] );
			m_TransomThickness = IfcNonNegativeLengthMeasure::readStepData( args[8] );
			m_TransomOffset = IfcLengthMeasure::readStepData( args[9] );
			m_LiningOffset = IfcLengthMeasure::readStepData( args[10] );
			m_ThresholdOffset = IfcLengthMeasure::readStepData( args[11] );
			m_CasingThickness = IfcPositiveLengthMeasure::readStepData( args[12] );
			m_CasingDepth = IfcPositiveLengthMeasure::readStepData( args[13] );
			readEntityReference( args[14], m_ShapeAspectStyle, map );
			m_LiningToPanelOffsetX = IfcLengthMeasure::readStepData( args[15] );
			m_LiningToPanelOffsetY = IfcLengthMeasure::readStepData( args[16] );
		}
		void IfcDoorLiningProperties::setInverseCounterparts( shared_ptr<IfcAlignmentP6Entity> ptr_self_entity )
		{
			IfcPreDefinedPropertySet::setInverseCounterparts( ptr_self_entity );
		}
		void IfcDoorLiningProperties::unlinkSelf()
		{
			IfcPreDefinedPropertySet::unlinkSelf();
		}
	} // end namespace IfcAlignment
} // end namespace OpenInfraPlatform
