set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	../Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	../Release)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG 	    ../Debug)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE 	    ../Release)

file(GLOB IfcBridgeGenerator_Source						src/*.*)
file(GLOB IfcBridgeGenerator_UserInterface_Source 		src/UserInterface/*.*)

set(IfcBridgeGenerator_UIS
	src/Forms/BridgeGenerator.ui
)

QT5_WRAP_UI(IfcBridgeGenerator_UIS_H ${IfcBridgeGenerator_UIS})

include_directories(
	${BLUEFRAMEWORK_INCLUDE_DIR}
	${Boost_INCLUDE_DIR}
	${CMAKE_CURRENT_BINARY_DIR} # Qt generated files will be located here
	../Ifc2x3/src
	../IfcAlignment/src
	../IfcBridge/src
	../IfcRoad/src
)	

add_executable(OpenInfraPlatform.IfcBridgeGenerator
	${IfcBridgeGenerator_UIS_H}
	${IfcBridgeGenerator_Source}
	${IfcBridgeGenerator_UserInterface_Source}
)

target_link_libraries(OpenInfraPlatform.IfcBridgeGenerator
		Qt5::WinMain
		${OpenInfraPlatform.EarlyBinding_LIBRARIES}
		Rpcrt4.lib
		# BlueFramework
		${BLUEFRAMEWORK_LIBRARIES}
)
	
install(TARGETS OpenInfraPlatform.IfcBridgeGenerator   
   RUNTIME DESTINATION bin
   COMPONENT oip_runtime
)
# Use the Widgets module from Qt 5.
qt5_use_modules(OpenInfraPlatform.IfcBridgeGenerator Widgets Xml XmlPatterns)
