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

// visual studio
#pragma once
// linux
#ifndef SPLINECONVERTER_H
#define SPLINECONVERTER_H

#include <sstream>
#include <memory>

#include "CarveHeaders.h"
#include "GeometryInputData.h"
#include "GeomUtils.h"

#include "EMTIfc4EntityTypes.h"
#include "OpenInfraPlatform/Ifc4/model/Ifc4Model.h"

namespace OpenInfraPlatform
{
	namespace IfcGeometryConverter
	{
		template <
			class IfcEntityTypesT,
			class IfcUnitConverterT
		>
		class SplineConverterT
		{
		public:
			SplineConverterT() { }
			virtual ~SplineConverterT() { }

			static void convertIfcBSplineCurve(
				const std::shared_ptr<typename IfcEntityTypesT::IfcBSplineCurve>& splineCurve,
				const std::vector<carve::geom::vector<3>>& controlPoints,
				std::vector<carve::geom::vector<3>>& loops)
			{
			}

			static void convertIfcBSplineSurface(
				const std::shared_ptr<typename IfcEntityTypesT::IfcBoundedSurface>& splineSurface,
				const std::vector<std::vector<carve::geom::vector<3>>>& controlPoints,
				std::shared_ptr<carve::input::PolylineSetData>& polylineData)
			{
			}

			// Compute B-Spline basis functions for given curve value t
			static void computeBSplineBasisFunctions(
				const uint8_t order, // k: order of basis and polynomial of degree k - 1
				const double t, // t: arbitrary value on B-Spline curve
				const uint32_t numControlPoints, // n + 1 control points
				const std::vector<double>& knotVector, // t_i: knot points
				std::vector<double>& basisFuncs)
			{
				const uint8_t degree = order - 1;
				const uint16_t numBasisFuncs = degree + numControlPoints;
				const uint16_t numKnots = order + numControlPoints;
				// create temporary basis functions of size k + n (or d + (n + 1), with d = k - 1)
				std::vector<double> tempBasisFuncs(numBasisFuncs, 0.0);

				// intialize first order basis functions
				for (auto i = 0; i < numBasisFuncs; ++i)
				{
					const double knot = knotVector[i];
					const double knotNext = knotVector[i + 1];
					if (t >= knot && t < knotNext && knot < knotNext)
					{
						tempBasisFuncs[i] = 1.0;
					}
				}

				double basisFuncFirst = 0.0;
				double basisFuncSecond = 0.0;

				// build basis functions of higher order up-to order = degree
				for (int k = 1; k <= degree; ++k)
				{
					for (int i = 0; i < numBasisFuncs - k; ++i)
					{
						const double t_i = knotVector[i];
						const double t_ik = knotVector[i + k];
						const double t_ik1 = knotVector[i + k + 1];
						const double t_i1 = knotVector[i + 1];
						// function is zero if basis is zero or denominator is zero
						if (tempBasisFuncs[i] == 0 || t_ik == t_i) { basisFuncFirst = 0.0; }
						else
						{
							// apply formula of first part
							basisFuncFirst = (t - t_i) / (t_ik - t_i) * tempBasisFuncs[i];
						}

						// function is zero if basis is zero or denominator is zero
						if (tempBasisFuncs[i + 1] == 0 || t_ik1 == t_i1) { basisFuncSecond = 0.0; }
						else
						{
							// apply formula of first part
							basisFuncSecond = (t_ik1 - t) / (t_ik1 - t_i1) * tempBasisFuncs[i + 1];
						}

						// compute sum and set as basis function for next order
						tempBasisFuncs[i] = basisFuncFirst + basisFuncSecond;
					}
				}

				const uint32_t numBasis = numControlPoints;
				for (int j = 0; j < numBasis; ++j)
				{
					basisFuncs[j] = tempBasisFuncs[j];
				}
			}
			
			// B-Spline surface definition according to: 
		    // http://www.buildingsmart-tech.org/ifc/IFC4/final/html/schema/ifcgeometryresource/lexical/ifcbsplinesurface.htm
			static void computeBSplineSurface(
				const uint8_t orderU,
				const uint8_t orderV,
				const uint32_t numCurvePointsU,
				const uint32_t numCurvePointsV,
				const uint32_t numControlPointsU,
				const uint32_t numControlPointsV,
				const std::vector<std::vector<carve::geom::vector<3>>>& controlPoints,
				const std::vector<std::vector<double>>& weights,
				const std::vector<double>& knotVectorU,
				const std::vector<double>& knotVectorV,
				std::vector<carve::geom::vector<3>>& curvePoints)
			{
				// curve is defined for [t_p;t_m-p], m := number of knots - 1
				const uint32_t firstIndexU = orderU - 1;
				const uint32_t lastIndexU = knotVectorU.size() - orderU;
				const uint32_t firstIndexV = orderV - 1;
				const uint32_t lastIndexV = knotVectorV.size() - orderV;

				const double knotStartU = knotVectorU[firstIndexU];
				const double knotEndU = knotVectorU[lastIndexU];
				const double knotRangeU = knotEndU - knotStartU;

				const double knotStartV = knotVectorV[firstIndexV];
				const double knotEndV = knotVectorV[lastIndexV];
				const double knotRangeV = knotEndV - knotStartV;

				// compute step size for each direction
				const double stepU = knotRangeU / static_cast<double>(numCurvePointsU - 1);
				const double stepV = knotRangeV / static_cast<double>(numCurvePointsV - 1);

				std::vector<double> basisFuncsU(numControlPointsU, 0.0);
				std::vector<double> basisFuncsV(numControlPointsV, 0.0);

				const double accuracy = 0.0000001;

				// start with first valid knot in each direction
				double tV = knotStartV;

				for (int j = 0; j < numCurvePointsV; ++j)
				{
					if (j == numCurvePointsV - 1) { tV = knotEndV - accuracy; }

					double tU = knotStartU;

					for (int i = 0; i < numCurvePointsU; ++i)
					{
						if (i == numCurvePointsU - 1) { tU = knotEndU - accuracy; }

						// 1) Evaluate basis functions at curve point tU and tV
						computeBSplineBasisFunctions(orderU, tU, numControlPointsU, knotVectorU, basisFuncsU);
						computeBSplineBasisFunctions(orderV, tV, numControlPointsV, knotVectorV, basisFuncsV);

						// 2) Compute exact point on surface
						carve::geom::vector<3> point = carve::geom::VECTOR(0, 0, 0);

						// 2i) If B-spline surface is rational, weights and their sum have to considered, as well
						double weightSum = 0.0;

						for (int x = 0; x < numControlPointsU; ++x)
						{
							const double basisFuncU = basisFuncsU[x];

							for (int y = 0; y < numControlPointsV; ++y)
							{
								const double basisFuncV = basisFuncsV[y];
								const carve::geom::vector<3>& controlPoint = controlPoints[x][y];

								if (!weights.empty())
								{
									// 3a) apply formula for rational B-spline surfaces
									const double weightProduct = weights[x][y] * basisFuncU * basisFuncV;
									point += weightProduct * controlPoint;
									weightSum += weightProduct;
								}
								else
								{
									// 3b) apply formula for normal B-spline surfaces
									point += basisFuncU * basisFuncV * controlPoint;
								}
							}
						}

						if (!weights.empty())
						{
							point /= weightSum;
						}

						curvePoints.push_back(point);

						tU += stepU;
					}

					tV += stepV;
				}
			}


			// B-Spline curve definition according to: http://mathworld.wolfram.com/B-Spline.html
			static void computeBSplineCurve(
				const uint8_t order,
				const uint32_t numCurvePoints,
				const uint32_t numControlPoints,
				const std::vector<carve::geom::vector<3>>& controlPoints,
				const std::vector<double>& weights,
				const std::vector<double>& knotVector,
				std::vector<carve::geom::vector<3>>& curvePoints)
			{

				// curve is defined for [t_p;t_m-p], m := number of knots - 1
				const uint32_t firstIndex = order - 1;
				const uint32_t lastIndex = knotVector.size() - order;

				const double knotStart = knotVector[firstIndex];
				const double knotEnd = knotVector[lastIndex];
				const double knotRange = knotEnd - knotStart;

				// compute step size
				const double step = knotRange / static_cast<double>(numCurvePoints - 1);

				std::vector<double> basisFuncs(numControlPoints, 0.0);
				// start with first valid knot
				double t = knotStart;
				// at the end, subtract current knot value with this to avoid zero-vectors (since last knot value is excluded by definition)
				const double accuracy = 0.0000001;

				for (auto i = 0; i < numCurvePoints; ++i)
				{
					if (i == numCurvePoints - 1) { t = knotEnd - accuracy; }

					// 1) Evaluate basis functions at curve point t
					computeBSplineBasisFunctions(order, t, numControlPoints, knotVector, basisFuncs);
					// 2) Compute exact point
					carve::geom::vector<3> point = carve::geom::VECTOR(0, 0, 0);
					// 2i) If B-spline surface is rational, weights and their sum have to considered, as well
					double weightSum = 0.0;

					for (int j = 0; j < numControlPoints; ++j)
					{
						const double basisFunc = basisFuncs[j];
						const carve::geom::vector<3>& controlPoint = controlPoints[j];
						
						if (!weights.empty())
						{ 
							// 3a) apply formula for rational B-spline surfaces
							const double weightProduct = weights[j] * basisFunc;
							point += weightProduct * controlPoint;
							weightSum += weightProduct;
						}
						else
						{
							// 3b) apply formula for normal B-spline curves
							point += basisFunc * controlPoint;
						}
						
					}

					if (!weights.empty())
					{
						point /= weightSum;
					}
					
					curvePoints.push_back(point);

					t += step;
				}
			}

