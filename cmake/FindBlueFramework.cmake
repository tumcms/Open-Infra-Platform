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
find_path(BlueFramework_DIR NAMES BlueFrameworkConfig.cmake PATHS "C:/Program Files/BlueFramework" REQUIRED)

if (MSVC)
	if("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "X86")
		set(BLUEFRAMEWORK_ARCHITECTURE "x86")
    elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "x64")
		set(BLUEFRAMEWORK_ARCHITECTURE "x64")
    elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "ARM")
		set(BLUEFRAMEWORK_ARCHITECTURE "arm")
    else()
		message(FATAL_ERROR "Failed to determine the MSVC target architecture: ${MSVC_C_ARCHITECTURE_ID}")
    endif()
endif()

if(BlueFramework_FIND_COMPONENTS)
	set(BLUEFRAMEWORK_COMPONENTS ${BlueFramework_FIND_COMPONENTS})
else(BlueFramework_FIND_COMPONENTS)
	set(BLUEFRAMEWORK_COMPONENTS Core Engine Application ImageProcessing Rasterizer D3D11RenderSystem D3D12RenderSystem GLRenderSystem)
endif(BlueFramework_FIND_COMPONENTS)

if(BlueFramework_DIR)
	find_path(BlueFramework_DIR_OVERRIDE OPTIONAL)
	if(BlueFramework_DIR_OVERRIDE)
		set(BlueFramework_DIR ${BlueFramework_DIR_OVERRIDE})
	endif()
	include(${BlueFramework_DIR}/CMake/BlueFrameworkMacros.cmake)
	set(BLUEFRAMEWORK_INCLUDE_DIR ${BLUEFRAMEWORK_INCLUDE_DIR} ${BlueFramework_DIR}/include/)
	set(BLUEFRAMEWORK_LIBRARY_DIR ${BlueFramework_DIR}/lib/${MSVC_VERSION_STRING}/${CMAKE_VS_PLATFORM_NAME}/)

	foreach(COMP ${BLUEFRAMEWORK_COMPONENTS})
		findInclude(${COMP})		
		findLibs(${COMP})
		findBinaries(${COMP})
	endforeach()
endif()