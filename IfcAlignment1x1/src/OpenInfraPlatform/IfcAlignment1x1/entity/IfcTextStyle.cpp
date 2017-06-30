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
#include "OpenInfraPlatform/IfcAlignment1x1/model/Exception.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1EntityEnums.h"
#include "IfcTextStyle.h"
#include "IfcLabel.h"
#include "IfcTextStyleForDefinedFont.h"
#include "IfcTextStyleTextModel.h"
#include "IfcTextFontSelect.h"
#include "IfcBoolean.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcTextStyle
			IfcTextStyle::IfcTextStyle() { m_entity_enum = IFCTEXTSTYLE;}
			IfcTextStyle::IfcTextStyle( int id ) { m_id = id; m_entity_enum = IFCTEXTSTYLE;}
			IfcTextStyle::~IfcTextStyle() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcTextStyle::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcTextStyle> other = std::dynamic_pointer_cast<IfcTextStyle>(other_entity);
				if( !other) { return; }
				m_Name = other->m_Name;
				m_TextCharacterAppearance = other->m_TextCharacterAppearance;
				m_TextStyle = other->m_TextStyle;
				m_TextFontStyle = other->m_TextFontStyle;
				m_ModelOrDraughting = other->m_ModelOrDraughting;
			}
			void IfcTextStyle::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCTEXTSTYLE" << "(";
				if( m_Name) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_TextCharacterAppearance) { stream << "#" << m_TextCharacterAppearance->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_TextStyle) { stream << "#" << m_TextStyle->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_TextFontStyle) { m_TextFontStyle->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_ModelOrDraughting) { m_ModelOrDraughting->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcTextStyle::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcTextStyle::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<5 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcTextStyle, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<5 ){ std::cout << "Wrong parameter count for entity IfcTextStyle, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_Name = IfcLabel::readStepData( args[0] );
				readEntityReference( args[1], m_TextCharacterAppearance, map);
				readEntityReference( args[2], m_TextStyle, map);
				m_TextFontStyle = IfcTextFontSelect::readStepData( args[3], map );
				m_ModelOrDraughting = IfcBoolean::readStepData( args[4] );
			}
			void IfcTextStyle::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcPresentationStyle::setInverseCounterparts(ptr_self_entity);
			}
			void IfcTextStyle::unlinkSelf()
			{
				IfcPresentationStyle::unlinkSelf();
			}
	}
}
