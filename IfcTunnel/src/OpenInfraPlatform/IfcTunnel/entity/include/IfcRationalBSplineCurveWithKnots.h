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

#pragma once
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include "../../model/shared_ptr.h"
#include "../../model/IfcTunnelObject.h"
#include "IfcBSplineCurveWithKnots.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		//ENTITY
		class IfcRationalBSplineCurveWithKnots : public IfcBSplineCurveWithKnots
		{
		public:
			IfcRationalBSplineCurveWithKnots();
			IfcRationalBSplineCurveWithKnots( int id );
			~IfcRationalBSplineCurveWithKnots();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity( shared_ptr<IfcTunnelEntity> other );
			virtual void getStepLine( std::stringstream& stream ) const;
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			virtual void readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcTunnelEntity> >& map );
			virtual void setInverseCounterparts( shared_ptr<IfcTunnelEntity> ptr_self );
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcRationalBSplineCurveWithKnots"; }


			// IfcRepresentationItem -----------------------------------------------------------
			// inverse attributes:
			//  std::vector<weak_ptr<IfcPresentationLayerAssignment> >	m_LayerAssignment_inverse;
			//  std::vector<weak_ptr<IfcStyledItem> >		m_StyledByItem_inverse;

			// IfcGeometricRepresentationItem -----------------------------------------------------------

			// IfcCurve -----------------------------------------------------------

			// IfcBoundedCurve -----------------------------------------------------------

			// IfcBSplineCurve -----------------------------------------------------------
			// attributes:
			//  int											m_Degree;
			//  std::vector<shared_ptr<IfcCartesianPoint> >	m_ControlPointsList;
			//  shared_ptr<IfcBSplineCurveForm>				m_CurveForm;
			//  bool											m_ClosedCurve;
			//  bool											m_SelfIntersect;

			// IfcBSplineCurveWithKnots -----------------------------------------------------------
			// attributes:
			//  std::vector<int >							m_KnotMultiplicities;
			//  std::vector<shared_ptr<IfcParameterValue> >	m_Knots;
			//  shared_ptr<IfcKnotType>						m_KnotSpec;

			// IfcRationalBSplineCurveWithKnots -----------------------------------------------------------
			// attributes:
			std::vector<double >							m_WeightsData;
		};
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform

