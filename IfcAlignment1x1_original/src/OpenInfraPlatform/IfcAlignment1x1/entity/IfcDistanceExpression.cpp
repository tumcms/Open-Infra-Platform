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
#include "IfcDistanceExpression.h"
#include "IfcLengthMeasure.h"
#include "IfcLengthMeasure.h"
#include "IfcLengthMeasure.h"
#include "IfcLengthMeasure.h"
#include "IfcBoolean.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcDistanceExpression
			IfcDistanceExpression::IfcDistanceExpression() { m_entity_enum = IFCDISTANCEEXPRESSION;}
			IfcDistanceExpression::IfcDistanceExpression( int id ) { m_id = id; m_entity_enum = IFCDISTANCEEXPRESSION;}
			IfcDistanceExpression::~IfcDistanceExpression() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcDistanceExpression::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcDistanceExpression> other = std::dynamic_pointer_cast<IfcDistanceExpression>(other_entity);
				if( !other) { return; }
				m_DistanceAlong = other->m_DistanceAlong;
				m_OffsetLateral = other->m_OffsetLateral;
				m_OffsetVertical = other->m_OffsetVertical;
				m_OffsetLongitudinal = other->m_OffsetLongitudinal;
				m_AlongHorizontal = other->m_AlongHorizontal;
			}
			void IfcDistanceExpression::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCDISTANCEEXPRESSION" << "(";
				if( m_DistanceAlong) { m_DistanceAlong->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_OffsetLateral) { m_OffsetLateral->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_OffsetVertical) { m_OffsetVertical->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_OffsetLongitudinal) { m_OffsetLongitudinal->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_AlongHorizontal) { m_AlongHorizontal->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcDistanceExpression::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcDistanceExpression::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<5 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcDistanceExpression, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<5 ){ std::cout << "Wrong parameter count for entity IfcDistanceExpression, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_DistanceAlong = IfcLengthMeasure::readStepData( args[0] );
				m_OffsetLateral = IfcLengthMeasure::readStepData( args[1] );
				m_OffsetVertical = IfcLengthMeasure::readStepData( args[2] );
				m_OffsetLongitudinal = IfcLengthMeasure::readStepData( args[3] );
				m_AlongHorizontal = IfcBoolean::readStepData( args[4] );
			}
			void IfcDistanceExpression::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
			}
			void IfcDistanceExpression::unlinkSelf()
			{
			}
	}
}
