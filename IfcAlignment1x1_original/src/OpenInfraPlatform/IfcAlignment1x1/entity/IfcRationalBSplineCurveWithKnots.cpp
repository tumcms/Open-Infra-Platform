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
#include "IfcRationalBSplineCurveWithKnots.h"
#include "IfcInteger.h"
#include "IfcCartesianPoint.h"
#include "IfcBSplineCurveForm.h"
#include "IfcLogical.h"
#include "IfcLogical.h"
#include "IfcInteger.h"
#include "IfcParameterValue.h"
#include "IfcKnotType.h"
#include "IfcReal.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcRationalBSplineCurveWithKnots
			IfcRationalBSplineCurveWithKnots::IfcRationalBSplineCurveWithKnots() { m_entity_enum = IFCRATIONALBSPLINECURVEWITHKNOTS;}
			IfcRationalBSplineCurveWithKnots::IfcRationalBSplineCurveWithKnots( int id ) { m_id = id; m_entity_enum = IFCRATIONALBSPLINECURVEWITHKNOTS;}
			IfcRationalBSplineCurveWithKnots::~IfcRationalBSplineCurveWithKnots() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcRationalBSplineCurveWithKnots::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcRationalBSplineCurveWithKnots> other = std::dynamic_pointer_cast<IfcRationalBSplineCurveWithKnots>(other_entity);
				if( !other) { return; }
				m_Degree = other->m_Degree;
				m_ControlPointsList = other->m_ControlPointsList;
				m_CurveForm = other->m_CurveForm;
				m_ClosedCurve = other->m_ClosedCurve;
				m_SelfIntersect = other->m_SelfIntersect;
				m_KnotMultiplicities = other->m_KnotMultiplicities;
				m_Knots = other->m_Knots;
				m_KnotSpec = other->m_KnotSpec;
				m_WeightsData = other->m_WeightsData;
			}
			void IfcRationalBSplineCurveWithKnots::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCRATIONALBSPLINECURVEWITHKNOTS" << "(";
				if( m_Degree) { m_Degree->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				writeEntityList( stream, m_ControlPointsList );
				stream << ",";
				if( m_CurveForm) { m_CurveForm->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_ClosedCurve) { m_ClosedCurve->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_SelfIntersect) { m_SelfIntersect->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				writeTypeList( stream, m_KnotMultiplicities );
				stream << ",";
				writeTypeOfRealList( stream, m_Knots );
				stream << ",";
				if( m_KnotSpec) { m_KnotSpec->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				writeTypeOfRealList( stream, m_WeightsData );
				stream << ");";
			}
			void IfcRationalBSplineCurveWithKnots::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcRationalBSplineCurveWithKnots::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<9 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcRationalBSplineCurveWithKnots, expecting 9, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<9 ){ std::cout << "Wrong parameter count for entity IfcRationalBSplineCurveWithKnots, expecting 9, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_Degree = IfcInteger::readStepData( args[0] );
				readEntityReferenceList( args[1], m_ControlPointsList , map);
				m_CurveForm = IfcBSplineCurveForm::readStepData( args[2] );
				m_ClosedCurve = IfcLogical::readStepData( args[3] );
				m_SelfIntersect = IfcLogical::readStepData( args[4] );
				readTypeList( args[5], m_KnotMultiplicities );
				readTypeOfRealList( args[6], m_Knots );
				m_KnotSpec = IfcKnotType::readStepData( args[7] );
				readTypeOfRealList( args[8], m_WeightsData );
			}
			void IfcRationalBSplineCurveWithKnots::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcBSplineCurveWithKnots::setInverseCounterparts(ptr_self_entity);
			}
			void IfcRationalBSplineCurveWithKnots::unlinkSelf()
			{
				IfcBSplineCurveWithKnots::unlinkSelf();
			}
	}
}
