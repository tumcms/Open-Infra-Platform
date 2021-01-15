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

#include <namespace.h>

#include "src\General\graph.h"

using namespace testing;

class Graph_Test : public Test {
    protected:
    virtual void SetUp() override {

    }

    virtual void TearDown() override {

    }

};

TEST_F(Graph_Test, AllLoopsIdentified_1) {
    // Arrange
    OpenInfraPlatform::ExpressBindingGenerator::Graph g1(5); 
    g1.addEdge(1, 0); 
    g1.addEdge(0, 2); 
    g1.addEdge(2, 1); 
    g1.addEdge(0, 3); 
    g1.addEdge(3, 4); 

    // Act
    auto scc = g1.SCC(); 

    // Assert
	// result should be
	// 4
	// 3
	// 1 2 0
    EXPECT_THAT(scc.size(), 3);

    EXPECT_THAT(scc[0].size(), 1);
    EXPECT_THAT(scc[0].front(), 4);

    EXPECT_THAT(scc[1].size(), 1);
    EXPECT_THAT(scc[1].front(), 3);
    
    ASSERT_THAT(scc[2].size(), 3);
	std::vector<size_t> cmp({ 1,2,0 });
	std::list<size_t>::iterator it = scc[2].begin();
	for( int i=0 ; it != scc[2].end(); it++, i++ )
		EXPECT_THAT(*it, cmp.at(i));

    // Annihilate
}
