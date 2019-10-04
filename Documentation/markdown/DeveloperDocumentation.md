# Steps

1.  Clone the repository
2.  Open CMake
    2.1. Click "Browse Source" and select the cloned repository. %TODO: Insert images
    2.2. Click "Browse Build" and select a build directory outside the source directory. %TODO: Insert image
    2.3. Click "Configure".
    2.4. Select the Generator
        2.4.1   Select "Visual Studio 14 2015 Win64" or "Visual Studio 15 2017 Win64" for CMake Version < 3.14.x
        2.4.2   Select "Visual Studio 14 2015" or "Visual Studio 15 2017" for CMake Version > 3.13.x and platform "Win64"
        2.4.3   If using "Visual Studio 14 2015" or "Visual Studio 14 2015 Win64" use "host=x64" under additional toolset.
    