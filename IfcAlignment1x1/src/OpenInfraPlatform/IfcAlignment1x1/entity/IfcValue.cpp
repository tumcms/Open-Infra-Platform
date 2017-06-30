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

#include "IfcValue.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

#include "IfcReal.h"
#include "IfcLabel.h"
#include "IfcAreaMeasure.h"
#include "IfcMassMeasure.h"
#include "IfcLengthMeasure.h"
#include "IfcPlaneAngleMeasure.h"
#include "IfcPressureMeasure.h"
#include "IfcThermodynamicTemperatureMeasure.h"
#include "IfcVolumeMeasure.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcValue::IfcValue() {}
		IfcValue::~IfcValue() {}
		std::shared_ptr<IfcValue> IfcValue::readStepData(const std::string& arg, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map)
		{
			// Read SELECT TYPE
			if( arg.size() == 0 ) { return std::shared_ptr<IfcValue>(); }
			if( arg[0] == '#' )
			{
				int id=atoi( arg.substr(1,arg.length()-1).c_str() );
				std::map<int,shared_ptr<IfcAlignment1x1Entity> >::const_iterator it_entity = map.find( id );
				if( it_entity != map.end() )
				{
					shared_ptr<IfcValue> type_object = dynamic_pointer_cast<IfcValue>(it_entity->second);
					return type_object;
				}
				else
				{
					std::stringstream strs;
					strs << "Object width id " << id << " not found";
					throw IfcAlignment1x1Exception( strs.str() );
				}
			}
			else if( arg.compare("$")==0 )
			{
				return shared_ptr<IfcValue>();
			}
			else if( arg.compare("*")==0 )
			{
				return shared_ptr<IfcValue>();
			}
			else
			{
				// inline arguments
				std::string keyword;
				std::string inline_arg;
				tokenizeInlineArgument( arg, keyword, inline_arg );

				if (keyword == "IFCREAL") {
					return std::make_shared<IfcReal>(atof(inline_arg.c_str()));
				} else if (keyword == "IFCLABEL") {
					return std::make_shared<IfcLabel>(inline_arg);
				} else if (keyword == "IFCAREAMEASURE") {
					return std::make_shared<IfcAreaMeasure>(atof(inline_arg.c_str()));
				} else if (keyword == "IFCMASSMEASURE") {
					return std::make_shared<IfcMassMeasure>(atof(inline_arg.c_str()));
				} else if (keyword == "IFCLENGTHMEASURE") {
					return std::make_shared<IfcLengthMeasure>(atof(inline_arg.c_str()));
				} else if (keyword == "IFCPLANEANGLEMEASURE") {
					return std::make_shared<IfcPlaneAngleMeasure>(atof(inline_arg.c_str()));
				} else if (keyword == "IFCPRESSUREMEASURE") {
					return std::make_shared<IfcPressureMeasure>(atof(inline_arg.c_str()));
				} else if (keyword == "IFCTHERMODYNAMICTEMPERATUREMEASURE") {
					return std::make_shared<IfcThermodynamicTemperatureMeasure>(atof(inline_arg.c_str()));
				} else if (keyword == "IFCVOLUMEMEASURE") {
					return std::make_shared<IfcVolumeMeasure>(atof(inline_arg.c_str()));
				}

				std::stringstream strs;
				strs << "unhandled inline argument: " << arg << " in function IfcAlignment1x1::IfcValue::readStepData" << std::endl;
				throw IfcAlignment1x1Exception( strs.str() );
			}
			return shared_ptr<IfcValue>();
		}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
