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
#include "include/IfcSizeSelect.h"
#include "include/IfcTextAlignment.h"
#include "include/IfcTextDecoration.h"
#include "include/IfcTextStyleTextModel.h"
#include "include/IfcTextTransformation.h"

namespace OpenInfraPlatform
{
	namespace IfcRoad
	{
		// ENTITY IfcTextStyleTextModel 
		IfcTextStyleTextModel::IfcTextStyleTextModel() { m_entity_enum = IFCTEXTSTYLETEXTMODEL; }
		IfcTextStyleTextModel::IfcTextStyleTextModel( int id ) { m_id = id; m_entity_enum = IFCTEXTSTYLETEXTMODEL; }
		IfcTextStyleTextModel::~IfcTextStyleTextModel() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcTextStyleTextModel::setEntity( shared_ptr<IfcRoadEntity> other_entity )
		{
			shared_ptr<IfcTextStyleTextModel> other = dynamic_pointer_cast<IfcTextStyleTextModel>(other_entity);
			if( !other) { return; }
			m_TextIndent = other->m_TextIndent;
			m_TextAlign = other->m_TextAlign;
			m_TextDecoration = other->m_TextDecoration;
			m_LetterSpacing = other->m_LetterSpacing;
			m_WordSpacing = other->m_WordSpacing;
			m_TextTransform = other->m_TextTransform;
			m_LineHeight = other->m_LineHeight;
		}
		void IfcTextStyleTextModel::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCTEXTSTYLETEXTMODEL" << "(";
			if( m_TextIndent ) { m_TextIndent->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_TextAlign ) { m_TextAlign->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_TextDecoration ) { m_TextDecoration->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LetterSpacing ) { m_LetterSpacing->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_WordSpacing ) { m_WordSpacing->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_TextTransform ) { m_TextTransform->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_LineHeight ) { m_LineHeight->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcTextStyleTextModel::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcTextStyleTextModel::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcRoadEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<7 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcTextStyleTextModel, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcRoadException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>7 ){ std::cout << "Wrong parameter count for entity IfcTextStyleTextModel, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_TextIndent = IfcSizeSelect::readStepData( args[0], map );
			m_TextAlign = IfcTextAlignment::readStepData( args[1] );
			m_TextDecoration = IfcTextDecoration::readStepData( args[2] );
			m_LetterSpacing = IfcSizeSelect::readStepData( args[3], map );
			m_WordSpacing = IfcSizeSelect::readStepData( args[4], map );
			m_TextTransform = IfcTextTransformation::readStepData( args[5] );
			m_LineHeight = IfcSizeSelect::readStepData( args[6], map );
		}
		void IfcTextStyleTextModel::setInverseCounterparts( shared_ptr<IfcRoadEntity> ptr_self_entity )
		{
			IfcPresentationItem::setInverseCounterparts( ptr_self_entity );
		}
		void IfcTextStyleTextModel::unlinkSelf()
		{
			IfcPresentationItem::unlinkSelf();
		}
	} // end namespace IfcRoad
} // end namespace OpenInfraPlatform
