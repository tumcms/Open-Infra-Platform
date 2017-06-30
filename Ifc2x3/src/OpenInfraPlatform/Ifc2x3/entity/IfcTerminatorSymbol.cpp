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
#include "include/IfcAnnotationCurveOccurrence.h"
#include "include/IfcDimensionCurve.h"
#include "include/IfcLabel.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcPresentationStyleAssignment.h"
#include "include/IfcRepresentationItem.h"
#include "include/IfcStyledItem.h"
#include "include/IfcTerminatorSymbol.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcTerminatorSymbol 
		IfcTerminatorSymbol::IfcTerminatorSymbol() { m_entity_enum = IFCTERMINATORSYMBOL; }
		IfcTerminatorSymbol::IfcTerminatorSymbol( int id ) { m_id = id; m_entity_enum = IFCTERMINATORSYMBOL; }
		IfcTerminatorSymbol::~IfcTerminatorSymbol() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcTerminatorSymbol::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcTerminatorSymbol> other = dynamic_pointer_cast<IfcTerminatorSymbol>(other_entity);
			if( !other) { return; }
			m_Item = other->m_Item;
			m_Styles = other->m_Styles;
			m_Name = other->m_Name;
			m_AnnotatedCurve = other->m_AnnotatedCurve;
		}
		void IfcTerminatorSymbol::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCTERMINATORSYMBOL" << "(";
			if( m_Item ) { stream << "#" << m_Item->getId(); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_Styles );
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_AnnotatedCurve ) { stream << "#" << m_AnnotatedCurve->getId(); } else { stream << "$"; }
			stream << ");";
		}
		void IfcTerminatorSymbol::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcTerminatorSymbol::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<4 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcTerminatorSymbol, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>4 ){ std::cout << "Wrong parameter count for entity IfcTerminatorSymbol, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readEntityReference( args[0], m_Item, map );
			readEntityReferenceList( args[1], m_Styles, map );
			m_Name = IfcLabel::readStepData( args[2] );
			readEntityReference( args[3], m_AnnotatedCurve, map );
		}
		void IfcTerminatorSymbol::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcAnnotationSymbolOccurrence::setInverseCounterparts( ptr_self_entity );
			shared_ptr<IfcTerminatorSymbol> ptr_self = dynamic_pointer_cast<IfcTerminatorSymbol>( ptr_self_entity );
			if( !ptr_self ) { throw Ifc2x3Exception( "IfcTerminatorSymbol::setInverseCounterparts: type mismatch" ); }
			shared_ptr<IfcDimensionCurve>  AnnotatedCurve_IfcDimensionCurve = dynamic_pointer_cast<IfcDimensionCurve>( m_AnnotatedCurve );
			if( AnnotatedCurve_IfcDimensionCurve )
			{
				AnnotatedCurve_IfcDimensionCurve->m_AnnotatedBySymbols_inverse.push_back( ptr_self );
			}
		}
		void IfcTerminatorSymbol::unlinkSelf()
		{
			IfcAnnotationSymbolOccurrence::unlinkSelf();
			shared_ptr<IfcDimensionCurve>  AnnotatedCurve_IfcDimensionCurve = dynamic_pointer_cast<IfcDimensionCurve>( m_AnnotatedCurve );
			if( AnnotatedCurve_IfcDimensionCurve )
			{
				std::vector<weak_ptr<IfcTerminatorSymbol> >& AnnotatedBySymbols_inverse = AnnotatedCurve_IfcDimensionCurve->m_AnnotatedBySymbols_inverse;
				std::vector<weak_ptr<IfcTerminatorSymbol> >::iterator it_AnnotatedBySymbols_inverse;
				for( it_AnnotatedBySymbols_inverse = AnnotatedBySymbols_inverse.begin(); it_AnnotatedBySymbols_inverse != AnnotatedBySymbols_inverse.end(); ++it_AnnotatedBySymbols_inverse)
				{
					shared_ptr<IfcTerminatorSymbol> self_candidate( *it_AnnotatedBySymbols_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						AnnotatedBySymbols_inverse.erase( it_AnnotatedBySymbols_inverse );
						break;
					}
				}
			}
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
