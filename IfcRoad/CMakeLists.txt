project(OpenInfraPlatform.IfcRoad)

set(CMAKE_DEBUG_POSTFIX "d")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	../Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	../Release)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG 	    ../Debug)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE 	    ../Release)

file(GLOB IfcRoad_Source 						src/OpenInfraPlatform/IfcRoad/*.*)
file(GLOB IfcRoad_guid_Source 					src/OpenInfraPlatform/IfcRoad/guid/*.*)
file(GLOB IfcRoad_entity_Source 				src/OpenInfraPlatform/IfcRoad/entity/*.*)
file(GLOB IfcRoad_entity_include_Source			src/OpenInfraPlatform/IfcRoad/entity/include/*.*)
file(GLOB IfcRoad_model_Source 					src/OpenInfraPlatform/IfcRoad/model/*.*)
file(GLOB IfcRoad_reader_Source 				src/OpenInfraPlatform/IfcRoad/reader/*.*)
file(GLOB IfcRoad_writer_Source 				src/OpenInfraPlatform/IfcRoad/writer/*.*)
file(GLOB IfcRoad_xml_Source 					src/OpenInfraPlatform/IfcRoad/xml/*.*)

source_group(OpenInfraPlatform\\IfcRoad						FILES ${IfcRoad_Source})
source_group(OpenInfraPlatform\\IfcRoad\\guid				FILES ${IfcRoad_guid_Source})
source_group(OpenInfraPlatform\\IfcRoad\\entity				FILES ${IfcRoad_entity_Source})
source_group(OpenInfraPlatform\\IfcRoad\\entity\\include	FILES ${IfcRoad_entity_include_Source})
source_group(OpenInfraPlatform\\IfcRoad\\model				FILES ${IfcRoad_model_Source})
source_group(OpenInfraPlatform\\IfcRoad\\reader				FILES ${IfcRoad_reader_Source})
source_group(OpenInfraPlatform\\IfcRoad\\writer				FILES ${IfcRoad_writer_Source})
source_group(OpenInfraPlatform\\IfcRoad\\xml				FILES ${IfcRoad_xml_Source})

add_library(OpenInfraPlatform.IfcRoad STATIC
	${IfcRoad_Source}
	${IfcRoad_guid_Source}
	${IfcRoad_entity_Source}
	${IfcRoad_entity_include_Source}
	${IfcRoad_model_Source}
	${IfcRoad_reader_Source}
	${IfcRoad_writer_Source}
	${IfcRoad_xml_Source}
)

include_directories(
	src
)

if (WIN32)
target_link_libraries(OpenInfraPlatform.IfcRoad Rpcrt4.lib)
endif (WIN32)
