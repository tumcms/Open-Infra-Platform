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

project(OpenInfraPlatform.ExpressBindingGenerator)

if(NOT Boost_FOUND)
	find_package(Boost 1.65.1 REQUIRED)
endif()
if(NOT gtest_FOUND)
	find_package(gtest REQUIRED)
endif()

find_file(BISON_EXECUTABLE win_bison.exe HINTS ${CMAKE_CURRENT_SOURCE_DIR}/Tools/win_flex_bison-2.5.5)
find_file(FLEX_EXECUTABLE win_flex.exe HINTS ${CMAKE_CURRENT_SOURCE_DIR}/Tools/win_flex_bison-2.5.5)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
find_package(Python COMPONENTS Interpreter Development REQUIRED)
if(Python_FOUND)
	message(STATUS "Found Python ${Python_VERSION}")
else()
	message(ERROR "Python not found.")
endif()

get_filename_component(Python_DIRECTORY ${Python_EXECUTABLE} DIRECTORY)

find_file(Python_2to3_SCRIPT NAMES 2to3.py HINTS "${Python_DIRECTORY}\\Tools\\scripts" REQUIRED)

message(STATUS ${Qt5_DIR})
string(FIND ${Qt5_DIR} "Qt" POS)
string(SUBSTRING ${Qt5_DIR} 0 ${POS} Qt5_ROOT)
string(SUBSTRING ${Qt5_DIR} ${POS} 2 Qt5_ROOT_SUFFIX)
string(APPEND Qt5_ROOT ${Qt5_ROOT_SUFFIX})
message(STATUS ${Qt5_ROOT})

set(MinGW_DIR ${Qt5_ROOT}/Tools/mingw730_64/bin)
file(TO_NATIVE_PATH ${MinGW_DIR} MinGW_DIR)
# Target which invokes a script inside boost to provide a MPL library build allowing up to 100 entries.
#add_custom_target(Commands.UpdateBoostMPL
#	COMMAND "${PYTHON_EXECUTABLE}" ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/fix_boost_mpl_preprocess.py ${Boost_INCLUDE_DIR}
#	COMMAND "${PYTHON_EXECUTABLE}" ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/boost_mpl_preprocess.py --sequence-type=both --num-elements=100 ${Boost_INCLUDE_DIR}
#)

#set(ENV{PATH} $ENV{PATH};${PYTHON_EXECUTABLE})

file(TO_NATIVE_PATH ${Python_EXECUTABLE} Python_FILEPATH)
file(TO_NATIVE_PATH ${Python_DIRECTORY} Python_DIRECTORY)


set(CUSTOM_PATH $ENV{PATH})
list(APPEND CUSTOM_PATH ${PYTHON_FILEPATH})
list(LENGTH CUSTOM_PATH CUSTOM_PATH_LENGTH)
list(JOIN CUSTOM_PATH ";" CUSTOM_PATH_JOINED)

add_custom_target(Commands.Print COMMAND set PYTHON_PATH=${Python_FILEPATH} COMMAND set PATH=%PATH%%PYTHON_PATH% COMMAND echo %PATH%) 
set_target_properties(Commands.Print PROPERTIES FOLDER "OpenInfraPlatform/ExpressBindingGenerator/Commands")

file(TO_NATIVE_PATH ${CMAKE_CXX_COMPILER} COMPILER)

file(READ ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/preprocess.cmd PREPROCESS_CMD)

string(REPLACE "gcc" "cl" PREPROCESS_CMD ${PREPROCESS_CMD})
file(WRITE ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/preprocess_cl.cmd ${PREPROCESS_CMD})

if(${Python_VERSION_MAJOR} EQUAL 3)
	add_custom_target(Commands.UpdateBoostMPL
		COMMAND set PYTHON_PATH=${Python_DIRECTORY}
		COMMAND set GCC_PATH=${MinGW_DIR}
		COMMAND set PATH=%PATH%%PYTHON_PATH%
		COMMAND set PATH=%PATH%\;
		COMMAND set PATH=%PATH%%GCC_PATH%
		COMMAND echo %PATH%
		COMMAND ${Python_EXECUTABLE} ${Python_2to3_SCRIPT} -w "${Boost_INCLUDE_DIR}\\libs\\mpl\\preprocessed\\fix_boost_mpl_preprocess.py"
		COMMAND ${Python_EXECUTABLE} ${Python_2to3_SCRIPT} -w "${Boost_INCLUDE_DIR}\\libs\\mpl\\preprocessed\\boost_mpl_preprocess.py"
		COMMAND ${Python_EXECUTABLE} ${Python_2to3_SCRIPT} -w "${Boost_INCLUDE_DIR}\\libs\\mpl\\preprocessed\\preprocess.py"
		COMMAND ${Python_EXECUTABLE} ${Python_2to3_SCRIPT} -w "${Boost_INCLUDE_DIR}\\libs\\mpl\\preprocessed\\pp.py"
	#COMMAND ${CMAKE_COMMAND} -E rename ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/preprocess.cmd ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/preprocess_gcc.cmd
		#COMMAND ${CMAKE_COMMAND} -E rename ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/preprocess_cl.cmd ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/preprocess.cmd
		COMMAND ${Python_EXECUTABLE} ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/fix_boost_mpl_preprocess.py ${Boost_INCLUDE_DIR}
		COMMAND ${Python_EXECUTABLE} ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/boost_mpl_preprocess.py --sequence-type=both --num-elements=100 ${Boost_INCLUDE_DIR}
		#COMMAND ${CMAKE_COMMAND} -E rename ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/preprocess.cmd ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/preprocess_cl.cmd
		#COMMAND ${CMAKE_COMMAND} -E rename ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/preprocess_gcc.cmd ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/preprocess.cmd
	)
	
	set_target_properties(Commands.UpdateBoostMPL PROPERTIES FOLDER "OpenInfraPlatform/ExpressBindingGenerator/Commands")
