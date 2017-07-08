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
#	For exported variables please refer to the FindZLIB.cmake file distributed with CMake.
#

set(CMAKE_MODULE_PATH ${CMAKE_ROOT}/Modules)
find_package(zlib REQUIRED)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake/)

if(NOT ZLIB_FOUND)
	if(NOT ZLIB_ROOT)
		find_path(ZLIB_ROOT NAMES NAMES test/minigzip.c adler32.c zlib.h PATHS ${ZLIB_INSTALL_DIR}/zlib-1.2.11	HINTS "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\zlib-1.2.11")
	endif()
	if(NOT ZLIB_ROOT)
		option(ZLIB_AUTOMATIC_INSTALL OFF)
		find_path(ZLIB_INSTALL_DIR OPTIONAL)
	
		if(ZLIB_AUTOMATIC_INSTALL AND ZLIB_INSTALL_DIR)
		message(STATUS "Installing zlib...")
			execute_process(COMMAND "${PROJECT_SOURCE_DIR}/external/Build_zlib-1.2.11_Visual Studio 14 2015 Win64.cmd"
			${ZLIB_INSTALL_DIR}
			"${CMAKE_COMMAND}"
			WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/external
			RESULT_VARIABLE RESULT
			ERROR_FILE "${PROJECT_SOURCE_DIR}/external/log_install_zlib.txt"
			OUTPUT_FILE "${PROJECT_SOURCE_DIR}/external/log_install_zlib.txt")
			if(RESULT EQUAL 0)
				message(STATUS "Successfully installed zlib.")
				find_path(ZLIB_ROOT NAMES NAMES test/minigzip.c adler32.c zlib.h PATHS ${ZLIB_INSTALL_DIR}/zlib-1.2.11	HINTS "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\zlib-1.2.11")
			else()
				message(SEND_ERROR "Installation failed. Processes exited with code ${RESULT}. Output was written to ${PROJECT_SOURCE_DIR}/external/log_install_zlib.txt")
			endif()
			set(ZLIB_AUTOMATIC_INSTALL OFF CACHE BOOL "Automatically install zlib" FORCE)
		endif()
	endif()
endif()

if(ZLIB_LIBRARIES AND ZLIB_INCLUDE_DIRS AND ZLIB_FOUND)
	message(STATUS "Successfully found zlib.")
else()
	message(FATAL_ERROR "Could NOT find zlib.")
endif()