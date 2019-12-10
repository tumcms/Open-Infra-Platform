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

file(GLOB Core_Source 								src/*.*)
file(GLOB Core_DataManagement_Source 				src/DataManagement/*.*)
file(GLOB Core_DataManagement_General_Source 		src/DataManagement/General/*.*)
file(GLOB Core_DataManagement_Command_Source		src/DataManagement/Command/*.*)
#file(GLOB Core_DataManagement_Import_Source		src/DataManagement/Import/*.*)
#file(GLOB Core_DataManagement_Export_Source		src/DataManagement/Export/*.*)
file(GLOB Core_IfcGeometryConverter_Source			src/IfcGeometryConverter/*.*)

source_group(Core								FILES $Core_Source})
source_group(Core\\DataManagement				FILES ${Core_DataManagement_Source})
source_group(Core\\DataManagement\\General		FILES ${Core_DataManagement_General_Source})
source_group(Core\\DataManagement\\Command		FILES ${Core_DataManagement_Command_Source})
#source_group(Core\\DataManagement\\Import		FILES ${Core_DataManagement_Import_Source})
#source_group(Core\\DataManagement\\Export		FILES ${Core_DataManagement_Export_Source})
source_group(Core\\IfcGeometryConverter			FILES ${Core_IfcGeometryConverter_Source})

set(PROJECT_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src ${BLUEFRAMEWORK_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/EarlyBinding/src)

include_directories(${PROJECT_INCLUDE_DIRS})		

add_library(OpenInfraPlatform.Core STATIC
	${Core_Source}
	${Core_DataManagement_Source}
	${Core_DataManagement_General_Source}
	${Core_DataManagement_Command_Source}
	#${Core_DataManagement_Import_Source}
	#${Core_DataManagement_Export_Source}
	${Core_IfcGeometryConverter_Source}
)

target_include_directories(OpenInfraPlatform.Core INTERFACE ${PROJECT_INCLUDE_DIRS} )

# Thirdparty libraries the project depends upon.
target_link_libraries(OpenInfraPlatform.Core PRIVATE
    Qt5::Core
    Qt5::OpenGL
    Qt5::Xml
    Qt5::XmlPatterns
    ${BLUEFRAMEWORK_LIBRARIES}
    carve
    eigen
)

if(MODULES_POINT_CLOUD_PROCESSING)
	add_definitions(-DOIP_WITH_POINT_CLOUD_PROCESSING)
	target_link_libraries(OpenInfraPlatform.Core PUBLIC OpenInfraPlatform.PointCloudProcessing)
	message(STATUS "Linking OpenInfraPlatform.Core against OpenInfraPlatform.PointCloudProcessing")
endif()

foreach(format ${IFC_FORMATS})
	target_link_libraries(OpenInfraPlatform.Core PUBLIC OpenInfraPlatform.${format})
endforeach()

set_target_properties(OpenInfraPlatform.Core 	PROPERTIES FOLDER "OpenInfraPlatform")