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


project(OpenInfraPlatform.EarlyBinding CXX)

file(GLOB OpenInfraPlatform_EarlyBinding_EXPRESS_Source		src/OpenInfraPlatform/EarlyBinding/EXPRESS/*.*)	
source_group(OpenInfraPlatform\\EarlyBinding\\EXPRESS		FILES ${OpenInfraPlatform_EarlyBinding_EXPRESS_Source})


include_directories(
  src
  ${Boost_INCLUDE_DIR}
  ${visit_struct_INCLUDE_DIR}
)

#add_library(OpenInfraPlatform.EXPRESS STATIC
#	${OpenInfraPlatform_EarlyBinding_EXPRESS_Source}
#)

add_library(OpenInfraPlatform.EarlyBinding STATIC
	${OpenInfraPlatform_EarlyBinding_EXPRESS_Source}
)

#target_link_libraries(OpenInfraPlatform.EarlyBinding OpenInfraPlatform.EXPRESS)


foreach(format ${IFC_FORMATS})
	message(STATUS "Format ${format} found.")
	if(EXISTS ${CMAKE_BINARY_DIR}/EarlyBinding/${format})
		add_subdirectory(${CMAKE_BINARY_DIR}/EarlyBinding/${format} ${CMAKE_BINARY_DIR}/EarlyBinding/${format})
		get_target_property(${format}_INCLUDE_DIRS OpenInfraPlatform.${format} INTERFACE_INCLUDE_DIRECTORIES)
		set_target_properties(OpenInfraPlatform.${format} PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding")
		target_link_libraries(OpenInfraPlatform.EarlyBinding OpenInfraPlatform.${format})
		set(EarlyBinding_INCLUDE_DIRS ${EarlyBinding_INCLUDE_DIRS} ${${format}_INCLUDE_DIRS})
	elseif()
		message(WARNING "Files for format ${format} not found.")
	endif()
endforeach()


target_include_directories(OpenInfraPlatform.EarlyBinding
	INTERFACE src
	INTERFACE ${visit_struct_INCLUDE_DIR}
	INTERFACE ${Boost_INCLUDE_DIR}
	INTERFACE ${EarlyBinding_INCLUDE_DIRS}
)

set_target_properties(OpenInfraPlatform.EarlyBinding PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding")
#set_target_properties(OpenInfraPlatform.EXPRESS PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding")


Install(DIRECTORY ${PROJECT_SOURCE_DIR} DESTINATION include
	COMPONENT EarlyBinding
	FILES_MATCHING PATTERN "*.h"
)
