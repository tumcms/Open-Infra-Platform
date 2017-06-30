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

#include "PointCloudProcessing.h"
#include <liblas/liblas.hpp>

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

	std::cout << "Compressed: " << (header.Compressed() == true) ? "true" : "false";
	std::cout << "Signature: " << header.GetFileSignature() << '\n';
	std::cout << "Points count: " << header.GetPointRecordsCount() << '\n';

	buw::Vector3d minv(0, 0, 0);
	buw::Vector3d maxv(0, 0, 0);

	pointCloud.points.reserve(header.GetPointRecordsCount());

	bool first = true;
	while (reader.ReadNextPoint())
	{
		liblas::Point const& p = reader.GetPoint();

		float colorRange = std::numeric_limits<liblas::Color::value_type>::max();
		//p.GetColor()
		pointCloud.points.push_back({
			buw::Vector3d(p.GetX(), p.GetY(), p.GetZ()),
			buw::Vector3f(p.GetColor().GetRed() / colorRange, p.GetColor().GetGreen() / colorRange, p.GetColor().GetBlue() / colorRange) });

		if (first)
		{
			minv = maxv = pointCloud.points.back().position;
			first = false;
		}
		else
		{
			minv = buw::minimizedVector(minv, pointCloud.points.back().position);
			maxv = buw::minimizedVector(maxv, pointCloud.points.back().position);
		}
	}

	pointCloud.minPos = minv;
	pointCloud.maxPos = maxv;
}