#
#    Copyright(c) 2018 Technical University of Munich
#    Chair of Computational Modeling and Simulation.
#
#    TUM Open Infra Platform is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License Version 3
#    as published by the Free Software Foundation.
#
#    TUM Open Infra Platform is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.If not, see <http://www.gnu.org/licenses/>.
#


# This file has been automatically generated using the TUM Open Infra Platform
# Early Binding EXPRESS Generator. Any changes to this file my be lost in the future.

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

Install(DIRECTORY ${PROJECT_SOURCE_DIR}/build/${MSVC_VERSION_STRING}/Debug DESTINATION lib/${MSVC_VERSION_STRING}/x64
	COMPONENT IfcAlignment1x1
	FILES_MATCHING PATTERN "*.lib" PATTERN "*.pdb"
)


Install(DIRECTORY ${PROJECT_SOURCE_DIR}/build/${MSVC_VERSION_STRING}/Release DESTINATION lib/${MSVC_VERSION_STRING}/x64
	COMPONENT IfcAlignment1x1
	FILES_MATCHING PATTERN "*.lib"
)

Install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/ DESTINATION include
	COMPONENT IfcAlignment1x1
	FILES_MATCHING PATTERN "*.h"
)
