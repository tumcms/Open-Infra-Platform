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

include(CreateUnitTests)

    set(UnitTest_Executable_Name UnitTest.Graph)

    # Executable for gtest
    file(GLOB OpenInfraPlatform_UnitTests_Graph src/*.cpp)

    source_group(UnitTests\\graph    FILES ${OpenInfraPlatform_UnitTests_Graph})
    source_group(UnitTests           FILES ${OpenInfraPlatform_UnitTests_Source})

    add_executable(${UnitTest_Executable_Name}
        ${OpenInfraPlatform_UnitTests_Graph}
        ${OpenInfraPlatform_UnitTests_Source}
    )

    add_dependencies(${UnitTest_Executable_Name} OpenInfraPlatform.ExpressBindingGenerator)

    get_directory_property(PARENT_DIR DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PARENT_DIRECTORY)

    target_include_directories(${UnitTest_Executable_Name}
        PUBLIC
            ${blue_framework_SOURCE_DIR}/include
            ${CMAKE_CURRENT_SOURCE_DIR}/ExpressBindingGenerator/src/
        PRIVATE
            ${PARENT_DIR}
    )

    target_link_libraries(${UnitTest_Executable_Name}
        PUBLIC
            gmock
            gtest
            gtest_main
    )

    gtest_discover_tests(${UnitTest_Executable_Name})

    set_target_properties(${UnitTest_Executable_Name} PROPERTIES FOLDER "OpenInfraPlatform/UnitTests/Generator/Graph")
