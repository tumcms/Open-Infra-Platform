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
#include "include/IfcTelecomAddress.h"
#include "include/IfcText.h"
#include "include/IfcURIReference.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// ENTITY IfcTelecomAddress 
		IfcTelecomAddress::IfcTelecomAddress() { m_entity_enum = IFCTELECOMADDRESS; }
		IfcTelecomAddress::IfcTelecomAddress( int id ) { m_id = id; m_entity_enum = IFCTELECOMADDRESS; }
		IfcTelecomAddress::~IfcTelecomAddress() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcTelecomAddress::setEntity( shared_ptr<IfcBridgeEntity> other_entity )
		{
			shared_ptr<IfcTelecomAddress> other = dynamic_pointer_cast<IfcTelecomAddress>(other_entity);
			if( !other) { return; }
			m_Purpose = other->m_Purpose;
			m_Description = other->m_Description;
			m_UserDefinedPurpose = other->m_UserDefinedPurpose;
			m_TelephoneNumbers = other->m_TelephoneNumbers;
			m_FacsimileNumbers = other->m_FacsimileNumbers;
			m_PagerNumber = other->m_PagerNumber;
			m_ElectronicMailAddresses = other->m_ElectronicMailAddresses;
			m_WWWHomePageURL = other->m_WWWHomePageURL;
			m_MessagingIDs = other->m_MessagingIDs;
		}
		void IfcTelecomAddress::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCTELECOMADDRESS" << "(";
			if( m_Purpose ) { m_Purpose->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_UserDefinedPurpose ) { m_UserDefinedPurpose->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeTypeList( stream, m_TelephoneNumbers );
			stream << ",";
			writeTypeList( stream, m_FacsimileNumbers );
			stream << ",";
			if( m_PagerNumber ) { m_PagerNumber->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeTypeList( stream, m_ElectronicMailAddresses );
			stream << ",";
			if( m_WWWHomePageURL ) { m_WWWHomePageURL->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeTypeList( stream, m_MessagingIDs );
			stream << ");";
		}
		void IfcTelecomAddress::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcTelecomAddress::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcBridgeEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<9 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcTelecomAddress, expecting 9, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcBridgeException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>9 ){ std::cout << "Wrong parameter count for entity IfcTelecomAddress, expecting 9, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Purpose = IfcAddressTypeEnum::readStepData( args[0] );
			m_Description = IfcText::readStepData( args[1] );
			m_UserDefinedPurpose = IfcLabel::readStepData( args[2] );
			readTypeList( args[3], m_TelephoneNumbers );
			readTypeList( args[4], m_FacsimileNumbers );
			m_PagerNumber = IfcLabel::readStepData( args[5] );
			readTypeList( args[6], m_ElectronicMailAddresses );
			m_WWWHomePageURL = IfcURIReference::readStepData( args[7] );
			readTypeList( args[8], m_MessagingIDs );
		}
		void IfcTelecomAddress::setInverseCounterparts( shared_ptr<IfcBridgeEntity> ptr_self_entity )
		{
			IfcAddress::setInverseCounterparts( ptr_self_entity );
		}
		void IfcTelecomAddress::unlinkSelf()
		{
			IfcAddress::unlinkSelf();
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
