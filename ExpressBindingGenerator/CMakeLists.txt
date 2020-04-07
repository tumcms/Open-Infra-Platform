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


find_file(BISON_EXECUTABLE win_bison.exe HINTS ${CMAKE_CURRENT_SOURCE_DIR}/Tools/win_flex_bison-2.5.5)
find_file(FLEX_EXECUTABLE win_flex.exe HINTS ${CMAKE_CURRENT_SOURCE_DIR}/Tools/win_flex_bison-2.5.5)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# FetchContent_Declare(
# 	winflexbison
# 	GIT_REPOSITORY https://github.com/lexxmark/winflexbison.git
# 	GIT_TAG v2.5.20
# )
 
# FetchContent_GetProperties(winflexbison)
# if(NOT winflexbison_POPULATED)
# 	FetchContent_Populate(winflexbison)
# 	add_subdirectory(${winflexbison_SOURCE_DIR} ${winflexbison_BINARY_DIR})
# endif()


#find_path(TCLAP_INCLUDE_DIR REQUIRED)
FetchContent_Declare(
	tclap
	GIT_REPOSITORY https://github.com/mirror/tclap.git
	GIT_TAG v1.2.2
)
  
FetchContent_GetProperties(tclap)
if(NOT tclap_POPULATED)
	FetchContent_Populate(tclap)
endif()

find_package(Python2 REQUIRED)
get_filename_component(Python2_DIRECTORY ${Python2_EXECUTABLE} DIRECTORY)

#find_file(Python_2to3_SCRIPT NAMES 2to3.py HINTS "${Python_DIRECTORY}\\Tools\\scripts" REQUIRED)

# Get root directory of Qt installation
string(FIND ${Qt5_DIR} "Qt" POS)
string(SUBSTRING ${Qt5_DIR} 0 ${POS} Qt5_ROOT)
string(SUBSTRING ${Qt5_DIR} ${POS} 2 Qt5_ROOT_SUFFIX)
string(APPEND Qt5_ROOT ${Qt5_ROOT_SUFFIX})
message(STATUS ${Qt5_ROOT})

# Set path to MinGW bin folder containing gcc executable
set(MinGW_DIR ${Qt5_ROOT}/Tools/mingw730_64/bin)

# Get Python and MinGW directories in native path format to add them to %PATH% variable
file(TO_NATIVE_PATH ${MinGW_DIR} MinGW_DIR)
file(TO_NATIVE_PATH ${Python2_DIRECTORY} Python2_DIRECTORY)

add_custom_target(Commands.UpdateBoostMPL
	COMMAND set PYTHON_PATH=${Python2_DIRECTORY}
	COMMAND set GCC_PATH=${MinGW_DIR}
	COMMAND set PATH=%GCC_PATH%\;%PYTHON_PATH%\;%PATH%;
	COMMAND echo %PATH%
	COMMAND ${Python2_EXECUTABLE} ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/fix_boost_mpl_preprocess.py ${Boost_INCLUDE_DIR}
	COMMAND ${Python2_EXECUTABLE} ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/boost_mpl_preprocess.py --sequence-type=both --num-elements=100 ${Boost_INCLUDE_DIR}
)
set_target_properties(Commands.UpdateBoostMPL PROPERTIES FOLDER "OpenInfraPlatform/ExpressBindingGenerator/Commands")

# Create list of possible IFC formats
#set(SUPPORTED_IFC_FORMATS IFC2X3 IFC4 IFC4X2_BIM4ROAD IFC4X1 IFC4X2_DRAFT_1 IFC4X2 IFC4X3_ALPHA)



# Macro to add IFC formats and the respective schemas.
macro(add_format format schema active)
	set(${format}_SCHEMA ${schema}.exp)
	set(EARLYBINDING_${format} ${format} ${schema})
	set(SUPPORTED_IFC_FORMATS ${SUPPORTED_IFC_FORMATS} EARLYBINDING_${format})
	option(EARLYBINDING_WITH_${format} "Build with support for ${format} and generate all required files.")
	
	#if(${active})
	#	set(IFC_FORMATS ${IFC_FORMATS} ${format})
	#	set(IFC_SCHEMAS ${IFC_SCHEMAS} ${schema})
	#	
	#	# Custom target that generates the early binding library files.
	#	add_custom_target(Commands.GenerateEarlyBinding.${format}
	#		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/EarlyBinding
	#		COMMAND ${CMAKE_COMMAND} -E remove_directory  ${CMAKE_BINARY_DIR}/EarlyBinding/${format}
	#
	#		COMMAND OpenInfraPlatform.ExpressBindingGenerator ${CMAKE_CURRENT_SOURCE_DIR}/schemas/${schema}.exp -o ${CMAKE_BINARY_DIR}/EarlyBinding
	#	)
	#
	#	add_dependencies(Commands.GenerateEarlyBinding.${format} OpenInfraPlatform.ExpressBindingGenerator)
	#	set_target_properties(Commands.GenerateEarlyBinding.${format} PROPERTIES FOLDER "OpenInfraPlatform/ExpressBindingGenerator/Commands")
	#endif()
