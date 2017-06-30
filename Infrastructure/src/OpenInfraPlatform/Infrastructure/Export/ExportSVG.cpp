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

#include "ExportSVG.h"

#include <list>

void OpenInfraPlatform::Infrastructure::ExportSVG::outputToSVG(FILE *fp, buw::ReferenceCounted<buw::HorizontalAlignment2D> horizontalAlignment)
{
	std::string output = "";
	buw::Vector2d start;
	auto he = horizontalAlignment->getAlignmentElementByIndex(0);
	he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition, &start);
	output += "<g>\n<path d=\"M " + std::to_string(start.x()) + "," + std::to_string(-start.y()) + " ";

	for (int i = 0; i < horizontalAlignment->getAlignmentElementCount(); i++)
	{
		he = horizontalAlignment->getAlignmentElementByIndex(i);

		if (he->getAlignmentType() == buw::eHorizontalAlignmentType::Line)
		{
			buw::Vector2d end = he->getEndPosition();
		
			output += "L " + std::to_string(end.x()) + "," + std::to_string(-end.y()) + " ";
		}

		if (he->getAlignmentType() == buw::eHorizontalAlignmentType::Arc)
		{
			buw::Vector2d end = he->getEndPosition();
			bool clockwise;
			double radius;

			he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Clockwise, &clockwise);
			he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Radius, &radius);

			output += "A " + std::to_string(radius) + "," + std::to_string(radius) + " 0 0," + std::to_string(clockwise) + " " + std::to_string(end.x()) + "," + std::to_string(-end.y()) + " ";
		}

		if (he->getAlignmentType() == buw::eHorizontalAlignmentType::Clothoid)
		{	
			for (float s = 0.0f; s < 1.0f; s+=0.05f) // use 20 segments to approximate clothoid
			{
				buw::Vector2d end = he->getPosition(s);
				output += "L " + std::to_string(end.x()) + "," + std::to_string(-end.y()) + " ";
			}

			buw::Vector2d end = he->getEndPosition();

			output += "L " + std::to_string(end.x()) + "," + std::to_string(-end.y()) + " ";
		}
	}

	output += "\">\n</path>\n</g>\n";
	fprintf(fp, output.c_str());
}

void OpenInfraPlatform::Infrastructure::ExportSVG::addPath(FILE *fp, const buw::Vector2d& a, const buw::Vector2d& b, const buw::Vector2d& c)
{
	fprintf(fp, "<path d=\"M %f,%f L %f,%f L %f,%f z\"/>\n", a.x(), -a.y(), b.x(), -b.y(), c.x(), -c.y());
}

