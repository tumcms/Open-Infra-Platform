#
#    Copyright (c) 2020 Technical University of Munich
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

enable_testing()
include(GoogleTest)

function(CreateIfcFileUnitTestForSchema test_name schema)

    file(GLOB OpenInfraPlatform_UnitTests_Schema_${schema}_${test_name}	src/*.cpp)

    source_group(UnitTests\\${test_name}   	FILES ${OpenInfraPlatform_UnitTests_Schema_${schema}_${test_name}})
    source_group(UnitTests                  FILES ${OpenInfraPlatform_UnitTests_Source})

    set(UnitTest_Executable_Name ${test_name})

    add_executable(${UnitTest_Executable_Name}
        ${OpenInfraPlatform_UnitTests_Schema_${schema}_${test_name}}
        ${OpenInfraPlatform_UnitTests_Source}
    )

    get_directory_property(PARENT_DIR DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PARENT_DIRECTORY)

    target_include_directories(${UnitTest_Executable_Name}
        PUBLIC
            ${blue_framework_SOURCE_DIR}/include
        PRIVATE
            ${PARENT_DIR}
    )

    target_link_libraries(${UnitTest_Executable_Name}
        PUBLIC
            OpenInfraPlatform.${schema}
            BlueFramework.Engine
            gmock
            gtest
            gtest_main
			Boost::filesystem
    )

    gtest_discover_tests(${UnitTest_Executable_Name})

    set_target_properties(${UnitTest_Executable_Name} PROPERTIES FOLDER "OpenInfraPlatform/UnitTests/Schemas/${schema}")
    set(UnitTest_Data_Rel_Path UnitTests/Schemas/${schema}/${test_name}/Data)

    add_custom_command(TARGET ${UnitTest_Executable_Name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying resources from '${CMAKE_SOURCE_DIR}/${UnitTest_Data_Rel_Path}' to '${CMAKE_BINARY_DIR}/$<CONFIG>/${UnitTest_Data_Rel_Path}'"
        COMMAND	${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/${UnitTest_Data_Rel_Path}
        COMMAND	${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/${UnitTest_Data_Rel_Path} ${CMAKE_BINARY_DIR}/$<CONFIG>/${UnitTest_Data_Rel_Path}
    )

endfunction()

function(CreateIfcFileVisualUnitTestForSchema test_name schema)
  CreateIfcFileUnitTestForSchema(${test_name} ${schema})
  target_link_libraries(${test_name} PUBLIC OpenInfraPlatform.Rendering)
endfunction(CreateIfcFileVisualUnitTestForSchema)


function(CreateGeneratorUnitTest schema)

    set(UnitTest_Executable_Name UnitTest.${schema})
    set(UnitTest_Generator_Name Generate.${schema})
    set(UnitTest_Rel_Path UnitTests/Generator/${schema})
    set(UnitTest_Binary_Path ${UnitTest_Rel_Path}/Generated)
    set(UnitTest_Data_Rel_Path ${UnitTest_Rel_Path}/Data)

    # Custom target that generates the early binding library files.
    add_custom_target(${UnitTest_Generator_Name}
        COMMAND ${CMAKE_COMMAND} -E make_directory  ${CMAKE_BINARY_DIR}/${UnitTest_Binary_Path}
        COMMAND ${CMAKE_COMMAND} -E remove_directory  ${CMAKE_BINARY_DIR}/${UnitTest_Binary_Path}/${schema}
        COMMAND OpenInfraPlatform.ExpressBindingGenerator ${CMAKE_SOURCE_DIR}/${UnitTest_Data_Rel_Path}/${schema}.exp -o ${CMAKE_BINARY_DIR}/${UnitTest_Binary_Path}
    )
    set_target_properties(${UnitTest_Generator_Name} PROPERTIES FOLDER "OpenInfraPlatform/UnitTests/Generator/${schema}")
    add_dependencies(${UnitTest_Generator_Name} OpenInfraPlatform.ExpressBindingGenerator)

    # Executable for gtest
    file(GLOB OpenInfraPlatform_UnitTests_Generator_${schema} src/*.cpp)

    source_group(UnitTests\\${schema}    FILES ${OpenInfraPlatform_UnitTests_Generator_${schema}})
    source_group(UnitTests               FILES ${OpenInfraPlatform_UnitTests_Source})

    add_executable(${UnitTest_Executable_Name}
        ${OpenInfraPlatform_UnitTests_Generator_${schema}}
        ${OpenInfraPlatform_UnitTests_Source}
    )

    get_directory_property(PARENT_DIR DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PARENT_DIRECTORY)

    target_include_directories(${UnitTest_Executable_Name}
        PUBLIC
            ${blue_framework_SOURCE_DIR}/include
        PRIVATE
            ${PARENT_DIR}
    )

    add_dependencies(${UnitTest_Executable_Name} ${UnitTest_Generator_Name})
    target_link_libraries(${UnitTest_Executable_Name}
        PUBLIC
            gmock
            gtest
            gtest_main
    )

    gtest_discover_tests(${UnitTest_Executable_Name})

    set_target_properties(${UnitTest_Executable_Name} PROPERTIES FOLDER "OpenInfraPlatform/UnitTests/Generator/${schema}")

    add_custom_command(TARGET ${UnitTest_Executable_Name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying resources from '${CMAKE_SOURCE_DIR}/${UnitTest_Data_Rel_Path}' to '${CMAKE_BINARY_DIR}/$<CONFIG>/${UnitTest_Data_Rel_Path}'"
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/${UnitTest_Data_Rel_Path}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/${UnitTest_Data_Rel_Path} ${CMAKE_BINARY_DIR}/$<CONFIG>/${UnitTest_Data_Rel_Path}
    )

    add_custom_command(TARGET ${UnitTest_Executable_Name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying generated from '${CMAKE_BINARY_DIR}/${UnitTest_Binary_Path}/${schema}' to '${CMAKE_BINARY_DIR}/$<CONFIG>/${UnitTest_Binary_Path}'"
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/${UnitTest_Binary_Path}/${schema}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/${UnitTest_Binary_Path}/${schema} ${CMAKE_BINARY_DIR}/$<CONFIG>/${UnitTest_Binary_Path}
    )

endfunction(CreateGeneratorUnitTest)

# see https://stackoverflow.com/questions/7787823/cmake-how-to-get-the-name-of-all-subdirectories-of-a-directory
# get all subdirectories of a directory
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child} AND EXISTS ${curdir}/${child}/CMakeLists.txt)
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()
