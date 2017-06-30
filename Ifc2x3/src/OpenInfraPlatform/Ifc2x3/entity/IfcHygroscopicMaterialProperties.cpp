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
#include "include/IfcHygroscopicMaterialProperties.h"
#include "include/IfcIsothermalMoistureCapacityMeasure.h"
#include "include/IfcMaterial.h"
#include "include/IfcMoistureDiffusivityMeasure.h"
#include "include/IfcPositiveRatioMeasure.h"
#include "include/IfcVaporPermeabilityMeasure.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcHygroscopicMaterialProperties 
		IfcHygroscopicMaterialProperties::IfcHygroscopicMaterialProperties() { m_entity_enum = IFCHYGROSCOPICMATERIALPROPERTIES; }
		IfcHygroscopicMaterialProperties::IfcHygroscopicMaterialProperties( int id ) { m_id = id; m_entity_enum = IFCHYGROSCOPICMATERIALPROPERTIES; }
		IfcHygroscopicMaterialProperties::~IfcHygroscopicMaterialProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcHygroscopicMaterialProperties::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcHygroscopicMaterialProperties> other = dynamic_pointer_cast<IfcHygroscopicMaterialProperties>(other_entity);
			if( !other) { return; }
			m_Material = other->m_Material;
			m_UpperVaporResistanceFactor = other->m_UpperVaporResistanceFactor;
			m_LowerVaporResistanceFactor = other->m_LowerVaporResistanceFactor;
			m_IsothermalMoistureCapacity = other->m_IsothermalMoistureCapacity;
			m_VaporPermeability = other->m_VaporPermeability;
			m_MoistureDiffusivity = other->m_MoistureDiffusivity;
		}
		void IfcHygroscopicMaterialProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCHYGROSCOPICMATERIALPROPERTIES" << "(";
			if( m_Material ) { stream << "#" << m_Material->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_UpperVaporResistanceFactor ) { m_UpperVaporResistanceFactor->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LowerVaporResistanceFactor ) { m_LowerVaporResistanceFactor->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_IsothermalMoistureCapacity ) { m_IsothermalMoistureCapacity->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_VaporPermeability ) { m_VaporPermeability->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MoistureDiffusivity ) { m_MoistureDiffusivity->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcHygroscopicMaterialProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcHygroscopicMaterialProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<6 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcHygroscopicMaterialProperties, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>6 ){ std::cout << "Wrong parameter count for entity IfcHygroscopicMaterialProperties, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readEntityReference( args[0], m_Material, map );
			m_UpperVaporResistanceFactor = IfcPositiveRatioMeasure::readStepData( args[1] );
			m_LowerVaporResistanceFactor = IfcPositiveRatioMeasure::readStepData( args[2] );
			m_IsothermalMoistureCapacity = IfcIsothermalMoistureCapacityMeasure::readStepData( args[3] );
			m_VaporPermeability = IfcVaporPermeabilityMeasure::readStepData( args[4] );
			m_MoistureDiffusivity = IfcMoistureDiffusivityMeasure::readStepData( args[5] );
		}
		void IfcHygroscopicMaterialProperties::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcMaterialProperties::setInverseCounterparts( ptr_self_entity );
		}
		void IfcHygroscopicMaterialProperties::unlinkSelf()
		{
			IfcMaterialProperties::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
