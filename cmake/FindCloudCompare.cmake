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

find_path(CC_SOURCE_DIR NAMES CCPConfig.cmake.in CC/include/AutoSegmentationTools.h REQUIRED)
find_path(CC_BUILD_DIR NAMES CloudCompareProjects.sln REQUIRED)

if(CC_SOURCE_DIR)
	set(CC_INCLUDE_DIRS
		${CC_SOURCE_DIR}/CC/include
		${CC_SOURCE_DIR}/libs/qCC_db 
		${CC_SOURCE_DIR}/libs/qCC_io
		${CC_SOURCE_DIR}/libs/qCC_glWindow
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
	
	set(CC_LIBRARIES ${CC_DB_LIBRARIES} ${CC_IO_LIBRARIES} ${CC_GL_LIBRARIES} ${CC_CORE_LIBRARIES})
endif()

function(CLOUDCOMPARE_COPY_BINARIES TargetDirectory)
	add_custom_target(CloudCompareCopyBinaries
		COMMENT "Copying CloudCompare binaries to '${TargetDirectory}'" VERBATIM
		COMMAND ${CMAKE_COMMAND} -E copy ${CC_DEBUG_BINARIES} ${TargetDirectory}/Debug
		COMMAND ${CMAKE_COMMAND} -E copy ${CC_RELEASE_BINARIES} ${TargetDirectory}/Release		
	)
endfunction(BLUEFRAMEWORK_COPY_BINARIES)