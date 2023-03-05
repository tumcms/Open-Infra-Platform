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

#include "OsmDataModel.h"
#include <BBox.h>
#include "../Exception/UnhandledException.h"


void OpenInfraPlatform::Core::OsmDataConverter::OsmModel::reset()
{
	for (auto geometry : geometries_)
		geometry->reset();
}


void OpenInfraPlatform::Core::OsmDataConverter::OsmModel::addGeometry(std::shared_ptr<GeometryDescription> geometry)
{
	// lock the multithread access to the lists
	geometryMutex_.lock();

	// add to the list of geometries
	geometries_.push_back(geometry);

	// free the access to the lists
	geometryMutex_.unlock();
}


// ************************************************************************************************************************************************************
// Interface IModel implementation
// ************************************************************************************************************************************************************


bool OpenInfraPlatform::Core::OsmDataConverter::OsmModel::isEmpty() const
{
	for (auto geometry : geometries_)
		if (!geometry->isEmpty())
			return false;
	return true;
}


std::string OpenInfraPlatform::Core::OsmDataConverter::OsmModel::getSource() const
{
	return filename_;
}


oip::BBox OpenInfraPlatform::Core::OsmDataConverter::OsmModel::getExtent()
{
	oip::BBox bb;
	for (auto geometry : geometries_)
		bb.update(geometry->bb);
	return bb;
}


oip::GeorefMetadata OpenInfraPlatform::Core::OsmDataConverter::OsmModel::getGeorefMetadata() const
{
	throw oip::UnhandledException("OsmDataGeometryModel::getGeorefMetaData()");
}


void OpenInfraPlatform::Core::OsmDataConverter::OsmModel::transformAllPoints(
	const oip::GeorefMetadata& newGeorefMetadata, std::function<std::tuple<double, double, double> const(double, double, double)>& transf)
{
	throw oip::UnhandledException("OsmDataGeometryModel::transformAllPoints()");
}
