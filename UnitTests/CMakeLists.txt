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
	dep_gtest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG release-1.10.0
)
 
FetchContent_GetProperties(dep_gtest)
if(NOT dep_gtest_POPULATED)
	FetchContent_Populate(dep_gtest)
	add_subdirectory(${dep_gtest_SOURCE_DIR} ${dep_gtest_BINARY_DIR} EXCLUDE_FROM_ALL)

	set_target_properties(gtest PROPERTIES FOLDER "ThirdParty/googletest")
	set_target_properties(gtest_main PROPERTIES FOLDER "ThirdParty/googletest")
	set_target_properties(gmock PROPERTIES FOLDER "ThirdParty/googletest")
endif()


file(GLOB OpenInfraPlatform_UnitTests_Source *.cpp)

add_subdirectory(Generator)
add_subdirectory(Schemas)
add_subdirectory(Utilities)


