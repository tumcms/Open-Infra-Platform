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

//#include "buw.BlueImageProcessing.color.h"
//#include "buw.BlueImageProcessing.colorConstants.h"
//#include "Viewport.h"
//#include "buw.BlueEngine.h"
//#include "../../DataManagement/Data.h"
//#include "TerrainMeshBuilder.h"
//#include "CoordinateSystem.h"
//
//void OpenInfraPlatform::UserInterface::Viewport::createAlignmentThreeDimensional_CrossSection()
//{
//	auto alignmentModel = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getAlignmentModel();
//	buw::Vector3d offsetViewArea = getOffset();
//
//	buw::Color3f c = buw::ColorConstants3f::lightgreen();
//
//	// draw cross sections
//	for (int alignmentIndex = 0; alignmentIndex < alignmentModel->getAlignmentCount(); alignmentIndex++)
//	{
//		if (alignmentModel->getAlignment(alignmentIndex)->getType() != buw::e3DAlignmentType::e2DBased)
//		{
//			continue;
//		}
//
//		buw::ReferenceCounted<buw::Alignment2DBased3D> alignment = std::static_pointer_cast<buw::Alignment2DBased3D>(alignmentModel->getAlignment(alignmentIndex));
//		int numberOfAlignmentCrossSections = alignment->getCrossSectionCount();
//
//		for(int csIndex = 0; csIndex < numberOfAlignmentCrossSections; csIndex++) //iterate through all CrossSections of alignment
//		{
//			buw::ReferenceCounted<buw::CrossSectionStatic> cs = alignment->getCrossSection(csIndex);
//			drawCrossSection(alignment,cs,offsetViewArea);
//
//			if(csIndex < numberOfAlignmentCrossSections-1)
//			{ 
//				buw::ReferenceCounted<buw::CrossSectionStatic> csNext = alignment->getCrossSection(csIndex+1);
//				if(connectCrossSections_ || doSolidCrossSections_) drawRoadBodyBetweenStation(alignment,cs,csNext,offsetViewArea);
//			}
//		}
//	}
//}
//
//void OpenInfraPlatform::UserInterface::Viewport::drawCrossSection(
//	buw::ReferenceCounted<buw::Alignment2DBased3D> alignment, 
//	buw::ReferenceCounted<buw::CrossSectionStatic> cs, 
//	buw::Vector3d offsetViewArea)
//{
//	buw::Vector3d center = alignment->getPosition(cs->stationing);
//	buw::matrix44d rotation = getGlobalRotationMatrixOnStation(alignment,cs->stationing);
//
//	if(showCrossSection_ || showDesignCrossSection_){
//		// draw station on alignment
//		vertexCacheAlignmentPoint_->setColor(buw::ColorConstants3f::blue());
//		vertexCacheAlignmentPoint_->drawPoint(alignment->getPosition(cs->stationing)-offsetViewArea);
//	}
//
//	if(showCrossSection_)
//	{
//		// iterate through all CrossSectionProfiles of CrossSection
//		for(int csSurfaceIndex=0; csSurfaceIndex < cs->getCrossSectionProfileCount(); csSurfaceIndex++) 
//		{
//			buw::ReferenceCounted<buw::CrossSectionProfile> csSurf =cs->getCrossSectionProfile(csSurfaceIndex);
//
//			bool isFirstPoint=true;
//			buw::Vector3d lastPoint;
//
//			// iterate through all points  of CrossSectionProfile
//			for (int p = 0; p < csSurf->pntList2D.size(); p++)	
//			{
//				buw::Vector3d csp = buw::Vector3d(
//					0,
//					csSurf->pntList2D[p].x(),
//					csSurf->pntList2D[p].y() 
//					);
//
//				buw::Vector3d t_csp = buw::transform(rotation, csp);
//
//				t_csp= buw::Vector3d(
//					t_csp[0] + center[0] - offsetViewArea[0],
//					t_csp[1] + center[1] - offsetViewArea[1],
//					t_csp[2] - offsetViewArea[2]
//				);
//
//				if(isFirstPoint)
//					isFirstPoint=false;
//				else{
//					vertexCacheAlignmentLine_->setColor(buw::ColorConstants3f::green());
//					vertexCacheAlignmentLine_->drawLine(lastPoint, t_csp);
//				}
//
//				lastPoint=t_csp;
//			}
//		}
//	}
//
//	if(showDesignCrossSection_)
//	{
//		// iterate through all DesignCrossSectionProfiles of CrossSection
//		for(int csDesignSurfaceIndex=0; csDesignSurfaceIndex < cs->getDesignCrossSectionProfileCount(); csDesignSurfaceIndex++)
//		{
//			buw::ReferenceCounted<buw::DesignCrossSectionProfile> csDesignSurf = cs->getDesignCrossSectionProfile(csDesignSurfaceIndex);
//
//			bool isFirstPoint = true;
//			buw::Vector3d lastPoint;
//
//			// iterate through all points  of DesignCrossSectionProfile
//			for(int p=0; p<csDesignSurf->crossSectionsPoints.size(); p++) 
//			{
//				buw::Vector3d csp = buw::Vector3d(
//					0,
//					csDesignSurf->crossSectionsPoints[p]->position.x(),
//					csDesignSurf->crossSectionsPoints[p]->position.y()
//				);
//
//				buw::Vector3d t_csp = buw::transform(rotation, csp);
//				t_csp+=  center - offsetViewArea;
//
//				if(isFirstPoint)
//				{ 
//					isFirstPoint = false;
//				}
//				else
//				{
//					vertexCacheAlignmentLine_->setColor(buw::ColorConstants3f::cornflowerblue());
//					vertexCacheAlignmentLine_->drawLine(lastPoint, t_csp);
//				}
//
//				lastPoint=t_csp;
//			}
//		}
//	}
//}
//
//void OpenInfraPlatform::UserInterface::Viewport::drawRoadBodyBetweenStation(
//	buw::ReferenceCounted<buw::Alignment2DBased3D> alignment,
//	buw::ReferenceCounted<buw::CrossSectionStatic> cs, 
//	buw::ReferenceCounted<buw::CrossSectionStatic> nextCs, 
//	buw::Vector3d offsetViewArea)
//{
//	buw::Vector3d startCenter = alignment->getPosition(cs->stationing);
//	buw::matrix44d startRotation = getGlobalRotationMatrixOnStation(alignment,cs->stationing);
//
//	buw::Vector3d endCenter = alignment->getPosition(nextCs->stationing);
//	buw::matrix44d endRotation = getGlobalRotationMatrixOnStation(alignment,nextCs->stationing);
//
//	// draw closed design surfaces
//	if(cs->getClosedDesignCrossSectionProfileCount() == nextCs->getClosedDesignCrossSectionProfileCount())
//	{
//		// iterate through all closed DesignCrossSectionProfiles of CrossSection
//		for(int csDesignSurfaceIndex=0; csDesignSurfaceIndex < cs->getClosedDesignCrossSectionProfileCount(); csDesignSurfaceIndex++)
//		{
//			buw::ReferenceCounted<buw::DesignCrossSectionProfile> csDesignSurf = cs->getClosedDesignCrossSectionProfile(csDesignSurfaceIndex);
//			buw::ReferenceCounted<buw::DesignCrossSectionProfile> nextCsDesignSurf = nextCs->getClosedDesignCrossSectionProfile(csDesignSurfaceIndex);
//
//			if (csDesignSurf->crossSectionsPoints.size() == nextCsDesignSurf->crossSectionsPoints.size())
//			{
//				buw::Vector3d lastPoint;
//				buw::Vector3d nextLastPoint;
//				bool isFirst=true;
//
//				bool isSlope=false;
//				int slopeType=0;
//				bool isTopFace=false; 
//
//				// iterate through all points of DesignCrossSectionProfile
//				for (int p = 0; p<csDesignSurf->crossSectionsPoints.size(); p++)
//				{
//					//   nextLastPoint	 next_t_csp
//					//		---O--------------O---	nextDesignSurface
//					//		   |		     /|
//					//		   |		    / |
//					//		   |	2	   /  |
//					//		   |		  /   |
//					//		   |	     /    |
//					//		   |		/     |
//					//		   |	   /      |
//					//		   |	  /       |
//					//		   |	 /        |
//					//		   |	/         |
//					//		   |   /          |
//					//		   |  /      1    |
//					//		   | /            |
//					//		   |/             |
//					//		---O--------------O--- actDesignSurface
//					//     lastPoint		t_csp
//
//					if (csDesignSurf->crossSectionsPoints.size() == 2){
//						isSlope=true;
//					}
//
//					// points on smaller station
//					buw::Vector3d csp = buw::Vector3d(
//						0,
//						csDesignSurf->crossSectionsPoints[p]->position.x(),
//						csDesignSurf->crossSectionsPoints[p]->position.y()
//						);
//
//					if(csp==buw::Vector3d(0,0,0)) isTopFace=true;
//
//					// transform points on smaller station
//					buw::Vector3d t_csp = buw::transform(startRotation, csp);
//					t_csp +=  startCenter - offsetViewArea;
//
//					// points on greater station
//					buw::Vector3d nextcsp = buw::Vector3d(
//						0,
//						nextCsDesignSurf->crossSectionsPoints[p]->position.x(),
//						nextCsDesignSurf->crossSectionsPoints[p]->position.y()
//						);
//
//					if(nextcsp==buw::Vector3d(0,0,0)) isTopFace=true;
//
//					// transform points on grater station
//					buw::Vector3d next_t_csp = buw::transform(endRotation, nextcsp);
//					next_t_csp +=  endCenter - offsetViewArea;
//
//					// draw line between station points
//					if(connectCrossSections_)
//					{
//						vertexCacheAlignmentLine_->setColor(buw::ColorConstants3f::white());
//						vertexCacheAlignmentLine_->drawLine(t_csp, next_t_csp);
//					}
//
//					// draw triangles of road body
//					if(!isFirst && doSolidCrossSections_)
//					{
//						buw::VertexPosition3Color3Normal3Texture2 v1,v2,v3;
//						buw::Vector3f color=buw::Vector3f(1.0f,1.0f,1.0f);
//
//						buw::Vector3f normal1 = (buw::Vector3f)((lastPoint - next_t_csp) ^ (t_csp - next_t_csp));
//						if(normal1.length()!=0) normal1.normalize();
//						buw::Vector3f normal2 = (buw::Vector3f)((lastPoint - next_t_csp) ^ (t_csp - next_t_csp));
//						if(normal2.length()!=0) normal2.normalize();
//
//						// draw road texture
//						if(drawRoadTexture_ && isTopFace)
//						{
//							double segmentLength=(endCenter-startCenter).length();
//
//							// triangle 1
//							v1=buw::VertexPosition3Color3Normal3Texture2::create((buw::Vector3f)lastPoint,		color,	normal1, buw::Vector2f(0,0));
//							v2=buw::VertexPosition3Color3Normal3Texture2::create((buw::Vector3f)t_csp,			color,	normal1, buw::Vector2f(1,0));
//							v3=buw::VertexPosition3Color3Normal3Texture2::create((buw::Vector3f)next_t_csp,		color,	normal1, buw::Vector2f(1,segmentLength));
//
//							triangleCacheP3C3N3UV2_->drawTriangle(v1,v2,v3);
//
//							// triangle 2
//							v1=buw::VertexPosition3Color3Normal3Texture2::create((buw::Vector3f)lastPoint,	    color,	normal2, buw::Vector2f(0,0));
//							v2=buw::VertexPosition3Color3Normal3Texture2::create((buw::Vector3f)next_t_csp,		color,	normal2, buw::Vector2f(1,segmentLength));
//							v3=buw::VertexPosition3Color3Normal3Texture2::create((buw::Vector3f)nextLastPoint,	color,	normal2, buw::Vector2f(0,segmentLength));
//
//							triangleCacheP3C3N3UV2_->drawTriangle(v1,v2,v3);
//						}
//						else
//						{
//							// triangle 1
//							buw::VertexCacheTriangleVertex* triangleVertices= new buw::VertexCacheTriangleVertex[3];
//							triangleVertices[0] = buw::VertexCacheTriangleVertex::create((buw::Vector3f)lastPoint,		color,	normal1 );
//							triangleVertices[1] = buw::VertexCacheTriangleVertex::create((buw::Vector3f)t_csp,			color,	normal1 );
//							triangleVertices[2] = buw::VertexCacheTriangleVertex::create((buw::Vector3f)next_t_csp,		color,	normal1 );
//
//							// triangle 2
//							buw::VertexCacheTriangleVertex* triangleVertices2= new buw::VertexCacheTriangleVertex[3];
//							triangleVertices2[0] = buw::VertexCacheTriangleVertex::create((buw::Vector3f)lastPoint,		color,	normal2 );
//							triangleVertices2[1] = buw::VertexCacheTriangleVertex::create((buw::Vector3f)next_t_csp,	color,	normal2 );
//							triangleVertices2[2] = buw::VertexCacheTriangleVertex::create((buw::Vector3f)nextLastPoint,	color,	normal2 );
//
//							vertexCacheAlignmentTriangle_->drawTriangle(triangleVertices);
//							vertexCacheAlignmentTriangle_->drawTriangle(triangleVertices2);
//						}
//
//					}
//					else isFirst=false;
//
//					lastPoint=t_csp;
//					nextLastPoint=next_t_csp;
//
//				}
//			}
//		}
//	}
//
//	// draw open design surfaces
//	if(cs->getOpenDesignCrossSectionProfileCount() == nextCs->getOpenDesignCrossSectionProfileCount())
//	{
//		// iterate through all open DesignCrossSectionProfiles of CrossSection
//		for(int csDesignSurfaceIndex=0; csDesignSurfaceIndex < cs->getOpenDesignCrossSectionProfileCount(); csDesignSurfaceIndex++)
//		{
//			buw::ReferenceCounted<buw::DesignCrossSectionProfile> csDesignSurf = cs->getOpenDesignCrossSectionProfile(csDesignSurfaceIndex);
//			buw::ReferenceCounted<buw::DesignCrossSectionProfile> nextCsDesignSurf = nextCs->getOpenDesignCrossSectionProfile(csDesignSurfaceIndex);
//
//			if (csDesignSurf->crossSectionsPoints.size() == nextCsDesignSurf->crossSectionsPoints.size())
//			{
//				buw::Vector3d lastPoint;
//				buw::Vector3d nextLastPoint;
//				bool isFirst=true;
//
//				// iterate through all points of DesignCrossSectionProfile
//				for (int p = 0; p<csDesignSurf->crossSectionsPoints.size(); p++)
//				{
//					// points on smaller station
//					buw::Vector3d csp = buw::Vector3d(
//						0,
//						csDesignSurf->crossSectionsPoints[p]->position.x(),
//						csDesignSurf->crossSectionsPoints[p]->position.y()
//						);
//
//					// transform points on smaller station
//					buw::Vector3d t_csp = buw::transform(startRotation, csp);
//					t_csp +=  startCenter - offsetViewArea;
//
//					// points on greater station
//					buw::Vector3d nextcsp = buw::Vector3d(
//						0,
//						nextCsDesignSurf->crossSectionsPoints[p]->position.x(),
//						nextCsDesignSurf->crossSectionsPoints[p]->position.y()
//						);
//
//					// transform points on grater station
//					buw::Vector3d next_t_csp = buw::transform(endRotation, nextcsp);
//					next_t_csp +=  endCenter - offsetViewArea;
//
//					// draw triangles of road body
//					if(!isFirst){
//
//						buw::Vector3f color;
//						if (csDesignSurf->crossSectionsPoints[p]->position.y()>0)
//							color=buw::Vector3f(1.0f,0.0f,0.0f);
//						else if (csDesignSurf->crossSectionsPoints[p]->position.y()<0)
//							color=buw::Vector3f(0.0f,1.0f,0.0f);
//
//						buw::Vector3d temp_next_t_csp;
//						double lerpParameter;
//
//						// --------------------------------------------------------------------------------------------------------------------------------------------------
//						// triangle 1
//						// --------------------------------------------------------------------------------------------------------------------------------------------------
//						// if change of slope sign
//						if (csDesignSurf->crossSectionsPoints[p]->position.y()*nextCsDesignSurf->crossSectionsPoints[p]->position.y()<0)
//						{
//							temp_next_t_csp=next_t_csp;
//
//							double h1=std::abs((t_csp-lastPoint).length());
//							double h2=std::abs((next_t_csp-nextLastPoint).length());
//
//							lerpParameter=(h1/h2)/(h1/h2+1);
//
//							next_t_csp=buw::lerp(lastPoint, nextLastPoint, lerpParameter);
//
//							if (csDesignSurf->crossSectionsPoints[p]->position.y()>0)
//								color=buw::Vector3f(1.0f,0.0f,0.0f);
//							else if (csDesignSurf->crossSectionsPoints[p]->position.y()<0)
//								color=buw::Vector3f(0.0f,1.0f,0.0f);
//						}
//	
//						// draw line between station points
//						if(connectCrossSections_)
//						{
//							vertexCacheAlignmentLine_->setColor(buw::ColorConstants3f::white());
//							vertexCacheAlignmentLine_->drawLine(t_csp, next_t_csp);
//						}
//
//						if(doSolidCrossSections_)
//						{
//							buw::Vector3f normal1 = (buw::Vector3f)((lastPoint - next_t_csp) ^ (t_csp - next_t_csp));
//							if(normal1.length()!=0) normal1.normalize();
//
//							buw::VertexCacheTriangleVertex* triangleVertices= new buw::VertexCacheTriangleVertex[3];
//							triangleVertices[0] = buw::VertexCacheTriangleVertex::create((buw::Vector3f)lastPoint,		color,	normal1 );
//							triangleVertices[1] = buw::VertexCacheTriangleVertex::create((buw::Vector3f)t_csp,			color,	normal1 );
//							triangleVertices[2] = buw::VertexCacheTriangleVertex::create((buw::Vector3f)next_t_csp,		color,	normal1 );
//
//							vertexCacheAlignmentTriangle_->drawTriangle(triangleVertices);
//						 }
//
//						// --------------------------------------------------------------------------------------------------------------------------------------------------
//						// triangle 2
//						// --------------------------------------------------------------------------------------------------------------------------------------------------
//						// if change of slope sign
//						if (csDesignSurf->crossSectionsPoints[p]->position.y()*nextCsDesignSurf->crossSectionsPoints[p]->position.y()<0)
//						{
//							next_t_csp=temp_next_t_csp;
//							lastPoint=buw::lerp(lastPoint, nextLastPoint, lerpParameter);
//
//							if (csDesignSurf->crossSectionsPoints[p]->position.y()>0)
//								color=buw::Vector3f(0.0f,1.0f,0.0f);
//							else if (csDesignSurf->crossSectionsPoints[p]->position.y()<0)
//								color=buw::Vector3f(1.0f,0.0f,0.0f);
//
//							// draw line between station points
//							if(connectCrossSections_)
//							{
//								vertexCacheAlignmentLine_->setColor(buw::ColorConstants3f::white());
//								vertexCacheAlignmentLine_->drawLine(lastPoint, next_t_csp);
//							}
//						}
//
//						if(doSolidCrossSections_){
//							buw::Vector3f normal2 = (buw::Vector3f)((next_t_csp-lastPoint) ^ (nextLastPoint-lastPoint));
//							if(normal2.length()!=0) normal2.normalize();
//
//							buw::VertexCacheTriangleVertex* triangleVertices2= new buw::VertexCacheTriangleVertex[3];
//							triangleVertices2[0] = buw::VertexCacheTriangleVertex::create((buw::Vector3f)lastPoint,		color,	normal2 );
//							triangleVertices2[1] = buw::VertexCacheTriangleVertex::create((buw::Vector3f)next_t_csp,	color,	normal2 );
//							triangleVertices2[2] = buw::VertexCacheTriangleVertex::create((buw::Vector3f)nextLastPoint,	color,	normal2 );
//
//							vertexCacheAlignmentTriangle_->drawTriangle(triangleVertices2);
//						 }
//					}
//					else isFirst=false;
//
//					lastPoint=t_csp;
//					nextLastPoint=next_t_csp;
//
//				}
//			}
//		}
//	}
//
//}
//
//buw::matrix44d OpenInfraPlatform::UserInterface::Viewport::getGlobalRotationMatrixOnStation(
//	buw::ReferenceCounted<buw::Alignment2DBased3D> alignment, 
//	buw::Stationing station)
//{
//	buw::Vector3d mid = alignment->getPosition(station);
//	buw::Vector3d mid2 = alignment->getPosition(station + 0.001);
//
//	buw::Vector3d tangentVector;
//	
//	if (buw::distance(mid2, mid) > 0.0001)
//	{
//		tangentVector = (mid2 - mid).normalize();
//	}
//	else
//	{
//		// hack... try differnt station
//		mid2 = alignment->getPosition(station + 0.1);
//		tangentVector = mid2 - mid;  
//	}
//		
//	buw::Vector3d xaxis = buw::Vector3d(1, 0, 0);
//	double angle = buw::calculateAngleBetweenVectors(xaxis, tangentVector);
//
//	// horizontal rotation transformation
//	buw::Vector2d normal2d= buw::Vector2d(tangentVector.x(),tangentVector.y());
//	buw::Vector2d xaxis2d= buw::Vector2d(1,0);
//	angle=buw::calculateAngleBetweenVectors(xaxis2d, normal2d);
//	buw::matrix44d rotationHrz = buw::createRotationZ44d(angle);
//
//	// vertical rotation transformation
//	normal2d=buw::Vector2d(tangentVector.x(), tangentVector.z());
//	angle=buw::calculateAngleBetweenVectors(xaxis2d, normal2d);
//	buw::matrix44d rotationVer = buw::createRotationY44d(angle);
//
//	return rotationHrz;//*rotationVer;
//}