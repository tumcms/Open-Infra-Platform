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

#find_package(GTest REQUIRED)

FetchContent_Declare(
	gtest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG release-1.10.0
)
 
FetchContent_GetProperties(gtest)
if(NOT gtest_POPULATED)
	FetchContent_Populate(gtest)
	add_subdirectory(${gtest_SOURCE_DIR} ${gtest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

file(GLOB OpenInfraPlatform_UnitTests_Source *.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Import/IFC2X3)

