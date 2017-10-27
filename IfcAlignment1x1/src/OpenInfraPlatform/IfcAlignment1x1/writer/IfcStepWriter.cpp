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

#include "model/shared_ptr.h"
#include "model/Object.h"
#include "model/Model.h"
#include "entity/IfcProduct.h"
#include "entity/IfcProject.h"
#include "writer/IfcStepWriter.h"
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include <locale.h>

#include <fstream>

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcStepWriter::IfcStepWriter()
		{
		}

		IfcStepWriter::~IfcStepWriter()
		{
		}

		void IfcStepWriter::writeStream( std::stringstream& stream, shared_ptr<IfcAlignment1x1Model> model )
		{
			char* current_numeric_locale = setlocale(LC_NUMERIC, NULL);
			setlocale(LC_NUMERIC,"C");

			stream << model->getFileHeader().c_str();
			stream << "DATA;\n";
			stream << std::setprecision(20);
			stream << std::showpoint;
			const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map = model->getMapIfcObjects();
			std::map<int,shared_ptr<IfcAlignment1x1Entity> >::const_iterator it;
			for( it=map.begin(); it!=map.end(); ++it )
			{
				shared_ptr<IfcAlignment1x1Entity> obj = it->second;

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

		// https://stackoverflow.com/questions/2896600/how-to-replace-all-occurrences-of-a-character-in-string
		std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
			size_t start_pos = 0;
			while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
				str.replace(start_pos, from.length(), to);
				start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
			}
			return str;
		}

		void IfcStepWriter::write(const std::string& filename, shared_ptr<IfcAlignment1x1Model> model)
		{
			shared_ptr<IfcStepWriter> step_writer = shared_ptr<IfcStepWriter>(new IfcStepWriter());
			std::stringstream stream;

			// write file header
			{
				std::stringstream strs;
				strs << "ISO-10303-21;" << std::endl;
				strs << "HEADER;" << std::endl;
				strs << "FILE_DESCRIPTION(('" << "IFC4X1" << "'),'2;1');" << std::endl;

				std::string filenameWithoutEscapeSequences = ReplaceAll(filename, "\\", "/");

				strs << "FILE_NAME('" << filenameWithoutEscapeSequences.c_str() << "','";

				// 2011-04-21T14:25:12
				time_t rawtime;
				struct tm timeinfo;
				time(&rawtime);

#ifdef _WIN32
				errno_t err_time;
				err_time = localtime_s(&timeinfo, &rawtime);
#else
				timeinfo = localtime(&rawtime);
#endif

				char buffer[80];
				strftime(buffer, 80, "%Y-%m-%dT%H:%M:%S", &timeinfo);
				strs << buffer;

				strs << "',(''),('',''),'','IfcAlignment','');" << std::endl;
				strs << "FILE_SCHEMA(('" << "IFC4X1" << "'));" << std::endl;
				strs << "ENDSEC;" << std::endl;

				model->setFileHeader(strs.str());
			}


			step_writer->writeStream(stream, model);

			std::ofstream textFile(filename.c_str());
			textFile << stream.str().c_str();
		}

	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
