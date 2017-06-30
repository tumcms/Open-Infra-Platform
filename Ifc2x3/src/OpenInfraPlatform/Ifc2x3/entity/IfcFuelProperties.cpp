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
#include "include/IfcFuelProperties.h"
#include "include/IfcHeatingValueMeasure.h"
#include "include/IfcMaterial.h"
#include "include/IfcPositiveRatioMeasure.h"
#include "include/IfcThermodynamicTemperatureMeasure.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcFuelProperties 
		IfcFuelProperties::IfcFuelProperties() { m_entity_enum = IFCFUELPROPERTIES; }
		IfcFuelProperties::IfcFuelProperties( int id ) { m_id = id; m_entity_enum = IFCFUELPROPERTIES; }
		IfcFuelProperties::~IfcFuelProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcFuelProperties::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcFuelProperties> other = dynamic_pointer_cast<IfcFuelProperties>(other_entity);
			if( !other) { return; }
			m_Material = other->m_Material;
			m_CombustionTemperature = other->m_CombustionTemperature;
			m_CarbonContent = other->m_CarbonContent;
			m_LowerHeatingValue = other->m_LowerHeatingValue;
			m_HigherHeatingValue = other->m_HigherHeatingValue;
		}
		void IfcFuelProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCFUELPROPERTIES" << "(";
			if( m_Material ) { stream << "#" << m_Material->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_CombustionTemperature ) { m_CombustionTemperature->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_CarbonContent ) { m_CarbonContent->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LowerHeatingValue ) { m_LowerHeatingValue->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_HigherHeatingValue ) { m_HigherHeatingValue->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcFuelProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcFuelProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<5 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcFuelProperties, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>5 ){ std::cout << "Wrong parameter count for entity IfcFuelProperties, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readEntityReference( args[0], m_Material, map );
			m_CombustionTemperature = IfcThermodynamicTemperatureMeasure::readStepData( args[1] );
			m_CarbonContent = IfcPositiveRatioMeasure::readStepData( args[2] );
			m_LowerHeatingValue = IfcHeatingValueMeasure::readStepData( args[3] );
			m_HigherHeatingValue = IfcHeatingValueMeasure::readStepData( args[4] );
		}
		void IfcFuelProperties::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcMaterialProperties::setInverseCounterparts( ptr_self_entity );
		}
		void IfcFuelProperties::unlinkSelf()
		{
			IfcMaterialProperties::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
