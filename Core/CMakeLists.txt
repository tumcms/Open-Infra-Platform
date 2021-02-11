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
file(GLOB Core_IfcGeometryConverter_Source			src/IfcGeometryConverter/*.*)
file(GLOB Core_OffConverter_Source					src/OffConverter/*.*)
file(GLOB Core_Exception_Source						src/Exception/*.*)
file(GLOB Core_SplineInterpretation_Source			src/SplineInterpretation/*.*)

source_group(Core								FILES $Core_Source})
source_group(Core\\DataManagement				FILES ${Core_DataManagement_Source})
source_group(Core\\DataManagement\\General		FILES ${Core_DataManagement_General_Source})
source_group(Core\\IfcGeometryConverter			FILES ${Core_IfcGeometryConverter_Source})
source_group(Core\\OffConverter					FILES ${Core_OffConverter_Source})
source_group(Core\\Exception					FILES ${Core_Exception_Source})
source_group(Core\\SplineInterpretation			FILES ${Core_SplineInterpretation_Source})

add_library(OpenInfraPlatform.Core STATIC
	${Core_Source}
	${Core_DataManagement_Source}
	${Core_DataManagement_General_Source}
	${Core_IfcGeometryConverter_Source}
	${Core_OffConverter_Source}
	${Core_Exception_Source}
	${Core_SplineInterpretation_Source}
)


target_include_directories(OpenInfraPlatform.Core
	PUBLIC 
		${PROJECT_SOURCE_DIR}/src
		${BLUEFRAMEWORK_INCLUDE_DIR}
		${CMAKE_SOURCE_DIR}/EarlyBinding/src
)

# Thirdparty libraries the project depends upon.
target_link_libraries(OpenInfraPlatform.Core PRIVATE
    Qt5::Core
    Qt5::OpenGL
    Qt5::Xml
    Qt5::XmlPatterns
    BlueFramework.Core
	BlueFramework.Rasterizer
	BlueFramework.Application
    carve
    eigen
)

target_link_libraries(OpenInfraPlatform.Core PUBLIC OpenInfraPlatform.Base)

if(MODULES_POINT_CLOUD_PROCESSING)
	add_definitions(-DOIP_WITH_POINT_CLOUD_PROCESSING)
	target_link_libraries(OpenInfraPlatform.Core PUBLIC OpenInfraPlatform.PointCloudProcessing)
	message(STATUS "Linking OpenInfraPlatform.Core against OpenInfraPlatform.PointCloudProcessing")
endif()

foreach(format ${IFC_FORMATS})
	target_link_libraries(OpenInfraPlatform.Core PUBLIC OpenInfraPlatform.${format})
endforeach()

#set_target_properties(OpenInfraPlatform.Core 	PROPERTIES FOLDER "OpenInfraPlatform")
