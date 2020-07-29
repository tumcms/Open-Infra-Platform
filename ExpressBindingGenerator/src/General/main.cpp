/*
    This file is part of TUM Open Infra Platform Early Binding EXPRESS
    Generator, a simple early binding generator for EXPRESS.
    Copyright (c) 2016-2017 Technical University of Munich
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

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

#include "Parser/node.h"
#include "parser.hpp"
#include "Generator/GeneratorOIP.h"
#include "Meta/Schema.h"

extern int yyparse();
extern FILE *yyin;

using namespace OpenInfraPlatform::ExpressBindingGenerator;

#include "tclap/CmdLine.h"

int main(int argc, char **argv) {
    try {
        TCLAP::CmdLine cmd("oipExpress", ' ', "0.1");

		TCLAP::UnlabeledValueArg<std::string> sourceFiles("i", "EXPRESS Schema file.", true, "./rectified", "string");
        cmd.add(sourceFiles);

		TCLAP::ValueArg<std::string> outputDirectory("o", "outputDir", "The output directory.", false, "", "string");
        cmd.add(outputDirectory);

        // Parse the args.
        cmd.parse(argc, argv);

        // open a file handle to a particular file:

        const char* filename = sourceFiles.getValue().c_str();
        std::string outputDirectoryName = outputDirectory.getValue();

		cout << "Generating .h/.cpp files from " << filename << std::endl;

        //std::string filename = "C:/dev/Neuer Ordner/IFC4x1_RC3.exp";
        // std::string filename = "C:/dev/OpenInfraPlatform2/IfcAlignment1x1/schema/IFC4x1_RC3.exp";

        FILE *myfile = fopen(filename, "r");
        // make sure it is valid:
        if (!myfile) {
            cout << "I can't open file!" << endl;
            return -1;
        }
        // set flex to read from it instead of defaulting to STDIN:
        yyin = myfile;

        // parse through the input until there is no more:
        do {
            yyparse();
        } while (!feof(yyin));

        std::ofstream ofs("test.txt", std::ofstream::out);

        std::ostream &out = ofs; // std::cout;
		       
		//link inverse attributes
		oip::Schema::getInstance().linkInverses();
       
        GeneratorOIP cppgen(outputDirectoryName);
        cppgen.generateREFACTORED(out, oip::Schema::getInstance());
        

        ofs.close();

    } catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
}

extern int line_num;

void yyerror(const char *s) {
    cout << "Parse error!  Message: " << s << endl;
    cout << "Line number: " << line_num << endl;
    // might as well halt now:
    exit(-1);
}