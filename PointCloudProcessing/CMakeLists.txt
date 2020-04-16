#
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
#

#-------------------------------------------------
# POINT CLOUD PROCESSING MODULE.
#-------------------------------------------------

if(MODULES_POINT_CLOUD_PROCESSING)

project(OpenInfraPlatform.PointCloudProcessing)
#include(FetchContent)
include(ExternalData)
add_definitions(-DBLUEINFRASTRUCTURE_EXPORT)


if(OPTION_USE_LIBE57FORMAT)
	message(STATUS "Building with libe57 support.")
		# Find thirdparty libraries.
	FetchContent_Declare(
		xerces_cpp
		GIT_REPOSITORY https://github.com/apache/xerces-c.git
		GIT_TAG 3.2.2
	)

	FetchContent_GetProperties(xerces_cpp)
	if(NOT xerces_cpp)
		FetchContent_Populate(xerces_cpp) 
		add_subdirectory(${xerces_cpp_SOURCE_DIR} ${xerces_cpp_BINARY_DIR} EXCLUDE_FROM_ALL)
	endif()

	get_target_property(xerces_BINARY_DIRECTORY xerces-c BINARY_DIR)
	get_target_property(xerces_OUTPUT_NAME xerces-c OUTPUT_NAME)
	get_target_property(Xerces_INCLUDE_DIR xerces-c INCLUDE_DIRECTORIES)
	
	set(Xerces_LIBRARY_DEBUG ${xerces_BINARY_DIRECTORY}/Debug/${xerces_OUTPUT_NAME}D.lib)
	set(Xerces_LIBRARY_RELEASE ${xerces_BINARY_DIRECTORY}/Release/${xerces_OUTPUT_NAME}.lib)

	set(Xerces_LIBRARY ${Xerces_LIBRARY_DEBUG} ${Xerces_LIBRARY_RELEASE})
	set(XERCES_ROOT ${xerces_cpp_SOURCE_DIR})
	message(STATUS "${Xerces_LIBRARY_DEBUG}, ${Xerces_LIBRARY_RELEASE} and ${Xerces_INCLUDE_DIR} found.")

	if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/libe57.zip")
		file(DOWNLOAD
			"http://sourceforge.net/projects/e57-3d-imgfmt/files/E57Refimpl-src/E57RefImpl_src-1.1.312.zip"
			${CMAKE_CURRENT_BINARY_DIR}/libe57.zip
			SHOW_PROGRESS
		)
		execute_process(COMMAND ${CMAKE_SOURCE_DIR}/external/7za.exe x ${CMAKE_CURRENT_BINARY_DIR}/libe57.zip -o${CMAKE_CURRENT_BINARY_DIR})
	endif()

	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_BINARY_DIR}/E57RefImpl_src-1.1.312/cmake ${CMAKE_CURRENT_BINARY_DIR}/E57RefImpl_src-1.1.312/cmake/Modules)
	add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/E57RefImpl_src-1.1.312 ${CMAKE_CURRENT_BINARY_DIR}/E57RefImpl_src-1.1.312 EXCLUDE_FROM_ALL)
	
	set(LIBE57FORMAT_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/E57RefImpl_src-1.1.312)
endif()


# Find thirdparty libraries.
FetchContent_Declare(
	cc
	GIT_REPOSITORY https://github.com/CloudCompare/CloudCompare.git
	GIT_TAG v2.10.3
)

FetchContent_GetProperties(cc)
if(NOT cc_POPULATED)
	FetchContent_Populate(cc) 
	add_subdirectory(${cc_SOURCE_DIR} ${cc_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

find_package(libLAS REQUIRED)

# Add files.
file(GLOB PointCloudProcessing_Source									src/*.*)	
source_group(PointCloudProcessing										FILES ${PointCloudProcessing_Source})	

# Create a target for the library
set(DEPENDENT_INCLUDE_DIRS
	src
	${LIBLAS_INCLUDE_DIRS}	
	${CMAKE_CURRENT_BINARY_DIR} 	
	${BLUEFRAMEWORK_INCLUDE_DIR}
	${cc_SOURCE_DIR}/CC/include
	${cc_SOURCE_DIR}/libs/qCC_io
	${cc_SOURCE_DIR}/libs/qCC_db
	${cc_SOURCE_DIR}/qCC
)

include_directories(${DEPENDENT_INCLUDE_DIRS})

add_library(OpenInfraPlatform.PointCloudProcessing SHARED ${PointCloudProcessing_Source})

target_include_directories(OpenInfraPlatform.PointCloudProcessing PUBLIC ${DEPENDENT_INCLUDE_DIRS})

target_link_libraries(OpenInfraPlatform.PointCloudProcessing PUBLIC
		${LIBLAS_LIBRARIES}	
		${BLUEFRAMEWORK_LIBRARIES}
)

# Use the Widgets module from Qt 5.
target_link_libraries(OpenInfraPlatform.PointCloudProcessing PUBLIC Qt5::Xml Qt5::XmlPatterns Qt5::Gui Qt5::OpenGL eigen CC_CORE_LIB QCC_DB_LIB QCC_IO_LIB)	

# Set the target properties.
set_target_properties(OpenInfraPlatform.PointCloudProcessing			PROPERTIES FOLDER "OpenInfraPlatform")	

endif()