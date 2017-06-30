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
#include "include/IfcLabel.h"
#include "include/IfcSymbolStyle.h"
#include "include/IfcSymbolStyleSelect.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// ENTITY IfcSymbolStyle 
		IfcSymbolStyle::IfcSymbolStyle() { m_entity_enum = IFCSYMBOLSTYLE; }
		IfcSymbolStyle::IfcSymbolStyle( int id ) { m_id = id; m_entity_enum = IFCSYMBOLSTYLE; }
		IfcSymbolStyle::~IfcSymbolStyle() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcSymbolStyle::setEntity( shared_ptr<IfcBridgeEntity> other_entity )
		{
			shared_ptr<IfcSymbolStyle> other = dynamic_pointer_cast<IfcSymbolStyle>(other_entity);
			if( !other) { return; }
			m_Name = other->m_Name;
			m_StyleOfSymbol = other->m_StyleOfSymbol;
		}
		void IfcSymbolStyle::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCSYMBOLSTYLE" << "(";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_StyleOfSymbol ) { m_StyleOfSymbol->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcSymbolStyle::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcSymbolStyle::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcBridgeEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<2 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcSymbolStyle, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcBridgeException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>2 ){ std::cout << "Wrong parameter count for entity IfcSymbolStyle, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Name = IfcLabel::readStepData( args[0] );
			m_StyleOfSymbol = IfcSymbolStyleSelect::readStepData( args[1], map );
		}
		void IfcSymbolStyle::setInverseCounterparts( shared_ptr<IfcBridgeEntity> ptr_self_entity )
		{
			IfcPresentationStyle::setInverseCounterparts( ptr_self_entity );
		}
		void IfcSymbolStyle::unlinkSelf()
		{
			IfcPresentationStyle::unlinkSelf();
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
