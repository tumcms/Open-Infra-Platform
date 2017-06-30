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

#pragma once

#include <vector>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include "OpenInfraPlatform/IfcAlignment1x1/model/Object.h"
#include "IfcDocumentSelect.h"
#include "IfcExternalInformation.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		class IfcIdentifier;
		class IfcLabel;
		class IfcText;
		class IfcURIReference;
		class IfcText;
		class IfcText;
		class IfcText;
		class IfcLabel;
		class IfcActorSelect;
		class IfcActorSelect;
		class IfcDateTime;
		class IfcDateTime;
		class IfcIdentifier;
		class IfcDate;
		class IfcDate;
		class IfcDocumentConfidentialityEnum;
		class IfcDocumentStatusEnum;
		// ENTITY IfcDocumentInformation
		class IfcDocumentInformation : public IfcExternalInformation, public IfcDocumentSelect

		{
		public:
			IfcDocumentInformation();
			IfcDocumentInformation( int id );
			~IfcDocumentInformation();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity(std::shared_ptr<IfcAlignment1x1Entity> other);
			virtual void getStepLine(std::stringstream& stream) const;
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			virtual void readStepData(std::vector<std::string>& args, const std::map<int, shared_ptr<IfcAlignment1x1Entity> >& map);
			virtual void setInverseCounterparts(shared_ptr<IfcAlignment1x1Entity> ptr_self);
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcDocumentInformation"; }

			// IfcDocumentInformation -----------------------
			// attributes:
			std::shared_ptr<IfcIdentifier> m_Identification;
			std::shared_ptr<IfcLabel> m_Name;
			std::shared_ptr<IfcText> m_Description;
			std::shared_ptr<IfcURIReference> m_Location;
			std::shared_ptr<IfcText> m_Purpose;
			std::shared_ptr<IfcText> m_IntendedUse;
			std::shared_ptr<IfcText> m_Scope;
			std::shared_ptr<IfcLabel> m_Revision;
			std::shared_ptr<IfcActorSelect> m_DocumentOwner;
			std::vector<std::shared_ptr<IfcActorSelect>>  m_Editors;
			std::shared_ptr<IfcDateTime> m_CreationTime;
			std::shared_ptr<IfcDateTime> m_LastRevisionTime;
			std::shared_ptr<IfcIdentifier> m_ElectronicFormat;
			std::shared_ptr<IfcDate> m_ValidFrom;
			std::shared_ptr<IfcDate> m_ValidUntil;
			std::shared_ptr<IfcDocumentConfidentialityEnum> m_Confidentiality;
			std::shared_ptr<IfcDocumentStatusEnum> m_Status;
		};
	}
}
