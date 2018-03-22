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
#include "IfcGeometricRepresentationContext.h"
#include "IfcLabel.h"
#include "IfcLabel.h"
#include "IfcDimensionCount.h"
#include "IfcReal.h"
#include "IfcAxis2Placement.h"
#include "IfcDirection.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcGeometricRepresentationContext
			IfcGeometricRepresentationContext::IfcGeometricRepresentationContext() { m_entity_enum = IFCGEOMETRICREPRESENTATIONCONTEXT;}
			IfcGeometricRepresentationContext::IfcGeometricRepresentationContext( int id ) { m_id = id; m_entity_enum = IFCGEOMETRICREPRESENTATIONCONTEXT;}
			IfcGeometricRepresentationContext::~IfcGeometricRepresentationContext() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcGeometricRepresentationContext::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcGeometricRepresentationContext> other = std::dynamic_pointer_cast<IfcGeometricRepresentationContext>(other_entity);
				if( !other) { return; }
				m_ContextIdentifier = other->m_ContextIdentifier;
				m_ContextType = other->m_ContextType;
				m_CoordinateSpaceDimension = other->m_CoordinateSpaceDimension;
				m_Precision = other->m_Precision;
				m_WorldCoordinateSystem = other->m_WorldCoordinateSystem;
				m_TrueNorth = other->m_TrueNorth;
			}
			void IfcGeometricRepresentationContext::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCGEOMETRICREPRESENTATIONCONTEXT" << "(";
				if( m_ContextIdentifier) { m_ContextIdentifier->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_ContextType) { m_ContextType->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_CoordinateSpaceDimension) { m_CoordinateSpaceDimension->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Precision) { m_Precision->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_WorldCoordinateSystem) { m_WorldCoordinateSystem->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_TrueNorth) { stream << "#" << m_TrueNorth->getId(); } else { stream << "$"; }
				stream << ");";
			}
			void IfcGeometricRepresentationContext::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcGeometricRepresentationContext::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<6 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcGeometricRepresentationContext, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<6 ){ std::cout << "Wrong parameter count for entity IfcGeometricRepresentationContext, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_ContextIdentifier = IfcLabel::readStepData( args[0] );
				m_ContextType = IfcLabel::readStepData( args[1] );
				m_CoordinateSpaceDimension = IfcDimensionCount::readStepData( args[2] );
				m_Precision = IfcReal::readStepData( args[3] );
				m_WorldCoordinateSystem = IfcAxis2Placement::readStepData( args[4], map );
				readEntityReference( args[5], m_TrueNorth, map);
			}
			void IfcGeometricRepresentationContext::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcRepresentationContext::setInverseCounterparts(ptr_self_entity);
			}
			void IfcGeometricRepresentationContext::unlinkSelf()
			{
				IfcRepresentationContext::unlinkSelf();
			}
	}
}
