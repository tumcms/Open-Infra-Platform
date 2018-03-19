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
#include "IfcSimplePropertyTemplate.h"
#include "IfcGloballyUniqueId.h"
#include "IfcOwnerHistory.h"
#include "IfcLabel.h"
#include "IfcText.h"
#include "IfcSimplePropertyTemplateTypeEnum.h"
#include "IfcLabel.h"
#include "IfcLabel.h"
#include "IfcPropertyEnumeration.h"
#include "IfcUnit.h"
#include "IfcUnit.h"
#include "IfcLabel.h"
#include "IfcStateEnum.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcSimplePropertyTemplate
			IfcSimplePropertyTemplate::IfcSimplePropertyTemplate() { m_entity_enum = IFCSIMPLEPROPERTYTEMPLATE;}
			IfcSimplePropertyTemplate::IfcSimplePropertyTemplate( int id ) { m_id = id; m_entity_enum = IFCSIMPLEPROPERTYTEMPLATE;}
			IfcSimplePropertyTemplate::~IfcSimplePropertyTemplate() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcSimplePropertyTemplate::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcSimplePropertyTemplate> other = std::dynamic_pointer_cast<IfcSimplePropertyTemplate>(other_entity);
				if( !other) { return; }
				m_GlobalId = other->m_GlobalId;
				m_OwnerHistory = other->m_OwnerHistory;
				m_Name = other->m_Name;
				m_Description = other->m_Description;
				m_TemplateType = other->m_TemplateType;
				m_PrimaryMeasureType = other->m_PrimaryMeasureType;
				m_SecondaryMeasureType = other->m_SecondaryMeasureType;
				m_Enumerators = other->m_Enumerators;
				m_PrimaryUnit = other->m_PrimaryUnit;
				m_SecondaryUnit = other->m_SecondaryUnit;
				m_Expression = other->m_Expression;
				m_AccessState = other->m_AccessState;
			}
			void IfcSimplePropertyTemplate::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCSIMPLEPROPERTYTEMPLATE" << "(";
				if( m_GlobalId) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_OwnerHistory) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Name) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Description) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_TemplateType) { m_TemplateType->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_PrimaryMeasureType) { m_PrimaryMeasureType->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_SecondaryMeasureType) { m_SecondaryMeasureType->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Enumerators) { stream << "#" << m_Enumerators->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_PrimaryUnit) { m_PrimaryUnit->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_SecondaryUnit) { m_SecondaryUnit->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Expression) { m_Expression->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_AccessState) { m_AccessState->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcSimplePropertyTemplate::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcSimplePropertyTemplate::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<12 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcSimplePropertyTemplate, expecting 12, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<12 ){ std::cout << "Wrong parameter count for entity IfcSimplePropertyTemplate, expecting 12, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
				readEntityReference( args[1], m_OwnerHistory, map);
				m_Name = IfcLabel::readStepData( args[2] );
				m_Description = IfcText::readStepData( args[3] );
				m_TemplateType = IfcSimplePropertyTemplateTypeEnum::readStepData( args[4] );
				m_PrimaryMeasureType = IfcLabel::readStepData( args[5] );
				m_SecondaryMeasureType = IfcLabel::readStepData( args[6] );
				readEntityReference( args[7], m_Enumerators, map);
				m_PrimaryUnit = IfcUnit::readStepData( args[8], map );
				m_SecondaryUnit = IfcUnit::readStepData( args[9], map );
				m_Expression = IfcLabel::readStepData( args[10] );
				m_AccessState = IfcStateEnum::readStepData( args[11] );
			}
			void IfcSimplePropertyTemplate::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcPropertyTemplate::setInverseCounterparts(ptr_self_entity);
			}
			void IfcSimplePropertyTemplate::unlinkSelf()
			{
				IfcPropertyTemplate::unlinkSelf();
			}
	}
}
