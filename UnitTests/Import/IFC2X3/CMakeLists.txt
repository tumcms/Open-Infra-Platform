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
file(GLOB OpenInfraPlatform_UnitTests_Import_IFC2X3	*.cpp)

source_group(UnitTests\\IFC2X3   			FILES ${OpenInfraPlatform_UnitTests_Import_IFC2X3})
source_group(UnitTests                   	FILES ${OpenInfraPlatform_UnitTests_Source})

add_executable(IFC2X3
	${OpenInfraPlatform_UnitTests_Import_IFC2X3}
	${OpenInfraPlatform_UnitTests_Source}
)

include_directories(${BLUEFRAMEWORK_INCLUDE_DIR})

target_link_libraries(IFC2X3
	OpenInfraPlatform.IFC2X3
	${BLUEFRAMEWORK_LIBRARIES}
	GTest::GTest
	GTest::Main
)

add_test(
    NAME IFC2X3Test
    COMMAND IFC2X3
)

set_target_properties(IFC2X3 PROPERTIES FOLDER "UnitTests/Import")

add_custom_target(CopyIFC2X3UnitTestResources
	COMMENT "Copying resources from '${CMAKE_SOURCE_DIR}/UnitTests/Import/IFC2X3/Data' to '${CMAKE_BINARY_DIR}/UnitTests/Import/IFC2X3'" VERBATIM
	COMMAND	${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/UnitTests/Import/IFC2X3/Data
	COMMAND	${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/UnitTests/Import/IFC2X3/Data   ${CMAKE_BINARY_DIR}/UnitTests/Import/IFC2X3/Data
)
	
set_target_properties(CopyIFC2X3UnitTestResources PROPERTIES FOLDER "UnitTests/Import/Copy")