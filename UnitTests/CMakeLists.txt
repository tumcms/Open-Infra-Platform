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

# Google Test
set(gtest_force_shared_crt ON CACHE INTERNAL "")

include_directories(
	${GTEST_INCLUDE_DIR}
)

file(GLOB OpenInfraPlatform_UnitTests_Source src/OpenInfraPlatform/UnitTests/*.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/OpenInfraPlatform/UnitTests/Infrastructure/HorizontalAlignmentElement2DArbitraryCurve)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/OpenInfraPlatform/UnitTests/Infrastructure/HorizontalAlignmentElement2DArc)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/OpenInfraPlatform/UnitTests/Infrastructure/HorizontalAlignmentElement2DClothoid)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/OpenInfraPlatform/UnitTests/Infrastructure/HorizontalAlignmentElement2DLine)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/OpenInfraPlatform/UnitTests/Infrastructure/OkstraExportImport)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/OpenInfraPlatform/UnitTests/Infrastructure/LandInfraExportImport)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/OpenInfraPlatform/UnitTests/Infrastructure/IfcOWLExport)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/OpenInfraPlatform/UnitTests/Infrastructure/TrafficSign)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/OpenInfraPlatform/UnitTests/ExpressBinding/SkeletonPrototype)

