# 	ConfigureDoxygen
#
# 	This is a configuration for the generation of doxygen documentation for the Open Infra Platform project. 
# 	ConfigureDoxygen is included in the top-level CMakeLists.txt of the project. 
#  	Changes to documentation settings should be made here. 
#  

find_path(Doxygen HINTS
".../thirdparty/doxygen-master"
)

find_package(Doxygen)

if(DOXYGEN_FOUND)
message("Doxygen found. For developers: Please use this project's doxygen documentation style specified in ${CMAKE_CURRENT_SOURCE_DIR}/Documentation/doxymentation/StyleSheetOIP.")


# CONFIGURATION. Check http://www.doxygen.nl/manual/config.html for all available options and their default values. 

# Build related configuration options. 
set(DOXYGEN_PROJECT_NAME OpenInfraPlatform)
set(DOXYGEN_PROJECT_BRIEF "Open source software for viewing and converting alignment data.")
set(DOXYGEN_PROJECT_LOGO ${CMAKE_CURRENT_SOURCE_DIR}/Documentation/interface.png)
set(DOXYGEN_CREATE_SUBDIRS YES)
set(DOXYGEN_HAVE_DOT YES) # GraphViz Package for diagrams

# Configuration file generation using CMake. 
set(DOXYFILE_CMAKE ${CMAKE_CURRENT_BINARY_DIR}/CMakeDoxyfile.in)
set(DOXYFILE ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

# Documentation settings.
set(DOXYGEN_EXTRACT_ALL YES) # Set to yes if you want to extract all existing documentation  from project. Do this for now, once starting proper documentation change to NO. 
set(DOXYGEN_RECURSIVE YES) #Search subdirectories for input files as well.
set(DOXYGEN_INTERNAL_DOCS NO) # Comments intended for developers and not for users (*! \internal *)
set(DOXYGEN_CLASS_DIAGRAMS YES)

# Output (HTML/Latex/...) configuration options.
set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_LATEX NO)
set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Documentation/doxymentation)
set(DOXYGEN_SEARCHENGINE YES)
set(DOXYGEN_SOURCE_BROWSER YES)
set(DOXYGEN_SUBGROUPING YES)
set(DOXYGEN_EXCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/CurrentlyExcluded ${CMAKE_CURRENT_SOURCE_DIR}/Documentation ${CMAKE_CURRENT_SOURCE_DIR}/external ${CMAKE_CURRENT_SOURCE_DIR}/testdata ${CMAKE_CURRENT_SOURCE_DIR}/Tools ${CMAKE_CURRENT_SOURCE_DIR}/UnitTests)

configure_file(${DOXYFILE_CMAKE} ${DOXYFILE} @ONLY)

# Documentation for entire OPEN INFRA PLATFORM project.
doxygen_add_docs(GenerateDocumentation ALL
${CMAKE_CURRENT_SOURCE_DIR} 	# Actual documented code here
WORKING DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}	# Current root
COMMENT "Generating doxymentation for TUM Open Infra Platform project.")

# Add important links to GenerateDocumentation Visual Studio project to facilitate access.
#set(OpenInfraPlatform_Documentation_ImportantLinks
#${CMAKE_CURRENT_SOURCE_DIR}/Documentation/doxymentation/html/index.html
#${CMAKE_CURRENT_SOURCE_DIR}/Documentation/doxymentation/html/classes.html
#${CMAKE_CURRENT_SOURCE_DIR}/Documentation/doxymentation/html/namespaces.html
#)

else()
message("Doxygen not found. Please install doxygen using ${CMAKE_CURRENT_SOURCE_DIR}/external/Get_Doxygen.cmd to be able to generate documentation for the project. Please also install the GraphViz DOT package using ${CMAKE_CURRENT_SOURCE_DIR}/external/Get_Dot.cmd for rendering diagrams.")
endif(DOXYGEN_FOUND)


