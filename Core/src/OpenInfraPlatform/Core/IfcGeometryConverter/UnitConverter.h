/*
	Copyright (c) 2018 Technical University of Munich
	Chair of Computational Modeling and Simulation.

	TUM Open Infra Platform is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License Version 3
	as published by the Free Software Foundation.

	TUM Open Infra Platform is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef OpenInfraPlatform_IfcGeometryConverter_UnitConverter_5F75E53B_DF06_4645_BDAA_F6585F55B2CF_h
#define OpenInfraPlatform_IfcGeometryConverter_UnitConverter_5F75E53B_DF06_4645_BDAA_F6585F55B2CF_h

#include <map>
#include <memory>
#include <vector>

namespace OpenInfraPlatform {
	namespace IfcGeometryConverter {

		template < class IfcEntityTypesT> class UnitConverter
		{
		public:
			UnitConverter() {
				m_length_unit_factor = 1.0;
				m_plane_angle_factor = 1.0; // defaulting to radian

				m_prefix_map[(int) IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_EXA] = 1E18;
				m_prefix_map[(int) IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_PETA] = 1E15;
				m_prefix_map[(int) IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_TERA] = 1E12;
				m_prefix_map[(int) IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_GIGA] = 1E9;
				m_prefix_map[(int) IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_MEGA] = 1E6;
				m_prefix_map[(int) IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_KILO] = 1E3;
				m_prefix_map[(int) IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_HECTO] = 1E2;
				m_prefix_map[(int) IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_DECA] = 1E1;
				m_prefix_map[(int) IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_DECI] = 1E-1;
				m_prefix_map[(int) IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_CENTI] = 1E-2;
				m_prefix_map[(int) IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_MILLI] = 1E-3;
				m_prefix_map[(int) IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_MICRO] = 1E-6;
				m_prefix_map[(int) IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_NANO] = 1E-9;
				m_prefix_map[(int) IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_PICO] = 1E-12;
				m_prefix_map[(int) IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_FEMTO] = 1E-15;
				m_prefix_map[(int) IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_ATTO] = 1E-18;
			}

			void setIfcProject(std::shared_ptr<typename IfcEntityTypesT::IfcProject> project) {
				m_length_unit_factor = 1.0;
				m_plane_angle_factor = 1.0; // defaulting to radian

				if (!project->UnitsInContext)
				{
					return;
				}

				std::shared_ptr<typename IfcEntityTypesT::IfcUnitAssignment> unit_assignment = project->UnitsInContext;
				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcUnit> >& units = unit_assignment->Units;
				//std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcUnit> >::iterator it;

				//for (it = units.begin(); it != units.end(); ++it)
				/*
				for(auto unit : project->UnitsInContext->Units) {			

					std::shared_ptr<typename IfcEntityTypesT::IfcSIUnit> si_unit = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSIUnit>(&unit);
					if (si_unit)
					{
						std::shared_ptr<typename IfcEntityTypesT::IfcUnitEnum> unit_type = si_unit->UnitType;
						std::shared_ptr<typename IfcEntityTypesT::IfcSIUnitName> unit_name = si_unit->Name;

						if (unit_type)
						{
							if (*unit_type == eIfcUnitEnum::ENUM_LENGTHUNIT)
							{
								if (si_unit->Prefix)
								{
									if (m_prefix_map.find(si_unit->Prefix) != m_prefix_map.end())
									{
										m_length_unit_factor = m_prefix_map[si_unit->Prefix];
									}
								}
							}
							else if (unit_type->m_enum == IfcUnitEnum::ENUM_PLANEANGLEUNIT)
							{
								if (unit_name->m_enum == IfcSIUnitName::ENUM_RADIAN)
								{
									m_plane_angle_factor = 1.0;
								}
							}
						}
						continue;
					}

					shared_ptr<IfcConversionBasedUnit> conversion_based_unit = dynamic_pointer_cast<IfcConversionBasedUnit>(unit);
					if (conversion_based_unit)
					{
						if (conversion_based_unit->m_ConversionFactor)
						{
							shared_ptr<IfcMeasureWithUnit> conversion_factor = conversion_based_unit->m_ConversionFactor;
							if (conversion_factor->m_UnitComponent)
							{
								shared_ptr<IfcUnit> unit_component = conversion_factor->m_UnitComponent;
								shared_ptr<IfcSIUnit> unit_component_si = dynamic_pointer_cast<IfcSIUnit>(unit_component);
								if (unit_component_si)
								{
									shared_ptr<IfcUnitEnum> type = unit_component_si->m_UnitType;
									if (type)
									{
										if (type->m_enum == IfcUnitEnum::ENUM_PLANEANGLEUNIT)
										{
											if (conversion_factor->m_ValueComponent)
											{
												shared_ptr<IfcValue> plane_angle_value = conversion_factor->m_ValueComponent;
												if (dynamic_pointer_cast<IfcPlaneAngleMeasure>(plane_angle_value))
												{
													shared_ptr<IfcPlaneAngleMeasure> plane_angle_measure = dynamic_pointer_cast<IfcPlaneAngleMeasure>(plane_angle_value);
													m_plane_angle_factor = plane_angle_measure->m_value;
												}
												else if (dynamic_pointer_cast<IfcRatioMeasure>(plane_angle_value))
												{
													shared_ptr<IfcRatioMeasure> plane_angle_measure = dynamic_pointer_cast<IfcRatioMeasure>(plane_angle_value);
													m_plane_angle_factor = plane_angle_measure->m_value;
												}
												else if (conversion_based_unit->m_Name)
												{
													if (_stricmp(conversion_based_unit->m_Name->m_value.c_str(), "DEGREE") == 0)
													{
														m_plane_angle_factor = M_PI / 180.0;
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
				*/
			}

			double getLengthInMeterFactor()
			{
				return m_length_unit_factor;
			}

			double getAngleInRadianFactor()
			{
				return m_plane_angle_factor;
			}

		private:
			std::map<int, double> m_prefix_map;
			double m_length_unit_factor;
			double m_plane_angle_factor;
		};
	}
}

#endif