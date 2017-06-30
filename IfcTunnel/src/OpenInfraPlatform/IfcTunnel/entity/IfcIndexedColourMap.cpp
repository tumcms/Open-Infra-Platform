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
#include "include/IfcColourRgbList.h"
#include "include/IfcIndexedColourMap.h"
#include "include/IfcSurfaceStyleShading.h"
#include "include/IfcTessellatedFaceSet.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		// ENTITY IfcIndexedColourMap 
		IfcIndexedColourMap::IfcIndexedColourMap() { m_entity_enum = IFCINDEXEDCOLOURMAP; }
		IfcIndexedColourMap::IfcIndexedColourMap( int id ) { m_id = id; m_entity_enum = IFCINDEXEDCOLOURMAP; }
		IfcIndexedColourMap::~IfcIndexedColourMap() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcIndexedColourMap::setEntity( shared_ptr<IfcTunnelEntity> other_entity )
		{
			shared_ptr<IfcIndexedColourMap> other = dynamic_pointer_cast<IfcIndexedColourMap>(other_entity);
			if( !other) { return; }
			m_MappedTo = other->m_MappedTo;
			m_Overrides = other->m_Overrides;
			m_Colours = other->m_Colours;
			m_ColourIndex = other->m_ColourIndex;
		}
		void IfcIndexedColourMap::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCINDEXEDCOLOURMAP" << "(";
			if( m_MappedTo ) { stream << "#" << m_MappedTo->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Overrides ) { stream << "#" << m_Overrides->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Colours ) { stream << "#" << m_Colours->getId(); } else { stream << "$"; }
			stream << ",";
			writeIntList( stream, m_ColourIndex );
			stream << ");";
		}
		void IfcIndexedColourMap::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcIndexedColourMap::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcTunnelEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<4 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcIndexedColourMap, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcTunnelException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>4 ){ std::cout << "Wrong parameter count for entity IfcIndexedColourMap, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readEntityReference( args[0], m_MappedTo, map );
			readEntityReference( args[1], m_Overrides, map );
			readEntityReference( args[2], m_Colours, map );
			readIntList(  args[3], m_ColourIndex );
		}
		void IfcIndexedColourMap::setInverseCounterparts( shared_ptr<IfcTunnelEntity> ptr_self_entity )
		{
			IfcPresentationItem::setInverseCounterparts( ptr_self_entity );
			shared_ptr<IfcIndexedColourMap> ptr_self = dynamic_pointer_cast<IfcIndexedColourMap>( ptr_self_entity );
			if( !ptr_self ) { throw IfcTunnelException( "IfcIndexedColourMap::setInverseCounterparts: type mismatch" ); }
			if( m_MappedTo )
			{
				m_MappedTo->m_HasColours_inverse.push_back( ptr_self );
			}
		}
		void IfcIndexedColourMap::unlinkSelf()
		{
			IfcPresentationItem::unlinkSelf();
			if( m_MappedTo )
			{
				std::vector<weak_ptr<IfcIndexedColourMap> >& HasColours_inverse = m_MappedTo->m_HasColours_inverse;
				std::vector<weak_ptr<IfcIndexedColourMap> >::iterator it_HasColours_inverse;
				for( it_HasColours_inverse = HasColours_inverse.begin(); it_HasColours_inverse != HasColours_inverse.end(); ++it_HasColours_inverse)
				{
					shared_ptr<IfcIndexedColourMap> self_candidate( *it_HasColours_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						HasColours_inverse.erase( it_HasColours_inverse );
						break;
					}
				}
			}
		}
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform
