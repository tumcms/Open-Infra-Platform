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
#ifndef OpenInfraPlatform_Infrastructure_LandXMLBaseTypes_b8936503_0da8_4a8a_a3cf_18346a7b1bcf_h
#define OpenInfraPlatform_Infrastructure_LandXMLBaseTypes_b8936503_0da8_4a8a_a3cf_18346a7b1bcf_h

#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"
#include <BlueFramework/Core/Math/vector.h>

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		enum class eProfAlignType
		{
			CircCurve,
			PVI,
			ParaCurve
		};

		struct BLUEINFRASTRUCTURE_API profAlignElement
		{
			profAlignElement()
			{
				length = 0;
				type = eProfAlignType::PVI;
			}

			eProfAlignType			type;

			// ParaCurve data
			double					length;
			buw::Vector2d			position;

			// CircCurve data
			double					radius;
		};
	} // end namespace Infrastructure
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::Infrastructure::eProfAlignType;
	using OpenInfraPlatform::Infrastructure::profAlignElement;
}

#endif // end define OpenInfraPlatform_Infrastructure_LandXMLBaseTypes_b8936503_0da8_4a8a_a3cf_18346a7b1bcf_h