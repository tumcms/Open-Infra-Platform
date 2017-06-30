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

#include "ImportIfcAlignment1x0.h"

#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment2DBased3D.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment3DBased3D.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DArc.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DParabola.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DArc.h"

#include "OpenInfraPlatform/IfcAlignment/model/IfcAlignmentP6Model.h"
#include "OpenInfraPlatform/IfcAlignment/model/IfcAlignmentP6Exception.h"
#include "OpenInfraPlatform/IfcAlignment/reader/IfcStepReader.h"
#include "OpenInfraPlatform/IfcAlignment/writer/IfcStepWriter.h"
#include "OpenInfraPlatform/IfcAlignment/IfcAlignmentP6Entities.h"
#include "OpenInfraPlatform/IfcAlignment/IfcAlignmentP6Types.h"
#include "OpenInfraPlatform/IfcAlignment/model/IfcAlignmentP6Model.h"
#include "OpenInfraPlatform/IfcAlignment/model/IfcAlignmentP6Exception.h"
#include "OpenInfraPlatform/IfcAlignment/reader/IfcStepReader.h"
#include "OpenInfraPlatform/IfcAlignment/reader/IfcAlignmentReader.h"
#include "OpenInfraPlatform/IfcAlignment/reader/IfcStepReader.h"
#include "OpenInfraPlatform/IfcAlignment/model/UnitConverter.h"
#include "OpenInfraPlatform/IfcAlignment/entity/include/IfcCartesianPoint.h"
#include "OpenInfraPlatform/IfcAlignment/IfcAlignmentP6EntityEnums.h"

#include <fstream>

using namespace OpenInfraPlatform::IfcAlignment;

class OpenInfraPlatform::Infrastructure::ImportIfcAlignment1x0::ImportIfcAlignmenImpl : public Import
{
public:
	ImportIfcAlignmenImpl(const std::string& filename) : 
		Import(filename)
	{
		const bool importTerrain = true;
		const bool importAlignment = true;
		
		shared_ptr<IfcStepReader> m_step_reader = shared_ptr<IfcStepReader>(new IfcStepReader());
		shared_ptr<IfcAlignmentModel> m_ifc_model(new IfcAlignmentModel());

		// open file
		std::ifstream infile;
		infile.open(filename.c_str(), std::ifstream::in);

		if (!infile.is_open())
		{
			throw buw::FileNotFoundException("Could not open file.");
		}

		// get length of file:
		infile.seekg(0, std::ios::end);
		const int length = infile.tellg();
		infile.seekg(0, std::ios::beg);

		// allocate memory:
		std::string buffer(length, '\0');

		// read data as a block:
		infile.read(&buffer[0], length);
		infile.close();

		m_ifc_model->clearIfcModel();

		int millisecs_read_start = clock();
		m_step_reader->readStreamHeader(buffer, m_ifc_model);
		std::string file_schema_version = m_ifc_model->getFileSchema();
		std::map<int, shared_ptr<IfcAlignmentP6Entity> > map_entities;

		try
		{
			m_step_reader->readStreamData(buffer, map_entities);
		}
		catch (IfcAlignmentP6Exception& e)
		{
			throw buw::Exception(e.what());
		}

		// get offset value!
		offset_ = buw::Vector3d(0.0, 0.0, 0.0);
		for (auto it = map_entities.begin(); it != map_entities.end(); it++)
		{
			if (it->second->m_entity_enum == IFCMAPCONVERSION)
			{
				std::shared_ptr<IfcMapConversion> mapConversion = std::static_pointer_cast<IfcMapConversion>(it->second);
				
				BLUE_ASSERT(mapConversion->m_Eastings != nullptr, "Invalid easting.");
				BLUE_ASSERT(mapConversion->m_Northings != nullptr, "Invalid northing.");
				BLUE_ASSERT(mapConversion->m_OrthogonalHeight != nullptr, "Invalid orthogonal height.");

				offset_.x() = mapConversion->m_Eastings->m_value;
				offset_.y() = mapConversion->m_Northings->m_value;
				offset_.z() = mapConversion->m_OrthogonalHeight->m_value;
			}
		}

		for (auto it = map_entities.begin(); it != map_entities.end(); it++)
		{
			int id = it->second->m_entity_enum;
			if (importAlignment)
			{
				if (it->second->m_entity_enum == IFCALIGNMENT)
				{
					std::shared_ptr<OpenInfraPlatform::IfcAlignment::IfcAlignment> alignment = 
						std::static_pointer_cast<OpenInfraPlatform::IfcAlignment::IfcAlignment>(it->second);
					createAlignment(alignment);
				}
			}

			if (importTerrain)
			{
				if (it->second->m_entity_enum == IFCTRIANGULATEDFACESET)
				{
					std::shared_ptr<IfcTriangulatedFaceSet> triangluatedFaceSet = std::static_pointer_cast<IfcTriangulatedFaceSet>(it->second);
					createTerrainSurface(triangluatedFaceSet);
				}
			}
		}
	}

	void createAlignment(std::shared_ptr<OpenInfraPlatform::IfcAlignment::IfcAlignment> ifcAlignment)
	{
		buw::ReferenceCounted<buw::Alignment2DBased3D> alignment = std::make_shared<buw::Alignment2DBased3D>();

		// read name of alignment
		if (ifcAlignment->m_Description != nullptr)
		{
			std::string name = ifcAlignment->m_Description->m_value;
			alignment->setName(buw::String::toWStdString(name));
		}
		else
		{
			alignment->setName(L"Alignment");
		}
		
		buw::ReferenceCounted<buw::HorizontalAlignment2D> h = createHorizontalAlignment(ifcAlignment);
		alignment->setHorizontalAlignment(h);

		if (alignment->hasHorizontalAlignment())
		{
			if (alignment->getHorizontalAlignment()->getAlignmentElementCount() > 0)
			{
				alignmentModel_->addAlignment(alignment);
			}
		}

		buw::ReferenceCounted<buw::VerticalAlignment2D> v = createVerticalAlignment(ifcAlignment);
		if (v != nullptr)
		{
			alignment->setVerticalAlignment(v);
		}

		if (ifcAlignment->m_Representation != nullptr)
		{
			createAlignment3D(ifcAlignment);
		}
		
	}

	void createAlignment3D(buw::ReferenceCounted<OpenInfraPlatform::IfcAlignment::IfcAlignment> ifcAlignment)
	{
		if (true)
		{
			std::vector<buw::ReferenceCounted<IfcRepresentation>> representations = ifcAlignment->m_Representation->m_Representations;
			if (representations[0])
			{
				std::vector<buw::ReferenceCounted<IfcRepresentationItem>> representationItems = representations[0]->m_Items;
				if (representationItems[0])
				{
					buw::ReferenceCounted<IfcIndexedPolyCurve> indexedPolyCurve = std::static_pointer_cast<IfcIndexedPolyCurve>(representationItems[0]);
					if (indexedPolyCurve)
					{
						buw::ReferenceCounted<IfcCartesianPointList3D> pointList = std::static_pointer_cast<IfcCartesianPointList3D>(indexedPolyCurve->m_Points);
						if (pointList)
						{
							buw::ReferenceCounted<buw::Alignment3DBased3D> alignment3d = std::make_shared<buw::Alignment3DBased3D>(0);

							for (auto& p : pointList->m_CoordList)
							{
								alignment3d->addPoint(buw::Vector3d(p[0]->m_value + offset_.x(), p[1]->m_value + offset_.y(), p[2]->m_value + offset_.z()));
							}

							alignmentModel_->addAlignment(alignment3d);
						}
					}
				}
			}
		}
	}

