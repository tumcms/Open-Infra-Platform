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
#include "include/IfcIdentifier.h"
#include "include/IfcLabel.h"
#include "include/IfcLayeredItem.h"
#include "include/IfcLogical.h"
#include "include/IfcPresentationLayerWithStyle.h"
#include "include/IfcPresentationStyle.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace Ifc4
	{
		// ENTITY IfcPresentationLayerWithStyle 
		IfcPresentationLayerWithStyle::IfcPresentationLayerWithStyle() { m_entity_enum = IFCPRESENTATIONLAYERWITHSTYLE; }
		IfcPresentationLayerWithStyle::IfcPresentationLayerWithStyle( int id ) { m_id = id; m_entity_enum = IFCPRESENTATIONLAYERWITHSTYLE; }
		IfcPresentationLayerWithStyle::~IfcPresentationLayerWithStyle() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcPresentationLayerWithStyle::setEntity( shared_ptr<Ifc4Entity> other_entity )
		{
			shared_ptr<IfcPresentationLayerWithStyle> other = dynamic_pointer_cast<IfcPresentationLayerWithStyle>(other_entity);
			if( !other) { return; }
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_AssignedItems = other->m_AssignedItems;
			m_Identifier = other->m_Identifier;
			m_LayerOn = other->m_LayerOn;
			m_LayerFrozen = other->m_LayerFrozen;
			m_LayerBlocked = other->m_LayerBlocked;
			m_LayerStyles = other->m_LayerStyles;
		}
		void IfcPresentationLayerWithStyle::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCPRESENTATIONLAYERWITHSTYLE" << "(";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeTypeList( stream, m_AssignedItems, true );
			stream << ",";
			if( m_Identifier ) { m_Identifier->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LayerOn ) { m_LayerOn->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LayerFrozen ) { m_LayerFrozen->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LayerBlocked ) { m_LayerBlocked->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_LayerStyles );
			stream << ");";
		}
		void IfcPresentationLayerWithStyle::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcPresentationLayerWithStyle::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc4Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<8 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcPresentationLayerWithStyle, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc4Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>8 ){ std::cout << "Wrong parameter count for entity IfcPresentationLayerWithStyle, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Name = IfcLabel::readStepData( args[0] );
			m_Description = IfcText::readStepData( args[1] );
			readSelectList( args[2], m_AssignedItems, map );
			m_Identifier = IfcIdentifier::readStepData( args[3] );
			m_LayerOn = IfcLogical::readStepData( args[4] );
			m_LayerFrozen = IfcLogical::readStepData( args[5] );
			m_LayerBlocked = IfcLogical::readStepData( args[6] );
			readEntityReferenceList( args[7], m_LayerStyles, map );
		}
		void IfcPresentationLayerWithStyle::setInverseCounterparts( shared_ptr<Ifc4Entity> ptr_self_entity )
		{
			IfcPresentationLayerAssignment::setInverseCounterparts( ptr_self_entity );
		}
		void IfcPresentationLayerWithStyle::unlinkSelf()
		{
			IfcPresentationLayerAssignment::unlinkSelf();
		}
	} // end namespace Ifc4
} // end namespace OpenInfraPlatform
