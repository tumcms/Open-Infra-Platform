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

#include "EXPRESS/EXPRESSReference.h"
#include "BlueFramework/Core/Diagnostics/log.h"

namespace OpenInfraPlatform 
{
	namespace Core 
	{
		namespace IfcGeometryConverter {

			/*! \brief Unit conversion functionality
			
			\param IfcEntityTypesT The IFC version specification.

			*/
			template <class IfcEntityTypesT> 
			class UnitConverter 
			{
			public:
				//! Constructor
				UnitConverter()
				{
					m_length_unit_factor = -1.0; // is set in the first call to the getter
					m_plane_angle_factor = -1.0; // is set in the first call to the getter
				}

				/*! \brief Gets the default units from the IfcProject.
				
				Sets all member variables.

				\param[in] project A pointer to the IfcProject entity within the model.
				*/
				void setIfcProject(const EXPRESSReference<typename IfcEntityTypesT::IfcProject>& project) 
				{
					if(!project->UnitsInContext) {
						throw oip::InconsistentModellingException(project, "project->UnitsInContext is not defined");
					}

					// remember units in context
					m_unit_assignment = project->UnitsInContext.get().lock();

					m_length_unit_factor = getFactorFor( typename IfcEntityTypesT::IfcUnitEnum::ENUM::ENUM_LENGTHUNIT ); 
					m_plane_angle_factor = getFactorFor( typename IfcEntityTypesT::IfcUnitEnum::ENUM::ENUM_PLANEANGLEUNIT ); 
				}

				/*! \brief Gets the factor for specified unit type.
				
				\param[in] unit_type The type of unit specified by the enumeration value of \c IfcUnitEnum.
				*/
				double getFactorFor(const typename IfcEntityTypesT::IfcUnitEnum& unit_type) const
				{
					
					if (!m_unit_assignment) {
						throw oip::InconsistentModellingException(m_unit_assignment, "m_unit_assignmentt is not defined");
					}
						

					for (auto& unit : m_unit_assignment->Units)
					{
						// TYPE IfcUnit = SELECT(
						//	IfcDerivedUnit,
						//	IfcNamedUnit,
						//	IfcMonetaryUnit);
						// END_TYPE;

						switch (unit.which())
						{
						case 0:
						{
							// IfcDerivedUnit
							continue;
						}
						case 1:
						{
							// IfcMonetaryUnit
							continue;
						}
						case 2:
						{
							// IfcNamedUnit
							const auto& namedUnit = unit.get<EXPRESSReference<typename IfcEntityTypesT::IfcNamedUnit>>().lock();

							if (namedUnit->UnitType == unit_type)
							{
								// found the one
								return convertUnit( namedUnit );
							}

							break;
						}
						} // end switch (unit.which())
					} // end for (auto& unit : m_unit_assignment->Units)

					// return 1 for unknown conversions
					return 1.;
				}

				/*! \brief Gets the factor for specified unit type.

				\param[in] unit_type The type of unit specified by the enumeration value of \c IfcDerivedUnitEnum.
				*/
				double getFactorFor(const typename IfcEntityTypesT::IfcDerivedUnitEnum& unit_type) const
				{
					if (!m_unit_assignment) {
						throw oip::InconsistentModellingException(m_unit_assignment, "m_unit_assignmentt is not defined");
					}

					for (auto& unit : m_unit_assignment->Units)
					{
						// TYPE IfcUnit = SELECT(
						//	IfcDerivedUnit,
						//	IfcNamedUnit,
						//	IfcMonetaryUnit);
						// END_TYPE;

						switch (unit.which())
						{
						case 0:
						{
							// IfcDerivedUnit
							auto& derivedUnit = unit.get<EXPRESSReference<typename IfcEntityTypesT::IfcDerivedUnit>>().lock();
							
							if (derivedUnit->UnitType == unit_type)
							{
								// found the one
								return convertUnit(derivedUnit);
							}
							
							break;
						}
						case 1:
						{
							// IfcMonetaryUnit
							continue;
						}
						case 2:
						{
							// IfcNamedUnit
							continue;
						}
						} // end switch (unit.which())
					} // end for (auto& unit : m_unit_assignment->Units)

					// return 1 for unknown conversions
					return 1.;
				}

