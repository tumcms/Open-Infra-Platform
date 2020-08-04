/*
Copyright (c) 2018 Technical University of Munich
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

int main(int argc, char **argv) {
	int result = 0;

	try {
		::testing::InitGoogleTest(&argc, argv);

		result = RUN_ALL_TESTS();
	}
	catch (const std::exception &e) {
		std::cout << "Unit test crashed..." << e.what() << std::endl;
	}

	if( result )
	{
		// only pause for user input if the result is not 0 ( != OK )
		std::cout << "Observe the results." << std::endl;
		std::cout << "Press Enter to exit ...";
		getchar();
	}

	return result;
}