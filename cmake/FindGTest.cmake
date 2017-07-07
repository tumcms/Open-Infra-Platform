#
#   This file is part of BlueFramework, a simple 3D engine.
#	Copyright (c) 2016-2017 Technical University of Munich
#	Chair of Computational Modeling and Simulation.
#
#   BlueFramework is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License Version 3
#   as published by the Free Software Foundation.
#
#   BlueFramework is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program. If not, see <http://www.gnu.org/licenses/>.
#
# This module defines the following variables:
#
#   GTEST_INCLUDE_DIRS
#	GTEST_MAIN_LIBRARIES
#   GTEST_LIBRARIES
#	GTEST_BOTH_LIBRARIES
#   GTEST_FOUND
#
find_path(GTEST_ROOT NAMES googletest/include/gtest/gtest.h googlemock/include/gmock/gmock.h  REQUIRED)

if(NOT GTEST_ROOT)
	set(CMAKE_MODULE_PATH ${CMAKE_ROOT}/Modules)
	find_package(gtest REQUIRED)
	set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake/)
	
	set(GTEST_INSTALL_DIR "C:/thirdparty/${MSVC_VERSION_STRING}/x64" CACHE FILEPATH "Please specify an installation directory.")
	option(GTEST_AUTOMATIC_INSTALL OFF)
	if(GTEST_AUTOMATIC_INSTALL AND GTEST_INSTALL_DIR)
		message(STATUS "Installing GTest...")
		execute_process(COMMAND "${PROJECT_SOURCE_DIR}/external/Build_googletest-1.8.0_Visual Studio 14 2015 Win64.cmd"
		${GTEST_INSTALL_DIR}
		"${CMAKE_COMMAND}"
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/external
		RESULT_VARIABLE RESULT
		ERROR_FILE "${PROJECT_SOURCE_DIR}/external/log_install_gtest.txt"
		OUTPUT_FILE "${PROJECT_SOURCE_DIR}/external/log_install_gtest.txt")
		if(RESULT EQUAL 0)
			set(GTEST_ROOT ${GTEST_INSTALL_DIR}/googletest-release-1.8.0 CACHE PATH "GTest root" FORCE)
			message(STATUS "Successfully installed GTest.")
		else()
			message(SEND_ERROR "Installation failed. Processes exited with code ${RESULT}. Output was written to ${PROJECT_SOURCE_DIR}/external/log_install_gtest.txt")
		endif()
		set(GTEST_AUTOMATIC_INSTALL OFF CACHE BOOL "Automatically install GTest" FORCE)
	endif()
endif()

if(GTEST_ROOT)
	find_library(GTEST_LIBRARY NAMES gtest.lib HINTS "${GTEST_ROOT}/build/googlemock/gtest/Release/")
	find_library(GTEST_MAIN_LIBRARY NAMES gtest_main.lib HINTS "${GTEST_ROOT}/build/googlemock/gtest/Release/")
	find_library(GTEST_LIBRARY_DEBUG NAMES gtest.lib HINTS "${GTEST_ROOT}/build/googlemock/gtest/Debug/")
	find_library(GTEST_MAIN_LIBRARY_DEBUG NAMES gtest_main.lib HINTS "${GTEST_ROOT}/build/googlemock/gtest/Debug/")
	find_path(GTEST_INCLUDE_DIR NAMES gtest/gtest.h HINTS "${GTEST_ROOT}/googletest/include")
	if(GTEST_LIBRARY AND GTEST_LIBRARY_DEBUG)
		set(GTEST_LIBRARIES debug "${GTEST_LIBRARY_DEBUG}" optimized "${GTEST_LIBRARY}")
	endif()
	if(GTEST_MAIN_LIBRARY AND GTEST_MAIN_LIBRARY_DEBUG)
		set(GTEST_MAIN_LIBRARIES debug "${GTEST_MAIN_LIBRARY_DEBUG}" optimized "${GTEST_MAIN_LIBRARY}")
	endif()
	if(GTEST_MAIN_LIBRARIES AND GTEST_LIBRARIES)
		set(GTEST_BOTH_LIBRARIES ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
	endif()
	if(GTEST_INCLUDE_DIR)
		set(GTEST_INCLUDE_DIRS ${GTEST_INCLUDE_DIR})
	endif()
endif()

if(GTEST_BOTH_LIBRARIES AND GTEST_INCLUDE_DIRS)
	set(GTEST_FOUND 1)
	message(STATUS "Successfully found GTest.")
else()
	unset(GTEST_FOUND)
	message(FATAL_ERROR "Could NOT find GTest.")
endif()
	

function(GTEST_COPY_BINARIES TargetDirectory)
	add_custom_target(GTestCopyBinaries
		COMMENT "Copying googletest binaries to '${TargetDirectory}'" VERBATIM
		COMMAND ${CMAKE_COMMAND} -E copy ${GTEST_ROOT}/build/googlemock/gtest/Debug/gtest.dll ${TargetDirectory}/Debug
		COMMAND ${CMAKE_COMMAND} -E copy ${GTEST_ROOT}/build/googlemock/gtest/Debug/gtest_main.dll ${TargetDirectory}/Debug
		COMMAND ${CMAKE_COMMAND} -E copy ${GTEST_ROOT}/build/googlemock/gtest/Release/gtest.dll ${TargetDirectory}/Release
		COMMAND ${CMAKE_COMMAND} -E copy ${GTEST_ROOT}/build/googlemock/gtest/Release/gtest_main.dll ${TargetDirectory}/Release
		COMMAND ${CMAKE_COMMAND} -E copy ${GTEST_ROOT}/build/googlemock/gtest/RelWithDebInfo/gtest.dll ${TargetDirectory}/RelWithDebInfo
		COMMAND ${CMAKE_COMMAND} -E copy ${GTEST_ROOT}/build/googlemock/gtest/RelWithDebInfo/gtest_main.dll ${TargetDirectory}/RelWithDebInfo
	)
endfunction(GTEST_COPY_BINARIES)