				/*! \brief Converts the unit to a factor to obtain SI unit.
				
				\param[in] unit The unit in question of type \c IfcNamedUnit.

				\return The factor to obtain the SI equivalent unit.
				*/
				double convertUnit(const EXPRESSReference<typename IfcEntityTypesT::IfcNamedUnit>& unit) const
				{
					// https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/schema/ifcmeasureresource/lexical/ifcnamedunit.htm
					// ENTITY IfcNamedUnit
					//	ABSTRACT SUPERTYPE OF(ONEOF(IfcContextDependentUnit, IfcConversionBasedUnit, IfcSIUnit));
					//	Dimensions: IfcDimensionalExponents;
					//	UnitType: IfcUnitEnum;
					// WHERE
					//	WR1 : IfcCorrectDimensions(SELF.UnitType, SELF.Dimensions);
					// END_ENTITY;
				
					// (1/3) IfcContextDependentUnit
					//std::shared_ptr<typename IfcEntityTypesT::IfcContextDependentUnit> contextDependentUnit =
					//	std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcContextDependentUnit>(unit);
					if (unit.isOfType<typename IfcEntityTypesT::IfcContextDependentUnit>())
					{
						EXPRESSReference<typename IfcEntityTypesT::IfcContextDependentUnit> contextDependentUnit = unit.as<typename IfcEntityTypesT::IfcContextDependentUnit>();
						//TODO
						throw oip::UnhandledException(unit);
					}

					// (2/3) IfcConversionBasedUnit
					//std::shared_ptr<typename IfcEntityTypesT::IfcConversionBasedUnit> conversionBasedUnit =
						//std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcConversionBasedUnit>(unit);
					if (unit.isOfType<typename IfcEntityTypesT::IfcConversionBasedUnit>())
					{
						// ENTITY IfcConversionBasedUnit
						//	SUPERTYPE OF(IfcConversionBasedUnitWithOffset)
						//	SUBTYPE OF(IfcNamedUnit);
						//	Name: IfcLabel;
						//	ConversionFactor: IfcMeasureWithUnit;
						// INVERSE
						//	HasExternalReference : SET[0:? ] OF IfcExternalReferenceRelationship FOR RelatedResourceObjects;
						// END_ENTITY;
						EXPRESSReference<typename IfcEntityTypesT::IfcConversionBasedUnit> conversionBasedUnit = unit.as<typename IfcEntityTypesT::IfcConversionBasedUnit >();
						if (conversionBasedUnit.isOfType<typename IfcEntityTypesT::IfcConversionBasedUnitWithOffset>())
						{
							/*BLUE_LOG(warning) << conversionBasedUnit->getErrorLog() << ": .. with offset is not supported.";
							BLUE_LOG(trace) << "Add "
											<< std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcConversionBasedUnitWithOffset>(conversionBasedUnit)->ConversionOffset
											<< " to all values of with unit "
											<< conversionBasedUnit->Name
											<< " of type "
											<< conversionBasedUnit->UnitType.getStepParameter();*/
							throw oip::UnhandledException(unit);
						}

						// ENTITY IfcMeasureWithUnit;
						//	ValueComponent: IfcValue; // <- Select
						//	UnitComponent: IfcUnit;   // <- Select
						// END_ENTITY;

						double value = convertValue(conversionBasedUnit->ConversionFactor->ValueComponent);
						double unitFactor = convertUnit(conversionBasedUnit->ConversionFactor->UnitComponent);

						//tweak until #36 gets resolved
						if (conversionBasedUnit->Name == "'degree'")
							value = 0.017453293;

						return value * unitFactor;
					}

					// (3/3) IfcSIUnit
					//std::shared_ptr<typename IfcEntityTypesT::IfcSIUnit> SIUnit =
						//std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSIUnit>(unit);
					if (unit.isOfType<typename IfcEntityTypesT::IfcSIUnit>())
					{
						// ENTITY IfcSIUnit
						//	SUBTYPE OF(IfcNamedUnit);
						//	Prefix: OPTIONAL IfcSIPrefix;
						//	Name: IfcSIUnitName;
						// DERIVE
						//	SELF\IfcNamedUnit.Dimensions : IfcDimensionalExponents: = IfcDimensionsForSiUnit(SELF.Name);
						// END_ENTITY;
						EXPRESSReference<typename IfcEntityTypesT::IfcSIUnit> SIUnit = unit.as<typename IfcEntityTypesT::IfcSIUnit>();
						// get the prefix factor
						double dPrefixFactor = 1.;
						if( SIUnit->Prefix)
						{
							switch (SIUnit->Prefix)
							{
							case typename IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_EXA:
							    dPrefixFactor = 1E18;
							    break;
							case typename IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_PETA:
							    dPrefixFactor = 1E15;
							    break;
							case typename IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_TERA:
							    dPrefixFactor = 1E12;
							    break;
							case typename IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_GIGA:
							    dPrefixFactor = 1E9;
							    break;
							case typename IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_MEGA:
							    dPrefixFactor = 1E6;
							    break;
							case typename IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_KILO:
							    dPrefixFactor = 1E3;
							    break;
							case typename IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_HECTO:
							    dPrefixFactor = 1E2;
							    break;
							case typename IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_DECA:
							    dPrefixFactor = 1E1;
							    break;
							case typename IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_DECI:
							    dPrefixFactor = 1E-1;
							    break;
							case typename IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_CENTI:
							    dPrefixFactor = 1E-2;
							    break;
							case typename IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_MILLI:
							    dPrefixFactor = 1E-3;
							    break;
							case typename IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_MICRO:
							    dPrefixFactor = 1E-6;
							    break;
							case typename IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_NANO:
							    dPrefixFactor = 1E-9;
							    break;
							case typename IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_PICO:
							    dPrefixFactor = 1E-12;
							    break;
							case typename IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_FEMTO:
							    dPrefixFactor = 1E-15;
							    break;
							case typename IfcEntityTypesT::IfcSIPrefix::ENUM::ENUM_ATTO:
							    dPrefixFactor = 1E-18;
							    break;
							default:
								dPrefixFactor = 1.;
								break;
							} // end switch (SIUnit->Prefix)
						} // end if (SIUnit->Prefix)

						return dPrefixFactor;
					}

					return 1.;
				}

