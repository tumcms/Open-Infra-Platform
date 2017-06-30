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
#include "include/IfcAreaMeasure.h"
#include "include/IfcCountMeasure.h"
#include "include/IfcLabel.h"
#include "include/IfcLengthMeasure.h"
#include "include/IfcPositiveLengthMeasure.h"
#include "include/IfcReinforcementBarProperties.h"
#include "include/IfcReinforcingBarSurfaceEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcReinforcementBarProperties 
		IfcReinforcementBarProperties::IfcReinforcementBarProperties() { m_entity_enum = IFCREINFORCEMENTBARPROPERTIES; }
		IfcReinforcementBarProperties::IfcReinforcementBarProperties( int id ) { m_id = id; m_entity_enum = IFCREINFORCEMENTBARPROPERTIES; }
		IfcReinforcementBarProperties::~IfcReinforcementBarProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcReinforcementBarProperties::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcReinforcementBarProperties> other = dynamic_pointer_cast<IfcReinforcementBarProperties>(other_entity);
			if( !other) { return; }
			m_TotalCrossSectionArea = other->m_TotalCrossSectionArea;
			m_SteelGrade = other->m_SteelGrade;
			m_BarSurface = other->m_BarSurface;
			m_EffectiveDepth = other->m_EffectiveDepth;
			m_NominalBarDiameter = other->m_NominalBarDiameter;
			m_BarCount = other->m_BarCount;
		}
		void IfcReinforcementBarProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCREINFORCEMENTBARPROPERTIES" << "(";
			if( m_TotalCrossSectionArea ) { m_TotalCrossSectionArea->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_SteelGrade ) { m_SteelGrade->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_BarSurface ) { m_BarSurface->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_EffectiveDepth ) { m_EffectiveDepth->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_NominalBarDiameter ) { m_NominalBarDiameter->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_BarCount ) { m_BarCount->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcReinforcementBarProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcReinforcementBarProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<6 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcReinforcementBarProperties, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>6 ){ std::cout << "Wrong parameter count for entity IfcReinforcementBarProperties, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_TotalCrossSectionArea = IfcAreaMeasure::readStepData( args[0] );
			m_SteelGrade = IfcLabel::readStepData( args[1] );
			m_BarSurface = IfcReinforcingBarSurfaceEnum::readStepData( args[2] );
			m_EffectiveDepth = IfcLengthMeasure::readStepData( args[3] );
			m_NominalBarDiameter = IfcPositiveLengthMeasure::readStepData( args[4] );
			m_BarCount = IfcCountMeasure::readStepData( args[5] );
		}
		void IfcReinforcementBarProperties::setInverseCounterparts( shared_ptr<Ifc2x3Entity> )
		{
		}
		void IfcReinforcementBarProperties::unlinkSelf()
		{
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
