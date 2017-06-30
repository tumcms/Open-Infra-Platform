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
#include "include/IfcFontStyle.h"
#include "include/IfcFontVariant.h"
#include "include/IfcFontWeight.h"
#include "include/IfcLabel.h"
#include "include/IfcSizeSelect.h"
#include "include/IfcTextFontName.h"
#include "include/IfcTextStyleFontModel.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		// ENTITY IfcTextStyleFontModel 
		IfcTextStyleFontModel::IfcTextStyleFontModel() { m_entity_enum = IFCTEXTSTYLEFONTMODEL; }
		IfcTextStyleFontModel::IfcTextStyleFontModel( int id ) { m_id = id; m_entity_enum = IFCTEXTSTYLEFONTMODEL; }
		IfcTextStyleFontModel::~IfcTextStyleFontModel() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcTextStyleFontModel::setEntity( shared_ptr<IfcTunnelEntity> other_entity )
		{
			shared_ptr<IfcTextStyleFontModel> other = dynamic_pointer_cast<IfcTextStyleFontModel>(other_entity);
			if( !other) { return; }
			m_Name = other->m_Name;
			m_FontFamily = other->m_FontFamily;
			m_FontStyle = other->m_FontStyle;
			m_FontVariant = other->m_FontVariant;
			m_FontWeight = other->m_FontWeight;
			m_FontSize = other->m_FontSize;
		}
		void IfcTextStyleFontModel::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCTEXTSTYLEFONTMODEL" << "(";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeTypeList( stream, m_FontFamily );
			stream << ",";
			if( m_FontStyle ) { m_FontStyle->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_FontVariant ) { m_FontVariant->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_FontWeight ) { m_FontWeight->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_FontSize ) { m_FontSize->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcTextStyleFontModel::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcTextStyleFontModel::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcTunnelEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<6 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcTextStyleFontModel, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcTunnelException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>6 ){ std::cout << "Wrong parameter count for entity IfcTextStyleFontModel, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Name = IfcLabel::readStepData( args[0] );
			readTypeList( args[1], m_FontFamily );
			m_FontStyle = IfcFontStyle::readStepData( args[2] );
			m_FontVariant = IfcFontVariant::readStepData( args[3] );
			m_FontWeight = IfcFontWeight::readStepData( args[4] );
			m_FontSize = IfcSizeSelect::readStepData( args[5], map );
		}
		void IfcTextStyleFontModel::setInverseCounterparts( shared_ptr<IfcTunnelEntity> ptr_self_entity )
		{
			IfcPreDefinedTextFont::setInverseCounterparts( ptr_self_entity );
		}
		void IfcTextStyleFontModel::unlinkSelf()
		{
			IfcPreDefinedTextFont::unlinkSelf();
		}
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform
