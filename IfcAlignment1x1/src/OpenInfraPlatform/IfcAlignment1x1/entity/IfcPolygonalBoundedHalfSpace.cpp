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
#include "IfcPolygonalBoundedHalfSpace.h"
#include "IfcSurface.h"
#include "IfcBoolean.h"
#include "IfcAxis2Placement3D.h"
#include "IfcBoundedCurve.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcPolygonalBoundedHalfSpace
			IfcPolygonalBoundedHalfSpace::IfcPolygonalBoundedHalfSpace() { m_entity_enum = IFCPOLYGONALBOUNDEDHALFSPACE;}
			IfcPolygonalBoundedHalfSpace::IfcPolygonalBoundedHalfSpace( int id ) { m_id = id; m_entity_enum = IFCPOLYGONALBOUNDEDHALFSPACE;}
			IfcPolygonalBoundedHalfSpace::~IfcPolygonalBoundedHalfSpace() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcPolygonalBoundedHalfSpace::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcPolygonalBoundedHalfSpace> other = std::dynamic_pointer_cast<IfcPolygonalBoundedHalfSpace>(other_entity);
				if( !other) { return; }
				m_BaseSurface = other->m_BaseSurface;
				m_AgreementFlag = other->m_AgreementFlag;
				m_Position = other->m_Position;
				m_PolygonalBoundary = other->m_PolygonalBoundary;
			}
			void IfcPolygonalBoundedHalfSpace::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCPOLYGONALBOUNDEDHALFSPACE" << "(";
				if( m_BaseSurface) { stream << "#" << m_BaseSurface->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_AgreementFlag) { m_AgreementFlag->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Position) { stream << "#" << m_Position->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_PolygonalBoundary) { stream << "#" << m_PolygonalBoundary->getId(); } else { stream << "$"; }
				stream << ");";
			}
			void IfcPolygonalBoundedHalfSpace::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcPolygonalBoundedHalfSpace::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<4 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcPolygonalBoundedHalfSpace, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<4 ){ std::cout << "Wrong parameter count for entity IfcPolygonalBoundedHalfSpace, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				readEntityReference( args[0], m_BaseSurface, map);
				m_AgreementFlag = IfcBoolean::readStepData( args[1] );
				readEntityReference( args[2], m_Position, map);
				readEntityReference( args[3], m_PolygonalBoundary, map);
			}
			void IfcPolygonalBoundedHalfSpace::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcHalfSpaceSolid::setInverseCounterparts(ptr_self_entity);
			}
			void IfcPolygonalBoundedHalfSpace::unlinkSelf()
			{
				IfcHalfSpaceSolid::unlinkSelf();
			}
	}
}
