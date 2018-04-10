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
#include <Neighbourhood.h>
#include <algorithm>

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
	buw::Vector3d eigenY = vec.col(1);
	buw::Vector3d eigenZ = vec.col(0);

	auto pitch = buw::calculateAngleBetweenVectors(buw::Vector3d(1, 0, 0), buw::Vector3d(1,0,0));
	auto roll = buw::calculateAngleBetweenVectors(eigenX, buw::Vector3d(1.0, 0.0, 0.0));
	auto yaw = buw::calculateAngleBetweenVectors(eigenX, buw::Vector3d(1.0, 0.0, 0.0));

	Eigen::AngleAxisd rollAngle(0, Eigen::Vector3d::UnitZ());
	Eigen::AngleAxisd yawAngle(0, Eigen::Vector3d::UnitY());
	Eigen::AngleAxisd pitchAngle(0, Eigen::Vector3d::UnitX());

	Eigen::Quaternion<double> q = rollAngle * yawAngle * pitchAngle;

	Eigen::Matrix3d rotationMatrix = q.matrix();

	pointCloud.minPos.applyOnTheLeft(rotationMatrix);
	pointCloud.maxPos.applyOnTheLeft(rotationMatrix);

	buw::Vector3d axis = eigenX.normalized();

	float minLength = 0.0f, maxLength = 0.0f;

	for(auto &point : pointCloud.points) {
		point.position.applyOnTheLeft(rotationMatrix);
		float length = axis.dot(point.position);
		minLength = fminf(minLength, length);
		maxLength = fmaxf(maxLength, length);		
	}

	float n = maxLength - minLength;

	float precision = 50.0f;

	size_t numBuckets = (std::floorf(precision * maxLength) - std::floorf(precision * minLength)) + 1;

	std::vector<std::vector<size_t>> segments = std::vector<std::vector<size_t>>(numBuckets);

	for(auto vec : segments) {
		vec = std::vector<size_t>();
	}

	for(size_t i = 0; i < pointCloud.points.size(); i++) {
		auto& point = pointCloud.points[i];
		float length = axis.dot(point.position);
		
		float col = (length - minLength) / n;
		point.color = buw::Vector3f(col, col, col);

		float diff = (std::floorf(precision *length) / precision) - length;
		point.position += diff*axis;

		size_t bucket = std::floorf(precision *length) - std::floorf(precision * minLength);
		segments[bucket].push_back(i);
	}

	buw::Vector3d center;
	for(auto point : pointCloud.points)
		center += point.position;

	center /= pointCloud.points.size();
	CCVector3 center3D = CCVector3(center.x(), center.y(), center.z());


	//BLUE_LOG(trace) << QString::number(numBuckets).toStdString();

	std::vector<buw::LaserPoint> segmentedPoints = std::vector<buw::LaserPoint>();

	for(auto segment : segments) {
		if(segment.size() > 2) {
			ccPointCloud cloud = ccPointCloud();
			cloud.reserve(segment.size());
			for(auto index : segment) {
				auto pos = pointCloud.points[index].position;
				const CCVector3 point = CCVector3(pos.x(), pos.y(), pos.z());
				cloud.addPoint(point);
			}

			CCLib::Neighbourhood neighbourhood = CCLib::Neighbourhood(&cloud);
			std::vector<CCVector2> points2D = std::vector<CCVector2>(cloud.size());

			CCVector3 N(neighbourhood.getLSPlane());

			CCVector3 u, v;
			CCLib::CCMiscTools::ComputeBaseVectors(N, u, v);


			std::shared_ptr<CCVector3> planeO = std::make_shared<CCVector3>(), planeX = std::make_shared<CCVector3>(), planeY = std::make_shared<CCVector3>();

			if(neighbourhood.projectPointsOn2DPlane(points2D,nullptr,planeO.get(), planeX.get(), planeY.get())) {
				auto comp = [](CCVector2 lhs, CCVector2 rhs)->bool {
					return lhs.x < rhs.x;
				};

				auto invertY = [](CCVector2 &point) {
					point.y = -point.y;
				};
				
				CCVector2 center2D = CCVector2(center3D.dot(*planeX), center3D.dot(*planeY));

				auto isOutlier = [=](const CCVector2 &point) -> bool {					
					float threshold = 1.0f;
					return std::fabsf(point.y - center2D.y) > threshold;
				};

				std::sort(points2D.begin(), points2D.end(), comp);

				std::for_each(points2D.begin(), points2D.end(), invertY);

				//auto end = std::remove_if(points2D.begin(), points2D.end(), isOutlier);
				//points2D.erase(end, points2D.end());
				

				if(points2D.size() > 2) {
					std::vector<float> dx = std::vector<float>(points2D.size() - 2);
					std::vector<float> dy = std::vector<float>(points2D.size() - 2);

					for(size_t i = 1; i < points2D.size() - 1; i++) {
						dx[i - 1] = points2D[i + 1].x - points2D[i - 1].x;
						dy[i - 1] = points2D[i + 1].y - points2D[i - 1].y;

						float delta = std::fabsf(dy[i - 1]) / std::fabsf(dx[i - 1]);
						if(delta > 500.0f) {
							CCVector3 point3D = *planeO + points2D[i].x * *planeX + (-points2D[i].y) * *planeY;
							segmentedPoints.push_back({ {point3D.x, point3D.y, point3D.z},{0.0f,1.0f,0.0f} });
						}
						else {
							CCVector3 point3D = *planeO + points2D[i].x * *planeX + (-points2D[i].y) * *planeY;
							segmentedPoints.push_back({ { point3D.x, point3D.y, point3D.z }, { 0.9f,0.9f,0.9f } });
						}
					}
				}

			}
			else {
				BLUE_LOG(warning) << "Projection failed.";
			}
		}
	}
	
	pointCloud.points = segmentedPoints;
}
