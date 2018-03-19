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
#include "OpenInfraPlatform/IfcAlignment1x1/model/Exception.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1EntityEnums.h"
#include "IfcStructuralLoadSingleDisplacementDistortion.h"
#include "IfcLabel.h"
#include "IfcLengthMeasure.h"
#include "IfcLengthMeasure.h"
#include "IfcLengthMeasure.h"
#include "IfcPlaneAngleMeasure.h"
#include "IfcPlaneAngleMeasure.h"
#include "IfcPlaneAngleMeasure.h"
#include "IfcCurvatureMeasure.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcStructuralLoadSingleDisplacementDistortion
			IfcStructuralLoadSingleDisplacementDistortion::IfcStructuralLoadSingleDisplacementDistortion() { m_entity_enum = IFCSTRUCTURALLOADSINGLEDISPLACEMENTDISTORTION;}
			IfcStructuralLoadSingleDisplacementDistortion::IfcStructuralLoadSingleDisplacementDistortion( int id ) { m_id = id; m_entity_enum = IFCSTRUCTURALLOADSINGLEDISPLACEMENTDISTORTION;}
			IfcStructuralLoadSingleDisplacementDistortion::~IfcStructuralLoadSingleDisplacementDistortion() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcStructuralLoadSingleDisplacementDistortion::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcStructuralLoadSingleDisplacementDistortion> other = std::dynamic_pointer_cast<IfcStructuralLoadSingleDisplacementDistortion>(other_entity);
				if( !other) { return; }
				m_Name = other->m_Name;
				m_DisplacementX = other->m_DisplacementX;
				m_DisplacementY = other->m_DisplacementY;
				m_DisplacementZ = other->m_DisplacementZ;
				m_RotationalDisplacementRX = other->m_RotationalDisplacementRX;
				m_RotationalDisplacementRY = other->m_RotationalDisplacementRY;
				m_RotationalDisplacementRZ = other->m_RotationalDisplacementRZ;
				m_Distortion = other->m_Distortion;
			}
			void IfcStructuralLoadSingleDisplacementDistortion::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCSTRUCTURALLOADSINGLEDISPLACEMENTDISTORTION" << "(";
				if( m_Name) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_DisplacementX) { m_DisplacementX->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_DisplacementY) { m_DisplacementY->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_DisplacementZ) { m_DisplacementZ->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_RotationalDisplacementRX) { m_RotationalDisplacementRX->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_RotationalDisplacementRY) { m_RotationalDisplacementRY->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_RotationalDisplacementRZ) { m_RotationalDisplacementRZ->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Distortion) { m_Distortion->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcStructuralLoadSingleDisplacementDistortion::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcStructuralLoadSingleDisplacementDistortion::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<8 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcStructuralLoadSingleDisplacementDistortion, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<8 ){ std::cout << "Wrong parameter count for entity IfcStructuralLoadSingleDisplacementDistortion, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_Name = IfcLabel::readStepData( args[0] );
				m_DisplacementX = IfcLengthMeasure::readStepData( args[1] );
				m_DisplacementY = IfcLengthMeasure::readStepData( args[2] );
				m_DisplacementZ = IfcLengthMeasure::readStepData( args[3] );
				m_RotationalDisplacementRX = IfcPlaneAngleMeasure::readStepData( args[4] );
				m_RotationalDisplacementRY = IfcPlaneAngleMeasure::readStepData( args[5] );
				m_RotationalDisplacementRZ = IfcPlaneAngleMeasure::readStepData( args[6] );
				m_Distortion = IfcCurvatureMeasure::readStepData( args[7] );
			}
			void IfcStructuralLoadSingleDisplacementDistortion::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcStructuralLoadSingleDisplacement::setInverseCounterparts(ptr_self_entity);
			}
			void IfcStructuralLoadSingleDisplacementDistortion::unlinkSelf()
			{
				IfcStructuralLoadSingleDisplacement::unlinkSelf();
			}
	}
}
