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
#include "include/IfcForceMeasure.h"
#include "include/IfcLabel.h"
#include "include/IfcStructuralLoadSingleForce.h"
#include "include/IfcTorqueMeasure.h"

namespace OpenInfraPlatform
{
	namespace IfcRoad
	{
		// ENTITY IfcStructuralLoadSingleForce 
		IfcStructuralLoadSingleForce::IfcStructuralLoadSingleForce() { m_entity_enum = IFCSTRUCTURALLOADSINGLEFORCE; }
		IfcStructuralLoadSingleForce::IfcStructuralLoadSingleForce( int id ) { m_id = id; m_entity_enum = IFCSTRUCTURALLOADSINGLEFORCE; }
		IfcStructuralLoadSingleForce::~IfcStructuralLoadSingleForce() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcStructuralLoadSingleForce::setEntity( shared_ptr<IfcRoadEntity> other_entity )
		{
			shared_ptr<IfcStructuralLoadSingleForce> other = dynamic_pointer_cast<IfcStructuralLoadSingleForce>(other_entity);
			if( !other) { return; }
			m_Name = other->m_Name;
			m_ForceX = other->m_ForceX;
			m_ForceY = other->m_ForceY;
			m_ForceZ = other->m_ForceZ;
			m_MomentX = other->m_MomentX;
			m_MomentY = other->m_MomentY;
			m_MomentZ = other->m_MomentZ;
		}
		void IfcStructuralLoadSingleForce::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCSTRUCTURALLOADSINGLEFORCE" << "(";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ForceX ) { m_ForceX->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ForceY ) { m_ForceY->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ForceZ ) { m_ForceZ->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MomentX ) { m_MomentX->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MomentY ) { m_MomentY->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MomentZ ) { m_MomentZ->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcStructuralLoadSingleForce::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcStructuralLoadSingleForce::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcRoadEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<7 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcStructuralLoadSingleForce, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcRoadException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>7 ){ std::cout << "Wrong parameter count for entity IfcStructuralLoadSingleForce, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Name = IfcLabel::readStepData( args[0] );
			m_ForceX = IfcForceMeasure::readStepData( args[1] );
			m_ForceY = IfcForceMeasure::readStepData( args[2] );
			m_ForceZ = IfcForceMeasure::readStepData( args[3] );
			m_MomentX = IfcTorqueMeasure::readStepData( args[4] );
			m_MomentY = IfcTorqueMeasure::readStepData( args[5] );
			m_MomentZ = IfcTorqueMeasure::readStepData( args[6] );
		}
		void IfcStructuralLoadSingleForce::setInverseCounterparts( shared_ptr<IfcRoadEntity> ptr_self_entity )
		{
			IfcStructuralLoadStatic::setInverseCounterparts( ptr_self_entity );
		}
		void IfcStructuralLoadSingleForce::unlinkSelf()
		{
			IfcStructuralLoadStatic::unlinkSelf();
		}
	} // end namespace IfcRoad
} // end namespace OpenInfraPlatform
