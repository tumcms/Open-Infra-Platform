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

#include "model/Ifc2x3Exception.h"
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "Ifc2x3EntityEnums.h"
#include "include/IfcBoundaryEdgeCondition.h"
#include "include/IfcLabel.h"
#include "include/IfcModulusOfLinearSubgradeReactionMeasure.h"
#include "include/IfcModulusOfRotationalSubgradeReactionMeasure.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcBoundaryEdgeCondition 
		IfcBoundaryEdgeCondition::IfcBoundaryEdgeCondition() { m_entity_enum = IFCBOUNDARYEDGECONDITION; }
		IfcBoundaryEdgeCondition::IfcBoundaryEdgeCondition( int id ) { m_id = id; m_entity_enum = IFCBOUNDARYEDGECONDITION; }
		IfcBoundaryEdgeCondition::~IfcBoundaryEdgeCondition() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcBoundaryEdgeCondition::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcBoundaryEdgeCondition> other = dynamic_pointer_cast<IfcBoundaryEdgeCondition>(other_entity);
			if( !other) { return; }
			m_Name = other->m_Name;
			m_LinearStiffnessByLengthX = other->m_LinearStiffnessByLengthX;
			m_LinearStiffnessByLengthY = other->m_LinearStiffnessByLengthY;
			m_LinearStiffnessByLengthZ = other->m_LinearStiffnessByLengthZ;
			m_RotationalStiffnessByLengthX = other->m_RotationalStiffnessByLengthX;
			m_RotationalStiffnessByLengthY = other->m_RotationalStiffnessByLengthY;
			m_RotationalStiffnessByLengthZ = other->m_RotationalStiffnessByLengthZ;
		}
		void IfcBoundaryEdgeCondition::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCBOUNDARYEDGECONDITION" << "(";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LinearStiffnessByLengthX ) { m_LinearStiffnessByLengthX->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LinearStiffnessByLengthY ) { m_LinearStiffnessByLengthY->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LinearStiffnessByLengthZ ) { m_LinearStiffnessByLengthZ->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RotationalStiffnessByLengthX ) { m_RotationalStiffnessByLengthX->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RotationalStiffnessByLengthY ) { m_RotationalStiffnessByLengthY->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RotationalStiffnessByLengthZ ) { m_RotationalStiffnessByLengthZ->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcBoundaryEdgeCondition::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcBoundaryEdgeCondition::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<7 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcBoundaryEdgeCondition, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>7 ){ std::cout << "Wrong parameter count for entity IfcBoundaryEdgeCondition, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Name = IfcLabel::readStepData( args[0] );
			m_LinearStiffnessByLengthX = IfcModulusOfLinearSubgradeReactionMeasure::readStepData( args[1] );
			m_LinearStiffnessByLengthY = IfcModulusOfLinearSubgradeReactionMeasure::readStepData( args[2] );
			m_LinearStiffnessByLengthZ = IfcModulusOfLinearSubgradeReactionMeasure::readStepData( args[3] );
			m_RotationalStiffnessByLengthX = IfcModulusOfRotationalSubgradeReactionMeasure::readStepData( args[4] );
			m_RotationalStiffnessByLengthY = IfcModulusOfRotationalSubgradeReactionMeasure::readStepData( args[5] );
			m_RotationalStiffnessByLengthZ = IfcModulusOfRotationalSubgradeReactionMeasure::readStepData( args[6] );
		}
		void IfcBoundaryEdgeCondition::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcBoundaryCondition::setInverseCounterparts( ptr_self_entity );
		}
		void IfcBoundaryEdgeCondition::unlinkSelf()
		{
			IfcBoundaryCondition::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
