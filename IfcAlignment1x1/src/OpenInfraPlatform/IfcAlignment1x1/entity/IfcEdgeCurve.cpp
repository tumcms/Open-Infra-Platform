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
#include "IfcEdgeCurve.h"
#include "IfcVertex.h"
#include "IfcVertex.h"
#include "IfcCurve.h"
#include "IfcBoolean.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcEdgeCurve
			IfcEdgeCurve::IfcEdgeCurve() { m_entity_enum = IFCEDGECURVE;}
			IfcEdgeCurve::IfcEdgeCurve( int id ) { m_id = id; m_entity_enum = IFCEDGECURVE;}
			IfcEdgeCurve::~IfcEdgeCurve() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcEdgeCurve::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcEdgeCurve> other = std::dynamic_pointer_cast<IfcEdgeCurve>(other_entity);
				if( !other) { return; }
				m_EdgeStart = other->m_EdgeStart;
				m_EdgeEnd = other->m_EdgeEnd;
				m_EdgeGeometry = other->m_EdgeGeometry;
				m_SameSense = other->m_SameSense;
			}
			void IfcEdgeCurve::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCEDGECURVE" << "(";
				if( m_EdgeStart) { stream << "#" << m_EdgeStart->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_EdgeEnd) { stream << "#" << m_EdgeEnd->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_EdgeGeometry) { stream << "#" << m_EdgeGeometry->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_SameSense) { m_SameSense->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcEdgeCurve::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcEdgeCurve::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<4 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcEdgeCurve, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<4 ){ std::cout << "Wrong parameter count for entity IfcEdgeCurve, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				readEntityReference( args[0], m_EdgeStart, map);
				readEntityReference( args[1], m_EdgeEnd, map);
				readEntityReference( args[2], m_EdgeGeometry, map);
				m_SameSense = IfcBoolean::readStepData( args[3] );
			}
			void IfcEdgeCurve::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcEdge::setInverseCounterparts(ptr_self_entity);
			}
			void IfcEdgeCurve::unlinkSelf()
			{
				IfcEdge::unlinkSelf();
			}
	}
}
