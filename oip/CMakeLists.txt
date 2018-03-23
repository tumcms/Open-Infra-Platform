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

project(OpenInfraPlatform.CommandLineUtilities)

find_package(TCLAP REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	../Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE	../Release)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG 	    ../Debug)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE 		../Release)

include_directories(
	${BLUEFRAMEWORK_INCLUDE_DIR}
	${TCLAP_INCLUDE_DIR}
)

# Tell CMake to create the Qt5HelloWorld executable
add_executable(OpenInfraPlatform.CommandLineUtilities main.cpp)

target_link_libraries(OpenInfraPlatform.CommandLineUtilities
	OpenInfraPlatform.Infrastructure
	# BlueFramework
	${BLUEFRAMEWORK_BLUECORE_LIBRARY}
	${BLUEFRAMEWORK_BLUEIMAGEPROCESSING_LIBRARY}
	${BLUEFRAMEWORK_BLUERASTERIZER_LIBRARY}
	${BLUEFRAMEWORK_BLUEENGINE_LIBRARY}
	${BLUEFRAMEWORK_BLUEAPPLICATION_LIBRARY}
)