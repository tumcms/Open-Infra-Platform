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

#include "OpenInfraPlatform/IfcRoad/model/IfcRoadException.h"
#include "OpenInfraPlatform/IfcRoad/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcRoad/writer/WriterUtil.h"
#include "OpenInfraPlatform/IfcRoad/IfcRoadEntityEnums.h"
#include "include/IfcAxis2Placement2D.h"
#include "include/IfcExternalReferenceRelationship.h"
#include "include/IfcLabel.h"
#include "include/IfcNonNegativeLengthMeasure.h"
#include "include/IfcPositiveLengthMeasure.h"
#include "include/IfcProfileProperties.h"
#include "include/IfcProfileTypeEnum.h"
#include "include/IfcRectangleHollowProfileDef.h"

namespace OpenInfraPlatform
{
	namespace IfcRoad
	{
		// ENTITY IfcRectangleHollowProfileDef 
		IfcRectangleHollowProfileDef::IfcRectangleHollowProfileDef() { m_entity_enum = IFCRECTANGLEHOLLOWPROFILEDEF; }
		IfcRectangleHollowProfileDef::IfcRectangleHollowProfileDef( int id ) { m_id = id; m_entity_enum = IFCRECTANGLEHOLLOWPROFILEDEF; }
		IfcRectangleHollowProfileDef::~IfcRectangleHollowProfileDef() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcRectangleHollowProfileDef::setEntity( shared_ptr<IfcRoadEntity> other_entity )
		{
			shared_ptr<IfcRectangleHollowProfileDef> other = dynamic_pointer_cast<IfcRectangleHollowProfileDef>(other_entity);
			if( !other) { return; }
			m_ProfileType = other->m_ProfileType;
			m_ProfileName = other->m_ProfileName;
			m_Position = other->m_Position;
			m_XDim = other->m_XDim;
			m_YDim = other->m_YDim;
			m_WallThickness = other->m_WallThickness;
			m_InnerFilletRadius = other->m_InnerFilletRadius;
			m_OuterFilletRadius = other->m_OuterFilletRadius;
		}
		void IfcRectangleHollowProfileDef::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCRECTANGLEHOLLOWPROFILEDEF" << "(";
			if( m_ProfileType ) { m_ProfileType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ProfileName ) { m_ProfileName->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Position ) { stream << "#" << m_Position->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_XDim ) { m_XDim->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_YDim ) { m_YDim->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_WallThickness ) { m_WallThickness->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_InnerFilletRadius ) { m_InnerFilletRadius->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_OuterFilletRadius ) { m_OuterFilletRadius->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcRectangleHollowProfileDef::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcRectangleHollowProfileDef::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcRoadEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<8 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcRectangleHollowProfileDef, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcRoadException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>8 ){ std::cout << "Wrong parameter count for entity IfcRectangleHollowProfileDef, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_ProfileType = IfcProfileTypeEnum::readStepData( args[0] );
			m_ProfileName = IfcLabel::readStepData( args[1] );
			readEntityReference( args[2], m_Position, map );
			m_XDim = IfcPositiveLengthMeasure::readStepData( args[3] );
			m_YDim = IfcPositiveLengthMeasure::readStepData( args[4] );
			m_WallThickness = IfcPositiveLengthMeasure::readStepData( args[5] );
			m_InnerFilletRadius = IfcNonNegativeLengthMeasure::readStepData( args[6] );
			m_OuterFilletRadius = IfcNonNegativeLengthMeasure::readStepData( args[7] );
		}
		void IfcRectangleHollowProfileDef::setInverseCounterparts( shared_ptr<IfcRoadEntity> ptr_self_entity )
		{
			IfcRectangleProfileDef::setInverseCounterparts( ptr_self_entity );
		}
		void IfcRectangleHollowProfileDef::unlinkSelf()
		{
			IfcRectangleProfileDef::unlinkSelf();
		}
	} // end namespace IfcRoad
} // end namespace OpenInfraPlatform
