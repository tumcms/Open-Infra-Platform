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
#include "IfcDerivedProfileDef.h"
#include "IfcProfileTypeEnum.h"
#include "IfcLabel.h"
#include "IfcProfileDef.h"
#include "IfcCartesianTransformationOperator2D.h"
#include "IfcLabel.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcDerivedProfileDef
			IfcDerivedProfileDef::IfcDerivedProfileDef() { m_entity_enum = IFCDERIVEDPROFILEDEF;}
			IfcDerivedProfileDef::IfcDerivedProfileDef( int id ) { m_id = id; m_entity_enum = IFCDERIVEDPROFILEDEF;}
			IfcDerivedProfileDef::~IfcDerivedProfileDef() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcDerivedProfileDef::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcDerivedProfileDef> other = std::dynamic_pointer_cast<IfcDerivedProfileDef>(other_entity);
				if( !other) { return; }
				m_ProfileType = other->m_ProfileType;
				m_ProfileName = other->m_ProfileName;
				m_ParentProfile = other->m_ParentProfile;
				m_Operator = other->m_Operator;
				m_Label = other->m_Label;
			}
			void IfcDerivedProfileDef::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCDERIVEDPROFILEDEF" << "(";
				if( m_ProfileType) { m_ProfileType->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_ProfileName) { m_ProfileName->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_ParentProfile) { stream << "#" << m_ParentProfile->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Operator) { stream << "#" << m_Operator->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Label) { m_Label->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcDerivedProfileDef::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcDerivedProfileDef::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<5 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcDerivedProfileDef, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<5 ){ std::cout << "Wrong parameter count for entity IfcDerivedProfileDef, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_ProfileType = IfcProfileTypeEnum::readStepData( args[0] );
				m_ProfileName = IfcLabel::readStepData( args[1] );
				readEntityReference( args[2], m_ParentProfile, map);
				readEntityReference( args[3], m_Operator, map);
				m_Label = IfcLabel::readStepData( args[4] );
			}
			void IfcDerivedProfileDef::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcProfileDef::setInverseCounterparts(ptr_self_entity);
			}
			void IfcDerivedProfileDef::unlinkSelf()
			{
				IfcProfileDef::unlinkSelf();
			}
	}
}
