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

#include "OpenInfraPlatform/IfcAlignment/model/IfcAlignmentP6Exception.h"
#include "OpenInfraPlatform/IfcAlignment/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment/writer/WriterUtil.h"
#include "OpenInfraPlatform/IfcAlignment/IfcAlignmentP6EntityEnums.h"
#include "include/IfcAlignment.h"
#include "include/IfcAlignment2DHorizontal.h"
#include "include/IfcAlignment2DHorizontalSegment.h"
#include "include/IfcLengthMeasure.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment
	{
		// ENTITY IfcAlignment2DHorizontal 
		IfcAlignment2DHorizontal::IfcAlignment2DHorizontal() { m_entity_enum = IFCALIGNMENT2DHORIZONTAL; }
		IfcAlignment2DHorizontal::IfcAlignment2DHorizontal( int id ) { m_id = id; m_entity_enum = IFCALIGNMENT2DHORIZONTAL; }
		IfcAlignment2DHorizontal::~IfcAlignment2DHorizontal() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcAlignment2DHorizontal::setEntity( shared_ptr<IfcAlignmentP6Entity> other_entity )
		{
			shared_ptr<IfcAlignment2DHorizontal> other = dynamic_pointer_cast<IfcAlignment2DHorizontal>(other_entity);
			if( !other) { return; }
			m_StartDistAlong = other->m_StartDistAlong;
			m_Segments = other->m_Segments;
		}
		void IfcAlignment2DHorizontal::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCALIGNMENT2DHORIZONTAL" << "(";
			if( m_StartDistAlong ) { m_StartDistAlong->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_Segments );
			stream << ");";
		}
		void IfcAlignment2DHorizontal::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcAlignment2DHorizontal::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignmentP6Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<2 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcAlignment2DHorizontal, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignmentP6Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>2 ){ std::cout << "Wrong parameter count for entity IfcAlignment2DHorizontal, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_StartDistAlong = IfcLengthMeasure::readStepData( args[0] );
			readEntityReferenceList( args[1], m_Segments, map );
		}
		void IfcAlignment2DHorizontal::setInverseCounterparts( shared_ptr<IfcAlignmentP6Entity> ptr_self_entity )
		{
			shared_ptr<IfcAlignment2DHorizontal> ptr_self = dynamic_pointer_cast<IfcAlignment2DHorizontal>( ptr_self_entity );
			if( !ptr_self ) { throw IfcAlignmentP6Exception( "IfcAlignment2DHorizontal::setInverseCounterparts: type mismatch" ); }
			for( int i=0; i<m_Segments.size(); ++i )
			{
				if( m_Segments[i] )
				{
					m_Segments[i]->m_ToHorizontal_inverse.push_back( ptr_self );
				}
			}
		}
		void IfcAlignment2DHorizontal::unlinkSelf()
		{
			for( int i=0; i<m_Segments.size(); ++i )
			{
				if( m_Segments[i] )
				{
					std::vector<weak_ptr<IfcAlignment2DHorizontal> >& ToHorizontal_inverse = m_Segments[i]->m_ToHorizontal_inverse;
					std::vector<weak_ptr<IfcAlignment2DHorizontal> >::iterator it_ToHorizontal_inverse;
					for( it_ToHorizontal_inverse = ToHorizontal_inverse.begin(); it_ToHorizontal_inverse != ToHorizontal_inverse.end(); ++it_ToHorizontal_inverse)
					{
						shared_ptr<IfcAlignment2DHorizontal> self_candidate( *it_ToHorizontal_inverse );
						if( self_candidate->getId() == this->getId() )
						{
							ToHorizontal_inverse.erase( it_ToHorizontal_inverse );
							break;
						}
					}
				}
			}
		}
	} // end namespace IfcAlignment
} // end namespace OpenInfraPlatform
