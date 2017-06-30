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
#include "include/IfcLabel.h"
#include "include/IfcLengthMeasure.h"
#include "include/IfcMassPerLengthMeasure.h"
#include "include/IfcMomentOfInertiaMeasure.h"
#include "include/IfcPositiveLengthMeasure.h"
#include "include/IfcPositiveRatioMeasure.h"
#include "include/IfcProfileDef.h"
#include "include/IfcSectionModulusMeasure.h"
#include "include/IfcStructuralSteelProfileProperties.h"
#include "include/IfcWarpingConstantMeasure.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcStructuralSteelProfileProperties 
		IfcStructuralSteelProfileProperties::IfcStructuralSteelProfileProperties() { m_entity_enum = IFCSTRUCTURALSTEELPROFILEPROPERTIES; }
		IfcStructuralSteelProfileProperties::IfcStructuralSteelProfileProperties( int id ) { m_id = id; m_entity_enum = IFCSTRUCTURALSTEELPROFILEPROPERTIES; }
		IfcStructuralSteelProfileProperties::~IfcStructuralSteelProfileProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcStructuralSteelProfileProperties::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcStructuralSteelProfileProperties> other = dynamic_pointer_cast<IfcStructuralSteelProfileProperties>(other_entity);
			if( !other) { return; }
			m_ProfileName = other->m_ProfileName;
			m_ProfileDefinition = other->m_ProfileDefinition;
			m_PhysicalWeight = other->m_PhysicalWeight;
			m_Perimeter = other->m_Perimeter;
			m_MinimumPlateThickness = other->m_MinimumPlateThickness;
			m_MaximumPlateThickness = other->m_MaximumPlateThickness;
			m_CrossSectionArea = other->m_CrossSectionArea;
			m_TorsionalConstantX = other->m_TorsionalConstantX;
			m_MomentOfInertiaYZ = other->m_MomentOfInertiaYZ;
			m_MomentOfInertiaY = other->m_MomentOfInertiaY;
			m_MomentOfInertiaZ = other->m_MomentOfInertiaZ;
			m_WarpingConstant = other->m_WarpingConstant;
			m_ShearCentreZ = other->m_ShearCentreZ;
			m_ShearCentreY = other->m_ShearCentreY;
			m_ShearDeformationAreaZ = other->m_ShearDeformationAreaZ;
			m_ShearDeformationAreaY = other->m_ShearDeformationAreaY;
			m_MaximumSectionModulusY = other->m_MaximumSectionModulusY;
			m_MinimumSectionModulusY = other->m_MinimumSectionModulusY;
			m_MaximumSectionModulusZ = other->m_MaximumSectionModulusZ;
			m_MinimumSectionModulusZ = other->m_MinimumSectionModulusZ;
			m_TorsionalSectionModulus = other->m_TorsionalSectionModulus;
			m_CentreOfGravityInX = other->m_CentreOfGravityInX;
			m_CentreOfGravityInY = other->m_CentreOfGravityInY;
			m_ShearAreaZ = other->m_ShearAreaZ;
			m_ShearAreaY = other->m_ShearAreaY;
			m_PlasticShapeFactorY = other->m_PlasticShapeFactorY;
			m_PlasticShapeFactorZ = other->m_PlasticShapeFactorZ;
		}
		void IfcStructuralSteelProfileProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCSTRUCTURALSTEELPROFILEPROPERTIES" << "(";
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
			stream << ",";
			if( m_TorsionalConstantX ) { m_TorsionalConstantX->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MomentOfInertiaYZ ) { m_MomentOfInertiaYZ->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MomentOfInertiaY ) { m_MomentOfInertiaY->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MomentOfInertiaZ ) { m_MomentOfInertiaZ->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_WarpingConstant ) { m_WarpingConstant->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ShearCentreZ ) { m_ShearCentreZ->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ShearCentreY ) { m_ShearCentreY->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ShearDeformationAreaZ ) { m_ShearDeformationAreaZ->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ShearDeformationAreaY ) { m_ShearDeformationAreaY->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MaximumSectionModulusY ) { m_MaximumSectionModulusY->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MinimumSectionModulusY ) { m_MinimumSectionModulusY->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MaximumSectionModulusZ ) { m_MaximumSectionModulusZ->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_MinimumSectionModulusZ ) { m_MinimumSectionModulusZ->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_TorsionalSectionModulus ) { m_TorsionalSectionModulus->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_CentreOfGravityInX ) { m_CentreOfGravityInX->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_CentreOfGravityInY ) { m_CentreOfGravityInY->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ShearAreaZ ) { m_ShearAreaZ->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ShearAreaY ) { m_ShearAreaY->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_PlasticShapeFactorY ) { m_PlasticShapeFactorY->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_PlasticShapeFactorZ ) { m_PlasticShapeFactorZ->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcStructuralSteelProfileProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcStructuralSteelProfileProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<27 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcStructuralSteelProfileProperties, expecting 27, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>27 ){ std::cout << "Wrong parameter count for entity IfcStructuralSteelProfileProperties, expecting 27, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_ProfileName = IfcLabel::readStepData( args[0] );
			readEntityReference( args[1], m_ProfileDefinition, map );
			m_PhysicalWeight = IfcMassPerLengthMeasure::readStepData( args[2] );
			m_Perimeter = IfcPositiveLengthMeasure::readStepData( args[3] );
			m_MinimumPlateThickness = IfcPositiveLengthMeasure::readStepData( args[4] );
			m_MaximumPlateThickness = IfcPositiveLengthMeasure::readStepData( args[5] );
			m_CrossSectionArea = IfcAreaMeasure::readStepData( args[6] );
			m_TorsionalConstantX = IfcMomentOfInertiaMeasure::readStepData( args[7] );
			m_MomentOfInertiaYZ = IfcMomentOfInertiaMeasure::readStepData( args[8] );
			m_MomentOfInertiaY = IfcMomentOfInertiaMeasure::readStepData( args[9] );
			m_MomentOfInertiaZ = IfcMomentOfInertiaMeasure::readStepData( args[10] );
			m_WarpingConstant = IfcWarpingConstantMeasure::readStepData( args[11] );
			m_ShearCentreZ = IfcLengthMeasure::readStepData( args[12] );
			m_ShearCentreY = IfcLengthMeasure::readStepData( args[13] );
			m_ShearDeformationAreaZ = IfcAreaMeasure::readStepData( args[14] );
			m_ShearDeformationAreaY = IfcAreaMeasure::readStepData( args[15] );
			m_MaximumSectionModulusY = IfcSectionModulusMeasure::readStepData( args[16] );
			m_MinimumSectionModulusY = IfcSectionModulusMeasure::readStepData( args[17] );
			m_MaximumSectionModulusZ = IfcSectionModulusMeasure::readStepData( args[18] );
			m_MinimumSectionModulusZ = IfcSectionModulusMeasure::readStepData( args[19] );
			m_TorsionalSectionModulus = IfcSectionModulusMeasure::readStepData( args[20] );
			m_CentreOfGravityInX = IfcLengthMeasure::readStepData( args[21] );
			m_CentreOfGravityInY = IfcLengthMeasure::readStepData( args[22] );
			m_ShearAreaZ = IfcAreaMeasure::readStepData( args[23] );
			m_ShearAreaY = IfcAreaMeasure::readStepData( args[24] );
			m_PlasticShapeFactorY = IfcPositiveRatioMeasure::readStepData( args[25] );
			m_PlasticShapeFactorZ = IfcPositiveRatioMeasure::readStepData( args[26] );
		}
		void IfcStructuralSteelProfileProperties::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcStructuralProfileProperties::setInverseCounterparts( ptr_self_entity );
		}
		void IfcStructuralSteelProfileProperties::unlinkSelf()
		{
			IfcStructuralProfileProperties::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
