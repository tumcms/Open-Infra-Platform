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
#source_group(OpenInfraPlatform\\EarlyBinding\\EXPRESS		FILES ${OpenInfraPlatform_EarlyBinding_EXPRESS_Source})


foreach(format ${IFC_FORMATS})
	message(STATUS "Format ${format} found.")
	if(EXISTS ${CMAKE_BINARY_DIR}/EarlyBinding/${format})
		add_subdirectory(${CMAKE_BINARY_DIR}/EarlyBinding/${format} ${CMAKE_BINARY_DIR}/EarlyBinding/${format})
		#get_target_property(OpenInfraPlatform.${format}_INCLUDE_DIRS OpenInfraPlatform.${format} INTERFACE_INCLUDE_DIRECTORIES)
		set_target_properties(OpenInfraPlatform.${format} PROPERTIES FOLDER "OpenInfraPlatform/EarlyBinding")
		
		#set(OpenInfraPlatform.EarlyBinding_INCLUDE_DIRS ${OpenInfraPlatform.EarlyBinding_INCLUDE_DIRS} ${OpenInfraPlatform.${format}_INCLUDE_DIRS})
	elseif()
		message(WARNING "Files for format ${format} not found.")
	endif()
endforeach()