		private:

		};

		template<>
		inline void SplineConverterT<emt::Ifc4EntityTypes, OpenInfraPlatform::Ifc4::UnitConverter>::convertIfcBSplineCurve(
			const std::shared_ptr<emt::Ifc4EntityTypes::IfcBSplineCurve>& splineCurve,
			const std::vector<carve::geom::vector<3>>& controlPoints,
			std::vector<carve::geom::vector<3>>& loops)
		{
			const int degree = splineCurve->m_Degree;
			const int order = degree + 1;
			const int numControlPoints = splineCurve->m_ControlPointsList.size();
			const int numKnots = order + numControlPoints;

			std::vector<double> knots;
			knots.reserve(numKnots);

			std::vector<double> weights;

			std::shared_ptr<emt::Ifc4EntityTypes::IfcRationalBSplineCurveWithKnots> rationalBSplineCurve =
				std::dynamic_pointer_cast<emt::Ifc4EntityTypes::IfcRationalBSplineCurveWithKnots>(splineCurve);

			if (rationalBSplineCurve)
			{
				//std::cout << "ERROR: IfcRationalBSplineCurveWithKnots not implemented" << std::endl;
				weights = rationalBSplineCurve->m_WeightsData;
			}

			std::shared_ptr<emt::Ifc4EntityTypes::IfcBSplineCurveWithKnots> bspline =
				std::dynamic_pointer_cast<emt::Ifc4EntityTypes::IfcBSplineCurveWithKnots>(splineCurve);

			if (bspline)
			{
				const std::vector<int>& knotMults = bspline->m_KnotMultiplicities;
				const std::vector<std::shared_ptr<emt::Ifc4EntityTypes::IfcParameterValue>>& splineKnots = bspline->m_Knots;
				//const std::vector<std::shared_ptr<emt::Ifc4EntityTypes::IfcCartesianPoint>>& splinePoints = bspline->m_ControlPointsList;

				if (knotMults.size() != splineKnots.size()) 
				{ 
					std::cout << "ERROR: knot multiplicity does not correspond number of knots" << std::endl;
					return; 
				}

				// obtain knots
				for (int i = 0; i < splineKnots.size(); ++i)
				{
					double knot = splineKnots[i]->m_value;
					const int knotMult = knotMults[i];
					// look at the multiplicity of the current knot
					for (int j = 0; j < knotMult; ++j)
					{
						knots.push_back(knot);
					}
				}

				//! TEMPORARY default number of curve points
				const uint8_t numCurvePoints = numKnots * 10;
				std::vector<carve::geom::vector<3>> curvePoints;
				curvePoints.reserve(numCurvePoints);
				
				computeBSplineCurve(order, numCurvePoints, numControlPoints, controlPoints, weights, knots, curvePoints);

				GeomUtils::appendPointsToCurve(curvePoints, loops);
			}
		}

