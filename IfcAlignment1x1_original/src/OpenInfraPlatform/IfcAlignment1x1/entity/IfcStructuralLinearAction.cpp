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
#include "IfcStructuralLinearAction.h"
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
#include "IfcStructuralCurveActivityTypeEnum.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcStructuralLinearAction
			IfcStructuralLinearAction::IfcStructuralLinearAction() { m_entity_enum = IFCSTRUCTURALLINEARACTION;}
			IfcStructuralLinearAction::IfcStructuralLinearAction( int id ) { m_id = id; m_entity_enum = IFCSTRUCTURALLINEARACTION;}
			IfcStructuralLinearAction::~IfcStructuralLinearAction() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcStructuralLinearAction::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcStructuralLinearAction> other = std::dynamic_pointer_cast<IfcStructuralLinearAction>(other_entity);
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
			void IfcStructuralLinearAction::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCSTRUCTURALLINEARACTION" << "(";
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
			void IfcStructuralLinearAction::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcStructuralLinearAction::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<12 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcStructuralLinearAction, expecting 12, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<12 ){ std::cout << "Wrong parameter count for entity IfcStructuralLinearAction, expecting 12, having " << num_args << ". Object id: " << getId() << std::endl; }
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
				m_PredefinedType = IfcStructuralCurveActivityTypeEnum::readStepData( args[11] );
			}
			void IfcStructuralLinearAction::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcStructuralCurveAction::setInverseCounterparts(ptr_self_entity);
			}
			void IfcStructuralLinearAction::unlinkSelf()
			{
				IfcStructuralCurveAction::unlinkSelf();
			}
	}
}
