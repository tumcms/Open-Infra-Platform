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

# Once done this will define
#	CC_INCLUDE_DIRS
#	CC_LIBRARIES

find_path(CC_ROOT NAMES build/CloudCompareProjects.sln CC/include/AutoSegmentationTools.h HINTS "C:/thirdparty/${MSVC_VERSION_STRING}/x64/CloudCOmpare-master" REQUIRED)
#find_path(CC_BUILD_DIR NAMES CloudCompareProjects.sln REQUIRED)

if(NOT CC_ROOT)
	set(CC_INSTALL_DIR "C:/thirdparty/${MSVC_VERSION_STRING}/x64" CACHE FILEPATH "Please specify an installation directory.")
	option(CC_AUTOMATIC_INSTALL OFF)
	if(CC_INSTALL_DIR AND CC_AUTOMATIC_INSTALL)
		message(STATUS "Installing CloudCompare...")
		set(CC_INSTALL_LOGFILE ${PROJECT_SOURCE_DIR}/external/log_install_cc.txt)
		if(${MSVC_VERSION_STRING} STREQUAL "vs2015")
			set(CC_BUILD_SCRIPT "Build_CloudCompare_Visual Studio 14 2015 Win64.cmd")
		elseif(${MSVC_VERSION_STRING} STREQUAL "vs2017")
			set(CC_BUILD_SCRIPT "Build_CloudCompare_Visual Studio 15 2017 Win64.cmd")		
		else()
			message(FATAL_ERROR "Couldn't determine VS version.")
		endif()
		execute_process(COMMAND "${PROJECT_SOURCE_DIR}/external/${CC_BUILD_SCRIPT}"
			${CC_INSTALL_DIR}
			"${CMAKE_COMMAND}"
			WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/external
			RESULT_VARIABLE RESULT
			ERROR_FILE "${CC_INSTALL_LOGFILE}"
			OUTPUT_FILE "${CC_INSTALL_LOGFILE}")
		if(RESULT EQUAL 0)
			set(CC_ROOT ${CC_INSTALL_DIR}/CloudCompare-master CACHE PATH "CC root" FORCE)
			set(CC_SOURCE_DIR ${CC_ROOT})
			set(CC_BUILD_DIR ${CC_ROOT}/build)
			message(STATUS "Successfully installed CloudCompare.")
		else()
			message(SEND_ERROR "Installation failed. Processes exited with code ${RESULT}. Output was written to ${CC_INSTALL_LOGFILE}")
		endif()
		set(CC_AUTOMATIC_INSTALL OFF CACHE BOOL "Automatically install CloudCompare" FORCE)
	endif()
else()
	set(CC_SOURCE_DIR ${CC_ROOT})
	set(CC_BUILD_DIR ${CC_ROOT}/build)
endif()

if(CC_SOURCE_DIR)
	set(CC_INCLUDE_DIRS
		${CC_SOURCE_DIR}/CC/include
		${CC_SOURCE_DIR}/libs/qCC_db 
		${CC_SOURCE_DIR}/libs/qCC_io
		${CC_SOURCE_DIR}/libs/qCC_glWindow
		CACHE STRING "CloudCompare include directories" FORCE
	)
endif()

if(CC_BUILD_DIR)
	set(CC_DB_LIBRARIES
		debug ${CC_BUILD_DIR}/libs/qCC_db/Debug/QCC_DB_LIBd.lib 
		optimized ${CC_BUILD_DIR}/libs/qCC_db/Release/QCC_DB_LIB.lib
	)
	
	set(CC_DEBUG_BINARIES ${CC_DEBUG_BINARIES} ${CC_BUILD_DIR}/libs/qCC_db/Debug/QCC_DB_LIBd.dll)
	set(CC_RELEASE_BINARIES ${CC_RELEASE_BINARIES} ${CC_BUILD_DIR}/libs/qCC_db/Release/QCC_DB_LIB.dll)


	set(CC_IO_LIBRARIES 
		debug ${CC_BUILD_DIR}/libs/qCC_io/Debug/QCC_IO_LIBd.lib
		optimized ${CC_BUILD_DIR}/libs/qCC_io/Release/QCC_IO_LIB.lib
	
	)
	
	set(CC_DEBUG_BINARIES ${CC_DEBUG_BINARIES} ${CC_BUILD_DIR}/libs/qCC_io/Debug/QCC_IO_LIBd.dll)
	set(CC_RELEASE_BINARIES ${CC_RELEASE_BINARIES} ${CC_BUILD_DIR}/libs/qCC_io/Release/QCC_IO_LIB.dll)
	
	set(CC_GL_LIBRARIES
		debug ${CC_BUILD_DIR}/libs/qCC_glWindow/Debug/QCC_GL_LIBd.lib
		optimized ${CC_BUILD_DIR}/libs/qCC_glWindow/Release/QCC_GL_LIB.lib
	)
	
	set(CC_CORE_LIBRARIES
		debug ${CC_BUILD_DIR}/CC/Debug/CC_CORE_LIBd.lib
		optimized ${CC_BUILD_DIR}/CC/Release/CC_CORE_LIB.lib
	)
	
	set(CC_DEBUG_BINARIES ${CC_DEBUG_BINARIES} ${CC_BUILD_DIR}/CC/Debug/CC_CORE_LIBd.dll)
	set(CC_RELEASE_BINARIES ${CC_RELEASE_BINARIES} ${CC_BUILD_DIR}/CC/Release/CC_CORE_LIB.dll)
	
	set(CC_LIBRARIES ${CC_DB_LIBRARIES} ${CC_IO_LIBRARIES} ${CC_GL_LIBRARIES} ${CC_CORE_LIBRARIES} CACHE STRING "CloudCompare libraries" FORCE)
	set(CC_BINARIES debug ${CC_DEBUG_BINARIES} optimized ${CC_RELEASE_BINARIES} CACHE STRING "CloudCompare shared library files" FORCE)
endif()

function(CLOUDCOMPARE_COPY_BINARIES TargetDirectory)
	add_custom_target(CloudCompareCopyBinaries
		COMMENT "Copying CloudCompare binaries to '${TargetDirectory}'" VERBATIM
		COMMAND ${CMAKE_COMMAND} -E copy ${CC_DEBUG_BINARIES} ${TargetDirectory}/Debug
		COMMAND ${CMAKE_COMMAND} -E copy ${CC_RELEASE_BINARIES} ${TargetDirectory}/Release		
	)
endfunction(CLOUDCOMPARE_COPY_BINARIES)