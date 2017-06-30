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

#include "OpenInfraPlatform/Infrastructure/Export/ExportIfcAlignment1x1.h"

#include "OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1Entities.h"
#include "OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1EntityEnums.h"
#include "OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1Types.h"
#include "OpenInfraPlatform/IfcAlignment1x1/guid/CreateGuid_64.h"
#include "OpenInfraPlatform/IfcAlignment1x1/model/Exception.h"
#include "OpenInfraPlatform/IfcAlignment1x1/model/Model.h"
#include "OpenInfraPlatform/IfcAlignment1x1/model/UnitConverter.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/IfcStepReader.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/Reader.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/IfcStepWriter.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment3DBased3D.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DParabola.h"

#include <fstream>
#include <memory>

using namespace OpenInfraPlatform::IfcAlignment1x1;

class OpenInfraPlatform::Infrastructure::ExportIfcAlignment1x1::IfcAlignment1x1ExportImpl : public Export {
public:
	IfcAlignment1x1ExportImpl(const ifcAlignmentExportDescription& desc,
	                          buw::ReferenceCounted<buw::AlignmentModel> am,
	                          buw::ReferenceCounted<buw::DigitalElevationModel> dem,
	                          const std::string& filename)
	    : Export(am, dem, filename), entityId_(1), model_(nullptr) {
		// create model
		model_ = std::shared_ptr<IfcAlignment1x1Model>(new IfcAlignment1x1Model());

		settings_ = desc;

		try {
			// Person, Organization, Application
			shared_ptr<IfcPerson> person = createIfcPerson();
			shared_ptr<IfcOrganization> organization = createIfcOrganization();
			shared_ptr<IfcApplication> application = createIfcApplication(organization);

			auto personAndOrganization = createIfcPersonAndOrganization(person, organization);

			shared_ptr<IfcOwnerHistory> ownerHistory = createIfcOwnerHistory(personAndOrganization, application);

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
			shared_ptr<IfcProject> project = std::make_shared<IfcProject>(createEntityId());
			project->m_GlobalId = createGlobalId();
			project->m_Name = std::make_shared<IfcLabel>("IfcAlignment Project");
			project->m_UnitsInContext = createIfcUnitAssignment(); // Units
			project->m_OwnerHistory = ownerHistory;
			model_->insertEntity(project);

			// create site
			shared_ptr<IfcAxis2Placement3D> site_axisPlacement = createIfcAxis2Placement3D(createIfcCartesianPoint(0, 0, 0));
			site_localPlacement = createIfcLocalPlacement(site_axisPlacement);

			shared_ptr<IfcSite> site = std::make_shared<IfcSite>(createEntityId());
			site->m_GlobalId = createGlobalId();
			site->m_OwnerHistory = nullptr; // ownerHistory;
			site->m_Description = std::make_shared<IfcText>("My description.");
			site->m_Name = std::make_shared<IfcLabel>("Terrain surface");
			site->m_ObjectPlacement = site_localPlacement;
			site->m_RefElevation = std::make_shared<IfcLengthMeasure>(0.0);
			model_->insertEntity(site);

			// create map conversion
			shared_ptr<IfcProjectedCRS> projectedCRS = std::make_shared<IfcProjectedCRS>(createEntityId());
			model_->insertEntity(projectedCRS);
			projectedCRS->m_Name = std::make_shared<IfcLabel>("EPSG:31467"); // todo get EPSG code from Gauï¿½-Krueger coordinates
			projectedCRS->m_Description = std::make_shared<IfcText>("EPSG:31467 - DHDN / 3-Degree Gauss-Krueger Zone 3");
			projectedCRS->m_GeodeticDatum = std::make_shared<IfcIdentifier>("EPSG:31467");
			projectedCRS->m_MapProjection = std::make_shared<IfcIdentifier>("Gauss-Krueger");
			projectedCRS->m_MapZone = std::make_shared<IfcIdentifier>("3");

			shared_ptr<IfcSIUnit> lengthUnit = std::make_shared<IfcSIUnit>(createEntityId());
			model_->insertEntity(lengthUnit);
			lengthUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_LENGTHUNIT);
			lengthUnit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_METRE);

			projectedCRS->m_MapUnit = lengthUnit;

			buw::Vector3d centerOffset;
			if (alignmentModel_->getAlignmentCount() > 0)
				centerOffset = alignmentModel_->getAlignment(0)->getPosition(0);
			else
				centerOffset = digitalElevationModel_->getCenterPoint();

			// in my view (and as an implementer agreement) we should not use the height setting in the IfcMapConversion - leave it 0.00 (sea level according to the CRS). 
			// Same for IfcSite. Then the z-Value would be in the vertical alignment values and in the z Values of the TIN.
			centerOffset.z() = 0;

			if (desc.roundOffsetMapConversion)
			{
				centerOffset = buw::Vector3d(
					std::round(centerOffset.x()),
					std::round(centerOffset.y()),
					std::round(centerOffset.z())
				);
			}

			// connect site and project with IfcRelAggregates
			shared_ptr<IfcRelAggregates> connection = std::make_shared<IfcRelAggregates>(createEntityId());
			model_->insertEntity(connection);
			connection->m_GlobalId = createGlobalId();
			connection->m_OwnerHistory = nullptr; // ownerHistory;
			connection->m_RelatingObject = project;
			connection->m_RelatedObjects.push_back(site);

			shared_ptr<IfcRelContainedInSpatialStructure> c2 = std::make_shared<IfcRelContainedInSpatialStructure>(createEntityId());
			model_->insertEntity(c2);
			c2->m_GlobalId = createGlobalId();
			c2->m_OwnerHistory = nullptr; // ownerHistory;
			c2->m_RelatingStructure = site;

			shared_ptr<IfcMapConversion> mapConversion = std::make_shared<IfcMapConversion>(createEntityId());
			model_->insertEntity(mapConversion);
			// mapConversion->m_SourceCRS =
			mapConversion->m_TargetCRS = projectedCRS;
			mapConversion->m_Eastings = std::make_shared<IfcLengthMeasure>(centerOffset.x());
			mapConversion->m_Northings = std::make_shared<IfcLengthMeasure>(centerOffset.y());
			mapConversion->m_OrthogonalHeight = std::make_shared<IfcLengthMeasure>(centerOffset.z());

			shared_ptr<IfcGeometricRepresentationContext> geometricRepresentationContext = std::make_shared<IfcGeometricRepresentationContext>(createEntityId());

			geometricRepresentationContext->m_ContextIdentifier = nullptr; // std::make_shared<IfcLabel>("Body");
			geometricRepresentationContext->m_ContextType = std::make_shared<IfcLabel>("Model");
			geometricRepresentationContext->m_CoordinateSpaceDimension = std::make_shared<IfcDimensionCount>(3);
			geometricRepresentationContext->m_WorldCoordinateSystem = site_axisPlacement;
			geometricRepresentationContext->m_Precision = nullptr; // std::make_shared<IfcReal>(1e-5);
			model_->insertEntity(geometricRepresentationContext);
			mapConversion->m_SourceCRS = geometricRepresentationContext;

