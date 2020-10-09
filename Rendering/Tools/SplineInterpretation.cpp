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
using OpenInfraPlatform::UserInterface::SplineInterpretationElement;

#include <fstream>
#include <sstream>
#include <stdio.h>
#include <QFileDialog>
#include <QMessageBox>

#include <QPushButton>
#include <math.h>

#include <algorithm>

#include "IfcGeometryConverter/SplineUtilities.h"

// CONSTRUCTOR
OpenInfraPlatform::UserInterface::SplineInterpretation::SplineInterpretation()
{}

// PUBLIC FUNCTIONS
void OpenInfraPlatform::UserInterface::SplineInterpretation::convertSketchToAlignment() const throw(...)
{
	// obtain control points from sketch or from file
	// (from file is from past sketch or from [external] test data)
	const std::vector<carve::geom::vector<3>> controlPoints = obtainControlPoints();
	// ToDo: exception handling if controlPoints is an empty vector, the functions has to be cancelled

	// DEBUG
	//std::cout << "Control points:" << std::endl;
	//debugFunction_printVectorOfPointsInConsolWindow(controlPoints);

	// Prepair properties for approximation
	const int nControlPoints = controlPoints.size();
	const int nCurvePoints = 10 * nControlPoints;
	const int order = ceil(static_cast<double>(nControlPoints) / 2.0);
	const std::vector<double> knotArray = obtainKnotArrayOpenUniform(nControlPoints, order);

	// Get instance of SplineUtilities
	Core::IfcGeometryConverter::SplineUtilities splineUtilities;
	// Calculate approximation with B-Splinecurve and its curvature
	const std::vector<carve::geom::vector<3>> bsplinePoints = splineUtilities.computeBSplineCurveWithKnots(order, knotArray, controlPoints, nCurvePoints, accuracy);
	std::vector<std::pair<double, double>> lengthsWithCurvatures = splineUtilities.computeCurvatureOfBSplineCurveWithKnots(order, controlPoints, knotArray, nCurvePoints);

	// correction of first and last curvature value
	lengthsWithCurvatures[0].second = lengthsWithCurvatures[1].second;
	lengthsWithCurvatures[nCurvePoints - 1].second = lengthsWithCurvatures[nCurvePoints - 2].second;

	// DEBUG
	//std::cout << "B-Spline-Curvepoints of approximation" << std::endl;
	//debugFunction_printVectorOfPointsInConsolWindow(bsplinePoints);

	// DEBUG
	//std::cout << "Curvature before smoothing:" << std::endl;
	//debugFunction_printCurvatureInConsolWindow(lengthsWithCurvatures);

	// smooth curvature
	lengthsWithCurvatures = movingAverageVariableWindow(lengthsWithCurvatures);

	// DEBUG
	//std::cout << "Curvature after smoothing:" << std::endl;
	//debugFunction_printCurvatureInConsolWindow(lengthsWithCurvatures);

	// calculate change of curvature as derivative
	std::vector<double> curvatureChange = numericDerivative(lengthsWithCurvatures);

	// DEBUG
	//std::cout << "Change of curvature before smoothing" << std::endl;
	//debugFunction_printCurvatureChangeInConsolWindow(curvatureChange);

	// smooth change of curvature
	curvatureChange = movingAverageVariableWindow(curvatureChange);

	// DEBUG
	//std::cout << "Change of curvature after smoothing" << std::endl;
	//debugFunction_printCurvatureChangeInConsolWindow(curvatureChange);

	// Get vector with element endpoints
	std::vector<SplineInterpretationElement> elements = identifyElementEndpoints(lengthsWithCurvatures, curvatureChange);
	
	// Set information in element vector
	elements = identifyElementTypes(bsplinePoints, lengthsWithCurvatures, elements);

	printElementsInConsoleWindow(elements);
}

