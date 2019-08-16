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
#include "DataManagement/General/namespace.h"
#include <boost/noncopyable.hpp>

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_BEGIN

namespace DataManagement 
{
		class /*BLUEINFRASTRUCTURE_API*/ Import : private boost::noncopyable 
		{
		public:
			Import(const std::string& filename);
			buw::ReferenceCounted<OpenInfraPlatform::Core::IfcGeometryConverter::IfcGeometryModel> getIfcGeometryModel();

		protected:
			std::string filename_;
			buw::ReferenceCounted<OpenInfraPlatform::Core::IfcGeometryConverter::IfcGeometryModel> ifcGeometryModel_;
		};

	void Import(const std::string & filename);
}

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_END

namespace buw {
	using OpenInfraPlatform::Core::DataManagement::Import;
}
