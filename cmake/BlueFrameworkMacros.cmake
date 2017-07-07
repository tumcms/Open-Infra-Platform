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

macro(findInclude Module)
	string(TOUPPER ${Module} Module2)	
	
	unset("BLUEFRAMEWORK_${Module2}_INCLUDE_DIR" CACHE)
	find_path("BLUEFRAMEWORK_${Module2}_INCLUDE_DIR" NAMES BlueFramework/${Module}/namespace.h HINTS ${BlueFramework_DIR}/include ${BlueFramework_DIR}/${Module}/src)	
	set(BLUEFRAMEWORK_INCLUDE_DIR ${BLUEFRAMEWORK_INCLUDE_DIR} "${BLUEFRAMEWORK_${Module2}_INCLUDE_DIR}")
endmacro()

macro(findLibs Module)
	string(TOUPPER ${Module} Module2)
	
	unset("BLUEFRAMEWORK_${Module2}_LIBRARY_DEBUG" CACHE)
	find_file("BLUEFRAMEWORK_${Module2}_LIBRARY_DEBUG" BlueFramework.${Module}d.lib PATHS ${BLUEFRAMEWORK_LIBRARY_DIR}/Debug)
	
	unset("BLUEFRAMEWORK_${Module2}_LIBRARY_RELEASE" CACHE)
	find_file("BLUEFRAMEWORK_${Module2}_LIBRARY_RELEASE" BlueFramework.${Module}.lib PATHS ${BLUEFRAMEWORK_LIBRARY_DIR}/Release)
	
	unset("BLUEFRAMEWORK_${Module2}_LIBRARY_RELWITHDEBINFO" CACHE)
	find_file("BLUEFRAMEWORK_${Module2}_LIBRARY_RELWITHDEBINFO" BlueFramework.${Module}.lib PATHS ${BLUEFRAMEWORK_LIBRARY_DIR}/RelWithDebInfo)
	
	set(BLUEFRAMEWORK_${Module2}_LIBRARY debug "${BLUEFRAMEWORK_${Module2}_LIBRARY_DEBUG}" optimized "${BLUEFRAMEWORK_${Module2}_LIBRARY_RELEASE}")
	set(BLUEFRAMEWORK_LIBRARIES ${BLUEFRAMEWORK_LIBRARIES} "${BLUEFRAMEWORK_${Module2}_LIBRARY}")
endmacro()

macro(findBinaries Module)
	string(TOUPPER ${Module} Module2)
	
	unset("BLUEFRAMEWORK_${Module2}_DLL_DEBUG" CACHE)
	unset("BLUEFRAMEWORK_${Module2}_DLL_RELEASE" CACHE)
	unset("BLUEFRAMEWORK_${Module2}_DLL_RELWITHDEBINFO" CACHE)	
	find_file("BLUEFRAMEWORK_${Module2}_DLL_DEBUG" BlueFramework.${Module}d.dll PATHS ${BLUEFRAMEWORK_LIBRARY_DIR}/Debug)
	find_file("BLUEFRAMEWORK_${Module2}_DLL_RELEASE" BlueFramework.${Module}.dll PATHS ${BLUEFRAMEWORK_LIBRARY_DIR}/Release)
	find_file("BLUEFRAMEWORK_${Module2}_DLL_RELWITHDEBINFO" BlueFramework.${Module}.dll PATHS ${BLUEFRAMEWORK_LIBRARY_DIR}/RelWithDebInfo)
	
	
	unset("BLUEFRAMEWORK_${Module2}_PDB_DEBUG" CACHE)
	unset("BLUEFRAMEWORK_${Module2}_PDB_RELWITHDEBINFO" CACHE)
	find_file("BLUEFRAMEWORK_${Module2}_PDB_DEBUG" BlueFramework.${Module}d.pdb PATHS ${BLUEFRAMEWORK_LIBRARY_DIR}/Debug)
	find_file("BLUEFRAMEWORK_${Module2}_PDB_RELWITHDEBINFO" BlueFramework.${Module}.pdb PATHS ${BLUEFRAMEWORK_LIBRARY_DIR}/RelWithDebInfo)
	
	set(BLUEFRAMEWORK_DEBUG_BINARIES ${BLUEFRAMEWORK_DEBUG_BINARIES} "${BLUEFRAMEWORK_${Module2}_DLL_DEBUG}" "${BLUEFRAMEWORK_${Module2}_PDB_DEBUG}")
	set(BLUEFRAMEWORK_RELEASE_BINARIES ${BLUEFRAMEWORK_RELEASE_BINARIES} "${BLUEFRAMEWORK_${Module2}_DLL_RELEASE}")
	set(BLUEFRAMEWORK_RELWITHDEBINFO_BINARIES ${BLUEFRAMEWORK_RELWITHDEBINFO_BINARIES} "${BLUEFRAMEWORK_${Module2}_DLL_RELWITHDEBINFO}" "${BLUEFRAMEWORK_${Module2}_PDB_RELWITHDEBINFO}")
endmacro()

function(BLUEFRAMEWORK_COPY_BINARIES TargetDirectory)
	add_custom_target(BlueFrameworkCopyBinaries
		COMMENT "Copying BlueFramwork binaries to '${TargetDirectory}'" VERBATIM
		COMMAND ${CMAKE_COMMAND} -E copy ${BLUEFRAMEWORK_DEBUG_BINARIES} ${CMAKE_BINARY_DIR}/Debug
		COMMAND ${CMAKE_COMMAND} -E copy ${BLUEFRAMEWORK_RELEASE_BINARIES} ${CMAKE_BINARY_DIR}/Release
		COMMAND ${CMAKE_COMMAND} -E copy ${BLUEFRAMEWORK_RELWITHDEBINFO_BINARIES} ${CMAKE_BINARY_DIR}/RelWithDebInfo
	)
endfunction(BLUEFRAMEWORK_COPY_BINARIES)