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

project(GeometryModelRenderer)

set(CMAKE_AUTOMOC OFF)

file(GLOB OpenInfraPlatform_UnitTests_Utilities_GeometryModelRenderer_Source src/*.*)

source_group(src FILES ${OpenInfraPlatform_UnitTests_Utilities_GeometryModelRenderer_Source})

add_library(GeometryModelRenderer STATIC ${OpenInfraPlatform_UnitTests_Utilities_GeometryModelRenderer_Source})


target_include_directories(GeometryModelRenderer
	PUBLIC
		src
)

target_link_libraries(GeometryModelRenderer
    PRIVATE
        OpenInfraPlatform.Rendering
        BlueFramework.Engine
        gmock
        gtest
        gtest_main
        Boost::filesystem
)

set_target_properties(GeometryModelRenderer PROPERTIES FOLDER "OpenInfraPlatform/UnitTests/Utilities")
