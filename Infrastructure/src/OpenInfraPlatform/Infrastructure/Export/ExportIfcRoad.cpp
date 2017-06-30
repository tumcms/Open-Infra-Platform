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

#include "ExportIfcRoad.h"

#include "OpenInfraPlatform/IfcRoad/guid/CreateGuid_64.h"
#include "OpenInfraPlatform/IfcRoad/model/IfcRoadModel.h"
#include "OpenInfraPlatform/IfcRoad/model/IfcRoadException.h"
#include "OpenInfraPlatform/IfcRoad/model/IfcRoadModel.h"
#include "OpenInfraPlatform/IfcRoad/model/IfcRoadException.h"
#include "OpenInfraPlatform/IfcRoad/model/UnitConverter.h"
#include "OpenInfraPlatform/IfcRoad/IfcRoadTypes.h"
#include "OpenInfraPlatform/IfcRoad/IfcRoadEntities.h"
#include "OpenInfraPlatform/IfcRoad/IfcRoadEntityEnums.h"
#include "OpenInfraPlatform/IfcRoad/reader/IfcStepReader.h"
#include "OpenInfraPlatform/IfcRoad/reader/IfcRoadReader.h"
#include "OpenInfraPlatform/IfcRoad/writer/IfcStepWriter.h"
                                   
#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment3DBased3D.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DParabola.h"

#include <fstream>

using namespace OpenInfraPlatform::IfcRoad;

class OpenInfraPlatform::Infrastructure::ExportIfcRoad::IfcRoadExportImpl : public Export
{
public:
	IfcRoadExportImpl(const IfcRoadExportDescription& desc, buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename) :
		Export(am, dem, filename),
		entityId_(1),
		model_(nullptr)
	{
		// create model
		model_ = buw::ReferenceCounted<IfcRoadModel>(new IfcRoadModel());

		settings_ = desc;

		try
		{
			// Person, Organization, Application
			buw::ReferenceCounted<IfcPerson> person = createIfcPerson();
			buw::ReferenceCounted<IfcOrganization> organization = createIfcOrganization();
			buw::ReferenceCounted<IfcApplication> application = createIfcApplication(organization);

			auto personAndOrganization = createIfcPersonAndOrganization(person, organization);

			buw::ReferenceCounted<IfcOwnerHistory> ownerHistory = createIfcOwnerHistory(personAndOrganization, application);

			zeroDimExp_ = std::make_shared<IfcDimensionalExponents>(createEntityId());
			zeroDimExp_->m_LengthExponent = 0;
			zeroDimExp_->m_MassExponent = 0;
			zeroDimExp_->m_TimeExponent = 0;
			zeroDimExp_->m_ElectricCurrentExponent = 0;
			zeroDimExp_->m_ThermodynamicTemperatureExponent = 0;
			zeroDimExp_->m_AmountOfSubstanceExponent = 0;
			zeroDimExp_->m_LuminousIntensityExponent = 0;
			model_->insertEntity(zeroDimExp_);

			// create project
			buw::ReferenceCounted<IfcProject> project = std::make_shared<IfcProject>(createEntityId());
			project->m_GlobalId = createGlobalId();
			project->m_Name = std::make_shared<IfcLabel>("IfcRoad Project");
			project->m_UnitsInContext = createIfcUnitAssignment();	// Units
			project->m_OwnerHistory = ownerHistory;
			model_->insertEntity(project);

			// create site
			buw::ReferenceCounted<IfcAxis2Placement3D> site_axisPlacement = createIfcAxis2Placement3D(createIfcCartesianPoint(0, 0, 0));
			buw::ReferenceCounted<IfcLocalPlacement> site_localPlacement = createIfcLocalPlacement(site_axisPlacement);

			buw::ReferenceCounted<IfcSite> site = std::make_shared<IfcSite>(createEntityId());
			site->m_GlobalId = createGlobalId();
			site->m_OwnerHistory = nullptr;// ownerHistory;
			site->m_Description = std::make_shared<IfcText>("My description.");
			site->m_Name = std::make_shared<IfcLabel>("Terrain surface");
			site->m_ObjectPlacement = site_localPlacement;
			model_->insertEntity(site);

			// create map conversion
			buw::ReferenceCounted<IfcProjectedCRS> projectedCRS = std::make_shared<IfcProjectedCRS>(createEntityId());
			model_->insertEntity(projectedCRS);
			projectedCRS->m_Name = std::make_shared<IfcLabel>("EPSG:31467"); // todo get EPSG code from Gauß-Krueger coordinates
			projectedCRS->m_Description = std::make_shared<IfcText>("EPSG:31467 - DHDN / 3-Degree Gauss-Krueger Zone 3");
			projectedCRS->m_GeodeticDatum = std::make_shared<IfcIdentifier>("EPSG:31467");
			projectedCRS->m_MapProjection = std::make_shared<IfcIdentifier>("Gauss-Krueger");
			projectedCRS->m_MapZone = std::make_shared<IfcIdentifier>("3");

			buw::ReferenceCounted<IfcSIUnit> lengthUnit = std::make_shared<IfcSIUnit>(createEntityId());
			model_->insertEntity(lengthUnit);
			lengthUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_LENGTHUNIT);
			lengthUnit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_METRE);

			projectedCRS->m_MapUnit = lengthUnit;

			buw::Vector3d centerOffset;
			if (alignmentModel_->getAlignmentCount() > 0)
				centerOffset = alignmentModel_->getAlignment(0)->getPosition(0);
			else
				centerOffset = digitalElevationModel_->getCenterPoint();

			// connect site and project with IfcRelAggregates
			buw::ReferenceCounted<IfcRelAggregates> connection = std::make_shared<IfcRelAggregates>(createEntityId());
			model_->insertEntity(connection);
			connection->m_GlobalId = createGlobalId();
			connection->m_OwnerHistory = nullptr; // ownerHistory;
			connection->m_RelatingObject = project;
			connection->m_RelatedObjects.push_back(site);

