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

//#include "buw.BlueCore.h"
//#include "buw.BlueImageProcessing.h"
//#include "buw.BlueEngine.h"
#include <BlueFramework/Core/string.h>
#include <vector>

namespace OpenInfraPlatform
{
	namespace UnitTesting
	{
		struct testDescription
		{
			buw::String LandXMLFile;
			buw::String screenshotImageFilename;
			buw::String referenceImageFilename;
			buw::String differenceImageFilename;
		};

		class ImageTester
		{
		public:
			ImageTester() :
				allTestSucceeded_(true)
			{

			}

			void writeTestHomepage();

			void createTest(const testDescription& td);

			bool testImage(
				const buw::String& screenshotImageFilename, 
				const buw::String& referenceImageFilename,
				const buw::String& differenceImageFilename);

			bool didAllTestSucceed() const;

		private:
			std::vector<testDescription>	testDesciptions_;
			bool							allTestSucceeded_;

		};
	}
}

namespace buw
{
	using OpenInfraPlatform::UnitTesting::testDescription;
	using OpenInfraPlatform::UnitTesting::ImageTester;
}