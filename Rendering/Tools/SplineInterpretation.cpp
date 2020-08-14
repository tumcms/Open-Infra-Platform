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

#include "SplineInterpretation.h"

#include "IfcGeometryConverter/SplineUtilities.h"

// CONSTRUCTOR
OpenInfraPlatform::UserInterface::SplineInterpretation::SplineInterpretation()
{
	accuracy = carve::EPSILON;
}

// PUBLIC FUNCTIONS
void OpenInfraPlatform::UserInterface::SplineInterpretation::convertSketchToAlignment() const throw(...)
{
	// obtain control points from sketch or from file
	// (from file is from past sketch or from [external] test data)
	// ToDo:
	// std::vector<carve::geom::vector<3>> controlPoints = ...

	// TEMPORARY constant test data
	std::vector<carve::geom::vector<3>> controlPoints;
	controlPoints.push_back(carve::geom::VECTOR(0., 2., 0.));
	controlPoints.push_back(carve::geom::VECTOR(1., 5., 0.));
	controlPoints.push_back(carve::geom::VECTOR(3., 4., 0.));
	controlPoints.push_back(carve::geom::VECTOR(3., 1., 0.));
	controlPoints.push_back(carve::geom::VECTOR(5., 0., 0.));
	controlPoints.push_back(carve::geom::VECTOR(7., 1., 0.));
	controlPoints.push_back(carve::geom::VECTOR(8., 4., 0.));
	controlPoints.push_back(carve::geom::VECTOR(10., 4., 0.));
	const int order = 4;
	const std::vector<double> knotArray = obtainKnotArrayOpenUniform(controlPoints.size(), order);

	// Compute curvature
	Core::IfcGeometryConverter::SplineUtilities splineUtilities;
	std::vector<std::pair<double, double>> lengthsWithCurvatures = splineUtilities.computeCurvatureOfBSplineCurveWithKnots(order, controlPoints, knotArray);

	// Test B-Spline
	std::vector<carve::geom::vector<3>> bspline = splineUtilities.computeBSplineCurveWithKnots(order, knotArray, controlPoints, 10*knotArray.size(), accuracy);

	//debugFunction_printCurvatureInConsolWindow(lengthsWithCurvatures);
	debugFunction_printVectorOfPointsInConsolWindow(bspline);
}

// PRIVATE FUNCTIONS
std::vector<double> OpenInfraPlatform::UserInterface::SplineInterpretation::obtainKnotArrayOpenUniform(const size_t nPoints, const int order) const throw(...)
{
	std::vector<double> knotArray;
	// .resize sets all vector values to 0
	knotArray.resize(nPoints + order);

	// set values from vector position order+1 to nPoints (positon according to mathematical one-based vector)
	for (size_t i = order; i < nPoints; i++)
		knotArray[i] = (i + 1) - order;

	// set values form vector positon nPoints+1 to end (positon according to mathematical one-based vector)
	for (size_t i = nPoints; i < nPoints + order; i++)
		knotArray[i] = nPoints - order + 1;

	return knotArray;
}

void OpenInfraPlatform::UserInterface::SplineInterpretation::debugFunction_printCurvatureInConsolWindow(
	const std::vector<std::pair<double, double>>& lengthsWithCurvatures) const throw(...)
{
	using std::cout;
	using std::endl;

	cout << endl;
	cout << "Length with curvature of the B-Spline:" << endl << "[";
	for (size_t i = 0; i < lengthsWithCurvatures.size() - 1; i++)
		cout << lengthsWithCurvatures[i].first << ", " << lengthsWithCurvatures[i].second << ";" << endl;

	cout << lengthsWithCurvatures.back().first << ", " << lengthsWithCurvatures.back().second << "];";
}

void OpenInfraPlatform::UserInterface::SplineInterpretation::debugFunction_printVectorOfPointsInConsolWindow(
	const std::vector<carve::geom::vector<3>>& points) const throw(...)
{
	using std::cout;
	using std::endl;

	cout << endl;
	cout << "Coordinates of the vector:" << endl << "[";
	for (size_t i = 0; i < points.size() - 1; i++)
		cout << points[i].x << ", " << points[i].y << ", " << points[i].z << ";" << endl;

	cout << points.back().x << ", " << points.back().y << ", " << points.back().z << "];";
}