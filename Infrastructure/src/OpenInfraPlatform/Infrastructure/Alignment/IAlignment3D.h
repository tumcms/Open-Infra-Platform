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
#ifndef OpenInfraPlatform_Infrastructure_IAlignment3D_f30b6bea_bf6e_4892_acc4_2b1f1952fe60_h
#define OpenInfraPlatform_Infrastructure_IAlignment3D_f30b6bea_bf6e_4892_acc4_2b1f1952fe60_h

#include "OpenInfraPlatform/Infrastructure/namespace.h"
#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"
#include "types.h"
#include <BlueFramework/Core/memory.h>
#include <BlueFramework/Core/Math/vector.h>
#include <BlueFramework/Core/string.h>
#include <boost/noncopyable.hpp>
#include <string>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

enum class e3DAlignmentType
{
	e2DBased,
	e3DBased,
	Unknown
};

class BLUEINFRASTRUCTURE_API IAlignment3D
{
public:
	IAlignment3D(const e3DAlignmentType type);

	virtual ~IAlignment3D();

	virtual buw::Vector3d	getPosition(const buw::Stationing station ) const = 0;
	virtual Stationing		getStartStation() const = 0;
	virtual Stationing		getEndStation() const = 0;
	virtual double			getLength() const = 0;

	//! Retrieve name of alignment
	buw::String				getName() const;

	//! Assign a name to the alignment
	void					setName(const std::string& name);
	void					setName(const std::wstring& name);

	e3DAlignmentType		getType() const;

protected:
	e3DAlignmentType		type_;

private:
	buw::String				name_;
}; // end class IAlignment3D

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw
{
	using OpenInfraPlatform::Infrastructure::e3DAlignmentType;
	using OpenInfraPlatform::Infrastructure::IAlignment3D;
}

#endif // end define OpenInfraPlatform_Infrastructure_IAlignment3D_f30b6bea_bf6e_4892_acc4_2b1f1952fe60_h
