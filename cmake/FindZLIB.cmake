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
# This module defines the following variables:
#
# ::
#
#   ZLIB_INCLUDE_DIRS   - where to find zlib.h, etc.
#   ZLIB_LIBRARIES      - List of libraries when using zlib.
#   ZLIB_FOUND          - True if zlib found.
#
# ::
#
#   ZLIB_VERSION_STRING - The version of zlib found (x.y.z)
#   ZLIB_VERSION_MAJOR  - The major version of zlib
#   ZLIB_VERSION_MINOR  - The minor version of zlib
#   ZLIB_VERSION_PATCH  - The patch version of zlib
#   ZLIB_VERSION_TWEAK  - The tweak version of zlib
#
# Backward Compatibility
# ^^^^^^^^^^^^^^^^^^^^^^
#
# The following variable are provided for backward compatibility
#
# ::
#
#   ZLIB_MAJOR_VERSION  - The major version of zlib
#   ZLIB_MINOR_VERSION  - The minor version of zlib
#   ZLIB_PATCH_VERSION  - The patch version of zlib
#
# Hints
# ^^^^^
#
# A user may set ``ZLIB_ROOT`` to a zlib installation root to tell this
# module where to look.

find_path(ZLIB_ROOT NAMES include/zlib.h include/zconf.h HINTS "C:/thirdparty/${MSVC_VERSION_STRING}/x64/zlib-1.2.11" CACHE PATH "Path to zlib installation root directory" REQUIRED)

if(ZLIB_ROOT)
	set(CMAKE_MODULE_PATH ${CMAKE_ROOT}/Modules)
	find_package(zlib 1.2.10 REQUIRED)
	if(ZLIB_FOUND)
		set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake/)
	endif()
else()
	set(ZLIB_INSTALL_DIR "C:/thirdparty/${MSVC_VERSION_STRING}/x64" CACHE FILEPATH "Please specify an installation directory.")
	option(ZLIB_AUTOMATIC_INSTALL OFF)
	if(ZLIB_INSTALL_DIR AND ZLIB_AUTOMATIC_INSTALL)
		message(STATUS "Installing zlib...")
		set(ZLIB_INSTALL_LOGFILE ${PROJECT_SOURCE_DIR}/external/log_install_zlib.txt)
		if(${MSVC_VERSION_STRING} STREQUAL "vs2015")
			set(ZLIB_BUILD_SCRIPT "Build_zlib-1.2.11_Visual Studio 14 2015 Win64.cmd")
		elseif(${MSVC_VERSION_STRING} STREQUAL "vs2017")
			set(ZLIB_BUILD_SCRIPT "Build_zlib-1.2.11_Visual Studio 15 2017 Win64.cmd")		
		else()
			message(FATAL_ERROR "Couldn't determine VS version.")
		endif()
		execute_process(COMMAND "${PROJECT_SOURCE_DIR}/external/${ZLIB_BUILD_SCRIPT}"
			${ZLIB_INSTALL_DIR}
			"${CMAKE_COMMAND}"
			WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/external
			RESULT_VARIABLE RESULT
			ERROR_FILE "${ZLIB_INSTALL_LOGFILE}"
			OUTPUT_FILE "${ZLIB_INSTALL_LOGFILE}")
		if(RESULT EQUAL 0)
			find_path(ZLIB_ROOT NAMES include/zlib.h include/zconf.h HINTS "${ZLIB_INSTALL_DIR}/zlib-1.2.11" CACHE PATH "Path to zlib installation root directory" REQUIRED)
			find_package(zlib 1.2.10)
			if(ZLIB_FOUND)
				message(STATUS "Successfully installed zlib.")
			elseif()
				message(STATUS "zlib installed without error but couldn't find required paths.")
			endif()
		else()
			message(SEND_ERROR "Installation failed. Processes exited with code ${RESULT}. Output was written to ${ZLIB_INSTALL_LOGFILE}")
		endif()
		set(ZLIB_AUTOMATIC_INSTALL OFF CACHE BOOL "Automatically install zlib" FORCE)
	endif()
endif()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake/)

if(ZLIB_ROOT AND ZLIB_FOUND)
	function(ZLIB_COPY_BINARIES TargetDirectory)
		add_custom_target(ZLIBCopyBinaries
			COMMENT "Copying zlib binaries to '${TargetDirectory}'" VERBATIM
			COMMAND ${CMAKE_COMMAND} -E copy ${ZLIB_ROOT}/bin/zlibd1.dll ${TargetDirectory}/Debug
			COMMAND ${CMAKE_COMMAND} -E copy ${ZLIB_ROOT}/bin/zlib1.dll ${TargetDirectory}/Release		
		)
	endfunction(ZLIB_COPY_BINARIES)
endif()