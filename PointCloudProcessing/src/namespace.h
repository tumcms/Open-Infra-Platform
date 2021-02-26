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

#pragma once
#ifndef OpenInfraPlatform_PointCloudProcessing_16452b8b_ee1f_4293_ac34_7c7e66b5395c_h
#define OpenInfraPlatform_PointCloudProcessing_16452b8b_ee1f_4293_ac34_7c7e66b5395c_h

#define OIP_NAMESPACE_OPENINFRAPLATFORM_POINTCLOUDPROCESSING_BEGIN \
	namespace OpenInfraPlatform {                            \
		namespace PointCloudProcessing {

#define OIP_NAMESPACE_OPENINFRAPLATFORM_POINTCLOUDPROCESSING_END }}

       
#ifdef BLUEINFRASTRUCTURE_EXPORT
#	if BLUE_PLATFORM == BLUE_PLATFORM_WINDOWS
#		define BLUEINFRASTRUCTURE_API __declspec(dllexport)
#	else
#		define BLUEINFRASTRUCTURE_API
#	endif
#else
#	define BLUEINFRASTRUCTURE_API
#	if BLUE_PLATFORM == BLUE_PLATFORM_WINDOWS && BLUE_ARCHITECTURE_TYPE == BLUE_ARCHITECTURE_64 && BLUE_COMPILER == BLUE_COMPILER_MSVC
#   endif
#endif

#endif // end define OpenInfraPlatform_Infrastructure_BlueInfrastructure_16452b8b_ee1f_4293_ac34_7c7e66b5395c_h




