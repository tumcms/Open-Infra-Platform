# CMake Options for the TUM Open Infra Platform.
This lists all CMake Options that can be set for the TUM Open Infra Platform project.

## Overview of the CMake Options

A CMake Option is visible in the CMake GUI as a box that can be ticked (or not). 
If you have made changes and want to return to the default values, you will have to delete the CMake cache and configure again. Refer to the CMake "Option" command [here](https://cmake.org/cmake/help/latest/command/option.html).

The options that can be set for the TUM Open Infra Platform are grouped as project-specific options and external options (libraries and thirdparty software). For each, you will find a description of what each option does, what its default value is and where to find the source code where the option is set if you require more information or wish to make changes there. 
Click on the name below to jump to the respective section. 

- [Project options](#project-options)
- [External options](#external-options)

## Project options

The following are options specific to the build of the TUM Open Infra Platform project. The options are grouped thematically. Click on the name below to jump to the respective section. If you want to see information about external library and thirdparty software options instead, you can find them [here](#external-options). 

- [Build options](#build-options)
- [Doxygen](#doxygen)
- [EarlyBinding](#earlybinding)
- [FetchContent](#fetchcontent)
- [Modules](#modules)
- [Project configuration](#project-configuration)

### Build options

| Option            | Default | Description | Link to file |
|-------------------|---------|-------------|--------------|
| BUILD_COVERAGE    | OFF     |             |              |
| BUILD_GMOCK       | ON      |             |              |
| BUILD_SHARED_LIBS | ON      |             |              |
| BUILD_TESTING     | ON      |             |              |
| BUILD_TESTS       | ON      |             |              |
| BUILD_UTILS       | ON      |             |              |

[Go back to overview](#project-options)

### Doxygen
The TUM Open Infra Platform uses doxygen to document its code. The CMake options listed below allow the user adjust the outcome of the documentation by selecting which parts of the source code should be included in the generated documentation. For more information on how doxygen is used in the TUM Open Infra Platform, please refer to [DoxygenHelp.md](./DoxygenHelp.md).

| Option                                   | Default | Description                                                                                                                                                                                                                                                                         | Link to file                                          										 				|
|------------------------------------------|---------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------|
| DOXYGEN_GENERATE_DOCUMENTATION           | ON      | This option needs to be selected to build documentation.<br>If selected in the CMake GUI, CMake will automatically find <br>the doxygen and dot executables and display the options <br>below.                                                                                      | [Go to file](https://github.com/tumcms/Open-Infra-Platform/blob/development/CMakeLists.txt) 				|
| DOXYGEN_OPTIONAL_INCLUDE_COMMENTED_ONLY  | ON      | If selected, only documentation for explicitly commented entities <br>will be generated. Otherwise, doxygen will assume that all entities <br>are documented, even if there is no documentation available.                                                                          | [Go to file](https://github.com/tumcms/Open-Infra-Platform/blob/development/cmake/ConfigureDoxygen.cmake)	|
| DOXYGEN_OPTIONAL_INCLUDE_INTERNAL        | OFF     | If selected, this will include all comments preceded by "\internal". <br>These are comments intended for developers only. <br>So if the generated documentation is intended for external users, <br>this option should not be selected.                                             | [Go to file](https://github.com/tumcms/Open-Infra-Platform/blob/development/cmake/ConfigureDoxygen.cmake)	|
| DOXYGEN_OPTIONAL_INCLUDE_EARLY_BINDING   | OFF     | If selected (... and already built), this will include the selected <br>IFC schemas in the documentation. Otherwise, the schemas will not be <br>included in the documentation, but this does not influence the <br>selection of IFC schemas (see EARLYBINDING_ tags in CMake GUI). | [Go to file](https://github.com/tumcms/Open-Infra-Platform/blob/development/cmake/ConfigureDoxygen.cmake)	|
| DOXYGEN_OPTIONAL_AUTO_OPEN_DOCUMENTATION | ON      | If selected, the landing page of the documentation will open automatically. <br>If not selected, you will have to find and open the generated documentation <br>manually.                                                         | [Go to file](https://github.com/tumcms/Open-Infra-Platform/blob/development/cmake/ConfigureDoxygen.cmake)	|

[Go back to overview](#project-options)

### EarlyBinding
These options allow you to select which IFC schemas should be built for the project. These options will only be displayed once *OpenInfraPlatform.Commands.UpdateBoostMPL* and *OpenInfraPlatform.ExpressBindingGenerator* have been built (see [Building.md](./Building.md)). Once the desired schema or schemas are selected, you have to generate CMake again. The default value for the schemata are set [here](https://github.com/tumcms/Open-Infra-Platform/blob/development/ExpressBindingGenerator/CMakeLists.txt).

| Option                            | Default |
|-----------------------------------|---------|
| EARLYBINDING_WITH_IFC2X3          | OFF     |           
| EARLYBINDING_WITH_IFC4            | OFF     |           
| EARLYBINDING_WITH_IFC4X1          | OFF     |
| EARLYBINDING_WITH_IFC4X2          | OFF     |            
| EARLYBINDING_WITH_IFC4X2_BIM4ROAD | OFF     |          
| EARLYBINDING_WITH_IFC4X2_DRAFT_1  | OFF     |       
| EARLYBINDING_WITH_IFC4X3_RC1      | ON      |  

[Go back to overview](#project-options)

### FetchContent

| Option                                           | Default | Description | Link to file |
|--------------------------------------------------|---------|-------------|--------------|
| FETCHCONTENT_FULLY_DISCONNECTED                  | OFF     |             |              |
| FETCHCONTENT_QUIET                               | ON      |             |              |
| FETCHCONTENT_UPDATES_DISCONNECTED                | OFF     |             |              |
| FETCHCONTENT_UPDATES_DISCONNECTED_BLUE_FRAMEWORK | OFF     |             |              |
| FETCHCONTENT_UPDATES_DISCONNECTED_DEP_GTEST      | OFF     |             |              |
| FETCHCONTENT_UPDATES_DISCONNECTED_EIGEN          | OFF     |             |              |
| FETCHCONTENT_UPDATES_DISCONNECTED_GLEW           | OFF     |             |              |
| FETCHCONTENT_UPDATES_DISCONNECTED_GTEST          | OFF     |             |              |
| FETCHCONTENT_UPDATES_DISCONNECTED_TCLAP          | OFF     |             |              |
| FETCHCONTENT_UPDATES_DISCONNECTED_TINYXML2       | OFF     |             |              |
| FETCHCONTENT_UPDATES_DISCONNECTED_VISIT_STRUCT   | OFF     |             |              |
| FETCHCONTENT_UPDATES_VISIT_STRUCT_ZLIB           | OFF     |             |              |

[Go back to overview](#project-options)

### Modules
These options allow you to include specific modules to the TUM Open Infra Platform project. Currently, only the point cloud processing module is supported. These options are specified [here](https://github.com/tumcms/Open-Infra-Platform/blob/development/CMakeLists.txt9.

| Option                          | Default | 
|---------------------------------|---------|
| MODULES_DIGITAL_ELEVATION_MODEL | OFF     |           
| MODULES_GIRDER                  | OFF     |           
| MODULES_POINT_CLOUD_PROCESSING  | OFF     |           
| MODULES_PROXY_MODEL             | OFF     |            
| MODULES_RAILWAY                 | OFF     |            
| MODULES_SLABFIELD               | OFF     |        
| MODULES_TESSELATION             | OFF     |     

[Go back to overview](#project-options)

### Project Configuration

| Option                                       | Default | Description | Link to file |
|----------------------------------------------|---------|-------------|--------------|
| BLUEFRAMEWORK_USE_PREDEFINED_THIRDPARTY_PATH | ON      |             |              |
| OIP_USE_PREDEFINED_THIRDPARTY_PATH           | ON      |             |              |
| ASMD64                                       | OFF     |             |              |
| ASM686                                       | OFF     |             |              |
| gmock_build_tests                            | OFF     |             |              |

[Go back to overview](#project-options)

## External options

The following are options for external libraries and thirdparty software that are used in the TUM Open Infra Platform project that can be set for the build of the TUM Open Infra platform project. Click on the name below to jump to the respective section. If you want to see information about project-specific options instead, you can find them [here](#project-options). 

- [Carve](#carve)
- [CMake](#cmake)
- [Cuda](#cuda)
- [Eigen](#eigen)
- [Glew](#glew)
- [Gtest](#gtest)
- [MPI](#mpi)

### Carve

| Option                           | Default | Description | Link to file |
|----------------------------------|---------|-------------|--------------|
| CARVE_DEBUG                      | OFF     |             |              |
| CARVE_DEBUG_WRITE_PLY_DATA       | OFF     |             |              |
| CARVE_GTESTS_TESTS               | OFF     |             |              |
| CARVE_INTERSECT_GLU_TRIANGULATOR | OFF     |             |              |
| CARVE_USE_EXACT_PREDICATES       | OFF     |             |              |
| CARVE_WITH_GUI                   | OFF     |             |              |

[Go back to overview](#external-options)

### CMake

| Option                   | Default | Description | Link to file |
|--------------------------|---------|-------------|--------------|
| CMAKE_SKIP_INSTALL_RPATH | OFF     |             |              |
| CMAKE_SKIP_RPATH         | OFF     |             |              |
| CMAKE_VERBOSE_MAKEFILE   | OFF     |             |              |

[Go back to overview](#external-options)

### Cuda

| Option                                 | Default | Description | Link to file |
|----------------------------------------|---------|-------------|--------------|
| CUDA_64_BIT_DEVICE_CODE                | ON      |             |              |
| CUDA_ATTACH_VS_BUILD_RULE_TO_CUDA_FILE | ON      |             |              |
| CUDA_BUILD_EMULATION                   | OFF     |             |              |
| CUDA_CUDART_LIBRARY                    | OFF     |             |              |
| CUDA_HOST_COMPILATION_CPP              | ON      |             |              |
| CUDA_PROPAGATE_HOST_FLAGS              | ON      |             |              |
| CUDA_SEPARABLE_COMPILATION             | OFF     |             |              |
| CUDA_VERBOSE_BUILD                     | OFF     |             |              |

[Go back to overview](#external-options)

### Eigen

| Option                               | Default | Description | Link to file |
|--------------------------------------|---------|-------------|--------------|
| EIGEN_DEBUG_ASSERTS                  | OFF     |             |              |
| EIGEN_DEFAULT_TO_ROW_MAJOR           | OFF     |             |              |
| EIGEN_FAILTEST                       | OFF     |             |              |
| EIGEN_INTERNAL_DOCUMENTATION         | OFF     |             |              |
| EIGEN_NO_ASSERTION_CHECKING          | OFF     |             |              |
| EIGEN_SPLIT_LARGE_TESTS              | ON      |             |              |
| EIGEN_TEST_32BIT                     | OFF     |             |              |
| EIGEN_TEST_BUILD_DOCUMENTATION       | OFF     |             |              |
| EIGEN_TEST_CUDA                      | OFF     |             |              |
| EIGEN_TEST_CUDA_CLANG                | OFF     |             |              |
| EIGEN_TEST_CXX1                      | OFF     |             |              |
| EIGEN_TEST_EIGEN2                    | OFF     |             |              |
| EIGEN_TEST_NOQT                      | OFF     |             |              |
| EIGEN_TEST_NO_EXCEPTIONS             | OFF     |             |              |
| EIGEN_TEST_NO_EXPLICIT_ALIGNMENT     | OFF     |             |              |
| EIGEN_TEST_NO_EXPLICIT_VECTORIZATION | OFF     |             |              |
| EIGEN_TEST_NO_OPENGL                 | OFF     |             |              |
| EIGEN_TEST_OPENMP                    | OFF     |             |              |
| EIGEN_TEST_SSE2                      | OFF     |             |              |
| EIGEN_TEST_SYCL                      | OFF     |             |              |
| EIGEN_TESTX87                        | OFF     |             |              |

[Go back to overview](#external-options)

### Glew

| Option      | Default | Description | Link to file |
|-------------|---------|-------------|--------------|
| GLEW_OSMESA | OFF     |             |              |
| GLEW_REGAL  | OFF     |             |              |

[Go back to overview](#external-options)

### Gtest

| Option                                       | Default | Description | Link to file |
|----------------------------------------------|---------|-------------|--------------|
| INSTALL_GTEST                                | ON      |             |              |
| gtest_build_samples                          | OFF     |             |              |
| gtest_build_tests                            | OFF     |             |              |
| gtest_disable_pthreads                       | OFF     |             |              |
| gtest_force_shared_crt                       | OFF     |             |              |
| gtest_hide_internal_symbols                  | OFF     |             |              |

[Go back to overview](#external-options)

### MPI

| Option                                       | Default | Description | Link to file |
|----------------------------------------------|---------|-------------|--------------|
| MPI_CXX_SKIP_MPICSS                          | OFF     |             |              |

[Go back to overview](#external-options)
