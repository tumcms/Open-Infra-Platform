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
#include "include/IfcAxis2Placement2D.h"
#include "include/IfcCraneRailAShapeProfileDef.h"
#include "include/IfcLabel.h"
#include "include/IfcPositiveLengthMeasure.h"
#include "include/IfcProfileTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcCraneRailAShapeProfileDef 
		IfcCraneRailAShapeProfileDef::IfcCraneRailAShapeProfileDef() { m_entity_enum = IFCCRANERAILASHAPEPROFILEDEF; }
		IfcCraneRailAShapeProfileDef::IfcCraneRailAShapeProfileDef( int id ) { m_id = id; m_entity_enum = IFCCRANERAILASHAPEPROFILEDEF; }
		IfcCraneRailAShapeProfileDef::~IfcCraneRailAShapeProfileDef() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcCraneRailAShapeProfileDef::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcCraneRailAShapeProfileDef> other = dynamic_pointer_cast<IfcCraneRailAShapeProfileDef>(other_entity);
			if( !other) { return; }
			m_ProfileType = other->m_ProfileType;
			m_ProfileName = other->m_ProfileName;
			m_Position = other->m_Position;
			m_OverallHeight = other->m_OverallHeight;
			m_BaseWidth2 = other->m_BaseWidth2;
			m_Radius = other->m_Radius;
			m_HeadWidth = other->m_HeadWidth;
			m_HeadDepth2 = other->m_HeadDepth2;
			m_HeadDepth3 = other->m_HeadDepth3;
			m_WebThickness = other->m_WebThickness;
			m_BaseWidth4 = other->m_BaseWidth4;
			m_BaseDepth1 = other->m_BaseDepth1;
			m_BaseDepth2 = other->m_BaseDepth2;
			m_BaseDepth3 = other->m_BaseDepth3;
			m_CentreOfGravityInY = other->m_CentreOfGravityInY;
		}
		void IfcCraneRailAShapeProfileDef::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCCRANERAILASHAPEPROFILEDEF" << "(";
			if( m_ProfileType ) { m_ProfileType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ProfileName ) { m_ProfileName->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Position ) { stream << "#" << m_Position->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_OverallHeight ) { m_OverallHeight->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_BaseWidth2 ) { m_BaseWidth2->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Radius ) { m_Radius->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_HeadWidth ) { m_HeadWidth->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_HeadDepth2 ) { m_HeadDepth2->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_HeadDepth3 ) { m_HeadDepth3->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_WebThickness ) { m_WebThickness->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_BaseWidth4 ) { m_BaseWidth4->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_BaseDepth1 ) { m_BaseDepth1->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_BaseDepth2 ) { m_BaseDepth2->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_BaseDepth3 ) { m_BaseDepth3->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_CentreOfGravityInY ) { m_CentreOfGravityInY->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcCraneRailAShapeProfileDef::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcCraneRailAShapeProfileDef::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<15 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcCraneRailAShapeProfileDef, expecting 15, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>15 ){ std::cout << "Wrong parameter count for entity IfcCraneRailAShapeProfileDef, expecting 15, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_ProfileType = IfcProfileTypeEnum::readStepData( args[0] );
			m_ProfileName = IfcLabel::readStepData( args[1] );
			readEntityReference( args[2], m_Position, map );
			m_OverallHeight = IfcPositiveLengthMeasure::readStepData( args[3] );
			m_BaseWidth2 = IfcPositiveLengthMeasure::readStepData( args[4] );
			m_Radius = IfcPositiveLengthMeasure::readStepData( args[5] );
			m_HeadWidth = IfcPositiveLengthMeasure::readStepData( args[6] );
			m_HeadDepth2 = IfcPositiveLengthMeasure::readStepData( args[7] );
			m_HeadDepth3 = IfcPositiveLengthMeasure::readStepData( args[8] );
			m_WebThickness = IfcPositiveLengthMeasure::readStepData( args[9] );
			m_BaseWidth4 = IfcPositiveLengthMeasure::readStepData( args[10] );
			m_BaseDepth1 = IfcPositiveLengthMeasure::readStepData( args[11] );
			m_BaseDepth2 = IfcPositiveLengthMeasure::readStepData( args[12] );
			m_BaseDepth3 = IfcPositiveLengthMeasure::readStepData( args[13] );
			m_CentreOfGravityInY = IfcPositiveLengthMeasure::readStepData( args[14] );
		}
		void IfcCraneRailAShapeProfileDef::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcParameterizedProfileDef::setInverseCounterparts( ptr_self_entity );
		}
		void IfcCraneRailAShapeProfileDef::unlinkSelf()
		{
			IfcParameterizedProfileDef::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
