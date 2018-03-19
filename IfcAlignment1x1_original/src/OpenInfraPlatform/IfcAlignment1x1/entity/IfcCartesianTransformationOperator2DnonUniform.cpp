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
#include "IfcCartesianTransformationOperator2DnonUniform.h"
#include "IfcDirection.h"
#include "IfcDirection.h"
#include "IfcCartesianPoint.h"
#include "IfcReal.h"
#include "IfcReal.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcCartesianTransformationOperator2DnonUniform
			IfcCartesianTransformationOperator2DnonUniform::IfcCartesianTransformationOperator2DnonUniform() { m_entity_enum = IFCCARTESIANTRANSFORMATIONOPERATOR2DNONUNIFORM;}
			IfcCartesianTransformationOperator2DnonUniform::IfcCartesianTransformationOperator2DnonUniform( int id ) { m_id = id; m_entity_enum = IFCCARTESIANTRANSFORMATIONOPERATOR2DNONUNIFORM;}
			IfcCartesianTransformationOperator2DnonUniform::~IfcCartesianTransformationOperator2DnonUniform() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcCartesianTransformationOperator2DnonUniform::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcCartesianTransformationOperator2DnonUniform> other = std::dynamic_pointer_cast<IfcCartesianTransformationOperator2DnonUniform>(other_entity);
				if( !other) { return; }
				m_Axis1 = other->m_Axis1;
				m_Axis2 = other->m_Axis2;
				m_LocalOrigin = other->m_LocalOrigin;
				m_Scale = other->m_Scale;
				m_Scale2 = other->m_Scale2;
			}
			void IfcCartesianTransformationOperator2DnonUniform::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCCARTESIANTRANSFORMATIONOPERATOR2DNONUNIFORM" << "(";
				if( m_Axis1) { stream << "#" << m_Axis1->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Axis2) { stream << "#" << m_Axis2->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_LocalOrigin) { stream << "#" << m_LocalOrigin->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Scale) { m_Scale->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				if( m_Scale2) { m_Scale2->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcCartesianTransformationOperator2DnonUniform::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcCartesianTransformationOperator2DnonUniform::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<5 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcCartesianTransformationOperator2DnonUniform, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<5 ){ std::cout << "Wrong parameter count for entity IfcCartesianTransformationOperator2DnonUniform, expecting 5, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				readEntityReference( args[0], m_Axis1, map);
				readEntityReference( args[1], m_Axis2, map);
				readEntityReference( args[2], m_LocalOrigin, map);
				m_Scale = IfcReal::readStepData( args[3] );
				m_Scale2 = IfcReal::readStepData( args[4] );
			}
			void IfcCartesianTransformationOperator2DnonUniform::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcCartesianTransformationOperator2D::setInverseCounterparts(ptr_self_entity);
			}
			void IfcCartesianTransformationOperator2DnonUniform::unlinkSelf()
			{
				IfcCartesianTransformationOperator2D::unlinkSelf();
			}
	}
}
