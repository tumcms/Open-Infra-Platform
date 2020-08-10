/*
    Copyright (c) 2018 Technical University of Munich
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

							std::vector<carve::geom::vector<3>> curvePoints = computeIfcRationalBSplineCurveWithKnots(order, knotArray, controlPoints, numControlPoints, weightsData);

							GeomUtils::appendPointsToCurve(curvePoints, loops);
							// return loops;
						}
						// IfcBSplineCurveWithKnots is a subtype of IfcBSplineCurve, 
						// it represents a B-Spline
						else if (splineCurve.isOfType<typename IfcEntityTypesT::IfcBSplineCurveWithKnots>())
						{
							junkfunctionToCallForCompiler(splineCurve.as<typename IfcEntityTypesT::IfcBSplineCurveWithKnots>());

							const std::vector<double> knotArray = loadKnotArray(splineCurve.as<typename IfcEntityTypesT::IfcBSplineCurveWithKnots>(), numKnotsArray);

							std::vector<carve::geom::vector<3>> curvePoints = computeIfcBSplineCurveWithKnots(order, knotArray, controlPoints, numControlPoints);

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
						const std::shared_ptr<typename IfcEntityTypesT::IfcBoundedSurface>& splineSurface,
						const std::vector<std::vector<carve::geom::vector<3>>>& controlPoints,
						std::shared_ptr<carve::input::PolylineSetData>& polylineData) const throw(...)
					{
						// not implemented, code in commented out part at the end of the file
						throw oip::UnhandledException(splineSurface);
					}

					/*! \brief This function calls other functions which aren't part of the current program flow.
					 *
					 * At the moment, \c computeCurvatureOfIfcBSplineCurveWithKnots is called from there.
					 * \note This function will be removed if the called functions are part of the usual program flow.
					 *
					 * param[in] bspline A \c computeCurvatureOfIfcBSplineCurveWithKnots entity
					 */
					void junkfunctionToCallForCompiler(const EXPRESSReference<typename IfcEntityTypesT::IfcBSplineCurveWithKnots>& bspline) const throw(...)
					{
						const int order = bspline->Degree + 1;
						const int numControlPoints = bspline->ControlPointsList.size();
						const int numKnotsArray = order + numControlPoints;
						const std::vector<double> knotArray = loadKnotArray(bspline, numKnotsArray);

						const std::vector<carve::geom::vector<3>> controlPoints = loadControlPoints(bspline);

						std::vector<std::pair<double, double>> curvature;
						curvature = computeCurvatureOfBSplineCurveWithKnots(order, controlPoints, knotArray);
					}

					/*! \brief Computes the length and curvature of an B-Spline curve
					 *
					 * This function calculates the curvature of a B-Spline; rational B-Splines can't be handled from this function. 
					 * As well, the corresponding curve length is calculated. 
					 * The \c length is necessary to display or analyse the \c curvature in dependency to the true curve length.
					 * The parameter \c t along a B-Spline curve doesn't represent the true length along the curve because the 
					 * calculated curve points aren't evenly spaced.\n
					 * The result comes back as a vector of \c std::pair in the order \c length, \c curvature.
					 * Access the members by \c .first to get the length and \c .second to get the curvature.
					 *
					 * \param[in]	order			Order of the B-Spline or rather the basis functions ( =degree+1 )
					 * \param[in]	controlPoints	The vector of the B-Spline control points.
					 * \param[in]	knotArray		The array / vector of knots.
					 *
					 * \return		Vector of pairs with curve length and curvature.
					 */
					std::vector<std::pair<double, double>> computeCurvatureOfBSplineCurveWithKnots(
						const int& order,
						const std::vector<carve::geom::vector<3>>& controlPoints,
						const std::vector<double>& knotArray) const throw(...)
					{
						const size_t numControlPoints = controlPoints.size();
						uint32_t numCurvePoints;
						// at the end, subtract current knot value with accuracy to avoid zero-vectors (since last knot value is excluded by definition)
						double accuracy;
						std::tie(numCurvePoints, accuracy) = obtainProperties(knotArray.size());

						// The following parameters corresponds to the parameter t of a curve c(t)
						double knotStart;
						double knotEnd;
						double step;
						std::tie(knotStart, knotEnd, step) = obtainKnotRange(order, knotArray, numCurvePoints);

						std::vector<std::pair<double, double>> curvature;
						curvature.reserve(numCurvePoints);

						// start with first valid knot
						double t = knotStart;

						carve::geom::vector<3> curvePoint;
						carve::geom::vector<3> curvePointPrevious;
						carve::geom::vector<3> derivativeOne;
						carve::geom::vector<3> derivativeTwo;

						double length_i;
						double curvature_i;

						for (size_t i = 0; i < numCurvePoints; ++i) {
							if (i == numCurvePoints - 1) { t = knotEnd - accuracy; }

							curvePoint = computePointOfBSpline(order, t, controlPoints, numControlPoints, knotArray);
							if (i == 0)
								length_i = 0;
							else
								length_i = curvature[i-1].first + (curvePoint - curvePointPrevious).length();
							curvePointPrevious = curvePoint;

							derivativeOne = computePointOfDerivativeOne(order, t, controlPoints, knotArray);
							derivativeTwo = computePointOfDerivativeTwo(order, t, controlPoints, knotArray);

							// curvature of curve c(t) in xy-plane
							// according to definition 3.500 in Bronstein et al., Taschenbuch der Mathematik, 10. Auflage, 2016
							curvature_i = (derivativeOne.x*derivativeTwo.y - derivativeTwo.x*derivativeOne.y) 
								/ (std::pow( std::pow(derivativeOne.x,2) + std::pow(derivativeOne.y,2), 3/2));

							curvature[i] = std::pair<double, double> (length_i, curvature_i);

							t += step;
						}

						return curvature;
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
					
					/*! \brief Obtains the range of knot values and the step size of curve parameter t.
					 *
					 * \param[in]	order			Order of the B-Spline or rather the basis functions ( =degree+1 )
					 * \param[in]	knotArray		The array / vector of knots, the function \c loadKnotArray gives this vector.
					 * \param[in]	numCurvePoints	The number of curve points where the curve c(t) has to be evaluated.
					 *
					 * \return		First valid knot value, correspondes to t_start
					 * \return		Last valid knot value, correspondes to t_end
					 * \return		Step size of curve parameter t between start and end
					 */
					std::tuple<double, double, double> obtainKnotRange(
						const uint8_t& order, 
						const std::vector<double>& knotArray,
						const uint32_t& numCurvePoints) const throw(...)
					{
						// curve is defined for [t_p;t_m-p], m := number of knots - 1
						const uint32_t firstIndex = order - 1;
						const uint32_t lastIndex = knotArray.size() - order;

						const double knotStart = knotArray[firstIndex];
						const double knotEnd = knotArray[lastIndex];
						const double knotRange = knotEnd - knotStart;

						// compute step size
						const double step = knotRange / static_cast<double>(numCurvePoints - 1);

						return { knotStart, knotEnd, step };
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

					/*! \brief Computes the curve points of the B-Spline.
					 *
					 * All information has to be loaded from an \c IfcBSplineCurveWithKnots entity before calling this function.
					 *
					 * \param[in]	order				Order of the B-Spline or rather the basis functions ( =degree+1 )
					 * \param[in]	knotArray			The array / vector of knots, the function \c loadKnotArray gives this vector.
					 * \param[in]	controlPoints		The vector of the B-Spline control points.
					 * \param[in]	numControlPoints	The total number of B-Spline control points ( =n+1 )
					 *
					 * \return		The array of curve points, which can be rendered in a viewport after correction by \c GeomUtils::appendPointsToCurve.
					 */
					// B-Spline curve definition according to: http://mathworld.wolfram.com/B-Spline.html
					std::vector<carve::geom::vector<3>> computeIfcBSplineCurveWithKnots(
						const int& order,
						const std::vector<double>& knotArray,
						const std::vector<carve::geom::vector<3>>& controlPoints,
						const int& numControlPoints) const throw(...)
					{
						uint32_t numCurvePoints;
						// at the end, subtract current knot value with accuracy to avoid zero-vectors (since last knot value is excluded by definition)
						double accuracy;
						std::tie(numCurvePoints, accuracy) = obtainProperties(knotArray.size());

						// The following parameters corresponds to the parameter t of a curve c(t)
						double knotStart;
						double knotEnd;
						double step;
						std::tie(knotStart, knotEnd, step) = obtainKnotRange(order, knotArray, numCurvePoints);

						std::vector<carve::geom::vector<3>> curvePoints;
						curvePoints.reserve(numCurvePoints);

						// start with first valid knot
						double t = knotStart;

						for (size_t i = 0; i < numCurvePoints; ++i) {
							if (i == numCurvePoints - 1) { t = knotEnd - accuracy; }

							curvePoints.push_back(computePointOfBSpline(order, t, controlPoints, numControlPoints, knotArray));
							t += step;
						}

						return curvePoints;
					}

					/*! \brief Computes the B-Spline point at the location t.
					 *
					 * This function is for B-Splines from an IfcBSplineCurveWithKnots-entity.
					 *
					 * \param[in]	order				Order of the B-Spline or rather the basis functions ( =degree+1 )
					 * \param[in]	t					The parameter value t of the curve c(t).
					 * \param[in]	controlPoints		The vector of the B-Spline control points.
					 * \param[in]	numControlPoints	The total number of B-Spline control points ( =n+1 )
					 * \param[in]	knotArray			The array / vector of knots, the function \c loadKnotArray gives this vector.
					 *
					 * \return		The B-Spline point at the position t.
					 */
					carve::geom::vector<3> computePointOfBSpline(
						const int& order,
						const double& t,
						const std::vector<carve::geom::vector<3>>& controlPoints,
						const int& numControlPoints,
						const std::vector<double>& knotArray) const throw(...)
					{
						// 1) Evaluate basis functions at curve point t
						std::vector<double> basisFuncs = computeBSplineBasisFunctions(order, t, numControlPoints, knotArray);

						// 2) Compute exact point
						carve::geom::vector<3> point = carve::geom::VECTOR(0, 0, 0);

						for (int j = 0; j < numControlPoints; ++j)
						{
							// 3b) apply formula for normal B-spline curves
							point += basisFuncs[j] * controlPoints[j];
						}

						return point;
					}

					/*! \brief Computes the curve points of the rational B-Spline.
					 *
					 * All information has to be loaded from an \c IfcRationalBSplineCurveWithKnots entity before calling this function.
					 *
					 * \param[in]	order				Order of the B-Spline or rather the basis functions ( =degree+1 )
					 * \param[in]	knotArray			The array / vector of knots, the function \c loadKnotArray gives this vector.
					 * \param[in]	controlPoints		The vector of the B-Spline control points.
					 * \param[in]	numControlPoints	The total number of B-Spline control points ( =n+1 )
					 * \param[in]	weightsData			The vector with the wight values per knot, the function \c loadWeightsData gives this vector.
					 *
					 * \return		The array of curve points, which can be rendered in a viewport after correction by \c GeomUtils::appendPointsToCurve.
					 */
					// B-Spline curve definition according to: http://mathworld.wolfram.com/B-Spline.html
					std::vector<carve::geom::vector<3>> computeIfcRationalBSplineCurveWithKnots(
						const int& order,
						const std::vector<double>& knotArray,
						const std::vector<carve::geom::vector<3>>& controlPoints,
						const int& numControlPoints,
						const std::vector<double>& weightsData) const throw(...)
					{
						uint32_t numCurvePoints;
						// at the end, subtract current knot value with accuracy to avoid zero-vectors (since last knot value is excluded by definition)
						double accuracy;
						std::tie(numCurvePoints, accuracy) = obtainProperties(knotArray.size());

						// The following parameters corresponds to the parameter t of a curve c(t)
						double knotStart;
						double knotEnd;
						double step;
						std::tie(knotStart, knotEnd, step) = obtainKnotRange(order, knotArray, numCurvePoints);

						std::vector<carve::geom::vector<3>> curvePoints;
						curvePoints.reserve(numCurvePoints);

						// start with first valid knot
						double t = knotStart;

						for (size_t i = 0; i < numCurvePoints; ++i) {
							if (i == numCurvePoints - 1) { t = knotEnd - accuracy; }

							curvePoints.push_back(computePointOfRationalBSpline(order, t, controlPoints, numControlPoints, knotArray, weightsData));
							t += step;
						}

						return curvePoints;
					}

					/*! \brief Computes the rational-B-Spline point at the location t.
					 *
					 * This function is for rational B-Splines from an IfcRationalBSplineCurveWithKnots-entity.
					 *
					 * \param[in]	order				Order of the B-Spline or rather the basis functions ( =degree+1 )
					 * \param[in]	t					The parameter value t of the curve c(t).
					 * \param[in]	controlPoints		The vector of the B-Spline control points.
					 * \param[in]	numControlPoints	The total number of B-Spline control points ( =n+1 )
					 * \param[in]	knotArray			The array / vector of knots, the function \c loadKnotArray gives this vector.
					 * \param[in]	weightsData			The vector with the wight values per knot, the function \c loadWeightsData gives this vector.
					 *
					 * \return		The rational-B-Spline point at the position t.
					 */
					carve::geom::vector<3> computePointOfRationalBSpline(
						const int& order,
						const double& t,
						const std::vector<carve::geom::vector<3>>& controlPoints,
						const int& numControlPoints,
						const std::vector<double>& knotArray,
						const std::vector<double>& weightsData) const throw(...)
					{
						// 1) Evaluate basis functions at curve point t
						std::vector<double> basisFuncs = computeBSplineBasisFunctions(order, t, numControlPoints, knotArray);

						// 2) Compute exact point
						carve::geom::vector<3> point = carve::geom::VECTOR(0, 0, 0);

						// 2i) If B-spline surface is rational, weights and their sum have to considered, as well
						double weightSum = 0.0;

						for (int j = 0; j < numControlPoints; ++j)
						{
							// 3a) apply formula for rational B-spline surfaces
							const double weightProduct = weightsData[j] * basisFuncs[j];
							point += weightProduct * controlPoints[j];
							weightSum += weightProduct;
						}

						point /= weightSum;

						return point;
					}

					/*! \brief Computes the B-Spline basis functions for given curve value t.
					 *
					 * For one specific value of t the function composes and evaluates the basis functions (=blending functions) of a B-Spline.
					 *
					 * \param[in]	order				Order of the B-Spline or rather the basis functions ( =degree+1 )
					 * \param[in]	t					Evaluation point of the curve c(t)
					 * \param[in]	numControlPoints	The total number of B-Spline control points ( =n+1 )
					 * \param[in]	knotVector			The array / vector of knots obtained from \c IfcBSplineCurveWithKnots,
					 *									the function \c loadKnotArray gives this vector.
					 *
					 * \return							Vector of evaluated basis functions, vector size is equal to number of control points.
					 */
					std::vector<double> computeBSplineBasisFunctions(
						const int order, // k: order of basis and polynomial of degree k - 1
						const double t, // t: arbitrary value on B-Spline curve
						const uint32_t numControlPoints, // n + 1 control points
						const std::vector<double>& knotVector // t_i: knot points
					) const throw(...)
					{
						const int degree = order - 1;
						const uint16_t numBasisFuncs = degree + numControlPoints;
						const uint16_t numKnots = order + numControlPoints;
						// create temporary basis functions of size k + n (or d + (n + 1), with d = k - 1)
						std::vector<double> tempBasisFuncs = obtainBasisFunctionFirstOrder(t, numBasisFuncs, knotVector);

						// build basis functions of higher order up-to order = degree
						for (int k = 1; k <= degree; ++k)
						{
							obtainBasisFunctionNextOrder(k, t, knotVector, tempBasisFuncs);
							// tempBasisFuncs is the return value by reference
						}

						std::vector<double> basisFuncs;
						basisFuncs.reserve(numControlPoints);
						const uint32_t numBasis = numControlPoints;
						for (size_t j = 0; j < numBasis; ++j) {
							basisFuncs[j] = tempBasisFuncs[j];
						}
						return basisFuncs;
					}

					/*! \brief Sets the basis functions of order one
					 *
					 * \param[in]	t				Evaluation point of the curve c(t)
					 * \param[in]	numBasisFuncs	Number of basis functions in first order
					 * \param[in]	knotVector		The array / vector of knots obtained from \c IfcBSplineCurveWithKnots.
					 *
					 * \return		A vector of the basis functions 'order one'
					 */
					std::vector<double> obtainBasisFunctionFirstOrder(
						const double& t,
						const uint16_t& numBasisFuncs,
						const std::vector<double>& knotVector) const throw(...)
					{
						std::vector<double> tempBasisFuncs(numBasisFuncs, 0.0);

						// intialize first order basis functions
						for (auto i = 0; i < numBasisFuncs; ++i) {
							const double knot = knotVector[i];
							const double knotNext = knotVector[i + 1];
							if (t >= knot && t < knotNext && knot < knotNext) {
								tempBasisFuncs[i] = 1.0;
							}
						}

						return tempBasisFuncs;
					}

					/*! \brief Computes the basis functions of next higher order.
					 *
					 * Increases the order of basis functions from k-1 to k.
					 *
					 * \param[in] k				 Order k of basis functions which should be computed.
					 * \param[in] t				 Evaluation point of the curve c(t)
					 * \param[in] knotVector	 The array / vector of knots obtained from \c IfcBSplineCurveWithKnots.
					 * \param[in] tempBasisFuncs Vector of basis functions of order k-1
					 *
					 * \return	  Vector of basis functions of order k
					 */
					void obtainBasisFunctionNextOrder(
						const int& k,
						const double& t,
						const std::vector<double>& knotVector,
						std::vector<double>& tempBasisFuncs) const throw(...)
					{
						double basisFuncFirst;
						double basisFuncSecond;

						for (size_t i = 0; i < tempBasisFuncs.size() - k; ++i) {
							const double t_i = knotVector[i];
							const double t_ik = knotVector[i + k];
							const double t_ik1 = knotVector[i + k + 1];
							const double t_i1 = knotVector[i + 1];

							// function is zero if basis is zero or denominator is zero
							if (tempBasisFuncs[i] == 0 || t_ik == t_i) 
							{ 
								basisFuncFirst = 0.0; 
							}
							else
							{
								// apply formula of first part
								basisFuncFirst = (t - t_i) / (t_ik - t_i) * tempBasisFuncs[i];
							}

							// function is zero if basis is zero or denominator is zero
							if (tempBasisFuncs[i + 1] == 0 || t_ik1 == t_i1) 
							{ 
								basisFuncSecond = 0.0; 
							}
							else 
							{
								// apply formula of first part
								basisFuncSecond = (t_ik1 - t) / (t_ik1 - t_i1) * tempBasisFuncs[i + 1];
							}

							// compute sum and set as basis function for next order
							tempBasisFuncs[i] = basisFuncFirst + basisFuncSecond;
						}
						// return tempBasisFuncs;
					}

					/*! \brief Computes the vector of first derivative at the location \c t.
					 *
					 * This function is for B-Splines from an \c IfcBSplineCurveWithKnots entity.
					 *
					 * \param[in]	order				Order of the B-Spline or rather the basis functions ( =degree+1 )
					 * \param[in]	t					The parameter value t of the curve c(t).
					 * \param[in]	controlPoints		The vector of the B-Spline control points.
					 * \param[in]	knotArray			The array / vector of knots, the function \c loadKnotArray gives this vector.
					 *
					 * \return		The vector of first derivative at the position t.
					 */
					carve::geom::vector<3> computePointOfDerivativeOne(
						const int& order,
						const double& t,
						const std::vector<carve::geom::vector<3>>& controlPoints,
						const std::vector<double>& knotArray)const throw(...)
					{
						// 1) Evaluate basis functions of first derivative at curve point t
						const std::vector<double> basisFuncs = computeDerivativeOneBasisFunctions(order, t, controlPoints.size(), knotArray);

						// 2) Compute exact point
						carve::geom::vector<3> point = carve::geom::VECTOR(0, 0, 0);

						for (size_t j = 0; j < controlPoints.size(); ++j)
						{
							// 3b) apply formula for normal B-spline curves
							point += basisFuncs[j] * controlPoints[j];
						}

						return point;
					}

					/*! \brief Computes the first derivative of basis functions for given curve value \c t.
					 *
					 * For one specific value of t the function composes and evaluates the basis functions (=blending functions) of the first derivative.
					 *
					 * \param[in]	order				Order of the B-Spline or rather the basis functions ( =degree+1 )
					 * \param[in]	t					Evaluation point of the curve c(t)
					 * \param[in]	numControlPoints	The total number of B-Spline control points ( =n+1 )
					 * \param[in]	knotArray			The array / vector of knots obtained from \c IfcBSplineCurveWithKnots,
					 *									the function \c loadKnotArray gives this vector.
					 *
					 * \return							Vector of evaluated first derivative basis functions, vector size is equal to number of control points.
					 */
					std::vector<double> computeDerivativeOneBasisFunctions(
						const int& order,
						const double& t,
						const size_t& numControlPoints,
						const std::vector<double>& knotArray) const throw(...)
					{
						const uint16_t numBasisFuncs = order-1 + numControlPoints;

						std::vector<double> basisFuncsBSpline = obtainBasisFunctionFirstOrder(t, numBasisFuncs, knotArray);
						std::vector<double> basisFuncsDerivativeOne = obtainBasisFunctionDerivativeFirstOrder(numBasisFuncs);

						// in C++, k goes from 0 to order-1 = degree; k=0 is done with obtain..FirstOrder()
						// in mathematical definition, k goes from 1 to order
						for (int k = 1; k < order; k++)
						{
							obtainBasisFunctionDerivativeOneNextOrder(k, t, knotArray, basisFuncsBSpline, basisFuncsDerivativeOne);
							// basisFuncsDerivativeOne is the return value by reference

							obtainBasisFunctionNextOrder(k, t, knotArray, basisFuncsBSpline);
							// basisFuncsBSpline is the return value by reference
						}

						std::vector<double> basisFuncs;
						basisFuncs.reserve(numControlPoints);
						const size_t numBasis = numControlPoints;
						for (size_t j = 0; j < numBasis; ++j) {
							basisFuncs[j] = basisFuncsDerivativeOne[j];
						}
						return basisFuncs;
					}

					/*! \brief Sets the first derivative basis functions of order one
					 *
					 * \param[in]	numBasisFuncs	Number of basis functions in first order
					 *
					 * \return		A vector of the first derivative basis functions 'order one'
					 */
					std::vector<double> obtainBasisFunctionDerivativeFirstOrder(
						const uint16_t& numBasisFuncs) const throw(...)
					{
						return std::vector<double> (numBasisFuncs, 0.0);
					}

					/*! \brief Computes the first derivative basis functions of next higher order.
					 *
					 * Increases the order of first derivative basis functions from k-1 to k.
					 *
					 * \param[in] k						   Order k of basis functions which should be computed.
					 * \param[in] t						   Evaluation point of the curve c(t)
					 * \param[in] knotVector			   The array / vector of knots obtained from \c IfcBSplineCurveWithKnots.
					 * \param[in] basisFuncsBSpline		   Vector of basis functions of order k-1
					 * \param[in] basisFuncsDerivativeOne  Vector of first derivative basis functions of order k-1
					 *
					 * \return	  Vector of first derivative basis functions of order k
					 */
					void obtainBasisFunctionDerivativeOneNextOrder(
						const int& k,
						const double& t,
						const std::vector<double>& knotVector,
						const std::vector<double>& basisFuncsBSpline,
						std::vector<double>& basisFuncsDerivativeOne) const throw(...)
					{
						double firstSummand;
						double secondSummand;

						for (size_t i = 0; i < basisFuncsDerivativeOne.size() - k; ++i) {
							const double t_i = knotVector[i];
							const double t_ik = knotVector[i + k];
							const double t_ik1 = knotVector[i + k + 1];
							const double t_i1 = knotVector[i + 1];

							// function is zero if denominator is zero
							if (t_ik == t_i)
								firstSummand = 0.0;
							else
								// apply formula of first part
								firstSummand = (basisFuncsBSpline[i] + (t - t_i)*basisFuncsDerivativeOne[i]) / (t_ik - t_i);

							// function is zero if denominator is zero
							if (t_ik1 == t_i1)
								secondSummand = 0.0;
							else
								// apply formula of first part
								secondSummand = ((t_ik1 - t)*basisFuncsDerivativeOne[i+1] - basisFuncsBSpline[i+1]) / (t_ik1 - t_i1);

							// compute sum and set as basis function for next order
							basisFuncsDerivativeOne[i] = firstSummand + secondSummand;
						}
						// return basisFuncsDerivativeOne;
					}

					/*! \brief Computes the vector of second derivative at the location \c t.
					 *
					 * This function is for B-Splines from an \c IfcBSplineCurveWithKnots entity.
					 *
					 * \param[in]	order				Order of the B-Spline or rather the basis functions ( =degree+1 )
					 * \param[in]	t					The parameter value t of the curve c(t).
					 * \param[in]	controlPoints		The vector of the B-Spline control points.
					 * \param[in]	knotArray			The array / vector of knots, the function \c loadKnotArray gives this vector.
					 *
					 * \return		The vector of second derivative at the position t.
					 */
					carve::geom::vector<3> computePointOfDerivativeTwo(
						const int& order,
						const double& t,
						const std::vector<carve::geom::vector<3>>& controlPoints,
						const std::vector<double>& knotArray)const throw(...)
					{
						// 1) Evaluate basis functions of first derivative at curve point t
						const std::vector<double> basisFuncs = computeDerivativeTwoBasisFunctions(order, t, controlPoints.size(), knotArray);

						// 2) Compute exact point
						carve::geom::vector<3> point = carve::geom::VECTOR(0, 0, 0);

						for (size_t j = 0; j < controlPoints.size(); ++j)
						{
							// 3b) apply formula for normal B-spline curves
							point += basisFuncs[j] * controlPoints[j];
						}

						return point;
					}

					/*! \brief Computes the second derivative of basis functions for given curve value \c t.
					 *
					 * For one specific value of t the function composes and evaluates the basis functions (=blending functions) of the second derivative.
					 *
					 * \param[in]	order				Order of the B-Spline or rather the basis functions ( =degree+1 )
					 * \param[in]	t					Evaluation point of the curve c(t)
					 * \param[in]	numControlPoints	The total number of B-Spline control points ( =n+1 )
					 * \param[in]	knotArray			The array / vector of knots obtained from \c IfcBSplineCurveWithKnots,
					 *									the function \c loadKnotArray gives this vector.
					 *
					 * \return							Vector of evaluated second derivative basis functions, vector size is equal to number of control points.
					 */
					std::vector<double> computeDerivativeTwoBasisFunctions(
						const int& order,
						const double& t,
						const size_t& numControlPoints,
						const std::vector<double>& knotArray) const throw(...)
					{
						const uint16_t numBasisFuncs = order - 1 + numControlPoints;

						std::vector<double> basisFuncsBSpline = obtainBasisFunctionFirstOrder(t, numBasisFuncs, knotArray);
						std::vector<double> basisFuncsDerivativeOne = obtainBasisFunctionDerivativeFirstOrder(numBasisFuncs);
						std::vector<double> basisFuncsDerivativeTwo = obtainBasisFunctionDerivativeFirstOrder(numBasisFuncs);

						// in C++, k goes from 0 to order-1 = degree; k=0 is done with obtain..FirstOrder()
						// in mathematical definition, k goes from 1 to order
						for (int k = 1; k < order; k++)
						{
							obtainBasisFunctionDerivativeTwoNextOrder(k, t, knotArray, basisFuncsBSpline, basisFuncsDerivativeOne, basisFuncsDerivativeTwo);
							// basisFuncsDerivativeTwo is the return value by reference

							obtainBasisFunctionDerivativeOneNextOrder(k, t, knotArray, basisFuncsBSpline, basisFuncsDerivativeOne);
							// basisFuncsDerivativeOne is the return value by reference

							obtainBasisFunctionNextOrder(k, t, knotArray, basisFuncsBSpline);
							// basisFuncsBSpline is the return value by reference
						}

						std::vector<double> basisFuncs;
						basisFuncs.reserve(numControlPoints);
						const size_t numBasis = numControlPoints;
						for (size_t j = 0; j < numBasis; ++j) {
							basisFuncs[j] = basisFuncsDerivativeTwo[j];
						}
						return basisFuncs;
					}

					/*! \brief Computes the second derivative basis functions of next higher order.
					 *
					 * Increases the order of second derivative basis functions from k-1 to k.
					 *
					 * \param[in] k						   Order k of basis functions which should be computed.
					 * \param[in] t						   Evaluation point of the curve c(t)
					 * \param[in] knotVector			   The array / vector of knots obtained from \c IfcBSplineCurveWithKnots.
					 * \param[in] basisFuncsBSpline		   Vector of basis functions of order k-1
					 * \param[in] basisFuncsDerivativeOne  Vector of first derivative basis functions of order k-1
					 * \param[in] basisFuncsDerivativeTwo  Vector of second derivative basis functions of order k-1
					 *
					 * \return	  Vector of second derivative basis functions of order k
					 */
					void obtainBasisFunctionDerivativeTwoNextOrder(
						const int& k,
						const double& t,
						const std::vector<double>& knotVector,
						const std::vector<double>& basisFuncsBSpline,
						const std::vector<double>& basisFuncsDerivativeOne,
						std::vector<double>& basisFuncsDerivativeTwo) const throw(...)
					{
						if (k == 2)
						{
							for (size_t i = 0; i < basisFuncsDerivativeTwo.size() - k; ++i)
								basisFuncsDerivativeTwo[i] = 0;
						}
						else
						{
							double firstSummand;
							double secondSummand;

							for (size_t i = 0; i < basisFuncsDerivativeTwo.size() - k; ++i) {
								const double t_i = knotVector[i];
								const double t_ik = knotVector[i + k];
								const double t_ik1 = knotVector[i + k + 1];
								const double t_i1 = knotVector[i + 1];

								// function is zero if denominator is zero
								if (t_ik == t_i)
									firstSummand = 0.0;
								else
									// apply formula of first part
									firstSummand = (2*basisFuncsDerivativeOne[i] + (t - t_i)*basisFuncsDerivativeTwo[i]) / (t_ik - t_i);

								// function is zero if denominator is zero
								if (t_ik1 == t_i1)
									secondSummand = 0.0;
								else
									// apply formula of first part
									secondSummand = ((t_ik1 - t)*basisFuncsDerivativeTwo[i + 1] - 2* basisFuncsDerivativeOne[i + 1]) / (t_ik1 - t_i1);

								// compute sum and set as basis function for next order
								basisFuncsDerivativeTwo[i] = firstSummand + secondSummand;
							}
							// return basisFuncsDerivativeTwo;
						}
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
								computeBSplineBasisFunctions(orderU, tU, numControlPointsU, knotVectorU, basisFuncsU);
								computeBSplineBasisFunctions(orderV, tV, numControlPointsV, knotVectorV, basisFuncsV);

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

			//template<>
			//inline void SplineConverterT<emt::Ifc4EntityTypes, OpenInfraPlatform::Ifc4::UnitConverter>::convertIfcBSplineSurface(
			//	const std::shared_ptr<emt::Ifc4EntityTypes::IfcBoundedSurface>& splineSurfaceWithKnots,
			//	const std::vector<std::vector<carve::geom::vector<3>>>& controlPoints,
			//	std::shared_ptr<carve::input::PolylineSetData>& polylineData)
			//{
			//	std::shared_ptr<emt::Ifc4EntityTypes::IfcBSplineSurfaceWithKnots> bsplineSurfaceWithKnots =
			//		std::dynamic_pointer_cast<emt::Ifc4EntityTypes::IfcBSplineSurfaceWithKnots>(splineSurfaceWithKnots);
			//
			//	if (splineSurfaceWithKnots)
			//	{
			//		// obtain degree of both b-spline curves
			//		const int degreeU = bsplineSurfaceWithKnots->m_UDegree;
			//		const int orderU = degreeU + 1;
			//		const int degreeV = bsplineSurfaceWithKnots->m_VDegree;
			//		const int orderV = degreeV + 1;
			//		// obtain number of control points
			//		const int numControlPointsU = controlPoints.size();
			//		const int numControlPointsV = controlPoints[0].size();
			//		// obtain number of knots
			//		const int numKnotsU = orderU + numControlPointsU;
			//		const int numKnotsV = orderV + numControlPointsV;
			//
			//		// obtain knots for each direction
			//		const std::vector<int>& knotMultsU = bsplineSurfaceWithKnots->m_UMultiplicities;
			//		const std::vector<std::shared_ptr<emt::Ifc4EntityTypes::IfcParameterValue>>& splineKnotsU = bsplineSurfaceWithKnots->m_UKnots;
			//		const std::vector<int>& knotMultsV = bsplineSurfaceWithKnots->m_VMultiplicities;
			//		const std::vector<std::shared_ptr<emt::Ifc4EntityTypes::IfcParameterValue>>& splineKnotsV = bsplineSurfaceWithKnots->m_VKnots;
			//
			//		std::vector<double> knotsU;
			//		std::vector<double> knotsV;
			//		knotsU.reserve(numKnotsU);
			//		knotsV.reserve(numKnotsV);
			//
			//		for (int i = 0; i < splineKnotsU.size(); ++i)
			//		{
			//			double knot = splineKnotsU[i]->m_value;
			//			const int knotMult = knotMultsU[i];
			//			// look at the multiplicity of the current knot
			//			for (int j = 0; j < knotMult; ++j)
			//			{
			//				knotsU.push_back(knot);
			//			}
			//		}
			//
			//		for (int i = 0; i < splineKnotsV.size(); ++i)
			//		{
			//			double knot = splineKnotsV[i]->m_value;
			//			const int knotMult = knotMultsV[i];
			//			// look at the multiplicity of the current knot
			//			for (int j = 0; j < knotMult; ++j)
			//			{
			//				knotsV.push_back(knot);
			//			}
			//		}
			//
			//		std::vector<std::vector<double>> weights;
			//
			//		std::shared_ptr<emt::Ifc4EntityTypes::IfcRationalBSplineSurfaceWithKnots> rationalBsplineSurfaceWithKnots =
			//			std::dynamic_pointer_cast<emt::Ifc4EntityTypes::IfcRationalBSplineSurfaceWithKnots>(splineSurfaceWithKnots);
			//
			//		if (rationalBsplineSurfaceWithKnots)
			//		{
			//			weights = rationalBsplineSurfaceWithKnots->m_WeightsData;
			//		}
			//
			//		// reserve memory for all surface points on b-spline surface
			//		//! TEMPORARY default number of curve points
			//		const uint8_t numCurvePointsU = splineKnotsU.size() * 10;
			//		const uint8_t numCurvePointsV = splineKnotsV.size() * 10;
			//		std::vector<carve::geom::vector<3>> curvePoints;
			//		curvePoints.reserve(numCurvePointsU * numCurvePointsV);
			//
			//		computeBSplineSurface(orderU, orderV, numCurvePointsU, numCurvePointsV, 
			//			numControlPointsU, numControlPointsV,
			//			controlPoints, weights, knotsU, knotsV, curvePoints);
			//
			//		std::unordered_map<std::string, int> vertexMap;
			//		vertexMap.reserve(curvePoints.size());
			//
			//		for (int v = 0; v < numCurvePointsV - 1; ++v)
			//		{
			//			for (int u = 0; u < numCurvePointsU - 1; ++u)
			//			{
			//				std::vector<carve::geom::vector<3>> facePoints;
			//				facePoints.reserve(4);
			//
			//				facePoints.push_back(curvePoints[u + numCurvePointsU * v]); // 00
			//				facePoints.push_back(curvePoints[u + 1 + numCurvePointsU * v]); // 10
			//				facePoints.push_back(curvePoints[u + 1 + numCurvePointsU * (v + 1)]); // 11
			//				facePoints.push_back(curvePoints[u + numCurvePointsU * (v + 1)]); // 01
			//
			//				size_t indices[4];
			//
			//				polylineData->beginPolyline();
			//
			//				for (auto k = 0; k < 4; ++k)
			//				{
			//					std::stringstream key;
			//					key << facePoints[k].x << " " << facePoints[k].y << " " << facePoints[k].z;
			//
			//					if (vertexMap.find(key.str()) != vertexMap.end()) { indices[k] = vertexMap[key.str()]; }
			//					else
			//					{
			//						indices[k] = polylineData->addVertex(facePoints[k]);
			//						vertexMap[key.str()] = indices[k];
			//					}
			//
			//					polylineData->addPolylineIndex(indices[k]);
			//				}
			//			}
			//		}
			//	}
			//}
		} // end namespace IfcGeometryConverter
	} // end namespace Core
} // end namespace OpenInfraPlatform

#endif