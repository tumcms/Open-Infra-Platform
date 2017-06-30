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
#include "IfcRelAssignsToProduct.h"
#include "IfcGloballyUniqueId.h"
#include "IfcOwnerHistory.h"
#include "IfcLabel.h"
#include "IfcText.h"
#include "IfcObjectDefinition.h"
#include "IfcObjectTypeEnum.h"
#include "IfcProductSelect.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcRelAssignsToProduct
			IfcRelAssignsToProduct::IfcRelAssignsToProduct() { m_entity_enum = IFCRELASSIGNSTOPRODUCT;}
			IfcRelAssignsToProduct::IfcRelAssignsToProduct( int id ) { m_id = id; m_entity_enum = IFCRELASSIGNSTOPRODUCT;}
			IfcRelAssignsToProduct::~IfcRelAssignsToProduct() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcRelAssignsToProduct::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcRelAssignsToProduct> other = std::dynamic_pointer_cast<IfcRelAssignsToProduct>(other_entity);
				if( !other) { return; }
				m_GlobalId = other->m_GlobalId;
				m_OwnerHistory = other->m_OwnerHistory;
				m_Name = other->m_Name;
				m_Description = other->m_Description;
				m_RelatedObjects = other->m_RelatedObjects;
				m_RelatedObjectsType = other->m_RelatedObjectsType;
				m_RelatingProduct = other->m_RelatingProduct;
			}
			void IfcRelAssignsToProduct::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCRELASSIGNSTOPRODUCT" << "(";
				if( m_GlobalId) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_OwnerHistory) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Name) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Description) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				writeEntityList( stream, m_RelatedObjects );
				stream << ",";
				if( m_RelatedObjectsType) { m_RelatedObjectsType->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_RelatingProduct) { m_RelatingProduct->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcRelAssignsToProduct::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcRelAssignsToProduct::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<7 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcRelAssignsToProduct, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<7 ){ std::cout << "Wrong parameter count for entity IfcRelAssignsToProduct, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
				readEntityReference( args[1], m_OwnerHistory, map);
				m_Name = IfcLabel::readStepData( args[2] );
				m_Description = IfcText::readStepData( args[3] );
				readEntityReferenceList( args[4], m_RelatedObjects , map);
				m_RelatedObjectsType = IfcObjectTypeEnum::readStepData( args[5] );
				m_RelatingProduct = IfcProductSelect::readStepData( args[6], map );
			}
			void IfcRelAssignsToProduct::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcRelAssigns::setInverseCounterparts(ptr_self_entity);
			}
			void IfcRelAssignsToProduct::unlinkSelf()
			{
				IfcRelAssigns::unlinkSelf();
			}
	}
}
