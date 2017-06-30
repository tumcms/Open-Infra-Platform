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
#include "include/IfcIonConcentrationMeasure.h"
#include "include/IfcMaterial.h"
#include "include/IfcNormalisedRatioMeasure.h"
#include "include/IfcPHMeasure.h"
#include "include/IfcWaterProperties.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcWaterProperties 
		IfcWaterProperties::IfcWaterProperties() { m_entity_enum = IFCWATERPROPERTIES; }
		IfcWaterProperties::IfcWaterProperties( int id ) { m_id = id; m_entity_enum = IFCWATERPROPERTIES; }
		IfcWaterProperties::~IfcWaterProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcWaterProperties::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcWaterProperties> other = dynamic_pointer_cast<IfcWaterProperties>(other_entity);
			if( !other) { return; }
			m_Material = other->m_Material;
			m_IsPotable = other->m_IsPotable;
			m_Hardness = other->m_Hardness;
			m_AlkalinityConcentration = other->m_AlkalinityConcentration;
			m_AcidityConcentration = other->m_AcidityConcentration;
			m_ImpuritiesContent = other->m_ImpuritiesContent;
			m_PHLevel = other->m_PHLevel;
			m_DissolvedSolidsContent = other->m_DissolvedSolidsContent;
		}
		void IfcWaterProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCWATERPROPERTIES" << "(";
			if( m_Material ) { stream << "#" << m_Material->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_IsPotable == false ) { stream << ".F."; }
			else if( m_IsPotable == true ) { stream << ".T."; }
			stream << ",";
			if( m_Hardness ) { m_Hardness->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_AlkalinityConcentration ) { m_AlkalinityConcentration->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_AcidityConcentration ) { m_AcidityConcentration->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ImpuritiesContent ) { m_ImpuritiesContent->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_PHLevel ) { m_PHLevel->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_DissolvedSolidsContent ) { m_DissolvedSolidsContent->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcWaterProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcWaterProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<8 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcWaterProperties, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>8 ){ std::cout << "Wrong parameter count for entity IfcWaterProperties, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readEntityReference( args[0], m_Material, map );
			if( _stricmp( args[1].c_str(), ".F." ) == 0 ) { m_IsPotable = false; }
			else if( _stricmp( args[1].c_str(), ".T." ) == 0 ) { m_IsPotable = true; }
			m_Hardness = IfcIonConcentrationMeasure::readStepData( args[2] );
			m_AlkalinityConcentration = IfcIonConcentrationMeasure::readStepData( args[3] );
			m_AcidityConcentration = IfcIonConcentrationMeasure::readStepData( args[4] );
			m_ImpuritiesContent = IfcNormalisedRatioMeasure::readStepData( args[5] );
			m_PHLevel = IfcPHMeasure::readStepData( args[6] );
			m_DissolvedSolidsContent = IfcNormalisedRatioMeasure::readStepData( args[7] );
		}
		void IfcWaterProperties::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcMaterialProperties::setInverseCounterparts( ptr_self_entity );
		}
		void IfcWaterProperties::unlinkSelf()
		{
			IfcMaterialProperties::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
