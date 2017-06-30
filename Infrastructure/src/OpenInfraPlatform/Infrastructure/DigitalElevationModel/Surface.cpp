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

#include "OpenInfraPlatform/Infrastructure/DigitalElevationModel/Surface.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

Surface::Surface()
{
	clear();
}

Surface::~Surface()
{

}

void Surface::clear()
{
	points_.clear();
	triangeIndices_.clear();
	boundsMin_ = buw::Vector3d::Ones() * std::numeric_limits<double>::max();
	boundsMax_ = buw::Vector3d::Ones() * std::numeric_limits<double>::min();
}

void Surface::addPoint(const buw::Vector3d& p)
{
	updateBounds(p);
	points_.push_back(p);
}

void Surface::updateBounds(const buw::Vector3d& p)
{
	boundsMin_[0] = std::min(boundsMin_[0], p[0]);
	boundsMin_[1] = std::min(boundsMin_[1], p[1]);
	boundsMin_[2] = std::min(boundsMin_[2], p[2]);

	boundsMax_[0] = std::max(boundsMax_[0], p[0]);
	boundsMax_[1] = std::max(boundsMax_[1], p[1]);
	boundsMax_[2] = std::max(boundsMax_[2], p[2]);
}

double Surface::sign(buw::Vector2d p1, buw::Vector2d p2, buw::Vector2d p3) const
{
	return (p1.x() - p3.x()) * (p2.y() - p3.y()) - (p2.x() - p3.x()) * (p1.y() - p3.y());
}

bool Surface::pointInTriangle(buw::Vector2d& pt, int faceID) const
{
	buw::Vector3i face = triangeIndices_[faceID];
	buw::Vector2d v1 = points_[face[0]].block<2,1>(0,0);
	buw::Vector2d v2 = points_[face[1]].block<2,1>(0,0);
	buw::Vector2d v3 = points_[face[2]].block<2,1>(0,0);

	bool b1, b2, b3;

	b1 = sign(pt, v1, v2) < 0.0f;
	b2 = sign(pt, v2, v3) < 0.0f;
	b3 = sign(pt, v3, v1) < 0.0f;

	return ((b1 == b2) && (b2 == b3));
}

double Surface::zRay(buw::Vector2d& xy, int faceID) const
{
	buw::Vector3i face = triangeIndices_[faceID];
	buw::Vector3d v0 = points_[face[0]];
	buw::Vector3d v1 = points_[face[1]];
	buw::Vector3d v2 = points_[face[2]];

	buw::Vector3d u = (v1 - v0);
	buw::Vector3d v = (v2 - v0);
	buw::Vector2d w = xy - v0.block<2,1>(0,0);

	double uv = u.block<2, 1>(0, 0).dot(v.block<2, 1>(0, 0));
	double wv = w.dot(v.block<2,1>(0,0));
	double vv = v.block<2, 1>(0, 0).dot(v.block<2, 1>(0, 0));
	double wu = w.dot(u.block<2, 1>(0, 0));
	double uu = u.block<2, 1>(0, 0).dot(u.block<2, 1>(0, 0));

	double denominator = (uv * uv - uu * vv);

	double s = (uv * wv - vv * wu) / denominator;
	double t = (uv * wu - uu * wv) / denominator;

	return v0.z() + s * u.z() + t * v.z();
}

double Surface::getZ(buw::Vector2d& xy) const
{
	for (int i = 0; i < getTriangleCount(); i++)
	{
		if (pointInTriangle(xy, i))
		{
			return zRay(xy, i);
		}
	}
	return 0;
}

bool Surface::contains(buw::Vector2d& p) const
{
	return boundsMin_[0] < p[0] && boundsMin_[1] < p[1] &&
		boundsMax_[0] > p[0] && boundsMax_[1] > p[1];
}

void Surface::addTriangle(const buw::Vector3i& indices)
{
	triangeIndices_.push_back(indices);
}

int Surface::getPointCount() const
{
	return static_cast<int>(points_.size());
}

Surface* OpenInfraPlatform::Infrastructure::Surface::createFlatCopy(const OpenInfraPlatform::Infrastructure::Surface& src)
{
	return new Surface(src);
}

const char* Surface::getName() const
{
	return name_.c_str();
}

buw::Vector3d Surface::getBoundsMax() const
{
	return boundsMax_;
}

buw::Vector3d Surface::getBoundsMin() const
{
	return boundsMin_;
}

void Surface::setName(const char* str)
{
	name_ = std::string(str);
}

const std::vector<buw::Vector3d>&
Surface::getPoints() const
{
	return points_;
}

const std::vector<buw::Vector3i>& 
Surface::getTriangeFaces() const
{
	return triangeIndices_;
}

int Surface::getTriangleCount() const
{
	return static_cast<int>(triangeIndices_.size());
}

void Surface::setPoints(const std::vector<buw::Vector3d>& points)
{
	boundsMin_ = buw::Vector3d::Ones() * std::numeric_limits<double>::max();
	boundsMax_ = buw::Vector3d::Ones() * std::numeric_limits<double>::min();

	for (int i = 0; i < points.size(); i++)
	{
		updateBounds(points[i]);
	}

	points_ = points;
}

bool Surface::validate() const
{
	for (int i = 0; i < triangeIndices_.size(); i++)
	{
		const buw::Vector3i& indices = triangeIndices_[i];

		if (indices[0] < 0 || indices[0] >= points_.size())
			return false;

		if (indices[1] < 0 || indices[1] >= points_.size())
			return false;

		if (indices[2] < 0 || indices[2] >= points_.size())
			return false;
	}

	return true;
}

void Surface::setTriangles(const std::vector<buw::Vector3i>& indices)
{
	triangeIndices_ = indices;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END