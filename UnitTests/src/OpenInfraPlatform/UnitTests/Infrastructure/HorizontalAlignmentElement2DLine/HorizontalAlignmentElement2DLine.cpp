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

#include "buw.OIPInfrastructure.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;

namespace {
	TEST(HorizontalAlignmentElement2DLine, getLength) {
		buw::Vector2d a(0, 0);
		buw::Vector2d b(1, 0);
		buw::Vector2d c(2, 0);

		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line1 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(a, b);
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line2 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(b, c);

		buw::ReferenceCounted<buw::HorizontalAlignment2D> ha = std::make_shared<buw::HorizontalAlignment2D>();
		ha->addElement(line1);
		ha->addElement(line2);

		EXPECT_NEAR(ha->getLength(), 2, 0.001);

		for (double s = 0.0f; s < ha->getLength(); s += 0.1) {
			EXPECT_NEAR(ha->getPosition(s).x(), s, 0.001);
		}
	}

	TEST(HorizontalAlignmentElement2DLine, getLength2) {
		buw::Vector2d a(0, 0);
		buw::Vector2d b(0, 1);
		buw::Vector2d c(0, 2);

		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line1 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(a, b);
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line2 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(b, c);

		buw::ReferenceCounted<buw::HorizontalAlignment2D> ha = std::make_shared<buw::HorizontalAlignment2D>();
		ha->addElement(line1);
		ha->addElement(line2);

		EXPECT_NEAR(ha->getLength(), 2, 0.001);

		for (double s = 0.0f; s < ha->getLength(); s += 0.1) {
			EXPECT_NEAR(ha->getPosition(s).y(), s, 0.001);
		}
	}
}