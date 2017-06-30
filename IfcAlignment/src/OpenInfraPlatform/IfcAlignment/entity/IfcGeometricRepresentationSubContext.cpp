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
#include "include/IfcAxis2Placement.h"
#include "include/IfcCoordinateOperation.h"
#include "include/IfcDimensionCount.h"
#include "include/IfcDirection.h"
#include "include/IfcGeometricProjectionEnum.h"
#include "include/IfcGeometricRepresentationContext.h"
#include "include/IfcGeometricRepresentationSubContext.h"
#include "include/IfcLabel.h"
#include "include/IfcPositiveRatioMeasure.h"
#include "include/IfcReal.h"
#include "include/IfcRepresentation.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment
	{
		// ENTITY IfcGeometricRepresentationSubContext 
		IfcGeometricRepresentationSubContext::IfcGeometricRepresentationSubContext() { m_entity_enum = IFCGEOMETRICREPRESENTATIONSUBCONTEXT; }
		IfcGeometricRepresentationSubContext::IfcGeometricRepresentationSubContext( int id ) { m_id = id; m_entity_enum = IFCGEOMETRICREPRESENTATIONSUBCONTEXT; }
		IfcGeometricRepresentationSubContext::~IfcGeometricRepresentationSubContext() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcGeometricRepresentationSubContext::setEntity( shared_ptr<IfcAlignmentP6Entity> other_entity )
		{
			shared_ptr<IfcGeometricRepresentationSubContext> other = dynamic_pointer_cast<IfcGeometricRepresentationSubContext>(other_entity);
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
			if( m_ContextIdentifier ) { m_ContextIdentifier->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ContextType ) { m_ContextType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_CoordinateSpaceDimension ) { m_CoordinateSpaceDimension->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Precision ) { m_Precision->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_WorldCoordinateSystem ) { m_WorldCoordinateSystem->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_TrueNorth ) { stream << "#" << m_TrueNorth->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_ParentContext ) { stream << "#" << m_ParentContext->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_TargetScale ) { m_TargetScale->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_TargetView ) { m_TargetView->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_UserDefinedTargetView ) { m_UserDefinedTargetView->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcGeometricRepresentationSubContext::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcGeometricRepresentationSubContext::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignmentP6Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<10 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcGeometricRepresentationSubContext, expecting 10, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignmentP6Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>10 ){ std::cout << "Wrong parameter count for entity IfcGeometricRepresentationSubContext, expecting 10, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_ContextIdentifier = IfcLabel::readStepData( args[0] );
			m_ContextType = IfcLabel::readStepData( args[1] );
			m_CoordinateSpaceDimension = IfcDimensionCount::readStepData( args[2] );
			m_Precision = IfcReal::readStepData( args[3] );
			m_WorldCoordinateSystem = IfcAxis2Placement::readStepData( args[4], map );
			readEntityReference( args[5], m_TrueNorth, map );
			readEntityReference( args[6], m_ParentContext, map );
			m_TargetScale = IfcPositiveRatioMeasure::readStepData( args[7] );
			m_TargetView = IfcGeometricProjectionEnum::readStepData( args[8] );
			m_UserDefinedTargetView = IfcLabel::readStepData( args[9] );
		}
		void IfcGeometricRepresentationSubContext::setInverseCounterparts( shared_ptr<IfcAlignmentP6Entity> ptr_self_entity )
		{
			IfcGeometricRepresentationContext::setInverseCounterparts( ptr_self_entity );
			shared_ptr<IfcGeometricRepresentationSubContext> ptr_self = dynamic_pointer_cast<IfcGeometricRepresentationSubContext>( ptr_self_entity );
			if( !ptr_self ) { throw IfcAlignmentP6Exception( "IfcGeometricRepresentationSubContext::setInverseCounterparts: type mismatch" ); }
			if( m_ParentContext )
			{
				m_ParentContext->m_HasSubContexts_inverse.push_back( ptr_self );
			}
		}
		void IfcGeometricRepresentationSubContext::unlinkSelf()
		{
			IfcGeometricRepresentationContext::unlinkSelf();
			if( m_ParentContext )
			{
				std::vector<weak_ptr<IfcGeometricRepresentationSubContext> >& HasSubContexts_inverse = m_ParentContext->m_HasSubContexts_inverse;
				std::vector<weak_ptr<IfcGeometricRepresentationSubContext> >::iterator it_HasSubContexts_inverse;
				for( it_HasSubContexts_inverse = HasSubContexts_inverse.begin(); it_HasSubContexts_inverse != HasSubContexts_inverse.end(); ++it_HasSubContexts_inverse)
				{
					shared_ptr<IfcGeometricRepresentationSubContext> self_candidate( *it_HasSubContexts_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						HasSubContexts_inverse.erase( it_HasSubContexts_inverse );
						break;
					}
				}
			}
		}
	} // end namespace IfcAlignment
} // end namespace OpenInfraPlatform
