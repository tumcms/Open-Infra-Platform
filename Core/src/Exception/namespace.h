/*
    Copyright (c) 2018 Technical University of Munich
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
#ifndef OpenInfraPlatform_Core_Exception_namespace_25e962e7_f00e_4cea_9f58_659100998a16_h
#define OpenInfraPlatform_Core_Exception_namespace_25e962e7_f00e_4cea_9f58_659100998a16_h
#if !defined OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_EXCEPTION_BEGIN
#define OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_EXCEPTION_BEGIN \
namespace OpenInfraPlatform { \
namespace Core { \
namespace Exception {
#endif
#if !defined OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_EXCEPTION_END
#define OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_EXCEPTION_END \
}\
}\
}
#endif
#if !defined EMBED_CORE_EXCEPTION_INTO_OIP_NAMESPACE
#define EMBED_CORE_EXCEPTION_INTO_OIP_NAMESPACE(X) \
namespace oip { \
using OpenInfraPlatform::Core::Exception::X; \
}
#endif
#endif // end define OpenInfraPlatform_Core_Exception_namespace_25e962e7_f00e_4cea_9f58_659100998a16_h
