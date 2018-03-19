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
#include "IfcWorkTime.h"
#include "IfcLabel.h"
#include "IfcDataOriginEnum.h"
#include "IfcLabel.h"
#include "IfcRecurrencePattern.h"
#include "IfcDate.h"
#include "IfcDate.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcWorkTime
			IfcWorkTime::IfcWorkTime() { m_entity_enum = IFCWORKTIME;}
			IfcWorkTime::IfcWorkTime( int id ) { m_id = id; m_entity_enum = IFCWORKTIME;}
			IfcWorkTime::~IfcWorkTime() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcWorkTime::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcWorkTime> other = std::dynamic_pointer_cast<IfcWorkTime>(other_entity);
				if( !other) { return; }
				m_Name = other->m_Name;
				m_DataOrigin = other->m_DataOrigin;
				m_UserDefinedDataOrigin = other->m_UserDefinedDataOrigin;
				m_RecurrencePattern = other->m_RecurrencePattern;
				m_Start = other->m_Start;
				m_Finish = other->m_Finish;
			}
			void IfcWorkTime::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCWORKTIME" << "(";
				if( m_Name) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_DataOrigin) { m_DataOrigin->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_UserDefinedDataOrigin) { m_UserDefinedDataOrigin->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_RecurrencePattern) { stream << "#" << m_RecurrencePattern->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Start) { m_Start->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Finish) { m_Finish->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcWorkTime::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcWorkTime::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<6 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcWorkTime, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<6 ){ std::cout << "Wrong parameter count for entity IfcWorkTime, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_Name = IfcLabel::readStepData( args[0] );
				m_DataOrigin = IfcDataOriginEnum::readStepData( args[1] );
				m_UserDefinedDataOrigin = IfcLabel::readStepData( args[2] );
				readEntityReference( args[3], m_RecurrencePattern, map);
				m_Start = IfcDate::readStepData( args[4] );
				m_Finish = IfcDate::readStepData( args[5] );
			}
			void IfcWorkTime::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcSchedulingTime::setInverseCounterparts(ptr_self_entity);
			}
			void IfcWorkTime::unlinkSelf()
			{
				IfcSchedulingTime::unlinkSelf();
			}
	}
}
