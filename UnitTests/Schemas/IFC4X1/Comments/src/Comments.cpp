/*
    Copyright (c) 2020 Technical University of Munich
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

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <EarlyBinding/IFC4X1/src/reader/IFC4X1Reader.h>
#include <namespace.h>

using namespace testing;

class CommentsTest : public Test {
protected:
    virtual void SetUp() override {
        express_model = OpenInfraPlatform::IFC4X1::IFC4X1Reader::FromFile(filename);
    }

    virtual void TearDown() override {
        express_model.reset();
    }


    const std::string filename = "UnitTests/Schemas/IFC4X1/Comments/Data/csg-primitive-commented.ifc";
    std::shared_ptr<oip::EXPRESSModel> express_model = nullptr;

};

TEST_F(CommentsTest, AllEntitiesAreRead) {
    EXPECT_THAT(express_model->entities.size(), Eq(31));
}
