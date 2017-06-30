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
#include "include/IfcColourOrFactor.h"
#include "include/IfcColourRgb.h"
#include "include/IfcNormalisedRatioMeasure.h"
#include "include/IfcReflectanceMethodEnum.h"
#include "include/IfcSpecularHighlightSelect.h"
#include "include/IfcSurfaceStyleRendering.h"

namespace OpenInfraPlatform
{
	namespace Ifc4
	{
		// ENTITY IfcSurfaceStyleRendering 
		IfcSurfaceStyleRendering::IfcSurfaceStyleRendering() { m_entity_enum = IFCSURFACESTYLERENDERING; }
		IfcSurfaceStyleRendering::IfcSurfaceStyleRendering( int id ) { m_id = id; m_entity_enum = IFCSURFACESTYLERENDERING; }
		IfcSurfaceStyleRendering::~IfcSurfaceStyleRendering() {}

		// method setEntity takes over all attributes from another instance of the class
		void IfcSurfaceStyleRendering::setEntity( shared_ptr<Ifc4Entity> other_entity )
		{
			shared_ptr<IfcSurfaceStyleRendering> other = dynamic_pointer_cast<IfcSurfaceStyleRendering>(other_entity);
			if( !other) { return; }
			m_SurfaceColour = other->m_SurfaceColour;
			m_Transparency = other->m_Transparency;
			m_DiffuseColour = other->m_DiffuseColour;
			m_TransmissionColour = other->m_TransmissionColour;
			m_DiffuseTransmissionColour = other->m_DiffuseTransmissionColour;
			m_ReflectionColour = other->m_ReflectionColour;
			m_SpecularColour = other->m_SpecularColour;
			m_SpecularHighlight = other->m_SpecularHighlight;
			m_ReflectanceMethod = other->m_ReflectanceMethod;
		}
		void IfcSurfaceStyleRendering::getStepLine( std::stringstream& stream ) const
		{
			stream << "#" << m_id << "=IFCSURFACESTYLERENDERING" << "(";
			if( m_SurfaceColour ) { stream << "#" << m_SurfaceColour->getId(); } else { stream << "$"; }
			stream << ",";
			if( m_Transparency ) { m_Transparency->getStepParameter( stream ); } else { stream << "$"; }
			stream << ",";
			if( m_DiffuseColour ) { m_DiffuseColour->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_TransmissionColour ) { m_TransmissionColour->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_DiffuseTransmissionColour ) { m_DiffuseTransmissionColour->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_ReflectionColour ) { m_ReflectionColour->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_SpecularColour ) { m_SpecularColour->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_SpecularHighlight ) { m_SpecularHighlight->getStepParameter( stream, true ); } else { stream << "$"; }
			stream << ",";
			if( m_ReflectanceMethod ) { m_ReflectanceMethod->getStepParameter( stream ); } else { stream << "$"; }
			stream << ");";
		}
		void IfcSurfaceStyleRendering::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
		void IfcSurfaceStyleRendering::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc4Entity> >& map )
		{
			const int num_args = (int)args.size();
			if( num_args<9 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcSurfaceStyleRendering, expecting 9, having " << num_args << ". Object id: " << getId() << std::endl; throw Ifc4Exception( strserr.str().c_str() ); }
			#ifdef _DEBUG
			if( num_args>9 ){ std::cout << "Wrong parameter count for entity IfcSurfaceStyleRendering, expecting 9, having " << num_args << ". Object id: " << getId() << std::endl; }
			#endif
			readEntityReference( args[0], m_SurfaceColour, map );
			m_Transparency = IfcNormalisedRatioMeasure::readStepData( args[1] );
			m_DiffuseColour = IfcColourOrFactor::readStepData( args[2], map );
			m_TransmissionColour = IfcColourOrFactor::readStepData( args[3], map );
			m_DiffuseTransmissionColour = IfcColourOrFactor::readStepData( args[4], map );
			m_ReflectionColour = IfcColourOrFactor::readStepData( args[5], map );
			m_SpecularColour = IfcColourOrFactor::readStepData( args[6], map );
			m_SpecularHighlight = IfcSpecularHighlightSelect::readStepData( args[7], map );
			m_ReflectanceMethod = IfcReflectanceMethodEnum::readStepData( args[8] );
		}
		void IfcSurfaceStyleRendering::setInverseCounterparts( shared_ptr<Ifc4Entity> ptr_self_entity )
		{
			IfcSurfaceStyleShading::setInverseCounterparts( ptr_self_entity );
		}
		void IfcSurfaceStyleRendering::unlinkSelf()
		{
			IfcSurfaceStyleShading::unlinkSelf();
		}
	} // end namespace Ifc4
} // end namespace OpenInfraPlatform