		template<>
		inline void SplineConverterT<emt::Ifc4EntityTypes, OpenInfraPlatform::Ifc4::UnitConverter>::convertIfcBSplineSurface(
			const std::shared_ptr<emt::Ifc4EntityTypes::IfcBoundedSurface>& splineSurfaceWithKnots,
			const std::vector<std::vector<carve::geom::vector<3>>>& controlPoints,
			std::shared_ptr<carve::input::PolylineSetData>& polylineData)
		{
			std::shared_ptr<emt::Ifc4EntityTypes::IfcBSplineSurfaceWithKnots> bsplineSurfaceWithKnots =
				std::dynamic_pointer_cast<emt::Ifc4EntityTypes::IfcBSplineSurfaceWithKnots>(splineSurfaceWithKnots);

			if (splineSurfaceWithKnots)
			{
				// obtain degree of both b-spline curves
				const int degreeU = bsplineSurfaceWithKnots->m_UDegree;
				const int orderU = degreeU + 1;
				const int degreeV = bsplineSurfaceWithKnots->m_VDegree;
				const int orderV = degreeV + 1;
				// obtain number of control points
				const int numControlPointsU = controlPoints.size();
				const int numControlPointsV = controlPoints[0].size();
				// obtain number of knots
				const int numKnotsU = orderU + numControlPointsU;
				const int numKnotsV = orderV + numControlPointsV;

				// obtain knots for each direction
				const std::vector<int>& knotMultsU = bsplineSurfaceWithKnots->m_UMultiplicities;
				const std::vector<std::shared_ptr<emt::Ifc4EntityTypes::IfcParameterValue>>& splineKnotsU = bsplineSurfaceWithKnots->m_UKnots;
				const std::vector<int>& knotMultsV = bsplineSurfaceWithKnots->m_VMultiplicities;
				const std::vector<std::shared_ptr<emt::Ifc4EntityTypes::IfcParameterValue>>& splineKnotsV = bsplineSurfaceWithKnots->m_VKnots;

				std::vector<double> knotsU;
				std::vector<double> knotsV;
				knotsU.reserve(numKnotsU);
				knotsV.reserve(numKnotsV);

				for (int i = 0; i < splineKnotsU.size(); ++i)
				{
					double knot = splineKnotsU[i]->m_value;
					const int knotMult = knotMultsU[i];
					// look at the multiplicity of the current knot
					for (int j = 0; j < knotMult; ++j)
					{
						knotsU.push_back(knot);
					}
				}

				for (int i = 0; i < splineKnotsV.size(); ++i)
				{
					double knot = splineKnotsV[i]->m_value;
					const int knotMult = knotMultsV[i];
					// look at the multiplicity of the current knot
					for (int j = 0; j < knotMult; ++j)
					{
						knotsV.push_back(knot);
					}
				}

				std::vector<std::vector<double>> weights;

				std::shared_ptr<emt::Ifc4EntityTypes::IfcRationalBSplineSurfaceWithKnots> rationalBsplineSurfaceWithKnots =
					std::dynamic_pointer_cast<emt::Ifc4EntityTypes::IfcRationalBSplineSurfaceWithKnots>(splineSurfaceWithKnots);

				if (rationalBsplineSurfaceWithKnots)
				{
					weights = rationalBsplineSurfaceWithKnots->m_WeightsData;
				}

				// reserve memory for all surface points on b-spline surface
				//! TEMPORARY default number of curve points
				const uint8_t numCurvePointsU = splineKnotsU.size() * 10;
				const uint8_t numCurvePointsV = splineKnotsV.size() * 10;
				std::vector<carve::geom::vector<3>> curvePoints;
				curvePoints.reserve(numCurvePointsU * numCurvePointsV);

				computeBSplineSurface(orderU, orderV, numCurvePointsU, numCurvePointsV, 
					numControlPointsU, numControlPointsV,
					controlPoints, weights, knotsU, knotsV, curvePoints);

				std::unordered_map<std::string, int> vertexMap;
				vertexMap.reserve(curvePoints.size());

				for (int v = 0; v < numCurvePointsV - 1; ++v)
				{
					for (int u = 0; u < numCurvePointsU - 1; ++u)
					{
						std::vector<carve::geom::vector<3>> facePoints;
						facePoints.reserve(4);

						facePoints.push_back(curvePoints[u + numCurvePointsU * v]); // 00
						facePoints.push_back(curvePoints[u + 1 + numCurvePointsU * v]); // 10
						facePoints.push_back(curvePoints[u + 1 + numCurvePointsU * (v + 1)]); // 11
						facePoints.push_back(curvePoints[u + numCurvePointsU * (v + 1)]); // 01

						size_t indices[4];

						polylineData->beginPolyline();

						for (auto k = 0; k < 4; ++k)
						{
							std::stringstream key;
							key << facePoints[k].x << " " << facePoints[k].y << " " << facePoints[k].z;

							if (vertexMap.find(key.str()) != vertexMap.end()) { indices[k] = vertexMap[key.str()]; }
							else
							{
								indices[k] = polylineData->addVertex(facePoints[k]);
								vertexMap[key.str()] = indices[k];
							}

							polylineData->addPolylineIndex(indices[k]);
						}
					}
				}
			}
		}
	} // end namespace IfcGeometryConverter
} // end namespace OpenInfraPlatform

#endif