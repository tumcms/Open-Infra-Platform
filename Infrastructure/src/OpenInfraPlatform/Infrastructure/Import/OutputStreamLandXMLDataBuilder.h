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

#pragma once
#ifndef OpenInfraPlatform_Infrastructure_OutputStreamLandXMLDataBuilder_829f8d4c_5a1b_4a3a_9876_c554e355d6e5_h
#define OpenInfraPlatform_Infrastructure_OutputStreamLandXMLDataBuilder_829f8d4c_5a1b_4a3a_9876_c554e355d6e5_h

#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"
#include "OpenInfraPlatform/Infrastructure/Import/ImportLandXml.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/IAlignment3D.h"
#include <boost/noncopyable.hpp>
#include <ostream>

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		class BLUEINFRASTRUCTURE_API OutputStreamLandXMLDataBuilder : public OpenInfraPlatform::Infrastructure::LandXMLDataBuilder
		{
		public:
			OutputStreamLandXMLDataBuilder(std::ostream& out);

			virtual void createAlignment(const PropertySet& parameters) override;

			virtual void createCoordGeom() override;

			virtual void createLine(const PropertySet& parameters) override;

			virtual void createCurve(const PropertySet& parameters) override;

			virtual void createSpiral(const PropertySet& parameters) override;

			virtual void createProfAlign(const PropertySet& parameters) override;

			virtual void createPVI(const PropertySet& parameters) override;

			virtual void createParaCurve(const PropertySet& parameters) override;

			virtual void createCircCurve(const PropertySet& parameters) override;

			virtual void createSurface(const PropertySet& parameters, const LandXMLSurface& surface) override;

			virtual void createCrossSectionSurf(const PropertySet& parameters) override;

			virtual void createDesignCrossSectSurf(const PropertySet& parameters) override;

			virtual void createCrossSectPnt(const PropertySet& parameters) override;

		private:
			std::ostream& out;
		};
	} // end namespace Infrastructure
} // end namespace BlueFramework

namespace buw
{
	using OpenInfraPlatform::Infrastructure::OutputStreamLandXMLDataBuilder;
}

#endif // end define OpenInfraPlatform_Infrastructure_OutputStreamLandXMLDataBuilder_829f8d4c_5a1b_4a3a_9876_c554e355d6e5_h