	buw::ReferenceCounted<buw::HorizontalAlignment2D> createHorizontalAlignment(std::shared_ptr<OpenInfraPlatform::IfcAlignment::IfcAlignment> ifcAlignment)
	{
		buw::ReferenceCounted<buw::HorizontalAlignment2D> h = nullptr;

		if (ifcAlignment->m_Horizontal != nullptr)
		{
			if (ifcAlignment->m_Horizontal->m_StartDistAlong)
			{
				h = std::make_shared<buw::HorizontalAlignment2D>(ifcAlignment->m_Horizontal->m_StartDistAlong->m_value);
			}
			else
			{
				h = std::make_shared<buw::HorizontalAlignment2D>(0.0);
			}

			for (int i = 0; i < ifcAlignment->m_Horizontal->m_Segments.size(); i++)
			{
				buw::ReferenceCounted<IfcCurveSegment2D> curveSegment = ifcAlignment->m_Horizontal->m_Segments[i]->m_CurveGeometry;

				BLUE_ASSERT(curveSegment != nullptr, "Invalid horizontal segment.");

				if (strcmp("IfcLineSegment2D", curveSegment->classname()) == 0)
				{
					createHorizontalLine(curveSegment, h);
					continue;
				}

				if (strcmp("IfcCircularArcSegment2D", curveSegment->classname()) == 0)
				{
					createHorizontalArc(curveSegment, h);
					continue;
				}
	
				if (strcmp("IfcClothoidalArcSegment2D", curveSegment->classname()) == 0)
				{
					createHorizontalClothoid(curveSegment, h);
					continue;
				}
			}
		}
	
		return h;
	}

	void createHorizontalLine(buw::ReferenceCounted<IfcCurveSegment2D> curveSegment, buw::ReferenceCounted<buw::HorizontalAlignment2D> h)
	{
		buw::Vector2d start;
		buw::Vector2d end;

		buw::ReferenceCounted<IfcLineSegment2D> ifcLine = std::static_pointer_cast<IfcLineSegment2D>(curveSegment);

		buw::ReferenceCounted<IfcCartesianPoint> ifcStartPoint =
			std::static_pointer_cast<IfcCartesianPoint>(ifcLine->m_StartPoint);

		start.x() = ifcStartPoint->m_Coordinates[0]->m_value;
		start.y() = ifcStartPoint->m_Coordinates[1]->m_value;

		double segmentLength = ifcLine->m_SegmentLength->m_value;

		double startDirection = ifcLine->m_StartDirection->m_value;

		buw::Vector2d direction(1.0, 0.0);
		direction = buw::createRotationMatrix(startDirection) * direction;

		end = start + segmentLength * direction.block<2, 1>(0, 0);

		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line = std::make_shared<buw::HorizontalAlignmentElement2DLine>(start.block<2,1>(0,0) + offset_.block<2,1>(0,0), end + offset_.block<2,1>(0,0));
		h->addElement(line);
	}
	
	void createHorizontalArc(std::shared_ptr<IfcCurveSegment2D> curveSegment, buw::ReferenceCounted<buw::HorizontalAlignment2D> h)
	{
		buw::ReferenceCounted<IfcCircularArcSegment2D> ifcArc = std::static_pointer_cast<IfcCircularArcSegment2D>(curveSegment);

		// read given data
		const bool		clockWise		= !ifcArc->m_IsCcw->m_value;
		const double	radius			= ifcArc->m_Radius->m_value;
		const double	startDirection	= ifcArc->m_StartDirection->m_value;
		const double	segmentLength	= ifcArc->m_SegmentLength->m_value;

		buw::ReferenceCounted<IfcCartesianPoint> ifcStartPoint = ifcArc->m_StartPoint;
		buw::Vector2d start;
		start.x() = ifcStartPoint->m_Coordinates[0]->m_value;
		start.y() = ifcStartPoint->m_Coordinates[1]->m_value;
	
		// compute center point
		buw::Vector2d toCenter = buw::createRotationMatrix(startDirection + 0.5 * buw::constantsd::pi()) * buw::Vector2d(1.0, 0.0);
	
		if (clockWise)
		{
			toCenter = -toCenter;
		}

		buw::Vector2d center = start + toCenter.block<2,1>(0,0) * radius;

		// calculate angle between start end endpoint
		buw::radiand angle = segmentLength / radius;

		// compute end point
		buw::Vector2d end = buw::createRotationMatrix(angle) * (start - center) + center;

		if (clockWise)
		{
			end = buw::createRotationMatrix(-angle) * (start - center) + center;
		}

		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DArc> arc = std::make_shared<buw::HorizontalAlignmentElement2DArc>(
			center + offset_.block<2,1>(0,0),
			start + offset_.block<2,1>(0,0),
			end + offset_.block<2,1>(0,0),
			clockWise);
		h->addElement(arc);
	}

