project(OpenInfraPlatform.IfcBridge)

set(CMAKE_DEBUG_POSTFIX "d")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	../Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	../Release)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG 	    ../Debug)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE 	    ../Release)

include_directories(src/OpenInfraPlatform/IfcBridge)

file(GLOB OpenInfraPlatform_IfcBridge_Source 					src/OpenInfraPlatform/IfcBridge/*.*)
file(GLOB OpenInfraPlatform_IfcBridge_guid_Source 				src/OpenInfraPlatform/IfcBridge/guid/*.*)
file(GLOB OpenInfraPlatform_IfcBridge_IFC4_Source 				src/OpenInfraPlatform/IfcBridge/entity/*.*)
file(GLOB OpenInfraPlatform_IfcBridge_IFC4_include_Source		src/OpenInfraPlatform/IfcBridge/entity/include/*.*)
file(GLOB OpenInfraPlatform_IfcBridge_model_Source 				src/OpenInfraPlatform/IfcBridge/model/*.*)
file(GLOB OpenInfraPlatform_IfcBridge_reader_Source 			src/OpenInfraPlatform/IfcBridge/reader/*.*)
file(GLOB OpenInfraPlatform_IfcBridge_writer_Source 			src/OpenInfraPlatform/IfcBridge/writer/*.*)
file(GLOB OpenInfraPlatform_IfcBridge_xml_Source 				src/OpenInfraPlatform/IfcBridge/xml/*.*)

source_group(OpenInfraPlatform\\IfcBridge\\						FILES ${OpenInfraPlatform_IfcBridge_Source})
source_group(OpenInfraPlatform\\IfcBridge\\guid					FILES ${OpenInfraPlatform_IfcBridge_guid_Source})
source_group(OpenInfraPlatform\\IfcBridge\\entity				FILES ${OpenInfraPlatform_IfcBridge_IFC4_Source})
source_group(OpenInfraPlatform\\IfcBridge\\entity\\include		FILES ${OpenInfraPlatform_IfcBridge_IFC4_include_Source})
source_group(OpenInfraPlatform\\IfcBridge\\model				FILES ${OpenInfraPlatform_IfcBridge_model_Source})
source_group(OpenInfraPlatform\\IfcBridge\\reader				FILES ${OpenInfraPlatform_IfcBridge_reader_Source})
source_group(OpenInfraPlatform\\IfcBridge\\writer				FILES ${OpenInfraPlatform_IfcBridge_writer_Source})
source_group(OpenInfraPlatform\\IfcBridge\\xml					FILES ${OpenInfraPlatform_IfcBridge_xml_Source})

add_library(OpenInfraPlatform.IfcBridge STATIC
	${OpenInfraPlatform_IfcBridge_Source}
	${OpenInfraPlatform_IfcBridge_guid_Source}
	${OpenInfraPlatform_IfcBridge_IFC4_Source}
	${OpenInfraPlatform_IfcBridge_IFC4_include_Source}
	${OpenInfraPlatform_IfcBridge_model_Source}
	${OpenInfraPlatform_IfcBridge_reader_Source}
	${OpenInfraPlatform_IfcBridge_writer_Source}
	${OpenInfraPlatform_IfcBridge_xml_Source}
)

if (WIN32)
target_link_libraries(OpenInfraPlatform.IfcBridge
	Rpcrt4.lib
)
endif (WIN32)
