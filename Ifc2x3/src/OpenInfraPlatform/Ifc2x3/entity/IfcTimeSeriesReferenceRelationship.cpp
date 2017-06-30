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

#include "model/Ifc2x3Exception.h"
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "Ifc2x3EntityEnums.h"
#include "include/IfcDocumentSelect.h"
#include "include/IfcTimeSeries.h"
#include "include/IfcTimeSeriesReferenceRelationship.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcTimeSeriesReferenceRelationship 
		IfcTimeSeriesReferenceRelationship::IfcTimeSeriesReferenceRelationship() { m_entity_enum = IFCTIMESERIESREFERENCERELATIONSHIP; }
		IfcTimeSeriesReferenceRelationship::IfcTimeSeriesReferenceRelationship( int id ) { m_id = id; m_entity_enum = IFCTIMESERIESREFERENCERELATIONSHIP; }
		IfcTimeSeriesReferenceRelationship::~IfcTimeSeriesReferenceRelationship() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcTimeSeriesReferenceRelationship::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcTimeSeriesReferenceRelationship> other = dynamic_pointer_cast<IfcTimeSeriesReferenceRelationship>(other_entity);
			if( !other) { return; }
			m_ReferencedTimeSeries = other->m_ReferencedTimeSeries;
			m_TimeSeriesReferences = other->m_TimeSeriesReferences;
		}
		void IfcTimeSeriesReferenceRelationship::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCTIMESERIESREFERENCERELATIONSHIP" << "(";
			if( m_ReferencedTimeSeries ) { stream << "#" << m_ReferencedTimeSeries->getId(); } else { stream << "$"; }
			stream << ",";
			writeTypeList( stream, m_TimeSeriesReferences, true );
			stream << ");";
		}
		void IfcTimeSeriesReferenceRelationship::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcTimeSeriesReferenceRelationship::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<2 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcTimeSeriesReferenceRelationship, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>2 ){ std::cout << "Wrong parameter count for entity IfcTimeSeriesReferenceRelationship, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readEntityReference( args[0], m_ReferencedTimeSeries, map );
			readSelectList( args[1], m_TimeSeriesReferences, map );
		}
		void IfcTimeSeriesReferenceRelationship::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			shared_ptr<IfcTimeSeriesReferenceRelationship> ptr_self = dynamic_pointer_cast<IfcTimeSeriesReferenceRelationship>( ptr_self_entity );
			if( !ptr_self ) { throw Ifc2x3Exception( "IfcTimeSeriesReferenceRelationship::setInverseCounterparts: type mismatch" ); }
			if( m_ReferencedTimeSeries )
			{
				m_ReferencedTimeSeries->m_DocumentedBy_inverse.push_back( ptr_self );
			}
		}
		void IfcTimeSeriesReferenceRelationship::unlinkSelf()
		{
			if( m_ReferencedTimeSeries )
			{
				std::vector<weak_ptr<IfcTimeSeriesReferenceRelationship> >& DocumentedBy_inverse = m_ReferencedTimeSeries->m_DocumentedBy_inverse;
				std::vector<weak_ptr<IfcTimeSeriesReferenceRelationship> >::iterator it_DocumentedBy_inverse;
				for( it_DocumentedBy_inverse = DocumentedBy_inverse.begin(); it_DocumentedBy_inverse != DocumentedBy_inverse.end(); ++it_DocumentedBy_inverse)
				{
					shared_ptr<IfcTimeSeriesReferenceRelationship> self_candidate( *it_DocumentedBy_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						DocumentedBy_inverse.erase( it_DocumentedBy_inverse );
						break;
					}
				}
			}
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
