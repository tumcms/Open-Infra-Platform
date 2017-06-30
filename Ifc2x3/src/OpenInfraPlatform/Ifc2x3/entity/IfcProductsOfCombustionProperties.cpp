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
#include "include/IfcPositiveRatioMeasure.h"
#include "include/IfcProductsOfCombustionProperties.h"
#include "include/IfcSpecificHeatCapacityMeasure.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcProductsOfCombustionProperties 
		IfcProductsOfCombustionProperties::IfcProductsOfCombustionProperties() { m_entity_enum = IFCPRODUCTSOFCOMBUSTIONPROPERTIES; }
		IfcProductsOfCombustionProperties::IfcProductsOfCombustionProperties( int id ) { m_id = id; m_entity_enum = IFCPRODUCTSOFCOMBUSTIONPROPERTIES; }
		IfcProductsOfCombustionProperties::~IfcProductsOfCombustionProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcProductsOfCombustionProperties::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcProductsOfCombustionProperties> other = dynamic_pointer_cast<IfcProductsOfCombustionProperties>(other_entity);
			if( !other) { return; }
			m_Material = other->m_Material;
			m_SpecificHeatCapacity = other->m_SpecificHeatCapacity;
			m_N20Content = other->m_N20Content;
			m_COContent = other->m_COContent;
			m_CO2Content = other->m_CO2Content;
		}
		void IfcProductsOfCombustionProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCPRODUCTSOFCOMBUSTIONPROPERTIES" << "(";
			if( m_Material ) { stream << "#" << m_Material->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_SpecificHeatCapacity ) { m_SpecificHeatCapacity->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_N20Content ) { m_N20Content->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_COContent ) { m_COContent->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_CO2Content ) { m_CO2Content->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcProductsOfCombustionProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcProductsOfCombustionProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<5 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcProductsOfCombustionProperties, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>5 ){ std::cout << "Wrong parameter count for entity IfcProductsOfCombustionProperties, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readEntityReference( args[0], m_Material, map );
			m_SpecificHeatCapacity = IfcSpecificHeatCapacityMeasure::readStepData( args[1] );
			m_N20Content = IfcPositiveRatioMeasure::readStepData( args[2] );
			m_COContent = IfcPositiveRatioMeasure::readStepData( args[3] );
			m_CO2Content = IfcPositiveRatioMeasure::readStepData( args[4] );
		}
		void IfcProductsOfCombustionProperties::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcMaterialProperties::setInverseCounterparts( ptr_self_entity );
		}
		void IfcProductsOfCombustionProperties::unlinkSelf()
		{
			IfcMaterialProperties::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
