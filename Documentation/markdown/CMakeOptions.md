# CMake Options for the TUM Open Infra Platform.
This lists all CMake Options that can be set for the TUM Open Infra Platform project.

## Overview of the CMake Options

A CMake Option is visible in the CMake GUI as a box that can be ticked (or not). 
Note that if the default value is set to "ON", whatever the option does will be executed, regardless of the option box being ticked in the CMake GUI or not. (?) Test this. Refer to the CMake "Option" command [here](https://cmake.org/cmake/help/latest/command/option.html).

The options that can be set for the TUM Open Infra Platform are grouped thematically. Click on the name below to jump to the respective section. There you will find a description of what each option does, what its default value is and where to find the source code where the option is set if you require more information or wish to make changes there. 

- [EarlyBinding](#earlybinding)
- [Doxygen](#doxygen)
- [Modules](#modules)
- [External](#external)

## EarlyBinding

## Doxygen
The TUM Open Infra Platform uses doxygen to document its code. The CMake options listed below allow the user adjust the outcome of the documentation by selecting which parts of the source code should be included in the generated documentation. For more information on how doxygen is used in the TUM Open Infra Platform, please refer to [DoxygenHelp.md](https://github.com/tumcms/Open-Infra-Platform/blob/development/Documentation/markdown/DoxygenHelp.md).

| Option                                   | Default | Description                                                                                                                                                                                                                                                                         | Link to file                                          										 				|
|------------------------------------------|---------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------|
| DOXYGEN_GENERATE_DOCUMENTATION           | ON      | This option needs to be selected to build documentation.<br>If selected in the CMake GUI, CMake will automatically find <br>the doxygen and dot executables and display the options <br>below.                                                                                      | [Go to file](https://github.com/tumcms/Open-Infra-Platform/blob/development/CMakeLists.txt) 				|
| DOXYGEN_OPTIONAL_INCLUDE_COMMENTED_ONLY  | ON      | If selected, only documentation for explicitly commented entities <br>will be generated. Otherwise, doxygen will assume that all entities <br>are documented, even if there is no documentation available.                                                                          | [Go to file](https://github.com/tumcms/Open-Infra-Platform/blob/development/cmake/ConfigureDoxygen.cmake)	|
| DOXYGEN_OPTIONAL_INCLUDE_INTERNAL        | OFF     | If selected, this will include all comments preceded by "\internal". <br>These are comments intended for developers only. <br>So if the generated documentation is intended for external users, <br>this option should not be selected.                                             | [Go to file](https://github.com/tumcms/Open-Infra-Platform/blob/development/cmake/ConfigureDoxygen.cmake)	|
| DOXYGEN_OPTIONAL_INCLUDE_EARLY_BINDING   | OFF     | If selected (... and already built), this will include the selected <br>IFC schemas in the documentation. Otherwise, the schemas will not be <br>included in the documentation, but this does not influence the <br>selection of IFC schemas (see EARLYBINDING_ tags in CMake GUI). | [Go to file](https://github.com/tumcms/Open-Infra-Platform/blob/development/cmake/ConfigureDoxygen.cmake)	|
| DOXYGEN_OPTIONAL_AUTO_OPEN_DOCUMENTATION | ON      | If selected, the landing page of the documentation will open automatically. <br>If not selected, you will have to find and open the generated documentation <br>manually (see section below on building the documentation).                                                         | [Go to file](https://github.com/tumcms/Open-Infra-Platform/blob/development/cmake/ConfigureDoxygen.cmake)	|

## Modules

## External





