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
	TEST(HorizontalAlignmentElement2DArc, getPosition)
	{
		using namespace buw;

		Vector2d center(0, 0);
		Vector2d start(1, 0);
		Vector2d end_(0, 1);
		bool cw = false;

		buw::ReferenceCounted<HorizontalAlignmentElement2DArc> arc = std::make_shared<HorizontalAlignmentElement2DArc>(center, start, end_, cw);
		buw::ReferenceCounted<HorizontalAlignment2D> ha = std::make_shared<HorizontalAlignment2D>();
		ha->addElement(arc);

		EXPECT_NEAR(ha->getLength(), buw::constantsd::pi() * 1.0 * (90.0 / 180.0), 0.001);

		for (double s = 0.0f; s < ha->getLength(); s += 0.1)
		{
			EXPECT_TRUE(ha->getPosition(s).x() >= 0.0);
			EXPECT_TRUE(ha->getPosition(s).y() >= 0.0);
		}
	}

	TEST(HorizontalAlignmentElement2DArc, getLength)
	{
		using namespace buw;

		Vector2d center(0, 0);
		Vector2d start(1, 0);
		Vector2d end_(0, 1);
		bool cw = true;

		buw::ReferenceCounted<HorizontalAlignmentElement2DArc> arc = std::make_shared<HorizontalAlignmentElement2DArc>(center, start, end_, cw);
		buw::ReferenceCounted<HorizontalAlignment2D> ha = std::make_shared<HorizontalAlignment2D>();
		ha->addElement(arc);

		EXPECT_NEAR(ha->getLength(), buw::constantsd::pi() * 1.0 * (270.0 / 180.0), 0.001);
	}

	TEST(HorizontalAlignmentElement2DArc, getLength2)
	{
		using namespace buw;

		Vector2d center(0, 0);
		Vector2d start(2, 0);
		Vector2d end_(0, 2);
		bool cw = true;

		buw::ReferenceCounted<HorizontalAlignmentElement2DArc> arc = std::make_shared<HorizontalAlignmentElement2DArc>(center, start, end_, cw);
		buw::ReferenceCounted<HorizontalAlignment2D> ha = std::make_shared<HorizontalAlignment2D>();
		ha->addElement(arc);

		EXPECT_NEAR(ha->getLength(), buw::constantsd::pi() * 2.0 * (270.0 / 180.0), 0.001);
	}

	TEST(HorizontalAlignmentElement2DArc, getLength3)
	{
		using namespace buw;

		Vector2d   center(3513050.8723, 5516206.7060);
		Vector2d   start(3513037.9591, 5516199.0738);
		Vector2d   end_(3513063.4562, 5516198.5423);
		bool cw = false;

		Vector2d	center2(50.8723, 206.7060);
		Vector2d	start2(37.9591, 199.0738);
		Vector2d	end_2(63.4562, 198.5423);

		buw::ReferenceCounted<HorizontalAlignmentElement2DArc> arc = std::make_shared<HorizontalAlignmentElement2DArc>(center, start, end_, cw);
		buw::ReferenceCounted<HorizontalAlignment2D> ha = std::make_shared<HorizontalAlignment2D>();
		ha->addElement(arc);

		buw::ReferenceCounted<HorizontalAlignmentElement2DArc> arc2 = std::make_shared<HorizontalAlignmentElement2DArc>(center, start, end_, cw);
		buw::ReferenceCounted<HorizontalAlignment2D> ha2 = std::make_shared<HorizontalAlignment2D>();
		ha2->addElement(arc2);

		auto v1 = start2 - center2;
		auto v2 = end_2 - center2;

		EXPECT_NEAR(ha->getLength(), ha2->getLength(), 0.001);
	}
}