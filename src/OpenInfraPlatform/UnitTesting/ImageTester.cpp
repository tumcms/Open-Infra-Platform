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

#include "ImageTester.h"

//#include "buw.BlueCore.Diagnostics.GraphicsCardInfo.h"
#include <fstream>
#include <BlueFramework/ImageProcessing/Image.h>


void OpenInfraPlatform::UnitTesting::ImageTester::writeTestHomepage()
{
	std::ofstream htmlPage("test_report.html");

	//buw::GraphicsCardInfo gci;
	

	htmlPage << "<head>";
	htmlPage << "</head>";
	htmlPage << "<body>";
	
	htmlPage << "<h2>Current graphics card</h2> <br/>" << std::endl;
	htmlPage << "<b>Name: </b>" << /*gci.getName().toCString()*/ "Not available" << "<br/>" << std::endl;

	for (int i = 0; i < testDesciptions_.size(); i++)
	{
		htmlPage << "<h2>" << testDesciptions_[i].LandXMLFile << "</h2> <br/>" << std::endl;
		htmlPage << "<img src=\"" << testDesciptions_[i].referenceImageFilename << "\"> " << std::endl;
		htmlPage << "<img src=\"" << testDesciptions_[i].screenshotImageFilename << "\">" << std::endl;
		htmlPage << "<img src=\"" << testDesciptions_[i].differenceImageFilename << "\"> <br/>" << std::endl;
	}

	htmlPage << "Test";
	htmlPage << "</body>";

	htmlPage.close();
}

void OpenInfraPlatform::UnitTesting::ImageTester::createTest(const testDescription& td)
{
	testDesciptions_.push_back(td);
	testImage(td.screenshotImageFilename, td.referenceImageFilename, td.differenceImageFilename);
}

bool OpenInfraPlatform::UnitTesting::ImageTester::testImage(const buw::String& screenshotImageFilename, const buw::String& referenceImageFilename, const buw::String& differenceImageFilename)
{
	/*buw::ReferenceCounted<buw::Image3b> screenshotImage = buw::loadImageFromFile<buw::Image3b>(screenshotImageFilename);
	buw::ReferenceCounted<buw::Image3b> referenceImage = buw::loadImageFromFile<buw::Image3b>(referenceImageFilename);
	buw::Color3b diffColor(255, 0, 0);
	buw::ReferenceCounted<buw::Image3b> diffImage = buw::createDifferenceImage(screenshotImage, referenceImage, &diffColor[0]);

	buw::storeImageAsFile(differenceImageFilename, diffImage.get());

	float mse = buw::MSE_PerceptionBased(referenceImage, screenshotImage);

	if (mse > 0.00001f)
	{
		BLUE_LOG_STREAM_EX("UnitTest", buw::eLogSeverityLevel::Error) << "Screenshot is not equal to reference image.";

		allTestSucceeded_ = false;

		return false;
	}
	else
		return true;*/
	return true;
}

bool OpenInfraPlatform::UnitTesting::ImageTester::didAllTestSucceed() const
{
	return allTestSucceeded_;
}
