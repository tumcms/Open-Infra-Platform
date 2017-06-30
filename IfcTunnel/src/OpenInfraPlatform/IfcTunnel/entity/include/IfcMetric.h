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
#include "../../model/IfcTunnelObject.h"
#include "IfcConstraint.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		class IfcBenchmarkEnum;
		class IfcLabel;
		class IfcMetricValueSelect;
		class IfcReference;
		//ENTITY
		class IfcMetric : public IfcConstraint
		{
		public:
			IfcMetric();
			IfcMetric( int id );
			~IfcMetric();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity( shared_ptr<IfcTunnelEntity> other );
			virtual void getStepLine( std::stringstream& stream ) const;
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			virtual void readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcTunnelEntity> >& map );
			virtual void setInverseCounterparts( shared_ptr<IfcTunnelEntity> ptr_self );
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcMetric"; }


			// IfcConstraint -----------------------------------------------------------
			// attributes:
			//  shared_ptr<IfcLabel>							m_Name;
			//  shared_ptr<IfcText>							m_Description;				//optional
			//  shared_ptr<IfcConstraintEnum>				m_ConstraintGrade;
			//  shared_ptr<IfcLabel>							m_ConstraintSource;			//optional
			//  shared_ptr<IfcActorSelect>					m_CreatingActor;			//optional
			//  shared_ptr<IfcDateTime>						m_CreationTime;				//optional
			//  shared_ptr<IfcLabel>							m_UserDefinedGrade;			//optional
			// inverse attributes:
			//  std::vector<weak_ptr<IfcExternalReferenceRelationship> >	m_HasExternalReferences_inverse;
			//  std::vector<weak_ptr<IfcResourceConstraintRelationship> >	m_PropertiesForConstraint_inverse;

			// IfcMetric -----------------------------------------------------------
			// attributes:
			shared_ptr<IfcBenchmarkEnum>					m_Benchmark;
			shared_ptr<IfcLabel>							m_ValueSource;				//optional
			shared_ptr<IfcMetricValueSelect>				m_DataValue;
			shared_ptr<IfcReference>						m_ReferencePath;			//optional
		};
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform

