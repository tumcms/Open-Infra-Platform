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

#include <map>
#include "OpenInfraPlatform/Ifc4/model/shared_ptr.h"
#include "OpenInfraPlatform/Ifc4/model/Ifc4Exception.h"
#include "OpenInfraPlatform/Ifc4/reader/ReaderUtil.h"
#include "include/IfcAmountOfSubstanceMeasure.h"
#include "include/IfcAreaMeasure.h"
#include "include/IfcComplexNumber.h"
#include "include/IfcContextDependentMeasure.h"
#include "include/IfcCountMeasure.h"
#include "include/IfcDescriptiveMeasure.h"
#include "include/IfcElectricCurrentMeasure.h"
#include "include/IfcLengthMeasure.h"
#include "include/IfcLuminousIntensityMeasure.h"
#include "include/IfcMassMeasure.h"
#include "include/IfcNonNegativeLengthMeasure.h"
#include "include/IfcNormalisedRatioMeasure.h"
#include "include/IfcNumericMeasure.h"
#include "include/IfcParameterValue.h"
#include "include/IfcPlaneAngleMeasure.h"
#include "include/IfcPositiveLengthMeasure.h"
#include "include/IfcPositivePlaneAngleMeasure.h"
#include "include/IfcPositiveRatioMeasure.h"
#include "include/IfcRatioMeasure.h"
#include "include/IfcSolidAngleMeasure.h"
#include "include/IfcThermodynamicTemperatureMeasure.h"
#include "include/IfcTimeMeasure.h"
#include "include/IfcVolumeMeasure.h"
#include "include/IfcValue.h"
#include "include/IfcMeasureValue.h"

namespace OpenInfraPlatform
{
	namespace Ifc4
	{
		// TYPE IfcMeasureValue 
		IfcMeasureValue::IfcMeasureValue() {}
		IfcMeasureValue::~IfcMeasureValue() {}
		shared_ptr<IfcMeasureValue> IfcMeasureValue::readStepData( std::string& arg, const std::map<int,shared_ptr<Ifc4Entity> >& map )
		{
			// Read SELECT TYPE
			if( arg.size() == 0 ){ return shared_ptr<IfcMeasureValue>(); }
			if( arg[0] == '#' )
			{
				int id=atoi( arg.substr(1,arg.length()-1).c_str() );
				std::map<int,shared_ptr<Ifc4Entity> >::const_iterator it_entity = map.find( id );
				if( it_entity != map.end() )
				{
					shared_ptr<IfcMeasureValue> type_object = dynamic_pointer_cast<IfcMeasureValue>(it_entity->second);
					return type_object;
				}
				else
				{
					std::stringstream strs;
					strs << "Object width id " << id << " not found";
					throw Ifc4Exception( strs.str() );
				}
			}
			else if( arg.compare("$")==0 )
			{
				return shared_ptr<IfcMeasureValue>();
			}
			else if( arg.compare("*")==0 )
			{
				return shared_ptr<IfcMeasureValue>();
			}
			else
			{
				// inline arguments
				std::string keyword;
				std::string inline_arg;
				tokenizeInlineArgument( arg, keyword, inline_arg );
				if( keyword.compare("IFCAMOUNTOFSUBSTANCEMEASURE")== 0 )
				{
					return IfcAmountOfSubstanceMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCAREAMEASURE")== 0 )
				{
					return IfcAreaMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCCOMPLEXNUMBER")== 0 )
				{
					return IfcComplexNumber::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCCONTEXTDEPENDENTMEASURE")== 0 )
				{
					return IfcContextDependentMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCCOUNTMEASURE")== 0 )
				{
					return IfcCountMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCDESCRIPTIVEMEASURE")== 0 )
				{
					return IfcDescriptiveMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCELECTRICCURRENTMEASURE")== 0 )
				{
					return IfcElectricCurrentMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCLENGTHMEASURE")== 0 )
				{
					return IfcLengthMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCLUMINOUSINTENSITYMEASURE")== 0 )
				{
					return IfcLuminousIntensityMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCMASSMEASURE")== 0 )
				{
					return IfcMassMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCNONNEGATIVELENGTHMEASURE")== 0 )
				{
					return IfcNonNegativeLengthMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCNORMALISEDRATIOMEASURE")== 0 )
				{
					return IfcNormalisedRatioMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCNUMERICMEASURE")== 0 )
				{
					return IfcNumericMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCPARAMETERVALUE")== 0 )
				{
					return IfcParameterValue::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCPLANEANGLEMEASURE")== 0 )
				{
					return IfcPlaneAngleMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCPOSITIVELENGTHMEASURE")== 0 )
				{
					return IfcPositiveLengthMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCPOSITIVEPLANEANGLEMEASURE")== 0 )
				{
					return IfcPositivePlaneAngleMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCPOSITIVERATIOMEASURE")== 0 )
				{
					return IfcPositiveRatioMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCRATIOMEASURE")== 0 )
				{
					return IfcRatioMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCSOLIDANGLEMEASURE")== 0 )
				{
					return IfcSolidAngleMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCTHERMODYNAMICTEMPERATUREMEASURE")== 0 )
				{
					return IfcThermodynamicTemperatureMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCTIMEMEASURE")== 0 )
				{
					return IfcTimeMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCVOLUMEMEASURE")== 0 )
				{
					return IfcVolumeMeasure::readStepData( inline_arg );
				}
				std::stringstream strs;
				strs << "unhandled inline argument: " << arg << " in function IFC4::IfcMeasureValue::readStepData" << std::endl;
				throw Ifc4Exception( strs.str() );
			}
			return shared_ptr<IfcMeasureValue>();
		}
	} // end namespace Ifc4
} // end namespace OpenInfraPlatform
