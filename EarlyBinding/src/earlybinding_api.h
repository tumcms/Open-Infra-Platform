/*
    Copyright (c) 2021 Technical University of Munich
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


#	if defined(_WIN32) || defined(WIN32) // we are on windows
#       if defined (OIP_EARLYBINDING_API_EXPRESS_ASEXPORT) // only defined with OpenInfraPlatform.Express.Lib project
#           define OIP_EARLYBINDING_API_EXPRESS __declspec(dllexport)
#       else // otherwise it is linked into as a DLL (all other projects)
#           define OIP_EARLYBINDING_API_EXPRESS __declspec(dllimport)
#       endif
#		if defined (OIP_EARLYBINDING_API_ZERO_ASEXPORT) // only defined with OpenInfraPlatform.IFC??.Zero projects
#			define OIP_EARLYBINDING_API_ZERO __declspec(dllexport)
#		else // otherwise it is linked into as a DLL (all other projects)
#			define OIP_EARLYBINDING_API_ZERO __declspec(dllimport)
#		endif
#		if defined (OIP_EARLYBINDING_API_BOT_ASEXPORT) // only defined with OpenInfraPlatform.IFC??.Bot projects
#			define OIP_EARLYBINDING_API_BOT __declspec(dllexport)
#		else // otherwise it is linked into as a DLL (all other projects)
#			define OIP_EARLYBINDING_API_BOT __declspec(dllimport)
#		endif
#		if defined (OIP_EARLYBINDING_API_MID_ASEXPORT) // only defined with OpenInfraPlatform.IFC??.Mid projects
#			define OIP_EARLYBINDING_API_MID __declspec(dllexport)
#		else // otherwise it is linked into as a DLL (all other projects)
#			define OIP_EARLYBINDING_API_MID __declspec(dllimport)
#		endif
#		if defined (OIP_EARLYBINDING_API_TOP_ASEXPORT) // only defined with OpenInfraPlatform.IFC??.Top projects
#			define OIP_EARLYBINDING_API_TOP __declspec(dllexport)
#		else // otherwise it is linked into as a DLL (all other projects)
#			define OIP_EARLYBINDING_API_TOP __declspec(dllimport)
#		endif
#       if defined (OIP_EARLYBINDING_API_MAIN_ASEXPORT) // only defined with OpenInfraPlatform.Express.Lib project
#           define OIP_EARLYBINDING_API_MAIN __declspec(dllexport)
#       else // otherwise it is linked into as a DLL (all other projects)
#           define OIP_EARLYBINDING_API_MAIN __declspec(dllimport)
#       endif
#	elif defined(UNIX) // we are on linux //20.08.20: added but not tested
#       define OIP_EARLYBINDING_API_EXPRESS
#		define OIP_EARLYBINDING_API_ZERO
#		define OIP_EARLYBINDING_API_BOT 
#		define OIP_EARLYBINDING_API_MID 
#		define OIP_EARLYBINDING_API_TOP 
#		define OIP_EARLYBINDING_API_MAIN
#	endif

#if !defined (OIP_EARLYBINDING_EXTERN)
	#if defined(__cplusplus) // we are compiling with c++ compiler
		#define OIP_EARLYBINDING_EXTERN extern "C"
	#else // we are on C //20.08.20: added but not tested
		#define OIP_EARLYBINDING_EXTERN extern
	#endif
#endif
