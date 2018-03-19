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
#include "IfcFixedReferenceSweptAreaSolid.h"
#include "IfcProfileDef.h"
#include "IfcAxis2Placement3D.h"
#include "IfcCurve.h"
#include "IfcParameterValue.h"
#include "IfcParameterValue.h"
#include "IfcDirection.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcFixedReferenceSweptAreaSolid
			IfcFixedReferenceSweptAreaSolid::IfcFixedReferenceSweptAreaSolid() { m_entity_enum = IFCFIXEDREFERENCESWEPTAREASOLID;}
			IfcFixedReferenceSweptAreaSolid::IfcFixedReferenceSweptAreaSolid( int id ) { m_id = id; m_entity_enum = IFCFIXEDREFERENCESWEPTAREASOLID;}
			IfcFixedReferenceSweptAreaSolid::~IfcFixedReferenceSweptAreaSolid() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcFixedReferenceSweptAreaSolid::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcFixedReferenceSweptAreaSolid> other = std::dynamic_pointer_cast<IfcFixedReferenceSweptAreaSolid>(other_entity);
				if( !other) { return; }
				m_SweptArea = other->m_SweptArea;
				m_Position = other->m_Position;
				m_Directrix = other->m_Directrix;
				m_StartParam = other->m_StartParam;
				m_EndParam = other->m_EndParam;
				m_FixedReference = other->m_FixedReference;
			}
			void IfcFixedReferenceSweptAreaSolid::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCFIXEDREFERENCESWEPTAREASOLID" << "(";
				if( m_SweptArea) { stream << "#" << m_SweptArea->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Position) { stream << "#" << m_Position->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Directrix) { stream << "#" << m_Directrix->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_StartParam) { m_StartParam->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_EndParam) { m_EndParam->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_FixedReference) { stream << "#" << m_FixedReference->getId(); } else { stream << "$"; }
				stream << ");";
			}
			void IfcFixedReferenceSweptAreaSolid::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcFixedReferenceSweptAreaSolid::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<6 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcFixedReferenceSweptAreaSolid, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<6 ){ std::cout << "Wrong parameter count for entity IfcFixedReferenceSweptAreaSolid, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				readEntityReference( args[0], m_SweptArea, map);
				readEntityReference( args[1], m_Position, map);
				readEntityReference( args[2], m_Directrix, map);
				m_StartParam = IfcParameterValue::readStepData( args[3] );
				m_EndParam = IfcParameterValue::readStepData( args[4] );
				readEntityReference( args[5], m_FixedReference, map);
			}
			void IfcFixedReferenceSweptAreaSolid::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcSweptAreaSolid::setInverseCounterparts(ptr_self_entity);
			}
			void IfcFixedReferenceSweptAreaSolid::unlinkSelf()
			{
				IfcSweptAreaSolid::unlinkSelf();
			}
	}
}
