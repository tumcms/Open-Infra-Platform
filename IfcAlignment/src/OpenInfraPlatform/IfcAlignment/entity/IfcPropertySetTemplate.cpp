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

#include "OpenInfraPlatform/IfcAlignment/model/IfcAlignmentP6Exception.h"
#include "OpenInfraPlatform/IfcAlignment/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment/writer/WriterUtil.h"
#include "OpenInfraPlatform/IfcAlignment/IfcAlignmentP6EntityEnums.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcIdentifier.h"
#include "include/IfcLabel.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcPropertySetTemplate.h"
#include "include/IfcPropertySetTemplateTypeEnum.h"
#include "include/IfcPropertyTemplate.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelDeclares.h"
#include "include/IfcRelDefinesByTemplate.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment
	{
		// ENTITY IfcPropertySetTemplate 
		IfcPropertySetTemplate::IfcPropertySetTemplate() { m_entity_enum = IFCPROPERTYSETTEMPLATE; }
		IfcPropertySetTemplate::IfcPropertySetTemplate( int id ) { m_id = id; m_entity_enum = IFCPROPERTYSETTEMPLATE; }
		IfcPropertySetTemplate::~IfcPropertySetTemplate() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcPropertySetTemplate::setEntity( shared_ptr<IfcAlignmentP6Entity> other_entity )
		{
			shared_ptr<IfcPropertySetTemplate> other = dynamic_pointer_cast<IfcPropertySetTemplate>(other_entity);
			if( !other) { return; }
			m_GlobalId = other->m_GlobalId;
			m_OwnerHistory = other->m_OwnerHistory;
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_TemplateType = other->m_TemplateType;
			m_ApplicableEntity = other->m_ApplicableEntity;
			m_HasPropertyTemplates = other->m_HasPropertyTemplates;
		}
		void IfcPropertySetTemplate::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCPROPERTYSETTEMPLATE" << "(";
			if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_TemplateType ) { m_TemplateType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ApplicableEntity ) { m_ApplicableEntity->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_HasPropertyTemplates );
			stream << ");";
		}
		void IfcPropertySetTemplate::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcPropertySetTemplate::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignmentP6Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<7 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcPropertySetTemplate, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignmentP6Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>7 ){ std::cout << "Wrong parameter count for entity IfcPropertySetTemplate, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
			readEntityReference( args[1], m_OwnerHistory, map );
			m_Name = IfcLabel::readStepData( args[2] );
			m_Description = IfcText::readStepData( args[3] );
			m_TemplateType = IfcPropertySetTemplateTypeEnum::readStepData( args[4] );
			m_ApplicableEntity = IfcIdentifier::readStepData( args[5] );
			readEntityReferenceList( args[6], m_HasPropertyTemplates, map );
		}
		void IfcPropertySetTemplate::setInverseCounterparts( shared_ptr<IfcAlignmentP6Entity> ptr_self_entity )
		{
			IfcPropertyTemplateDefinition::setInverseCounterparts( ptr_self_entity );
			shared_ptr<IfcPropertySetTemplate> ptr_self = dynamic_pointer_cast<IfcPropertySetTemplate>( ptr_self_entity );
			if( !ptr_self ) { throw IfcAlignmentP6Exception( "IfcPropertySetTemplate::setInverseCounterparts: type mismatch" ); }
			for( int i=0; i<m_HasPropertyTemplates.size(); ++i )
			{
				if( m_HasPropertyTemplates[i] )
				{
					m_HasPropertyTemplates[i]->m_PartOfPsetTemplate_inverse.push_back( ptr_self );
				}
			}
		}
		void IfcPropertySetTemplate::unlinkSelf()
		{
			IfcPropertyTemplateDefinition::unlinkSelf();
			for( int i=0; i<m_HasPropertyTemplates.size(); ++i )
			{
				if( m_HasPropertyTemplates[i] )
				{
					std::vector<weak_ptr<IfcPropertySetTemplate> >& PartOfPsetTemplate_inverse = m_HasPropertyTemplates[i]->m_PartOfPsetTemplate_inverse;
					std::vector<weak_ptr<IfcPropertySetTemplate> >::iterator it_PartOfPsetTemplate_inverse;
					for( it_PartOfPsetTemplate_inverse = PartOfPsetTemplate_inverse.begin(); it_PartOfPsetTemplate_inverse != PartOfPsetTemplate_inverse.end(); ++it_PartOfPsetTemplate_inverse)
					{
						shared_ptr<IfcPropertySetTemplate> self_candidate( *it_PartOfPsetTemplate_inverse );
						if( self_candidate->getId() == this->getId() )
						{
							PartOfPsetTemplate_inverse.erase( it_PartOfPsetTemplate_inverse );
							break;
						}
					}
				}
			}
		}
	} // end namespace IfcAlignment
} // end namespace OpenInfraPlatform
