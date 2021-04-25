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

#include "tclap/CmdLine.h"

#include <buw.Engine.h>
#include <buw.ImageProcessing.h>

#include <IfcGeometryConverter/ConverterBuw.h>
#include <IfcGeometryConverter/IfcImporter.h>
#include <IfcGeometryConverter/IfcImporterImpl.h>

#include <IfcGeometryModelRenderer.h>
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

        const char* filename = sourceFiles.getValue().c_str();
        std::string outputDirectoryName = outputDirectory.getValue();

		std::cout << "Generating screen shots from " << filename << " to " << outputDirectoryName << std::endl;
		
        FILE *myfile = fopen(filename, "r");
        // make sure it is valid:
        if (!myfile) {
			std::cout << "I can't open file " << filename << "!" << std::endl;
            return -1;
        }
		fclose(myfile);





    } catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }

	// wait for confirm of exit
	std::cout << "Press any key to exit" << std::endl;
	getchar();
}
