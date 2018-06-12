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

cmake_minimum_required(VERSION 3.8)
cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0048 NEW)
project(OpenInfraPlatform)

#-------------------------------------------------------------------------------------
# CMake definitions and propertiess
#-------------------------------------------------------------------------------------

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
set(CMAKE_AUTOMOC ON)
set(CMAKE_DEBUG_POSTFIX "d")
include(ProjectVersion)
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
# Look for thirdparty libraries in some predefined locations.
#------------------------------------------------------------------------------

option(OIP_USE_PREDEFINED_THIRDPARTY_PATH "Set to ON to find boost, Eigen and Qt path" ON)

if(OIP_USE_PREDEFINED_THIRDPARTY_PATH)
	# Try to find Boost, Eigen3, Qt5 and other dependencies without user input
	find_path(BOOST_ROOT NAMES boost/version.hpp HINTS 
			  "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\boost_1_65_1"
	          "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\boost_1_65_0" 
			  "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\boost_1_64_0" 
			  "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\boost_1_63_0")
	find_path(EIGEN3_INCLUDE_DIR NAMES Eigen/Core HINTS 
			  "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\Eigen_3.3.4")
	find_path(CMAKE_PREFIX_PATH NAMES include/QtCore/QObject HINTS 
			  "C:\\Qt\\Qt5.9.0\\5.9\\msvc${MSVC_VERSION_YEAR}_64" 
			  "C:\\Qt\\5.9\\msvc${MSVC_VERSION_YEAR}_64" 
			  "C:\\Qt\\Qt5.9.1\\5.9.1\\msvc${MSVC_VERSION_YEAR}_64"
			  "C:\\Qt\\5.9.2\\msvc${MSVC_VERSION_YEAR}_64"
			  "C:\\Qt\\Qt5.9.3\\5.9.3\\msvc${MSVC_VERSION_YEAR}_64"
			  "C:\\Qt\\Qt5.10.0\\5.10.0\\msvc${MSVC_VERSION_YEAR}_64"
			  "C:\\Qt\\5.10.0\\msvc${MSVC_VERSION_YEAR}_64"
			  "C:\\Qt\\5.10.1\\msvc${MSVC_VERSION_YEAR}_64")
	find_path(GTEST_ROOT NAMES googletest/include/gtest/gtest.h HINTS 
		      "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\googletest-release-1.8.0" 
		      "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\googletest-1.8.0")
	find_path(ZLIB_ROOT NAMES zlib.h HINTS 
	          "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\zlib-1.2.11")
	find_path(RAPTOR2_ROOT_DIR include/raptor2/raptor2.h HINTS 
	          "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\raptor2")		
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

set(Boost_USE_STATIC_LIBS   ON)
find_package(Boost 1.63.0 COMPONENTS signals system filesystem REQUIRED) # we suggest Boost 1.65.1
find_package(BlueFramework COMPONENTS Core Engine Application ImageProcessing Rasterizer D3D11RenderSystem D3D12RenderSystem REQUIRED)
find_package(OpenInfraPlatform.EarlyBinding REQUIRED)
find_package(Eigen3 3.3.2  REQUIRED)
find_package(Oklabi REQUIRED)
find_package(gtest REQUIRED) 
find_package(ZLIB 1.2.10 REQUIRED)
find_package(libLAS REQUIRED)
find_package(qhull REQUIRED)
find_package(raptor2 REQUIRED)
find_package(CloudCompare REQUIRED)
find_path(visit_struct_INCLUDE_DIR REQUIRED)

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
foreach(Component ${QT5_COMPONENTS})
	find_package( Qt5 5.11.0 COMPONENTS ${Component}	REQUIRED)
	if(TARGET ${Qt5${Component}_LIBRARIES})
		get_target_property(Qt5${Component}_location ${Qt5${Component}_LIBRARIES} LOCATION_Release)
		set(QT5_DLLS_RELEASE ${QT5_DLLS_RELEASE} ${Qt5${Component}_location})
		get_target_property(Qt5${Component}_location ${Qt5${Component}_LIBRARIES} LOCATION_Debug)
		set(QT5_DLLS_DEBUG ${QT5_DLLS_DEBUG} ${Qt5${Component}_location})
	endif()
