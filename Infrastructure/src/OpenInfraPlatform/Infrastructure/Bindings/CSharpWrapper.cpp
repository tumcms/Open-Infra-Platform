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

// see also: http://tirania.org/blog/archive/2011/Dec-19.html

#include "CSharpWrapper.h"

#include "OpenInfraPlatform/Infrastructure/Import/ImportLandXml.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment2DBased3D.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid.h"
#include "OpenInfraPlatform/Infrastructure/DigitalElevationModel/DigitalElevationModel.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/AlignmentModel.h"

extern "C" 
{
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// LandXml Parser
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	BLUEINFRASTRUCTURE_API buw::ImportLandXml* LandXmlParser_Create(char* fileName)
	{
		buw::ImportLandXml* parser = new buw::ImportLandXml(fileName);
		return parser;
	}

	BLUEINFRASTRUCTURE_API buw::DigitalElevationModel* LandXmlParser_GetDigitalElevationModel(buw::ImportLandXml* p)
	{
		buw::DigitalElevationModel* digitalElevationModel = p->getDigitalElevationModel().get();
		buw::DigitalElevationModel *dm = buw::DigitalElevationModel::createFlatCopy(*digitalElevationModel);
		return dm;
	}

	BLUEINFRASTRUCTURE_API buw::AlignmentModel* LandXmlParser_GetAlignmentModel(buw::ImportLandXml* p)
	{
		buw::AlignmentModel* alignmentModel = p->getAlignmentModel().get();
		buw::AlignmentModel *a = buw::AlignmentModel::createFlatCopy(*alignmentModel);
		return a;
	}

	BLUEINFRASTRUCTURE_API buw::Vector3d LandXmlParser_GetModelCenter(buw::ImportLandXml* p)
	{
		buw::Vector3d minPos;
		buw::Vector3d maxPos;

		buw::DigitalElevationModel* digitalElevationModel = LandXmlParser_GetDigitalElevationModel(p);
		buw::AlignmentModel* alignmentModel = LandXmlParser_GetAlignmentModel(p);

		digitalElevationModel->getSurfacesExtend(minPos, maxPos);

		if (alignmentModel->getAlignmentCount() > 0)
		{
			auto aabb = alignmentModel->getExtends();

			if (digitalElevationModel->getSurfaceCount() > 0)
			{
				minPos = buw::minimizedVector(minPos, aabb.getMinimum());
				maxPos = buw::minimizedVector(maxPos, aabb.getMaximum());
			}
			else
			{
				minPos = aabb.getMinimum();
				maxPos = aabb.getMaximum();
			}
		}

		buw::Vector3d offsetViewArea = minPos + 0.5 * (maxPos - minPos);

		return offsetViewArea;
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// AlignmentModel
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	BLUEINFRASTRUCTURE_API int AlignmentModel_AlignmentsCount(buw::AlignmentModel* a)
	{
		return a->getAlignmentCount();
	}

	BLUEINFRASTRUCTURE_API buw::Alignment2DBased3D* AlignmentModel_GetAlignmentByIndex(buw::AlignmentModel* a, int index)
	{
		buw::ReferenceCounted<buw::IAlignment3D> alignment3d = a->getAlignments()[index];

		if (alignment3d->getType() == buw::e3DAlignmentType::e2DBased)
		{
			buw::ReferenceCounted<buw::Alignment2DBased3D> a = std::static_pointer_cast<buw::Alignment2DBased3D>(alignment3d);

			buw::Alignment2DBased3D *ap = buw::Alignment2DBased3D::createFlatCopy(*a.get());

			return ap;
		}

		return nullptr;
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// DigitalElevationModel
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	BLUEINFRASTRUCTURE_API int DigitalElevationModel_SurfaceCount(buw::DigitalElevationModel* d)
	{
		return d->getSurfaceCount();
	}

	BLUEINFRASTRUCTURE_API buw::Surface* DigitalElevationModel_GetSurface(buw::DigitalElevationModel* d, int index)
	{
		buw::ReferenceCounted<buw::Surface> surface = d->getSurface(index);
		buw::Surface *s = buw::Surface::createFlatCopy(*surface.get());

		return s;
	}

	BLUEINFRASTRUCTURE_API double DigitalElevationModel_getHeightAtPosition(buw::DigitalElevationModel* d, double x, double y)
	{
		return d->getHeightAtPosition(buw::Vector2d(x, y));
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Surface
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	BLUEINFRASTRUCTURE_API int Surface_GetPointsCount(buw::Surface* s)
	{
		return s->getPointCount();
	}

	BLUEINFRASTRUCTURE_API int Surface_GetFaceCount(buw::Surface* s)
	{
		return s->getTriangleCount();
	}

	BLUEINFRASTRUCTURE_API buw::Vector3d Surface_GetPoint(buw::Surface* s, int index)
	{
		return s->getPoints()[index];
	}

	BLUEINFRASTRUCTURE_API buw::Vector3d Surface_GetFace(buw::Surface* s, int index)
	{
		return buw::Vector3d(
			s->getTriangeFaces()[index][0], 
			s->getTriangeFaces()[index][1], 
			s->getTriangeFaces()[index][2]
		);
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Alignment
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	BLUEINFRASTRUCTURE_API buw::Alignment2DBased3D* Alignment2DBased3D_Create()
	{
		buw::ImportLandXml parser("C:/Users/Dominic/Desktop/Studium/MA4/Master-Thesis/Implementierung/OpenInfraPlatform/testdata/LandXML/Mainbruecke_Klingenberg.xml");

		buw::ReferenceCounted<buw::IAlignment3D> alignment3d = parser.getAlignmentModel()->getAlignments()[0];
		
		if (alignment3d->getType() == buw::e3DAlignmentType::e2DBased)
		{
			buw::ReferenceCounted<buw::Alignment2DBased3D> a = std::static_pointer_cast<buw::Alignment2DBased3D>(alignment3d);

			buw::Alignment2DBased3D *ap = buw::Alignment2DBased3D::createFlatCopy(*a.get());
		
			return ap;
		}

		return nullptr;
	}

	BLUEINFRASTRUCTURE_API void Alignment2DBased3D_Destroy(buw::Alignment2DBased3D* a)
	{
		delete a;
	}

	BLUEINFRASTRUCTURE_API double Alignment2DBased3D_getStartStation(buw::Alignment2DBased3D* a)
	{
		return a->getStartStation();
	}

	BLUEINFRASTRUCTURE_API double Alignment2DBased3D_getEndStation(buw::Alignment2DBased3D* a)
	{
		return a->getEndStation();
	}

	BLUEINFRASTRUCTURE_API buw::Vector3d Alignment2DBased3D_getPosition(buw::Alignment2DBased3D* a, double station)
	{
		
		return a->getPosition(station);
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// HorizontalAlignmentElement2DLine
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	BLUEINFRASTRUCTURE_API buw::HorizontalAlignmentElement2DLine* HorizontalAlignmentElement2DLine_Create()
	{
		buw::Vector2d start(0, 0);
		buw::Vector2d endP(1, 0);

		buw::HorizontalAlignmentElement2DLine* line = new buw::HorizontalAlignmentElement2DLine(start, endP);

		return line;
	}

	BLUEINFRASTRUCTURE_API void HorizontalAlignmentElement2DLine_Destroy(buw::HorizontalAlignmentElement2DLine *p)
	{
		delete p;
	}

	BLUEINFRASTRUCTURE_API double HorizontalAlignmentElement2DLine_getLength(buw::HorizontalAlignmentElement2DLine *p)
	{
		return p->getLength();
	}

	BLUEINFRASTRUCTURE_API buw::Vector2d HorizontalAlignmentElement2DLine_getPositon(buw::HorizontalAlignmentElement2DLine *p, double lerpParameter)
	{
		return p->getPosition(lerpParameter);
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// HorizontalAlignmentElement2DClothoid
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	BLUEINFRASTRUCTURE_API buw::HorizontalAlignmentElement2DClothoid* HorizontalAlignmentElement2DClothoid_Create()
	{ 
		buw::Vector2d start = buw::Vector2d(861.369007, 537.722476);
		buw::Vector2d end	= buw::Vector2d(930.775243, 503.483954);
		buw::Vector2d pi	= buw::Vector2d(896.290146, 516.54507);
		
		double length		= 77.500241;
		double radiusStart	= 500;
		double radiusEnd	= 367;
		bool clockwise		= false;

		/*<Spiral length="77.500241" radiusEnd="367.000000" radiusStart="500.000000" rot="ccw" spiType="clothoid" constant="326.996979" dirEnd="4.3503375925" dirStart="4.1672511921" theta="0.1830864004" totalY="7.435685" totalX="-77.033840" staStart="628.971429" tanLong="40.840770" tanShort="36.875665">
			<Start>5333537.722476 4467861.369007</Start>
			<PI>5333516.54507 4467896.290146</PI>
			<End>5333503.483954 </End>
			</Spiral>*/

		double startCurvature = 0;
		if (radiusStart != 0 || radiusStart != std::numeric_limits<double>::infinity())
			startCurvature = 1 / radiusStart;

		double endCurvature = 0;
		if (radiusEnd != 0 || radiusEnd != std::numeric_limits<double>::infinity())
			endCurvature = 1 / radiusEnd;

		double startDirection = buw::HorizontalAlignmentElement2DClothoid::computeStartDirection(start, pi);
		double clothoidConstant = buw::HorizontalAlignmentElement2DClothoid::computeClothoidConstant(length, startCurvature, endCurvature);
		bool entry = buw::HorizontalAlignmentElement2DClothoid::computeEntry(startCurvature, endCurvature);

		buw::clothoidDescription desc(start, startDirection, startCurvature, !clockwise, clothoidConstant, entry, length);
		buw::HorizontalAlignmentElement2DClothoid* clothoid = new buw::HorizontalAlignmentElement2DClothoid(desc);

		return clothoid; 
	}

	BLUEINFRASTRUCTURE_API void HorizontalAlignmentElement2DClothoid_Destroy(buw::HorizontalAlignmentElement2DClothoid *p)
	{ 
		delete p; 
	}

	BLUEINFRASTRUCTURE_API buw::Vector2d HorizontalAlignmentElement2DClothoid_getPosition(buw::HorizontalAlignmentElement2DClothoid *p, double lerpParameter)
	{
		return p->getPosition(lerpParameter);
	}

	BLUEINFRASTRUCTURE_API double HorizontalAlignmentElement2DClothoid_getLength(buw::HorizontalAlignmentElement2DClothoid *p)
	{
		return p->getLength();
	}
}; // end extern "C"
