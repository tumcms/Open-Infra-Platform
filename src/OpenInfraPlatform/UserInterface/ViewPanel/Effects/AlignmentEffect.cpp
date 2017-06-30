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

#include "AlignmentEffect.h"

#include "OpenInfraPlatform/UserInterface/ViewPanel/RenderResources.h"
#include "OpenInfraPlatform/DataManagement/PickIdGenerator.h"
#include "OpenInfraPlatform/DataManagement/Command/SelectAlignment.h"
#include <BlueFramework/Rasterizer/vertex.h>
#include <mutex>
#include <time.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

typedef buw::VertexPosition3Id3 VertexTypeWireframe;
typedef buw::VertexPosition3Normal3Id3Texture2 VertexTypeSolid;



AlignmentEffect::AlignmentEffect(buw::IRenderSystem* renderSystem,
                                 buw::ReferenceCounted<buw::IViewport> viewport,
                                 buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA,
                                 buw::ReferenceCounted<buw::ITexture2D> pickBuffer,
                                 buw::ReferenceCounted<buw::ITexture2D> depthStencil,
                                 buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer,
                                 buw::ReferenceCounted<buw::IConstantBuffer> viewportBuffer,
                                 buw::ReferenceCounted<buw::IConstantBuffer> pickIdBuffer /*= nullptr*/)
    :
    Effect(renderSystem),
    viewport_(viewport),
    depthStencilMSAA_(depthStencilMSAA),
    pickBuffer_(pickBuffer),
    depthStencil_(depthStencil),
    worldBuffer_(worldBuffer),
    viewportBuffer_(viewportBuffer),
    pickIdBuffer_(pickIdBuffer)
{
}

AlignmentEffect::~AlignmentEffect()
{
	vertexBuffersAlignment_.clear();
	crossSectionVertexBuffers_.clear();
	designCrossSectionVertexBuffers_.clear();
	roadBodyWireframeVertexBuffers_.clear();
	roadBodySolidVertexBuffers_.clear();

	lineStripState_ = nullptr;
	lineListState_ = nullptr;
	triangleListState_ = nullptr;
	pickLineStripState_ = nullptr;
	pickLineListState_ = nullptr;
	pickTriangleListState_ = nullptr;

	viewport_ = nullptr;
	depthStencilMSAA_ = nullptr;
	pickBuffer_ = nullptr;
	depthStencil_ = nullptr;

	roadBodyTexture_ = nullptr;
	roadBodyNormalTexture_ = nullptr;
	sampler_ = nullptr;

	worldBuffer_ = nullptr;
	viewportBuffer_ = nullptr;
	settingsBuffer_ = nullptr;
	colorBuffer_ = nullptr;
	pickIdBuffer_ = nullptr;
}

void AlignmentEffect::enableAlignmentColor(const bool checked)
{
    settings_.bDrawColored = checked;
    updateSettingsBuffer();
}

void AlignmentEffect::enableHighlightSelected(const bool checked)
{
    settings_.bHighlightSelected = checked;
    updateSettingsBuffer();
}

void AlignmentEffect::showCrossSections(const bool checked)
{
    bShowCrossSections_ = checked;
}

void AlignmentEffect::showDesignCrossSections(const bool checked)
{
    bShowDesignCrossSections_ = checked;
}

void AlignmentEffect::showRoadBodyWireframe(const bool checked)
{
    bShowRoadBodyWireframe_ = checked;
}

void AlignmentEffect::showRoadBodySolid(const bool checked)
{
    bShowRoadBodySolid_ = checked;
}

void AlignmentEffect::drawRoadBodyTextured(const bool checked)
{
    settings_.bDrawTextured = checked;
    updateSettingsBuffer();
}

void AlignmentEffect::drawFlattened(const bool checked)
{
    settings_.bDrawFlattened = checked;
    updateSettingsBuffer();
}

