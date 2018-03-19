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
#include "IfcSweptDiskSolid.h"
#include "IfcCurve.h"
#include "IfcPositiveLengthMeasure.h"
#include "IfcPositiveLengthMeasure.h"
#include "IfcParameterValue.h"
#include "IfcParameterValue.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcSweptDiskSolid
			IfcSweptDiskSolid::IfcSweptDiskSolid() { m_entity_enum = IFCSWEPTDISKSOLID;}
			IfcSweptDiskSolid::IfcSweptDiskSolid( int id ) { m_id = id; m_entity_enum = IFCSWEPTDISKSOLID;}
			IfcSweptDiskSolid::~IfcSweptDiskSolid() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcSweptDiskSolid::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcSweptDiskSolid> other = std::dynamic_pointer_cast<IfcSweptDiskSolid>(other_entity);
				if( !other) { return; }
				m_Directrix = other->m_Directrix;
				m_Radius = other->m_Radius;
				m_InnerRadius = other->m_InnerRadius;
				m_StartParam = other->m_StartParam;
				m_EndParam = other->m_EndParam;
			}
			void IfcSweptDiskSolid::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCSWEPTDISKSOLID" << "(";
				if( m_Directrix) { stream << "#" << m_Directrix->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Radius) { m_Radius->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_InnerRadius) { m_InnerRadius->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_StartParam) { m_StartParam->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_EndParam) { m_EndParam->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcSweptDiskSolid::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcSweptDiskSolid::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<5 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcSweptDiskSolid, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<5 ){ std::cout << "Wrong parameter count for entity IfcSweptDiskSolid, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				readEntityReference( args[0], m_Directrix, map);
				m_Radius = IfcPositiveLengthMeasure::readStepData( args[1] );
				m_InnerRadius = IfcPositiveLengthMeasure::readStepData( args[2] );
				m_StartParam = IfcParameterValue::readStepData( args[3] );
				m_EndParam = IfcParameterValue::readStepData( args[4] );
			}
			void IfcSweptDiskSolid::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcSolidModel::setInverseCounterparts(ptr_self_entity);
			}
			void IfcSweptDiskSolid::unlinkSelf()
			{
				IfcSolidModel::unlinkSelf();
			}
	}
}
