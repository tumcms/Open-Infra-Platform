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

#include "DigitalElevationModel.h"

#include "OpenInfraPlatform/Infrastructure/Alignment/IAlignment3D.h"
#include <BlueFramework/Core/assert.h>
#include <set>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

DigitalElevationModel::DigitalElevationModel()
{

}

DigitalElevationModel::~DigitalElevationModel()
{

}

void DigitalElevationModel::addSurface(buw::ReferenceCounted<buw::Surface> surface)
{
	surfaces_.push_back(surface);
}

int DigitalElevationModel::getSurfaceCount() const
{
	return static_cast<int>(surfaces_.size());
}

buw::ReferenceCounted<buw::Surface> DigitalElevationModel::getSurface(const int index) const
{
	return surfaces_[index];
}

const std::vector<buw::ReferenceCounted<buw::Surface>>& DigitalElevationModel::getSurfaces() const
{
	return surfaces_;
}

void DigitalElevationModel::getSurfacesExtend(
	buw::Vector3d& minimalPosition, 
	buw::Vector3d& maximalPosition) const
{
	// Determine min and max positions
	minimalPosition = buw::Vector3d::Ones() * std::numeric_limits<double>::max();
	maximalPosition = buw::Vector3d::Ones() * std::numeric_limits<double>::min();

	int surfaceCount = getSurfaceCount();

	if (surfaceCount == 0)
	{
		minimalPosition = maximalPosition = buw::Vector3d(0, 0, 0);
	}

	for (int si = 0; si < surfaceCount; si++)
	{
		auto s = getSurface(si);

		for (int fi = 0; fi < s->getTriangleCount(); fi++)
		{
			for(int i = 0; i < 3; i++)
			{
				int indexId = s->getTriangeFaces()[fi][i];
				auto position = s->getPoints()[indexId];

				updateMinMax(position, minimalPosition, maximalPosition);
			}
		}
	}
}

std::vector<std::pair<double, double>> 
DigitalElevationModel::getSurfaceProfile(buw::ReferenceCounted<buw::IAlignment3D> a) const
{
	std::vector<std::pair<double, double>> profile;

	for (double s = a->getStartStation(); s < a->getEndStation(); s+=0.5)
	{
		buw::Vector2d position = a->getPosition(s).block<2,1>(0,0);
		for(buw::ReferenceCounted<buw::Surface> surface : surfaces_)
		{
			if(surface->contains(position))
			{
				double z = surface->getZ(position);
				profile.push_back(std::pair<double,double>(s,z));
				if(z != 0)
					break;
			}
		}
	}
	return profile;
}

double DigitalElevationModel::getHeightAtPosition(buw::Vector2d position) const
{
	double z = 0;

	for (buw::ReferenceCounted<buw::Surface> surface : surfaces_)
	{
		if (surface->contains(position))
		{
			z = surface->getZ(position);
			if (z != 0)
				break;
		}
	}

	return z;
}

void DigitalElevationModel::updateMinMax(
	const buw::Vector3d& position, 
	buw::Vector3d &minPos, 
	buw::Vector3d &maxPos) const
{
	// find min and max positions
	for (int j = 0; j < 3; j++)
	{
		if (position[j] < minPos[j])
			minPos[j] = position[j];

		if (position[j] > maxPos[j])
			maxPos[j] = position[j];
	}
}

double DigitalElevationModel::getMinimumHeight() const
{
	buw::Vector3d extendMinimum;
	buw::Vector3d extendMaximum;
	getSurfacesExtend(extendMinimum, extendMaximum);
	return extendMinimum.z();
}

double DigitalElevationModel::getMaximumHeight() const
{
	buw::Vector3d extendMinimum;
	buw::Vector3d extendMaximum;
	getSurfacesExtend(extendMinimum, extendMaximum);
	return extendMaximum.z();
}

