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
#include "IfcControl.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		class IfcIdentifier;
		class IfcDateTimeSelect;
		class IfcPerson;
		class IfcLabel;
		class IfcTimeMeasure;
		class IfcWorkControlTypeEnum;
		//ENTITY
		class IfcWorkControl : public IfcControl
		{
		public:
			IfcWorkControl();
			IfcWorkControl( int id );
			~IfcWorkControl();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity( shared_ptr<Ifc2x3Entity> other );
			virtual void getStepLine( std::stringstream& stream ) const;
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			virtual void readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map );
			virtual void setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self );
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcWorkControl"; }


			// IfcRoot -----------------------------------------------------------
			// attributes:
			//  shared_ptr<IfcGloballyUniqueId>				m_GlobalId;
			//  shared_ptr<IfcOwnerHistory>					m_OwnerHistory;
			//  shared_ptr<IfcLabel>							m_Name;						//optional
			//  shared_ptr<IfcText>							m_Description;				//optional

			// IfcObjectDefinition -----------------------------------------------------------
			// inverse attributes:
			//  std::vector<weak_ptr<IfcRelAssigns> >		m_HasAssignments_inverse;
			//  std::vector<weak_ptr<IfcRelDecomposes> >		m_IsDecomposedBy_inverse;
			//  std::vector<weak_ptr<IfcRelDecomposes> >		m_Decomposes_inverse;
			//  std::vector<weak_ptr<IfcRelAssociates> >		m_HasAssociations_inverse;

			// IfcObject -----------------------------------------------------------
			// attributes:
			//  shared_ptr<IfcLabel>							m_ObjectType;				//optional
			// inverse attributes:
			//  std::vector<weak_ptr<IfcRelDefines> >		m_IsDefinedBy_inverse;

			// IfcControl -----------------------------------------------------------
			// inverse attributes:
			//  std::vector<weak_ptr<IfcRelAssignsToControl> >	m_Controls_inverse;

			// IfcWorkControl -----------------------------------------------------------
			// attributes:
			shared_ptr<IfcIdentifier>					m_Identifier;
			shared_ptr<IfcDateTimeSelect>				m_CreationDate;
			std::vector<shared_ptr<IfcPerson> >			m_Creators;					//optional
			shared_ptr<IfcLabel>							m_Purpose;					//optional
			shared_ptr<IfcTimeMeasure>					m_Duration;					//optional
			shared_ptr<IfcTimeMeasure>					m_TotalFloat;				//optional
			shared_ptr<IfcDateTimeSelect>				m_StartTime;
			shared_ptr<IfcDateTimeSelect>				m_FinishTime;				//optional
			shared_ptr<IfcWorkControlTypeEnum>			m_WorkControlType;			//optional
			shared_ptr<IfcLabel>							m_UserDefinedControlType;	//optional
		};
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform

