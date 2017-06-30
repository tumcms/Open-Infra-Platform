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

#include <sstream>
#include <vector>
#include <map>
#include "../model/shared_ptr.h"

namespace OpenInfraPlatform
{
	namespace IfcRoad
	{
		enum IfcRoadEntityEnum;

		class IfcRoadObject
		{
		public:
			virtual const char* classname() const
			{
				return "IfcAlignmentObject";
			}
			virtual void getStepData( std::stringstream& ) {};
		};

		class IfcRoadEntity : public IfcRoadObject
		{
		protected:
			int m_id;

		public:
			IfcRoadEntity();
			IfcRoadEntity( int id );
			virtual ~IfcRoadEntity();
			virtual const char* classname() const
			{
				return "IfcAlignmentEntity";
			}
			virtual void getStepLine( std::stringstream& stream ) const;
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			virtual void readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcRoadEntity> >& map );
			virtual void setInverseCounterparts( shared_ptr<IfcRoadEntity> ptr_self );
			virtual void unlinkSelf();
			virtual const int getId() const
			{
				return m_id;
			}
			void setId( int id );
			std::string m_arguments;
			IfcRoadEntityEnum m_entity_enum;
		};

		//// pure abstract class to derive IFC TYPEs from
		class IfcRoadType : public IfcRoadObject
		{
		public:
			virtual const char* classname() const
			{
				return "IfcAlignmentType";
			}
			virtual void getStepData( std::stringstream& ) {};
		};


		//// pure abstract class to derive IFC TYPEs from
		class IfcRoadAbstractSelect
		{
		public:
			virtual const char* classname() const
			{
				return "AbstractSelect";
			}
			virtual void getStepData( std::stringstream& ) {};
		};

		class IfcRoadAbstractEnum
		{
		public:
			virtual const char* classname() const
			{
				return "AbstractEnum";
			}
			virtual void getStepData( std::stringstream& ) {};
		};
	} // end namespace IfcRoad
} // end namespace OpenInfraPlatform