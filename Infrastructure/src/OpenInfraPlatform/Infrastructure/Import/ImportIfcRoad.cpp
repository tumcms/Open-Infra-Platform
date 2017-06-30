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

#include "ImportIfcRoad.h"

#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DArc.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DParabola.h"

#include "OpenInfraPlatform/IfcRoad/model/IfcRoadModel.h"
#include "OpenInfraPlatform/IfcRoad/model/IfcRoadException.h"
#include "OpenInfraPlatform/IfcRoad/reader/IfcStepReader.h"
#include "OpenInfraPlatform/IfcRoad/writer/IfcStepWriter.h"
#include "OpenInfraPlatform/IfcRoad/IfcRoadEntities.h"
#include "OpenInfraPlatform/IfcRoad/IfcRoadTypes.h"
#include "OpenInfraPlatform/IfcRoad/model/IfcRoadModel.h"
#include "OpenInfraPlatform/IfcRoad/model/IfcRoadException.h"
#include "OpenInfraPlatform/IfcRoad/reader/IfcStepReader.h"
#include "OpenInfraPlatform/IfcRoad/reader/IfcRoadReader.h"
#include "OpenInfraPlatform/IfcRoad/reader/IfcStepReader.h"
#include "OpenInfraPlatform/IfcRoad/model/UnitConverter.h"
#include "OpenInfraPlatform/IfcRoad/entity/include/IfcCartesianPoint.h"
#include "OpenInfraPlatform/IfcRoad/IfcRoadEntityEnums.h"

#include <BlueFramework/Core/Exception.h>
#include <fstream>

using namespace OpenInfraPlatform::IfcRoad;

class OpenInfraPlatform::Infrastructure::ImportIfcRoad::IfcRoadImportImpl : public Import
{
public:
	std::map<int, shared_ptr<IfcRoadEntity> > map_entities;

