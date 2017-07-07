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
#ifndef OpenInfraPlatform_Infrastructure_Alignment3DBased3D_361647d9_ca33_4ef1_827e_ede8fb1f0a1e_h
#define OpenInfraPlatform_Infrastructure_Alignment3DBased3D_361647d9_ca33_4ef1_827e_ede8fb1f0a1e_h

#include "OpenInfraPlatform/Infrastructure/namespace.h"
#include "IAlignment3D.h"
#include "types.h"
#include "../Core/CatmullRomSpline.h"
#include "../Core/Polyline.h"
#include <boost/noncopyable.hpp>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

enum class Alignment3DBased3DType
{
	Spline,
	Polyline
};

class BLUEINFRASTRUCTURE_API Alignment3DBased3D : public buw::IAlignment3D
{
public:
	Alignment3DBased3D(const Stationing startSation, Alignment3DBased3DType type = Alignment3DBased3DType::Spline);

	virtual ~Alignment3DBased3D();

	//! Computes the 3d position given a stationing.
	buw::Vector3d			getPosition(const Stationing station ) const override;

	buw::Stationing			getStartStation() const override;

	buw::Stationing			getEndStation() const override;

	//! Length of horizontal alignment
	double					getLength() const override;	

	void					addPoint(const buw::Vector3d& p);
	buw::Vector3d const&	getPoint(size_t const idx) const;
	size_t					getNumPoints() const;

private:
	buw::Stationing	startSation_;

	Alignment3DBased3DType type_;
	CatmullRomSpline3d crs_;
	Polyline3d polyline_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw
{
	using OpenInfraPlatform::Infrastructure::Alignment3DBased3D;
	using OpenInfraPlatform::Infrastructure::Alignment3DBased3DType;
}

#endif // end define OpenInfraPlatform_Infrastructure_Alignment3DBased3D_361647d9_ca33_4ef1_827e_ede8fb1f0a1e_h
