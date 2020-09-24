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


#include "IfcGeometryModel.h"
#include "Exception\UnhandledException.h"

void OpenInfraPlatform::Core::IfcGeometryConverter::IfcGeometryModel::reset() 
{ 
	bb_.reset(); 
	meshDescription_.reset(); 
	polylineDescription_.reset(); 
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------
// Interface IModel implementation
bool OpenInfraPlatform::Core::IfcGeometryConverter::IfcGeometryModel::isEmpty() const
{
	return (meshDescription_.isEmpty() && polylineDescription_.isEmpty());
}

oip::BBox OpenInfraPlatform::Core::IfcGeometryConverter::IfcGeometryModel::getExtent()
{
	return bb_;
}

std::string OpenInfraPlatform::Core::IfcGeometryConverter::IfcGeometryModel::getEPSGcode() const
{
	throw oip::UnhandledException("IfcGeometryModel::getEPSGcode()");
}

void OpenInfraPlatform::Core::IfcGeometryConverter::IfcGeometryModel::transformAllPoints(
	const std::string& newEPSGcode,
	std::function<std::tuple<double, double, double> const(double, double, double)>& transf
)
{
	throw oip::UnhandledException("IfcGeometryModel::transformAllPoints()");
}