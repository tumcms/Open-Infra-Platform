/*
    Copyright (c) 2020 Technical University of Munich
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

#include <string>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <namespace.h>

#include <IfcGeometryModelRenderer.h>

#include <buw.Engine.h>
#include <buw.ImageProcessing.h>

#include <boost/dll/runtime_symbol_info.hpp>

using namespace testing;

class VisualTest : public Test
{
protected:

    buw::ReferenceCounted<buw::IRenderSystem> renderSystem_ = nullptr;
    buw::ReferenceCounted<IfcGeometryModelRenderer> renderer = nullptr;

    VisualTest();

    virtual ~VisualTest();

    virtual void SetUp() override;

    virtual void TearDown() override;

public:
	virtual buw::Image4b CaptureImage();

	virtual std::string TestName() const = 0; // provide the test name as specified in the solution and the folder structure
	virtual std::string Schema() const = 0; // provide the schema as specified in the solution and the folder structure

	boost::filesystem::path executablePath() const;

	virtual boost::filesystem::path filePath(const std::string& relPath) const;

	boost::filesystem::path dataPath(const std::string& relPath) const;

	boost::filesystem::path testPath(const std::string& relPath) const;


};
