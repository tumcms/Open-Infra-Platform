#/*
#    Copyright (c) 2018 Technical University of Munich
#    Chair of Computational Modeling and Simulation.
#
#    TUM Open Infra Platform is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License Version 3
#    as published by the Free Software Foundation.
#
#    TUM Open Infra Platform is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program. If not, see <http://www.gnu.org/licenses/>.
#*/

cmake_minimum_required(VERSION 3.13.0)

project(OpenInfraPlatform.Core)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 14)

file(GLOB DataManagement_Source 					src/OpenInfraPlatform/Core/DataManagement/*.*)
file(GLOB IfcGeometryConverter_Source  			    src/OpenInfraPlatform/Core/IfcGeometryConverter/*.*)	
file(GLOB Import_Source  			                src/OpenInfraPlatform/Core/Import/*.*)	
file(GLOB Export_Source  			                src/OpenInfraPlatform/Core/Export/*.*)	

source_group(DataManagement						FILES ${DataManagement_Source})
source_group(IfcGeometryConverter				FILES ${IfcGeometryConverter_Source})
source_group(Import						        FILES ${Import_Source})
source_group(Export						        FILES ${Export_Source})

include_directories(
    ${BLUEFRAMEWORK_INCLUDE_DIR}
    src
	${CMAKE_SOURCE_DIR}/EarlyBinding/src
)

add_library(OpenInfraPlatform.Core STATIC
    ${DataManagement_Source}
    ${IfcGeometryConverter_Source}
    ${Import_Source}
    ${Export_Source}
)

target_link_libraries(OpenInfraPlatform.Core
    Qt5::Core
    Qt5::OpenGL
    Qt5::Xml
    Qt5::XmlPatterns
    ${BLUEFRAMEWORK_LIBRARIES}
    carve
)

foreach(format ${IFC_FORMATS})
	target_link_libraries(OpenInfraPlatform.Core OpenInfraPlatform.${format})
endforeach()