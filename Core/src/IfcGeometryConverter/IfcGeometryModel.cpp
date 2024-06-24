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


#include "IfcGeometryModel.h"
#include "Exception\UnhandledException.h"


void OpenInfraPlatform::Core::IfcGeometryConverter::IfcModel::reset() 
{ 
	for( auto geom : geometries_ ) 
		geom->reset(); 
}

void OpenInfraPlatform::Core::IfcGeometryConverter::IfcModel::addGeometry(std::shared_ptr<GeometryDescription> geometry)
{
	// lock the multithread access to the lists
	geometryMutex_.lock();

	// add to the list of geometries
	geometries_.push_back(geometry);

	// free the access to the lists
	geometryMutex_.unlock();
}

void OpenInfraPlatform::Core::IfcGeometryConverter::IfcModel::setExpressModel(std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSModel> expressModel)
{
	expressModel_ = expressModel;
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------
// Interface IModel implementation
bool OpenInfraPlatform::Core::IfcGeometryConverter::IfcModel::isEmpty() const
{
	for (auto geom : geometries_)
		if (!geom->isEmpty())
			return false;
	return true;
}

std::string OpenInfraPlatform::Core::IfcGeometryConverter::IfcModel::getSource() const
{
	return filename_;
}

oip::BBox OpenInfraPlatform::Core::IfcGeometryConverter::IfcModel::getExtent()
{
	oip::BBox bb;
	for (auto geom : geometries_)
		bb.update(geom->bb);
	return bb;
}

oip::GeorefMetadata OpenInfraPlatform::Core::IfcGeometryConverter::IfcModel::getGeorefMetadata() const
{
	return georefMeta_;
}

void OpenInfraPlatform::Core::IfcGeometryConverter::IfcModel::transformAllPoints(
	const oip::GeorefMetadata& newGeorefMetadata,
	std::function<std::tuple<double, double, double> const(double, double, double)>& transf
)
{
	throw oip::UnhandledException("IfcGeometryModel::transformAllPoints()");
}
