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

#include <sstream>
#include <limits>
#include <map>
#include "OpenInfraPlatform/IfcBridge/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcBridge/writer/WriterUtil.h"
#include "OpenInfraPlatform/IfcBridge/model/shared_ptr.h"
#include "OpenInfraPlatform/IfcBridge/model/IfcBridgeException.h"
#include "IfcBridgeSubstructureElementType.h"

// TYPE IfcBridgeSubstructureElementType 
IfcBridgeSubstructureElementType::IfcBridgeSubstructureElementType() {}
IfcBridgeSubstructureElementType::~IfcBridgeSubstructureElementType() {}
void IfcBridgeSubstructureElementType::getStepParameter( std::stringstream& stream, bool is_select_type ) const
{
	if( is_select_type ) { stream << "IFCBRIDGESUBSTRUCTUREELEMENTTYPE("; }
	if( m_enum == ENUM_ABUTMENT )
	{
		stream << ".ABUTMENT.";
	}
	else if( m_enum == ENUM_PIER )
	{
		stream << ".PIER.";
	}
	else if( m_enum == ENUM_FOUNDATION )
	{
		stream << ".FOUNDATION.";
	}
	if( is_select_type ) { stream << ")"; }
}
shared_ptr<IfcBridgeSubstructureElementType> IfcBridgeSubstructureElementType::readStepData( std::string& arg )
{
	// read TYPE
	if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcBridgeSubstructureElementType>(); }
	shared_ptr<IfcBridgeSubstructureElementType> type_object( new IfcBridgeSubstructureElementType() );
	if( _stricmp( arg.c_str(), ".ABUTMENT." ) == 0 )
	{
		type_object->m_enum = IfcBridgeSubstructureElementType::ENUM_ABUTMENT;
	}
	else if( _stricmp( arg.c_str(), ".PIER." ) == 0 )
	{
		type_object->m_enum = IfcBridgeSubstructureElementType::ENUM_PIER;
	}
	else if( _stricmp( arg.c_str(), ".FOUNDATION." ) == 0 )
	{
		type_object->m_enum = IfcBridgeSubstructureElementType::ENUM_FOUNDATION;
	}
	return type_object;
}
