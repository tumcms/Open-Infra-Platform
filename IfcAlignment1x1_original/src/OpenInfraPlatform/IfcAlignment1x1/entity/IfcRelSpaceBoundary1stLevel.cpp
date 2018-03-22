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
#include "IfcRelSpaceBoundary1stLevel.h"
#include "IfcGloballyUniqueId.h"
#include "IfcOwnerHistory.h"
#include "IfcLabel.h"
#include "IfcText.h"
#include "IfcSpaceBoundarySelect.h"
#include "IfcElement.h"
#include "IfcConnectionGeometry.h"
#include "IfcPhysicalOrVirtualEnum.h"
#include "IfcInternalOrExternalEnum.h"
#include "IfcRelSpaceBoundary1stLevel.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcRelSpaceBoundary1stLevel
			IfcRelSpaceBoundary1stLevel::IfcRelSpaceBoundary1stLevel() { m_entity_enum = IFCRELSPACEBOUNDARY1STLEVEL;}
			IfcRelSpaceBoundary1stLevel::IfcRelSpaceBoundary1stLevel( int id ) { m_id = id; m_entity_enum = IFCRELSPACEBOUNDARY1STLEVEL;}
			IfcRelSpaceBoundary1stLevel::~IfcRelSpaceBoundary1stLevel() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcRelSpaceBoundary1stLevel::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcRelSpaceBoundary1stLevel> other = std::dynamic_pointer_cast<IfcRelSpaceBoundary1stLevel>(other_entity);
				if( !other) { return; }
				m_GlobalId = other->m_GlobalId;
				m_OwnerHistory = other->m_OwnerHistory;
				m_Name = other->m_Name;
				m_Description = other->m_Description;
				m_RelatingSpace = other->m_RelatingSpace;
				m_RelatedBuildingElement = other->m_RelatedBuildingElement;
				m_ConnectionGeometry = other->m_ConnectionGeometry;
				m_PhysicalOrVirtualBoundary = other->m_PhysicalOrVirtualBoundary;
				m_InternalOrExternalBoundary = other->m_InternalOrExternalBoundary;
				m_ParentBoundary = other->m_ParentBoundary;
			}
			void IfcRelSpaceBoundary1stLevel::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCRELSPACEBOUNDARY1STLEVEL" << "(";
				if( m_GlobalId) { m_GlobalId->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_OwnerHistory) { stream << "#" << m_OwnerHistory->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Name) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Description) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_RelatingSpace) { m_RelatingSpace->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_RelatedBuildingElement) { stream << "#" << m_RelatedBuildingElement->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_ConnectionGeometry) { stream << "#" << m_ConnectionGeometry->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_PhysicalOrVirtualBoundary) { m_PhysicalOrVirtualBoundary->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_InternalOrExternalBoundary) { m_InternalOrExternalBoundary->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_ParentBoundary) { stream << "#" << m_ParentBoundary->getId(); } else { stream << "$"; }
				stream << ");";
			}
			void IfcRelSpaceBoundary1stLevel::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcRelSpaceBoundary1stLevel::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<10 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcRelSpaceBoundary1stLevel, expecting 10, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<10 ){ std::cout << "Wrong parameter count for entity IfcRelSpaceBoundary1stLevel, expecting 10, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
				readEntityReference( args[1], m_OwnerHistory, map);
				m_Name = IfcLabel::readStepData( args[2] );
				m_Description = IfcText::readStepData( args[3] );
				m_RelatingSpace = IfcSpaceBoundarySelect::readStepData( args[4], map );
				readEntityReference( args[5], m_RelatedBuildingElement, map);
				readEntityReference( args[6], m_ConnectionGeometry, map);
				m_PhysicalOrVirtualBoundary = IfcPhysicalOrVirtualEnum::readStepData( args[7] );
				m_InternalOrExternalBoundary = IfcInternalOrExternalEnum::readStepData( args[8] );
				readEntityReference( args[9], m_ParentBoundary, map);
			}
			void IfcRelSpaceBoundary1stLevel::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcRelSpaceBoundary::setInverseCounterparts(ptr_self_entity);
			}
			void IfcRelSpaceBoundary1stLevel::unlinkSelf()
			{
				IfcRelSpaceBoundary::unlinkSelf();
			}
	}
}
