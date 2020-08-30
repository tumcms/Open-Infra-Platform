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

#include "IfcGeometryConverter/SplineUtilities.h"

// CONSTRUCTOR
OpenInfraPlatform::UserInterface::SplineInterpretation::SplineInterpretation()
{}

// PUBLIC FUNCTIONS
void OpenInfraPlatform::UserInterface::SplineInterpretation::convertSketchToAlignment() const throw(...)
{
	// obtain control points from sketch or from file
	// (from file is from past sketch or from [external] test data)
	// ToDo:
	// std::vector<carve::geom::vector<3>> controlPoints = ...

	// TEMPORARY constant test data
	std::vector<carve::geom::vector<3>> controlPointsToSave;
	controlPointsToSave.push_back(carve::geom::VECTOR(0., 2., 0));
	controlPointsToSave.push_back(carve::geom::VECTOR(1., 5., 0.));
	controlPointsToSave.push_back(carve::geom::VECTOR(3., 4., 0.));
	controlPointsToSave.push_back(carve::geom::VECTOR(3., 1., 0.));
	controlPointsToSave.push_back(carve::geom::VECTOR(5., 0., 0.));
	controlPointsToSave.push_back(carve::geom::VECTOR(7., 1., 0.));
	controlPointsToSave.push_back(carve::geom::VECTOR(8., 4., 0.));
	controlPointsToSave.push_back(carve::geom::VECTOR(10., 4., 0.));

	// TEMPORARY call of saveControlPointsIntoFile and loadControlPointsFromFile
	saveControlPointsIntoFile(controlPointsToSave);
	const std::vector<carve::geom::vector<3>> controlPoints = loadControlPointsFromFile();
	// ToDo: exception handling if controlPoints is an empty vector, the functions has to be cancelled

	// Prepair properties
	const int order = 4;
	const std::vector<double> knotArray = obtainKnotArrayOpenUniform(controlPointsToSave.size(), order);

	// Compute curvature
	Core::IfcGeometryConverter::SplineUtilities splineUtilities;
	std::vector<std::pair<double, double>> lengthsWithCurvatures = splineUtilities.computeCurvatureOfBSplineCurveWithKnots(order, controlPoints, knotArray);

	// Test B-Spline
	std::vector<carve::geom::vector<3>> bspline = splineUtilities.computeBSplineCurveWithKnots(order, knotArray, controlPoints, 10*knotArray.size(), accuracy);

	//debugFunction_printCurvatureInConsolWindow(lengthsWithCurvatures);
	debugFunction_printVectorOfPointsInConsolWindow(bspline);
}

// PRIVATE FUNCTIONS
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