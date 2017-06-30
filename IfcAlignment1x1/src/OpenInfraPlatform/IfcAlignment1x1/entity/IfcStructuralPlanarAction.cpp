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
#include "IfcStructuralPlanarAction.h"
#include "IfcGloballyUniqueId.h"
#include "IfcOwnerHistory.h"
#include "IfcLabel.h"
#include "IfcText.h"
#include "IfcLabel.h"
#include "IfcObjectPlacement.h"
#include "IfcProductRepresentation.h"
#include "IfcStructuralLoad.h"
#include "IfcGlobalOrLocalEnum.h"
#include "IfcBoolean.h"
#include "IfcProjectedOrTrueLengthEnum.h"
#include "IfcStructuralSurfaceActivityTypeEnum.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcStructuralPlanarAction
			IfcStructuralPlanarAction::IfcStructuralPlanarAction() { m_entity_enum = IFCSTRUCTURALPLANARACTION;}
			IfcStructuralPlanarAction::IfcStructuralPlanarAction( int id ) { m_id = id; m_entity_enum = IFCSTRUCTURALPLANARACTION;}
			IfcStructuralPlanarAction::~IfcStructuralPlanarAction() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcStructuralPlanarAction::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcStructuralPlanarAction> other = std::dynamic_pointer_cast<IfcStructuralPlanarAction>(other_entity);
				if( !other) { return; }
				m_GlobalId = other->m_GlobalId;
				m_OwnerHistory = other->m_OwnerHistory;
				m_Name = other->m_Name;
				m_Description = other->m_Description;
				m_ObjectType = other->m_ObjectType;
				m_ObjectPlacement = other->m_ObjectPlacement;
				m_Representation = other->m_Representation;
				m_AppliedLoad = other->m_AppliedLoad;
				m_GlobalOrLocal = other->m_GlobalOrLocal;
				m_DestabilizingLoad = other->m_DestabilizingLoad;
				m_ProjectedOrTrue = other->m_ProjectedOrTrue;
				m_PredefinedType = other->m_PredefinedType;
			}
			void IfcStructuralPlanarAction::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCSTRUCTURALPLANARACTION" << "(";
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
				if( m_ObjectPlacement) { stream << "#" << m_ObjectPlacement->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Representation) { stream << "#" << m_Representation->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_AppliedLoad) { stream << "#" << m_AppliedLoad->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_GlobalOrLocal) { m_GlobalOrLocal->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_DestabilizingLoad) { m_DestabilizingLoad->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_ProjectedOrTrue) { m_ProjectedOrTrue->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_PredefinedType) { m_PredefinedType->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcStructuralPlanarAction::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcStructuralPlanarAction::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<12 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcStructuralPlanarAction, expecting 12, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<12 ){ std::cout << "Wrong parameter count for entity IfcStructuralPlanarAction, expecting 12, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
				readEntityReference( args[1], m_OwnerHistory, map);
				m_Name = IfcLabel::readStepData( args[2] );
				m_Description = IfcText::readStepData( args[3] );
				m_ObjectType = IfcLabel::readStepData( args[4] );
				readEntityReference( args[5], m_ObjectPlacement, map);
				readEntityReference( args[6], m_Representation, map);
				readEntityReference( args[7], m_AppliedLoad, map);
				m_GlobalOrLocal = IfcGlobalOrLocalEnum::readStepData( args[8] );
				m_DestabilizingLoad = IfcBoolean::readStepData( args[9] );
				m_ProjectedOrTrue = IfcProjectedOrTrueLengthEnum::readStepData( args[10] );
				m_PredefinedType = IfcStructuralSurfaceActivityTypeEnum::readStepData( args[11] );
			}
			void IfcStructuralPlanarAction::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcStructuralSurfaceAction::setInverseCounterparts(ptr_self_entity);
			}
			void IfcStructuralPlanarAction::unlinkSelf()
			{
				IfcStructuralSurfaceAction::unlinkSelf();
			}
	}
}
