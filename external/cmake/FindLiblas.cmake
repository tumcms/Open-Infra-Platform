if(NOT LIBLAS_ROOT)
	find_path(LIBLAS_ROOT NAMES liblas-osgeo4w-init.bat include/liblas/liblas.hpp HINTS "C:\\thirdparty\\vs2015\\x64\\libLAS-1.6-master" REQUIRED)
endif()
if(LIBLAS_ROOT)
	find_path(LIBLAS_INCLUDE_DIR NAMES liblas/liblas.hpp PATHS ${LIBLAS_ROOT}/include)
	find_library(LIBLAS_LIBRARY_RELEASE NAMES liblas.lib HINTS "${LIBLAS_ROOT}/build/bin/Release")
	find_library(LIBLAS_C_LIBRARY_RELEASE NAMES liblas_c.lib HINTS "${LIBLAS_ROOT}/build/bin/Release")
	find_library(LIBLAS_LIBRARY_DEBUG NAMES liblas.lib HINTS "${LIBLAS_ROOT}/build/bin/Debug")	
	find_library(LIBLAS_C_LIBRARY_DEBUG NAMES liblas_c.lib HINTS "${LIBLAS_ROOT}/build/bin/Debug")
	find_library(LIBLAS_LIBRARY_RELWITHDEBINFO NAMES liblas.lib HINTS "${LIBLAS_ROOT}/build/bin/RelWithDebInfo")
	find_library(LIBLAS_C_LIBRARY_RELWITHDEBINFO NAMES liblas_c.lib HINTS "${LIBLAS_ROOT}/build/bin/RelWithDebInfo")
	set(LIBLAS_LIB debug "${LIBLAS_LIBRARY_DEBUG}" optimized "${LIBLAS_LIBRARY_RELEASE}")
	set(LIBLAS_C_LIB debug "${LIBLAS_C_LIBRARY_DEBUG}" optimized "${LIBLAS_C_LIBRARY_RELEASE}")
endif()

function(LIBLAS_COPY_BINARIES TargetDirectory)
	add_custom_target(libLASCopyBinaries
		COMMENT "Copying libLAS binaries to '${TargetDirectory}'" VERBATIM
		COMMAND ${CMAKE_COMMAND} -E copy ${LIBLAS_ROOT}/build/bin/Debug/liblas.dll ${TargetDirectory}/Debug
		COMMAND ${CMAKE_COMMAND} -E copy ${LIBLAS_ROOT}/build/bin/Debug/liblas_c.dll ${TargetDirectory}/Debug
		COMMAND ${CMAKE_COMMAND} -E copy ${LIBLAS_ROOT}/build/bin/Release/liblas.dll ${TargetDirectory}/Release
		COMMAND ${CMAKE_COMMAND} -E copy ${LIBLAS_ROOT}/build/bin/Release/liblas_c.dll ${TargetDirectory}/Release
		COMMAND ${CMAKE_COMMAND} -E copy ${LIBLAS_ROOT}/build/bin/RelwithDebInfo/liblas.dll ${TargetDirectory}/RelwithDebInfo
		COMMAND ${CMAKE_COMMAND} -E copy ${LIBLAS_ROOT}/build/bin/RelwithDebInfo/liblas_c.dll ${TargetDirectory}/RelwithDebInfo
	)
endfunction(LIBLAS_COPY_BINARIES)