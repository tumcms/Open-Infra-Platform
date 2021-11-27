# Tools for unit testing and QA

OIP ships with a small collection of tools that support testing and simplify repetitive tasks. A short list with explanations can be found here:

* **Screen shot maker:** Simple console application written with tclap that creates and saves screenshots that are needed for unit testing. It requires inputting the absolute or relative path of the IFC file that needs to be rendered, and the path of the output directory where the screenshots will be saved (see [here](../../UnitTests/Utilities/ScreenShotMaker/src/main.cpp)).

* **Header generator:** Python tool that writes reoccurring elements of C++ header files, including the Copywrite and licences statement, namespaces, and the beginning of the class definition according to the input class name (see [here](../../Tools/fileHeaderGenerator.py)). A similar tool exists for creating EMT headers (see [here](../../Tools/EMTHeaderGenerator.py)). 

* **Namespace generator:** Python tool that writes a file defining namespaces dependent on the input module name. The resulting file can be included in other files to skip the definition of namespaces and make the code cleaner and more uniform. Apart from the module name, the name of the file that will be generated is to be provided as an input parameter (see [here](../../Tools/getStringFromEnumGenerator.py)). 

* **Cast and call generator:** Python tool that searches a given directory for all files. Each file is checked for non-abstract classes and "VISITABLE_STRUCT". A file is created that defines templates for castDerivedAndCall or castToVisitableAndCall for all of them (see [here](../../Tools/castAndCallGenerator.py)).

* **Get string from enum:** Python tool that searches a given directory for all files. Each file is checked for enum definitions. After going through all files, a new file is created that defines a function for every enum returning the enum values as strings (see [here](../../Tools/getStringFromEnumGenerator.py)). 

* **Plot:** Python tool that plots diagrams for the chainage, curvature, and bearings based on values from an input file (see [here](../../Tools/plot.py)).

