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
#	This module defines the following variables:
#
#   QHULL_INCLUDE_DIRS
#	QHULL_STATIC_LIBRARIES
#   QHULL_FOUND
#

find_path(QHULL_ROOT NAMES src/qhull-all.pro HINTS "C:\\thirdparty\\vs2015\\x64\\qhull-master" REQUIRED)

if(NOT QHULL_ROOT)
	option(QHULL_AUTOMATIC_INSTALL "Automatically install qhull" OFF)
	set(QHULL_INSTALL_DIR "C:/thirdparty/${MSVC_VERSION_STRING}/x64" CACHE FILEPATH "Please specify an installation directory.")
	if(QHULL_AUTOMATIC_INSTALL AND QHULL_INSTALL_DIR)
		MESSAGE(STATUS "Installing qhull...")
		execute_process(COMMAND "${PROJECT_SOURCE_DIR}/external/Build_qhull-2015.2_Visual Studio 14 2015 Win64.cmd"
		${QHULL_INSTALL_DIR}
		"${CMAKE_COMMAND}"
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/external
		RESULT_VARIABLE RESULT
		ERROR_FILE "${PROJECT_SOURCE_DIR}/external/log_install_qhull.txt"
		OUTPUT_FILE "${PROJECT_SOURCE_DIR}/external/log_install_qhull.txt")
		set(QHULL_AUTOMATIC_INSTALL OFF CACHE BOOL "Automatically install qhull" FORCE)
		if(RESULT EQUAL 0)
			message(STATUS "Successfully installed qhull.")
			set(QHULL_ROOT ${QHULL_INSTALL_DIR}/qhull-master CACHE PATH "qhull root" FORCE)
		else()
			message(SEND_ERROR "Installation failed. Processes exited with code ${RESULT}. Output was written to ${PROJECT_SOURCE_DIR}/external/log_install_qhull.txt")
		endif()
	endif()
endif()

if(QHULL_ROOT)
	find_path(QHULL_INCLUDE_DIR NAMES qhull-all.pro PATHS ${QHULL_ROOT}/src)
	find_library(QHULL_STATIC_LIBRARY_RELEASE NAMES qhullstatic.lib PATHS ${QHULL_ROOT}/build/Release)
	find_library(QHULL_STATIC_LIBRARY_DEBUG NAMES qhullstatic.lib PATHS ${QHULL_ROOT}/build/Debug)
	if(QHULL_STATIC_LIBRARY_RELEASE AND QHULL_STATIC_LIBRARY_DEBUG)
		set(QHULL_STATIC_LIBRARIES debug "${QHULL_STATIC_LIBRARY_DEBUG}" optimized "${QHULL_STATIC_LIBRARY_RELEASE}")
	endif()
	if(QHULL_INCLUDE_DIR)
		set(QHULL_INCLUDE_DIRS ${QHULL_INCLUDE_DIR})
	endif()
endif()

if(QHULL_STATIC_LIBRARIES AND QHULL_INCLUDE_DIRS)
	set(QHULL_FOUND 1)
	message(STATUS "Successfully found qhull.")
else()
	unset(QHULL_FOUND)
	message(FATAL_ERROR "Could NOT find qhull.")
endif()