endforeach()

#------------------------------------------------------------------------------
# Set required Qt plugins variables and find and add the corresponding dlls for deployment and copying.
#------------------------------------------------------------------------------

set(Qt5_IMAGEFORMATS_PLUGINS
	QGifPlugin
	QICNSPlugin
	QICOPlugin
	QJpegPlugin
	QTgaPlugin
	QTiffPlugin
	QWbmpPlugin
	QWebpPlugin
	QSvgPlugin
)

set(Qt5_GEOSERVICES_PLUGINS
	QGeoServiceProviderFactoryOsm
	QGeoServiceProviderFactoryNokia
	QGeoServiceProviderFactoryMapbox
	QGeoServiceProviderFactoryItemsOverlay
	GeoServiceProviderFactoryEsri
)

set(Qt5_PLATFORMS_PLUGINS
	QWindowsIntegrationPlugin
	QWindowsDirect2DIntegrationPlugin
	QMinimalIntegrationPlugin
	QOffscreenIntegrationPlugin
)

set(Qt5_NETWORK_PLUGINS
	QGenericEnginePlugin
)

set(Qt5_ICONENGINES_PLUGINS
	QSvgIconPlugin
)

foreach(plugin ${Qt5_GEOSERVICES_PLUGINS})
	include(${Qt5Location_DIR}/Qt5Location_${plugin}.cmake)
endforeach()

string(REPLACE "lib/cmake/Qt5" "bin" Qt5_BIN_DIR "${Qt5_DIR}")

macro(addQt5Dll lib)
	set(QT5_DLLS_RELEASE ${QT5_DLLS_RELEASE} ${Qt5_BIN_DIR}/Qt5${lib}.dll)
	set(QT5_DLLS_DEBUG ${QT5_DLLS_DEBUG} ${Qt5_BIN_DIR}/Qt5${lib}d.dll)
endmacro()

macro(addQt5PluginDll plugin output)
	get_target_property(_loc Qt5::${plugin} LOCATION)
	list(APPEND ${output} ${_loc})
endmacro()

addQt5Dll(Gui)
addQt5Dll(Multimedia)
addQt5Dll(MultimediaWidgets)
addQt5Dll(OpenGL)
addQt5Dll(Sensors)
addQt5Dll(Sql)
addQt5Dll(WebChannel)
addQt5Dll(Concurrent)

foreach(plugin ${Qt5_PLATFORMS_PLUGINS})
	addQt5PluginDll(${plugin} Qt5_PLATFORMS_PLUGINS_DLLS)
endforeach()
foreach(plugin ${Qt5_IMAGEFORMATS_PLUGINS})
	addQt5PluginDll(${plugin} Qt5_IMAGEFORMATS_PLUGINS_DLLS)
endforeach()
foreach(plugin ${Qt5_GEOSERVICES_PLUGINS})
	addQt5PluginDll(${plugin} Qt5_GEOSERVICES_PLUGINS_DLLS)
endforeach()
foreach(plugin ${Qt5_NETWORK_PLUGINS})
	addQt5PluginDll(${plugin} Qt5_NETWORK_PLUGINS_DLLS)
endforeach()
foreach(plugin ${Qt5_ICONENGINES_PLUGINS})
	addQt5PluginDll(${plugin} Qt5_ICONENGINES_PLUGINS_DLLS)
endforeach()

#------------------------------------------------------------------------------
# Set include directories and link directories.
#------------------------------------------------------------------------------

