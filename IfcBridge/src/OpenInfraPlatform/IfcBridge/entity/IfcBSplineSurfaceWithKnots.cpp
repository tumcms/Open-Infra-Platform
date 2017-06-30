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

#include "model/IfcBridgeException.h"
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "IfcBridgeEntityEnums.h"
#include "include/IfcBSplineSurfaceForm.h"
#include "include/IfcBSplineSurfaceWithKnots.h"
#include "include/IfcCartesianPoint.h"
#include "include/IfcKnotType.h"
#include "include/IfcParameterValue.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcStyledItem.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// ENTITY IfcBSplineSurfaceWithKnots 
		IfcBSplineSurfaceWithKnots::IfcBSplineSurfaceWithKnots() { m_entity_enum = IFCBSPLINESURFACEWITHKNOTS; }
		IfcBSplineSurfaceWithKnots::IfcBSplineSurfaceWithKnots( int id ) { m_id = id; m_entity_enum = IFCBSPLINESURFACEWITHKNOTS; }
		IfcBSplineSurfaceWithKnots::~IfcBSplineSurfaceWithKnots() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcBSplineSurfaceWithKnots::setEntity( shared_ptr<IfcBridgeEntity> other_entity )
		{
			shared_ptr<IfcBSplineSurfaceWithKnots> other = dynamic_pointer_cast<IfcBSplineSurfaceWithKnots>(other_entity);
			if( !other) { return; }
			m_UDegree = other->m_UDegree;
			m_VDegree = other->m_VDegree;
			m_ControlPointsList = other->m_ControlPointsList;
			m_SurfaceForm = other->m_SurfaceForm;
			m_UClosed = other->m_UClosed;
			m_VClosed = other->m_VClosed;
			m_SelfIntersect = other->m_SelfIntersect;
			m_UMultiplicities = other->m_UMultiplicities;
			m_VMultiplicities = other->m_VMultiplicities;
			m_UKnots = other->m_UKnots;
			m_VKnots = other->m_VKnots;
			m_KnotSpec = other->m_KnotSpec;
		}
		void IfcBSplineSurfaceWithKnots::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCBSPLINESURFACEWITHKNOTS" << "(";
			if( m_UDegree == m_UDegree ){ stream << m_UDegree; }
			else { stream << "$"; }
			stream << ",";
			if( m_VDegree == m_VDegree ){ stream << m_VDegree; }
			else { stream << "$"; }
			stream << ",";
			writeEntityList2D( stream, m_ControlPointsList );
			stream << ",";
			if( m_SurfaceForm ) { m_SurfaceForm->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_UClosed == false ) { stream << ".F."; }
			else if( m_UClosed == true ) { stream << ".T."; }
			stream << ",";
			if( m_VClosed == false ) { stream << ".F."; }
			else if( m_VClosed == true ) { stream << ".T."; }
			stream << ",";
			if( m_SelfIntersect == false ) { stream << ".F."; }
			else if( m_SelfIntersect == true ) { stream << ".T."; }
			stream << ",";
			writeIntList( stream, m_UMultiplicities );
			stream << ",";
			writeIntList( stream, m_VMultiplicities );
			stream << ",";
			writeTypeOfRealList( stream, m_UKnots );
			stream << ",";
			writeTypeOfRealList( stream, m_VKnots );
			stream << ",";
			if( m_KnotSpec ) { m_KnotSpec->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcBSplineSurfaceWithKnots::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcBSplineSurfaceWithKnots::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcBridgeEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<12 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcBSplineSurfaceWithKnots, expecting 12, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcBridgeException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>12 ){ std::cout << "Wrong parameter count for entity IfcBSplineSurfaceWithKnots, expecting 12, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readIntValue( args[0], m_UDegree );
			readIntValue( args[1], m_VDegree );
			readEntityReferenceList2D( args[2], m_ControlPointsList, map );
			m_SurfaceForm = IfcBSplineSurfaceForm::readStepData( args[3] );
			if( _stricmp( args[4].c_str(), ".F." ) == 0 ) { m_UClosed = false; }
			else if( _stricmp( args[4].c_str(), ".T." ) == 0 ) { m_UClosed = true; }
			if( _stricmp( args[5].c_str(), ".F." ) == 0 ) { m_VClosed = false; }
			else if( _stricmp( args[5].c_str(), ".T." ) == 0 ) { m_VClosed = true; }
			if( _stricmp( args[6].c_str(), ".F." ) == 0 ) { m_SelfIntersect = false; }
			else if( _stricmp( args[6].c_str(), ".T." ) == 0 ) { m_SelfIntersect = true; }
			readIntList(  args[7], m_UMultiplicities );
			readIntList(  args[8], m_VMultiplicities );
			readTypeOfRealList( args[9], m_UKnots );
			readTypeOfRealList( args[10], m_VKnots );
			m_KnotSpec = IfcKnotType::readStepData( args[11] );
		}
		void IfcBSplineSurfaceWithKnots::setInverseCounterparts( shared_ptr<IfcBridgeEntity> ptr_self_entity )
		{
			IfcBSplineSurface::setInverseCounterparts( ptr_self_entity );
		}
		void IfcBSplineSurfaceWithKnots::unlinkSelf()
		{
			IfcBSplineSurface::unlinkSelf();
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
