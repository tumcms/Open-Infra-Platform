option(ZLIB_AUTOMATIC_INSTALL OFF)
find_path(ZLIB_INSTALL_DIR OPTIONAL)

if(ZLIB_AUTOMATIC_INSTALL AND ZLIB_INSTALL_DIR)
	execute_process(COMMAND "${PROJECT_SOURCE_DIR}/external/Build_zlib-1.2.11_Visual Studio 14 2015 Win64.cmd" ${ZLIB_INSTALL_DIR} "${CMAKE_COMMAND}" WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/external)
	find_path(ZLIB_ROOT NAMES NAMES test/minigzip.c adler32.c zlib.h PATHS ${ZLIB_INSTALL_DIR}/zlib-1.2.11	HINTS "C:\\thridparty\\vs2015\\x64\\zlib-1.2.11")
	set(ZLIB_AUTOMATIC_INSTALL OFF CACHE BOOL "Automatically install zlib" FORCE)
endif()