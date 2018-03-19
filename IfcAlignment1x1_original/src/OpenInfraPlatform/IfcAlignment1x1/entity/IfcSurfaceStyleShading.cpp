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
#include "IfcSurfaceStyleShading.h"
#include "IfcColourRgb.h"
#include "IfcNormalisedRatioMeasure.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcSurfaceStyleShading
			IfcSurfaceStyleShading::IfcSurfaceStyleShading() { m_entity_enum = IFCSURFACESTYLESHADING;}
			IfcSurfaceStyleShading::IfcSurfaceStyleShading( int id ) { m_id = id; m_entity_enum = IFCSURFACESTYLESHADING;}
			IfcSurfaceStyleShading::~IfcSurfaceStyleShading() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcSurfaceStyleShading::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcSurfaceStyleShading> other = std::dynamic_pointer_cast<IfcSurfaceStyleShading>(other_entity);
				if( !other) { return; }
				m_SurfaceColour = other->m_SurfaceColour;
				m_Transparency = other->m_Transparency;
			}
			void IfcSurfaceStyleShading::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCSURFACESTYLESHADING" << "(";
				if( m_SurfaceColour) { stream << "#" << m_SurfaceColour->getId(); } else { stream << "$"; }
				stream << ",";
				if( m_Transparency) { m_Transparency->getStepParameter( stream ); } else { stream << "$"; }
				stream << ");";
			}
			void IfcSurfaceStyleShading::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcSurfaceStyleShading::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<2 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcSurfaceStyleShading, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<2 ){ std::cout << "Wrong parameter count for entity IfcSurfaceStyleShading, expecting 2, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				readEntityReference( args[0], m_SurfaceColour, map);
				m_Transparency = IfcNormalisedRatioMeasure::readStepData( args[1] );
			}
			void IfcSurfaceStyleShading::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcPresentationItem::setInverseCounterparts(ptr_self_entity);
			}
			void IfcSurfaceStyleShading::unlinkSelf()
			{
				IfcPresentationItem::unlinkSelf();
			}
	}
}
