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

#include "model/IfcBridgeException.h"
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "IfcBridgeEntityEnums.h"
#include "include/IfcAddressTypeEnum.h"
#include "include/IfcLabel.h"
#include "include/IfcOrganization.h"
#include "include/IfcPerson.h"
#include "include/IfcPostalAddress.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// ENTITY IfcPostalAddress 
		IfcPostalAddress::IfcPostalAddress() { m_entity_enum = IFCPOSTALADDRESS; }
		IfcPostalAddress::IfcPostalAddress( int id ) { m_id = id; m_entity_enum = IFCPOSTALADDRESS; }
		IfcPostalAddress::~IfcPostalAddress() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcPostalAddress::setEntity( shared_ptr<IfcBridgeEntity> other_entity )
		{
			shared_ptr<IfcPostalAddress> other = dynamic_pointer_cast<IfcPostalAddress>(other_entity);
			if( !other) { return; }
			m_Purpose = other->m_Purpose;
			m_Description = other->m_Description;
			m_UserDefinedPurpose = other->m_UserDefinedPurpose;
			m_InternalLocation = other->m_InternalLocation;
			m_AddressLines = other->m_AddressLines;
			m_PostalBox = other->m_PostalBox;
			m_Town = other->m_Town;
			m_Region = other->m_Region;
			m_PostalCode = other->m_PostalCode;
			m_Country = other->m_Country;
		}
		void IfcPostalAddress::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCPOSTALADDRESS" << "(";
			if( m_Purpose ) { m_Purpose->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_UserDefinedPurpose ) { m_UserDefinedPurpose->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_InternalLocation ) { m_InternalLocation->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeTypeList( stream, m_AddressLines );
			stream << ",";
			if( m_PostalBox ) { m_PostalBox->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Town ) { m_Town->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Region ) { m_Region->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_PostalCode ) { m_PostalCode->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Country ) { m_Country->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcPostalAddress::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcPostalAddress::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcBridgeEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<10 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcPostalAddress, expecting 10, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcBridgeException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>10 ){ std::cout << "Wrong parameter count for entity IfcPostalAddress, expecting 10, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Purpose = IfcAddressTypeEnum::readStepData( args[0] );
			m_Description = IfcText::readStepData( args[1] );
			m_UserDefinedPurpose = IfcLabel::readStepData( args[2] );
			m_InternalLocation = IfcLabel::readStepData( args[3] );
			readTypeList( args[4], m_AddressLines );
			m_PostalBox = IfcLabel::readStepData( args[5] );
			m_Town = IfcLabel::readStepData( args[6] );
			m_Region = IfcLabel::readStepData( args[7] );
			m_PostalCode = IfcLabel::readStepData( args[8] );
			m_Country = IfcLabel::readStepData( args[9] );
		}
		void IfcPostalAddress::setInverseCounterparts( shared_ptr<IfcBridgeEntity> ptr_self_entity )
		{
			IfcAddress::setInverseCounterparts( ptr_self_entity );
		}
		void IfcPostalAddress::unlinkSelf()
		{
			IfcAddress::unlinkSelf();
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
