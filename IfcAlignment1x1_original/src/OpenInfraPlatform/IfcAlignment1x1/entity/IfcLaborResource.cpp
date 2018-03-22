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
#include "IfcLaborResource.h"
#include "IfcGloballyUniqueId.h"
#include "IfcOwnerHistory.h"
#include "IfcLabel.h"
#include "IfcText.h"
#include "IfcLabel.h"
#include "IfcIdentifier.h"
#include "IfcText.h"
#include "IfcResourceTime.h"
#include "IfcAppliedValue.h"
#include "IfcPhysicalQuantity.h"
#include "IfcLaborResourceTypeEnum.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcLaborResource
			IfcLaborResource::IfcLaborResource() { m_entity_enum = IFCLABORRESOURCE;}
			IfcLaborResource::IfcLaborResource( int id ) { m_id = id; m_entity_enum = IFCLABORRESOURCE;}
			IfcLaborResource::~IfcLaborResource() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcLaborResource::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcLaborResource> other = std::dynamic_pointer_cast<IfcLaborResource>(other_entity);
				if( !other) { return; }
				m_GlobalId = other->m_GlobalId;
				m_OwnerHistory = other->m_OwnerHistory;
				m_Name = other->m_Name;
				m_Description = other->m_Description;
				m_ObjectType = other->m_ObjectType;
				m_Identification = other->m_Identification;
				m_LongDescription = other->m_LongDescription;
				m_Usage = other->m_Usage;
				m_BaseCosts = other->m_BaseCosts;
				m_BaseQuantity = other->m_BaseQuantity;
				m_PredefinedType = other->m_PredefinedType;
			}
			void IfcLaborResource::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCLABORRESOURCE" << "(";
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
				if( m_Identification) { m_Identification->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_LongDescription) { m_LongDescription->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Usage) { stream << "#" << m_Usage->getId(); } else { stream << "$"; }
				stream << ",";
				writeEntityList( stream, m_BaseCosts );
				stream << ",";
				if( m_BaseQuantity) { stream << "#" << m_BaseQuantity->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_PredefinedType) { m_PredefinedType->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcLaborResource::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcLaborResource::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<11 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcLaborResource, expecting 11, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<11 ){ std::cout << "Wrong parameter count for entity IfcLaborResource, expecting 11, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
				readEntityReference( args[1], m_OwnerHistory, map);
				m_Name = IfcLabel::readStepData( args[2] );
				m_Description = IfcText::readStepData( args[3] );
				m_ObjectType = IfcLabel::readStepData( args[4] );
				m_Identification = IfcIdentifier::readStepData( args[5] );
				m_LongDescription = IfcText::readStepData( args[6] );
				readEntityReference( args[7], m_Usage, map);
				readEntityReferenceList( args[8], m_BaseCosts , map);
				readEntityReference( args[9], m_BaseQuantity, map);
				m_PredefinedType = IfcLaborResourceTypeEnum::readStepData( args[10] );
			}
			void IfcLaborResource::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcConstructionResource::setInverseCounterparts(ptr_self_entity);
			}
			void IfcLaborResource::unlinkSelf()
			{
				IfcConstructionResource::unlinkSelf();
			}
	}
}
