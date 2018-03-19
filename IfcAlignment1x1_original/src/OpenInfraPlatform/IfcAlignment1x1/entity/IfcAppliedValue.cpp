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
#include "IfcAppliedValue.h"
#include "IfcLabel.h"
#include "IfcText.h"
#include "IfcAppliedValueSelect.h"
#include "IfcMeasureWithUnit.h"
#include "IfcDate.h"
#include "IfcDate.h"
#include "IfcLabel.h"
#include "IfcLabel.h"
#include "IfcArithmeticOperatorEnum.h"
#include "IfcAppliedValue.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcAppliedValue
			IfcAppliedValue::IfcAppliedValue() { m_entity_enum = IFCAPPLIEDVALUE;}
			IfcAppliedValue::IfcAppliedValue( int id ) { m_id = id; m_entity_enum = IFCAPPLIEDVALUE;}
			IfcAppliedValue::~IfcAppliedValue() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcAppliedValue::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcAppliedValue> other = std::dynamic_pointer_cast<IfcAppliedValue>(other_entity);
				if( !other) { return; }
				m_Name = other->m_Name;
				m_Description = other->m_Description;
				m_AppliedValue = other->m_AppliedValue;
				m_UnitBasis = other->m_UnitBasis;
				m_ApplicableDate = other->m_ApplicableDate;
				m_FixedUntilDate = other->m_FixedUntilDate;
				m_Category = other->m_Category;
				m_Condition = other->m_Condition;
				m_ArithmeticOperator = other->m_ArithmeticOperator;
				m_Components = other->m_Components;
			}
			void IfcAppliedValue::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCAPPLIEDVALUE" << "(";
				if( m_Name) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Description) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_AppliedValue) { m_AppliedValue->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_UnitBasis) { stream << "#" << m_UnitBasis->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_ApplicableDate) { m_ApplicableDate->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_FixedUntilDate) { m_FixedUntilDate->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Category) { m_Category->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Condition) { m_Condition->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_ArithmeticOperator) { m_ArithmeticOperator->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				writeEntityList( stream, m_Components );
				stream << ");";
			}
			void IfcAppliedValue::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcAppliedValue::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<10 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcAppliedValue, expecting 10, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<10 ){ std::cout << "Wrong parameter count for entity IfcAppliedValue, expecting 10, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				m_Name = IfcLabel::readStepData( args[0] );
				m_Description = IfcText::readStepData( args[1] );
				m_AppliedValue = IfcAppliedValueSelect::readStepData( args[2], map );
				readEntityReference( args[3], m_UnitBasis, map);
				m_ApplicableDate = IfcDate::readStepData( args[4] );
				m_FixedUntilDate = IfcDate::readStepData( args[5] );
				m_Category = IfcLabel::readStepData( args[6] );
				m_Condition = IfcLabel::readStepData( args[7] );
				m_ArithmeticOperator = IfcArithmeticOperatorEnum::readStepData( args[8] );
				readEntityReferenceList( args[9], m_Components , map);
			}
			void IfcAppliedValue::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
			}
			void IfcAppliedValue::unlinkSelf()
			{
			}
	}
}
