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

#pragma once

#include <vector>
#include "SplineInterpretationElement.h"
#include "IfcGeometryConverter/CarveHeaders.h"

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		/*! \brief The class provides functions to interpret / convert the stroke of a sketch to an alignment.
		 *
		 * \c convertSketchToAlignment is the current main function.
		 */
		class SplineInterpretation
		{
		public:
			// CONSTRUCTOR
			/*! \brief Default constructor of \c SplineInterpretation
			 */
			SplineInterpretation();

			// FUNCTIONS
			/*! \brief Converts the stroke of a sketch to an alignment.
			 *
			 * During execution, the user decides whether the input data will be sketched on screen or 
			 * will be loaded from a file. The function interprets the data and convert it to an alignment.
			 */
			void convertSketchToAlignment() const throw(...);

		private:
			// VARIABLES
			/*! \brief The value of \c accuracy is needed to call the function \c computeBSplineCurveWithKnots.
			 * 
			 * The value of \c carve::EPSILON is assignt because \c GeometrySettings::getPrecision() uses it at the moment.
			 * Here, \c GeometrySettings::getPrecision() isn't available.
			 */
			double accuracy = carve::EPSILON;

			// FUNCTIONS
			/*! \brief Provides the choise between sketch points or load points.
			 * 
			 * \return A vector of the control points.
			 */
			std::vector<carve::geom::vector<3>> obtainControlPoints() const throw(...);

			/*! \brief Saves the control points or points from sketch input into a file.
			 *
			 * The file will be stored in the directory \c [build folder]/testdata/StrokeToAlignment/. 
			 * The file name will be obtained automatically; it's a consecutive number in dependence on the number of existing files. 
			 * After saving, the file name can be changed manually (e.g. with the usual explorer) in the directory.\n
			 * With every text editor, the file can be opened like a \c .txt file. 
			 * The saved information from line 2 to the end has the syntax, which can be pasted as a matrix into a MATLAB.
			 *
			 * \param [in]	controlPoints	The control points or points from sketch input, which are in a \c std::vector<carve::geom::vector<3>>.
			 */
			void saveControlPointsIntoFile(const std::vector<carve::geom::vector<3>>& points) const throw(...);

			/*! \brief Loads the control points or points from a previous sketch input from a file.
			 *
			 * By default, the save file should be in the directory \c [build folder]/testdata/StrokeToAlignment/.
			 * However, the user can select another directory as well. The selected file must have the type \c .sketch,
			 * and the syntax which is provided by the function \c saveControlPointsIntoFile.
			 *
			 * \return	A vector of the control points.
			 */
			std::vector<carve::geom::vector<3>> loadControlPointsFromFile() const throw(...);

			/*! \brief Generates the open uniform knot array of a B-Spline.
			 *
			 * The elements \c x_i of an open uniform knot array is defined by: \n
			 * \c x_i=0 if \c 1<=i<=order \n
			 * \c x_i=i-order if \c order+1<=i<=numberOfControlPoints \n
			 * \c x_i=numberOfControlPoints-order+1 if \c numberOfControlPoints+1<=i<=numberOfControlPoints+order \n
			 * (vector indices according to mathematical one-based definition)
			 *
			 * \param [in]	nPoints		Number of control points
			 * \param [in]	order		Order of the B-Spline or rather the basis functions ( =degree+1 )
			 *
			 * \return		The open uniform knots array.
			 */
			std::vector<double> obtainKnotArrayOpenUniform(const size_t nPoints, const int order) const throw(...);

			/*! \brief Applies the moving average with variable window on the y-data of \c xy.
			 *
			 * The window size is calculated with a semivariogramm. At the begin and end of the data vector, 
			 * the window size is reduced but symmetrical around the current position. The x-values will not change.\n
			 * This function only obtains the y-values of \c xy and call the function \c movingAverageVariableWindow with a \c std::vector<double>
			 *
			 * \param[in]	xy	A vector of pairs; the first pair value denotes x, second pair value denotes y. In example, the pair denotes {curveLength, curvature}.
			 *
			 * \return			The pair from the input, but the y-values are smoothed by the moving average.
			 */
			std::vector<std::pair<double, double>> movingAverageVariableWindow(std::vector<std::pair<double, double>>& xy) const throw(...);

			/*! \brief Applies the moving average with variable window on the vector \c data.
			 *
			 * The window size is calculated with a semivariogramm. At the begin and end of the data vector, 
			 * the window size is reduced but symmetrical around the current position.
			 *
			 * \param[in]	data	A vector of \c double.
			 *
			 * \return				A vector of \c double, but the values are smoothed by the moving average.
			 */
			std::vector<double> movingAverageVariableWindow(std::vector<double>& data) const throw(...);

			std::vector<double> obtainCurvatureFrom_lengthWithCurvatures(const std::vector<std::pair<double, double>>& lengthsWithCurvatures) const throw(...);

			/* \brief Calculates the range of a variogramm.
			 *
			 * Calculates the semevariogramm variable with the values in \c data. 
			 * The lags are defined by the vector elements; a corresponding vector of x-values should be about equally spaced.
			 * In this implementation, the range is obtaind as the position of the first maximum turning point.
			 *
			 * param[in]	data	A vector of \c double.
			 *
			 * return	Range of a semivariogramm regarding the number of values.
			 */
			size_t variogrammGetRange(std::vector<double>& data) const throw(...);

			/* \brief Calculates the numeric derivative of a vector of x-y-pairs.
			 *
			 * param[in]	xy	A vector of pairs; the first pair value denotes x, second pair value denotes y. In example, the pair denotes {curveLength, curvature}.
			 *
			 * return	A vector of the y-values of the derivative. The vector will be one shorter as the original vector of pairs.
			 */
			std::vector<double> numericDerivative(std::vector<std::pair<double, double>>& xy) const throw(...);

			std::vector<SplineInterpretationElement> identifyElementEndpoints(
				std::vector<std::pair<double, double>> lengthsWithCurvatures, std::vector<double> curvatureChange) const throw(...);

			std::tuple<std::vector<int>, double> indicateCurvatureChange(std::vector<double> curvatureChange) const throw(...);

			double obtainThreshold(const std::vector<std::pair<double, double>>& lengthsWithCurvatures) const throw(...);

			double obtainThreshold(std::vector<double> data) const throw(...);

			std::vector<SplineInterpretationElement> obtainElementsFromIndicator(std::vector<int> indicator, std::vector<std::pair<double, double>> curveLength) const throw(...);

			std::vector<SplineInterpretationElement> correctShortElements(std::vector<SplineInterpretationElement> elements, std::vector<double> curvatureChange, const double curvatureZero) const throw(...);

			//int indicateDataByAverage(std::vector<std::pair<double, double>> lengthsWithCurvatures, double threshold) const throw(...);

			int indicateDataByAverage(std::vector<double> data, double threshold) const throw(...);

			std::vector<SplineInterpretationElement> mergeShortElements(std::vector<SplineInterpretationElement> elements) const throw(...);

			std::vector<SplineInterpretationElement> identifyElementTypes(
				const std::vector<carve::geom::vector<3>>& bsplinePoints, 
				const std::vector<std::pair<double, double>>& lengthsWithCurvatures, 
				std::vector<SplineInterpretationElement>& elements) const throw(...);

			SplineInterpretationElement obtainStraigth(
				const carve::geom::vector<3>& startPoint, const carve::geom::vector<3>& endPoint, SplineInterpretationElement& element) const throw(...);

			SplineInterpretationElement obtainArc(
				const carve::geom::vector<3>& startPoint, 
				const carve::geom::vector<3>& midPoint,
				const carve::geom::vector<3>& endPoint, 
				const int curvatureIndicator,
				SplineInterpretationElement& element) const throw(...);

			double angleOfVectors2D(const carve::geom::vector<3>& a, const carve::geom::vector<3>& b) const throw(...);

			double tangentDirection(const carve::geom::vector<3>& centerPoint, const carve::geom::vector<3>& tangentPoint, const int isCCW) const throw(...);

			carve::geom::vector<3> tangentVector(const carve::geom::vector<3>& centerPoint, const carve::geom::vector<3>& tangentPoint, const int isCCW) const throw(...);


			/*! \brief Displays the vector of length with curvature in the console window.
			 *
			 * The syntax in the consol matches the syntax of MATLAB. The information can be pasted into MATLAB as nx2-matrix.
			 *
			 * param[in] lengthsWithCurvatures	The vector of length with curvature which is the return of \c SplineUtilities::computeCurvatureOfBSplineCurveWithKnots
			 */
			void debugFunction_printCurvatureInConsolWindow(const std::vector<std::pair<double, double>>&) const throw(...);

			/*! \brief Displays the coordinates of a \c std::vector<carve::geom::vector<3>> in the console window.
			 *
			 * In example, this function can be used to print the coordinates of a B-Spline.
			 * The syntax in the consol matches the syntax of MATLAB. The information can be pasted into MATLAB as nx2-matrix.
			 *
			 * param[in] lengthsWithCurvatures	The vector of length with curvature which is the return of \c SplineUtilities::computeCurvatureOfBSplineCurveWithKnots
			 */
			void debugFunction_printVectorOfPointsInConsolWindow(const std::vector<carve::geom::vector<3>>&) const throw(...);

			/*! \brief Displays a \c std::vector<double> in the console window.
			 *
			 * In example, this function can be used to print the \c curvatureChange.
			 * The syntax in the consol matches the syntax of MATLAB. The information can be pasted into MATLAB as nx1-matrix.
			 *
			 * param[in] curvatureChange	The vector of \c double which should be displayed.
			 */
			void debugFunction_printCurvatureChangeInConsolWindow(const std::vector<double> curvatureChange) const throw(...);

		}; // end of class SplineInterpretation
	}
}