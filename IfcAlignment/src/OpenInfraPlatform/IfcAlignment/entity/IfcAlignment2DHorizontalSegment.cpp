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
#include "include/IfcAlignment2DHorizontal.h"
#include "include/IfcAlignment2DHorizontalSegment.h"
#include "include/IfcBoolean.h"
#include "include/IfcCurveSegment2D.h"
#include "include/IfcLabel.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment
	{
		// ENTITY IfcAlignment2DHorizontalSegment 
		IfcAlignment2DHorizontalSegment::IfcAlignment2DHorizontalSegment() { m_entity_enum = IFCALIGNMENT2DHORIZONTALSEGMENT; }
		IfcAlignment2DHorizontalSegment::IfcAlignment2DHorizontalSegment( int id ) { m_id = id; m_entity_enum = IFCALIGNMENT2DHORIZONTALSEGMENT; }
		IfcAlignment2DHorizontalSegment::~IfcAlignment2DHorizontalSegment() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcAlignment2DHorizontalSegment::setEntity( shared_ptr<IfcAlignmentP6Entity> other_entity )
		{
			shared_ptr<IfcAlignment2DHorizontalSegment> other = dynamic_pointer_cast<IfcAlignment2DHorizontalSegment>(other_entity);
			if( !other) { return; }
			m_TangentialContinuity = other->m_TangentialContinuity;
			m_StartTag = other->m_StartTag;
			m_EndTag = other->m_EndTag;
			m_CurveGeometry = other->m_CurveGeometry;
		}
		void IfcAlignment2DHorizontalSegment::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCALIGNMENT2DHORIZONTALSEGMENT" << "(";
			if( m_TangentialContinuity ) { m_TangentialContinuity->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_StartTag ) { m_StartTag->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_EndTag ) { m_EndTag->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_CurveGeometry ) { stream << "#" << m_CurveGeometry->getId(); } else { stream << "$"; }
			stream << ");";
		}
		void IfcAlignment2DHorizontalSegment::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcAlignment2DHorizontalSegment::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignmentP6Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<4 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcAlignment2DHorizontalSegment, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignmentP6Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>4 ){ std::cout << "Wrong parameter count for entity IfcAlignment2DHorizontalSegment, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_TangentialContinuity = IfcBoolean::readStepData( args[0] );
			m_StartTag = IfcLabel::readStepData( args[1] );
			m_EndTag = IfcLabel::readStepData( args[2] );
			readEntityReference( args[3], m_CurveGeometry, map );
		}
		void IfcAlignment2DHorizontalSegment::setInverseCounterparts( shared_ptr<IfcAlignmentP6Entity> ptr_self_entity )
		{
			IfcAlignment2DSegment::setInverseCounterparts( ptr_self_entity );
		}
		void IfcAlignment2DHorizontalSegment::unlinkSelf()
		{
			IfcAlignment2DSegment::unlinkSelf();
		}
	} // end namespace IfcAlignment
} // end namespace OpenInfraPlatform
