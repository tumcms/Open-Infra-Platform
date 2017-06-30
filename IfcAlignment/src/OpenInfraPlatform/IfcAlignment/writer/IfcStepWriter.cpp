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

#include "OpenInfraPlatform/IfcAlignment/model/shared_ptr.h"
#include "OpenInfraPlatform/IfcAlignment/model/IfcAlignmentP6Object.h"
#include "OpenInfraPlatform/IfcAlignment/model/IfcAlignmentP6Model.h"
#include "OpenInfraPlatform/IfcAlignment/entity/include/IfcProduct.h"
#include "OpenInfraPlatform/IfcAlignment/entity/include/IfcProject.h"
#include "OpenInfraPlatform/IfcAlignment/writer/IfcStepWriter.h"
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include <locale.h>

namespace OpenInfraPlatform
{
    namespace IfcAlignment
    {
        IfcStepWriter::IfcStepWriter()
        {
        }

        IfcStepWriter::~IfcStepWriter()
        {
        }

        void IfcStepWriter::writeStream( std::stringstream& stream, shared_ptr<IfcAlignmentModel> model )
        {
            char* current_numeric_locale = setlocale(LC_NUMERIC, nullptr);
            setlocale(LC_NUMERIC,"C");
			
            stream << model->getFileHeader().c_str();
            stream << "DATA;\n";
			stream << std::setprecision(20);
			stream << std::showpoint;
            const std::map<int,shared_ptr<IfcAlignmentP6Entity> >& map = model->getMapIfcObjects();
            std::map<int,shared_ptr<IfcAlignmentP6Entity> >::const_iterator it;
            for( it=map.begin(); it!=map.end(); ++it )
            {
                shared_ptr<IfcAlignmentP6Entity> obj = it->second;

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
    } // end namespace IfcAlignment
} // end namespace OpenInfraPlatform
