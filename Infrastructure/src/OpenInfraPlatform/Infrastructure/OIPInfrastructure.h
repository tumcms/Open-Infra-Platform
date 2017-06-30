/*
    Copyright (c) 2017 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    TUM Open Infra Platform is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    TUM Open Infra Platform is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef OpenInfraPlatform_Infrastructure_16452b8b_ee1f_4293_ac34_7c7e66b5395c_h
#define OpenInfraPlatform_Infrastructure_16452b8b_ee1f_4293_ac34_7c7e66b5395c_h

//#include <BlueFramework/Core/platform.h> @TODO
       
#ifdef BLUEINFRASTRUCTURE_EXPORT
#	if BLUE_PLATFORM == BLUE_PLATFORM_WINDOWS
#		define BLUEINFRASTRUCTURE_API __declspec(dllexport)
#	else
#		define BLUEINFRASTRUCTURE_API
#	endif
#else
#	define BLUEINFRASTRUCTURE_API
#	if BLUE_PLATFORM == BLUE_PLATFORM_WINDOWS && BLUE_ARCHITECTURE_TYPE == BLUE_ARCHITECTURE_64 && BLUE_COMPILER == BLUE_COMPILER_MSVC
// try to link library automatically on Visual Studio 2010/2012/2013
// todo: find out which compiler we are using
// todo: find out if we use debug or release mode 
//#	pragma comment(lib, "BlueCored.lib")  
//#	pragma comment(lib, "BlueCore.lib")  
#   endif
#endif

#endif // end define OpenInfraPlatform_Infrastructure_BlueInfrastructure_16452b8b_ee1f_4293_ac34_7c7e66b5395c_h




