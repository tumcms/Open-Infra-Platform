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
| `IfcAdvancedBrep`                     | :heavy_check_mark:   | `SolidModelConverter`      | :heavy_check_mark:    | -     |
| `IfcAdvancedBrepWithVoids`            | :x:                  | `SolidModelConverter`      | -                     | -     |
| `IfcAdvancedFace`                     | :heavy_check_mark:   | `SolidModelConverter`      | :heavy_check_mark:    | -     |
| `IfcAlignmentCurve`                   | :heavy_check_mark:   | `CurveConverter`           | :heavy_check_mark:    | -     |
| `IfcAnnotationFillArea`               | :x:                  | -                          | -                     | -     |
| `IfcAxis1Placement`                   | :heavy_check_mark:   | `PlacementConverter`       | :heavy_check_mark:    | -     |
| `IfcAxis2Placement2D`                 | :heavy_check_mark:   | `PlacementConverter`       | :heavy_check_mark:    | -     |
| `IfcAxis2Placement3D`                 | :heavy_check_mark:   | `PlacementConverter`       | :heavy_check_mark:    | -     |
| `IfcAxis2PlacementLinear`             | :x:                  | `PlacementConverter`       | -                     | -     |
| `IfcBlock`                            | :heavy_check_mark:   | `SolidModelConverter`      | :heavy_check_mark:    | -     |
| `IfcBlossCurve`                       | :x:                  | `CurveConverter`           | -                     | -     |
| `IfcBooleanClippingResult`            | :heavy_check_mark:   | `SolidModelConverter`      | :x:                   | -     |
| `IfcBooleanResult`                    | :heavy_check_mark:   | `SolidModelConverter`      | :heavy_check_mark:    | -     |
| `IfcBoundedCurve`                     | :heavy_check_mark:   | `CurveConverter`           | :x:                   | -     |
| `IfcBoundingBox`                      | :heavy_check_mark:   | `SolidModelConverter`      | :x:                   | -     |
| `IfcBoxedHalfSpace`                   | :x:                  | `SolidModelConverter`      | -                     | -     |
| `IfcBSplineCurveWithKnots`            | :heavy_check_mark:   | `SplineConverter`          | :heavy_check_mark:    | -     |
| `IfcBSplineSurfaceWithKnots`          | :heavy_check_mark:   | `SplineConverter`          | :heavy_check_mark:    | -     |
| `IfcCartesianPoint`                   | :heavy_check_mark:   | `PlacementConverter`       | :heavy_check_mark:    | -     |
| `IfcCartesianPointList2D`             | :heavy_check_mark:   | `CurveConverter`           | :x:                   | -     |
| `IfcCartesianPointList3D`             | :heavy_check_mark:   | `CurveConverter`           | :heavy_check_mark:    | -     |
| `IfcCartesianTransformationOperator2D`| :heavy_check_mark:   | `PlacementConverter`       | :x:                   | -     |
| `IfcCartesianTransformationOperator3D`| :heavy_check_mark:   | `PlacementConverter`       | :heavy_check_mark:    | -     |
| `IfcCartesianTransformationOperator2DnonUniform` | :heavy_check_mark:   | `PlacementConverter`       | :x:                   | -     |
| `IfcCircle`                           | :heavy_check_mark:   | `CurveConverter`           | :heavy_check_mark:    | -     |
| `IfcCircularArcSegment2D`             | :heavy_check_mark:   | `CurveConverter`           | :heavy_check_mark:    | -     |
| `IfcClosedShell`                      | :heavy_check_mark:   | `SolidModelConverter`      | :heavy_check_mark:    | -     |
| `IfcClothoid`                         | :heavy_check_mark:   | `CurveConverter`           | :x:                   | [#304](https://github.com/tumcms/Open-Infra-Platform/issues/304) |
| `IfcCompositeCurve`                   | :heavy_check_mark:   | `CurveConverter`           | :x:                   | -     |
| `IfcCompositeCurveOnSurface`          | :x:                  | -                          | -                     | -     |
| `IfcCompositeCurveSegment`            | :heavy_check_mark:   | `CurveConverter`           | :x:                   | -     |
| `IfcConnectedFaceSet`                 | :x:                  | 'RepresentationConverter'  | -                     | -     |
| `IfcCosine`                           | :x:                  | `CurveConverter`           | :x:                   |[#524](https://github.com/tumcms/Open-Infra-Platform/issues/524)|  
| `IfcCsgSolid`                         | :heavy_check_mark:   | `SolidModelConverter`      | :heavy_check_mark:    | -     |
| `IfcCurveBoundedPlane`                | :heavy_check_mark:   | `FaceConverter`            | :x:                   | -     |
| `IfcCurveBoundedSurface`              | :heavy_check_mark:   | `FaceConverter`            | :x:                   | [#150](https://github.com/tumcms/Open-Infra-Platform/issues/150) |
| `IfcCurveSegment`                     | :x:                  | `CurveConverter`           | -                     | -     |
| `IfcCylindricalSurface`               | :x:                  | `FaceConverter`            | -                     | [#150](https://github.com/tumcms/Open-Infra-Platform/issues/150) |
| `IfcDirection`                        | :heavy_check_mark:   | `PlacementConverter`       | :heavy_check_mark:    | -     |
| `IfcEdge`                             | :heavy_check_mark:   | `CurveConverter`           | :heavy_check_mark:    | -     |
| `IfcEdgeCurve`                        | :heavy_check_mark:   | `CurveConverter`           | :x:                   | -     |
| `IfcEdgeLoop`                         | :heavy_check_mark:   | `CurveConverter`           | :x:                   | -     |
| `IfcEllipse`                          | :heavy_check_mark:   | `CurveConverter`           | :x:                   | -     |
| `IfcExtrudedAreaSolid`                | :heavy_check_mark:   | `SolidModelConverter`      | :heavy_check_mark:    | -     |
| `IfcExtrudedAreaSolidTapered`         | :x:                  | -                          | -                     | -     |
| `IfcFace`                             | :heavy_check_mark:   | `FaceConverter`            | :heavy_check_mark:    | -     |
| `IfcFaceBasedSurfaceModel`            | :heavy_check_mark:   | `FaceConverter`            | :heavy_check_mark:    | -     |
| `IfcFaceBound`                        | :heavy_check_mark:   | `FaceConverter`            | :heavy_check_mark:    | -     |
| `IfcFaceSurface`                      | :heavy_check_mark:   | `FaceConverter`            | :x:                   | -     |
| `IfcFacetedBrep`                      | :heavy_check_mark:   | `SolidModelConverter`      | :heavy_check_mark:    | -     |
| `IfcFacetedBrepWithVoids`             | :x:                  | `SolidModelConverter`      | -                     | [#143](https://github.com/tumcms/Open-Infra-Platform/issues/143) |
| `IfcFaceOuterBound`                   | :heavy_check_mark:   | `FaceConverter`            | :heavy_check_mark:    | -     |
| `IfcFillAreaStyleHatching`            | :x:                  | -                          | -                     | -     |
| `IfcFillAreaStyleTiles`               | :x:                  | -                          | -                     | -     |
| `IfcFixedReferenceSweptAreaSolid`     | :heavy_check_mark:   | `SolidModelConverter`      | :heavy_check_mark:    | -     |
| `IfcGeometricCurveSet`                | :heavy_check_mark:   | 'RepresentationConverter'  | :x:                   | -     |
| `IfcGeometricSet`                     | :heavy_check_mark:   | `RepresentationConverter`  | :x:                   | -     |
| `IfcGradientCurve`                    | :x:                  | `CurveConverter`           | -                     | -     |
| `IfcHalfSpaceSolid`                   | :x:                  | `SolidModelConverter`      | -                     | -     |
| `IfcIndexedPolyCurve`                 | :heavy_check_mark:   | `CurveConverter`           | :heavy_check_mark:    | -     |
| `IfcIndexedPolygonalFace`             | :heavy_check_mark:   | `FaceConverter`            | :heavy_check_mark:    | -     |
| `IfcIndexedPolygonalFaceWithVoids`    | :heavy_check_mark:   | `FaceConverter`            | :heavy_check_mark:    | -     |
| `IfcIntersectionCurve`                | :x:                  | -                          | -                     | -     |
| `IfcLightSourceAmbient`               | :x:                  | -                          | -                     | -     |
| `IfcLightSourceDirectional`           | :x:                  | -                          | -                     | -     |
| `IfcLightSourceGoniometric`           | :x:                  | -                          | -                     | -     |
| `IfcLightSourcePositional`            | :x:                  | -                          | -                     | -     |
| `IfcLightSourceSpot`                  | :x:                  | -                          | -                     | -     |
| `IfcLine`                             | :heavy_check_mark:   | `CurveConverter`           | :x:                   | -     |
| `IfcLineSegment2D`                    | :heavy_check_mark:   | `CurveConverter`           | :heavy_check_mark:    | -     |
| `IfcLoop`                             | :heavy_check_mark:   | `CurveConverter`           | :x:                   | -     |
| `IfcMappedItem`                       | :heavy_check_mark:   | `RepresentationConverter`  | :heavy_check_mark:    | -     |
| `IfcOffsetCurve2D`                    | :x:                  | -                          | -                     | -     |
| `IfcOffsetCurve3D`                    | :x:                  | -                          | -                     | -     |
| `IfcOffsetCurveByDistances`           | :x:                  | -                          | -                     | -     |
| `IfcOpenShell`                        | :x:                  | -                          | -                     | -     |
| `IfcOrientationExpression`            | :heavy_check_mark:   | `PlacementConverter`       | :x:                   | -     |
| `IfcOrientedEdge`                     | :x:                  | -                          | -                     | -     |
| `IfcOuterBoundaryCurve`               | :x:                  | -                          | -                     | -     |
| `IfcPath`                             | :x:                  | `RepresentationConverter`  | -                     | -     |
| `IfcPcurve`                           | :heavy_check_mark:   | `CurveConverter`           | :x:                   | -     |
| `IfcPlanarExtent`                     | :x:                  | `FaceConverter`            | -                     | -     |
| `IfcPlanarBox`                        | :heavy_check_mark:   | `FaceConverter`            | :x:                   | -     |
| `IfcPlane`                            | :heavy_check_mark:   | `FaceConverter`            | :x:                   | -     |
| `IfcPointByDistanceExpression`        | :heavy_check_mark:   | `PlacementConverter`       | :x:                   | -     |
| `IfcPointOnCurve`                     | :heavy_check_mark:   | `PlacementConverter`       | :x:                   | -     |
| `IfcPointOnSurface`                   | :x:                  | `CurveConverter`           | -                     | -     |
| `IfcPolyline`                         | :heavy_check_mark:   | `CurveConverter`           | :heavy_check_mark:    | -     |
| `IfcPolyLoop`                         | :heavy_check_mark:   | `CurveConverter`           | :heavy_check_mark:    | -     |
| `IfcPolygonalBoundedHalfSpace`        | :x:                  | `SolidModelConverter`      | -                     | -     |
| `IfcPolygonalFaceSet`                 | :heavy_check_mark:   | `FaceConverter`            | :heavy_check_mark:    | -     |
| `IfcPolynomialCurve`                  | :x:                  | `CurveConverter`           | :x:                   | [#524](https://github.com/tumcms/Open-Infra-Platform/issues/524)|
| `IfcRationalBSplineCurveWithKnots`    | :heavy_check_mark:   | `SplineConverter`          | :heavy_check_mark:    | -     |
| `IfcRationalBSplineSurfaceWithKnots`  | :heavy_check_mark:   | `SplineConverter`          | :heavy_check_mark:    | -     |
| `IfcRectangularPyramid`               | :heavy_check_mark:   | `SolidModelConverter`      | :x:                   | -     |
| `IfcRectangularTrimmedSurface`        | :heavy_check_mark:   | `FaceConverter`            | :x:                   | [#150](https://github.com/tumcms/Open-Infra-Platform/issues/150)|
| `IfcReparametrisedCompositeCurveSegment`| :x:                  | -                          | -                     | -     |
| `IfcRevolvedAreaSolid`                | :heavy_check_mark:   | `SolidModelConverter`      | :x:                   | -     |
| `IfcRevolvedAreaSolidTapered`         | :x:                  | -                          | -                     | -     |
| `IfcRightCircularCone`                | :heavy_check_mark:   | `SolidModelConverter`      | :x:                   | -     |
| `IfcRightCircularCylinder`            | :heavy_check_mark:   | `SolidModelConverter`      | :x:                   | -     |
| `IfcSeamCurve`                        | :x:                  | -                          | -                     | -     |
| `IfcSecondOrderPolynomialSpiral`      | :x:                  | `CurveConverter`           | :x:                   | [#524](https://github.com/tumcms/Open-Infra-Platform/issues/524)|                
| `IfcSectionedSurface`                 | :x:                  | -                          | -                     | -     |
| `IfcSectionedSolid`                   | :heavy_check_mark:   | `SolidModelConverter`      | :x:                   | [#287](https://github.com/tumcms/Open-Infra-Platform/issues/287) |
| `IfcSectionedSolidHorizontal`         | :heavy_check_mark:   | `SolidModelConverter`      | :heavy_check_mark:    | [#356](https://github.com/tumcms/Open-Infra-Platform/issues/356)|
| `IfcSectionedSpine`                   | :x:                  | `RepresentationConverter`  | -                     | -     |
| `IfcSegmentedReferenceCurve`          | :x:                  | `CurveConverter`           | -                     | -     |
| `IfcSeriesParameterCurve`             | :x:                  | `CurveConverter`           | -                     | -     |
| `IfcSeventhOrderPolynomialSpiral`     | :x:                  | `CurveConverter`           | :x:                   | [#524](https://github.com/tumcms/Open-Infra-Platform/issues/524)|
| `IfcShellBasedSurfaceModel`           | :heavy_check_mark:   | `FaceConverter`            | :x:                   | -     |
| `IfcSine`                             | :heavy_check_mark:   | `CurveConverter`           | :x:                   | [#524](https://github.com/tumcms/Open-Infra-Platform/issues/524)|
| `IfcSphere`                           | :heavy_check_mark:   | `SolidModelConverter`      | :x:                   | -     |
| `IfcSphericalSurface`                 | :heavy_check_mark:   | `FaceConverter`            | :x:                   | [#150](https://github.com/tumcms/Open-Infra-Platform/issues/150)|
| `IfcStyledItem`                       | :heavy_check_mark:   | `RepresentationConverter`  | :x:                   | -     |
| `IfcSubedge`                          | :x:                  | `CurveConverter`           | -                     | -     |
| `IfcSurfaceCurve`                     | :heavy_check_mark:   | `CurveConverter`           | :x:                   | -     |
| `IfcSurfaceCurveSweptAreaSolid`       | :heavy_check_mark:   | `SolidModelConverter`      | :x:                   | -     |
| `IfcSurfaceOfLinearExtrusion`         | :heavy_check_mark:   | `FaceConverter`            | :x:                   | [#150](https://github.com/tumcms/Open-Infra-Platform/issues/150)|
| `IfcSurfaceOfRevolution`              | :heavy_check_mark:   | `FaceConverter`            | :x:                   | [#150](https://github.com/tumcms/Open-Infra-Platform/issues/150)|
| `IfcSweptDiskSolid`                   | :heavy_check_mark:   | `SolidModelConverter`      | :heavy_check_mark:    | [#232](https://github.com/tumcms/Open-Infra-Platform/issues/232)|
| `IfcSweptDiskSolidPolygonal`          | :x:                  | `SolidModelConverter`      | -                     | -     |
| `IfcTextLiteral`                      | :x:                  | `RepresentationConverter`  | -                     | -     |
| `IfcTextLiteralWithExtent`            | :x:                  | -                          | -                     | -     |
| `IfcThirdOrderPolynomialSpiral`       | :heavy_check_mark:   | `CurveConverter`           | :x:                   | [#524](https://github.com/tumcms/Open-Infra-Platform/issues/524)|                
| `IfcToroidalSurface`                  | :heavy_check_mark:   | `FaceConverter`            | :x:                   | [#150](https://github.com/tumcms/Open-Infra-Platform/issues/150)|
| `IfcTransitionCurveSegment2D`         | :heavy_check_mark:   | `CurveConverter`           | :heavy_check_mark:    | -     |
| `IfcTriangulatedIrregularNetwork`     | :heavy_check_mark:   | `FaceConverter`            | :heavy_check_mark:    | -     |
| `IfcTrimmedCurve`                     | :heavy_check_mark:   | `CurveConverter`           | :heavy_check_mark:    | -     |
| `IfcVector`                           | :heavy_check_mark:   | `PlacementConverter`       | :x:                   | -     |
| `IfcVertex`                           | :heavy_check_mark:   | `CurveConverter`           | :x:                   | -     |
| `IfcVertexLoop`                       | :x:                  | `FaceConverter`            | -                     | -     |
| `IfcVertexPoint`                      | :heavy_check_mark:   | `CurveConverter`           | :heavy_check_mark:    | -     |