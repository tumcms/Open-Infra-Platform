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

#ifndef __TESSELLATION_H_76580AE86DC74786B51A1DAAA396053E__
#define __TESSELLATION_H_76580AE86DC74786B51A1DAAA396053E__

#include <OpenInfraPlatform/Infrastructure/namespace.h>
#include <OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignment2D.h>
#include <OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignment2D.h>
#include <OpenInfraPlatform/Infrastructure/Alignment/Alignment3DBased3D.h>

#include <BlueFramework/Core/Math/Vector.h>
#include <BlueFramework/Core/Math/constants.h>

#include <cmath>
#include <vector>
#include <functional>
#include <utility>
#include <stdexcept>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

namespace Tessellation
{
	// Utility function to convert a maximum segment error criterion into a minimum segment
	// crease angle error criterion for circles. For use with tessellateArc() for instance.
	// The maximum segment error is the largest (orthogonal) gap between the perfect circle
	// and a segment that approximates it. The minimum segment crease angle error is defined
	// as for tessellateArc(): The minimal segment crease allowed, where this is the inner
	// angle in radians between two discretisation segments of the arc.
	inline double circleMaxSegErr2minSegCrease(double const radius, double const maxSegErr)
	{
		if(radius <= 0.0)
			throw std::domain_error("The radius must be > 0.");
		if(maxSegErr <= 0.0 || maxSegErr >= radius)
			throw std::domain_error("The maximum segment error must be in ]0, radius[.");

		// Let e be the maximum segment error, a the minimum segment crease angle and r the
		// circle radius (sketch it!). Then
		// e = r - r*sin(a/2)   <=>   a = 2*asin(1-(e/r))
		return 2.0*asin(1.0 - (maxSegErr/radius));
	}

	// Tessellates a circle arc.
	// \param minSegCrease The minimal segment crease allowed, where this is the inner angle
	//                     in radians between two discretisation segments of the arc. Values
	//                     close to Pi result in a very dense, thus exact tessellation of the
	//                     arc. The default value for instance, results in two arc points
	//                     between start and end for a quarter circle, thus the arc has a total
	//                     of four points. Must be in [0, Pi[.
	void tessellateArc(
		buw::Vector2d const& start,
		buw::Vector2d const& end,
		buw::Vector2d const& center,
		bool const bCCW,
		std::vector<buw::Vector2d>& positionsOut,
		std::vector<buw::Vector2d>* normalsOut,
		double const minSegCreaseRAD = M_PI - ((M_PI/2) / (2 + 0.5)));

	// Tessellates a circle arc. The shortest possible arc from start to end is preferred.
	// \param minSegCrease Same as for the version above.
	void tessellateArc(
		buw::Vector2d const& start,
		buw::Vector2d const& end,
		double const radius,
		bool const bCCW,
		std::vector<buw::Vector2d>& positionsOut,
		std::vector<buw::Vector2d>* normalsOut,
		double const minSegCreaseRAD = M_PI - ((M_PI/2) / (2 + 0.5)));

	// Tessellates a 3D alignment given by its 2D components \parm horiz and \param vert.
	// \param evaluator is a custom callback that is used to get the sampled 3D point and
	// can thereby apply some transformations on it (if needed, e.g. add world offset).
	// However only affine transformations make sense because otherwise the tessellation
	// criterions (e.g. minimum segment crease angle for arcs) are not fulfilled anymore.
	void tessellate(
		double const dFrom,
		double const dTo,
		std::shared_ptr<buw::HorizontalAlignment2D> horiz,
		std::shared_ptr<buw::VerticalAlignment2D> vert,
		std::shared_ptr<buw::Alignment3DBased3D> alignmentOut,
		std::vector<std::pair<buw::Vector2d, buw::Vector2d>>* pHorizontalTangentsAndNormalsOut,
		std::function<buw::Vector3d(
			double /*dStation*/,
			std::shared_ptr<buw::HorizontalAlignment2D> /*same as horiz*/,
			std::shared_ptr<buw::VerticalAlignment2D> /*same as vert*/,
			std::pair<buw::Vector2d, buw::Vector2d>* /*optional pHorizontalTangentAndNormalOut*/)> const& evaluator,
		bool const bSkipFirst = false,
		bool const bSkipLast = false);
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

#endif // __TESSELLATION_H_76580AE86DC74786B51A1DAAA396053E__