include_directories(
	${CMAKE_CURRENT_BINARY_DIR} # Qt generated files will be located here
	${Boost_INCLUDE_DIR}
	${BLUEFRAMEWORK_INCLUDE_DIR}
	${OpenInfraPlatform.EarlyBinding_INCLUDE_DIR}
	${EIGEN3_INCLUDE_DIR}	
	src
	external/QtXlsxWriter/src/xlsx
	external/QSimpleUpdater/src
	external/QSimpleUpdater/dialogs
	Infrastructure/canonicalHeaders
	${ZLIB_INCLUDE_DIRS}	
	${visit_struct_INCLUDE_DIR}
	external/carve/include
	${CMAKE_BINARY_DIR}/external/carve/include
	external/carve/common
	ExpressBinding/src
	Infrastructure/src
	${CC_INCLUDE_DIRS}
)

link_directories(
	${Boost_LIBRARY_DIRS}
	${OKLABI_ROOT_DIR}
)

#------------------------------------------------------------------------------
# Add subdirectories.
#------------------------------------------------------------------------------

add_subdirectory(external/QtXlsxWriter)
add_subdirectory(external/QSimpleUpdater)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/carve)
add_subdirectory(Infrastructure)
add_subdirectory(UnitTests)
add_subdirectory(oip)
add_subdirectory(IfcBridgeGenerator)
add_subdirectory(ExpressBinding)

# Do currently not work
#add_subdirectory(RoadXMLViewer)
#add_subdirectory(LandXMLViewer)
#add_subdirectory(IfcTunnelGenerator)


#------------------------------------------------------------------------------
# Collect source files
#------------------------------------------------------------------------------