buw::Vector3d DigitalElevationModel::getCenterPoint() const
{
	buw::Vector3d extendMinimum;
	buw::Vector3d extendMaximum;
	getSurfacesExtend(extendMinimum, extendMaximum);

	return extendMinimum + 0.5 * (extendMaximum - extendMinimum);
}

void DigitalElevationModel::deleteSurface(buw::ReferenceCounted<buw::Surface> s)
{
	auto iterator = std::find(surfaces_.begin(), surfaces_.end(), s);

	BLUE_ASSERT(iterator != surfaces_.end(), "Invalid surface");

	if (iterator != surfaces_.end())
	{
		surfaces_.erase(iterator);
	}
	else
	{
		throw std::runtime_error("Deletion of alignment failed.");
	}
}


buw::DigitalElevationModel* DigitalElevationModel::createFlatCopy(const DigitalElevationModel& src)
{
	return new DigitalElevationModel(src);
}

void DigitalElevationModel::addBreakLine(const std::vector<buw::Vector3d>& breakLine)
{
	breakLines_.push_back(breakLine);
}

const std::vector<std::vector<buw::Vector3d>>& DigitalElevationModel::getBreakLines() const
{
	return breakLines_;
}


// http://guido.vonrudorff.de/qhull-minimal-example/
// http://www.gamedev.net/topic/250932-convex-hull/
// http://www.codeproject.com/Articles/6751/Delaunay-s-TIN-Triangulated-Irregular-Network
extern "C" {

#include "libqhull/libqhull.h"
#include "libqhull/io.h"
#include "libqhull/qset.h"
}

buw::ReferenceCounted<buw::Surface>
createSurfaceFromXYZPoints(const std::vector<buw::Vector3d>& positions)
{
	buw::ReferenceCounted<buw::Surface> s = std::make_shared<buw::Surface>();

	buw::Vector2d min(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
	for (auto& pos : positions)
	{
		min.x() = std::min(min.x(), pos.x());
		min.y() = std::min(min.y(), pos.y());
	}

	std::vector<buw::Vector2d> positions2;
	for (auto& pos : positions)
	{
		positions2.push_back(buw::Vector2d(pos.x() - min.x(), pos.y() - min.y()));
	}
	 
	for (int i = 0; i < positions.size(); i++)
	{
		s->addPoint(positions[i]);
	}

	if (positions.size() >= 4)
	{
		if (true)
		{
			char flags[250];


			FILE *outfile = stdout;
			FILE *errfile = stderr;

			double* ptr = &(positions2[0].x());

			sprintf_s(flags, "qhull QJ");
			int exitcode = qh_new_qhull(2, (int)positions.size(), ptr, false, flags, outfile, errfile);


			std::set<int> ignoreVertices;
			if (!exitcode)
			{
				int i = 0;
				vertexT *vertex, **vertexp;;
				FORALLvertices
				{
					ignoreVertices.insert(qh_pointid(vertex->point));
				}
			}

			sprintf_s(flags, "qhull d QJ");
			exitcode = qh_new_qhull(2, (int)positions.size(), ptr, false, flags, outfile, errfile);
			if (!exitcode)
			{
				facetT* facet;
				FORALLfacets
				{
					vertexT *vertex, **vertexp;
					buw::Vector3i indices;

					int i = facet->toporient ^ qh_ORIENTclock ? 0 : 2;
					FOREACHvertex_(facet->vertices)
					{
						indices[i] = qh_pointid(vertex->point);
						
						i += facet->toporient ^ qh_ORIENTclock ? 1 : -1;
					}
					
					bool ignore =
						ignoreVertices.find(indices[0]) != ignoreVertices.end() &&
						ignoreVertices.find(indices[1]) != ignoreVertices.end() &&
						ignoreVertices.find(indices[2]) != ignoreVertices.end();

					if (!ignore)
						s->addTriangle(indices);
				}
			}
			else
			{
				assert(false);
			};
		}
	}
	
	return s;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END