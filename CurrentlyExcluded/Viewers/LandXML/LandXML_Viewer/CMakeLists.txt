set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	../Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE	../Release)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG 	    ../Debug)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE 		../Release)

file(GLOB LandXMLViewer_Source	*.*)

include_directories(
	${BLUEFRAMEWORK_INCLUDE_DIR}
	${Boost_INCLUDE_DIR}
	${CMAKE_CURRENT_BINARY_DIR} # Qt generated files will be located here
	${VLD_INCLUDE_DIR}
)

link_directories(	
	${Boost_LIBRARY_DIRS} 
	${VLD_LIBRARIES_DIR}
)

# Tell CMake to create the Qt5HelloWorld executable
add_executable(OpenInfraPlatform.LandXMLViewer
	${LandXMLViewer_Source}
)

target_link_libraries( OpenInfraPlatform.LandXMLViewer
	OpenInfraPlatform.Infrastructure
    Qt5::WinMain  # <-- New target available via find_package ( Qt5Core )
	# BlueFramework
	${BLUEFRAMEWORK_BLUECORE_LIBRARY}
	${BLUEFRAMEWORK_BLUEIMAGEPROCESSING_LIBRARY}
	${BLUEFRAMEWORK_BLUERASTERIZER_LIBRARY}
	${BLUEFRAMEWORK_BLUEENGINE_LIBRARY}
	${BLUEFRAMEWORK_BLUEAPPLICATION_LIBRARY}
)