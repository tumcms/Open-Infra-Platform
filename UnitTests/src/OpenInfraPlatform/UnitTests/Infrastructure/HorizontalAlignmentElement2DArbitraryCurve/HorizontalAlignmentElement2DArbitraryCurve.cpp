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

#include <string>
#include <iostream>
using namespace std;
#include "gtest/gtest.h"

#include <BlueFramework/Core/Math/vector.h>
#include <BlueFramework/Core/Math/quaternion.h>
#include <BlueFramework/Core/Math/util.h>
#include <BlueFramework/Core/Math/matrix.h>

#include "buw.OIPInfrastructure.h"

namespace
{
	TEST(HorizontalAlignmentElement2DArbitraryCurve, getPosition)
	{
		using namespace buw;

		// test data
		buw::Vector2d start = buw::Vector2d(861.369007, 537.722476);
		buw::Vector2d end = buw::Vector2d(930.775243, 503.483954);
		buw::Vector2d pi = buw::Vector2d(896.290146, 516.54507);

		double length = 77.500241;
		double radiusStart = 500;
		double radiusEnd = 367;
		bool clockwise = false;

		buw::ReferenceCounted<HorizontalAlignmentElement2DArbitraryCurve> a = std::make_shared<HorizontalAlignmentElement2DArbitraryCurve>(
			start,
			end,
			pi,
			length,
			radiusStart,
			radiusEnd,
			clockwise
		);

		// trivial tests
		EXPECT_NEAR(a->getLength(), length, 0.001);
		EXPECT_NEAR(buw::distance(start, a->getPosition(0)), 0.0, 0.001);
		EXPECT_NEAR(buw::distance(end, a->getPosition(1)), 0.0, 0.001);

		double startCurvature = 0;
		if (radiusStart != 0 && radiusStart != std::numeric_limits<double>::infinity())
			startCurvature = 1 / radiusStart;

		double endCurvature = 0;
		if (radiusEnd != 0 && radiusEnd != std::numeric_limits<double>::infinity())
			endCurvature = 1 / radiusEnd;

		double startDirection = buw::HorizontalAlignmentElement2DClothoid::computeStartDirection(start, pi);
		double clothoidConstant = buw::HorizontalAlignmentElement2DClothoid::computeClothoidConstant(length, startCurvature, endCurvature);
		bool entry = buw::HorizontalAlignmentElement2DClothoid::computeEntry(startCurvature, endCurvature);

		buw::clothoidDescription desc(start, startDirection, startCurvature, !clockwise, clothoidConstant, entry, length);
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> c =
			std::make_shared<buw::HorizontalAlignmentElement2DClothoid>(desc);

		buw::Vector2d calculatedStartPoint = c->getPosition(0);
		buw::Vector2d test1 = c->getPosition(0.3);
		buw::Vector2d test2 = c->getPosition(0.5);
		buw::Vector2d test3 = c->getPosition(0.7);
		buw::Vector2d calculatedEndPoint = c->getPosition(1);

		buw::Vector2d calculatedStartPoint2 = a->getPosition(0);
		buw::Vector2d test1_arb = a->getPosition(0.3);
		buw::Vector2d test2_arb = a->getPosition(0.5);
		buw::Vector2d test3_arb = a->getPosition(0.7);
		buw::Vector2d calculatedEndPoint_arb = a->getPosition(1);

		EXPECT_NEAR(buw::distance(calculatedStartPoint, calculatedStartPoint2), 0.0, 0.001);
		EXPECT_NEAR(buw::distance(test1, test1_arb), 0.0, 0.001);
		EXPECT_NEAR(buw::distance(test2, test2_arb), 0.0, 0.001);
		EXPECT_NEAR(buw::distance(test3, test3_arb), 0.0, 0.001);
		EXPECT_NEAR(buw::distance(calculatedEndPoint, calculatedEndPoint_arb), 0.0, 0.001);
	}

	TEST(HorizontalAlignmentElement2DArbitraryCurve, getPosition2)
	{
		// test data
		buw::Vector2d start = buw::Vector2d(4468141.633883, 5333462.303922);
		buw::Vector2d end = buw::Vector2d(4468161.038359, 5333457.490118);
		buw::Vector2d pi = buw::Vector2d(4468151.242887, 5333460.115737);
		double length = 19.993861;
		double radiusStart = 504.7;
		double radiusEnd = 550;
		bool clockwise = true;

		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DArbitraryCurve> a = std::make_shared<buw::HorizontalAlignmentElement2DArbitraryCurve>(
			start,
			end,
			pi,
			length,
			radiusStart,
			radiusEnd,
			clockwise
			);

		double startCurvature = 0;
		if (radiusStart != 0 && radiusStart != std::numeric_limits<double>::infinity())
			startCurvature = 1 / radiusStart;

		double endCurvature = 0;
		if (radiusEnd != 0 && radiusEnd != std::numeric_limits<double>::infinity())
			endCurvature = 1 / radiusEnd;

		double startDirection = buw::HorizontalAlignmentElement2DClothoid::computeStartDirection(start, pi);
		double clothoidConstant = buw::HorizontalAlignmentElement2DClothoid::computeClothoidConstant(length, startCurvature, endCurvature);
		bool entry = buw::HorizontalAlignmentElement2DClothoid::computeEntry(startCurvature, endCurvature);

		buw::clothoidDescription desc(start, startDirection, startCurvature, !clockwise, clothoidConstant, entry, length);
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> c =
			std::make_shared<buw::HorizontalAlignmentElement2DClothoid>(desc);

		buw::Vector2d test3 = c->getPosition(0.7);
		buw::Vector2d test3_arb = a->getPosition(0.7);

		buw::Vector2d calculatedEndPoint_arb = a->getPosition(1);
	}
}