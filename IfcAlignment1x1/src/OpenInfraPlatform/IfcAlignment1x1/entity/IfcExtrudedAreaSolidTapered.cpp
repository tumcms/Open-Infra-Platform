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
#include "IfcExtrudedAreaSolidTapered.h"
#include "IfcProfileDef.h"
#include "IfcAxis2Placement3D.h"
#include "IfcDirection.h"
#include "IfcPositiveLengthMeasure.h"
#include "IfcProfileDef.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcExtrudedAreaSolidTapered
			IfcExtrudedAreaSolidTapered::IfcExtrudedAreaSolidTapered() { m_entity_enum = IFCEXTRUDEDAREASOLIDTAPERED;}
			IfcExtrudedAreaSolidTapered::IfcExtrudedAreaSolidTapered( int id ) { m_id = id; m_entity_enum = IFCEXTRUDEDAREASOLIDTAPERED;}
			IfcExtrudedAreaSolidTapered::~IfcExtrudedAreaSolidTapered() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcExtrudedAreaSolidTapered::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcExtrudedAreaSolidTapered> other = std::dynamic_pointer_cast<IfcExtrudedAreaSolidTapered>(other_entity);
				if( !other) { return; }
				m_SweptArea = other->m_SweptArea;
				m_Position = other->m_Position;
				m_ExtrudedDirection = other->m_ExtrudedDirection;
				m_Depth = other->m_Depth;
				m_EndSweptArea = other->m_EndSweptArea;
			}
			void IfcExtrudedAreaSolidTapered::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCEXTRUDEDAREASOLIDTAPERED" << "(";
				if( m_SweptArea) { stream << "#" << m_SweptArea->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Position) { stream << "#" << m_Position->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_ExtrudedDirection) { stream << "#" << m_ExtrudedDirection->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Depth) { m_Depth->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_EndSweptArea) { stream << "#" << m_EndSweptArea->getId(); } else { stream << "$"; }
				stream << ");";
			}
			void IfcExtrudedAreaSolidTapered::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcExtrudedAreaSolidTapered::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<5 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcExtrudedAreaSolidTapered, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<5 ){ std::cout << "Wrong parameter count for entity IfcExtrudedAreaSolidTapered, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				readEntityReference( args[0], m_SweptArea, map);
				readEntityReference( args[1], m_Position, map);
				readEntityReference( args[2], m_ExtrudedDirection, map);
				m_Depth = IfcPositiveLengthMeasure::readStepData( args[3] );
				readEntityReference( args[4], m_EndSweptArea, map);
			}
			void IfcExtrudedAreaSolidTapered::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcExtrudedAreaSolid::setInverseCounterparts(ptr_self_entity);
			}
			void IfcExtrudedAreaSolidTapered::unlinkSelf()
			{
				IfcExtrudedAreaSolid::unlinkSelf();
			}
	}
}
