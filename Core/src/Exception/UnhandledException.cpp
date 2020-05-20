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

#include "UnhandledException.h"

OpenInfraPlatform::Core::Exception::UnhandledException::UnhandledException() noexcept
{
}

OpenInfraPlatform::Core::Exception::UnhandledException::UnhandledException(
    const UnhandledException& other) noexcept: item_(other.item_)
{
}

OpenInfraPlatform::Core::Exception::UnhandledException::UnhandledException(
    const std::shared_ptr<oip::EXPRESSObject>& item) noexcept
{
    item_ = item;
}


OpenInfraPlatform::Core::Exception::UnhandledException::~UnhandledException() noexcept
{
}

const char* OpenInfraPlatform::Core::Exception::UnhandledException::what() const noexcept
{
    std::string s = item_->getErrorLog() + ": IFC Entity not supported.";
    return s.c_str();
}
