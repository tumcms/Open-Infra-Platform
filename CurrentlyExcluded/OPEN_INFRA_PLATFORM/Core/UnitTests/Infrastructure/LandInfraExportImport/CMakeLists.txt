#
#    Copyright (c) 2021 Technical University of Munich
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

file(GLOB OpenInfraPlatform_UnitTests_Infrastructure_LandInfraExportImport	*.cpp)

source_group(OpenInfraPlatform\\UnitTests\\Infrastructure 	FILES ${OpenInfraPlatform_UnitTests_Infrastructure_LandInfraExportImport})
source_group(OpenInfraPlatform\\UnitTests       			FILES ${OpenInfraPlatform_UnitTests_Source})

add_executable(LandInfraExportImport
	${OpenInfraPlatform_UnitTests_Source}
	${OpenInfraPlatform_UnitTests_Infrastructure_LandInfraExportImport}
)

target_link_libraries(LandInfraExportImport 
	OpenInfraPlatform.Infrastructure
	# BlueFramework
	${BLUEFRAMEWORK_BLUECORE_LIBRARY}
	${BLUEFRAMEWORK_BLUEIMAGEPROCESSING_LIBRARY}
	${BLUEFRAMEWORK_BLUERASTERIZER_LIBRARY}
	${BLUEFRAMEWORK_BLUEENGINE_LIBRARY}
	${BLUEFRAMEWORK_BLUEAPPLICATION_LIBRARY}
	# Googletest
	${GTEST_BOTH_LIBRARIES}
)


add_test(
    NAME LandInfraExportImportTest
    COMMAND LandInfraExportImport
)

set_target_properties(LandInfraExportImport PROPERTIES FOLDER "OpenInfraPlatform/UnitTests/Infrastructure")
