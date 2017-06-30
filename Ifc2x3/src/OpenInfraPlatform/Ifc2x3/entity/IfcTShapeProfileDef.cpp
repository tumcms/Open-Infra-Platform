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
#include "include/IfcLabel.h"
#include "include/IfcPlaneAngleMeasure.h"
#include "include/IfcPositiveLengthMeasure.h"
#include "include/IfcProfileTypeEnum.h"
#include "include/IfcTShapeProfileDef.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcTShapeProfileDef 
		IfcTShapeProfileDef::IfcTShapeProfileDef() { m_entity_enum = IFCTSHAPEPROFILEDEF; }
		IfcTShapeProfileDef::IfcTShapeProfileDef( int id ) { m_id = id; m_entity_enum = IFCTSHAPEPROFILEDEF; }
		IfcTShapeProfileDef::~IfcTShapeProfileDef() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcTShapeProfileDef::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcTShapeProfileDef> other = dynamic_pointer_cast<IfcTShapeProfileDef>(other_entity);
			if( !other) { return; }
			m_ProfileType = other->m_ProfileType;
			m_ProfileName = other->m_ProfileName;
			m_Position = other->m_Position;
			m_Depth = other->m_Depth;
			m_FlangeWidth = other->m_FlangeWidth;
			m_WebThickness = other->m_WebThickness;
			m_FlangeThickness = other->m_FlangeThickness;
			m_FilletRadius = other->m_FilletRadius;
			m_FlangeEdgeRadius = other->m_FlangeEdgeRadius;
			m_WebEdgeRadius = other->m_WebEdgeRadius;
			m_WebSlope = other->m_WebSlope;
			m_FlangeSlope = other->m_FlangeSlope;
			m_CentreOfGravityInY = other->m_CentreOfGravityInY;
		}
		void IfcTShapeProfileDef::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCTSHAPEPROFILEDEF" << "(";
			if( m_ProfileType ) { m_ProfileType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ProfileName ) { m_ProfileName->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Position ) { stream << "#" << m_Position->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Depth ) { m_Depth->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_FlangeWidth ) { m_FlangeWidth->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_WebThickness ) { m_WebThickness->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_FlangeThickness ) { m_FlangeThickness->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_FilletRadius ) { m_FilletRadius->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_FlangeEdgeRadius ) { m_FlangeEdgeRadius->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_WebEdgeRadius ) { m_WebEdgeRadius->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_WebSlope ) { m_WebSlope->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_FlangeSlope ) { m_FlangeSlope->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_CentreOfGravityInY ) { m_CentreOfGravityInY->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcTShapeProfileDef::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcTShapeProfileDef::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<13 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcTShapeProfileDef, expecting 13, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>13 ){ std::cout << "Wrong parameter count for entity IfcTShapeProfileDef, expecting 13, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_ProfileType = IfcProfileTypeEnum::readStepData( args[0] );
			m_ProfileName = IfcLabel::readStepData( args[1] );
			readEntityReference( args[2], m_Position, map );
			m_Depth = IfcPositiveLengthMeasure::readStepData( args[3] );
			m_FlangeWidth = IfcPositiveLengthMeasure::readStepData( args[4] );
			m_WebThickness = IfcPositiveLengthMeasure::readStepData( args[5] );
			m_FlangeThickness = IfcPositiveLengthMeasure::readStepData( args[6] );
			m_FilletRadius = IfcPositiveLengthMeasure::readStepData( args[7] );
			m_FlangeEdgeRadius = IfcPositiveLengthMeasure::readStepData( args[8] );
			m_WebEdgeRadius = IfcPositiveLengthMeasure::readStepData( args[9] );
			m_WebSlope = IfcPlaneAngleMeasure::readStepData( args[10] );
			m_FlangeSlope = IfcPlaneAngleMeasure::readStepData( args[11] );
			m_CentreOfGravityInY = IfcPositiveLengthMeasure::readStepData( args[12] );
		}
		void IfcTShapeProfileDef::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcParameterizedProfileDef::setInverseCounterparts( ptr_self_entity );
		}
		void IfcTShapeProfileDef::unlinkSelf()
		{
			IfcParameterizedProfileDef::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
