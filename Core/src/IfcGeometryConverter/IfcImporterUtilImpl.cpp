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

#ifdef OIP_MODULE_EARLYBINDING_IFC4X3_RC2
#include "EMTIFC4X3_RC2EntityTypes.h"
#include "IFC4X3_RC2Entities.h"
#endif

#include <tuple>
#include "IfcImporterUtilImpl.h"

//IFC4x3_RC2 specifics
#ifdef OIP_MODULE_EARLYBINDING_IFC4X3_RC2
template <>
oip::EXPRESSReference<emt::IFC4X3_RC2EntityTypes::IfcGeometricRepresentationItem>
OpenInfraPlatform::Core::IfcGeometryConverter::IfcImporterUtilT<emt::IFC4X3_RC2EntityTypes>::getIfcLinearPositioningElementAxis(
	const oip::EXPRESSReference<emt::IFC4X3_RC2EntityTypes::IfcLinearPositioningElement>& linposel
)
{
	// check input
	if (linposel.expired())
		throw oip::ReferenceExpiredException(linposel);

	// in IFC4x3_RC2 -> Axis is a Select
	switch (linposel->Axis.which())
	{
	case 0: //IfcCurve
		return linposel->Axis.get<0>().as<emt::IFC4X3_RC2EntityTypes::IfcGeometricRepresentationItem>();
	case 1: //IfcLinearAxisWithInclination
		return linposel->Axis.get<1>()->Directrix.as<emt::IFC4X3_RC2EntityTypes::IfcGeometricRepresentationItem>();
	default:
		throw oip::UnhandledException(linposel);
	}
}
#endif