	void createHorizontalClothoid(buw::ReferenceCounted<IfcCurveSegment2D> curveSegment, buw::ReferenceCounted<buw::HorizontalAlignment2D> h)
	{
		buw::ReferenceCounted<IfcClothoidalArcSegment2D> ifcClothoid = std::static_pointer_cast<IfcClothoidalArcSegment2D>(curveSegment);

		BLUE_ASSERT(ifcClothoid->m_StartPoint != nullptr, "Invalid data.");
		BLUE_ASSERT(ifcClothoid->m_StartPoint->m_Coordinates[0] != nullptr, "Invalid data.");
		BLUE_ASSERT(ifcClothoid->m_StartPoint->m_Coordinates[1] != nullptr, "Invalid data.");
		BLUE_ASSERT(ifcClothoid->m_IsEntry != nullptr, "Invalid data.");
		BLUE_ASSERT(ifcClothoid->m_StartDirection != nullptr, "Invalid data.");
		BLUE_ASSERT(ifcClothoid->m_SegmentLength != nullptr, "Invalid data.");
		BLUE_ASSERT(ifcClothoid->m_IsCcw != nullptr, "Invalid data.");

		// read basic data
		buw::ReferenceCounted<IfcCartesianPoint> ifcStartPoint = ifcClothoid->m_StartPoint;

		buw::Vector2d start = buw::Vector2d(
			ifcStartPoint->m_Coordinates[0]->m_value,
			ifcStartPoint->m_Coordinates[1]->m_value)
			+ offset_.block<2,1>(0,0);

		const bool		isEntry				= ifcClothoid->m_IsEntry->m_value;
		const double	startDirection		= ifcClothoid->m_StartDirection->m_value;
		const double	length				= ifcClothoid->m_SegmentLength->m_value;
		const double	clothoidConstant	= ifcClothoid->m_ClothoidConstant->m_value;
		const bool		counterClockwise	= ifcClothoid->m_IsCcw->m_value;
		const bool		hasStartRadius		= ifcClothoid->m_StartRadius != nullptr ? true : false;
		

		double startCurvature = 0;
		if (hasStartRadius)
		{
			startCurvature = 1 / ifcClothoid->m_StartRadius->m_value;
		}

		buw::clothoidDescription desc(start,
			startDirection,
			startCurvature,
			counterClockwise,
			clothoidConstant,
			isEntry,
			length);
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> clothoid = std::make_shared<buw::HorizontalAlignmentElement2DClothoid>(desc);

		h->addElement(clothoid);
	}

	void createTerrainSurface(buw::ReferenceCounted<IfcTriangulatedFaceSet> triangluatedFaceSet)
	{
		buw::ReferenceCounted<buw::Surface> s = std::make_shared<buw::Surface>();

		// read position values
		for (int i = 0; i < triangluatedFaceSet->m_Coordinates->m_CoordList.size(); i++)
		{
			buw::Vector3d p;
				
			double x = triangluatedFaceSet->m_Coordinates->m_CoordList[i][0]->m_value;
			double y = triangluatedFaceSet->m_Coordinates->m_CoordList[i][1]->m_value;
			double z = triangluatedFaceSet->m_Coordinates->m_CoordList[i][2]->m_value;

			p = buw::Vector3d(x, y, z) + offset_;

			s->addPoint(p);
		}

		// read faces
		
		for (int i = 0; i < triangluatedFaceSet->m_CoordIndex.size(); i++)
		{
			buw::Vector3i indices;

			for (int k = 0; k < 3; k++)
			{
				indices[k] = triangluatedFaceSet->m_CoordIndex[i][k] - 1; // IFC Index start with 1 ... N
			}

			s->addTriangle(indices);
		}

		digitalElevationModel_->addSurface(s);
	}

