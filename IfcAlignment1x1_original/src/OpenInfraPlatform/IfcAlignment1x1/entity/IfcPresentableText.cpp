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

#include "IfcPresentableText.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcPresentableText::IfcPresentableText() {}
		IfcPresentableText::IfcPresentableText(std::string value) { m_value = value; }
		IfcPresentableText::~IfcPresentableText() {}
		void IfcPresentableText::getStepParameter(std::stringstream& stream, bool is_select_type) const
		{
			if (is_select_type) { stream << "IFCPRESENTABLETEXT("; }
			stream << "'" << encodeStepString( m_value ) << "'";
			if (is_select_type) { stream << ")"; }
		}
		std::shared_ptr<IfcPresentableText> IfcPresentableText::readStepData(const std::string& arg)
		{
			if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcPresentableText>(); }
			else if( arg.compare( "*" ) == 0 ) { return std::shared_ptr<IfcPresentableText>(); }
			std::shared_ptr<IfcPresentableText> type_object(new IfcPresentableText() );
			type_object->m_value = arg;
			return type_object;
		}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
