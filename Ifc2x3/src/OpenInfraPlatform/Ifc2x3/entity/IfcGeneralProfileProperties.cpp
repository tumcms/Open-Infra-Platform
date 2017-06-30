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
#include "include/IfcGeneralProfileProperties.h"
#include "include/IfcLabel.h"
#include "include/IfcMassPerLengthMeasure.h"
#include "include/IfcPositiveLengthMeasure.h"
#include "include/IfcProfileDef.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcGeneralProfileProperties 
		IfcGeneralProfileProperties::IfcGeneralProfileProperties() { m_entity_enum = IFCGENERALPROFILEPROPERTIES; }
		IfcGeneralProfileProperties::IfcGeneralProfileProperties( int id ) { m_id = id; m_entity_enum = IFCGENERALPROFILEPROPERTIES; }
		IfcGeneralProfileProperties::~IfcGeneralProfileProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcGeneralProfileProperties::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcGeneralProfileProperties> other = dynamic_pointer_cast<IfcGeneralProfileProperties>(other_entity);
			if( !other) { return; }
			m_ProfileName = other->m_ProfileName;
			m_ProfileDefinition = other->m_ProfileDefinition;
			m_PhysicalWeight = other->m_PhysicalWeight;
			m_Perimeter = other->m_Perimeter;
			m_MinimumPlateThickness = other->m_MinimumPlateThickness;
			m_MaximumPlateThickness = other->m_MaximumPlateThickness;
			m_CrossSectionArea = other->m_CrossSectionArea;
		}
		void IfcGeneralProfileProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCGENERALPROFILEPROPERTIES" << "(";
			if( m_ProfileName ) { m_ProfileName->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ProfileDefinition ) { stream << "#" << m_ProfileDefinition->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_PhysicalWeight ) { m_PhysicalWeight->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Perimeter ) { m_Perimeter->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MinimumPlateThickness ) { m_MinimumPlateThickness->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MaximumPlateThickness ) { m_MaximumPlateThickness->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_CrossSectionArea ) { m_CrossSectionArea->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcGeneralProfileProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcGeneralProfileProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<7 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcGeneralProfileProperties, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>7 ){ std::cout << "Wrong parameter count for entity IfcGeneralProfileProperties, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_ProfileName = IfcLabel::readStepData( args[0] );
			readEntityReference( args[1], m_ProfileDefinition, map );
			m_PhysicalWeight = IfcMassPerLengthMeasure::readStepData( args[2] );
			m_Perimeter = IfcPositiveLengthMeasure::readStepData( args[3] );
			m_MinimumPlateThickness = IfcPositiveLengthMeasure::readStepData( args[4] );
			m_MaximumPlateThickness = IfcPositiveLengthMeasure::readStepData( args[5] );
			m_CrossSectionArea = IfcAreaMeasure::readStepData( args[6] );
		}
		void IfcGeneralProfileProperties::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcProfileProperties::setInverseCounterparts( ptr_self_entity );
		}
		void IfcGeneralProfileProperties::unlinkSelf()
		{
			IfcProfileProperties::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
