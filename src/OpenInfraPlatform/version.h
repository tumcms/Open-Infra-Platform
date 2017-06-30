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
#ifndef OpenInfraPlatform_version_8381e70b_23e7_421b_aebc_017552d70cec_h
#define OpenInfraPlatform_version_8381e70b_23e7_421b_aebc_017552d70cec_h

#include <boost/noncopyable.hpp>
#include <string>

namespace OpenInfraPlatform
{
	
static const std::string	NAME         		= std::string("TUM Open Infra Platfrom");

static const int      		VERSION_MAJOR		= 1;
static const int      		VERSION_MINOR		= 0;
static const int            VERSION_BUILD 		= 0; // 0 for alpha, 1 for beta, 2 for release candidate, 3 for (final) release
static const int			VERSION_REVISION    = 1933;

static const std::string	VERSION_STR = std::string { 
										std::to_string(VERSION_MAJOR) + "." + 
										std::to_string(VERSION_MINOR) + "." + 
										std::to_string(VERSION_BUILD) + "." + 
										std::to_string(VERSION_REVISION) 
							};

#if BLUE_DEBUG
static const std::string    VERSION_BUILD_TAG   = std::string("debug");
#else
static const std::string    VERSION_BUILD_TAG   = std::string("release");
#endif

#if   BLUE_ARCHITECTURE_TYPE == BLUE_ARCHITECTURE_32
static const std::string    VERSION_ARCH_TAG   = std::string("x86");
#elif BLUE_ARCHITECTURE_TYPE == BLUE_ARCHITECTURE_64
static const std::string    VERSION_ARCH_TAG   = std::string("x64");
#endif

} // end namespace OpenInfraPlatform

// namespace buw already contains those (from BlueFramework-2.4.624\Core\src\BlueFramework\Core\version.h)
/*
namespace buw
{
	using OpenInfraPlatform::NAME;
	using OpenInfraPlatform::VERSION_MAJOR;
	using OpenInfraPlatform::VERSION_MINOR;
	using OpenInfraPlatform::VERSION_REVISION;
	using OpenInfraPlatform::VERSION_STR;
	using OpenInfraPlatform::VERSION_ARCH_TAG;
	using OpenInfraPlatform::VERSION_BUILD_TAG;
}
*/

#endif // end define OpenInfraPlatform_version_8381e70b_23e7_421b_aebc_017552d70cec_h