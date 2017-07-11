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

#ifndef __RAILING_H_CDF60130BDB74E008EF218179045C693__
#define __RAILING_H_CDF60130BDB74E008EF218179045C693__

#include <OpenInfraPlatform/Infrastructure/namespace.h>
#include <OpenInfraPlatform/Infrastructure/OIPInfrastructure.h>
#include "SlabFieldElement.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

class BLUEINFRASTRUCTURE_API Railing : public SlabFieldElement
{
public:
	explicit Railing(int const id, std::wstring const& name);
	virtual ~Railing();
};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw
{
	using OpenInfraPlatform::Infrastructure::Railing;
}

#endif // __RAILING_H_CDF60130BDB74E008EF218179045C693__
