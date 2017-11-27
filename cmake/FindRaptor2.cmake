
find_path(RAPTOR2_ROOT_DIR include/raptor2/raptor2.h)

if(RAPTOR2_ROOT_DIR)
	find_path(RAPTOR2_INCLUDE_DIR raptor2/raptor2.h
		PATHS ${RAPTOR2_ROOT_DIR}/include)

	find_library(RAPTOR2_LIBRARY NAMES raptor2.lib	
		PATHS ${RAPTOR2_ROOT_DIR}/lib)
endif()


include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBXML2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(Raptor2  DEFAULT_MSG
                                  RAPTOR2_LIBRARY RAPTOR2_INCLUDE_DIR)

mark_as_advanced(LIBXML2_INCLUDE_DIR LIBXML2_LIBRARY )

set(RAPTOR2_LIBRARIES ${RAPTOR2_LIBRARY} )
set(RAPTOR2_INCLUDE_DIRS ${RAPTOR2_INCLUDE_DIR} )