			buw::ReferenceCounted<IfcRelContainedInSpatialStructure> c2 = std::make_shared<IfcRelContainedInSpatialStructure>(createEntityId());
			model_->insertEntity(c2);
			c2->m_GlobalId = createGlobalId();
			c2->m_OwnerHistory = nullptr; // ownerHistory;
			c2->m_RelatingStructure = site;

			buw::ReferenceCounted<IfcMapConversion> mapConversion = std::make_shared<IfcMapConversion>(createEntityId());
			model_->insertEntity(mapConversion);
			//mapConversion->m_SourceCRS = 
			mapConversion->m_TargetCRS = projectedCRS;
			mapConversion->m_Eastings = std::make_shared<IfcLengthMeasure>(centerOffset.x());
			mapConversion->m_Northings = std::make_shared<IfcLengthMeasure>(centerOffset.y());
			mapConversion->m_OrthogonalHeight = std::make_shared<IfcLengthMeasure>(centerOffset.z());

			buw::ReferenceCounted<IfcGeometricRepresentationContext> geometricRepresentationContext = std::make_shared<IfcGeometricRepresentationContext>(createEntityId());

			geometricRepresentationContext->m_ContextIdentifier = nullptr;// std::make_shared<IfcLabel>("Body");
			geometricRepresentationContext->m_ContextType = std::make_shared<IfcLabel>("Model");
			geometricRepresentationContext->m_CoordinateSpaceDimension = std::make_shared<IfcDimensionCount>(3);
			geometricRepresentationContext->m_WorldCoordinateSystem = site_axisPlacement;
			geometricRepresentationContext->m_Precision = std::make_shared<IfcReal>(1e-5);
			model_->insertEntity(geometricRepresentationContext);
			mapConversion->m_SourceCRS = geometricRepresentationContext;

			project->m_RepresentationContexts.push_back(geometricRepresentationContext);

			if (desc.exportTerrain)
			{
				exportTerrain(digitalElevationModel_, centerOffset, geometricRepresentationContext, c2);
			}

			// export alignments
			if (desc.exportAlignment)
			{
				for (int ai = 0; ai < alignmentModel_->getAlignmentCount(); ai++)
				{
					buw::ReferenceCounted<buw::IAlignment3D> alignment3D = alignmentModel_->getAlignment(ai);
					if (alignment3D->getType() == buw::e3DAlignmentType::e3DBased)
					{
						// marker
						if (subcontextAxis == nullptr)
						{
							subcontextAxis = std::make_shared<IfcGeometricRepresentationSubContext>(createEntityId());
							model_->insertEntity(subcontextAxis);
							subcontextAxis->m_ContextIdentifier = std::make_shared<IfcLabel>("Axis");
							subcontextAxis->m_ContextType = std::make_shared<IfcLabel>("Model");
							subcontextAxis->m_CoordinateSpaceDimension = std::make_shared<IfcDimensionCount>(3);
							subcontextAxis->m_WorldCoordinateSystem = site_axisPlacement;
							subcontextAxis->m_ParentContext = geometricRepresentationContext;
							subcontextAxis->m_TargetView = std::make_shared<IfcGeometricProjectionEnum>(IfcGeometricProjectionEnum::ENUM_MODEL_VIEW);
							subcontextAxis->m_Precision = std::make_shared<IfcReal>(1e-5);
						}

						buw::ReferenceCounted<OpenInfraPlatform::IfcRoad::IfcAlignment> ifcAlignment =
							std::make_shared<OpenInfraPlatform::IfcRoad::IfcAlignment>(createEntityId());
						model_->insertEntity(ifcAlignment);

						ifcAlignment->m_GlobalId = createGlobalId();

						// set name of alignment
						std::string name = alignment3D->getName().toStdString();
						ifcAlignment->m_Description = std::make_shared<IfcText>(name);

						buw::ReferenceCounted<IfcCartesianPointList3D> pointList = std::make_shared<IfcCartesianPointList3D>(createEntityId());
						model_->insertEntity(pointList);

						buw::ReferenceCounted<buw::Alignment3DBased3D> alignment = std::static_pointer_cast<buw::Alignment3DBased3D>(alignment);

						for (double s = alignment->getStartStation(); s < alignment->getEndStation(); s += 1.0)
						{
							auto position = alignment->getPosition(s) - centerOffset;

							std::vector<buw::ReferenceCounted<IfcLengthMeasure>> coordinates;
							for (int i = 0; i < 3; i++)
							{
								coordinates.push_back(std::make_shared<IfcLengthMeasure>(position[i]));
							}

							pointList->m_CoordList.push_back(coordinates);
						}

						buw::ReferenceCounted<IfcIndexedPolyCurve> indexedPolyCurve = std::make_shared<IfcIndexedPolyCurve>(createEntityId());
						model_->insertEntity(indexedPolyCurve);
						indexedPolyCurve->m_SelfIntersect = buw::ReferenceCounted<IfcBoolean>(false);
						indexedPolyCurve->m_Points = pointList;

						std::vector<buw::ReferenceCounted<IfcRepresentation>> representation;
						std::vector<buw::ReferenceCounted<IfcRepresentationItem>> representationItems;
						representationItems.push_back(indexedPolyCurve);
						representation.push_back(createIfcShapeRepresentation(representationItems, geometricRepresentationContext, "Axis", "Curve3D"));
						auto sr = createIfcProductDefinitionShape(representation);

						ifcAlignment->m_Representation = sr;
					}
					else
					{
						buw::ReferenceCounted<Alignment2DBased3D> alignment = std::static_pointer_cast<buw::Alignment2DBased3D>(alignment3D);

						buw::ReferenceCounted<OpenInfraPlatform::IfcRoad::IfcAlignment> ifcAlignment =
							std::make_shared<OpenInfraPlatform::IfcRoad::IfcAlignment>(createEntityId());
						model_->insertEntity(ifcAlignment);
						ifcAlignment->m_GlobalId = createGlobalId();

						// set name of alignment
						std::string name = alignment->getName().toStdString();
						ifcAlignment->m_Description = std::make_shared<IfcText>(name);

						convertHorizontalAlignment(ifcAlignment, alignment, centerOffset);

						convertVerticalAlignment(alignment, ifcAlignment);

						// connect ifcAlignment with site
						c2->m_RelatedElements.push_back(ifcAlignment);

						// export static cross sections
						int numberOfAlignmentCrossSections = alignment->getCrossSectionCount();

						if (numberOfAlignmentCrossSections > 0)
						{
							buw::ReferenceCounted<IfcRoadBody> roadBody = std::make_shared<IfcRoadBody>(createEntityId());
							model_->insertEntity(roadBody);

							buw::ReferenceCounted<OpenInfraPlatform::IfcRoad::IfcRoad> road = std::make_shared<OpenInfraPlatform::IfcRoad::IfcRoad>(createEntityId());
							model_->insertEntity(road);
							road->m_Body = roadBody;
							road->m_Alignment = ifcAlignment;

							for (int csIndex = 0; csIndex < numberOfAlignmentCrossSections; csIndex++) //iterate through all CrossSections of alignment
							{
								buw::ReferenceCounted<buw::CrossSectionStatic> cs = alignment->getCrossSection(csIndex);
								//exportCrossSection(alignment, cs, centerOffset);

								buw::ReferenceCounted<IfcCrossSectionStatic> crossSectionStatic = std::make_shared<IfcCrossSectionStatic>(createEntityId());
								model_->insertEntity(crossSectionStatic);

								roadBody->m_CrossSections.push_back(crossSectionStatic);
								crossSectionStatic->m_Station = std::make_shared<IfcReal>(cs->stationing);

								buw::ReferenceCounted<IfcCrossSectionGeometry> geo = std::make_shared<IfcCrossSectionGeometry>(createEntityId());
								model_->insertEntity(geo);

								crossSectionStatic->m_Geometry = geo;

								for (int csDesignSurfaceIndex = 0; csDesignSurfaceIndex < cs->getDesignCrossSectionProfileCount(); csDesignSurfaceIndex++)
								{
									buw::ReferenceCounted<buw::DesignCrossSectionProfile> csDesignSurf = cs->getDesignCrossSectionProfile(csDesignSurfaceIndex);

									buw::ReferenceCounted<IfcPolyline> polyline = std::make_shared<IfcPolyline>(createEntityId());
									model_->insertEntity(polyline);

									geo->m_Geometry.push_back(polyline);

									// iterate through all points  of DesignCrossSectionProfile
									for (int p = 0; p < csDesignSurf->crossSectionsPoints.size(); p++)
									{
										buw::Vector2d position = buw::Vector2d(
											csDesignSurf->crossSectionsPoints[p]->position.x(),
											csDesignSurf->crossSectionsPoints[p]->position.y()
											);

										polyline->m_Points.push_back(createIfcCartesianPoint(position));
									}
								}
							}
						}
					}
				}
			}

