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

#pragma once

#include <BlueFramework/ImageProcessing/color.h>
#include <BlueFramework/Core/Math/vector.h>

class ViewCubeData {
public:
	ViewCubeData();

	void setViewCubeFilename(const std::string filename);
	std::string getViewCubeFilename();

    void setTexturedViewCubeFilename(const std::string filename);
    std::string getTexturedViewCubeFilename();

	void setFaceColor(const buw::Color3f &color);
	buw::Color3f getFaceColor();

	void setSelectedColor(const buw::Color3f &color);
	buw::Color3f getSelectedColor();

	void setBoundColor(const buw::Color3f &color);
	buw::Color3f getBoundColor();

    void setTextColor(const buw::Color3f &color);
    buw::Color3f getTextColor();

	void setBoundHeight(const double value);
	double getBoundHeight() const;

	void setOuterBoundWidth(const double value);
	double getOuterBoundWidth() const;

	void setInnerBoundWidth(const double value);
	double getInnerBoundWidth() const;

    void setSize(const double value);
    double getSize() const;

	buw::Vector3d getBindings();

private:
	buw::Color3f faceColor_ = buw::Color3f(0x66/255.0f, 0x66 / 255.0f, 0x66 / 255.0f);
	buw::Color3f selectedColor_ = buw::Color3f(0x48 / 255.0f, 0xb7 / 255.0f, 0xe7 / 255.0f);
	buw::Color3f boundColor_ = buw::Color3f(0x47 / 255.0f, 0x47 / 255.0f, 0x47 / 255.0f);
    buw::Color3f textColor_ = buw::Color3f(1.0f, 1.0f, 1.0f);
	double innerBoundWidth_ = 0.0115;
	double outerBoundWidth_ = 0.0155;
	double boundHeight_ = 0.23;
    double size_ = 1.0;
	std::string viewCubeFilename_ = "Data/ViewCube.json";
    std::string texturedViewCubeFilename_ = "";
};