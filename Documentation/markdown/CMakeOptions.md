# CMake Options for the TUM Open Infra Platform.
This lists all CMake Options that can be set for the TUM Open Infra Platform project.

## Overview of files using CMake Options:

Grouping by files or topic? Link to section below.
- Doxygen
- EarlyBinding

- External

Default value / preselection etc. 

## Doxygen
General desciption what these options are for. Refer to DoxygenHelp.md.

| Option                                   | Default | Description                                                                                                                                                                                                                                                                         | Link to file                                          										 |
|------------------------------------------|---------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------|
| DOXYGEN_GENERATE_DOCUMENTATION           | ON      | This option needs to be selected to build documentation.<br>If selected in the CMake GUI, CMake will automatically find <br>the doxygen and dot executables and display the options <br>below.                                                                                      | [Go to file](https://github.com/tumcms/Open-Infra-Platform/blob/development/CMakeLists.txt) |
| DOXYGEN_OPTIONAL_INCLUDE_COMMENTED_ONLY  | ON      | If selected, only documentation for explicitly commented entities <br>will be generated. Otherwise, doxygen will assume that all entities <br>are documented, even if there is no documentation available.                                                                          | {CMAKE_CURRENT_ROOT_DIR}/cmake/ConfigureDoxygen.cmake 										 |
| DOXYGEN_OPTIONAL_INCLUDE_INTERNAL        | OFF     | If selected, this will include all comments preceded by "\internal". <br>These are comments intended for developers only. <br>So if the generated documentation is intended for external users, <br>this option should not be selected.                                             | {CMAKE_CURRENT_ROOT_DIR}/cmake/ConfigureDoxygen.cmake 										 |
| DOXYGEN_OPTIONAL_INCLUDE_EARLY_BINDING   | OFF     | If selected (... and already built), this will include the selected <br>IFC schemas in the documentation. Otherwise, the schemas will not be <br>included in the documentation, but this does not influence the <br>selection of IFC schemas (see EARLYBINDING_ tags in CMake GUI). | {CMAKE_CURRENT_ROOT_DIR}/cmake/ConfigureDoxygen.cmake 										 |
| DOXYGEN_OPTIONAL_AUTO_OPEN_DOCUMENTATION | ON      | If selected, the landing page of the documentation will open automatically. <br>If not selected, you will have to find and open the generated documentation <br>manually (see section below on building the documentation).                                                         | {CMAKE_CURRENT_ROOT_DIR}/cmake/ConfigureDoxygen.cmake 										 |

## EarlyBinding




