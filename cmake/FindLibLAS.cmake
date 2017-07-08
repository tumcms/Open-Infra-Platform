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
#	LIBLAS_FOUND
#	LIBLAS_LIBRARIES
#	LIBLAS_INCLUDE_DIRS
#	LIBLAS_RELEASE_BINARIES
#	LIBLAS_DEBUG_BINARIES
#	LIBLAS_RELWITHDEBINFO_BINARIES
#

find_path(LIBLAS_ROOT NAMES liblas-osgeo4w-init.bat include/liblas/liblas.hpp HINTS "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\libLAS-1.6-master" REQUIRED)

if(NOT LIBLAS_ROOT)
	set(LIBLAS_INSTALL_DIR "C:/thirdparty/${MSVC_VERSION_STRING}/x64" CACHE FILEPATH "Please specify an installation directory.")
	option(LIBLAS_AUTOMATIC_INSTALL OFF)
	if(NOT BOOST_ROOT)
		find_path(BOOST_ROOT REQUIRED)
		message(FATAL_ERROR"Boost required!")
	endif()
	if(LIBLAS_AUTOMATIC_INSTALL AND LIBLAS_INSTALL_DIR AND BOOST_ROOT)
		message(STATUS "Installing libLAS...")
		execute_process(COMMAND "${PROJECT_SOURCE_DIR}/external/Build_libLAS-1.6_Visual Studio 14 2015 Win64.cmd"
		${LIBLAS_INSTALL_DIR}
		"${CMAKE_COMMAND}"
		"${BOOST_ROOT}"
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/external
		RESULT_VARIABLE RESULT
		ERROR_FILE "${PROJECT_SOURCE_DIR}/external/log_install_liblas.txt"
		OUTPUT_FILE "${PROJECT_SOURCE_DIR}/external/log_install_liblas.txt")
		if(RESULT EQUAL 0)
			message(STATUS "Successfully installed libLAS.")
			set(LIBLAS_ROOT ${LIBLAS_INSTALL_DIR}/libLAS-1.6-master CACHE PATH "libLAS root" FORCE)
		else()
			message(SEND_ERROR "Installation failed. Processes exited with code ${RESULT}. Output was written to ${PROJECT_SOURCE_DIR}/external/log_install_liblas.txt")
		endif()
		set(LIBLAS_AUTOMATIC_INSTALL OFF CACHE BOOL "Automatically install libLAS" FORCE)
	endif()	
endif()