void AlignmentEffect::setAlignment(buw::ReferenceCounted<buw::AlignmentModel> alignmentModel, buw::Vector3d& offset) {
	vertexBuffersAlignment_.clear();
    crossSectionVertexBuffers_.clear();
    designCrossSectionVertexBuffers_.clear();
	roadBodyWireframeVertexBuffers_.clear();
	roadBodySolidVertexBuffers_.clear();

	buw::VertexLayout vertexLayout = buw::VertexPosition3::getVertexLayout();
	std::mutex mutex;
	std::time_t start, end;
	std::time(&start);

	for (int index = 0; index < alignmentModel->getAlignmentCount(); index++) {
		auto alignment = alignmentModel->getAlignment(index);
        UINT alignmentId = index;
        UINT alignmentType = 0;

        UINT pickId = OpenInfraPlatform::PickIdGenerator::getInstance().getId();
		buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::Alignment2DBased3D> alignment2D = nullptr;
        alignmentIds_.insert(std::pair<UINT, int>(pickId, alignmentId));

        //const int numSamples = 1000;
        std::vector<VertexTypeWireframe> vertices(0);
       
        float start = alignment->getStartStation();
        float end = alignment->getEndStation();

		if(alignment->getType() == OpenInfraPlatform::Infrastructure::e3DAlignmentType::e2DBased)
			alignment2D = std::static_pointer_cast<OpenInfraPlatform::Infrastructure::Alignment2DBased3D>(alignment);
				

        for(float s = start; s < end; s += 0.8) {
            buw::Vector3f position = (alignment->getPosition(s) + offset).cast<float>();            

			if(alignment2D && alignment2D->hasHorizontalAlignment())
				alignmentType = (UINT)alignment2D->getHorizontalAlignment()->getAlignmentElementByStationing(s)->getAlignmentType();
			else
				alignmentType = 0;
            VertexTypeWireframe vertex = { position, alignmentId, alignmentType, pickId };
            vertices.push_back(vertex);
        }

        if(vertices.size() >= 1) {
			vertices.insert(vertices.begin(), vertices[0]);
			vertices.push_back(vertices.back());

            buw::vertexBufferDescription vbd;
            vbd.data = &vertices[0];
            vbd.vertexCount = static_cast<int>(vertices.size());
            vbd.vertexLayout = VertexTypeWireframe::getVertexLayout();

			auto vertexBuffer = renderSystem()->createVertexBuffer(vbd);
            vertexBuffersAlignment_.push_back(vertexBuffer);
		}

        if(alignment2D) {
            std::vector<std::vector<VertexTypeWireframe>> crossSectionVertices(alignment2D->getCrossSectionCount());
            std::vector<std::vector<VertexTypeWireframe>> designCrossSectionVertices(alignment2D->getCrossSectionCount());
            std::vector<std::vector<VertexTypeWireframe>> roadBodyWireframeVertices(alignment2D->getCrossSectionCount());
            std::vector<std::vector<VertexTypeSolid>> roadBodySolidVertices(alignment2D->getCrossSectionCount());
			
			#pragma omp parallel for firstprivate(alignmentType)
            for(int sectionIdx = 0; sectionIdx < alignment2D->getCrossSectionCount() - 1; sectionIdx++) {
                auto crossSection = alignment2D->getCrossSection(sectionIdx);
                alignmentType = 4;

                buw::Vector3d currentCenter = (alignment2D->getPosition(crossSection->stationing));
                buw::Vector3d nextCenter = (alignment2D->getPosition(alignment2D->getCrossSection(sectionIdx + 1)->stationing));
				
				auto getRotation44f = [&](buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::CrossSectionStatic> crossSection) {
					auto pos1 = alignment2D->getPosition(crossSection->stationing);
					auto pos2 = alignment2D->getPosition(crossSection->stationing + 0.001f);
					buw::Vector3d direction;
					if(buw::distance(pos2, pos1) > 0.0001) {
						direction = (pos2 - pos1).normalized();
					}
					else {
						pos2 = alignment2D->getPosition(crossSection->stationing + 0.1f);
						direction = (pos2 - pos1).normalized();
					}
					
					buw::Matrix44f rotation = buw::createRotationMatrixZ(
						buw::calculateAngleBetweenVectors(
							buw::Vector2f(1, 0),
							buw::Vector2f(direction.x(), direction.y())
						)
					);
					return rotation;
				};

				auto getRotation33d = [&](buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::CrossSectionStatic> crossSection) {
					auto pos1 = alignment2D->getPosition(crossSection->stationing);
					auto pos2 = alignment2D->getPosition(crossSection->stationing + 0.001);
					buw::Vector3d direction;
					if(buw::distance(pos2, pos1) > 0.0001) {
						direction = (pos2 - pos1).normalized();
					}
					else {
						pos2 = alignment2D->getPosition(crossSection->stationing + 0.01);
						if(buw::distance(pos2, pos1) > 0.0001) {
							direction = (pos2 - pos1).normalized();
						}
						else
						{
							pos2 = alignment2D->getPosition(crossSection->stationing + 0.1);
							direction = (pos2 - pos1).normalized();
						}
					}
					buw::Matrix33d rotation = buw::createRotationMatrix3TZ(
						buw::calculateAngleBetweenVectors(
							buw::Vector2d(-1, 0),
							buw::Vector2d(direction.x(), direction.y())
						)
					);
					return rotation;
				};

				auto rotation = getRotation33d(crossSection);
				auto nextRotation = getRotation33d(alignment2D->getCrossSection(sectionIdx + 1));

				for(int surfaceIdx = 0; surfaceIdx < crossSection->getCrossSectionProfileCount(); surfaceIdx++) {
					auto crossSectionProfile = crossSection->getCrossSectionProfile(surfaceIdx);
					
					// iterate through all points  of CrossSectionProfile

					bool isFirstPoint = true;
					buw::Vector3d lastPoint;
					for(int p = 0; p < crossSectionProfile->pntList2D.size(); p++) {
						buw::Vector3d position = buw::Vector3d(
							0,
							crossSectionProfile->pntList2D[p].x(),
							crossSectionProfile->pntList2D[p].y()
						);

						position = rotation * position;
						position = buw::Vector3d(
							position[0] + currentCenter[0] + offset[0],
							position[1] + currentCenter[1] + offset[1],
							position[2] + offset[2]
						);

						if(isFirstPoint)
							isFirstPoint = false;
						else {
							crossSectionVertices[sectionIdx].push_back({ buw::Vector3f(lastPoint.x(),lastPoint.y(),lastPoint.z()) ,alignmentId, alignmentType, pickId });
							crossSectionVertices[sectionIdx].push_back({ buw::Vector3f(position.x(),position.y(),position.z()) ,alignmentId, alignmentType, pickId });
						}

						lastPoint = position;
					}

				}

                for(int surfaceIdx = 0; surfaceIdx < crossSection->getDesignCrossSectionProfileCount(); surfaceIdx++) {
                    auto designCrossSectionProfile = crossSection->getDesignCrossSectionProfile(surfaceIdx);
                    alignmentType = 5;
					if(designCrossSectionProfile->crossSectionsPoints.size() > 1) {
						buw::Vector3d lastPosition = buw::Vector3d(0, designCrossSectionProfile->crossSectionsPoints[0]->position.x(), designCrossSectionProfile->crossSectionsPoints[0]->position.y());
						lastPosition = rotation*lastPosition;
						lastPosition += buw::Vector3d(
							currentCenter.x() + offset[0],
							currentCenter.y() + offset[1],
							currentCenter.z() + offset[2]);

						for(auto point2D = designCrossSectionProfile->crossSectionsPoints.begin() + 1; point2D != designCrossSectionProfile->crossSectionsPoints.end(); point2D++) {
							buw::Vector3d position = lastPosition;
							designCrossSectionVertices[sectionIdx].push_back({ buw::Vector3f(position.x(),position.y(),position.z()) ,alignmentId, alignmentType, pickId });

							buw::Vector3d nextPosition = buw::Vector3d(0, point2D->get()->position.x(), point2D->get()->position.y());
							nextPosition = rotation * nextPosition;
							nextPosition += buw::Vector3d(
								currentCenter.x() + offset[0],
								currentCenter.y() + offset[1],
								currentCenter.z() + offset[2]);
							designCrossSectionVertices[sectionIdx].push_back({ buw::Vector3f(nextPosition.x(),nextPosition.y(),nextPosition.z()) ,alignmentId, alignmentType, pickId });

							lastPosition = nextPosition;
						}
					}
                }

                auto nextCrossSection = crossSection;
				if(sectionIdx < alignment2D->getCrossSectionCount() - 1) {
					nextCrossSection = alignment2D->getCrossSection(sectionIdx + 1);
					
					if(crossSection->getClosedDesignCrossSectionProfileCount() == nextCrossSection->getClosedDesignCrossSectionProfileCount()) {
						alignmentType = 6;
						
						for(int closedDesignSurfaceIdx = 0; closedDesignSurfaceIdx < crossSection->getClosedDesignCrossSectionProfileCount(); closedDesignSurfaceIdx++) {
							buw::ReferenceCounted<buw::DesignCrossSectionProfile> startProfile = crossSection->getClosedDesignCrossSectionProfile(closedDesignSurfaceIdx);
							buw::ReferenceCounted<buw::DesignCrossSectionProfile> endProfile = nextCrossSection->getClosedDesignCrossSectionProfile(closedDesignSurfaceIdx);
							alignmentType = 6;
							if(startProfile->crossSectionsPoints.size() == endProfile->crossSectionsPoints.size()) {
								buw::Vector3d previousStartPoint;
								buw::Vector3d previousEndPoint;

								bool isSlope = false;
								int slopeType = 0;
								bool isTopFace = false;

								for(int pointIdx = 0; pointIdx < startProfile->crossSectionsPoints.size(); pointIdx++) {
									if(startProfile->crossSectionsPoints.size() == 2) isSlope = true;
									bool left = false, right = false;

									buw::Vector3d startPoint = buw::Vector3d(
										0,
										startProfile->crossSectionsPoints[pointIdx]->position.x(),
										startProfile->crossSectionsPoints[pointIdx]->position.y()										
									);
									
									// points on greater station
									buw::Vector3d endPoint = buw::Vector3d(
										0,
										endProfile->crossSectionsPoints[pointIdx]->position.x(),
										endProfile->crossSectionsPoints[pointIdx]->position.y()
									);

									if(startPoint == buw::Vector3d(0, 0, 0) || endPoint == buw::Vector3d(0, 0, 0))
										isTopFace = true;

									
									if(startPoint.y() < 0)
										right = true;
									else
										left = true;


									// transform points on smaller station
									startPoint = rotation * startPoint + currentCenter + offset;

									endPoint = nextRotation * endPoint + nextCenter + offset;

									roadBodyWireframeVertices[sectionIdx].push_back({ buw::Vector3f(startPoint.x(),startPoint.y(),startPoint.z()) ,alignmentId, alignmentType, pickId });
									roadBodyWireframeVertices[sectionIdx].push_back({ buw::Vector3f(endPoint.x(),endPoint.y(),endPoint.z()) ,alignmentId, alignmentType, pickId });

									if(pointIdx > 0 && isTopFace) {
										float segmentLength = (currentCenter - nextCenter).norm();
										alignmentType = 7;

										buw::Vector3f normal1 = (buw::Vector3f)(previousStartPoint - endPoint).cross(startPoint - endPoint).cast<float>();
										if(normal1.norm()!=0)
											normal1.normalize();
										buw::Vector3f normal2 = (buw::Vector3f)(previousStartPoint - endPoint).cross(startPoint - endPoint).cast<float>();
										if(normal2.norm()!=0)
											normal2.normalize();
										
										if(right) {
											roadBodySolidVertices[sectionIdx].push_back(VertexTypeSolid(buw::Vector3f(previousStartPoint.x(), previousStartPoint.y(), previousStartPoint.z()), normal1, alignmentId, alignmentType, pickId, buw::Vector2f(0, 0)));
											roadBodySolidVertices[sectionIdx].push_back(VertexTypeSolid(buw::Vector3f(previousEndPoint.x(), previousEndPoint.y(), previousEndPoint.z()), normal1, alignmentId, alignmentType, pickId, buw::Vector2f(0, segmentLength)));
											roadBodySolidVertices[sectionIdx].push_back(VertexTypeSolid(buw::Vector3f(endPoint.x(), endPoint.y(), endPoint.z()), normal1, alignmentId, alignmentType, pickId, buw::Vector2f(1, segmentLength)));

											roadBodySolidVertices[sectionIdx].push_back(VertexTypeSolid(buw::Vector3f(startPoint.x(), startPoint.y(), startPoint.z()), normal2, alignmentId, alignmentType, pickId, buw::Vector2f(1, 0)));
											roadBodySolidVertices[sectionIdx].push_back(VertexTypeSolid(buw::Vector3f(previousStartPoint.x(), previousStartPoint.y(), previousStartPoint.z()), normal2, alignmentId, alignmentType, pickId, buw::Vector2f(0,0)));
											roadBodySolidVertices[sectionIdx].push_back(VertexTypeSolid(buw::Vector3f(endPoint.x(), endPoint.y(), endPoint.z()), normal2, alignmentId, alignmentType, pickId, buw::Vector2f(1, segmentLength)));
										}
										else
										{
											roadBodySolidVertices[sectionIdx].push_back(VertexTypeSolid(buw::Vector3f(previousStartPoint.x(), previousStartPoint.y(), previousStartPoint.z()), normal1, alignmentId, alignmentType, pickId, buw::Vector2f(0, 0)));
											roadBodySolidVertices[sectionIdx].push_back(VertexTypeSolid(buw::Vector3f(endPoint.x(), endPoint.y(), endPoint.z()), normal1, alignmentId, alignmentType, pickId, buw::Vector2f(1, segmentLength)));
											roadBodySolidVertices[sectionIdx].push_back(VertexTypeSolid(buw::Vector3f(previousEndPoint.x(), previousEndPoint.y(), previousEndPoint.z()), normal1, alignmentId, alignmentType, pickId, buw::Vector2f(0, segmentLength)));

											roadBodySolidVertices[sectionIdx].push_back(VertexTypeSolid(buw::Vector3f(startPoint.x(), startPoint.y(), startPoint.z()), normal2, alignmentId, alignmentType, pickId, buw::Vector2f(1, 0)));
											roadBodySolidVertices[sectionIdx].push_back(VertexTypeSolid(buw::Vector3f(endPoint.x(), endPoint.y(), endPoint.z()), normal2, alignmentId, alignmentType, pickId, buw::Vector2f(1, segmentLength)));
											roadBodySolidVertices[sectionIdx].push_back(VertexTypeSolid(buw::Vector3f(previousStartPoint.x(), previousStartPoint.y(), previousStartPoint.z()), normal2, alignmentId, alignmentType, pickId, buw::Vector2f(0, 0)));
										}
									}

									previousStartPoint = startPoint;
									previousEndPoint = endPoint;
								}

							}
						}
						
					}
					
					if(crossSection->getOpenDesignCrossSectionProfileCount() == nextCrossSection->getOpenDesignCrossSectionProfileCount()) {
						for(int openDesignSurfaceIdx = 0; openDesignSurfaceIdx < crossSection->getOpenDesignCrossSectionProfileCount(); openDesignSurfaceIdx++) {
							buw::ReferenceCounted<buw::DesignCrossSectionProfile> startProfile = crossSection->getOpenDesignCrossSectionProfile(openDesignSurfaceIdx);
							buw::ReferenceCounted<buw::DesignCrossSectionProfile> endProfile = nextCrossSection->getOpenDesignCrossSectionProfile(openDesignSurfaceIdx);
							alignmentType = 6;
							if(startProfile->crossSectionsPoints.size() == endProfile->crossSectionsPoints.size()) {
								buw::Vector3d previousStartPoint;
								buw::Vector3d previousEndPoint;

								bool isSlope = false;
								int slopeType = 0;
								bool isTopFace = false;

								for(int pointIdx = 0; pointIdx < startProfile->crossSectionsPoints.size(); pointIdx++) {
									if(startProfile->crossSectionsPoints.size() == 2) isSlope = true;
									bool right = false;
									buw::Vector3d startPoint = buw::Vector3d(
										0,
										startProfile->crossSectionsPoints[pointIdx]->position.x(),
										startProfile->crossSectionsPoints[pointIdx]->position.y()										
									);

									if(startPoint.y() >= 0)
										right = true;
									
									

									// transform points on smaller station
									startPoint = rotation * startPoint + currentCenter + offset;

									// points on greater station
									buw::Vector3d endPoint = buw::Vector3d(
										0,
										endProfile->crossSectionsPoints[pointIdx]->position.x(),
										endProfile->crossSectionsPoints[pointIdx]->position.y()
									);

									endPoint = nextRotation * endPoint + nextCenter + offset;


									if(pointIdx > 0) {										
										float segmentLength = (currentCenter - nextCenter).norm();
										auto tempEndPoint = endPoint;
										double lerpParameter = 0.0;

										if(startProfile->crossSectionsPoints[pointIdx]->position.y() < 0)
											alignmentType = 9;
										else
											alignmentType = 8;

										if(startProfile->crossSectionsPoints[pointIdx]->position.y() * endProfile->crossSectionsPoints[pointIdx]->position.y() < 0) {
											double h1 = (startPoint - previousStartPoint).norm();
											double h2 = (endPoint - previousEndPoint).norm();
										
											BLUE_ASSERT(h1 > 0 || h2 > 0)
											lerpParameter = (h1 / h2) / (h1 / h2 + 1.0);
										
											endPoint = buw::lerp(previousStartPoint, previousEndPoint, lerpParameter);									
										}
										alignmentType = 7;

										roadBodyWireframeVertices[sectionIdx].push_back({ buw::Vector3f(startPoint.x(),startPoint.y(),startPoint.z()) ,alignmentId, alignmentType, pickId });
										roadBodyWireframeVertices[sectionIdx].push_back({ buw::Vector3f(endPoint.x(),endPoint.y(),endPoint.z()) ,alignmentId, alignmentType, pickId });

										if(startProfile->crossSectionsPoints[pointIdx]->position.y() < 0)
											alignmentType = 9;
										else 
											alignmentType = 8;

										buw::Vector3f normal1 = (buw::Vector3f)(previousStartPoint - endPoint).cross(startPoint - endPoint).cast<float>();
										if(normal1.norm() != 0)
											normal1.normalize();

										
										if(right) {
											roadBodySolidVertices[sectionIdx].push_back({ buw::Vector3f(previousStartPoint.x(),previousStartPoint.y(),previousStartPoint.z()),normal1 ,alignmentId, alignmentType, pickId, buw::Vector2f(0,0) });
											roadBodySolidVertices[sectionIdx].push_back({ buw::Vector3f(startPoint.x(),startPoint.y(),startPoint.z()),normal1 ,alignmentId, alignmentType, pickId, buw::Vector2f(1,0) });
											roadBodySolidVertices[sectionIdx].push_back({ buw::Vector3f(endPoint.x(),endPoint.y(),endPoint.z()),normal1 ,alignmentId, alignmentType, pickId, buw::Vector2f(1,segmentLength) });
										}
										else {
											roadBodySolidVertices[sectionIdx].push_back({ buw::Vector3f(previousStartPoint.x(),previousStartPoint.y(),previousStartPoint.z()),normal1 ,alignmentId, alignmentType, pickId, buw::Vector2f(0,0) });
											roadBodySolidVertices[sectionIdx].push_back({ buw::Vector3f(endPoint.x(),endPoint.y(),endPoint.z()),normal1 ,alignmentId, alignmentType, pickId, buw::Vector2f(1,segmentLength) });
											roadBodySolidVertices[sectionIdx].push_back({ buw::Vector3f(startPoint.x(),startPoint.y(),startPoint.z()),normal1 ,alignmentId, alignmentType, pickId, buw::Vector2f(1,0) });
										}
										if(startProfile->crossSectionsPoints[pointIdx]->position.y() * endProfile->crossSectionsPoints[pointIdx]->position.y() < 0) {
										
											endPoint = tempEndPoint;
											previousStartPoint = buw::lerp(previousStartPoint, previousEndPoint, lerpParameter);
										
											alignmentType = 7;
										
											roadBodyWireframeVertices[sectionIdx].push_back({ buw::Vector3f(previousStartPoint.x(),previousStartPoint.y(),previousStartPoint.z()) ,alignmentId, alignmentType, pickId });
											roadBodyWireframeVertices[sectionIdx].push_back({ buw::Vector3f(endPoint.x(),endPoint.y(),endPoint.z()) ,alignmentId, alignmentType, pickId });

											if(startProfile->crossSectionsPoints[pointIdx]->position.y() < 0)
												alignmentType = 8;
											else 
												alignmentType = 9;
										}
																	
										buw::Vector3f normal2 = (buw::Vector3f)(endPoint - previousStartPoint).cross(previousEndPoint - previousStartPoint).cast<float>();
										if(normal2.norm() != 0)
											normal2.normalize();

										if(right) {
											roadBodySolidVertices[sectionIdx].push_back({ buw::Vector3f(previousStartPoint.x(),previousStartPoint.y(),previousStartPoint.z()),normal2 ,alignmentId, alignmentType, pickId, buw::Vector2f(0,0) });
											roadBodySolidVertices[sectionIdx].push_back({ buw::Vector3f(endPoint.x(),endPoint.y(),endPoint.z()),normal2 ,alignmentId, alignmentType, pickId, buw::Vector2f(1,segmentLength) });
											roadBodySolidVertices[sectionIdx].push_back({ buw::Vector3f(previousEndPoint.x(),previousEndPoint.y(),previousEndPoint.z()),normal2 ,alignmentId, alignmentType, pickId, buw::Vector2f(0,segmentLength) });
										}
										else {
											roadBodySolidVertices[sectionIdx].push_back({ buw::Vector3f(previousStartPoint.x(),previousStartPoint.y(),previousStartPoint.z()),normal2 ,alignmentId, alignmentType, pickId, buw::Vector2f(0,0) });
											roadBodySolidVertices[sectionIdx].push_back({ buw::Vector3f(previousEndPoint.x(),previousEndPoint.y(),previousEndPoint.z()),normal2 ,alignmentId, alignmentType, pickId, buw::Vector2f(0,segmentLength) });
											roadBodySolidVertices[sectionIdx].push_back({ buw::Vector3f(endPoint.x(),endPoint.y(),endPoint.z()),normal2 ,alignmentId, alignmentType, pickId, buw::Vector2f(1,segmentLength) });
										}
									}									

									previousStartPoint = startPoint;
									previousEndPoint = endPoint;
								}

							}
						}
					}
				}
            }

            if(crossSectionVertices.size() >= 1) {
				std::vector<VertexTypeWireframe> vertices(0);
				for(int i = 0; i < crossSectionVertices.size(); i++)
					vertices.insert(vertices.end(), crossSectionVertices[i].begin(), crossSectionVertices[i].end());
				if(vertices.size() > 0) {
					buw::vertexBufferDescription vbd;
					vbd.data = &vertices[0];
					vbd.vertexCount = static_cast<int>(vertices.size());
					vbd.vertexLayout = VertexTypeWireframe::getVertexLayout();

					auto vertexBuffer = renderSystem()->createVertexBuffer(vbd);
					crossSectionVertexBuffers_.push_back(vertexBuffer);
				}
			}

            if(designCrossSectionVertices.size() >= 1) {
				std::vector<VertexTypeWireframe> vertices(0);
				for(int i = 0; i < designCrossSectionVertices.size(); i++)
					vertices.insert(vertices.end(), designCrossSectionVertices[i].begin(), designCrossSectionVertices[i].end());

				if(vertices.size() > 0) {
					buw::vertexBufferDescription vbd;
					vbd.data = &vertices[0];
					vbd.vertexCount = static_cast<int>(vertices.size());
					vbd.vertexLayout = VertexTypeWireframe::getVertexLayout();

					auto vertexBuffer = renderSystem()->createVertexBuffer(vbd);
					designCrossSectionVertexBuffers_.push_back(vertexBuffer);
				}
			}

            if(roadBodyWireframeVertices.size() > 0) {
				std::vector<VertexTypeWireframe> vertices(0);
				for(int i = 0; i < roadBodyWireframeVertices.size(); i++)
					vertices.insert(vertices.end(), roadBodyWireframeVertices[i].begin(), roadBodyWireframeVertices[i].end());

				if(vertices.size() > 0) {
					buw::vertexBufferDescription vbd;
					vbd.data = &vertices[0];
					vbd.vertexCount = static_cast<int>(vertices.size());
					vbd.vertexLayout = VertexTypeWireframe::getVertexLayout();

					auto vertexBuffer = renderSystem()->createVertexBuffer(vbd);
					roadBodyWireframeVertexBuffers_.push_back(vertexBuffer);
				}
			}

            if(roadBodySolidVertices.size() > 0) {
				std::vector<VertexTypeSolid> vertices(0);
				for(int i = 0; i < roadBodySolidVertices.size(); i++)
					vertices.insert(vertices.end(), roadBodySolidVertices[i].begin(), roadBodySolidVertices[i].end());

				if(vertices.size() > 0) {
					buw::vertexBufferDescription vbd;
					vbd.data = &vertices[0];
					vbd.vertexCount = static_cast<int>(vertices.size());
					vbd.vertexLayout = VertexTypeSolid::getVertexLayout();

					auto vertexBuffer = renderSystem()->createVertexBuffer(vbd);
					roadBodySolidVertexBuffers_.push_back(vertexBuffer);
				}
            }
        }        
    }	
	
	printf("Time passed: %.5f \n", difftime(time(&end), start));
}

void AlignmentEffect::loadShader() {
	try {
		buw::VertexLayout vertexLayout = VertexTypeWireframe::getVertexLayout();

		std::string effectFilename = buw::Singleton<RenderResources>::instance().getResourceRootDir() + "/Shader/AlignmentEffect.be";      

        sampler_ = renderSystem()->createSampler(buw::samplerStateDescription(buw::eFilter::Linear));

		buw::pipelineStateDescription psd;
		psd.effectFilename = effectFilename;
		psd.pipelineStateName = "lineStrip";
		psd.vertexLayout = vertexLayout;
		psd.primitiveTopology = buw::ePrimitiveTopology::LineStrip;
		psd.useAdjacency = true;
		psd.renderTargetFormats = {buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB};
		psd.useDepth = true;
		psd.useMSAA = true;
		psd.fillMode = buw::eFillMode::Solid;

		lineStripState_ = createPipelineState(psd);

		psd.pipelineStateName = "lineList";
        psd.primitiveTopology = buw::ePrimitiveTopology::LineList;
		psd.useAdjacency = false;
        lineListState_ = createPipelineState(psd);
		

		psd.pipelineStateName = "triangleList";
        psd.primitiveTopology = buw::ePrimitiveTopology::TriangleList;
		psd.useAdjacency = false;
        psd.vertexLayout = VertexTypeSolid::getVertexLayout();
        triangleListState_ = createPipelineState(psd);


		psd.pipelineStateName = "pickLineStrip";
        psd.vertexLayout = VertexTypeWireframe::getVertexLayout();
        psd.primitiveTopology = buw::ePrimitiveTopology::LineStrip;
		psd.useAdjacency = true;
        psd.renderTargetFormats = { buw::eTextureFormat::R32_UnsignedInt };
        psd.useDepth = true;
        psd.useMSAA = false;

        pickLineStripState_ = createPipelineState(psd);

		psd.pipelineStateName = "pickLineList";
		psd.primitiveTopology = buw::ePrimitiveTopology::LineList;
		psd.useAdjacency = false;
        pickLineListState_ = createPipelineState(psd);

		psd.pipelineStateName = "pickTriangleList";
        psd.primitiveTopology = buw::ePrimitiveTopology::TriangleList;
		psd.useAdjacency = false;
        psd.vertexLayout = VertexTypeSolid::getVertexLayout();
        pickTriangleListState_ = createPipelineState(psd);
        

       
	} catch (...) {
		lineStripState_ = nullptr;
	}
}

void AlignmentEffect::v_init() {
	loadShader();
	    
	
    setColors({
        buw::Vector4f(144.0f / 255.0f, 238.0f / 255.0f, 144.0f / 255.0f, 1.0f),
        buw::Vector4f(1.0f, 168.0f / 255.0f, 25.0f / 255.0f, 1.0f),
        buw::Vector4f(1.0f, 1.0f, 1.0f, 1.0f),
        buw::Vector4f(0.6f, 168.0f / 255.0f, 25.0f / 255.0f, 1.0f),
        buw::Vector4f(100.0f / 255.0f, 149.0f / 255.0f, 237.0f / 255.0f, 1.0f),
        buw::Vector4f(1.0f, 1.0f, 0.0f, 1.0f),
        buw::Vector4f(1.0f, 0.0f, 0.0f, 1.0f),
        buw::Vector4f(144.0f / 255.0f, 238.0f / 255.0f, 144.0f / 255.0f, 1.0f),
        buw::Vector4f(139.0f / 255.0f, 35.0f / 255.0f, 35.0f / 255.0f, 1.0f),
        buw::Vector4f(0.8f, 0.8f, 0.8f, 1.0f),
        buw::Vector4f(0.0f, 1.0f, 0.0f, 1.0f),
        buw::Vector4f(1.0f, 0.0f, 0.0f, 1.0f)
    });


    auto img1 = buw::loadImage4b("Data/Road.png");

    buw::texture2DDescription td1;
    td1.width = img1.getWidth();
    td1.height = img1.getHeight();
    td1.format = buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB;
    td1.data = img1.getData();

    roadBodyTexture_ = renderSystem()->createTexture2D(td1, buw::eTextureBindType::SRV);

	auto img2 = buw::loadImage4b("Data/RoadNormal.png");

	buw::texture2DDescription td2;
	td2.width = img2.getWidth();
	td2.height = img2.getHeight();
	td2.format = buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB;
	td2.data = img2.getData();

	roadBodyNormalTexture_ = renderSystem()->createTexture2D(td2, buw::eTextureBindType::SRV);


	buw::constantBufferDescription cbd;
	cbd.sizeInBytes = sizeof(SettingsBuffer);
	cbd.data = nullptr;

	settingsBuffer_ = renderSystem()->createConstantBuffer(cbd);

	cbd.sizeInBytes = sizeof(ColorBuffer);
	colorBuffer_ = renderSystem()->createConstantBuffer(cbd); 


	updateSettingsBuffer();
	updateColorBuffer();
}

void AlignmentEffect::v_render() {
	if (lineStripState_ && vertexBuffersAlignment_.size() > 0) {
		buw::ReferenceCounted<buw::ITexture2D> renderTarget = renderSystem()->getBackBufferTarget();
		setRenderTarget(renderTarget, depthStencilMSAA_);
		setViewport(viewport_);

		setPipelineState(lineStripState_);
		setConstantBuffer(worldBuffer_, "WorldBuffer");
		setConstantBuffer(viewportBuffer_, "ViewportBuffer");
        setConstantBuffer(settingsBuffer_, "SettingsBuffer");
        setConstantBuffer(colorBuffer_, "ColorBuffer");
        setConstantBuffer(pickIdBuffer_, "PickIdBuffer");

		for (auto vertexBuffer : vertexBuffersAlignment_) {
			setVertexBuffer(vertexBuffer);
			draw(static_cast<UINT>(vertexBuffer->getVertexCount()));
		}                

        if(bShowCrossSections_ || bShowDesignCrossSections_ || bShowRoadBodyWireframe_) {
            setPipelineState(lineListState_);
            setConstantBuffer(worldBuffer_, "WorldBuffer");
            setConstantBuffer(viewportBuffer_, "ViewportBuffer");
            setConstantBuffer(settingsBuffer_, "SettingsBuffer");
            setConstantBuffer(colorBuffer_, "ColorBuffer");
            setConstantBuffer(pickIdBuffer_, "PickIdBuffer");

            if(bShowCrossSections_) {
                for(auto vertexBuffer : crossSectionVertexBuffers_) {
                    setVertexBuffer(vertexBuffer);
                    draw(static_cast<UINT>(vertexBuffer->getVertexCount()));
                }
            }

            if(bShowDesignCrossSections_) {
                for(auto vertexBuffer : designCrossSectionVertexBuffers_) {
                    setVertexBuffer(vertexBuffer);
                    draw(static_cast<UINT>(vertexBuffer->getVertexCount()));
                }
            }

            if(bShowRoadBodyWireframe_) {
                for(auto vertexBuffer : roadBodyWireframeVertexBuffers_) {
                    setVertexBuffer(vertexBuffer);
                    draw(static_cast<UINT>(vertexBuffer->getVertexCount()));
                }
            }
        }

        if(bShowRoadBodySolid_) {
            setPipelineState(triangleListState_);
            setConstantBuffer(worldBuffer_, "WorldBuffer");
            setConstantBuffer(settingsBuffer_, "SettingsBuffer");
            setConstantBuffer(colorBuffer_, "ColorBuffer");
			setConstantBuffer(pickIdBuffer_, "PickIdBuffer");
            setSampler(sampler_, "samplerLinear");
			setTexture(roadBodyTexture_, "texRoadBodySolid");
			setTexture(roadBodyNormalTexture_, "texRoadBodyNormalSolid");

            for(auto vertexBuffer : roadBodySolidVertexBuffers_) {
                setVertexBuffer(vertexBuffer);
                draw(static_cast<UINT>(vertexBuffer->getVertexCount()));
            }
        }

        setRenderTarget(pickBuffer_, depthStencil_);
        setViewport(viewport_);
        setPipelineState(pickLineStripState_);
        setConstantBuffer(worldBuffer_, "WorldBuffer");
        setConstantBuffer(settingsBuffer_, "SettingsBuffer");

        for(auto vertexBuffer : vertexBuffersAlignment_) {
            setVertexBuffer(vertexBuffer);
            draw(static_cast<UINT>(vertexBuffer->getVertexCount()));
        }

		
		if (bShowCrossSections_ || bShowDesignCrossSections_ || bShowRoadBodyWireframe_) {
			setPipelineState(pickLineListState_);

			if (bShowCrossSections_) {
				for (auto vertexBuffer : crossSectionVertexBuffers_) {
					setVertexBuffer(vertexBuffer);
					draw(static_cast<UINT>(vertexBuffer->getVertexCount()));
				}
			}

			if (bShowDesignCrossSections_) {
				for (auto vertexBuffer : designCrossSectionVertexBuffers_) {
					setVertexBuffer(vertexBuffer);
					draw(static_cast<UINT>(vertexBuffer->getVertexCount()));
				}
			}


			if (bShowRoadBodyWireframe_) {
				for (auto vertexBuffer : roadBodyWireframeVertexBuffers_) {
					setVertexBuffer(vertexBuffer);
					draw(static_cast<UINT>(vertexBuffer->getVertexCount()));
				}
			}
		}
	}
}

