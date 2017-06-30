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
#include "include/IfcCurrencyRelationship.h"
#include "include/IfcDateTime.h"
#include "include/IfcLabel.h"
#include "include/IfcLibraryInformation.h"
#include "include/IfcMonetaryUnit.h"
#include "include/IfcPositiveRatioMeasure.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// ENTITY IfcCurrencyRelationship 
		IfcCurrencyRelationship::IfcCurrencyRelationship() { m_entity_enum = IFCCURRENCYRELATIONSHIP; }
		IfcCurrencyRelationship::IfcCurrencyRelationship( int id ) { m_id = id; m_entity_enum = IFCCURRENCYRELATIONSHIP; }
		IfcCurrencyRelationship::~IfcCurrencyRelationship() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcCurrencyRelationship::setEntity( shared_ptr<IfcBridgeEntity> other_entity )
		{
			shared_ptr<IfcCurrencyRelationship> other = dynamic_pointer_cast<IfcCurrencyRelationship>(other_entity);
			if( !other) { return; }
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_RelatingMonetaryUnit = other->m_RelatingMonetaryUnit;
			m_RelatedMonetaryUnit = other->m_RelatedMonetaryUnit;
			m_ExchangeRate = other->m_ExchangeRate;
			m_RateDateTime = other->m_RateDateTime;
			m_RateSource = other->m_RateSource;
		}
		void IfcCurrencyRelationship::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCCURRENCYRELATIONSHIP" << "(";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RelatingMonetaryUnit ) { stream << "#" << m_RelatingMonetaryUnit->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_RelatedMonetaryUnit ) { stream << "#" << m_RelatedMonetaryUnit->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_ExchangeRate ) { m_ExchangeRate->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RateDateTime ) { m_RateDateTime->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_RateSource ) { stream << "#" << m_RateSource->getId(); } else { stream << "$"; }
			stream << ");";
		}
		void IfcCurrencyRelationship::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcCurrencyRelationship::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcBridgeEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<7 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcCurrencyRelationship, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcBridgeException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>7 ){ std::cout << "Wrong parameter count for entity IfcCurrencyRelationship, expecting 7, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Name = IfcLabel::readStepData( args[0] );
			m_Description = IfcText::readStepData( args[1] );
			readEntityReference( args[2], m_RelatingMonetaryUnit, map );
			readEntityReference( args[3], m_RelatedMonetaryUnit, map );
			m_ExchangeRate = IfcPositiveRatioMeasure::readStepData( args[4] );
			m_RateDateTime = IfcDateTime::readStepData( args[5] );
			readEntityReference( args[6], m_RateSource, map );
		}
		void IfcCurrencyRelationship::setInverseCounterparts( shared_ptr<IfcBridgeEntity> ptr_self_entity )
		{
			IfcResourceLevelRelationship::setInverseCounterparts( ptr_self_entity );
		}
		void IfcCurrencyRelationship::unlinkSelf()
		{
			IfcResourceLevelRelationship::unlinkSelf();
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
