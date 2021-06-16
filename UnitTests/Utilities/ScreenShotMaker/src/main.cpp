/*
    This file is part of TUM Open Infra Platform Early Binding EXPRESS
    Generator, a simple early binding generator for EXPRESS.
    Copyright (c) 2021 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    TUM Open Infra Platform Early Binding EXPRESS Generator is free
    software; you can redistribute it and/or modify it under the terms
    of the GNU General Public License Version 3 as published by the Free
    Software Foundation.

    TUM Open Infra Platform Early Binding EXPRESS Generator is
    distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

/* INSTRUCTIONS 

Usage:

> OpenInfraPlatform.ScreenShotMaker.exe <pathToIfcFile> -o <pathToOutputDirectory>

with:

- <pathToIfcFile>: the relative or absolute path to the IFC file to be rendered
- <pathToOutputDirectory>: the relative or absolute path to the directory where screen shots should be saved

*NOTE:* make sure that the correct IFC version is being compiled - select accordingly in CMake.

If you wish to debug, you should put the arguments in [Visual Studio]:
- OpenInfraPlatform.ScreenShotMaker project -> right mouse button
- Properties
- Debuggin
- Command Arguments

*/


#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string>
#include <iostream>
#include <vector>
#include <utility>

#include <boost/filesystem.hpp>

#include "tclap/CmdLine.h"

#include <buw.Engine.h>
#include <buw.ImageProcessing.h>

#include "IfcGeometryConverter\IfcPeekStepReader.h"
using OpenInfraPlatform::Core::IfcGeometryConverter::IfcPeekStepReader;

#include <IfcGeometryConverter/ConverterBuw.h>
#include <IfcGeometryConverter/IfcImporter.h>
#include <IfcGeometryConverter/IfcImporterImpl.h>

#include <IfcGeometryModelRenderer.h>

#ifdef OIP_MODULE_EARLYBINDING_IFC4X1
#include "EarlyBinding\IFC4X1\src\IFC4X1Entities.h"
#include "EarlyBinding\IFC4X1\src\EMTIFC4X1EntityTypes.h"
#endif

#ifdef OIP_MODULE_EARLYBINDING_IFC4X3_RC1
#include "EarlyBinding\IFC4X3_RC1\src\IFC4X3_RC1Entities.h"
#include "EarlyBinding\IFC4X3_RC1\src\EMTIFC4X3_RC1EntityTypes.h"
#endif

#ifdef OIP_MODULE_EARLYBINDING_IFC4X3_RC4
#include <EarlyBinding/IFC4X3_RC4/src/reader/IFC4X3_RC4Reader.h>
#include <EarlyBinding/IFC4X3_RC4/src/IFC4X3_RC4.h>
#endif


template <typename IfcEntityTypesT, class IfcReaderT>
buw::ReferenceCounted<IfcGeometryModelRenderer> setUpRenderer(
	const std::string& filename
)
{
	// https://docs.microsoft.com/de-de/windows/console/getconsolewindow
	HWND handle = GetConsoleWindow();

	buw::renderSystemDescription scd;
	scd.width = 640;
	scd.height = 480;
	scd.windowId = static_cast<void*>(handle);
	scd.forceWarpDevice = false;
	scd.enableMSAA = true;
	scd.renderAPI = BlueFramework::Rasterizer::eRenderAPI::Direct3D11;

	auto renderSystem_ = BlueFramework::Rasterizer::createRenderSystem(scd);

	auto rendererIfc = buw::makeReferenceCounted<IfcGeometryModelRenderer>(renderSystem_);

	auto express_model = IfcReaderT::FromFile(filename);

	auto importer = buw::makeReferenceCounted<oip::IfcImporterT<IfcEntityTypesT>>();
	auto model = importer->collectData(express_model);

	rendererIfc->setModel(model[0]);

	return rendererIfc;
}


void saveAllViews(
	const buw::ReferenceCounted<IfcGeometryModelRenderer>& renderer,
	const std::string& outputDirectoryName,
	const std::string& filename
)
{
	std::vector<std::pair< buw::eViewDirection, std::string >> views =
	{
		{ buw::eViewDirection::Front, "front"},
		{ buw::eViewDirection::Top, "top"},
		{ buw::eViewDirection::Bottom, "bottom"},
		{ buw::eViewDirection::Left, "left"},
		{ buw::eViewDirection::Right, "right"},
		{ buw::eViewDirection::Back, "back"},
        { buw::eViewDirection::FrontLeftBottom, "front_left_bottom" },
        { buw::eViewDirection::FrontRightBottom, "front_right_bottom" },
        { buw::eViewDirection::TopLeftFront, "top_left_front" },
        { buw::eViewDirection::TopFrontRight, "top_front_right" },
        { buw::eViewDirection::TopLeftBack, "top_left_back" },
        { buw::eViewDirection::TopRightBack, "top_right_back" },
        { buw::eViewDirection::BackLeftBottom, "back_left_bottom" },
        { buw::eViewDirection::RightBottomBack, "right_bottom_back" }
	};

	for( const auto& view : views )
	{
		renderer->setViewDirection( view.first );
		buw::Image4b image = renderer->captureImage();
		buw::storeImage(outputDirectoryName + "\\" + filename + "_" + view.second + ".png", image);

		std::cout << "Saved image " << std::endl;
		std::cout << outputDirectoryName + "\\" + filename + "_" + view.second + ".png" << std::endl;
	}
}


