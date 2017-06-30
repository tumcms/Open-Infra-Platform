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
#ifndef OpenInfraPlatform_Infrastructure_HorizontalAlignmentElement2DArbitraryCurve_f536b9fa_a17e_44fb_a769_40207e65828c_h
#define OpenInfraPlatform_Infrastructure_HorizontalAlignmentElement2DArbitraryCurve_f536b9fa_a17e_44fb_a769_40207e65828c_h

#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2D.h"
#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"
#include <BlueFramework/Core/PropertySet.h>

namespace IArbitraryTransitionCurve {
	class IArbitraryTransitionCurve {
	public:
		virtual double getLength() const = 0;

		virtual buw::Vector2d getPostion(const double lerpParamter) const = 0;

		virtual double getCurvature(const double lerpParamter) const = 0;
	};
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

class BLUEINFRASTRUCTURE_API HorizontalAlignmentElement2DArbitraryCurve : public HorizontalAlignmentElement2D {
public:
	HorizontalAlignmentElement2DArbitraryCurve(const buw::Vector2d& start,
	                                           const buw::Vector2d& end,
	                                           const buw::Vector2d& pi,
	                                           const double length,
	                                           const double radiusStart,
	                                           const double radiusEnd,
	                                           const bool clockwise);

	virtual ~HorizontalAlignmentElement2DArbitraryCurve();

	virtual buw::Vector2d getPosition(const double lerpParameter) const override;

	virtual buw::Vector2d getTangent(const double lerpParameter) const override;

	virtual buw::Vector2d getNormal(const double lerpParameter) const override;

	virtual buw::Vector2d getStartPosition() const override;

	virtual buw::Vector2d getEndPosition() const override;

	virtual double getLength() const;

	virtual bool genericQuery(const int id, void* result) const override;

	virtual eHorizontalAlignmentType getAlignmentType() const override;

private:
	class HorizontalAlignmentElement2DArbitraryCurveImpl;                  // Forward declaration of internal class
	std::unique_ptr<HorizontalAlignmentElement2DArbitraryCurveImpl> impl_; // Opaque pointer to implementation
};                                                                         // end class HorizontalAlignmentElement2DArbitraryCurve

class BLUEINFRASTRUCTURE_API HorizontalAlignmentElement2DIfcPLArbitraryTransitionCurve : public HorizontalAlignmentElement2D {
public:
	HorizontalAlignmentElement2DIfcPLArbitraryTransitionCurve(const buw::Vector2d startPosition,
	                                                          const double startDirection,
	                                                          const double startCurvature,
	                                                          const bool counterClockwise,
	                                                          const double clothoidConstant,
	                                                          const bool entry,
	                                                          const double length);

	virtual buw::Vector2d getPosition(const double lerpParameter) const override;

	virtual buw::Vector2d getTangent(const double lerpParameter) const override;

	virtual buw::Vector2d getNormal(const double lerpParameter) const override;

	virtual buw::Vector2d getStartPosition() const override;

	virtual buw::Vector2d getEndPosition() const override;

	virtual double getLength() const override;

	virtual eHorizontalAlignmentType getAlignmentType() const override;

private:
	buw::PropertySet properties_;

	IArbitraryTransitionCurve::IArbitraryTransitionCurve* atc_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw {
	using OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DArbitraryCurve;
	using OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DIfcPLArbitraryTransitionCurve;
}

#endif // end define OpenInfraPlatform_Infrastructure_HorizontalAlignmentElement2DArbitraryCurve_f536b9fa_a17e_44fb_a769_40207e65828c_h