if(LIBLAS_ROOT)
	find_path(LIBLAS_INCLUDE_DIR NAMES liblas/liblas.hpp PATHS ${LIBLAS_ROOT}/include)
	
	find_library(LIBLAS_LIBRARY_RELEASE NAMES liblas.lib HINTS "${LIBLAS_ROOT}/build/bin/Release")
	find_library(LIBLAS_LIBRARY_DEBUG NAMES liblas.lib HINTS "${LIBLAS_ROOT}/build/bin/Debug")	
	find_library(LIBLAS_LIBRARY_RELWITHDEBINFO NAMES liblas.lib HINTS "${LIBLAS_ROOT}/build/bin/RelWithDebInfo")
	
	find_file(LIBLAS_LIBRARY_RELEASE_DLL NAMES liblas.dll HINTS "${LIBLAS_ROOT}/build/bin/Release")
	find_file(LIBLAS_LIBRARY_DEBUG_DLL NAMES liblas.dll HINTS "${LIBLAS_ROOT}/build/bin/Debug")	
	find_file(LIBLAS_LIBRARY_RELWITHDEBINFO_DLL NAMES liblas.dll HINTS "${LIBLAS_ROOT}/build/bin/RelWithDebInfo")
	
	find_file(LIBLAS_LIBRARY_DEBUG_PDB NAMES liblas.pdb HINTS "${LIBLAS_ROOT}/build/bin/Debug")	
	find_file(LIBLAS_LIBRARY_RELWITHDEBINFO_PDB NAMES liblas.pdb HINTS "${LIBLAS_ROOT}/build/bin/RelWithDebInfo")
	
	find_library(LIBLAS_C_LIBRARY_RELEASE NAMES liblas_c.lib HINTS "${LIBLAS_ROOT}/build/bin/Release")
	find_library(LIBLAS_C_LIBRARY_DEBUG NAMES liblas_c.lib HINTS "${LIBLAS_ROOT}/build/bin/Debug")
	find_library(LIBLAS_C_LIBRARY_RELWITHDEBINFO NAMES liblas_c.lib HINTS "${LIBLAS_ROOT}/build/bin/RelWithDebInfo")
	
	find_file(LIBLAS_C_LIBRARY_RELEASE_DLL NAMES liblas_c.dll HINTS "${LIBLAS_ROOT}/build/bin/Release")
	find_file(LIBLAS_C_LIBRARY_DEBUG_DLL NAMES liblas_c.dll HINTS "${LIBLAS_ROOT}/build/bin/Debug")
	find_file(LIBLAS_C_LIBRARY_RELWITHDEBINFO_DLL NAMES liblas_c.dll HINTS "${LIBLAS_ROOT}/build/bin/RelWithDebInfo")
	
	find_file(LIBLAS_C_LIBRARY_DEBUG_PDB NAMES liblas_c.pdb HINTS "${LIBLAS_ROOT}/build/bin/Debug")	
	find_file(LIBLAS_C_LIBRARY_RELWITHDEBINFO_PDB NAMES liblas_c.pdb HINTS "${LIBLAS_ROOT}/build/bin/RelWithDebInfo")
	
	if(LIBLAS_LIBRARY_RELEASE AND LIBLAS_LIBRARY_DEBUG)
		set(LIBLAS_LIBRARY debug "${LIBLAS_LIBRARY_DEBUG}" optimized "${LIBLAS_LIBRARY_RELEASE}")
	endif()
	
	if(LIBLAS_C_LIBRARY_RELEASE AND LIBLAS_C_LIBRARY_DEBUG)
		set(LIBLAS_C_LIBRARY debug "${LIBLAS_C_LIBRARY_DEBUG}" optimized "${LIBLAS_C_LIBRARY_RELEASE}")
	endif()
	
	if(LIBLAS_LIBRARY_RELEASE_DLL AND LIBLAS_C_LIBRARY_RELEASE_DLL)
		set(LIBLAS_RELEASE_BINARIES "${LIBLAS_LIBRARY_RELEASE_DLL}" "${LIBLAS_C_LIBRARY_RELEASE_DLL}")
	endif()
	
	if(LIBLAS_LIBRARY_DEBUG_DLL AND LIBLAS_C_LIBRARY_DEBUG_DLL AND LIBLAS_LIBRARY_DEBUG_PDB AND LIBLAS_C_LIBRARY_DEBUG_PDB)
		set(LIBLAS_DEBUG_BINARIES 
			"${LIBLAS_LIBRARY_DEBUG_DLL}"
			"${LIBLAS_C_LIBRARY_DEBUG_DLL}"
			"${LIBLAS_LIBRARY_DEBUG_PDB}"
			"${LIBLAS_C_LIBRARY_DEBUG_PDB}")
	endif()
	
	if(LIBLAS_LIBRARY_RELWITHDEBINFO_DLL AND LIBLAS_C_LIBRARY_RELWITHDEBINFO_DLL AND LIBLAS_LIBRARY_DEBUG_PDB AND LIBLAS_C_LIBRARY_DEBUG_PDB)
		set(LIBLAS_RELWITHDEBINFO_BINARIES
			"${LIBLAS_LIBRARY_RELWITHDEBINFO_DLL}"
			"${LIBLAS_C_LIBRARY_RELWITHDEBINFO_DLL}"
			"${LIBLAS_LIBRARY_RELWITHDEBINFO_PDB}"
			"${LIBLAS_C_LIBRARY_RELWITHDEBINFO_PDB}")
	endif()
	
	if(LIBLAS_LIBRARY AND LIBLAS_C_LIBRARY)
		set(LIBLAS_LIBRARIES ${LIBLAS_C_LIBRARY} ${LIBLAS_LIBRARY})
	endif()
	if(LIBLAS_INCLUDE_DIR)
		set(LIBLAS_INCLUDE_DIRS ${LIBLAS_INCLUDE_DIR})
	endif()
endif()

if(LIBLAS_LIBRARIES AND LIBLAS_INCLUDE_DIRS)
	message(STATUS "Successfully found libLAS.")
	set(LIBLAS_FOUND 1)
else()
	unset(LIBLAS_FOUND)
	message(FATAL_ERROR "Could NOT find libLAS.")
endif()

if(LIBLAS_DEBUG_BINARIES AND LIBLAS_RELEASE_BINARIES AND LIBLAS_RELWITHDEBINFO_BINARIES)
	function(LIBLAS_COPY_BINARIES TargetDirectory)
		add_custom_target(libLASCopyBinaries
			COMMENT "Copying libLAS binaries to '${TargetDirectory}'" VERBATIM
			COMMAND ${CMAKE_COMMAND} -E copy ${LIBLAS_DEBUG_BINARIES} ${TargetDirectory}/Debug
			COMMAND ${CMAKE_COMMAND} -E copy ${LIBLAS_RELEASE_BINARIES} ${TargetDirectory}/Release
			COMMAND ${CMAKE_COMMAND} -E copy ${LIBLAS_RELWITHDEBINFO_BINARIES} ${TargetDirectory}/RelWithDebInfo		
		)
	endfunction(LIBLAS_COPY_BINARIES)
endif()

LIBLAS_COPY_BINARIES(${CMAKE_BINARY_DIR})