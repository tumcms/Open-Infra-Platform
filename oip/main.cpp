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
#include "tclap/CmdLine.h"
#include <BlueFramework/Core/Diagnostics/log.h>
#include <BlueFramework/Core/version.h>
#include <boost/algorithm/string/predicate.hpp>
#include <iomanip>

void convertLandXMLtoIfcAlignment1x1ExcelComparison(const char* inputFilename, const char* outputFilename) {
	buw::ImportLandXml landxml_import(inputFilename);

	buw::ReferenceCounted<buw::DigitalElevationModel> dem = std::make_shared<buw::DigitalElevationModel>();

	if (landxml_import.getDigitalElevationModel()) {
		for (int i = 0; i < landxml_import.getDigitalElevationModel()->getSurfaceCount(); i++) {
			dem->addSurface(landxml_import.getDigitalElevationModel()->getSurface(i));
		}
	}

	buw::ifcAlignmentExportDescription desc;
	desc.exportAlignment = true;
	desc.exportTerrain = true;
	buw::ExportIfcAlignment1x1 sfc(desc, landxml_import.getAlignmentModel(), dem, "alignment.ifc");

	buw::IfcAlignment1x1ExcelReport ec(outputFilename, inputFilename, "alignment.ifc");
}

void convertLandXMLtoIfcAlignment1x0(const std::string& inputFilename, const std::string& outputFilename) {
	buw::ImportLandXml parser(inputFilename);

	buw::ReferenceCounted<buw::DigitalElevationModel> dem = std::make_shared<buw::DigitalElevationModel>();

	if (parser.getDigitalElevationModel()) {
		for (int i = 0; i < parser.getDigitalElevationModel()->getSurfaceCount(); i++) {
			dem->addSurface(parser.getDigitalElevationModel()->getSurface(i));
		}
	}

	buw::ifcAlignmentExportDescription desc;
	desc.exportTerrain = true;
	desc.exportAlignment = true;

	buw::ExportIfcAlignment1x0 ifcExport(desc, parser.getAlignmentModel(), dem, outputFilename);
}

void convertLandXMLtoIfcAlignment1x1(const std::string& inputFilename, const std::string& outputFilename) {
	buw::ImportLandXml parser(inputFilename);

	buw::ReferenceCounted<buw::DigitalElevationModel> dem = std::make_shared<buw::DigitalElevationModel>();

	if (parser.getDigitalElevationModel()) {
		for (int i = 0; i < parser.getDigitalElevationModel()->getSurfaceCount(); i++) {
			dem->addSurface(parser.getDigitalElevationModel()->getSurface(i));
		}
	}

	buw::ifcAlignmentExportDescription desc;
	desc.exportTerrain = true;
	desc.exportAlignment = true;

	buw::ExportIfcAlignment1x1 ifcExport(desc, parser.getAlignmentModel(), dem, outputFilename);
}

void convertLandXMLtoSVG(const std::string& inputFilename, const std::string& outputFilename) {
	buw::ImportLandXml parser(inputFilename);

	buw::ReferenceCounted<buw::DigitalElevationModel> dem = std::make_shared<buw::DigitalElevationModel>();

	if (parser.getDigitalElevationModel()) {
		for (int i = 0; i < parser.getDigitalElevationModel()->getSurfaceCount(); i++) {
			dem->addSurface(parser.getDigitalElevationModel()->getSurface(i));
		}
	}

	buw::ExportSVG svgExport(parser.getAlignmentModel(), dem, outputFilename);
}

int main(int argc, char* argv[]) {
	buw::initializeLogSystem(true, true);

	if (BlueFramework::Core::Version::getPatch() != BLUEFRAMEWORK_API_PATCH) {
		BLUE_LOG(error) << "Invalid BlueFramwork Core DLL found!";
	}

	try {
		buw::CmdLine cmd("TUM Open Infra Platform command line utilities", ' ', "0.1");

		std::vector<std::string> allowed;
		allowed.push_back("IfcAlignment1x0");
		allowed.push_back("IfcAlignment1x1");
		allowed.push_back("IfcAlignment1x1_XLSX");
		allowed.push_back("SVG");
		buw::ValuesConstraint<std::string> allowedVals(allowed);

		buw::ValueArg<std::string> nameArg("t", "exportType", "Export type that should be used", true, "IfcAlignment1x0", &allowedVals);
		cmd.add(nameArg);

		// Define a value argument and add it to the command line.
		buw::ValueArg<std::string> nameOutputArg("o", "output", "Path to output file", true, "text.xml", "string");
		cmd.add(nameOutputArg);

	    // Define a value argument and add it to the command line.
		buw::ValueArg<std::string> nameInputArg("i", "input", "Path to input file", true, "text.xml", "string");
		cmd.add(nameInputArg);

		// Parse the args.
		cmd.parse(argc, argv);

		// Get the value parsed by each arg.
		std::string inputFilename = nameInputArg.getValue();
		std::string outputFilename = nameOutputArg.getValue();
		std::string exportType = nameArg.getValue();

		if (exportType == "IfcAlignment1x0") {
			convertLandXMLtoIfcAlignment1x0(inputFilename, outputFilename);
		}

		if (exportType == "IfcAlignment1x1") {
			convertLandXMLtoIfcAlignment1x1(inputFilename, outputFilename);
		}

		if (exportType == "SVG") {
			convertLandXMLtoSVG(inputFilename.c_str(), outputFilename.c_str());
		}

		if (exportType == "IfcAlignment1x1_XLSX") {
			convertLandXMLtoIfcAlignment1x1ExcelComparison(inputFilename.c_str(), outputFilename.c_str());
		}
	} catch (buw::ArgException& e) // catch any exceptions
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}

	return 0;
}
