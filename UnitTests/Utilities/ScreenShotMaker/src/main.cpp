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

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string>
#include <iostream>

#include <boost/filesystem.hpp>

#include "tclap/CmdLine.h"

#include <buw.Engine.h>
#include <buw.ImageProcessing.h>

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

#ifdef OIP_MODULE_EARLYBINDING_IFC4X3_RC3
#include <EarlyBinding/IFC4X3_RC3/src/reader/IFC4X3_RC3Reader.h>
#include <EarlyBinding/IFC4X3_RC3/src/IFC4X3_RC3.h>
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
	renderer->setViewDirection(buw::eViewDirection::Left);
	buw::Image4b image_left = renderer->captureImage();
	buw::storeImage(outputDirectoryName + "\\" + filename + "_left.png", image_left);

	std::cout << "Saved image " << std::endl;
	std::cout << outputDirectoryName + "\\" + filename + "_left.png" << std::endl;
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

		std::cout << "Generating screen shots from " << std::endl;
		std::cout << filepath << std::endl;
		std::cout << "Saving screen shots to " << std::endl;
		std::cout << outputDirectoryName << std::endl;

        FILE *myfile = fopen(filepath, "r");
        // make sure it is valid:
        if (!myfile) {
			std::string err = std::string("I can't open file ") + std::string(filepath) + std::string("!");
			throw std::exception(err.c_str());
        }
		fclose(myfile);


#ifdef OIP_MODULE_EARLYBINDING_IFC4X1
		buw::ReferenceCounted<IfcGeometryModelRenderer> renderer = 
			setUpRenderer<emt::IFC4X1EntityTypes, OpenInfraPlatform::IFC4X1::IFC4X1Reader>(filepath);
#endif
#ifdef OIP_MODULE_EARLYBINDING_IFC4X3_RC1
		buw::ReferenceCounted<IfcGeometryModelRenderer> renderer = 
			setUpRenderer<emt::IFC4X3_RC1EntityTypes, OpenInfraPlatform::IFC4X3_RC1::IFC4X3_RC1Reader>(filepath);
#endif
#ifdef OIP_MODULE_EARLYBINDING_IFC4X3_RC3
		buw::ReferenceCounted<IfcGeometryModelRenderer> renderer = 
			setUpRenderer<emt::IFC4X3_RC3EntityTypes, OpenInfraPlatform::IFC4X3_RC3::IFC4X3_RC3Reader>(filepath);
#endif

		boost::filesystem::path givenPathToIfcFile(filepath);
		std::string filename = givenPathToIfcFile.stem().string();

		saveAllViews(renderer, outputDirectoryName, filename);

    } catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }

	// wait for confirm of exit
	std::cout << "Press ENTER to exit" << std::endl;
	getchar();

}
