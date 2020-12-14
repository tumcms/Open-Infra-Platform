#
#    Copyright(c) 2018 Technical University of Munich
#    Chair of Computational Modeling and Simulation.
#
#    TUM Open Infra Platform is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License Version 3
#    as published by the Free Software Foundation.
#
#    TUM Open Infra Platform is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.If not, see <http://www.gnu.org/licenses/>.
#

project(OpenInfraPlatform.EarlyBinding CXX)

add_library(OpenInfraPlatform.ExpressLib INTERFACE)

file(GLOB OpenInfraPlatform_EarlyBinding_EXPRESS_Source		src/EXPRESS/*.*)	
file(GLOB OpenInfraPlatform_EarlyBinding_EXPRESS_Namespace	src/*.*)	

target_include_directories(OpenInfraPlatform.ExpressLib INTERFACE 
	${OpenInfraPlatform_EarlyBinding_EXPRESS_Source}
	${OpenInfraPlatform_EarlyBinding_EXPRESS_Namespace}
)
add_definitions(-DOIP_EARLYBINDING_API_EXPRESS_ASEXPORT)

include_directories(
    ${Boost_INCLUDE_DIR}
    ${tclap_SOURCE_DIR}/include
)

#show the lib in UI - no use otherwise (see https://stackoverflow.com/questions/39887352/how-to-create-a-cmake-header-only-library-that-depends-on-external-header-files)
add_custom_target(OpenInfraPlatform.ExpressLibrary SOURCES 
	${OpenInfraPlatform_EarlyBinding_EXPRESS_Source}
	${OpenInfraPlatform_EarlyBinding_EXPRESS_Namespace}
)
source_group(EXPRESS FILES ${OpenInfraPlatform_EarlyBinding_EXPRESS_Source})
source_group(defines FILES ${OpenInfraPlatform_EarlyBinding_EXPRESS_Namespace})
set_target_properties(OpenInfraPlatform.ExpressLibrary PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding")
add_dependencies(OpenInfraPlatform.ExpressLibrary OpenInfraPlatform.ExpressLib)

foreach(format ${IFC_FORMATS})
	message(STATUS "Format ${format} found.")
	if(EXISTS ${CMAKE_BINARY_DIR}/EarlyBinding/${format})
		add_subdirectory(${CMAKE_BINARY_DIR}/EarlyBinding/${format} ${CMAKE_BINARY_DIR}/EarlyBinding/${format})
        set_target_properties(OpenInfraPlatform.${format}.Zero PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding/${format}")
        set_target_properties(OpenInfraPlatform.${format}.Bot PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding/${format}")
        set_target_properties(OpenInfraPlatform.${format}.Mid PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding/${format}")
        set_target_properties(OpenInfraPlatform.${format}.Top PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding/${format}")
		
	elseif()
		message(WARNING "Files for format ${format} not found.")
	endif()
endforeach()

macro(add_unit_test_generated schema)
    if(EXISTS ${CMAKE_BINARY_DIR}/UnitTests/Generator/${schema}/Generated/${schema})
        add_subdirectory(${CMAKE_BINARY_DIR}/UnitTests/Generator/${schema}/Generated/${schema} ${CMAKE_BINARY_DIR}/UnitTests/Generator/${schema}/Generated/${schema})
        set_target_properties(OpenInfraPlatform.${schema}.Zero PROPERTIES FOLDER "OpenInfraPlatform/UnitTests/Generator/${schema}")
        set_target_properties(OpenInfraPlatform.${schema}.Bot PROPERTIES FOLDER "OpenInfraPlatform/UnitTests/Generator/${schema}")
        set_target_properties(OpenInfraPlatform.${schema}.Mid PROPERTIES FOLDER "OpenInfraPlatform/UnitTests/Generator/${schema}")
        set_target_properties(OpenInfraPlatform.${schema}.Top PROPERTIES FOLDER "OpenInfraPlatform/UnitTests/Generator/${schema}")
    endif()
endmacro()

add_unit_test_generated(schema_UT_family_1)
add_unit_test_generated(schema_UT_family_2)
add_unit_test_generated(schema_UT_family_3)

add_unit_test_generated(schema_UT_v1)
add_unit_test_generated(schema_UT_v2)
add_unit_test_generated(schema_UT_v3)

