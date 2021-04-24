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

project(OpenInfraPlatform.ScreenShotMaker)

set(CMAKE_AUTOMOC OFF)

file(GLOB OpenInfraPlatform_UnitTests_Utilities_ScreenShotMaker_Source src/*.*)

source_group(src FILES ${OpenInfraPlatform_UnitTests_Utilities_ScreenShotMaker_Source})

add_executable(OpenInfraPlatform.ScreenShotMaker ${OpenInfraPlatform_UnitTests_Utilities_ScreenShotMaker_Source})


target_include_directories(OpenInfraPlatform.ScreenShotMaker
	PUBLIC
		src
        ${tclap_SOURCE_DIR}/include
)

target_link_libraries(OpenInfraPlatform.ScreenShotMaker
    PRIVATE
        OpenInfraPlatform.GeometryModelRenderer
        BlueFramework.Engine
        Boost::filesystem
)

set_target_properties(OpenInfraPlatform.ScreenShotMaker PROPERTIES FOLDER "OpenInfraPlatform/UnitTests/Utilities")