	buw::ReferenceCounted<buw::VerticalAlignment2D> createVerticalAlignment(std::shared_ptr<OpenInfraPlatform::IfcAlignment::IfcAlignment> ifcAlignment)
	{
		buw::ReferenceCounted<buw::VerticalAlignment2D> v = nullptr;

		if (ifcAlignment->m_Vertical != nullptr)
		{
			v = std::make_shared<buw::VerticalAlignment2D>();

			for (int i = 0; i < ifcAlignment->m_Vertical->m_Segments.size(); i++)
			{
				shared_ptr<IfcAlignment2DVerticalSegment> vs = ifcAlignment->m_Vertical->m_Segments[i];

				BLUE_ASSERT(vs != nullptr, "Invalid vertical segment.");

				if (strcmp("IfcAlignment2DVerSegLine", vs->classname()) == 0)
				{
					createVerticalAlignmentLine(vs, v);
					continue;
				}
				
				if (strcmp("IfcAlignment2DVerSegParabolicArc", vs->classname()) == 0)
				{
					createVerticalAlignmentParabola(vs, v);
					continue;
				}

				if (strcmp("IfcAlignment2DVerSegCircularArc", vs->classname()) == 0)
				{
					createVerticalAlignmentArc(vs, v);
					continue;
				}
			}
		}

		return v;
	}

	void createVerticalAlignmentLine(shared_ptr<IfcAlignment2DVerticalSegment> vs, buw::ReferenceCounted<buw::VerticalAlignment2D> v)
	{
		std::shared_ptr<IfcAlignment2DVerSegLine> ifcLine = std::static_pointer_cast<IfcAlignment2DVerSegLine>(vs);

		BLUE_ASSERT(ifcLine->m_StartDistAlong != nullptr, "Invalid attribute");
		BLUE_ASSERT(ifcLine->m_HorizontalLength != nullptr, "Invalid attribute");
		BLUE_ASSERT(ifcLine->m_StartHeight != nullptr, "Invalid attribute");
		BLUE_ASSERT(ifcLine->m_StartGradient != nullptr, "Invalid attribute");

		const double startDistAlong = ifcLine->m_StartDistAlong->m_value;
		const double horizontalLength = ifcLine->m_HorizontalLength->m_value;
		const double startHeight = ifcLine->m_StartHeight->m_value;
		const double startGradient = ifcLine->m_StartGradient->m_value;

		buw::Vector2d a, b;
		a.x() = startDistAlong;
		a.y() = startHeight;

		b.x() = startDistAlong + horizontalLength;
		b.y() = horizontalLength * startGradient + startHeight;

		v->addElement(std::make_shared<buw::VerticalAlignmentElement2DLine>(a, b));
	}

	void createVerticalAlignmentParabola(shared_ptr<IfcAlignment2DVerticalSegment> vs, buw::ReferenceCounted<buw::VerticalAlignment2D> v)
	{
		std::shared_ptr<IfcAlignment2DVerSegParabolicArc> ifcLine = std::static_pointer_cast<IfcAlignment2DVerSegParabolicArc>(vs);
		
		BLUE_ASSERT(ifcLine->m_StartDistAlong != nullptr, "Invalid attribute");
		BLUE_ASSERT(ifcLine->m_HorizontalLength != nullptr, "Invalid attribute");
		BLUE_ASSERT(ifcLine->m_StartHeight != nullptr, "Invalid attribute");
		BLUE_ASSERT(ifcLine->m_StartGradient != nullptr, "Invalid attribute");
		BLUE_ASSERT(ifcLine->m_ParabolaConstant != nullptr, "Invalid attribute");
		BLUE_ASSERT(ifcLine->m_IsConvex != nullptr, "Invalid attribute");

		const double startDistAlong = ifcLine->m_StartDistAlong->m_value;
		const double horizontalLength = ifcLine->m_HorizontalLength->m_value;
		const double startHeight = ifcLine->m_StartHeight->m_value;
		const double startGradient = ifcLine->m_StartGradient->m_value;
		const double parabolaConstant = ifcLine->m_ParabolaConstant->m_value;
		const bool isConvex = ifcLine->m_IsConvex->m_value;

		double g1 = isConvex ? (horizontalLength / parabolaConstant) + startGradient : (horizontalLength / -parabolaConstant) + startGradient;
		double z1 = horizontalLength*(g1 + startGradient) / 2.0 + startHeight;

		buw::Vector2d a, b;
		a.x() = startDistAlong;
		a.y() = startHeight;

		b.x() = startDistAlong + horizontalLength;
		b.y() = z1;

		v->addElement(std::make_shared<buw::VerticalAlignmentElement2DParabola>(a, b, startGradient, g1));
	}

