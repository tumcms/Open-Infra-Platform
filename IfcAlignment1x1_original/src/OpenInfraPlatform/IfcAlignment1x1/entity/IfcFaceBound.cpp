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
#include "IfcFaceBound.h"
#include "IfcLoop.h"
#include "IfcBoolean.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcFaceBound
			IfcFaceBound::IfcFaceBound() { m_entity_enum = IFCFACEBOUND;}
			IfcFaceBound::IfcFaceBound( int id ) { m_id = id; m_entity_enum = IFCFACEBOUND;}
			IfcFaceBound::~IfcFaceBound() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcFaceBound::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcFaceBound> other = std::dynamic_pointer_cast<IfcFaceBound>(other_entity);
				if( !other) { return; }
				m_Bound = other->m_Bound;
				m_Orientation = other->m_Orientation;
			}
			void IfcFaceBound::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCFACEBOUND" << "(";
				if( m_Bound) { stream << "#" << m_Bound->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Orientation) { m_Orientation->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcFaceBound::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcFaceBound::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<2 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcFaceBound, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<2 ){ std::cout << "Wrong parameter count for entity IfcFaceBound, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				readEntityReference( args[0], m_Bound, map);
				m_Orientation = IfcBoolean::readStepData( args[1] );
			}
			void IfcFaceBound::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcTopologicalRepresentationItem::setInverseCounterparts(ptr_self_entity);
			}
			void IfcFaceBound::unlinkSelf()
			{
				IfcTopologicalRepresentationItem::unlinkSelf();
			}
	}
}
