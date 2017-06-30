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
#include "include/IfcDerivedMeasureValue.h"
#include "include/IfcFluidFlowProperties.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcLinearVelocityMeasure.h"
#include "include/IfcMaterial.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcPositiveRatioMeasure.h"
#include "include/IfcPressureMeasure.h"
#include "include/IfcPropertySourceEnum.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelDefinesByProperties.h"
#include "include/IfcText.h"
#include "include/IfcThermodynamicTemperatureMeasure.h"
#include "include/IfcTimeSeries.h"
#include "include/IfcTypeObject.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcFluidFlowProperties 
		IfcFluidFlowProperties::IfcFluidFlowProperties() { m_entity_enum = IFCFLUIDFLOWPROPERTIES; }
		IfcFluidFlowProperties::IfcFluidFlowProperties( int id ) { m_id = id; m_entity_enum = IFCFLUIDFLOWPROPERTIES; }
		IfcFluidFlowProperties::~IfcFluidFlowProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcFluidFlowProperties::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcFluidFlowProperties> other = dynamic_pointer_cast<IfcFluidFlowProperties>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_PropertySource = other->m_PropertySource;
			m_FlowConditionTimeSeries = other->m_FlowConditionTimeSeries;
			m_VelocityTimeSeries = other->m_VelocityTimeSeries;
			m_FlowrateTimeSeries = other->m_FlowrateTimeSeries;
			m_Fluid = other->m_Fluid;
			m_PressureTimeSeries = other->m_PressureTimeSeries;
			m_UserDefinedPropertySource = other->m_UserDefinedPropertySource;
			m_TemperatureSingleValue = other->m_TemperatureSingleValue;
			m_WetBulbTemperatureSingleValue = other->m_WetBulbTemperatureSingleValue;
			m_WetBulbTemperatureTimeSeries = other->m_WetBulbTemperatureTimeSeries;
			m_TemperatureTimeSeries = other->m_TemperatureTimeSeries;
			m_FlowrateSingleValue = other->m_FlowrateSingleValue;
			m_FlowConditionSingleValue = other->m_FlowConditionSingleValue;
			m_VelocitySingleValue = other->m_VelocitySingleValue;
			m_PressureSingleValue = other->m_PressureSingleValue;
		}
		void IfcFluidFlowProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCFLUIDFLOWPROPERTIES" << "(";
			if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_PropertySource ) { m_PropertySource->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_FlowConditionTimeSeries ) { stream << "#" << m_FlowConditionTimeSeries->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_VelocityTimeSeries ) { stream << "#" << m_VelocityTimeSeries->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_FlowrateTimeSeries ) { stream << "#" << m_FlowrateTimeSeries->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Fluid ) { stream << "#" << m_Fluid->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_PressureTimeSeries ) { stream << "#" << m_PressureTimeSeries->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_UserDefinedPropertySource ) { m_UserDefinedPropertySource->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_TemperatureSingleValue ) { m_TemperatureSingleValue->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_WetBulbTemperatureSingleValue ) { m_WetBulbTemperatureSingleValue->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_WetBulbTemperatureTimeSeries ) { stream << "#" << m_WetBulbTemperatureTimeSeries->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_TemperatureTimeSeries ) { stream << "#" << m_TemperatureTimeSeries->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_FlowrateSingleValue ) { m_FlowrateSingleValue->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_FlowConditionSingleValue ) { m_FlowConditionSingleValue->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_VelocitySingleValue ) { m_VelocitySingleValue->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_PressureSingleValue ) { m_PressureSingleValue->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcFluidFlowProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcFluidFlowProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<19 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcFluidFlowProperties, expecting 19, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>19 ){ std::cout << "Wrong parameter count for entity IfcFluidFlowProperties, expecting 19, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			m_PropertySource = IfcPropertySourceEnum::readStepData( args[4] );
			readEntityReference( args[5], m_FlowConditionTimeSeries, map );
			readEntityReference( args[6], m_VelocityTimeSeries, map );
			readEntityReference( args[7], m_FlowrateTimeSeries, map );
			readEntityReference( args[8], m_Fluid, map );
			readEntityReference( args[9], m_PressureTimeSeries, map );
			m_UserDefinedPropertySource = IfcLabel::readStepData( args[10] );
			m_TemperatureSingleValue = IfcThermodynamicTemperatureMeasure::readStepData( args[11] );
			m_WetBulbTemperatureSingleValue = IfcThermodynamicTemperatureMeasure::readStepData( args[12] );
			readEntityReference( args[13], m_WetBulbTemperatureTimeSeries, map );
			readEntityReference( args[14], m_TemperatureTimeSeries, map );
			m_FlowrateSingleValue = IfcDerivedMeasureValue::readStepData( args[15], map );
			m_FlowConditionSingleValue = IfcPositiveRatioMeasure::readStepData( args[16] );
			m_VelocitySingleValue = IfcLinearVelocityMeasure::readStepData( args[17] );
			m_PressureSingleValue = IfcPressureMeasure::readStepData( args[18] );
		}
		void IfcFluidFlowProperties::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcPropertySetDefinition::setInverseCounterparts( ptr_self_entity );
		}
		void IfcFluidFlowProperties::unlinkSelf()
		{
			IfcPropertySetDefinition::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
