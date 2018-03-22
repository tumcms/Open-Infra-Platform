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
#include "IfcPropertyEnumeration.h"
#include "IfcLabel.h"
#include "IfcValue.h"
#include "IfcUnit.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcPropertyEnumeration
			IfcPropertyEnumeration::IfcPropertyEnumeration() { m_entity_enum = IFCPROPERTYENUMERATION;}
			IfcPropertyEnumeration::IfcPropertyEnumeration( int id ) { m_id = id; m_entity_enum = IFCPROPERTYENUMERATION;}
			IfcPropertyEnumeration::~IfcPropertyEnumeration() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcPropertyEnumeration::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcPropertyEnumeration> other = std::dynamic_pointer_cast<IfcPropertyEnumeration>(other_entity);
				if( !other) { return; }
				m_Name = other->m_Name;
				m_EnumerationValues = other->m_EnumerationValues;
				m_Unit = other->m_Unit;
			}
			void IfcPropertyEnumeration::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCPROPERTYENUMERATION" << "(";
				if( m_Name) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				writeTypeList( stream, m_EnumerationValues );
				stream << ",";
				if( m_Unit) { m_Unit->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcPropertyEnumeration::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcPropertyEnumeration::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<3 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcPropertyEnumeration, expecting 3, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<3 ){ std::cout << "Wrong parameter count for entity IfcPropertyEnumeration, expecting 3, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_Name = IfcLabel::readStepData( args[0] );
				readSelectList( args[1], m_EnumerationValues, map );
				m_Unit = IfcUnit::readStepData( args[2], map );
			}
			void IfcPropertyEnumeration::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcPropertyAbstraction::setInverseCounterparts(ptr_self_entity);
			}
			void IfcPropertyEnumeration::unlinkSelf()
			{
				IfcPropertyAbstraction::unlinkSelf();
			}
	}
}
