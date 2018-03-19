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
#include "IfcBoundaryEdgeCondition.h"
#include "IfcLabel.h"
#include "IfcModulusOfTranslationalSubgradeReactionSelect.h"
#include "IfcModulusOfTranslationalSubgradeReactionSelect.h"
#include "IfcModulusOfTranslationalSubgradeReactionSelect.h"
#include "IfcModulusOfRotationalSubgradeReactionSelect.h"
#include "IfcModulusOfRotationalSubgradeReactionSelect.h"
#include "IfcModulusOfRotationalSubgradeReactionSelect.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcBoundaryEdgeCondition
			IfcBoundaryEdgeCondition::IfcBoundaryEdgeCondition() { m_entity_enum = IFCBOUNDARYEDGECONDITION;}
			IfcBoundaryEdgeCondition::IfcBoundaryEdgeCondition( int id ) { m_id = id; m_entity_enum = IFCBOUNDARYEDGECONDITION;}
			IfcBoundaryEdgeCondition::~IfcBoundaryEdgeCondition() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcBoundaryEdgeCondition::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcBoundaryEdgeCondition> other = std::dynamic_pointer_cast<IfcBoundaryEdgeCondition>(other_entity);
				if( !other) { return; }
				m_Name = other->m_Name;
				m_TranslationalStiffnessByLengthX = other->m_TranslationalStiffnessByLengthX;
				m_TranslationalStiffnessByLengthY = other->m_TranslationalStiffnessByLengthY;
				m_TranslationalStiffnessByLengthZ = other->m_TranslationalStiffnessByLengthZ;
				m_RotationalStiffnessByLengthX = other->m_RotationalStiffnessByLengthX;
				m_RotationalStiffnessByLengthY = other->m_RotationalStiffnessByLengthY;
				m_RotationalStiffnessByLengthZ = other->m_RotationalStiffnessByLengthZ;
			}
			void IfcBoundaryEdgeCondition::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCBOUNDARYEDGECONDITION" << "(";
				if( m_Name) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_TranslationalStiffnessByLengthX) { m_TranslationalStiffnessByLengthX->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_TranslationalStiffnessByLengthY) { m_TranslationalStiffnessByLengthY->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_TranslationalStiffnessByLengthZ) { m_TranslationalStiffnessByLengthZ->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_RotationalStiffnessByLengthX) { m_RotationalStiffnessByLengthX->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_RotationalStiffnessByLengthY) { m_RotationalStiffnessByLengthY->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_RotationalStiffnessByLengthZ) { m_RotationalStiffnessByLengthZ->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcBoundaryEdgeCondition::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcBoundaryEdgeCondition::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<7 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcBoundaryEdgeCondition, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<7 ){ std::cout << "Wrong parameter count for entity IfcBoundaryEdgeCondition, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_Name = IfcLabel::readStepData( args[0] );
				m_TranslationalStiffnessByLengthX = IfcModulusOfTranslationalSubgradeReactionSelect::readStepData( args[1], map );
				m_TranslationalStiffnessByLengthY = IfcModulusOfTranslationalSubgradeReactionSelect::readStepData( args[2], map );
				m_TranslationalStiffnessByLengthZ = IfcModulusOfTranslationalSubgradeReactionSelect::readStepData( args[3], map );
				m_RotationalStiffnessByLengthX = IfcModulusOfRotationalSubgradeReactionSelect::readStepData( args[4], map );
				m_RotationalStiffnessByLengthY = IfcModulusOfRotationalSubgradeReactionSelect::readStepData( args[5], map );
				m_RotationalStiffnessByLengthZ = IfcModulusOfRotationalSubgradeReactionSelect::readStepData( args[6], map );
			}
			void IfcBoundaryEdgeCondition::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcBoundaryCondition::setInverseCounterparts(ptr_self_entity);
			}
			void IfcBoundaryEdgeCondition::unlinkSelf()
			{
				IfcBoundaryCondition::unlinkSelf();
			}
	}
}
