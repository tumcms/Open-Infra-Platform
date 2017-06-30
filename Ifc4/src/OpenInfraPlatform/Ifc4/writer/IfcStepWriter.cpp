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

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <locale.h>
#include "model/shared_ptr.h"
#include "model/Ifc4Object.h"
#include "model/Ifc4Model.h"
#include "entity/include/IfcProduct.h"
#include "entity/include/IfcProject.h"
#include "writer/IfcStepWriter.h"

namespace OpenInfraPlatform
{
    namespace Ifc4
    {
        IfcStepWriter::IfcStepWriter()
        {
        }

        IfcStepWriter::~IfcStepWriter()
        {
        }

        void IfcStepWriter::writeStream( std::stringstream& stream, shared_ptr<Ifc4Model> model )
        {
            char* current_numeric_locale = setlocale(LC_NUMERIC, NULL);
            setlocale(LC_NUMERIC,"C");

            stream << model->getFileHeader().c_str();
            stream << "DATA;\n";

            const std::map<int,shared_ptr<Ifc4Entity> >& map = model->getMapIfcObjects();
            std::map<int,shared_ptr<Ifc4Entity> >::const_iterator it;
            for( it=map.begin(); it!=map.end(); ++it )
            {
                shared_ptr<Ifc4Entity> obj = it->second;

                if( obj.use_count() < 2 )
                {
                    // entity is referenced only in model map, not by other entities
                    if( !dynamic_pointer_cast<IfcProduct>(obj) && !dynamic_pointer_cast<IfcProject>(obj) )
                    {
                        continue;
                    }
                }
                obj->getStepLine( stream );
                stream << std::endl;
            }

            stream << "ENDSEC;\nEND-ISO-10303-21;\n";

            setlocale(LC_NUMERIC, current_numeric_locale);
        }
    } // end namespace Ifc4
} // end namespace OpenInfraPlatform
