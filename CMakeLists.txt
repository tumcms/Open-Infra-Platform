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

# Updated to 3.13 in revision 531
cmake_minimum_required(VERSION 3.13)
cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0074 NEW)
cmake_policy(SET CMP0071 OLD)

project(OpenInfraPlatform)

#-------------------------------------------------------------------------------------
# CMake definitions and propertiess
#-------------------------------------------------------------------------------------

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH})
set(CMAKE_AUTOMOC ON)

# Changed C++ standard to 14 in revision 534
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_DEBUG_POSTFIX "d")
include(ProjectVersion)
find_package(Git REQUIRED)

include(FetchContent)

enable_testing()
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
# Check for Microsoft VisualStudio version and processor architecture.
# Some checks to ensure that the prerequisites are ok
#------------------------------------------------------------------------------

if(MSVC_VERSION EQUAL 1900)
	set(MSVC_VERSION_STRING "vs2015")
	set(MSVC_VERSION_YEAR "2015")
elseif(MSVC_VERSION GREATER_EQUAL 1910 AND MSVC_VERSION LESS_EQUAL 1919)
	set(MSVC_VERSION_STRING "vs2017")
	set(MSVC_VERSION_YEAR "2017")
else()
	message("Please switch to Visual Studio 14 2015 or Visual Studio 15 2017.")
	return()
endif()

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message("Please switch to x64 build.")
	return()
endif()


#------------------------------------------------------------------------------
# Fix for MSVC 1915 / Visual Studio 2017 15.8
#------------------------------------------------------------------------------

if(MSVC_VERSION GREATER_EQUAL 1915)
	add_compile_definitions(_ENABLE_EXTENDED_ALIGNED_STORAGE)
endif()


#------------------------------------------------------------------------------
# Look for thirdparty libraries in some predefined locations.
#------------------------------------------------------------------------------

option(OIP_USE_PREDEFINED_THIRDPARTY_PATH "Set to ON to find boost, Eigen and Qt path" ON)

if(OIP_USE_PREDEFINED_THIRDPARTY_PATH)
	# Try to find Boost, Eigen3, Qt5 and other dependencies without user input
	find_path(BOOST_ROOT NAMES boost/version.hpp HINTS
		"C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\boost_1_65_1"
		"C:\\thirdparty\\boost_1_65_1")
	find_path(Boost_DIR NAMES boost/version.hpp HINTS
		"C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\boost_1_65_1"
		"C:\\thirdparty\\boost_1_65_1")

	#find_path(EIGEN3_INCLUDE_DIR NAMES Eigen/Core HINTS
	#	"C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\Eigen_3.3.4"
	#	"C:\\thirdparty\\eigen")
	find_path(CMAKE_PREFIX_PATH NAMES include/QtCore/QObject HINTS "C:\\Qt\\5.12.1\\msvc${MSVC_VERSION_YEAR}_64")
	#find_path(GTEST_ROOT NAMES lib/cmake/GTest/GTestConfig.cmake HINTS
	#	"C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\googletest"
	#	"C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\googletest-master")
	#if(NOT GTEST_ROOT)
	#	find_path(GTEST_ROOT NAMES googletest/include/gtest/gtest.h HINTS
	#		"C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\googletest-release-1.8.0" 
	#		"C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\googletest-1.8.0")
	#endif()
	#find_path(ZLIB_ROOT NAMES zlib.h HINTS 
	#          "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\zlib-1.2.11")
	#find_path(RAPTOR2_ROOT_DIR NAMES include/raptor2/raptor2.h HINTS 
	#          "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\raptor2"
	#		  "C:\\thirdparty\\raptor2")
	# Added to predefined path list in revision 533
	#find_path(FFTW3_DIR NAMES FFTW3Config.cmake HINTS "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\fftw-3.3.8\\lib\\cmake\\fftw3")
	#find_path(visit_struct_INCLUDE_DIR NAMES visit_struct/visit_struct.hpp HINTS "C:\\thirdparty\\visit_struct-master\\include")
endif()

#------------------------------------------------------------------------------
# Set output directories.
#------------------------------------------------------------------------------

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG     ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG         ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE   ${CMAKE_BINARY_DIR}/Release)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE       ${CMAKE_BINARY_DIR}/Release)

#------------------------------------------------------------------------------
# Add preprocessor directives and compiler flags.
#------------------------------------------------------------------------------

add_definitions(-D_UNICODE 			# Unicode rules
				#-DQT_NO_KEYWORDS 	# No qt keywords
				-D_VARIADIC_MAX=10 	# Visual Studio 2012 set VARIDAIC_MAX default to 5 which is not enough for googletest to build
) # -DNOMINMAX does not work because GDI+ needs these macros

if (WIN32)
	# Standard:          /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR
	set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W4 /Zi /EHsc /GR /MP /openmp /bigobj")
endif (WIN32)

#------------------------------------------------------------------------------
# Find required thirdparty libraries.
#------------------------------------------------------------------------------

set(Boost_USE_STATIC_LIBS ON)

# As of revision 530, boost 1.65.1 required.
find_package(Boost 1.65.1 COMPONENTS signals system filesystem REQUIRED)

#if(MSVC_VERSION LESS 1910)
#	add_compile_definitions(BOOST_VARIANT_DO_NOT_USE_VARIADIC_TEMPLATES)
#endif()

