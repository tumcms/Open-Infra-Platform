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
#include "IfcRationalBSplineSurfaceWithKnots.h"
#include "IfcInteger.h"
#include "IfcInteger.h"
#include "IfcCartesianPoint.h"
#include "IfcBSplineSurfaceForm.h"
#include "IfcLogical.h"
#include "IfcLogical.h"
#include "IfcLogical.h"
#include "IfcInteger.h"
#include "IfcInteger.h"
#include "IfcParameterValue.h"
#include "IfcParameterValue.h"
#include "IfcKnotType.h"
#include "IfcReal.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcRationalBSplineSurfaceWithKnots
			IfcRationalBSplineSurfaceWithKnots::IfcRationalBSplineSurfaceWithKnots() { m_entity_enum = IFCRATIONALBSPLINESURFACEWITHKNOTS;}
			IfcRationalBSplineSurfaceWithKnots::IfcRationalBSplineSurfaceWithKnots( int id ) { m_id = id; m_entity_enum = IFCRATIONALBSPLINESURFACEWITHKNOTS;}
			IfcRationalBSplineSurfaceWithKnots::~IfcRationalBSplineSurfaceWithKnots() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcRationalBSplineSurfaceWithKnots::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcRationalBSplineSurfaceWithKnots> other = std::dynamic_pointer_cast<IfcRationalBSplineSurfaceWithKnots>(other_entity);
				if( !other) { return; }
				m_UDegree = other->m_UDegree;
				m_VDegree = other->m_VDegree;
				m_ControlPointsList = other->m_ControlPointsList;
				m_SurfaceForm = other->m_SurfaceForm;
				m_UClosed = other->m_UClosed;
				m_VClosed = other->m_VClosed;
				m_SelfIntersect = other->m_SelfIntersect;
				m_UMultiplicities = other->m_UMultiplicities;
				m_VMultiplicities = other->m_VMultiplicities;
				m_UKnots = other->m_UKnots;
				m_VKnots = other->m_VKnots;
				m_KnotSpec = other->m_KnotSpec;
				m_WeightsData = other->m_WeightsData;
			}
			void IfcRationalBSplineSurfaceWithKnots::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCRATIONALBSPLINESURFACEWITHKNOTS" << "(";
				if( m_UDegree) { m_UDegree->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_VDegree) { m_VDegree->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				writeEntityList2D( stream, m_ControlPointsList );
				stream << ",";
				if( m_SurfaceForm) { m_SurfaceForm->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_UClosed) { m_UClosed->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_VClosed) { m_VClosed->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_SelfIntersect) { m_SelfIntersect->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				writeTypeList( stream, m_UMultiplicities );
				stream << ",";
				writeTypeList( stream, m_VMultiplicities );
				stream << ",";
				writeTypeOfRealList( stream, m_UKnots );
				stream << ",";
				writeTypeOfRealList( stream, m_VKnots );
				stream << ",";
				if( m_KnotSpec) { m_KnotSpec->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				writeTypeOfRealList2D( stream, m_WeightsData );
				stream << ");";
			}
			void IfcRationalBSplineSurfaceWithKnots::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcRationalBSplineSurfaceWithKnots::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<13 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcRationalBSplineSurfaceWithKnots, expecting 13, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<13 ){ std::cout << "Wrong parameter count for entity IfcRationalBSplineSurfaceWithKnots, expecting 13, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_UDegree = IfcInteger::readStepData( args[0] );
				m_VDegree = IfcInteger::readStepData( args[1] );
				readEntityReferenceList2D( args[2], m_ControlPointsList , map);
				m_SurfaceForm = IfcBSplineSurfaceForm::readStepData( args[3] );
				m_UClosed = IfcLogical::readStepData( args[4] );
				m_VClosed = IfcLogical::readStepData( args[5] );
				m_SelfIntersect = IfcLogical::readStepData( args[6] );
				readTypeList( args[7], m_UMultiplicities );
				readTypeList( args[8], m_VMultiplicities );
				readTypeOfRealList( args[9], m_UKnots );
				readTypeOfRealList( args[10], m_VKnots );
				m_KnotSpec = IfcKnotType::readStepData( args[11] );
				readTypeOfRealList2D( args[12], m_WeightsData);
			}
			void IfcRationalBSplineSurfaceWithKnots::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcBSplineSurfaceWithKnots::setInverseCounterparts(ptr_self_entity);
			}
			void IfcRationalBSplineSurfaceWithKnots::unlinkSelf()
			{
				IfcBSplineSurfaceWithKnots::unlinkSelf();
			}
	}
}
