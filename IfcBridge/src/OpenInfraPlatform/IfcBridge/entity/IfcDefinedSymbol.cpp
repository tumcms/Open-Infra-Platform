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

#include "model/IfcBridgeException.h"
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "IfcBridgeEntityEnums.h"
#include "include/IfcCartesianTransformationOperator2D.h"
#include "include/IfcDefinedSymbol.h"
#include "include/IfcDefinedSymbolSelect.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcStyledItem.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// ENTITY IfcDefinedSymbol 
		IfcDefinedSymbol::IfcDefinedSymbol() { m_entity_enum = IFCDEFINEDSYMBOL; }
		IfcDefinedSymbol::IfcDefinedSymbol( int id ) { m_id = id; m_entity_enum = IFCDEFINEDSYMBOL; }
		IfcDefinedSymbol::~IfcDefinedSymbol() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcDefinedSymbol::setEntity( shared_ptr<IfcBridgeEntity> other_entity )
		{
			shared_ptr<IfcDefinedSymbol> other = dynamic_pointer_cast<IfcDefinedSymbol>(other_entity);
			if( !other) { return; }
			m_Definition = other->m_Definition;
			m_Target = other->m_Target;
		}
		void IfcDefinedSymbol::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCDEFINEDSYMBOL" << "(";
			if( m_Definition ) { m_Definition->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_Target ) { stream << "#" << m_Target->getId(); } else { stream << "$"; }
			stream << ");";
		}
		void IfcDefinedSymbol::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcDefinedSymbol::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcBridgeEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<2 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcDefinedSymbol, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcBridgeException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>2 ){ std::cout << "Wrong parameter count for entity IfcDefinedSymbol, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Definition = IfcDefinedSymbolSelect::readStepData( args[0], map );
			readEntityReference( args[1], m_Target, map );
		}
		void IfcDefinedSymbol::setInverseCounterparts( shared_ptr<IfcBridgeEntity> ptr_self_entity )
		{
			IfcGeometricRepresentationItem::setInverseCounterparts( ptr_self_entity );
		}
		void IfcDefinedSymbol::unlinkSelf()
		{
			IfcGeometricRepresentationItem::unlinkSelf();
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
