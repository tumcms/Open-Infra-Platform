# 	ConfigureDoxygen
#
# 	This is a configuration for the generation of doxygen documentation for the Open Infra Platform project. 
# 	ConfigureDoxygen is included in the top-level CMakeLists.txt of the project. 
#  	Changes to documentation settings should be made here. 
#  

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Doxymentation)

find_file(DOXYGEN_EXECUTABLE NAMES doxygen.exe HINTS
"C:/thirdparty/doxygen"
)

find_file(DOXYGEN_DOT_EXECUTABLE NAMES dot.exe HINTS
"C:/thirdparty/graphviz_dot/release/bin"
)

find_package(Doxygen
	REQUIRED dot
)


if(DOXYGEN_FOUND)
message("Use of DOXYGEN for developers: DOXYGEN_GENERATE_DOCUMENTATION enables building the documentation for the Open Infra Platform. \n"
"Selecting DOXYGEN_GENERATE_DOCUMENTATION and DOXYGEN_AUTO_OPEN_DOCUMENTATION recommended. \n"
"Refer to DoxygenHelp.md for the selection of the DOXYGEN_OPTIONALs and on how to use DOXYGEN within project.")

# Doxygen build options. 
Option(DOXYGEN_OPTIONAL_INCLUDE_COMMENTED_ONLY ON)
Option(DOXYGEN_OPTIONAL_INCLUDE_INTERNAL ON)
Option(DOXYGEN_OPTIONAL_INCLUDE_EARLYBINDING ON)
Option(DOXYGEN_OPTIONAL_AUTO_OPEN_DOCUMENTATION ON)

# CONFIGURATION. Check http://www.doxygen.nl/manual/config.html for all available options and their default values. 

# Configuration file generation using CMake. 
set(DOXYFILE_CMAKE ${CMAKE_CURRENT_BINARY_DIR}/CMakeDoxyfile.in)
set(DOXYFILE ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

# Build related configuration options. 
set(DOXYGEN_PROJECT_NAME OpenInfraPlatform)
set(DOXYGEN_PROJECT_BRIEF "Open source software for viewing and converting alignment data.")
set(DOXYGEN_PROJECT_LOGO ${CMAKE_CURRENT_SOURCE_DIR}/Documentation/Beta1_5_Windows8_1.png)
set(DOXYGEN_CREATE_SUBDIRS YES)
set(DOXYGEN_HAVE_DOT YES) # GraphViz Package for diagrams

# Documentation settings.
if(DOXYGEN_OPTIONAL_INCLUDE_COMMENTED_ONLY)
set(DOXYGEN_EXTRACT_ALL NO) # Set to yes if you want to extract all existing documentation  from project. Do this for now, once starting proper documentation change to NO. 
else()
set(DOXYGEN_EXTRACT_ALL YES)
endif(DOXYGEN_OPTIONAL_INCLUDE_COMMENTED_ONLY)

set(DOXYGEN_RECURSIVE YES) #Search subdirectories for input files as well.

if(DOXYGEN_OPTIONAL_INCLUDE_INTERNAL)
set(DOXYGEN_INTERNAL_DOCS YES) # Comments intended for developers and not for users (*! \internal *)
else()
set(DOXYGEN_INTERNAL_DOCS NO)
endif(DOXYGEN_OPTIONAL_INCLUDE_INTERNAL)

set(DOXYGEN_CLASS_DIAGRAMS YES)

# Output (HTML/Latex/...) configuration options.
set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_LATEX NO)
set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Doxymentation)
set(DOXYGEN_SEARCHENGINE YES)
set(DOXYGEN_SOURCE_BROWSER YES)
set(DOXYGEN_SUBGROUPING YES)
set(DOXYGEN_EXCLUDE_PATTERNS */CurrentlyExcluded/* */cmake/* */deploy/* */Documentation/* */external/* */testdata/* */Tools/* */UserInterface/QtPropertyBrowser/*)

configure_file(${DOXYFILE_CMAKE} ${DOXYFILE} @ONLY) 

# add source code to doxygen input
set(DOXYGEN_INPUT ${CMAKE_CURRENT_SOURCE_DIR})

# add IFC generated files to doxygen input directory
if(DOXYGEN_OPTIONAL_INCLUDE_EARLYBINDING)
foreach(format ${IFC_FORMATS})	
	if(EXISTS ${CMAKE_BINARY_DIR}/EarlyBinding/${format})
		set(DOXYGEN_INPUT ${DOXYGEN_INPUT} "${CMAKE_BINARY_DIR}/EarlyBinding/${format}/src")
	endif()
endforeach()
endif(DOXYGEN_OPTIONAL_INCLUDE_EARLYBINDING)

# Create target for the documentation.
doxygen_add_docs(OpenInfraPlatform.GenerateDocumentation ALL
${DOXYGEN_INPUT} 	# Source code that is (to be) documented located here
WORKING DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}	# Current root. Change if relative base point should be different.
#USE_STAMP_FILE
COMMENT "Generating doxymentation for TUM Open Infra Platform project.")

# Automatically open index page of the documentation after building. 
if(DOXYGEN_OPTIONAL_AUTO_OPEN_DOCUMENTATION)
add_custom_command(TARGET OpenInfraPlatform.GenerateDocumentation POST_BUILD
	COMMAND "${DOXYGEN_OUTPUT_DIRECTORY}/html/index.html"
)
endif(DOXYGEN_OPTIONAL_AUTO_OPEN_DOCUMENTATION)

else()
message("Doxygen not found. Please install doxygen using ${CMAKE_CURRENT_SOURCE_DIR}/external/Get_Doxygen.cmd to be able to generate documentation for the project. Please also install the GraphViz DOT package using ${CMAKE_CURRENT_SOURCE_DIR}/external/Get_Dot.cmd for rendering diagrams.")
endif(DOXYGEN_FOUND)


