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
#include "include/IfcCrossSectionGeometry.h"
#include "include/IfcCrossSectionStatic.h"
#include "include/IfcReal.h"

namespace OpenInfraPlatform
{
	namespace IfcRoad
	{
		// ENTITY IfcCrossSectionStatic 
		IfcCrossSectionStatic::IfcCrossSectionStatic() { m_entity_enum = IFCCROSSSECTIONSTATIC; }
		IfcCrossSectionStatic::IfcCrossSectionStatic( int id ) { m_id = id; m_entity_enum = IFCCROSSSECTIONSTATIC; }
		IfcCrossSectionStatic::~IfcCrossSectionStatic() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcCrossSectionStatic::setEntity( shared_ptr<IfcRoadEntity> other_entity )
		{
			shared_ptr<IfcCrossSectionStatic> other = dynamic_pointer_cast<IfcCrossSectionStatic>(other_entity);
			if( !other) { return; }
			m_Station = other->m_Station;
			m_Geometry = other->m_Geometry;
		}
		void IfcCrossSectionStatic::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCCROSSSECTIONSTATIC" << "(";
			if( m_Station ) { m_Station->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Geometry ) { stream << "#" << m_Geometry->getId(); } else { stream << "$"; }
			stream << ");";
		}
		void IfcCrossSectionStatic::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcCrossSectionStatic::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcRoadEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<2 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcCrossSectionStatic, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcRoadException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>2 ){ std::cout << "Wrong parameter count for entity IfcCrossSectionStatic, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Station = IfcReal::readStepData( args[0] );
			readEntityReference( args[1], m_Geometry, map );
		}
		void IfcCrossSectionStatic::setInverseCounterparts( shared_ptr<IfcRoadEntity> ptr_self_entity )
		{
			IfcCrossSection::setInverseCounterparts( ptr_self_entity );
		}
		void IfcCrossSectionStatic::unlinkSelf()
		{
			IfcCrossSection::unlinkSelf();
		}
	} // end namespace IfcRoad
} // end namespace OpenInfraPlatform