// PRIVATE FUNCTIONS
std::vector<carve::geom::vector<3>> OpenInfraPlatform::UserInterface::SplineInterpretation::obtainControlPoints() const throw(...)
{
	// initialice MessageBox
	QMessageBox msgBox;
	msgBox.setText("Do you want to get control points from sketch or load from file?");
	msgBox.setInformativeText("(Note: Sketch isn't implemented.\nThere is a rerouting to load from file)");

	// set buttons of MessageBox
	QAbstractButton* pButtonSketch = msgBox.addButton("Sketch", QMessageBox::YesRole);
	msgBox.addButton("Load", QMessageBox::NoRole);

	// disable close button of MessageBox
	msgBox.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	// execute MessageBox; choice will be saved in msgBox
	msgBox.exec();

	// declare target variable
	std::vector<carve::geom::vector<3>> controlPoints;
	if (msgBox.clickedButton() == pButtonSketch) 
	{
		//ToDo: Implement sketch input
		//controlPoints = ...

		// Save the Input in file
		//saveControlPointsIntoFile(controlPoints);
	}
	//else // button 'load' has been pressed
	{
		controlPoints = loadControlPointsFromFile();
	}
	
	return controlPoints;
}

void OpenInfraPlatform::UserInterface::SplineInterpretation::saveControlPointsIntoFile(const std::vector<carve::geom::vector<3>>& points) const throw(...)
{
	// get number of files, which are in the default folder of sketches
	const QString path = "testdata/StrokeToAlignment/";
	QDir dir(path);
	dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
	const int numberOfFiles = dir.count();

	// set file name (with path) of the new file:
	//   the part
	//   std::setw(3) << std::setfill('0') << (numberOfFiles + 1)
	//   converts the number of files into a string with 3 digits, this must be done in a std::stringstream
	std::stringstream ssFilename;
	ssFilename << path.toStdString() << std::setw(3) << std::setfill('0') << (numberOfFiles + 1) << ".sketch";

	// initialise the file stream to write
	std::ofstream file(ssFilename.str());
	
	// check whether file generation was successfull
	if (file.is_open())
	{
		// write first two lines
		file << points.size() << " = Number of vertices; the following lines can be pasted into MATLAB:\n" 
			 << "[\n";

		// for each point add line with coordinates
		for (size_t i = 0; i < points.size(); i++)
		{
			file << points[i].x << " " << points[i].y << " " << points[i].z;

			// set end of line, depends on the last element of 'points'
			if (i == points.size() - 1)
				// last line (all points are stored)
				file << " ];";
			else
				// add new line
				file << " ;\n";
		}

		file.close();
	}
	else
	{
		QMessageBox::information(nullptr, "Convert Stroke to Alignment", 
			"The save process failed. Maybe the directory [build folde]/testdata/StrokeToAlignment/ doesn't exist or is protected.\n"
			"If you are a developer, build the project 'Copy/CopyOpenInfraPlatformUIResources' in Visual Studio", QMessageBox::Ok);
	}
}

std::vector<carve::geom::vector<3>> OpenInfraPlatform::UserInterface::SplineInterpretation::loadControlPointsFromFile() const throw(...)
{
	// from a file open dialog, get file name (including path) which should be opened
	const std::string fileName = QFileDialog::getOpenFileName(nullptr, // parent Widget
		"Open Set Of Sketch Points", // caption / titel
		"testdata/StrokeToAlignment/", // directory
		"Sketch Points (*.sketch)" // filter of file type
		).toStdString(); // convert QString (from getOpenFileName) to std::string

	// initialize a reading file stream with the file name
	std::ifstream file(fileName);

	// declare target vector
	std::vector<carve::geom::vector<3>> points;

	// check whether file opening was successfull;
	//   if it was NOT, nothing happens and an emptiy std::vector is the return value
	if (file.is_open())
	{
		// ToDo: exception handling if parsing fails (e.g. because invalid information inside the file)

		// get first line into a stringstream
		std::string lineString;
		std::getline(file, lineString);
		std::stringstream line(lineString);

		// number of Points is first element in first line
		size_t numPoints;
		line >> numPoints;
		// prepare memory in target vector
		points.reserve(numPoints);

		// skip second line
		std::getline(file, lineString);

		// declare temporary  variables
		std::string dStr;
		double x, y, z;
		// read all lines with points
		while (getline(file, lineString))
		{
			std::stringstream line(lineString);

			// obtain x, y and z from line
			line >> dStr;
			x = std::stof(dStr, nullptr);

			line >> dStr;
			y = std::stof(dStr, nullptr);

			line >> dStr;
			z = std::stof(dStr, nullptr);

			points.push_back(carve::geom::VECTOR(x, y, z));
		}

		file.close();
	}

	return points;
}

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

