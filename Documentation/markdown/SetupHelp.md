# OpenInfraPlatform Installation 

***
## Prerequisites 

Before you can proceed to the Installation of **OpenInfraPlatform**, check, if these steps are completed:

1. **Visual Studio 2017** is installed to your computer - Viusal Studio 2017 you will find [here](https://my.visualstudio.com/Downloads?q=visual%20studio%202017&wt.mc_id=o~msft~vscom~older-downloads)
2. **CMake 3.17.0** is installed - CMake 3.17.0 you will find [here](https://cmake.org/download/)
3. **Qt 5.12.1** is installed and included in path - Qt 5.12.1 you will find [here](https://www.qt.io/download-open-source)
4. **Boost 1_65_1** is installed and included in path - Boost 1_65_1 you will find [here](https://sourceforge.net/projects/boost/files/boost-binaries/1.65.1/boost_1_65_1-msvc-14.1-64.exe/download)
5. **OpenInfraPlatform** repository is cloned to your computer - All the information you will find [here](./GitProcess.md)

***
## Installation 

## CMake 

1. Open your CMake.
2. In the line **Where is the source code:** copy the path to your source (e.g. C:\dev\Open-Infra-Platform).
3. In the line **Where to build the binaries:**  copy the path to another folder (e.g. C:\dev\project_OIP). **NOTE:** This folder cannot be in the **Open-Infra-Platform** folder as well as in the **Program Files** and **Windows** folders.
4. Put a tick in the both check boxes *Grouped* and *Advanced*.
5. Click *Configure*. 
6. Select the Generator:
	* Select "Visual Studio 15 2017 Win64".
	* Select "x64"
	* Select "host=x64".

![](./fig/CMake_Installation_settings.png)

7. After configuration process is done click *Generate*.

***
## Building your OpenInfraPlatform in Visual Studio (+ CMake)

1. After generation process is done click *open Project*. It will open OpenInfraPlatform in the Visual Studio.
2. In the *project browser* open **OpenInfraPlatform** project folder. Find folder **Commands**. In the folder **Commands** select project **OpenInfraPlatform.Commands.UpdateBoostMpl**. Right click on this file and select *Build*.
3. After first project is succesfully built find folder **ExpressBindingGenerator**. Select project **OpenInfraPlatform.ExpressBindingGenerator** and *build* it.
4. In the folder **ExpressBindingGenerator** find folder **Commands**. There you should select project **Commands.GenerateEarlyBinding.IFC4X3_RC1** and *build* it.
5. **Improtant**: Open CMake and select *Generate*.
6. Open again Visual Studio and open folder **EarlyBinding**. Select project **OpenInfraPlatform.IFC4X3_RC1** and *build* it.
7. Select project **OpenInfraPlatform.Core** and *build* it.
8. Select project **OpenInfraPlatform.UI** and *build* it.
