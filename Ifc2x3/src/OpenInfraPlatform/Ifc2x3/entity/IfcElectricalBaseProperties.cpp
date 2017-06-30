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
#include "include/IfcElectricCurrentEnum.h"
#include "include/IfcElectricCurrentMeasure.h"
#include "include/IfcElectricVoltageMeasure.h"
#include "include/IfcElectricalBaseProperties.h"
#include "include/IfcEnergySequenceEnum.h"
#include "include/IfcFrequencyMeasure.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcPowerMeasure.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelDefinesByProperties.h"
#include "include/IfcText.h"
#include "include/IfcTypeObject.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcElectricalBaseProperties 
		IfcElectricalBaseProperties::IfcElectricalBaseProperties() { m_entity_enum = IFCELECTRICALBASEPROPERTIES; }
		IfcElectricalBaseProperties::IfcElectricalBaseProperties( int id ) { m_id = id; m_entity_enum = IFCELECTRICALBASEPROPERTIES; }
		IfcElectricalBaseProperties::~IfcElectricalBaseProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcElectricalBaseProperties::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcElectricalBaseProperties> other = dynamic_pointer_cast<IfcElectricalBaseProperties>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_EnergySequence = other->m_EnergySequence;
			m_UserDefinedEnergySequence = other->m_UserDefinedEnergySequence;
			m_ElectricCurrentType = other->m_ElectricCurrentType;
			m_InputVoltage = other->m_InputVoltage;
			m_InputFrequency = other->m_InputFrequency;
			m_FullLoadCurrent = other->m_FullLoadCurrent;
			m_MinimumCircuitCurrent = other->m_MinimumCircuitCurrent;
			m_MaximumPowerInput = other->m_MaximumPowerInput;
			m_RatedPowerInput = other->m_RatedPowerInput;
			m_InputPhase = other->m_InputPhase;
		}
		void IfcElectricalBaseProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCELECTRICALBASEPROPERTIES" << "(";
			if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_EnergySequence ) { m_EnergySequence->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_UserDefinedEnergySequence ) { m_UserDefinedEnergySequence->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ElectricCurrentType ) { m_ElectricCurrentType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_InputVoltage ) { m_InputVoltage->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_InputFrequency ) { m_InputFrequency->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_FullLoadCurrent ) { m_FullLoadCurrent->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MinimumCircuitCurrent ) { m_MinimumCircuitCurrent->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MaximumPowerInput ) { m_MaximumPowerInput->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RatedPowerInput ) { m_RatedPowerInput->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_InputPhase == m_InputPhase ){ stream << m_InputPhase; }
			else { stream << "$"; }
			stream << ");";
		}
		void IfcElectricalBaseProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcElectricalBaseProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<14 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcElectricalBaseProperties, expecting 14, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>14 ){ std::cout << "Wrong parameter count for entity IfcElectricalBaseProperties, expecting 14, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			m_EnergySequence = IfcEnergySequenceEnum::readStepData( args[4] );
			m_UserDefinedEnergySequence = IfcLabel::readStepData( args[5] );
			m_ElectricCurrentType = IfcElectricCurrentEnum::readStepData( args[6] );
			m_InputVoltage = IfcElectricVoltageMeasure::readStepData( args[7] );
			m_InputFrequency = IfcFrequencyMeasure::readStepData( args[8] );
			m_FullLoadCurrent = IfcElectricCurrentMeasure::readStepData( args[9] );
			m_MinimumCircuitCurrent = IfcElectricCurrentMeasure::readStepData( args[10] );
			m_MaximumPowerInput = IfcPowerMeasure::readStepData( args[11] );
			m_RatedPowerInput = IfcPowerMeasure::readStepData( args[12] );
			readIntValue( args[13], m_InputPhase );
		}
		void IfcElectricalBaseProperties::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcEnergyProperties::setInverseCounterparts( ptr_self_entity );
		}
		void IfcElectricalBaseProperties::unlinkSelf()
		{
			IfcEnergyProperties::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
