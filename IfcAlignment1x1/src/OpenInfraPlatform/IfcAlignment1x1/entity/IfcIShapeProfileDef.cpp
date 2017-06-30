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
#include "IfcIShapeProfileDef.h"
#include "IfcProfileTypeEnum.h"
#include "IfcLabel.h"
#include "IfcAxis2Placement2D.h"
#include "IfcPositiveLengthMeasure.h"
#include "IfcPositiveLengthMeasure.h"
#include "IfcPositiveLengthMeasure.h"
#include "IfcPositiveLengthMeasure.h"
#include "IfcNonNegativeLengthMeasure.h"
#include "IfcNonNegativeLengthMeasure.h"
#include "IfcPlaneAngleMeasure.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcIShapeProfileDef
			IfcIShapeProfileDef::IfcIShapeProfileDef() { m_entity_enum = IFCISHAPEPROFILEDEF;}
			IfcIShapeProfileDef::IfcIShapeProfileDef( int id ) { m_id = id; m_entity_enum = IFCISHAPEPROFILEDEF;}
			IfcIShapeProfileDef::~IfcIShapeProfileDef() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcIShapeProfileDef::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcIShapeProfileDef> other = std::dynamic_pointer_cast<IfcIShapeProfileDef>(other_entity);
				if( !other) { return; }
				m_ProfileType = other->m_ProfileType;
				m_ProfileName = other->m_ProfileName;
				m_Position = other->m_Position;
				m_OverallWidth = other->m_OverallWidth;
				m_OverallDepth = other->m_OverallDepth;
				m_WebThickness = other->m_WebThickness;
				m_FlangeThickness = other->m_FlangeThickness;
				m_FilletRadius = other->m_FilletRadius;
				m_FlangeEdgeRadius = other->m_FlangeEdgeRadius;
				m_FlangeSlope = other->m_FlangeSlope;
			}
			void IfcIShapeProfileDef::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCISHAPEPROFILEDEF" << "(";
				if( m_ProfileType) { m_ProfileType->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_ProfileName) { m_ProfileName->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Position) { stream << "#" << m_Position->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_OverallWidth) { m_OverallWidth->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_OverallDepth) { m_OverallDepth->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_WebThickness) { m_WebThickness->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_FlangeThickness) { m_FlangeThickness->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_FilletRadius) { m_FilletRadius->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_FlangeEdgeRadius) { m_FlangeEdgeRadius->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_FlangeSlope) { m_FlangeSlope->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcIShapeProfileDef::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcIShapeProfileDef::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<10 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcIShapeProfileDef, expecting 10, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<10 ){ std::cout << "Wrong parameter count for entity IfcIShapeProfileDef, expecting 10, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_ProfileType = IfcProfileTypeEnum::readStepData( args[0] );
				m_ProfileName = IfcLabel::readStepData( args[1] );
				readEntityReference( args[2], m_Position, map);
				m_OverallWidth = IfcPositiveLengthMeasure::readStepData( args[3] );
				m_OverallDepth = IfcPositiveLengthMeasure::readStepData( args[4] );
				m_WebThickness = IfcPositiveLengthMeasure::readStepData( args[5] );
				m_FlangeThickness = IfcPositiveLengthMeasure::readStepData( args[6] );
				m_FilletRadius = IfcNonNegativeLengthMeasure::readStepData( args[7] );
				m_FlangeEdgeRadius = IfcNonNegativeLengthMeasure::readStepData( args[8] );
				m_FlangeSlope = IfcPlaneAngleMeasure::readStepData( args[9] );
			}
			void IfcIShapeProfileDef::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcParameterizedProfileDef::setInverseCounterparts(ptr_self_entity);
			}
			void IfcIShapeProfileDef::unlinkSelf()
			{
				IfcParameterizedProfileDef::unlinkSelf();
			}
	}
}
