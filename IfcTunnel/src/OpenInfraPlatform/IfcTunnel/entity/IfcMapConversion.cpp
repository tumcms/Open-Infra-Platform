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

#include "model/IfcTunnelException.h"
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "IfcTunnelEntityEnums.h"
#include "include/IfcCoordinateReferenceSystem.h"
#include "include/IfcCoordinateReferenceSystemSelect.h"
#include "include/IfcLengthMeasure.h"
#include "include/IfcMapConversion.h"
#include "include/IfcReal.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		// ENTITY IfcMapConversion 
		IfcMapConversion::IfcMapConversion() { m_entity_enum = IFCMAPCONVERSION; }
		IfcMapConversion::IfcMapConversion( int id ) { m_id = id; m_entity_enum = IFCMAPCONVERSION; }
		IfcMapConversion::~IfcMapConversion() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcMapConversion::setEntity( shared_ptr<IfcTunnelEntity> other_entity )
		{
			shared_ptr<IfcMapConversion> other = dynamic_pointer_cast<IfcMapConversion>(other_entity);
			if( !other) { return; }
			m_SourceCRS = other->m_SourceCRS;
			m_TargetCRS = other->m_TargetCRS;
			m_Eastings = other->m_Eastings;
			m_Northings = other->m_Northings;
			m_OrthogonalHeight = other->m_OrthogonalHeight;
			m_XAxisAbscissa = other->m_XAxisAbscissa;
			m_XAxisOrdinate = other->m_XAxisOrdinate;
			m_Scale = other->m_Scale;
		}
		void IfcMapConversion::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCMAPCONVERSION" << "(";
			if( m_SourceCRS ) { m_SourceCRS->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_TargetCRS ) { stream << "#" << m_TargetCRS->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Eastings ) { m_Eastings->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Northings ) { m_Northings->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_OrthogonalHeight ) { m_OrthogonalHeight->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_XAxisAbscissa ) { m_XAxisAbscissa->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_XAxisOrdinate ) { m_XAxisOrdinate->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_Scale ) { m_Scale->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcMapConversion::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcMapConversion::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcTunnelEntity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<8 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcMapConversion, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcTunnelException( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>8 ){ std::cout << "Wrong parameter count for entity IfcMapConversion, expecting 8, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			m_SourceCRS = IfcCoordinateReferenceSystemSelect::readStepData( args[0], map );
			readEntityReference( args[1], m_TargetCRS, map );
			m_Eastings = IfcLengthMeasure::readStepData( args[2] );
			m_Northings = IfcLengthMeasure::readStepData( args[3] );
			m_OrthogonalHeight = IfcLengthMeasure::readStepData( args[4] );
			m_XAxisAbscissa = IfcReal::readStepData( args[5] );
			m_XAxisOrdinate = IfcReal::readStepData( args[6] );
			m_Scale = IfcReal::readStepData( args[7] );
		}
		void IfcMapConversion::setInverseCounterparts( shared_ptr<IfcTunnelEntity> ptr_self_entity )
		{
			IfcCoordinateOperation::setInverseCounterparts( ptr_self_entity );
		}
		void IfcMapConversion::unlinkSelf()
		{
			IfcCoordinateOperation::unlinkSelf();
		}
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform
