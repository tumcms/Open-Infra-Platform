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
#ifndef OpenInfraPlatform_Infrastructure_VerticalAlignmentElement2D_521307f1_b2a5_46f2_9d0f_2b9c744fc5bc_h
#define OpenInfraPlatform_Infrastructure_VerticalAlignmentElement2D_521307f1_b2a5_46f2_9d0f_2b9c744fc5bc_h

#include "OpenInfraPlatform/Infrastructure/Alignment/types.h"
#include "OpenInfraPlatform/Infrastructure/Core/IQueryable.h"
#include "OpenInfraPlatform/Infrastructure/Core/Line2.h"
#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"
#include <BlueFramework/Core/Math/vector.h>
#include <BlueFramework/Core/memory.h>
#include <boost/noncopyable.hpp>
#include <iostream>

namespace OpenInfraPlatform {
	namespace Infrastructure {
		enum class eVerticalAlignmentType { Line, Arc, Parabola, Unknown };

		BLUEINFRASTRUCTURE_API std::ostream& operator<<(std::ostream& os, const eVerticalAlignmentType vat);
		BLUEINFRASTRUCTURE_API std::string verticalAlignmentTypeToString(const eVerticalAlignmentType type);

		class BLUEINFRASTRUCTURE_API VerticalAlignmentElement2D : public OpenInfraPlatform::Infrastructure::IQueryable {
		public:
			//! Get a point on the alignment element.
			/*!
			    \param[in]	lerpParameter	A paramter of [0;1] where 0
			    \returns
			*/
			virtual buw::Vector2d getPosition(const Stationing station) const = 0;

			//! Should return the same value as getPositon(getStartStation));
			virtual buw::Vector2d getStartPosition() const = 0;

			//! Should return the same value as getPositon(getEndStation));
			virtual buw::Vector2d getEndPosition() const = 0;

			virtual Stationing getStartStation() const = 0;

			virtual Stationing getEndStation() const = 0;

			//! Determines the type of the horizontal alignment element.
			virtual eVerticalAlignmentType getAlignmentType() const;
			;

			//! A generic Query
			virtual bool genericQuery(const int /*id*/, void* /*result*/) const;
		};

		BLUEINFRASTRUCTURE_API std::ostream& operator<<(std::ostream& os, buw::ReferenceCounted<VerticalAlignmentElement2D> vae);
	} // end namespace Infrastructure
} // end namespace OpenInfraPlatform

namespace buw {
	using OpenInfraPlatform::Infrastructure::verticalAlignmentTypeToString;
	using OpenInfraPlatform::Infrastructure::eVerticalAlignmentType;
	using OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2D;
}

#endif // end define OpenInfraPlatform_Infrastructure_VerticalAlignmentElement2D_521307f1_b2a5_46f2_9d0f_2b9c744fc5bc_h
