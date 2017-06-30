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

#include "IfcRoleEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcRoleEnum::IfcRoleEnum() {}
		IfcRoleEnum::IfcRoleEnum(IfcRoleEnum::IfcRoleEnumEnum value) { m_enum = value; }
		IfcRoleEnum::~IfcRoleEnum() {}
		void IfcRoleEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcRoleEnumEnum::ENUM_SUPPLIER)
				{
					stream << ".SUPPLIER.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_MANUFACTURER)
				{
					stream << ".MANUFACTURER.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_CONTRACTOR)
				{
					stream << ".CONTRACTOR.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_SUBCONTRACTOR)
				{
					stream << ".SUBCONTRACTOR.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_ARCHITECT)
				{
					stream << ".ARCHITECT.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_STRUCTURALENGINEER)
				{
					stream << ".STRUCTURALENGINEER.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_COSTENGINEER)
				{
					stream << ".COSTENGINEER.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_CLIENT)
				{
					stream << ".CLIENT.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_BUILDINGOWNER)
				{
					stream << ".BUILDINGOWNER.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_BUILDINGOPERATOR)
				{
					stream << ".BUILDINGOPERATOR.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_MECHANICALENGINEER)
				{
					stream << ".MECHANICALENGINEER.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_ELECTRICALENGINEER)
				{
					stream << ".ELECTRICALENGINEER.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_PROJECTMANAGER)
				{
					stream << ".PROJECTMANAGER.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_FACILITIESMANAGER)
				{
					stream << ".FACILITIESMANAGER.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_CIVILENGINEER)
				{
					stream << ".CIVILENGINEER.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_COMMISSIONINGENGINEER)
				{
					stream << ".COMMISSIONINGENGINEER.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_ENGINEER)
				{
					stream << ".ENGINEER.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_OWNER)
				{
					stream << ".OWNER.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_CONSULTANT)
				{
					stream << ".CONSULTANT.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_CONSTRUCTIONMANAGER)
				{
					stream << ".CONSTRUCTIONMANAGER.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_FIELDCONSTRUCTIONMANAGER)
				{
					stream << ".FIELDCONSTRUCTIONMANAGER.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_RESELLER)
				{
					stream << ".RESELLER.";
				}
				else if ( m_enum == IfcRoleEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcRoleEnum> IfcRoleEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcRoleEnum>(); }
				std::shared_ptr<IfcRoleEnum> type_object(new IfcRoleEnum() );
				if ( _stricmp( arg.c_str(), ".SUPPLIER.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_SUPPLIER;
				}
				else if ( _stricmp( arg.c_str(), ".MANUFACTURER.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_MANUFACTURER;
				}
				else if ( _stricmp( arg.c_str(), ".CONTRACTOR.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_CONTRACTOR;
				}
				else if ( _stricmp( arg.c_str(), ".SUBCONTRACTOR.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_SUBCONTRACTOR;
				}
				else if ( _stricmp( arg.c_str(), ".ARCHITECT.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_ARCHITECT;
				}
				else if ( _stricmp( arg.c_str(), ".STRUCTURALENGINEER.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_STRUCTURALENGINEER;
				}
				else if ( _stricmp( arg.c_str(), ".COSTENGINEER.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_COSTENGINEER;
				}
				else if ( _stricmp( arg.c_str(), ".CLIENT.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_CLIENT;
				}
				else if ( _stricmp( arg.c_str(), ".BUILDINGOWNER.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_BUILDINGOWNER;
				}
				else if ( _stricmp( arg.c_str(), ".BUILDINGOPERATOR.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_BUILDINGOPERATOR;
				}
				else if ( _stricmp( arg.c_str(), ".MECHANICALENGINEER.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_MECHANICALENGINEER;
				}
				else if ( _stricmp( arg.c_str(), ".ELECTRICALENGINEER.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_ELECTRICALENGINEER;
				}
				else if ( _stricmp( arg.c_str(), ".PROJECTMANAGER.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_PROJECTMANAGER;
				}
				else if ( _stricmp( arg.c_str(), ".FACILITIESMANAGER.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_FACILITIESMANAGER;
				}
				else if ( _stricmp( arg.c_str(), ".CIVILENGINEER.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_CIVILENGINEER;
				}
				else if ( _stricmp( arg.c_str(), ".COMMISSIONINGENGINEER.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_COMMISSIONINGENGINEER;
				}
				else if ( _stricmp( arg.c_str(), ".ENGINEER.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_ENGINEER;
				}
				else if ( _stricmp( arg.c_str(), ".OWNER.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_OWNER;
				}
				else if ( _stricmp( arg.c_str(), ".CONSULTANT.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_CONSULTANT;
				}
				else if ( _stricmp( arg.c_str(), ".CONSTRUCTIONMANAGER.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_CONSTRUCTIONMANAGER;
				}
				else if ( _stricmp( arg.c_str(), ".FIELDCONSTRUCTIONMANAGER.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_FIELDCONSTRUCTIONMANAGER;
				}
				else if ( _stricmp( arg.c_str(), ".RESELLER.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_RESELLER;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcRoleEnum::IfcRoleEnumEnum::ENUM_USERDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
