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

#include "OpenInfraPlatform/Ifc4/model/Ifc4Exception.h"
#include "OpenInfraPlatform/Ifc4/reader/ReaderUtil.h"
#include "OpenInfraPlatform/Ifc4/writer/WriterUtil.h"
#include "OpenInfraPlatform/Ifc4/Ifc4EntityEnums.h"
#include "include/IfcComplexProperty.h"
#include "include/IfcCurveInterpolationEnum.h"
#include "include/IfcExternalReferenceRelationship.h"
#include "include/IfcIdentifier.h"
#include "include/IfcPropertyDependencyRelationship.h"
#include "include/IfcPropertySet.h"
#include "include/IfcPropertyTableValue.h"
#include "include/IfcResourceApprovalRelationship.h"
#include "include/IfcResourceConstraintRelationship.h"
#include "include/IfcText.h"
#include "include/IfcUnit.h"
#include "include/IfcValue.h"

namespace OpenInfraPlatform
{
	namespace Ifc4
	{
		// ENTITY IfcPropertyTableValue 
		IfcPropertyTableValue::IfcPropertyTableValue() { m_entity_enum = IFCPROPERTYTABLEVALUE; }
		IfcPropertyTableValue::IfcPropertyTableValue( int id ) { m_id = id; m_entity_enum = IFCPROPERTYTABLEVALUE; }
		IfcPropertyTableValue::~IfcPropertyTableValue() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcPropertyTableValue::setEntity( shared_ptr<Ifc4Entity> other_entity )
		{
			shared_ptr<IfcPropertyTableValue> other = dynamic_pointer_cast<IfcPropertyTableValue>(other_entity);
			if( !other) { return; }
			m_Name = other->m_Name;
			m_Description = other->m_Description;
			m_DefiningValues = other->m_DefiningValues;
			m_DefinedValues = other->m_DefinedValues;
			m_Expression = other->m_Expression;
			m_DefiningUnit = other->m_DefiningUnit;
			m_DefinedUnit = other->m_DefinedUnit;
			m_CurveInterpolation = other->m_CurveInterpolation;
		}
		void IfcPropertyTableValue::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCPROPERTYTABLEVALUE" << "(";
			if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			writeTypeList( stream, m_DefiningValues, true );
			stream << ",";
			writeTypeList( stream, m_DefinedValues, true );
			stream << ",";
			if( m_Expression ) { m_Expression->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_DefiningUnit ) { m_DefiningUnit->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_DefinedUnit ) { m_DefinedUnit->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_CurveInterpolation ) { m_CurveInterpolation->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcPropertyTableValue::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcPropertyTableValue::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc4Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<8 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcPropertyTableValue, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc4Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>8 ){ std::cout << "Wrong parameter count for entity IfcPropertyTableValue, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_Name = IfcIdentifier::readStepData( args[0] );
			m_Description = IfcText::readStepData( args[1] );
			readSelectList( args[2], m_DefiningValues, map );
			readSelectList( args[3], m_DefinedValues, map );
			m_Expression = IfcText::readStepData( args[4] );
			m_DefiningUnit = IfcUnit::readStepData( args[5], map );
			m_DefinedUnit = IfcUnit::readStepData( args[6], map );
			m_CurveInterpolation = IfcCurveInterpolationEnum::readStepData( args[7] );
		}
		void IfcPropertyTableValue::setInverseCounterparts( shared_ptr<Ifc4Entity> ptr_self_entity )
		{
			IfcSimpleProperty::setInverseCounterparts( ptr_self_entity );
		}
		void IfcPropertyTableValue::unlinkSelf()
		{
			IfcSimpleProperty::unlinkSelf();
		}
	} // end namespace Ifc4
} // end namespace OpenInfraPlatform
