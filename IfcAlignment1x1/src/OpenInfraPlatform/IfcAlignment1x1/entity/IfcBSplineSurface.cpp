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
#include "IfcBSplineSurface.h"
#include "IfcInteger.h"
#include "IfcInteger.h"
#include "IfcCartesianPoint.h"
#include "IfcBSplineSurfaceForm.h"
#include "IfcLogical.h"
#include "IfcLogical.h"
#include "IfcLogical.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcBSplineSurface
			IfcBSplineSurface::IfcBSplineSurface() { m_entity_enum = IFCBSPLINESURFACE;}
			IfcBSplineSurface::IfcBSplineSurface( int id ) { m_id = id; m_entity_enum = IFCBSPLINESURFACE;}
			IfcBSplineSurface::~IfcBSplineSurface() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcBSplineSurface::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcBSplineSurface> other = std::dynamic_pointer_cast<IfcBSplineSurface>(other_entity);
				if( !other) { return; }
				m_UDegree = other->m_UDegree;
				m_VDegree = other->m_VDegree;
				m_ControlPointsList = other->m_ControlPointsList;
				m_SurfaceForm = other->m_SurfaceForm;
				m_UClosed = other->m_UClosed;
				m_VClosed = other->m_VClosed;
				m_SelfIntersect = other->m_SelfIntersect;
			}
			void IfcBSplineSurface::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCBSPLINESURFACE" << "(";
				if( m_UDegree) { m_UDegree->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_VDegree) { m_VDegree->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				writeEntityList2D( stream, m_ControlPointsList );
				stream << ",";
				if( m_SurfaceForm) { m_SurfaceForm->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_UClosed) { m_UClosed->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_VClosed) { m_VClosed->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_SelfIntersect) { m_SelfIntersect->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcBSplineSurface::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcBSplineSurface::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<7 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcBSplineSurface, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<7 ){ std::cout << "Wrong parameter count for entity IfcBSplineSurface, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_UDegree = IfcInteger::readStepData( args[0] );
				m_VDegree = IfcInteger::readStepData( args[1] );
				readEntityReferenceList2D( args[2], m_ControlPointsList , map);
				m_SurfaceForm = IfcBSplineSurfaceForm::readStepData( args[3] );
				m_UClosed = IfcLogical::readStepData( args[4] );
				m_VClosed = IfcLogical::readStepData( args[5] );
				m_SelfIntersect = IfcLogical::readStepData( args[6] );
			}
			void IfcBSplineSurface::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcBoundedSurface::setInverseCounterparts(ptr_self_entity);
			}
			void IfcBSplineSurface::unlinkSelf()
			{
				IfcBoundedSurface::unlinkSelf();
			}
	}
}
