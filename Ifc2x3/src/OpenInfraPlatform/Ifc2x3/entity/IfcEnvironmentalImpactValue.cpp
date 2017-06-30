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
#include "include/IfcAppliedValueRelationship.h"
#include "include/IfcAppliedValueSelect.h"
#include "include/IfcDateTimeSelect.h"
#include "include/IfcEnvironmentalImpactCategoryEnum.h"
#include "include/IfcEnvironmentalImpactValue.h"
#include "include/IfcLabel.h"
#include "include/IfcMeasureWithUnit.h"
#include "include/IfcReferencesValueDocument.h"
#include "include/IfcText.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcEnvironmentalImpactValue 
		IfcEnvironmentalImpactValue::IfcEnvironmentalImpactValue() { m_entity_enum = IFCENVIRONMENTALIMPACTVALUE; }
		IfcEnvironmentalImpactValue::IfcEnvironmentalImpactValue( int id ) { m_id = id; m_entity_enum = IFCENVIRONMENTALIMPACTVALUE; }
		IfcEnvironmentalImpactValue::~IfcEnvironmentalImpactValue() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcEnvironmentalImpactValue::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcEnvironmentalImpactValue> other = dynamic_pointer_cast<IfcEnvironmentalImpactValue>(other_entity);
			if( !other) { return; }
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_AppliedValue = other->m_AppliedValue;
			m_UnitBasis = other->m_UnitBasis;
			m_ApplicableDate = other->m_ApplicableDate;
			m_FixedUntilDate = other->m_FixedUntilDate;
			m_ImpactType = other->m_ImpactType;
			m_Category = other->m_Category;
			m_UserDefinedCategory = other->m_UserDefinedCategory;
		}
		void IfcEnvironmentalImpactValue::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCENVIRONMENTALIMPACTVALUE" << "(";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_AppliedValue ) { m_AppliedValue->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_UnitBasis ) { stream << "#" << m_UnitBasis->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_ApplicableDate ) { m_ApplicableDate->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_FixedUntilDate ) { m_FixedUntilDate->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_ImpactType ) { m_ImpactType->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Category ) { m_Category->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_UserDefinedCategory ) { m_UserDefinedCategory->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcEnvironmentalImpactValue::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcEnvironmentalImpactValue::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<9 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcEnvironmentalImpactValue, expecting 9, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>9 ){ std::cout << "Wrong parameter count for entity IfcEnvironmentalImpactValue, expecting 9, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Name = IfcLabel::readStepData( args[0] );
			m_Description = IfcText::readStepData( args[1] );
			m_AppliedValue = IfcAppliedValueSelect::readStepData( args[2], map );
			readEntityReference( args[3], m_UnitBasis, map );
			m_ApplicableDate = IfcDateTimeSelect::readStepData( args[4], map );
			m_FixedUntilDate = IfcDateTimeSelect::readStepData( args[5], map );
			m_ImpactType = IfcLabel::readStepData( args[6] );
			m_Category = IfcEnvironmentalImpactCategoryEnum::readStepData( args[7] );
			m_UserDefinedCategory = IfcLabel::readStepData( args[8] );
		}
		void IfcEnvironmentalImpactValue::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			IfcAppliedValue::setInverseCounterparts( ptr_self_entity );
		}
		void IfcEnvironmentalImpactValue::unlinkSelf()
		{
			IfcAppliedValue::unlinkSelf();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
