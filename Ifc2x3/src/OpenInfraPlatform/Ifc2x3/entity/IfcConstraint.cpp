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

#include "model/Ifc2x3Exception.h"
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "Ifc2x3EntityEnums.h"
#include "include/IfcActorSelect.h"
#include "include/IfcConstraint.h"
#include "include/IfcConstraintAggregationRelationship.h"
#include "include/IfcConstraintClassificationRelationship.h"
#include "include/IfcConstraintEnum.h"
#include "include/IfcConstraintRelationship.h"
#include "include/IfcDateTimeSelect.h"
#include "include/IfcLabel.h"
#include "include/IfcPropertyConstraintRelationship.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcConstraint 
		IfcConstraint::IfcConstraint() { m_entity_enum = IFCCONSTRAINT; }
		IfcConstraint::IfcConstraint( int id ) { m_id = id; m_entity_enum = IFCCONSTRAINT; }
		IfcConstraint::~IfcConstraint() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcConstraint::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcConstraint> other = dynamic_pointer_cast<IfcConstraint>(other_entity);
			if( !other) { return; }
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_ConstraintGrade = other->m_ConstraintGrade;
			m_ConstraintSource = other->m_ConstraintSource;
			m_CreatingActor = other->m_CreatingActor;
			m_CreationTime = other->m_CreationTime;
			m_UserDefinedGrade = other->m_UserDefinedGrade;
		}
		void IfcConstraint::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCCONSTRAINT" << "(";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ConstraintGrade ) { m_ConstraintGrade->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ConstraintSource ) { m_ConstraintSource->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_CreatingActor ) { m_CreatingActor->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_CreationTime ) { m_CreationTime->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_UserDefinedGrade ) { m_UserDefinedGrade->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcConstraint::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcConstraint::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<7 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcConstraint, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>7 ){ std::cout << "Wrong parameter count for entity IfcConstraint, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Name = IfcLabel::readStepData( args[0] );
			m_Description = IfcText::readStepData( args[1] );
			m_ConstraintGrade = IfcConstraintEnum::readStepData( args[2] );
			m_ConstraintSource = IfcLabel::readStepData( args[3] );
			m_CreatingActor = IfcActorSelect::readStepData( args[4], map );
			m_CreationTime = IfcDateTimeSelect::readStepData( args[5], map );
			m_UserDefinedGrade = IfcLabel::readStepData( args[6] );
		}
		void IfcConstraint::setInverseCounterparts( shared_ptr<Ifc2x3Entity> )
		{
		}
		void IfcConstraint::unlinkSelf()
		{
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
