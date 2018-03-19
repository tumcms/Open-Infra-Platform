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
#include "IfcAlignment2DSegment.h"
#include "IfcBoolean.h"
#include "IfcLabel.h"
#include "IfcLabel.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcAlignment2DSegment
			IfcAlignment2DSegment::IfcAlignment2DSegment() { m_entity_enum = IFCALIGNMENT2DSEGMENT;}
			IfcAlignment2DSegment::IfcAlignment2DSegment( int id ) { m_id = id; m_entity_enum = IFCALIGNMENT2DSEGMENT;}
			IfcAlignment2DSegment::~IfcAlignment2DSegment() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcAlignment2DSegment::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcAlignment2DSegment> other = std::dynamic_pointer_cast<IfcAlignment2DSegment>(other_entity);
				if( !other) { return; }
				m_TangentialContinuity = other->m_TangentialContinuity;
				m_StartTag = other->m_StartTag;
				m_EndTag = other->m_EndTag;
			}
			void IfcAlignment2DSegment::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCALIGNMENT2DSEGMENT" << "(";
				if( m_TangentialContinuity) { m_TangentialContinuity->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_StartTag) { m_StartTag->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_EndTag) { m_EndTag->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcAlignment2DSegment::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcAlignment2DSegment::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<3 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcAlignment2DSegment, expecting 3, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<3 ){ std::cout << "Wrong parameter count for entity IfcAlignment2DSegment, expecting 3, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_TangentialContinuity = IfcBoolean::readStepData( args[0] );
				m_StartTag = IfcLabel::readStepData( args[1] );
				m_EndTag = IfcLabel::readStepData( args[2] );
			}
			void IfcAlignment2DSegment::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
			}
			void IfcAlignment2DSegment::unlinkSelf()
			{
			}
	}
}
