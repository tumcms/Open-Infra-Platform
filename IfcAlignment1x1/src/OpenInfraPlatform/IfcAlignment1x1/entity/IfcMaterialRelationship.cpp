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
#include "IfcMaterialRelationship.h"
#include "IfcLabel.h"
#include "IfcText.h"
#include "IfcMaterial.h"
#include "IfcMaterial.h"
#include "IfcLabel.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcMaterialRelationship
			IfcMaterialRelationship::IfcMaterialRelationship() { m_entity_enum = IFCMATERIALRELATIONSHIP;}
			IfcMaterialRelationship::IfcMaterialRelationship( int id ) { m_id = id; m_entity_enum = IFCMATERIALRELATIONSHIP;}
			IfcMaterialRelationship::~IfcMaterialRelationship() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcMaterialRelationship::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcMaterialRelationship> other = std::dynamic_pointer_cast<IfcMaterialRelationship>(other_entity);
				if( !other) { return; }
				m_Name = other->m_Name;
				m_Description = other->m_Description;
				m_RelatingMaterial = other->m_RelatingMaterial;
				m_RelatedMaterials = other->m_RelatedMaterials;
				m_Expression = other->m_Expression;
			}
			void IfcMaterialRelationship::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCMATERIALRELATIONSHIP" << "(";
				if( m_Name) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Description) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_RelatingMaterial) { stream << "#" << m_RelatingMaterial->getId(); } else { stream << "$"; }
				stream << ",";
				writeEntityList( stream, m_RelatedMaterials );
				stream << ",";
				if( m_Expression) { m_Expression->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcMaterialRelationship::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcMaterialRelationship::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<5 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcMaterialRelationship, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<5 ){ std::cout << "Wrong parameter count for entity IfcMaterialRelationship, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_Name = IfcLabel::readStepData( args[0] );
				m_Description = IfcText::readStepData( args[1] );
				readEntityReference( args[2], m_RelatingMaterial, map);
				readEntityReferenceList( args[3], m_RelatedMaterials , map);
				m_Expression = IfcLabel::readStepData( args[4] );
			}
			void IfcMaterialRelationship::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcResourceLevelRelationship::setInverseCounterparts(ptr_self_entity);
			}
			void IfcMaterialRelationship::unlinkSelf()
			{
				IfcResourceLevelRelationship::unlinkSelf();
			}
	}
}
