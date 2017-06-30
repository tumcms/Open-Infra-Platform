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

#include "ViewCubeData.h"
#include "OpenInfraPlatform/DataManagement/Data.h"

ViewCubeData::ViewCubeData() {};

void ViewCubeData::setViewCubeFilename(const std::string filename) {
	viewCubeFilename_ = filename;

    OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().Change();
}
std::string ViewCubeData::getViewCubeFilename() {
	return viewCubeFilename_;
}

void ViewCubeData::setTexturedViewCubeFilename(const std::string filename)
{
    texturedViewCubeFilename_ = filename;

    OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().Change();
}

std::string ViewCubeData::getTexturedViewCubeFilename()
{
    return texturedViewCubeFilename_;
}

void ViewCubeData::setFaceColor(const buw::Color3f &color) {
	faceColor_ = color;

    OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().Change();
}

void ViewCubeData::setSelectedColor(const buw::Color3f &color) {
	selectedColor_ = color;

    OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().Change();
}

void ViewCubeData::setBoundColor(const buw::Color3f &color) {
	boundColor_ = color;

    OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().Change();
}

void ViewCubeData::setTextColor(const buw::Color3f &color) {
    textColor_ = color;

    OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().Change();
}

void ViewCubeData::setBoundHeight(const double value) {
	boundHeight_ = value;

    OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().Change();
}

void ViewCubeData::setOuterBoundWidth(const double value) {
	outerBoundWidth_ = value;

    OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().Change();
}

void ViewCubeData::setInnerBoundWidth(const double value) {
	innerBoundWidth_ = value;

    OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().Change();
}

buw::Color3f ViewCubeData::getFaceColor() {
	return faceColor_;
}

buw::Color3f ViewCubeData::getSelectedColor() {
	return selectedColor_;
}

buw::Color3f ViewCubeData::getBoundColor() {
	return boundColor_;
}

buw::Color3f ViewCubeData::getTextColor() {
    return textColor_;
}

double ViewCubeData::getBoundHeight() const {
	return (const double) boundHeight_;
}

double ViewCubeData::getOuterBoundWidth() const {
	return (const double)outerBoundWidth_;
}

double ViewCubeData::getInnerBoundWidth() const {
	return (const double) innerBoundWidth_;
}

void ViewCubeData::setSize(const double value)
{
    size_ = value;

    OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().Change();
}

double ViewCubeData::getSize() const
{
    return (const double) size_;
}

buw::Vector3d ViewCubeData::getBindings() {
	double epsilon = 0.00001;

	buw::Vector3d bindings;
	double innerBoundWidth_x = getInnerBoundWidth();
	double outerBoundWidth_z = getOuterBoundWidth();
	double boundHeight_y = getBoundHeight();

	double cornerFaceHeight = outerBoundWidth_z + boundHeight_y + innerBoundWidth_x;
	double centerFaceHeight = 1.0 - 2.0*cornerFaceHeight;
	double totalHeight = 2.0 * cornerFaceHeight + centerFaceHeight;
	
	while (totalHeight < 1.0 - epsilon || totalHeight > 1.0 + epsilon) {
		double rest = 1.0 - totalHeight;
		centerFaceHeight += centerFaceHeight * rest;
		cornerFaceHeight += cornerFaceHeight * rest;
		totalHeight = 2.0 * cornerFaceHeight + centerFaceHeight;
	}

	boundHeight_y = cornerFaceHeight - innerBoundWidth_x - outerBoundWidth_z;
	bindings = buw::Vector3d(outerBoundWidth_z, boundHeight_y, innerBoundWidth_x);
	return bindings;
}