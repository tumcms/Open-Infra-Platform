# Coding Guideline for Developers

***
## Info

This document is incomplete. It has been compiled at the beginning of the great refactor, starting April 2020.

**NOTE:** A lot of code is legacy code and has not yet been approved or refactored. A good rule of thumb is: 
> no doxy-like comment => no refactor has occured

***
## Conventions

### Functions

* A function serves one purpose and one purpose only.
* Ideally, a function is not longer than 10 lines of code.
* Function's name is descriptive and requires no guessing as to what it does.
* Name starts with a small letter and follows CamelCase convention.
* Each function and class has a doxy comment according to the [guidelines](./DoxygenHelp.md).

### Member variable

* The name is post-pended with `_` (underscore).
* Private with a public getter and optional setter.
* Name starts with a small letter and follows CamelCase convention.

***
## Geometry Converter

The main task of the elements within `IfcGeometryConverter` namespace is transforming the definitions of IFC to sequences of points, lines and/or meshes to be consumed by the shader. 

### Function signature

- Input: `const EXPRESSReference<IfcEntity>&`
- Input: additional parameters
- Output: `carve` objects (`carve::geom::vector<3>` or similar)
- Output: multiple return object of different type as `std::tuple<...>`

### Unit conversion

Open Infra Platform assumes everything is in SI units (e.g. meters, radians).

IFC content is scaled according to the specified units within the file.
The conversion factors can be obtained with `UnitConvert()` member of conversion classes.

**NOTE:** Abide by this rule:
> Any `IFC` entity or content has not been scaled, every `carve` entity has been scaled.

### Tessellation and precision

The curved content is tessellated for the shader according to the precision settings within the IFC file.
These can be accessed with `GeomSettings()` member of conversion classes.

### Case: Entity definition changed between IFC versions

If the definition of the entity has changed between versions, these steps need to be followed:
* First, provide a general implementation.
* Define a function that handles this case specifically.
* Provide the specific implementation as a [template specialization](https://de.cppreference.com/w/cpp/language/template_specialization).
**NOTE:** This needs to be enclosed in `#ifdef` with the corresponding IFC version.

Example: see function `PlacementConverterT::GetCurveOfPlacement`.

***
## Exceptions

### Case: IFC entity not supported

If an entity is not supported, the code should throw `oip::UnhandledException`.

### Case: Inconsistent geometry

If the calculated geometry is inconsistent, the code should throw `oip::InconsistentGeometryException`.

Examples: 
- `IfcCartesianPoint` can have `[1..3]` coordinate values. Any other number constitutes an exception.
- `IfcLinearPlacement` has an attribute `CartesianPosition` that provides the 3D position of the reference point. If this position does not agree with the position linearly referenced (attributes `DistanceAlong` and `Distance`), an exception is thrown.

### Case: Inconsistent model data

If there is a problem with the data in the IFC file, the code should throw `oip::InconsistentModellingException`.

Example:
- `ÌfcLinearPlacement` can only use an `IfcBoundedCurve` as its `Directrix` although the schema allows for `IfcCurve`. If that is not the case, an exception is thrown.

***
## Data management

ToDo:
Here comes the descriptions for the data management part of Core.
