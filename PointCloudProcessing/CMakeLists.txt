#
#    Copyright (c) 2018 Technical University of Munich
#    Chair of Computational Modeling and Simulation.
#
#    TUM Open Infra Platform is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License Version 3
#    as published by the Free Software Foundation.
#
#    TUM Open Infra Platform is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program. If not, see <http://www.gnu.org/licenses/>.
#

#-------------------------------------------------
# POINT CLOUD PROCESSING MODULE.
#-------------------------------------------------

if(MODULES_POINT_CLOUD_PROCESSING)

#project(OpenInfraPlatform_PointCloudProcessing)

add_definitions(-DBLUEINFRASTRUCTURE_EXPORT)
set(CMAKE_DEBUG_POSTFIX "d")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	../Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	../Release)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG 	    ../Debug)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE 	    ../Release)

# Unicode rules!
add_definitions(-D_UNICODE)
add_definitions(-DNOMINMAX)
add_definitions(-D_UNICODE -DBOOST_PYTHON_STATIC_LIB)
add_definitions(-DRAPTOR_STATIC)		

# Create a target for the library
add_library(OpenInfraPlatform.PointCloudProcessing MODULE	
	${OpenInfraPlatform_PointCloudProcessing_Source}	
	)

include_directories(
	../PointCloudProcessing/src
	${LIBLAS_INCLUDE_DIRS}	
	${CloudCompare_INCLUDE_DIRS}
	${CMAKE_CURRENT_BINARY_DIR} 	
)

target_link_libraries(OpenInfraPlatform.PointCloudProcessing 	
		${LIBLAS_LIBRARIES}	
		${CloudCompare_LIBRARIES}	
)

# Use the Widgets module from Qt 5.
target_link_libraries(OpenInfraPlatform.PointCloudProcessing Qt5::Xml Qt5::XmlPatterns Qt5::Gui Qt5::OpenGL)	

# Set the target properties.
set_target_properties(OpenInfraPlatform.PointCloudProcessing						PROPERTIES FOLDER "OpenInfraPlatform")	

# Install files.
install(FILES ${LIBLAS_RELEASE_BINARIES} ${CC_RELEASE_BINARIES}
	LIBRARY DESTINATION lib
	COMPONENT oip_thirdparty)

install(TARGETS OpenInfraPlatform.PointCloudProcessing 	
       	RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
     	ARCHIVE DESTINATION lib/static)

endif()