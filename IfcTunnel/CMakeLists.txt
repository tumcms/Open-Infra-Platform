project(OpenInfraPlatform.IfcTunnel)

set(CMAKE_DEBUG_POSTFIX "d")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	../Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	../Release)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG 	    ../Debug)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE 	    ../Release)

include_directories(src/OpenInfraPlatform)
include_directories(src/OpenInfraPlatform/IfcTunnel)

file(GLOB OpenInfraPlatform_IfcTunnel_Source 					src/OpenInfraPlatform/IfcTunnel/*.*)
file(GLOB OpenInfraPlatform_IfcTunnel_guid_Source 				src/OpenInfraPlatform/IfcTunnel/guid/*.*)
file(GLOB OpenInfraPlatform_IfcTunnel_IFC4_Source 				src/OpenInfraPlatform/IfcTunnel/entity/*.*)
file(GLOB OpenInfraPlatform_IfcTunnel_IFC4_include_Source		src/OpenInfraPlatform/IfcTunnel/entity/include/*.*)
file(GLOB OpenInfraPlatform_IfcTunnel_model_Source 				src/OpenInfraPlatform/IfcTunnel/model/*.*)
file(GLOB OpenInfraPlatform_IfcTunnel_reader_Source 			src/OpenInfraPlatform/IfcTunnel/reader/*.*)
file(GLOB OpenInfraPlatform_IfcTunnel_writer_Source 			src/OpenInfraPlatform/IfcTunnel/writer/*.*)
file(GLOB OpenInfraPlatform_IfcTunnel_xml_Source 				src/OpenInfraPlatform/IfcTunnel/xml/*.*)

source_group(OpenInfraPlatform\\IfcTunnel\\						FILES ${OpenInfraPlatform_IfcTunnel_Source})
source_group(OpenInfraPlatform\\IfcTunnel\\guid					FILES ${OpenInfraPlatform_IfcTunnel_guid_Source})
source_group(OpenInfraPlatform\\IfcTunnel\\entity				FILES ${OpenInfraPlatform_IfcTunnel_IFC4_Source})
source_group(OpenInfraPlatform\\IfcTunnel\\entity\\include		FILES ${OpenInfraPlatform_IfcTunnel_IFC4_include_Source})
source_group(OpenInfraPlatform\\IfcTunnel\\model				FILES ${OpenInfraPlatform_IfcTunnel_model_Source})
source_group(OpenInfraPlatform\\IfcTunnel\\reader				FILES ${OpenInfraPlatform_IfcTunnel_reader_Source})
source_group(OpenInfraPlatform\\IfcTunnel\\writer				FILES ${OpenInfraPlatform_IfcTunnel_writer_Source})
source_group(OpenInfraPlatform\\IfcTunnel\\xml					FILES ${OpenInfraPlatform_IfcTunnel_xml_Source})

add_library(OpenInfraPlatform.IfcTunnel STATIC
	${OpenInfraPlatform_IfcTunnel_Source}
	${OpenInfraPlatform_IfcTunnel_guid_Source}
	${OpenInfraPlatform_IfcTunnel_IFC4_Source}
	${OpenInfraPlatform_IfcTunnel_IFC4_include_Source}
	${OpenInfraPlatform_IfcTunnel_model_Source}
	${OpenInfraPlatform_IfcTunnel_reader_Source}
	${OpenInfraPlatform_IfcTunnel_writer_Source}
	${OpenInfraPlatform_IfcTunnel_xml_Source}
)

if (WIN32)
	target_link_libraries(OpenInfraPlatform.IfcTunnel
		Rpcrt4.lib
	)
endif (WIN32)