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
#include "IfcRectangleProfileDef.h"
#include "IfcProfileTypeEnum.h"
#include "IfcLabel.h"
#include "IfcAxis2Placement2D.h"
#include "IfcPositiveLengthMeasure.h"
#include "IfcPositiveLengthMeasure.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcRectangleProfileDef
			IfcRectangleProfileDef::IfcRectangleProfileDef() { m_entity_enum = IFCRECTANGLEPROFILEDEF;}
			IfcRectangleProfileDef::IfcRectangleProfileDef( int id ) { m_id = id; m_entity_enum = IFCRECTANGLEPROFILEDEF;}
			IfcRectangleProfileDef::~IfcRectangleProfileDef() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcRectangleProfileDef::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcRectangleProfileDef> other = std::dynamic_pointer_cast<IfcRectangleProfileDef>(other_entity);
				if( !other) { return; }
				m_ProfileType = other->m_ProfileType;
				m_ProfileName = other->m_ProfileName;
				m_Position = other->m_Position;
				m_XDim = other->m_XDim;
				m_YDim = other->m_YDim;
			}
			void IfcRectangleProfileDef::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCRECTANGLEPROFILEDEF" << "(";
				if( m_ProfileType) { m_ProfileType->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_ProfileName) { m_ProfileName->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Position) { stream << "#" << m_Position->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_XDim) { m_XDim->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_YDim) { m_YDim->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcRectangleProfileDef::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcRectangleProfileDef::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<5 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcRectangleProfileDef, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<5 ){ std::cout << "Wrong parameter count for entity IfcRectangleProfileDef, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_ProfileType = IfcProfileTypeEnum::readStepData( args[0] );
				m_ProfileName = IfcLabel::readStepData( args[1] );
				readEntityReference( args[2], m_Position, map);
				m_XDim = IfcPositiveLengthMeasure::readStepData( args[3] );
				m_YDim = IfcPositiveLengthMeasure::readStepData( args[4] );
			}
			void IfcRectangleProfileDef::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcParameterizedProfileDef::setInverseCounterparts(ptr_self_entity);
			}
			void IfcRectangleProfileDef::unlinkSelf()
			{
				IfcParameterizedProfileDef::unlinkSelf();
			}
	}
}
