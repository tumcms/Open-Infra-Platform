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

file(GLOB OpenInfraPlatform_UnitTests_Infrastructure_TrafficSign	*.*)

source_group(OpenInfraPlatform\\UnitTests\\Infrastructure 	FILES ${OpenInfraPlatform_UnitTests_Infrastructure_TrafficSign})
source_group(OpenInfraPlatform\\UnitTests       			FILES ${OpenInfraPlatform_UnitTests_Source})

add_executable(TrafficSign
	${OpenInfraPlatform_UnitTests_Source}
	${OpenInfraPlatform_UnitTests_Infrastructure_TrafficSign}
)

target_link_libraries(TrafficSign 
	OpenInfraPlatform.Infrastructure
	OpenInfraPlatform.IfcAlignment1x1
	# BlueFramework
	${BLUEFRAMEWORK_BLUECORE_LIBRARY}
	${BLUEFRAMEWORK_BLUEIMAGEPROCESSING_LIBRARY}
	${BLUEFRAMEWORK_BLUERASTERIZER_LIBRARY}
	${BLUEFRAMEWORK_BLUEENGINE_LIBRARY}
	${BLUEFRAMEWORK_BLUEAPPLICATION_LIBRARY}
	# Googletest
	${GTEST_LIBRARIES}
	${GTEST_MAIN_LIBRARIES}	
)

include_directories(
	${DirectX12_INCLUDE_DIR}
	${DirectX12_INCLUDE_DIR_SHARED}
)

add_test(
    NAME TrafficSignTest
    COMMAND TrafficSign
)

set_target_properties(TrafficSign PROPERTIES FOLDER "OpenInfraPlatform/UnitTests/Infrastructure")

# housekeeping for shaders, resources, etc. which are needed during testing
add_custom_target(CopyTrafficSignResources
	# Effect
	COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/UnitTests/src/OpenInfraPlatform/UnitTests/Infrastructure/TrafficSign/Data   Data		
)

set_target_properties(CopyTrafficSignResources PROPERTIES FOLDER "OpenInfraPlatform/UnitTests/Infrastructure/Copy")

add_dependencies(TrafficSign
	CopyTrafficSignResources
)