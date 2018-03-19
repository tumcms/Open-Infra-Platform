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
#include "IfcGeometricRepresentationSubContext.h"
#include "IfcLabel.h"
#include "IfcLabel.h"
#include "IfcDimensionCount.h"
#include "IfcReal.h"
#include "IfcAxis2Placement.h"
#include "IfcDirection.h"
#include "IfcGeometricRepresentationContext.h"
#include "IfcPositiveRatioMeasure.h"
#include "IfcGeometricProjectionEnum.h"
#include "IfcLabel.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcGeometricRepresentationSubContext
			IfcGeometricRepresentationSubContext::IfcGeometricRepresentationSubContext() { m_entity_enum = IFCGEOMETRICREPRESENTATIONSUBCONTEXT;}
			IfcGeometricRepresentationSubContext::IfcGeometricRepresentationSubContext( int id ) { m_id = id; m_entity_enum = IFCGEOMETRICREPRESENTATIONSUBCONTEXT;}
			IfcGeometricRepresentationSubContext::~IfcGeometricRepresentationSubContext() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcGeometricRepresentationSubContext::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcGeometricRepresentationSubContext> other = std::dynamic_pointer_cast<IfcGeometricRepresentationSubContext>(other_entity);
				if( !other) { return; }
				m_ContextIdentifier = other->m_ContextIdentifier;
				m_ContextType = other->m_ContextType;
				m_CoordinateSpaceDimension = other->m_CoordinateSpaceDimension;
				m_Precision = other->m_Precision;
				m_WorldCoordinateSystem = other->m_WorldCoordinateSystem;
				m_TrueNorth = other->m_TrueNorth;
				m_ParentContext = other->m_ParentContext;
				m_TargetScale = other->m_TargetScale;
				m_TargetView = other->m_TargetView;
				m_UserDefinedTargetView = other->m_UserDefinedTargetView;
			}
			void IfcGeometricRepresentationSubContext::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCGEOMETRICREPRESENTATIONSUBCONTEXT" << "(";
				if( m_ContextIdentifier) { m_ContextIdentifier->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_ContextType) { m_ContextType->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_CoordinateSpaceDimension) { m_CoordinateSpaceDimension->getStepParameter( stream ); } else { stream << "*"; }
				stream << ",";
				if( m_Precision) { m_Precision->getStepParameter( stream ); } else { stream << "*"; }
				stream << ",";
				if( m_WorldCoordinateSystem) { m_WorldCoordinateSystem->getStepParameter( stream ); } else { stream << "*"; }
				stream << ",";
				if( m_TrueNorth) { stream << "#" << m_TrueNorth->getId(); } else { stream << "*"; }
				stream << ",";
				if( m_ParentContext) { stream << "#" << m_ParentContext->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_TargetScale) { m_TargetScale->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_TargetView) { m_TargetView->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_UserDefinedTargetView) { m_UserDefinedTargetView->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcGeometricRepresentationSubContext::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcGeometricRepresentationSubContext::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<10 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcGeometricRepresentationSubContext, expecting 10, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<10 ){ std::cout << "Wrong parameter count for entity IfcGeometricRepresentationSubContext, expecting 10, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_ContextIdentifier = IfcLabel::readStepData( args[0] );
				m_ContextType = IfcLabel::readStepData( args[1] );
				m_CoordinateSpaceDimension = IfcDimensionCount::readStepData( args[2] );
				m_Precision = IfcReal::readStepData( args[3] );
				m_WorldCoordinateSystem = IfcAxis2Placement::readStepData( args[4], map );
				readEntityReference( args[5], m_TrueNorth, map);
				readEntityReference( args[6], m_ParentContext, map);
				m_TargetScale = IfcPositiveRatioMeasure::readStepData( args[7] );
				m_TargetView = IfcGeometricProjectionEnum::readStepData( args[8] );
				m_UserDefinedTargetView = IfcLabel::readStepData( args[9] );
			}
			void IfcGeometricRepresentationSubContext::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcGeometricRepresentationContext::setInverseCounterparts(ptr_self_entity);
			}
			void IfcGeometricRepresentationSubContext::unlinkSelf()
			{
				IfcGeometricRepresentationContext::unlinkSelf();
			}
	}
}
