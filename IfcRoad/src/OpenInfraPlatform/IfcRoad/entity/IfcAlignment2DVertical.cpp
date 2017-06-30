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

#include "OpenInfraPlatform/IfcRoad/model/IfcRoadException.h"
#include "OpenInfraPlatform/IfcRoad/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcRoad/writer/WriterUtil.h"
#include "OpenInfraPlatform/IfcRoad/IfcRoadEntityEnums.h"
#include "include/IfcAlignment.h"
#include "include/IfcAlignment2DVertical.h"
#include "include/IfcAlignment2DVerticalSegment.h"

namespace OpenInfraPlatform
{
	namespace IfcRoad
	{
		// ENTITY IfcAlignment2DVertical 
		IfcAlignment2DVertical::IfcAlignment2DVertical() { m_entity_enum = IFCALIGNMENT2DVERTICAL; }
		IfcAlignment2DVertical::IfcAlignment2DVertical( int id ) { m_id = id; m_entity_enum = IFCALIGNMENT2DVERTICAL; }
		IfcAlignment2DVertical::~IfcAlignment2DVertical() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcAlignment2DVertical::setEntity( shared_ptr<IfcRoadEntity> other_entity )
		{
			shared_ptr<IfcAlignment2DVertical> other = dynamic_pointer_cast<IfcAlignment2DVertical>(other_entity);
			if( !other) { return; }
			m_Segments = other->m_Segments;
		}
		void IfcAlignment2DVertical::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCALIGNMENT2DVERTICAL" << "(";
			writeEntityList( stream, m_Segments );
			stream << ");";
		}
		void IfcAlignment2DVertical::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcAlignment2DVertical::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcRoadEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<1 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcAlignment2DVertical, expecting 1, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcRoadException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>1 ){ std::cout << "Wrong parameter count for entity IfcAlignment2DVertical, expecting 1, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readEntityReferenceList( args[0], m_Segments, map );
		}
		void IfcAlignment2DVertical::setInverseCounterparts( shared_ptr<IfcRoadEntity> ptr_self_entity )
		{
			shared_ptr<IfcAlignment2DVertical> ptr_self = dynamic_pointer_cast<IfcAlignment2DVertical>( ptr_self_entity );
			if( !ptr_self ) { throw IfcRoadException( "IfcAlignment2DVertical::setInverseCounterparts: type mismatch" ); }
			for( int i=0; i<m_Segments.size(); ++i )
			{
				if( m_Segments[i] )
				{
					m_Segments[i]->m_ToVertical_inverse.push_back( ptr_self );
				}
			}
		}
		void IfcAlignment2DVertical::unlinkSelf()
		{
			for( int i=0; i<m_Segments.size(); ++i )
			{
				if( m_Segments[i] )
				{
					std::vector<weak_ptr<IfcAlignment2DVertical> >& ToVertical_inverse = m_Segments[i]->m_ToVertical_inverse;
					std::vector<weak_ptr<IfcAlignment2DVertical> >::iterator it_ToVertical_inverse;
					for( it_ToVertical_inverse = ToVertical_inverse.begin(); it_ToVertical_inverse != ToVertical_inverse.end(); ++it_ToVertical_inverse)
					{
						shared_ptr<IfcAlignment2DVertical> self_candidate( *it_ToVertical_inverse );
						if( self_candidate->getId() == this->getId() )
						{
							ToVertical_inverse.erase( it_ToVertical_inverse );
							break;
						}
					}
				}
			}
		}
	} // end namespace IfcRoad
} // end namespace OpenInfraPlatform
