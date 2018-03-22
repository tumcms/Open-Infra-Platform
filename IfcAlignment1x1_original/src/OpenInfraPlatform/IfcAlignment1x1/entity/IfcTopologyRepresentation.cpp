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
#include "IfcTopologyRepresentation.h"
#include "IfcRepresentationContext.h"
#include "IfcLabel.h"
#include "IfcLabel.h"
#include "IfcRepresentationItem.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcTopologyRepresentation
			IfcTopologyRepresentation::IfcTopologyRepresentation() { m_entity_enum = IFCTOPOLOGYREPRESENTATION;}
			IfcTopologyRepresentation::IfcTopologyRepresentation( int id ) { m_id = id; m_entity_enum = IFCTOPOLOGYREPRESENTATION;}
			IfcTopologyRepresentation::~IfcTopologyRepresentation() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcTopologyRepresentation::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcTopologyRepresentation> other = std::dynamic_pointer_cast<IfcTopologyRepresentation>(other_entity);
				if( !other) { return; }
				m_ContextOfItems = other->m_ContextOfItems;
				m_RepresentationIdentifier = other->m_RepresentationIdentifier;
				m_RepresentationType = other->m_RepresentationType;
				m_Items = other->m_Items;
			}
			void IfcTopologyRepresentation::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCTOPOLOGYREPRESENTATION" << "(";
				if( m_ContextOfItems) { stream << "#" << m_ContextOfItems->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_RepresentationIdentifier) { m_RepresentationIdentifier->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_RepresentationType) { m_RepresentationType->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				writeEntityList( stream, m_Items );
				stream << ");";
			}
			void IfcTopologyRepresentation::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcTopologyRepresentation::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<4 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcTopologyRepresentation, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<4 ){ std::cout << "Wrong parameter count for entity IfcTopologyRepresentation, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				readEntityReference( args[0], m_ContextOfItems, map);
				m_RepresentationIdentifier = IfcLabel::readStepData( args[1] );
				m_RepresentationType = IfcLabel::readStepData( args[2] );
				readEntityReferenceList( args[3], m_Items , map);
			}
			void IfcTopologyRepresentation::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcShapeModel::setInverseCounterparts(ptr_self_entity);
			}
			void IfcTopologyRepresentation::unlinkSelf()
			{
				IfcShapeModel::unlinkSelf();
			}
	}
}
