project(OpenInfraPlatform.Ifc4)

set(CMAKE_DEBUG_POSTFIX "d")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	../Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	../Release)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG 	    ../Debug)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE 	    ../Release)

include_directories(
	src/OpenInfraPlatform/Ifc4
	src
)

file(GLOB OpenInfraPlatform_Ifc4_Source 					src/OpenInfraPlatform/Ifc4/*.*)
file(GLOB OpenInfraPlatform_Ifc4_guid_Source 				src/OpenInfraPlatform/Ifc4/guid/*.*)
file(GLOB OpenInfraPlatform_Ifc4_Ifc4_Source 				src/OpenInfraPlatform/Ifc4/entity/*.*)
file(GLOB OpenInfraPlatform_Ifc4_Ifc4_include_Source		src/OpenInfraPlatform/Ifc4/entity/include/*.*)
file(GLOB OpenInfraPlatform_Ifc4_model_Source 				src/OpenInfraPlatform/Ifc4/model/*.*)
file(GLOB OpenInfraPlatform_Ifc4_reader_Source 				src/OpenInfraPlatform/Ifc4/reader/*.*)
file(GLOB OpenInfraPlatform_Ifc4_writer_Source 				src/OpenInfraPlatform/Ifc4/writer/*.*)
file(GLOB OpenInfraPlatform_Ifc4_xml_Source 				src/OpenInfraPlatform/Ifc4/xml/*.*)

source_group(OpenInfraPlatform\\Ifc4\\					FILES ${OpenInfraPlatform_Ifc4_Source})
source_group(OpenInfraPlatform\\Ifc4\\guid				FILES ${OpenInfraPlatform_Ifc4_guid_Source})
source_group(OpenInfraPlatform\\Ifc4\\entity			FILES ${OpenInfraPlatform_Ifc4_Ifc4_Source})
source_group(OpenInfraPlatform\\Ifc4\\entity\\include	FILES ${OpenInfraPlatform_Ifc4_Ifc4_include_Source})
source_group(OpenInfraPlatform\\Ifc4\\model				FILES ${OpenInfraPlatform_Ifc4_model_Source})
source_group(OpenInfraPlatform\\Ifc4\\reader			FILES ${OpenInfraPlatform_Ifc4_reader_Source})
source_group(OpenInfraPlatform\\Ifc4\\writer			FILES ${OpenInfraPlatform_Ifc4_writer_Source})
source_group(OpenInfraPlatform\\Ifc4\\xml				FILES ${OpenInfraPlatform_Ifc4_xml_Source})

add_library(OpenInfraPlatform.Ifc4 STATIC
	${OpenInfraPlatform_Ifc4_Source}
	${OpenInfraPlatform_Ifc4_guid_Source}
	${OpenInfraPlatform_Ifc4_Ifc4_Source}
	${OpenInfraPlatform_Ifc4_Ifc4_include_Source}
	${OpenInfraPlatform_Ifc4_model_Source}
	${OpenInfraPlatform_Ifc4_reader_Source}
	${OpenInfraPlatform_Ifc4_writer_Source}
	${OpenInfraPlatform_Ifc4_xml_Source}
)

if (WIN32)
target_link_libraries(OpenInfraPlatform.Ifc4
	Rpcrt4.lib)
endif (WIN32)
