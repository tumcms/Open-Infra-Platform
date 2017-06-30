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
#include <sstream>
#include <string>
#include "OpenInfraPlatform/Ifc4/model/shared_ptr.h"
#include "OpenInfraPlatform/Ifc4/model/Ifc4Object.h"
#include "IfcLibrarySelect.h"
#include "IfcExternalReference.h"

namespace OpenInfraPlatform
{
	namespace Ifc4
	{
		class IfcText;
		class IfcLanguageId;
		class IfcLibraryInformation;
		class IfcRelAssociatesLibrary;
		//ENTITY
		class IfcLibraryReference : public IfcLibrarySelect, public IfcExternalReference
		{
		public:
			IfcLibraryReference();
			IfcLibraryReference( int id );
			~IfcLibraryReference();

			// method setEntity takes over all attributes from another instance of the class
			virtual void setEntity( shared_ptr<Ifc4Entity> other );
			virtual void getStepLine( std::stringstream& stream ) const;
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			virtual void readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc4Entity> >& map );
			virtual void setInverseCounterparts( shared_ptr<Ifc4Entity> ptr_self );
			virtual void unlinkSelf();
			virtual const char* classname() const { return "IfcLibraryReference"; }


			// IfcExternalReference -----------------------------------------------------------
			// attributes:
			//  shared_ptr<IfcURIReference>						m_Location;					//optional
			//  shared_ptr<IfcIdentifier>						m_Identification;			//optional
			//  shared_ptr<IfcLabel>								m_Name;						//optional
			// inverse attributes:
			//  std::vector<weak_ptr<IfcExternalReferenceRelationship> >	m_ExternalReferenceForResources_inverse;

			// IfcLibraryReference -----------------------------------------------------------
			// attributes:
			shared_ptr<IfcText>								m_Description;				//optional
			shared_ptr<IfcLanguageId>						m_Language;					//optional
			shared_ptr<IfcLibraryInformation>				m_ReferencedLibrary;		//optional
			// inverse attributes:
			std::vector<weak_ptr<IfcRelAssociatesLibrary> >	m_LibraryRefForObjects_inverse;
		};
	} // end namespace Ifc4
} // end namespace OpenInfraPlatform

