#/*
#    Copyright (c) 2021 Technical University of Munich
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
#*/

cmake_minimum_required(VERSION 3.13.0)

project(OpenInfraPlatform.Base)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 14)

file(GLOB Base_Source 								src/*.*)

source_group(Base								FILES $Base_Source})

add_library(OpenInfraPlatform.Base STATIC
	${Base_Source}
)

target_include_directories(OpenInfraPlatform.Base
	PUBLIC 
		${PROJECT_SOURCE_DIR}/src
		${BLUEFRAMEWORK_INCLUDE_DIR}
)

# Thirdparty libraries the project depends upon.
target_link_libraries(OpenInfraPlatform.Base PRIVATE
    BlueFramework.Core
    BlueFramework.Rasterizer
    carve
)