endmacro()

add_format(IFC2X3 			IFC2X3_TC1 		ON)
add_format(IFC4 			IFC4_ADD1 		ON)
add_format(IFC4X2_BIM4ROAD 	IFC4x2_BIM4ROAD	OFF)
add_format(IFC4X1		 	IFC4x1_RC3		ON)
add_format(IFC4X2_DRAFT_1 	IFC4x2_DRAFT_1	OFF)
add_format(IFC4X2			IFC4x2			OFF)
add_format(IFC4X3_ALPHA	 	IFC4X3_ALPHA	ON)

# Add options to create early bindings for formats
foreach(standard IN LISTS SUPPORTED_IFC_FORMATS)
	list(GET ${standard} 0 format)
	list(GET ${standard} 1 schema)
	if(EARLYBINDING_WITH_${format})
		message(STATUS "Building with ${format}.")
		set(IFC_FORMATS ${IFC_FORMATS} ${format})
		set(IFC_SCHEMAS ${IFC_SCHEMAS} ${schema})
		
		# Custom target that generates the early binding library files.
		add_custom_target(Commands.GenerateEarlyBinding.${format}
			COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/EarlyBinding
			COMMAND ${CMAKE_COMMAND} -E remove_directory  ${CMAKE_BINARY_DIR}/EarlyBinding/${format}	
			COMMAND OpenInfraPlatform.ExpressBindingGenerator ${CMAKE_CURRENT_SOURCE_DIR}/schemas/${schema}.exp -o ${CMAKE_BINARY_DIR}/EarlyBinding
		)
	
		add_dependencies(Commands.GenerateEarlyBinding.${format} OpenInfraPlatform.ExpressBindingGenerator)
		set_target_properties(Commands.GenerateEarlyBinding.${format} PROPERTIES FOLDER "OpenInfraPlatform/ExpressBindingGenerator/Commands")
	endif()
endforeach()

# Push to parent scope to be able to determine which folders to add in the higher level CMakeLists.txt
set(IFC_FORMATS ${IFC_FORMATS} PARENT_SCOPE)

bison_target(Parser
	#${CMAKE_CURRENT_SOURCE_DIR}/ExpressBindingGenerator/Parser/parser.y
	${CMAKE_CURRENT_SOURCE_DIR}/src/Parser/parser.y
	${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
	COMPILE_FLAGS "-Wother -Wconflicts-sr -Wconflicts-rr"
	DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hpp
	VERBOSE REPORT_FILE ${CMAKE_CURRENT_BINARY_DIR}/bison_log.txt
)
	
flex_target(Scanner ${CMAKE_CURRENT_SOURCE_DIR}/src/Parser/tokens.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
#flex_target(Scanner ${CMAKE_CURRENT_SOURCE_DIR}/ExpressBindingGenerator/Parser/tokens.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
add_flex_bison_dependency(Scanner Parser)

include_directories(
	../ExpressBindingGenerator/src
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${Boost_INCLUDE_DIR}
	${tclap_SOURCE_DIR}/include
)

# Add files and set source groups.
file(GLOB ExpressBindingGenerator_Source	        				src/*.*)	
file(GLOB ExpressBindingGenerator_General_Source	        		src/General/*.*)		# necessary for finding correct namespace and main file.
file(GLOB ExpressBindingGenerator_Generator_Source					src/Generator/*.*)	
file(GLOB ExpressBindingGenerator_Meta_Source						src/Meta/*.*)	
file(GLOB ExpressBindingGenerator_Parser_Source						src/Parser/*.*)	

source_group(ExpressBindingGenerator								FILES ${ExpressBindingGenerator_Source})	
source_group(ExpressBindingGenerator\\General						FILES ${ExpressBindingGenerator_General_Source})
source_group(ExpressBindingGenerator\\Generator						FILES ${ExpressBindingGenerator_Generator_Source})
source_group(ExpressBindingGenerator\\Meta    						FILES ${ExpressBindingGenerator_Meta_Source})	
source_group(ExpressBindingGenerator\\Parser						FILES ${ExpressBindingGenerator_Parser_Source})	

add_executable(OpenInfraPlatform.ExpressBindingGenerator
	${ExpressBindingGenerator_Source}
	${ExpressBindingGenerator_General_Source}
	${ExpressBindingGenerator_Generator_Source}
	${ExpressBindingGenerator_Meta_Source}
	${ExpressBindingGenerator_Parser_Source}
	${FLEX_Scanner_OUTPUTS} 
	${BISON_Parser_OUTPUTS}
)


#-------------------------------------------------------------------------------------
# Installation
#-------------------------------------------------------------------------------------

# TODO: Fix installation for project.
