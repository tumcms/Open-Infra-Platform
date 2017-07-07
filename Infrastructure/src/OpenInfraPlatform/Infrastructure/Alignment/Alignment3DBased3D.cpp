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

#include "Alignment3DBased3D.h"
#include <BlueFramework/Core/Math/util.h>

#include <iomanip>      // std::setprecision

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

void Alignment3DBased3D::addPoint( const buw::Vector3d& p )
{
	if (type_ == Alignment3DBased3DType::Spline)
		crs_.AddSplinePoint(p);
	else if (type_ == Alignment3DBased3DType::Polyline)
		polyline_.AddPoint(p);
	else
		assert(false);
}

buw::Vector3d const& Alignment3DBased3D::getPoint(size_t const idx) const
{
	if (type_ == Alignment3DBased3DType::Spline)
		return crs_.GetNthPoint(idx);
	else if (type_ == Alignment3DBased3DType::Polyline)
		return polyline_.GetNthPoint(idx);
	else
		assert(false);

	return buw::Vector3d();
}

size_t Alignment3DBased3D::getNumPoints() const
{
	if (type_ == Alignment3DBased3DType::Spline)
		return crs_.GetNumPoints();
	else if (type_ == Alignment3DBased3DType::Polyline)
		return polyline_.GetNumPoints();
	else
		assert(false);

	return 0;
}

double Alignment3DBased3D::getLength() const 
{
	if (type_ == Alignment3DBased3DType::Spline)
		return crs_.Length();
	else if (type_ == Alignment3DBased3DType::Polyline)
		return polyline_.Length();
	else
		assert(false);
}

buw::Stationing Alignment3DBased3D::getEndStation() const 
{
	return startSation_ + getLength();
}

buw::Stationing Alignment3DBased3D::getStartStation() const {
	return startSation_;
}

buw::Vector3d Alignment3DBased3D::getPosition( const Stationing station ) const {
	double length = getEndStation() - getStartStation();
	double t = station / length;
	t = buw::clamp(t, 0.0, 1.0);
	if (type_ == Alignment3DBased3DType::Spline)
		return crs_.GetInterpolatedSplinePoint(t);
	else if (type_ == Alignment3DBased3DType::Polyline)
		return polyline_.Interpolate(t);
	else
		return buw::Vector3d(0.0, 0.0, 0.0);
}

Alignment3DBased3D::~Alignment3DBased3D() {

}

Alignment3DBased3D::Alignment3DBased3D(const Stationing startSation, Alignment3DBased3DType type) :
	IAlignment3D(e3DAlignmentType::e3DBased),
	startSation_(startSation),
	type_(type)
{

}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END
