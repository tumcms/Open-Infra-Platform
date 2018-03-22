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
#include "IfcMaterialLayer.h"
#include "IfcMaterial.h"
#include "IfcNonNegativeLengthMeasure.h"
#include "IfcLogical.h"
#include "IfcLabel.h"
#include "IfcText.h"
#include "IfcLabel.h"
#include "IfcInteger.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcMaterialLayer
			IfcMaterialLayer::IfcMaterialLayer() { m_entity_enum = IFCMATERIALLAYER;}
			IfcMaterialLayer::IfcMaterialLayer( int id ) { m_id = id; m_entity_enum = IFCMATERIALLAYER;}
			IfcMaterialLayer::~IfcMaterialLayer() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcMaterialLayer::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcMaterialLayer> other = std::dynamic_pointer_cast<IfcMaterialLayer>(other_entity);
				if( !other) { return; }
				m_Material = other->m_Material;
				m_LayerThickness = other->m_LayerThickness;
				m_IsVentilated = other->m_IsVentilated;
				m_Name = other->m_Name;
				m_Description = other->m_Description;
				m_Category = other->m_Category;
				m_Priority = other->m_Priority;
			}
			void IfcMaterialLayer::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCMATERIALLAYER" << "(";
				if( m_Material) { stream << "#" << m_Material->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_LayerThickness) { m_LayerThickness->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_IsVentilated) { m_IsVentilated->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Name) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Description) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Category) { m_Category->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Priority) { m_Priority->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcMaterialLayer::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcMaterialLayer::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<7 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcMaterialLayer, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<7 ){ std::cout << "Wrong parameter count for entity IfcMaterialLayer, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				readEntityReference( args[0], m_Material, map);
				m_LayerThickness = IfcNonNegativeLengthMeasure::readStepData( args[1] );
				m_IsVentilated = IfcLogical::readStepData( args[2] );
				m_Name = IfcLabel::readStepData( args[3] );
				m_Description = IfcText::readStepData( args[4] );
				m_Category = IfcLabel::readStepData( args[5] );
				m_Priority = IfcInteger::readStepData( args[6] );
			}
			void IfcMaterialLayer::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcMaterialDefinition::setInverseCounterparts(ptr_self_entity);
			}
			void IfcMaterialLayer::unlinkSelf()
			{
				IfcMaterialDefinition::unlinkSelf();
			}
	}
}
