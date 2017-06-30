#
#    Copyright (c) 2017 Technical University of Munich
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

cmake_minimum_required(VERSION 3.8)
cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0048 NEW)
project(OpenInfraPlatform VERSION "2.20.0.0")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#------------------------------------------------------------------------------
# Create folders for different build configurations (if they do not exist)
#------------------------------------------------------------------------------

if(EXISTS ${CMAKE_BINARY_DIR}/Debug)
else()
  file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)
endif()

if(EXISTS ${CMAKE_BINARY_DIR}/Release)
else()
  file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Release)
endif()

if(EXISTS ${CMAKE_BINARY_DIR}/RelWithDebInfo)
else()
  file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/RelWithDebInfo)
endif()

#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Some checks to ensure that the prerequisites are ok
#------------------------------------------------------------------------------

if(NOT MSVC14)
	message("Please switch to Visual Studio 14 2015.")
	return()
endif()

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8 )
    message("Please switch to x64 build.")
	return()
endif()

#------------------------------------------------------------------------------

option(OIP_USE_PREDEFINED_THIRDPARTY_PATH "Set to ON to set boost, Eigen and Qt path" ON)
option(OIP_USE_PREBUILD_EARLYBINDING_LIBS "Set to OFF to build early binding by yourself" ON)

if(OIP_USE_PREDEFINED_THIRDPARTY_PATH)
	# Try to find Boost, Eigen3, Qt5 and other dependencies without user input
	find_path(BOOST_ROOT NAMES boost/version.hpp HINTS "C:\\thirdparty\\vs2015\\x64\\boost_1_64_0")
	find_path(EIGEN3_INCLUDE_DIR NAMES Eigen/Core HINTS "C:\\thirdparty\\vs2015\\x64\\Eigen_3.3.4" "C:\\thirdparty\\vs2015\\x64\\Eigen_3.3.3")
	find_path(CMAKE_PREFIX_PATH NAMES include/QtCore/QObject HINTS "C:\\Qt\\Qt5.9.1\\5.9.1\\msvc2015_64" "C:\\Qt\\Qt5.9.0\\5.9\\msvc2015_64")
	find_path(GTEST_ROOT NAMES googletest/include/gtest/gtest.h HINTS "C:\\thirdparty\\vs2015\\x64\\googletest-release-1.8.0" "C:\\thirdparty\\vs2015\\x64\\googletest-1.8.0")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG     ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG         ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE   ${CMAKE_BINARY_DIR}/Release)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE       ${CMAKE_BINARY_DIR}/Release)

add_definitions(-D_UNICODE 			# Unicode rules
				-DQT_NO_KEYWORDS 	# No qt keywords
				-D_VARIADIC_MAX=10 	# Visual Studio 2012 set VARIDAIC_MAX default to 5 which is not enough for googletest to build
) # -DNOMINMAX does not work because GDI+ needs these macros

# Compiler settings
if (WIN32)
	# Standard:          /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR
	set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W4 /Zi /EHsc /GR /MP /openmp /bigobj")
endif (WIN32)

# tell cmake where to look for our scripts
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)

# Visual Studio expected
# Find Boost
set(Boost_USE_STATIC_LIBS   ON)
find_package(Boost				1.63.0 COMPONENTS signals system filesystem thread program_options python REQUIRED)

#Find VisualLeakDetector
find_package(VLD 					   REQUIRED)

#Find BlueFramework root dir
#set(BLUEFRAMEWORK3_USE_INSTALLED FALSE CACHE BOOL "bool")
#set(BLUEFRAMEWORK3_ROOT "" CACHE PATH "path")
find_package(BlueFramework3		3.0.491 COMPONENTS Core Engine Application ImageProcessing Rasterizer D3D11RenderSystem D3D12RenderSystem REQUIRED)

#Find Eigen
find_package(Eigen3             3.3.2  REQUIRED)
#Find Python
#unset(PYTHON_LIBRARY)
find_package(PythonLibs 		3.5.2  REQUIRED)

# Find the Oklabi libraries
find_package(Oklabi)


#Gtest
if(NOT GTEST_ROOT)
	include(external/cmake/InstallGTest.cmake)
endif()

find_package(gtest REQUIRED) #reduce to this line

if(NOT gtest OR NOT GTEST_ROOT)
	include(external/cmake/FindGTest.cmake)
endif()
GTEST_COPY_BINARIES(${CMAKE_BINARY_DIR})

#ZLib
if(NOT ZLIB_ROOT)
	include(external/cmake/InstallZLIB.cmake)
endif()

if(NOT ZLIB_LIBRARY)
	include(external/cmake/FindZLIB.cmake)
endif()
if(ZLIB_LIBRARY_RELEASE AND ZLIB_LIBRARY_DEBUG)
	set(ZLIB_LIBRARY debug "${ZLIB_LIBRARY_DEBUG}" optimized "${ZLIB_LIBRARY_RELEASE}")
endif()
find_package(ZLIB REQUIRED)


# Find the Qt components
set(QT5_COMPONENTS
	Core 
	Xml
	XmlPatterns
	Widgets
	Network
	Svg
	PrintSupport
	LinguistTools
	Qml
	Quick
	Positioning
	Location)

foreach(Component ${QT5_COMPONENTS})
	find_package( Qt5 5.7.0 COMPONENTS ${Component}	REQUIRED)
	if(TARGET ${Qt5${Component}_LIBRARIES})
		get_target_property(Qt5${Component}_location ${Qt5${Component}_LIBRARIES} LOCATION_Release)
		set(QT5_DLLS_RELEASE ${QT5_DLLS_RELEASE} ${Qt5${Component}_location})
		get_target_property(Qt5${Component}_location ${Qt5${Component}_LIBRARIES} LOCATION_Debug)
		set(QT5_DLLS_DEBUG ${QT5_DLLS_DEBUG} ${Qt5${Component}_location})
	endif()
