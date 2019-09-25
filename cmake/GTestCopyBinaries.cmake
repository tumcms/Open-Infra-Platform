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

if(GTEST_ROOT)
	find_file(GTEST_LIBRARY_RELEASE_DLL NAMES gtest.dll HINTS "${GTEST_ROOT}/bin/")
	find_file(GTEST_LIBRARY_DEBUG_DLL NAMES gtestd.dll HINTS "${GTEST_ROOT}/bin/")	
	
	find_file(GTEST_MAIN_LIBRARY_RELEASE_DLL NAMES gtest_main.dll HINTS "${GTEST_ROOT}/bin/")
	find_file(GTEST_MAIN_LIBRARY_DEBUG_DLL NAMES gtest_maind.dll HINTS "${GTEST_ROOT}/bin/")	
		
	if(GTEST_LIBRARY_RELEASE_DLL AND GTEST_MAIN_LIBRARY_RELEASE_DLL)
		set(GTEST_RELEASE_BINARIES ${GTEST_LIBRARY_RELEASE_DLL} ${GTEST_MAIN_LIBRARY_RELEASE_DLL})
	endif()
	
	if(GTEST_LIBRARY_DEBUG_DLL AND GTEST_MAIN_LIBRARY_DEBUG_DLL)
		set(GTEST_DEBUG_BINARIES ${GTEST_LIBRARY_DEBUG_DLL} ${GTEST_MAIN_LIBRARY_DEBUG_DLL})
	endif()
endif()
	
if(GTEST_RELEASE_BINARIES AND GTEST_DEBUG_BINARIES)
	function(GTEST_COPY_BINARIES TargetDirectory)
		add_custom_target(GTestCopyBinaries
			COMMENT "Copying googletest release binaries ${GTEST_RELEASE_BINARIES} to '${TargetDirectory}/Release'" VERBATIM
			COMMAND ${CMAKE_COMMAND} -E copy ${GTEST_RELEASE_BINARIES} ${TargetDirectory}/Release
			COMMENT "Copying googletest debug binaries ${GTEST_DEBUG_BINARIES} to '${TargetDirectory}/Debug'" VERBATIM
			COMMAND ${CMAKE_COMMAND} -E copy ${GTEST_DEBUG_BINARIES} ${TargetDirectory}/Debug
		)
	endfunction(GTEST_COPY_BINARIES)	
endif()