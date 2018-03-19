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
#include "IfcSectionedSpine.h"
#include "IfcCompositeCurve.h"
#include "IfcProfileDef.h"
#include "IfcAxis2Placement3D.h"
namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
			// ENTITY IfcSectionedSpine
			IfcSectionedSpine::IfcSectionedSpine() { m_entity_enum = IFCSECTIONEDSPINE;}
			IfcSectionedSpine::IfcSectionedSpine( int id ) { m_id = id; m_entity_enum = IFCSECTIONEDSPINE;}
			IfcSectionedSpine::~IfcSectionedSpine() {}

			// method setEntity takes over all attributes from another instance of the class
			void IfcSectionedSpine::setEntity( std::shared_ptr<IfcAlignment1x1Entity> other_entity)
			{
				std::shared_ptr<IfcSectionedSpine> other = std::dynamic_pointer_cast<IfcSectionedSpine>(other_entity);
				if( !other) { return; }
				m_SpineCurve = other->m_SpineCurve;
				m_CrossSections = other->m_CrossSections;
				m_CrossSectionPositions = other->m_CrossSectionPositions;
			}
			void IfcSectionedSpine::getStepLine( std::stringstream& stream ) const
			{
				stream << "#" << m_id << "=IFCSECTIONEDSPINE" << "(";
				if( m_SpineCurve) { stream << "#" << m_SpineCurve->getId(); } else { stream << "$"; }
				stream << ",";
				writeEntityList( stream, m_CrossSections );
				stream << ",";
				writeEntityList( stream, m_CrossSectionPositions );
				stream << ");";
			}
			void IfcSectionedSpine::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
			void IfcSectionedSpine::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
			{
				const int num_args = (int)args.size();
				if( num_args<3 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcSectionedSpine, expecting 3, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcAlignment1x1Exception( strserr.str().c_str() ); }
				#ifdef _DEBUG
				if( num_args<3 ){ std::cout << "Wrong parameter count for entity IfcSectionedSpine, expecting 3, having " << num_args << ". Object id: " << getId() << std::endl; }
				#endif
				readEntityReference( args[0], m_SpineCurve, map);
				readEntityReferenceList( args[1], m_CrossSections , map);
				readEntityReferenceList( args[2], m_CrossSectionPositions , map);
			}
			void IfcSectionedSpine::setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self_entity)
			{
				IfcGeometricRepresentationItem::setInverseCounterparts(ptr_self_entity);
			}
			void IfcSectionedSpine::unlinkSelf()
			{
				IfcGeometricRepresentationItem::unlinkSelf();
			}
	}
}
