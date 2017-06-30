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
#include "include/IfcProfileDef.h"
#include "include/IfcSectionProperties.h"
#include "include/IfcSectionTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcSectionProperties 
		IfcSectionProperties::IfcSectionProperties() { m_entity_enum = IFCSECTIONPROPERTIES; }
		IfcSectionProperties::IfcSectionProperties( int id ) { m_id = id; m_entity_enum = IFCSECTIONPROPERTIES; }
		IfcSectionProperties::~IfcSectionProperties() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcSectionProperties::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcSectionProperties> other = dynamic_pointer_cast<IfcSectionProperties>(other_entity);
			if( !other) { return; }
			m_SectionType = other->m_SectionType;
			m_StartProfile = other->m_StartProfile;
			m_EndProfile = other->m_EndProfile;
		}
		void IfcSectionProperties::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCSECTIONPROPERTIES" << "(";
			if( m_SectionType ) { m_SectionType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_StartProfile ) { stream << "#" << m_StartProfile->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_EndProfile ) { stream << "#" << m_EndProfile->getId(); } else { stream << "$"; }
			stream << ");";
		}
		void IfcSectionProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcSectionProperties::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<3 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcSectionProperties, expecting 3, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>3 ){ std::cout << "Wrong parameter count for entity IfcSectionProperties, expecting 3, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_SectionType = IfcSectionTypeEnum::readStepData( args[0] );
			readEntityReference( args[1], m_StartProfile, map );
			readEntityReference( args[2], m_EndProfile, map );
		}
		void IfcSectionProperties::setInverseCounterparts( shared_ptr<Ifc2x3Entity> )
		{
		}
		void IfcSectionProperties::unlinkSelf()
		{
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
