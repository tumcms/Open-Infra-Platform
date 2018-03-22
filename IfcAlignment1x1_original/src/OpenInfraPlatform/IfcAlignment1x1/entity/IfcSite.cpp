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
#include "IfcSite.h"
#include "IfcGloballyUniqueId.h"
#include "IfcOwnerHistory.h"
#include "IfcLabel.h"
#include "IfcText.h"
#include "IfcLabel.h"
#include "IfcObjectPlacement.h"
#include "IfcProductRepresentation.h"
#include "IfcLabel.h"
#include "IfcElementCompositionEnum.h"
#include "IfcCompoundPlaneAngleMeasure.h"
#include "IfcCompoundPlaneAngleMeasure.h"
#include "IfcLengthMeasure.h"
#include "IfcLabel.h"
#include "IfcPostalAddress.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcSite
			IfcSite::IfcSite() { m_entity_enum = IFCSITE;}
			IfcSite::IfcSite( int id ) { m_id = id; m_entity_enum = IFCSITE;}
			IfcSite::~IfcSite() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcSite::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcSite> other = std::dynamic_pointer_cast<IfcSite>(other_entity);
				if( !other) { return; }
				m_GlobalId = other->m_GlobalId;
				m_OwnerHistory = other->m_OwnerHistory;
				m_Name = other->m_Name;
				m_Description = other->m_Description;
				m_ObjectType = other->m_ObjectType;
				m_ObjectPlacement = other->m_ObjectPlacement;
				m_Representation = other->m_Representation;
				m_LongName = other->m_LongName;
				m_CompositionType = other->m_CompositionType;
				m_RefLatitude = other->m_RefLatitude;
				m_RefLongitude = other->m_RefLongitude;
				m_RefElevation = other->m_RefElevation;
				m_LandTitleNumber = other->m_LandTitleNumber;
				m_SiteAddress = other->m_SiteAddress;
			}
			void IfcSite::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCSITE" << "(";
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
				if( m_LongName) { m_LongName->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_CompositionType) { m_CompositionType->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_RefLatitude) { m_RefLatitude->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_RefLongitude) { m_RefLongitude->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_RefElevation) { m_RefElevation->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_LandTitleNumber) { m_LandTitleNumber->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_SiteAddress) { stream << "#" << m_SiteAddress->getId(); } else { stream << "$"; }
				stream << ");";
			}
			void IfcSite::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcSite::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<14 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcSite, expecting 14, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<14 ){ std::cout << "Wrong parameter count for entity IfcSite, expecting 14, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_GlobalId = IfcGloballyUniqueId::readStepData( args[0] );
				readEntityReference( args[1], m_OwnerHistory, map);
				m_Name = IfcLabel::readStepData( args[2] );
				m_Description = IfcText::readStepData( args[3] );
				m_ObjectType = IfcLabel::readStepData( args[4] );
				readEntityReference( args[5], m_ObjectPlacement, map);
				readEntityReference( args[6], m_Representation, map);
				m_LongName = IfcLabel::readStepData( args[7] );
				m_CompositionType = IfcElementCompositionEnum::readStepData( args[8] );
				m_RefLatitude = IfcCompoundPlaneAngleMeasure::readStepData( args[9] );
				m_RefLongitude = IfcCompoundPlaneAngleMeasure::readStepData( args[10] );
				m_RefElevation = IfcLengthMeasure::readStepData( args[11] );
				m_LandTitleNumber = IfcLabel::readStepData( args[12] );
				readEntityReference( args[13], m_SiteAddress, map);
			}
			void IfcSite::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcSpatialStructureElement::setInverseCounterparts(ptr_self_entity);
			}
			void IfcSite::unlinkSelf()
			{
				IfcSpatialStructureElement::unlinkSelf();
			}
	}
}
