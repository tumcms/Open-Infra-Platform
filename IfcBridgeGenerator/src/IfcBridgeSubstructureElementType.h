/*
    Copyright (c) 2017 Technical University of Munich
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
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include "OpenInfraPlatform/IfcBridge/model/shared_ptr.h"
#include "OpenInfraPlatform/IfcBridge/model/IfcBridgeObject.h"

// TYPE IfcBridgeSubstructureElementType = ENUMERATION OF (ABUTMENT, PIER, FOUNDATION);
class IfcBridgeSubstructureElementType : public OpenInfraPlatform::IfcBridge::IfcBridgeAbstractEnum, public OpenInfraPlatform::IfcBridge::IfcBridgeType
{
public:
	enum IfcBridgeSubstructureElementTypeEnum
	{
		ENUM_ABUTMENT,
		ENUM_PIER,
		ENUM_FOUNDATION
	};

	IfcBridgeSubstructureElementType();
	IfcBridgeSubstructureElementType( IfcBridgeSubstructureElementTypeEnum e ) { m_enum = e; }
	~IfcBridgeSubstructureElementType();
	virtual const char* classname() const { return "IfcBridgeSubstructureElementType"; }
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	static shared_ptr<IfcBridgeSubstructureElementType> readStepData( std::string& arg );
	IfcBridgeSubstructureElementTypeEnum m_enum;
};

