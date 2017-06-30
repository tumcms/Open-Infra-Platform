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
#include "include/IfcAnnotationSurface.h"
#include "include/IfcGeometricRepresentationItem.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcStyledItem.h"
#include "include/IfcTextureCoordinate.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcAnnotationSurface 
		IfcAnnotationSurface::IfcAnnotationSurface() { m_entity_enum = IFCANNOTATIONSURFACE; }
		IfcAnnotationSurface::IfcAnnotationSurface( int id ) { m_id = id; m_entity_enum = IFCANNOTATIONSURFACE; }
		IfcAnnotationSurface::~IfcAnnotationSurface() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcAnnotationSurface::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcAnnotationSurface> other = dynamic_pointer_cast<IfcAnnotationSurface>(other_entity);
			if( !other) { return; }
			m_Item = other->m_Item;
			m_TextureCoordinates = other->m_TextureCoordinates;
		}
		void IfcAnnotationSurface::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCANNOTATIONSURFACE" << "(";
			if( m_Item ) { stream << "#" << m_Item->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_TextureCoordinates ) { stream << "#" << m_TextureCoordinates->getId(); } else { stream << "$"; }
			stream << ");";
		}
		void IfcAnnotationSurface::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcAnnotationSurface::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<2 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcAnnotationSurface, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>2 ){ std::cout << "Wrong parameter count for entity IfcAnnotationSurface, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readEntityReference( args[0], m_Item, map );
			readEntityReference( args[1], m_TextureCoordinates, map );
		}
		void IfcAnnotationSurface::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcGeometricRepresentationItem::setInverseCounterparts( ptr_self_entity );
			shared_ptr<IfcAnnotationSurface> ptr_self = dynamic_pointer_cast<IfcAnnotationSurface>( ptr_self_entity );
			if( !ptr_self ) { throw Ifc2x3Exception( "IfcAnnotationSurface::setInverseCounterparts: type mismatch" ); }
			if( m_TextureCoordinates )
			{
				m_TextureCoordinates->m_AnnotatedSurface_inverse.push_back( ptr_self );
			}
		}
		void IfcAnnotationSurface::unlinkSelf()
		{
			IfcGeometricRepresentationItem::unlinkSelf();
			if( m_TextureCoordinates )
			{
				std::vector<weak_ptr<IfcAnnotationSurface> >& AnnotatedSurface_inverse = m_TextureCoordinates->m_AnnotatedSurface_inverse;
				std::vector<weak_ptr<IfcAnnotationSurface> >::iterator it_AnnotatedSurface_inverse;
				for( it_AnnotatedSurface_inverse = AnnotatedSurface_inverse.begin(); it_AnnotatedSurface_inverse != AnnotatedSurface_inverse.end(); ++it_AnnotatedSurface_inverse)
				{
					shared_ptr<IfcAnnotationSurface> self_candidate( *it_AnnotatedSurface_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						AnnotatedSurface_inverse.erase( it_AnnotatedSurface_inverse );
						break;
					}
				}
			}
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
