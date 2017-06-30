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
	namespace IfcAlignment
	{
		enum IfcAlignmentP6EntityEnum;

		class IfcAlignmentP6Object
		{
		public:
			virtual const char* classname() const
			{
				return "IfcAlignmentObject";
			}
			virtual void getStepData( std::stringstream& ) {};
		};

		class IfcAlignmentP6Entity : public IfcAlignmentP6Object
		{
		protected:
			int m_id;

		public:
			IfcAlignmentP6Entity();
			IfcAlignmentP6Entity( int id );
			virtual ~IfcAlignmentP6Entity();
			virtual const char* classname() const
			{
				return "IfcAlignmentEntity";
			}
			virtual void getStepLine( std::stringstream& stream ) const;
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			virtual void readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignmentP6Entity> >& map );
			virtual void setInverseCounterparts( shared_ptr<IfcAlignmentP6Entity> ptr_self );
			virtual void unlinkSelf();
			virtual const int getId() const
			{
				return m_id;
			}
			void setId( int id );
			std::string m_arguments;
			IfcAlignmentP6EntityEnum m_entity_enum;
		};

		//// pure abstract class to derive IFC TYPEs from
		class IfcAlignmentP6Type : public IfcAlignmentP6Object
		{
		public:
			virtual const char* classname() const
			{
				return "IfcAlignmentType";
			}
			virtual void getStepData( std::stringstream& ) {};
		};


		//// pure abstract class to derive IFC TYPEs from
		class IfcAlignmentP6AbstractSelect
		{
		public:
			virtual const char* classname() const
			{
				return "AbstractSelect";
			}
			virtual void getStepData( std::stringstream& ) {};
		};

		class IfcAlignmentP6AbstractEnum
		{
		public:
			virtual const char* classname() const
			{
				return "AbstractEnum";
			}
			virtual void getStepData( std::stringstream& ) {};
		};
	} // end namespace IfcAlignment
} // end namespace OpenInfraPlatform