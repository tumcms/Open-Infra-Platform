if(NOT GTEST_ROOT)
		find_path(GTEST_ROOT NAMES googletest/include/gtest/gtest.h googlemock/include/gmock/gmock.h HINTS "C:\\thirdparty\\vs2015\\x64\\googletest-1.8.0" REQUIRED)
endif()
if(GTEST_ROOT)
	find_library(GTEST_LIBRARY NAMES gtest.lib HINTS "${GTEST_ROOT}/build/googlemock/gtest/Release/")
	find_library(GTEST_MAIN_LIBRARY NAMES gtest_main.lib HINTS "${GTEST_ROOT}/build/googlemock/gtest/Release/")
	find_library(GTEST_LIBRARY_DEBUG NAMES gtest.lib HINTS "${GTEST_ROOT}/build/googlemock/gtest/Debug/")
	find_library(GTEST_MAIN_LIBRARY_DEBUG NAMES gtest_main.lib HINTS "${GTEST_ROOT}/build/googlemock/gtest/Debug/")
	find_path(GTEST_INCLUDE_DIR NAMES gtest/gtest.h HINTS "${GTEST_ROOT}/googletest/include")
	if(GTEST_LIBRARY AND GTEST_LIBRARY_DEBUG)
		set(GTEST_LIBRARIES debug "${GTEST_LIBRARY_DEBUG}" optimized "${GTEST_LIBRARY}")
	endif()
	if(GTEST_MAIN_LIBRARY AND GTEST_MAIN_LIBRARY_DEBUG)
		set(GTEST_MAIN_LIBRARIES debug "${GTEST_MAIN_LIBRARY_DEBUG}" optimized "${GTEST_MAIN_LIBRARY}")
	endif()
endif()

function(GTEST_COPY_BINARIES TargetDirectory)
	add_custom_target(GTestCopyBinaries
		COMMENT "Copying googletest binaries to '${TargetDirectory}'" VERBATIM
		COMMAND ${CMAKE_COMMAND} -E copy ${GTEST_ROOT}/build/googlemock/gtest/Debug/gtest.dll ${TargetDirectory}/Debug
		COMMAND ${CMAKE_COMMAND} -E copy ${GTEST_ROOT}/build/googlemock/gtest/Debug/gtest_main.dll ${TargetDirectory}/Debug
		COMMAND ${CMAKE_COMMAND} -E copy ${GTEST_ROOT}/build/googlemock/gtest/Release/gtest.dll ${TargetDirectory}/Release
		COMMAND ${CMAKE_COMMAND} -E copy ${GTEST_ROOT}/build/googlemock/gtest/Release/gtest_main.dll ${TargetDirectory}/Release
		COMMAND ${CMAKE_COMMAND} -E copy ${GTEST_ROOT}/build/googlemock/gtest/RelWithDebInfo/gtest.dll ${TargetDirectory}/RelWithDebInfo
		COMMAND ${CMAKE_COMMAND} -E copy ${GTEST_ROOT}/build/googlemock/gtest/RelWithDebInfo/gtest_main.dll ${TargetDirectory}/RelWithDebInfo
	)
endfunction(GTEST_COPY_BINARIES)