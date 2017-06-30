if(NOT ZLIB_FOUND AND NOT ZLIB_ROOT)
	find_path(ZLIB_ROOT NAMES NAMES test/minigzip.c adler32.c zlib.h PATHS ${ZLIB_INSTALL_DIR}/zlib-1.2.11 HINTS "C:\\thirdparty\\vs2015\\x64\\zlib-1.2.11")
endif()

if(ZLIB_ROOT)
	find_library(ZLIB_LIBRARY_DEBUG NAMES zlibstaticd.lib PATHS ${ZLIB_ROOT}/build/Debug)
	find_library(ZLIB_LIBRARY_RELEASE NAMES zlibstatic.lib PATHS ${ZLIB_ROOT}/build/Release)
	
	find_path(ZLIB_INCLUDE_DIR NAMES zlib.h PATHS ${ZLIB_ROOT})
	set(ZLIB_LIBRARY debug "${ZLIB_LIBRARY_DEBUG}" optimized "${ZLIB_LIBRARY_RELEASE}")
endif()