#
#   This file is part of BlueFramework, a simple 3D engine.
#	Copyright (c) 2016 Technical University of Munich
#	Chair of Computational Modeling and Simulation.
#   
#   BlueFramework is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License Version 3
#   as published by the Free Software Foundation.
#   
#   BlueFramework is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
#   
#   You should have received a copy of the GNU General Public License
#   along with this program. If not, see <http://www.gnu.org/licenses/>.
#


if (MSVC)
	if("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "X86")
		set(BLUEFRAMEWORK3_ARCHITECTURE "x86")
    elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "x64")
		set(BLUEFRAMEWORK3_ARCHITECTURE "x64")
    elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "ARM")
		set(BLUEFRAMEWORK3_ARCHITECTURE "arm")
    else()
		message(FATAL_ERROR "Failed to determine the MSVC target architecture: ${MSVC_C_ARCHITECTURE_ID}")
    endif()
endif()

if(BlueFramework3_FIND_COMPONENTS)
	set(BLUEFRAMEWORK3_COMPONENTS ${BlueFramework3_FIND_COMPONENTS})
else(BlueFramework3_FIND_COMPONENTS)
	set(BLUEFRAMEWORK3_COMPONENTS Core Engine Application ImageProcessing Rasterizer D3D11RenderSystem D3D12RenderSystem Cheetah)
endif(BlueFramework3_FIND_COMPONENTS)

find_path(BlueFramework3_DIR_OVERRIDE OPTIONAL)

if(BlueFramework3_DIR_OVERRIDE)
	set(BlueFramework3_DIR ${BlueFramework3_DIR_OVERRIDE})
endif()

if(BlueFramework3_DIR)
	include(${BlueFramework3_DIR}/CMake/BlueFramework3-macros.cmake)
	set(BLUEFRAMEWORK3_INCLUDE_DIR ${BLUEFRAMEWORK3_INCLUDE_DIR} ${BlueFramework3_DIR}/include/)
	set(BLUEFRAMEWORK3_LIBRARY_DIR ${BlueFramework3_DIR}/lib/vs2015/${CMAKE_VS_PLATFORM_NAME}/)

	foreach(COMP ${BLUEFRAMEWORK3_COMPONENTS})
		findInclude(${COMP})		
		findLibs(${COMP})
		findBinaries(${COMP})
	endforeach()
endif()