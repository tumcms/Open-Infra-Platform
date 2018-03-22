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

#include "IfcSIPrefix.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcSIPrefix::IfcSIPrefix() {}
		IfcSIPrefix::IfcSIPrefix(IfcSIPrefix::IfcSIPrefixEnum value) { m_enum = value; }
		IfcSIPrefix::~IfcSIPrefix() {}
		void IfcSIPrefix::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcSIPrefixEnum::ENUM_EXA)
				{
					stream << ".EXA.";
				}
				else if ( m_enum == IfcSIPrefixEnum::ENUM_PETA)
				{
					stream << ".PETA.";
				}
				else if ( m_enum == IfcSIPrefixEnum::ENUM_TERA)
				{
					stream << ".TERA.";
				}
				else if ( m_enum == IfcSIPrefixEnum::ENUM_GIGA)
				{
					stream << ".GIGA.";
				}
				else if ( m_enum == IfcSIPrefixEnum::ENUM_MEGA)
				{
					stream << ".MEGA.";
				}
				else if ( m_enum == IfcSIPrefixEnum::ENUM_KILO)
				{
					stream << ".KILO.";
				}
				else if ( m_enum == IfcSIPrefixEnum::ENUM_HECTO)
				{
					stream << ".HECTO.";
				}
				else if ( m_enum == IfcSIPrefixEnum::ENUM_DECA)
				{
					stream << ".DECA.";
				}
				else if ( m_enum == IfcSIPrefixEnum::ENUM_DECI)
				{
					stream << ".DECI.";
				}
				else if ( m_enum == IfcSIPrefixEnum::ENUM_CENTI)
				{
					stream << ".CENTI.";
				}
				else if ( m_enum == IfcSIPrefixEnum::ENUM_MILLI)
				{
					stream << ".MILLI.";
				}
				else if ( m_enum == IfcSIPrefixEnum::ENUM_MICRO)
				{
					stream << ".MICRO.";
				}
				else if ( m_enum == IfcSIPrefixEnum::ENUM_NANO)
				{
					stream << ".NANO.";
				}
				else if ( m_enum == IfcSIPrefixEnum::ENUM_PICO)
				{
					stream << ".PICO.";
				}
				else if ( m_enum == IfcSIPrefixEnum::ENUM_FEMTO)
				{
					stream << ".FEMTO.";
				}
				else if ( m_enum == IfcSIPrefixEnum::ENUM_ATTO)
				{
					stream << ".ATTO.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcSIPrefix> IfcSIPrefix::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcSIPrefix>(); }
				std::shared_ptr<IfcSIPrefix> type_object(new IfcSIPrefix() );
				if ( _stricmp( arg.c_str(), ".EXA.") == 0)
				{
					type_object->m_enum = IfcSIPrefix::IfcSIPrefixEnum::ENUM_EXA;
				}
				else if ( _stricmp( arg.c_str(), ".PETA.") == 0)
				{
					type_object->m_enum = IfcSIPrefix::IfcSIPrefixEnum::ENUM_PETA;
				}
				else if ( _stricmp( arg.c_str(), ".TERA.") == 0)
				{
					type_object->m_enum = IfcSIPrefix::IfcSIPrefixEnum::ENUM_TERA;
				}
				else if ( _stricmp( arg.c_str(), ".GIGA.") == 0)
				{
					type_object->m_enum = IfcSIPrefix::IfcSIPrefixEnum::ENUM_GIGA;
				}
				else if ( _stricmp( arg.c_str(), ".MEGA.") == 0)
				{
					type_object->m_enum = IfcSIPrefix::IfcSIPrefixEnum::ENUM_MEGA;
				}
				else if ( _stricmp( arg.c_str(), ".KILO.") == 0)
				{
					type_object->m_enum = IfcSIPrefix::IfcSIPrefixEnum::ENUM_KILO;
				}
				else if ( _stricmp( arg.c_str(), ".HECTO.") == 0)
				{
					type_object->m_enum = IfcSIPrefix::IfcSIPrefixEnum::ENUM_HECTO;
				}
				else if ( _stricmp( arg.c_str(), ".DECA.") == 0)
				{
					type_object->m_enum = IfcSIPrefix::IfcSIPrefixEnum::ENUM_DECA;
				}
				else if ( _stricmp( arg.c_str(), ".DECI.") == 0)
				{
					type_object->m_enum = IfcSIPrefix::IfcSIPrefixEnum::ENUM_DECI;
				}
				else if ( _stricmp( arg.c_str(), ".CENTI.") == 0)
				{
					type_object->m_enum = IfcSIPrefix::IfcSIPrefixEnum::ENUM_CENTI;
				}
				else if ( _stricmp( arg.c_str(), ".MILLI.") == 0)
				{
					type_object->m_enum = IfcSIPrefix::IfcSIPrefixEnum::ENUM_MILLI;
				}
				else if ( _stricmp( arg.c_str(), ".MICRO.") == 0)
				{
					type_object->m_enum = IfcSIPrefix::IfcSIPrefixEnum::ENUM_MICRO;
				}
				else if ( _stricmp( arg.c_str(), ".NANO.") == 0)
				{
					type_object->m_enum = IfcSIPrefix::IfcSIPrefixEnum::ENUM_NANO;
				}
				else if ( _stricmp( arg.c_str(), ".PICO.") == 0)
				{
					type_object->m_enum = IfcSIPrefix::IfcSIPrefixEnum::ENUM_PICO;
				}
				else if ( _stricmp( arg.c_str(), ".FEMTO.") == 0)
				{
					type_object->m_enum = IfcSIPrefix::IfcSIPrefixEnum::ENUM_FEMTO;
				}
				else if ( _stricmp( arg.c_str(), ".ATTO.") == 0)
				{
					type_object->m_enum = IfcSIPrefix::IfcSIPrefixEnum::ENUM_ATTO;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
