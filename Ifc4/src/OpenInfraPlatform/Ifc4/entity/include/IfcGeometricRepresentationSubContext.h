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
#include "OpenInfraPlatform/Ifc4/model/shared_ptr.h"
#include "OpenInfraPlatform/Ifc4/model/Ifc4Object.h"
#include "IfcGeometricRepresentationContext.h"

namespace OpenInfraPlatform
{
	namespace Ifc4
	{
		class IfcGeometricRepresentationContext;
		class IfcPositiveRatioMeasure;
		class IfcGeometricProjectionEnum;
		class IfcLabel;
		//ENTITY
		class IfcGeometricRepresentationSubContext : public IfcGeometricRepresentationContext
		{
		public:
			IfcGeometricRepresentationSubContext();
			IfcGeometricRepresentationSubContext( int id );
			~IfcGeometricRepresentationSubContext();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity( shared_ptr<Ifc4Entity> other );
			virtual void getStepLine( std::stringstream& stream ) const;
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			virtual void readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc4Entity> >& map );
			virtual void setInverseCounterparts( shared_ptr<Ifc4Entity> ptr_self );
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcGeometricRepresentationSubContext"; }


			// IfcRepresentationContext -----------------------------------------------------------
			// attributes:
			//  shared_ptr<IfcLabel>								m_ContextIdentifier;		//optional
			//  shared_ptr<IfcLabel>								m_ContextType;				//optional
			// inverse attributes:
			//  std::vector<weak_ptr<IfcRepresentation> >		m_RepresentationsInContext_inverse;

			// IfcGeometricRepresentationContext -----------------------------------------------------------
			// attributes:
			//  shared_ptr<IfcDimensionCount>					m_CoordinateSpaceDimension;
			//  double											m_Precision;				//optional
			//  shared_ptr<IfcAxis2Placement>					m_WorldCoordinateSystem;
			//  shared_ptr<IfcDirection>							m_TrueNorth;				//optional
			// inverse attributes:
			//  std::vector<weak_ptr<IfcGeometricRepresentationSubContext> >	m_HasSubContexts_inverse;
			//  std::vector<weak_ptr<IfcCoordinateOperation> >	m_HasCoordinateOperation_inverse;

			// IfcGeometricRepresentationSubContext -----------------------------------------------------------
			// attributes:
			shared_ptr<IfcGeometricRepresentationContext>	m_ParentContext;
			shared_ptr<IfcPositiveRatioMeasure>				m_TargetScale;				//optional
			shared_ptr<IfcGeometricProjectionEnum>			m_TargetView;
			shared_ptr<IfcLabel>								m_UserDefinedTargetView;	//optional
		};
	} // end namespace Ifc4
} // end namespace OpenInfraPlatform

