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

| Entity                                | Covered              | Converter                  | Unit test             | Issue |
|---------------------------------------|----------------------|----------------------------|-----------------------|-------|
| `IfcAdvancedBrep`                     | :clock9:             | `SolidModelConverter`      | -                     | -     |
| `IfcAdvancedBrepWithVoids`            | :clock9:             | `SolidModelConverter`      | -                     | -     |
| `IfcAlignmentCurve`                   | :heavy_check_mark:   | `CurveConverter`           | -                     | -     |
| `IfcAnnotationFillArea`               | :x:                  | -                          | -                     | -     |
| `IfcAxis1Placement`                   | :clock9:             | `PlacementConverter`       | -                     | -     |
| `IfcAxis2Placement2D`                 | :heavy_check_mark:   | `PlacementConverter`       | -                     | -     |
| `IfcAxis2Placement3D`                 | :heavy_check_mark:   | `PlacementConverter`       | -                     | -     |
| `IfcAxis2PlacementLinear`             | :x:                  | `PlacementConverter`       | -                     | -     |
| `IfcBlock`                            | :heavy_check_mark:   | `SolidModelConverter`      | -                     | -     |
| `IfcBlossCurve`                       | :x:                  | `CurveConverter`           | -                     | -     |
| `IfcBooleanClippingResult`            | :clock9:             | `SolidModelConverter`      | -                     | -     |
| `IfcBooleanResult`                    | :heavy_check_mark:   | `SolidModelConverter`      | -                     | -     |
| `IfcBoundedCurve`                     | :heavy_check_mark:   | `CurveConverter`           | -                     | -     |
| `IfcBoundingBox`                      | :heavy_check_mark:   | `SolidModelConverter`      | -                     | -     |
| `IfcBoxedHalfSpace`                   | :clock9:             | `SolidModelConverter`      | -                     | -     |
| `IfcBSplineCurveWithKnots`            | :heavy_check_mark:   | `SplineConverter.`         | -                     | -     |
| `IfcCartesianPoint`                   | :heavy_check_mark:   | `PlacementConverter`       | :heavy_check_mark:    | -     |
| `IfcCartesianPointList2D`             | :heavy_check_mark:   | `CurveConverter`           | -                     | -     |
| `IfcCartesianPointList3D`             | :heavy_check_mark:   | `CurveConverter`           | -                     | -     |
| `IfcCartesianTransformationOperator2D`| :heavy_check_mark:   | `PlacementConverter`       | -                     | -     |
| `IfcCartesianTransformationOperator3D`| :heavy_check_mark:   | `PlacementConverter`       | -                     | -     |
| `IfcCartesianTransformationOperator2DnonUniform` | :heavy_check_mark:   | `PlacementConverter`       | -                     | -     |
| `IfcCircle`                           | :heavy_check_mark:   | `CurveConverter`           | -                     | -     |
| `IfcCircularArcSegment2D`             | :heavy_check_mark:   | `CurveConverter`           | -                     | -     |
| `IfcClothoid`                         | :x:                  | `CurveConverter`           | -                     | [#304](https://github.com/tumcms/Open-Infra-Platform/issues/304) |
| `IfcCompositeCurve`                   | :heavy_check_mark:   | `CurveConverter`           | -                     | -     |
| `IfcCompositeCurveOnSurface`          | :x:                  | -                          | -                     | -     |
| `IfcCompositeCurveSegment`            | :x:                  | `CurveConverter`           | -                     | -     |
| `IfcCsgSolid`                         | :heavy_check_mark:   | `SolidModelConverter`      | -                     | -     |
| `IfcCurveSegment`                     | :x:                  | `CurveConverter`           | -                     | -     |
| `IfcDirection`                        | :heavy_check_mark:   | `PlacementConverter`       | -                     | -     |
| `IfcEllipse`                          | :heavy_check_mark:   | `CurveConverter`           | -                     | -     |
| `IfcExtrudedAreaSolid`                | :heavy_check_mark:   | `SolidModelConverter`      | -                     | -     |
| `IfcExtrudedAreaSolidTapered`         | :x:                  | -                          | -                     | -     |
| `IfcFaceBasedSurfaceModel`            | :heavy_check_mark:   | `FaceConverter`            | -                     | -     |
| `IfcFacetedBrep`                      | :x:                  | `SolidModelConverter`      | -                     | -     |
| `IfcFacetedBrepWithVoids`             | :x:                  | `SolidModelConverter`      | -                     | -     |
| `IfcFillAreaStyleHatching`            | :x:                  | -                          | -                     | -     |
| `IfcFillAreaStyleTiles`               | :x:                  | -                          | -                     | -     |
| `IfcFixedReferenceSweptAreaSolid`     | :x:                  | `SolidModelConverter`      | -                     | -     |
| `IfcGeometricCurveSet`                | :x:                  | -                          | -                     | -     |
| `IfcGeometricSet`                     | :heavy_check_mark:   | `RepresentationConverter`  | -                     | -     |
| `IfcGradientCurve`                    | :x:                  | `CurveConverter`           | -                     | -     |
| `IfcHalfSpaceSolid`                   | :clock9:             | `SolidModelConverter`      | -                     | -     |
| `IfcIndexedPolyCurve`                 | :heavy_check_mark:   | `CurveConverter`           | -                     | -     |
| `IfcIntersectionCurve`                | :x:                  | -                          | -                     | -     |
| `IfcLightSourceAmbient`               | :x:                  | -                          | -                     | -     |
| `IfcLightSourceDirectional`           | :x:                  | -                          | -                     | -     |
| `IfcLightSourceGoniometric`           | :x:                  | -                          | -                     | -     |
| `IfcLightSourcePositional`            | :x:                  | -                          | -                     | -     |
| `IfcLightSourceSpot`                  | :x:                  | -                          | -                     | -     |
| `IfcLine`                             | :heavy_check_mark:   | `CurveConverter`           | -                     | -     |
| `IfcLineSegment2D`                    | :heavy_check_mark:   | `CurveConverter`           | -                     | -     |
| `IfcOffsetCurve2D`                    | :x:                  | -                          | -                     | -     |
| `IfcOffsetCurve3D`                    | :x:                  | -                          | -                     | -     |
| `IfcOffsetCurveByDistances`           | :x:                  | -                          | -                     | -     |
| `IfcOrientationExpression`            | :x:                  | -                          | -                     | -     |
| `IfcOuterBoundaryCurve`               | :x:                  | -                          | -                     | -     |
| `IfcPcurve`                           | :heavy_check_mark:   | `CurveConverter`           | -                     | -     |
| `IfcPlanarExtent`                     | :x:                  | -                          | -                     | -     |
| `IfcPlanarBox`                        | :x:                  | -                          | -                     | -     |
| `IfcPointByDistanceExpression`        | :x:                  | `PlacementConverter`       | -                     | -     |
| `IfcPointOnCurve`                     | :x:                  | -                          | -                     | [#359](https://www.github.com/tumcms/Open-Infra-Platform/issues/359) |
| `IfcPolyline`                         | :heavy_check_mark:   | `CurveConverter`           | -                     | -     |
| `IfcPolyline`                         | :heavy_check_mark:   | `CurveConverter`           | -                     | -     |
| `IfcPolygonalBoundedHalfSpace`        | :clock9:             | `CurveConverter`           | -                     | -     |
| `IfcRationalBSplineCurveWithKnots`    | :heavy_check_mark:   | `SplineConverter.`         | -                     | -     |
| `IfcRectangularPyramid`               | :heavy_check_mark:   | `SolidModelConverter`      | -                     | -     |
| `IfcReparametrisedCompositeCurveSegment`| :x:                  | -                          | -                     | -     |
| `IfcRevolvedAreaSolid`                | :heavy_check_mark:   | `SolidModelConverter`      | -                     | -     |
| `IfcRevolvedAreaSolidTapered`         | :x:                  | -                          | -                     | -     |
| `IfcRightCircularCone`                | :heavy_check_mark:   | `SolidModelConverter`      | -                     | -     |
| `IfcRightCircularCylinder`            | :heavy_check_mark:   | `SolidModelConverter`      | -                     | -     |
| `IfcSeamCurve`                        | :x:                  | -                          | -                     | -     |
| `IfcSectionedSolid`                   | :heavy_check_mark:   | `SolidModelConverter`      | -                     | -     |
| `IfcSectionedSolidHorizontal`         | :heavy_check_mark:   | `SolidModelConverter`      | :heavy_check_mark:    | -     |
| `IfcSectionedSpine`                   | :x:                  | `RepresentationConverter`  | -                     | -     |
| `IfcSegmentedReferenceCurve`          | :x:                  | `CurveConverter`           | -                     | -     |
| `IfcSeriesParameterCurve`             | :x:                  | `CurveConverter`           | -                     | -     |
| `IfcShellBasedSurfaceModel`           | :heavy_check_mark:   | `FaceConverter`            | -                     | -     |
| `IfcSphere`                           | :heavy_check_mark:   | `SolidModelConverter`      | -                     | -     |
| `IfcSurfaceCurve`                     | :heavy_check_mark:   | `CurveConverter`           | -                     | -     |
| `IfcSurfaceCurveSweptAreaSolid`       | :heavy_check_mark:   | `SolidModelConverter`      | -                     | -     |
| `IfcSweptDiskSolid`                   | :heavy_check_mark:   | `SolidModelConverter`      | -                     | -     |
| `IfcSweptDiskSolidPolygonal`          | :x:                  | `SolidModelConverter`      | -                     | -     |
| `IfcTransitionCurveSegment2D`         | :heavy_check_mark:   | `CurveConverter`           | -                     | -     |
| `IfcTrimmedCurve`                     | :heavy_check_mark:   | `CurveConverter`           | -                     | -     |