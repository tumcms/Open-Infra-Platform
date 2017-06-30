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
#include "include/IfcMaterial.h"
#include "include/IfcOpticalMaterialProperties.h"
#include "include/IfcPositiveRatioMeasure.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcOpticalMaterialProperties 
		IfcOpticalMaterialProperties::IfcOpticalMaterialProperties() { m_entity_enum = IFCOPTICALMATERIALPROPERTIES; }
		IfcOpticalMaterialProperties::IfcOpticalMaterialProperties( int id ) { m_id = id; m_entity_enum = IFCOPTICALMATERIALPROPERTIES; }
		IfcOpticalMaterialProperties::~IfcOpticalMaterialProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcOpticalMaterialProperties::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcOpticalMaterialProperties> other = dynamic_pointer_cast<IfcOpticalMaterialProperties>(other_entity);
			if( !other) { return; }
			m_Material = other->m_Material;
			m_VisibleTransmittance = other->m_VisibleTransmittance;
			m_SolarTransmittance = other->m_SolarTransmittance;
			m_ThermalIrTransmittance = other->m_ThermalIrTransmittance;
			m_ThermalIrEmissivityBack = other->m_ThermalIrEmissivityBack;
			m_ThermalIrEmissivityFront = other->m_ThermalIrEmissivityFront;
			m_VisibleReflectanceBack = other->m_VisibleReflectanceBack;
			m_VisibleReflectanceFront = other->m_VisibleReflectanceFront;
			m_SolarReflectanceFront = other->m_SolarReflectanceFront;
			m_SolarReflectanceBack = other->m_SolarReflectanceBack;
		}
		void IfcOpticalMaterialProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCOPTICALMATERIALPROPERTIES" << "(";
			if( m_Material ) { stream << "#" << m_Material->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_VisibleTransmittance ) { m_VisibleTransmittance->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_SolarTransmittance ) { m_SolarTransmittance->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ThermalIrTransmittance ) { m_ThermalIrTransmittance->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ThermalIrEmissivityBack ) { m_ThermalIrEmissivityBack->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ThermalIrEmissivityFront ) { m_ThermalIrEmissivityFront->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_VisibleReflectanceBack ) { m_VisibleReflectanceBack->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_VisibleReflectanceFront ) { m_VisibleReflectanceFront->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_SolarReflectanceFront ) { m_SolarReflectanceFront->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_SolarReflectanceBack ) { m_SolarReflectanceBack->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcOpticalMaterialProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcOpticalMaterialProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<10 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcOpticalMaterialProperties, expecting 10, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>10 ){ std::cout << "Wrong parameter count for entity IfcOpticalMaterialProperties, expecting 10, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readEntityReference( args[0], m_Material, map );
			m_VisibleTransmittance = IfcPositiveRatioMeasure::readStepData( args[1] );
			m_SolarTransmittance = IfcPositiveRatioMeasure::readStepData( args[2] );
			m_ThermalIrTransmittance = IfcPositiveRatioMeasure::readStepData( args[3] );
			m_ThermalIrEmissivityBack = IfcPositiveRatioMeasure::readStepData( args[4] );
			m_ThermalIrEmissivityFront = IfcPositiveRatioMeasure::readStepData( args[5] );
			m_VisibleReflectanceBack = IfcPositiveRatioMeasure::readStepData( args[6] );
			m_VisibleReflectanceFront = IfcPositiveRatioMeasure::readStepData( args[7] );
			m_SolarReflectanceFront = IfcPositiveRatioMeasure::readStepData( args[8] );
			m_SolarReflectanceBack = IfcPositiveRatioMeasure::readStepData( args[9] );
		}
		void IfcOpticalMaterialProperties::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcMaterialProperties::setInverseCounterparts( ptr_self_entity );
		}
		void IfcOpticalMaterialProperties::unlinkSelf()
		{
			IfcMaterialProperties::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
