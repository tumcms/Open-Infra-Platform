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

#include "PointCloudProcessing.h"
#include <liblas/liblas.hpp>
#include <BlueFramework/Core/Diagnostics/log.h>

#include <FileIOFilter.h>
#include <ccPointCloud.h>
#include <ccHObjectCaster.h>


BLUEINFRASTRUCTURE_API void OpenInfraPlatform::Infrastructure::importLASPointCloud(
	const char* filename,
	buw::PointCloud& pointCloud)
{
	// see http://www.liblas.org/tutorial/cpp.html
	std::ifstream ifs;

	ifs.open(filename, std::ios::in | std::ios::binary);

	liblas::ReaderFactory f;
	liblas::Reader reader = f.CreateWithStream(ifs);

	liblas::Header const& header = reader.GetHeader();

	BLUE_LOG(info) << "Compressed: " << ((header.Compressed() == true) ? "true" : "false");
	BLUE_LOG(info) << "Signature: " << header.GetFileSignature();
	BLUE_LOG(info) << "Points count: " << header.GetPointRecordsCount();

	buw::Vector3d minv(0, 0, 0);
	buw::Vector3d maxv(0, 0, 0);

	pointCloud.points.resize(header.GetPointRecordsCount());

	bool first = true;
	for(int i = 0; i < header.GetPointRecordsCount(); i++) {
		if(reader.ReadNextPoint())
		{
			liblas::Point const& p = reader.GetPoint();

			float colorRange = std::numeric_limits<liblas::Color::value_type>::max();
			auto pos = buw::Vector3d(p.GetX(), p.GetY(), p.GetZ());

			pointCloud.points[i] = {
				pos,
				buw::Vector3f(p.GetColor().GetRed() / colorRange, p.GetColor().GetGreen() / colorRange, p.GetColor().GetBlue() / colorRange) };
			
				if(first) {
					minv = maxv = pos;
					first = false;
				}
				else {
					minv = buw::minimizedVector(minv, pos);
					maxv = buw::maximizedVector(maxv, pos);
				}
			
		}		
	}

	pointCloud.minPos = minv;
	pointCloud.maxPos = maxv;
}

BLUEINFRASTRUCTURE_API void OpenInfraPlatform::Infrastructure::importCCPointCloud(const char * filename, PointCloud & pointCloud)
{
	//Initialize the filters for file IO
	if(FileIOFilter::GetFilters().size() == 0)
		FileIOFilter::InitInternalFilters();
	
	ColorCompType color = ColorCompType();
	CC_FILE_ERROR err;
	std::shared_ptr<ccHObject> ccTempObject = std::shared_ptr<ccHObject>(FileIOFilter::LoadFromFile(QString(filename), FileIOFilter::LoadParameters(), FileIOFilter::FindBestFilterForExtension("BIN"), err));
	
	buw::Vector3d minv(0, 0, 0);
	buw::Vector3d maxv(0, 0, 0);
	bool first = true;

	auto parsePoint = [&](const CCVector3* point) {
		buw::LaserPoint lasPoint;
		buw::Vector3d pos = { (double)point->x, (double)point->y, (double)point->z };
		lasPoint.position = pos;
		lasPoint.color = { 255.f, 255.f, 255.f };

		if(first) {
			minv = maxv = pos;
			first = false;
		}
		else {
			minv = buw::minimizedVector(minv, pos);
			maxv = buw::maximizedVector(maxv, pos);
		}

		pointCloud.points.push_back(lasPoint);
	};


	for(size_t i = 0; i < ccTempObject->getChildrenNumber(); i++) {
		ccPointCloud* ccTempCloud = ccHObjectCaster::ToPointCloud(ccTempObject->getChild(i));

		if(ccTempCloud) {
			for(size_t idx = 0; idx < ccTempCloud->size(); idx++) {
				parsePoint(ccTempCloud->getPoint(idx));
			}
		}
	}
	ccTempObject = nullptr;

	pointCloud.minPos = minv;
	pointCloud.maxPos = maxv;

	Eigen::MatrixX3d points;
	points.resize(pointCloud.points.size(), 3);

	for(size_t i = 0; i < pointCloud.points.size(); i++) {
		points.row(i) = pointCloud.points[i].position;
	}

	//Do PCA to find the largest eigenvector -> main axis
	Eigen::MatrixXd centered = points.rowwise() - points.colwise().mean();
	Eigen::MatrixXd cov = centered.adjoint() * centered;
	Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
	Eigen::Matrix<double,3,3> vec = eig.eigenvectors().rightCols(3);

	buw::Vector3d eigenX = vec.col(2);
	buw::Vector3d eigenY = vec.col(0);
	buw::Vector3d eigenZ = vec.col(1);

	auto pitch = buw::calculateAngleBetweenVectors(buw::Vector3d(1, 0, 0), buw::Vector3d(1,0,0));
	auto roll = buw::calculateAngleBetweenVectors(eigenX, buw::Vector3d(1.0, 0.0, 0.0));
	auto yaw = buw::calculateAngleBetweenVectors(eigenX, buw::Vector3d(1.0, 0.0, 0.0));

	Eigen::AngleAxisd rollAngle(roll, Eigen::Vector3d::UnitZ());
	Eigen::AngleAxisd yawAngle(0, Eigen::Vector3d::UnitY());
	Eigen::AngleAxisd pitchAngle(0, Eigen::Vector3d::UnitX());

	Eigen::Quaternion<double> q = rollAngle * yawAngle * pitchAngle;

	Eigen::Matrix3d rotationMatrix = q.matrix();

	for(auto &point : pointCloud.points) {
		point.position.applyOnTheLeft(rotationMatrix);
	}

	pointCloud.minPos.applyOnTheLeft(rotationMatrix);
	pointCloud.maxPos.applyOnTheLeft(rotationMatrix);


}
