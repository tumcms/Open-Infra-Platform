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
#ifndef SPLINEUTILITIES_H
#define SPLINEUTILITIES_H

//#include <sstream>
//#include <memory>

//#include "CarveHeaders.h"
//#include "GeometryInputData.h"
//#include "GeomUtils.h"

//#include "ConverterBase.h"
//#include "PlacementConverter.h"
//#include "CurveConverter.h"


namespace OpenInfraPlatform
{
	namespace Core {
		namespace IfcGeometryConverter {
			/*! \brief Provides some functions for spline calculations.
			 *
			 * Here are functions which are used from the classes \c SplineConverterT and \c SplineInterpretation [and maybe more in future].
			 * These functions are independent from \c GeometrySettings, \c UnitConverter, etc., which aren't included in \c SplineInterpretation.
			 */
			class SplineUtilities
			{
			public:
				SplineUtilities() {}

				virtual ~SplineUtilities() {}

				/*! \brief Computes the curve points of the B-Spline.
				 *
				 * All information has to be loaded from an \c IfcBSplineCurveWithKnots entity before calling this function.
				 *
				 * \param[in]	order				Order of the B-Spline or rather the basis functions ( =degree+1 )
				 * \param[in]	knotArray			The array / vector of knots, the function \c loadKnotArray gives this vector.
				 * \param[in]	controlPoints		The vector of the B-Spline control points.
				 * \param[in]	numControlPoints	The total number of B-Spline control points ( =n+1 )
				 * \param[in]	numCurvePoints		The number of curve points where the curve c(t) has to be evaluated.
				 * \param[in]	accuracy			Accuracy which is technically needed in the calculation.
				 *
				 * \return		The array of curve points, which can be rendered in a viewport after correction by \c GeomUtils::appendPointsToCurve.
				 */
				 // B-Spline curve definition according to: http://mathworld.wolfram.com/B-Spline.html
				std::vector<carve::geom::vector<3>> computeBSplineCurveWithKnots(
					const int& order,
					const std::vector<double>& knotArray,
					const std::vector<carve::geom::vector<3>>& controlPoints,
					const uint32_t& numCurvePoints,
					const double& accuracy) const throw(...)
				{
					// The following parameters corresponds to the parameter t of a curve c(t)
					double knotStart;
					double knotEnd;
					double step;
					std::tie(knotStart, knotEnd, step) = obtainKnotRange(order, knotArray, numCurvePoints);

					std::vector<carve::geom::vector<3>> curvePoints;
					curvePoints.reserve(numCurvePoints);

					// t: representative of the parameter vector, start with first valid knot
					double t = knotStart;

					for (size_t i = 0; i < numCurvePoints; ++i) {
						// the for-loop iterates over all values t of the parameter vector
						if (i == numCurvePoints - 1) { t = knotEnd - accuracy; }

						curvePoints.push_back(computePointOfBSpline(order, t, controlPoints, knotArray));

						// go to next representative t of the parameter vector (= increase its value)
						t += step;
					}

					return curvePoints;
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
				 * \param[in]	numCurvePoints		The number of curve points where the curve c(t) has to be evaluated.
				 * \param[in]	accuracy			Accuracy which is technically needed in the calculation.
				 *
				 * \return		The array of curve points, which can be rendered in a viewport after correction by \c GeomUtils::appendPointsToCurve.
				 */
				 // B-Spline curve definition according to: http://mathworld.wolfram.com/B-Spline.html
				std::vector<carve::geom::vector<3>> computeRationalBSplineCurveWithKnots(
					const int& order,
					const std::vector<double>& knotArray,
					const std::vector<carve::geom::vector<3>>& controlPoints,
					const std::vector<double>& weightsData,
					const uint32_t& numCurvePoints,
					const double& accuracy) const throw(...)
				{
					// The following parameters corresponds to the parameter t of a curve c(t)
					double knotStart;
					double knotEnd;
					double step;
					std::tie(knotStart, knotEnd, step) = obtainKnotRange(order, knotArray, numCurvePoints);

					std::vector<carve::geom::vector<3>> curvePoints;
					curvePoints.reserve(numCurvePoints);

					// t: representative of the parameter vector, start with first valid knot
					double t = knotStart;

					for (size_t i = 0; i < numCurvePoints; ++i) {
						// the for-loop iterates over all values t of the parameter vector
						if (i == numCurvePoints - 1) { t = knotEnd - accuracy; }

						curvePoints.push_back(computePointOfRationalBSpline(order, t, controlPoints, knotArray, weightsData));

						// go to next representative t of the parameter vector (= increase its value)
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
				 * \param[in]	knotArray			The array / vector of knots, the function \c loadKnotArray gives this vector.
				 *
				 * \return		The B-Spline point at the position t.
				 */
				carve::geom::vector<3> computePointOfBSpline(
					const int& order,
					const double& t,
					const std::vector<carve::geom::vector<3>>& controlPoints,
					const std::vector<double>& knotArray) const throw(...)
				{
					const size_t numControlPoints = controlPoints.size();

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

				/*! \brief Computes the rational-B-Spline point at the location t.
				 *
				 * This function is for rational B-Splines from an IfcRationalBSplineCurveWithKnots-entity.
				 *
				 * \param[in]	order				Order of the B-Spline or rather the basis functions ( =degree+1 )
				 * \param[in]	t					The parameter value t of the curve c(t).
				 * \param[in]	controlPoints		The vector of the B-Spline control points.
				 * \param[in]	knotArray			The array / vector of knots, the function \c loadKnotArray gives this vector.
				 * \param[in]	weightsData			The vector with the wight values per knot, the function \c loadWeightsData gives this vector.
				 *
				 * \return		The rational-B-Spline point at the position t.
				 */
				carve::geom::vector<3> computePointOfRationalBSpline(
					const int& order,
					const double& t,
					const std::vector<carve::geom::vector<3>>& controlPoints,
					const std::vector<double>& knotArray,
					const std::vector<double>& weightsData) const throw(...)
				{
					const size_t numControlPoints = controlPoints.size();

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

				/*! \brief Computes the length and curvature of an B-Spline curve
				 *
				 * This function calculates the curvature of a B-Spline; rational B-Splines can't be handled from this function.
				 * As well, the corresponding curve length in xy-plane is calculated.
				 * The \c length is necessary to display or analyse the \c curvature in dependency to the true curve length.
				 * The parameter \c t along a B-Spline curve doesn't represent the true length along the curve because the
				 * calculated curve points aren't evenly spaced. 
				 * The \c length is only needed in the xy-plane because the height in \c z doesn't matter to the intended analyse of the horizontal alignment.\n
				 * The result comes back as a vector of \c std::pair in the order \c length, \c curvature.
				 * Access the members by \c .first to get the length and \c .second to get the curvature.
				 *
				 * \param[in]	order			Order of the B-Spline or rather the basis functions ( =degree+1 )
				 * \param[in]	controlPoints	The vector of the B-Spline control points.
				 * \param[in]	knotArray		The array / vector of knots.
				 * \param[in]	numCurvePoints	The number of curve points where the curvature will be calculated.
				 *
				 * \return		Vector of pairs with curve length and curvature.
				 */
				std::vector<std::pair<double, double>> computeCurvatureOfBSplineCurveWithKnots(
					const int& order,
					const std::vector<carve::geom::vector<3>>& controlPoints,
					const std::vector<double>& knotArray,
					const uint32_t& numCurvePoints) const throw(...)
				{
					const size_t numControlPoints = controlPoints.size();
					
					// at the end, subtract current knot value with accuracy to avoid zero-vectors (since last knot value is excluded by definition)
					const double accuracy = obtainProperties();

					// The following parameters corresponds to the parameter t of a curve c(t)
					double knotStart;
					double knotEnd;
					double step;
					std::tie(knotStart, knotEnd, step) = obtainKnotRange(order, knotArray, numCurvePoints);

					std::vector<std::pair<double, double>> lengthsWithCurvatures;
					lengthsWithCurvatures.resize(numCurvePoints);

					// t: representative of the parameter vector, start with first valid knot
					double t = knotStart;

					carve::geom::vector<3> curvePoint;
					carve::geom::vector<3> curvePointPrevious;
					carve::geom::vector<3> derivativeOne;
					carve::geom::vector<3> derivativeTwo;

					// Debug: Output of first derivative in console
					//std::cout << std::endl << "Values of basis functions first derivative:" << std::endl << "[";

					// Debug: Output of second derivative in console
					//std::cout << std::endl << "Values of basis functions second derivative:" << std::endl << "[";

					for (size_t i = 0; i < numCurvePoints; ++i) {
						// the for-loop iterates over all values t of the parameter vector
						if (i == numCurvePoints - 1) { t = knotEnd - accuracy; }

						curvePoint = computePointOfBSpline(order, t, controlPoints, knotArray);

						derivativeOne = computePointOfDerivativeOne(order, t, controlPoints, knotArray);
						derivativeTwo = computePointOfDerivativeTwo(order, t, controlPoints, knotArray);

						// create lengthsWithCurvatures[i] = {length_i, curvature_i}
						lengthsWithCurvatures[i] = std::pair<double, double>(
							// length_i:
							(i == 0 ? 0 : lengthsWithCurvatures[i - 1].first + lengthInXyPlane(curvePoint - curvePointPrevious)),
							// curvature_i of curve c(t) in xy-plane
							// according to definition 3.500 in Bronstein et al., Taschenbuch der Mathematik, 10. Auflage, 2016
							(derivativeOne.x*derivativeTwo.y - derivativeTwo.x*derivativeOne.y)
							/ (std::pow(std::pow(derivativeOne.x, 2) + std::pow(derivativeOne.y, 2), 3.0 / 2.0)));

						curvePointPrevious = curvePoint;

						// go to next representative t of the parameter vector (= increase its value)
						t += step;
					}

					// Debug: Output in console
					//std::cout << "]";

					return lengthsWithCurvatures;
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

			private:
				/*! \brief Caluclates the length in xy-plane, the height in z doesn't matter.
				 *
				 * \param[in]	vector	The vector from which the length in xy has to be calculated.
				 *
				 * \return		Length in xy-plane from \c vector.
				 */
				double lengthInXyPlane(carve::geom::vector<3> vector) const throw(...)
				{
					return std::sqrt(vector.x*vector.x + vector.y*vector.y);
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
				const double obtainProperties() const throw(...)
				{
					// at the end, subtract current knot value with this to avoid zero-vectors (since last knot value is excluded by definition)
					const double accuracy = 0.0000001;
					//double accuracy = GeomSettings()->getPrecision();

					return { accuracy };
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
					basisFuncs.resize(numControlPoints);
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

						// Debug: Output in console
						//std::cout << " " << basisFuncs[j];
					}

					// Debug: Output in console
					//std::cout << ";" << std::endl;

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
					const uint16_t numBasisFuncs = order - 1 + numControlPoints;

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
					basisFuncs.resize(numControlPoints);
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
					return std::vector<double>(numBasisFuncs, 0.0);
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
							secondSummand = ((t_ik1 - t)*basisFuncsDerivativeOne[i + 1] - basisFuncsBSpline[i + 1]) / (t_ik1 - t_i1);

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

						// Debug: Output in console
						//std::cout << " " << basisFuncs[j];
					}

					// Debug: Output in console
					//std::cout << ";" << std::endl;

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
					basisFuncs.resize(numControlPoints);
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
					if (k == 1)
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
								firstSummand = (2 * basisFuncsDerivativeOne[i] + (t - t_i)*basisFuncsDerivativeTwo[i]) / (t_ik - t_i);

							// function is zero if denominator is zero
							if (t_ik1 == t_i1)
								secondSummand = 0.0;
							else
								// apply formula of first part
								secondSummand = ((t_ik1 - t)*basisFuncsDerivativeTwo[i + 1] - 2 * basisFuncsDerivativeOne[i + 1]) / (t_ik1 - t_i1);

							// compute sum and set as basis function for next order
							basisFuncsDerivativeTwo[i] = firstSummand + secondSummand;
						}
						// return basisFuncsDerivativeTwo;
					}
				}
			}; // end class SplineUtilities
		}
	}
}

#endif