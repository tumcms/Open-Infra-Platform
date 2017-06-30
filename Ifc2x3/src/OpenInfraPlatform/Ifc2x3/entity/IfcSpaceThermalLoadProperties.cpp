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
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcPositiveRatioMeasure.h"
#include "include/IfcPowerMeasure.h"
#include "include/IfcPropertySourceEnum.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelDefinesByProperties.h"
#include "include/IfcSpaceThermalLoadProperties.h"
#include "include/IfcText.h"
#include "include/IfcThermalLoadSourceEnum.h"
#include "include/IfcThermalLoadTypeEnum.h"
#include "include/IfcTimeSeries.h"
#include "include/IfcTypeObject.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcSpaceThermalLoadProperties 
		IfcSpaceThermalLoadProperties::IfcSpaceThermalLoadProperties() { m_entity_enum = IFCSPACETHERMALLOADPROPERTIES; }
		IfcSpaceThermalLoadProperties::IfcSpaceThermalLoadProperties( int id ) { m_id = id; m_entity_enum = IFCSPACETHERMALLOADPROPERTIES; }
		IfcSpaceThermalLoadProperties::~IfcSpaceThermalLoadProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcSpaceThermalLoadProperties::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcSpaceThermalLoadProperties> other = dynamic_pointer_cast<IfcSpaceThermalLoadProperties>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_ApplicableValueRatio = other->m_ApplicableValueRatio;
			m_ThermalLoadSource = other->m_ThermalLoadSource;
			m_PropertySource = other->m_PropertySource;
			m_SourceDescription = other->m_SourceDescription;
			m_MaximumValue = other->m_MaximumValue;
			m_MinimumValue = other->m_MinimumValue;
			m_ThermalLoadTimeSeriesValues = other->m_ThermalLoadTimeSeriesValues;
			m_UserDefinedThermalLoadSource = other->m_UserDefinedThermalLoadSource;
			m_UserDefinedPropertySource = other->m_UserDefinedPropertySource;
			m_ThermalLoadType = other->m_ThermalLoadType;
		}
		void IfcSpaceThermalLoadProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCSPACETHERMALLOADPROPERTIES" << "(";
			if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ApplicableValueRatio ) { m_ApplicableValueRatio->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ThermalLoadSource ) { m_ThermalLoadSource->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_PropertySource ) { m_PropertySource->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_SourceDescription ) { m_SourceDescription->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MaximumValue ) { m_MaximumValue->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MinimumValue ) { m_MinimumValue->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ThermalLoadTimeSeriesValues ) { stream << "#" << m_ThermalLoadTimeSeriesValues->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_UserDefinedThermalLoadSource ) { m_UserDefinedThermalLoadSource->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_UserDefinedPropertySource ) { m_UserDefinedPropertySource->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ThermalLoadType ) { m_ThermalLoadType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcSpaceThermalLoadProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcSpaceThermalLoadProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<14 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcSpaceThermalLoadProperties, expecting 14, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>14 ){ std::cout << "Wrong parameter count for entity IfcSpaceThermalLoadProperties, expecting 14, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			m_ApplicableValueRatio = IfcPositiveRatioMeasure::readStepData( args[4] );
			m_ThermalLoadSource = IfcThermalLoadSourceEnum::readStepData( args[5] );
			m_PropertySource = IfcPropertySourceEnum::readStepData( args[6] );
			m_SourceDescription = IfcText::readStepData( args[7] );
			m_MaximumValue = IfcPowerMeasure::readStepData( args[8] );
			m_MinimumValue = IfcPowerMeasure::readStepData( args[9] );
			readEntityReference( args[10], m_ThermalLoadTimeSeriesValues, map );
			m_UserDefinedThermalLoadSource = IfcLabel::readStepData( args[11] );
			m_UserDefinedPropertySource = IfcLabel::readStepData( args[12] );
			m_ThermalLoadType = IfcThermalLoadTypeEnum::readStepData( args[13] );
		}
		void IfcSpaceThermalLoadProperties::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcPropertySetDefinition::setInverseCounterparts( ptr_self_entity );
		}
		void IfcSpaceThermalLoadProperties::unlinkSelf()
		{
			IfcPropertySetDefinition::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
