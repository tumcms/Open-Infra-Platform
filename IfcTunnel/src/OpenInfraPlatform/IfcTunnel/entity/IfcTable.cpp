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

#include "model/IfcTunnelException.h"
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "IfcTunnelEntityEnums.h"
#include "include/IfcLabel.h"
#include "include/IfcTable.h"
#include "include/IfcTableColumn.h"
#include "include/IfcTableRow.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		// ENTITY IfcTable 
		IfcTable::IfcTable() { m_entity_enum = IFCTABLE; }
		IfcTable::IfcTable( int id ) { m_id = id; m_entity_enum = IFCTABLE; }
		IfcTable::~IfcTable() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcTable::setEntity( shared_ptr<IfcTunnelEntity> other_entity )
		{
			shared_ptr<IfcTable> other = dynamic_pointer_cast<IfcTable>(other_entity);
			if( !other) { return; }
			m_Name = other->m_Name;
			m_Rows = other->m_Rows;
			m_Columns = other->m_Columns;
		}
		void IfcTable::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCTABLE" << "(";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_Rows );
			stream << ",";
			writeEntityList( stream, m_Columns );
			stream << ");";
		}
		void IfcTable::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcTable::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcTunnelEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<3 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcTable, expecting 3, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcTunnelException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>3 ){ std::cout << "Wrong parameter count for entity IfcTable, expecting 3, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Name = IfcLabel::readStepData( args[0] );
			readEntityReferenceList( args[1], m_Rows, map );
			readEntityReferenceList( args[2], m_Columns, map );
		}
		void IfcTable::setInverseCounterparts( shared_ptr<IfcTunnelEntity> ptr_self_entity )
		{
			shared_ptr<IfcTable> ptr_self = dynamic_pointer_cast<IfcTable>( ptr_self_entity );
			if( !ptr_self ) { throw IfcTunnelException( "IfcTable::setInverseCounterparts: type mismatch" ); }
			for( int i=0; i<m_Rows.size(); ++i )
			{
				if( m_Rows[i] )
				{
					m_Rows[i]->m_OfTable_inverse = ptr_self;
				}
			}
		}
		void IfcTable::unlinkSelf()
		{
			for( int i=0; i<m_Rows.size(); ++i )
			{
				if( m_Rows[i] )
				{
					shared_ptr<IfcTable> self_candidate( m_Rows[i]->m_OfTable_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						weak_ptr<IfcTable>& self_candidate_weak = m_Rows[i]->m_OfTable_inverse;
						self_candidate_weak.reset();
					}
				}
			}
		}
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform
