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

#include "ImportIfcAlignment1x1.h"

#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment2DBased3D.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment3DBased3D.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DArc.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DBlossCurve.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DParabola.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DArc.h"
#include "OpenInfraPlatform/Infrastructure/SlabField/SlabField.h"
#include "OpenInfraPlatform/Infrastructure/SlabField/Railing.h"
#include "OpenInfraPlatform/Infrastructure/Tessellation/Tessellation.h"

#include "OpenInfraPlatform/IfcAlignment1x1/model/Model.h"
#include "OpenInfraPlatform/IfcAlignment1x1/model/Exception.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/IfcStepReader.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/IfcStepWriter.h"
#include "OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1Entities.h"
#include "OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1Types.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/IfcStepReader.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/Reader.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/IfcStepReader.h"
#include "OpenInfraPlatform/IfcAlignment1x1/model/UnitConverter.h"
#include "OpenInfraPlatform/IfcAlignment1x1/entity/IfcCartesianPoint.h"
#include "OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1EntityEnums.h"

#include <cmath>
#include <fstream>
#include <limits>
#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include <functional>

using namespace OpenInfraPlatform::IfcAlignment1x1;

class OpenInfraPlatform::Infrastructure::ImportIfcAlignment1x1::ImportIfcAlignment1x1Impl : public Import
{
public:
	ImportIfcAlignment1x1Impl(const std::string& filename)
		: Import(filename)
		, offset_(0.0, 0.0, 0.0)
		, project_()
		, unitConv_()
		, geometryPrecision_(std::numeric_limits<double>::epsilon())
		, aggregations_()
		, spatialContainments_()
	{
		const bool importTerrain = true;
		const bool importAlignment = true;
		const bool importProxyElements = true; // e.g. traffic signs
		const bool importGirders = true;
		const bool importSlabFields = true;

		shared_ptr<IfcStepReader> m_step_reader = shared_ptr<IfcStepReader>(new IfcStepReader());
		shared_ptr<IfcAlignment1x1Model> m_ifc_model(new IfcAlignment1x1Model());

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
		std::map<int, shared_ptr<IfcAlignment1x1Entity> > map_entities;

		try
		{
			m_step_reader->readStreamData(buffer, map_entities);
		}
		catch (IfcAlignment1x1Exception& e)
		{
			throw buw::Exception(e.what());
		}

		// get offset value and project entity!
		for (auto it = map_entities.begin(); it != map_entities.end(); it++)
		{
			switch (it->second->m_entity_enum)
			{
			case IFCMAPCONVERSION:
			{
				std::shared_ptr<IfcMapConversion> mapConversion = std::static_pointer_cast<IfcMapConversion>(it->second);

				BLUE_ASSERT(mapConversion->m_Eastings != nullptr, "Invalid easting.");
				BLUE_ASSERT(mapConversion->m_Northings != nullptr, "Invalid northing.");
				BLUE_ASSERT(mapConversion->m_OrthogonalHeight != nullptr, "Invalid orthogonal height.");

				offset_.x() = mapConversion->m_Eastings->m_value;
				offset_.y() = mapConversion->m_Northings->m_value;
				offset_.z() = mapConversion->m_OrthogonalHeight->m_value;
			} break;
			case IFCPROJECT:
				project_ = std::static_pointer_cast<IfcProject>(it->second);
				unitConv_.setIfcProject(project_);
				for (auto representationContext : project_->m_RepresentationContexts)
				{
					if (representationContext->m_entity_enum == IFCGEOMETRICREPRESENTATIONCONTEXT)
					{
						auto geoRepresentationContext = std::static_pointer_cast<IfcGeometricRepresentationContext>(representationContext);
						if(geoRepresentationContext->m_Precision)
							geometryPrecision_ = geoRepresentationContext->m_Precision->m_value;
						break;
					}
				}
				break;
			case IFCRELAGGREGATES:
			{
				auto aggregation = std::static_pointer_cast<IfcRelAggregates>(it->second);
				if (aggregation->m_RelatingObject)
				{
					BLUE_ASSERT(aggregations_.find(aggregation->m_RelatingObject) == aggregations_.end(),
						"One and the same aggregating object has multiple aggregation relationships.");
					aggregations_[aggregation->m_RelatingObject] = aggregation;
				}
			} break;
			case IFCRELCONTAINEDINSPATIALSTRUCTURE:
			{
				auto spatialContainment = std::static_pointer_cast<IfcRelContainedInSpatialStructure>(it->second);
				spatialContainments_.insert(spatialContainment->m_RelatedElements.begin(), spatialContainment->m_RelatedElements.end());
			} break;
			}
		}

		for (auto it = map_entities.begin(); it != map_entities.end(); it++)
		{
			int id = it->second->m_entity_enum;
			if (importAlignment)
			{
				if (it->second->m_entity_enum == IFCALIGNMENT)
				{
					std::shared_ptr<IfcAlignment> alignment = 
						std::static_pointer_cast<IfcAlignment>(it->second);
					createAlignment(alignment);
				}
			}

			if (importTerrain)
			{
				if (it->second->m_entity_enum == IFCGEOGRAPHICELEMENT) {
					auto geographicElement = std::static_pointer_cast<IfcGeographicElement>(it->second);

					if (geographicElement != nullptr) {
						if (geographicElement->m_PredefinedType != nullptr) {
							if (geographicElement->m_PredefinedType->m_enum == IfcGeographicElementTypeEnum::ENUM_TERRAIN) {
								// try to read IfcProductRepresentation
								if (geographicElement->m_Representation) {
									if (geographicElement->m_Representation->m_entity_enum == IFCPRODUCTDEFINITIONSHAPE) {
										auto pds = std::static_pointer_cast<IfcProductDefinitionShape>(geographicElement->m_Representation);
										for (int i = 0; i < pds->m_Representations.size(); ++i) {
											for (int representationItemIndex = 0; representationItemIndex < pds->m_Representations[i]->m_Items.size(); ++representationItemIndex) {
												auto item = pds->m_Representations[i]->m_Items[representationItemIndex];

												if (item->m_entity_enum == IFCTRIANGULATEDFACESET) {
													auto triangluatedFaceSet = std::static_pointer_cast<IfcTriangulatedFaceSet>(item);
													createTerrainSurface(triangluatedFaceSet);
												}
											}
										}
									}
								}
							}
						}
					}
				}

				//if (it->second->m_entity_enum == IFCTRIANGULATEDFACESET)
				//{
				//	std::shared_ptr<IfcTriangulatedFaceSet> triangluatedFaceSet = std::static_pointer_cast<IfcTriangulatedFaceSet>(it->second);
				//	createTerrainSurface(triangluatedFaceSet);
				//}
			} // endif importTerrain

			if(importProxyElements)	{
				if (it->second->m_entity_enum == IFCBUILDINGELEMENTPROXY) {
					buw::ReferenceCounted<buw::TrafficSign> trafficSign = buw::makeReferenceCounted<buw::TrafficSign>();

					auto proxy = std::static_pointer_cast<IfcBuildingElementProxy>(it->second);

					if (proxy->m_ObjectPlacement != nullptr) {
						if (proxy->m_ObjectPlacement->m_entity_enum == IFCLINEARPLACEMENT) {
							auto lp = std::static_pointer_cast<IfcLinearPlacement>(proxy->m_ObjectPlacement);

							if (lp->m_PlacementRelTo->m_entity_enum == IFCALIGNMENTCURVE) {
								auto alignmentCurve = std::static_pointer_cast<IfcAlignmentCurve>(lp->m_PlacementRelTo);

								std::cout << alignmentCurve->getId() << std::endl;
								trafficSign->alignmentId = alignmentCurve->getId();
							}

							if (lp->m_Distance != nullptr) {
								trafficSign->distanceAlong =  lp->m_Distance->m_DistanceAlong->m_value;

								if (lp->m_Distance->m_AlongHorizontal) {
									trafficSign->bAlongHorizontal = lp->m_Distance->m_AlongHorizontal->m_value;
								}

								if (lp->m_Distance->m_OffsetLateral) {
									trafficSign->offsetLateral = lp->m_Distance->m_OffsetLateral->m_value;
								}
							}

							if (lp->m_Orientation != nullptr) {
								if (lp->m_Orientation->m_LateralAxisDirection) {
									double x= lp->m_Orientation->m_LateralAxisDirection->m_DirectionRatios[0]->m_value;
									double y = lp->m_Orientation->m_LateralAxisDirection->m_DirectionRatios[1]->m_value;
									double z = lp->m_Orientation->m_LateralAxisDirection->m_DirectionRatios[2]->m_value;

									buw::Vector3d lateralDirection(x, y, z);
									buw::Vector3d standardLateralDirection(0, 1, 0);

									double rotation = buw::calculateAngleBetweenVectors(standardLateralDirection, lateralDirection);
									trafficSign->rotation = rotation;
									rotation = buw::radianToDegree(rotation);
									std::cout << rotation << std::endl;
								}
							}
						}
					}

					if (proxy->m_Representation != nullptr) {
						if (proxy->m_Representation->m_entity_enum == IFCPRODUCTDEFINITIONSHAPE) {
							auto pds = std::static_pointer_cast<IfcProductDefinitionShape>(proxy->m_Representation);
							for (int i = 0; i < pds->m_Representations.size(); ++i) {
								
								for (int representationItemIndex = 0; representationItemIndex < pds->m_Representations[i]->m_Items.size(); ++representationItemIndex) {

									auto item = pds->m_Representations[i]->m_Items[representationItemIndex];
							
									if (item->m_entity_enum == IFCTRIANGULATEDFACESET) {
										auto triangluatedFaceSet = std::static_pointer_cast<IfcTriangulatedFaceSet>(item);
										createTrafficSign(triangluatedFaceSet, trafficSign);
									}
								}
							}
						}
					}

					trafficSignModel_->addTrafficSign(trafficSign);
				}
			}

			if ((importGirders || importSlabFields) && it->second->m_entity_enum == IFCELEMENTASSEMBLY)
			{
				auto assembly = std::static_pointer_cast<IfcElementAssembly>(it->second);

				// Only top-level assemblies.
				if (spatialContainments_.find(assembly) != spatialContainments_.end())
				{
					// Handle assembly's own explicit representation.
					if(assembly->m_Representation)
						for (auto repr : assembly->m_Representation->m_Representations)
							for (auto reprItem : repr->m_Items)
								if(reprItem && reprItem->m_entity_enum == IFCGEOMETRICREPRESENTATIONITEM)
									throw buw::NotImplementedYetException("Assembly self geometric representation not implemented.");

					if (assembly->m_PredefinedType)
					{
						switch (assembly->m_PredefinedType->m_enum)
						{
						case IfcElementAssemblyTypeEnum::ENUM_GIRDER:
						{
							auto ssh = createSectionedSolidHorizontals(assembly);
							if (!ssh.empty())
							{
								auto girder = std::make_shared<Girder>(
									assembly->getId(),
									assembly->m_Name ? buw::String::toWStdString(assembly->m_Name->m_value) : L"Girder");
								girder->addSectionedSolid(ssh);
								girderModel_->addItem(girder);
							}
						} break;
						case IfcElementAssemblyTypeEnum::ENUM_SLAB_FIELD:
						{
							auto ssh = createSectionedSolidHorizontals(assembly);
							if (!ssh.empty())
							{
								auto slabField = std::make_shared<SlabField>(
									assembly->getId(),
									assembly->m_Name ? buw::String::toWStdString(assembly->m_Name->m_value) : L"SlabField");
								slabField->addSectionedSolid(ssh);
								slabFieldModel_->addItem(slabField);
							}
						} break;
						default:
							throw buw::NotImplementedYetException("Unimplemented assembly type.");
						}
					}
				}
			}

			if (importSlabFields && it->second->m_entity_enum == IFCRAILING)
			{
				auto ifcRailing = std::static_pointer_cast<IfcRailing>(it->second);
				if (ifcRailing->m_PredefinedType && ifcRailing->m_PredefinedType->m_enum == IfcRailingTypeEnum::ENUM_GUARDRAIL)
				{
					auto ssh = createSectionedSolidHorizontals(ifcRailing);
					if (!ssh.empty())
					{
						auto railing = std::make_shared<Railing>(
							ifcRailing->getId(),
							ifcRailing->m_Name ? buw::String::toWStdString(ifcRailing->m_Name->m_value) : L"Railing");
						railing->addSectionedSolid(ssh);
						slabFieldModel_->addItem(railing);
					}
				}
				else
					throw buw::NotImplementedYetException("Unimplemented railing type.");
			}
		}
	}

	buw::Vector3d computeOffsetPoint(
		std::shared_ptr<buw::HorizontalAlignment2D> horiz,
		std::shared_ptr<buw::VerticalAlignment2D> vert,
		double const dStation,
		double const dOffsetLateral,
		double const dOffsetVertical,
		double const dOffsetLongitudinal,
		std::pair<buw::Vector2d, buw::Vector2d>* pHorizontalTangentAndNormalOut = nullptr)
	{
		auto const& horizPos = horiz->getPosition(dStation);
		auto const& horizNormal = horiz->getNormal(dStation);
		auto const& horizTangent = horiz->getTangent(dStation);
		double const dHeight = vert ? vert->getPosition(dStation)[1] : 0.0;

		if (pHorizontalTangentAndNormalOut)
			*pHorizontalTangentAndNormalOut = std::make_pair(horizTangent, horizNormal);

		auto const& newHorizPos = horizPos + dOffsetLateral * horizNormal + dOffsetLongitudinal * horizTangent;
		return buw::Vector3d(
			newHorizPos[0] + offset_.x(),
			newHorizPos[1] + offset_.y(),
			dHeight + dOffsetVertical + offset_.z());
	}

	std::shared_ptr<Alignment3DBased3D> sampleIfcAlignmentCurve(
		std::shared_ptr<IfcAlignmentCurve> ifcAlignmentCurve,
		std::vector<std::shared_ptr<IfcDistanceExpression>> stations,
		bool const bExtendToHeadAndTail = false,
		std::vector<std::pair<buw::Vector2d, buw::Vector2d>>* pHorizontalTangentsAndNormalsOut = nullptr,
		bool const bAdaptiveSampling = false)
	{
		using namespace std::placeholders;
		auto h = createHorizontalAlignment(ifcAlignmentCurve);
		if (!h || h->getAlignmentElementCount() < 1) return nullptr; // At least the horizontal alignment is mandatory.
		auto v = createVerticalAlignment(ifcAlignmentCurve);
		double const dStartStation = h->getStartStation();
		double const dEndStation = h->getEndStation();
		auto alignment = std::make_shared<buw::Alignment3DBased3D>(dStartStation, Alignment3DBased3DType::Polyline /*Spline*/);
		std::pair<buw::Vector2d, buw::Vector2d> horizontalTangentAndNormal;

		// Sample the 2D alignments, offset the samples and add them to the 3D curve.
		// From the specification (IfcOffsetCurveByDistances):
		// "If the offsets do not span the full extent of the basis curve (e.g. if the list contains only one item),
		// then the lateral and vertical offsets implicitly continue with the same value towards the head and tail of
		// the basis curve."

		// Extend towards the head of the basis curve, if needed.
		if (bExtendToHeadAndTail && !stations.empty())
		{
			auto firstStation = stations.front();
			if (firstStation->m_AlongHorizontal && firstStation->m_AlongHorizontal->m_value
				&& fabs(firstStation->m_DistanceAlong->m_value - dStartStation) > geometryPrecision_)
			{
				double const dOffsetLateral = firstStation->m_OffsetLateral ? firstStation->m_OffsetLateral->m_value : 0.0;
				double const dOffsetVertical = firstStation->m_OffsetVertical ? firstStation->m_OffsetVertical->m_value : 0.0;
				double const dOffsetLongitudinal = 0.0;
				if (bAdaptiveSampling && ((firstStation->m_DistanceAlong->m_value - dStartStation) > geometryPrecision_))
				{
					auto const& eval = std::bind<buw::Vector3d>(&ImportIfcAlignment1x1Impl::computeOffsetPoint, this, _2, _3, _1,
						dOffsetLateral, dOffsetVertical, dOffsetLongitudinal, _4);
					Tessellation::tessellate(dStartStation, firstStation->m_DistanceAlong->m_value, h, v,
						alignment, pHorizontalTangentsAndNormalsOut, eval, false, true);
				}
				else
				{
					alignment->addPoint(computeOffsetPoint(h, v, dStartStation, dOffsetLateral, dOffsetVertical,
						dOffsetLongitudinal, &horizontalTangentAndNormal));
					if (pHorizontalTangentsAndNormalsOut)
						pHorizontalTangentsAndNormalsOut->push_back(horizontalTangentAndNormal);
				}
			}
		}

		std::shared_ptr<IfcDistanceExpression> lastStation;
		for (size_t i = 0; i < stations.size(); ++i)
		{
			auto station = stations[i];
			if (!station->m_AlongHorizontal || !station->m_AlongHorizontal->m_value)
				throw buw::NotImplementedYetException("Only horizontal distances are supported.");
			double const dOffsetLateral = station->m_OffsetLateral ? station->m_OffsetLateral->m_value : 0.0;
			double const dOffsetVertical = station->m_OffsetVertical ? station->m_OffsetVertical->m_value : 0.0;
			double const dOffsetLongitudinal = station->m_OffsetLongitudinal ? station->m_OffsetLongitudinal->m_value : 0.0;
			double const dStation = station->m_DistanceAlong->m_value;
			if (dStation < dStartStation || dStation > dEndStation) continue;

			// Don't evaluate points before the first (valid) station, even when doing adaptive sampling.
			// When doing adaptive sampling and it's not the first (valid) station, then possibly intermediate
			// stations will be evaluated by the tessellator.
			if (bAdaptiveSampling && lastStation)
			{
				// The tessellation evaluator must linearly interpolate the offset values.
				auto const& eval = [this, dOffsetLateral, dOffsetVertical, dOffsetLongitudinal, dStation, lastStation](
					double dStationInterpolated,
					std::shared_ptr<buw::HorizontalAlignment2D> horiz,
					std::shared_ptr<buw::VerticalAlignment2D> vert,
					std::pair<buw::Vector2d, buw::Vector2d>* pHorizontalTangentAndNormalOut)->buw::Vector3d{
						// Get the last offsets and station for interpolation.
						double const dLastOffsetLateral = lastStation->m_OffsetLateral ? lastStation->m_OffsetLateral->m_value : 0.0;
						double const dLastOffsetVertical = lastStation->m_OffsetVertical ? lastStation->m_OffsetVertical->m_value : 0.0;
						double const dLastOffsetLongitudinal = lastStation->m_OffsetLongitudinal ? lastStation->m_OffsetLongitudinal->m_value : 0.0;
						double const dLastStation = lastStation->m_DistanceAlong->m_value;
						double const dInterpolationLength = dStation - dLastStation;
						double const p = (dStationInterpolated - dLastStation) / dInterpolationLength;

						return computeOffsetPoint(horiz, vert, dStationInterpolated,
							(1-p)*dLastOffsetLateral + p*dOffsetLateral,
							(1-p)*dLastOffsetVertical + p*dOffsetVertical,
							(1-p)*dLastOffsetLongitudinal + p*dOffsetLongitudinal,
							pHorizontalTangentAndNormalOut);
						};
				Tessellation::tessellate(lastStation->m_DistanceAlong->m_value, dStation, h, v,
					alignment, pHorizontalTangentsAndNormalsOut, eval, true, false);
			}
			else
			{
				alignment->addPoint(computeOffsetPoint(h, v, dStation, dOffsetLateral, dOffsetVertical, dOffsetLongitudinal,
					&horizontalTangentAndNormal));
				if (pHorizontalTangentsAndNormalsOut)
					pHorizontalTangentsAndNormalsOut->push_back(horizontalTangentAndNormal);
			}

			lastStation = station;
		}

		// Extend towards the tail of the basis curve, if needed.
		if (bExtendToHeadAndTail && !stations.empty())
		{
			auto lastStation = stations.back();
			if (lastStation->m_AlongHorizontal && lastStation->m_AlongHorizontal->m_value
				&& fabs(lastStation->m_DistanceAlong->m_value - dEndStation) > geometryPrecision_)
			{
				double const dOffsetLateral = lastStation->m_OffsetLateral ? lastStation->m_OffsetLateral->m_value : 0.0;
				double const dOffsetVertical = lastStation->m_OffsetVertical ? lastStation->m_OffsetVertical->m_value : 0.0;
				double const dOffsetLongitudinal = 0.0;
				if (bAdaptiveSampling && ((dEndStation - lastStation->m_DistanceAlong->m_value) > geometryPrecision_))
				{
					auto const& eval = std::bind<buw::Vector3d>(&ImportIfcAlignment1x1Impl::computeOffsetPoint, this, _2, _3, _1,
						dOffsetLateral, dOffsetVertical, dOffsetLongitudinal, _4);
					Tessellation::tessellate(lastStation->m_DistanceAlong->m_value, dEndStation, h, v,
						alignment, pHorizontalTangentsAndNormalsOut, eval, true, false);
				}
				else
				{
					alignment->addPoint(computeOffsetPoint(h, v, dEndStation, dOffsetLateral, dOffsetVertical,
						dOffsetLongitudinal, &horizontalTangentAndNormal));
					if (pHorizontalTangentsAndNormalsOut)
						pHorizontalTangentsAndNormalsOut->push_back(horizontalTangentAndNormal);
				}
			}
		}

		return alignment;
	}

	std::vector<SectionedSolidHorizontal> createSectionedSolidHorizontals(std::shared_ptr<IfcElementAssembly> ifcAssembly)
	{
		std::vector<SectionedSolidHorizontal> results;

		auto findIt = aggregations_.find(ifcAssembly);
		if (findIt == aggregations_.end() || !findIt->second || findIt->second->m_RelatedObjects.empty())
			return results;
		auto parts = findIt->second->m_RelatedObjects;
		for (auto part : parts)
		{
			if (!part) continue;
			if (part->m_entity_enum != IFCBEAM && part->m_entity_enum != IFCSLAB)
				throw buw::NotImplementedYetException("Unimplemented part element type.");
			auto const& ssh = createSectionedSolidHorizontals(std::static_pointer_cast<IfcElement>(part));
			results.insert(results.end(), ssh.begin(), ssh.end());
		}

		return results;
	}

	std::vector<SectionedSolidHorizontal> createSectionedSolidHorizontals(std::shared_ptr<IfcProduct> ifcProduct)
	{
		std::vector<SectionedSolidHorizontal> results;
		if (!ifcProduct->m_Representation)
			return results;

		for (auto repr : ifcProduct->m_Representation->m_Representations)
		{
			for (auto reprItem : repr->m_Items)
			{
				if (!reprItem || reprItem->m_entity_enum != IFCSECTIONEDSOLIDHORIZONTAL) continue;

				auto ssh = std::static_pointer_cast<IfcSectionedSolidHorizontal>(reprItem);
				if (!ssh->m_Directrix || ssh->m_CrossSectionPositions.size() < 2) continue;
				if (!ssh->m_FixedAxisVertical || !ssh->m_FixedAxisVertical->m_value)
					throw buw::NotImplementedYetException("Profile Y axis only in world Z direction supported.");

				// Though not documented in the official specification, we interpolate cross sections if
				// only 2 are given. The need to do so was motivated by the example file given at
				// http://www.buildingsmart-tech.org/ifc/review/IFC4x1/rc3/html/annex/annex-e/sectioned-solid.htm
				// The railings are IfcSectionedSolidHorizontal entities running partially along an arc,
				// however only the first and last cross sections are given. Directly connecting those
				// would make the railings not follow the curve. Therefore we repeat the first profile at
				// intermediate positions along the directrix, if the first and the last profiles are
				// identical.
				bool const bAdaptiveSampling =
					(ssh->m_CrossSectionPositions.size() == 2) && (ssh->m_CrossSections.size() == 2) &&
					ssh->m_CrossSections.front() && ssh->m_CrossSections.back() &&
					(ssh->m_CrossSections.front()->getId() == ssh->m_CrossSections.back()->getId());

				// Get the profile positions (and associated horizontal tangent and normal directions).
				std::shared_ptr<Alignment3DBased3D> profilePositions;
				std::vector<std::pair<buw::Vector2d, buw::Vector2d>> horizontalTangentsAndNormals;
				switch (ssh->m_Directrix->m_entity_enum)
				{
				case IFCALIGNMENTCURVE:
				{
					auto directrix = std::static_pointer_cast<IfcAlignmentCurve>(ssh->m_Directrix);
					profilePositions = sampleIfcAlignmentCurve(
						directrix,
						ssh->m_CrossSectionPositions,
						false,
						&horizontalTangentsAndNormals,
						bAdaptiveSampling);
					if (!profilePositions) continue;
					profilePositions->setName(directrix->m_Tag ? buw::String::toWStdString(directrix->m_Tag->m_value) : L"Directrix");
				} break;
				default:
					throw buw::NotImplementedYetException("Unimplemented reference curve type.");
				}
				if (profilePositions->getNumPoints() != horizontalTangentsAndNormals.size())
					throw buw::Exception("Mismatch between number of profile positions and number of tangents and normals for them.");

				// Get the profile curves.
				std::vector<std::shared_ptr<CrossSectionProfile>> profiles;
				for (auto cs : ssh->m_CrossSections)
					profiles.push_back(createProfileCurve(cs));
				if (bAdaptiveSampling)
				{
					// We checked previously that there are only two cross sections and that they are identical.
					// Therefore we repeat the last cross section for the number of interpolated anchor points.
					for (size_t i = 0; i < profilePositions->getNumPoints()-2; ++i)
						profiles.push_back(profiles.back());
				}
				if (profilePositions->getNumPoints() != profiles.size())
					throw buw::Exception("Mismatch between number of profile positions and number of profiles.");

				results.push_back(SectionedSolidHorizontal(profilePositions, horizontalTangentsAndNormals, profiles));
			}
		}

		return results;
	}

	std::shared_ptr<CrossSectionProfile> createProfileCurve(std::shared_ptr<IfcProfileDef> profile)
	{
		if (!profile) return nullptr;
		switch (profile->m_entity_enum)
		{
		case IFCASYMMETRICISHAPEPROFILEDEF:
			return std::make_shared<CrossSectionProfile>(std::static_pointer_cast<IfcAsymmetricIShapeProfileDef>(profile));
		case IFCARBITRARYCLOSEDPROFILEDEF:
			return std::make_shared<CrossSectionProfile>(std::static_pointer_cast<IfcArbitraryClosedProfileDef>(profile));
		case IFCMIRROREDPROFILEDEF:
		{
			auto mirroredProfile = std::static_pointer_cast<IfcMirroredProfileDef>(profile);
			if (mirroredProfile->m_Operator)
				throw buw::NotImplementedYetException("Advanced mirror profiles are not supported.");
			auto profileCurve = createProfileCurve(mirroredProfile->m_ParentProfile);
			std::transform(profileCurve->pntList2D.begin(), profileCurve->pntList2D.end(), profileCurve->pntList2D.begin(),
				[](buw::Vector2d const& p)->buw::Vector2d {return buw::Vector2d(-p[0], p[1]); });
			return profileCurve;
		}
		default:
			throw buw::NotImplementedYetException("Unsupported profile type.");
		}

		return nullptr;
	}

	void createAlignment(std::shared_ptr<IfcAlignment> ifcAlignment)
	{
		buw::ReferenceCounted<buw::Alignment2DBased3D> alignment = std::make_shared<buw::Alignment2DBased3D>();
		alignment->setId(ifcAlignment->getId());

		// read name of alignment
		if (ifcAlignment->m_Name != nullptr)
		{
			alignment->setName(buw::String::toWStdString(ifcAlignment->m_Name->m_value));
		}
		else
		{
			alignment->setName(L"Alignment");
		}

		switch(ifcAlignment->m_Axis->m_entity_enum)
		{
		case IFCALIGNMENTCURVE:
		{
			auto ifcAlignmentCurve = std::static_pointer_cast<IfcAlignmentCurve>(ifcAlignment->m_Axis);
			alignment->setId(ifcAlignmentCurve->getId());

			// The horizontal alignment is mandatory for IfcAlignmentCurve.
			auto h = createHorizontalAlignment(ifcAlignmentCurve);
			if (h && h->getAlignmentElementCount() > 0)
			{
				alignment->setHorizontalAlignment(h);

				// The accompanying vertical alignment is optional for IfcAlignmentCurve.
				auto v = createVerticalAlignment(ifcAlignmentCurve);
				if (v)
					alignment->setVerticalAlignment(v);

				if (ifcAlignment->m_Representation)
					createAlignmentRepresentation(ifcAlignment);
			}
		} break;
		case IFCOFFSETCURVEBYDISTANCES:
		case IFCPOLYLINE:
		default:
			throw buw::NotImplementedYetException("Unknown/unimplemented alignment representation.");
		}

		alignmentModel_->addAlignment(alignment);
	}

	void createAlignmentRepresentation(buw::ReferenceCounted<IfcAlignment> ifcAlignment)
	{
		std::vector<buw::ReferenceCounted<IfcRepresentation>> representations = ifcAlignment->m_Representation->m_Representations;
		for (auto pRepresentation : representations)
		{
			if (!pRepresentation) continue;
			for (auto pRepresentationItem : pRepresentation->m_Items)
			{
				if (!pRepresentationItem) continue;
				switch (pRepresentationItem->m_entity_enum)
				{
				case IFCINDEXEDPOLYCURVE:
				{
					auto ifcIndexedPolyCurve = std::static_pointer_cast<IfcIndexedPolyCurve>(pRepresentationItem);
					if (ifcIndexedPolyCurve->m_Points->m_entity_enum == IFCCARTESIANPOINTLIST3D)
					{
						auto pointList = std::static_pointer_cast<IfcCartesianPointList3D>(ifcIndexedPolyCurve->m_Points);
						auto alignment3d = std::make_shared<buw::Alignment3DBased3D>(0);
						for (auto& p : pointList->m_CoordList)
						{
							alignment3d->addPoint(buw::Vector3d(p[0]->m_value + offset_.x(), p[1]->m_value + offset_.y(), p[2]->m_value + offset_.z()));
						}

						alignmentModel_->addAlignment(alignment3d);
					}
				} break;
				case IFCOFFSETCURVEBYDISTANCES:
				{
					// Convert the basis curve into horizontal and vertical 2D alignments.
					auto ifcOffsetCurve = std::static_pointer_cast<IfcOffsetCurveByDistances>(pRepresentationItem);
					if (!ifcOffsetCurve->m_BasisCurve) break;
					if (ifcOffsetCurve->m_BasisCurve->m_entity_enum != IFCALIGNMENTCURVE)
						throw buw::NotImplementedYetException("Unknown/unimplemented offset basis curve type.");
					if(ifcOffsetCurve->m_OffsetValues.empty()) break;
					auto ifcBasisCurve = std::static_pointer_cast<IfcAlignmentCurve>(ifcOffsetCurve->m_BasisCurve);
					auto alignment = sampleIfcAlignmentCurve(ifcBasisCurve, ifcOffsetCurve->m_OffsetValues, true);
					if (!alignment) break;
					alignment->setName(ifcOffsetCurve->m_Tag ?
						buw::String::toWStdString(ifcOffsetCurve->m_Tag->m_value) : L"Offset curve");
					alignmentModel_->addAlignment(alignment);
				} break;
				case IFCSECTIONEDSOLIDHORIZONTAL:
					break;
				default:
					throw buw::NotImplementedYetException("Unknown IfcRepresentationItem.");
				}
			}
		}
	}

	buw::ReferenceCounted<buw::HorizontalAlignment2D> createHorizontalAlignment(std::shared_ptr<IfcAlignmentCurve> ifcAlignmentCurve)
	{
		auto ifcHoriz = ifcAlignmentCurve->m_Horizontal;
		if (!ifcHoriz) return nullptr;

		auto h = std::make_shared<buw::HorizontalAlignment2D>(ifcHoriz->m_StartDistAlong ? ifcHoriz->m_StartDistAlong->m_value : 0.0);

		for (auto const& seg : ifcHoriz->m_Segments)
		{
			auto curveSegment = seg->m_CurveGeometry;
			BLUE_ASSERT(curveSegment != nullptr, "Invalid horizontal segment.");

			switch (curveSegment->m_entity_enum)
			{
			case IFCLINESEGMENT2D:
				createHorizontalLine(curveSegment, h);
				break;
			case IFCCIRCULARARCSEGMENT2D:
				createHorizontalArc(curveSegment, h);
				break;
			case IFCCLOTHOIDALARCSEGMENT2D:
				createHorizontalClothoid(curveSegment, h);
				break;
			case IFCTRANSITIONCURVESEGMENT2D:
				createHorizontalIfcTransitionCurveSegment2D(curveSegment, h);
				break;
			default:
				throw buw::NotImplementedYetException("Unknown curve segment type.");
			}
		}

		return h->getAlignmentElementCount() > 0 ? h : nullptr;
	}

	void createHorizontalLine(buw::ReferenceCounted<IfcCurveSegment2D> curveSegment, buw::ReferenceCounted<buw::HorizontalAlignment2D> h)
	{
		double const dRadFactor = unitConv_.getAngleInRadianFactor();
		auto ifcLine = std::static_pointer_cast<IfcLineSegment2D>(curveSegment);
		auto ifcStartPoint = ifcLine->m_StartPoint;
		double const startTangentAngle = ifcLine->m_StartDirection->m_value;
		double const segmentLength = ifcLine->m_SegmentLength->m_value;

		buw::Vector2d const startPnt(ifcStartPoint->m_Coordinates[0]->m_value, ifcStartPoint->m_Coordinates[1]->m_value);
		buw::Vector2d const startTangent = buw::createRotationMatrix(dRadFactor * startTangentAngle) * buw::Vector2d(1.0, 0.0);
		buw::Vector2d const endPnt = startPnt + (segmentLength * startTangent);

		auto line = std::make_shared<buw::HorizontalAlignmentElement2DLine>(
			startPnt + offset_.block<2,1>(0,0),
			endPnt + offset_.block<2,1>(0,0));

		h->addElement(line);
	}
	
	void createHorizontalArc(std::shared_ptr<IfcCurveSegment2D> curveSegment, buw::ReferenceCounted<buw::HorizontalAlignment2D> h)
	{
		auto ifcArc = std::static_pointer_cast<IfcCircularArcSegment2D>(curveSegment);
		double const dRadFactor = unitConv_.getAngleInRadianFactor();
		double const PI_2 = buw::constantsd::pi_over_2();

		// read given data
		bool const ccw = ifcArc->m_IsCCW->m_value;
		double const radius = ifcArc->m_Radius->m_value;
		double const startTangentAngle = ifcArc->m_StartDirection->m_value;
		double const segmentLength = ifcArc->m_SegmentLength->m_value;
		buw::Vector2d const startPnt(ifcArc->m_StartPoint->m_Coordinates[0]->m_value, ifcArc->m_StartPoint->m_Coordinates[1]->m_value);
	
		// compute center point
		buw::Vector2d const startTangentOrtho =
			buw::createRotationMatrix((dRadFactor * startTangentAngle) + (ccw ? PI_2 : -PI_2)) * buw::Vector2d(1.0, 0.0);
		buw::Vector2d const centerPnt = startPnt + (radius * startTangentOrtho);

		// calculate angle between start end endpoint
		double const angleSection = segmentLength / radius;

		// compute end point
		buw::Vector2d const endPnt = centerPnt + (buw::createRotationMatrix(ccw ? angleSection : -angleSection) * (startPnt - centerPnt));

		auto arc = std::make_shared<buw::HorizontalAlignmentElement2DArc>(
			centerPnt + offset_.block<2,1>(0,0),
			startPnt + offset_.block<2,1>(0,0),
			endPnt + offset_.block<2,1>(0,0),
			!ccw);

		h->addElement(arc);
	}

	void createHorizontalIfcTransitionCurveSegment2D(buw::ReferenceCounted<IfcCurveSegment2D> curveSegment, buw::ReferenceCounted<buw::HorizontalAlignment2D> h)
	{
		double const dRadFactor = unitConv_.getAngleInRadianFactor();
		buw::ReferenceCounted<IfcTransitionCurveSegment2D> ifcTransitionCurve = std::static_pointer_cast<IfcTransitionCurveSegment2D>(curveSegment);

		if (ifcTransitionCurve->m_TransitionCurveType->m_enum == IfcTransitionCurveType::ENUM_CLOTHOIDCURVE)
		{
			BLUE_ASSERT(ifcTransitionCurve->m_StartPoint != nullptr, "Invalid data.");
			BLUE_ASSERT(ifcTransitionCurve->m_StartPoint->m_Coordinates[0] != nullptr, "Invalid data.");
			BLUE_ASSERT(ifcTransitionCurve->m_StartPoint->m_Coordinates[1] != nullptr, "Invalid data.");
		
			// read basic data
			buw::ReferenceCounted<IfcCartesianPoint> ifcStartPoint = ifcTransitionCurve->m_StartPoint;

			buw::Vector2d start = buw::Vector2d(
				ifcStartPoint->m_Coordinates[0]->m_value,
				ifcStartPoint->m_Coordinates[1]->m_value)
				+ offset_.block<2, 1>(0, 0);

//			const bool		isEntry = ifcTransitionCurve->m_IsEntry->m_value;
			const double	startDirection = ifcTransitionCurve->m_StartDirection->m_value;
			const double	length = ifcTransitionCurve->m_SegmentLength->m_value;
			//const double	clothoidConstant = ifcTransitionCurve->m_ClothoidConstant->m_value;
			const bool		counterClockwise = ifcTransitionCurve->m_IsStartRadiusCCW->m_value;
			const bool		hasStartRadius = ifcTransitionCurve->m_StartRadius != nullptr ? true : false;
			const bool		hasEndRadius = ifcTransitionCurve->m_EndRadius != nullptr ? true : false;

			double startCurvature = 0;
			if (hasStartRadius)	{
				startCurvature = 1 / ifcTransitionCurve->m_StartRadius->m_value;
			}

			double endCurvature = 0;
			if (hasEndRadius) {
				endCurvature = 1 / ifcTransitionCurve->m_EndRadius->m_value;
			}

			bool isEntry = false;
			if (startCurvature < endCurvature) {
				isEntry = true;
			}
			
			double clothoidConstant = 
				buw::HorizontalAlignmentElement2DClothoid::computeClothoidConstant(
					length, startCurvature, endCurvature);

			buw::clothoidDescription desc(start,
				dRadFactor*startDirection,
				startCurvature,
				counterClockwise,
				clothoidConstant,
				isEntry,
				length);
			buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> clothoid = std::make_shared<buw::HorizontalAlignmentElement2DClothoid>(desc);

			h->addElement(clothoid);
		}
		else if(ifcTransitionCurve->m_TransitionCurveType->m_enum == IfcTransitionCurveType::ENUM_BLOSSCURVE)
		{
			BLUE_ASSERT(ifcTransitionCurve->m_StartPoint != nullptr, "Invalid data.");
			BLUE_ASSERT(ifcTransitionCurve->m_StartPoint->m_Coordinates[0] != nullptr, "Invalid data.");
			BLUE_ASSERT(ifcTransitionCurve->m_StartPoint->m_Coordinates[1] != nullptr, "Invalid data.");

			// read basic data
			buw::ReferenceCounted<IfcCartesianPoint> ifcStartPoint = ifcTransitionCurve->m_StartPoint;

			buw::Vector2d start = buw::Vector2d(
				ifcStartPoint->m_Coordinates[0]->m_value,
				ifcStartPoint->m_Coordinates[1]->m_value)
				+ offset_.block<2, 1>(0, 0);

			const double	startDirection = ifcTransitionCurve->m_StartDirection->m_value;
			const double	length = ifcTransitionCurve->m_SegmentLength->m_value;
			const bool		counterClockwise = ifcTransitionCurve->m_IsStartRadiusCCW->m_value;
			const bool		hasStartRadius = ifcTransitionCurve->m_StartRadius != nullptr ? true : false;
			const bool		hasEndRadius = ifcTransitionCurve->m_EndRadius != nullptr ? true : false;

			assert(hasStartRadius != hasEndRadius);

			double radius = 0;
			if (hasStartRadius) {
				radius = ifcTransitionCurve->m_StartRadius->m_value;
			}

			if (hasEndRadius) {
				radius = ifcTransitionCurve->m_EndRadius->m_value;
			}

			bool isEntry = hasEndRadius;

			buw::blossDescription desc(start,
				dRadFactor*startDirection,
				counterClockwise,
				isEntry,
				length,
				radius);

			buw::ReferenceCounted<buw::HorizontalAlignmentElement2DBlossCurve> bloss = 
				std::make_shared<buw::HorizontalAlignmentElement2DBlossCurve>(desc);

			h->addElement(bloss);
		}
		else {
			// throw buw::Exception("Unknown transition curve type");
		}
	}

	void createHorizontalClothoid(buw::ReferenceCounted<IfcCurveSegment2D> curveSegment, buw::ReferenceCounted<buw::HorizontalAlignment2D> h)
	{
		double const dRadFactor = unitConv_.getAngleInRadianFactor();
		buw::ReferenceCounted<IfcClothoidalArcSegment2D> ifcClothoid = std::static_pointer_cast<IfcClothoidalArcSegment2D>(curveSegment);

		BLUE_ASSERT(ifcClothoid->m_StartPoint != nullptr, "Invalid data.");
		BLUE_ASSERT(ifcClothoid->m_StartPoint->m_Coordinates[0] != nullptr, "Invalid data.");
		BLUE_ASSERT(ifcClothoid->m_StartPoint->m_Coordinates[1] != nullptr, "Invalid data.");
		BLUE_ASSERT(ifcClothoid->m_IsEntry != nullptr, "Invalid data.");
		BLUE_ASSERT(ifcClothoid->m_StartDirection != nullptr, "Invalid data.");
		BLUE_ASSERT(ifcClothoid->m_SegmentLength != nullptr, "Invalid data.");
		BLUE_ASSERT(ifcClothoid->m_IsCCW != nullptr, "Invalid data.");

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
		const bool		counterClockwise	= ifcClothoid->m_IsCCW->m_value;
		const bool		hasStartRadius		= ifcClothoid->m_StartRadius != nullptr ? true : false;
		

		double startCurvature = 0;
		if (hasStartRadius)
		{
			startCurvature = 1 / ifcClothoid->m_StartRadius->m_value;
		}

		buw::clothoidDescription desc(start,
			dRadFactor*startDirection,
			startCurvature,
			counterClockwise,
			clothoidConstant,
			isEntry,
			length);
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> clothoid = std::make_shared<buw::HorizontalAlignmentElement2DClothoid>(desc);

		h->addElement(clothoid);
	}

	void createTrafficSign(buw::ReferenceCounted<IfcTriangulatedFaceSet> triangluatedFaceSet, buw::ReferenceCounted<TrafficSign> ts)
	{
		// read position values
		for (int i = 0; i < triangluatedFaceSet->m_Coordinates->m_CoordList.size(); i++)
		{
			buw::Vector3d p;

			double x = triangluatedFaceSet->m_Coordinates->m_CoordList[i][0]->m_value;
			double y = triangluatedFaceSet->m_Coordinates->m_CoordList[i][1]->m_value;
			double z = triangluatedFaceSet->m_Coordinates->m_CoordList[i][2]->m_value;

			p = buw::Vector3d(x, z, y); //+ offset_;

			ts->vertices.push_back(
				buw::VertexPosition3(
					buw::Vector3f(p.x(), p.y(), p.z())
				)
			);
		}

		// read faces
		for (int i = 0; i < triangluatedFaceSet->m_CoordIndex.size(); i++)
		{
			buw::Vector3i indices;

			for (int k = 0; k < 3; k++)
			{
				indices[k] = triangluatedFaceSet->m_CoordIndex[i][k]->m_value - 1; // IFC Index start with 1 ... N
			}

			ts->indices.push_back(indices.x());
			ts->indices.push_back(indices.y());
			ts->indices.push_back(indices.z());
		}
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
				indices[k] = triangluatedFaceSet->m_CoordIndex[i][k]->m_value - 1; // IFC Index start with 1 ... N
			}

			s->addTriangle(indices);
		}

		digitalElevationModel_->addSurface(s);
	}

	buw::ReferenceCounted<buw::VerticalAlignment2D> createVerticalAlignment(std::shared_ptr<IfcAlignmentCurve> ifcAlignmentCurve)
	{
		auto ifcVert = ifcAlignmentCurve->m_Vertical;
		if (!ifcVert) return nullptr;

		auto v = std::make_shared<buw::VerticalAlignment2D>();

		for (auto const& seg : ifcVert->m_Segments)
		{
			BLUE_ASSERT(seg != nullptr, "Invalid vertical segment.");

			switch (seg->m_entity_enum)
			{
			case IFCALIGNMENT2DVERSEGLINE:
				createVerticalAlignmentLine(seg, v);
				break;
			case IFCALIGNMENT2DVERSEGPARABOLICARC:
				createVerticalAlignmentParabola(seg, v);
				break;
			case IFCALIGNMENT2DVERSEGCIRCULARARC:
				createVerticalAlignmentArc(seg, v);
				break;
			}
		}

		return v->getAlignmentElementCount() > 0 ? v : nullptr;
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
		const bool isConvex = !ifcLine->m_IsConvex->m_value;

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
		tocenter = tocenter.normalized() * radius * (!isConvex ? -1.0 : 1.0);

		buw::Vector2d center = start + tocenter;
		buw::Vector2d tostart = tocenter * -1.0;

		double x = horizontalLength - tocenter.x();

		double alpha1 = std::asin(tocenter.x() / radius);
		double alpha2 = std::asin(x / radius);
		double alpha = alpha1 + alpha2;

		if (isConvex)
			alpha *= -1;

		buw::Vector2d toend;
		float s = std::sin(alpha);
		float c = std::cos(alpha);
		toend.x() = tostart.x() * c - tostart.y() * s;
		toend.y() = tostart.y() * c + tostart.x() * s;

		buw::Vector2d end = center + toend;

		v->addElement(std::make_shared<buw::VerticalAlignmentElement2DArc>(start, end, radius, startGradient, !isConvex));
	}

private:
	buw::Vector3d offset_;
	buw::ReferenceCounted<IfcProject> project_;
	UnitConverter unitConv_;
	double geometryPrecision_;
	std::map<std::shared_ptr<IfcObjectDefinition>, std::shared_ptr<IfcRelAggregates>> aggregations_; // Whole/part relationships. Key value is the whole entity.
	std::set<std::shared_ptr<IfcProduct>> spatialContainments_; // "Top-level objects". Others are parts (of assemblies) or subassemblies.
};

OpenInfraPlatform::Infrastructure::ImportIfcAlignment1x1::ImportIfcAlignment1x1(
 	const std::string& filename) :
	Import(filename),
	impl_(new ImportIfcAlignment1x1Impl(filename))
{
	alignmentModel_ = impl_->getAlignmentModel();
	digitalElevationModel_ = impl_->getDigitalElevationModel();
	trafficSignModel_ = impl_->getTrafficSignModel();
	girderModel_ = impl_->getGirderModel();
	slabFieldModel_ = impl_->getSlabFieldModel();
}