endforeach()

string(REPLACE "lib/cmake/Qt5" "bin" Qt5_BIN_DIR "${Qt5_DIR}")

macro(addQt5Dll lib)
	set(QT5_DLLS_RELEASE ${QT5_DLLS_RELEASE} ${Qt5_BIN_DIR}/Qt5${lib}.dll)
	set(QT5_DLLS_DEBUG ${QT5_DLLS_DEBUG} ${Qt5_BIN_DIR}/Qt5${lib}d.dll)
endmacro()

addQt5Dll(Gui)
addQt5Dll(Multimedia)
addQt5Dll(MultimediaWidgets)
addQt5Dll(OpenGL)
addQt5Dll(Script)
addQt5Dll(Sensors)
addQt5Dll(Sql)
addQt5Dll(WebChannel)

include_directories(
	${CMAKE_CURRENT_BINARY_DIR} # Qt generated files will be located here
	${Boost_INCLUDE_DIR}
	${VLD_INCLUDE_DIR}
	${BLUEFRAMEWORK3_INCLUDE_DIR}
	${EIGEN3_INCLUDE_DIR}
	${PYTHON_INCLUDE_DIRS}
	#DirectX for rendering
	${DirectX12_INCLUDE_DIR}
	${DirectX12_INCLUDE_DIR_SHARED}
	src
	external/QtXlsxWriter/src/xlsx
	external/QSimpleUpdater/src
	external/QSimpleUpdater/dialogs
	Infrastructure/canonicalHeaders
	${ZLIB_INCLUDE_DIR}
)

link_directories(
	${Boost_LIBRARY_DIRS}
	${VLD_LIBRARIES_DIR}
	${OKLABI_ROOT_DIR}
	${CMAKE_CURRENT_BINARY_DIR}/external/zlib/src
)

# macro for precompiled header - see also http://stackoverflow.com/questions/148570/using-pre-compiled-headers-with-cmake
#MACRO(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
#  IF(MSVC)
#    GET_FILENAME_COMPONENT(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
#    SET(PrecompiledBinary "${CMAKE_CURRENT_BINARY_DIR}/${PrecompiledBasename}.pch")
#    SET(Sources ${${SourcesVar}})
#
#    SET_SOURCE_FILES_PROPERTIES(${PrecompiledSource}
#                                PROPERTIES COMPILE_FLAGS "/Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
#                                           OBJECT_OUTPUTS "${PrecompiledBinary}")
#    SET_SOURCE_FILES_PROPERTIES(${Sources}
#                                PROPERTIES COMPILE_FLAGS "/Yu\"${PrecompiledHeader}\" /FI\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
#                                           OBJECT_DEPENDS "${PrecompiledBinary}")
#    # Add precompiled header to SourcesVar
#    LIST(APPEND ${SourcesVar} ${PrecompiledSource})
#  ENDIF(MSVC)
#ENDMACRO(ADD_MSVC_PRECOMPILED_HEADER)

# BlueFramework Copy Binaries
BLUEFRAMEWORK3_COPY_BINARIES(${CMAKE_BINARY_DIR})

# Oklabi Copy Binaries
OKLABI_COPY_BINARIES(${CMAKE_BINARY_DIR})

# QtXlsxWriter
add_subdirectory(external/QtXlsxWriter)

# QSimpleUpdater
add_subdirectory(external/QSimpleUpdater)

# libLAS
#add_subdirectory(external/libLAS-1.7.0)

if(NOT LIBLAS_ROOT)
	include(external/cmake/InstallLiblas.cmake)
endif()
include(external/cmake/FindLiblas.cmake)
LIBLAS_COPY_BINARIES(${CMAKE_BINARY_DIR})

if(NOT QHULL_ROOT)
	include(external/cmake/InstallQhull.cmake)
endif()
include(external/cmake/FindQhull.cmake)

#add_subdirectory(${PROJECT_SOURCE_DIR}/external/qhull)
#include_directories(external/qhull/src)

#####################################################################################################
# add carve
#####################################################################################################

#add_definitions(-DCARVE_SYSTEM_BOOST) # use system boost directories

include_directories(external/carve/include)
include_directories(${CMAKE_BINARY_DIR}/external/carve/include) #for out of source builds
include_directories(external/carve/common)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/carve)
set_target_properties(carve 								PROPERTIES FOLDER "ThirdParty/carve")

macro (find_prebuild_earlybinding library) 
	find_file(OpenInfraPlatform_${library}_LIBRARY_RELEASE
		NAMES OpenInfraPlatform.${library}.lib
		HINTS ${OIP_PRBEUILD_LIBS_DIR} REQUIRED)
		
	find_file(OpenInfraPlatform_${library}_LIBRARY_DEBUG
		NAMES OpenInfraPlatform.${library}d.lib
		HINTS ${OIP_PRBEUILD_LIBS_DIR} REQUIRED)
		
	set(OpenInfraPlatform_${library}_LIBRARY
		optimized 	${OpenInfraPlatform_${library}_LIBRARY_RELEASE}
		debug		${OpenInfraPlatform_${library}_LIBRARY_DEBUG})
endmacro()

# Earlybinding
if(OIP_USE_PREBUILD_EARLYBINDING_LIBS)
	include_directories(
		Ifc2x3/src
		Ifc4/src
		IfcAlignment/src
		IfcAlignment1x1/src
		IfcBridge/src
		IfcRoad/src
		IfcTunnel/src
	)
	
	set(OIP_PRBEUILD_LIBS_DIR ${PROJECT_SOURCE_DIR}/prebuild_libs/vs2015/x64/)

	link_directories(${OIP_PRBEUILD_LIBS_DIR})
		
	find_prebuild_earlybinding(Ifc2x3)
	find_prebuild_earlybinding(IfcAlignment)
	find_prebuild_earlybinding(IfcAlignment1x1)
	find_prebuild_earlybinding(Ifc4)
	find_prebuild_earlybinding(IfcBridge)
	find_prebuild_earlybinding(IfcRoad)
	find_prebuild_earlybinding(IfcTunnel)
			
