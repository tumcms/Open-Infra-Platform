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
#include "include/IfcAlignment2DVerSegLine.h"
#include "include/IfcAlignment2DVertical.h"
#include "include/IfcBoolean.h"
#include "include/IfcLabel.h"
#include "include/IfcLengthMeasure.h"
#include "include/IfcPositiveLengthMeasure.h"
#include "include/IfcRatioMeasure.h"

namespace OpenInfraPlatform
{
	namespace IfcRoad
	{
		// ENTITY IfcAlignment2DVerSegLine 
		IfcAlignment2DVerSegLine::IfcAlignment2DVerSegLine() { m_entity_enum = IFCALIGNMENT2DVERSEGLINE; }
		IfcAlignment2DVerSegLine::IfcAlignment2DVerSegLine( int id ) { m_id = id; m_entity_enum = IFCALIGNMENT2DVERSEGLINE; }
		IfcAlignment2DVerSegLine::~IfcAlignment2DVerSegLine() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcAlignment2DVerSegLine::setEntity( shared_ptr<IfcRoadEntity> other_entity )
		{
			shared_ptr<IfcAlignment2DVerSegLine> other = dynamic_pointer_cast<IfcAlignment2DVerSegLine>(other_entity);
			if( !other) { return; }
			m_TangentialContinuity = other->m_TangentialContinuity;
			m_StartTag = other->m_StartTag;
			m_EndTag = other->m_EndTag;
			m_StartDistAlong = other->m_StartDistAlong;
			m_HorizontalLength = other->m_HorizontalLength;
			m_StartHeight = other->m_StartHeight;
			m_StartGradient = other->m_StartGradient;
		}
		void IfcAlignment2DVerSegLine::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCALIGNMENT2DVERSEGLINE" << "(";
			if( m_TangentialContinuity ) { m_TangentialContinuity->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_StartTag ) { m_StartTag->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_EndTag ) { m_EndTag->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_StartDistAlong ) { m_StartDistAlong->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_HorizontalLength ) { m_HorizontalLength->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_StartHeight ) { m_StartHeight->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_StartGradient ) { m_StartGradient->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcAlignment2DVerSegLine::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcAlignment2DVerSegLine::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcRoadEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<7 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcAlignment2DVerSegLine, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcRoadException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>7 ){ std::cout << "Wrong parameter count for entity IfcAlignment2DVerSegLine, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_TangentialContinuity = IfcBoolean::readStepData( args[0] );
			m_StartTag = IfcLabel::readStepData( args[1] );
			m_EndTag = IfcLabel::readStepData( args[2] );
			m_StartDistAlong = IfcLengthMeasure::readStepData( args[3] );
			m_HorizontalLength = IfcPositiveLengthMeasure::readStepData( args[4] );
			m_StartHeight = IfcLengthMeasure::readStepData( args[5] );
			m_StartGradient = IfcRatioMeasure::readStepData( args[6] );
		}
		void IfcAlignment2DVerSegLine::setInverseCounterparts( shared_ptr<IfcRoadEntity> ptr_self_entity )
		{
			IfcAlignment2DVerticalSegment::setInverseCounterparts( ptr_self_entity );
		}
		void IfcAlignment2DVerSegLine::unlinkSelf()
		{
			IfcAlignment2DVerticalSegment::unlinkSelf();
		}
	} // end namespace IfcRoad
} // end namespace OpenInfraPlatform
