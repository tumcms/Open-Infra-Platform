/*
    Copyright (c) 2017 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    TUM Open Infra Platform is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    TUM Open Infra Platform is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcReferenceCurveAlignment2D.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcCartesianPoint.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcLengthMeasure.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcAlignmentElement.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcTrimmedCurve.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcLine.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcVector.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcDirection.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcCircle.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcPositiveLengthMeasure.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcAxis2Placement2D.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcBridgeElement.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcLabel.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcProject.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcGloballyUniqueId.h"
#include "OpenInfraPlatform/IfcBridge/guid/CreateGuid_64.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcSIUnit.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcUnitEnum.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcSIUnitName.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcUnitAssignment.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcBridge.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcBridgeStructureElement.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcBridgeStructureIndicator.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcBridgeStructureType.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelAggregates.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcBridgePart.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcBridgeStructureElementType.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcBridgeTechnologicalElementType.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcBridgePrismaticElement.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcBridgePrismaticElementType.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcProductDefinitionShape.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcShapeRepresentation.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcGeometricRepresentationContext.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcDimensionCount.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcReferencedSectionedSpine.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcReferenceCurve3D.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcPolyline.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcArbitraryClosedProfileDef.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcRelContainedInSpatialStructure.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcReferenceCurvePlacementSystem.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcProfileTypeEnum.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcReferenceCurvePlacement.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcDirection.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcExtrudedAreaSolid.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcAxis2Placement3D.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcPositiveLengthMeasure.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcOffsetCurve2D.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcOffsetCurve3D.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcBooleanResult.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcBooleanOperand.h"
#include "OpenInfraPlatform/IfcBridge/entity/include/IfcBooleanOperator.h"
#include "IfcBridgeSubstructureElement.h"
#include "IfcBridgeSubstructureElementType.h"