std::vector<std::pair<double, double>> OpenInfraPlatform::UserInterface::SplineInterpretation::movingAverageVariableWindow(std::vector<std::pair<double, double>>& xy) const throw(...)
{
	std::vector<double> data = obtainCurvatureFrom_lengthWithCurvatures(xy);

	// call main function of moving average
	data = movingAverageVariableWindow(data);

	// save temporary values in target variable
	for (size_t i = 0; i < xy.size(); i++)
		xy[i].second = data[i];

	return xy;
}

std::vector<double> OpenInfraPlatform::UserInterface::SplineInterpretation::movingAverageVariableWindow(std::vector<double>& data) const throw(...)
{
	// window size
	const size_t range = variogrammGetRange(data);
	// window size per side
	const int K = ceil(range / 2.0);
	// number of elements in data
	const size_t n = data.size();

	// initialice temporary vector of smoothed values 
	std::vector<double> value(n, 0.0);

	// initialice start & end index of the moving window
	int jStart;
	int jEnd;

	// go over each pair element
	for (size_t i = 0; i < n; i++)
	{
		// set current window indices
		jStart = i - K;
		jEnd = i + K;
		// resize window near the vector begin
		if (jStart < 0){
			jStart = 0;
			jEnd = i + (i - jStart);
		}
		// resize window near the vector end
		if (jEnd >= n){
			jEnd = n - 1;
			jStart = i - (n - i);
		}

		// add all values in the window
		for (int j = jStart; j <= jEnd; j++)
			value[i] += data[j];
		// make average by divide with size of window
		value[i] /= (jEnd - jStart + 1);
	}

	return value;
}

std::vector<double> OpenInfraPlatform::UserInterface::SplineInterpretation::obtainCurvatureFrom_lengthWithCurvatures(
	const std::vector<std::pair<double, double>>& lengthsWithCurvatures) const throw(...)
{
	// numer of elements
	const size_t n = lengthsWithCurvatures.size();

	// obtain second value of xy
	std::vector<double> curvature(n, 0.0);
	for (size_t i = 0; i < n; i++)
		curvature[i] = lengthsWithCurvatures[i].second;

	return curvature;
}

size_t OpenInfraPlatform::UserInterface::SplineInterpretation::variogrammGetRange(std::vector<double>& data) const throw(...)
{
	// initialice vector of semivariogramm variable gamma(h)
	std::vector<double> gamma(data.size() - 1, 0.0);

	// for each step size h
	for (size_t h = 1; h < data.size(); h++)
	{
		// number of step-pairs to current step
		size_t N = data.size() - h;
		// sum up all step-pairs
		for (size_t i = 0; i < N; i++)
			gamma[h - 1] += pow(data[i] - data[i + h], 2);
		// divide by pre-factor
		gamma[h - 1] /= (2 * N);
	}

	// initialice range with nonsense value
	size_t range = -1;
	size_t rangeMax = std::min((size_t)100, gamma.size() - 1);

	for (size_t h = 0; h < rangeMax; h++)
	{
		if (gamma[h] >= gamma[h + 1])
		{
			// if maximum turning point found, set range and break loop
			range = h + 1;
			break;
		}
	}

	// if no range was set, it's (temporarlly) the max. step size
	if (range == -1)
		range = rangeMax;

	return range;
}

std::vector<double> OpenInfraPlatform::UserInterface::SplineInterpretation::numericDerivative(std::vector<std::pair<double, double>>& xy) const throw(...)
{
	// initialice target vector
	std::vector<double> dy;
	dy.resize(xy.size() - 1);

	// apply numeric derivative for each space in xy
	for (size_t i = 0; i < dy.size(); i++)
		dy[i] = (xy[i + 1].second - xy[i].second) / (xy[i + 1].first - xy[i].first);

	return dy;
}

