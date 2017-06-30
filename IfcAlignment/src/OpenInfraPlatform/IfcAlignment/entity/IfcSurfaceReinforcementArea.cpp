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
#include "include/IfcLabel.h"
#include "include/IfcLengthMeasure.h"
#include "include/IfcRatioMeasure.h"
#include "include/IfcSurfaceReinforcementArea.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment
	{
		// ENTITY IfcSurfaceReinforcementArea 
		IfcSurfaceReinforcementArea::IfcSurfaceReinforcementArea() { m_entity_enum = IFCSURFACEREINFORCEMENTAREA; }
		IfcSurfaceReinforcementArea::IfcSurfaceReinforcementArea( int id ) { m_id = id; m_entity_enum = IFCSURFACEREINFORCEMENTAREA; }
		IfcSurfaceReinforcementArea::~IfcSurfaceReinforcementArea() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcSurfaceReinforcementArea::setEntity( shared_ptr<IfcAlignmentP6Entity> other_entity )
		{
			shared_ptr<IfcSurfaceReinforcementArea> other = dynamic_pointer_cast<IfcSurfaceReinforcementArea>(other_entity);
			if( !other) { return; }
			m_Name = other->m_Name;
			m_SurfaceReinforcement1 = other->m_SurfaceReinforcement1;
			m_SurfaceReinforcement2 = other->m_SurfaceReinforcement2;
			m_ShearReinforcement = other->m_ShearReinforcement;
		}
		void IfcSurfaceReinforcementArea::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCSURFACEREINFORCEMENTAREA" << "(";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeTypeOfRealList( stream, m_SurfaceReinforcement1 );
			stream << ",";
			writeTypeOfRealList( stream, m_SurfaceReinforcement2 );
			stream << ",";
			if( m_ShearReinforcement ) { m_ShearReinforcement->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcSurfaceReinforcementArea::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcSurfaceReinforcementArea::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignmentP6Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<4 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcSurfaceReinforcementArea, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignmentP6Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>4 ){ std::cout << "Wrong parameter count for entity IfcSurfaceReinforcementArea, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Name = IfcLabel::readStepData( args[0] );
			readTypeOfRealList( args[1], m_SurfaceReinforcement1 );
			readTypeOfRealList( args[2], m_SurfaceReinforcement2 );
			m_ShearReinforcement = IfcRatioMeasure::readStepData( args[3] );
		}
		void IfcSurfaceReinforcementArea::setInverseCounterparts( shared_ptr<IfcAlignmentP6Entity> ptr_self_entity )
		{
			IfcStructuralLoadOrResult::setInverseCounterparts( ptr_self_entity );
		}
		void IfcSurfaceReinforcementArea::unlinkSelf()
		{
			IfcStructuralLoadOrResult::unlinkSelf();
		}
	} // end namespace IfcAlignment
} // end namespace OpenInfraPlatform
