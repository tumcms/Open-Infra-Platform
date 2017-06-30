#-------------------------------------------------------------------
# This file is part of the CMake build system for OGRE
#     (Object-oriented Graphics Rendering Engine)
# For the latest info, see http://www.ogre3d.org/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# -----------------------------------------------------------------------------
# Find DirectX11 SDK
# Define:
# DirectX11_FOUND
# DirectX11_INCLUDE_DIRS
# DirectX11_LIBRARIES

if(WIN32) # The only platform it makes sense to check for DirectX11 SDK
	include(FindPkgMacros)
	findpkg_begin(DirectX12)

	# Windows Phone 8.1 SDK
	if(MSVC14)
		find_path(DirectX12_INCLUDE_DIR NAMES d3d12.h HINTS "C:/Program Files (x86)/Windows Kits/10/Include/10.0.10586.0/um" "C:/Program Files/Windows Kits/10/Include/10.0.10586.0/um")
		find_path(DirectX12_INCLUDE_DIR_SHARED NAMES dxgi1_4.h HINTS "C:/Program Files (x86)/Windows Kits/10/Include/10.0.10586.0/shared" "C:/Program Files/Windows Kits/10/Include/10.0.10586.0/shared")
		
		set(DirectX12_LibDirX86	"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10586.0/um/${MSVC_CXX_ARCHITECTURE_ID}")
		set(DirectX12_LibDirX64	"C:/Program Files/Windows Kits/10/Lib/10.0.10586.0/um/${MSVC_CXX_ARCHITECTURE_ID}")
		
		find_library(DirectX12_DXERR_LIBRARY NAMES DxErr HINTS ${DirectX12_LibDirX86} ${DirectX12_LibDirX64})
		find_library(DirectX12_DXGUID_LIBRARY NAMES dxguid HINTS ${DirectX12_LibDirX86} ${DirectX12_LibDirX64})
		find_library(DirectX12_DXGI_LIBRARY NAMES dxgi HINTS ${DirectX12_LibDirX86} ${DirectX12_LibDirX64})
		find_library(DirectX12_D3DCOMPILER_LIBRARY NAMES d3dcompiler HINTS ${DirectX12_LibDirX86} ${DirectX12_LibDirX64})
		find_library(DirectX12_D3D12_LIBRARY NAMES d3d12 HINTS ${DirectX12_LibDirX86} ${DirectX12_LibDirX64})
		find_library(DirectX12_D3DX12_LIBRARY NAMES d3dx12 HINTS  ${DirectX12_LibDirX86} ${DirectX12_LibDirX64})	

		set(DirectX_D3D12_LIBRARIES
			${DirectX12_D3D12_LIBRARY}
			${DirectX12_DXGI_LIBRARY}
			${DirectX12_DXGUID_LIBRARY}
			${DirectX12_D3DCOMPILER_LIBRARY})
		
		set(DirectX12_LIBRARY d3d12.lib dxgi.lib dxguid.lib d3dcompiler.lib) # in "C:/Program Files (x86)/Windows Phone Kits/8.1/lib/${MSVC_CXX_ARCHITECTURE_ID}/"	
	else() 

	# Get path, convert backslashes as ${ENV_DXSDK_DIR}
	getenv_path(DXSDK_DIR)
	getenv_path(DIRECTX_HOME)
	getenv_path(DIRECTX_ROOT)
	getenv_path(DIRECTX_BASE)

	# construct search paths
	set(DirectX12_PREFIX_PATH 
	"${DXSDK_DIR}" "${ENV_DXSDK_DIR}"
	"${DIRECTX_HOME}" "${ENV_DIRECTX_HOME}"
	"${DIRECTX_ROOT}" "${ENV_DIRECTX_ROOT}"
	"${DIRECTX_BASE}" "${ENV_DIRECTX_BASE}"
	"C:/apps_x86/Microsoft DirectX SDK*"
	"C:/Program Files (x86)/Microsoft DirectX SDK*"
	"C:/apps/Microsoft DirectX SDK*"
	"C:/Program Files/Microsoft DirectX SDK*"
	"$ENV{ProgramFiles}/Microsoft DirectX SDK*"
	)

	create_search_paths(DirectX12)
	# redo search if prefix path changed
	clear_if_changed(DirectX12_PREFIX_PATH
		DirectX12_LIBRARY
		DirectX12_INCLUDE_DIR
	)
  
	# dlls are in DirectX11_ROOT_DIR/Developer Runtime/x64|x86
	# lib files are in DirectX11_ROOT_DIR/Lib/x64|x86
	if(CMAKE_CL_64)
		set(DirectX12_LIBPATH_SUFFIX "x64")
	else(CMAKE_CL_64)
		set(DirectX12_LIBPATH_SUFFIX "x86")
	endif(CMAKE_CL_64)

	# look for D3D12 components
    find_path(DirectX12_INCLUDE_DIR NAMES d3d12.h HINTS ${DirectX12_INC_SEARCH_PATH})
    find_library(DirectX12_DXERR_LIBRARY NAMES DxErr HINTS ${DirectX12_LIB_SEARCH_PATH} PATH_SUFFIXES ${DirectX12_LIBPATH_SUFFIX})
	find_library(DirectX12_DXGUID_LIBRARY NAMES dxguid HINTS ${DirectX12_LIB_SEARCH_PATH} PATH_SUFFIXES ${DirectX12_LIBPATH_SUFFIX})
	find_library(DirectX12_DXGI_LIBRARY NAMES dxgi HINTS ${DirectX12_LIB_SEARCH_PATH} PATH_SUFFIXES ${DirectX12_LIBPATH_SUFFIX})
	find_library(DirectX12_D3DCOMPILER_LIBRARY NAMES d3dcompiler HINTS ${DirectX12_LIB_SEARCH_PATH} PATH_SUFFIXES ${DirectX12_LIBPATH_SUFFIX})
	find_library(DirectX12_D3D12_LIBRARY NAMES d3d12 HINTS ${DirectX12_LIB_SEARCH_PATH} PATH_SUFFIXES ${DirectX12_LIBPATH_SUFFIX})
	find_library(DirectX12_D3DX12_LIBRARY NAMES d3dx12 HINTS ${DirectX12_LIB_SEARCH_PATH} PATH_SUFFIXES ${DirectX12_LIBPATH_SUFFIX})	

	if (DirectX12_INCLUDE_DIR AND DirectX12_D3D12_LIBRARY)
	  set(DirectX12_D3D12_LIBRARIES ${DirectX12_D3D12_LIBRARIES}
	    ${DirectX12_D3D12_LIBRARY}
	    ${DirectX12_DXGI_LIBRARY}
        ${DirectX12_DXGUID_LIBRARY}
        ${DirectX12_D3DCOMPILER_LIBRARY}        	  
      )	
    endif ()
    if (DirectX12_D3DX12_LIBRARY)
        set(DirectX12_D3D12_LIBRARIES ${DirectX12_D3D12_LIBRARIES} ${DirectX12_D3DX12_LIBRARY})
    endif ()
    if (DirectX12_DXERR_LIBRARY)
        set(DirectX12_D3D12_LIBRARIES ${DirectX12_D3D12_LIBRARIES} ${DirectX12_DXERR_LIBRARY})
    endif ()

	set(DirectX12_LIBRARY 
		${DirectX12_D3D12_LIBRARIES} 
	)
	
	mark_as_advanced(DirectX12_D3D12_LIBRARY 
					 DirectX12_D3DX12_LIBRARY
					 DirectX12_DXERR_LIBRARY 
					 DirectX12_DXGUID_LIBRARY
					 DirectX12_DXGI_LIBRARY 
					 DirectX12_D3DCOMPILER_LIBRARY)	

	set(DirectX_D3D12_LIBRARIES ${DirectX12_D3D12_LIBRARIES})
					 
	endif () # Legacy Direct X SDK
	
	message(STATUS "D3D12: '${DirectX12_INCLUDE_DIR}', '${DirectX_D3D12_LIBRARIES}'")

	findpkg_finish(DirectX12)
	
endif(WIN32)