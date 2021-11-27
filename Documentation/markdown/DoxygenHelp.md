# Doxygen for Open Infra Platform 

The TUM Open Infra Platform uses doxygen to document its code.

## Style 

Open Infra Platform follows this style: 
1. start a comment block with `/*!`, 
1. start every line with `*` and 
1. end it with `*/`.

Some useful keywords:
- Brief description: `\brief`
- Internal comments: `\internal`
- Parameters: `\param`
- Return: `\return`

Refer to the [doxygen manual](http://www.doxygen.nl/manual) for everything else.

## Doxygen settings in CMake

### Top-level CMakelists.txt

If `DOXYGEN_GENERATE_DOCUMENTATION` is checked in the CMake GUI (default = ON), CMake will try to find the doxygen and dot executables in `C/thirdparty`. Additionally, a command that builds the documentation will be added to the solution.

Additionally, the following options can be selected:
- `DOXYGEN_INCLUDE_COMMENTED_ONLY` (default = ON): If selected, only the documentation for explicitly commented entities will be generated. Otherwise, doxygen will assume that all entities are documented, even if there is no documentation available. 
- `DOXYGEN_INCLUDE_INTERNAL` (default = OFF): If selected, this will include all comments preceded by "\internal". These are comments intended for developers only. So if the generated documentation is intended for external users, this option should not be selected.
- DOXYGEN_INCLUDE_EARLYBINDING (default = OFF): If selected (... and already built), this will include the selected IFC schemas in the documentation. Otherwise, the schemas will not be included in the documentation, but this does not influence the selection of IFC schemas (see EARLYBINDING_ tags in CMake GUI).
- DOXYGEN_AUTO_OPEN_DOCUMENTATION (default = ON): If selected, the landing page of the documentation will automatically open. If not selected, you will have to find and open the generated documentation manually (see section below on building the documentation). 

### ConfigureDoxygen.cmake
If DOXYGEN_GENERATE_DOCUMENTATION is selected in CMake, CMake will include ConfigureDoxygen.cmake. This file includes all settings for the generation of doxygen documentation for the Open Infra Platform project. Changes to documentation settings should be made here. doxygen_add_docs() creates the GenerateDocumentation target. The up-to-date version of the file can be found here:

See [file](../../cmake/ConfigureDoxygen.cmake)

#### ToDos.
The DOXYGEN_EXCLUDE_PATTERNS tag used in ConfigureDoxygen.cmake is one that is more likely to be required to change.
It excludes certain source code directories or files from the documentation. In this project, the following directories including the following patterns are currently excluded:
- CurrentlyExcluded
- cmake
- deploy
- Documentation
- external
- testdata
- Tools
- UserInterface/QtPropertyBrowser

Refer to ConfigureDoxygen.cmake (see link above) if you do want to include any these directories in the documentation. 

More settings to be added can be found here:
http://www.doxygen.nl/manual/index.html

Important: when adding settings in CMake, always use DOXYGEN_ before the standard doxygen tag, e.g. the doxygen tag "PROJECT_BRIEF" has to be "DOXYGEN_PROJECT_BRIEF" in the ConfigureDoxygen.cmake file.

## Building the documentation
In Visual studio, build "OpenInfraPlatform.GenerateDocumentation". This target can be found in Visual Studio under OpenInfraPlatform/Commands.
If "DOXYGEN_OPTIONAL_AUTO_OPEN_DOCUMENTATION" was selected in the CMake GUI, the landing pages of the documentation will be opened automatically if the build succeeded.
Otherwise, the documentation has to be opened manually. In your build directory under Doxymentation/html you will find something called “index.html”. Clicking on this file will open the landing page of the HTML documentation browser. 

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


