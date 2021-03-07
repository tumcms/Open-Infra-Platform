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

#include "PointCloudProcessing.h"


#include <liblas/liblas.hpp>
#include <BlueFramework/Core/Diagnostics/log.h>

#include <FileIOFilter.h>
#include <ccPointCloud.h>
#include <ReferenceCloud.h>
#include <ccHObjectCaster.h>
#include <Neighbourhood.h>
#include <ccScalarField.h>
#include <algorithm>


/*
		//Parse the point cloud.
		parsePointCloud(ccTempObject, pointCloud);		


		//Calculate the center of mass of our point cloud and store it in center and center3D.
		buw::Vector3d center;
		for(auto point : pointCloud.points) {
			center += point.position;
		}
		center /= pointCloud.points.size();
		CCVector3 center3D = CCVector3(center.x(), center.y(), center.z());

		//Get three largest eigenvectors by PCA.
		Eigen::Matrix<double, 3, 3> vec = getEigenvectors<3>(pointCloud);

		//Get the 3 main axis of the dataset which and interpret them as x,y,z axis.
		buw::Vector3d eigenX, eigenY, eigenZ;
		eigenX = vec.col(2).normalized();
		eigenY = vec.col(1).normalized();
		eigenZ = vec.col(0).normalized();

		//The main axis of the dataset.
		buw::Vector3d axis = eigenX;

		//Calculate the projection of all points along the main axis to find the min and max.
		float minLength = 0.0f, maxLength = 0.0f;
		for(auto point : pointCloud.points) {
			float length = axis.dot(point.position);
			minLength = fminf(minLength, length);
			maxLength = fmaxf(maxLength, length);
		}

		//Normalization constant for the length of projection along main axis.
		float n = maxLength - minLength;

		//The actual precision is 1/precision, so if precision is 1, each segment covers 1 meter along the main axis.
		float precision = 10.0f;

		//Determine the number of buckets where floor(prec*minLength) is the number of buckets in "negative direction" - so also negative - and this is "subtracted" from
		//the number of buckets in "positive direction".
		size_t numBuckets = (std::floorf(precision * maxLength) - std::floorf(precision * minLength)) + 1;
		std::vector<std::vector<size_t>> sections2D = std::vector<std::vector<size_t>>(numBuckets);
		for(auto vec : sections2D) {
			vec = std::vector<size_t>();
		}

		//Determine the segment and color for each point.
		for(size_t i = 0; i < pointCloud.points.size(); i++) {
			auto& point = pointCloud.points[i];
			float length = axis.dot(point.position);

			//Set the color as grayscale to indicate the position along the main axis.
			float col = (length - minLength) / n;
			point.color = buw::Vector3f(col, col, col);

			//Remove this for now and let the cc library find the ls plane to improve the behaviour in curves slightly.
			//float diff = (std::floorf(precision *length) / precision) - length;
			//point.position += diff*axis;

			//Each bucket is a segment, so insert the index of the point into the corresponding bucket to avoid cloning all points etc.
			size_t bucket = std::floorf(precision *length) - std::floorf(precision * minLength);
			sections2D[bucket].push_back(i);
		}

		//Initialize and empty vector for the points which will be segmented.
		std::vector<buw::LaserPoint> segmentedPoints = std::vector<buw::LaserPoint>();

		//Iterate over all sections2D and try to segment the rail points.
		for(auto segment : sections2D) {			

			//If segment has less then 2 points, we can't fit a distinct plane - we can fit infinitely many planes with 0 error.
			if(segment.size() > 2) {

				//Create a empty point cloud and add all points from the segment to it to have access to the CCLib::Neighbourhood functionality.
				ccPointCloud cloud3D = ccPointCloud();
				cloud3D.reserve(segment.size());
				for(auto index : segment) {
					auto pos = pointCloud.points[index].position;
					const CCVector3 point = CCVector3(pos.x(), pos.y(), pos.z());
					cloud3D.addPoint(point);
				}

				//Get the center of the segment.
				CCVector3 segmentCenter = cloud3D.computeGravityCenter();

				//Create a CCLib::Neighbourhood from our cloud to do projection and search etc.
				CCLib::Neighbourhood neighbourhood = CCLib::Neighbourhood(&cloud3D);
				
				//Initialize a vector of 2D points to hold our projected points.
				std::vector<CCVector2> points2D = std::vector<CCVector2>(cloud3D.size());

				//Calculate d as projection of the segment center onto the main axis.
				float d = (float)axis.dot(buw::Vector3d(segmentCenter.x, segmentCenter.y, segmentCenter.z));

				//Set the plane along the main axis at the position of the projection of the center of mass of the segment.
				float plane[4] = { axis.x(), axis.y(), axis.z(), d };
				
				//Store the plane origin, X and Y axis to project our segmented points back into the original 3D space.
				std::shared_ptr<CCVector3> planeO = std::make_shared<CCVector3>(), planeX = std::make_shared<CCVector3>(), planeY = std::make_shared<CCVector3>();

				//Project the points of the segment onto plane determined by the main axis plane.
				if(neighbourhood.projectPointsOn2DPlane(points2D, plane, planeO.get(), planeX.get(), planeY.get())) {

					//Create a 2D point cloud to estimate the curvature of the points.
					std::shared_ptr<ccPointCloud> cloud2D = std::make_shared<ccPointCloud>();
					cloud2D->reserve(points2D.size());
					for(auto point : points2D) {
						//Add points with their 3D coordinates, but in 2d space to make the curvature computation "2D".
						cloud2D->addPoint(*planeO + point.x * *planeX + point.y * *planeY);
					}
					int result = 0;
					
					//Remove duplicate points
					result = CCLib::GeometricalAnalysisTools::flagDuplicatePoints(cloud2D.get(),0.005f);
					if(result == 0) {
						size_t sizeBefore = cloud2D->size();
						cloud2D.swap(std::shared_ptr<ccPointCloud>(cloud2D->filterPointsByScalarValue(0, 0)));
						BLUE_LOG(trace) << "Removed " << QString::number(sizeBefore - cloud2D->size()).toStdString() << " duplicate points.";
					}
					else {
						BLUE_LOG(warning) << "Duplicate flagging failed! Error code: " << QString::number(result).toStdString();
						result = 0;
					}

					//Not really working, cant detect outliers.			
					{
						int idx_density = cloud2D->addScalarField("density");
						cloud2D->setCurrentInScalarField(idx_density);

						result = CCLib::GeometricalAnalysisTools::computeLocalDensity(cloud2D.get(), CCLib::GeometricalAnalysisTools::DENSITY_3D, 0.1f);
						if(result == 0) {
							cloud2D->setCurrentOutScalarField(idx_density);
							size_t sizeBefore = cloud2D->size();
							cloud2D.swap(std::shared_ptr<ccPointCloud>(cloud2D->filterPointsByScalarValue(0, 100, true)));
							BLUE_LOG(trace) << "Removed " << QString::number(sizeBefore - cloud2D->size()).toStdString() << " lonesome outlier points.";
						}
						else {
							BLUE_LOG(warning) << "Approximate density computation failed! Error code: " << QString::number(result).toStdString();
							result = 0;
						}
					}	

					//Compute the curvature for all points with diefferent metrics
					int idx[2];
					idx[0] = cloud2D->addScalarField("curvature_mean");
					idx[1] = cloud2D->addScalarField("curvature_normal");					

					cloud2D->setCurrentInScalarField(idx[0]);
					result += CCLib::GeometricalAnalysisTools::computeCurvature(cloud2D.get(), CCLib::Neighbourhood::CC_CURVATURE_TYPE::MEAN_CURV, 0.7f);

					cloud2D->setCurrentInScalarField(idx[1]);
					result += CCLib::GeometricalAnalysisTools::computeCurvature(cloud2D.get(), CCLib::Neighbourhood::CC_CURVATURE_TYPE::NORMAL_CHANGE_RATE, 0.05f);					

					if(result == 0) {
						float mean0, mean1, min0, min1, max0, max1;

						cloud2D->getScalarField(idx[0])->computeMeanAndVariance(mean0);
						cloud2D->getScalarField(idx[0])->computeMinAndMax();
						min0 = cloud2D->getScalarField(idx[0])->getMin();
						max0 = cloud2D->getScalarField(idx[0])->getMax();

						cloud2D->getScalarField(idx[1])->computeMeanAndVariance(mean1);
						cloud2D->getScalarField(idx[1])->computeMinAndMax();
						min1 = cloud2D->getScalarField(idx[1])->getMin();
						max1 = cloud2D->getScalarField(idx[1])->getMax();
						
						float scale = 200000.0f;

						for(size_t i = 0; i < cloud2D->size(); i++) {
							auto point = cloud2D->getPoint(i);
							buw::Vector3d pos = { point->x,point->y,point->z };
							buw::Vector3f col = buw::Vector3f(0.0f, 0.0f, 0.0f);

							cloud2D->setCurrentOutScalarField(idx[0]);
							float curvature0 = cloud2D->getPointScalarValue(i);
							bool hasAboveAvgMeanCurve = curvature0 >= mean0;
							col[0] = scale *curvature0;

							cloud2D->setCurrentOutScalarField(idx[1]);
							float curvature1 = cloud2D->getPointScalarValue(i);
							bool hasAboveAvgNormalChangeRate = curvature1 >= mean1;
							col[1] = scale *curvature1;

							//if(hasAboveAvgNormalChangeRate && !hasAboveAvgMeanCurve)
							segmentedPoints.push_back({ pos, col });
								
							
						}
					}
					else {
						BLUE_LOG(warning) << "Curvature computation failed! Error code: " << QString::number(result).toStdString();
						result = 0;
					}					

					//Lambda function which sorts after increasing X value
					auto increasingX = [](const CCVector2 &lhs, const CCVector2 &rhs)->bool {
						return lhs.x < rhs.x;
					};

					//Lambda function to invert the y values.
					auto invertY = [](CCVector2 &point) {
						point.y = -point.y;
					};

					//Is somewhere, don't know why, but not the real center.
					CCVector2 center2D = CCVector2(center3D.dot(*planeX), center3D.dot(*planeY));

					//Lambda function which performs a flat threshold on the y values.
					auto isOutlierFlat = [](const CCVector2 &point) -> bool {
						float threshold = 0.2f;
						return std::fabsf(point.y) > threshold;
					};


					//Currently disabled to use curvature.
					//std::sort(points2D.begin(), points2D.end(), increasingX);

					//Invert y values since they are upside down.
					//std::for_each(points2D.begin(), points2D.end(), invertY);

					//Currently removed since the metric is not yet really effective.
					//auto end = std::remove_if(points2D.begin(), points2D.end(), isOutlier);
					//points2D.erase(end, points2D.end());

					//If we have more than 2 points, calculate derivatives and decide whether the point is belonging to a rail or not.
					if(points2D.size() > 2) {

						//Initialize vectors to store changes in x and y direction and compute derivatives.
						std::vector<float> dx = std::vector<float>(points2D.size() - 2), dy = std::vector<float>(points2D.size() - 2);
						for(size_t i = 1; i < points2D.size() - 1; i++) {
							dx[i - 1] = points2D[i + 1].x - points2D[i - 1].x;
							dy[i - 1] = points2D[i + 1].y - points2D[i - 1].y;
						}

						//Currently disabled to test curvature
						{
							//Calculate rate of change as dy/dx - first derivative.
							float delta = std::fabsf(dy[i - 1]) / std::fabsf(dx[i - 1]);

							//Segment point if delta is above a flat threshold.
							if(delta > 500.0f) {
								CCVector3 point3D = *planeO + points2D[i].x * *planeX + (-points2D[i].y) * *planeY;
								segmentedPoints.push_back({ {point3D.x, point3D.y, point3D.z},{ 0.0f,1.0f,0.0f} });
							}
							else {
								CCVector3 point3D = *planeO + points2D[i].x * *planeX + (-points2D[i].y) * *planeY;
								segmentedPoints.push_back({ { point3D.x, point3D.y, point3D.z }, { 0.9f,0.9f,0.9f } });
							}
						}
						
					}
				}
				else {
					//Write an info, but no warning since this might happen quite often.
					BLUE_LOG(info) << "Projection failed.";
				}
			}
		}

		pointCloud.points = segmentedPoints;
	}
}
*/

std::array<double, 4> OpenInfraPlatform::PointCloudProcessing::fitHarmonicOscilation(const std::vector<double>& x, const std::vector<double>& y)
{
	return std::array<double, 4>();
}
