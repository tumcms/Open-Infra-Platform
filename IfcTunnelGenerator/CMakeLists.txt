set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	../Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	../Release)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG 	    ../Debug)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE 	    ../Release)

file(GLOB IfcTunnelGenerator_Source						src/*.*)
file(GLOB IfcTunnelGenerator_UserInterface_Source 		src/UserInterface/*.*)

set(IfcTunnelGenerator_UIS
	src/Forms/TunnelGenerator.ui
)

QT5_WRAP_UI(IfcTunnelGenerator_UIS_H ${IfcTunnelGenerator_UIS})

include_directories(
	${BLUEFRAMEWORK_INCLUDE_DIR}
	${Boost_INCLUDE_DIR}
	${CMAKE_CURRENT_BINARY_DIR} # Qt generated files will be located here
	../Ifc2x3/src
	../Ifc4/src
	../IfcAlignment/src
	../IfcTunnel/src
	../IfcRoad/src
)	

add_executable(OpenInfraPlatform.IfcTunnelGenerator
	${IfcTunnelGenerator_UIS_H}
	${IfcTunnelGenerator_Source}
	${IfcTunnelGenerator_UserInterface_Source}
)

# Use the Widgets module from Qt 5.
qt5_use_modules(OpenInfraPlatform.IfcTunnelGenerator Widgets Xml XmlPatterns)

if(OIP_USE_PREBUILD_EARLYBINDING_LIBS)
	target_link_libraries(OpenInfraPlatform.IfcTunnelGenerator
		Qt5::WinMain
		${OpenInfraPlatform_IfcTunnel_LIBRARY}
		${OpenInfraPlatform_Ifc4_LIBRARY}
		Rpcrt4.lib
		# BlueFramework
		${BLUEFRAMEWORK_BLUECORE_LIBRARY}
		${BLUEFRAMEWORK_BLUEIMAGEPROCESSING_LIBRARY}
		${BLUEFRAMEWORK_BLUERASTERIZER_LIBRARY}
		${BLUEFRAMEWORK_BLUEENGINE_LIBRARY}
		${BLUEFRAMEWORK_BLUEGRAPHICSENGINE_LIBRARY}
		${BLUEFRAMEWORK_BLUEGL4XRENDERER_LIBRARY}
		${BLUEFRAMEWORK_BLUEAPPLICATION_LIBRARY}
	)
else()
	target_link_libraries(OpenInfraPlatform.IfcTunnelGenerator
		Qt5::WinMain
		OpenInfraPlatform.IfcTunnel
		OpenInfraPlatform.Ifc4
		${OpenInfraPlatform_IfcTunnel_LIBRARY}
		${OpenInfraPlatform_Ifc4_LIBRARY}
		# BlueFramework
		${BLUEFRAMEWORK_BLUECORE_LIBRARY}
		${BLUEFRAMEWORK_BLUEIMAGEPROCESSING_LIBRARY}
		${BLUEFRAMEWORK_BLUERASTERIZER_LIBRARY}
		${BLUEFRAMEWORK_BLUEENGINE_LIBRARY}
		${BLUEFRAMEWORK_BLUEGL4XRENDERER_LIBRARY}
		${BLUEFRAMEWORK_BLUEAPPLICATION_LIBRARY}	
	)
endif()

install(TARGETS OpenInfraPlatform.IfcTunnelGenerator   
   RUNTIME DESTINATION bin
   COMPONENT oip_runtime
)