# Collect general source files
file(GLOB OpenInfraPlatform_Source									src/OpenInfraPlatform/*.*)
file(GLOB OpenInfraPlatform_Core_Source 							src/OpenInfraPlatform/Core/*.*)
file(GLOB OpenInfraPlatform_Data_Source 							src/OpenInfraPlatform/Data/*.*)
file(GLOB OpenInfraPlatform_DataManagement_Command_Source 			src/OpenInfraPlatform/DataManagement/Command/*.*)
file(GLOB OpenInfraPlatform_DataManagement_Source 					src/OpenInfraPlatform/DataManagement/*.*)
file(GLOB OpenInfraPlatform_IfcGeometryConverter_Source  			src/OpenInfraPlatform/IfcGeometryConverter/*.*)

# UnitTesting for images is currently not working but still in the code so files have to be collected
file(GLOB OpenInfraPlatform_UnitTesting_Source						src/OpenInfraPlatform/UnitTesting/*.*)

# Collect Shader files
file(GLOB OpenInfraPlatform_Shader_Source 							src/OpenInfraPlatform/Shader/*.*)
file(GLOB OpenInfraPlatform_Shader_D3D_Source 						src/OpenInfraPlatform/Shader/D3D/*.*)

# Collect UserInterface files
file(GLOB OpenInfraPlatform_UserInterface_ColorPicker_Source		src/OpenInfraPlatform/UserInterface/ColorPicker/*.*)
file(GLOB OpenInfraPlatform_UserInterface_Tools_Source				src/OpenInfraPlatform/UserInterface/Tools/*.*)
file(GLOB OpenInfraPlatform_UserInterface_Source 					src/OpenInfraPlatform/UserInterface/*.*)
file(GLOB OpenInfraPlatform_UserInterface_View2DWindow			 	src/OpenInfraPlatform/UserInterface/View2DWindow/*.*)
file(GLOB OpenInfraPlatform_UserInterface_ViewPanel_Source 			src/OpenInfraPlatform/UserInterface/ViewPanel/*.*)
file(GLOB OpenInfraPlatform_UserInterface_ViewPanel_Effects_Source 	src/OpenInfraPlatform/UserInterface/ViewPanel/Effects/*.*)

file(GLOB OpenInfraPlatform_QtPropertyBrowser_Source 				src/QtPropertyBrowser/*.*)

# Collect Qt related stuff and UI files
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
	src/OpenInfraPlatform/Forms/ShowIFCtree.ui
	src/OpenInfraPlatform/Forms/ExportExcel.ui
	src/OpenInfraPlatform/Forms/ExportIfc4x1Dialog.ui
	src/OpenInfraPlatform/Forms/ExportIfcAlignmentDialog.ui
	src/OpenInfraPlatform/Forms/ExportIfcZipDialog.ui
	src/OpenInfraPlatform/Forms/GenerateTerrain.ui
	src/OpenInfraPlatform/Forms/MainWindow.ui
	src/OpenInfraPlatform/Forms/OSMImportDialog.ui
	src/OpenInfraPlatform/Forms/PreferencesDialog.ui
	src/OpenInfraPlatform/Forms/VerticalAlignmentWindow.ui
	src/OpenInfraPlatform/Forms/XYZImportDialog.ui
	src/OpenInfraPlatform/Forms/LicenseAndCopyrightInformation.ui
	src/OpenInfraPlatform/Forms/CreateAccidentReport.ui
	src/OpenInfraPlatform/Forms/AddGeoreferenceDialog.ui
)

# Collect RC files
set(OpenInfraPlatform_RC
	src/OpenInfraPlatform/Resources/OpenInfraPlatform.qrc
	src/QtPropertyBrowser/qtpropertybrowser.qrc
)

# Collect all translation files
FILE(GLOB Translation_TS Data/translations/*.ts)

#------------------------------------------------------------------------------
# Set source groups
#------------------------------------------------------------------------------

source_group(OpenInfraPlatform										FILES ${OpenInfraPlatform_Source})
source_group(OpenInfraPlatform\\Core								FILES ${OpenInfraPlatform_Core_Source})
source_group(OpenInfraPlatform\\Data								FILES ${OpenInfraPlatform_Data_Source})
source_group(OpenInfraPlatform\\DataManagement						FILES ${OpenInfraPlatform_DataManagement_Source})
source_group(OpenInfraPlatform\\DataManagement\\Command				FILES ${OpenInfraPlatform_DataManagement_Command_Source})
source_group(OpenInfraPlatform\\IfcGeometryConverter				FILES ${OpenInfraPlatform_IfcGeometryConverter_Source})

# Set Shader source groups
source_group(OpenInfraPlatform\\Shader								FILES ${OpenInfraPlatform_Shader_Source})
source_group(OpenInfraPlatform\\Shader\\D3D							FILES ${OpenInfraPlatform_Shader_D3D_Source})

# UnitTesting for images is currently not working but still in the code so it has to be linked
source_group(OpenInfraPlatform\\UnitTesting  						FILES ${OpenInfraPlatform_UnitTesting_Source})

# Set UserInterface source groups
source_group(OpenInfraPlatform\\UserInterface						FILES ${OpenInfraPlatform_UserInterface_Source})
source_group(OpenInfraPlatform\\UserInterface\\ColorPicker			FILES ${OpenInfraPlatform_UserInterface_ColorPicker_Source})
source_group(OpenInfraPlatform\\UserInterface\\Tools				FILES ${OpenInfraPlatform_UserInterface_Tools_Source})
source_group(OpenInfraPlatform\\UserInterface\\View2DWindow			FILES ${OpenInfraPlatform_UserInterface_View2DWindow})
source_group(OpenInfraPlatform\\UserInterface\\ViewPanel			FILES ${OpenInfraPlatform_UserInterface_ViewPanel_Source})
source_group(OpenInfraPlatform\\UserInterface\\ViewPanel\\Effects	FILES ${OpenInfraPlatform_UserInterface_ViewPanel_Effects_Source})
source_group(OpenInfraPlatform\\UserInterface\\Forms				FILES ${OpenInfraPlatform_UIS})

source_group(QtPropertyBrowser										FILES ${OpenInfraPlatform_QtPropertyBrowser_Source})

#------------------------------------------------------------------------------
# Set source group properties
#------------------------------------------------------------------------------

# Set HEADER_FILES_ONLY to true to make them show up in the IDE but be excluded from compiling
set_source_files_properties(${OpenInfraPlatform_Shader_Source} 		PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties(${OpenInfraPlatform_Shader_D3D_Source} 	PROPERTIES HEADER_FILE_ONLY TRUE)

# Qt related stuff
QT5_ADD_RESOURCES(OpenInfraPlatform_RC_SRCS ${OpenInfraPlatform_RC})
QT5_WRAP_UI(OpenInfraPlatform_UIS_H ${OpenInfraPlatform_UIS})
QT5_ADD_TRANSLATION(OpenInfra_QMS ${Translation_TS})

IF(NOT QT_LRELEASE_EXECUTABLE AND NOT Qt5_LRELEASE_EXECUTABLE)
	MESSAGE(WARNING "Could not find lrelease. Your build won't contain translations.")
ENDIF(NOT QT_LRELEASE_EXECUTABLE AND NOT Qt5_LRELEASE_EXECUTABLE)

#------------------------------------------------------------------------------
# Add the actual executable.
#------------------------------------------------------------------------------

add_executable(OpenInfraPlatform.UI
	${OpenInfraPlatform_QtPropertyBrowser_Source}
	${OpenInfraPlatform_UIS_H}
	${OpenInfraPlatform_RC_SRCS}
	${OpenInfraPlatform_Source}
	${OpenInfraPlatform_Core_Source}
	${OpenInfraPlatform_Data_Source}
	${OpenInfraPlatform_DataManagement_Source}
	${OpenInfraPlatform_DataManagement_Command_Source}
	${OpenInfraPlatform_IfcGeometryConverter_Source}
	${OpenInfraPlatform_UnitTesting_Source}
	${OpenInfraPlatform_UserInterface_Source}
	${OpenInfraPlatform_UserInterface_ColorPicker_Source}
	${OpenInfraPlatform_UserInterface_Tools_Source}
	${OpenInfraPlatform_UserInterface_ViewPanel_Source}
	${OpenInfraPlatform_UserInterface_ViewPanel_Effects_Source}
	${OpenInfraPlatform_UserInterface_View2DWindow}	
	${OpenInfraPlatform_Shader_Source}
	${OpenInfraPlatform_Shader_D3D_Source}
)

#------------------------------------------------------------------------------
# Link qt and other external libraries to our executable.
#------------------------------------------------------------------------------

# Use the Widgets module from Qt 5.
target_link_libraries(OpenInfraPlatform.UI Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Xml Qt5::XmlPatterns Qt5::Svg Qt5::PrintSupport Qt5::Quick Qt5::Qml Qt5::Location Qt5::Positioning)

target_link_libraries( OpenInfraPlatform.UI
	OpenInfraPlatform.Infrastructure
	OpenInfraPlatform.ExpressBinding	
	${OpenInfraPlatform.EarlyBinding_LIBRARIES}
	Qt5::WinMain  # New target available via find_package ( Qt5Core )
	${BLUEFRAMEWORK_LIBRARIES}
	QtXlsxWriter
	QSimpleUpdater
	${LIBLAS_LIBRARIES}
	carve
	${ZLIB_LIBRARIES}
	Rpcrt4.lib
	${CC_LIBRARIES}
)


#------------------------------------------------------------------------------
# Calling copy functions to provide custom targets.
# Add the custom targets to copy the required binaries.
#------------------------------------------------------------------------------

# BlueFramework Copy Binaries
BLUEFRAMEWORK_COPY_BINARIES(${CMAKE_BINARY_DIR})

# CloudCompare Copy Binaries
CLOUDCOMPARE_COPY_BINARIES(${CMAKE_BINARY_DIR})

# Oklabi Copy Binaries
OKLABI_COPY_BINARIES(${CMAKE_BINARY_DIR})

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

# QSimpleUpdater
add_custom_target(QSimpleUpdaterCopyBinaries
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/libeay32.dll	${CMAKE_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/libeay32.dll	${CMAKE_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/libeay32.dll	${CMAKE_BINARY_DIR}/RelWithDebInfo

	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/ssleay32.dll	${CMAKE_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/ssleay32.dll	${CMAKE_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/external/QSimpleUpdater/ssleay32.dll	${CMAKE_BINARY_DIR}/RelWithDebInfo
)


add_custom_target(ZLIBCopyBinaries
  COMMAND	${CMAKE_COMMAND} -E copy ${ZLIB_ROOT}/build/Debug/zlibd.dll           ${CMAKE_BINARY_DIR}/Debug
  COMMAND	${CMAKE_COMMAND} -E copy ${ZLIB_ROOT}/build/Release/zlib.dll          ${CMAKE_BINARY_DIR}/Release
  COMMAND	${CMAKE_COMMAND} -E copy ${ZLIB_ROOT}/build/RelWithDebInfo/zlib.dll   ${CMAKE_BINARY_DIR}/RelWithDebInfo
)

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

set_target_properties(ZLIBCopyBinaries							PROPERTIES FOLDER "Copy")
set_target_properties(CopyOpenInfraPlatformUIResources 			PROPERTIES FOLDER "Copy")
set_target_properties(OklabiCopyBinaries						PROPERTIES FOLDER "Copy")
set_target_properties(BlueFrameworkCopyBinaries 				PROPERTIES FOLDER "Copy")
set_target_properties(CloudCompareCopyBinaries 				PROPERTIES FOLDER "Copy")
set_target_properties(Qt5CopyBinaries			 				PROPERTIES FOLDER "Copy")
set_target_properties(QSimpleUpdaterCopyBinaries				PROPERTIES FOLDER "Copy")
set_target_properties(GTestCopyBinaries							PROPERTIES FOLDER "Copy")
set_target_properties(libLASCopyBinaries						PROPERTIES FOLDER "Copy")
set_target_properties(OpenInfraPlatform.ExpressBinding		 	PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding")
#set_target_properties(OpenInfraPlatform.EXPRESS2Source		 	PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding")

set_target_properties(OpenInfraPlatform.CommandLineUtilities PROPERTIES FOLDER "OpenInfraPlatform")
set_target_properties(OpenInfraPlatform.IfcBridgeGenerator	 PROPERTIES FOLDER "OpenInfraPlatform")
#set_target_properties(OpenInfraPlatform.IfcTunnelGenerator	 PROPERTIES FOLDER "OpenInfraPlatform")
set_target_properties(OpenInfraPlatform.Infrastructure		 PROPERTIES FOLDER "OpenInfraPlatform")
#set_target_properties(OpenInfraPlatform.LandXMLViewer		 PROPERTIES FOLDER "OpenInfraPlatform")
#set_target_properties(OpenInfraPlatform.RoadXMLViewer		 PROPERTIES FOLDER "OpenInfraPlatform")
set_target_properties(OpenInfraPlatform.UI					 PROPERTIES FOLDER "OpenInfraPlatform")

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
set(CPACK_WIX_PRODUCT_ICON "${PROJECT_SOURCE_DIR}/src/OpenInfraPlatform/Resources/icons/icon.ico")
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

installData(${PROJECT_SOURCE_DIR}/src/OpenInfraPlatform/Shader)
installData(${PROJECT_SOURCE_DIR}/Data)
installData(${PROJECT_SOURCE_DIR}/testdata)
installData(${CMAKE_BINARY_DIR}/schema)
installData(${CMAKE_BINARY_DIR}/res)
installData(${CMAKE_BINARY_DIR}/fbliste)
installData(${CMAKE_BINARY_DIR}/Style)
		
install(FILES ${WINDOWS_RUNTIME_DLLS} ${BLUEFRAMEWORK_RELEASE_BINARIES} ${OKLABI_DLLS} ${QT5_DLLS_RELEASE} ${LIBLAS_RELEASE_BINARIES} ${GTEST_RELEASE_BINARIES} ${CC_RELEASE_BINARIES}
	DESTINATION bin
	COMPONENT oip_thirdparty)
	
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