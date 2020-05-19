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

#pragma once

#include "DataManagement/General/Data.h"
#include "IfcGeometryConverter\ConverterBuw.h"
//#include "OpenInfraPlatform/Infrastructure/Alignment/AlignmentModel.h"
//#include "OpenInfraPlatform/Infrastructure/DigitalElevationModel/DigitalElevationModel.h"
//#include "OpenInfraPlatform/Infrastructure/ProxyModel/ProxyModel.h"

#include <boost/noncopyable.hpp>

namespace OpenInfraPlatform 
{
	namespace Core 
	{
		namespace DataManagement 
		{
				class /*BLUEINFRASTRUCTURE_API*/ Export : private boost::noncopyable
				{
				public:
					Export(buw::ReferenceCounted<OpenInfraPlatform::Core::IfcGeometryConverter::IfcGeometryModel> igm, const std::string& filename);

				protected:
					buw::ReferenceCounted<OpenInfraPlatform::Core::IfcGeometryConverter::IfcGeometryModel> ifcGeometryModel_;
					std::string filename_;
				};
	
		} // end namespace DataManagement
	} // end namespace Core
} // end namespace OpenInfraPlatform

namespace buw 
{
	using OpenInfraPlatform::Core::DataManagement::Export;
}