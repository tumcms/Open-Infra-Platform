#/*
#   This file is part of TUM Open Infra Platform Early Binding EXPRESS 
#	Generator, a simple early binding generator for EXPRESS.
#	Copyright (c) 2016-2017 Technical University of Munich
#	Chair of Computational Modeling and Simulation.
#
#	TUM Open Infra Platform Early Binding EXPRESS Generator is free 
#	software; you can redistribute it and/or modify it under the terms 
#	of the GNU General Public License Version 3 as published by the Free
#	Software Foundation.
#
#   TUM Open Infra Platform Early Binding EXPRESS Generator is 
#	distributed in the hope that it will be useful, but WITHOUT ANY 
#	WARRANTY; without even the implied warranty of MERCHANTABILITY or 
#	FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
#	for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program. If not, see <http://www.gnu.org/licenses/>.
#*/

cmake_minimum_required(VERSION 3.13.0)

project(OpenInfraPlatform.ExpressGenerator)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 14)

if (WIN32)
	# Standard:          /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR
	set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W4 /Zi /EHsc /GR /MP /openmp /bigobj")
endif (WIN32)



#------------------------------------------------------------------------------
# Some checks to ensure that the prerequisites are ok
#------------------------------------------------------------------------------

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8 )
	message("Please switch to x64 build.")
	return()
endif()

#------------------------------------------------------------------------------

if (WIN32)
	set(BISON_EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR}/Tools/win_flex_bison-2.5.5/win_bison.exe)
	set(FLEX_EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR}/Tools/win_flex_bison-2.5.5/win_flex.exe)
endif()

find_package(Boost 1.65.1 REQUIRED)
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
find_package(gtest REQUIRED)
find_package(PythonInterp REQUIRED)

add_custom_target(UpdateBoostMPL
	COMMAND "${PYTHON_EXECUTABLE}" ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/fix_boost_mpl_preprocess.py ${Boost_INCLUDE_DIR}
	COMMAND "${PYTHON_EXECUTABLE}" ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/boost_mpl_preprocess.py --sequence-type=both --num-elements=100 ${Boost_INCLUDE_DIR}
)

macro(add_format format schema)
	set(IFC_FORMATS ${IFC_FORMATS} ${format})
	set(IFC_SCHEMAS ${IFC_SCHEMAS} ${schema})
	set(${format}_SCHEMA ${schema}.exp)
endmacro()

add_format(IFC2X3 IFC2X3_TC1)
add_format(IFC4 IFC4_ADD1)
add_format(IFC4X2_BIM4ROAD IFC4x2_BIM4ROAD)
add_format(IFC4X1 IFC4x1_RC3)
add_format(IFC4X2_DRAFT_1 IFC4x2_DRAFT_1)

set(IFC_FORMATS ${IFC_FORMATS} PARENT_SCOPE)

