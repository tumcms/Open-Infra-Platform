#
#    Copyright (c) 2021 Technical University of Munich
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

if(OIP_WITH_POINT_CLOUD_PROCESSING)

project(OpenInfraPlatform.PointCloudProcessing)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH})

include(ExternalData)
add_definitions(-DBLUEINFRASTRUCTURE_EXPORT)

#[[ Find thirdparty libraries.
FetchContent_Declare(
	dep_libtiff
	GIT_REPOSITORY https://gitlab.com/libtiff/libtiff.git
	GIT_TAG v4.3.0
)]]

#FetchContent_GetProperties(dep_libtiff)
#if(NOT dep_libtiff_POPULATED)
#	FetchContent_Populate(dep_libtiff)
#	add_subdirectory(${dep_libtiff_SOURCE_DIR}/libtiff ${dep_libtiff_BINARY_DIR} EXCLUDE_FROM_ALL)
#
#	set_target_properties(tiff_library PROPERTIES FOLDER "ThirdParty")
#endif()

#set(TIFF_INCLUDE_DIR "C:/dev/LibTiff/LibTiff/libtiff/libtiff")
#set(TIFF_LIBRARIES "C:/dev/LibTiff/LibTiff/build/libtiff/Debug/tiffd.dll")
#set(TIFF_DIRECTORY )
#if point cloud
#findtiff()
#set(TIFF_INCLUDE_DIR "C:/OSGeo4W/include")
#set(TIFF_LIBRARY "C:/OSGeo4W/lib/tiff.lib")
#find_package(TIFF REQUIRED)

#[[FetchContent_Declare(
	dep_libgeo
	GIT_REPOSITORY https://github.com/OSGeo/libgeotiff.git
	GIT_TAG 1.6.0
)
  
FetchContent_GetProperties(dep_libgeo)
if(NOT dep_libgeo_POPULATED)
	FetchContent_Populate(dep_libgeo)
	add_subdirectory(${dep_libgeo_SOURCE_DIR}/libgeotiff ${dep_libgeo_BINARY_DIR} EXCLUDE_FROM_ALL)

	set_target_properties(geotiff_library PROPERTIES FOLDER "ThirdParty")
endif()]]

#set(GeoTIFF_INCLUDE_DIR "C:/OSGeo4W/include")
#set(GeoTIFF_LIBRARY "C:/OSGeo4W/lib/geotiff_i.lib")
#find_package(GeoTIFF REQUIRED)

#[[FetchContent_Declare(
	dep_liblas
	GIT_REPOSITORY https://github.com/libLAS/libLAS.git
	GIT_TAG 6ada875661c46842433a13f28637f8d3d2c393bc
)

FetchContent_GetProperties(dep_liblas)

set(WITH_UTILITIES FALSE CACHE INTERNAL "Build libLAS with utilities" FORCE)
set(WITH_TESTS FALSE CACHE INTERNAL "Build libLAS with tests" FORCE)
mark_as_advanced(FORCE WITH_UTILITIES WITH_TESTS)

if(NOT dep_liblas_POPULATED)
	FetchContent_Populate(dep_liblas)
	add_subdirectory(${dep_liblas_SOURCE_DIR} ${dep_liblas_BINARY_DIR} EXCLUDE_FROM_ALL)

	set_target_properties(las PROPERTIES FOLDER "ThirdParty/libLAS")
	set_target_properties(las_c PROPERTIES FOLDER "ThirdParty/libLAS")
endif()]]

set(libLAS_INCLUDE_DIR "C:/OSGeo4W/include")
set(libLAS_LIBRARY "C:/OSGeo4W/lib/liblas.lib")
find_path(libLAS_DIR NAMES liblas-config.cmake HINTS "C:\\OSGeo4W\\cmake")
set (CMAKE_PREFIX_PATH ${libLAS_DIR})
find_package(libLAS REQUIRED)

FetchContent_Declare(
	cc
	GIT_REPOSITORY https://github.com/CloudCompare/CloudCompare.git
	GIT_TAG v2.10.3
)

FetchContent_GetProperties(cc)
if(NOT cc_POPULATED)
	FetchContent_Populate(cc) 
	add_subdirectory(${cc_SOURCE_DIR} ${cc_BINARY_DIR} EXCLUDE_FROM_ALL)

	set_target_properties(CC_FBO_LIB PROPERTIES FOLDER "ThirdParty/CloudCompare")
	set_target_properties(CC_CORE_LIB PROPERTIES FOLDER "ThirdParty/CloudCompare")
	set_target_properties(QCC_DB_LIB PROPERTIES FOLDER "ThirdParty/CloudCompare")
	set_target_properties(QCC_IO_LIB PROPERTIES FOLDER "ThirdParty/CloudCompare")
endif()



# Add files.
file(GLOB PointCloudProcessing_Source									src/*.*)	
source_group(PointCloudProcessing										FILES ${PointCloudProcessing_Source})	

# Create a target for the library
set(DEPENDENT_INCLUDE_DIRS
	src
	#${TIFF_INCLUDE_DIR}
	#${GeoTIFF_INCLUDE_DIR}
	#${dep_libgeo_SOURCE_DIR}/include
	#${dep_liblas_SOURCE_DIR}/include
	${libLAS_INCLUDE_DIR}/include
	${CMAKE_CURRENT_BINARY_DIR} 	
	${blue_framework_SOURCE_DIR}/include
	${cc_SOURCE_DIR}/CC/include
	${cc_SOURCE_DIR}/libs/qCC_io
	${cc_SOURCE_DIR}/libs/qCC_db
	${cc_SOURCE_DIR}/qCC
)

include_directories(${DEPENDENT_INCLUDE_DIRS})

add_library(OpenInfraPlatform.PointCloudProcessing SHARED ${PointCloudProcessing_Source})

target_include_directories(OpenInfraPlatform.PointCloudProcessing PUBLIC ${DEPENDENT_INCLUDE_DIRS})

target_link_libraries(OpenInfraPlatform.PointCloudProcessing PUBLIC
		#las
		#las_c
	    #${TIFF_LIBRARIES}
	    #${GeoTIFF_LIBRARIES}
		#geotiff_library
		${libLAS_LIBRARIES}
		BlueFramework.ImageProcessing
		BlueFramework.Rasterizer
		OpenInfraPlatform.Base
)

# Use the Widgets module from Qt 5.
target_link_libraries(OpenInfraPlatform.PointCloudProcessing PUBLIC Qt5::Xml Qt5::XmlPatterns Qt5::Gui Qt5::OpenGL eigen CC_CORE_LIB QCC_DB_LIB QCC_IO_LIB)	

# Set the target properties.
set_target_properties(OpenInfraPlatform.PointCloudProcessing			PROPERTIES FOLDER "OpenInfraPlatform")	

endif()