	void createVerticalAlignmentArc(shared_ptr<IfcAlignment2DVerticalSegment> vs, buw::ReferenceCounted<buw::VerticalAlignment2D> v)
	{
		std::shared_ptr<IfcAlignment2DVerSegCircularArc> ifcLine = std::static_pointer_cast<IfcAlignment2DVerSegCircularArc>(vs);

		BLUE_ASSERT(ifcLine->m_StartDistAlong != nullptr, "Invalid attribute");
		BLUE_ASSERT(ifcLine->m_HorizontalLength != nullptr, "Invalid attribute");
		BLUE_ASSERT(ifcLine->m_StartHeight != nullptr, "Invalid attribute");
		BLUE_ASSERT(ifcLine->m_StartGradient != nullptr, "Invalid attribute");
		BLUE_ASSERT(ifcLine->m_Radius != nullptr, "Invalid attribute");
		BLUE_ASSERT(ifcLine->m_IsConvex != nullptr, "Invalid attribute");

		const double startDistAlong = ifcLine->m_StartDistAlong->m_value;
		const double horizontalLength = ifcLine->m_HorizontalLength->m_value;
		const double startHeight = ifcLine->m_StartHeight->m_value;
		const double startGradient = ifcLine->m_StartGradient->m_value;
		const double radius = ifcLine->m_Radius->m_value;
		const bool isConvex = ifcLine->m_IsConvex->m_value;

		buw::Vector2d start;
		start.x() = startDistAlong;
		start.y() = startHeight;

		buw::Vector2d tocenter;
		tocenter.x() = startGradient;
		tocenter.y() = -1;
		tocenter = tocenter.normalized() * radius * (isConvex ? -1.0 : 1.0);

		buw::Vector2d center = start + tocenter;
		buw::Vector2d tostart = tocenter * -1.0;

		double x = horizontalLength - tocenter.x();

		double alpha1 = std::asin(tocenter.x() / radius);
		double alpha2 = std::asin(x / radius);
		double alpha = alpha1 + alpha2;

		if (!isConvex)
			alpha *= -1;

		buw::Vector2d toend;
		float s = std::sin(alpha);
		float c = std::cos(alpha);
		toend.x() = tostart.x() * c - tostart.y() * s;
		toend.y() = tostart.y() * c + tostart.x() * s;

		buw::Vector2d end = center + toend;

		v->addElement(std::make_shared<buw::VerticalAlignmentElement2DArc>(start, end, radius, startGradient, isConvex));

		/*i++;

		buw::Vector2d a, b;
		a.x() = startDistAlong;
		a.y() = startHeight;

		double alpha = std::atan(abs(startGradient));
		double beta = (M_PI / 2.0) - alpha;
		double x = horizontalLength;

		double x_1 = std::cos(beta) * radius;
		double y_1 = std::sin(beta) * radius;

		double x_2;
		if (i != 4)
			x_2 = x - x_1;
		else
			x_2 = x + x_1;

		double y_2 = std::sqrt(std::pow(radius,2) - std::pow(x_2, 2));

		double y;
		if (i != 4)
			y = y_2 - y_1;
		else
			y = y_1 - y_2;


		b = a;
		b.x() += x;
		if (startGradient > 0)
			b.y() += y;
		else
			b.y() -= y;

		v->addElement(std::make_shared<buw::VerticalAlignmentElement2DArc>(a, b, radius, startGradient, isConvex));*/
	}

private:
	buw::Vector3d									offset_;
};
	
OpenInfraPlatform::Infrastructure::ImportIfcAlignment1x0::ImportIfcAlignment1x0(
 	const std::string& filename) :
	Import(filename),
	impl_(new ImportIfcAlignmenImpl(filename))
{
	alignmentModel_ = impl_->getAlignmentModel();
	digitalElevationModel_ = impl_->getDigitalElevationModel();
}