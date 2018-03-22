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
#include "IfcSlippageConnectionCondition.h"
#include "IfcLabel.h"
#include "IfcLengthMeasure.h"
#include "IfcLengthMeasure.h"
#include "IfcLengthMeasure.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcSlippageConnectionCondition
			IfcSlippageConnectionCondition::IfcSlippageConnectionCondition() { m_entity_enum = IFCSLIPPAGECONNECTIONCONDITION;}
			IfcSlippageConnectionCondition::IfcSlippageConnectionCondition( int id ) { m_id = id; m_entity_enum = IFCSLIPPAGECONNECTIONCONDITION;}
			IfcSlippageConnectionCondition::~IfcSlippageConnectionCondition() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcSlippageConnectionCondition::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcSlippageConnectionCondition> other = std::dynamic_pointer_cast<IfcSlippageConnectionCondition>(other_entity);
				if( !other) { return; }
				m_Name = other->m_Name;
				m_SlippageX = other->m_SlippageX;
				m_SlippageY = other->m_SlippageY;
				m_SlippageZ = other->m_SlippageZ;
			}
			void IfcSlippageConnectionCondition::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCSLIPPAGECONNECTIONCONDITION" << "(";
				if( m_Name) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_SlippageX) { m_SlippageX->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_SlippageY) { m_SlippageY->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_SlippageZ) { m_SlippageZ->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcSlippageConnectionCondition::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcSlippageConnectionCondition::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<4 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcSlippageConnectionCondition, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<4 ){ std::cout << "Wrong parameter count for entity IfcSlippageConnectionCondition, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_Name = IfcLabel::readStepData( args[0] );
				m_SlippageX = IfcLengthMeasure::readStepData( args[1] );
				m_SlippageY = IfcLengthMeasure::readStepData( args[2] );
				m_SlippageZ = IfcLengthMeasure::readStepData( args[3] );
			}
			void IfcSlippageConnectionCondition::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcStructuralConnectionCondition::setInverseCounterparts(ptr_self_entity);
			}
			void IfcSlippageConnectionCondition::unlinkSelf()
			{
				IfcStructuralConnectionCondition::unlinkSelf();
			}
	}
}
