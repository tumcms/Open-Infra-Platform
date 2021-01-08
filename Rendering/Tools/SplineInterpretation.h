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
			 * In case of an error, the function will return a vector of size 0.
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
			 * and the syntax which is provided by the function \c saveControlPointsIntoFile.\n
			 * In case of an error, the function will retrun a vector of size 0.
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
			 * \param[in]	xy	A vector of pairs; the first pair value denotes x, second pair value denotes y. In example, the pair denotes {curveLength, curvature}.
			 *
			 * \return	A vector of the y-values of the derivative. The vector will be one shorter as the original vector of pairs.
			 */
			std::vector<double> numericDerivative(std::vector<std::pair<double, double>>& xy) const throw(...);

			/* \brief Identifies the endpoints of the alignment elements based on the change of curvature.
			 *
			 * A curve (e.g. a B-Spline curve), described by its curvature and change of curvature, is analysed to find the start- and end-points of alignment elements.
			 * Based on the relative value of the curvature change an alternate sequence of (1) transition curves and (2) straights or circular arcs are defined by their
			 * start- and end-point-id, curve length and type.\n
			 * The type is represented by an indicator:\n
			 * case 1: indicator = 1 -> transition curve\n
			 * case 2: indicator = 0 -> straight, or circular arc\n
			 *
			 * \param[in]	lengthsWithCurvatures	A vector of \c pair<double,double> with the curve length (first element in \c pair ) and the corresponding curvature (second element in \c pair ) of a curve.
			 * \param[in]	curvatureChange			A vector of \c double with the change of curvature, corresponding to \c lengthsWithCurvatures.
			 *
			 * \return	A vector of \c SplineInterpretationElement, per element the information about start-/end-point, length, and corresponding id in 'lengthWithCurvature' is stored.
			 */
			std::vector<SplineInterpretationElement> identifyElementEndpoints(
				std::vector<std::pair<double, double>> lengthsWithCurvatures, std::vector<double> curvatureChange) const throw(...);

			/* \brief Examines the value of curvature change by a relative threshold.
			 *
			 * If an absolute value is less than the threshold, the indicator is 0, otherwise 1. The threshold is obtained by the call of the function \c obtainThreshold.
			 *
			 * \param[in]	curvatureChange		A vector of \c double with the change of curvature, corresponding to \c lengthsWithCurvatures.
			 *
			 * \return		Vector with indicators of curvature change and the (one) corresponding threshold value.
			 */
			std::tuple<std::vector<int>, double> indicateCurvatureChange(std::vector<double> curvatureChange) const throw(...);

			/* \brief Returns the threshold value from a vector of \c double.
			 *
			 * The threshold is defined by the function as 25 % of the absolute magnitude.
			 *
			 * \param[in]	data	A vector of \c double.
			 *
			 * \return	Threshold value.
			 */
			double obtainThreshold(std::vector<double> data) const throw(...);

			/* \brief Converts a vector of indicators to a vector of elements.
			 * 
			 * Each sequence of identical indicators is grouped as one element. This function doesn't care about the minimum length of elements.
			 * Per element the information about start-/end-point, length, and corresponding id in 'lengthWithCurvature' is stored in a \c SplineInterpretationElement.
			 * All \c SplineInterpretationElement are grouped in a vector.
			 *
			 * \param[in]	indicator				Vector of indicators, e.g. the return from the function \c indicateCurvatureChange.
			 * \param[in]	lengthsWithCurvatures	Vector of \c pair<double,double> where the first pair value is the curve length.
			 *
			 * \return	A vector of \c SplineInterpretationElement, per element the information about start-/end-point, length, and corresponding id in 'lengthWithCurvature' is stored.
			 */
			std::vector<SplineInterpretationElement> obtainElementsFromIndicator(std::vector<int> indicator, std::vector<std::pair<double, double>> lengthsWithCurvatures) const throw(...);

			/* \brief Corrects the indicator of short elements.
			 *
			 * If an element is shorter than the minimum length (50 m), its indicator will be changed in dependency of neighbour elements:
			 * In case one element is to short, its indicator will be changed.
			 * In case of multiple contiguous elements are to short, a new average of curvature change is the base of the new indicator.
			 *
			 * \param[in]	elements			Vector of elements, includes short elements.
			 * \param[in]	curvatureChange		Change of curvature of the hole curve.
			 * \param[in]	curvatureZero		Threshold of curvature change.
			 *
			 * \return	Vector of elements with corrected indicators.
			 */
			std::vector<SplineInterpretationElement> correctShortElements(std::vector<SplineInterpretationElement> elements, std::vector<double> curvatureChange, const double curvatureZero) const throw(...);

			//int indicateDataByAverage(std::vector<std::pair<double, double>> lengthsWithCurvatures, double threshold) const throw(...);

			/* \brief Gives the indicator of the \c data vector, based on the given \c threshold.
			 *
			 * The function calculates the arithmetical average of the values in \c data and returns an indicator (-1, 0, or 1) based on the \c threshold:\n
			 * average < -threshold -> -1\n
			 * average >  threshold ->  1\n
			 * else -> 0
			 *
			 * \param[in]	data		Vecotr of \c double values.
			 * \param[in]	threshold	Threshold for the definition of the indicator.
			 *
			 * \return	The obtained indicator.
			 */
			int indicateDataByAverage(std::vector<double> data, double threshold) const throw(...);

			/* \brief Contiguous elements with an identical indicator will be merged to one large element.
			 *
			 * \param[in]	elements	Vector of alignment elements of type \c SplineInterpretationElement.

			 * \return	Vector with merged alignment elements.
			 */
			std::vector<SplineInterpretationElement> mergeShortElements(std::vector<SplineInterpretationElement> elements) const throw(...);

			/* \brief	Obtains the type and its parameter of the alignment elements.
			 *
			 * The function decides per element which type it is (straight, circular arc, clothoid) and obtains their parameters by the call of appropriate functions.
			 * The results are saved in the vector \c elements.
			 *
			 * \param[in]	bsplinePoints			Curve points along the curve.
			 * \param[in]	lengthsWithCurvatures	Curve length with corresponding curvature.
			 * \param[in]	elements				Vector of elements, without identified alignment type.
			 *
			 * \return	Vector of defined alignment elements.
			 */
			std::vector<SplineInterpretationElement> identifyElementTypes(
				const std::vector<carve::geom::vector<3>>& bsplinePoints, 
				const std::vector<std::pair<double, double>>& lengthsWithCurvatures, 
				std::vector<SplineInterpretationElement>& elements) const throw(...);

			/* \brief	The function sets the parameters of a straight.
			 *
			 * The parameters type, start point, direction, and length will be calculated and set in the \c element object.
			 *
			 * \param[in]	startPoint	Curve point of the approximated B-Spline curve at the begin of the straight.
			 * \param[in]	endPoint	Curve point of the approximated B-Spline curve at the end of the straight.
			 * \param[in]	element		Corresponding alignment element to the straight.
			 *
			 * \return	\c element object with the parameters of the straight.
			 */
			SplineInterpretationElement obtainStraight(
				const carve::geom::vector<3>& startPoint, const carve::geom::vector<3>& endPoint, SplineInterpretationElement& element) const throw(...);

			/* \brief	The function sets the parameters of a circular arc.
			 *
			 * The parameters type, start point, direction, length, center, radius, isCCW, and angle will be calculated and set in the \c element object.
			 * The parameter isCCW stands for 'is counter-clock-wise' and describes the orientation of the arc. If isCCW is 'true', it's a left turn, otherwise it's a right turn.
			 * The parameter angle is defined as central angle, here without a sign.
			 *
			 * \param[in]	startPoint			Curve point of the approximated B-Spline curve at the begin of the arc.
			 * \param[in]	midPoint			Curve point of the approximated B-Spline curve at the end of the arc.
			 * \param[in]	endPoint			Curve point of the approximated B-Spline curve at the end of the arc.
			 * \param[in]	curvatureIndicator	Indicates curvature with -1 for curvature < 0 (right turn) or 1 for curvature > 0 (left turn).
			 * \param[in]	element				Corresponding alignment element to the circular arc.
			 *
			 * \return	\c element object with the parameters of the circular arc.
			 */
			SplineInterpretationElement obtainArc(
				const carve::geom::vector<3>& startPoint, 
				const carve::geom::vector<3>& midPoint,
				const carve::geom::vector<3>& endPoint, 
				const int curvatureIndicator,
				SplineInterpretationElement& element) const throw(...);

			/* \brief	The function sets the parameters of a clothoid.
			 *
			 * The parameters type, start point, direction, length, radius at start, radius at end, isCCW, and clothoid parameter will be calculated and set in the \c element object.
			 * The parameter isCCW stands for 'is counter-clock-wise' and describes the orientation of the arc. If isCCW is 'true', it's a left turn, otherwise it's a right turn.
			 *
			 * \param[in]	previousElement	Previous alignment element of type \c element with seted parameters.
			 * \param[in]	nextElement		Next / following alignment element of type \c element with seted parameters.
			 * \param[in]	startPoint		Curve point of the approximated B-Spline curve at the begin of the clothoid.
			 * \param[in]	element			Corresponding alignment element to the clothoid.
			 *
			 * \return	\c element object with the parameters of the clothoid.
			 */
			SplineInterpretationElement obtainClothoid(
				const SplineInterpretationElement previousElement,
				const SplineInterpretationElement nextElement,
				const carve::geom::vector<3>& startPoint,
				SplineInterpretationElement& element) const throw(...);

			/* \brief	Calculates the angle in degree measured in xy-plane between two 3D vectors.
			 *
			 * The z coordinate will be ignored
			 *
			 * \param[in]	a	First vector.
			 ' \param[in]	b	Second vector.
			 *
			 * \return	Angle [degree] between vectors.
			 */
			double angleOfVectors2D(const carve::geom::vector<3>& a, const carve::geom::vector<3>& b) const throw(...);

			/* \brief Calculates the direction / angle of an tangential straight at one point of an arc, relative to the positive x-axis, in xy-plane.
			 *
			 * The calculation is in the xy-plane, the z coordinate will be ignored.
			 *
			 * \param[in]	centerPoint		Coordinates of the arc center.
			 * \param[in]	tangentPoint	Coordinates of the tangential point where the angle should be calculated.
			 * \param[in]	isCCW			Orientation 'is counter-clock-wise of the arc.
			 *
			 * \return	Tangential direction at the given tangent point.
			 */
			double tangentDirection(const carve::geom::vector<3>& centerPoint, const carve::geom::vector<3>& tangentPoint, const int isCCW) const throw(...);

			/* \brief Calculates the 2D tangential vector at one point of an arc.
			 *
			 * The calculation is in the xy-plane, the z coordinate will be ignored.
			 *
			 * \param[in]	centerPoint		Coordinates of the arc center.
			 * \param[in]	tangentPoint	Coordinates of the tangential point where the angle should be calculated.
			 * \param[in]	isCCW			Orientation 'is counter-clock-wise of the arc.
			 *
			 * \return	Tangential vector at the given tangent point.
			 */
			carve::geom::vector<3> tangentVector(const carve::geom::vector<3>& centerPoint, const carve::geom::vector<3>& tangentPoint, const int isCCW) const throw(...);

			/* \brief	Gives an unit vector which shows in the direction of the given angle \c direction, relative to the positive x-axis.
			 *
			 * The function name correspondes to the usage in the class \c SplienInterpretation 
			 * where this function usually calculate the tangential vector at an alignment element start.
			 *
			 * \param[in]	direction	The agle of the tangential vector in degree, relative to the positive x-axis.
			 *
			 * \return	Tangential vector of the given direction / angle.
			 */
			carve::geom::vector<3> tangentVectorFromDirection(double direction) const throw(...);

			/* \brief	Prints the obtained information of all alignment elements as result into the console window.
			 *
			 * \param[in]	elements	Vector of \c SplineInterpretationElement which contains all obtained information about the alignment elements.
			 */
			void printElementsInConsoleWindow(const std::vector<SplineInterpretationElement>& elements) const;


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