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
#include "include/IfcDynamicViscosityMeasure.h"
#include "include/IfcMaterial.h"
#include "include/IfcMechanicalSteelMaterialProperties.h"
#include "include/IfcModulusOfElasticityMeasure.h"
#include "include/IfcPositiveRatioMeasure.h"
#include "include/IfcPressureMeasure.h"
#include "include/IfcRelaxation.h"
#include "include/IfcThermalExpansionCoefficientMeasure.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcMechanicalSteelMaterialProperties 
		IfcMechanicalSteelMaterialProperties::IfcMechanicalSteelMaterialProperties() { m_entity_enum = IFCMECHANICALSTEELMATERIALPROPERTIES; }
		IfcMechanicalSteelMaterialProperties::IfcMechanicalSteelMaterialProperties( int id ) { m_id = id; m_entity_enum = IFCMECHANICALSTEELMATERIALPROPERTIES; }
		IfcMechanicalSteelMaterialProperties::~IfcMechanicalSteelMaterialProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcMechanicalSteelMaterialProperties::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcMechanicalSteelMaterialProperties> other = dynamic_pointer_cast<IfcMechanicalSteelMaterialProperties>(other_entity);
			if( !other) { return; }
			m_Material = other->m_Material;
			m_DynamicViscosity = other->m_DynamicViscosity;
			m_YoungModulus = other->m_YoungModulus;
			m_ShearModulus = other->m_ShearModulus;
			m_PoissonRatio = other->m_PoissonRatio;
			m_ThermalExpansionCoefficient = other->m_ThermalExpansionCoefficient;
			m_YieldStress = other->m_YieldStress;
			m_UltimateStress = other->m_UltimateStress;
			m_UltimateStrain = other->m_UltimateStrain;
			m_HardeningModule = other->m_HardeningModule;
			m_ProportionalStress = other->m_ProportionalStress;
			m_PlasticStrain = other->m_PlasticStrain;
			m_Relaxations = other->m_Relaxations;
		}
		void IfcMechanicalSteelMaterialProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCMECHANICALSTEELMATERIALPROPERTIES" << "(";
			if( m_Material ) { stream << "#" << m_Material->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_DynamicViscosity ) { m_DynamicViscosity->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_YoungModulus ) { m_YoungModulus->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ShearModulus ) { m_ShearModulus->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_PoissonRatio ) { m_PoissonRatio->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ThermalExpansionCoefficient ) { m_ThermalExpansionCoefficient->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_YieldStress ) { m_YieldStress->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_UltimateStress ) { m_UltimateStress->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_UltimateStrain ) { m_UltimateStrain->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_HardeningModule ) { m_HardeningModule->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ProportionalStress ) { m_ProportionalStress->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_PlasticStrain ) { m_PlasticStrain->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_Relaxations );
			stream << ");";
		}
		void IfcMechanicalSteelMaterialProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcMechanicalSteelMaterialProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<13 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcMechanicalSteelMaterialProperties, expecting 13, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>13 ){ std::cout << "Wrong parameter count for entity IfcMechanicalSteelMaterialProperties, expecting 13, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readEntityReference( args[0], m_Material, map );
			m_DynamicViscosity = IfcDynamicViscosityMeasure::readStepData( args[1] );
			m_YoungModulus = IfcModulusOfElasticityMeasure::readStepData( args[2] );
			m_ShearModulus = IfcModulusOfElasticityMeasure::readStepData( args[3] );
			m_PoissonRatio = IfcPositiveRatioMeasure::readStepData( args[4] );
			m_ThermalExpansionCoefficient = IfcThermalExpansionCoefficientMeasure::readStepData( args[5] );
			m_YieldStress = IfcPressureMeasure::readStepData( args[6] );
			m_UltimateStress = IfcPressureMeasure::readStepData( args[7] );
			m_UltimateStrain = IfcPositiveRatioMeasure::readStepData( args[8] );
			m_HardeningModule = IfcModulusOfElasticityMeasure::readStepData( args[9] );
			m_ProportionalStress = IfcPressureMeasure::readStepData( args[10] );
			m_PlasticStrain = IfcPositiveRatioMeasure::readStepData( args[11] );
			readEntityReferenceList( args[12], m_Relaxations, map );
		}
		void IfcMechanicalSteelMaterialProperties::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcMechanicalMaterialProperties::setInverseCounterparts( ptr_self_entity );
		}
		void IfcMechanicalSteelMaterialProperties::unlinkSelf()
		{
			IfcMechanicalMaterialProperties::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