				/*! \brief Converts the unit to a factor to obtain SI unit.

				\param[in] unit The unit in question of type \c IfcDerivedUnit.

				\return The factor to obtain the SI equivalent unit.
				*/
				double convertUnit(const EXPRESSReference<typename IfcEntityTypesT::IfcDerivedUnit>& unit) const
				{
					// https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/schema/ifcmeasureresource/lexical/ifcderivedunit.htm
					// ENTITY IfcDerivedUnit;
					//	Elements: SET[1:? ] OF IfcDerivedUnitElement;
					//	UnitType: IfcDerivedUnitEnum;
					//	UserDefinedType: OPTIONAL IfcLabel;
					// DERIVE
					//	Dimensions : IfcDimensionalExponents: = IfcDeriveDimensionalExponents(Elements);
					// WHERE
					//	WR1 : (SIZEOF(Elements) > 1) OR((SIZEOF(Elements) = 1) AND(Elements[1].Exponent < > 1));
					//	WR2: (UnitType <> IfcDerivedUnitEnum.USERDEFINED) OR
					//		((UnitType = IfcDerivedUnitEnum.USERDEFINED) AND
					//		(EXISTS(SELF.UserDefinedType)));
					// END_ENTITY;

					double factor = 1.;

					for (auto& unitElement : unit->Elements)
					{
						// https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/schema/ifcmeasureresource/lexical/ifcderivedunitelement.htm
						// ENTITY IfcDerivedUnitElement;
						//	Unit: IfcNamedUnit;
						//	Exponent: INTEGER;
						// END_ENTITY;

						double element_factor = convertUnit( unitElement->Unit.lock() );
						factor *= pow(element_factor, unitElement->Exponent);
					}

					return factor;
				}