else(OIP_USE_PREBUILD_EARLYBINDING_LIBS)
	# add Ifc2x3
	add_subdirectory(Ifc2x3)
	include_directories(Ifc2x3/src)

	# add Ifc4
	add_subdirectory(Ifc4)
	include_directories(Ifc4/src)

	# add IfcAlignment
	add_subdirectory(IfcAlignment)
	include_directories(IfcAlignment/src)

	# add IfcAlignment1x1
	add_subdirectory(IfcAlignment1x1)
	include_directories(IfcAlignment1x1/src)

	# add IfcBridge
	add_subdirectory(IfcBridge)
	include_directories(IfcBridge/src)

	# add IfcRoad
	add_subdirectory(IfcRoad)
	include_directories(IfcRoad/src)

	# add IfcTunnel
	add_subdirectory(IfcTunnel)
	include_directories(IfcTunnel/src)
endif(OIP_USE_PREBUILD_EARLYBINDING_LIBS)

# add ExpressBinding
add_subdirectory(ExpressBinding)
include_directories(ExpressBinding/src)

# add source directory
add_subdirectory(Infrastructure)
include_directories(Infrastructure/src)

add_subdirectory(UnitTests)

add_definitions(-DNOMINMAX)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

file(GLOB OpenInfraPlatform_QtPropertyBrowser_Source 				src/QtPropertyBrowser/*.*)

file(GLOB OpenInfraPlatform_Core_Source 							src/OpenInfraPlatform/Core/*.*)
file(GLOB OpenInfraPlatform_Data_Source 							src/OpenInfraPlatform/Data/*.*)
file(GLOB OpenInfraPlatform_DataManagement_Command_Source 			src/OpenInfraPlatform/DataManagement/Command/*.*)
file(GLOB OpenInfraPlatform_DataManagement_Source 					src/OpenInfraPlatform/DataManagement/*.*)
file(GLOB OpenInfraPlatform_IfcGeometryConverter_Source  			src/OpenInfraPlatform/IfcGeometryConverter/*.*)
file(GLOB_RECURSE OpenInfraPlatform_Shader_Header					src/OpenInfraPlatform/Shader/*.hlsl.inc)
file(GLOB OpenInfraPlatform_Shader_D3D12_Source 					src/OpenInfraPlatform/Shader/D3D12/*.hlsl)
file(GLOB OpenInfraPlatform_Shader_D3D11_Source 					src/OpenInfraPlatform/Shader/D3D11/*.*)
file(GLOB OpenInfraPlatform_Shader_GL4x_Source 						src/OpenInfraPlatform/Shader/GL4x/*.*)
file(GLOB OpenInfraPlatform_Shader_Source 							src/OpenInfraPlatform/Shader/*.*)
file(GLOB OpenInfraPlatform_Source									src/OpenInfraPlatform/*.*)
file(GLOB OpenInfraPlatform_UnitTesting_Source						src/OpenInfraPlatform/UnitTesting/*.*)
file(GLOB OpenInfraPlatform_UserInterface_ColorPicker_Source		src/OpenInfraPlatform/UserInterface/ColorPicker/*.*)
file(GLOB OpenInfraPlatform_UserInterface_Tools_Source				src/OpenInfraPlatform/UserInterface/Tools/*.*)
file(GLOB OpenInfraPlatform_UserInterface_Source 					src/OpenInfraPlatform/UserInterface/*.*)
file(GLOB OpenInfraPlatform_UserInterface_View2DWindow			 	src/OpenInfraPlatform/UserInterface/View2DWindow/*.*)
file(GLOB OpenInfraPlatform_UserInterface_ViewPanel_Source 			src/OpenInfraPlatform/UserInterface/ViewPanel/*.*)
file(GLOB OpenInfraPlatform_UserInterface_ViewPanel_Effects_Source 	src/OpenInfraPlatform/UserInterface/ViewPanel/Effects/*.*)


source_group(OpenInfraPlatform										FILES ${OpenInfraPlatform_Source})
source_group(OpenInfraPlatform\\Core								FILES ${OpenInfraPlatform_Core_Source})
source_group(OpenInfraPlatform\\Data								FILES ${OpenInfraPlatform_Data_Source})
source_group(OpenInfraPlatform\\DataManagement						FILES ${OpenInfraPlatform_DataManagement_Source})
source_group(OpenInfraPlatform\\DataManagement\\Command				FILES ${OpenInfraPlatform_DataManagement_Command_Source})
source_group(OpenInfraPlatform\\IfcGeometryConverter				FILES ${OpenInfraPlatform_IfcGeometryConverter_Source})
source_group(OpenInfraPlatform\\Shader								FILES ${OpenInfraPlatform_Shader_Source})
source_group(OpenInfraPlatform\\Shader\\Header						FILES ${OpenInfraPlatform_Shader_Header})
source_group(OpenInfraPlatform\\Shader\\D3D12						FILES ${OpenInfraPlatform_Shader_D3D12_Source})
source_group(OpenInfraPlatform\\Shader\\D3D11						FILES ${OpenInfraPlatform_Shader_D3D11_Source})
source_group(OpenInfraPlatform\\Shader\\GL4x						FILES ${OpenInfraPlatform_Shader_GL4x_Source})
source_group(OpenInfraPlatform\\UnitTesting  						FILES ${OpenInfraPlatform_UnitTesting_Source})
source_group(OpenInfraPlatform\\UserInterface						FILES ${OpenInfraPlatform_UserInterface_Source})
source_group(OpenInfraPlatform\\UserInterface\\ColorPicker			FILES ${OpenInfraPlatform_UserInterface_ColorPicker_Source})
source_group(OpenInfraPlatform\\UserInterface\\Tools				FILES ${OpenInfraPlatform_UserInterface_Tools_Source})
source_group(OpenInfraPlatform\\UserInterface\\View2DWindow			FILES ${OpenInfraPlatform_UserInterface_View2DWindow})
source_group(OpenInfraPlatform\\UserInterface\\ViewPanel			FILES ${OpenInfraPlatform_UserInterface_ViewPanel_Source})
source_group(OpenInfraPlatform\\UserInterface\\ViewPanel\\Effects	FILES ${OpenInfraPlatform_UserInterface_ViewPanel_Effects_Source})
source_group(QtPropertyBrowser										FILES ${OpenInfraPlatform_QtPropertyBrowser_Source})


set_property(SOURCE ${OpenInfraPlatform_Shader_D3D12_Source} PROPERTY VS_SHADER_TYPE Vertex)
set_property(SOURCE ${OpenInfraPlatform_Shader_D3D12_Source} PROPERTY VS_SHADER_ENTRYPOINT VS_main)
set_property(SOURCE ${OpenInfraPlatform_Shader_D3D12_Source} PROPERTY VS_SHADER_MODEL 5.0)
set_property(SOURCE ${OpenInfraPlatform_Shader_D3D12_Source} PROPERTY PS_SHADER_TYPE PIXEL)
set_property(SOURCE ${OpenInfraPlatform_Shader_D3D12_Source} PROPERTY PS_SHADER_ENTRYPOINT PS_main)
set_property(SOURCE ${OpenInfraPlatform_Shader_D3D12_Source} PROPERTY PS_SHADER_MODEL 5.0)

set_property(SOURCE ${OpenInfraPlatform_Shader_D3D11_Source} PROPERTY VS_SHADER_TYPE Vertex)
set_property(SOURCE ${OpenInfraPlatform_Shader_D3D11_Source} PROPERTY VS_SHADER_ENTRYPOINT VS_main)
set_property(SOURCE ${OpenInfraPlatform_Shader_D3D11_Source} PROPERTY VS_SHADER_MODEL 5.0)
set_property(SOURCE ${OpenInfraPlatform_Shader_D3D11_Source} PROPERTY PS_SHADER_TYPE PIXEL)
set_property(SOURCE ${OpenInfraPlatform_Shader_D3D11_Source} PROPERTY PS_SHADER_ENTRYPOINT PS_main)
set_property(SOURCE ${OpenInfraPlatform_Shader_D3D11_Source} PROPERTY PS_SHADER_MODEL 5.0)


file(GLOB BlueFramework_GraphicsEngine_Source 					src/BlueFramework/GraphicsEngine/*.*)
source_group(BlueFramework\\GraphicsEngine						FILES ${BlueFramework_GraphicsEngine_Source})

file(GLOB BlueFramework_Core_Source 							src/BlueFramework/Core/*.*)
source_group(BlueFramework\\Core								FILES ${BlueFramework_Core_Source})

IF(NOT QT_LRELEASE_EXECUTABLE AND NOT Qt5_LRELEASE_EXECUTABLE)
	MESSAGE(WARNING "Could not find lrelease. Your build won't contain translations.")
ENDIF(NOT QT_LRELEASE_EXECUTABLE AND NOT Qt5_LRELEASE_EXECUTABLE)

#ADD_MSVC_PRECOMPILED_HEADER(
#	"precompiled.h"
#	"src/OpenInfraPlatform/precompiled.cpp"
#	OpenInfraPlatform_UserInterface_Source)


# Qt related stuff
set(OpenInfraPlatform_UIS
	external/QSimpleUpdater/src/dialogs/download_dialog.ui
	src/OpenInfraPlatform/Forms/CodeEditorWindow.ui
	src/OpenInfraPlatform/Forms/CreateArcClothoidArc.ui
	src/OpenInfraPlatform/Forms/CreateArcClothoidArcMeth2.ui
	src/OpenInfraPlatform/Forms/CreateArcClothoidClothoidArc.ui
	src/OpenInfraPlatform/Forms/CreateArcClothoidClothoidArcMeth2.ui
	src/OpenInfraPlatform/Forms/CreateClothoid.ui
	src/OpenInfraPlatform/Forms/CreateClothoid2.ui
	src/OpenInfraPlatform/Forms/CreateLineArcArcArcLine.ui
	src/OpenInfraPlatform/Forms/CreateLineArcArcLine.ui
	src/OpenInfraPlatform/Forms/CreateLineClothoidArcClothoidLine.ui
	src/OpenInfraPlatform/Forms/CreateLineClothoidClothoidLine.ui
	src/OpenInfraPlatform/Forms/CurvatureWindow.ui
	src/OpenInfraPlatform/Forms/ExportExcel.ui
	src/OpenInfraPlatform/Forms/ExportIfcAlignment1x1Dialog.ui
	src/OpenInfraPlatform/Forms/ExportIfcAlignmentDialog.ui
	src/OpenInfraPlatform/Forms/ExportIfcZipDialog.ui
	src/OpenInfraPlatform/Forms/GenerateTerrain.ui
	src/OpenInfraPlatform/Forms/MainWindow.ui
	src/OpenInfraPlatform/Forms/OSMImportDialog.ui
	src/OpenInfraPlatform/Forms/PreferencesDialog.ui
	src/OpenInfraPlatform/Forms/VerticalAlignmentWindow.ui
	src/OpenInfraPlatform/Forms/XYZImportDialog.ui
)

source_group(OpenInfraPlatform\\UserInterface\\Forms					FILES ${OpenInfraPlatform_UIS})

set(OpenInfraPlatform_RC
	src/OpenInfraPlatform/Resources/OpenInfraPlatform.qrc
	src/QtPropertyBrowser/qtpropertybrowser.qrc
)

QT5_ADD_RESOURCES(OpenInfraPlatform_RC_SRCS ${OpenInfraPlatform_RC})
QT5_WRAP_UI(OpenInfraPlatform_UIS_H ${OpenInfraPlatform_UIS})

# Tell CMake to create the Qt5HelloWorld executable
add_executable(OpenInfraPlatform.UI
	${OpenInfraPlatform_QtPropertyBrowser_Source}
	${OpenInfraPlatform_UIS_H}
	${OpenInfraPlatform_RC_SRCS}
	${OpenInfraPlatform_Source}
	${OpenInfraPlatform_UserInterface_Source}
	${OpenInfraPlatform_UserInterface_ColorPicker_Source}
	${OpenInfraPlatform_UserInterface_Tools_Source}
	${OpenInfraPlatform_UserInterface_ViewPanel_Source}
	${OpenInfraPlatform_UserInterface_ViewPanel_Effects_Source}
	${OpenInfraPlatform_UserInterface_View2DWindow}
	${OpenInfraPlatform_UnitTesting_Source}
	${OpenInfraPlatform_Data_Source}
	${OpenInfraPlatform_DataManagement_Source}
	${OpenInfraPlatform_DataManagement_Command_Source}
	${OpenInfraPlatform_IfcGeometryConverter_Source}
	${OpenInfraPlatform_Shader_Source}
	${OpenInfraPlatform_Shader_Header}
	${OpenInfraPlatform_Shader_D3D12_Source}
	${OpenInfraPlatform_Shader_D3D11_Source}
	${OpenInfraPlatform_Shader_GL4x_Source}
	${OpenInfraPlatform_Core_Source}
)

set(CMAKE_DEBUG_POSTFIX "d")
# Use the Widgets module from Qt 5.
qt5_use_modules(OpenInfraPlatform.UI Widgets Xml XmlPatterns Svg PrintSupport Quick Qml Location Positioning)

if(OIP_USE_PREBUILD_EARLYBINDING_LIBS)
	target_link_libraries( OpenInfraPlatform.UI
		OpenInfraPlatform.Infrastructure
		# Early bindings
		${OpenInfraPlatform_Ifc2x3_LIBRARY}
		${OpenInfraPlatform_Ifc4_LIBRARY}
		${OpenInfraPlatform_IfcAlignment_LIBRARY}
		${OpenInfraPlatform_IfcAlignment1x1_LIBRARY}
		${OpenInfraPlatform_IfcBridge_LIBRARY}
		${OpenInfraPlatform_IfcRoad_LIBRARY}
		${OpenInfraPlatform_IfcTunnel_LIBRARY}
		# Qt
		Qt5::WinMain  # New target available via find_package ( Qt5Core )
		# BlueFramework
		${BLUEFRAMEWORK3_LIBRARIES}
		# External libs
		QtXlsxWriter
		QSimpleUpdater
		${LIBLAS_LIB}
		carve
		# Python
		${PYTHON_LIBRARIES}
		${ZLIB_LIB}
	)
elseif(OIP_USE_PREBUILD_EARLYBINDING_LIBS)
	target_link_libraries( OpenInfraPlatform.UI
		OpenInfraPlatform.Infrastructure
		# Early bindings
		OpenInfraPlatform.Ifc2x3
		OpenInfraPlatform.Ifc4
		OpenInfraPlatform.IfcAlignment
		OpenInfraPlatform.IfcAlignment1x1
		OpenInfraPlatform.IfcBridge
		OpenInfraPlatform.IfcRoad
		# Qt
		Qt5::WinMain  # New target available via find_package ( Qt5Core )
		# BlueFramework
		${BLUEFRAMEWORK3_LIBRARIES}
		# External libs
		QtXlsxWriter
		QSimpleUpdater
		${LIBLAS_LIB}
		carve
		# Python
		${PYTHON_LIBRARIES}
		${ZLIB_LIB}
	)
endif(OIP_USE_PREBUILD_EARLYBINDING_LIBS)

target_link_libraries( OpenInfraPlatform.UI
	OpenInfraPlatform.Infrastructure
	OpenInfraPlatform.IfcBridge
	OpenInfraPlatform.IfcRoad
	OpenInfraPlatform.IfcAlignment
	OpenInfraPlatform.IfcAlignment1x1
	OpenInfraPlatform.Ifc2x3
	OpenInfraPlatform.Ifc4
	Qt5::WinMain  # New target available via find_package ( Qt5Core )
	# BlueFramework
	${BLUEFRAMEWORK3_LIBRARIES}
	# External libs
	QtXlsxWriter
	QSimpleUpdater
	${LIBLAS_LIB}
	carve
	# Python
	${PYTHON_LIBRARIES}
	${ZLIB_LIB}
)

# Python35
add_custom_target(Python35CopyBinaries
	COMMAND	${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deploy/python/python35.dll		${CMAKE_BINARY_DIR}/Debug
	COMMAND	${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deploy/python/python35.dll		${CMAKE_BINARY_DIR}/Release

	# Output Message
	COMMENT "Copying Pyhton35 binaries from ' ${CMAKE_CURRENT_SOURCE_DIR}/deploy/python' to '${CMAKE_BINARY_DIR}'" VERBATIM
)

# QtCopyBinaries
add_custom_target(Qt5CopyBinaries
	COMMAND ${CMAKE_COMMAND} -E copy ${QT5_DLLS_RELEASE} ${CMAKE_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${QT5_DLLS_RELEASE} ${CMAKE_BINARY_DIR}/RelWithDebInfo
	COMMAND ${CMAKE_COMMAND} -E copy ${QT5_DLLS_DEBUG} ${CMAKE_BINARY_DIR}/Debug	

	COMMAND	${CMAKE_COMMAND} -E copy_directory ${Qt5Core_DIR}/../../../qml						${CMAKE_BINARY_DIR}/Release/qml
	COMMAND	${CMAKE_COMMAND} -E copy_directory ${Qt5Core_DIR}/../../../plugins/geoservices		${CMAKE_BINARY_DIR}/Release/plugins/geoservices
	COMMAND	${CMAKE_COMMAND} -E copy_directory ${Qt5Core_DIR}/../../../plugins/imageformats		${CMAKE_BINARY_DIR}/Release/plugins/imageformats
	COMMAND	${CMAKE_COMMAND} -E copy_directory ${Qt5Core_DIR}/../../../plugins/platforms		${CMAKE_BINARY_DIR}/Release/platforms

	# Output Message
	COMMENT "Copying Ot binaries from '${Qt5Core_DIR}/../../bin/' to '${CMAKE_BINARY_DIR}'" VERBATIM
)

# Collect all translation files
FILE(GLOB Translation_TS Data/translations/*.ts)
QT5_ADD_TRANSLATION(OpenInfra_QMS ${Translation_TS})

add_custom_target(CopyOpenInfraPlatformUIResources
	ALL DEPENDS ${OpenInfra_QMS}

	COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/src/OpenInfraPlatform/Shader		${CMAKE_BINARY_DIR}/Shader
	COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/src/OpenInfraPlatform/Shader		${CMAKE_BINARY_DIR}/RoadXMLViewer/Shader
	COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/src/OpenInfraPlatform/Shader		${CMAKE_BINARY_DIR}/LandXMLViewer/Shader
	COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/testdata							${CMAKE_BINARY_DIR}/LandXMLViewer/testdata
	COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/src/OpenInfraPlatform/Style		${CMAKE_BINARY_DIR}/Style
	COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/UnitTesting						${CMAKE_BINARY_DIR}/UnitTesting
	COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Data								${CMAKE_BINARY_DIR}/Data
	COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/testdata							${CMAKE_BINARY_DIR}/testdata
	COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Data/DesignAutomation				${CMAKE_BINARY_DIR}/UnitTests/Data/DesignAutomation

	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/Deutsch.qm								${CMAKE_BINARY_DIR}/Data/translations/Deutsch.qm
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/English.qm								${CMAKE_BINARY_DIR}/Data/translations/English.qm
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/Espanol.qm								${CMAKE_BINARY_DIR}/Data/translations/Espanol.qm

	# QM files are generated in ${CMAKE_BINARY_DIR}, but we want to move them to /Data/translations
	# therefore we will delete them after they're copied
	COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/Deutsch.qm ${CMAKE_BINARY_DIR}/English.qm ${CMAKE_BINARY_DIR}/Espanol.qm
	
	# # InstanceLevelTranslator
	COMMAND	${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deploy/InstanceLevelTranslator/InstanceLevelTranslator.exe		${CMAKE_BINARY_DIR}/Debug/InstanceLevelTranslator.exe
	COMMAND	${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deploy/InstanceLevelTranslator/OkstraI18NTranslation.dll		${CMAKE_BINARY_DIR}/Debug/OkstraI18NTranslation.dll
	
	COMMAND	${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deploy/InstanceLevelTranslator/InstanceLevelTranslator.exe		${CMAKE_BINARY_DIR}/Release/InstanceLevelTranslator.exe
	COMMAND	${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deploy/InstanceLevelTranslator/OkstraI18NTranslation.dll		${CMAKE_BINARY_DIR}/Release/OkstraI18NTranslation.dll
	
	COMMAND	${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deploy/InstanceLevelTranslator/InstanceLevelTranslator.exe		${CMAKE_BINARY_DIR}/RelWithDebInfo/InstanceLevelTranslator.exe
	COMMAND	${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deploy/InstanceLevelTranslator/OkstraI18NTranslation.dll		${CMAKE_BINARY_DIR}/RelWithDebInfo/OkstraI18NTranslation.dll
)

# DirectX
# add_custom_target(DirectXCopyBinaries
	# COMMAND	${CMAKE_COMMAND} -E copy "C:/Program Files (x86)/Windows Kits/8.1/Redist/D3D/x64/d3dcompiler_47.dll" ${CMAKE_BINARY_DIR}/Debug
	# COMMAND	${CMAKE_COMMAND} -E copy "C:/Program Files (x86)/Windows Kits/8.1/Redist/D3D/x64/d3dcompiler_47.dll" ${CMAKE_BINARY_DIR}/Release
	# COMMAND	${CMAKE_COMMAND} -E copy "C:/Program Files (x86)/Windows Kits/8.1/Redist/D3D/x64/d3dcompiler_47.dll" ${CMAKE_BINARY_DIR}/RelWithDebInfo
# )

# QSimpleUpdater
add_custom_target(QSimpleUpdaterCopyBinaries
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/libeay32.dll	${CMAKE_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/libeay32.dll	${CMAKE_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/libeay32.dll	${CMAKE_BINARY_DIR}/RelWithDebInfo

	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/ssleay32.dll	${CMAKE_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/ssleay32.dll	${CMAKE_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/ssleay32.dll	${CMAKE_BINARY_DIR}/RelWithDebInfo
)

# Do currently not work
#add_subdirectory(RoadXMLViewer)
#add_subdirectory(LandXMLViewer)

add_subdirectory(oip)

if (WIN32)

set_target_properties(CopyOpenInfraPlatformUIResources 			PROPERTIES FOLDER "Copy")
set_target_properties(OklabiCopyBinaries						PROPERTIES FOLDER "Copy")
set_target_properties(BlueFramework3CopyBinaries 				PROPERTIES FOLDER "Copy")
set_target_properties(Qt5CopyBinaries			 				PROPERTIES FOLDER "Copy")
#set_target_properties(DirectXCopyBinaries		 				PROPERTIES FOLDER "Copy")
set_target_properties(QSimpleUpdaterCopyBinaries				PROPERTIES FOLDER "Copy")
set_target_properties(Python35CopyBinaries						PROPERTIES FOLDER "Copy")
set_target_properties(GTestCopyBinaries							PROPERTIES FOLDER "Copy")
set_target_properties(libLASCopyBinaries						PROPERTIES FOLDER "Copy")

if(NOT OIP_USE_PREBUILD_EARLYBINDING_LIBS)
	set_target_properties(OpenInfraPlatform.Ifc2x3		 		PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding")
	set_target_properties(OpenInfraPlatform.Ifc4		 		PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding")
	set_target_properties(OpenInfraPlatform.IfcAlignment 		PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding")
	set_target_properties(OpenInfraPlatform.IfcAlignment1x1		PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding")
	set_target_properties(OpenInfraPlatform.IfcBridge	 		PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding")
	set_target_properties(OpenInfraPlatform.IfcRoad		 		PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding")
	set_target_properties(OpenInfraPlatform.IfcTunnel	 		PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding")
endif(NOT OIP_USE_PREBUILD_EARLYBINDING_LIBS)

set_target_properties(OpenInfraPlatform.ExpressBinding		 	PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding")
#set_target_properties(OpenInfraPlatform.EXPRESS2Source		 	PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding")

endif (WIN32)

# http://annealingtechnologies.blogspot.de/2010/02/wix-and-cpack-integration.html
# http://www.cmake.org/cmake/help/cmake_tutorial.html
# http://stackoverflow.com/questions/18457044/what-is-the-cmake-configuration-for-wixproject
# build a CPack driven installer package
# include (InstallRequiredSystemLibraries)
# set (CPACK_RESOURCE_FILE_LICENSE
	 # "${CMAKE_CURRENT_SOURCE_DIR}/docs/licenses.txt")
# set (CPACK_PACKAGE_VERSION_MAJOR "0")
# set (CPACK_PACKAGE_VERSION_MINOR "1")
# set (CPACK_GENERATOR "WIX")
# set (CPACK_WIX_XSL ${YOUR_PACKAGE_SOURCE_DIR}/win.xsl)
# include (CPack)

if(WIN32)
	if(MSVC12 OR MSVC14)
			if (MSVC12)
				set(BIN_DIR "${PROJECT_SOURCE_DIR}/bin/vs2013/x64/")
				set(LIB_DIR "${PROJECT_SOURCE_DIR}/lib/vs2013/x64/")
			elseif(MSVC14)
				set(BIN_DIR "${PROJECT_SOURCE_DIR}/bin/vs2015/x64/")
				set(LIB_DIR "${PROJECT_SOURCE_DIR}/lib/vs2015/x64/")
			endif(MSVC12)

			add_custom_target(UpdateOpenInfraPlatformLibsDebugSymbolsAndDLLs
				COMMENT "Copying BlueFramework Libraries ..." VERBATIM
			)

			add_custom_command(TARGET UpdateOpenInfraPlatformLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/Release/OpenInfraPlatform.Infrastructure.dll 						${BIN_DIR}OpenInfraPlatform.Infrastructure.dll VERBATIM)
			add_custom_command(TARGET UpdateOpenInfraPlatformLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/Infrastructure/Release/OpenInfraPlatform.Infrastructure.exp 		${LIB_DIR}OpenInfraPlatform.Infrastructure.exp VERBATIM)
			add_custom_command(TARGET UpdateOpenInfraPlatformLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/Infrastructure/Release/OpenInfraPlatform.Infrastructure.lib 		${LIB_DIR}OpenInfraPlatform.Infrastructure.lib VERBATIM)
			add_custom_command(TARGET UpdateOpenInfraPlatformLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/Debug/OpenInfraPlatform.Infrastructured.dll 						${BIN_DIR}OpenInfraPlatform.Infrastructured.dll VERBATIM)
			add_custom_command(TARGET UpdateOpenInfraPlatformLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/Infrastructure/Debug/OpenInfraPlatform.Infrastructured.exp 		${LIB_DIR}OpenInfraPlatform.Infrastructured.exp VERBATIM)
			#add_custom_command(TARGET UpdateOpenInfraPlatformLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/Infrastructure/Debug/OpenInfraPlatform.Infrastructured.ilk 						${LIB_DIR}OpenInfraPlatform.Infrastructured.ilk VERBATIM)
			add_custom_command(TARGET UpdateOpenInfraPlatformLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/Infrastructure/Debug/OpenInfraPlatform.Infrastructured.lib 		${LIB_DIR}OpenInfraPlatform.Infrastructured.lib VERBATIM)
			#add_custom_command(TARGET UpdateOpenInfraPlatformLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/Infrastructure/Debug/OpenInfraPlatform.Infrastructured.pdb 		${LIB_DIR}OpenInfraPlatform.Infrastructured.pdb VERBATIM)

			add_dependencies(UpdateOpenInfraPlatformLibsDebugSymbolsAndDLLs
				OpenInfraPlatform.Infrastructure
			)

			set_target_properties(UpdateOpenInfraPlatformLibsDebugSymbolsAndDLLs	PROPERTIES FOLDER "Copy")
	endif()
endif()

macro(add_thirdparty TGT)
	if(TARGET ${TGT})
		set(extra_macro_args ${ARGN})
	
		# Did we get any optional args?
		list(LENGTH extra_macro_args num_extra_args)
		if(${num_extra_args} EQUAL 2)
			list(GET extra_macro_args 0 DEST)
			set(DEST "ThirdParty/${DEST}")
			list(GET extra_macro_args 1 MODE)
		elseif(${num_extra_args} EQUAL 1)
			list(GET extra_macro_args 0 arg0)
			if("${arg0}" STREQUAL "REQUIRED")
				set(MODE "REQUIRED")
				set(DEST "ThirdParty")
			else()
				set(DEST "ThirdParty/${arg0}")
				set(MODE "EXCLUDE")
			endif()
		else()
			set(DEST "ThirdParty")
			set(MODE "EXCLUDE")
		endif()
	
		if("${MODE}" STREQUAL "REQUIRED")
			set_target_properties(${TGT} PROPERTIES FOLDER "${DEST}")
		else()
			set_target_properties(${TGT} PROPERTIES FOLDER "${DEST}" EXCLUDE_FROM_ALL ON)
		endif()
	endif()
endmacro()

# Thirdparty
if (WIN32)
	add_thirdparty(QtXlsxWriter 	"REQUIRED")
	add_thirdparty(QSimpleUpdater 	"REQUIRED")
		
	# carve
	add_thirdparty(carve					"carve")
	add_thirdparty(carve_fileformats		"carve")
	add_thirdparty(carve_misc				"carve")
	add_thirdparty(close_manifold			"carve")
	add_thirdparty(cutgraph					"carve")
	add_thirdparty(convert					"carve")
	add_thirdparty(extrude					"carve")
	add_thirdparty(face_merge				"carve")
	add_thirdparty(gloop_model				"carve")
	add_thirdparty(gloop_image				"carve")
	add_thirdparty(gloop_math				"carve")
	add_thirdparty(intersect				"carve")
	add_thirdparty(slice					"carve")		
	add_thirdparty(tetrahedron				"carve")
	add_thirdparty(triangulate				"carve")
	add_thirdparty(test_eigen				"carve")
	add_thirdparty(test_aabb				"carve")
	add_thirdparty(test_geom				"carve")
	add_thirdparty(test_rescale				"carve")
	add_thirdparty(test_spacetree			"carve")
	add_thirdparty(test_carve_polyhedrons_2	"carve")
endif (WIN32)

#add_subdirectory(IfcBridgeGenerator)
#add_subdirectory(IfcTunnelGenerator)

set_target_properties(OpenInfraPlatform.CommandLineUtilities PROPERTIES FOLDER "OpenInfraPlatform")
#set_target_properties(OpenInfraPlatform.IfcBridgeGenerator	 PROPERTIES FOLDER "OpenInfraPlatform")
#set_target_properties(OpenInfraPlatform.IfcTunnelGenerator	 PROPERTIES FOLDER "OpenInfraPlatform")
set_target_properties(OpenInfraPlatform.Infrastructure		 PROPERTIES FOLDER "OpenInfraPlatform")
#set_target_properties(OpenInfraPlatform.LandXMLViewer		 PROPERTIES FOLDER "OpenInfraPlatform")
#set_target_properties(OpenInfraPlatform.RoadXMLViewer		 PROPERTIES FOLDER "OpenInfraPlatform")
set_target_properties(OpenInfraPlatform.UI					 PROPERTIES FOLDER "OpenInfraPlatform")

#-------------------------------------------------------------------------------------
# Deployment
set(CPACK_GENERATOR WIX)
set(CPACK_WIX_UPGRADE_GUID "178111DC-0B0C-4E3F-8C80-D756F742645F")
set(CPACK_WIX_PRODUCT_GUID "D936BC02-9157-4D86-9652-F8CB6D62BAAE")
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VENDOR "https://www.cms.bgu.tum.de/en/")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "OpenInfraPlatform")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VERSION_TEWAK "${PROJECT_VERSION_TWEAK}}")

set(CPACK_PACKAGE_INSTALL_DIRECTORY "OpenInfraPlatform")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/README.md")

include(CPackComponent)

cpack_add_component(oip_runtime INSTALL_TYPES default)
cpack_add_component(oip_import_libs INSTALL_TYPES default)
cpack_add_component(oip_static_libs INSTALL_TYPES default)
cpack_add_component(oip_data INSTALL_TYPES default)
cpack_add_component(oip_thirdparty INSTALL_TYPES default)

set(CPACK_COMPONENTS_ALL "oip_runtime;oip_import_libs;oip_static_libs;oip_data;oip_thirdparty")

install(TARGETS OpenInfraPlatform.UI
   RUNTIME DESTINATION bin
   COMPONENT oip_runtime
)

macro(installData DATA)
	install(DIRECTORY ${DATA} DESTINATION bin
    COMPONENT oip_data
    FILES_MATCHING PATTERN "*.*") 
endmacro()

installData(${PROJECT_SOURCE_DIR}/src/OpenInfraPlatform/Shader)
installData(${PROJECT_SOURCE_DIR}/Data)
installData(${PROJECT_SOURCE_DIR}/testdata)
installData(${CMAKE_BINARY_DIR}/schema)
installData(${CMAKE_BINARY_DIR}/res)
installData(${CMAKE_BINARY_DIR}/fbliste)
installData(${CMAKE_BINARY_DIR}/Style)
		
install(FILES ${BLUEFRAMEWORK3_RELEASE_BINARIES} ${OKLABI_DLLS} ${QT5_DLLS_RELEASE}
	DESTINATION bin
	COMPONENT oip_thirdparty)

include(CPack)