project(OpenInfraPlatform.ExpressBinding)

set(CMAKE_DEBUG_POSTFIX "d")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	../Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	../Release)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG 	    ../Debug)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE 	    ../Release)


if (WIN32)
	set(BISON_EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR}/..//Tools/win_flex_bison-2.5.5/win_bison.exe)
	set(FLEX_EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR}/../Tools/win_flex_bison-2.5.5/win_flex.exe)
endif()

find_package(BISON)
find_package(FLEX)

bison_target(Parser ${CMAKE_CURRENT_SOURCE_DIR}/src/OpenInfraPlatform/ExpressBinding/Parser/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
flex_target(Scanner ${CMAKE_CURRENT_SOURCE_DIR}/src/OpenInfraPlatform/ExpressBinding/Parser/tokens.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
add_flex_bison_dependency(Scanner Parser)

include_directories(
	${Boost_INCLUDE_DIR} 
	${BLUEFRAMEWORK_INCLUDE_DIR}
	src
	src/OpenInfraPlatform/ExpressBinding
	${CMAKE_CURRENT_SOURCE_DIR}/../
	${CMAKE_CURRENT_BINARY_DIR}
)


file(GLOB OpenInfraPlatform_ExpressBinding_Source 					src/OpenInfraPlatform/ExpressBinding/*.*)
file(GLOB OpenInfraPlatform_ExpressBinding_Meta_Source 				src/OpenInfraPlatform/ExpressBinding/Meta/*.*)
file(GLOB OpenInfraPlatform_ExpressBinding_Parser_Source 			src/OpenInfraPlatform/ExpressBinding/Parser/*.*)

source_group(OpenInfraPlatform\\ExpressBinding\\					FILES ${OpenInfraPlatform_ExpressBinding_Source})
source_group(OpenInfraPlatform\\ExpressBinding\\Meta				FILES ${OpenInfraPlatform_ExpressBinding_Meta_Source})
source_group(OpenInfraPlatform\\ExpressBinding\\Parser				FILES ${OpenInfraPlatform_ExpressBinding_Parser_Source})

add_library(OpenInfraPlatform.ExpressBinding STATIC
	${OpenInfraPlatform_ExpressBinding_Source}
	${OpenInfraPlatform_ExpressBinding_Meta_Source}
	${OpenInfraPlatform_ExpressBinding_Parser_Source}
	${FLEX_Scanner_OUTPUTS} 
	${BISON_Parser_OUTPUTS}
)
