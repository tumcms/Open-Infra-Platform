/*
    Copyright (c) 2021 Technical University of Munich
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

#include "boost\filesystem.hpp"

#include <namespace.h>

using namespace testing;

class Schema_UT_v2_Test : public Test {
    protected:
    virtual void SetUp() override {

    }

    virtual void TearDown() override {

    }

	// see https://stackoverflow.com/questions/2802188/file-count-in-a-directory-using-c
	size_t getNumberOfFilesInFolder(const std::string& directoryPath, const bool countDirectoriesAsWell)
	{
		if (countDirectoriesAsWell)
			return std::distance(boost::filesystem::directory_iterator(directoryPath), boost::filesystem::directory_iterator());
		else
		{
			size_t i = 0;
			for (auto file : boost::filesystem::directory_iterator(directoryPath))
				if (!boost::filesystem::is_directory(file))
					i++;
			return i;
		}
	}

    const std::string filepathGenerated = "UnitTests/Generator/schema_UT_v2/Generated/src";

};

TEST_F(Schema_UT_v2_Test, AllFilesAreGenerated) {
	EXPECT_THAT(getNumberOfFilesInFolder(filepathGenerated, true), Eq(9));
	EXPECT_THAT(getNumberOfFilesInFolder(filepathGenerated, false), Eq(6));
	EXPECT_THAT(getNumberOfFilesInFolder(filepathGenerated + "/entity", false), Eq(28));
	EXPECT_THAT(getNumberOfFilesInFolder(filepathGenerated + "/reader", false), Eq(2));
	EXPECT_THAT(getNumberOfFilesInFolder(filepathGenerated + "/type", false), Eq(24));
}
