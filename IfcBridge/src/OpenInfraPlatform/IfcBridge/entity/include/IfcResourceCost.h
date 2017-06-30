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
#include "../../model/IfcBridgeObject.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		class IfcLabel;
		class IfcDataOriginEnum;
		class IfcDateTime;
		class IfcMonetaryMeasure;
		//ENTITY
		class IfcResourceCost : public IfcBridgeEntity
		{
		public:
			IfcResourceCost();
			IfcResourceCost( int id );
			~IfcResourceCost();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity( shared_ptr<IfcBridgeEntity> other );
			virtual void getStepLine( std::stringstream& stream ) const;
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			virtual void readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcBridgeEntity> >& map );
			virtual void setInverseCounterparts( shared_ptr<IfcBridgeEntity> ptr_self );
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcResourceCost"; }


			// IfcResourceCost -----------------------------------------------------------
			// attributes:
			shared_ptr<IfcLabel>							m_Name;						//optional
			shared_ptr<IfcDataOriginEnum>				m_DataOrigin;				//optional
			shared_ptr<IfcLabel>							m_UserDefinedDataOrigin;	//optional
			shared_ptr<IfcDateTime>						m_StatusDate;				//optional
			shared_ptr<IfcMonetaryMeasure>				m_ScheduleCost;				//optional
			shared_ptr<IfcMonetaryMeasure>				m_ActualCost;				//optional
			shared_ptr<IfcMonetaryMeasure>				m_RemainingCost;			//optional
			shared_ptr<IfcMonetaryMeasure>				m_PlannedValue;				//optional
			shared_ptr<IfcMonetaryMeasure>				m_EarnedValue;				//optional
			shared_ptr<IfcMonetaryMeasure>				m_ActualValue;				//optional
		};
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform

