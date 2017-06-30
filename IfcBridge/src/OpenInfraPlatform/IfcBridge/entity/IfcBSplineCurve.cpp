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

#include "model/IfcBridgeException.h"
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "IfcBridgeEntityEnums.h"
#include "include/IfcBSplineCurve.h"
#include "include/IfcBSplineCurveForm.h"
#include "include/IfcCartesianPoint.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcStyledItem.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// ENTITY IfcBSplineCurve 
		IfcBSplineCurve::IfcBSplineCurve() { m_entity_enum = IFCBSPLINECURVE; }
		IfcBSplineCurve::IfcBSplineCurve( int id ) { m_id = id; m_entity_enum = IFCBSPLINECURVE; }
		IfcBSplineCurve::~IfcBSplineCurve() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcBSplineCurve::setEntity( shared_ptr<IfcBridgeEntity> other_entity )
		{
			shared_ptr<IfcBSplineCurve> other = dynamic_pointer_cast<IfcBSplineCurve>(other_entity);
			if( !other) { return; }
			m_Degree = other->m_Degree;
			m_ControlPointsList = other->m_ControlPointsList;
			m_CurveForm = other->m_CurveForm;
			m_ClosedCurve = other->m_ClosedCurve;
			m_SelfIntersect = other->m_SelfIntersect;
		}
		void IfcBSplineCurve::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCBSPLINECURVE" << "(";
			if( m_Degree == m_Degree ){ stream << m_Degree; }
			else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_ControlPointsList );
			stream << ",";
			if( m_CurveForm ) { m_CurveForm->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ClosedCurve == false ) { stream << ".F."; }
			else if( m_ClosedCurve == true ) { stream << ".T."; }
			stream << ",";
			if( m_SelfIntersect == false ) { stream << ".F."; }
			else if( m_SelfIntersect == true ) { stream << ".T."; }
			stream << ");";
		}
		void IfcBSplineCurve::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcBSplineCurve::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcBridgeEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<5 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcBSplineCurve, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcBridgeException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>5 ){ std::cout << "Wrong parameter count for entity IfcBSplineCurve, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readIntValue( args[0], m_Degree );
			readEntityReferenceList( args[1], m_ControlPointsList, map );
			m_CurveForm = IfcBSplineCurveForm::readStepData( args[2] );
			if( _stricmp( args[3].c_str(), ".F." ) == 0 ) { m_ClosedCurve = false; }
			else if( _stricmp( args[3].c_str(), ".T." ) == 0 ) { m_ClosedCurve = true; }
			if( _stricmp( args[4].c_str(), ".F." ) == 0 ) { m_SelfIntersect = false; }
			else if( _stricmp( args[4].c_str(), ".T." ) == 0 ) { m_SelfIntersect = true; }
		}
		void IfcBSplineCurve::setInverseCounterparts( shared_ptr<IfcBridgeEntity> ptr_self_entity )
		{
			IfcBoundedCurve::setInverseCounterparts( ptr_self_entity );
		}
		void IfcBSplineCurve::unlinkSelf()
		{
			IfcBoundedCurve::unlinkSelf();
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
