/*
	Copyright (c) 2021 Technical University of Munich
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
//#include <namespace.h>

#include <VisualTest.h>
#include <PointCloudGeometryModelRenderer.h>

using namespace testing;

class PointCloudVisualTest : public VisualTest
{
protected:
	buw::ReferenceCounted<OffGeometryModelRenderer> rendererOff = nullptr;

	virtual void SetUp() override;

	virtual void TearDown() override;

public:
	virtual buw::Image4b CaptureImage() override;

	virtual std::string TestName() const = 0;

	virtual boost::filesystem::path filePath(const std::string& relPath) const override;
};