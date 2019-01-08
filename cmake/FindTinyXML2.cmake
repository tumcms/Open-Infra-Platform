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
#   TINYXML2_INCLUDE_DIRS
#   TINYXML2_LIBRARIES
#   TINYXML2_FOUND
#

find_path(TINYXML2_ROOT NAMES tinyxml2.h REQUIRED)

if(NOT TINYXML2_ROOT)
	set(TINYXML2_INSTALL_DIR "C:/thirdparty/${MSVC_VERSION_STRING}/x64" CACHE PATH "Tinyxml2 root")
	option(TINYXML2_AUTOMATIC_INSTALL OFF)
	if(TINYXML2_AUTOMATIC_INSTALL AND TINYXML2_INSTALL_DIR)
		message(STATUS "Installing TinyXML2...")
		if(${MSVC_VERSION_STRING} STREQUAL "vs2015")
			execute_process(COMMAND "${PROJECT_SOURCE_DIR}/external/Build_tinyxml2_Visual Studio 14 2015 Win64.cmd"
				${TINYXML2_INSTALL_DIR}
				"${CMAKE_COMMAND}"
				WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/external
				RESULT_VARIABLE RESULT
				ERROR_FILE "${PROJECT_SOURCE_DIR}/external/log_install_tinyxml2.txt"
				OUTPUT_FILE "${PROJECT_SOURCE_DIR}/external/log_install_tinyxml2.txt")
		elseif(${MSVC_VERSION_STRING} STREQUAL "vs2017")
			execute_process(COMMAND "${PROJECT_SOURCE_DIR}/external/Build_tinyxml2_Visual Studio 15 2017 Win64.cmd"
				${TINYXML2_INSTALL_DIR}
				"${CMAKE_COMMAND}"
				WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/external
				RESULT_VARIABLE RESULT
				ERROR_FILE "${PROJECT_SOURCE_DIR}/external/log_install_tinyxml2.txt"
				OUTPUT_FILE "${PROJECT_SOURCE_DIR}/external/log_install_tinyxml2.txt")
		else()
			message(FATAL_ERROR "Couldn't determine VS version.")
		endif()

		if(RESULT EQUAL 0)
			message(STATUS "Successfully installed TinyXML2.")
			set(TINYXML2_ROOT ${TINYXML2_INSTALL_DIR}/tinyxml2-master CACHE PATH "Tinyxml2 root" FORCE)
		else()
			message(SEND_ERROR "Installation failed. Processes exited with code ${RESULT}. Output was written to ${PROJECT_SOURCE_DIR}/external/log_install_tinyxml2.txt")
		endif()
		set(TINYXML2_AUTOMATIC_INSTALL OFF CACHE BOOL "Automatically install tinyxml2" FORCE)
	endif()
endif()

if(TINYXML2_ROOT)
	find_library(TINYXML2_LIBRARY_RELEASE NAMES tinyxml2.lib PATHS ${TINYXML2_ROOT}/build/Release REQUIRED)
	find_library(TINYXML2_LIBRARY_DEBUG NAMES tinyxml2d.lib PATHS ${TINYXML2_ROOT}/build/Debug REQUIRED)
	find_library(TINYXML2_LIBRARY_RELWITHDEBINFO NAMES tinyxml2.lib PATHS ${TINYXML2_ROOT}/build/RelWithDebInfo)
	find_path(TINYXML2_INCLUDE_DIR NAMES tinyxml2.h HINTS ${TINYXML2_ROOT} REQUIRED)
	if(TINYXML2_LIBRARY_RELEASE AND TINYXML2_LIBRARY_DEBUG)
		set(TINYXML2_LIBRARIES debug "${TINYXML2_LIBRARY_DEBUG}" optimized "${TINYXML2_LIBRARY_RELEASE}")
	endif()
endif()

if(NOT TINYXML2_INCLUDE_DIR)
	message(FATAL_ERROR "Could NOT find TINYXML2_INCLUDE_DIR.")
	unset(TINYXML2_FOUND)
else()
	set(TINYXML2_INCLUDE_DIRS ${TINYXML2_INCLUDE_DIR})
	message(STATUS "Found TINYXML2_INCLUDE_DIRS: ${TINYXML2_INCLUDE_DIRS}")
endif()
if(NOT TINYXML2_LIBRARIES)
	message(FATAL_ERROR "Could NOT find TINYXML2_LIBRARIES.")
	unset(TINYXML2_FOUND)
else()
	message(STATUS "Found TINYXML2_LIBRARIES: ${TINYXML2_LIBRARIES}")
endif()

if(TINYXML2_LIBRARIES AND TINYXML2_INCLUDE_DIR)
	message(STATUS "Successfully found TinyXML2.")
	set(TINYXML2_FOUND 1)
endif()