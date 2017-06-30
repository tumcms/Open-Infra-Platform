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

#include "ImportD40.h"

#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DArc.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid.h"

#include <fstream>
#include <sstream>

using namespace std;

OpenInfraPlatform::Infrastructure::ImportD40Import::ImportD40Import(const string& filename) :
	Import(filename)
{
	struct D40Point
	{
		buw::Vector2d position;
		double station;
		double distToPrev;
		double succRadius;
		double succClothoid;
		double succAngle;
	};
	map<int,vector<D40Point>> allpoints;

	ifstream file = ifstream(filename);
	string line;
	while (getline(file, line))
	{
		if (line.empty())
			continue;

		stringstream stream(line);
		string _040;
		int id;
		D40Point point;

		stream >> _040 >> id >> point.station >> point.distToPrev >> point.succRadius >> point.succClothoid >> point.succAngle >> point.position.x() >> point.position.y();

		assert(_040 == "040");
		assert(stream.eof());

		allpoints[id].push_back(point);
	}

	

	for (auto& kv : allpoints)
	{
		auto alignment = buw::makeReferenceCounted<buw::Alignment2DBased3D>();
		auto horizontalAlignment = buw::makeReferenceCounted<buw::HorizontalAlignment2D>();

		alignmentModel_->addAlignment(alignment);
		alignment->setHorizontalAlignment(horizontalAlignment);

		alignment->setName("Achse " + to_string(kv.first));

		vector<D40Point>& points = kv.second;
		for (int i = 0; i < points.size() - 1; i++)
		{
			buw::Vector2d start = points[i].position;
			buw::Vector2d end = points[i + 1].position;

			double startStation = points[i].station;
			double endStation = points[i + 1].station;
			double elementLength = points[i + 1].distToPrev;

			assert(abs((endStation - startStation) - elementLength) <= 0.1);

			double startRadius = points[i].succRadius;
			double startDirection = buw::constantsd::pi() / 2 - points[i].succAngle / 180 * buw::constantsd::pi();
			double clothoidConstant = points[i].succClothoid;

			if (abs(clothoidConstant) < 0.001)
			{
				if (abs(startRadius) < 0.001)
				{
					auto line = buw::makeReferenceCounted<buw::HorizontalAlignmentElement2DLine>(start, end);
					horizontalAlignment->addElement(line);
				}
				else
				{
					bool clockwise = startRadius > 0;

					buw::Vector2d m = end - start;
					m = m * 0.5;

					buw::Vector2d n(m.y(), -m.x());
					n.normalize();

					double d = sqrt(pow(startRadius, 2) - pow(m.norm(), 2));
					d = d * (clockwise ? 1 : -1);

					buw::Vector2d center = start + m + n * d;

					auto arc = buw::makeReferenceCounted<buw::HorizontalAlignmentElement2DArc>(center, start, end, clockwise);
					horizontalAlignment->addElement(arc);
				}
			}
			else
			{
				double startCurvature = 0;
				if (abs(startRadius) > 0.001 && startRadius != std::numeric_limits<double>::infinity())
					startCurvature = 1 / abs(startRadius);

				bool isEntry = clothoidConstant > 0;
				bool clockwise = startRadius > 0;

				buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> clothoid;

				buw::clothoidDescription desc;
				desc = buw::clothoidDescription(start, 0, startCurvature, !clockwise, abs(clothoidConstant), isEntry, elementLength);
				clothoid = buw::makeReferenceCounted<buw::HorizontalAlignmentElement2DClothoid>(desc);

				buw::Vector2d offset1 = end - start;
				buw::Vector2d offset2 = clothoid->getEndPosition() - clothoid->getStartPosition();
				double angle = buw::calculateAngleBetweenVectors(offset2, offset1);

				desc = buw::clothoidDescription(start, angle, startCurvature, !clockwise, abs(clothoidConstant), isEntry, elementLength);
				clothoid = buw::makeReferenceCounted<buw::HorizontalAlignmentElement2DClothoid>(desc);


				double ec = clothoid->getEndCurvature();
				buw::Vector2d ep = clothoid->getEndPosition();

				horizontalAlignment->addElement(clothoid);
			}

		}
	}
}