int main(int argc, char **argv) {
    try {
        TCLAP::CmdLine cmd("oipScreenShot", ' ', "0.1");

		TCLAP::UnlabeledValueArg<std::string> sourceFiles("i", "IFC file.", true, "./rectified", "string");
        cmd.add(sourceFiles);

		TCLAP::ValueArg<std::string> outputDirectory("o", "outputDir", "The output directory for figures.", true, "", "string");
        cmd.add(outputDirectory);

        // Parse the args.
        cmd.parse(argc, argv);

        // open a file handle to a particular file:

        const char* filepath = sourceFiles.getValue().c_str();
        std::string outputDirectoryName = outputDirectory.getValue();

		// check input
		boost::filesystem::path givenPathToFile(filepath);
		if (!boost::filesystem::exists(givenPathToFile))
			throw std::exception("Provided IFC file does not exist.");
		if (!boost::filesystem::exists(outputDirectoryName))
			throw std::exception("Provided output directory does not exist.");

		std::cout << "Generating screen shots from " << std::endl;
		std::cout << filepath << std::endl;
		std::cout << "Saving screen shots to " << std::endl;
		std::cout << outputDirectoryName << std::endl;

		std::string filename = givenPathToFile.stem().string();
		std::string filetype = givenPathToFile.extension().string();
		std::transform(filetype.begin(), filetype.end(), filetype.begin(), ::tolower);

		IfcPeekStepReader::IfcSchema ifcSchema;
		std::string strSchema;
		if (filetype == ".ifc" || filetype == ".stp")
		{
			std::tie(strSchema, ifcSchema) = IfcPeekStepReader::parseIfcHeader(filepath);
		}
		else
		{
			std::string msg("File type not IFC, but " + filetype);
			throw std::exception(msg.c_str());
		}

		buw::ReferenceCounted<IfcGeometryModelRenderer> renderer;
		if (ifcSchema == IfcPeekStepReader::IfcSchema::IFC4X1) {
#ifdef OIP_MODULE_EARLYBINDING_IFC4X1
			renderer =
				setUpRenderer<emt::IFC4X1EntityTypes, OpenInfraPlatform::IFC4X1::IFC4X1Reader>(filepath);
#else // OIP_MODULE_EARLYBINDING_IFC4X1
			throw std::exception("IFC4X1 not compiled");
#endif //OIP_MODULE_EARLYBINDING_IFC4X1
		}
		else if (ifcSchema == IfcPeekStepReader::IfcSchema::IFC4X3_RC1) {
#ifdef OIP_MODULE_EARLYBINDING_IFC4X3_RC1
			renderer =
				setUpRenderer<emt::IFC4X3_RC1EntityTypes, OpenInfraPlatform::IFC4X3_RC1::IFC4X3_RC1Reader>(filepath);
#else // OIP_MODULE_EARLYBINDING_IFC4X3_RC1
			throw std::exception("IFC4X3_RC1 not compiled");
#endif //OIP_MODULE_EARLYBINDING_IFC4X3_RC1
		}
		else if (ifcSchema == IfcPeekStepReader::IfcSchema::IFC4X3_RC4) {
#ifdef OIP_MODULE_EARLYBINDING_IFC4X3_RC4
			renderer =
				setUpRenderer<emt::IFC4X3_RC4EntityTypes, OpenInfraPlatform::IFC4X3_RC4::IFC4X3_RC4Reader>(filepath);
#else // OIP_MODULE_EARLYBINDING_IFC4X3_RC4
			throw std::exception("IFC4X3_RC4 not compiled");
#endif //OIP_MODULE_EARLYBINDING_IFC4X3_RC4
		}
		else
		{
			std::string msg("IFC version " + strSchema + " not supported");
			throw std::exception(msg.c_str());
		}

		saveAllViews(renderer, outputDirectoryName, filename);

    } catch (std::exception &ex) {
		std::cout << std::endl;
		std::cout << "---- EXCEPTION ENCOUNTERED ----" << std::endl;
        std::cout << ex.what() << std::endl;
		std::cout << "----  Press ENTER to exit  ----" << std::endl;
		getchar();
    }

}
