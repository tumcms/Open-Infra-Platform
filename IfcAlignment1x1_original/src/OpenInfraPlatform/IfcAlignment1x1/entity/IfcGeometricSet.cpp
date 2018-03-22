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
#include "IfcGeometricSet.h"
#include "IfcGeometricSetSelect.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcGeometricSet
			IfcGeometricSet::IfcGeometricSet() { m_entity_enum = IFCGEOMETRICSET;}
			IfcGeometricSet::IfcGeometricSet( int id ) { m_id = id; m_entity_enum = IFCGEOMETRICSET;}
			IfcGeometricSet::~IfcGeometricSet() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcGeometricSet::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcGeometricSet> other = std::dynamic_pointer_cast<IfcGeometricSet>(other_entity);
				if( !other) { return; }
				m_Elements = other->m_Elements;
			}
			void IfcGeometricSet::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCGEOMETRICSET" << "(";
				writeTypeList( stream, m_Elements );
				stream << ");";
			}
			void IfcGeometricSet::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcGeometricSet::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<1 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcGeometricSet, expecting 1, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<1 ){ std::cout << "Wrong parameter count for entity IfcGeometricSet, expecting 1, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				readSelectList( args[0], m_Elements, map );
			}
			void IfcGeometricSet::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcGeometricRepresentationItem::setInverseCounterparts(ptr_self_entity);
			}
			void IfcGeometricSet::unlinkSelf()
			{
				IfcGeometricRepresentationItem::unlinkSelf();
			}
	}
}
