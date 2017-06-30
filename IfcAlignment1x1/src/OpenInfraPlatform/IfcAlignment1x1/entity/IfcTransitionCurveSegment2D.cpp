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
#include "OpenInfraPlatform/IfcAlignment1x1/model/Exception.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1EntityEnums.h"
#include "IfcTransitionCurveSegment2D.h"
#include "IfcCartesianPoint.h"
#include "IfcPlaneAngleMeasure.h"
#include "IfcPositiveLengthMeasure.h"
#include "IfcLengthMeasure.h"
#include "IfcLengthMeasure.h"
#include "IfcBoolean.h"
#include "IfcBoolean.h"
#include "IfcTransitionCurveType.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcTransitionCurveSegment2D
			IfcTransitionCurveSegment2D::IfcTransitionCurveSegment2D() { m_entity_enum = IFCTRANSITIONCURVESEGMENT2D;}
			IfcTransitionCurveSegment2D::IfcTransitionCurveSegment2D( int id ) { m_id = id; m_entity_enum = IFCTRANSITIONCURVESEGMENT2D;}
			IfcTransitionCurveSegment2D::~IfcTransitionCurveSegment2D() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcTransitionCurveSegment2D::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcTransitionCurveSegment2D> other = std::dynamic_pointer_cast<IfcTransitionCurveSegment2D>(other_entity);
				if( !other) { return; }
				m_StartPoint = other->m_StartPoint;
				m_StartDirection = other->m_StartDirection;
				m_SegmentLength = other->m_SegmentLength;
				m_StartRadius = other->m_StartRadius;
				m_EndRadius = other->m_EndRadius;
				m_IsStartRadiusCCW = other->m_IsStartRadiusCCW;
				m_IsEndRadiusCCW = other->m_IsEndRadiusCCW;
				m_TransitionCurveType = other->m_TransitionCurveType;
			}
			void IfcTransitionCurveSegment2D::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCTRANSITIONCURVESEGMENT2D" << "(";
				if( m_StartPoint) { stream << "#" << m_StartPoint->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_StartDirection) { m_StartDirection->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_SegmentLength) { m_SegmentLength->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_StartRadius) { m_StartRadius->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_EndRadius) { m_EndRadius->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_IsStartRadiusCCW) { m_IsStartRadiusCCW->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_IsEndRadiusCCW) { m_IsEndRadiusCCW->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_TransitionCurveType) { m_TransitionCurveType->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcTransitionCurveSegment2D::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcTransitionCurveSegment2D::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<8 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcTransitionCurveSegment2D, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<8 ){ std::cout << "Wrong parameter count for entity IfcTransitionCurveSegment2D, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				readEntityReference( args[0], m_StartPoint, map);
				m_StartDirection = IfcPlaneAngleMeasure::readStepData( args[1] );
				m_SegmentLength = IfcPositiveLengthMeasure::readStepData( args[2] );
				m_StartRadius = IfcLengthMeasure::readStepData( args[3] );
				m_EndRadius = IfcLengthMeasure::readStepData( args[4] );
				m_IsStartRadiusCCW = IfcBoolean::readStepData( args[5] );
				m_IsEndRadiusCCW = IfcBoolean::readStepData( args[6] );
				m_TransitionCurveType = IfcTransitionCurveType::readStepData( args[7] );
			}
			void IfcTransitionCurveSegment2D::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcCurveSegment2D::setInverseCounterparts(ptr_self_entity);
			}
			void IfcTransitionCurveSegment2D::unlinkSelf()
			{
				IfcCurveSegment2D::unlinkSelf();
			}
	}
}
