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

#include "model/Ifc2x3Exception.h"
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "Ifc2x3EntityEnums.h"
#include "include/IfcLabel.h"
#include "include/IfcPositiveLengthMeasure.h"
#include "include/IfcProfileDef.h"
#include "include/IfcRibPlateDirectionEnum.h"
#include "include/IfcRibPlateProfileProperties.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcRibPlateProfileProperties 
		IfcRibPlateProfileProperties::IfcRibPlateProfileProperties() { m_entity_enum = IFCRIBPLATEPROFILEPROPERTIES; }
		IfcRibPlateProfileProperties::IfcRibPlateProfileProperties( int id ) { m_id = id; m_entity_enum = IFCRIBPLATEPROFILEPROPERTIES; }
		IfcRibPlateProfileProperties::~IfcRibPlateProfileProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcRibPlateProfileProperties::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcRibPlateProfileProperties> other = dynamic_pointer_cast<IfcRibPlateProfileProperties>(other_entity);
			if( !other) { return; }
			m_ProfileName = other->m_ProfileName;
			m_ProfileDefinition = other->m_ProfileDefinition;
			m_Thickness = other->m_Thickness;
			m_RibHeight = other->m_RibHeight;
			m_RibWidth = other->m_RibWidth;
			m_RibSpacing = other->m_RibSpacing;
			m_Direction = other->m_Direction;
		}
		void IfcRibPlateProfileProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCRIBPLATEPROFILEPROPERTIES" << "(";
			if( m_ProfileName ) { m_ProfileName->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_ProfileDefinition ) { stream << "#" << m_ProfileDefinition->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Thickness ) { m_Thickness->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RibHeight ) { m_RibHeight->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RibWidth ) { m_RibWidth->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RibSpacing ) { m_RibSpacing->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Direction ) { m_Direction->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcRibPlateProfileProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcRibPlateProfileProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<7 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcRibPlateProfileProperties, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>7 ){ std::cout << "Wrong parameter count for entity IfcRibPlateProfileProperties, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_ProfileName = IfcLabel::readStepData( args[0] );
			readEntityReference( args[1], m_ProfileDefinition, map );
			m_Thickness = IfcPositiveLengthMeasure::readStepData( args[2] );
			m_RibHeight = IfcPositiveLengthMeasure::readStepData( args[3] );
			m_RibWidth = IfcPositiveLengthMeasure::readStepData( args[4] );
			m_RibSpacing = IfcPositiveLengthMeasure::readStepData( args[5] );
			m_Direction = IfcRibPlateDirectionEnum::readStepData( args[6] );
		}
		void IfcRibPlateProfileProperties::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcProfileProperties::setInverseCounterparts( ptr_self_entity );
		}
		void IfcRibPlateProfileProperties::unlinkSelf()
		{
			IfcProfileProperties::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
