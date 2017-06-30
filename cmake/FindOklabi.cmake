# - Try to find Oklabi lib
#
# Once done this will define
#
#  OKLABI_FOUND - system has eigen lib with correct version
#  OKLABI_VERSION - Oklabi version

set(OKLABI_VERSION "20161209")
find_path(OKLABI_ROOT_DIR 
    NAMES OklabiKern1464.dll
    PATHS "C:\\thirdparty\\vs2015\\x64"
    HINTS "C:\\thirdparty\\vs2015\\x64\\Oklabi_20161209"
    PATH_SUFFIXES gdal_data
	REQUIRED
)

macro(findLIB LIB)
	find_file(OKLABI_${LIB}_LIBRARY Oklabi${LIB}.lib PATHS ${OKLABI_ROOT_DIR} )
	set(OKLABI_LIBRARIES ${OKLABI_LIBRARIES} "${OKLABI_${LIB}_LIBRARY}")
endmacro()

macro(findDLL LIB)
	find_file(OKLABI_${LIB}_DLL Oklabi${LIB}.dll PATHS ${OKLABI_ROOT_DIR} )
	if("${OKLABI_${LIB}_DLL}" STREQUAL "OKLABI_${LIB}_DLL-NOTFOUND")
		MESSAGE(STATUS "Couldn't find Oklabi${LIB}.dll, trying with different suffix.")		
		string(REPLACE "_i" "" OKLABI_NAME_DLL "Oklabi${LIB}.dll")
		find_file(OKLABI_${LIB}_DLL ${OKLABI_NAME_DLL} PATHS ${OKLABI_ROOT_DIR})		
		if("${OKLABI_${LIB}_DLL}" STREQUAL "OKLABI_${LIB}_DLL-NOTFOUND")
			MESSAGE(ERROR "Can't find corresponding DLL")
			set(OKALBI_FOUND False)
		else()
			MESSAGE(STATUS "Found ${OKLABI_${LIB}_DLL}")
		endif()
	endif()
	set(OKLABI_DLLS ${OKLABI_DLLS} ${OKLABI_${LIB}_DLL})
endmacro()

if(OKLABI_FIND_COMPONENTS)
	set(OKLABI_COMPONENTS ${OKLABI_FIND_COMPONENTS})
else(OKLABI_FIND_COMPONENTS)
	set(OKLABI_COMPONENTS Kern1464 _JNI1464 COM1464 Gdal1464_i Geos1464_c_i Libiconv1464 Proj1464_i StdC1464 Tar1464 Util1464 Zlib1464)
endif(OKLABI_FIND_COMPONENTS)

set(OKLABI_FOUND True)
foreach(COMP ${OKLABI_COMPONENTS})
	findLIB(${COMP})
	findDLL(${COMP})
endforeach()

function(OKLABI_COPY_BINARIES TargetDirectory)
	add_custom_target(OklabiCopyBinaries
		COMMENT "Copying Oklabi binaries to '${TargetDirectory}'" VERBATIM
		COMMAND ${CMAKE_COMMAND} -E copy ${OKLABI_DLLS} ${TargetDirectory}/Debug
		COMMAND ${CMAKE_COMMAND} -E copy ${OKLABI_DLLS} ${TargetDirectory}/Release
		COMMAND ${CMAKE_COMMAND} -E copy ${OKLABI_DLLS} ${TargetDirectory}/RelWithDebInfo
		
		COMMAND	${CMAKE_COMMAND} -E copy_directory ${OKLABI_ROOT_DIR}/res 		${TargetDirectory}/Debug/res
		COMMAND	${CMAKE_COMMAND} -E copy_directory ${OKLABI_ROOT_DIR}/schema 	${TargetDirectory}/Debug/schema
		COMMAND	${CMAKE_COMMAND} -E copy_directory ${OKLABI_ROOT_DIR}/fbliste	${TargetDirectory}/Debug/fbliste
		COMMAND	${CMAKE_COMMAND} -E copy_directory ${OKLABI_ROOT_DIR}/res		${TargetDirectory}/Release/res
		COMMAND	${CMAKE_COMMAND} -E copy_directory ${OKLABI_ROOT_DIR}/schema	${TargetDirectory}/Release/schema
		COMMAND	${CMAKE_COMMAND} -E copy_directory ${OKLABI_ROOT_DIR}/fbliste	${TargetDirectory}/Release/fbliste
	)
endfunction(OKLABI_COPY_BINARIES)