# OpenInfraPlatform Installation 

***
## Prerequisites 

Before you can proceed to the Installation of **OpenInfraPlatform**, check, if these steps are completed:

1. **Visual Studio 2017** is installed to your computer - find [here](https://my.visualstudio.com/Downloads?q=visual%20studio%202017&wt.mc_id=o~msft~vscom~older-downloads)
2. **CMake 3.17.0** is installed - find [here](https://cmake.org/download/)
3. **Qt 5.12.1** is installed and included in path -  find [here](https://www.qt.io/download-open-source)
	-binaries x64 msvc2017 
	-mingw
4. **Boost 1_65_1** is installed and included in path -  find [here](https://sourceforge.net/projects/boost/files/boost-binaries/1.65.1/boost_1_65_1-msvc-14.1-64.exe/download)
5. **Anaconda 2** 


***
## Setup

### Download source code 

 Clone **OpenInfraPlatform** repository  - more information you can find [here](./GitProcess.md)

### Preparing solution 

1. Open CMake.
2. In the line **Where is the source code:** copy the path to your source folder (e.g. C:\dev\Open-Infra-Platform).
3. In the line **Where to build the binaries:**  copy the path to the binaries folder (e.g. C:\dev\project_OIP). **NOTE:** This folder cannot be in the source folder as well as in the **Program Files** and **Windows** folders.
4. Put a tick in the both check boxes *Grouped* and *Advanced*.
5. Click *Configure*. 
6. Select the Generator:
	* Select "Visual Studio 15 2017 Win64".
	* Select "x64"
	* Write "host=x64".

![](./fig/CMake_Installation_settings.png)

7. Choose the options according to [this](./BuildOptions.md)
8. After configuration process has successfully finished, click *Generate*.
9. After generation process is done click *open Project*. It will open OpenInfraPlatform in the Visual Studio.
***
## Building the OpenInfraPlatform in Visual Studio 

### Generating IFC early binding

**NOTE:** If you are using Open-Infra-Platform only with point clouds, you can skip these steps.

1. In the *project browser* open **OpenInfraPlatform** project folder. Find folder **Commands**. In the folder **Commands** *build*  **OpenInfraPlatform.Commands.UpdateBoostMpl**. **NOTE:** This only is to be done only for the first time. 
2. After first project is succesfully built find folder **ExpressBindingGenerator**. *Build* project **OpenInfraPlatform.ExpressBindingGenerator**.
3. In the folder **ExpressBindingGenerator** find folder **Commands**. There you should *build* project **Commands.GenerateEarlyBinding.IFC?**.
4. **Important**: Open CMake and select *Generate* to include newly generated IFC early binding code in the solution.

### Compiling user interface

**NOTE:** Build dependencies are set, so building only the last step should automatically build all.

1. Open Visual Studio and find folder **EarlyBinding**. *Build* project **OpenInfraPlatform.IFC?**.
2. If you are using point clouds *build* project **OpenInfraPlatform.PointCloudProcessing**
3. *Build* project **OpenInfraPlatform.Core**.
4. *Build* project **OpenInfraPlatform.UI**.
