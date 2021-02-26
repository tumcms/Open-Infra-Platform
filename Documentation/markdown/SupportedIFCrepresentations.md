# List of supported IFC entities

This documents lists the supported IFC entities.

## Legend

| code | symbol | meaning |
|-----|-----|-----|
| `:heavy_check_mark:` | :heavy_check_mark: | yes |
| `:x:` | :x: | no |
| `:clock9:` | :clock9: | unclear |

## IfcRepresentationItem

All `IfcRepresentationItem`s are handled by `OpenInfraPlatform.Core` project, within the `IfcGeometryConverter` folder.

Meaning of columns:

| Column | Meaning |
|--------|---------|
| Entity | the `IFC` entity, in alphabetical order |
| Covered | does OIP handle the entity; denoted by symbol, see [legend above](#legend) |
| Converter | which converter class handles the entity |
| Unit test | does OIP have unit tests for this entity; denoted by symbol, see [legend above](#legend) |
| Issue | Link to corresponding open issue(s) |

| Entity                | Covered              | Converter                  | Unit test             | Issue |
|-----------------------|----------------------|----------------------------|-----------------------|-------|
| `IfcCartesianPoint`   | :heavy_check_mark:   | `PlacementConverter`       | :heavy_check_mark:    | -     |
| `IfcPointOnCurve`     | :x:                  | -                          | -                     | [#359](github.com/tumcms/Open-Infra-Platform/issues/359) |
