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

#pragma once

#include <EXPRESS.h>

#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"
#include "OpenInfraPlatform/Infrastructure/namespace.h"
#include <BlueFramework/Rasterizer/vertex.h>
#include <boost/noncopyable.hpp>
#include <vector>
#include <string>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

struct accidentReportDescription {
	buw::Vector3d position;
	std::string roadName;
};

class BLUEINFRASTRUCTURE_API ProxyModel {
public:
	ProxyModel();

	virtual ~ProxyModel();
	
	void setIfc4x1Entities(std::map<int, std::shared_ptr<OpenInfraPlatform::ExpressBinding::EXPRESSEntity> > entities);

	bool hasIfc4x1Data();

	const std::map<int, std::shared_ptr<OpenInfraPlatform::ExpressBinding::EXPRESSEntity> >& getIfc4x1Data() const;;

	// Each car accident has a unique id 
	int addAccidentReport(const accidentReportDescription& c );

	int getAccidentReportCount();

	void removeAccidentReportAt(const int index);

	const accidentReportDescription& getAccidentReportByIndex(const int index) const;

private:
	std::vector<accidentReportDescription> accidentReports_;

	// IFC4x1 entities
	std::map<int, std::shared_ptr<OpenInfraPlatform::ExpressBinding::EXPRESSEntity> > Ifc4x1Entities_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw {
	using OpenInfraPlatform::Infrastructure::accidentReportDescription;
	using OpenInfraPlatform::Infrastructure::ProxyModel;
}
