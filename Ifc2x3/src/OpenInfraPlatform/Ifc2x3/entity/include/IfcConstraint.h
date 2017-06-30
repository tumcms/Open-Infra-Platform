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

#pragma once
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include "../../model/shared_ptr.h"
#include "../../model/Ifc2x3Object.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		class IfcLabel;
		class IfcText;
		class IfcConstraintEnum;
		class IfcActorSelect;
		class IfcDateTimeSelect;
		class IfcConstraintClassificationRelationship;
		class IfcConstraintRelationship;
		class IfcPropertyConstraintRelationship;
		class IfcConstraintAggregationRelationship;
		//ENTITY
		class IfcConstraint : public Ifc2x3Entity
		{
		public:
			IfcConstraint();
			IfcConstraint( int id );
			~IfcConstraint();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity( shared_ptr<Ifc2x3Entity> other );
			virtual void getStepLine( std::stringstream& stream ) const;
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			virtual void readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map );
			virtual void setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self );
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcConstraint"; }


			// IfcConstraint -----------------------------------------------------------
			// attributes:
			shared_ptr<IfcLabel>												m_Name;
			shared_ptr<IfcText>												m_Description;				//optional
			shared_ptr<IfcConstraintEnum>									m_ConstraintGrade;
			shared_ptr<IfcLabel>												m_ConstraintSource;			//optional
			shared_ptr<IfcActorSelect>										m_CreatingActor;			//optional
			shared_ptr<IfcDateTimeSelect>									m_CreationTime;				//optional
			shared_ptr<IfcLabel>												m_UserDefinedGrade;			//optional
			// inverse attributes:
			std::vector<weak_ptr<IfcConstraintClassificationRelationship> >	m_ClassifiedAs_inverse;
			std::vector<weak_ptr<IfcConstraintRelationship> >				m_RelatesConstraints_inverse;
			std::vector<weak_ptr<IfcConstraintRelationship> >				m_IsRelatedWith_inverse;
			std::vector<weak_ptr<IfcPropertyConstraintRelationship> >		m_PropertiesForConstraint_inverse;
			std::vector<weak_ptr<IfcConstraintAggregationRelationship> >		m_Aggregates_inverse;
			std::vector<weak_ptr<IfcConstraintAggregationRelationship> >		m_IsAggregatedIn_inverse;
		};
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform

