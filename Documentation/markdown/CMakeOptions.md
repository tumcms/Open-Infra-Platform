# CMake Options for the TUM Open Infra Platform.
This lists all CMake Options that can be set for the TUM Open Infra Platform project.

## Overview of files using CMake Options:

Grouping by files or topic?
- Doxygen
- EarlyBinding

- External

Default value / preselection etc. 


## Doxygen
General desciption what these options are for. Refer to DoxygenHelp.md.

| Option                                   | Default | Description                                                                                                                                                                                                                                                                | Link to file                                                  								|
|------------------------------------------|---------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------|
| DOXYGEN_GENERATE_DOCUMENTATION           | ON      | This option needs to be selected to build documentation. If selected in the CMake GUI, CMake will automatically find  the doxygen and dot executables and display the options  below.                                                                                      | https://github.com/tumcms/Open-Infra-Platform/blob/development/CMakeLists.txt           	|
| DOXYGEN_OPTIONAL_INCLUDE_COMMENTED_ONLY  | ON      | If selected, only documentation for explicitly commented entities  will be generated. Otherwise, doxygen will assume that all entities  are documented, even if there is no documentation available.                                                                       | https://github.com/tumcms/Open-Infra-Platform/blob/development/cmake/ConfigureDoxygen.cmake	|
| DOXYGEN_OPTIONAL_INCLUDE_INTERNAL        | OFF     | If selected, this will include all comments preceded by "\internal".  These are comments intended for developers only.  So if the generated documentation is intended for external users,  this option should not be selected.                                             | https://github.com/tumcms/Open-Infra-Platform/blob/development/cmake/ConfigureDoxygen.cmake	|
| DOXYGEN_OPTIONAL_INCLUDE_EARLY_BINDING   | OFF     | If selected (... and already built), this will include the selected  IFC schemas in the documentation. Otherwise, the schemas will not be  included in the documentation, but this does not influence the  selection of IFC schemas (see EARLYBINDING_ tags in CMake GUI). | https://github.com/tumcms/Open-Infra-Platform/blob/development/cmake/ConfigureDoxygen.cmake	|
| DOXYGEN_OPTIONAL_AUTO_OPEN_DOCUMENTATION | ON      | If selected, the landing page of the documentation will open automatically.  If not selected, you will have to find and open the generated documentation  manually (see section below on building the documentation).                                                      | https://github.com/tumcms/Open-Infra-Platform/blob/development/cmake/ConfigureDoxygen.cmake |

## EarlyBinding




