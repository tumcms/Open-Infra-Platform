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
#include "include/IfcClassificationNotationSelect.h"
#include "include/IfcConstraint.h"
#include "include/IfcConstraintClassificationRelationship.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// ENTITY IfcConstraintClassificationRelationship 
		IfcConstraintClassificationRelationship::IfcConstraintClassificationRelationship() { m_entity_enum = IFCCONSTRAINTCLASSIFICATIONRELATIONSHIP; }
		IfcConstraintClassificationRelationship::IfcConstraintClassificationRelationship( int id ) { m_id = id; m_entity_enum = IFCCONSTRAINTCLASSIFICATIONRELATIONSHIP; }
		IfcConstraintClassificationRelationship::~IfcConstraintClassificationRelationship() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcConstraintClassificationRelationship::setEntity( shared_ptr<Ifc2x3Entity> other_entity )
		{
			shared_ptr<IfcConstraintClassificationRelationship> other = dynamic_pointer_cast<IfcConstraintClassificationRelationship>(other_entity);
			if( !other) { return; }
			m_ClassifiedConstraint = other->m_ClassifiedConstraint;
			m_RelatedClassifications = other->m_RelatedClassifications;
		}
		void IfcConstraintClassificationRelationship::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCCONSTRAINTCLASSIFICATIONRELATIONSHIP" << "(";
			if( m_ClassifiedConstraint ) { stream << "#" << m_ClassifiedConstraint->getId(); } else { stream << "$"; }
			stream << ",";
			writeTypeList( stream, m_RelatedClassifications, true );
			stream << ");";
		}
		void IfcConstraintClassificationRelationship::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcConstraintClassificationRelationship::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<2 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcConstraintClassificationRelationship, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc2x3Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>2 ){ std::cout << "Wrong parameter count for entity IfcConstraintClassificationRelationship, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readEntityReference( args[0], m_ClassifiedConstraint, map );
			readSelectList( args[1], m_RelatedClassifications, map );
		}
		void IfcConstraintClassificationRelationship::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self_entity )
		{
			shared_ptr<IfcConstraintClassificationRelationship> ptr_self = dynamic_pointer_cast<IfcConstraintClassificationRelationship>( ptr_self_entity );
			if( !ptr_self ) { throw Ifc2x3Exception( "IfcConstraintClassificationRelationship::setInverseCounterparts: type mismatch" ); }
			if( m_ClassifiedConstraint )
			{
				m_ClassifiedConstraint->m_ClassifiedAs_inverse.push_back( ptr_self );
			}
		}
		void IfcConstraintClassificationRelationship::unlinkSelf()
		{
			if( m_ClassifiedConstraint )
			{
				std::vector<weak_ptr<IfcConstraintClassificationRelationship> >& ClassifiedAs_inverse = m_ClassifiedConstraint->m_ClassifiedAs_inverse;
				std::vector<weak_ptr<IfcConstraintClassificationRelationship> >::iterator it_ClassifiedAs_inverse;
				for( it_ClassifiedAs_inverse = ClassifiedAs_inverse.begin(); it_ClassifiedAs_inverse != ClassifiedAs_inverse.end(); ++it_ClassifiedAs_inverse)
				{
					shared_ptr<IfcConstraintClassificationRelationship> self_candidate( *it_ClassifiedAs_inverse );
					if( self_candidate->getId() == this->getId() )
					{
						ClassifiedAs_inverse.erase( it_ClassifiedAs_inverse );
						break;
					}
				}
			}
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
