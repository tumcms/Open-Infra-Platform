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

#include "IfcDocumentStatusEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcDocumentStatusEnum::IfcDocumentStatusEnum() {}
		IfcDocumentStatusEnum::IfcDocumentStatusEnum(IfcDocumentStatusEnum::IfcDocumentStatusEnumEnum value) { m_enum = value; }
		IfcDocumentStatusEnum::~IfcDocumentStatusEnum() {}
		void IfcDocumentStatusEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcDocumentStatusEnumEnum::ENUM_DRAFT)
				{
					stream << ".DRAFT.";
				}
				else if ( m_enum == IfcDocumentStatusEnumEnum::ENUM_FINALDRAFT)
				{
					stream << ".FINALDRAFT.";
				}
				else if ( m_enum == IfcDocumentStatusEnumEnum::ENUM_FINAL)
				{
					stream << ".FINAL.";
				}
				else if ( m_enum == IfcDocumentStatusEnumEnum::ENUM_REVISION)
				{
					stream << ".REVISION.";
				}
				else if ( m_enum == IfcDocumentStatusEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcDocumentStatusEnum> IfcDocumentStatusEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcDocumentStatusEnum>(); }
				std::shared_ptr<IfcDocumentStatusEnum> type_object(new IfcDocumentStatusEnum() );
				if ( _stricmp( arg.c_str(), ".DRAFT.") == 0)
				{
					type_object->m_enum = IfcDocumentStatusEnum::IfcDocumentStatusEnumEnum::ENUM_DRAFT;
				}
				else if ( _stricmp( arg.c_str(), ".FINALDRAFT.") == 0)
				{
					type_object->m_enum = IfcDocumentStatusEnum::IfcDocumentStatusEnumEnum::ENUM_FINALDRAFT;
				}
				else if ( _stricmp( arg.c_str(), ".FINAL.") == 0)
				{
					type_object->m_enum = IfcDocumentStatusEnum::IfcDocumentStatusEnumEnum::ENUM_FINAL;
				}
				else if ( _stricmp( arg.c_str(), ".REVISION.") == 0)
				{
					type_object->m_enum = IfcDocumentStatusEnum::IfcDocumentStatusEnumEnum::ENUM_REVISION;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcDocumentStatusEnum::IfcDocumentStatusEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
