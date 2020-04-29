# Doxygen for OpenInfraPlatform 
The TUM Open Infra Platform uses doxygen to document its code.

## Installation
Doxygen (http://www.doxygen.nl/download.html). For windows, there is:
A self-installing archive (doxygen-1.8.17-setup.exe) with the GUI frontend and HTML versions of manual and a doxygen binary download in zip (32 or 64-bit version).

- Run “Get_Doxygen.cmd” and “Get_Dot.cmd” under “.../Open-Infra-Platform/external”. This should be suggested to you when configuring CMake if they are missing anyway (... if you have selected DOXYGEN_GENERATE_DOCUMENTATION in the CMake GUI) 

Alternatively install doxygen and dot yourself:
- Download the 64-bit version of the doxygen binary in zip. We don’t need the GUI front end, because we are setting everything within CMake. 
- Extract into “C:/thirdparty/doxygen”
- Download the DOT package. This GraphViz package is necessary for creating the dependency diagrams etc. in the documentation. 
- Download the DOT package (https://graphviz.gitlab.io/_pages/Download/windows/graphviz-2.38.zip)
- Extract into “C:/thirdparty/graphviz_dot”

## Doxygen in CMake

### Top-level CMakelists.txt
If DOXYGEN_GENERATE_DOCUMENTATION is selected in the CMake GUI, CMake will automatically find the doxygen and dot executables. The up-to-date version of the file can be found here:
https://github.com/tumcms/Open-Infra-Platform/blob/development/CMakeLists.txt

In the CMake GUI, the following options can be selected:
- DOXYGEN_OPTIONAL_COMMENTED_ONLY: If this is not selected, doxygen will assume that all entities are documented, even if there is no documentation available. 
- DOXYGEN_OPTIONAL_INCLUDE_INTERNAL: If selected, this will include all comments preceded by "\internal" (comments intended for developers only).
- DOXYGEN_OPTIONAL_INCLUDE_EARLYBINDING: If selected (... and already built), this will include the selected IFC schemas in the documentation. 

### ConfigureDoxygen.cmake file
If DOXYGEN_GENERATE_DOCUMENTATION is selected in CMake, CMake will include ConfigureDoxygen.cmake. This file includes all settings for the generation of doxygen documentation for the Open Infra Platform project. Changes to documentation settings should be made here. doxygen_add_docs() creates the GenerateDocumentation target. The up-to-date version of the file can be found here:

https://github.com/tumcms/Open-Infra-Platform/blob/development/cmake/ConfigureDoxygen.cmake

A tag that is more likely to be required to change:
- DOXYGEN_EXCLUDE_PATTERNS: if you want to exclude certain source code directories or files from the documentation, you should add them here.

More settings to be added can be found here:
http://www.doxygen.nl/manual/index.html

Important: when adding settingsthem in CMake, always use DOXYGEN_ before the standard doxygen tag, e.g. the doxygen tag "PROJECT_BRIEF" has to be "DOXYGEN_PROJECT_BRIEF" in the ConfigureDoxygen.cmake file.

## Building the documentation
In Visual studio, build "GenerateDocumentation".
In your build directory under Doxymentation/html you will then find something called “index.html”. This is a link to the index page of the HTML documentation browser. 
This index page of the documentation will be opened automatically if the build succeeded.

## Style 
When using doxygen within the Open Infra Platform, please use this style: start a comment block with /*!, start every line with * and end it with */.

- Brief description: introduced by \brief 
- Internal comments: introduced by \internal
- Parameters: introduced by \param

Refer to the doxygen manual (http://www.doxygen.nl/manual) for everything else.

## Useful links

- Code blocks:
Entire source code file: http://www.doxygen.nl/manual/commands.html#cmdinclude 
Code snippet: http://www.doxygen.nl/manual/commands.html#cmdsnippet 

- Links to other classes, files, functions:
If in correct format, will recognize class, file, function names as such and create a link automatically. 
http://www.doxygen.nl/manual/autolink.html

- Custom commands:
http://www.doxygen.nl/manual/custcmd.html

- Linking to external documentation:
http://www.doxygen.nl/manual/external.html


