# TUM Open Infra Platform

[![status](https://joss.theoj.org/papers/ab5757cf53fc55c74f4948e8b336a7ca/status.svg)](https://joss.theoj.org/papers/ab5757cf53fc55c74f4948e8b336a7ca)

## Info

`TUM Open Infra Platform` (OIP in short) is a software for checking and viewing IFC data. 
It comes with its own `EXPRESS` parser and `C++` classes generator.

The whole software underwent major overhaul as described by [Hecht & Jaud (2019)](./Documentation/2019_Hecht_Jaud_FBI.pdf).
As a consequence, OIP can be used in two ways:

1. Using the installer which corresponds to the frozen state of the `master` branch from 2018:

![Beta1_5_Windows8_1.png](./Documentation/images/Beta1_5_Windows8_1.png)

2. Compiling the newest developments yourself on the `development` branch - see below for instructions.

## News

See [Release Notes](Documentation/markdown/ReleaseNotes.md)

## Documentation

- [Building OIP on your machine](Documentation/markdown/SetupHelp.md)
- [Software Architecture](Documentation/markdown/SoftwareArchitecture.md)
- [CMake Options Documentation](Documentation/markdown/CMakeOptions.md)
- [Unit Tests](Documentation/markdown/UnitTests.md)
- [Git process Guideline](Documentation/markdown/GitProcess.md)
- [Coding Guideline](Documentation/markdown/CodingGuideline.md)
- [Doxymentation Guideline](Documentation/markdown/DoxygenHelp.md)
- [List of Contributors](Documentation/markdown/Contributors.md)
- [Tools for unit testing and QA](Documentation/markdown/MiniApps.md)

Out-of-sync:

[Installation, Usage & Updating](Documentation/markdown/User.md)

## Operating Sytems
Currently, TUM Open Infra Platform only supports machines running on Windows. However, Linux support is considered for the future.

## License

See [TUM Open Infra Platform's license](./LICENSE) and [third party licenses](./Licenses/readme.md).
