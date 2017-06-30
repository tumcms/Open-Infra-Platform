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
#include "include/IfcLabel.h"
#include "include/IfcLinearForceMeasure.h"
#include "include/IfcLinearMomentMeasure.h"
#include "include/IfcStructuralLoadLinearForce.h"

namespace OpenInfraPlatform
{
	namespace IfcRoad
	{
		// ENTITY IfcStructuralLoadLinearForce 
		IfcStructuralLoadLinearForce::IfcStructuralLoadLinearForce() { m_entity_enum = IFCSTRUCTURALLOADLINEARFORCE; }
		IfcStructuralLoadLinearForce::IfcStructuralLoadLinearForce( int id ) { m_id = id; m_entity_enum = IFCSTRUCTURALLOADLINEARFORCE; }
		IfcStructuralLoadLinearForce::~IfcStructuralLoadLinearForce() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcStructuralLoadLinearForce::setEntity( shared_ptr<IfcRoadEntity> other_entity )
		{
			shared_ptr<IfcStructuralLoadLinearForce> other = dynamic_pointer_cast<IfcStructuralLoadLinearForce>(other_entity);
			if( !other) { return; }
			m_Name = other->m_Name;
			m_LinearForceX = other->m_LinearForceX;
			m_LinearForceY = other->m_LinearForceY;
			m_LinearForceZ = other->m_LinearForceZ;
			m_LinearMomentX = other->m_LinearMomentX;
			m_LinearMomentY = other->m_LinearMomentY;
			m_LinearMomentZ = other->m_LinearMomentZ;
		}
		void IfcStructuralLoadLinearForce::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCSTRUCTURALLOADLINEARFORCE" << "(";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LinearForceX ) { m_LinearForceX->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LinearForceY ) { m_LinearForceY->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LinearForceZ ) { m_LinearForceZ->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LinearMomentX ) { m_LinearMomentX->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LinearMomentY ) { m_LinearMomentY->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LinearMomentZ ) { m_LinearMomentZ->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcStructuralLoadLinearForce::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcStructuralLoadLinearForce::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcRoadEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<7 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcStructuralLoadLinearForce, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcRoadException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>7 ){ std::cout << "Wrong parameter count for entity IfcStructuralLoadLinearForce, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Name = IfcLabel::readStepData( args[0] );
			m_LinearForceX = IfcLinearForceMeasure::readStepData( args[1] );
			m_LinearForceY = IfcLinearForceMeasure::readStepData( args[2] );
			m_LinearForceZ = IfcLinearForceMeasure::readStepData( args[3] );
			m_LinearMomentX = IfcLinearMomentMeasure::readStepData( args[4] );
			m_LinearMomentY = IfcLinearMomentMeasure::readStepData( args[5] );
			m_LinearMomentZ = IfcLinearMomentMeasure::readStepData( args[6] );
		}
		void IfcStructuralLoadLinearForce::setInverseCounterparts( shared_ptr<IfcRoadEntity> ptr_self_entity )
		{
			IfcStructuralLoadStatic::setInverseCounterparts( ptr_self_entity );
		}
		void IfcStructuralLoadLinearForce::unlinkSelf()
		{
			IfcStructuralLoadStatic::unlinkSelf();
		}
	} // end namespace IfcRoad
} // end namespace OpenInfraPlatform
