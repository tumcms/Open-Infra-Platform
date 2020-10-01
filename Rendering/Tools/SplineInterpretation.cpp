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

#include <fstream>
#include <sstream>
#include <QFileDialog>
#include <QMessageBox>

#include <QPushButton>
#include <math.h>

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

	// Prepair properties for first approximation
	int nCurvePoints = controlPoints.size();
	const int nControlPoints = controlPoints.size();
	const int order = ceil(static_cast<double>(nControlPoints) / 2.0);
	const std::vector<double> knotArray = obtainKnotArrayOpenUniform(nControlPoints, order);

	// Get instance of SplineUtilities
	Core::IfcGeometryConverter::SplineUtilities splineUtilities;
	// Calculate first approximation with B-Splinecurve
	const std::vector<carve::geom::vector<3>> bsplinePoints = splineUtilities.computeBSplineCurveWithKnots(order, knotArray, controlPoints, nCurvePoints, accuracy);

	// Set properties for second approximation and compute curvature
	// (nControlPoints, order, and knoteArray are const, because nCurvePoints in first approximation were equal nControlPoints)
	nCurvePoints = 10 * controlPoints.size();
	std::vector<std::pair<double, double>> lengthsWithCurvatures = splineUtilities.computeCurvatureOfBSplineCurveWithKnots(order, controlPoints, knotArray, nCurvePoints);

	// smooth curvature
	lengthsWithCurvatures = movingAverageVariableWindow(lengthsWithCurvatures);

	debugFunction_printCurvatureInConsolWindow(lengthsWithCurvatures);
	//debugFunction_printVectorOfPointsInConsolWindow(bsplinePoints);
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

std::vector<std::pair<double, double>> OpenInfraPlatform::UserInterface::SplineInterpretation::movingAverageVariableWindow(std::vector<std::pair<double, double>> xy) const throw(...)
{
	// window size
	const size_t range = variogrammGetRange(xy);
	// window size per side
	const int K = ceil(range / 2.0);
	// number of elements in xy
	const size_t n = xy.size();

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
			value[i] += xy[i].second;
		// make average by divide with size of window
		value[i] /= (jEnd - jStart + 1);
	}

	// save temporary values in target variable
	for (size_t i = 0; i < n; i++)
		xy[i].second = value[i];

	return xy;
}

size_t OpenInfraPlatform::UserInterface::SplineInterpretation::variogrammGetRange(std::vector<std::pair<double, double>> xy) const throw(...)
{
	// initialice vector of semivariogramm variable gamma(h)
	std::vector<double> gamma(xy.size() - 1, 0.0);

	// for each step size h
	for (size_t h = 1; h < xy.size(); h++)
	{
		// number of step-pairs to current step
		size_t N = xy.size() - h;
		// sum up all step-pairs
		for (size_t i = 0; i < N; i++)
			gamma[h - 1] += pow(xy[i].second - xy[i + h].second, 2);
		// divide by pre-factor
		gamma[h - 1] /= (2 * N);
	}

	// initialice range with nonsense value
	size_t range = -1;

	for (size_t h = 0; h < gamma.size() - 1; h++)
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
		range = gamma.size();

	return range;
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