void AlignmentEffect::updateSettingsBuffer()
{
    buw::constantBufferDescription cbd;
    cbd.sizeInBytes = sizeof(SettingsBuffer);
    cbd.data = &settings_;

    settingsBuffer_->uploadData(cbd);
}

void AlignmentEffect::updateColorBuffer()
{
    buw::constantBufferDescription cbd;
    cbd.sizeInBytes = sizeof(ColorBuffer);
    cbd.data = &colors_;

    colorBuffer_->uploadData(cbd);
}


void AlignmentEffect::setCurrentSelectedAlignment(const int index) {
	if(index != -1 && index != settings_.selectedAlignmentIndex.data[0]) {
		AlignmentSelectionChanged((const unsigned int)index);
		settings_.selectedAlignmentIndex = index;
		updateSettingsBuffer();
	}
}

void AlignmentEffect::setColors(std::vector<buw::Vector4f> colors)
{
    if(colors.size() < 12)
        return;
    colors_.alignment = colors[0];
    colors_.selected = colors[1];
    colors_.highlight = colors[2];
    colors_.crossSection = colors[3];
    colors_.designCrossSection = colors[4];
    colors_.clothoid = colors[5];
    colors_.arc = colors[6];
    colors_.line = colors[7];
    colors_.bloss = colors[8];
    colors_.roadBody = colors[9];
    colors_.roadBodyConvex = colors[10];
    colors_.roadBodyConcave = colors[11];
}

int AlignmentEffect::getAlignmentId(UINT pickId)
{
    if(alignmentIds_.count(pickId))
        return alignmentIds_[pickId];
    else
        return -1;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END