				/*! \brief Converts the unit to a factor to obtain SI unit.

				\param[in] unit The unit in question of type \c IfcUnit.

				\return The factor to obtain the SI equivalent unit.
				*/
				double convertUnit(typename IfcEntityTypesT::IfcUnit& unit) const
				{
					// TYPE IfcUnit = SELECT(
					//	IfcDerivedUnit,
					//	IfcNamedUnit,
					//	IfcMonetaryUnit);
					// END_TYPE;

					switch (unit.which())
					{
					case 0:
					{
						// IfcDerivedUnit
						auto& derivedUnit = unit.get<EXPRESSReference<typename IfcEntityTypesT::IfcDerivedUnit>>().lock();

						return convertUnit(derivedUnit); // call recursively the other overload
					}
					case 1:
					{
						// IfcMonetaryUnit
						auto& monetaryUnit = unit.get<EXPRESSReference<typename IfcEntityTypesT::IfcMonetaryUnit>>().lock();
						BLUE_LOG(warning) << monetaryUnit->getErrorLog() << ": Not supported.";
						break;
					}
					case 2:
					{
						// IfcNamedUnit
						auto& namedUnit = unit.get<EXPRESSReference<typename IfcEntityTypesT::IfcNamedUnit>>().lock();

						return convertUnit(namedUnit); // call recursively the other overload
					}
					} // end switch (unit.which())

					return 1.;
				}

				/*! \brief Converts the value to a floating point (if applicable).

				\param[in] value The value in question of type \c IfcValue.

				\return The value saved or 1. (if not a real number).
				*/
				double convertValue(const typename IfcEntityTypesT::IfcValue& value) const
				{
					//TODO IfcValue conversion

					// TYPE IfcValue = SELECT (
					//	IfcMeasureValue,
					//	IfcSimpleValue,
					//	IfcDerivedMeasureValue);
					// END_TYPE;

					//switch (value.which())
					//{
					//case 0:
					//{
					//	// IfcDerivedMeasureValue
					//	auto& derivedMeasureValue = value.get<EXPRESSReference<typename IfcEntityTypesT::IfcDerivedMeasureValue>>().lock();
					//	throw oip::UnhandledException(derivedMeasureValue);
					//}
					//case 1:
					//{
					//	// IfcMeasureValue
					//	auto& measureValue = value.get<EXPRESSReference<typename IfcEntityTypesT::IfcMeasureValue>>().lock();
					//	double val = (double)measureValue->m_value;
					//	return val;
					//}
					//case 2:
					//{
					//	// IfcSimpleValue
					//	auto& simpleValue = value.get<EXPRESSReference<typename IfcEntityTypesT::IfcSimpleValue>>().lock();
					//	throw oip::UnhandledException(simpleValue);
					//}
					//} // end switch (value.which())

					return 1.;
				}

				/*! \brief Gets the factor for length.

				This factor is accessed very often and is therefore cached.
				It gets set in UnitConverter<T>::setIfcProject function.

				\return The factor to obtain meters of length.
				*/
				double getLengthInMeterFactor()
				{
					if (m_length_unit_factor < 0.0) // means, it is unset
						m_length_unit_factor = getFactorFor(typename IfcEntityTypesT::IfcUnitEnum::ENUM::ENUM_LENGTHUNIT);
					return m_length_unit_factor;
				}

				/*! \brief Gets the factor for angles.

				This factor is accessed very often and is therefore cached.
				It gets set in UnitConverter<T>::setIfcProject function.

				\return The factor to obtain radians of angle.
				*/
				double getAngleInRadianFactor()
				{
					if (m_plane_angle_factor < 0.0) // means, it is unset
						m_plane_angle_factor = getFactorFor(typename IfcEntityTypesT::IfcUnitEnum::ENUM::ENUM_PLANEANGLEUNIT);
					return m_plane_angle_factor;
				}

			private:

				std::shared_ptr<typename IfcEntityTypesT::IfcUnitAssignment> m_unit_assignment; //< the unit assignment present in the IFC file

				double m_length_unit_factor; //< cached value for the factor of distance [to meters]
				double m_plane_angle_factor; //< cached value for the factor of angle [to radians]
			};
		}
	}
}

#endif
