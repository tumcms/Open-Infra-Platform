project(OpenInfraPlatform.IfcAlignment1x1)

set(CMAKE_DEBUG_POSTFIX "d")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	../Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	../Release)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG 	    ../Debug)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE 	    ../Release)

include_directories(
  src/OpenInfraPlatform/IfcAlignment1x1
  src
  ${Boost_INCLUDE_DIR}
)

file(GLOB OpenInfraPlatform_IfcAlignment1x1_Source              src/OpenInfraPlatform/IfcAlignment1x1/*.*)
file(GLOB OpenInfraPlatform_IfcAlignment1x1_guid_Source         src/OpenInfraPlatform/IfcAlignment1x1/guid/*.*)
file(GLOB OpenInfraPlatform_IfcAlignment1x1_entity_Source         src/OpenInfraPlatform/IfcAlignment1x1/entity/*.*)
file(GLOB OpenInfraPlatform_IfcAlignment1x1_include_Source src/OpenInfraPlatform/IfcAlignment1x1/entity/include/*.*)
file(GLOB OpenInfraPlatform_IfcAlignment1x1_model_Source        src/OpenInfraPlatform/IfcAlignment1x1/model/*.*)
file(GLOB OpenInfraPlatform_IfcAlignment1x1_reader_Source       src/OpenInfraPlatform/IfcAlignment1x1/reader/*.*)
file(GLOB OpenInfraPlatform_IfcAlignment1x1_writer_Source       src/OpenInfraPlatform/IfcAlignment1x1/writer/*.*)
file(GLOB OpenInfraPlatform_IfcAlignment1x1_xml_Source          src/OpenInfraPlatform/IfcAlignment1x1/xml/*.*)

source_group(OpenInfraPlatform\\IfcAlignment1x1                FILES ${OpenInfraPlatform_IfcAlignment1x1_Source})
source_group(OpenInfraPlatform\\IfcAlignment1x1\\guid            FILES ${OpenInfraPlatform_IfcAlignment1x1_guid_Source})
source_group(OpenInfraPlatform\\IfcAlignment1x1\\entity          FILES ${OpenInfraPlatform_IfcAlignment1x1_entity_Source})
source_group(OpenInfraPlatform\\IfcAlignment1x1\\entity\\include FILES ${OpenInfraPlatform_IfcAlignment1x1_include_Source})
source_group(OpenInfraPlatform\\IfcAlignment1x1\\model           FILES ${OpenInfraPlatform_IfcAlignment1x1_model_Source})
source_group(OpenInfraPlatform\\IfcAlignment1x1\\reader          FILES ${OpenInfraPlatform_IfcAlignment1x1_reader_Source})
source_group(OpenInfraPlatform\\IfcAlignment1x1\\writer          FILES ${OpenInfraPlatform_IfcAlignment1x1_writer_Source})
source_group(OpenInfraPlatform\\IfcAlignment1x1\\xml             FILES ${OpenInfraPlatform_IfcAlignment1x1_xml_Source})

add_library(OpenInfraPlatform.IfcAlignment1x1 STATIC
	${OpenInfraPlatform_IfcAlignment1x1_Source}
	${OpenInfraPlatform_IfcAlignment1x1_guid_Source}
	${OpenInfraPlatform_IfcAlignment1x1_entity_Source}
	${OpenInfraPlatform_IfcAlignment1x1_include_Source}
	${OpenInfraPlatform_IfcAlignment1x1_model_Source}
	${OpenInfraPlatform_IfcAlignment1x1_reader_Source}
	${OpenInfraPlatform_IfcAlignment1x1_writer_Source}
	${OpenInfraPlatform_IfcAlignment1x1_xml_Source}
)

if (WIN32)
	target_link_libraries(OpenInfraPlatform.IfcAlignment1x1
	Rpcrt4.lib)
endif (WIN32)