	IfcRoadImportImpl(const std::string& filename) :
		Import(filename)
	{
		const bool importTerrain = true;
		const bool importAlignment = true;
		
		shared_ptr<IfcStepReader> m_step_reader = shared_ptr<IfcStepReader>(new IfcStepReader());
		shared_ptr<IfcRoadModel> m_ifc_model(new IfcRoadModel());

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
		
		try
		{
			m_step_reader->readStreamData(buffer, map_entities);
		}
		catch (IfcRoadException& e)
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
			if (importAlignment)
			{
				if (it->second->m_entity_enum == IFCALIGNMENT)
				{
					std::shared_ptr<OpenInfraPlatform::IfcRoad::IfcAlignment> alignment = 
						std::static_pointer_cast<OpenInfraPlatform::IfcRoad::IfcAlignment>(it->second);
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

	shared_ptr<OpenInfraPlatform::IfcRoad::IfcRoad> findIfcRoadElement()
	{
		for (auto it = map_entities.begin(); it != map_entities.end(); it++)
		{
			
				if (it->second->m_entity_enum == IFCROAD)
				{
					std::shared_ptr<OpenInfraPlatform::IfcRoad::IfcRoad> road =
						std::static_pointer_cast<OpenInfraPlatform::IfcRoad::IfcRoad>(it->second);
					return road;
				}
		}

		return nullptr;
	}

	void createAlignment(std::shared_ptr<OpenInfraPlatform::IfcRoad::IfcAlignment> ifcAlignment)
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

		// load corresponding IfcRoad element

		auto road = findIfcRoadElement();

		if (road != nullptr)
		{
			for (int i = 0; i < road->m_Body->m_CrossSections.size(); i++)
			{
				auto cs = road->m_Body->m_CrossSections[i];

				buw::ReferenceCounted<buw::CrossSectionStatic> css = std::make_shared<buw::CrossSectionStatic>();
				alignment->addCrossSection(css);
				css->stationing = cs->m_Station->m_value;

				for (int pi = 0; pi < cs->m_Geometry->m_Geometry.size(); pi++)
				{
					auto polyline = cs->m_Geometry->m_Geometry[pi];

					buw::ReferenceCounted<buw::DesignCrossSectionProfile> dcs = std::make_shared<buw::DesignCrossSectionProfile>();

					for (int k = 0; k < polyline->m_Points.size(); k++)
					{
						buw::ReferenceCounted<buw::CrossSectionPoint> point = std::make_shared<buw::CrossSectionPoint>();

						buw::Vector2d start;
						start.x() = polyline->m_Points[k]->m_Coordinates[0]->m_value;
						start.y() = polyline->m_Points[k]->m_Coordinates[1]->m_value;

						point->position = start;

						dcs->crossSectionsPoints.push_back(point);
						
					}

					css->addDesignCrossSectionProfile(dcs);
				}
			}
		}
	}

	buw::ReferenceCounted<buw::HorizontalAlignment2D> createHorizontalAlignment(std::shared_ptr<OpenInfraPlatform::IfcRoad::IfcAlignment> ifcAlignment)
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
				std::shared_ptr<IfcCurveSegment2D> curveSegment = ifcAlignment->m_Horizontal->m_Segments[i]->m_CurveGeometry;

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

	void createHorizontalLine(std::shared_ptr<IfcCurveSegment2D> curveSegment, buw::ReferenceCounted<buw::HorizontalAlignment2D> h)
	{
		buw::Vector2d start;
		buw::Vector2d end;

		std::shared_ptr<IfcLineSegment2D> ifcLine =	std::static_pointer_cast<IfcLineSegment2D>(curveSegment);

		std::shared_ptr<IfcCartesianPoint> ifcStartPoint =
			std::static_pointer_cast<IfcCartesianPoint>(ifcLine->m_StartPoint);

		start.x() = ifcStartPoint->m_Coordinates[0]->m_value;
		start.y() = ifcStartPoint->m_Coordinates[1]->m_value;

		double segmentLength = ifcLine->m_SegmentLength->m_value;

		double startDirection = ifcLine->m_StartDirection->m_value;

		buw::Vector2d direction(1.0, 0.0);
		direction = buw::createRotationMatrix(startDirection) * direction;

		end = start + segmentLength * direction;

		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line = std::make_shared<buw::HorizontalAlignmentElement2DLine>(start.block<2, 1>(0, 0) + offset_.block<2, 1>(0, 0), end + offset_.block<2, 1>(0, 0));
		h->addElement(line);
	}
	
	void createHorizontalArc(std::shared_ptr<IfcCurveSegment2D> curveSegment, buw::ReferenceCounted<buw::HorizontalAlignment2D> h)
	{
		std::shared_ptr<IfcCircularArcSegment2D> ifcArc = std::static_pointer_cast<IfcCircularArcSegment2D>(curveSegment);

		// read given data
		const bool		clockWise		= !ifcArc->m_IsCcw->m_value;
		const double	radius			= ifcArc->m_Radius->m_value;
		const double	startDirection	= ifcArc->m_StartDirection->m_value;
		const double	segmentLength	= ifcArc->m_SegmentLength->m_value;

		std::shared_ptr<IfcCartesianPoint> ifcStartPoint = ifcArc->m_StartPoint;
		buw::Vector2d start;
		start.x() = ifcStartPoint->m_Coordinates[0]->m_value;
		start.y() = ifcStartPoint->m_Coordinates[1]->m_value;
	
		// compute center point
		buw::Vector2d toCenter = buw::createRotationMatrix(startDirection + 0.5 * buw::constantsd::pi()) * buw::Vector2d(1.0, 0.0);
	
		if (clockWise)
		{
			toCenter = -toCenter;
		}

		buw::Vector2d center = start + toCenter.block<2, 1>(0, 0) * radius;

		// calculate angle between start end endpoint
		buw::radiand angle = segmentLength / radius;

		// compute end point
		buw::Vector2d end = buw::createRotationMatrix(angle) * (start - center) + center;

		if (clockWise)
		{
			end = buw::createRotationMatrix(-angle) * (start - center) + center;
		}

		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DArc> arc = std::make_shared<buw::HorizontalAlignmentElement2DArc>(
			center + offset_.block<2, 1>(0, 0),
			start + offset_.block<2, 1>(0, 0),
			end + offset_.block<2, 1>(0, 0),
			clockWise);
		h->addElement(arc);
	}

	void createHorizontalClothoid(std::shared_ptr<IfcCurveSegment2D> curveSegment, buw::ReferenceCounted<buw::HorizontalAlignment2D> h)
	{
		std::shared_ptr<IfcClothoidalArcSegment2D> ifcClothoid = std::static_pointer_cast<IfcClothoidalArcSegment2D>(curveSegment);

		BLUE_ASSERT(ifcClothoid->m_StartPoint != nullptr, "Invalid data.");
		BLUE_ASSERT(ifcClothoid->m_StartPoint->m_Coordinates[0] != nullptr, "Invalid data.");
		BLUE_ASSERT(ifcClothoid->m_StartPoint->m_Coordinates[1] != nullptr, "Invalid data.");
		BLUE_ASSERT(ifcClothoid->m_IsEntry != nullptr, "Invalid data.");
		BLUE_ASSERT(ifcClothoid->m_StartDirection != nullptr, "Invalid data.");
		BLUE_ASSERT(ifcClothoid->m_SegmentLength != nullptr, "Invalid data.");
		BLUE_ASSERT(ifcClothoid->m_IsCcw != nullptr, "Invalid data.");

		// read basic data
		std::shared_ptr<IfcCartesianPoint> ifcStartPoint =	ifcClothoid->m_StartPoint;

		buw::Vector2d start = buw::Vector2d(
			ifcStartPoint->m_Coordinates[0]->m_value,
			ifcStartPoint->m_Coordinates[1]->m_value
		);
		const bool		isEntry				= ifcClothoid->m_IsEntry->m_value;
		const double	startDirection		= ifcClothoid->m_StartDirection->m_value;
		const double	length				= ifcClothoid->m_SegmentLength->m_value;
		const double	clothoidConstant	= ifcClothoid->m_ClothoidConstant->m_value;
		const bool		counterClockwise	= ifcClothoid->m_IsCcw->m_value;
		const bool		hasStartRadius		= ifcClothoid->m_StartRadius != nullptr ? true : false;

		//---------------------------------------------------------------------------------------
		// compute start radius
		double startCurvature = 0;
		 
		if (hasStartRadius)
		{
			startCurvature = 1 / ifcClothoid->m_StartRadius->m_value;
		}

		//---------------------------------------------------------------------------------------
		buw::clothoidDescription desc(start + offset_.block<2, 1>(0, 0),
			startDirection,
			startCurvature,
			counterClockwise,
			clothoidConstant,
			isEntry,
			length);
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> clothoid = std::make_shared<buw::HorizontalAlignmentElement2DClothoid>(desc);

		h->addElement(clothoid);
	}

	void createTerrainSurface(std::shared_ptr<IfcTriangulatedFaceSet> triangluatedFaceSet)
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
				indices[k] = triangluatedFaceSet->m_CoordIndex[i][k];
			}

			s->addTriangle(indices);
		}

		digitalElevationModel_->addSurface(s);
	}

	buw::ReferenceCounted<buw::VerticalAlignment2D> createVerticalAlignment(std::shared_ptr<OpenInfraPlatform::IfcRoad::IfcAlignment> ifcAlignment)
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
private:
	buw::Vector3d									offset_;
};
	
OpenInfraPlatform::Infrastructure::ImportIfcRoad::ImportIfcRoad(
 	const std::string& filename) :
	Import(filename),
impl_(new IfcRoadImportImpl(filename))
{
	alignmentModel_ = impl_->getAlignmentModel();
	digitalElevationModel_ = impl_->getDigitalElevationModel();
}