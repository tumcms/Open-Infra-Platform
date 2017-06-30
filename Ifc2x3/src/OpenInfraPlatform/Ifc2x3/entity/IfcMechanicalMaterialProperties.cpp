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
#include "include/IfcMechanicalMaterialProperties.h"
#include "include/IfcModulusOfElasticityMeasure.h"
#include "include/IfcPositiveRatioMeasure.h"
#include "include/IfcThermalExpansionCoefficientMeasure.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcMechanicalMaterialProperties 
		IfcMechanicalMaterialProperties::IfcMechanicalMaterialProperties() { m_entity_enum = IFCMECHANICALMATERIALPROPERTIES; }
		IfcMechanicalMaterialProperties::IfcMechanicalMaterialProperties( int id ) { m_id = id; m_entity_enum = IFCMECHANICALMATERIALPROPERTIES; }
		IfcMechanicalMaterialProperties::~IfcMechanicalMaterialProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcMechanicalMaterialProperties::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcMechanicalMaterialProperties> other = dynamic_pointer_cast<IfcMechanicalMaterialProperties>(other_entity);
			if( !other) { return; }
			m_Material = other->m_Material;
			m_DynamicViscosity = other->m_DynamicViscosity;
			m_YoungModulus = other->m_YoungModulus;
			m_ShearModulus = other->m_ShearModulus;
			m_PoissonRatio = other->m_PoissonRatio;
			m_ThermalExpansionCoefficient = other->m_ThermalExpansionCoefficient;
		}
		void IfcMechanicalMaterialProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCMECHANICALMATERIALPROPERTIES" << "(";
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
			stream << ");";
		}
		void IfcMechanicalMaterialProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcMechanicalMaterialProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<6 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcMechanicalMaterialProperties, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>6 ){ std::cout << "Wrong parameter count for entity IfcMechanicalMaterialProperties, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readEntityReference( args[0], m_Material, map );
			m_DynamicViscosity = IfcDynamicViscosityMeasure::readStepData( args[1] );
			m_YoungModulus = IfcModulusOfElasticityMeasure::readStepData( args[2] );
			m_ShearModulus = IfcModulusOfElasticityMeasure::readStepData( args[3] );
			m_PoissonRatio = IfcPositiveRatioMeasure::readStepData( args[4] );
			m_ThermalExpansionCoefficient = IfcThermalExpansionCoefficientMeasure::readStepData( args[5] );
		}
		void IfcMechanicalMaterialProperties::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcMaterialProperties::setInverseCounterparts( ptr_self_entity );
		}
		void IfcMechanicalMaterialProperties::unlinkSelf()
		{
			IfcMaterialProperties::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
