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
#include "include/IfcConstraintAggregationRelationship.h"
#include "include/IfcConstraintClassificationRelationship.h"
#include "include/IfcConstraintEnum.h"
#include "include/IfcConstraintRelationship.h"
#include "include/IfcDateTimeSelect.h"
#include "include/IfcLabel.h"
#include "include/IfcMetric.h"
#include "include/IfcObjective.h"
#include "include/IfcObjectiveEnum.h"
#include "include/IfcPropertyConstraintRelationship.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcObjective 
		IfcObjective::IfcObjective() { m_entity_enum = IFCOBJECTIVE; }
		IfcObjective::IfcObjective( int id ) { m_id = id; m_entity_enum = IFCOBJECTIVE; }
		IfcObjective::~IfcObjective() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcObjective::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcObjective> other = dynamic_pointer_cast<IfcObjective>(other_entity);
			if( !other) { return; }
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_ConstraintGrade = other->m_ConstraintGrade;
			m_ConstraintSource = other->m_ConstraintSource;
			m_CreatingActor = other->m_CreatingActor;
			m_CreationTime = other->m_CreationTime;
			m_UserDefinedGrade = other->m_UserDefinedGrade;
			m_BenchmarkValues = other->m_BenchmarkValues;
			m_ResultValues = other->m_ResultValues;
			m_ObjectiveQualifier = other->m_ObjectiveQualifier;
			m_UserDefinedQualifier = other->m_UserDefinedQualifier;
		}
		void IfcObjective::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCOBJECTIVE" << "(";
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
			stream << ",";
			if( m_BenchmarkValues ) { stream << "#" << m_BenchmarkValues->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_ResultValues ) { stream << "#" << m_ResultValues->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_ObjectiveQualifier ) { m_ObjectiveQualifier->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_UserDefinedQualifier ) { m_UserDefinedQualifier->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcObjective::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcObjective::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<11 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcObjective, expecting 11, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>11 ){ std::cout << "Wrong parameter count for entity IfcObjective, expecting 11, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Name = IfcLabel::readStepData( args[0] );
			m_Description = IfcText::readStepData( args[1] );
			m_ConstraintGrade = IfcConstraintEnum::readStepData( args[2] );
			m_ConstraintSource = IfcLabel::readStepData( args[3] );
			m_CreatingActor = IfcActorSelect::readStepData( args[4], map );
			m_CreationTime = IfcDateTimeSelect::readStepData( args[5], map );
			m_UserDefinedGrade = IfcLabel::readStepData( args[6] );
			readEntityReference( args[7], m_BenchmarkValues, map );
			readEntityReference( args[8], m_ResultValues, map );
			m_ObjectiveQualifier = IfcObjectiveEnum::readStepData( args[9] );
			m_UserDefinedQualifier = IfcLabel::readStepData( args[10] );
		}
		void IfcObjective::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcConstraint::setInverseCounterparts( ptr_self_entity );
		}
		void IfcObjective::unlinkSelf()
		{
			IfcConstraint::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
