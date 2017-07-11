#
#    Copyright (c) 2017 Technical University of Munich
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

file(GLOB OpenInfraPlatform_Infrastructure_Alignment_HorizontalAlignment_Source 	src/OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/*.*)								
file(GLOB OpenInfraPlatform_Infrastructure_Alignment_Source 						src/OpenInfraPlatform/Infrastructure/Alignment/*.*)			
file(GLOB OpenInfraPlatform_Infrastructure_Alignment_VerticalAlignment_Source 		src/OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/*.*)			
file(GLOB OpenInfraPlatform_Infrastructure_Bindings_Source 							src/OpenInfraPlatform/Infrastructure/Bindings/*.*)		
file(GLOB OpenInfraPlatform_Infrastructure_Core_Source 								src/OpenInfraPlatform/Infrastructure/Core/*.*)	
file(GLOB OpenInfraPlatform_Infrastructure_CrossSection_Source 						src/OpenInfraPlatform/Infrastructure/CrossSection/*.*)			
file(GLOB OpenInfraPlatform_Infrastructure_DigitalElevationModel_Source 			src/OpenInfraPlatform/Infrastructure/DigitalElevationModel/*.*)
file(GLOB OpenInfraPlatform_Infrastructure_SectionedSolid_Source 					src/OpenInfraPlatform/Infrastructure/SectionedSolid/*.*)
file(GLOB OpenInfraPlatform_Infrastructure_Girder_Source 							src/OpenInfraPlatform/Infrastructure/Girder/*.*)
file(GLOB OpenInfraPlatform_Infrastructure_SlabField_Source 						src/OpenInfraPlatform/Infrastructure/SlabField/*.*)
file(GLOB OpenInfraPlatform_Infrastructure_Tessellation_Source 						src/OpenInfraPlatform/Infrastructure/Tessellation/*.*)
file(GLOB OpenInfraPlatform_Infrastructure_EnergyConsumption_Source 				src/OpenInfraPlatform/Infrastructure/EnergyConsumption/*.*)						
file(GLOB OpenInfraPlatform_Infrastructure_EnergyConsumption_Calculators_Source 	src/OpenInfraPlatform/Infrastructure/EnergyConsumption/Calculators/*.*)	
file(GLOB OpenInfraPlatform_Infrastructure_EnergyConsumption_Calculators_Parameters_Source 	src/OpenInfraPlatform/Infrastructure/EnergyConsumption/Calculators/Parameters/*.*)	
file(GLOB OpenInfraPlatform_Infrastructure_EnergyConsumption_Profiles_Source 		src/OpenInfraPlatform/Infrastructure/EnergyConsumption/Profiles/*.*)	
file(GLOB OpenInfraPlatform_Infrastructure_Export_Source 							src/OpenInfraPlatform/Infrastructure/Export/*.*)		
file(GLOB OpenInfraPlatform_Infrastructure_IfcPL_Source 							src/OpenInfraPlatform/Infrastructure/IfcPL/*.*)		
file(GLOB OpenInfraPlatform_Infrastructure_Import_Source 							src/OpenInfraPlatform/Infrastructure/Import/*.*)		
file(GLOB OpenInfraPlatform_Infrastructure_PointCloudProcessing_Source				src/OpenInfraPlatform/Infrastructure/PointCloudProcessing/*.*)					
file(GLOB OpenInfraPlatform_Infrastructure_Source 									src/OpenInfraPlatform/Infrastructure/*.*)	

source_group(OpenInfraPlatform\\Infrastructure										FILES ${OpenInfraPlatform_Infrastructure_Source})
source_group(OpenInfraPlatform\\Infrastructure\\Alignment							FILES ${OpenInfraPlatform_Infrastructure_Alignment_Source})			
source_group(OpenInfraPlatform\\Infrastructure\\Alignment\\HorizontalAlignment		FILES ${OpenInfraPlatform_Infrastructure_Alignment_HorizontalAlignment_Source})								
source_group(OpenInfraPlatform\\Infrastructure\\Alignment\\VerticalAlignment		FILES ${OpenInfraPlatform_Infrastructure_Alignment_VerticalAlignment_Source})													
source_group(OpenInfraPlatform\\Infrastructure\\Bindings							FILES ${OpenInfraPlatform_Infrastructure_Bindings_Source})			
source_group(OpenInfraPlatform\\Infrastructure\\Core								FILES ${OpenInfraPlatform_Infrastructure_Core_Source})		
source_group(OpenInfraPlatform\\Infrastructure\\CrossSection						FILES ${OpenInfraPlatform_Infrastructure_CrossSection_Source})				
source_group(OpenInfraPlatform\\Infrastructure\\DigitalElevationModel  				FILES ${OpenInfraPlatform_Infrastructure_DigitalElevationModel_Source})						
source_group(OpenInfraPlatform\\Infrastructure\\SectionedSolid						FILES ${OpenInfraPlatform_Infrastructure_SectionedSolid_Source})
source_group(OpenInfraPlatform\\Infrastructure\\Girder  							FILES ${OpenInfraPlatform_Infrastructure_Girder_Source})
source_group(OpenInfraPlatform\\Infrastructure\\SlabField  							FILES ${OpenInfraPlatform_Infrastructure_SlabField_Source})
source_group(OpenInfraPlatform\\Infrastructure\\Tessellation  						FILES ${OpenInfraPlatform_Infrastructure_Tessellation_Source})
source_group(OpenInfraPlatform\\Infrastructure\\EnergyConsumption					FILES ${OpenInfraPlatform_Infrastructure_EnergyConsumption_Source})
source_group(OpenInfraPlatform\\Infrastructure\\EnergyConsumption\\Calculators 		FILES ${OpenInfraPlatform_Infrastructure_EnergyConsumption_Calculators_Source_Source})
source_group(OpenInfraPlatform\\Infrastructure\\EnergyConsumption\\Calculators\\Parameters_Source 	FILES ${OpenInfraPlatform_Infrastructure_EnergyConsumption_Calculators_Parameters_Source})
source_group(OpenInfraPlatform\\Infrastructure\\EnergyConsumption\\Profiles 		FILES ${OpenInfraPlatform_Infrastructure_EnergyConsumption_Profiles_Source})
source_group(OpenInfraPlatform\\Infrastructure\\Export								FILES ${OpenInfraPlatform_Infrastructure_Export_Source})		
source_group(OpenInfraPlatform\\Infrastructure\\IfcPL								FILES ${OpenInfraPlatform_Infrastructure_IfcPL_Source})		
source_group(OpenInfraPlatform\\Infrastructure\\Import								FILES ${OpenInfraPlatform_Infrastructure_Import_Source})		
source_group(OpenInfraPlatform\\Infrastructure\\PointCloudProcessing				FILES ${OpenInfraPlatform_Infrastructure_PointCloudProcessing_Source})				

include_directories(
	${Boost_INCLUDE_DIR} 
	${PYTHON_INCLUDE_DIRS}
	${VLD_INCLUDE_DIR}
	${BLUEFRAMEWORK_INCLUDE_DIR}
	${EIGEN3_INCLUDE_DIR}
	src
	${LIBLAS_INCLUDE_DIRS}
	../external/QtXlsxWriter/src/xlsx
	${OKLABI_ROOT_DIR}/Kern-C++
	${OKLABI_ROOT_DIR}/Dienst
	${QHULL_INCLUDE_DIRS}
)

# Create a target for the library
add_library(OpenInfraPlatform.Infrastructure SHARED 
	${OpenInfraPlatform_Infrastructure_Alignment_HorizontalAlignment_Source}
	${OpenInfraPlatform_Infrastructure_Alignment_Source}
	${OpenInfraPlatform_Infrastructure_Alignment_VerticalAlignment_Source}
	${OpenInfraPlatform_Infrastructure_Bindings_Source}
	${OpenInfraPlatform_Infrastructure_Core_Source}
	${OpenInfraPlatform_Infrastructure_CrossSection_Source}
	${OpenInfraPlatform_Infrastructure_DigitalElevationModel_Source}
	${OpenInfraPlatform_Infrastructure_SectionedSolid_Source}
	${OpenInfraPlatform_Infrastructure_Girder_Source}
	${OpenInfraPlatform_Infrastructure_SlabField_Source}
	${OpenInfraPlatform_Infrastructure_Tessellation_Source}
	${OpenInfraPlatform_Infrastructure_EnergyConsumption_Source}
	${OpenInfraPlatform_Infrastructure_EnergyConsumption_Calculators_Source_Source}
	${OpenInfraPlatform_Infrastructure_EnergyConsumption_Calculators_Parameters_Source}
	${OpenInfraPlatform_Infrastructure_EnergyConsumption_Profiles_Source}
	${OpenInfraPlatform_Infrastructure_Export_Source}
	${OpenInfraPlatform_Infrastructure_IfcPL_Source}
	${OpenInfraPlatform_Infrastructure_Import_Source}
	${OpenInfraPlatform_Infrastructure_PointCloudProcessing_Source}
	${OpenInfraPlatform_Infrastructure_Source}
)


if(OIP_USE_PREBUILD_EARLYBINDING_LIBS)		
	target_link_libraries( OpenInfraPlatform.Infrastructure			
		${OpenInfraPlatform_IfcRoad_LIBRARY}
		${OpenInfraPlatform_IfcAlignment1x1_LIBRARY}
		${OpenInfraPlatform_IfcAlignment_LIBRARY}
		Rpcrt4.lib
		# Boost
		${Boost_LIBRARIES}
		# BlueFramework
		${BLUEFRAMEWORK_LIBRARIES}
		# Python
		${PYTHON_LIBRARIES}
		# External libs
		QtXlsxWriter
		${LIBLAS_LIBRARIES}
		# Oklabi
		${OKLABI_LIBRARIES}
		#
		${QHULL_STATIC_LIBRARIES}
		)
else(OIP_USE_PREBUILD_EARLYBINDING_LIBS)
	target_link_libraries( OpenInfraPlatform.Infrastructure
		OpenInfraPlatform.IfcAlignment
		OpenInfraPlatform.IfcAlignment1x1
		OpenInfraPlatform.IfcRoad
		# Boost
		${Boost_LIBRARIES}		
		# BlueFramework
		${BLUEFRAMEWORK_LIBRARIES}	
		# Python
		${PYTHON_LIBRARIES}
		# External libs
		QtXlsxWriter
		${LIBLAS_LIBRARIES}
		# Oklabi
		${OKLABI_LIBRARIES}
		#
		${QHULL_STATIC_LIBRARIES}
	)
endif(OIP_USE_PREBUILD_EARLYBINDING_LIBS)

# Use the Widgets module from Qt 5.
qt5_use_modules(OpenInfraPlatform.Infrastructure Xml XmlPatterns)

install(TARGETS OpenInfraPlatform.Infrastructure   
   RUNTIME DESTINATION bin
   COMPONENT oip_runtime
)

install(TARGETS OpenInfraPlatform.Infrastructure   
   ARCHIVE DESTINATION lib
   COMPONENT oip_import_libs
)
