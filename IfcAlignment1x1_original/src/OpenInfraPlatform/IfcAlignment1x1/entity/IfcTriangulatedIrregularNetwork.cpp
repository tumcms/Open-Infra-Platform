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
#include "IfcTriangulatedIrregularNetwork.h"
#include "IfcCartesianPointList3D.h"
#include "IfcParameterValue.h"
#include "IfcBoolean.h"
#include "IfcPositiveInteger.h"
#include "IfcPositiveInteger.h"
#include "IfcInteger.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcTriangulatedIrregularNetwork
			IfcTriangulatedIrregularNetwork::IfcTriangulatedIrregularNetwork() { m_entity_enum = IFCTRIANGULATEDIRREGULARNETWORK;}
			IfcTriangulatedIrregularNetwork::IfcTriangulatedIrregularNetwork( int id ) { m_id = id; m_entity_enum = IFCTRIANGULATEDIRREGULARNETWORK;}
			IfcTriangulatedIrregularNetwork::~IfcTriangulatedIrregularNetwork() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcTriangulatedIrregularNetwork::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcTriangulatedIrregularNetwork> other = std::dynamic_pointer_cast<IfcTriangulatedIrregularNetwork>(other_entity);
				if( !other) { return; }
				m_Coordinates = other->m_Coordinates;
				m_Normals = other->m_Normals;
				m_Closed = other->m_Closed;
				m_CoordIndex = other->m_CoordIndex;
				m_PnIndex = other->m_PnIndex;
				m_Flags = other->m_Flags;
			}
			void IfcTriangulatedIrregularNetwork::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCTRIANGULATEDIRREGULARNETWORK" << "(";
				if( m_Coordinates) { stream << "#" << m_Coordinates->getId(); } else { stream << "$"; }
				stream << ",";
				writeTypeOfRealList2D( stream, m_Normals );
				stream << ",";
				if( m_Closed) { m_Closed->getStepParameter( stream ); } else { stream << "$"; }
				stream << ",";
				writeTypeOfIntList2D( stream, m_CoordIndex );
				stream << ",";
				writeTypeList( stream, m_PnIndex );
				stream << ",";
				writeTypeList( stream, m_Flags );
				stream << ");";
			}
			void IfcTriangulatedIrregularNetwork::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcTriangulatedIrregularNetwork::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<6 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcTriangulatedIrregularNetwork, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<6 ){ std::cout << "Wrong parameter count for entity IfcTriangulatedIrregularNetwork, expecting 6, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				readEntityReference( args[0], m_Coordinates, map);
				readTypeOfRealList2D( args[1], m_Normals);
				m_Closed = IfcBoolean::readStepData( args[2] );
				readTypeOfIntList2D( args[3], m_CoordIndex);
				readTypeList( args[4], m_PnIndex );
				readTypeList( args[5], m_Flags );
			}
			void IfcTriangulatedIrregularNetwork::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcTriangulatedFaceSet::setInverseCounterparts(ptr_self_entity);
			}
			void IfcTriangulatedIrregularNetwork::unlinkSelf()
			{
				IfcTriangulatedFaceSet::unlinkSelf();
			}
	}
}
