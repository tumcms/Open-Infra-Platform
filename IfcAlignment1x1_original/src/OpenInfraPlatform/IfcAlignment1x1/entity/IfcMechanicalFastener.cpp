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
#include "IfcMechanicalFastener.h"
#include "IfcGloballyUniqueId.h"
#include "IfcOwnerHistory.h"
#include "IfcLabel.h"
#include "IfcText.h"
#include "IfcLabel.h"
#include "IfcObjectPlacement.h"
#include "IfcProductRepresentation.h"
#include "IfcIdentifier.h"
#include "IfcPositiveLengthMeasure.h"
#include "IfcPositiveLengthMeasure.h"
#include "IfcMechanicalFastenerTypeEnum.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcMechanicalFastener
			IfcMechanicalFastener::IfcMechanicalFastener() { m_entity_enum = IFCMECHANICALFASTENER;}
			IfcMechanicalFastener::IfcMechanicalFastener( int id ) { m_id = id; m_entity_enum = IFCMECHANICALFASTENER;}
			IfcMechanicalFastener::~IfcMechanicalFastener() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcMechanicalFastener::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcMechanicalFastener> other = std::dynamic_pointer_cast<IfcMechanicalFastener>(other_entity);
				if( !other) { return; }
				m_GlobalId = other->m_GlobalId;
				m_OwnerHistory = other->m_OwnerHistory;
				m_Name = other->m_Name;
				m_Description = other->m_Description;
				m_ObjectType = other->m_ObjectType;
				m_ObjectPlacement = other->m_ObjectPlacement;
				m_Representation = other->m_Representation;
				m_Tag = other->m_Tag;
				m_NominalDiameter = other->m_NominalDiameter;
				m_NominalLength = other->m_NominalLength;
				m_PredefinedType = other->m_PredefinedType;
			}
			void IfcMechanicalFastener::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCMECHANICALFASTENER" << "(";
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
				if( m_Tag) { m_Tag->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_NominalDiameter) { m_NominalDiameter->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_NominalLength) { m_NominalLength->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_PredefinedType) { m_PredefinedType->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcMechanicalFastener::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcMechanicalFastener::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<11 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcMechanicalFastener, expecting 11, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<11 ){ std::cout << "Wrong parameter count for entity IfcMechanicalFastener, expecting 11, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
				readEntityReference( args[1], m_OwnerHistory, map);
				m_Name = IfcLabel::readStepData( args[2] );
				m_Description = IfcText::readStepData( args[3] );
				m_ObjectType = IfcLabel::readStepData( args[4] );
				readEntityReference( args[5], m_ObjectPlacement, map);
				readEntityReference( args[6], m_Representation, map);
				m_Tag = IfcIdentifier::readStepData( args[7] );
				m_NominalDiameter = IfcPositiveLengthMeasure::readStepData( args[8] );
				m_NominalLength = IfcPositiveLengthMeasure::readStepData( args[9] );
				m_PredefinedType = IfcMechanicalFastenerTypeEnum::readStepData( args[10] );
			}
			void IfcMechanicalFastener::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcElementComponent::setInverseCounterparts(ptr_self_entity);
			}
			void IfcMechanicalFastener::unlinkSelf()
			{
				IfcElementComponent::unlinkSelf();
			}
	}
}
