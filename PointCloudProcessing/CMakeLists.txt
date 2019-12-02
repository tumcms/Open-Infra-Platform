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

add_definitions(-DBLUEINFRASTRUCTURE_EXPORT)


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

#FetchContent_Declare(
#	libgeo
#	GIT_REPOSITORY https://github.com/OSGeo/libgeotiff.git
#	GIT_TAG 1.5.1
#)
  
#FetchContent_GetProperties(libgeo)
#if(NOT libgeo_POPULATED)
#	FetchContent_Populate(libgeo)
#	add_subdirectory(${libgeo_SOURCE_DIR}/libgeotiff ${libgeo_BINARY_DIR} EXCLUDE_FROM_ALL)
#endif()

# Find thirdparty libraries.
#FetchContent_Declare(
#	liblas
#	GIT_REPOSITORY https://github.com/libLAS/libLAS.git
#	GIT_TAG 1.8.1
#)
  
#FetchContent_GetProperties(liblas)
#if(NOT liblas_POPULATED)
#	FetchContent_Populate(liblas)
#	add_subdirectory(${liblas_SOURCE_DIR} ${liblas_BINARY_DIR} EXCLUDE_FROM_ALL)
#endif()

# Add files.
file(GLOB PointCloudProcessing_Source									src/*.*)	
source_group(PointCloudProcessing										FILES ${PointCloudProcessing_Source})	


# Create a target for the library
add_library(OpenInfraPlatform.PointCloudProcessing SHARED ${PointCloudProcessing_Source})

include_directories(
	src
	${LIBLAS_INCLUDE_DIRS}	
	${CMAKE_CURRENT_BINARY_DIR} 	
	${BLUEFRAMEWORK_INCLUDE_DIR}
	${cc_SOURCE_DIR}/CC/include
	${cc_SOURCE_DIR}/qCC
	${cc_SOURCE_DIR}/libs/qCC_db
	${cc_SOURCE_DIR}/libs/qCC_io
)

target_link_libraries(OpenInfraPlatform.PointCloudProcessing 	
		${LIBLAS_LIBRARIES}	
		${BLUEFRAMEWORK_LIBRARIES}
)

# Use the Widgets module from Qt 5.
target_link_libraries(OpenInfraPlatform.PointCloudProcessing Qt5::Xml Qt5::XmlPatterns Qt5::Gui Qt5::OpenGL eigen CC_CORE_LIB QCC_DB_LIB QCC_IO_LIB)	

# Set the target properties.
set_target_properties(OpenInfraPlatform.PointCloudProcessing			PROPERTIES FOLDER "OpenInfraPlatform")	

endif()