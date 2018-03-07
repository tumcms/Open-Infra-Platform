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