endif()


# Macro to add IFC formats and the respective schemas.
macro(add_format format schema active)
	if(${active})
		set(IFC_FORMATS ${IFC_FORMATS} ${format})
		set(IFC_SCHEMAS ${IFC_SCHEMAS} ${schema})
	endif()
	set(${format}_SCHEMA ${schema}.exp)
endmacro()

add_format(IFC2X3 			IFC2X3_TC1 		ON)
add_format(IFC4 			IFC4_ADD1 		OFF)
add_format(IFC4X2_BIM4ROAD 	IFC4x2_BIM4ROAD	OFF)
add_format(IFC4X1		 	IFC4x1_RC3		OFF)
add_format(IFC4X2_DRAFT_1 	IFC4x2_DRAFT_1	OFF)

# Push to parent scope to be able to determine which folders to add in the higher level CMakeLists.txt
set(IFC_FORMATS ${IFC_FORMATS} PARENT_SCOPE)

bison_target(Parser
	${CMAKE_CURRENT_SOURCE_DIR}/src/OpenInfraPlatform/ExpressBindingGenerator/Parser/parser.y
	${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
	COMPILE_FLAGS "-Wother -Wconflicts-sr -Wconflicts-rr"
	DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hpp
	VERBOSE REPORT_FILE ${CMAKE_CURRENT_BINARY_DIR}/bison_log.txt
)
	
flex_target(Scanner ${CMAKE_CURRENT_SOURCE_DIR}/src/OpenInfraPlatform/ExpressBindingGenerator/Parser/tokens.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
add_flex_bison_dependency(Scanner Parser)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${Boost_INCLUDE_DIR}
	${TCLAP_INCLUDE_DIR}
)

file(GLOB OpenInfraPlatform_ExpressBindingGenerator_Generator_Source	src/OpenInfraPlatform/ExpressBindingGenerator/Generator/*.*)	
file(GLOB OpenInfraPlatform_ExpressBindingGenerator_Meta_Source			src/OpenInfraPlatform/ExpressBindingGenerator/Meta/*.*)	
file(GLOB OpenInfraPlatform_ExpressBindingGenerator_Parser_Source		src/OpenInfraPlatform/ExpressBindingGenerator/Parser/*.*)	
file(GLOB OpenInfraPlatform_ExpressBindingGenerator_Source	        	src/OpenInfraPlatform/ExpressBindingGenerator/*.*)	


source_group(OpenInfraPlatform\\ExpressBindingGenerator\\Generator	FILES ${OpenInfraPlatform_ExpressBindingGenerator_Generator_Source})
source_group(OpenInfraPlatform\\ExpressBindingGenerator\\Meta    	FILES ${OpenInfraPlatform_ExpressBindingGenerator_Meta_Source})	
source_group(OpenInfraPlatform\\ExpressBindingGenerator\\Parser		FILES ${OpenInfraPlatform_ExpressBindingGenerator_Parser_Source})	
source_group(OpenInfraPlatform\\ExpressBindingGenerator				FILES ${OpenInfraPlatform_ExpressBindingGenerator_Source})	

add_executable(OpenInfraPlatform.ExpressBindingGenerator
	${OpenInfraPlatform_ExpressBindingGenerator_Generator_Source}
	${OpenInfraPlatform_ExpressBindingGenerator_Meta_Source}
	${OpenInfraPlatform_ExpressBindingGenerator_Parser_Source}
	${OpenInfraPlatform_ExpressBindingGenerator_Source}
	${FLEX_Scanner_OUTPUTS} 
	${BISON_Parser_OUTPUTS}
)


# Custom target that generates the early binding library files.
add_custom_target(Commands.GenerateEarlyBinding
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/EarlyBinding	
	COMMAND OpenInfraPlatform.ExpressBindingGenerator ${CMAKE_CURRENT_SOURCE_DIR}/schemas/${IFC2X3_SCHEMA} -o ${CMAKE_BINARY_DIR}/EarlyBinding
)

add_dependencies(Commands.GenerateEarlyBinding OpenInfraPlatform.ExpressBindingGenerator)

set_target_properties(Commands.GenerateEarlyBinding PROPERTIES FOLDER "OpenInfraPlatform/ExpressBindingGenerator/Commands")


#-------------------------------------------------------------------------------------
# Installation
#-------------------------------------------------------------------------------------

# TODO: Fix installation for project.