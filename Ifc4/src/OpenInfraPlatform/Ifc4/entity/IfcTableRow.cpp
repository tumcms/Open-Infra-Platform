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

#include "OpenInfraPlatform/Ifc4/model/Ifc4Exception.h"
#include "OpenInfraPlatform/Ifc4/reader/ReaderUtil.h"
#include "OpenInfraPlatform/Ifc4/writer/WriterUtil.h"
#include "OpenInfraPlatform/Ifc4/Ifc4EntityEnums.h"
#include "include/IfcBoolean.h"
#include "include/IfcTableRow.h"
#include "include/IfcValue.h"

namespace OpenInfraPlatform
{
	namespace Ifc4
	{
		// ENTITY IfcTableRow 
		IfcTableRow::IfcTableRow() { m_entity_enum = IFCTABLEROW; }
		IfcTableRow::IfcTableRow( int id ) { m_id = id; m_entity_enum = IFCTABLEROW; }
		IfcTableRow::~IfcTableRow() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcTableRow::setEntity( shared_ptr<Ifc4Entity> other_entity )
		{
			shared_ptr<IfcTableRow> other = dynamic_pointer_cast<IfcTableRow>(other_entity);
			if( !other) { return; }
			m_RowCells = other->m_RowCells;
			m_IsHeading = other->m_IsHeading;
		}
		void IfcTableRow::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCTABLEROW" << "(";
			writeTypeList( stream, m_RowCells, true );
			stream << ",";
			if( m_IsHeading ) { m_IsHeading->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcTableRow::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcTableRow::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc4Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<2 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcTableRow, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc4Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>2 ){ std::cout << "Wrong parameter count for entity IfcTableRow, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readSelectList( args[0], m_RowCells, map );
			m_IsHeading = IfcBoolean::readStepData( args[1] );
		}
		void IfcTableRow::setInverseCounterparts( shared_ptr<Ifc4Entity> )
		{
		}
		void IfcTableRow::unlinkSelf()
		{
		}
	} // end namespace Ifc4
} // end namespace OpenInfraPlatform
