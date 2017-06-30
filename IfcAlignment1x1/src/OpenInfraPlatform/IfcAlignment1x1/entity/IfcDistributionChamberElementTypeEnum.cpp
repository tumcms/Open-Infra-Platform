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

#include "IfcDistributionChamberElementTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcDistributionChamberElementTypeEnum::IfcDistributionChamberElementTypeEnum() {}
		IfcDistributionChamberElementTypeEnum::IfcDistributionChamberElementTypeEnum(IfcDistributionChamberElementTypeEnum::IfcDistributionChamberElementTypeEnumEnum value) { m_enum = value; }
		IfcDistributionChamberElementTypeEnum::~IfcDistributionChamberElementTypeEnum() {}
		void IfcDistributionChamberElementTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcDistributionChamberElementTypeEnumEnum::ENUM_FORMEDDUCT)
				{
					stream << ".FORMEDDUCT.";
				}
				else if ( m_enum == IfcDistributionChamberElementTypeEnumEnum::ENUM_INSPECTIONCHAMBER)
				{
					stream << ".INSPECTIONCHAMBER.";
				}
				else if ( m_enum == IfcDistributionChamberElementTypeEnumEnum::ENUM_INSPECTIONPIT)
				{
					stream << ".INSPECTIONPIT.";
				}
				else if ( m_enum == IfcDistributionChamberElementTypeEnumEnum::ENUM_MANHOLE)
				{
					stream << ".MANHOLE.";
				}
				else if ( m_enum == IfcDistributionChamberElementTypeEnumEnum::ENUM_METERCHAMBER)
				{
					stream << ".METERCHAMBER.";
				}
				else if ( m_enum == IfcDistributionChamberElementTypeEnumEnum::ENUM_SUMP)
				{
					stream << ".SUMP.";
				}
				else if ( m_enum == IfcDistributionChamberElementTypeEnumEnum::ENUM_TRENCH)
				{
					stream << ".TRENCH.";
				}
				else if ( m_enum == IfcDistributionChamberElementTypeEnumEnum::ENUM_VALVECHAMBER)
				{
					stream << ".VALVECHAMBER.";
				}
				else if ( m_enum == IfcDistributionChamberElementTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcDistributionChamberElementTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcDistributionChamberElementTypeEnum> IfcDistributionChamberElementTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcDistributionChamberElementTypeEnum>(); }
				std::shared_ptr<IfcDistributionChamberElementTypeEnum> type_object(new IfcDistributionChamberElementTypeEnum() );
				if ( _stricmp( arg.c_str(), ".FORMEDDUCT.") == 0)
				{
					type_object->m_enum = IfcDistributionChamberElementTypeEnum::IfcDistributionChamberElementTypeEnumEnum::ENUM_FORMEDDUCT;
				}
				else if ( _stricmp( arg.c_str(), ".INSPECTIONCHAMBER.") == 0)
				{
					type_object->m_enum = IfcDistributionChamberElementTypeEnum::IfcDistributionChamberElementTypeEnumEnum::ENUM_INSPECTIONCHAMBER;
				}
				else if ( _stricmp( arg.c_str(), ".INSPECTIONPIT.") == 0)
				{
					type_object->m_enum = IfcDistributionChamberElementTypeEnum::IfcDistributionChamberElementTypeEnumEnum::ENUM_INSPECTIONPIT;
				}
				else if ( _stricmp( arg.c_str(), ".MANHOLE.") == 0)
				{
					type_object->m_enum = IfcDistributionChamberElementTypeEnum::IfcDistributionChamberElementTypeEnumEnum::ENUM_MANHOLE;
				}
				else if ( _stricmp( arg.c_str(), ".METERCHAMBER.") == 0)
				{
					type_object->m_enum = IfcDistributionChamberElementTypeEnum::IfcDistributionChamberElementTypeEnumEnum::ENUM_METERCHAMBER;
				}
				else if ( _stricmp( arg.c_str(), ".SUMP.") == 0)
				{
					type_object->m_enum = IfcDistributionChamberElementTypeEnum::IfcDistributionChamberElementTypeEnumEnum::ENUM_SUMP;
				}
				else if ( _stricmp( arg.c_str(), ".TRENCH.") == 0)
				{
					type_object->m_enum = IfcDistributionChamberElementTypeEnum::IfcDistributionChamberElementTypeEnumEnum::ENUM_TRENCH;
				}
				else if ( _stricmp( arg.c_str(), ".VALVECHAMBER.") == 0)
				{
					type_object->m_enum = IfcDistributionChamberElementTypeEnum::IfcDistributionChamberElementTypeEnumEnum::ENUM_VALVECHAMBER;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcDistributionChamberElementTypeEnum::IfcDistributionChamberElementTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcDistributionChamberElementTypeEnum::IfcDistributionChamberElementTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
