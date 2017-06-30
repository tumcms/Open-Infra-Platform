PROJECT(OpenInfraPlatform.Ifc2x3)

set(CMAKE_DEBUG_POSTFIX "d")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	../Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	../Release)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG 	    ../Debug)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE 	    ../Release)

include_directories(src/OpenInfraPlatform/Ifc2x3)

file(GLOB OpenInfraPlatform_Ifc2x3_Source 					src/OpenInfraPlatform/Ifc2x3/*.*)
file(GLOB OpenInfraPlatform_Ifc2x3_guid_Source 				src/OpenInfraPlatform/Ifc2x3/guid/*.*)
file(GLOB OpenInfraPlatform_Ifc2x3_IFC2x3_Source 				src/OpenInfraPlatform/Ifc2x3/entity/*.*)
file(GLOB OpenInfraPlatform_Ifc2x3_IFC2x3_include_Source		src/OpenInfraPlatform/Ifc2x3/entity/include/*.*)
file(GLOB OpenInfraPlatform_Ifc2x3_model_Source 				src/OpenInfraPlatform/Ifc2x3/model/*.*)
file(GLOB OpenInfraPlatform_Ifc2x3_reader_Source 				src/OpenInfraPlatform/Ifc2x3/reader/*.*)
file(GLOB OpenInfraPlatform_Ifc2x3_writer_Source 				src/OpenInfraPlatform/Ifc2x3/writer/*.*)
file(GLOB OpenInfraPlatform_Ifc2x3_xml_Source 				src/OpenInfraPlatform/Ifc2x3/xml/*.*)

source_group(OpenInfraPlatform\\Ifc2x3\\					FILES ${OpenInfraPlatform_Ifc2x3_Source})
source_group(OpenInfraPlatform\\Ifc2x3\\guid				FILES ${OpenInfraPlatform_Ifc2x3_guid_Source})
source_group(OpenInfraPlatform\\Ifc2x3\\entity				FILES ${OpenInfraPlatform_Ifc2x3_IFC2x3_Source})
source_group(OpenInfraPlatform\\Ifc2x3\\entity\\include		FILES ${OpenInfraPlatform_Ifc2x3_IFC2x3_include_Source})
source_group(OpenInfraPlatform\\Ifc2x3\\model				FILES ${OpenInfraPlatform_Ifc2x3_model_Source})
source_group(OpenInfraPlatform\\Ifc2x3\\reader				FILES ${OpenInfraPlatform_Ifc2x3_reader_Source})
source_group(OpenInfraPlatform\\Ifc2x3\\writer				FILES ${OpenInfraPlatform_Ifc2x3_writer_Source})
source_group(OpenInfraPlatform\\Ifc2x3\\xml					FILES ${OpenInfraPlatform_Ifc2x3_xml_Source})

add_library(OpenInfraPlatform.Ifc2x3 STATIC
	${OpenInfraPlatform_Ifc2x3_Source}
	${OpenInfraPlatform_Ifc2x3_guid_Source}
	${OpenInfraPlatform_Ifc2x3_IFC2x3_Source}
	${OpenInfraPlatform_Ifc2x3_IFC2x3_include_Source}
	${OpenInfraPlatform_Ifc2x3_model_Source}
	${OpenInfraPlatform_Ifc2x3_reader_Source}
	${OpenInfraPlatform_Ifc2x3_writer_Source}
	${OpenInfraPlatform_Ifc2x3_xml_Source}
)

if (WIN32)
target_link_libraries(OpenInfraPlatform.Ifc2x3
	Rpcrt4.lib)
endif (WIN32)
