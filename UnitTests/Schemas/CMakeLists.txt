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

add_subdirectory(IFC4X1)

macro(CreateIfcFileUnitTestForSchema test_name schema)
    
    file(GLOB OpenInfraPlatform_UnitTests_Schema_${schema}_${test_name}	*.cpp)

    source_group(UnitTests\\Schema\\${schema}\\${test_name}   	FILES ${OpenInfraPlatform_UnitTests_Schema_${schema}_${test_name}})
    source_group(UnitTests                   	                FILES ${OpenInfraPlatform_UnitTests_Source})

    set(UnitTest_Executable_Name OpenInfraPlatform.UnitTests.Schema.${schema}.${test_name})

    add_executable(${UnitTest_Executable_Name}
        ${OpenInfraPlatform_UnitTests_Schema_${schema}_${test_name}}
    	${OpenInfraPlatform_UnitTests_Source}
    )

    target_include_directories(${UnitTest_Executable_Name}
        PUBLIC
            ${blue_framework_SOURCE_DIR}/include
    )

    target_link_libraries(${UnitTest_Executable_Name}
        PUBLIC
    	    OpenInfraPlatform.${schema}
    	    BlueFramework.Engine
    	    gtest	
    	    gtest_main
    )

    add_test(
        NAME ${UnitTest_Executable_Name}Test
        COMMAND ${UnitTest_Executable_Name}
    )

    set_target_properties(${UnitTest_Executable_Name} PROPERTIES FOLDER "UnitTests/Schema/${schema}")
    set(OpenInfraPlatform_UnitTests_Schema_${schema}_${test_name}_Data_Path ${CMAKE_SOURCE_DIR}/UnitTests/Schema/${schema}/${test_name}/Data)
    

    add_custom_command(TARGET ${UnitTest_Executable_Name} POST_BUILD
    	COMMENT "Copying resources from '${CMAKE_SOURCE_DIR}/UnitTests/Schema/${schema}/${test_name}/Data' to '${CMAKE_BINARY_DIR}/UnitTests/Schema/${schema}/'" VERBATIM
    	COMMAND	${CMAKE_COMMAND} -E make_directory OpenInfraPlatform_UnitTests_Schema_${schema}_${test_name}_Data_Path
    	COMMAND	${CMAKE_COMMAND} -E copy_directory OpenInfraPlatform_UnitTests_Schema_${schema}_${test_name}_Data_Path ${CMAKE_BINARY_DIR}/UnitTests/Schema/${schema}/${test_name}/Data
    )

endmacro()