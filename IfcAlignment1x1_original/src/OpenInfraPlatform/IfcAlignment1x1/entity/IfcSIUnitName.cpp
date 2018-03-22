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

#include "IfcSIUnitName.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcSIUnitName::IfcSIUnitName() {}
		IfcSIUnitName::IfcSIUnitName(IfcSIUnitName::IfcSIUnitNameEnum value) { m_enum = value; }
		IfcSIUnitName::~IfcSIUnitName() {}
		void IfcSIUnitName::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcSIUnitNameEnum::ENUM_AMPERE)
				{
					stream << ".AMPERE.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_BECQUEREL)
				{
					stream << ".BECQUEREL.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_CANDELA)
				{
					stream << ".CANDELA.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_COULOMB)
				{
					stream << ".COULOMB.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_CUBIC_METRE)
				{
					stream << ".CUBIC_METRE.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_DEGREE_CELSIUS)
				{
					stream << ".DEGREE_CELSIUS.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_FARAD)
				{
					stream << ".FARAD.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_GRAM)
				{
					stream << ".GRAM.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_GRAY)
				{
					stream << ".GRAY.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_HENRY)
				{
					stream << ".HENRY.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_HERTZ)
				{
					stream << ".HERTZ.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_JOULE)
				{
					stream << ".JOULE.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_KELVIN)
				{
					stream << ".KELVIN.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_LUMEN)
				{
					stream << ".LUMEN.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_LUX)
				{
					stream << ".LUX.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_METRE)
				{
					stream << ".METRE.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_MOLE)
				{
					stream << ".MOLE.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_NEWTON)
				{
					stream << ".NEWTON.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_OHM)
				{
					stream << ".OHM.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_PASCAL)
				{
					stream << ".PASCAL.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_RADIAN)
				{
					stream << ".RADIAN.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_SECOND)
				{
					stream << ".SECOND.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_SIEMENS)
				{
					stream << ".SIEMENS.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_SIEVERT)
				{
					stream << ".SIEVERT.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_SQUARE_METRE)
				{
					stream << ".SQUARE_METRE.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_STERADIAN)
				{
					stream << ".STERADIAN.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_TESLA)
				{
					stream << ".TESLA.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_VOLT)
				{
					stream << ".VOLT.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_WATT)
				{
					stream << ".WATT.";
				}
				else if ( m_enum == IfcSIUnitNameEnum::ENUM_WEBER)
				{
					stream << ".WEBER.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcSIUnitName> IfcSIUnitName::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcSIUnitName>(); }
				std::shared_ptr<IfcSIUnitName> type_object(new IfcSIUnitName() );
				if ( _stricmp( arg.c_str(), ".AMPERE.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_AMPERE;
				}
				else if ( _stricmp( arg.c_str(), ".BECQUEREL.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_BECQUEREL;
				}
				else if ( _stricmp( arg.c_str(), ".CANDELA.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_CANDELA;
				}
				else if ( _stricmp( arg.c_str(), ".COULOMB.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_COULOMB;
				}
				else if ( _stricmp( arg.c_str(), ".CUBIC_METRE.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_CUBIC_METRE;
				}
				else if ( _stricmp( arg.c_str(), ".DEGREE_CELSIUS.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_DEGREE_CELSIUS;
				}
				else if ( _stricmp( arg.c_str(), ".FARAD.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_FARAD;
				}
				else if ( _stricmp( arg.c_str(), ".GRAM.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_GRAM;
				}
				else if ( _stricmp( arg.c_str(), ".GRAY.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_GRAY;
				}
				else if ( _stricmp( arg.c_str(), ".HENRY.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_HENRY;
				}
				else if ( _stricmp( arg.c_str(), ".HERTZ.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_HERTZ;
				}
				else if ( _stricmp( arg.c_str(), ".JOULE.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_JOULE;
				}
				else if ( _stricmp( arg.c_str(), ".KELVIN.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_KELVIN;
				}
				else if ( _stricmp( arg.c_str(), ".LUMEN.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_LUMEN;
				}
				else if ( _stricmp( arg.c_str(), ".LUX.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_LUX;
				}
				else if ( _stricmp( arg.c_str(), ".METRE.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_METRE;
				}
				else if ( _stricmp( arg.c_str(), ".MOLE.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_MOLE;
				}
				else if ( _stricmp( arg.c_str(), ".NEWTON.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_NEWTON;
				}
				else if ( _stricmp( arg.c_str(), ".OHM.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_OHM;
				}
				else if ( _stricmp( arg.c_str(), ".PASCAL.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_PASCAL;
				}
				else if ( _stricmp( arg.c_str(), ".RADIAN.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_RADIAN;
				}
				else if ( _stricmp( arg.c_str(), ".SECOND.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_SECOND;
				}
				else if ( _stricmp( arg.c_str(), ".SIEMENS.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_SIEMENS;
				}
				else if ( _stricmp( arg.c_str(), ".SIEVERT.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_SIEVERT;
				}
				else if ( _stricmp( arg.c_str(), ".SQUARE_METRE.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_SQUARE_METRE;
				}
				else if ( _stricmp( arg.c_str(), ".STERADIAN.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_STERADIAN;
				}
				else if ( _stricmp( arg.c_str(), ".TESLA.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_TESLA;
				}
				else if ( _stricmp( arg.c_str(), ".VOLT.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_VOLT;
				}
				else if ( _stricmp( arg.c_str(), ".WATT.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_WATT;
				}
				else if ( _stricmp( arg.c_str(), ".WEBER.") == 0)
				{
					type_object->m_enum = IfcSIUnitName::IfcSIUnitNameEnum::ENUM_WEBER;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
