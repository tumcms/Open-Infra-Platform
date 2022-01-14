// Copied and modified code from "IfcPlusPlus".
// This code is available under the OSGPL license. Original copyright notice:

/* -*-c++-*- IfcPlusPlus - www.ifcplusplus.com  - Copyright (C) 2011 Fabian Gerold
*
* This library is open source and may be redistributed and/or modified under
* the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
* (at your option) any later version.  The full license is in LICENSE file
* included with this distribution, and on the openscenegraph.org website.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* OpenSceneGraph Public License for more details.
*/

// More details can be found in README.md file in the root directory.

#pragma once
// unix
#ifndef SOLIDMODELCONVERTER_H
#define SOLIDMODELCONVERTER_H

#include "CarveHeaders.h"

#include "ConverterBase.h"

#include "ProfileCache.h"
#include "ProfileConverter.h"
#include "FaceConverter.h"
#include "PlacementConverter.h"
#include "CurveConverter.h"

#include "EXPRESS/EXPRESSEntity.h"

namespace OpenInfraPlatform
{
	namespace Core {
	namespace IfcGeometryConverter
	{
		template <
			class IfcEntityTypesT
		>
			class SolidModelConverterT : public ConverterBaseT<IfcEntityTypesT>
		{
		public:
			SolidModelConverterT(
				std::shared_ptr<GeometrySettings> geomSettings,
				std::shared_ptr<UnitConverter<IfcEntityTypesT>> uc,
				std::shared_ptr<PlacementConverterT<IfcEntityTypesT>> pc,
				std::shared_ptr<CurveConverterT<IfcEntityTypesT>> cc,
				std::shared_ptr<FaceConverterT<IfcEntityTypesT>> fc,
				std::shared_ptr<ProfileCacheT<IfcEntityTypesT>> profc)
				:
				ConverterBaseT<IfcEntityTypesT>(geomSettings, uc),
				placementConverter(pc),
				curveConverter(cc),
				faceConverter(fc),
				profileCache(profc)
			{

			}

			~SolidModelConverterT()
			{

			}


			/*	SolidModelConverter.h
			For IFC4x1:

			IfcCsgSolid						http://www.buildingsmart-tech.org/ifc/IFC4x1/final/html/schema/ifcgeometricmodelresource/lexical/ifccsgsolid.htm

			IfcManifoldSolidBrep			http://www.buildingsmart-tech.org/ifc/IFC4x1/final/html/schema/ifcgeometricmodelresource/lexical/ifcmanifoldsolidbrep.htm
				IfcAdvancedBrep*
				IfcFacetedBrep

			IfcSectionedSolid				http://www.buildingsmart-tech.org/ifc/IFC4x1/final/html/schema/ifcgeometricmodelresource/lexical/ifcsectionedsolid.htm
				IfcSectionedSolidHorizontal*

			IfcSweptAreaSolid				http://www.buildingsmart-tech.org/ifc/IFC4x1/final/html/schema/ifcgeometricmodelresource/lexical/ifcsweptareasolid.htm
				IfcExtrudedAreaSolid*
				IfcFixedReferenceSweptAreaSolid*
				IfcRevolvedAreaSolid*
				IfcSurfaceCurveSweptAreaSolid

			IfcSweptDiskSolid				http://www.buildingsmart-tech.org/ifc/IFC4x1/final/html/schema/ifcgeometricmodelresource/lexical/ifcsweptdisksolid.htm
				IfcSweptDiskSolidPolygonal*

			*: not implemented in SolidModelConverter.h

			*/

			/**********************************************************************************************/
			/*! \brief Converts \c IfcSolidModel to meshes.
			*
			* \param[in] solidModel				The \c IfcSolidModel to be converted.
			* \param[in] pos					The relative location of the origin of the representation's coordinate system within the geometric context.
			* \param[out] itemData				A pointer to be filled with the relevant data.
			*
			* \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricmodelresource/lexical/ifcsolidmodel.htm
			*/
			void convertIfcSolidModel(
				const oip::EXPRESSReference<typename IfcEntityTypesT::IfcSolidModel>& solidModel,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				// **************************************************************************************************************************
				//	ENTITY IfcSolidModel
				//		ABSTRACT SUPERTYPE OF(ONEOF(
				//			IfcCsgSolid, 
				//			IfcManifoldSolidBrep, 
				//			IfcSectionedSolid, 
				//			IfcSweptAreaSolid, 
				//			IfcSweptDiskSolid))
				//		SUBTYPE OF(IfcGeometricRepresentationItem);
				//		DERIVE
				//		Dim : IfcDimensionCount: = 3;
				//	END_ENTITY;
				// **************************************************************************************************************************

				//	IfcCsgSolid SUBTYPE of IfcSolidModel																									//																			//
				if (solidModel.template isOfType<typename IfcEntityTypesT::IfcCsgSolid>())
				{
					convertIfcCsgSolid( solidModel.template as<typename IfcEntityTypesT::IfcCsgSolid>(), 
						pos, itemData);
					return;
				} //End of IfcCsgSolid.

				//	IfcManifoldSolidBrep SUBTYPE of IfcSolidModel																							//
				//	ABSTRACT SUPERTYPE of IfcAdvancedBrep, IfcFacetedBrep																					//
				if (solidModel.template isOfType<typename IfcEntityTypesT::IfcManifoldSolidBrep>())
				{
					convertIfcManifoldSolidBrep(solidModel.template as<typename IfcEntityTypesT::IfcManifoldSolidBrep>(), 
						pos, itemData);
					return;
				} // End of IfcManifoldSolidBrep.

				//	IfcSectionedSolid SUBTYPE of IfcSolidModel																							  //
				//	ABSTRACT SUPERTYPE of IfcSectionedSolidHorizontal																					  //
				if (solidModel.template isOfType<typename IfcEntityTypesT::IfcSectionedSolid>())
				{
					convertIfcSectionedSolid(solidModel.template as<typename IfcEntityTypesT::IfcSectionedSolid>(), 
						pos, itemData);
					return;
				} // End of IfcSectionedSolid.

				//	IfcSweptAreaSolid SUBTYPE of IfcSolidModel																								//
				//	ABSTRACT SUPERTYPE of IfcExtrudedAreaSolid, IfcFixedReferenceSweptAreaSolid, IfcRevolvedAreaSolid, IfcSurfaceCurveSweptAreaSolid		//
				if (solidModel.template isOfType<typename IfcEntityTypesT::IfcSweptAreaSolid>())
				{
					convertIfcSweptAreaSolid(solidModel.template as<typename IfcEntityTypesT::IfcSweptAreaSolid>(),
						pos, itemData);
					return;
				} // End of IfcSweptAreaSolid.

				//	IfcSweptDiskSolid SUBTYPE of IfcSolidModel																								//
				//	ABSTRACT SUPERTYPE of IfcSweptDiskSolidPolygonal																						//
				if (solidModel.template isOfType<typename IfcEntityTypesT::IfcSweptDiskSolid>())
				{
					convertIfcSweptDiskSolid(solidModel.template as<typename IfcEntityTypesT::IfcSweptDiskSolid>(), 
						pos, itemData);
					return;
				} // End of IfcSweptDiskSolid.

				// Other entities we do not support.
				throw oip::UnhandledException(solidModel);
			}

			/**********************************************************************************************/
			/*! \brief Converts \c IfcCsgSolid to meshes.
			*
			* \param[in] csgSolid				The \c IfcCsgSolid to be converted.
			* \param[in] pos					The relative location of the origin of the representation's coordinate system within the geometric context.
			* \param[out] itemData				A pointer to be filled with the relevant data.
			*
			* \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricmodelresource/lexical/ifccsgsolid.htm
			*/
            void convertIfcCsgSolid(
				const oip::EXPRESSReference<typename IfcEntityTypesT::IfcCsgSolid> &csgSolid, 
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
            {
				// **************************************************************************************************************************
				//	ENTITY IfcCsgSolid
				//		SUBTYPE OF(IfcSolidModel);
				//		TreeRootExpression: IfcCsgSelect;
				//	END_ENTITY;
				// **************************************************************************************************************************

                if(csgSolid.expired())
                    throw oip::ReferenceExpiredException(csgSolid);

                switch(csgSolid->TreeRootExpression.which()) {
                case 0:
                    convertIfcBooleanResult(csgSolid->TreeRootExpression.get<0>().lock(), pos, itemData);
                    break;
                case 1:
                    convertIfcCsgPrimitive3D(csgSolid->TreeRootExpression.get<1>().lock(), pos, itemData);
                    break;
                default:
                    throw oip::InconsistentModellingException("IfcCsgSolid->TreeRootExpression has no value set.");
                }
            }

			/*! \brief Converts \c IfcManifoldSolidBrep to meshes.
			 *
			 * \param[in] manifoldSolidBrep			The \c IfcManifoldSolidBrep to be converted.
			 * \param[in] pos						The relative location of the origin of the representation's coordinate system within the geometric context.
			 * \param[out] itemData					A pointer to be filled with the relevant data.
			 *
			 * \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricmodelresource/lexical/ifcmanifoldsolidbrep.htm
			*/
			void convertIfcManifoldSolidBrep(
				const EXPRESSReference<typename IfcEntityTypesT::IfcManifoldSolidBrep> &manifoldSolidBrep,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				// **************************************************************************************************************************
				//	ENTITY IfcManifoldSolidBrep
				//		ABSTRACT SUPERTYPE OF(ONEOF(
				//			IfcAdvancedBrep, 
				//			IfcFacetedBrep))
				//		SUBTYPE OF(IfcSolidModel);
				//		Outer: IfcClosedShell;
				//	END_ENTITY;
				// **************************************************************************************************************************

				// check input
				if (manifoldSolidBrep.expired())
					throw oip::ReferenceExpiredException(manifoldSolidBrep);

				// (1/2) IfcAdvancedBrep SUBTYPE of IfcManifoldSolidBrep
				if (manifoldSolidBrep.template isOfType<typename IfcEntityTypesT::IfcAdvancedBrep>())
				{
					convertIfcAdvancedBrep(manifoldSolidBrep.template as<typename IfcEntityTypesT::IfcAdvancedBrep>(),
						pos, itemData);
					return;
				}

				// (2/2) IfcFacetedBrep SUBTYPE of IfcManifoldSolidBrep
				if (manifoldSolidBrep.template isOfType<typename IfcEntityTypesT::IfcFacetedBrep>()) {
					convertIfcFacetedBrep(manifoldSolidBrep.template as<typename IfcEntityTypesT::IfcFacetedBrep>(), 
						pos, itemData);
					return;
				}

				// the rest is not supported
				throw oip::UnhandledException(manifoldSolidBrep);
			}

			void convertIfcAdvancedBrep(
				const EXPRESSReference<typename IfcEntityTypesT::IfcAdvancedBrep> &advancedBrep,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				throw oip::UnhandledException(advancedBrep);
			}

			void convertIfcFacetedBrep(
				const EXPRESSReference<typename IfcEntityTypesT::IfcFacetedBrep> &facetedBrep,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				if (facetedBrep.expired())
					throw oip::ReferenceExpiredException(facetedBrep);

				// (1/2) IfcFacetedBrepWithVoids SUBTYPE of IfcFacetedBrep
				if (facetedBrep.isOfType<typename IfcEntityTypesT::IfcFacetedBrepWithVoids>()) 
				{
					convertIfcFacetedBrepWithVoids(facetedBrep.template as<typename IfcEntityTypesT::IfcFacetedBrepWithVoids>(),
						pos, itemData);
					return;
				}
				// (2/2) IfcFacetedBrep
				// Get outer (attribute 1).
				convertIfcClosedShell(facetedBrep->Outer, pos, itemData);
				// Done
			}

			void convertIfcFacetedBrepWithVoids(
				const EXPRESSReference<typename IfcEntityTypesT::IfcFacetedBrepWithVoids> &facetedBrepWithVoids,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				throw oip::UnhandledException(facetedBrepWithVoids);
			}

            void convertIfcClosedShell(
				const EXPRESSReference<typename IfcEntityTypesT::IfcClosedShell> &outerShell, 
				const carve::math::Matrix& pos, 
				std::shared_ptr<ItemData>& itemData
			) const noexcept(false)
            {
				if (outerShell.expired())
					throw oip::ReferenceExpiredException(outerShell);

                std::shared_ptr<ItemData> inputDataOuterShell(new ItemData());

                faceConverter->convertIfcFaceList(outerShell->CfsFaces, pos, inputDataOuterShell);

                std::copy(inputDataOuterShell->open_or_closed_polyhedrons.begin(),
                            inputDataOuterShell->open_or_closed_polyhedrons.end(),
                            std::back_inserter(itemData->closed_polyhedrons));
            }

			/*! \brief Converts \c IfcSectionedSolid to meshes.
			 *
			 * \param[in] sectionedSolid			The \c IfcSectionedSolid to be converted.
			 * \param[in] pos						The relative location of the origin of the representation's coordinate system within the geometric context.
			 * \param[out] itemData					A pointer to be filled with the relevant data.
			 *
			 * \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricmodelresource/lexical/ifcsectionedsolid.htm
			*/
			void convertIfcSectionedSolid(
				const EXPRESSReference<typename IfcEntityTypesT::IfcSectionedSolid>& sectionedSolid,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				// **************************************************************************************************************************
				//	ENTITY IfcSectionedSolid
				//		ABSTRACT SUPERTYPE OF(
				//			IfcSectionedSolidHorizontal)
				//		SUBTYPE OF(IfcSolidModel);
				//			Directrix: IfcCurve;
				//			CrossSections: LIST[2:? ] OF IfcProfileDef;
				//		WHERE
				//			DirectrixIs3D : Directrix.Dim = 3;
				//			ConsistentProfileTypes: SIZEOF(QUERY(temp < *CrossSections | CrossSections[1].ProfileType <> temp.ProfileType)) = 0;
				//			SectionsSameType: SIZEOF(QUERY(temp < *CrossSections | TYPEOF(CrossSections[1]) :<> : TYPEOF(temp))) = 0;
				//	END_ENTITY;
				// **************************************************************************************************************************

				if (sectionedSolid.expired())
					throw oip::ReferenceExpiredException(sectionedSolid);

				// (1/1) IfcSectionedSolidHorizontal SUBTYPE of IfcSectionedSolid
				if (sectionedSolid.template isOfType<typename IfcEntityTypesT::IfcSectionedSolidHorizontal>())
				{
					convertIfcSectionedSolidHorizontal(sectionedSolid.template as<typename IfcEntityTypesT::IfcSectionedSolidHorizontal>(), 
						pos, itemData);
					return;
				}

				throw oip::UnhandledException(sectionedSolid);
			}
			
			void convertIfcSectionedSolidHorizontal(
				const EXPRESSReference<typename IfcEntityTypesT::IfcSectionedSolidHorizontal>& sectionedSolidHorizontal,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				if (sectionedSolidHorizontal.expired())
					throw oip::ReferenceExpiredException(sectionedSolidHorizontal);

				//Get directrix and cross sections (attributes 1-2).
				const EXPRESSReference<typename IfcEntityTypesT::IfcCurve>& directrix =
					sectionedSolidHorizontal->Directrix;
				std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcProfileDef>> vecCrossSections =
					sectionedSolidHorizontal->CrossSections;

				// Get cross section positions and fixed axis vertical (attributes 3-4).
				const auto& crossSectionPositions = sectionedSolidHorizontal->CrossSectionPositions;

				bool fixedAxisVertical = sectionedSolidHorizontal->FixedAxisVertical;

				//check dimensions and correct attributes sizes
				if (vecCrossSections.size() != crossSectionPositions.size())
				{
					throw oip::InconsistentModellingException(sectionedSolidHorizontal, "CrossSections and CrossSectionsPositions are not equal in size.");
				}

				//Give directrix to Curve converter: for each station 1 Point and 1 Direction
				// the stations at which a point of the tessellation has to be calcuated - to be converted and fill the targetVec
#if defined(OIP_MODULE_EARLYBINDING_IFC4X1) || defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC1)
				std::vector<double> stations = curveConverter->getStationsForTessellationOfIfcAlignmentCurve(
					directrix.template as<typename IfcEntityTypesT::IfcAlignmentCurve>());
#else
				std::vector<double> stations;
#endif
				carve::geom::vector<3> targetPoint3D;
				carve::geom::vector<3> targetDirection3D;
				std::vector<carve::geom::vector<3>> BasisCurvePoints;
				std::vector<carve::geom::vector<3>> BasisPointDirection;

				// attach the curve points
				for (auto& it_station : stations)
				{
					// call the placement converter that handles the geometry and calculates the 3D point along a curve
					placementConverter->convertBoundedCurveDistAlongToPoint3D(
						directrix.as<typename IfcEntityTypesT::IfcBoundedCurve>(), 
						it_station, true, targetPoint3D, targetDirection3D);

					BasisCurvePoints.push_back(targetPoint3D);
					BasisPointDirection.push_back(targetDirection3D);
				}


				std::shared_ptr<carve::input::PolyhedronData> bodyData = std::make_shared<carve::input::PolyhedronData>();
				itemData->closed_polyhedrons.push_back(bodyData);
				//std::vector<carve::geom::vector<3> > innerShapePoints;  //TO DO: find out if i need innerShapePoints for the CrossSections

				int numCurvePoints = BasisCurvePoints.size();
				carve::math::Matrix matrixSweep;

				// Less than two points is a point
				if (numCurvePoints < 2)
				{
					throw oip::InconsistentModellingException(sectionedSolidHorizontal, "Curve should contain atleast 2 points");
				}

				////define Vector to fill with the coordinates of the CrossSections
				std::vector<std::vector<std::vector<carve::geom::vector<2>>>> paths;

				for (int i = 0; i < vecCrossSections.size(); ++i)
				{
					std::shared_ptr<ProfileConverterT<IfcEntityTypesT>> profileConverter = profileCache->getProfileConverter(vecCrossSections[i]);
					const std::vector<std::vector<carve::geom::vector<2>>>& profileCoords = profileConverter->getCoordinates();

					// Save profile coords in paths
					std::vector<std::vector<carve::geom::vector<2>>> profileCoords2D;
					for (const auto& profileLoop : profileCoords)
					{
						profileCoords2D.push_back(profileLoop);
					}
					paths.push_back(profileCoords2D);

				}

				if (paths.size() == 0)
				{
					throw oip::InconsistentModellingException(sectionedSolidHorizontal, "Profile converter could not find coordinates");
				}

				//declare Variables to fill with the information of the Cross Section Positions
				std::vector<carve::geom::vector<3>> offsetFromCurve;
				std::vector<carve::geom::vector<3>> CrossSectionPoints;
				std::vector<carve::geom::vector<3>> directionsOfCurve;

				std::vector<carve::math::Matrix> localPlacementMatrix;
				std::vector<carve::math::Matrix> objectPlacementMatrix;
							
				for (int pos = 0; pos < crossSectionPositions.size(); ++pos)
				{
								
					//1. get offset from curve   
#if defined(OIP_MODULE_EARLYBINDING_IFC4X1) || defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC1)
					carve::geom::vector<3> offset = placementConverter->convertIfcDistanceExpressionOffsets(crossSectionPositions[pos]);
#else
					carve::geom::vector<3> offset = placementConverter->convertIfcPoint(crossSectionPositions[pos]->Location);
#endif
					offsetFromCurve.push_back(offset);

					//2. calculate the position on and the direction of the base curve
					//also apply the relative dist along	
					carve::geom::vector<3> pointOnCurve;
					carve::geom::vector<3> directionOfCurve;

					std::tie(pointOnCurve, directionOfCurve) = 
						placementConverter->calculatePositionOnAndDirectionOfBaseCurve(
							directrix.template as<typename IfcEntityTypesT::IfcBoundedCurve>(),
#if defined(OIP_MODULE_EARLYBINDING_IFC4X1) || defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC1)
							crossSectionPositions[pos],
#else
							crossSectionPositions[pos]->Location.template as<typename IfcEntityTypesT::IfcPointByDistanceExpression>(),
#endif
							0.);

					CrossSectionPoints.push_back(pointOnCurve);
					directionsOfCurve.push_back(directionOfCurve);

					//TO DO:
					//3. get information from FixedAxisVertical 
					if (fixedAxisVertical == true)
					{
						directionsOfCurve[pos].z = 0;
						directionsOfCurve[pos].normalize();
					}		
								
					//4. calculate the rotations
					//the direction of the curve's tangent = directionOfCurve
					//now that localPLacement Matrix is a Vector ----> 1 Matrix for each CrossSectionPosition saved in the Vector localPlacementMatrix
					carve::math::Matrix localm = placementConverter->calculateCurveOrientationMatrix(directionsOfCurve[pos], fixedAxisVertical);
					localPlacementMatrix.push_back(localm);

					// 4. calculate the position
					// the position on the curve = pointOnCurve
					// the offsets = offsetFromCurve
					carve::geom::vector<3> translate = CrossSectionPoints[pos] + localPlacementMatrix[pos] * offsetFromCurve[pos];
					carve::math::Matrix objectPlacementMatrix_pos = convertCurveOrientation(directionsOfCurve[pos], fixedAxisVertical, translate);
					objectPlacementMatrix.push_back(objectPlacementMatrix_pos);
				}
							
				//Declare Variable for the addFace
				int  ppoints = 0;

				//Declare a new vector which will include all points for the Tesselation
				std::vector<carve::geom::vector<3>> points_for_tessellation;
				std::vector<carve::geom::vector<3>> direction_for_tessellation;
				std::vector<std::vector<std::vector<carve::geom::vector<3>>>> paths_for_tessellation;
				int i = 0;
				int j = 0;

				if (BasisCurvePoints[0] == CrossSectionPoints[0])
				{
					++i;
					++j;
				}
				else
				{//iterate BasisCurvePoints[] until it gets to CrossSectionPoints[0]
				//if dist_1 is bigger than dist_2 they are before CrossSectionPoints[0], else they are after that point
					double dist_1 = distance(BasisCurvePoints[0], CrossSectionPoints[0]);
					double dist_2 = distance(BasisCurvePoints[1], CrossSectionPoints[0]);

					while (dist_1 > dist_2)
					{
						dist_1 = distance(BasisCurvePoints[i], CrossSectionPoints[0]);
						dist_2 = distance(BasisCurvePoints[i + 1], CrossSectionPoints[0]);
						++i;
					}
				}
				//The first point for tesselation is where the Profile Starts
				points_for_tessellation.push_back(CrossSectionPoints[0]);
				direction_for_tessellation.push_back(directionsOfCurve[0]);

				//Convert profile information from 2D to 3D
				std::vector<std::vector<carve::geom::vector<2> > >& compositeProfile = paths[0];
				std::vector<std::vector<carve::geom::vector<3> > > TFcompositeprofile;
				for (int w = 0; w < compositeProfile.size(); ++w)
				{
					std::vector<carve::geom::vector<2> >& loop = compositeProfile[w];
					ppoints = loop.size();
					std::vector<carve::geom::vector<3>> Tloop;
					for (int k = 0; k < loop.size(); ++k)
					{
						carve::geom::vector<2>& point = loop[k];

						carve::geom::vector<3> Tpoint = objectPlacementMatrix[0] * (carve::geom::VECTOR(point.x, point.y, 0)); 
						Tloop.push_back(Tpoint);
					}
					TFcompositeprofile.push_back(Tloop);
				}
				//The first profile for tessellation
				paths_for_tessellation.push_back(TFcompositeprofile);

				//now that CrossSectionPoints[0] is reached iterate and fill points_for_tessellation
			    while (j < CrossSectionPoints.size()) 
				{

			      	//if basisCurvePoints[i]==pointsOnCurve[j] ->save the information of pointsOnCurve
					if (BasisCurvePoints[i] == CrossSectionPoints[j])
					{
						//1. save the information of pointsOnCurve in the new vector
						points_for_tessellation.push_back(CrossSectionPoints[j]);
						direction_for_tessellation.push_back(directionsOfCurve[j]); //3D coord carve matrix ausrechnen zum multiplizieren

						//2. Save CrossSections
						std::vector<std::vector<carve::geom::vector<2> > >& compositeProfile = paths[j];
						std::vector<std::vector<carve::geom::vector<3> > > Tcompositeprofile;
						for (int w = 0; w < compositeProfile.size(); ++w)
						{
							std::vector<carve::geom::vector<2> >& loop = compositeProfile[w];
							std::vector<carve::geom::vector<3>> Tloop;
							for (int k = 0; k < loop.size(); ++k)
							{
								carve::geom::vector<2>& point = loop[k];

								carve::geom::vector<3>  Tpoint = objectPlacementMatrix[j] * (carve::geom::VECTOR(point.x, point.y, 0));
								Tloop.push_back(Tpoint);
							}
							Tcompositeprofile.push_back(Tloop);
						}
									
						paths_for_tessellation.push_back(Tcompositeprofile);
									
						//4. go to the next element in both lists
						++i;
						++j;
					}

					//if basisCurvePoints[i]!=pointsOnCurve[j] alternate depending on distance
					else if (BasisCurvePoints[i] != CrossSectionPoints[j])
					{
						// get the distance of the points 
						double distCrossSectionPositions;
						double distBasisCurvePoints;
									
						//calculate the distance from the point in basisCurvePoints to the last element in the joint list
						int last = points_for_tessellation.size() - 1;

						distCrossSectionPositions = distance(points_for_tessellation[last], CrossSectionPoints[j]);
						distBasisCurvePoints = distance(points_for_tessellation[last], BasisCurvePoints[i]);

						if (distCrossSectionPositions < distBasisCurvePoints)
						{
							//1. Save the point and direction in new vector
							points_for_tessellation.push_back(CrossSectionPoints[j]);
							direction_for_tessellation.push_back(directionsOfCurve[j]);

							//2. Save CrossSections
							std::vector<std::vector<carve::geom::vector<2> > >& compositeProfile = paths[j];
							std::vector<std::vector<carve::geom::vector<3> > > Tcompositeprofile;
							for (int w = 0; w < compositeProfile.size(); ++w)
							{
								std::vector<carve::geom::vector<2> >& loop = compositeProfile[w];
								std::vector<carve::geom::vector<3>> Tloop;
								for (int k = 0; k < loop.size(); ++k)
								{
									carve::geom::vector<2>& point = loop[k];
			
									carve::geom::vector<3>  Tpoint = objectPlacementMatrix[j] * (carve::geom::VECTOR(point.x, point.y, 0));
									Tloop.push_back(Tpoint);
								}
								Tcompositeprofile.push_back(Tloop);
							}
										
							paths_for_tessellation.push_back(Tcompositeprofile);


							//3. increment based on its position on the directrix
							++j;
						}
									
						else if (distCrossSectionPositions > distBasisCurvePoints)
						{
							//Save the point in the curve in the new vector
							points_for_tessellation.push_back(BasisCurvePoints[i]);
							direction_for_tessellation.push_back(BasisPointDirection[i]);

							//calculate the direction of the point (Interpolate with the pointOnCurve before and after that point)
							int directionSize = direction_for_tessellation.size()-1;
							int lastPoint = points_for_tessellation.size() -1;

							double totalDistance = distance(CrossSectionPoints[j - 1], CrossSectionPoints[j]);
							double factorBefore = (distance(CrossSectionPoints[j - 1], BasisCurvePoints[i]))/totalDistance;
							double factorAfter = (distance(BasisCurvePoints[i], CrossSectionPoints[j]))/totalDistance;

							//1. interpolate OffsetsFromCurve
							carve::geom::vector<3> IoffsetFromCurve = offsetFromCurve[j - 1] * factorAfter + offsetFromCurve[j] * factorBefore;

							//Calculate Matrices
							//2. local_placement
							carve::math::Matrix localm = placementConverter->calculateCurveOrientationMatrix(BasisPointDirection[i], fixedAxisVertical);

							// 3. calculate the position
							// the position on the curve = pointOnCurve
							// the offsets = offsetFromCurve
							carve::geom::vector<3> translate = BasisCurvePoints[i] + localm * IoffsetFromCurve;
							carve::math::Matrix objectPlacementMatrix_pos = convertCurveOrientation(BasisPointDirection[i], fixedAxisVertical, translate);
									

							//interpolate profile
							// Informal proposition: for the Interpolation to work the Profiles of the CrossSection before and afer need to have the same amount of points and loops.
									
							std::vector<std::vector<carve::geom::vector<2> > >& compositeProfileBefore = paths[j - 1];
							std::vector<std::vector<carve::geom::vector<2> > >& compositeProfileAfter = paths[j];

							std::vector<std::vector<carve::geom::vector<3> > > Tcompositeprofile;
							for (int w = 0; w < compositeProfileBefore.size(); ++w)
							{
								std::vector<carve::geom::vector<2> >& loopBefore = compositeProfileBefore[w];
								std::vector<carve::geom::vector<2> >& loopAfter = compositeProfileAfter[w];

								std::vector<carve::geom::vector<3>> Tloop;
								for (int k = 0; k < loopBefore.size(); ++k)
								{
									carve::geom::vector<2>& pointBefore = loopBefore[k];
									carve::geom::vector<2>& pointAfter = loopAfter[k];
												
									carve::geom::vector<2> deltapoint = carve::geom::VECTOR(pointAfter.x - pointBefore.x, pointAfter.y - pointBefore.y);
									carve::geom::vector<2> Tpoint2D = carve::geom::VECTOR(deltapoint.x * factorBefore + pointBefore.x, deltapoint.y * factorBefore + pointBefore.y);
												
									carve::geom::vector<3> Tpoint = objectPlacementMatrix_pos *(carve::geom::VECTOR(Tpoint2D.x, Tpoint2D.y, 0));
									Tloop.push_back(Tpoint);
								}
								Tcompositeprofile.push_back(Tloop);
							}
										
							paths_for_tessellation.push_back(Tcompositeprofile);
										
							//increment based on its position on the directrix
							++i;
						}
					}
				}

                // Add Vertex, each point is a vertex. for each paths_for_tesselation
				//paths_for_tesselation.size() == points_for_tessellation.size()
							
				for (i = 0; i < paths_for_tessellation.size(); ++i)
				{
					std::vector<std::vector<carve::geom::vector<3> > >& compositeProfile = paths_for_tessellation[i];
					for (int w = 0; w < compositeProfile.size(); ++w)
					{
						std::vector<carve::geom::vector<3> >& loop = compositeProfile[w];
						for (int k = 0; k < loop.size(); ++k)
						{
							carve::geom::vector<3>& point = loop[k];
							bodyData->addVertex(pos*point);
						}
					}
				}

				// Add Faces Step1: calculate the Profile along the directrix and add each face of the outer profile
				// Step2: close the Profile front and back

				//1. Add Faces between Cross Sections to create a body along the Directrix
				//size of Tloop has to be the same for every Profile
				size_t num_vertices = bodyData->getVertexCount();
				int PFTS = paths_for_tessellation.size() -1;
				for (int i = 0; i < PFTS ; ++i)
				{
					for (int j = 0; j < ppoints - 1; ++j)
					{
						bodyData->addFace(i*ppoints + j, i*ppoints + j + 1, (i + 1)*ppoints + j);
						bodyData->addFace(i*ppoints + j + 1, (i + 1)*ppoints + j, (i + 1)*ppoints + j + 1);
					}
				}
						
						
				//close the first positions of the body
				bodyData->addFace(0, ppoints - 1, ppoints);

				//close the body
				int closingBodyVertices = num_vertices / ppoints;
				for (int ii = 1; ii < closingBodyVertices - 1; ++ii)
				{
					bodyData->addFace(ii*ppoints, ii*ppoints - 1, (ii+1)*ppoints - 1);
					bodyData->addFace((ii + 1)*ppoints, ii*ppoints, (ii + 1)*ppoints - 1);
				}
					
				// close front cap
				for (int jj = 0; jj < ppoints - 2; ++jj)
				{
					bodyData->addFace(0, jj + 1, jj + 2);
				}

				// close back cap
				int BackCapVertex = num_vertices - ppoints;
				for (int jj = BackCapVertex; jj < num_vertices ; ++jj)
				{
					int last = num_vertices - 1;
					bodyData->addFace(last, jj - 1, jj - 2);
				}
	
			}//endif sectionedSolidHorizontal

			carve::math::Matrix multiplyMatrixWithFactor(const carve::math::Matrix &A, const double &factor)
			{
				return carve::math::Matrix(A._11 * factor, A._12 * factor, A._13 * factor, A._14 * factor,
					A._21 * factor, A._22 * factor, A._23 * factor, A._24 * factor,
					A._31 * factor, A._32 * factor, A._33 * factor, A._34 * factor,
					A._41 * factor, A._42 * factor, A._43 * factor, A._44 * factor);
			}

			carve::math::Matrix addTwoMatrices(const carve::math::Matrix &A, const carve::math::Matrix &B)
			{
				return carve::math::Matrix(A._11 + B._11, A._12 + B._12, A._13 + B._13, A._14 + B._14,
					A._21 + B._21, A._22 + B._22, A._23 + B._23, A._24 + B._24,
					A._31 + B._31, A._32 + B._32, A._33 + B._33, A._34 + B._34,
					A._41 + B._41, A._42 + B._42, A._43 + B._43, A._43 + B._44);
			}

			//TO DO: it has to work for ssh
			carve::math::Matrix convertCurveOrientation(
				const carve::geom::vector<3> directionOfCurve,
				const bool fixedAxisVertical,
				const carve::geom::vector<3> translate = carve::geom::VECTOR(0., 0., 0.)
			) const noexcept(false)
			{

				carve::geom::vector<3> local_z(carve::geom::VECTOR(directionOfCurve.x, directionOfCurve.y, fixedAxisVertical ? 0.0 : directionOfCurve.z));

				// get the perpendicular to the left of the curve in the z-y plane (curve's coordinate system)
				carve::geom::vector<3> local_y(carve::geom::VECTOR(-local_z.y, local_z.x, 0.0)); // always lies in the z-y plane(Curve (and x-y 2D-Profile)

				// get the vertical as cross product
				carve::geom::vector<3> local_x = carve::geom::cross(local_z, local_y);

				// normalize the direction vectors
				local_x.normalize();
				local_y.normalize();
				local_z.normalize();

				// produce a rotation matrix
				return carve::math::Matrix(
					local_x.x, local_y.x, local_z.x, translate.x,
					local_x.y, local_y.y, local_z.y, translate.y,
					local_x.z, local_y.z, local_z.z, translate.z,
					0, 0, 0, 1);
			}

			/*! \brief Converts \c IfcSweptAreaSolid to meshes.
			 *
			 * \param[in] sweptAreaSolid			The \c IfcSweptAreaSolid to be converted.
			 * \param[in] pos						The relative location of the origin of the representation's coordinate system within the geometric context.
			 * \param[out] itemData					A pointer to be filled with the relevant data.
			 *
			 * \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricmodelresource/lexical/ifcsweptareasolid.htm
			*/
			void convertIfcSweptAreaSolid(EXPRESSReference<typename IfcEntityTypesT::IfcSweptAreaSolid> sweptAreaSolid, 
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				if (sweptAreaSolid.expired())
					throw oip::ReferenceExpiredException(sweptAreaSolid);

				// Get swept area and position (attributes 1-2). 
				oip::EXPRESSReference<typename IfcEntityTypesT::IfcProfileDef> sweptArea = sweptAreaSolid->SweptArea;
				// swept area
				std::shared_ptr<ProfileConverterT<IfcEntityTypesT>> profile_converter = profileCache->getProfileConverter(sweptArea);
				const std::vector<std::vector<carve::geom::vector<2> > >& profile_coords = profile_converter->getCoordinates();

				carve::math::Matrix sweptAreaPos(pos);	// check if local coordinate system is specified for extrusion
				if (sweptAreaSolid->Position)
				{
					EXPRESSReference<typename IfcEntityTypesT::IfcAxis2Placement3D> sweptAreaPosition = sweptAreaSolid->Position;

					sweptAreaPos = pos * placementConverter->convertIfcAxis2Placement3D(sweptAreaPosition);
				}

				
				// IfcFixedReferenceSweptAreaSolid SUBTYPE of IfcSweptAreaSolid
				if (sweptAreaSolid.template isOfType<IfcEntityTypesT::IfcFixedReferenceSweptAreaSolid>()) 
				{
					convertIfcFixedReferenceSweptAreaSolid(
						sweptAreaSolid.template as<IfcEntityTypesT::IfcFixedReferenceSweptAreaSolid>(),
						profile_coords, sweptAreaPos, itemData);
					return;
				}
				

				// IfcSurfaceCurveSweptAreaSolid SUBTYPE of IfcSweptAreaSolid
				if (sweptAreaSolid.template isOfType<typename IfcEntityTypesT::IfcSurfaceCurveSweptAreaSolid>())
				{
					convertIfcSurfaceCurveSweptAreaSolid(
						sweptAreaSolid.template as<typename IfcEntityTypesT::IfcSurfaceCurveSweptAreaSolid>(),
						sweptAreaPos, itemData, sweptArea);
					return;
				}

				// IfcExtrudedAreaSolid SUBTYPE of IfcSweptAreaSolid
				if (sweptAreaSolid.template isOfType<typename IfcEntityTypesT::IfcExtrudedAreaSolid>())
				{
					convertIfcExtrudedAreaSolid(sweptAreaSolid.template as<typename IfcEntityTypesT::IfcExtrudedAreaSolid>(),
						sweptAreaPos, itemData);
					return;
					// TO DO: implement
				}

				// IfcRevolvedAreaSolid SUBTYPE of IfcSweptAreaSolid
				if (sweptAreaSolid.template isOfType<typename IfcEntityTypesT::IfcRevolvedAreaSolid>())
				{
					convertIfcRevolvedAreaSolid(sweptAreaSolid.template as<typename IfcEntityTypesT::IfcRevolvedAreaSolid>(), 
						sweptAreaPos, itemData);
					return;
					// TO DO: implement//
				}

				throw oip::UnhandledException(sweptAreaSolid);
			}

			void convertIfcFixedReferenceSweptAreaSolid(
				const EXPRESSReference<typename IfcEntityTypesT::IfcFixedReferenceSweptAreaSolid>& fixedRefSweptAreaSolid,
				const std::vector<std::vector<carve::geom::vector<2> > >& profile_coords,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				

				// Get directrix, start parameter, end parameter and fixed reference (attributes 3-6).
				std::vector<carve::geom::vector<3> > segment_start_points;
				std::vector<carve::geom::vector<3> > basis_curve_points;
				curveConverter->convertIfcCurve(
					fixedRefSweptAreaSolid->Directrix, basis_curve_points, segment_start_points);

				//double start_param = fixedRefSweptAreaSolid->StartParam.value_or(0.0);	// TO DO: optional
				//double end_param = fixedRefSweptAreaSolid->EndParam.value_or(1.0);		// TO DO: optional

				carve::geom::vector<3> fixedRef = placementConverter->convertIfcDirection(
					fixedRefSweptAreaSolid->FixedReference);

				std::shared_ptr<carve::input::PolyhedronData> polyhedron_data(new carve::input::PolyhedronData());
				itemData->closed_polyhedrons.push_back(polyhedron_data);

				// create vertices
				size_t num_segments = basis_curve_points.size();
				for (size_t i = 0; i < num_segments; ++i)
				{
					size_t
						prev = (i == 0 ? 0 : i - 1),
						next = std::min<size_t>(i + 1, num_segments - 1);

					carve::geom::vector<3> tangent = basis_curve_points[next] - basis_curve_points[prev];

					carve::geom::vector<3> local_z = tangent;
					carve::geom::vector<3> local_y = carve::geom::cross(local_z, fixedRef);
					carve::geom::vector<3> local_x = carve::geom::cross(local_y, local_z);

					local_x.normalize();
					local_y.normalize();
					local_z.normalize();

					carve::math::Matrix profileLocalPos(
						local_x.x, local_y.x, local_z.x, basis_curve_points[i].x,
						local_x.y, local_y.y, local_z.y, basis_curve_points[i].y,
						local_x.z, local_y.z, local_z.z, basis_curve_points[i].z,
						0., 0., 0., 1.);

					for (const std::vector<carve::geom::vector<2> >& loop : profile_coords)
					{
						for (const carve::geom::vector<2>& point : loop)
						{
							polyhedron_data->addVertex(pos * profileLocalPos * carve::geom::VECTOR(point.x, point.y, 0.));
						}
					}
				}

				// front cap
				std::vector<int> front_face_loop;
				int num_polygon_points = 0;
				for (int j = 0; j < profile_coords.size(); ++j)
				{
					const std::vector<carve::geom::vector<2> >& loop = profile_coords[j];

					for (int k = 0; k < loop.size(); ++k)
					{
						front_face_loop.push_back(j*loop.size() + k);
						++num_polygon_points;
					}
				}
				polyhedron_data->addFace(front_face_loop.rbegin(), front_face_loop.rend());

				// end cap
				std::vector<int> end_face_loop;
				const int end_face_begin = (num_segments - 1) * num_polygon_points;
				for (int j = 0; j < num_polygon_points; ++j)
				{
					end_face_loop.push_back(end_face_begin + j);
				}
				polyhedron_data->addFace(end_face_loop.begin(), end_face_loop.end());

				// faces of revolved shape
				for (int i = 0; i < num_polygon_points - 1; ++i)
				{
					int i_offset_next = i + num_polygon_points;
					for (int j = 0; j < num_segments - 1; ++j)
					{
						int j_offset = j * num_polygon_points;
						polyhedron_data->addFace(j_offset + i, j_offset + i + 1, j_offset + 1 + i_offset_next, j_offset + i_offset_next);
					}
				}

				for (int j = 0; j < num_segments - 1; ++j)
				{
					int j_offset = j * num_polygon_points;
					polyhedron_data->addFace(j_offset + num_polygon_points - 1, j_offset, j_offset + num_polygon_points, j_offset + num_polygon_points + num_polygon_points - 1);
				}

				return;
			}

			void convertIfcSurfaceCurveSweptAreaSolid(
				EXPRESSReference<typename IfcEntityTypesT::IfcSurfaceCurveSweptAreaSolid> surfaceCurveSweptAreaSolid,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData,
				oip::EXPRESSReference<typename IfcEntityTypesT::IfcProfileDef> sweptArea
			) const noexcept(false)
			{
				throw oip::UnhandledException(surfaceCurveSweptAreaSolid);
				// TO DO: implement / check current implementation //
				/*
				// Get directrix, start parameter, end paramter and reference surface (attributes 3-6).
				oip::EXPRESSReference<typename IfcEntityTypesT::IfcCurve> directrix =
					surfaceCurveSweptAreaSolid->Directrix;	// TO DO: formal proposition: if no StartParam or EndParam, Directrix has to be a bounded or closed curve. 
				//double startParam = surfaceCurveSweptAreaSolid->StartParam;	// TO DO: optional
				//double endParam = surfaceCurveSweptAreaSolid->EndParam;		// TO DO: optional
				oip::EXPRESSReference<typename IfcEntityTypesT::IfcSurface> ref_surface =
					surfaceCurveSweptAreaSolid->ReferenceSurface;	// TO DO: next level


#ifdef _DEBUG
				std::cout << "Warning\t| IfcSurfaceCurveSweptAreaSolid not implemented" << std::endl;
#endif

				std::shared_ptr<ProfileConverterT<IfcEntityTypesT>> profileConverter = profileCache->getProfileConverter(sweptArea);
				const std::vector<std::vector<carve::geom::vector<2>>>& paths = profileConverter->getCoordinates();
				std::shared_ptr<carve::input::PolyhedronData> poly_data(new carve::input::PolyhedronData);

				oip::EXPRESSReference<typename IfcEntityTypesT::IfcCurve>& directrixCurve = surfaceCurveSweptAreaSolid->Directrix;

				std::vector<carve::geom::vector<3> > segmentStartPoints;
				std::vector<carve::geom::vector<3> > basisCurvePoints;
				curveConverter->convertIfcCurve(directrixCurve, basisCurvePoints, segmentStartPoints);

				std::shared_ptr<carve::input::PolylineSetData> polyline_data =
					faceConverter->convertIfcSurface(surfaceCurveSweptAreaSolid->ReferenceSurface, pos);
				*/
			}

			/*! \brief Converts \c IfcExtrudedAreaSolid to meshes.
			 *
			 * \param[in] extrudedArea				The \c IfcExtrudedAreaSolid to be converted.
			 * \param[in] pos						The relative location of the origin of the representation's coordinate system within the geometric context.
			 * \param[out] itemData					A pointer to be filled with the relevant data.
			 *
			 * \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricmodelresource/lexical/ifcextrudedareasolid.htm
			*/
			void convertIfcExtrudedAreaSolid(
				const oip::EXPRESSReference<typename IfcEntityTypesT::IfcExtrudedAreaSolid>& extrudedArea,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				// **************************************************************************************************************************
				//	ENTITY IfcExtrudedAreaSolid
				//		SUPERTYPE OF(IfcExtrudedAreaSolidTapered)
				//		SUBTYPE OF(IfcSweptAreaSolid);
				//		ExtrudedDirection: IfcDirection;
				//		Depth: IfcPositiveLengthMeasure;
				//		WHERE
				//			ValidExtrusionDirection : IfcDotProduct(IfcRepresentationItem() || IfcGeometricRepresentationItem() || IfcDirection([0.0, 0.0, 1.0]), SELF.ExtrudedDirection) < > 0.0;
				//	END_ENTITY;
				// **************************************************************************************************************************

				if (extrudedArea.expired())
					throw oip::ReferenceExpiredException(extrudedArea);

				if (!extrudedArea->ExtrudedDirection)
				{
					throw oip::InconsistentModellingException(extrudedArea, "Invalid ExtrudedDirection!");
				}

				if (!extrudedArea->Depth)
				{
					throw oip::InconsistentModellingException(extrudedArea, "Invalid Depth!");
				}

				// direction and length of extrusion
				carve::geom::vector<3> extrusionVector = placementConverter->convertIfcDirection(extrudedArea->ExtrudedDirection) 
					* extrudedArea->Depth * this->UnitConvert()->getLengthInMeterFactor();

				// swept area
				oip::EXPRESSReference<typename IfcEntityTypesT::IfcProfileDef> sweptArea = extrudedArea->SweptArea;

				std::shared_ptr<ProfileConverterT<IfcEntityTypesT>> profileConverter =
					profileCache->getProfileConverter(sweptArea);
				profileConverter->simplifyPaths();

				const std::vector<std::vector<carve::geom::vector<2>>>& paths = profileConverter->getCoordinates();

				if (paths.size() == 0)
				{
					throw oip::InconsistentGeometryException(extrudedArea, "Paths are empty!");
				}

				// .AREA. vs .CURVE. (is the result closed or open, i.e. full solid vs pipe)
				bool closed = true;
				switch (sweptArea->ProfileType)
				{
				case IfcEntityTypesT::IfcProfileTypeEnum::ENUM::ENUM_AREA:
					closed = true;
					break;
				case IfcEntityTypesT::IfcProfileTypeEnum::ENUM::ENUM_CURVE:
					closed = false;
					break;
				default:
					throw oip::InconsistentModellingException(extrudedArea->SweptArea, "Unknown ProfileTypeEnum.");
				}

				std::shared_ptr<carve::input::PolyhedronData> poly_data(new carve::input::PolyhedronData);
				std::stringstream err;
				GeomUtils::extrude(paths, extrusionVector, closed, poly_data);

				// apply object coordinate system
				std::transform(poly_data->points.begin(), poly_data->points.end(), poly_data->points.begin(), 
					[pos](auto vertex) -> decltype(vertex) {return pos * vertex; });

				if( closed )
					itemData->closed_polyhedrons.push_back(poly_data);
				else
					itemData->open_polyhedrons.push_back(poly_data);

			}//end convertIfcExtrudedAreaSolid()

			/*! \brief Converts \c IfcRevolvedAreaSolid to meshes.
			 *
			 * \param[in] revolvedArea				The \c IfcRevolvedAreaSolid to be converted.
			 * \param[in] pos						The relative location of the origin of the representation's coordinate system within the geometric context.
			 * \param[out] itemData					A pointer to be filled with the relevant data.
			 *
			 * \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricmodelresource/lexical/ifcrevolvedareasolid.htm
			*/
			void convertIfcRevolvedAreaSolid(
				const oip::EXPRESSReference<typename IfcEntityTypesT::IfcRevolvedAreaSolid>& revolvedArea,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				// **************************************************************************************************************************
				//	ENTITY IfcRevolvedAreaSolid
				//		SUPERTYPE OF(IfcRevolvedAreaSolidTapered)
				//		SUBTYPE OF(IfcSweptAreaSolid);
				//			Axis: IfcAxis1Placement;
				//			Angle: IfcPlaneAngleMeasure;
				//		DERIVE
				//			AxisLine : IfcLine: = IfcRepresentationItem() || IfcGeometricRepresentationItem() || IfcCurve() || IfcLine(Axis.Location, IfcRepresentationItem() || IfcGeometricRepresentationItem() || IfcVector(Axis.Z, 1.0));
				//		WHERE
				//			AxisStartInXY : Axis.Location.Coordinates[3] = 0.0;
				//			AxisDirectionInXY: Axis.Z.DirectionRatios[3] = 0.0;
				//	END_ENTITY;
				// **************************************************************************************************************************

				if (revolvedArea.expired())
					throw oip::ReferenceExpiredException(revolvedArea);

				// Get axis and angle (attributes 3-4). 
				oip::EXPRESSReference<typename IfcEntityTypesT::IfcAxis1Placement> axis = revolvedArea->Axis;

				// angle and axis
			
				oip::EXPRESSReference<typename IfcEntityTypesT::IfcProfileDef> sweptAreaProfile = revolvedArea->SweptArea;
				double revolutionAngle = revolvedArea->Angle * this->UnitConvert()->getAngleInRadianFactor();
			
				carve::geom::vector<3>  axisLocation;
				carve::geom::vector<3>  axisDirection;

				if (revolvedArea->Axis)
				{
					oip::EXPRESSReference<typename IfcEntityTypesT::IfcAxis1Placement> axisPlacement = revolvedArea->Axis;


					if (axisPlacement->Location)
						axisLocation = placementConverter->convertIfcPoint(axisPlacement->Location);

					if (axisPlacement->Axis)
						axisDirection = placementConverter->convertIfcDirection(axisPlacement->Axis);
				}

				// rotation base point is the one with the smallest distance on the rotation axis
				carve::geom::vector<3>  origin;
				carve::geom::vector<3>  basePoint;
				GeomUtils::closestPointOnLine(origin, axisLocation, axisDirection, basePoint);
				basePoint *= -1;

				// swept area
				std::shared_ptr<ProfileConverterT<IfcEntityTypesT>> profileConverter = profileCache->getProfileConverter(sweptAreaProfile);
				const std::vector<std::vector<carve::geom::vector<2>>>& profileCoords = profileConverter->getCoordinates();

				// tesselate
				std::vector<std::vector<carve::geom::vector<2>>> profileCoords2D = profileCoords;
				std::vector<carve::geom::vector<2>> merged;
				std::vector<carve::triangulate::tri_idx> triangulated;

				try //TODO> Decide, if it is necessary here to have try ... catch (...).
				{
					std::vector<std::pair<size_t, size_t>> result = carve::triangulate::incorporateHolesIntoPolygon(profileCoords2D); // first is loop index, second is vertex index in loop
					merged.resize(result.size());
					for (size_t i = 0; i < result.size(); ++i)
					{
						int loopNumber = result[i].first;
						int indexInLoop = result[i].second;

						if (loopNumber >= profileCoords2D.size())
						{
							std::cout << ": loopNumber >= face_loops_projected.size()" << std::endl;
							continue;
						}

						std::vector<carve::geom2d::P2>& loopProjected = profileCoords2D[loopNumber];

						carve::geom2d::P2& pointProjected = loopProjected[indexInLoop];
						merged.push_back(pointProjected);
					}
					carve::triangulate::triangulate(merged, triangulated);
					carve::triangulate::improve(merged, triangulated);
				}
				catch (...)
				{
					throw oip::InconsistentGeometryException(revolvedArea, "carve::triangulate::incorporateHolesIntoPolygon failed");
				}

				if (profileCoords.size() == 0)
				{
					throw oip::InconsistentModellingException(revolvedArea, "profileCoords are empty!");
				}
				if (profileCoords[0].size() < 3)
				{
					throw oip::InconsistentModellingException(revolvedArea, "Not enough coordinates!");
				}

				// determine the biggest distance to rotational axis -> biggest radius that needs to be tesselated
				double biggestRadius = 0.;
				for (int i = 0; i < profileCoords.size(); ++i)
				{
					const std::vector<carve::geom::vector<2>>& profileLoop = profileCoords[i];
					for (int j = 0; j < profileLoop.size(); ++j)
					{
						const carve::geom::vector<2>& point2d = profileLoop.at(j);
						carve::geom::vector<3>  point(carve::geom::VECTOR(point2d.x, point2d.y, 0.));
						carve::geom::vector<3>  pointOnLine;
						GeomUtils::closestPointOnLine(point, axisLocation, axisDirection, pointOnLine);
						biggestRadius = std::max(biggestRadius, (pointOnLine - point).length());
					}
				}

				if (revolutionAngle > M_PI * 2.) revolutionAngle = M_PI * 2.;
				if (revolutionAngle < -M_PI * 2.) revolutionAngle = M_PI * 2.;

				int numOfSegments = this->GeomSettings()->getNumberOfSegmentsForTessellation(biggestRadius, abs(revolutionAngle));
				if (numOfSegments < 6)
				{
					numOfSegments = 6;
				}
				double angle = 0.0;
				double deltaAngle = revolutionAngle / (double)numOfSegments;

				// check if we have to change the direction
				carve::geom::vector<3>  polygonNormal = GeomUtils::computePolygon2DNormal(profileCoords[0]);
				const carve::geom::vector<2>&  Opoint2D = profileCoords[0][0];
				carve::geom::vector<3>  Opoint3D(carve::geom::VECTOR(Opoint2D.x, Opoint2D.y, 0));
				carve::geom::vector<3>  point0 = carve::math::Matrix::ROT(deltaAngle, axisDirection)*(Opoint3D + basePoint);
				if (polygonNormal.z*point0.z > 0)
				{
					angle = revolutionAngle;
					deltaAngle = -deltaAngle;
				}

				std::shared_ptr<carve::input::PolyhedronData> polyhedronData(new carve::input::PolyhedronData());
				itemData->closed_polyhedrons.push_back(polyhedronData);

				// create vertices
				carve::math::Matrix martix;
				for (int i = 0; i <= numOfSegments; ++i)
				{
					martix = carve::math::Matrix::ROT(angle, -axisDirection);
					for (int j = 0; j < profileCoords.size(); ++j)
					{
						const std::vector<carve::geom::vector<2>>& loop = profileCoords[j];

						for (int k = 0; k < loop.size(); ++k)
						{
							const carve::geom::vector<2>& point = loop[k];

							carve::geom::vector<3>  vertex = martix * (carve::geom::VECTOR(point.x, point.y, 0) + basePoint) - basePoint;
							polyhedronData->addVertex(pos*vertex);
						}
					}
					angle += deltaAngle;
				}

				// front cap
				std::vector<int> frontFaceLoop;
				int numPolygonPoints = 0;
				for (int j = 0; j < profileCoords.size(); ++j)
				{
					const std::vector<carve::geom::vector<2>>& loop = profileCoords[j];

					for (int k = 0; k < loop.size(); ++k)
					{
						frontFaceLoop.push_back(j*loop.size() + k);
						++numPolygonPoints;
					}
				}
				// TODO: use triangulated
				polyhedronData->addFace(frontFaceLoop.rbegin(), frontFaceLoop.rend());

				// end cap
				std::vector<int> end_face_loop;
				const int end_face_begin = numOfSegments * numPolygonPoints;
				for (int j = 0; j < numPolygonPoints; ++j)
				{
					end_face_loop.push_back(end_face_begin + j);
				}
				polyhedronData->addFace(end_face_loop.begin(), end_face_loop.end());

				// faces of revolved shape
				for (int i = 0; i < numPolygonPoints - 1; ++i)
				{
					int i_offsetNext = i + numPolygonPoints;
					for (int j = 0; j < numOfSegments; ++j)
					{
						int j_offset = j * numPolygonPoints;
						polyhedronData->addFace(j_offset + i,
							j_offset + i + 1, j_offset + 1 + i_offsetNext,
							j_offset + i_offsetNext);
					}
				}

				for (int j = 0; j < numOfSegments; ++j)
				{
					int j_offset = j * numPolygonPoints;
					polyhedronData->addFace(j_offset + numPolygonPoints - 1,
						j_offset, j_offset + numPolygonPoints,
						j_offset + numPolygonPoints + numPolygonPoints - 1);
				}
			}



			/*! \brief Converts \c IfcSweptDiskSolid to meshes.
			 *
			 * \param[in] sweptDiskSolid			The \c IfcSweptDiskSolid to be converted.
			 * \param[in] pos						The relative location of the origin of the representation's coordinate system within the geometric context.
			 * \param[out] itemData					A pointer to be filled with the relevant data.
			 *
			 * \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricmodelresource/lexical/ifcsweptdisksolid.htm
			*/
			void convertIfcSweptDiskSolid(
				const oip::EXPRESSReference<typename IfcEntityTypesT::IfcSweptDiskSolid>& sweptDiskSolid,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				// **************************************************************************************************************************
				//	ENTITY IfcSweptDiskSolid
				//		SUPERTYPE OF(IfcSweptDiskSolidPolygonal)
				//		SUBTYPE OF(IfcSolidModel);
				//			Directrix: IfcCurve;
				//			Radius: IfcPositiveLengthMeasure;
				//			InnerRadius: OPTIONAL IfcPositiveLengthMeasure;
				//			StartParam: OPTIONAL IfcParameterValue;
				//			EndParam: OPTIONAL IfcParameterValue;
				//		WHERE
				//			DirectrixDim : Directrix.Dim = 3;
				//			InnerRadiusSize: (NOT EXISTS(InnerRadius)) OR(Radius > InnerRadius);
				//			DirectrixBounded: (EXISTS(StartParam) AND EXISTS(EndParam)) OR
				//		(SIZEOF(['IFCGEOMETRYRESOURCE.IfcConic', 'IFCGEOMETRYRESOURCE.IfcBoundedCurve'] * TYPEOF(Directrix)) = 1);
				//	END_ENTITY;
				// **************************************************************************************************************************

				if (sweptDiskSolid.expired())
					throw oip::ReferenceExpiredException(sweptDiskSolid);

				// Get directrix, radius, inner radius, start parameter and end parameter (attributes 1-5). 
				oip::EXPRESSReference<typename IfcEntityTypesT::IfcCurve> directrixCurve = sweptDiskSolid->Directrix;

				double radius = sweptDiskSolid->Radius * this->UnitConvert()->getLengthInMeterFactor();

				double radiusInner = sweptDiskSolid->InnerRadius.value_or(0.0);
				double startParam = sweptDiskSolid->StartParam.value_or(0.0);
				double endParam = sweptDiskSolid->EndParam.value_or(1.0);

				// TODO: handle inner radius, start param, end param and check for formal propositions!

				// IfcSweptDiskSolidPolygonal SUBTYPE of IfcSweptDiskSolid
				if (sweptDiskSolid.template isOfType<typename IfcEntityTypesT::IfcSweptDiskSolidPolygonal>())
				{
					//TODO: implement and check for formal propositions.
					convertIfcSweptDiskSolidPolygonal(sweptDiskSolid.template as<typename IfcEntityTypesT::IfcSweptDiskSolidPolygonal>(),
						pos, itemData);
					
					return;
				} //endif IfcSweptDiskSolidPolygonal

				// TO DO: understand what happens here
				std::vector<carve::geom::vector<3>> segmentStartPoints;
				std::vector<carve::geom::vector<3>> basisCurvePoints;
				curveConverter->convertIfcCurve(directrixCurve, basisCurvePoints, segmentStartPoints);

				std::shared_ptr<carve::input::PolyhedronData> pipeData(new carve::input::PolyhedronData());
				itemData->closed_polyhedrons.push_back(pipeData);
				std::vector<carve::geom::vector<3>> outerShapePoints;
				std::vector<carve::geom::vector<3>> innerShapePoints;

				const int numberOfVertices = this->GeomSettings()->getNumberOfVerticesForTessellation(radius);
				double deltaAngle = this->GeomSettings()->getAngleLength(radius);

				std::vector<carve::geom::vector<3>> circlePoints;
				std::vector<carve::geom::vector<3>> circlePointsInner;
				int i; double angle;
				for (i = 0, angle = 0.;
					i < numberOfVertices;
					++i, angle += deltaAngle)
				{
					// cross section (circle) is defined in YZ plane
					double x = sin(angle);
					double y = cos(angle);
					circlePoints.push_back(carve::geom::VECTOR(0.0, x*radius, y*radius));
					circlePointsInner.push_back(carve::geom::VECTOR(0.0, x*radiusInner, y*radiusInner));
				}

				int numBasePoints = basisCurvePoints.size();
				carve::math::Matrix matrixSweep;

				carve::geom::vector<3> local_z(carve::geom::VECTOR(0, 0, 1));

				if (basisCurvePoints.size() < 2)
				{
					throw oip::InconsistentModellingException("IfcSweptDiskSolid: num curve points < 2");
				}

				bool bendFound = false;
				if (basisCurvePoints.size() > 3)
				{
					// compute local z vector by dot product of the first bend of the reference line
					carve::geom::vector<3> vertexBack2 = basisCurvePoints.at(0);
					carve::geom::vector<3> vertexBack1 = basisCurvePoints.at(1);
					for (int i = 2; i < basisCurvePoints.size(); ++i)
					{
						carve::geom::vector<3> vertexCurrent = basisCurvePoints.at(i);
						carve::geom::vector<3> section1 = vertexBack1 - vertexBack2;
						carve::geom::vector<3> section2 = vertexCurrent - vertexBack1;
						section1.normalize();
						section2.normalize();

						double dotProduct = dot(section1, section2);
						double dotProduct_abs = abs(dotProduct);

						// if dot == 1 or -1, then points are colinear
						if (dotProduct_abs < (1.0 - 0.0001) || dotProduct_abs >(1.0 + 0.0001))
						{
							// bend found, compute cross product
							carve::geom::vector<3> lateral_vec = cross(section1, section2);
							local_z = cross(lateral_vec, section1);
							local_z.normalize();
							bendFound = true;
							break;
						}
					}
				}

				if (!bendFound)
				{
					// sweeping curve is linear. assume any local z vector
					local_z = carve::geom::VECTOR(0, 0, 1);
					double dot_normal_local_z = dot((basisCurvePoints.at(1) - basisCurvePoints.at(0)), local_z);
					if (this->GeomSettings()->areEqual(abs(dot_normal_local_z), 0.))
					{
						local_z = carve::geom::VECTOR(0, 1, 0);
						local_z.normalize();
					}
				}

				for (int ii = 0; ii < basisCurvePoints.size(); ++ii)
				{
					carve::geom::vector<3> vertexCurrent = basisCurvePoints.at(ii);
					carve::geom::vector<3> vertexNext;
					carve::geom::vector<3> vertexBefore;
					if (ii == 0)
					{
						// first point
						vertexNext = basisCurvePoints.at(ii + 1);
						carve::geom::vector<3> delta_element = vertexNext - vertexCurrent;
						vertexBefore = vertexCurrent - (delta_element);
					}
					else if (ii == basisCurvePoints.size() - 1)
					{
						// last point
						vertexBefore = basisCurvePoints.at(ii - 1);
						carve::geom::vector<3> delta_element = vertexCurrent - vertexBefore;
						vertexNext = vertexBefore + (delta_element);
					}
					else
					{
						// inner point
						vertexNext = basisCurvePoints.at(ii + 1);
						vertexBefore = basisCurvePoints.at(ii - 1);
					}

					carve::geom::vector<3> bisecting_normal;
					GeomUtils::bisectingPlane(vertexBefore, vertexCurrent, vertexNext, bisecting_normal);

					carve::geom::vector<3> section1 = vertexCurrent - vertexBefore;
					carve::geom::vector<3> section2 = vertexNext - vertexCurrent;
					section1.normalize();
					section2.normalize();
					double dotProduct = dot(section1, section2);
					double dotProduct_abs = abs(dotProduct);
					if (!this->GeomSettings()->areEqual(dotProduct_abs, 0.))
					{
						// bend found, compute next local z vector
						carve::geom::vector<3> lateral_vec = cross(section1, section2);
						local_z = cross(lateral_vec, section1);
						local_z.normalize();
					}

					if (ii == basisCurvePoints.size() - 1)
					{
						bisecting_normal *= -1.0;
					}

					matrixSweep = GeomUtils::convertPlane2Matrix(bisecting_normal, vertexCurrent, local_z);
					matrixSweep = pos * matrixSweep;
					GeomUtils::applyPositionToVertex(circlePoints, matrixSweep, numberOfVertices, outerShapePoints);
					
					if (radiusInner > 0)
					{
						GeomUtils::applyPositionToVertex(circlePointsInner, matrixSweep, numberOfVertices, innerShapePoints);
					}
				}

				// Create faces of outer shape.
				for (int jj = 0; jj < numberOfVertices; ++jj) {
					pipeData->addVertex(outerShapePoints.at(jj));
				}

				size_t numVerticesOuter = pipeData->getVertexCount();
				createFacesOfTheShape(basisCurvePoints.size() - 1, numberOfVertices, pipeData);
				
				if (radiusInner > 0)
				{
					if (innerShapePoints.size() != numVerticesOuter)
					{
						throw oip::InconsistentModellingException("IfcSweptDiskSolid: innerShapePoints.size() != numVerticesOuter");
					}

					// add points for inner shape
					for (size_t i = 0; i < innerShapePoints.size(); ++i)
					{
						pipeData->addVertex(innerShapePoints[i]);
					}

					// Create faces of inner shape.
					createFacesOfTheShape(basisCurvePoints.size() - 1, numberOfVertices, pipeData, numVerticesOuter);
					
					// front cap
					for (int jj = 0; jj < numberOfVertices; ++jj)
					{
						int outer_rim_next = (jj + 1) % numberOfVertices;
						int inner_rim_next = outer_rim_next + numVerticesOuter;
						pipeData->addFace(jj, outer_rim_next, numVerticesOuter + jj);
						pipeData->addFace(outer_rim_next, inner_rim_next, numVerticesOuter + jj);
					}

					// back cap
					int back_offset = (basisCurvePoints.size() - 1)*numberOfVertices;
					for (int jj = 0; jj < numberOfVertices; ++jj)
					{
						int outer_rim_next = (jj + 1) % numberOfVertices + back_offset;
						int inner_rim_next = outer_rim_next + numVerticesOuter;
						pipeData->addFace(jj + back_offset, numVerticesOuter + jj + back_offset, outer_rim_next);
						pipeData->addFace(outer_rim_next, numVerticesOuter + jj + back_offset, inner_rim_next);
					}
				}
				else
				{
					// front cap, full pipe, create triangle fan
					for (int jj = 0; jj < numberOfVertices - 2; ++jj)
					{
						pipeData->addFace(0, jj + 1, jj + 2);
					}

					// back cap
					int back_offset = (basisCurvePoints.size() - 1)*numberOfVertices;
					for (int jj = 0; jj < numberOfVertices - 2; ++jj)
					{
						pipeData->addFace(back_offset, back_offset + jj + 2, back_offset + jj + 1);
					}
				}
			}

			/*! \brief creates faces of the shape.
			 *
			 * \param[in] numOffsets				Number of offsets.
			 * \param[in] numberOfVertices			Number of offsets of the inner circle.
			 * \param[out] pipeData					A pointer to be filled with the relevant data.
			 * \param[in] numVerticesOuter			Number of offsets of the outer circle. 
			*/
			void createFacesOfTheShape(const int numOffsets, const int numberOfVertices,
				 std::shared_ptr<carve::input::PolyhedronData>& pipeData, const int numVerticesOuter = 0
			) const noexcept(false)
			{
				for (size_t i = 0; i < numOffsets; ++i)
				{
					int i_offset = i * numberOfVertices + numVerticesOuter;
					int i_offsetNext = (i + 1)*numberOfVertices + numVerticesOuter;
					for (int jj = 0; jj < numberOfVertices; ++jj)
					{
						int currentLoopPoint = jj + i_offset;
						int currentLoopPointNext = (jj + 1) % numberOfVertices + i_offset;

						int nextLoopPoint = jj + i_offsetNext;
						int nextLoopPointNext = (jj + 1) % numberOfVertices + i_offsetNext;
						//pipeData->addFace( currentLoopPoint, nextLoopPoint, nextLoopPointNext, currentLoopPointNext );  
						pipeData->addFace(currentLoopPoint, currentLoopPointNext, nextLoopPointNext, nextLoopPoint);
					}
				}
			}
			

			void convertIfcSweptDiskSolidPolygonal(
				const oip::EXPRESSReference<typename IfcEntityTypesT::IfcSweptDiskSolidPolygonal>& sweptDiskSolidPolygonal,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				throw oip::UnhandledException(sweptDiskSolidPolygonal);
				//Get fillet radius(attribute 6).
				//double fillet_radius = sweptDiskSolid_polygonal->FilletRadius;
			}

			/*! \brief converts \c IfcBooleanResult to meshes.
			 *
			 * \param[in] boolResult				The \c IfcBooleanResult to be converted.
			 * \param[in] pos						The relative location of the origin of the representation's coordinate system within the geometric context.
			 * \param[out] itemData					A pointer to be filled with the relevant data.
			 *
			 * \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricmodelresource/lexical/ifcbooleanresult.htm
			*/
			void convertIfcBooleanResult(
				const oip::EXPRESSReference<typename IfcEntityTypesT::IfcBooleanResult>& boolResult,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				// **************************************************************************************************************************
				//	ENTITY IfcBooleanResult
				//		SUPERTYPE OF(IfcBooleanClippingResult)
				//		SUBTYPE OF(IfcGeometricRepresentationItem);
				//			Operator: IfcBooleanOperator;
				//			FirstOperand: IfcBooleanOperand;
				//			SecondOperand: IfcBooleanOperand;
				//		DERIVE
				//			Dim : IfcDimensionCount: = FirstOperand.Dim;
				//		WHERE
				//			SameDim : FirstOperand.Dim = SecondOperand.Dim;
				//			FirstOperandClosed: 
				//				NOT('IFCGEOMETRICMODELRESOURCE.IfcTessellatedFaceSet' IN TYPEOF(FirstOperand))
				//					OR(EXISTS(FirstOperand.Closed) AND FirstOperand.Closed);
				//			SecondOperandClosed: 
				//				NOT('IFCGEOMETRICMODELRESOURCE.IfcTessellatedFaceSet' IN TYPEOF(SecondOperand)) 
				//					OR(EXISTS(SecondOperand.Closed) AND SecondOperand.Closed);
				//	END_ENTITY;
				// **************************************************************************************************************************

				if (boolResult.expired())
					throw oip::ReferenceExpiredException(boolResult);

				const int boolean_result_id = boolResult->getId();

				//IfcBooleanClippingResult is already supported with IfcBooleanResult

				typename IfcEntityTypesT::IfcBooleanOperator ifcBooleanOperator = boolResult->Operator;
				typename IfcEntityTypesT::IfcBooleanOperand ifcFirstOperand = boolResult->FirstOperand;
				typename IfcEntityTypesT::IfcBooleanOperand ifcSecondOperand = boolResult->SecondOperand;

				carve::csg::CSG::OP csgOperation = carve::csg::CSG::A_MINUS_B;

				if (typeid(IfcEntityTypesT::IfcBooleanOperator::ENUM::ENUM_UNION) == typeid(ifcBooleanOperator))
					csgOperation = carve::csg::CSG::UNION;
				else if (typeid(IfcEntityTypesT::IfcBooleanOperator::ENUM::ENUM_INTERSECTION) == typeid(ifcBooleanOperator))
					csgOperation = carve::csg::CSG::INTERSECTION;
				else if (typeid(IfcEntityTypesT::IfcBooleanOperator::ENUM::ENUM_DIFFERENCE) == typeid(ifcBooleanOperator))
					csgOperation = carve::csg::CSG::A_MINUS_B;
				else
					throw oip::InconsistentModellingException("There is no other CSG operation posible!");

				// convert the first operand
				std::shared_ptr<ItemData> firstOperandData(new ItemData());
				std::shared_ptr<ItemData> emptyOperand;
				convertIfcBooleanOperand(ifcFirstOperand, pos, firstOperandData, emptyOperand);
				firstOperandData->createMeshSetsFromClosedPolyhedrons();

				// convert the second operand
				std::shared_ptr<ItemData> secondOperandData(new ItemData());
				convertIfcBooleanOperand(ifcSecondOperand, pos, secondOperandData, firstOperandData);
				secondOperandData->createMeshSetsFromClosedPolyhedrons();

				// for every first operand polyhedrons, apply all second operand polyhedrons
				std::vector<std::shared_ptr<carve::mesh::MeshSet<3>>>::iterator it_first_operands;
				for (it_first_operands = firstOperandData->meshsets.begin();
					it_first_operands != firstOperandData->meshsets.end(); ++it_first_operands)
				{
					std::shared_ptr<carve::mesh::MeshSet<3>>& first_operand_meshset = (*it_first_operands);

					std::vector<std::shared_ptr<carve::mesh::MeshSet<3> > >::iterator it_second_operands;
					for (it_second_operands = secondOperandData->meshsets.begin();
						it_second_operands != secondOperandData->meshsets.end(); ++it_second_operands)
					{
						std::shared_ptr<carve::mesh::MeshSet<3>>& second_operand_meshset = (*it_second_operands);

						int id1 = selectOperand(ifcFirstOperand);
						int id2 = selectOperand(ifcSecondOperand);
						
						std::shared_ptr<carve::mesh::MeshSet<3>> result;
						bool csg_op_ok = computeCSG(first_operand_meshset.get(),
							second_operand_meshset.get(),
							csgOperation, id1, id2, result);

						if (csg_op_ok)
						{
							first_operand_meshset = result;
						}
					}
				}

				// now copy processed first operands to result input data
				std::copy(firstOperandData->meshsets.begin(), firstOperandData->meshsets.end(), std::back_inserter(itemData->meshsets));

			}
			
			/*! \brief Returns an ID of the selected geometric representations. 
				*
				* \param[in] ifcOperand				A select type which identifies all those types of entities which may participate in a boolean operation to form a CSG solid.
				* \return							An ID of the selected geometric representations.
			*/
			int selectOperand(
				const typename IfcEntityTypesT::IfcBooleanOperand& ifcOperand
			) const noexcept(false)
			{
				switch (ifcOperand.which()) {
				case 0:
					return ifcOperand.get<0>().lock()->getId();
				case 1:
					return ifcOperand.get<1>().lock()->getId();
				case 2:
					return ifcOperand.get<2>().lock()->getId();
				case 3:
					return ifcOperand.get<3>().lock()->getId();
				default:
					throw oip::UnhandledException("Other types of entiteies are not supported in boolean operations!");
				}
			}

			/*! \brief Converts \c IfcBooleanOperand geometric representation item which may participate in a Boolean operation to form a CSG solid.
			 *
			 * \param[in] operand					The \c IfcBooleanOperand to be converted.
			 * \param[in] pos						The relative location of the origin of the representation's coordinate system within the geometric context.
			 * \param[out] itemData					A pointer to be filled with the relevant data.
			 * \param[in] otherOperand				A pointer to the other operand. 
			 *
			 * \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricmodelresource/lexical/ifcbooleanoperand.htm
			 */
			void convertIfcBooleanOperand(typename IfcEntityTypesT::IfcBooleanOperand& operand,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData,
				const std::shared_ptr<ItemData>& otherOperand
			) const noexcept(false)
			{
				// **************************************************************************************************************************
				//	TYPE IfcBooleanOperand = SELECT(
				//		IfcSolidModel,
				//		IfcHalfSpaceSolid,
				//		IfcBooleanResult,
				//		IfcCsgPrimitive3D,
				//		IfcTessellatedFaceSet);
				//	END_TYPE;
				// **************************************************************************************************************************

				switch (operand.which()) {
				case 0:
				{
					return convertIfcBooleanResult(
						operand.get<EXPRESSReference<typename IfcEntityTypesT::IfcBooleanResult>>(), 
						pos, itemData);
				}
				case 1:
				{
					return convertIfcCsgPrimitive3D(
						operand.get<EXPRESSReference<typename IfcEntityTypesT::IfcCsgPrimitive3D>>(),
						pos, itemData);
				}
				case 2:
				{
					return convertIfcHalfSpaceSolid(
						operand.get<EXPRESSReference<typename IfcEntityTypesT::IfcHalfSpaceSolid>>(),
						pos, itemData, otherOperand);
				}
				case 3:
				{
					return convertIfcSolidModel(
						operand.get<EXPRESSReference<typename IfcEntityTypesT::IfcSolidModel>>(), 
						pos, itemData);
				}
				case 4:
				{
					return faceConverter->convertIfcTessellatedItem(
						operand.get<EXPRESSReference<typename IfcEntityTypesT::IfcTessellatedFaceSet>>()
							.as<typename IfcEntityTypesT::IfcTessellatedItem>(),
						pos, itemData);
				}
				default:
					throw oip::UnhandledException(operand.classname());
				}
			}

			/*! \brief converts \c IfcCsgPrimitive3D to meshes.
			 *
			 * \param[in] csgPrimitive				The \c IfcCsgPrimitive3D to be converted.
			 * \param[in] pos						The relative location of the origin of the representation's coordinate system within the geometric context.
			 * \param[out] itemData					A pointer to be filled with the relevant data.
			 *
			 * \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricmodelresource/lexical/ifccsgprimitive3d.htm
			*/
			void convertIfcCsgPrimitive3D(
				const EXPRESSReference<typename IfcEntityTypesT::IfcCsgPrimitive3D>& csgPrimitive,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				// **************************************************************************************************************************
				//	ENTITY IfcCsgPrimitive3D
				//		ABSTRACT SUPERTYPE OF(ONEOF(
				//			IfcBlock, 
				//			IfcRectangularPyramid, 
				//			IfcRightCircularCone, 
				//			IfcRightCircularCylinder, 
				//			IfcSphere))
				//		SUBTYPE OF(IfcGeometricRepresentationItem);
				//		Position: IfcAxis2Placement3D;
				//		DERIVE
				//			Dim : IfcDimensionCount: = 3;
				//	END_ENTITY;
				// **************************************************************************************************************************

				if (csgPrimitive.expired())
					throw oip::ReferenceExpiredException(csgPrimitive);

				if (csgPrimitive.template isOfType<typename IfcEntityTypesT::IfcBlock>())
				{
					convertIfcBlock(csgPrimitive.template as<typename IfcEntityTypesT::IfcBlock>(),
						pos, itemData);
					return;
				}

				if (csgPrimitive.template isOfType<typename IfcEntityTypesT::IfcRectangularPyramid>())
				{
					convertIfcRectangularPyramid(csgPrimitive.template as<typename IfcEntityTypesT::IfcRectangularPyramid>(), 
						pos, itemData);
					return;
				}

				if (csgPrimitive.template isOfType<typename IfcEntityTypesT::IfcRightCircularCone>())
				{
					convertIfcRightCircularCone(csgPrimitive.template as<typename IfcEntityTypesT::IfcRightCircularCone>(), 
						pos, itemData);
					return;
				}

				if (csgPrimitive.template isOfType<typename IfcEntityTypesT::IfcRightCircularCylinder>())
				{
					convertIfcRightCircularCylinder(csgPrimitive.template as<typename IfcEntityTypesT::IfcRightCircularCylinder>(), 
						pos, itemData);
					return;
				}

				if (csgPrimitive.template isOfType<typename IfcEntityTypesT::IfcSphere>())
				{
					convertIfcSphere(csgPrimitive.template as<typename IfcEntityTypesT::IfcSphere>(), 
						pos, itemData);
					return;
				}
				throw oip::UnhandledException(csgPrimitive);
			}
			/*! \brief converts \c IfcBlock to meshes.
						 *
						 * \param[in] block						The \c IfcBlock to be converted.
						 * \param[in] pos						The relative location of the origin of the representation's coordinate system within the geometric context.
						 * \param[out] itemData					A pointer to be filled with the relevant data.
						 *
						 * \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricmodelresource/lexical/ifcblock.htm
						*/
			void convertIfcBlock(
				const EXPRESSReference<typename IfcEntityTypesT::IfcBlock>& block,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				// **************************************************************************************************************************
				//	ENTITY IfcBlock
				//		SUBTYPE OF(IfcCsgPrimitive3D);
				//		XLength: IfcPositiveLengthMeasure;
				//		YLength: IfcPositiveLengthMeasure;
				//		ZLength: IfcPositiveLengthMeasure;
				//	END_ENTITY;
				// **************************************************************************************************************************

				if (block.expired())
					throw oip::ReferenceExpiredException(block);

				std::shared_ptr<carve::input::PolyhedronData> polyhedronData(new carve::input::PolyhedronData());

				carve::math::Matrix primitivePlacementMatrix = block->Position ?
					pos * placementConverter->convertIfcAxis2Placement3D(block->Position) :
					pos;

				double x_length = block->XLength * this->UnitConvert()->getLengthInMeterFactor();
				double y_length = block->YLength * this->UnitConvert()->getLengthInMeterFactor();
				double z_length = block->ZLength * this->UnitConvert()->getLengthInMeterFactor();

				polyhedronData->addVertex(primitivePlacementMatrix *carve::geom::VECTOR(x_length, y_length, z_length));
				polyhedronData->addVertex(primitivePlacementMatrix *carve::geom::VECTOR(0.0, y_length, z_length));
				polyhedronData->addVertex(primitivePlacementMatrix *carve::geom::VECTOR(0.0, 0.0, z_length));
				polyhedronData->addVertex(primitivePlacementMatrix *carve::geom::VECTOR(x_length, 0.0, z_length));
				polyhedronData->addVertex(primitivePlacementMatrix *carve::geom::VECTOR(x_length, y_length, 0.0));
				polyhedronData->addVertex(primitivePlacementMatrix *carve::geom::VECTOR(0.0, y_length, 0.0));
				polyhedronData->addVertex(primitivePlacementMatrix *carve::geom::VECTOR(0.0, 0.0, 0.0));
				polyhedronData->addVertex(primitivePlacementMatrix *carve::geom::VECTOR(x_length, 0.0, 0.0));

				polyhedronData->addFace(0, 1, 2);
				polyhedronData->addFace(2, 3, 0);

				polyhedronData->addFace(7, 6, 5);
				polyhedronData->addFace(5, 4, 7);

				polyhedronData->addFace(0, 4, 5);
				polyhedronData->addFace(5, 1, 0);

				polyhedronData->addFace(1, 5, 6);
				polyhedronData->addFace(6, 2, 1);

				polyhedronData->addFace(2, 6, 7);
				polyhedronData->addFace(7, 3, 2);

				polyhedronData->addFace(3, 7, 4);
				polyhedronData->addFace(4, 0, 3);

				itemData->closed_polyhedrons.push_back(polyhedronData);
			}

			/*! \brief converts \c IfcRectangularPyramid to meshes.
			 *
			 * \param[in] rectangularPyramid		The \c IfcRectangularPyramid to be converted.
			 * \param[in] pos						The relative location of the origin of the representation's coordinate system within the geometric context.
			 * \param[out] itemData					A pointer to be filled with the relevant data.
			 *
			 * \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricmodelresource/lexical/ifcrectangularpyramid.htm
			*/
			void convertIfcRectangularPyramid(
				const EXPRESSReference<typename IfcEntityTypesT::IfcRectangularPyramid>& rectangularPyramid,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				// **************************************************************************************************************************
				//	ENTITY IfcRectangularPyramid
				//		SUBTYPE OF(IfcCsgPrimitive3D);
				//		XLength: IfcPositiveLengthMeasure;
				//		YLength: IfcPositiveLengthMeasure;
				//		Height: IfcPositiveLengthMeasure;
				//	END_ENTITY;
				// **************************************************************************************************************************

				if (rectangularPyramid.expired())
					throw oip::ReferenceExpiredException(rectangularPyramid);

				std::shared_ptr<carve::input::PolyhedronData> polyhedronData(new carve::input::PolyhedronData());

				carve::math::Matrix primitivePlacementMatrix = rectangularPyramid->Position ?
					pos * placementConverter->convertIfcAxis2Placement3D(rectangularPyramid->Position) :
					pos;

				double x_length = rectangularPyramid->XLength * 0.5 * this->UnitConvert()->getLengthInMeterFactor();
				double  y_length = rectangularPyramid->YLength * 0.5 * this->UnitConvert()->getLengthInMeterFactor();
				double height = rectangularPyramid->Height * 0.5 * this->UnitConvert()->getLengthInMeterFactor();

				polyhedronData->addVertex(primitivePlacementMatrix*carve::geom::VECTOR(0., 0., height));
				polyhedronData->addVertex(primitivePlacementMatrix*carve::geom::VECTOR(x_length, -y_length, 0.0));
				polyhedronData->addVertex(primitivePlacementMatrix*carve::geom::VECTOR(-x_length, -y_length, 0.0));
				polyhedronData->addVertex(primitivePlacementMatrix*carve::geom::VECTOR(-x_length, y_length, 0.0));
				polyhedronData->addVertex(primitivePlacementMatrix*carve::geom::VECTOR(x_length, y_length, 0.0));

				polyhedronData->addFace(1, 2, 3);
				polyhedronData->addFace(3, 4, 1);
				polyhedronData->addFace(0, 2, 1);
				polyhedronData->addFace(0, 1, 4);
				polyhedronData->addFace(0, 4, 3);
				polyhedronData->addFace(0, 3, 2);

				itemData->closed_polyhedrons.push_back(polyhedronData);
			}

			/*! \brief converts \c IfcRightCircularCone to meshes.
			 *
			 * \param[in] rightCircularCone		The \c IfcRightCircularCone to be converted.
			 * \param[in] pos						The relative location of the origin of the representation's coordinate system within the geometric context.
			 * \param[out] itemData					A pointer to be filled with the relevant data.
			 *
			 * \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricmodelresource/lexical/ifcrightcircularcone.htm
			*/
			void convertIfcRightCircularCone(
				const EXPRESSReference<typename IfcEntityTypesT::IfcRightCircularCone>& rightCircularCone,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				// **************************************************************************************************************************
				//	ENTITY IfcRightCircularCone
				//		SUBTYPE OF(IfcCsgPrimitive3D);
				//		Height: IfcPositiveLengthMeasure;
				//		BottomRadius: IfcPositiveLengthMeasure;
				//	END_ENTITY;
				// **************************************************************************************************************************

				if (rightCircularCone.expired())
					throw oip::ReferenceExpiredException(rightCircularCone);

				std::shared_ptr<carve::input::PolyhedronData> polyhedronData(new carve::input::PolyhedronData());

				carve::math::Matrix primitivePlacementMatrix = rightCircularCone->Position ?
					pos * placementConverter->convertIfcAxis2Placement3D(rightCircularCone->Position) :
					pos;

				double height = rightCircularCone->Height * this->UnitConvert()->getLengthInMeterFactor();
				double radius = rightCircularCone->BottomRadius * this->UnitConvert()->getLengthInMeterFactor();

				polyhedronData->addVertex(primitivePlacementMatrix*carve::geom::VECTOR(0.0, 0.0, height)); // top
				polyhedronData->addVertex(primitivePlacementMatrix*carve::geom::VECTOR(0.0, 0.0, 0.0)); // bottom center

				int numVerticesInCircle = this->GeomSettings()->getNumberOfVerticesForTessellation(radius);
				double deltaAngle = this->GeomSettings()->getAngleLength(radius);
				for (double angle = 0.; angle < 2 * M_PI; angle += deltaAngle)
				{
					polyhedronData->addVertex(primitivePlacementMatrix*carve::geom::VECTOR(sin(angle)*radius, cos(angle)*radius, 0.0));
				}

				// outer shape
				for (int i = 0; i < numVerticesInCircle - 1; ++i)
				{
					polyhedronData->addFace(0, i + 3, i + 2);
				}
				polyhedronData->addFace(0, 2, numVerticesInCircle + 1);

				// bottom circle
				for (int i = 0; i < numVerticesInCircle - 1; ++i)
				{
					polyhedronData->addFace(1, i + 2, i + 3);
				}
				polyhedronData->addFace(1, numVerticesInCircle + 1, 2);

				itemData->closed_polyhedrons.push_back(polyhedronData);
			}

			/*! \brief converts \c IfcRightCircularCylinder to meshes.
			 *
			 * \param[in] rightCircularCylinder		The \c IfcRightCircularCone to be converted.
			 * \param[in] pos						The relative location of the origin of the representation's coordinate system within the geometric context.
			 * \param[out] itemData					A pointer to be filled with the relevant data.
			 *
			 * \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricmodelresource/lexical/ifcrightcircularcylinder.htm
			*/
			void convertIfcRightCircularCylinder(
				const EXPRESSReference<typename IfcEntityTypesT::IfcRightCircularCylinder>& rightCircularCylinder,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				// **************************************************************************************************************************
				//	ENTITY IfcRightCircularCylinder
				//		SUBTYPE OF(IfcCsgPrimitive3D);
				//		Height: IfcPositiveLengthMeasure;
				//		Radius: IfcPositiveLengthMeasure;
				//	END_ENTITY;
				// **************************************************************************************************************************

				if (rightCircularCylinder.expired())
					throw oip::ReferenceExpiredException(rightCircularCylinder);

				std::shared_ptr<carve::input::PolyhedronData> polyhedronData(new carve::input::PolyhedronData());

				carve::math::Matrix primitivePlacementMatrix = rightCircularCylinder->Position ?
					pos * placementConverter->convertIfcAxis2Placement3D(rightCircularCylinder->Position) :
					pos;

				double height = rightCircularCylinder->Height * this->UnitConvert()->getLengthInMeterFactor();
				double radius = rightCircularCylinder->Radius * this->UnitConvert()->getLengthInMeterFactor();

				double deltaAngle = this->GeomSettings()->getAngleLength(radius);
				int slices = this->GeomSettings()->getNumberOfSegmentsForTessellation(radius);

				for (double angle = 0.; angle < 2 * M_PI; angle += deltaAngle)
				{
					polyhedronData->addVertex(primitivePlacementMatrix*carve::geom::VECTOR(sin(angle)*radius, cos(angle)*radius, height));
					polyhedronData->addVertex(primitivePlacementMatrix*carve::geom::VECTOR(sin(angle)*radius, cos(angle)*radius, 0.0));
				}

				for (int i = 0; i < slices - 1; ++i)
				{
					polyhedronData->addFace(0, i * 2 + 2, i * 2 + 4);		// top cap:		0-2-4	0-4-6		0-6-8
					polyhedronData->addFace(1, i * 2 + 3, i * 2 + 5);		// bottom cap:	1-3-5	1-5-7		1-7-9
					polyhedronData->addFace(i, i + 1, i + 3, i + 2);		// side
				}
				polyhedronData->addFace(2 * slices - 2, 2 * slices - 1, 1, 0);		// side

				itemData->closed_polyhedrons.push_back(polyhedronData);
			}

			/*! \brief converts \c IfcSphere to meshes.
			 *
			 * \param[in] sphere					The \c IfcSphere to be converted.
			 * \param[in] pos						The relative location of the origin of the representation's coordinate system within the geometric context.
			 * \param[out] itemData					A pointer to be filled with the relevant data.
			 *
			 * \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricmodelresource/lexical/ifcsphere.htm
			*/
			void convertIfcSphere(
				const EXPRESSReference<typename IfcEntityTypesT::IfcSphere>& sphere,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData
			) const noexcept(false)
			{
				// **************************************************************************************************************************
				//	ENTITY IfcSphere
				//		SUBTYPE OF(IfcCsgPrimitive3D);
				//		Radius: IfcPositiveLengthMeasure;
				//	END_ENTITY;
				// **************************************************************************************************************************

				if (sphere.expired())
					throw oip::ReferenceExpiredException(sphere);

				std::shared_ptr<carve::input::PolyhedronData> polyhedronData(new carve::input::PolyhedronData());
				carve::math::Matrix primitivePlacementMatrix = sphere->Position ?
					pos * placementConverter->convertIfcAxis2Placement3D(sphere->Position) :
					pos;

				double radius = sphere->Radius * this->UnitConvert()->getLengthInMeterFactor();

				// seen from the top, each ring is:
				//        \   |   /
				//         2- 1 -numberOfVertices
				//        / \ | / \
			    //    ---3--- 0 ---7---
				//       \  / | \ /
				//         4- 5 -6
				//        /   |   \


				polyhedronData->addVertex(pos*carve::geom::VECTOR(0.0, 0.0, radius)); // top

				const int numberOfVertices = this->GeomSettings()->getNumberOfSegmentsForTessellation(radius);
				const double horizontalAngleDelta = this->GeomSettings()->getAngleLength(radius);
				const int num_vertical_edges = ceil(0.5 * numberOfVertices);
				double verticalAngleDelta = M_PI / double(num_vertical_edges - 1);	
				double verticalAngle = verticalAngleDelta;

				for (int vertical = 1; vertical < num_vertical_edges - 1; ++vertical)
				{
					// for each vertical angle, add one horizontal circle
					double vertical_level = cos(verticalAngle)*radius;
					double radius_at_level = sin(verticalAngle)*radius;
					double horizontal_angle = 0;
					for (int i = 0; i < numberOfVertices; ++i)
					{
						polyhedronData->addVertex(primitivePlacementMatrix*carve::geom::VECTOR(sin(horizontal_angle)*radius_at_level, cos(horizontal_angle)*radius_at_level, vertical_level));
						horizontal_angle += horizontalAngleDelta;
					}
					verticalAngle += verticalAngleDelta;
				}
				polyhedronData->addVertex(primitivePlacementMatrix*carve::geom::VECTOR(0.0, 0.0, -radius)); // bottom

				// uppper triangle fan
				for (int i = 0; i < numberOfVertices - 1; ++i)
				{
					polyhedronData->addFace(0, i + 2, i + 1);
				}
				polyhedronData->addFace(0, 1, numberOfVertices);

				for (int vertical = 1; vertical < num_vertical_edges - 2; ++vertical)
				{
					int offset_inner = numberOfVertices * (vertical - 1) + 1;
					int offset_outer = numberOfVertices * vertical + 1;
					for (int i = 0; i < numberOfVertices - 1; ++i)
					{
						polyhedronData->addFace(offset_inner + i, offset_inner + 1 + i, offset_outer + 1 + i, offset_outer + i);
					}
					polyhedronData->addFace(offset_inner + numberOfVertices - 1, offset_inner, offset_outer, offset_outer + numberOfVertices - 1);

				}

				// lower triangle fan
				int last_index = (num_vertical_edges - 2)*numberOfVertices + 1;
				for (int i = 0; i < numberOfVertices - 1; ++i)
				{
					polyhedronData->addFace(last_index, last_index - (i + 2), last_index - (i + 1));
				}
				polyhedronData->addFace(last_index, last_index - 1, last_index - numberOfVertices);
				itemData->closed_polyhedrons.push_back(polyhedronData);
			}

			/*! \brief converts \c IfcHalfSpaceSolid to meshes.
			 *
			 * \param[in] halfSpaceSolid			The \c IfcHalfSpaceSolid to be converted.
			 * \param[in] pos						The relative location of the origin of the representation's coordinate system within the geometric context.
			 * \param[out] itemData					A pointer to be filled with the relevant data.
			 * \param[in] otherOperand				A pointer to the other operand.
			 *
			 * \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricmodelresource/lexical/ifchalfspacesolid.htm
			*/
			void convertIfcHalfSpaceSolid(
				const EXPRESSReference<typename IfcEntityTypesT::IfcHalfSpaceSolid>& halfSpaceSolid,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData,
				const std::shared_ptr<ItemData>& otherOperand
			) const noexcept(false)
			{
				// **************************************************************************************************************************
				//	ENTITY IfcHalfSpaceSolid
				//	SUPERTYPE OF(ONEOF(IfcBoxedHalfSpace, IfcPolygonalBoundedHalfSpace))
				//		SUBTYPE OF(IfcGeometricRepresentationItem);
				//		BaseSurface: IfcSurface;
				//		AgreementFlag: IfcBoolean;
				//	DERIVE
				//		Dim : IfcDimensionCount: = 3;
				//	END_ENTITY;
				// **************************************************************************************************************************

				if (halfSpaceSolid.expired())
					throw oip::ReferenceExpiredException(halfSpaceSolid);

				//ENTITY IfcHalfSpaceSolid SUPERTYPE OF(ONEOF(IfcBoxedHalfSpace, IfcPolygonalBoundedHalfSpace))
				EXPRESSReference<typename IfcEntityTypesT::IfcSurface> baseSurface = halfSpaceSolid->BaseSurface;

				// The base surface shall be an unbounded surface (subtype of IfcElementarySurface).
				if (!baseSurface.template isOfType<typename IfcEntityTypesT::IfcElementarySurface>())
				{
					throw oip::InconsistentModellingException(baseSurface,
						"The base surface shall be an unbounded surface (subtype of IfcElementarySurface)");
				}
				
				EXPRESSReference<typename IfcEntityTypesT::IfcElementarySurface> elemBaseSurface =
					baseSurface.template as <typename IfcEntityTypesT::IfcElementarySurface>();

				if (halfSpaceSolid.template isOfType<typename IfcEntityTypesT::IfcBoxedHalfSpace>())
				{
					convertIfcBoxedHalfSpace(
						halfSpaceSolid.template as<typename IfcEntityTypesT::IfcBoxedHalfSpace>(),
						pos, itemData);
					return;
				}
				
				carve::geom::plane<3> baseSurfacePlane;
				carve::geom::vector<3> baseSurfacePosition;
				carve::math::Matrix basePositionMatrix(carve::math::Matrix::IDENT());
				
				placementConverter->getPlane(elemBaseSurface->Position, baseSurfacePlane, baseSurfacePosition);
				basePositionMatrix = placementConverter->convertIfcAxis2Placement3D(elemBaseSurface->Position);
				

				// If the agreement flag is TRUE, then the subset is the one the normal points away from
				if (!halfSpaceSolid->AgreementFlag)
				{
					baseSurfacePlane.negate();
				}

				// check dimentions of other operand
				double extrusionDepth = HALF_SPACE_BOX_SIZE;
				carve::geom::vector<3> otherOperandPos = baseSurfacePosition;
				if (otherOperand)
				{
					carve::geom::aabb<3> aabb;
					otherOperand->createMeshSetsFromClosedPolyhedrons();
					for (int ii = 0; ii < otherOperand->meshsets.size(); ++ii)
					{
						std::shared_ptr<carve::mesh::MeshSet<3>>& meshset = otherOperand->meshsets[ii];

						if (!meshset)
						{
							throw oip::InconsistentGeometryException("Meshset not given!");
						}

						if (ii == 0)
						{
							aabb = meshset->getAABB();
						}
						else
						{
							aabb.unionAABB(meshset->getAABB());
						}
					}
					aabb.max();
					carve::geom::vector<3>& aabbExtent = aabb.extent;
					double maxExtent = std::max(aabbExtent.x, std::max(aabbExtent.y, aabbExtent.z));
					extrusionDepth = 2.0 * maxExtent;
					otherOperandPos = aabb.pos;
				}

				// ENTITY IfcPolygonalBoundedHalfSpace SUBTYPE OF IfcHalfSpaceSolid
				if (halfSpaceSolid.template isOfType<typename IfcEntityTypesT::IfcPolygonalBoundedHalfSpace>())
				{
					convertIfcPolygonalBoundedHalfSpace(
						halfSpaceSolid.template as<typename IfcEntityTypesT::IfcPolygonalBoundedHalfSpace>(), 
						pos, itemData, otherOperand, extrusionDepth);
					return;
				}
				// else, its an unbounded half space solid, create simple box
				else
				{
					std::shared_ptr<ItemData> surfaceData(new ItemData());
					faceConverter->convertIfcSurface(baseSurface, carve::math::Matrix::IDENT(), surfaceData);

					std::vector<std::shared_ptr<carve::input::PolylineSetData>> surfacePolylineData = surfaceData->polylines;
					std::vector<std::vector<carve::geom::vector<3>>> baseSurfacePointVector;

					for (auto polyline : surfacePolylineData) {
						baseSurfacePointVector.push_back(polyline->points);
					}

					std::vector<carve::geom::vector<3>> baseSurfacePoints = baseSurfacePointVector[0];

					if (baseSurfacePoints.size() != 4)
					{
						throw oip::InconsistentModellingException(halfSpaceSolid, "Invalid BaseSurface selected!");
					}

					// If the agreement flag is TRUE, then the subset is the one the normal points away from
					if (!halfSpaceSolid->AgreementFlag)
					{
						std::reverse(baseSurfacePoints.begin(), baseSurfacePoints.end());
					}
					carve::geom::vector<3>  baseSurfaceNormal = GeomUtils::computePolygonNormal(baseSurfacePoints);

					carve::geom::vector<3>  halfSpaceExtrusionDirection = -baseSurfaceNormal;
					carve::geom::vector<3>  halfSpaceExtrusionVector = halfSpaceExtrusionDirection * HALF_SPACE_BOX_SIZE;
					std::shared_ptr<carve::input::PolyhedronData> halfSpaceBoxData(new carve::input::PolyhedronData());
					itemData->closed_polyhedrons.push_back(halfSpaceBoxData);
					extrudeBox(baseSurfacePoints, halfSpaceExtrusionVector, halfSpaceBoxData);

					// apply object coordinate system
					for (auto& point : halfSpaceBoxData->points) {
						point = pos * point;
					}
				}
			}

			/*! \brief converts \c IfcBoxedHalfSpace to meshes.
			 *
			 * \param[in] halfSpaceSolid			The \c IfcBoxedHalfSpace to be converted.
			 * \param[in] pos						The relative location of the origin of the representation's coordinate system within the geometric context.
			 * \param[out] itemData					A pointer to be filled with the relevant data.
			 *
			 * \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricmodelresource/lexical/ifcboxedhalfspace.htm
			*/
			void convertIfcBoxedHalfSpace(
				const EXPRESSReference<typename IfcEntityTypesT::IfcBoxedHalfSpace>& boxedHalfSpace,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData) const noexcept(false)
			{
				// **************************************************************************************************************************
				//	ENTITY IfcBoxedHalfSpace
				//		SUBTYPE OF(IfcHalfSpaceSolid);
				//		Enclosure: IfcBoundingBox;
				//	WHERE
				//		UnboundedSurface : NOT('IFCGEOMETRYRESOURCE.IfcCurveBoundedPlane' IN TYPEOF(SELF\IfcHalfSpaceSolid.BaseSurface));
				//	END_ENTITY;
				// **************************************************************************************************************************

				if (boxedHalfSpace.expired())
					throw oip::ReferenceExpiredException(boxedHalfSpace);

				EXPRESSReference<typename IfcEntityTypesT::IfcElementarySurface> elemBaseSurface =
					boxedHalfSpace.template as <typename IfcEntityTypesT::IfcElementarySurface>();

				oip::EXPRESSReference<typename IfcEntityTypesT::IfcAxis2Placement3D>& baseSurfacePos = elemBaseSurface->Position;
				carve::geom::plane<3> baseSurfacePlane;
				carve::geom::vector<3> baseSurfacePosition;
				carve::math::Matrix basePositionMatrix(carve::math::Matrix::IDENT());
				if (elemBaseSurface->Position)
				{
					placementConverter->getPlane(elemBaseSurface->Position, baseSurfacePlane, baseSurfacePosition);
					basePositionMatrix = placementConverter->convertIfcAxis2Placement3D(elemBaseSurface->Position);
				}

				// If the agreement flag is TRUE, then the subset is the one the normal points away from
				if (!boxedHalfSpace->AgreementFlag)
				{
					baseSurfacePlane.negate();
				}

				EXPRESSReference<typename IfcEntityTypesT::IfcBoundingBox> bbox = boxedHalfSpace->Enclosure;

				typename IfcEntityTypesT::IfcLengthMeasure	bbox_x_dim = bbox->XDim;
				typename IfcEntityTypesT::IfcLengthMeasure	bbox_y_dim = bbox->YDim;
				typename IfcEntityTypesT::IfcLengthMeasure	bbox_z_dim = bbox->ZDim;

				carve::geom::vector<3> corner = placementConverter->convertIfcCartesianPoint(bbox->Corner);
				carve::math::Matrix box_position_matrix = pos * basePositionMatrix*carve::math::Matrix::TRANS(corner);

				// else, its an unbounded half space solid, create simple box
				std::shared_ptr<carve::input::PolyhedronData> polyhedron_data(new carve::input::PolyhedronData());
				polyhedron_data->addVertex(carve::geom::VECTOR(bbox_x_dim, bbox_y_dim, bbox_z_dim));
				polyhedron_data->addVertex(carve::geom::VECTOR(-bbox_x_dim, bbox_y_dim, bbox_z_dim));
				polyhedron_data->addVertex(carve::geom::VECTOR(-bbox_x_dim, -bbox_y_dim, bbox_z_dim));
				polyhedron_data->addVertex(carve::geom::VECTOR(bbox_x_dim, -bbox_y_dim, bbox_z_dim));
				polyhedron_data->addVertex(carve::geom::VECTOR(bbox_x_dim, bbox_y_dim, -bbox_z_dim));
				polyhedron_data->addVertex(carve::geom::VECTOR(-bbox_x_dim, bbox_y_dim, -bbox_z_dim));
				polyhedron_data->addVertex(carve::geom::VECTOR(-bbox_x_dim, -bbox_y_dim, -bbox_z_dim));
				polyhedron_data->addVertex(carve::geom::VECTOR(bbox_x_dim, -bbox_y_dim, -bbox_z_dim));

				polyhedron_data->addFace(0, 1, 2);
				polyhedron_data->addFace(2, 3, 0);
				polyhedron_data->addFace(7, 6, 5);
				polyhedron_data->addFace(5, 4, 7);
				polyhedron_data->addFace(0, 4, 5);
				polyhedron_data->addFace(5, 1, 0);
				polyhedron_data->addFace(1, 5, 6);
				polyhedron_data->addFace(6, 2, 1);
				polyhedron_data->addFace(2, 6, 7);
				polyhedron_data->addFace(7, 3, 2);
				polyhedron_data->addFace(3, 7, 4);
				polyhedron_data->addFace(4, 0, 3);

				itemData->closed_polyhedrons.push_back(polyhedron_data);

				// apply object coordinate system
				for (auto& point : polyhedron_data->points) {
					point = pos * point;
				}
			}


			/*! \brief converts \c IfcPolygonalBoundedHalfSpace to meshes.
			 *
			 * \param[in] halfSpaceSolid			The \c IfcPolygonalBoundedHalfSpace to be converted.
			 * \param[in] pos						The relative location of the origin of the representation's coordinate system within the geometric context.
			 * \param[out] itemData					A pointer to be filled with the relevant data.
			 * \param[in] otherOperand				A pointer to the other operand.
			 *
			 * \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricmodelresource/lexical/ifcpolygonalboundedhalfspace.htm
			*/
			void convertIfcPolygonalBoundedHalfSpace(
				const EXPRESSReference<typename IfcEntityTypesT::IfcPolygonalBoundedHalfSpace>& polygonalHalfSpace,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData,
				const std::shared_ptr<ItemData>& otherOperand,
				double extrusionDepth) const noexcept(false)
			{
				// **************************************************************************************************************************
				//	ENTITY IfcPolygonalBoundedHalfSpace
				//		SUBTYPE OF(IfcHalfSpaceSolid);
				//		Position: IfcAxis2Placement3D;
				//		PolygonalBoundary: IfcBoundedCurve;
				//	WHERE
				//		BoundaryDim : PolygonalBoundary.Dim = 2;
				//		BoundaryType: SIZEOF(TYPEOF(PolygonalBoundary) *[
				//		'IFCGEOMETRYRESOURCE.IfcPolyline',
				//		'IFCGEOMETRYRESOURCE.IfcCompositeCurve']
				//		) = 1;
				//	END_ENTITY;
				// **************************************************************************************************************************

				if (polygonalHalfSpace.expired())
					throw oip::ReferenceExpiredException(polygonalHalfSpace);
				
				EXPRESSReference<typename IfcEntityTypesT::IfcSurface> baseSurface = polygonalHalfSpace->BaseSurface;

				EXPRESSReference<typename IfcEntityTypesT::IfcElementarySurface> elemBaseSurface =
					baseSurface.template as <typename IfcEntityTypesT::IfcElementarySurface>();

				carve::geom::plane<3> baseSurfacePlane;
				carve::geom::vector<3> baseSurfacePosition;
				carve::math::Matrix basePositionMatrix(carve::math::Matrix::IDENT());
				if (elemBaseSurface->Position)
				{
					placementConverter->getPlane(elemBaseSurface->Position, baseSurfacePlane, baseSurfacePosition);
					basePositionMatrix = placementConverter->convertIfcAxis2Placement3D(elemBaseSurface->Position);
				}

				// If the agreement flag is TRUE, then the subset is the one the normal points away from
				if (!polygonalHalfSpace->AgreementFlag)
				{
					baseSurfacePlane.negate();
				}

				carve::math::Matrix boundaryPositionMatrix(carve::math::Matrix::IDENT());
				carve::geom::vector<3> boundaryPlaneNormal(carve::geom::VECTOR(0, 0, 1));
				carve::geom::vector<3> boundaryPosition;

				if (polygonalHalfSpace->Position)
				{
					boundaryPositionMatrix = placementConverter->convertIfcAxis2Placement3D(polygonalHalfSpace->Position);
					boundaryPlaneNormal = carve::geom::VECTOR(boundaryPositionMatrix._31, boundaryPositionMatrix._32, boundaryPositionMatrix._33);
					boundaryPosition = carve::geom::VECTOR(boundaryPositionMatrix._41, boundaryPositionMatrix._42, boundaryPositionMatrix._43);
				}

				// PolygonalBoundary is given in 2D
				std::vector<carve::geom::vector<2>> polygonalBoundary;
				std::vector<carve::geom::vector<2>> segmentStartPoints2D;
				curveConverter->convertIfcCurve2D(polygonalHalfSpace->PolygonalBoundary.lock(), polygonalBoundary, segmentStartPoints2D);
				ProfileConverterT<IfcEntityTypesT>::deleteLastPointIfEqualToFirst(polygonalBoundary);
				ProfileConverterT<IfcEntityTypesT>::simplifyPath(polygonalBoundary);

				if (otherOperand)
				{
					extrusionDepth = extrusionDepth * 2.0;
				}

				std::vector<std::vector<carve::geom::vector<2>>> paths;
				paths.push_back(polygonalBoundary);
				std::shared_ptr<carve::input::PolyhedronData> polyData(new carve::input::PolyhedronData);
				GeomUtils::extrude(paths, carve::geom::vector<3>(carve::geom::VECTOR(0, 0, extrusionDepth)), true, polyData);

				if (polyData->points.size() != 2 * polygonalBoundary.size())
				{
					throw oip::InconsistentGeometryException(polygonalHalfSpace, 
						"Problems in extrude : polyData->points.size() != 2 * polygonalBoundary.size()");
				}

				// apply position of PolygonalBoundary
				std::transform(polyData->points.begin(), polyData->points.end(), polyData->points.begin(), 
					[boundaryPositionMatrix](carve::geom3d::Vector& vertex)->carve::geom3d::Vector
					{ return boundaryPositionMatrix * vertex; });

				// project to base surface
				int iBasePoint = 0;
				for (auto polyPoint : polyData->points)
				{
					++iBasePoint;
					// points below the base surface are projected into plane
					double distanceToBaseSurface = carve::geom::distance(baseSurfacePlane, polyPoint);
					carve::geom::vector<3> intersectionPoint;
					double t;
					carve::IntersectionClass intersect = carve::geom3d::rayPlaneIntersection(baseSurfacePlane, polyPoint, polyPoint + boundaryPlaneNormal, intersectionPoint, t);
					if (intersect > 0)
					{
						if (iBasePoint < polygonalBoundary.size())
						{
							polyPoint = intersectionPoint;
						}
						else
						{
							polyPoint = intersectionPoint + boundaryPlaneNormal * extrusionDepth;
						}
					}
					else
					{
						BLUE_LOG(info) << "No intersection found!";
					}
				}

				// apply object coordinate system
				for (auto& point : polyData->points)
				{
					point = pos * point;
				}

				itemData->closed_polyhedrons.push_back(polyData);				
			}

			bool computeCSG(carve::mesh::MeshSet<3>* op1,
				carve::mesh::MeshSet<3>* op2,
				const carve::csg::CSG::OP operation,
				const int entity1, const int entity2,
				std::shared_ptr<carve::mesh::MeshSet<3>>& result) const noexcept(false)
			{
				bool isCSGComputationOk = false;
				std::stringstream err;

				bool meshset1_ok = GeomUtils::checkMeshSet(op1, err, entity1);
				bool meshset2_ok = GeomUtils::checkMeshSet(op2, err, entity2);

				if (meshset1_ok && meshset2_ok)
				{
					carve::csg::CSG csg;
					csg.hooks.registerHook(new carve::csg::CarveTriangulator(), carve::csg::CSG::Hooks::PROCESS_OUTPUT_FACE_BIT);
					csg.hooks.registerHook(new carve::csg::CarveTriangulatorWithImprovement(), carve::csg::CSG::Hooks::PROCESS_OUTPUT_FACE_BIT);
					csg.hooks.registerHook(new carve::csg::CarveHoleResolver(), carve::csg::CSG::Hooks::PROCESS_OUTPUT_FACE_BIT);

					try
					{
						result = std::shared_ptr<carve::mesh::MeshSet<3>>(csg.compute(op1, op2,
							operation, nullptr,
							this->GeomSettings()->getCSGtype()));

						isCSGComputationOk = GeomUtils::checkMeshSet(result.get(), err, -1);

						if (!result->isClosed() && isCSGComputationOk)
						{
							isCSGComputationOk = false;

							/*for(auto& mesh : result->meshes)
							{
							mesh->open_edges.clear();
							mesh->recalc();
							}*/

						}
					}
					catch (carve::exception& ce)
					{
						isCSGComputationOk = false;
						BLUE_LOG(error) << "csg operation failed, id1 = " << entity1 << ", id2 = " << entity2 << ", " << ce.str();
						//throw oip::InconsistentModelingException("csg operation failed");
					}
					catch (const std::out_of_range& oor)
					{
						isCSGComputationOk = false;
						BLUE_LOG(error) << "csg operation failed, id1 = " << entity1 << ", id2 = " << entity2 << ", " << oor.what();
						//throw oip::InconsistentModelingException("csg operation failed");
					}
					catch (std::exception& e)
					{
						isCSGComputationOk = false;
						BLUE_LOG(error) << "csg operation failed, id1 = " << entity1 << ", id2 = " << entity2 << ", " << e.what();
						//throw oip::InconsistentModelingException("csg operation failed");
					}
					catch (...)
					{
						isCSGComputationOk = false;
						std::cerr << "csg operation failed, id1 = " << entity1 << ", id2 = " << entity2 << std::endl;
						//throw oip::InconsistentModelingException("csg operation failed");
					}

					if (!result)
					{
						isCSGComputationOk = false;
					}
				}

				return isCSGComputationOk;
			}

			static void extrudeBox(const std::vector<carve::geom::vector<3> >& boundary_points,
				const carve::geom::vector<3>& extrusionVector,
				std::shared_ptr<carve::input::PolyhedronData>& box_data)
			{
				box_data->addVertex(boundary_points[0]);
				box_data->addVertex(boundary_points[1]);
				box_data->addVertex(boundary_points[2]);
				box_data->addVertex(boundary_points[3]);
				box_data->addVertex(boundary_points[0] + extrusionVector);
				box_data->addVertex(boundary_points[1] + extrusionVector);
				box_data->addVertex(boundary_points[2] + extrusionVector);
				box_data->addVertex(boundary_points[3] + extrusionVector);
				box_data->addFace(0, 1, 2);
				box_data->addFace(2, 3, 0);
				box_data->addFace(1, 5, 6);
				box_data->addFace(6, 2, 1);
				box_data->addFace(5, 4, 7);
				box_data->addFace(7, 6, 5);
				box_data->addFace(0, 3, 7);
				box_data->addFace(7, 4, 0);
				box_data->addFace(0, 4, 5);
				box_data->addFace(5, 1, 0);
				box_data->addFace(2, 6, 7);
				box_data->addFace(7, 3, 2);
			}


			// triangulate polyline data to flat triangulated geometry
			void triangulatePolyline(const std::shared_ptr<typename IfcEntityTypesT::IfcPolyline>& polyline,
				const carve::geom::vector<3>& refDirection,
				std::shared_ptr<carve::input::PolyhedronData>& polygonData)
			{
				uint32_t index0, index1, index2;

				carve::geom::vector<3> pos0 =
					carve::geom::VECTOR(polyline->Points[0]->Coordinates[0],
						polyline->Points[0]->Coordinates[1],
						polyline->Points[0]->Coordinates[2]);

				pos0 += refDirection;

				index0 = polygonData->addVertex(pos0);


				for (auto j = 1; j < polyline->Points.size() - 1; ++j)
				{

					carve::geom::vector<3> pos1 =
						carve::geom::VECTOR(polyline->Points[j]->Coordinates[0],
							polyline->Points[j]->Coordinates[1],
							polyline->Points[j]->Coordinates[2]);

					pos1 += refDirection;

					carve::geom::vector<3> pos2 =
						carve::geom::VECTOR(polyline->Points[j + 1]->Coordinates[0],
							polyline->Points[j + 1]->Coordinates[1],
							polyline->Points[j + 1]->Coordinates[2]);

					pos2 += refDirection;

					index1 = polygonData->addVertex(pos1);
					index2 = polygonData->addVertex(pos2);

					polygonData->addFace(index0, index1, index2);
				}
			}

		protected:

			std::shared_ptr<PlacementConverterT<IfcEntityTypesT>> placementConverter;
			std::shared_ptr<CurveConverterT<IfcEntityTypesT>> curveConverter;
			std::shared_ptr<FaceConverterT<IfcEntityTypesT>>  faceConverter;
			std::shared_ptr<ProfileCacheT<IfcEntityTypesT>>   profileCache;
		};

		//template<>
		//inline void SolidModelConverterT<emt::IfcBridgeEntityTypes, OpenInfraPlatform::IfcBridge::UnitConverter,
		//	OpenInfraPlatform::IfcBridge::IfcBridgeEntity>::convertIfcSpecificSolidModel(
		//		const std::shared_ptr<OpenInfraPlatform::IfcBridge::IfcSolidModel>& solidModel,
		//		const carve::math::Matrix& placement,
		//		std::shared_ptr<ItemData> itemData,
		//		std::stringstream& err)
		//{
		//	const double lengthFactor = unitConverter->getLengthInMeterFactor();
		//
		//	std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferencedSectionedSpine> spine =
		//		std::dynamic_pointer_cast<emt::IfcBridgeEntityTypes::IfcReferencedSectionedSpine>(solidModel);
		//
		//	if (spine)
		//	{
		//
		//		std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferenceCurve> spine_curve = spine->SpineCurve;
		//		std::vector<std::shared_ptr<emt::IfcBridgeEntityTypes::IfcProfileDef> >& vecCrossSections_unordered = spine->CrossSections;
		//		std::vector<std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferencePlacement> >& vec_crossSectionPositions_unordered = spine->CrossSectionPositions;
		//
		//		// copy cross sections
		//		std::vector<std::shared_ptr<emt::IfcBridgeEntityTypes::IfcProfileDef>>::iterator it_cross_sections;
		//		std::vector<std::shared_ptr<emt::IfcBridgeEntityTypes::IfcProfileDef>> vecCrossSections = vecCrossSections_unordered;
		//
		//		// copy placements
		//		std::vector<std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferencePlacement>>::iterator it_placements;
		//		std::vector<std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferenceCurvePlacement>> vec_crossSectionPositions;
		//		std::vector<carve::geom::vector<3>> vecCurveAbscissas;
		//		for (it_placements = vec_crossSectionPositions_unordered.begin(); it_placements != vec_crossSectionPositions_unordered.end(); ++it_placements)
		//		{
		//			std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferencePlacement> reference_placement = (*it_placements);
		//
		//			std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferenceCurvePlacement> reference_curve_placement =
		//				std::dynamic_pointer_cast<emt::IfcBridgeEntityTypes::IfcReferenceCurvePlacement>(reference_placement);
		//
		//			if (reference_curve_placement)
		//			{
		//				vec_crossSectionPositions.push_back(reference_curve_placement);
		//			}
		//		}
		//
		//		unsigned int num_cross_sections = vecCrossSections.size();
		//		if (vec_crossSectionPositions.size() < num_cross_sections)
		//		{
		//			num_cross_sections = vec_crossSectionPositions.size();
		//		}
		//
		//		std::shared_ptr<carve::input::PolyhedronData> polyhedron_data(new carve::input::PolyhedronData());
		//
		//		// sort placements according to abscissa
		//		std::vector<std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferenceCurvePlacement> >::iterator it_curve_placements;
		//		std::vector<std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferenceCurvePlacement> >::iterator it_curve_placements_inner;
		//
		//		for (unsigned int i = 0; i < num_cross_sections; ++i)
		//		{
		//			std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferenceCurvePlacement> reference_curve_placement = vec_crossSectionPositions[i];
		//			double abscissa = reference_curve_placement->CurvilinearAbscissa;
		//
		//			for (unsigned int j = i + 1; j < num_cross_sections; ++j)
		//			{
		//				std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferenceCurvePlacement> other = vec_crossSectionPositions[j];
		//				double abscissa_other = other->CurvilinearAbscissa;
		//
		//				if (abscissa_other < abscissa)
		//				{
		//					// reordering necessary
		//					std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferenceCurvePlacement> copy = vec_crossSectionPositions[i];
		//					vec_crossSectionPositions[i] = vec_crossSectionPositions[j];
		//					vec_crossSectionPositions[j] = copy;
		//
		//					std::shared_ptr<emt::IfcBridgeEntityTypes::IfcProfileDef> copy_profile = vecCrossSections[i];
		//					vecCrossSections[i] = vecCrossSections[j];
		//					vecCrossSections[j] = copy_profile;
		//					abscissa = abscissa_other;
		//				}
		//			}
		//		}
		//
		//		if (num_cross_sections > 1)
		//		{
		//			for (unsigned int k = 0; k < num_cross_sections; ++k)
		//			{
		//				std::shared_ptr<emt::IfcBridgeEntityTypes::IfcArbitraryClosedProfileDef> profileDef
		//					= std::dynamic_pointer_cast<emt::IfcBridgeEntityTypes::IfcArbitraryClosedProfileDef>(vecCrossSections[k]);
		//
		//				const double curveAbcissa = vec_crossSectionPositions[k]->CurvilinearAbscissa;
		//				const carve::geom::vector<3> refDirection =
		//					carve::geom::VECTOR(vec_crossSectionPositions[k]->RefDirection->DirectionRatios[0],
		//						vec_crossSectionPositions[k]->RefDirection->DirectionRatios[1],
		//						vec_crossSectionPositions[k]->RefDirection->DirectionRatios[2]);
		//
		//				const carve::geom::vector<3> curveAbscissa3D = refDirection * curveAbcissa * lengthFactor;
		//
		//				vecCurveAbscissas.push_back(curveAbscissa3D);
		//
		//				if (profileDef)
		//				{
		//
		//					// create cabs with voids
		//					std::shared_ptr<emt::IfcBridgeEntityTypes::IfcPolyline> outerCurvePolyline =
		//						std::dynamic_pointer_cast<emt::IfcBridgeEntityTypes::IfcPolyline>(profileDef->OuterCurve);
		//
		//					// gather all curve polygons
		//					std::vector<std::vector<carve::geom::vector<3>>> polygonVertices3D;
		//					std::vector<std::vector<carve::geom2d::P2>> polygonVertices2D;
		//
		//					std::vector<carve::geom::vector<3>> curveVertices3D;
		//					std::vector<carve::geom2d::P2> curveVertices2D;
		//
		//					ProjectionPlane plane = UNDEFINED;
		//
		//					for (const auto& point : outerCurvePolyline->Points)
		//					{
		//						carve::geom::vector<3> pos3D =
		//							carve::geom::VECTOR(point->Coordinates[0] * lengthFactor,
		//								point->Coordinates[1] * lengthFactor,
		//								point->Coordinates[2] * lengthFactor);
		//
		//						pos3D += curveAbscissa3D;
		//						pos3D = placement * pos3D;
		//
		//						const double nx = std::abs(refDirection.x);
		//						const double ny = std::abs(refDirection.y);
		//						const double nz = std::abs(refDirection.z);
		//
		//						const double refDirMax = std::max(std::max(nx, ny), nz);
		//
		//						carve::geom2d::P2 pos2D = carve::geom::VECTOR(0, 0);
		//
		//						if (refDirMax == nx)
		//						{
		//							plane = YZ_PLANE;
		//							pos2D = carve::geom::VECTOR(pos3D.y, pos3D.z);
		//						}
		//						else if (refDirMax == ny)
		//						{
		//							plane = XZ_PLANE;
		//							pos2D = carve::geom::VECTOR(pos3D.x, pos3D.z);
		//						}
		//						else if (refDirMax == nz)
		//						{
		//							plane = XY_PLANE;
		//							pos2D = carve::geom::VECTOR(pos3D.x, pos3D.y);
		//						}
		//
		//						curveVertices3D.push_back(pos3D);
		//						curveVertices2D.push_back(pos2D);
		//					}
		//
		//					carve::geom3d::Vector normal2D = GeomUtils::computePolygon2DNormal(curveVertices2D);
		//
		//					if (normal2D.z < 0)
		//					{
		//						std::reverse(curveVertices3D.begin(), curveVertices3D.end());
		//						std::reverse(curveVertices2D.begin(), curveVertices2D.end());
		//					}
		//
		//					polygonVertices3D.push_back(curveVertices3D);
		//					polygonVertices2D.push_back(curveVertices2D);
		//
		//					std::shared_ptr<emt::IfcBridgeEntityTypes::IfcArbitraryProfileDefWithVoids> profileDefWithVoids
		//						= std::dynamic_pointer_cast<emt::IfcBridgeEntityTypes::IfcArbitraryProfileDefWithVoids>(profileDef);
		//
		//
		//					// if profile defintion contains voids than subtract inner curves from outer curve
		//					if (profileDefWithVoids)
		//					{
		//						for (auto j = 0; j < profileDefWithVoids->InnerCurves.size(); ++j)
		//						{
		//							std::shared_ptr<emt::IfcBridgeEntityTypes::IfcPolyline> innerCurvePolyline =
		//								std::dynamic_pointer_cast<emt::IfcBridgeEntityTypes::IfcPolyline>(profileDefWithVoids->InnerCurves[j]);
		//
		//							curveVertices3D.clear();
		//							curveVertices2D.clear();
		//
		//							for (const auto& point : innerCurvePolyline->Points)
		//							{
		//								carve::geom::vector<3> pos3D =
		//									carve::geom::VECTOR(point->Coordinates[0] * lengthFactor,
		//										point->Coordinates[1] * lengthFactor,
		//										point->Coordinates[2] * lengthFactor);
		//
		//								pos3D += curveAbscissa3D;
		//								pos3D = placement * pos3D;
		//
		//								carve::geom2d::P2 pos2D = carve::geom::VECTOR(0, 0);
		//
		//								if (plane == YZ_PLANE) { pos2D = carve::geom::VECTOR(pos3D.y, pos3D.z); }
		//								else if (plane == XZ_PLANE) { pos2D = carve::geom::VECTOR(pos3D.x, pos3D.z); }
		//								else if (plane == XY_PLANE) { pos2D = carve::geom::VECTOR(pos3D.x, pos3D.y); }
		//
		//								curveVertices3D.push_back(pos3D);
		//								curveVertices2D.push_back(pos2D);
		//							}
		//
		//							normal2D = GeomUtils::computePolygon2DNormal(curveVertices2D);
		//
		//							if (normal2D.z > 0)
		//							{
		//								// reverse order of inner curves to incorporate holes
		//								std::reverse(curveVertices3D.begin(), curveVertices3D.end());
		//								std::reverse(curveVertices2D.begin(), curveVertices2D.end());
		//							}
		//
		//							polygonVertices3D.push_back(curveVertices3D);
		//							polygonVertices2D.push_back(curveVertices2D);
		//						}
		//					}
		//
		//					// result after incorporating holes in polygons if defined
		//					std::vector<std::pair<size_t, size_t>> resultIndices;
		//
		//					// merged vertices after incorporating of holes
		//					std::vector<carve::geom2d::P2> mergedVertices2D;
		//					std::vector<carve::geom::vector<3>> mergedVertices3D;
		//
		//					try
		//					{
		//						resultIndices = carve::triangulate::incorporateHolesIntoPolygon(polygonVertices2D);
		//
		//						for (const auto& index : resultIndices)
		//						{
		//							const size_t curveIndex = index.first;
		//							const size_t vertexIndex = index.second;
		//
		//							mergedVertices2D.push_back(polygonVertices2D[curveIndex][vertexIndex]);
		//							mergedVertices3D.push_back(polygonVertices3D[curveIndex][vertexIndex]);
		//						}
		//					}
		//					// if incorporation of holes failes then triangulate only the outer curve
		//					catch (...)
		//					{
		//						mergedVertices3D = polygonVertices3D[0];
		//						mergedVertices2D = polygonVertices2D[0];
		//					}
		//
		//					// if appropriate index configuration was found proceed with triangulation
		//					std::vector<carve::triangulate::tri_idx> triangulatedIndices;
		//
		//					carve::triangulate::triangulate(mergedVertices2D, triangulatedIndices);
		//					carve::triangulate::improve(mergedVertices2D, triangulatedIndices);
		//
		//					// contains index in polyhedron data for each merged vertex
		//					std::map<std::string, uint32_t> mergedVertexIndices;
		//					std::vector<uint32_t> vertexIndices;
		//					vertexIndices.resize(mergedVertices3D.size());
		//
		//					std::shared_ptr<carve::input::PolyhedronData> polygon(new carve::input::PolyhedronData());
		//
		//					// gather all vertices in a new polyhedron data and obtain their indices 
		//					for (const auto& vertex : mergedVertices3D)
		//					{
		//						std::stringstream keyID;
		//						keyID << vertex.x << " " << vertex.y << " " << vertex.z;
		//
		//						uint32_t vIndex = 0;
		//
		//						auto itFound = mergedVertexIndices.find(keyID.str());
		//						if (itFound != mergedVertexIndices.end()) { vIndex = itFound->second; }
		//						else
		//						{
		//							vIndex = polygon->addVertex(vertex);
		//							mergedVertexIndices[keyID.str()] = vIndex;
		//						}
		//
		//						vertexIndices.push_back(vIndex);
		//					}
		//
		//					// read triangulated result and add corresponding faces to resulting polygon
		//					for (const auto& triangle : triangulatedIndices)
		//					{
		//						uint32_t v0, v1, v2;
		//						v0 = vertexIndices[triangle.a];
		//						v1 = vertexIndices[triangle.b];
		//						v2 = vertexIndices[triangle.c];
		//
		//						polygon->addFace(v0, v1, v2);
		//					}
		//
		//					itemData->open_or_closed_polyhedrons.push_back(polygon);
		//				}
		//			}
		//		}
		//
		//		//convert all profiles
		//		for (unsigned int i = 0; i < num_cross_sections - 1; ++i)
		//		{
		//			carve::geom::vector<3> abscissa3D = vecCurveAbscissas[i] * lengthFactor;
		//
		//			std::shared_ptr<emt::IfcBridgeEntityTypes::IfcProfileDef> profile_def = vecCrossSections[i];
		//			std::shared_ptr<emt::IfcBridgeEntityTypes::IfcArbitraryProfileDefWithVoids> profile_with_voids
		//				= std::dynamic_pointer_cast<emt::IfcBridgeEntityTypes::IfcArbitraryProfileDefWithVoids>(profile_def);
		//
		//			// if profile contains inner and outer curve profile definitions create corresponding cabs as well.
		//			if (profile_with_voids)
		//			{
		//				std::shared_ptr<emt::IfcBridgeEntityTypes::IfcArbitraryProfileDefWithVoids> next_profile_with_voids;
		//
		//				carve::geom::vector<3> abscissaNext3D = vecCurveAbscissas[i + 1] * lengthFactor;
		//
		//				std::shared_ptr<emt::IfcBridgeEntityTypes::IfcProfileDef> profile_def2 = vecCrossSections[i + 1];
		//				next_profile_with_voids = std::dynamic_pointer_cast<emt::IfcBridgeEntityTypes::IfcArbitraryProfileDefWithVoids>(profile_def2);
		//
		//				ProfileConverterT<emt::IfcBridgeEntityTypes, OpenInfraPlatform::IfcBridge::UnitConverter> profileConverter(geomSettings, unitConverter);
		//				profileConverter.convertIfcArbitraryProfileWithVoids(profile_with_voids, next_profile_with_voids, placement, itemData, abscissa3D, abscissaNext3D);
		//				continue;
		//			}
		//
		//			std::shared_ptr<emt::IfcBridgeEntityTypes::IfcArbitraryClosedProfileDef> profile
		//				= std::dynamic_pointer_cast<emt::IfcBridgeEntityTypes::IfcArbitraryClosedProfileDef>(profile_def);
		//
		//			// if profile is simply closed (no voids inside) just convert geometry
		//			if (profile)
		//			{
		//				std::shared_ptr<emt::IfcBridgeEntityTypes::IfcArbitraryClosedProfileDef> next_profile;
		//
		//				carve::geom::vector<3> abscissaNext3D = vecCurveAbscissas[i + 1] * lengthFactor;
		//
		//				std::shared_ptr<emt::IfcBridgeEntityTypes::IfcProfileDef> profile_def2 = vecCrossSections[i + 1];
		//				next_profile = std::dynamic_pointer_cast<emt::IfcBridgeEntityTypes::IfcArbitraryClosedProfileDef>(profile_def2);
		//
		//				ProfileConverterT<emt::IfcBridgeEntityTypes, OpenInfraPlatform::IfcBridge::UnitConverter> profileConverter(geomSettings, unitConverter);
		//
		//				profileConverter.convertIfcArbitraryClosedProfileDef(profile, next_profile, placement, itemData, abscissa3D, abscissaNext3D);
		//				continue;
		//			}
		//		}
		//	}
		//}
		//
		//template<>
		//inline bool SolidModelConverterT<emt::Ifc4EntityTypes, OpenInfraPlatform::Ifc4::UnitConverter,
		//	OpenInfraPlatform::Ifc4::Ifc4Entity>::convertAdvancedBrep(
		//		std::shared_ptr<emt::Ifc4EntityTypes::IfcManifoldSolidBrep>& manifoldSolidBrep,
		//		const carve::math::Matrix& pos,
		//		std::shared_ptr<ItemData> itemData,
		//		std::stringstream& err)
		//{
		//	std::shared_ptr<emt::Ifc4EntityTypes::IfcAdvancedBrep> advancedBrep =
		//		std::dynamic_pointer_cast<emt::Ifc4EntityTypes::IfcAdvancedBrep>(manifoldSolidBrep);
		//
		//	if (advancedBrep)
		//	{
		//
		//		std::shared_ptr<emt::Ifc4EntityTypes::IfcClosedShell>& outerShell = manifoldSolidBrep->Outer;
		//
		//		if (outerShell)
		//		{
		//			// first convert outer shell
		//			std::vector<std::shared_ptr<emt::Ifc4EntityTypes::IfcFace> >& facesOuterShell = outerShell->CfsFaces;
		//			std::shared_ptr<ItemData> inputDataOuterShell(new ItemData());
		//
		//			try
		//			{
		//				faceConverter->convertIfcAdvancedFaceList(facesOuterShell, pos, inputDataOuterShell, err);
		//			}
		//			catch (...)
		//			{
		//				//return;
		//			}
		//			std::copy(inputDataOuterShell->closed_polyhedrons.begin(),
		//				inputDataOuterShell->closed_polyhedrons.end(),
		//				std::back_inserter(itemData->closed_polyhedrons));
		//
		//			std::copy(inputDataOuterShell->polylines.begin(),
		//				inputDataOuterShell->polylines.end(),
		//				std::back_inserter(itemData->polylines));
		//
		//			std::shared_ptr<emt::Ifc4EntityTypes::IfcAdvancedBrepWithVoids> advancedBrepWithVoids =
		//				std::dynamic_pointer_cast<emt::Ifc4EntityTypes::IfcAdvancedBrepWithVoids>(advancedBrep);
		//
		//			if (advancedBrepWithVoids)
		//			{
		//				std::cout << "ERROR\t| IfcAdvancedBrepWithVoids not implemented, yet" << std::endl;
		//				return false;
		//			}
		//		}
		//
		//		return true;
		//	}
		//
		//	return false;
		//}

	}
	}
}

#endif
