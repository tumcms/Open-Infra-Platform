#
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
#

project(OpenInfraPlatform.Rendering)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB OpenInfraPlatform_Rendering_Effects_Source 	    Effects/*.h Effects/*.cpp)
file(GLOB OpenInfraPlatform_Rendering_Resources_Source 	    Resources/*.*)
file(GLOB OpenInfraPlatform_Rendering_Shader_Source 		Shader/*.*)
file(GLOB OpenInfraPlatform_Rendering_Shader_D3D_Source 	Shader/D3D/*.*)
file(GLOB OpenInfraPlatform_Rendering_Tools_Source			Tools/*.*)	

if(MODULES_POINT_CLOUD_PROCESSING)
	file(GLOB OpenInfraPlatform_Rendering_Effects_PointCloudProcessing_Source 	Effects/PointCloudProcessing/*.*)
	source_group(Rendering\\Effects\\PointCloudProcessing	FILES ${OpenInfraPlatform_Rendering_Effects_PointCloudProcessing_Source})
	list(APPEND OpenInfraPlatform_Rendering_Effects_Source ${OpenInfraPlatform_Rendering_Effects_PointCloudProcessing_Source})
endif()

source_group(Rendering\\Effects	        FILES ${OpenInfraPlatform_Rendering_Effects_Source})
source_group(Rendering\\Resources		FILES ${OpenInfraPlatform_Rendering_Resources_Source})
source_group(Rendering\\Shader			FILES ${OpenInfraPlatform_Rendering_Shader_Source})
source_group(Rendering\\Shader\\D3D		FILES ${OpenInfraPlatform_Rendering_Shader_D3D_Source})
source_group(Rendering\\Tools			FILES ${OpenInfraPlatform_Rendering_Tools_Source})

# Set HEADER_FILES_ONLY to true to make them show up in the IDE but be excluded from compiling
set_source_files_properties(${OpenInfraPlatform_Rendering_Shader_Source} 		PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties(${OpenInfraPlatform_Rendering_Shader_D3D_Source} 	PROPERTIES HEADER_FILE_ONLY TRUE)

add_library(OpenInfraPlatform.Rendering STATIC
    ${OpenInfraPlatform_Rendering_Effects_Source}
    ${OpenInfraPlatform_Rendering_Shader_Source}
    ${OpenInfraPlatform_Rendering_Shader_D3D_Source}
	${OpenInfraPlatform_Rendering_Resources_Source}
	${OpenInfraPlatform_Rendering_Tools_Source}
)

target_include_directories(OpenInfraPlatform.Rendering INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(OpenInfraPlatform.Rendering
    PUBLIC
        OpenInfraPlatform.Core
        BlueFramework.Rasterizer
        BlueFramework.Engine    
		Qt5::Core
		Qt5::Gui
		Qt5::Widgets
		Qt5::Quick
		Qt5::Location
		Qt5::Positioning)
