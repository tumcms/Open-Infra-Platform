# OpenInfraPlatform Installation 

***
## Prerequisites 

Before you can proceed to the Installation of **OpenInfraPlatform**, there are several steps, which have to be done before Installation: 

1. Installation of **Visual Studio 2017** - 
2. Installation of **CMake** -
3. Installation of **Git** - 
4. Creation of **GitHub account**
5. Clone the **OpenInfraPlatform** repository - All the information you will find [here](./GitProcess.md)
6. Installation of **Qt** -
7. Installation of **Boost** -

***
## Installation 

## CMake 

1. Open your CMake.
2. In the line **Where is the source code:** copy the path to your source (e.g. C:\dev\Open-Infra-Platform).
3. In the line **Where to build the binaries:**  copy the path to other folder (e.g. C:\dev\project_OIP). **NOTE:** This folder can not be in the **Open-Infra-Platform** folder as well as in the **Program Files** and **Windows** folders.
4. Put a tick in the both check boxes *Grouped* and *Advanced*.
5. Click *Configure*. 
6. Select the Generator:
	* Select "Visual Studio 15 2017 Win64".
	* Select "x64"
	* Select "host=x64".

![](./fig/CMake_Installation_settings.png)

7. After configuration process is done click *Generate*.

***
## Buildng your OpenInfraPlatform in Visual Studio (+ CMake)

1. After generation process is done click *open Project*. It will opens OpenInfraPlatform in the Visual Studio.
2. In the right corner open **OpenInfraPlatform** project folder. Find folder **Commands**. In the folder **Commands** select file **OpenInfraPlatform.Commands.UpdateBoostMpl**. Right click on this file and select *Build*.
3. After first file is succesfully built find folder **ExpressBindingGenerator**. Select file **OpenInfraPlatform.ExpressBindingGenerator** and *build* it.
4. In the folder **ExpressBindingGenerator** find folder **Commands**. There you should select file **Commands.GenerateEarlyBinding.IFC4X3_RC1** and *build* it.
5. Open CMake and select *Generate*.
6. Open again Visual Studio and open folder **EarlyBinding**. Select file **OpenInfraPlatform.IFC4X3_RC1** and *build* it.
7. Select file **OpenInfraPlatform.Core** and *build* it.
8. Select file **OpenInfraPlatform.UI** and *build* it.