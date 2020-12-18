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


#include "OffModel.h"
#include "Exception\UnhandledException.h"

void OpenInfraPlatform::Core::OffConverter::OffModel::reset()
{
	geometry_.reset();
}

void OpenInfraPlatform::Core::OffConverter::OffModel::addVertices(std::vector<buw::Vector3d> vertices)
{
	for (const auto& vertex : vertices)
		geometry_.vertices.push_back(vertex);
	geometry_.UpdateBBox();
}

void OpenInfraPlatform::Core::OffConverter::OffModel::addIndices(std::vector<uint32_t> indices)
{
	for (const auto& index : indices)
		geometry_.indices.push_back(index);
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------
// Interface IModel implementation
bool OpenInfraPlatform::Core::OffConverter::OffModel::isEmpty() const
{
	if (!geometry_.isEmpty())
		return false;
	return true;
}

std::string OpenInfraPlatform::Core::OffConverter::OffModel::getSource() const
{
	return filename_;
}

oip::BBox OpenInfraPlatform::Core::OffConverter::OffModel::getExtent()
{
	oip::BBox bb;
	bb.update(geometry_.bb);
	return bb;
}

oip::GeorefMetadata OpenInfraPlatform::Core::OffConverter::OffModel::getGeorefMetadata() const
{
	throw oip::UnhandledException("OffGeometryModel::getGeorefMetadata()");
}

void OpenInfraPlatform::Core::OffConverter::OffModel::transformAllPoints(
	const oip::GeorefMetadata& newGeorefMetadata,
	std::function<std::tuple<double,double,double> const(double,double,double)>& transf
)
{
	throw oip::UnhandledException("OffGeometryModel::transformAllPoints()");
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------

void OpenInfraPlatform::Core::OffConverter::OffModel::setFilename(const std::string& filename)
{
	filename_ = filename;
}