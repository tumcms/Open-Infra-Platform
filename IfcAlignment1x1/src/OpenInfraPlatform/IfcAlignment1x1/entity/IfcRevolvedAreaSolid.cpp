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
#include "IfcRevolvedAreaSolid.h"
#include "IfcProfileDef.h"
#include "IfcAxis2Placement3D.h"
#include "IfcAxis1Placement.h"
#include "IfcPlaneAngleMeasure.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcRevolvedAreaSolid
			IfcRevolvedAreaSolid::IfcRevolvedAreaSolid() { m_entity_enum = IFCREVOLVEDAREASOLID;}
			IfcRevolvedAreaSolid::IfcRevolvedAreaSolid( int id ) { m_id = id; m_entity_enum = IFCREVOLVEDAREASOLID;}
			IfcRevolvedAreaSolid::~IfcRevolvedAreaSolid() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcRevolvedAreaSolid::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcRevolvedAreaSolid> other = std::dynamic_pointer_cast<IfcRevolvedAreaSolid>(other_entity);
				if( !other) { return; }
				m_SweptArea = other->m_SweptArea;
				m_Position = other->m_Position;
				m_Axis = other->m_Axis;
				m_Angle = other->m_Angle;
			}
			void IfcRevolvedAreaSolid::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCREVOLVEDAREASOLID" << "(";
				if( m_SweptArea) { stream << "#" << m_SweptArea->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Position) { stream << "#" << m_Position->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Axis) { stream << "#" << m_Axis->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Angle) { m_Angle->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcRevolvedAreaSolid::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcRevolvedAreaSolid::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<4 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcRevolvedAreaSolid, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<4 ){ std::cout << "Wrong parameter count for entity IfcRevolvedAreaSolid, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				readEntityReference( args[0], m_SweptArea, map);
				readEntityReference( args[1], m_Position, map);
				readEntityReference( args[2], m_Axis, map);
				m_Angle = IfcPlaneAngleMeasure::readStepData( args[3] );
			}
			void IfcRevolvedAreaSolid::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcSweptAreaSolid::setInverseCounterparts(ptr_self_entity);
			}
			void IfcRevolvedAreaSolid::unlinkSelf()
			{
				IfcSweptAreaSolid::unlinkSelf();
			}
	}
}
