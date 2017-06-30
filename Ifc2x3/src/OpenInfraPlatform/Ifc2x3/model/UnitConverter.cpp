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

#define _USE_MATH_DEFINES
#include <math.h>


#include "entity/include/IfcConversionBasedUnit.h"
#include "entity/include/IfcLabel.h"
#include "entity/include/IfcMeasureWithUnit.h"
#include "entity/include/IfcPlaneAngleMeasure.h"
#include "entity/include/IfcProject.h"
#include "entity/include/IfcRatioMeasure.h"
#include "entity/include/IfcSIUnit.h"
#include "entity/include/IfcSIUnitName.h"
#include "entity/include/IfcSIPrefix.h"
#include "entity/include/IfcUnitAssignment.h"
#include "entity/include/IfcUnitEnum.h"

#include "UnitConverter.h"

namespace OpenInfraPlatform
{
    namespace Ifc2x3
    {
        UnitConverter::UnitConverter()
        {
            m_length_unit_factor = 1.0;
            m_plane_angle_factor = 1.0; // defaulting to radian

            m_prefix_map[IfcSIPrefix::ENUM_EXA] = 1E18;
            m_prefix_map[IfcSIPrefix::ENUM_PETA] = 1E15;
            m_prefix_map[IfcSIPrefix::ENUM_TERA] = 1E12;
            m_prefix_map[IfcSIPrefix::ENUM_GIGA] = 1E9;
            m_prefix_map[IfcSIPrefix::ENUM_MEGA] = 1E6;
            m_prefix_map[IfcSIPrefix::ENUM_KILO] = 1E3;
            m_prefix_map[IfcSIPrefix::ENUM_HECTO] = 1E2;
            m_prefix_map[IfcSIPrefix::ENUM_DECA] = 1E1;
            m_prefix_map[IfcSIPrefix::ENUM_DECI] = 1E-1;
            m_prefix_map[IfcSIPrefix::ENUM_CENTI] = 1E-2;
            m_prefix_map[IfcSIPrefix::ENUM_MILLI] = 1E-3;
            m_prefix_map[IfcSIPrefix::ENUM_MICRO] = 1E-6;
            m_prefix_map[IfcSIPrefix::ENUM_NANO] = 1E-9;
            m_prefix_map[IfcSIPrefix::ENUM_PICO] = 1E-12;
            m_prefix_map[IfcSIPrefix::ENUM_FEMTO] = 1E-15;
            m_prefix_map[IfcSIPrefix::ENUM_ATTO] = 1E-18;
        }

        void UnitConverter::setIfcProject(shared_ptr<IfcProject> project)
        {
            m_length_unit_factor = 1.0;
            m_plane_angle_factor = 1.0; // defaulting to radian

            if( !project->m_UnitsInContext )
            {
                return;
            }

            shared_ptr<IfcUnitAssignment> unit_assignment = project->m_UnitsInContext;
            std::vector<shared_ptr<IfcUnit> >& units = unit_assignment->m_Units;
            std::vector<shared_ptr<IfcUnit> >::iterator it;
            for( it=units.begin(); it!=units.end(); ++it )
            {
                shared_ptr<IfcUnit> unit = (*it);

                shared_ptr<IfcSIUnit> si_unit = dynamic_pointer_cast<IfcSIUnit>( unit );
                if( si_unit )
                {
                    shared_ptr<IfcUnitEnum> unit_type = si_unit->m_UnitType;
                    shared_ptr<IfcSIUnitName> unit_name = si_unit->m_Name;

                    if( unit_type )
                    {
                        if( unit_type->m_enum == IfcUnitEnum::ENUM_LENGTHUNIT )
                        {
                            if( si_unit->m_Prefix )
                            {
                                if( m_prefix_map.find( si_unit->m_Prefix->m_enum ) != m_prefix_map.end() )
                                {
                                    m_length_unit_factor = m_prefix_map[si_unit->m_Prefix->m_enum];
                                }
                            }
                        }
                        else if( unit_type->m_enum == IfcUnitEnum::ENUM_PLANEANGLEUNIT )
                        {
                            if( unit_name->m_enum == IfcSIUnitName::ENUM_RADIAN )
                            {
                                m_plane_angle_factor = 1.0;
                            }
                        }
                    }
                    continue;
                }

                shared_ptr<IfcConversionBasedUnit> conversion_based_unit = dynamic_pointer_cast<IfcConversionBasedUnit>(unit);
                if( conversion_based_unit )
                {
                    if( conversion_based_unit->m_ConversionFactor )
                    {
                        shared_ptr<IfcMeasureWithUnit> conversion_factor = conversion_based_unit->m_ConversionFactor;
                        if( conversion_factor->m_UnitComponent )
                        {
                            shared_ptr<IfcUnit> unit_component = conversion_factor->m_UnitComponent;
                            shared_ptr<IfcSIUnit> unit_component_si = dynamic_pointer_cast<IfcSIUnit>(unit_component);
                            if( unit_component_si )
                            {
                                shared_ptr<IfcUnitEnum> type = unit_component_si->m_UnitType;
                                if( type )
                                {
                                    if( type->m_enum == IfcUnitEnum::ENUM_PLANEANGLEUNIT )
                                    {
                                        if( conversion_factor->m_ValueComponent )
                                        {
                                            shared_ptr<IfcValue> plane_angle_value = conversion_factor->m_ValueComponent;
                                            if( dynamic_pointer_cast<IfcPlaneAngleMeasure>(plane_angle_value) )
                                            {
                                                shared_ptr<IfcPlaneAngleMeasure> plane_angle_measure = dynamic_pointer_cast<IfcPlaneAngleMeasure>(plane_angle_value);
                                                m_plane_angle_factor = plane_angle_measure->m_value;
                                            }
                                            else if( dynamic_pointer_cast<IfcRatioMeasure>(plane_angle_value) )
                                            {
                                                shared_ptr<IfcRatioMeasure> plane_angle_measure = dynamic_pointer_cast<IfcRatioMeasure>(plane_angle_value);
                                                m_plane_angle_factor = plane_angle_measure->m_value;
                                            }
                                            else if( conversion_based_unit->m_Name )
                                            {
                                                if( _stricmp(conversion_based_unit->m_Name->m_value.c_str(), "DEGREE" ) == 0 )
                                                {
                                                    m_plane_angle_factor = M_PI/180.0;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    } // end namespace Ifc2x3
} // end namespace OpenInfraPlatform