#find_package(BlueFramework 3.1.1.94 COMPONENTS Core Engine Application ImageProcessing Rasterizer D3D11RenderSystem D3D12RenderSystem REQUIRED)

# Deprecated as of Revision 530
#find_package(OpenInfraPlatform.EarlyBinding REQUIRED)
#find_package(Eigen3 3.3.2  REQUIRED)
#find_path(eigen_DIR)
FetchContent_Declare(
	eigen
	GIT_REPOSITORY https://github.com/eigenteam/eigen-git-mirror.git
	GIT_TAG 3.3.7
)
  
FetchContent_GetProperties(eigen)
if(NOT eigen_POPULATED)
	FetchContent_Populate(eigen)
	add_subdirectory(${eigen_SOURCE_DIR} ${eigen_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


find_package(Oklabi REQUIRED)

# FetchContent_Declare(
# 	qhull
# 	GIT_REPOSITORY https://github.com/qhull/qhull.git
# 	GIT_TAG v7.3.2
# )
 
# FetchContent_GetProperties(qhull)
# if(NOT qhull_POPULATED)
# 	FetchContent_Populate(qhull)
# 	add_subdirectory(${qhull_SOURCE_DIR} ${qhull_BINARY_DIR} EXCLUDE_FROM_ALL)
# endif()

#find_package(raptor2 REQUIRED)

FetchContent_Declare(
	visit_struct
	GIT_REPOSITORY https://github.com/cbeck88/visit_struct.git
	GIT_TAG v1.0
)
  
FetchContent_GetProperties(visit_struct)
if(NOT visit_struct_POPULATED)
	FetchContent_Populate(visit_struct)
endif()
set(visit_struct_INCLUDE_DIR ${visit_struct_SOURCE_DIR}/include)

# find_package(CC REQUIRED)	02.05.2019 moved to pcp module (coetzee)
# find_package(libLAS REQUIRED)	02.05.2019 moved to pcp module (coetzee)

# Added 12.09.2018: FFTW3
#find_package(FFTW3 REQUIRED)

#include(GTestCopyBinaries)
#GTEST_COPY_BINARIES(${CMAKE_BINARY_DIR})
#set_target_properties(GTestCopyBinaries	PROPERTIES FOLDER "Copy")


FetchContent_Declare(
	zlib
	GIT_REPOSITORY https://github.com/madler/zlib.git
)

FetchContent_GetProperties(zlib)
if(NOT zlib_POPULATED)
	FetchContent_Populate(zlib)
	add_subdirectory(${zlib_SOURCE_DIR} ${zlib_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()



# Find the Qt components
set(QT5_COMPONENTS
	Core
	Gui
	OpenGL
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
	Location
)

# Loop over all components, find them and initialize the corresponding variables
# foreach(Component ${QT5_COMPONENTS})
# 	find_package( Qt5 5.10.0 COMPONENTS ${Component}	REQUIRED)
# 	if(TARGET ${Qt5${Component}_LIBRARIES})
# 		get_target_property(Qt5${Component}_location ${Qt5${Component}_LIBRARIES} LOCATION_Release)
# 		set(QT5_DLLS_RELEASE ${QT5_DLLS_RELEASE} ${Qt5${Component}_location})
# 		get_target_property(Qt5${Component}_location ${Qt5${Component}_LIBRARIES} LOCATION_Debug)
# 		set(QT5_DLLS_DEBUG ${QT5_DLLS_DEBUG} ${Qt5${Component}_location})
# 	endif()
# endforeach()
find_package( Qt5 5.12.1 COMPONENTS ${QT5_COMPONENTS} REQUIRED)



if(Qt5_FOUND AND WIN32 AND TARGET Qt5::qmake AND NOT TARGET Qt5::windeployqt)
    get_target_property(_qt5_qmake_location Qt5::qmake IMPORTED_LOCATION)

    execute_process(
        COMMAND "${_qt5_qmake_location}" -query QT_INSTALL_PREFIX
        RESULT_VARIABLE return_code
        OUTPUT_VARIABLE qt5_install_prefix
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    set(imported_location "${qt5_install_prefix}/bin/windeployqt.exe")

    if(EXISTS ${imported_location})
        add_executable(Qt5::windeployqt IMPORTED)

        set_target_properties(Qt5::windeployqt PROPERTIES
            IMPORTED_LOCATION ${imported_location}
        )
    endif()
endif()

#------------------------------------------------------------------------------
# DOXYGEN. 
#------------------------------------------------------------------------------
Option(DOXYGEN_GENERATE_DOCUMENTATION ON)

if(DOXYGEN_GENERATE_DOCUMENTATION)
include(ConfigureDoxygen OPTIONAL)	# Refer to ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ConfigureDoxygen.cmake 
else()
message("DOXYGEN_GENERATE_DOCUMENTATION box not checked. Thus not generating doxygen documentation for TUM Open Infra Platform project. To generate doxygen documentation, check the box next to DOXYGEN_GENERATE_DOCUMENTATION.")
endif(DOXYGEN_GENERATE_DOCUMENTATION)


FetchContent_Declare(
	blue_framework
	GIT_REPOSITORY https://github.com/hechth/Blue-Framework.git
	GIT_TAG alpha
)
  
FetchContent_GetProperties(blue_framework)
if(NOT blue_framework_POPULATED)
	FetchContent_Populate(blue_framework)
	add_subdirectory(${blue_framework_SOURCE_DIR} ${blue_framework_BINARY_DIR})
endif()

#------------------------------------------------------------------------------
# Set required Qt plugins variables and find and add the corresponding dlls for deployment and copying.
#------------------------------------------------------------------------------

# set(Qt5_IMAGEFORMATS_PLUGINS
# 	QGifPlugin
# 	QICNSPlugin
# 	QICOPlugin
# 	QJpegPlugin
# 	QTgaPlugin
# 	QTiffPlugin
# 	QWbmpPlugin
# 	QWebpPlugin
# 	QSvgPlugin
# )

# set(Qt5_GEOSERVICES_PLUGINS
# 	QGeoServiceProviderFactoryOsm
# 	QGeoServiceProviderFactoryNokia
# 	QGeoServiceProviderFactoryMapbox
# 	QGeoServiceProviderFactoryItemsOverlay
# 	GeoServiceProviderFactoryEsri
# )

# set(Qt5_PLATFORMS_PLUGINS
# 	QWindowsIntegrationPlugin
# 	QWindowsDirect2DIntegrationPlugin
# 	QMinimalIntegrationPlugin
# 	QOffscreenIntegrationPlugin
# )

# set(Qt5_NETWORK_PLUGINS
# 	QGenericEnginePlugin
# )

# set(Qt5_ICONENGINES_PLUGINS
# 	QSvgIconPlugin
# )

# set(Qt5_PLUGINS ${Qt5_IMAGEFORMATS_PLUGINS} ${Qt5_GEOSERVICES_PLUGINS} ${Qt5_PLATFORMS_PLUGINS} ${Qt5_NETWORK_PLUGINS} ${Qt5_ICONENGINES_PLUGINS})

# foreach(plugin ${Qt5_GEOSERVICES_PLUGINS})
# 	include(${Qt5Location_DIR}/Qt5Location_${plugin}.cmake)
# endforeach()

# string(REPLACE "lib/cmake/Qt5" "bin" Qt5_BIN_DIR "${Qt5_DIR}")

# macro(addQt5Dll lib)
# 	set(QT5_DLLS_RELEASE ${QT5_DLLS_RELEASE} ${Qt5_BIN_DIR}/Qt5${lib}.dll)
# 	set(QT5_DLLS_DEBUG ${QT5_DLLS_DEBUG} ${Qt5_BIN_DIR}/Qt5${lib}d.dll)
# endmacro()

# macro(addQt5PluginDll plugin output)
# 	get_target_property(_loc Qt5::${plugin} LOCATION)
# 	list(APPEND ${output} ${_loc})
# endmacro()

# addQt5Dll(Gui)
# addQt5Dll(Multimedia)
# addQt5Dll(MultimediaWidgets)
# addQt5Dll(OpenGL)
# addQt5Dll(Sensors)
# addQt5Dll(Sql)
# addQt5Dll(WebChannel)
# addQt5Dll(Concurrent)

# foreach(plugin ${Qt5_PLATFORMS_PLUGINS})
# 	addQt5PluginDll(${plugin} Qt5_PLATFORMS_PLUGINS_DLLS)
# endforeach()
# foreach(plugin ${Qt5_IMAGEFORMATS_PLUGINS})
# 	addQt5PluginDll(${plugin} Qt5_IMAGEFORMATS_PLUGINS_DLLS)
# endforeach()
# foreach(plugin ${Qt5_GEOSERVICES_PLUGINS})
# 	addQt5PluginDll(${plugin} Qt5_GEOSERVICES_PLUGINS_DLLS)
# endforeach()
# foreach(plugin ${Qt5_NETWORK_PLUGINS})
# 	addQt5PluginDll(${plugin} Qt5_NETWORK_PLUGINS_DLLS)
# endforeach()
# foreach(plugin ${Qt5_ICONENGINES_PLUGINS})
# 	addQt5PluginDll(${plugin} Qt5_ICONENGINES_PLUGINS_DLLS)
# endforeach()

#------------------------------------------------------------------------------
# Set include directories and link directories.
#------------------------------------------------------------------------------

include_directories(
	${CMAKE_CURRENT_BINARY_DIR} # Qt generated files will be located here
	# thirdpary libraries:
	${Boost_INCLUDE_DIR}
	${blue_framework_SOURCE_DIR}/include
	${OpenInfraPlatform.EarlyBinding_INCLUDE_DIR}
	${FFTW3_INCLUDE_DIRS}
	${ZLIB_INCLUDE_DIRS}	
	${visit_struct_INCLUDE_DIR}
	$(Doxygen_INCLUDE_DIR)
	# external:
	external/QtXlsxWriter/src/xlsx
	external/QSimpleUpdater/src
	external/QSimpleUpdater/src/dialogs
	external/carve/include
	${CMAKE_BINARY_DIR}/external/carve/include
	external/carve/common
	external/qcustomplot
	# projects:
	ExpressBindingGenerator
	UserInterface
	Core
)

link_directories(
	${Boost_LIBRARY_DIRS}
	${OKLABI_ROOT_DIR}
	${FFTW3_LIBRARY_DIRS}
	${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>
)

#------------------------------------------------------------------------------
# Add subdirectories.
#------------------------------------------------------------------------------

add_subdirectory(external/QtXlsxWriter)
add_subdirectory(external/QSimpleUpdater)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/carve)

add_subdirectory(ExpressBindingGenerator)
# As of revision 531, replaces old OpenInfraPlatform_EarlyBinding_DIR
add_subdirectory(${PROJECT_SOURCE_DIR}/EarlyBinding)

foreach(format ${IFC_FORMATS})	
	add_compile_definitions(OIP_MODULE_EARLYBINDING_${format})
endforeach()

#----------------------------------------------------------
# (1/7) Point Cloud Processing ("pcp_module")
#----------------------------------------------------------

Option(MODULES_POINT_CLOUD_PROCESSING OFF)

if(MODULES_POINT_CLOUD_PROCESSING)
	add_definitions(-DOIP_WITH_POINT_CLOUD_PROCESSING)
	add_subdirectory(PointCloudProcessing)
endif()


add_subdirectory(Core)



add_subdirectory(UnitTests)

# Do currently not work. Located in Other. 
#add_subdirectory(RoadXMLViewer)
#add_subdirectory(LandXMLViewer)
#add_subdirectory(IfcTunnelGenerator)
#add_subdirectory(oip)
#add_subdirectory(IfcBridgeGenerator)

#------------------------------------------------------------------------------------------------------------------------------------------------------------
# Collect source files
#------------------------------------------------------------------------------------------------------------------------------------------------------------

# USER INTERFACE. 

file(GLOB OpenInfraPlatform_UserInterface_Source 					UserInterface/*.*)
file(GLOB OpenInfraPlatform_UserInterface_Forms_Source 				UserInterface/Forms/*.*)
file(GLOB OpenInfraPlatform_UserInterface_ColorPicker_Source		UserInterface/ColorPicker/*.*)
file(GLOB OpenInfraPlatform_UserInterface_Dialogues_Source 			UserInterface/Dialogues/*.*)
file(GLOB OpenInfraPlatform_UserInterface_QtPropertyBrowser_Source 	UserInterface/QtPropertyBrowser/*.*)
file(GLOB OpenInfraPlatform_UserInterface_Shader_Source 			UserInterface/Shader/*.*)
file(GLOB OpenInfraPlatform_UserInterface_Shader_D3D_Source 		UserInterface/Shader/D3D/*.*)
file(GLOB OpenInfraPlatform_UserInterface_ViewPanel_Source 			UserInterface/ViewPanel/*.*)
file(GLOB OpenInfraPlatform_UserInterface_ViewPanel_Effects_Source 	UserInterface/ViewPanel/Effects/*.h UserInterface/ViewPanel/Effects/*.cpp)

if(MODULES_POINT_CLOUD_PROCESSING)
	file(GLOB OpenInfraPlatform_UserInterface_ViewPanel_Effects_PointCloudProcessing_Source 	UserInterface/ViewPanel/Effects/PointCloudProcessing/*.*)
	source_group(UserInterface\\ViewPanel\\Effects\\PointCloudProcessing	FILES ${OpenInfraPlatform_UserInterface_ViewPanel_Effects_PointCloudProcessing_Source})
	list(APPEND OpenInfraPlatform_UserInterface_ViewPanel_Effects_Source ${OpenInfraPlatform_UserInterface_ViewPanel_Effects_PointCloudProcessing_Source})
endif()


file(GLOB OpenInfraPlatform_UserInterface_QCustomPlot_Source 		external/qcustomplot/*.*)
file(GLOB OpenInfraPlatform_UserInterface_Resources_Source 			UserInterface/Resources/*.*)

# Currently not included.
#file(GLOB OpenInfraPlatform_UserInterface_Tools_Source				UserInterface/other/Tools/*.*)
#file(GLOB OpenInfraPlatform_UserInterface_View2DWindow			 	UserInterface/other/View2DWindow/*.*)
# file(GLOB OpenInfraPlatform_UserInterface_Data_Source 				UserInterface/Data/*.*)


# Does currently not work. 
file(GLOB OpenInfraPlatform_UserInterface_UnitTesting_Source					UserInterface/UnitTesting/*.*)

set(OpenInfraPlatform_UserInterface_Forms
	external/QSimpleUpdater/src/dialogs/download_dialog.ui
	UserInterface/Forms/MainWindow.ui
	UserInterface/Forms/LicenseAndCopyrightInformation.ui
	UserInterface/Forms/PreferencesDialog.ui

	# Currently not included.
	#UserInterface/Forms/CreateAccidentReport.ui
	#UserInterface/Forms/CreateArcClothoidArc.ui
	#UserInterface/Forms/CreateArcClothoidArcMeth2.ui
	#UserInterface/Forms/CreateArcClothoidClothoidArc.ui
	#UserInterface/Forms/CreateArcClothoidClothoidArcMeth2.ui
	#UserInterface/Forms/CreateClothoid.ui
	#UserInterface/Forms/CreateClothoid2.ui
	#UserInterface/Forms/CreateLineArcArcArcLine.ui
	#UserInterface/Forms/CreateLineArcArcLine.ui
	#UserInterface/Forms/CreateLineClothoidArcClothoidLine.ui
	#UserInterface/Forms/CreateLineClothoidClothoidLine.ui
	#UserInterface/Forms/CodeEditorWindow.ui
	#UserInterface/Forms/CurvatureWindow.ui
	#UserInterface/Forms/ShowIFCtree.ui
	#UserInterface/Forms/ExportExcel.ui
	#UserInterface/Forms/ExportIfc4x1Dialog.ui
	#UserInterface/Forms/ExportIfcAlignmentDialog.ui
	#UserInterface/Forms/ExportIfcZipDialog.ui
	#UserInterface/Forms/GenerateTerrain.ui
	#UserInterface/Forms/OSMImportDialog.ui
	#UserInterface/Forms/VerticalAlignmentWindow.ui
	#UserInterface/Forms/XYZImportDialog.ui
	#UserInterface/Forms/AddGeoreferenceDialog.ui
)

# Collect all translation files
FILE(GLOB Translation_TS UserInterface/Data/translations/*.ts)

set(OpenInfraPlatform_RC
	UserInterface/Resources/OpenInfraPlatform.qrc
	UserInterface/QtPropertyBrowser/qtpropertybrowser.qrc
)

#------------------------------------------------------------------------------
# Set source groups
#------------------------------------------------------------------------------

# USER INTERFACE.
source_group(UserInterface						FILES ${OpenInfraPlatform_UserInterface_Source})
source_group(UserInterface\\Forms				FILES ${OpenInfraPlatform_UserInterface_Forms_Source})
source_group(UserInterface\\ColorPicker			FILES ${OpenInfraPlatform_UserInterface_ColorPicker_Source})
source_group(UserInterface\\Dialogues			FILES ${OpenInfraPlatform_UserInterface_Dialogues_Source})
source_group(UserInterface\\QtPropertyBrowser	FILES ${OpenInfraPlatform_UserInterface_QtPropertyBrowser_Source})
source_group(UserInterface\\Shader				FILES ${OpenInfraPlatform_UserInterface_Shader_Source})
source_group(UserInterface\\Shader\\D3D			FILES ${OpenInfraPlatform_UserInterface_Shader_D3D_Source})
source_group(UserInterface\\ViewPanel			FILES ${OpenInfraPlatform_UserInterface_ViewPanel_Source})
source_group(UserInterface\\ViewPanel\\Effects	FILES ${OpenInfraPlatform_UserInterface_ViewPanel_Effects_Source})
source_group(UserInterface\\QCustomPlot			FILES ${OpenInfraPlatform_UserInterface_QCustomPlot_Source})
source_group(UserInterface\\Resources			FILES ${OpenInfraPlatform_UserInterface_Resources_Source})

# Does not currently work.
source_group(UserInterface\\UnitTesting  		FILES ${OpenInfraPlatform_UserInterface_UnitTesting_Source})

# Currently not included.
#source_group(UserInterface\\Tools			FILES ${OpenInfraPlatform_UserInterface_Tools_Source})
#source_group(UserInterface\\View2DWindow		FILES ${OpenInfraPlatform_UserInterface_View2DWindow})
# source_group(UserInterface\\Data				FILES ${OpenInfraPlatform_UserInterface_Data_Source})

#------------------------------------------------------------------------------
# Set source group properties
#------------------------------------------------------------------------------

# Set HEADER_FILES_ONLY to true to make them show up in the IDE but be excluded from compiling
set_source_files_properties(${OpenInfraPlatform_UserInterface_Shader_Source} 		PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties(${OpenInfraPlatform_UserInterfaces_Shader_D3D_Source} 	PROPERTIES HEADER_FILE_ONLY TRUE)

# Qt related stuff
#QT5_ADD_RESOURCES(OpenInfraPlatform_UserInterface_Resources_Source_SRCS ${OpenInfraPlatform_UserInterface_Resources_Source})
QT5_ADD_RESOURCES(OpenInfraPlatform_UserInterface_Resources_Source_SRCS ${OpenInfraPlatform_RC})
QT5_WRAP_UI(OpenInfraPlatform_UserInterface_Forms_H ${OpenInfraPlatform_UserInterface_Forms})
QT5_ADD_TRANSLATION(OpenInfra_QMS ${Translation_TS})

IF(NOT QT_LRELEASE_EXECUTABLE AND NOT Qt5_LRELEASE_EXECUTABLE)
	MESSAGE(WARNING "Could not find lrelease. Your build won't contain translations.")
ENDIF(NOT QT_LRELEASE_EXECUTABLE AND NOT Qt5_LRELEASE_EXECUTABLE)

#------------------------------------------------------------------------------
# Add the actual executable.
#------------------------------------------------------------------------------

add_executable(OpenInfraPlatform.UI
	${OpenInfraPlatform_UserInterface_Source}
	${OpenInfraPlatform_UserInterface_QtPropertyBrowser_Source}
	${OpenInfraPlatform_UserInterface_Forms} 		
	${OpenInfraPlatform_UserInterface_ColorPicker_Source}
	${OpenInfraPlatform_UserInterface_Dialogues_Source}
	${OpenInfraPlatform_UserInterface_ViewPanel_Source}
	${OpenInfraPlatform_UserInterface_ViewPanel_Effects_Source}
	${OpenInfraPlatform_UserInterface_Shader_Source}
	#${OpenInfraPlatform_UserInterface_Shader_D3D_Source}
	${OpenInfraPlatform_UserInterface_QCustomPlot_Source}
	${OpenInfraPlatform_UserInterface_UnitTesting_Source}	
	
	# Currently not included.
	#${OpenInfraPlatform_UserInterface_View2DWindow}
	#${OpenInfraPlatform_UserInterface_Tools_Source}	
	${OpenInfraPlatform_UserInterface_Resources_Source_SRCS}		
	#${OpenInfraPlatform_UserInterface_Data_Source}
)

# set up start-up project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT OpenInfraPlatform.UI)


#------------------------------------------------------------------------------
# Link qt and other external libraries to our executable.
#------------------------------------------------------------------------------

# Use the Widgets module from Qt 5.
#find_package(BlueFramework 3.1.1.94 COMPONENTS Core Engine Application ImageProcessing Rasterizer D3D11RenderSystem D3D12RenderSystem REQUIRED)

target_link_libraries( OpenInfraPlatform.UI
	OpenInfraPlatform.Core
	Qt5::WinMain  # New target available via find_package ( Qt5Core )
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	Qt5::Svg
	Qt5::PrintSupport
	Qt5::Quick
	Qt5::Qml
	Qt5::Location
	Qt5::Positioning
	BlueFramework.Core
	BlueFramework.Engine
	BlueFramework.Application
	BlueFramework.ImageProcessing
	BlueFramework.Rasterizer
	BlueFramework.D3D11RenderSystem
	BlueFramework.D3D12RenderSystem
	QtXlsxWriter
	QSimpleUpdater
	carve
	#ZLIB::ZLIB
	zlib
	Rpcrt4.lib
	eigen
)

if(TARGET Qt5::windeployqt)
    # execute windeployqt in a tmp directory after build
    add_custom_command(TARGET OpenInfraPlatform.UI
        POST_BUILD
        COMMAND set PATH=%PATH%$<SEMICOLON>${qt5_install_prefix}/bin
        COMMAND Qt5::windeployqt --dir "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>" "$<TARGET_FILE_DIR:OpenInfraPlatform.UI>/$<TARGET_FILE_NAME:OpenInfraPlatform.UI>"

    )

    # # copy deployment directory during installation
    # install(
    #     DIRECTORY
    #     "${CMAKE_CURRENT_BINARY_DIR}/windeployqt/"
    #     DESTINATION ${FOO_INSTALL_RUNTIME_DESTINATION}
    # )
endif()

#------------------------------------------------------------------------------
# Calling copy functions to provide custom targets.
# Add the custom targets to copy the required binaries.
#------------------------------------------------------------------------------

# BlueFramework Copy Binaries
#BLUEFRAMEWORK_COPY_BINARIES(${CMAKE_BINARY_DIR})

# Oklabi Copy Binaries
OKLABI_COPY_BINARIES(${CMAKE_BINARY_DIR})

# zlic Copy Binaries
#ZLIB_COPY_BINARIES(${CMAKE_BINARY_DIR})

# # QtCopyBinaries
# add_custom_target(Qt5CopyBinaries
# 	COMMAND ${CMAKE_COMMAND} -E copy ${QT5_DLLS_RELEASE} ${CMAKE_BINARY_DIR}/Release
# 	COMMAND ${CMAKE_COMMAND} -E copy ${QT5_DLLS_RELEASE} ${CMAKE_BINARY_DIR}/RelWithDebInfo
# 	COMMAND ${CMAKE_COMMAND} -E copy ${QT5_DLLS_DEBUG} ${CMAKE_BINARY_DIR}/Debug	

# 	COMMAND	${CMAKE_COMMAND} -E copy_directory ${Qt5Core_DIR}/../../../qml						${CMAKE_BINARY_DIR}/Release/qml
# 	COMMAND	${CMAKE_COMMAND} -E copy_directory ${Qt5Core_DIR}/../../../plugins/geoservices		${CMAKE_BINARY_DIR}/Release/plugins/geoservices
# 	COMMAND	${CMAKE_COMMAND} -E copy_directory ${Qt5Core_DIR}/../../../plugins/imageformats		${CMAKE_BINARY_DIR}/Release/plugins/imageformats
# 	COMMAND	${CMAKE_COMMAND} -E copy_directory ${Qt5Core_DIR}/../../../plugins/platforms		${CMAKE_BINARY_DIR}/Release/platforms

# 	# Output Message
# 	COMMENT "Copying Ot binaries from '${Qt5Core_DIR}/../../bin/' to '${CMAKE_BINARY_DIR}'" VERBATIM
# )

add_custom_target(CopyOpenInfraPlatformUIResources
	ALL DEPENDS ${OpenInfra_QMS}
	COMMENT "Copying UIResources from '${PROJECT_SOURCE_DIR}' to '${CMAKE_BINARY_DIR}'" VERBATIM
	COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/UserInterface/Shader		${CMAKE_BINARY_DIR}/UserInterface/Shader
	#COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/src/OpenInfraPlatform/Shader		${CMAKE_BINARY_DIR}/RoadXMLViewer/Shader
	#COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/src/OpenInfraPlatform/Shader		${CMAKE_BINARY_DIR}/LandXMLViewer/Shader
	#COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/testdata							${CMAKE_BINARY_DIR}/LandXMLViewer/testdata
	COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/UserInterface/Style		${CMAKE_BINARY_DIR}/UserInterface/Style
	COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/UserInterface/Data					${CMAKE_BINARY_DIR}/UserInterface/Data
	COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/testdata							${CMAKE_BINARY_DIR}/testdata
	COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/UserInterface/Data/DesignAutomation				${CMAKE_BINARY_DIR}/UnitTests/Data/DesignAutomation

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

# QSimpleUpdater
add_custom_target(QSimpleUpdaterCopyBinaries
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/libeay32.dll	${CMAKE_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/libeay32.dll	${CMAKE_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/libeay32.dll	${CMAKE_BINARY_DIR}/RelWithDebInfo

	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/ssleay32.dll	${CMAKE_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/ssleay32.dll	${CMAKE_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/ssleay32.dll	${CMAKE_BINARY_DIR}/RelWithDebInfo
)

#add_custom_target(ZLIBCopyBinaries
#  COMMAND	${CMAKE_COMMAND} -E copy ${ZLIB_ROOT}/build/Debug/zlibd.dll           ${CMAKE_BINARY_DIR}/Debug
#  COMMAND	${CMAKE_COMMAND} -E copy ${ZLIB_ROOT}/build/Release/zlib.dll          ${CMAKE_BINARY_DIR}/Release
#  COMMAND	${CMAKE_COMMAND} -E copy ${ZLIB_ROOT}/build/RelWithDebInfo/zlib.dll   ${CMAKE_BINARY_DIR}/RelWithDebInfo
#)

#-------------------------------------------------------------------------------------
# Add carve thirdparty library without corrupting our own install target.
#-------------------------------------------------------------------------------------

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

#-------------------------------------------------------------------------------------
# Set the target properties.
#-------------------------------------------------------------------------------------

#set_target_properties(ZLIBCopyBinaries							PROPERTIES FOLDER "Copy")
set_target_properties(CopyOpenInfraPlatformUIResources 					PROPERTIES FOLDER "Copy")
set_target_properties(OklabiCopyBinaries						PROPERTIES FOLDER "Copy")
#set_target_properties(BlueFrameworkCopyBinaries 					PROPERTIES FOLDER "Copy")
#set_target_properties(Qt5CopyBinaries			 				PROPERTIES FOLDER "Copy")
set_target_properties(QSimpleUpdaterCopyBinaries					PROPERTIES FOLDER "Copy")
set_target_properties(OpenInfraPlatform.UI						PROPERTIES FOLDER "OpenInfraPlatform")
set_target_properties(OpenInfraPlatform.Core						PROPERTIES FOLDER "OpenInfraPlatform")
set_target_properties(OpenInfraPlatform.ExpressBindingGenerator				PROPERTIES FOLDER "OpenInfraPlatform/ExpressBindingGenerator")

# Currently not included. 
#set_target_properties(OpenInfraPlatform.CommandLineUtilities		PROPERTIES FOLDER "OpenInfraPlatform")
#set_target_properties(OpenInfraPlatform.IfcBridgeGenerator			PROPERTIES FOLDER "OpenInfraPlatform")
#set_target_properties(OpenInfraPlatform.IfcTunnelGenerator			PROPERTIES FOLDER "OpenInfraPlatform")
#set_target_properties(OpenInfraPlatform.LandXMLViewer				PROPERTIES FOLDER "OpenInfraPlatform")
#set_target_properties(OpenInfraPlatform.RoadXMLViewer				PROPERTIES FOLDER "OpenInfraPlatform")

# Switched to static gtest on 28.11.2018 / Revision 388+
#set_target_properties(GTestCopyBinaries							PROPERTIES FOLDER "Copy")

#----------------------------------------------------------
# MODULES
#----------------------------------------------------------

# Group of entries below. 
# Select all modules with necessary thirdparty libraries to be built. 
# Otherwise only core project is built.



#----------------------------------------------------------
# (2/7) Digital Elevation Model 
#----------------------------------------------------------
Option(MODULES_DIGITAL_ELEVATION_MODEL ON)

if(MODULES_DIGITAL_ELEVATION_MODEL)

ENDIF()

#----------------------------------------------------------
# (3/7) Girder 
#----------------------------------------------------------
Option(MODULES_GIRDER ON)

if(MODULES_GIRDER)

ENDIF()

#----------------------------------------------------------
# (4/7) Proxy Model 
#----------------------------------------------------------
Option(MODULES_PROXY_MODEL ON)

if(MODULES_PROXY_MODEL)

ENDIF()

#----------------------------------------------------------
# (5/7) Railway 
#----------------------------------------------------------
Option(MODULES_RAILWAY ON)

if(MODULES_RAILWAY)

ENDIF()

#----------------------------------------------------------
# (6/7) Slabfield 
#----------------------------------------------------------
Option(MODULES_SLABFIELD ON)

if(MODULES_SLABFIELD)

ENDIF()

#----------------------------------------------------------
# (7/7) Tesselation 
#----------------------------------------------------------
Option(MODULES_TESSELATION ON)

if(MODULES_TESSELATION)

ENDIF()

#-------------------------------------------------------------------------------------
# Deployment & Installation.
#-------------------------------------------------------------------------------------

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
set(CPACK_WIX_UI_BANNER "${PROJECT_SOURCE_DIR}/Data/banner.bmp")
set(CPACK_WIX_PRODUCT_ICON "${PROJECT_SOURCE_DIR}/UserInterface/Resources/icons/icon.ico")
set(CPACK_WIX_PROGRAM_MENU_FOLDER "TUM OpenInfraPlatform")
set(CPACK_PACKAGE_EXECUTABLES OpenInfraPlatform.UI "TUM OpenInfraPlatform")
set(CPACK_WIX_CULTURES "en-us")

include(CPackComponent)

cpack_add_component(oip_runtime 	DISPLAY_NAME "Runtime" DESCRIPTION "Application runtime components (*.dll, *.exe)" REQUIRED INSTALL_TYPES default)
cpack_add_component(oip_import_libs DISPLAY_NAME "Import libs" DESCRIPTION "Infrastructure import library (*.lib)" REQUIRED INSTALL_TYPES default)
cpack_add_component(oip_static_libs DISPLAY_NAME "Static libs" DESCRIPTION "Infrastructure static library (*.lib)" REQUIRED INSTALL_TYPES default)
cpack_add_component(oip_data 		DISPLAY_NAME "Application data" DESCRIPTION "Data required by the application" REQUIRED INSTALL_TYPES default)
cpack_add_component(oip_thirdparty 	DISPLAY_NAME "Thirdparty libraries" DESCRIPTION "Thirdparty libraries required by the application" REQUIRED INSTALL_TYPES default)

set(CPACK_COMPONENTS_ALL "oip_runtime;oip_import_libs;oip_static_libs;oip_data;oip_thirdparty")

install(TARGETS OpenInfraPlatform.UI
   RUNTIME DESTINATION bin
   COMPONENT oip_runtime
)

find_file(MSVC_VCOMP_DLL NAMES vcomp140.dll PATHS ${WINDIR}/System32)
find_file(MSVC_VCRUNTIME_DLL NAMES vcruntime140.dll PATHS ${WINDIR}/System32)
find_file(MSVC_VCCORLIB_DLL NAMES vccorlib140.dll PATHS ${WINDIR}/System32)
find_file(MSVC_MSVCP_DLL NAMES msvcp140.dll PATHS ${WINDIR}/System32)
find_file(MSVC_MSVCP_WIN_DLL NAMES msvcp_win.dll PATHS ${WINDIR}/System32)
find_file(MSVC_MSVCRT_DLL NAMES msvcrt.dll PATHS ${WINDIR}/System32)

set(WINDOWS_RUNTIME_DLLS
	${MSVC_VCOMP_DLL}
	${MSVC_VCRUNTIME_DLL}
	${MSVC_VCCORLIB_DLL}
	${MSVC_MSVCP_DLL}
	${MSVC_MSVCP_WIN_DLL}
	${MSVC_MSVCRT_DLL}
)

macro(installData DATA)
	install(DIRECTORY ${DATA} DESTINATION bin
    COMPONENT oip_data
    FILES_MATCHING PATTERN "*.*") 
endmacro()

installData(${PROJECT_SOURCE_DIR}/UserInterface/Shader)
installData(${PROJECT_SOURCE_DIR}/UserInterface/Data)
installData(${CMAKE_BINARY_DIR}/$<CONFIG>/schema)
installData(${CMAKE_BINARY_DIR}/$<CONFIG>/res)
installData(${CMAKE_BINARY_DIR}/$<CONFIG>/fbliste)
installData(${CMAKE_BINARY_DIR}/UserInterface/Style)
#installData(${PROJECT_SOURCE_DIR}/other/testdata)
		
install(FILES ${WINDOWS_RUNTIME_DLLS} ${BLUEFRAMEWORK_RELEASE_BINARIES} ${OKLABI_DLLS} ${QT5_DLLS_RELEASE} ${LIBLAS_RELEASE_BINARIES} ${GTEST_RELEASE_BINARIES} ${ZLIB_RELEASE_BINARIES} ${CC_RELEASE_BINARIES} ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/libeay32.dll ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/ssleay32.dll ${CMAKE_BINARY_DIR}/Debug/tinyxml2.dll
	DESTINATION bin
	COMPONENT oip_thirdparty)
	
#install(FILES ${WINDOWS_RUNTIME_DLLS} ${BLUEFRAMEWORK_RELEASE_BINARIES} ${OKLABI_DLLS} ${QT5_DLLS_RELEASE} ${LIBLAS_RELEASE_BINARIES} ${GTEST_RELEASE_BINARIES} ${ZLIB_RELEASE_BINARIES} ${CC_RELEASE_BINARIES} ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/libeay32.dll ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/ssleay32.dll ${CMAKE_BINARY_DIR}/Release/tinyxml2.dll
#	DESTINATION bin
#	COMPONENT oip_thirdparty)

install(FILES ${Qt5_IMAGEFORMATS_PLUGINS_DLLS}
		DESTINATION bin/plugins/imageformats
		COMPONENT oip_thirdparty)
		
install(FILES ${Qt5_GEOSERVICES_PLUGINS_DLLS}
	DESTINATION bin/plugins/geoservices
	COMPONENT oip_thirdparty)

install(FILES ${Qt5_PLATFORMS_PLUGINS_DLLS}
	DESTINATION bin/platforms
	COMPONENT oip_thirdparty)

install(FILES ${Qt5_NETWORK_PLUGINS_DLLS}
	DESTINATION bin/plugins/bearer
	COMPONENT oip_thirdparty)
	
install(FILES ${Qt5_ICONENGINES_PLUGINS_DLLS}
	DESTINATION bin/plugins/iconengines
	COMPONENT oip_thirdparty)
	
include(CPack)
