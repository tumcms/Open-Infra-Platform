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
#include "../../model/Ifc2x3Object.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		class IfcAreaMeasure;
		class IfcLabel;
		class IfcReinforcingBarSurfaceEnum;
		class IfcLengthMeasure;
		class IfcPositiveLengthMeasure;
		class IfcCountMeasure;
		//ENTITY
		class IfcReinforcementBarProperties : public Ifc2x3Entity
		{
		public:
			IfcReinforcementBarProperties();
			IfcReinforcementBarProperties( int id );
			~IfcReinforcementBarProperties();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity( shared_ptr<Ifc2x3Entity> other );
			virtual void getStepLine( std::stringstream& stream ) const;
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			virtual void readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map );
			virtual void setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self );
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcReinforcementBarProperties"; }


			// IfcReinforcementBarProperties -----------------------------------------------------------
			// attributes:
			shared_ptr<IfcAreaMeasure>					m_TotalCrossSectionArea;
			shared_ptr<IfcLabel>							m_SteelGrade;
			shared_ptr<IfcReinforcingBarSurfaceEnum>		m_BarSurface;				//optional
			shared_ptr<IfcLengthMeasure>					m_EffectiveDepth;			//optional
			shared_ptr<IfcPositiveLengthMeasure>			m_NominalBarDiameter;		//optional
			shared_ptr<IfcCountMeasure>					m_BarCount;					//optional
		};
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform

