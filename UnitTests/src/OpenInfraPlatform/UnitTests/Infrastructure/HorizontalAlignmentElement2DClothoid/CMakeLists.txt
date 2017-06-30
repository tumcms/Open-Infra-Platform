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

file(GLOB OpenInfraPlatform_UnitTests_Infrastructure_HorizontalAlignmentElement2DClothoid	*.*)

source_group(OpenInfraPlatform\\UnitTests\\Infrastructure 	FILES ${OpenInfraPlatform_UnitTests_Infrastructure_HorizontalAlignmentElement2DClothoid})
source_group(OpenInfraPlatform\\UnitTests       			FILES ${OpenInfraPlatform_UnitTests_Source})

add_executable(HorizontalAlignmentElement2DClothoid
	${OpenInfraPlatform_UnitTests_Source}
	${OpenInfraPlatform_UnitTests_Infrastructure_HorizontalAlignmentElement2DClothoid}
)

target_link_libraries(HorizontalAlignmentElement2DClothoid 
	OpenInfraPlatform.Infrastructure
	# BlueFramework
	${BLUEFRAMEWORK_BLUECORE_LIBRARY}
	${BLUEFRAMEWORK_BLUEIMAGEPROCESSING_LIBRARY}
	${BLUEFRAMEWORK_BLUERASTERIZER_LIBRARY}
	${BLUEFRAMEWORK_BLUEENGINE_LIBRARY}
	${BLUEFRAMEWORK_BLUEAPPLICATION_LIBRARY}
	# Googletest
	${GTEST_LIBRARIES}
	${GTEST_MAIN_LIBRARIES})

include_directories(
	${DirectX12_INCLUDE_DIR}
	${DirectX12_INCLUDE_DIR_SHARED}
)

add_test(
    NAME HorizontalAlignmentElement2DClothoidTest
    COMMAND HorizontalAlignmentElement2DClothoid
)

set_target_properties(HorizontalAlignmentElement2DClothoid PROPERTIES FOLDER "OpenInfraPlatform/UnitTests/Infrastructure")