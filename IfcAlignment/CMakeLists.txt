project(OpenInfraPlatform.IfcAlignment)

set(CMAKE_DEBUG_POSTFIX "d")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	../Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	../Release)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG 	    ../Debug)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE 	    ../Release)

file(GLOB IfcAlignment_Source 						src/OpenInfraPlatform/IfcAlignment/*.*)
file(GLOB IfcAlignment_guid_Source 					src/OpenInfraPlatform/IfcAlignment/guid/*.*)
file(GLOB IfcAlignment_entity_Source 				src/OpenInfraPlatform/IfcAlignment/entity/*.*)
file(GLOB IfcAlignment_entity_include_Source		src/OpenInfraPlatform/IfcAlignment/entity/include/*.*)
file(GLOB IfcAlignment_model_Source 				src/OpenInfraPlatform/IfcAlignment/model/*.*)
file(GLOB IfcAlignment_reader_Source 				src/OpenInfraPlatform/IfcAlignment/reader/*.*)
file(GLOB IfcAlignment_writer_Source 				src/OpenInfraPlatform/IfcAlignment/writer/*.*)
file(GLOB IfcAlignment_xml_Source 					src/OpenInfraPlatform/IfcAlignment/xml/*.*)

source_group(OpenInfraPlatform\\IfcAlignment					FILES ${IfcAlignment_Source})
source_group(OpenInfraPlatform\\IfcAlignment\\guid				FILES ${IfcAlignment_guid_Source})
source_group(OpenInfraPlatform\\IfcAlignment\\entity			FILES ${IfcAlignment_entity_Source})
source_group(OpenInfraPlatform\\IfcAlignment\\entity\\include	FILES ${IfcAlignment_entity_include_Source})
source_group(OpenInfraPlatform\\IfcAlignment\\model				FILES ${IfcAlignment_model_Source})
source_group(OpenInfraPlatform\\IfcAlignment\\reader			FILES ${IfcAlignment_reader_Source})
source_group(OpenInfraPlatform\\IfcAlignment\\writer			FILES ${IfcAlignment_writer_Source})
source_group(OpenInfraPlatform\\IfcAlignment\\xml				FILES ${IfcAlignment_xml_Source})

add_library(OpenInfraPlatform.IfcAlignment STATIC
	${IfcAlignment_Source}
	${IfcAlignment_guid_Source}
	${IfcAlignment_entity_Source}
	${IfcAlignment_entity_include_Source}
	${IfcAlignment_model_Source}
	${IfcAlignment_reader_Source}
	${IfcAlignment_writer_Source}
	${IfcAlignment_xml_Source}
)

include_directories(
	src
)

if (WIN32)
target_link_libraries(OpenInfraPlatform.IfcAlignment Rpcrt4.lib)
endif (WIN32)