std::vector<SplineInterpretationElement> OpenInfraPlatform::UserInterface::SplineInterpretation::identifyElementEndpoints(
	std::vector<std::pair<double, double>> lengthsWithCurvatures, 
	std::vector<double> curvatureChange) const throw(...)
{
	// indicate the change of curvature
	//   curvatureZero: threshold
	//   indicator: 0 for abs(curvatureChange) <= curvatureZero
	//              1 for abs(curvatureChange) >  curvatureZero
	std::vector<int> indicator;
	double curvatureZero;
	std::tie(indicator, curvatureZero) = indicateCurvatureChange(curvatureChange);

	// 'elements' holds information about element start-/end-point, length, and corresponding id in 'lengthWithCurvature'
	std::vector<SplineInterpretationElement> elements =
		obtainElementsFromIndicator(indicator, lengthsWithCurvatures);

	// indicator of short elements will be modified to obtain long elements
	elements = correctShortElements(elements, curvatureChange, curvatureZero);

	// consecutive elements with identical indicator will be merged
	elements = mergeShortElements(elements);

	return elements;
}

std::tuple<std::vector<int>, double> OpenInfraPlatform::UserInterface::SplineInterpretation::indicateCurvatureChange(
	std::vector<double> curvatureChange) const throw(...)
{
	// threshold of curvatureChange
	const double curvatureZero = obtainThreshold(curvatureChange);

	// check values of curvatureChange against threshold
	std::vector<int> indicator(curvatureChange.size(), 0);
	for (size_t i = 0; i < curvatureChange.size(); i++)
		if (std::abs(curvatureChange[i]) <= curvatureZero)
			indicator[i] = 0;
		else
			indicator[i] = 1;

	return { indicator, curvatureZero };
}

double OpenInfraPlatform::UserInterface::SplineInterpretation::obtainThreshold(
	const std::vector<std::pair<double, double>>& lengthsWithCurvatures) const throw(...)
{
	return obtainThreshold(obtainCurvatureFrom_lengthWithCurvatures(lengthsWithCurvatures));
}

double OpenInfraPlatform::UserInterface::SplineInterpretation::obtainThreshold(std::vector<double> data) const throw(...) {
	// allows +- 25 % around 0
	return std::max(
		0.25 * std::abs(*std::min_element(data.begin(), data.end())),
		0.25 * std::abs(*std::max_element(data.begin(), data.end())));
}

std::vector<SplineInterpretationElement> OpenInfraPlatform::UserInterface::SplineInterpretation::obtainElementsFromIndicator(
	std::vector<int> indicator,
	std::vector<std::pair<double, double>> lengthsWithCurvatures) const throw(...)
{
	// predetermine variables with first point
	// vector-id of each element start
	size_t idStart = 0;
	// type holds information of indicator at each element start
	int type = indicator[idStart];
	
	// initialize variables
	// vector-id of each element end
	size_t idEnd;
	// result vector
	std::vector<SplineInterpretationElement> elements;

	for (size_t i = 1; i < indicator.size(); i++)
		// if the type is changing
		if (indicator[i] != type)
		{
			idEnd = i;
			// add element to result vector
			elements.push_back(SplineInterpretationElement(
				lengthsWithCurvatures[idEnd].first - lengthsWithCurvatures[idStart].first, // length of element
				type, // type (=value of indicator) of element
				std::make_pair(idStart, idEnd))); // ids of element regarding the vector 'lengthWithCurvature'

			// set start conditions of next element
			idStart = i;
			type = indicator[idStart];
		}

	// close last element
	idEnd = lengthsWithCurvatures.size() - 1;
	elements.push_back(SplineInterpretationElement(
		lengthsWithCurvatures[idEnd].first - lengthsWithCurvatures[idStart].first,
		type,
		std::make_pair(idStart, idEnd)));

	return elements;
}

std::vector<SplineInterpretationElement> OpenInfraPlatform::UserInterface::SplineInterpretation::correctShortElements(
	std::vector<SplineInterpretationElement> elements, 
	std::vector<double> curvatureChange, 
	const double curvatureZero) const throw(...)
{
	// minimum length of an element
	const double minLength = 50;

	// id..Element regarding vector of elements
	size_t idFirstElement;
	size_t idLastElement;
	// id..Point regarding vector lengthWithCurvature
	size_t idFirstPoint;
	size_t idLastPoint;
	// indicator according to the average of curve points
	int newIndicator;

	const size_t n = elements.size();
	for (size_t i = 0; i < n; i++)
		// if element is to short ...
		if (elements[i].getLengthBSpline() < minLength)
		{
			// save number of first short element
			idFirstElement = i;
			for (size_t j = i; j < n; j++)
				// if element is long enough OR if end of elements vector
				if (elements[j].getLengthBSpline() >= minLength || j == n - 1)
				{
					if (j == n - 1)
						// end of vector: use current index as last short element
						idLastElement = j;
					else
						// index points to a long element: use previous as last short element
						idLastElement = j-1;

					if (idFirstElement == idLastElement)
						// only one singl element is short: invert indicator
						if (elements[idFirstElement].getIndicator() == 0)
							elements[idFirstElement].setindicator(1);
						else
							elements[idFirstElement].setindicator(0);
					else // multiple elements are short
					{
						// indices regarding vector lengthWithCurvature
						idFirstPoint = elements[idFirstElement].getIndicesStart();
						idLastPoint = elements[idLastElement].getIndicesEnd();
						// calculate average of the curvature change between the points of lengthWithCurvature
						newIndicator = std::abs(indicateDataByAverage(
							std::vector<double>(curvatureChange.begin() + idFirstPoint, curvatureChange.begin() + idLastPoint), 
							curvatureZero));
						// apply new indicator to all short elements
						for (size_t k = idFirstElement; k <= idLastElement; k++)
							elements[k].setindicator(newIndicator);
					}
					// i jumps over the short elements
					i = j;
					break;
				}
		}
	return elements;
}

//int OpenInfraPlatform::UserInterface::SplineInterpretation::indicateDataByAverage(
//	std::vector<std::pair<double, double>> lengthsWithCurvatures, double threshold) const throw(...)
//{
//	return indicateDataByAverage(obtainCurvatureFrom_lengthWithCurvatures(lengthsWithCurvatures), threshold);
//}

int OpenInfraPlatform::UserInterface::SplineInterpretation::indicateDataByAverage(std::vector<double> data, double threshold) const throw(...)
{
	// sum up all values (begin to end) of curvatureChange, divide by the number of values 
	double average = std::accumulate(data.begin(), data.end(), 0.0) / data.size();

	// obtain indicator
	if (average < -threshold)
		return -1;
	else if (average > threshold)
		return 1;
	else
		return 0;
}

std::vector<SplineInterpretationElement> OpenInfraPlatform::UserInterface::SplineInterpretation::mergeShortElements(
	std::vector<SplineInterpretationElement> elements) const throw(...)
{
	// run over elements vector from end to begin (because the vector becomes shorter)
	for (size_t i = elements.size() - 1; i > 0; i--)
		// if consecutive elements have the same indicator ...
		if (elements[i-1].getIndicator() == elements[i].getIndicator())
		{	
			// move needed information from elements[i] to [i-1] (to the previous one)
			elements[i - 1].setLengthBSpline(elements[i - 1].getLengthBSpline() + elements[i].getLengthBSpline());
			elements[i - 1].setIndicesEnd(elements[i].getIndicesEnd());

			// delete elements[i]
			elements.erase(elements.begin() + i);
		}

	return elements;
}

std::vector<SplineInterpretationElement> OpenInfraPlatform::UserInterface::SplineInterpretation::identifyElementTypes(
	const std::vector<carve::geom::vector<3>>& bsplinePoints,
	const std::vector<std::pair<double, double>>& lengthsWithCurvatures,
	std::vector<SplineInterpretationElement>& elements) const throw(...)
{
	// parameters over complete curve
	const double curvatureThreshold = obtainThreshold(lengthsWithCurvatures);
	const std::vector<double> curvature = obtainCurvatureFrom_lengthWithCurvatures(lengthsWithCurvatures);

	// parameters for each element
	int idStart;
	int idEnd;
	int curvatureIndicator;

	// number of elements
	const size_t n = elements.size();
	// loop over all elements
	for (size_t i = 0; i < n; i++)
		// if change of curvature is about 0 ...
		if (elements[i].getIndicator() == 0)
		{
			// IDs of element
			idStart = elements[i].getIndicesStart();
			idEnd = elements[i].getIndicesEnd();

			// curvature about 0, negative or positive
			curvatureIndicator = indicateDataByAverage(
				std::vector<double>(curvature.begin() + idStart, curvature.begin() + idEnd),
				curvatureThreshold);

			if (curvatureIndicator == 0)
			{
				// place a straight element
				elements[i] = obtainStraight(bsplinePoints[idStart], bsplinePoints[idEnd], elements[i]);
			}
			else
			{
				// get id of the middle
				int idMid = ceil((idStart + idEnd) / 2);

				// place a arc element
				elements[i] = obtainArc(bsplinePoints[idStart], bsplinePoints[idMid], bsplinePoints[idEnd], curvatureIndicator, elements[i]);
			}
		}

	// loop over all elements
	for (size_t i = 0; i < n; i++)
		// if change of curvature is not about 0 ...
		if (elements[i].getIndicator() == 1)
			// exclude special cases which aren't implemented
			if (i == 0 && elements[1].getType() == "straight" ||
				i == n - 1 && elements[i - 1].getType() == "straight")
				elements[i].setType("clothoid with radius at sketch start / end not implemented");
			else if (elements[i - 1].getType() == "arc" && elements[i + 1].getType() == "arc")
				elements[i].setType("clothoid of type reversible clothoid not implemented");
			else if (elements[i - 1].getType() == "straight" && elements[i + 1].getType() == "straight")
				elements[i].setType("clothoid of type straight-radius-straight (without arc) not implemented");
			else
			// calculate parameters of clothoid
			{
				// IDs of element
				idStart = elements[i].getIndicesStart();
				idEnd = elements[i].getIndicesEnd();

				// previous element
				SplineInterpretationElement previousElement;
				if (i == 0)
				{
					// virtual straight element at sketch start
					previousElement.setType("straight");
					// directional vector of straight
					carve::geom::vector<3> vector = bsplinePoints[idStart + 1] - bsplinePoints[idStart];
					// direction at sketch start
					previousElement.setDirection(copysign(
						angleOfVectors2D(carve::geom::VECTOR(1.0, 0.0, 0.0), vector), // value (magnitude)
						vector.y)); // sign
				}
				else
					previousElement = elements[i - 1];

				// next element
				SplineInterpretationElement nextElement;
				if (i == n - 1)
				{
					// virtual straight element at sketch end
					nextElement.setType("straight");
					// directional vector of straight
					carve::geom::vector<3> vector = bsplinePoints[idEnd] - bsplinePoints[idEnd - 1];
					// directon at sketch start
					nextElement.setDirection(copysign(
						angleOfVectors2D(carve::geom::VECTOR(1.0, 0.0, 0.0), vector), // value (magnitude)
						vector.y)); // sign
				}
				else
					nextElement = elements[i + 1];

				elements[i] = obtainClothoid(
					previousElement, nextElement, 
					bsplinePoints[idStart], bsplinePoints[idEnd],
					elements[i]);
			}

	return elements;
}

SplineInterpretationElement OpenInfraPlatform::UserInterface::SplineInterpretation::obtainStraight(
	const carve::geom::vector<3>& startPoint,
	const carve::geom::vector<3>& endPoint,
	SplineInterpretationElement& element) const throw(...)
{
	element.setType("straight");
	element.setStartpoint(startPoint);

	double dx = endPoint.x - startPoint.x;
	double dy = endPoint.y - startPoint.y;
	element.setDirection(copysign(
		angleOfVectors2D(carve::geom::VECTOR(1.0, 0.0, 0.0), carve::geom::VECTOR(dx, dy, 0.0)), // value (magnitude)
		dy)); // sign
	element.setLength(sqrt(pow(dx, 2) + pow(dy, 2)));

	return element;
}

SplineInterpretationElement OpenInfraPlatform::UserInterface::SplineInterpretation::obtainArc(
	const carve::geom::vector<3>& startPoint,
	const carve::geom::vector<3>& midPoint,
	const carve::geom::vector<3>& endPoint,
	const int curvatureIndicator,
	SplineInterpretationElement& element) const throw(...)
{
	element.setType("arc");
	element.setStartpoint(startPoint);

	// directional vectors between the arc points (startPoint, midPoint, endPoint)
	const carve::geom::vector<2> AB = carve::geom::VECTOR(midPoint.x - startPoint.x, midPoint.y - startPoint.y);
	const carve::geom::vector<2> BC = carve::geom::VECTOR(endPoint.x - midPoint.x, endPoint.y - midPoint.y);

	// coordinates of the mid points between the arc points
	const carve::geom::vector<2> P1 = carve::geom::VECTOR(startPoint.x, startPoint.y) + 0.5 * AB;
	const carve::geom::vector<2> P2 = carve::geom::VECTOR(midPoint.x, midPoint.y) + 0.5 * BC;

	// directional vectors of linear equation
	const carve::geom::vector<2> v = carve::geom::VECTOR(AB.y, -AB.x);
	const carve::geom::vector<2> w = carve::geom::VECTOR(BC.y, -BC.x);

	// parameter of linear equations
	const double n2 = (v.x*(P2.y - P1.y) - v.y*(P2.x - P1.x)) / (w.x*v.y - w.y*v.x);

	element.setCenter(carve::geom::VECTOR(P2.x + n2 * w.x, P2.y + n2 * w.y, 0.0));
	element.setRadius(sqrt(pow(startPoint.x-element.getCenter().x,2) + pow(startPoint.y - element.getCenter().y, 2)));

	if (curvatureIndicator == 1)
		element.setIsCCW(1); // left curve / turn
	else
		element.setIsCCW(0); // right curve / turn

	// tangential direction at element start
	element.setDirection(tangentDirection(element.getCenter(), element.getStartpoint(), element.getIsCCW()));
	
	// angle in degree of the arc in two steps, this makes angles 180° to 359.9° possible as well
	double arcAngle = abs(
		angleOfVectors2D(startPoint - element.getCenter(), midPoint - element.getCenter())
		+ angleOfVectors2D(midPoint - element.getCenter(), endPoint - element.getCenter()));
	// convert angle to radian, calculate curve length of arc
	element.setLength(element.getRadius() * arcAngle * M_PI / 180);

	return element;
}

SplineInterpretationElement OpenInfraPlatform::UserInterface::SplineInterpretation::obtainClothoid(
	const SplineInterpretationElement previousElement,
	const SplineInterpretationElement nextElement,
	const carve::geom::vector<3>& startPoint,
	const carve::geom::vector<3>& endPoint,
	SplineInterpretationElement& element) const throw(...) 
{
	element.setType("clothoid");
	element.setStartpoint(startPoint);

	// radius of clothoid (for calculation)
	double radius;

	// tangential vector at element start
	carve::geom::vector<3> tangentStart;
	if (previousElement.getType() == "straight")
	{
		tangentStart = tangentVectorFromDirection(previousElement.getDirection());
		element.setDirection(previousElement.getDirection());
		element.setRadiusClothoidStart(NAN);
	}
	else // it's "arc"
	{
		tangentStart = tangentVector(previousElement.getCenter(), startPoint, previousElement.getIsCCW());
		element.setDirection(copysign(
			angleOfVectors2D(carve::geom::VECTOR(1.0, 0.0, 0.0), tangentStart), // value (magnitude)
			tangentStart.y)); // sign
		element.setRadiusClothoidStart(previousElement.getRadius());
		radius = previousElement.getRadius();
		element.setIsCCW(previousElement.getIsCCW());
	}

	// tangential vector at element end
	carve::geom::vector<3> tangentEnd;
	if (nextElement.getType() == "straight")
	{
		tangentEnd = tangentVectorFromDirection(nextElement.getDirection());
		element.setRadiusClothoidEnd(NAN);
	}
	else // it's "arc"
	{
		tangentEnd = tangentVectorFromDirection(nextElement.getDirection());
		element.setRadiusClothoidEnd(nextElement.getRadius());
		radius = nextElement.getRadius();
		element.setIsCCW(nextElement.getIsCCW());
	}

	// change of direction, angle in degree
	const double tau = angleOfVectors2D(tangentStart, tangentEnd);

	// element curve length
	element.setLength(2 * radius*(tau*M_PI / 180));

	// clothoid parameter A
	element.setClothoidparameterA(sqrt(radius * element.getLength()));

	return element;
}

double OpenInfraPlatform::UserInterface::SplineInterpretation::angleOfVectors2D(
	const carve::geom::vector<3>& a, 
	const carve::geom::vector<3>& b) const throw(...)
{
	// angle in degree
	return acos((a.x*b.x + a.y*b.y)
		/ (sqrt(pow(a.x, 2) + pow(a.y, 2))*sqrt(pow(b.x, 2) + pow(b.y, 2)))) * 180 / M_PI;
}

double OpenInfraPlatform::UserInterface::SplineInterpretation::tangentDirection(
	const carve::geom::vector<3>& centerPoint, 
	const carve::geom::vector<3>& tangentPoint, 
	const int isCCW) const throw(...)
{
	return angleOfVectors2D(
		carve::geom::VECTOR(1.0, 0.0, 0.0),
		tangentVector(centerPoint, tangentPoint, isCCW));
}

carve::geom::vector<3>  OpenInfraPlatform::UserInterface::SplineInterpretation::tangentVector(
	const carve::geom::vector<3>& centerPoint, 
	const carve::geom::vector<3>& tangentPoint, 
	const int isCCW) const throw(...)
{
	// vector from center to tangent point
	const carve::geom::vector<3> radialVector = tangentPoint - centerPoint;

	if (isCCW == 1)
		return carve::geom::VECTOR(-radialVector.y, radialVector.x, 0.0);
	else
		return carve::geom::VECTOR(radialVector.y, -radialVector.x, 0.0);
}

carve::geom::vector<3> OpenInfraPlatform::UserInterface::SplineInterpretation::tangentVectorFromDirection(
	double direction) const throw(...)
{
	return carve::geom::VECTOR(cos(direction*M_PI / 180), sin(direction*M_PI / 180), 0.0);
}

void OpenInfraPlatform::UserInterface::SplineInterpretation::printElementsInConsoleWindow(const std::vector<SplineInterpretationElement>& elements) const
{
	using std::cout;
	using std::endl;

	cout << endl;

	for (size_t i = 0; i < elements.size(); i++)
	{
		SplineInterpretationElement element = elements[i];

		std::string elementType = element.getType();

		cout << endl;
		printf("Element %i: %s\n", i + 1, elementType.c_str());

		if (elementType == "straight" || elementType == "arc" || elementType == "clothoid")
		{
			printf("   Start Point: x = %.3f; y = %.3f\n", element.getStartpoint().x, element.getStartpoint().y);
			printf("   Direction = %.3f      Length = %.3f\n", element.getDirection(), element.getLength());
		}

		if (elementType == "arc")
		{
			printf("   Radius = %.3f      isCCW = %i\n", element.getRadius(), element.getIsCCW());
			printf("   Center: x = %.3f; y = %.3f\n", element.getCenter().x, element.getCenter().y);
		}

		if (elementType == "clothoid")
		{
			printf("   Clothoid Parameter A = %.3f\n", element.getClothoidparameterA());
			printf("   Radius Start = %.3f      Radius End = %.3f\n", element.getRadiusClothoidStart(), element.getRadiusClothoidEnd());
			printf("   isCCW = %i\n", element.getIsCCW());
		}
	}

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

void OpenInfraPlatform::UserInterface::SplineInterpretation::debugFunction_printCurvatureChangeInConsolWindow(
	const std::vector<double> curvatureChange) const throw(...)
{
	using std::cout;
	using std::endl;

	cout << endl << "[";
	for (size_t i = 0; i < curvatureChange.size() - 1; i++)
		cout << curvatureChange[i] << ";" << endl;

	cout << curvatureChange.back() << "];";
}