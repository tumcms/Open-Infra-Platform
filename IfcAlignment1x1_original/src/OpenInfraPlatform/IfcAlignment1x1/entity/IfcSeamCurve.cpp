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
#include "IfcSeamCurve.h"
#include "IfcCurve.h"
#include "IfcPcurve.h"
#include "IfcPreferredSurfaceCurveRepresentation.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcSeamCurve
			IfcSeamCurve::IfcSeamCurve() { m_entity_enum = IFCSEAMCURVE;}
			IfcSeamCurve::IfcSeamCurve( int id ) { m_id = id; m_entity_enum = IFCSEAMCURVE;}
			IfcSeamCurve::~IfcSeamCurve() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcSeamCurve::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcSeamCurve> other = std::dynamic_pointer_cast<IfcSeamCurve>(other_entity);
				if( !other) { return; }
				m_Curve3D = other->m_Curve3D;
				m_AssociatedGeometry = other->m_AssociatedGeometry;
				m_MasterRepresentation = other->m_MasterRepresentation;
			}
			void IfcSeamCurve::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCSEAMCURVE" << "(";
				if( m_Curve3D) { stream << "#" << m_Curve3D->getId(); } else { stream << "$"; }
				stream << ",";
				writeEntityList( stream, m_AssociatedGeometry );
				stream << ",";
				if( m_MasterRepresentation) { m_MasterRepresentation->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcSeamCurve::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcSeamCurve::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<3 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcSeamCurve, expecting 3, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<3 ){ std::cout << "Wrong parameter count for entity IfcSeamCurve, expecting 3, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				readEntityReference( args[0], m_Curve3D, map);
				readEntityReferenceList( args[1], m_AssociatedGeometry , map);
				m_MasterRepresentation = IfcPreferredSurfaceCurveRepresentation::readStepData( args[2] );
			}
			void IfcSeamCurve::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcSurfaceCurve::setInverseCounterparts(ptr_self_entity);
			}
			void IfcSeamCurve::unlinkSelf()
			{
				IfcSurfaceCurve::unlinkSelf();
			}
	}
}
