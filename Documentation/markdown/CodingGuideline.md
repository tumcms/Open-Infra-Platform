# Coding Guideline for Developers

***
## Info

This document is incomplete. It has been compiled at the beginning of the great refactor, starting April 2020.

**NOTE:** A lot of code is legacy code and has not yet been approved or refactored. A good rule of thumb is: 
> no doxy-like comment => no refactor

***
## General Guidelines

* A function serves one purpose and one purpose only.
* Ideally, a function is not longer than 10 lines of code.
* Function's name is descriptive and requires no guessing as to what it does.
* Each function and class has a doxy comment according to the [guidelines](./DoxygenHelp.md).

***
## Geometry Converter

The main task of the elements within `IfcGeometryConverter` namespace is transforming the definitions of IFC to sequences of points, lines and/or meshes to be consumed by the shader. 

Function input: `const EXPRESSReference<IfcEntity>&`, additional parameters.
Function output: `carve::geom::vector<3>` or similar objects (multiple return object as `std::tuple<...>`).

### Unit conversion

OpenInfraPlatform assumes everything is in SI units (e.g. meters, radians).

IFC content is scaled according to the specified units within the file.
The conversion factors can be obtained with `UnitConvert()` member of conversion classes.

**NOTE:** Abide by this rule:
> Any `IFC` entity or content has not been scaled, every `carve` entity has been scaled.

### Tessellation and precision

The curved content is tessellated for the shader according to the precision settings within the IFC file.
These can be accessed with `GeomSettings()` member of conversion classes.

### Case: IFC entity not supported

If an entity is not supported, the code should throw `UnhandledException`.

### Case: Entity definition changed between IFC versions

If the definition of the entity has changed between versions, these steps need to be followed:
* Define a function that handles this case specifically.
* Provide the specific implementation as a [template specialization](https://de.cppreference.com/w/cpp/language/template_specialization).
**NOTE:** This needs to be enclosed in `#ifdef` with the corresponding IFC version.
* Do not forget to provide a general implementation.

For an example, see function `PlacementConverterT::GetCurveOfPlacement`.

***
## Data management

ToDo:
Here comes the descriptions for the data management part of Core.
