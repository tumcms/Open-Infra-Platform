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
#include "include/IfcLabel.h"
#include "include/IfcMaterial.h"
#include "include/IfcMaterialRelationship.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace IfcRoad
	{
		// ENTITY IfcMaterialRelationship 
		IfcMaterialRelationship::IfcMaterialRelationship() { m_entity_enum = IFCMATERIALRELATIONSHIP; }
		IfcMaterialRelationship::IfcMaterialRelationship( int id ) { m_id = id; m_entity_enum = IFCMATERIALRELATIONSHIP; }
		IfcMaterialRelationship::~IfcMaterialRelationship() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcMaterialRelationship::setEntity( shared_ptr<IfcRoadEntity> other_entity )
		{
			shared_ptr<IfcMaterialRelationship> other = dynamic_pointer_cast<IfcMaterialRelationship>(other_entity);
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
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RelatingMaterial ) { stream << "#" << m_RelatingMaterial->getId(); } else { stream << "$"; }
			stream << ",";
			writeEntityList( stream, m_RelatedMaterials );
			stream << ",";
			if( m_Expression ) { m_Expression->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcMaterialRelationship::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcMaterialRelationship::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcRoadEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<5 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcMaterialRelationship, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcRoadException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>5 ){ std::cout << "Wrong parameter count for entity IfcMaterialRelationship, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Name = IfcLabel::readStepData( args[0] );
			m_Description = IfcText::readStepData( args[1] );
			readEntityReference( args[2], m_RelatingMaterial, map );
			readEntityReferenceList( args[3], m_RelatedMaterials, map );
			m_Expression = IfcLabel::readStepData( args[4] );
		}
		void IfcMaterialRelationship::setInverseCounterparts( shared_ptr<IfcRoadEntity> ptr_self_entity )
		{
			IfcResourceLevelRelationship::setInverseCounterparts( ptr_self_entity );
			shared_ptr<IfcMaterialRelationship> ptr_self = dynamic_pointer_cast<IfcMaterialRelationship>( ptr_self_entity );
			if( !ptr_self ) { throw IfcRoadException( "IfcMaterialRelationship::setInverseCounterparts: type mismatch" ); }
			for( int i=0; i<m_RelatedMaterials.size(); ++i )
			{
				if( m_RelatedMaterials[i] )
				{
					m_RelatedMaterials[i]->m_IsRelatedWith_inverse.push_back( ptr_self );
				}
			}
			if( m_RelatingMaterial )
			{
				m_RelatingMaterial->m_RelatesTo_inverse.push_back( ptr_self );
			}
		}
		void IfcMaterialRelationship::unlinkSelf()
		{
			IfcResourceLevelRelationship::unlinkSelf();
			for( int i=0; i<m_RelatedMaterials.size(); ++i )
			{
				if( m_RelatedMaterials[i] )
				{
					std::vector<weak_ptr<IfcMaterialRelationship> >& IsRelatedWith_inverse = m_RelatedMaterials[i]->m_IsRelatedWith_inverse;
					std::vector<weak_ptr<IfcMaterialRelationship> >::iterator it_IsRelatedWith_inverse;
					for( it_IsRelatedWith_inverse = IsRelatedWith_inverse.begin(); it_IsRelatedWith_inverse != IsRelatedWith_inverse.end(); ++it_IsRelatedWith_inverse)
					{
						shared_ptr<IfcMaterialRelationship> self_candidate( *it_IsRelatedWith_inverse );
						if( self_candidate->getId() == this->getId() )
						{
							IsRelatedWith_inverse.erase( it_IsRelatedWith_inverse );
							break;
						}
					}
				}
			}
			if( m_RelatingMaterial )
			{
				std::vector<weak_ptr<IfcMaterialRelationship> >& RelatesTo_inverse = m_RelatingMaterial->m_RelatesTo_inverse;
				std::vector<weak_ptr<IfcMaterialRelationship> >::iterator it_RelatesTo_inverse;
				for( it_RelatesTo_inverse = RelatesTo_inverse.begin(); it_RelatesTo_inverse != RelatesTo_inverse.end(); ++it_RelatesTo_inverse)
				{
					shared_ptr<IfcMaterialRelationship> self_candidate( *it_RelatesTo_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						RelatesTo_inverse.erase( it_RelatesTo_inverse );
						break;
					}
				}
			}
		}
	} // end namespace IfcRoad
} // end namespace OpenInfraPlatform