OpenInfraPlatform::Infrastructure::ExportSVG::ExportSVG(buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename) :
	Export(am, dem, filename)
{
	FILE *fp = fopen(filename.c_str(), "w");

	if (!fp)
		return;

	fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
	fprintf(fp, "<svg\n");
	fprintf(fp, "xmlns:svg=\"http://www.w3.org/2000/svg\"\n");
	fprintf(fp, "xmlns=\"http://www.w3.org/2000/svg\"\n");
	fprintf(fp, "version=\"1.0\"\n");

	buw::Vector3d pmin, pmax, Surfacesmax, Surfacesmin, Alignmentsmin, Alignmentsmax, pnull = { 0, 0, 0 };

	//the following code until the chapter "surfaces" determines the maximal positions of all alignments and surfaces.
	//It is considered if alignments and surfaces were created or not

	if (alignmentModel_->getAlignmentCount() != 0)
	{
		Alignmentsmin = alignmentModel_->getAlignment(0)->getPosition(0);		Alignmentsmax = alignmentModel_->getAlignment(0)->getPosition(0);
		for (const auto& alignment : alignmentModel_->getAlignments())
		{
			for (double s = alignment->getStartStation(); s < alignment->getEndStation(); s += 1.0)
			{
				auto p = alignment->getPosition(s);
				Alignmentsmin = buw::minimizedVector(Alignmentsmin, p);
				Alignmentsmax = buw::minimizedVector(Alignmentsmax, p);
			}
		}
	}
	if (digitalElevationModel_->getSurfaceCount() != 0)
	{
		digitalElevationModel_->getSurfacesExtend(Surfacesmin, Surfacesmax);
	}
	if (digitalElevationModel_->getSurfaceCount() != 0 && alignmentModel_->getAlignmentCount() != 0)
	{
		for (int i = 0; i < 2; i++)
		{
			if (Alignmentsmin[i] < Surfacesmin[i])
			{
				pmin[i] = Alignmentsmin[i];
			}
			else pmin[i] = Surfacesmin[i];
			if (Alignmentsmax[i] > Surfacesmax[i])
			{
				pmax[i] = Alignmentsmax[i];
			}
			else pmax[i] = Surfacesmax[i];
		}
	}
	if (digitalElevationModel_->getSurfaceCount() != 0 && alignmentModel_->getAlignmentCount() == 0)
	{
		pmin = Surfacesmin;	pmax = Surfacesmax;
	}
	if (digitalElevationModel_->getSurfaceCount() == 0 && alignmentModel_->getAlignmentCount() != 0)
	{
		pmin = Alignmentsmin;		pmax = Alignmentsmax;
	}
	if (alignmentModel_->getAlignmentCount() == 0 && digitalElevationModel_->getSurfaceCount() == 0)
	{
		Alignmentsmax = Alignmentsmin = Surfacesmin = Surfacesmax = pnull;
	}
	fprintf(fp, "width=\"1280\" height=\"1024\" viewBox=\" %f %f %f %f \">\n", pmin[0], -pmax[1], abs(pmax[0] - pmin[0]), abs(pmax[1] - pmin[1]));
	fprintf(fp, "<style type=\"text/css\"><![CDATA[.surface{stroke:black;stroke-width:0.001in;fill:orange;}.parcel{stroke:blue;stroke-width:0.01in;fill:none;}.planFeature{stroke:cyan;stroke-width:0.01in;fill:none;}.alignment{stroke:blue;stroke-width:0.02in;fill:none;}.cgpoint{fill:cyan;}.cgpointtext{font-family:'Verdana';font-size:8%;}]]></style>");

	// Surfaces
	for (int i = 0; i < digitalElevationModel_->getSurfaceCount(); i++)
	{
		std::list <int> unsortIDList;
		std::list <int>::const_iterator iter1;
		std::vector <int> missingPointsID;
		fprintf(fp, "<g id=\"Surfaces\">\n");
		fprintf(fp, "<g id=\"SurfaceSet_\" class=\"surface\">\n");
		fprintf(fp, "<g>");
		buw::ReferenceCounted<buw::Surface> currentSurface = digitalElevationModel_->getSurface(i);
		int x = 0; // first point has always id 0 - old behaviour was differntly from this  //currentSurface.getPoints()[0].id;

		// the following code until "gaps found" searches for gaps in the point ids
		for (int j = 0; j < currentSurface->getTriangeFaces().size(); j++) // create unsortIDList
		{
			for (int f = 0; f < 3; f++)
			{
				unsortIDList.push_back(currentSurface->getTriangeFaces()[j][f]);
			}
		}
		unsortIDList.sort();// sort unsortIDList 
		unsortIDList.unique();// deletes IDs that are more than one time in the list

		// compare every input with a normal numeration and determine by this way the gaps
		for (iter1 = unsortIDList.begin(); iter1 != unsortIDList.end(); iter1++)
		{
			if (*iter1 != x)
			{
				missingPointsID.push_back(x);
				x++;
			}
			x++;
		}// gaps found

		for (int j = 0; j<currentSurface->getTriangeFaces().size(); j++)
		{
			int pointNo1 = currentSurface->getTriangeFaces()[j][0];
			int pointNo2 = currentSurface->getTriangeFaces()[j][1];
			int pointNo3 = currentSurface->getTriangeFaces()[j][2];

			// because of the gap the numeration has been changed, in the following loop this is corrected		
			for (int g = 0; g<missingPointsID.size(); g++)
			{
				if (currentSurface->getTriangeFaces()[j][0] > missingPointsID[g])
				{
					pointNo1--;
				}
				if (currentSurface->getTriangeFaces()[j][1] > missingPointsID[g])
				{
					pointNo2--;
				}
				if (currentSurface->getTriangeFaces()[j][2] > missingPointsID[g])
				{
					pointNo3--;
				}
			}
			buw::Vector2d a;
			a.x() = currentSurface->getPoints()[pointNo1][0];
			a.y() = currentSurface->getPoints()[pointNo1][1];
			buw::Vector2d b;
			b.x() = currentSurface->getPoints()[pointNo2][0];
			b.y() = currentSurface->getPoints()[pointNo2][1];
			buw::Vector2d c;
			c.x() = currentSurface->getPoints()[pointNo3][0];
			c.y() = currentSurface->getPoints()[pointNo3][1];

			addPath(fp, a, b, c);
		}

		fprintf(fp, "</g>\n");
		fprintf(fp, "</g>\n");
		fprintf(fp, "</g>\n");
	}
	
	// Horizontal alignment
	fprintf(fp, "<g id=\"AlignmentSet_\" class=\"alignment\">\n");

	for (const auto& alignment : alignmentModel_->getAlignments())
	{
		if (alignment->getType() != buw::e3DAlignmentType::e2DBased)
		{
			continue;
		}

		buw::ReferenceCounted<buw::Alignment2DBased3D> alignment2D = std::static_pointer_cast<buw::Alignment2DBased3D>(alignment);
		std::string output = "";
		outputToSVG(fp, alignment2D->getHorizontalAlignment());
	}
	fprintf(fp, "</g>\n");
	fprintf(fp, "</svg>\n");

	fclose(fp);
}