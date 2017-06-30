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
#include "include/IfcMechanicalConcreteMaterialProperties.h"
#include "include/IfcModulusOfElasticityMeasure.h"
#include "include/IfcNormalisedRatioMeasure.h"
#include "include/IfcPositiveLengthMeasure.h"
#include "include/IfcPositiveRatioMeasure.h"
#include "include/IfcPressureMeasure.h"
#include "include/IfcText.h"
#include "include/IfcThermalExpansionCoefficientMeasure.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcMechanicalConcreteMaterialProperties 
		IfcMechanicalConcreteMaterialProperties::IfcMechanicalConcreteMaterialProperties() { m_entity_enum = IFCMECHANICALCONCRETEMATERIALPROPERTIES; }
		IfcMechanicalConcreteMaterialProperties::IfcMechanicalConcreteMaterialProperties( int id ) { m_id = id; m_entity_enum = IFCMECHANICALCONCRETEMATERIALPROPERTIES; }
		IfcMechanicalConcreteMaterialProperties::~IfcMechanicalConcreteMaterialProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcMechanicalConcreteMaterialProperties::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcMechanicalConcreteMaterialProperties> other = dynamic_pointer_cast<IfcMechanicalConcreteMaterialProperties>(other_entity);
			if( !other) { return; }
			m_Material = other->m_Material;
			m_DynamicViscosity = other->m_DynamicViscosity;
			m_YoungModulus = other->m_YoungModulus;
			m_ShearModulus = other->m_ShearModulus;
			m_PoissonRatio = other->m_PoissonRatio;
			m_ThermalExpansionCoefficient = other->m_ThermalExpansionCoefficient;
			m_CompressiveStrength = other->m_CompressiveStrength;
			m_MaxAggregateSize = other->m_MaxAggregateSize;
			m_AdmixturesDescription = other->m_AdmixturesDescription;
			m_Workability = other->m_Workability;
			m_ProtectivePoreRatio = other->m_ProtectivePoreRatio;
			m_WaterImpermeability = other->m_WaterImpermeability;
		}
		void IfcMechanicalConcreteMaterialProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCMECHANICALCONCRETEMATERIALPROPERTIES" << "(";
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
			if( m_CompressiveStrength ) { m_CompressiveStrength->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MaxAggregateSize ) { m_MaxAggregateSize->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_AdmixturesDescription ) { m_AdmixturesDescription->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Workability ) { m_Workability->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ProtectivePoreRatio ) { m_ProtectivePoreRatio->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_WaterImpermeability ) { m_WaterImpermeability->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcMechanicalConcreteMaterialProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcMechanicalConcreteMaterialProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<12 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcMechanicalConcreteMaterialProperties, expecting 12, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>12 ){ std::cout << "Wrong parameter count for entity IfcMechanicalConcreteMaterialProperties, expecting 12, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readEntityReference( args[0], m_Material, map );
			m_DynamicViscosity = IfcDynamicViscosityMeasure::readStepData( args[1] );
			m_YoungModulus = IfcModulusOfElasticityMeasure::readStepData( args[2] );
			m_ShearModulus = IfcModulusOfElasticityMeasure::readStepData( args[3] );
			m_PoissonRatio = IfcPositiveRatioMeasure::readStepData( args[4] );
			m_ThermalExpansionCoefficient = IfcThermalExpansionCoefficientMeasure::readStepData( args[5] );
			m_CompressiveStrength = IfcPressureMeasure::readStepData( args[6] );
			m_MaxAggregateSize = IfcPositiveLengthMeasure::readStepData( args[7] );
			m_AdmixturesDescription = IfcText::readStepData( args[8] );
			m_Workability = IfcText::readStepData( args[9] );
			m_ProtectivePoreRatio = IfcNormalisedRatioMeasure::readStepData( args[10] );
			m_WaterImpermeability = IfcText::readStepData( args[11] );
		}
		void IfcMechanicalConcreteMaterialProperties::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcMechanicalMaterialProperties::setInverseCounterparts( ptr_self_entity );
		}
		void IfcMechanicalConcreteMaterialProperties::unlinkSelf()
		{
			IfcMechanicalMaterialProperties::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
