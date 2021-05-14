/*
    Copyright (c) 2021 Technical University of Munich
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

#include "ConverterBase.h"
#include "PlacementConverter.h"
#include "CurveConverter.h"

#include "SplineUtilities.h"

namespace OpenInfraPlatform
{
	namespace Core {
		namespace IfcGeometryConverter {
			/*! \brief Converter functionality for \c IfcBSplineCurve's and \c IfcBSplineSurface's subtypes.
			*
			* \param IfcEntityTypesT The IFC version templates
			*/
			template <
				class IfcEntityTypesT
			>
			class SplineConverterT : public ConverterBaseT<IfcEntityTypesT> // TODO 2020.04.08.: spline converter does not apply length corrections: UnitConverter()->getLengthinMeterFactor()
			{
				public:
					SplineConverterT(
						std::shared_ptr<GeometrySettings> geomSettings,
						std::shared_ptr<UnitConverter<IfcEntityTypesT>> unitConverter,
						std::shared_ptr<PlacementConverterT<IfcEntityTypesT>> pc)
						:
						ConverterBaseT<IfcEntityTypesT>(geomSettings, unitConverter),
						placementConverter(pc)
					{}

					virtual ~SplineConverterT() {}

					/*! \brief Converts \c IfcBSplineCurve subtypes to an array of curve points, which can be rendered in a viewport.
					 *
					 * This converter can handle
					 * \c IfcBSplineCurveWithKnots and
					 * \c IfcRationalBSplineCurveWithKnots, which are subtypes of IfcBSplineCurve.
					 *
					 * \param[in]	splineCurve		\c IfcBSplineCurve entity to be converted.
					 * \param[out]	loops			The array of curve points, which can be rendered in a viewport.
					 */
					void convertIfcBSplineCurve(
						const EXPRESSReference<typename IfcEntityTypesT::IfcBSplineCurve>& splineCurve,
						std::vector<carve::geom::vector<3>>& loops) const throw(...)
					{
						const int degree = splineCurve->Degree;
						const int order = degree + 1;
						const int numControlPoints = splineCurve->ControlPointsList.size();
						const int numKnotsArray = order + numControlPoints;

						const std::vector<carve::geom::vector<3>> controlPoints = loadControlPoints(splineCurve);

						// IfcRationalBSplineCurveWithKnots is a subtype of IfcBSplineCurveWithKnots which is a subtype of IfcBSplineCurve, 
						// it represents a rational B-Spline / a NURBS.
						if (splineCurve.isOfType<typename IfcEntityTypesT::IfcRationalBSplineCurveWithKnots>())
						{
							const std::vector<double> knotArray = loadKnotArray(splineCurve.as<typename IfcEntityTypesT::IfcBSplineCurveWithKnots>(), numKnotsArray);
							const std::vector<double> weightsData = loadWeightsData(splineCurve.as<typename IfcEntityTypesT::IfcRationalBSplineCurveWithKnots>());

							uint32_t numCurvePoints;
							// at the end, subtract current knot value with accuracy to avoid zero-vectors (since last knot value is excluded by definition)
							double accuracy;
							std::tie(numCurvePoints, accuracy) = obtainProperties(knotArray.size());

							std::vector<carve::geom::vector<3>> curvePoints = 
								IfcGeometryConverter::SplineUtilities::computeRationalBSplineCurveWithKnots(order, knotArray, controlPoints, weightsData, numCurvePoints, accuracy);

							GeomUtils::appendPointsToCurve(curvePoints, loops);
							// return loops;
						}
						// IfcBSplineCurveWithKnots is a subtype of IfcBSplineCurve, 
						// it represents a B-Spline
						else if (splineCurve.isOfType<typename IfcEntityTypesT::IfcBSplineCurveWithKnots>())
						{
							const std::vector<double> knotArray = loadKnotArray(splineCurve.as<typename IfcEntityTypesT::IfcBSplineCurveWithKnots>(), numKnotsArray);

							uint32_t numCurvePoints;
							// at the end, subtract current knot value with accuracy to avoid zero-vectors (since last knot value is excluded by definition)
							double accuracy;
							std::tie(numCurvePoints, accuracy) = obtainProperties(knotArray.size());

							std::vector<carve::geom::vector<3>> curvePoints = 
								IfcGeometryConverter::SplineUtilities::computeBSplineCurveWithKnots(order, knotArray, controlPoints, numCurvePoints, accuracy);

							GeomUtils::appendPointsToCurve(curvePoints, loops);
							// return loops;
						}
						// there is no further subtype, which is known now (ifc 4x3 RC 1)
						else if (numControlPoints == order)
						{
							// if the number of control points is equal to the order ( = degree + 1 ), there are enough information 
							// to calculate a Bezier Curve - but it isn't mentioned in the ifc documentation

							// TODO: has to be implemented,
							//       the knotArray has to be set in a specific way
							//       with this special knotArray the function computeBSplineCurveWithKnots can be called for calculation

							throw oip::UnhandledException(splineCurve);
						}
						// it's unknown what to do with this ifc entity
						else
						{
							throw oip::UnhandledException(splineCurve);
						}
					}

					/*! \brief Converts \c IfcBSplineSurface subtypes to ploylineSetData.
					 *
					 * This convert function can handle
					 * \c IfcBSplineSurfaceWithKnots and
					 * \c IfcRationalBSplineSurfaceWithKnots.
					 *
					 * \param[in]	splineSurface		\c IfcBSplineSurface entity to be converted.
					 * \param[in]	controlPoints		A vector of the B-Spline control points, must be obtain from the \c IfcBSplineSurface entity.
					 * \param[out]	polylineData		ploylineSetData (?)
					 *
					 * \note		At the moment, this converter isn't implemented.
					 * \internal	The Code of the function is in the commented out part at the end of the file.
					 */
					void convertIfcBSplineSurface(
						const EXPRESSReference<typename IfcEntityTypesT::IfcBSplineSurface>& splineSurface,
						const carve::math::Matrix& pos, // AT THE MOMENT, NO IDEA WHAT THIS IS
						//const std::vector<std::vector<carve::geom::vector<3>>>& controlPoints,
						std::shared_ptr<carve::input::PolylineSetData>& polylineData) const throw(...)
					{

						if (splineSurface.isOfType<typename IfcEntityTypesT::IfcBSplineSurfaceWithKnots>())
						{
							const EXPRESSReference<typename IfcEntityTypesT::IfcBSplineSurfaceWithKnots>& bsplineSurfaceWithKnots =
								splineSurface.as<typename IfcEntityTypesT::IfcBSplineSurfaceWithKnots>();

							// obtain degree of both b-spline curves
							const int degreeU = bsplineSurfaceWithKnots->UDegree;
							const int orderU = degreeU + 1;
							const int degreeV = bsplineSurfaceWithKnots->VDegree;
							const int orderV = degreeV + 1;
							// obtain number of control points
							//const int numControlPointsU = controlPoints.size();
							//const int numControlPointsV = controlPoints[0].size();

							// load array of control points from ifc-entity
							auto controlPointList = bsplineSurfaceWithKnots->ControlPointsList;
							// temporary control point container of type std::vector<std::vector<..>> which is needed for converter function
							std::vector<std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcCartesianPoint>>> controlPointListVector;
							controlPointListVector.reserve(controlPointList.size());
							// loop over u-indeces (=K1) of control points
							for (auto& itControlPointList : controlPointList)
							{
								// temporary control point sub-vector of one u-index
								std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcCartesianPoint>> controlPointListSubvector;
								controlPointListSubvector.resize(itControlPointList.size());
								// std::transform loops over v-indeces (=K2) 
								std::transform(itControlPointList.begin(),
									itControlPointList.end(),
									controlPointListSubvector.begin(),
									[](EXPRESSReference<typename IfcEntityTypesT::IfcCartesianPoint> it) { return it; });

								// save temporary sub-vector in temporary vector
								controlPointListVector.push_back(controlPointListSubvector);
							}

							// temporary instances to curve and face converter, potential relocation will be considered in further refactoring
							std::shared_ptr<CurveConverterT<IfcEntityTypesT>> curveConverter =
								std::make_shared<CurveConverterT<IfcEntityTypesT>>(CurveConverterT<IfcEntityTypesT>(GeomSettings(), UnitConvert(), placementConverter));
							FaceConverterT<IfcEntityTypesT> faceConverter(GeomSettings(), UnitConvert(), placementConverter, curveConverter);

							// obtain control points
							std::vector<std::vector<carve::geom::vector<3>>> controlPoints = faceConverter.convertIfcCartesianPoint2DVector(controlPointListVector);

							/*
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
							*/
						}
						
					}

				private:
					/*! \brief Loads the control points from an IfcBSplineCurve-entity
					 *
					 * \param[in] splineCurve	The IfcBSplineCurve-entity which contains the control points
					 *
					 * \return	  A vector with the B-Spline control points
					 */
					std::vector<carve::geom::vector<3>> loadControlPoints(
						const EXPRESSReference<typename IfcEntityTypesT::IfcBSplineCurve>& splineCurve) const throw(...)
					{
						CurveConverterT<IfcEntityTypesT> curveConverter(GeomSettings(), UnitConvert(), placementConverter);
						return curveConverter.convertIfcCartesianPointVector(splineCurve->ControlPointsList);
					}

					/*! \brief Loads the knot array from an \c IfcBSplineCurveWithKnots.
					 *
					 * \param[in]	bspline				The \c IfcBSplineCurveWithKnots entity from where the knots have to be loaded.
					 * \param[in]	numKnotsArray		The total number of knots, which define the basis functions ( = order + total number of control points )
					 *
					 * \return		The array / vector of knots.
					 */
					std::vector<double> loadKnotArray(
						const EXPRESSReference<typename IfcEntityTypesT::IfcBSplineCurveWithKnots>& bspline,
						const int& numKnotsArray) const throw(...)
					{
						// check whether data in ifc matches the definition in documentation
						if (bspline->KnotMultiplicities.size() != bspline->Knots.size())
						{
							//std::cout << "ERROR: knot multiplicity does not correspond number of knots" << std::endl;
							throw oip::InconsistentModellingException(bspline, "Function convertIfcBSplineCurve::loadKnotArray: Knot multiplicity does not correspond number of distinct knots; unable to construct a knot array.");
						}

						std::vector<double> knots;
						knots.resize(bspline->Knots.size());
						std::transform(
							bspline->Knots.begin(),
							bspline->Knots.end(),
							knots.begin(),
							[](auto &it) { return it; });
						// convert 'it' (Knots) from IfcParameterValue to double ?

						std::vector<int> knotMults;
						knotMults.resize(bspline->KnotMultiplicities.size());
						std::transform(
							bspline->KnotMultiplicities.begin(),
							bspline->KnotMultiplicities.end(),
							knotMults.begin(),
							[](auto &it) -> int { return it; });
						// convert 'it' (KnotMultiplicities) from IfcInteger to int ?

						// preset target vector
						std::vector<double> knotArray;
						knotArray.reserve(numKnotsArray);

						// obtain knots
						for (int i = 0; i < knots.size(); ++i)
						{
							const double knot = knots[i];
							const int knotMult = knotMults[i];
							// look at the multiplicity of the current knot
							for (int j = 0; j < knotMult; ++j)
							{
								knotArray.push_back(knot);
							}
						}

						return knotArray;
					}

					/*! \brief Loads the knot weights from an \c IfcRationalBSplineCurveWithKnots.
					 *
					 * \param[in]	rationalBSplineCurve	The \c IfcRationalBSplineCurveWithKnots entity from where the weights have to be loaded.
					 *
					 * \return		The vector of weights per knot.
					 */
					std::vector<double> loadWeightsData(
						const EXPRESSReference<typename IfcEntityTypesT::IfcRationalBSplineCurveWithKnots>& rationalBSplineCurve) const throw(...)
					{
						std::vector<double> weightsData;

						weightsData.resize(rationalBSplineCurve->WeightsData.size());
						std::transform(
							rationalBSplineCurve->WeightsData.begin(),
							rationalBSplineCurve->WeightsData.end(),
							weightsData.begin(),
							[](auto &it) -> double { return it; });
						// convert 'it' (WeightsData) from IfcReal to double ?

						return weightsData;
					}
					
					/*! \brief Loads general properties, which are used in the calculation.
					 *
					 * \param[in]	numKnotsArray	The total number of knots, which define the basis functions ( = order + total number of control points )
					 *
					 * \return		Number of curve points
					 * \return		Accuracy which is technically needed in the calculation.
					 *
					 * \note	The number of curve points \c numCurvePoints, where the curve c(t) has to be evaluated,
					 *			is temporary preset with a default value proportional to the number of knots.
					 */
					std::tuple<const uint32_t, const double> obtainProperties(const int& numKnotsArray) const throw(...)
					{
						// ! TEMPORARY default number of curve points
						const uint32_t numCurvePoints = numKnotsArray * 10;

						// at the end, subtract current knot value with this to avoid zero-vectors (since last knot value is excluded by definition)
						//const double accuracy = 0.0000001;
						double accuracy = GeomSettings()->getPrecision();

						return { numCurvePoints, accuracy };
					}

					// B-Spline surface definition according to: 
					// http://www.buildingsmart-tech.org/ifc/IFC4/final/html/schema/ifcgeometryresource/lexical/ifcbsplinesurface.htm
					void computeBSplineSurface(
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
						std::vector<carve::geom::vector<3>>& curvePoints) const throw(...)
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

						for (int j = 0; j < numCurvePointsV; ++j) {
							if (j == numCurvePointsV - 1) { tV = knotEndV - accuracy; }

							double tU = knotStartU;

							for (int i = 0; i < numCurvePointsU; ++i) {
								if (i == numCurvePointsU - 1) { tU = knotEndU - accuracy; }

								// 1) Evaluate basis functions at curve point tU and tV
								IfcGeometryConverter::SplineUtilities::computeBSplineBasisFunctions(orderU, tU, numControlPointsU, knotVectorU, basisFuncsU);
								IfcGeometryConverter::SplineUtilities::computeBSplineBasisFunctions(orderV, tV, numControlPointsV, knotVectorV, basisFuncsV);

								// 2) Compute exact point on surface
								carve::geom::vector<3> point = carve::geom::VECTOR(0, 0, 0);

								// 2i) If B-spline surface is rational, weights and their sum have to considered, as well
								double weightSum = 0.0;

								for (int x = 0; x < numControlPointsU; ++x) {
									const double basisFuncU = basisFuncsU[x];

									for (int y = 0; y < numControlPointsV; ++y) {
										const double basisFuncV = basisFuncsV[y];
										const carve::geom::vector<3>& controlPoint = controlPoints[x][y];

										if (!weights.empty()) {
											// 3a) apply formula for rational B-spline surfaces
											const double weightProduct = weights[x][y] * basisFuncU * basisFuncV;
											point += weightProduct * controlPoint;
											weightSum += weightProduct;
										}
										else {
											// 3b) apply formula for normal B-spline surfaces
											point += basisFuncU * basisFuncV * controlPoint;
										}
									}
								}

								if (!weights.empty()) {
									point /= weightSum;
								}

								curvePoints.push_back(point);

								tU += stepU;
							}

							tV += stepV;
						}
					}

				protected:

					std::shared_ptr<PlacementConverterT<IfcEntityTypesT>> placementConverter;

			}; // end class SplineConverterT
		} // end namespace IfcGeometryConverter
	} // end namespace Core
} // end namespace OpenInfraPlatform

#endif