			project->m_RepresentationContexts.push_back(geometricRepresentationContext);

			if (desc.exportTerrain) {
				exportTerrain(digitalElevationModel_, centerOffset, geometricRepresentationContext, c2);
			}

			// export alignments
			if (desc.exportAlignment && desc.schemaVersion == eIfcSchemaVersion::IFC4x1) {
				exportAlignment(alignmentModel_->getAlignments(), site_axisPlacement, geometricRepresentationContext, centerOffset, c2);
			}

			wirteStepFile(filename);
		} catch (const IfcAlignment1x1Exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	virtual ~IfcAlignment1x1ExportImpl() {
	}

	void exportAlignment(std::vector<buw::ReferenceCounted<buw::IAlignment3D>>& alignments,
	                     shared_ptr<IfcAxis2Placement3D> site_axisPlacement,
	                     shared_ptr<IfcGeometricRepresentationContext> geometricRepresentationContext,
	                     buw::Vector3d centerOffset,
	                     shared_ptr<IfcRelContainedInSpatialStructure> c2) {
		for (int ai = 0; ai < alignments.size(); ai++) {
			if (alignments[ai]->getType() == buw::e3DAlignmentType::e3DBased) {
				// marker
				if (subcontextAxis == nullptr) {
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

				// name of alignment
				std::string name = alignments[ai]->getName().toStdString();

				shared_ptr<IfcAlignment> ifcAlignment = std::make_shared<IfcAlignment>(createEntityId());
				model_->insertEntity(ifcAlignment);

				ifcAlignment->m_GlobalId = createGlobalId();
				ifcAlignment->m_Name = std::make_shared<IfcLabel>(name);
				ifcAlignment->m_ObjectPlacement = site_localPlacement;

				shared_ptr<IfcCartesianPointList3D> pointList = std::make_shared<IfcCartesianPointList3D>(createEntityId());
				model_->insertEntity(pointList);

				buw::ReferenceCounted<buw::Alignment3DBased3D> alignment = std::static_pointer_cast<buw::Alignment3DBased3D>(alignments[ai]);

				for (double s = alignment->getStartStation(); s < alignment->getEndStation(); s += 1.0) {
					auto position = alignment->getPosition(s) - centerOffset;

					std::vector<shared_ptr<IfcLengthMeasure>> coordinates;
					for (int i = 0; i < 3; i++) {
						coordinates.push_back(std::make_shared<IfcLengthMeasure>(position[i]));
					}

					pointList->m_CoordList.push_back(coordinates);
				}

				shared_ptr<IfcIndexedPolyCurve> indexedPolyCurve = std::make_shared<IfcIndexedPolyCurve>(createEntityId());
				model_->insertEntity(indexedPolyCurve);
				indexedPolyCurve->m_SelfIntersect = std::shared_ptr<IfcBoolean>(false);
				indexedPolyCurve->m_Points = pointList;

				std::vector<shared_ptr<IfcRepresentation>> representation;
				std::vector<shared_ptr<IfcRepresentationItem>> representationItems;
				representationItems.push_back(indexedPolyCurve);
				representation.push_back(createIfcShapeRepresentation(representationItems, geometricRepresentationContext, "Axis", "Curve3D"));
				auto sr = createIfcProductDefinitionShape(representation);

				ifcAlignment->m_Representation = sr;
			} else {
				buw::ReferenceCounted<buw::Alignment2DBased3D> alignment = std::static_pointer_cast<buw::Alignment2DBased3D>(alignments[ai]);

				shared_ptr<IfcAlignment> ifcAlignment = std::make_shared<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment>(createEntityId());
				model_->insertEntity(ifcAlignment);
				ifcAlignment->m_GlobalId = createGlobalId();

				shared_ptr<IfcAlignmentCurve> ifcAlignmentCurve = std::make_shared<IfcAlignmentCurve>(createEntityId());
				model_->insertEntity(ifcAlignmentCurve);

				ifcAlignment->m_Axis = ifcAlignmentCurve;

				// set name of alignment
				std::string name = alignments[ai]->getName().toStdString();
				ifcAlignment->m_Description = std::make_shared<IfcText>(name);
				ifcAlignment->m_ObjectPlacement = site_localPlacement;

				convertHorizontalAlignment(ifcAlignmentCurve, alignment, centerOffset);

				convertVerticalAlignment(alignment, ifcAlignmentCurve, centerOffset.z());

				// connect ifcAlignment with site
				c2->m_RelatedElements.push_back(ifcAlignment);

				// cross sections
				/*
				for (int i = 0; i < alignment->getCrossSectionCount(); i++)	{

					auto cs = alignment->getCrossSection(i);
					auto dcsp = cs->getDesignCrossSectionProfile(i);
					
					
					//std::shared_ptr<IfcLinearPlacement > lp = std::make_shared<IfcLinearPlacement >(createEntityId());


					std::shared_ptr<IfcDistanceExpression> de = std::make_shared<IfcDistanceExpression>(createEntityId());
					model_->insertEntity(de);
					de->m_DistanceAlong = std::make_shared<IfcLengthMeasure>(cs->stationing);
					de->m_OffsetLateral = std::make_shared<IfcLengthMeasure>(0.0);
					de->m_OffsetVertical = std::make_shared<IfcLengthMeasure>(0.0);
					de->m_OffsetLongitudinal = std::make_shared<IfcLengthMeasure>(0.0);
					de->m_AlongHorizontal = std::make_shared<IfcBoolean>(true);

					buw::ReferenceCounted<buw::CrossSectionStatic> cs = alignment->getCrossSection(i);
					
					shared_ptr<IfcLinearPositioningElement> ifcLinearPositioningElement = std::make_shared<IfcLinearPositioningElement>(createEntityId());
					model_->insertEntity(ifcLinearPositioningElement);
					
					double station = cs->stationing;

					shared_ptr<IfcReference> ifcReference = std::make_shared<IfcReference>(createEntityId());
					//ifcReference->
					model_->insertEntity(ifcReference);
					
				}
				*/
			}
			
		}
	}

	void wirteStepFile(const std::string& filename) {
		// writer
		shared_ptr<IfcStepWriter> step_writer = shared_ptr<IfcStepWriter>(new IfcStepWriter());
		std::stringstream stream;

		/*
		    IFC 4.0.0 – final release – encoded as “IFC4”
		    IFC 4.0.1 – Addendum 1 – encoded as “IFC4”
		    IFC 4.0.2 – Addendum 2 – encoded as “IFC4”
		    IFC 4.1.0 – Alignment 1.0 – encoded as “IFC4X1”
		    IFC 4.1.1 – Alignment 1.0.5 – encoded as “IFC4X1” – October 21, 2016
		    IFC 4.1.2 – Alignment 1.1 – encoded as “IFC4X1” – November 2016
		*/

		std::string fileSchema = "IFC4X1";

		switch (settings_.schemaVersion) {
		case eIfcSchemaVersion::IFC2x3: fileSchema = "IFC2X3"; break;
		case eIfcSchemaVersion::IFC4: fileSchema = "IFC4"; break;
		case eIfcSchemaVersion::IFC4x1: fileSchema = "IFC4X1"; break;
		default: break;
		}

		// write file header
		{
			std::stringstream strs;
			strs << "ISO-10303-21;" << std::endl;
			strs << "HEADER;" << std::endl;
			strs << "FILE_DESCRIPTION(('" << fileSchema << "'),'2;1');" << std::endl;

			std::string filenameWithoutEscapeSequences = buw::replace(filename, "\\", "/");

			strs << "FILE_NAME('" << filenameWithoutEscapeSequences.c_str() << "','";

			// 2011-04-21T14:25:12
			time_t rawtime;
			struct tm timeinfo;
			time(&rawtime);

#ifdef _WIN32
			errno_t err_time;
			err_time = localtime_s(&timeinfo, &rawtime);
#else
			timeinfo = localtime(&rawtime);
#endif

			char buffer[80];
			strftime(buffer, 80, "%Y-%m-%dT%H:%M:%S", &timeinfo);
			strs << buffer;

			strs << "',(''),('',''),'','IfcAlignment','');" << std::endl;
			strs << "FILE_SCHEMA(('" << fileSchema << "'));" << std::endl;
			strs << "ENDSEC;" << std::endl;

			model_->setFileHeader(strs.str());
		}

		step_writer->writeStream(stream, model_);

		std::ofstream textFile(filename.c_str());
		textFile << stream.str().c_str();
	}

private:
	void convertVerticalAlignment(buw::ReferenceCounted<buw::Alignment2DBased3D> alignment,
		std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignmentCurve> ifcAlignment,
		const double centerHeight) {
		if (alignment->getType() != buw::e3DAlignmentType::e2DBased) {
			return;
		}

		buw::ReferenceCounted<buw::Alignment2DBased3D> alignment2D = std::static_pointer_cast<buw::Alignment2DBased3D>(alignment);

		if (!alignment2D->hasVerticalAlignment()) {
			return;
		}

		buw::ReferenceCounted<IfcAlignment2DVertical> ifcVerticalAlignment = std::make_shared<IfcAlignment2DVertical>(entityId_++);
		model_->insertEntity(ifcVerticalAlignment);

		ifcAlignment->m_Vertical = ifcVerticalAlignment;

		if (alignment->hasVerticalAlignment()) {
			buw::ReferenceCounted<buw::VerticalAlignment2D> v = alignment->getVerticalAlignment();
			BLUE_ASSERT(v != nullptr, "Invalid vertical alignment");

			for (int ai = 0; ai < v->getAlignmentElementCount(); ai++) {
				if (v->getAlignmentElementByIndex(ai)->getAlignmentType() == buw::eVerticalAlignmentType::Line) {
					auto ve = v->getAlignmentElementByIndex(ai);
					buw::ReferenceCounted<buw::VerticalAlignmentElement2DLine> line = std::static_pointer_cast<buw::VerticalAlignmentElement2DLine>(ve);

					const buw::Vector2d start = ve->getStartPosition();
					const buw::Vector2d end = ve->getEndPosition();

					BLUE_ASSERT(start != end, "Invalid line segment.");

					const double startGradient = line->getGradient();

					buw::ReferenceCounted<IfcAlignment2DVerSegLine> ifcLine = std::make_shared<IfcAlignment2DVerSegLine>(createEntityId());
					model_->insertEntity(ifcLine);
					ifcVerticalAlignment->m_Segments.push_back(ifcLine);

					ifcLine->m_StartDistAlong = std::make_shared<IfcLengthMeasure>(start.x());
					ifcLine->m_HorizontalLength = std::make_shared<IfcPositiveLengthMeasure>();
					ifcLine->m_HorizontalLength->m_value = (end.x() - start.x());
					ifcLine->m_StartHeight = std::make_shared<IfcLengthMeasure>(start.y() - centerHeight);
					ifcLine->m_StartGradient = std::make_shared<IfcNormalisedRatioMeasure>();
					ifcLine->m_StartGradient->m_value = startGradient;
				}

				if (v->getAlignmentElementByIndex(ai)->getAlignmentType() == buw::eVerticalAlignmentType::Arc) {
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

					arc->m_StartHeight = std::make_shared<IfcLengthMeasure>(start.y() - centerHeight);

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
					arc->m_IsConvex = std::make_shared<IfcBoolean>(!isConvex);
				}

				if (v->getAlignmentElementByIndex(ai)->getAlignmentType() == buw::eVerticalAlignmentType::Parabola) {
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
					para->m_StartHeight = std::make_shared<IfcLengthMeasure>(start.y() - centerHeight);

					double startGradient = parabola->getStartGradient(); // returns an angle

					para->m_StartGradient = std::make_shared<IfcNormalisedRatioMeasure>();
					para->m_StartGradient->m_value = startGradient;

					para->m_ParabolaConstant = std::make_shared<IfcPositiveLengthMeasure>();
					para->m_ParabolaConstant->m_value = std::abs(parabola->getFocalLength() * 2.0);

					if (parabola->getFocalLength() * 2.0 < 0) {
						BLUE_ASSERT(parabola->isConvex() == false, "Invalid value.");
					} else {
						BLUE_ASSERT(parabola->isConvex() == true, "Invalid value.");
					}

					para->m_IsConvex = std::make_shared<IfcBoolean>(!parabola->isConvex());
				}
			}
		}
	}

	void convertHorizontalAlignment(std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignmentCurve> ifcAlignment,
	                                buw::ReferenceCounted<buw::Alignment2DBased3D> alignment,
	                                buw::Vector3d& centerOffset) {
		// create horizontal alignment model
		shared_ptr<IfcAlignment2DHorizontal> horizontalAlignment = std::make_shared<IfcAlignment2DHorizontal>(createEntityId());
		model_->insertEntity(horizontalAlignment);
		ifcAlignment->m_Horizontal = horizontalAlignment;

		horizontalAlignment->m_StartDistAlong = std::make_shared<IfcLengthMeasure>(alignment->getHorizontalAlignment()->getStartStation());

		for (int i = 0; i < alignment->getHorizontalAlignment()->getAlignmentElementCount(); i++) {
			auto hAlignSegment = alignment->getHorizontalAlignment()->getAlignmentElementByIndex(i);

			if (hAlignSegment->getAlignmentType() == buw::eHorizontalAlignmentType::Line) {
				shared_ptr<IfcAlignment2DHorizontalSegment> line = std::make_shared<IfcAlignment2DHorizontalSegment>(createEntityId());

				if (alignment->getHorizontalAlignment()->hasSuccessor(hAlignSegment)) {
					auto successor = alignment->getHorizontalAlignment()->getSuccessor(hAlignSegment);

					BLUE_ASSERT(successor != nullptr, "Invalid successor");

					double g1, g2;

					bool querySuccessful = successor->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartGradientAsPlaneAngleMeasure, &g1);
					BLUE_ASSERT(querySuccessful, "Query failed.");

					querySuccessful = hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartGradientAsPlaneAngleMeasure, &g2);
					BLUE_ASSERT(querySuccessful, "Query failed.");

					if (std::abs(g1 - g2) > 0.0001) {
						line->m_TangentialContinuity = std::make_shared<IfcBoolean>(true);
					} else {
						line->m_TangentialContinuity = std::make_shared<IfcBoolean>(false);
					}
				} else {
					// last element - does not matter
					line->m_TangentialContinuity = std::make_shared<IfcBoolean>(true);
				}

				model_->insertEntity(line);
				horizontalAlignment->m_Segments.push_back(line);

				buw::Vector2d start = hAlignSegment->getStartPosition();
				buw::Vector2d end = hAlignSegment->getEndPosition();

				createIfcLineSegment2D(line, start - centerOffset.block<2, 1>(0, 0), end - centerOffset.block<2, 1>(0, 0));
			}
			else if (hAlignSegment->getAlignmentType() == buw::eHorizontalAlignmentType::Arc) {
				shared_ptr<IfcAlignment2DHorizontalSegment> arc = std::make_shared<IfcAlignment2DHorizontalSegment>(createEntityId());
				model_->insertEntity(arc);
				horizontalAlignment->m_Segments.push_back(arc);

				double radius;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Radius, &radius);

				buw::Vector2d center;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Center, &center);

				buw::Vector2d start = hAlignSegment->getStartPosition();
				buw::Vector2d end = hAlignSegment->getEndPosition();

				bool cw;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Clockwise, &cw);

				convertIfcCircularArcSegment2D(
					arc, radius, center - centerOffset.block<2, 1>(0, 0), start - centerOffset.block<2, 1>(0, 0), end - centerOffset.block<2, 1>(0, 0), cw);
			} else if (hAlignSegment->getAlignmentType() == buw::eHorizontalAlignmentType::Clothoid) {
				shared_ptr<IfcAlignment2DHorizontalSegment> hs = std::make_shared<IfcAlignment2DHorizontalSegment>(createEntityId());
				model_->insertEntity(hs);
				horizontalAlignment->m_Segments.push_back(hs);

				buw::Vector2d start = hAlignSegment->getStartPosition();
				buw::Vector2d end = hAlignSegment->getEndPosition();

				buw::Vector2d pi;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::PI, &pi);

				double curvatureStart;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::AlignmentCurvatureStart, &curvatureStart);

				double curvatureEnd;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::CurvatureEnd, &curvatureEnd);

				bool clockwise;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Clockwise, &clockwise);

				double length;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Length, &length);

				double startDirection;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::AlignmentStartDirection1D, &startDirection);

				double clothoidConstant;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::ClothoidConstant, &clothoidConstant);
				
				createIfcClothoidalArcSegment2D(hs,
					start - centerOffset.block<2, 1>(0, 0),
					end - centerOffset.block<2, 1>(0, 0),
					curvatureStart,
					curvatureEnd,
					clockwise,
					length,
					startDirection,
					pi - centerOffset.block<2, 1>(0, 0),
					clothoidConstant);
			}
			else if (hAlignSegment->getAlignmentType() == buw::eHorizontalAlignmentType::Bloss) {
				shared_ptr<IfcAlignment2DHorizontalSegment> hs = std::make_shared<IfcAlignment2DHorizontalSegment>(createEntityId());
				model_->insertEntity(hs);
				horizontalAlignment->m_Segments.push_back(hs);

				buw::Vector2d start = hAlignSegment->getStartPosition();
				buw::Vector2d end = hAlignSegment->getEndPosition();

				buw::Vector2d pi;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::PI, &pi);

				double curvatureStart;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::AlignmentCurvatureStart, &curvatureStart);

				double curvatureEnd;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::CurvatureEnd, &curvatureEnd);

				bool clockwise;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Clockwise, &clockwise);

				double length;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Length, &length);

				double startDirection;
				hAlignSegment->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::AlignmentStartDirection1D, &startDirection);

				createIfcBlossCurveSegment2D(hs,
					start - centerOffset.block<2, 1>(0, 0),
					end - centerOffset.block<2, 1>(0, 0),
					curvatureStart,
					curvatureEnd,
					clockwise,
					length,
					startDirection,
					pi - centerOffset.block<2, 1>(0, 0));
				
			} else {
				BLUE_LOG(error) << "Not supported curve type.";
				throw buw::Exception("Not supported curve type.");
			}
		}
	}

	shared_ptr<IfcPlaneAngleMeasure> createIfcPlaneAngleMeasure(const buw::radiand angle) {
		if (settings_.useRadiansInsteadOfDegrees) {
			return std::make_shared<IfcPlaneAngleMeasure>(angle);
		} else {
			return std::make_shared<IfcPlaneAngleMeasure>(buw::radianToDegree(angle));
		}
	}

	void convertIfcCircularArcSegment2D(shared_ptr<IfcAlignment2DHorizontalSegment> arc,
	                                    const double radius,
	                                    const buw::Vector2d& center,
	                                    const buw::Vector2d& start,
	                                    const buw::Vector2d& end,
	                                    const bool cw) {
		shared_ptr<IfcCircularArcSegment2D> curveSegement = std::make_shared<IfcCircularArcSegment2D>(createEntityId());
		model_->insertEntity(curveSegement);
		arc->m_CurveGeometry = curveSegement;

		curveSegement->m_StartPoint = createIfcCartesianPoint(start);

		buw::Vector2d startDirection = buw::createRotationMatrix(-0.5 * buw::constantsd::pi()) * (start - center);

		buw::Vector2d xAxis = buw::Vector2d(1.0, 0.0);
		buw::radiand angle = buw::calculateAngleBetweenVectors(xAxis, startDirection);

		if (!cw) {
			angle += buw::constantsd::pi();
		}

		BLUE_ASSERT(angle < buw::constantsd::pi() * 4.0, "Invalid angle");

		while (angle > buw::constantsd::pi() * 2.0) {
			angle -= buw::constantsd::pi() * 2.0;
		}

		curveSegement->m_StartDirection = createIfcPlaneAngleMeasure(angle);
		curveSegement->m_SegmentLength = std::make_shared<IfcPositiveLengthMeasure>();

		double segmentLength = buw::calculateAngleBetweenVectors(buw::Vector2d(start - center), buw::Vector2d(end - center)) * radius;

		BLUE_ASSERT(segmentLength >= 0, "Invalid segment length");

		if (cw) {
			segmentLength = (2.0 * buw::constantsd::pi() - buw::calculateAngleBetweenVectors(buw::Vector2d(start - center), buw::Vector2d(end - center))) * radius;
		}

		curveSegement->m_SegmentLength->m_value = segmentLength;

		curveSegement->m_Radius = std::make_shared<IfcPositiveLengthMeasure>();
		curveSegement->m_Radius->m_value = radius;
		curveSegement->m_IsCCW = std::make_shared<IfcBoolean>(!cw);
	}

	void exportTerrain(buw::ReferenceCounted<buw::DigitalElevationModel> dem,
	                   buw::Vector3d& centerOffset,
	                   shared_ptr<IfcGeometricRepresentationContext> geometricRepresentationContext,
	                   shared_ptr<IfcRelContainedInSpatialStructure> c2) {
		for (int i = 0; i < dem->getSurfaceCount(); i++) {
			buw::ReferenceCounted<buw::Surface> s = dem->getSurface(i);

			int tempId = getCurrentEntityId();
			if (settings_.useFixedEntityIdForGeometry) {
				setCurrentEntityId(settings_.startId);
			}

			if (settings_.schemaVersion == eIfcSchemaVersion::IFC2x3) {
				std::vector<shared_ptr<IfcFace>> faces;

				for (int faceIndex = 0; faceIndex < s->getTriangleCount(); faceIndex++) {
					std::vector<int> face_indices;

					// reverse order of faces
					/*
					int i1 = s->getTriangeFaces()[faceIndex][0];
					int i2 = s->getTriangeFaces()[faceIndex][2];
					int i3 = s->getTriangeFaces()[faceIndex][1];
					*/

					// do not reverse order - we expect a right hand coordinate system with ccw winded triangles
					int i1 = s->getTriangeFaces()[faceIndex][0];
					int i2 = s->getTriangeFaces()[faceIndex][1];
					int i3 = s->getTriangeFaces()[faceIndex][2];

					buw::Vector3d v1 = s->getPoints()[i1] - centerOffset;
					buw::Vector3d v2 = s->getPoints()[i2] - centerOffset;
					buw::Vector3d v3 = s->getPoints()[i3] - centerOffset;

					std::vector<shared_ptr<IfcCartesianPoint>> points;

					points.push_back(createIfcCartesianPoint(v1.x(), v1.y(), v1.z()));
					points.push_back(createIfcCartesianPoint(v2.x(), v2.y(), v2.z()));
					points.push_back(createIfcCartesianPoint(v3.x(), v3.y(), v3.z()));

					shared_ptr<IfcPolyLoop> polyLoop = createIfcPolyLoop(points);
					shared_ptr<IfcFaceOuterBound> outerBound = createIfcFaceOuterbound(polyLoop);
					faces.push_back(createIfcFace(outerBound));
				}

				shared_ptr<IfcClosedShell> closedShell = createIfcClosedShell(faces);

				auto triangluratedFaceSet = createIfcFacetedBrep(closedShell);

				if (settings_.useFixedEntityIdForGeometry) {
					setCurrentEntityId(tempId);
				}
				//---------------------------

				std::vector<shared_ptr<IfcRepresentation>> representation;
				std::vector<shared_ptr<IfcRepresentationItem>> representationItems;
				representationItems.push_back(triangluratedFaceSet);
				representation.push_back(createIfcShapeRepresentation(representationItems, geometricRepresentationContext));

				shared_ptr<IfcAxis2Placement3D> axisPlacement = createIfcAxis2Placement3D(createIfcCartesianPoint(0, 0, 0));
				shared_ptr<IfcLocalPlacement> localPlacement = createIfcLocalPlacement(axisPlacement);

				auto sr = createIfcProductDefinitionShape(representation);

				shared_ptr<IfcGeographicElement> geographicElement = std::make_shared<IfcGeographicElement>(createEntityId());
				model_->insertEntity(geographicElement);
				geographicElement->m_PredefinedType = std::make_shared<IfcGeographicElementTypeEnum>(IfcGeographicElementTypeEnum::ENUM_TERRAIN);
				geographicElement->m_GlobalId = createGlobalId();
				geographicElement->m_Name = std::make_shared<IfcLabel>("Terrain");
				geographicElement->m_OwnerHistory = nullptr; // ownerHistory;
				geographicElement->m_Representation = sr;
				geographicElement->m_ObjectPlacement = localPlacement;

				// connect GeographicElement with site
				c2->m_RelatedElements.push_back(geographicElement);
			} else {
				shared_ptr<IfcTriangulatedFaceSet> triangluratedFaceSet = std::make_shared<IfcTriangulatedFaceSet>(createEntityId());
				model_->insertEntity(triangluratedFaceSet);

				triangluratedFaceSet->m_Closed = std::make_shared<IfcBoolean>(false);
				triangluratedFaceSet->m_Coordinates = std::make_shared<IfcCartesianPointList3D>(createEntityId());
				model_->insertEntity(triangluratedFaceSet->m_Coordinates);

				// iterate over all points of the current surface element
				for (int pointIndex = 0; pointIndex < s->getPointCount(); pointIndex++) {
					double x = s->getPoints()[pointIndex].x() - centerOffset.x();
					double y = s->getPoints()[pointIndex].y() - centerOffset.y();
					double z = s->getPoints()[pointIndex].z() - centerOffset.z();

					std::vector<shared_ptr<IfcLengthMeasure>> coordinates;
					coordinates.push_back(std::make_shared<IfcLengthMeasure>(x));
					coordinates.push_back(std::make_shared<IfcLengthMeasure>(y));
					coordinates.push_back(std::make_shared<IfcLengthMeasure>(z));

					triangluratedFaceSet->m_Coordinates->m_CoordList.push_back(coordinates);
				}

				for (int faceIndex = 0; faceIndex < s->getTriangleCount(); faceIndex++) {
					std::vector<std::shared_ptr<IfcPositiveInteger>> face_indices;

					// reverse order of faces

					face_indices.push_back(std::make_shared<IfcPositiveInteger>(s->getTriangeFaces()[faceIndex][0] + 1));
					face_indices.push_back(std::make_shared<IfcPositiveInteger>(s->getTriangeFaces()[faceIndex][2] + 1));
					face_indices.push_back(std::make_shared<IfcPositiveInteger>(s->getTriangeFaces()[faceIndex][1] + 1));

					for (int j = 0; j < 3; j++)
						triangluratedFaceSet->m_CoordIndex.push_back(face_indices);
				}

				std::vector<shared_ptr<IfcRepresentation>> representation;
				std::vector<shared_ptr<IfcRepresentationItem>> representationItems;
				representationItems.push_back(triangluratedFaceSet);
				representation.push_back(createIfcShapeRepresentation(representationItems, geometricRepresentationContext));

				shared_ptr<IfcAxis2Placement3D> axisPlacement = createIfcAxis2Placement3D(createIfcCartesianPoint(0, 0, 0));
				shared_ptr<IfcLocalPlacement> localPlacement = createIfcLocalPlacement(axisPlacement);

				auto sr = createIfcProductDefinitionShape(representation);

				shared_ptr<IfcGeographicElement> geographicElement = std::make_shared<IfcGeographicElement>(createEntityId());
				model_->insertEntity(geographicElement);
				geographicElement->m_PredefinedType = std::make_shared<IfcGeographicElementTypeEnum>(IfcGeographicElementTypeEnum::ENUM_TERRAIN);
				geographicElement->m_GlobalId = createGlobalId();
				geographicElement->m_Name = std::make_shared<IfcLabel>("Terrain");
				geographicElement->m_OwnerHistory = nullptr; // ownerHistory;
				geographicElement->m_Representation = sr;
				geographicElement->m_ObjectPlacement = localPlacement;

				// connect GeographicElement with site
				c2->m_RelatedElements.push_back(geographicElement);
			}
		}
	}

	shared_ptr<IfcFaceOuterBound> createIfcFaceOuterbound(shared_ptr<IfcPolyLoop> polyLoop) {
		shared_ptr<IfcFaceOuterBound> outerBound = std::make_shared<IfcFaceOuterBound>(createEntityId());
		model_->insertEntity(outerBound);
		outerBound->m_Bound = polyLoop;
		outerBound->m_Orientation = std::make_shared<IfcBoolean>(true);

		return outerBound;
	}

	shared_ptr<IfcPolyLoop> createIfcPolyLoop(std::vector<shared_ptr<IfcCartesianPoint>> points) {
		shared_ptr<IfcPolyLoop> polyLoop = std::make_shared<IfcPolyLoop>(createEntityId());
		polyLoop->m_Polygon = points;
		model_->insertEntity(polyLoop);
		return polyLoop;
	}

	shared_ptr<IfcShapeRepresentation> createIfcShapeRepresentation(std::vector<shared_ptr<IfcRepresentationItem>> representationItems,
	                                                                shared_ptr<IfcRepresentationContext> context,
	                                                                std::string representationIdentifier = "Body",
	                                                                std::string representationType = "Tessellation") {
		shared_ptr<IfcShapeRepresentation> shapeRepresentation = std::make_shared<IfcShapeRepresentation>(createEntityId());
		model_->insertEntity(shapeRepresentation);
		shapeRepresentation->m_ContextOfItems = context;
		shapeRepresentation->m_Items = representationItems;
		shapeRepresentation->m_RepresentationIdentifier = std::make_shared<IfcLabel>(representationIdentifier.c_str());
		shapeRepresentation->m_RepresentationType = std::make_shared<IfcLabel>(representationType.c_str());
		return shapeRepresentation;
	}

	shared_ptr<IfcOrganization> createIfcOrganization() {
		shared_ptr<IfcOrganization> organization = std::make_shared<IfcOrganization>(createEntityId());
		model_->insertEntity(organization);
		// organization->m_Identification = std::make_shared<IfcIdentifier>("TUM");
		organization->m_Name = std::make_shared<IfcLabel>("TUM");
		organization->m_Description = std::make_shared<IfcText>("Chair of Computational Modeling and Simulation");
		return organization;
	}

	shared_ptr<IfcApplication> createIfcApplication(shared_ptr<IfcOrganization> applicationDeveloper) {
		shared_ptr<IfcApplication> application = std::make_shared<IfcApplication>(createEntityId());
		model_->insertEntity(application);
		application->m_ApplicationDeveloper = applicationDeveloper;
		application->m_Version = std::make_shared<IfcLabel>("RTM");
		application->m_ApplicationFullName = std::make_shared<IfcLabel>("TUM Open Infra Platform 2017");
		application->m_ApplicationIdentifier = std::make_shared<IfcIdentifier>("OIP");
		return application;
	}

	shared_ptr<IfcUnitAssignment> createIfcUnitAssignment() {
		shared_ptr<IfcUnitAssignment> unitAssignment = std::make_shared<IfcUnitAssignment>(createEntityId());
		model_->insertEntity(unitAssignment);

		// length unit [m]
		shared_ptr<IfcSIUnit> lengthUnit = std::make_shared<IfcSIUnit>(createEntityId());
		model_->insertEntity(lengthUnit);
		// lengthUnit->m_Prefix = std::make_shared<IfcSIPrefix>(IfcSIPrefix::ENUM_MILLI);
		lengthUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_LENGTHUNIT);
		lengthUnit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_METRE);
		unitAssignment->m_Units.push_back(lengthUnit);

		// plane unit [rad/degree]
		if (settings_.useRadiansInsteadOfDegrees) {
			auto unit = std::make_shared<IfcSIUnit>(createEntityId());
			model_->insertEntity(unit);
			unit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_PLANEANGLEUNIT);
			unit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_RADIAN);

			unitAssignment->m_Units.push_back(unit);
		} else {
			shared_ptr<IfcConversionBasedUnit> conversionBasedUnit = std::make_shared<IfcConversionBasedUnit>(createEntityId());
			model_->insertEntity(conversionBasedUnit);

			auto conversionFactor = std::make_shared<IfcMeasureWithUnit>(createEntityId());
			model_->insertEntity(conversionFactor);

			conversionFactor->m_ValueComponent = std::make_shared<IfcPlaneAngleMeasure>(0.017453293);

			auto unit = std::make_shared<IfcSIUnit>(createEntityId());
			model_->insertEntity(unit);

			unit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_PLANEANGLEUNIT);
			unit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_RADIAN);
			conversionFactor->m_UnitComponent = unit;

			shared_ptr<IfcDimensionalExponents> dimensionalExponents = zeroDimExp_;

			conversionBasedUnit->m_Dimensions = dimensionalExponents;
			conversionBasedUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_PLANEANGLEUNIT);
			conversionBasedUnit->m_Name = std::make_shared<IfcLabel>("degree");
			conversionBasedUnit->m_ConversionFactor = conversionFactor;

			unitAssignment->m_Units.push_back(conversionBasedUnit);
		}

		// area unit
		shared_ptr<IfcSIUnit> areaUnit = std::make_shared<IfcSIUnit>(createEntityId());
		model_->insertEntity(areaUnit);
		areaUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_AREAUNIT);
		areaUnit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_SQUARE_METRE);
		unitAssignment->m_Units.push_back(areaUnit);

		// volume unit
		shared_ptr<IfcSIUnit> volumeUnit = std::make_shared<IfcSIUnit>(createEntityId());
		model_->insertEntity(volumeUnit);
		volumeUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_VOLUMEUNIT);
		volumeUnit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_CUBIC_METRE);

		unitAssignment->m_Units.push_back(volumeUnit);

		return unitAssignment;
	}

	shared_ptr<IfcAxis2Placement3D> createIfcAxis2Placement3D(shared_ptr<IfcCartesianPoint> location) {
		shared_ptr<IfcAxis2Placement3D> ap = std::make_shared<IfcAxis2Placement3D>(createEntityId());
		model_->insertEntity(ap);
		ap->m_Location = location;
		return ap;
	}

	shared_ptr<IfcLocalPlacement> createIfcLocalPlacement(shared_ptr<IfcAxis2Placement3D> axisPlacement) {
		shared_ptr<IfcLocalPlacement> lp = std::make_shared<IfcLocalPlacement>(createEntityId());
		model_->insertEntity(lp);
		lp->m_RelativePlacement = axisPlacement;
		return lp;
	}

	shared_ptr<IfcCartesianPoint> createIfcCartesianPoint(const buw::Vector3d& positon) {
		return createIfcCartesianPoint(positon.x(), positon.y(), positon.z());
	}

	shared_ptr<IfcClosedShell> createIfcClosedShell(std::vector<shared_ptr<IfcFace>> faces) {
		shared_ptr<IfcClosedShell> shell = std::make_shared<IfcClosedShell>(createEntityId());
		model_->insertEntity(shell);

		shell->m_CfsFaces = faces;

		return shell;
	}

	shared_ptr<IfcCartesianPoint> createIfcCartesianPoint(const float x, const float y, const float z) {
		shared_ptr<IfcCartesianPoint> point = std::make_shared<IfcCartesianPoint>(createEntityId());
		model_->insertEntity(point);
		point->m_Coordinates.push_back(std::make_shared<IfcLengthMeasure>(x));
		point->m_Coordinates.push_back(std::make_shared<IfcLengthMeasure>(y));
		point->m_Coordinates.push_back(std::make_shared<IfcLengthMeasure>(z));
		return point;
	}

	shared_ptr<IfcCartesianPoint> createIfcCartesianPoint(const double x, const double y) {
		shared_ptr<IfcCartesianPoint> pnt = std::make_shared<IfcCartesianPoint>(entityId_++);
		model_->insertEntity(pnt);

		pnt->m_Coordinates.push_back(std::make_shared<IfcLengthMeasure>(x));
		pnt->m_Coordinates.push_back(std::make_shared<IfcLengthMeasure>(y));

		return pnt;
	}

	shared_ptr<IfcCartesianPoint> createIfcCartesianPoint(const buw::Vector2d& point) {
		shared_ptr<IfcCartesianPoint> pnt = std::make_shared<IfcCartesianPoint>(entityId_++);
		model_->insertEntity(pnt);

		pnt->m_Coordinates.push_back(std::make_shared<IfcLengthMeasure>(point.x()));
		pnt->m_Coordinates.push_back(std::make_shared<IfcLengthMeasure>(point.y()));

		return pnt;
	}

	shared_ptr<IfcFace> createIfcFace(shared_ptr<IfcFaceOuterBound> outerBound) {
		shared_ptr<IfcFace> face = std::make_shared<IfcFace>(createEntityId());
		model_->insertEntity(face);
		face->m_Bounds.push_back(outerBound);
		return face;
	}

	shared_ptr<IfcFacetedBrep> createIfcFacetedBrep(shared_ptr<IfcClosedShell> closedShell) {
		shared_ptr<IfcFacetedBrep> facetedBrep = std::make_shared<IfcFacetedBrep>(createEntityId());
		model_->insertEntity(facetedBrep);
		facetedBrep->m_Outer = closedShell;
		return facetedBrep;
	}

	shared_ptr<IfcRepresentationContext> createIfcRepresentationContext() {
		shared_ptr<IfcRepresentationContext> rc = std::make_shared<IfcRepresentationContext>(createEntityId());
		model_->insertEntity(rc);
		return rc;
	}

	shared_ptr<IfcProductDefinitionShape> createIfcProductDefinitionShape(std::vector<shared_ptr<IfcRepresentation>> representation) {
		shared_ptr<IfcProductDefinitionShape> productDefinitionShape = std::make_shared<IfcProductDefinitionShape>(createEntityId());
		model_->insertEntity(productDefinitionShape);
		productDefinitionShape->m_Representations = representation;
		return productDefinitionShape;
	}

	shared_ptr<IfcOwnerHistory> createIfcOwnerHistory(shared_ptr<IfcPersonAndOrganization> personAndOrganization, shared_ptr<IfcApplication> application) {
		shared_ptr<IfcOwnerHistory> oh = std::make_shared<IfcOwnerHistory>(createEntityId());
		model_->insertEntity(oh);
		oh->m_OwningUser = personAndOrganization;
		oh->m_OwningApplication = application;
		// oh->m_State = std::make_shared<IfcStateEnum>( IfcStateEnum::ENUM_READONLY );
		oh->m_ChangeAction = std::make_shared<IfcChangeActionEnum>(IfcChangeActionEnum::ENUM_NOCHANGE);
		oh->m_CreationDate = std::make_shared<IfcTimeStamp>(0);
		return oh;
	}

	shared_ptr<IfcPersonAndOrganization> createIfcPersonAndOrganization(shared_ptr<IfcPerson> person, shared_ptr<IfcOrganization> organization) {
		shared_ptr<IfcPersonAndOrganization> pao = std::make_shared<IfcPersonAndOrganization>(createEntityId());
		model_->insertEntity(pao);
		pao->m_ThePerson = person;
		pao->m_TheOrganization = organization;
		return pao;
	}

	void createIfcLineSegment2D(shared_ptr<IfcAlignment2DHorizontalSegment> line, const buw::Vector2d& start, const buw::Vector2d& end) {
		shared_ptr<IfcLineSegment2D> curveSegement = std::make_shared<IfcLineSegment2D>(createEntityId());
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

	void createIfcBlossCurveSegment2D(shared_ptr<IfcAlignment2DHorizontalSegment> clothoid,
		const buw::Vector2d& start,
		const buw::Vector2d& end,
		const double curvatureStart,
		const double curvatureEnd,
		const bool clockwise,
		const double length,
		const buw::radiand startDirection,
		const buw::Vector2d& CheckPointOfIntersection) {
		shared_ptr<IfcTransitionCurveSegment2D> curveSegement = std::make_shared<IfcTransitionCurveSegment2D>(createEntityId());
		model_->insertEntity(curveSegement);
		clothoid->m_CurveGeometry = curveSegement;

		curveSegement->m_StartPoint = createIfcCartesianPoint(start);
		curveSegement->m_StartDirection = createIfcPlaneAngleMeasure(startDirection);
		curveSegement->m_SegmentLength = std::make_shared<IfcPositiveLengthMeasure>();
		curveSegement->m_SegmentLength->m_value = length;

		if (curvatureStart == 0.0) {
			curveSegement->m_StartRadius = nullptr; // There is no INF value in STEP - convention: store INF values as not available values
		}
		else {
			curveSegement->m_StartRadius = std::make_shared<IfcPositiveLengthMeasure>();
			curveSegement->m_StartRadius->m_value = (1.0 / curvatureStart);
		}

		if (curvatureEnd == 0.0) {
			curveSegement->m_EndRadius = nullptr; // There is no INF value in STEP - convention: store INF values as not available values
		}
		else {
			curveSegement->m_EndRadius = std::make_shared<IfcPositiveLengthMeasure>();
			curveSegement->m_EndRadius->m_value = (1.0 / curvatureEnd);
		}

		curveSegement->m_IsStartRadiusCCW = std::make_shared<IfcBoolean>(!clockwise);

		// IsStartRadiusCCW equals to IsEndRadiusCCW if the transition curve is a clothoid!
		curveSegement->m_IsEndRadiusCCW = std::make_shared<IfcBoolean>(curveSegement->m_IsStartRadiusCCW->m_value);

		curveSegement->m_TransitionCurveType = std::make_shared<IfcTransitionCurveType>(IfcTransitionCurveType::ENUM_BLOSSCURVE);
	}

	void createIfcClothoidalArcSegment2D(shared_ptr<IfcAlignment2DHorizontalSegment> clothoid,
	                                     const buw::Vector2d& start,
	                                     const buw::Vector2d& end,
	                                     const double curvatureStart,
	                                     const double curvatureEnd,
	                                     const bool clockwise,
	                                     const double length,
	                                     const buw::radiand startDirection,
	                                     const buw::Vector2d& CheckPointOfIntersection,
	                                     const double clothoidConstant) {

		bool useOldClothoidType = false;

		if (useOldClothoidType)
		{
			shared_ptr<IfcClothoidalArcSegment2D> curveSegement = std::make_shared<IfcClothoidalArcSegment2D>(createEntityId());
			model_->insertEntity(curveSegement);
			clothoid->m_CurveGeometry = curveSegement;

			curveSegement->m_StartPoint = createIfcCartesianPoint(start);
			curveSegement->m_StartDirection = createIfcPlaneAngleMeasure(startDirection);
			curveSegement->m_SegmentLength = std::make_shared<IfcPositiveLengthMeasure>();
			curveSegement->m_SegmentLength->m_value = length;

			if (curvatureStart == 0.0) {
				curveSegement->m_StartRadius = nullptr; // There is no INF value in STEP - convention: store INF values as not available values
			} else {
				curveSegement->m_StartRadius = std::make_shared<IfcPositiveLengthMeasure>();
				curveSegement->m_StartRadius->m_value = (1.0 / curvatureStart);
			}

			curveSegement->m_IsCCW = std::make_shared<IfcBoolean>(!clockwise);

			if (curvatureStart < curvatureEnd) {
				curveSegement->m_IsEntry = std::make_shared<IfcBoolean>(true);
			} else {
				curveSegement->m_IsEntry = std::make_shared<IfcBoolean>(false);
			}

			curveSegement->m_ClothoidConstant = std::make_shared<IfcReal>(clothoidConstant);
		}
		else
		{
			shared_ptr<IfcTransitionCurveSegment2D> curveSegement = std::make_shared<IfcTransitionCurveSegment2D>(createEntityId());
			model_->insertEntity(curveSegement);
			clothoid->m_CurveGeometry = curveSegement;

			curveSegement->m_StartPoint = createIfcCartesianPoint(start);
			curveSegement->m_StartDirection = createIfcPlaneAngleMeasure(startDirection);
			curveSegement->m_SegmentLength = std::make_shared<IfcPositiveLengthMeasure>();
			curveSegement->m_SegmentLength->m_value = length;

			if (curvatureStart == 0.0) {
				curveSegement->m_StartRadius = nullptr; // There is no INF value in STEP - convention: store INF values as not available values
			}
			else {
				curveSegement->m_StartRadius = std::make_shared<IfcPositiveLengthMeasure>();
				curveSegement->m_StartRadius->m_value = (1.0 / curvatureStart);
			}

			if (curvatureEnd == 0.0) {
				curveSegement->m_EndRadius = nullptr; // There is no INF value in STEP - convention: store INF values as not available values
			}
			else {
				curveSegement->m_EndRadius = std::make_shared<IfcPositiveLengthMeasure>();
				curveSegement->m_EndRadius->m_value = (1.0 / curvatureEnd);
			}

			curveSegement->m_IsStartRadiusCCW = std::make_shared<IfcBoolean>(!clockwise);

			// IsStartRadiusCCW equals to IsEndRadiusCCW if the transition curve is a clothoid!
			curveSegement->m_IsEndRadiusCCW = std::make_shared<IfcBoolean>(curveSegement->m_IsStartRadiusCCW->m_value);

			curveSegement->m_TransitionCurveType = std::make_shared<IfcTransitionCurveType>(IfcTransitionCurveType::ENUM_CLOTHOIDCURVE);
		}
	}

	double mapAngleToRatioMeasure(buw::degreef angle) const {
		if (angle <= 180.0) {
			angle = angle / 45.0;
		} else {
			if (angle > 270.0) {
				angle = 360.0 - angle;

				angle = -1.0f * angle / 45.0;
			} else {
				angle = 0;
				BLUE_LOG(error) << "Invalid angle.";
			}
		}

		return angle;
	}

	shared_ptr<IfcPerson> createIfcPerson() {
		shared_ptr<IfcPerson> person = std::make_shared<IfcPerson>(createEntityId());
		model_->insertEntity(person);
		person->m_FamilyName = std::make_shared<IfcLabel>("User (FamilyName)");
		person->m_GivenName = std::make_shared<IfcLabel>("User (GivenName)");
		// person->m_MiddleNames.push_back(std::make_shared<IfcLabel>(""));
		return person;
	}

	int getCurrentEntityId() const {
		return entityId_;
	}

	void setCurrentEntityId(int id) {
		entityId_ = id;
	}

	int createEntityId() {
		return entityId_++;
	}

	shared_ptr<IfcGloballyUniqueId> createGlobalId() {
		std::string guid = CreateCompressedGuidString22();

		return std::make_shared<IfcGloballyUniqueId>(guid);
	}

private:
	shared_ptr<IfcLocalPlacement> site_localPlacement;

	std::shared_ptr<IfcAlignment1x1Model> model_;
	int entityId_;
	ifcAlignmentExportDescription settings_;

	shared_ptr<IfcDimensionalExponents> zeroDimExp_ = nullptr;
	shared_ptr<IfcGeometricRepresentationSubContext> subcontextAxis = nullptr;
};

void OpenInfraPlatform::Infrastructure::exportIfcAlignment1x1(buw::ReferenceCounted<buw::AlignmentModel> am,
                                                              buw::ReferenceCounted<buw::DigitalElevationModel> dem,
                                                              const std::string& filename) {
}

OpenInfraPlatform::Infrastructure::ExportIfcAlignment1x1::ExportIfcAlignment1x1(const ifcAlignmentExportDescription& desc,
                                                                                buw::ReferenceCounted<buw::AlignmentModel> am,
                                                                                buw::ReferenceCounted<buw::DigitalElevationModel> dem,
                                                                                const std::string& filename)
    : Export(am, dem, filename), impl_(new IfcAlignment1x1ExportImpl(desc, am, dem, filename)) {
}

OpenInfraPlatform::Infrastructure::ExportIfcAlignment1x1::~ExportIfcAlignment1x1() {
}
