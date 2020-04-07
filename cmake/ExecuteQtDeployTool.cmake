if(WIN32)
	# Unit tests need access to Qt DLLs and resources - this project copies this stuff to the right place
	add_custom_target(ExecuteQtDeployTool
				
		COMMAND  ${Qt5Core_DIR}/../../../bin/windeployqt.exe --no-system-d3d-compiler --force --debug ${CMAKE_BINARY_DIR}/Debug/OpenInfraPlatform.UI.exe
		COMMAND  ${Qt5Core_DIR}/../../../bin/windeployqt.exe --no-system-d3d-compiler --force --pdb ${CMAKE_BINARY_DIR}/Debug/OpenInfraPlatform.UI.exe
		#COMMAND  ${Qt5Core_DIR}/../../../bin/windeployqt.exe --no-system-d3d-compiler --force --release ${CMAKE_BINARY_DIR}/RelWithDebInfo/OpenInfraPlatform.UI.exe
		#COMMAND  ${Qt5Core_DIR}/../../../bin/windeployqt.exe --no-system-d3d-compiler --force --release ${CMAKE_BINARY_DIR}/Release/OpenInfraPlatform.UI.exe
	)
endif()
