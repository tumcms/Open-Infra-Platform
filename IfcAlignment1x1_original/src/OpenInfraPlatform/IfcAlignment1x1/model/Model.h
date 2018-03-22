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

#pragma once

#include <vector>
#include <map>
#include <string>
#include "shared_ptr.h"
#include "OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1Entities.h"
#include "OpenInfraPlatform/IfcAlignment1x1/entity/IfcGeometricRepresentationContext.h"
#include "OpenInfraPlatform/IfcAlignment1x1/model/UnitConverter.h"
#include "OpenInfraPlatform/IfcAlignment1x1/entity/IfcProject.h"

namespace OpenInfraPlatform
{
    namespace IfcAlignment1x1
    {
        //class IfcAlignment1x1Entity;
        //class IfcProject;
        //class IfcGeometricRepresentationContext;
        //class UnitConverter;

        class IfcAlignment1x1Model
        {
        public:
            IfcAlignment1x1Model();
            ~IfcAlignment1x1Model();

            enum IfcVersion { UNDEFINED, UNKNOWN, IFC2X, IFC2X2, IFC2X3, IFC2X4, IfcAlignment1x1, Ifc4, Ifc4x1 };

            const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& getMapIfcObjects() const
            {
                return m_map_entities;
            }
            void insertEntity( shared_ptr<IfcAlignment1x1Entity> e, bool overwrite_existing = false );
            void removeEntity( shared_ptr<IfcAlignment1x1Entity> e );
            void removeEntity( int entity_id );
            int getMaxUsedEntityId();
            shared_ptr<IfcProject> getIfcProject();
            shared_ptr<IfcGeometricRepresentationContext> getIfcGeometricRepresentationContext3D();
            std::string getFileHeader()
            {
                return m_file_header;
            }
            std::string getFileSchema()
            {
                return m_file_schema;
            }
            shared_ptr<UnitConverter> getUnitConverter()
            {
                return m_unit_converter;
            }

            void setFileHeader( std::string header );
            void setFileSchema( std::string schema );
            void setIfcProject( shared_ptr<IfcProject> project );
            void resolveInverseAttributes();
            void clearIfcModel();
            void initIfcModel();
            void resetIfcModel();
            void updateCache();
            void clearCache();
            void initFileHeader( std::string file_name );

        private:
            std::map<int,shared_ptr<IfcAlignment1x1Entity> >		m_map_entities;
            shared_ptr<IfcProject>							m_ifc_project;
            shared_ptr<IfcGeometricRepresentationContext>	m_geom_context_3d;
            shared_ptr<UnitConverter>						m_unit_converter;
            std::string										m_file_header;
            std::string										m_file_schema;
        };
    } // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
