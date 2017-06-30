project(OpenInfraPlatform.ExpressBinding)

set(CMAKE_DEBUG_POSTFIX "d")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	../Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	../Release)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG 	    ../Debug)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE 	    ../Release)

include_directories(
	${Boost_INCLUDE_DIR} 
	${BLUEFRAMEWORK_INCLUDE_DIR}
	src
)

include_directories(src/OpenInfraPlatform/ExpressBinding)

file(GLOB OpenInfraPlatform_ExpressBinding_Source 					src/OpenInfraPlatform/ExpressBinding/*.*)

source_group(OpenInfraPlatform\\ExpressBinding\\					FILES ${OpenInfraPlatform_ExpressBinding_Source})

add_library(OpenInfraPlatform.ExpressBinding STATIC
	${OpenInfraPlatform_ExpressBinding_Source}
)