bison_target(Parser
	${CMAKE_CURRENT_SOURCE_DIR}/ExpressBinding/src/OpenInfraPlatform/ExpressBinding/Parser/parser.y
	${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
	COMPILE_FLAGS "-Wother -Wconflicts-sr -Wconflicts-rr"
	DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hpp
	VERBOSE REPORT_FILE ${CMAKE_CURRENT_BINARY_DIR}/bison_log.txt
)
	
flex_target(Scanner ${CMAKE_CURRENT_SOURCE_DIR}/ExpressBinding/src/OpenInfraPlatform/ExpressBinding/Parser/tokens.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
add_flex_bison_dependency(Scanner Parser)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	ExpressBinding/src
	${Boost_INCLUDE_DIR}
)

file(GLOB OpenInfraPlatform_ExpressBinding_EXPRESS_Source	ExpressBinding/src/OpenInfraPlatform/ExpressBinding/EXPRESS/*.*)	
file(GLOB OpenInfraPlatform_ExpressBinding_Generator_Source	ExpressBinding/src/OpenInfraPlatform/ExpressBinding/Generator/*.*)	
file(GLOB OpenInfraPlatform_ExpressBinding_Meta_Source		ExpressBinding/src/OpenInfraPlatform/ExpressBinding/Meta/*.*)	
file(GLOB OpenInfraPlatform_ExpressBinding_Parser_Source	ExpressBinding/src/OpenInfraPlatform/ExpressBinding/Parser/*.*)	
file(GLOB OpenInfraPlatform_ExpressBinding_Source	        ExpressBinding/src/OpenInfraPlatform/ExpressBinding/*.*)	


source_group(OpenInfraPlatform\\ExpressBinding\\EXPRESS	FILES ${OpenInfraPlatform_ExpressBinding_EXPRESS_Source})
source_group(OpenInfraPlatform\\ExpressBinding\\Generator	FILES ${OpenInfraPlatform_ExpressBinding_Generator_Source})
source_group(OpenInfraPlatform\\ExpressBinding\\Meta    	FILES ${OpenInfraPlatform_ExpressBinding_Meta_Source})	
source_group(OpenInfraPlatform\\ExpressBinding\\Parser		FILES ${OpenInfraPlatform_ExpressBinding_Parser_Source})	
source_group(OpenInfraPlatform\\ExpressBinding				FILES ${OpenInfraPlatform_ExpressBinding_Source})	

add_executable(OpenInfraPlatform.ExpressGenerator
	${OpenInfraPlatform_ExpressBinding_EXPRESS_Source}
	${OpenInfraPlatform_ExpressBinding_Generator_Source}
	${OpenInfraPlatform_ExpressBinding_Meta_Source}
	${OpenInfraPlatform_ExpressBinding_Parser_Source}
	${OpenInfraPlatform_ExpressBinding_Source}
	${FLEX_Scanner_OUTPUTS} 
	${BISON_Parser_OUTPUTS}
)

set_target_properties(OpenInfraPlatform.ExpressGenerator PROPERTIES FOLDER "OpenInfraPlatform")

add_custom_target(GenerateEarlyBinding
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/EarlyBinding
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt.in ${CMAKE_BINARY_DIR}/EarlyBinding/
	COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_BINARY_DIR}/EarlyBinding/CMakeLists.txt.in ${CMAKE_BINARY_DIR}/EarlyBinding/CMakeLists.txt
	COMMAND OpenInfraPlatform.ExpressGenerator ${PROJECT_SOURCE_DIR}/schemas/${IFC2X3_SCHEMA} -o ${CMAKE_BINARY_DIR}/EarlyBinding
	COMMAND OpenInfraPlatform.ExpressGenerator ${PROJECT_SOURCE_DIR}/schemas/${IFC4_SCHEMA} -o ${CMAKE_BINARY_DIR}/EarlyBinding
	COMMAND OpenInfraPlatform.ExpressGenerator ${PROJECT_SOURCE_DIR}/schemas/${IFC4X1_SCHEMA} -o ${CMAKE_BINARY_DIR}/EarlyBinding
	COMMAND OpenInfraPlatform.ExpressGenerator ${PROJECT_SOURCE_DIR}/schemas/${IFC4X2_BIM4ROAD_SCHEMA} -o ${CMAKE_BINARY_DIR}/EarlyBinding
	COMMAND OpenInfraPlatform.ExpressGenerator ${PROJECT_SOURCE_DIR}/schemas/${IFC4X2_DRAFT_1_SCHEMA} -o ${CMAKE_BINARY_DIR}/EarlyBinding
	
)

add_dependencies(GenerateEarlyBinding OpenInfraPlatform.ExpressGenerator)

set_target_properties(GenerateEarlyBinding PROPERTIES FOLDER "OpenInfraPlatform\\ExpressGenerator")


#-------------------------------------------------------------------------------------
# Installation
#-------------------------------------------------------------------------------------
install(TARGETS OpenInfraPlatform.ExpressGenerator RUNTIME DESTINATION bin COMPONENT oip_runtime)

file(WRITE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake "set(${PROJECT_NAME}_FOUND 1) \nset(oipExpress_EXE \${oipExpress_DIR}/bin/ExpressBinding.exe)")
file(WRITE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake "set(PACKAGE_VERSION \"${CPACK_PACKAGE_VERSION}\") \nset(PACKAGE_VERSION_EXACT True) \nset(PACKAGE_VERSION_COMPATIBLE True) \nset(PACKAGE_VERSION_UNSUITABLE False)")

install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake DESTINATION / COMPONENT cmake)
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake DESTINATION / COMPONENT cmake)