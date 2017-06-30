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
#include "IfcInventory.h"
#include "IfcGloballyUniqueId.h"
#include "IfcOwnerHistory.h"
#include "IfcLabel.h"
#include "IfcText.h"
#include "IfcLabel.h"
#include "IfcInventoryTypeEnum.h"
#include "IfcActorSelect.h"
#include "IfcPerson.h"
#include "IfcDate.h"
#include "IfcCostValue.h"
#include "IfcCostValue.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcInventory
			IfcInventory::IfcInventory() { m_entity_enum = IFCINVENTORY;}
			IfcInventory::IfcInventory( int id ) { m_id = id; m_entity_enum = IFCINVENTORY;}
			IfcInventory::~IfcInventory() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcInventory::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcInventory> other = std::dynamic_pointer_cast<IfcInventory>(other_entity);
				if( !other) { return; }
				m_GlobalId = other->m_GlobalId;
				m_OwnerHistory = other->m_OwnerHistory;
				m_Name = other->m_Name;
				m_Description = other->m_Description;
				m_ObjectType = other->m_ObjectType;
				m_PredefinedType = other->m_PredefinedType;
				m_Jurisdiction = other->m_Jurisdiction;
				m_ResponsiblePersons = other->m_ResponsiblePersons;
				m_LastUpdateDate = other->m_LastUpdateDate;
				m_CurrentValue = other->m_CurrentValue;
				m_OriginalValue = other->m_OriginalValue;
			}
			void IfcInventory::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCINVENTORY" << "(";
				if( m_GlobalId) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_OwnerHistory) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Name) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Description) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_ObjectType) { m_ObjectType->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_PredefinedType) { m_PredefinedType->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Jurisdiction) { m_Jurisdiction->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				writeEntityList( stream, m_ResponsiblePersons );
				stream << ",";
				if( m_LastUpdateDate) { m_LastUpdateDate->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_CurrentValue) { stream << "#" << m_CurrentValue->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_OriginalValue) { stream << "#" << m_OriginalValue->getId(); } else { stream << "$"; }
				stream << ");";
			}
			void IfcInventory::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcInventory::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<11 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcInventory, expecting 11, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<11 ){ std::cout << "Wrong parameter count for entity IfcInventory, expecting 11, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
				readEntityReference( args[1], m_OwnerHistory, map);
				m_Name = IfcLabel::readStepData( args[2] );
				m_Description = IfcText::readStepData( args[3] );
				m_ObjectType = IfcLabel::readStepData( args[4] );
				m_PredefinedType = IfcInventoryTypeEnum::readStepData( args[5] );
				m_Jurisdiction = IfcActorSelect::readStepData( args[6], map );
				readEntityReferenceList( args[7], m_ResponsiblePersons , map);
				m_LastUpdateDate = IfcDate::readStepData( args[8] );
				readEntityReference( args[9], m_CurrentValue, map);
				readEntityReference( args[10], m_OriginalValue, map);
			}
			void IfcInventory::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcGroup::setInverseCounterparts(ptr_self_entity);
			}
			void IfcInventory::unlinkSelf()
			{
				IfcGroup::unlinkSelf();
			}
	}
}