			// writer
			buw::ReferenceCounted<IfcStepWriter> step_writer = buw::ReferenceCounted<IfcStepWriter>(new IfcStepWriter());
			std::stringstream stream;

			step_writer->writeStream(stream, model_);

			std::ofstream textFile(filename.c_str());
			textFile << stream.str().c_str();
		}
		catch (const IfcRoadException& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	virtual ~IfcRoadExportImpl()
	{

	}
	
	buw::ReferenceCounted<IfcDimensionalExponents> zeroDimExp_ = nullptr;
	buw::ReferenceCounted<IfcGeometricRepresentationSubContext> subcontextAxis = nullptr;

private:
	void convertVerticalAlignment(
		buw::ReferenceCounted<buw::Alignment2DBased3D> alignment,
		shared_ptr<OpenInfraPlatform::IfcRoad::IfcAlignment> ifcAlignment)
	{
		if (alignment->getType() != buw::e3DAlignmentType::e2DBased)
		{
			return;
		}

		buw::ReferenceCounted<Alignment2DBased3D> alignment2D = std::static_pointer_cast<buw::Alignment2DBased3D>(alignment);

		if (!alignment2D->hasVerticalAlignment())
		{
			return;
		}

		buw::ReferenceCounted<IfcAlignment2DVertical> ifcVerticalAlignment = std::make_shared<IfcAlignment2DVertical>(entityId_++);
		model_->insertEntity(ifcVerticalAlignment);
		ifcAlignment->m_Vertical = ifcVerticalAlignment;

		buw::ReferenceCounted<buw::VerticalAlignment2D> v = alignment->getVerticalAlignment();

		if (v != nullptr)
		{
			for (int ai = 0; ai < v->getAlignmentElementCount(); ai++)
			{
				if (v->getAlignmentElementByIndex(ai)->getAlignmentType() == buw::eVerticalAlignmentType::Line)
				{
					auto ve = v->getAlignmentElementByIndex(ai);
					buw::ReferenceCounted<buw::VerticalAlignmentElement2DLine> line = std::static_pointer_cast<buw::VerticalAlignmentElement2DLine>(ve);

					const buw::Vector2d start	= ve->getStartPosition();
					const buw::Vector2d end		= ve->getEndPosition();

					BLUE_ASSERT(start != end, "Invalid line segment.");

					const double startGradient	= line->getGradient();

					buw::ReferenceCounted<IfcAlignment2DVerSegLine> ifcLine = std::make_shared<IfcAlignment2DVerSegLine>(createEntityId());
					model_->insertEntity(ifcLine);
					ifcVerticalAlignment->m_Segments.push_back(ifcLine);

					ifcLine->m_StartDistAlong = std::make_shared<IfcLengthMeasure>(start.x());
					ifcLine->m_HorizontalLength = std::make_shared<IfcPositiveLengthMeasure>();
					ifcLine->m_HorizontalLength->m_value = (end.x() - start.x());
					ifcLine->m_StartHeight = std::make_shared<IfcLengthMeasure>(start.y());
					ifcLine->m_StartGradient = std::make_shared<IfcNormalisedRatioMeasure>();
					ifcLine->m_StartGradient->m_value = startGradient;
				}

				if (v->getAlignmentElementByIndex(ai)->getAlignmentType() == buw::eVerticalAlignmentType::Arc)
				{
					auto ve = v->getAlignmentElementByIndex(ai);

					buw::Vector2d start = ve->getStartPosition();
					buw::Vector2d end = ve->getEndPosition();
	
					buw::ReferenceCounted<IfcAlignment2DVerSegCircularArc> arc = std::make_shared<IfcAlignment2DVerSegCircularArc>(createEntityId());
					model_->insertEntity(arc);
					ifcVerticalAlignment->m_Segments.push_back(arc);

					arc->m_StartDistAlong = std::make_shared<IfcLengthMeasure>(start.x());
					arc->m_HorizontalLength = std::make_shared<IfcPositiveLengthMeasure>();
					arc->m_HorizontalLength->m_value = (end.x() - start.x());

					BLUE_ASSERT(arc->m_HorizontalLength->m_value >= 0.0, "Invalid segment length.");

					arc->m_StartHeight = std::make_shared<IfcLengthMeasure>(start.y());
					
					double startGradient = 0;
					ve->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartGradient, &startGradient);
					arc->m_StartGradient = std::make_shared<IfcNormalisedRatioMeasure>();
					arc->m_StartGradient->m_value = startGradient;

					double radius = 0;
					ve->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Radius, &radius);
					arc->m_Radius = std::make_shared<IfcPositiveLengthMeasure>();
					arc->m_Radius->m_value = radius;

					bool isConvex = 0;
					ve->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::IsConvex, &isConvex);
					arc->m_IsConvex = std::make_shared<IfcBoolean>(isConvex);
				}

				if (v->getAlignmentElementByIndex(ai)->getAlignmentType() == buw::eVerticalAlignmentType::Parabola)
				{
					auto ve = v->getAlignmentElementByIndex(ai);

					buw::ReferenceCounted<buw::VerticalAlignmentElement2DParabola> parabola = std::static_pointer_cast<buw::VerticalAlignmentElement2DParabola>(ve);

					buw::Vector2d start = parabola->getStartPosition();
					buw::Vector2d end = parabola->getEndPosition();
				
					buw::Vector2d pvi;
					ve->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::PVI, &pvi);

					buw::ReferenceCounted<IfcAlignment2DVerSegParabolicArc> para = std::make_shared<IfcAlignment2DVerSegParabolicArc>(createEntityId());
					model_->insertEntity(para);
					ifcVerticalAlignment->m_Segments.push_back(para);

					para->m_StartDistAlong = std::make_shared<IfcLengthMeasure>(start.x());
					para->m_HorizontalLength = std::make_shared<IfcPositiveLengthMeasure>();
					para->m_HorizontalLength->m_value = (end.x() - start.x());
					para->m_StartHeight = std::make_shared<IfcLengthMeasure>(start.y());

					double startGradient = parabola->getStartGradient();  // returns an angle
					//double startGradient2 = parabola->getGradient(start.x());

					para->m_StartGradient = std::make_shared<IfcNormalisedRatioMeasure>();
					para->m_StartGradient->m_value = startGradient;

					para->m_ParabolaConstant = std::make_shared<IfcPositiveLengthMeasure>();
					para->m_ParabolaConstant->m_value = std::abs(parabola->getFocalLength() * 2.0);

					if (parabola->getFocalLength() * 2.0 < 0)
					{
						BLUE_ASSERT(parabola->isConvex() == false, "Invalid value.");
					}
					else
					{
						BLUE_ASSERT(parabola->isConvex() == true, "Invalid value.");
					}

					para->m_IsConvex = std::make_shared<IfcBoolean>(parabola->isConvex());
				}
			}
		}
	}

	void convertHorizontalAlignment(
		shared_ptr<OpenInfraPlatform::IfcRoad::IfcAlignment> ifcAlignment,
		buw::ReferenceCounted<buw::Alignment2DBased3D> alignment,
		buw::Vector3d &centerOffset)
	{
		// create horizontal alignment model
		buw::ReferenceCounted<IfcAlignment2DHorizontal> horizontalAlignment = std::make_shared<IfcAlignment2DHorizontal>(createEntityId());
		model_->insertEntity(horizontalAlignment);
		ifcAlignment->m_Horizontal = horizontalAlignment;

		horizontalAlignment->m_StartDistAlong = std::make_shared<IfcLengthMeasure>(alignment->getHorizontalAlignment()->getStartStation());

		for (int i = 0; i < alignment->getHorizontalAlignment()->getAlignmentElementCount(); i++)
		{
			auto hAlignSegment = alignment->getHorizontalAlignment()->getAlignmentElementByIndex(i);

			if (hAlignSegment->getAlignmentType() == buw::eHorizontalAlignmentType::Line)
			{
				buw::ReferenceCounted<IfcAlignment2DHorizontalSegment> line = std::make_shared<IfcAlignment2DHorizontalSegment>(createEntityId());

				if (alignment->getHorizontalAlignment()->hasSuccessor(hAlignSegment))
				{
					auto successor = alignment->getHorizontalAlignment()->getSuccessor(hAlignSegment);

					BLUE_ASSERT(successor != nullptr, "Invalid successor");

					double g1, g2;

					bool querySuccessful = successor->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartGradientAsPlaneAngleMeasure, &g1);
					BLUE_ASSERT(querySuccessful, "Query failed.");

					querySuccessful = hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartGradientAsPlaneAngleMeasure, &g2);
					BLUE_ASSERT(querySuccessful, "Query failed.");

					if (std::abs(g1 - g2) > 0.0001)
					{
						line->m_TangentialContinuity = std::make_shared<IfcBoolean>(true);
					}
					else
					{
						line->m_TangentialContinuity = std::make_shared<IfcBoolean>(false);
					}
				}
				else
				{
					// last element - does not matter
					line->m_TangentialContinuity = std::make_shared<IfcBoolean>(true);
				}

				model_->insertEntity(line);
				horizontalAlignment->m_Segments.push_back(line);

				buw::Vector2d start = hAlignSegment->getStartPosition();
				buw::Vector2d end = hAlignSegment->getEndPosition();

				createIfcLineSegment2D(line, start - centerOffset.block<2,1>(0,0), end - centerOffset.block<2,1>(0,0));
			}
			else if (hAlignSegment->getAlignmentType() == buw::eHorizontalAlignmentType::Arc)
			{
				buw::ReferenceCounted<IfcAlignment2DHorizontalSegment> arc = std::make_shared<IfcAlignment2DHorizontalSegment>(createEntityId());
				model_->insertEntity(arc);
				horizontalAlignment->m_Segments.push_back(arc);

				double radius;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Radius,
					&radius);

				buw::Vector2d center;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Center,
					&center);

				buw::Vector2d start = hAlignSegment->getStartPosition();
				buw::Vector2d end = hAlignSegment->getEndPosition();

				bool cw;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Clockwise,
					&cw);

				convertIfcCircularArcSegment2D(arc, radius, center - centerOffset.block<2,1>(0,0), start - centerOffset.block<2,1>(0,0), end - centerOffset.block<2,1>(0,0), cw);
			}
			else
			{
				buw::ReferenceCounted<IfcAlignment2DHorizontalSegment> clothoid = std::make_shared<IfcAlignment2DHorizontalSegment>(createEntityId());
				model_->insertEntity(clothoid);
				horizontalAlignment->m_Segments.push_back(clothoid);

				buw::Vector2d start = hAlignSegment->getStartPosition();
				buw::Vector2d end = hAlignSegment->getEndPosition();

				buw::Vector2d pi;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::PI,
					&pi);

				double curvatureStart;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::AlignmentCurvatureStart,
					&curvatureStart);

				double curvatureEnd;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::CurvatureEnd,
					&curvatureEnd);

				bool clockwise;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Clockwise,
					&clockwise);

				double length;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Length,
					&length);

				double startDirection;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::AlignmentStartDirection1D,
					&startDirection);

				double clothoidConstant;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::ClothoidConstant,
					&clothoidConstant);

				createIfcClothoidalArcSegment2D(clothoid, start - centerOffset.block<2,1>(0,0), end - centerOffset.block<2,1>(0,0), curvatureStart, curvatureEnd, clockwise, length, startDirection, pi, clothoidConstant);
			}
		}
	}

	buw::ReferenceCounted<IfcPlaneAngleMeasure> createIfcPlaneAngleMeasure(const buw::radiand angle)
	{
		if (settings_.useRadiansInsteadOfDegrees)
		{
			return std::make_shared<IfcPlaneAngleMeasure>(angle);
		}
		else
		{
			return std::make_shared<IfcPlaneAngleMeasure>(buw::radianToDegree(angle));
		}
	}

	void convertIfcCircularArcSegment2D(
		buw::ReferenceCounted<IfcAlignment2DHorizontalSegment> arc,
		const double radius,
		const buw::Vector2d &center,
		const buw::Vector2d &start,
		const buw::Vector2d &end,
		const bool cw)
	{
		buw::ReferenceCounted<IfcCircularArcSegment2D> curveSegement = std::make_shared<IfcCircularArcSegment2D>(createEntityId());
		model_->insertEntity(curveSegement);
		arc->m_CurveGeometry = curveSegement;

		curveSegement->m_StartPoint = createIfcCartesianPoint(start);

		buw::Vector2d startDirection = buw::createRotationMatrix(-0.5 * buw::constantsd::pi()) * (start - center);

		buw::Vector2d xAxis = buw::Vector2d(1.0, 0.0);
		buw::radiand angle = buw::calculateAngleBetweenVectors(xAxis, startDirection);

		if (!cw)
		{
			angle += buw::constantsd::pi();
		}

		BLUE_ASSERT(angle < buw::constantsd::pi() * 4.0, "Invalid angle");

		while (angle > buw::constantsd::pi() * 2.0)
		{
			angle -= buw::constantsd::pi() * 2.0;
		}

		curveSegement->m_StartDirection = createIfcPlaneAngleMeasure(angle);
		curveSegement->m_SegmentLength = std::make_shared<IfcPositiveLengthMeasure>();

		double segmentLength = buw::calculateAngleBetweenVectors(buw::Vector2d(start - center), buw::Vector2d(end - center)) * radius;

		BLUE_ASSERT(segmentLength >= 0, "Invalid segment length");

		if (cw)
		{
			segmentLength = (2.0 * buw::constantsd::pi() - buw::calculateAngleBetweenVectors(buw::Vector2d(start - center), buw::Vector2d(end - center))) * radius;
		}

		curveSegement->m_SegmentLength->m_value = segmentLength;

		curveSegement->m_Radius = std::make_shared<IfcPositiveLengthMeasure>();
		curveSegement->m_Radius->m_value = radius;
		curveSegement->m_IsCcw = std::make_shared<IfcBoolean>(!cw);
	}

	void exportTerrain(
		buw::ReferenceCounted<buw::DigitalElevationModel> dem,
		buw::Vector3d &centerOffset, 
		buw::ReferenceCounted<IfcGeometricRepresentationContext> geometricRepresentationContext,
		buw::ReferenceCounted<IfcRelContainedInSpatialStructure> c2)
	{
		for (int i = 0; i < dem->getSurfaceCount(); i++)
		{
			buw::ReferenceCounted<buw::Surface> s = dem->getSurface(i);

			buw::ReferenceCounted<IfcTriangulatedFaceSet> triangluratedFaceSet = std::make_shared<IfcTriangulatedFaceSet>(createEntityId());
			model_->insertEntity(triangluratedFaceSet);

			triangluratedFaceSet->m_Closed = std::make_shared<IfcBoolean>(false);
			triangluratedFaceSet->m_Coordinates = std::make_shared< IfcCartesianPointList3D >(createEntityId());
			model_->insertEntity(triangluratedFaceSet->m_Coordinates);

			// iterate over all points of the current surface element
			for (int pointIndex = 0; pointIndex < s->getPointCount(); pointIndex++)
			{
				double x = s->getPoints()[pointIndex].x() - centerOffset.x();
				double y = s->getPoints()[pointIndex].y() - centerOffset.y();
				double z = s->getPoints()[pointIndex].z() - centerOffset.z();

				std::vector<shared_ptr<IfcLengthMeasure>> coordinates;
				coordinates.push_back(std::make_shared<IfcLengthMeasure>(x));
				coordinates.push_back(std::make_shared<IfcLengthMeasure>(y));
				coordinates.push_back(std::make_shared<IfcLengthMeasure>(z));

				triangluratedFaceSet->m_Coordinates->m_CoordList.push_back(coordinates);
			}

			for (int faceIndex = 0; faceIndex < s->getTriangleCount(); faceIndex++)
			{
				std::vector<int> face_indices;

				// reverse order of faces
				face_indices.push_back(s->getTriangeFaces()[faceIndex][0]);
				face_indices.push_back(s->getTriangeFaces()[faceIndex][2]);
				face_indices.push_back(s->getTriangeFaces()[faceIndex][1]);

				triangluratedFaceSet->m_CoordIndex.push_back(face_indices);
			}

			std::vector<shared_ptr<IfcRepresentation>> representation;
			std::vector<shared_ptr<IfcRepresentationItem>> representationItems;
			representationItems.push_back(triangluratedFaceSet);
			representation.push_back(createIfcShapeRepresentation(representationItems, geometricRepresentationContext));

			buw::ReferenceCounted<IfcAxis2Placement3D> axisPlacement = createIfcAxis2Placement3D(createIfcCartesianPoint(0, 0, 0));
			buw::ReferenceCounted<IfcLocalPlacement> localPlacement = createIfcLocalPlacement(axisPlacement);

			auto sr = createIfcProductDefinitionShape(representation);

			buw::ReferenceCounted<IfcGeographicElement> geographicElement = std::make_shared<IfcGeographicElement>(createEntityId());
			model_->insertEntity(geographicElement);
			geographicElement->m_PredefinedType = std::make_shared<IfcGeographicElementTypeEnum>(IfcGeographicElementTypeEnum::ENUM_TERRAIN);
			geographicElement->m_GlobalId = createGlobalId();
			geographicElement->m_Name = std::make_shared<IfcLabel>("Terrain");
			geographicElement->m_OwnerHistory = nullptr;// ownerHistory;
			geographicElement->m_Representation = sr;
			geographicElement->m_ObjectPlacement = localPlacement;

			// connect GeographicElement with site
			c2->m_RelatedElements.push_back(geographicElement);
		}
	}

	buw::ReferenceCounted<IfcShapeRepresentation>
	createIfcShapeRepresentation(
	std::vector<buw::ReferenceCounted<IfcRepresentationItem>> representationItems,
		buw::ReferenceCounted<IfcRepresentationContext> context,
		std::string representationIdentifier = "Body",
		std::string representationType = "Tessellation")
	{
		buw::ReferenceCounted<IfcShapeRepresentation> shapeRepresentation = std::make_shared<IfcShapeRepresentation>(createEntityId());
		model_->insertEntity(shapeRepresentation);
		shapeRepresentation->m_ContextOfItems = context;
		shapeRepresentation->m_Items = representationItems;
		shapeRepresentation->m_RepresentationIdentifier = std::make_shared<IfcLabel>(representationIdentifier.c_str());
		shapeRepresentation->m_RepresentationType = std::make_shared<IfcLabel>(representationType.c_str());
		return shapeRepresentation;
	}

	buw::ReferenceCounted<IfcOrganization> createIfcOrganization()
	{
		buw::ReferenceCounted<IfcOrganization> organization = std::make_shared<IfcOrganization>(createEntityId());
		model_->insertEntity(organization);
		//organization->m_Identification = std::make_shared<IfcIdentifier>("TUM");
		organization->m_Name = std::make_shared<IfcLabel>("TUM");
		organization->m_Description = std::make_shared<IfcText>("Chair of Computational Modeling and Simulation");
		return organization;
	}

	buw::ReferenceCounted<IfcApplication> createIfcApplication(shared_ptr<IfcOrganization> applicationDeveloper)
	{
		buw::ReferenceCounted<IfcApplication> application = std::make_shared<IfcApplication>(createEntityId());
		model_->insertEntity(application);
		application->m_ApplicationDeveloper = applicationDeveloper;
		application->m_Version = std::make_shared<IfcLabel>("RTM");
		application->m_ApplicationFullName = std::make_shared<IfcLabel>("TUM Open Infra Platform 2017");
		application->m_ApplicationIdentifier = std::make_shared<IfcIdentifier>("OIP");
		return application;
	}

	buw::ReferenceCounted<IfcUnitAssignment> createIfcUnitAssignment()
	{
		buw::ReferenceCounted<IfcUnitAssignment> unitAssignment = std::make_shared<IfcUnitAssignment>(createEntityId());
		model_->insertEntity(unitAssignment);

		// length unit [m]
		buw::ReferenceCounted<IfcSIUnit> lengthUnit = std::make_shared<IfcSIUnit>(createEntityId());
		model_->insertEntity(lengthUnit);
		//lengthUnit->m_Prefix = std::make_shared<IfcSIPrefix>(IfcSIPrefix::ENUM_MILLI);
		lengthUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_LENGTHUNIT);
		lengthUnit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_METRE);
		unitAssignment->m_Units.push_back(lengthUnit);

		// plane unit [rad/degree]
		if (settings_.useRadiansInsteadOfDegrees)
		{
			auto unit = std::make_shared<IfcSIUnit>(createEntityId());
			model_->insertEntity(unit);
			unit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_PLANEANGLEUNIT);
			unit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_RADIAN);

			unitAssignment->m_Units.push_back(unit);
		}
		else
		{
			buw::ReferenceCounted<IfcConversionBasedUnit> conversionBasedUnit = std::make_shared<IfcConversionBasedUnit>(createEntityId());
			model_->insertEntity(conversionBasedUnit);

			auto conversionFactor = std::make_shared<IfcMeasureWithUnit>(createEntityId());
			model_->insertEntity(conversionFactor);

			conversionFactor->m_ValueComponent = std::make_shared<IfcPlaneAngleMeasure>(0.017453293);
			
			auto unit = std::make_shared<IfcSIUnit>(createEntityId());
			model_->insertEntity(unit);

			unit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_PLANEANGLEUNIT);
			unit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_RADIAN);
			conversionFactor->m_UnitComponent = unit;

			buw::ReferenceCounted<IfcDimensionalExponents> dimensionalExponents = zeroDimExp_;

			conversionBasedUnit->m_Dimensions = dimensionalExponents;
			conversionBasedUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_PLANEANGLEUNIT);
			conversionBasedUnit->m_Name = std::make_shared<IfcLabel>("degree");
			conversionBasedUnit->m_ConversionFactor = conversionFactor;

			unitAssignment->m_Units.push_back(conversionBasedUnit);
		}

		// area unit
		buw::ReferenceCounted<IfcSIUnit> areaUnit = std::make_shared<IfcSIUnit>(createEntityId());
		model_->insertEntity(areaUnit);
		areaUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_AREAUNIT);
		areaUnit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_SQUARE_METRE);
		unitAssignment->m_Units.push_back(areaUnit);

		// volume unit
		buw::ReferenceCounted<IfcSIUnit> volumeUnit = std::make_shared<IfcSIUnit>(createEntityId());
		model_->insertEntity(volumeUnit);
		volumeUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_VOLUMEUNIT);
		volumeUnit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_CUBIC_METRE);

		unitAssignment->m_Units.push_back(volumeUnit);

		return unitAssignment;
	}

	buw::ReferenceCounted<IfcAxis2Placement3D> createIfcAxis2Placement3D(
		buw::ReferenceCounted<IfcCartesianPoint> location)
	{
		buw::ReferenceCounted<IfcAxis2Placement3D> ap = std::make_shared<IfcAxis2Placement3D>(createEntityId());
		model_->insertEntity(ap);
		ap->m_Location = location;
		return ap;
	}

	buw::ReferenceCounted<IfcLocalPlacement> createIfcLocalPlacement(
		buw::ReferenceCounted<IfcAxis2Placement3D> axisPlacement)
	{
		buw::ReferenceCounted<IfcLocalPlacement> lp = std::make_shared<IfcLocalPlacement>(createEntityId());
		model_->insertEntity(lp);
		lp->m_RelativePlacement = axisPlacement;
		return lp;
	}

	buw::ReferenceCounted<IfcCartesianPoint> createIfcCartesianPoint(
		const buw::Vector3d& positon)
	{
		return createIfcCartesianPoint(positon.x(), positon.y(), positon.z());
	}

	buw::ReferenceCounted<IfcCartesianPoint> createIfcCartesianPoint(
		const float x,
		const float y,
		const float z)
	{
		buw::ReferenceCounted<IfcCartesianPoint> point = std::make_shared<IfcCartesianPoint>(createEntityId());
		model_->insertEntity(point);
		point->m_Coordinates.push_back(std::make_shared<IfcLengthMeasure>(x));
		point->m_Coordinates.push_back(std::make_shared<IfcLengthMeasure>(y));
		point->m_Coordinates.push_back(std::make_shared<IfcLengthMeasure>(z));
		return point;
	}

	buw::ReferenceCounted<IfcCartesianPoint> createIfcCartesianPoint(const double x, const double y)
	{
		buw::ReferenceCounted<	IfcCartesianPoint> pnt = std::make_shared<	IfcCartesianPoint>(entityId_++);
		model_->insertEntity(pnt);

		pnt->m_Coordinates.push_back(std::make_shared<IfcLengthMeasure>(x));
		pnt->m_Coordinates.push_back(std::make_shared<IfcLengthMeasure>(y));

		return pnt;
	}

	buw::ReferenceCounted<IfcCartesianPoint> createIfcCartesianPoint(const buw::Vector2d& point)
	{
		buw::ReferenceCounted<	IfcCartesianPoint> pnt = std::make_shared<	IfcCartesianPoint>(entityId_++);
		model_->insertEntity(pnt);

		pnt->m_Coordinates.push_back(std::make_shared<IfcLengthMeasure>(point.x()));
		pnt->m_Coordinates.push_back(std::make_shared<IfcLengthMeasure>(point.y()));

		return pnt;
	}

	buw::ReferenceCounted<IfcFace> createIfcFace(
		buw::ReferenceCounted<IfcFaceOuterBound> outerBound)
	{
		buw::ReferenceCounted<IfcFace> face = std::make_shared<IfcFace>(createEntityId());
		model_->insertEntity(face);
		face->m_Bounds.push_back(outerBound);
		return face;
	}

	buw::ReferenceCounted<IfcFacetedBrep> createIfcFacetedBrep(
		buw::ReferenceCounted<IfcClosedShell> closedShell)
	{
		buw::ReferenceCounted<IfcFacetedBrep> facetedBrep = std::make_shared<IfcFacetedBrep>(createEntityId());
		model_->insertEntity(facetedBrep);
		facetedBrep->m_Outer = closedShell;
		return facetedBrep;
	}

	buw::ReferenceCounted<IfcRepresentationContext> createIfcRepresentationContext()
	{
		buw::ReferenceCounted<IfcRepresentationContext> rc = std::make_shared<IfcRepresentationContext>(createEntityId());
		model_->insertEntity(rc);
		return rc;
	}

	buw::ReferenceCounted<IfcProductDefinitionShape> createIfcProductDefinitionShape(
		std::vector<buw::ReferenceCounted<IfcRepresentation>> representation)
	{
		buw::ReferenceCounted<IfcProductDefinitionShape> productDefinitionShape = std::make_shared<IfcProductDefinitionShape>(createEntityId());
		model_->insertEntity(productDefinitionShape);
		productDefinitionShape->m_Representations = representation;
		return productDefinitionShape;
	}

	buw::ReferenceCounted<IfcOwnerHistory> createIfcOwnerHistory(
		buw::ReferenceCounted<IfcPersonAndOrganization> personAndOrganization,
		buw::ReferenceCounted<IfcApplication> application)
	{
		buw::ReferenceCounted<IfcOwnerHistory> oh = std::make_shared<IfcOwnerHistory>(createEntityId());
		model_->insertEntity(oh);
		oh->m_OwningUser = personAndOrganization;
		oh->m_OwningApplication = application;
		//oh->m_State = std::make_shared<IfcStateEnum>( IfcStateEnum::ENUM_READONLY );
		oh->m_ChangeAction = std::make_shared<IfcChangeActionEnum>(IfcChangeActionEnum::ENUM_NOCHANGE);
		oh->m_CreationDate = std::make_shared<IfcTimeStamp>(0);
		return oh;
	}

	buw::ReferenceCounted<IfcPersonAndOrganization> createIfcPersonAndOrganization(
		buw::ReferenceCounted<IfcPerson> person,
		buw::ReferenceCounted<IfcOrganization> organization)
	{
		buw::ReferenceCounted<IfcPersonAndOrganization> pao = std::make_shared<IfcPersonAndOrganization>(createEntityId());
		model_->insertEntity(pao);
		pao->m_ThePerson = person;
		pao->m_TheOrganization = organization;
		return pao;
	}

	void createIfcLineSegment2D(
		buw::ReferenceCounted<IfcAlignment2DHorizontalSegment> line,
		const buw::Vector2d& start,
		const buw::Vector2d& end)
	{
		buw::ReferenceCounted<IfcLineSegment2D> curveSegement = std::make_shared<IfcLineSegment2D>(createEntityId());
		model_->insertEntity(curveSegement);
		line->m_CurveGeometry = curveSegement;

		curveSegement->m_StartPoint = createIfcCartesianPoint(start);

		buw::Vector2d startDirection = end - start;
		buw::Vector2d xAxis = buw::Vector2d(1.0, 0.0);
		buw::radiand angle = buw::calculateAngleBetweenVectors(xAxis, startDirection);

		curveSegement->m_StartDirection = createIfcPlaneAngleMeasure(angle);
		curveSegement->m_SegmentLength = std::make_shared<IfcPositiveLengthMeasure>();
		const double segmentLength = startDirection.norm();
		curveSegement->m_SegmentLength->m_value = segmentLength;
	}

	void createIfcClothoidalArcSegment2D(
		buw::ReferenceCounted<IfcAlignment2DHorizontalSegment> clothoid,
		const buw::Vector2d &start,
		const buw::Vector2d &end,
		const double curvatureStart,
		const double curvatureEnd,
		const bool clockwise,
		const double length,
		const buw::radiand startDirection,
		const buw::Vector2d &CheckPointOfIntersection,
		const double clothoidConstant)
	{
		buw::ReferenceCounted<IfcClothoidalArcSegment2D> curveSegement = std::make_shared<IfcClothoidalArcSegment2D>(createEntityId());
		model_->insertEntity(curveSegement);
		clothoid->m_CurveGeometry = curveSegement;

		curveSegement->m_StartPoint = createIfcCartesianPoint(start);
		curveSegement->m_StartDirection = createIfcPlaneAngleMeasure(startDirection);
		curveSegement->m_SegmentLength = std::make_shared<IfcPositiveLengthMeasure>();
		curveSegement->m_SegmentLength->m_value = length;

		if (curvatureStart == 0.0)
		{
			curveSegement->m_StartRadius = nullptr; // There is no INF value in STEP - convention: store INF values as not available values
		}
		else
		{
			curveSegement->m_StartRadius = std::make_shared<IfcPositiveLengthMeasure>();
			curveSegement->m_StartRadius->m_value = (1.0 / curvatureStart);
		}

		curveSegement->m_IsCcw = std::make_shared<IfcBoolean>(!clockwise);

		if (curvatureStart < curvatureEnd)
		{
			curveSegement->m_IsEntry = std::make_shared<IfcBoolean>(true);
		}
		else
		{
			curveSegement->m_IsEntry = std::make_shared<IfcBoolean>(false);
		}

		curveSegement->m_ClothoidConstant = std::make_shared<IfcReal>(clothoidConstant);
	}

	double mapAngleToRatioMeasure(buw::degreed angle)
	{
		if (angle <= 180.0)
		{
			angle = angle / 45.0;
		}
		else
		{
			if (angle > 270.0)
			{
				angle = 360.0 - angle;

				angle = -1.0f * angle / 45.0;
			}
			else
			{
				angle = 0;
				BLUE_LOG(error)	<< "Invalid angle.";
			}
		}

		return angle;
	}
	
	buw::ReferenceCounted<IfcPerson> createIfcPerson()
	{
		buw::ReferenceCounted<IfcPerson> person = std::make_shared<IfcPerson>(createEntityId());
		model_->insertEntity(person);
		person->m_FamilyName = std::make_shared<IfcLabel>("User (FamilyName)");
		person->m_GivenName = std::make_shared<IfcLabel>("User (GivenName)");
		//person->m_MiddleNames.push_back(std::make_shared<IfcLabel>(""));
		return person;
	}

	int createEntityId()
	{
		return entityId_++;
	}

	buw::ReferenceCounted<IfcGloballyUniqueId> createGlobalId()
	{
		std::string guid = CreateCompressedGuidString22();

		return std::make_shared<IfcGloballyUniqueId>(guid);
	}

	

private:
	buw::ReferenceCounted<IfcRoadModel>	model_;
	int								entityId_;
	IfcRoadExportDescription	settings_;
};

OpenInfraPlatform::Infrastructure::ExportIfcRoad::ExportIfcRoad(const IfcRoadExportDescription& desc, buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename) :
Export(am, dem, filename),
impl_(new IfcRoadExportImpl(desc, am, dem, filename))
{
	
}

OpenInfraPlatform::Infrastructure::ExportIfcRoad::~ExportIfcRoad()
{

}