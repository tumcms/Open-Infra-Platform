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

			void convertIfcCsgSolid(const carve::math::Matrix& pos, std::shared_ptr<ItemData> itemData, const EXPRESSReference<typename IfcEntityTypesT::IfcCsgSolid> &csg_solid) throw(...)
			{
				if (csg_solid.expired())
					throw oip::ReferenceExpiredException(csg_solid);

				switch (csg_solid->TreeRootExpression.which()) {
				case 0:
					convertIfcBooleanResult(csg_solid->TreeRootExpression.get<0>().lock(), pos, itemData);
					break;
				case 1:
					convertIfcCsgPrimitive3D(csg_solid->TreeRootExpression.get<1>().lock(), pos, itemData);
					break;
				default:
					throw oip::InconsistentModellingException("IfcCsgSolid->TreeRootExpression has no value set.");
					break;
				}
			}

			void convertIfcManifoldSolidBrepOuterShell(const carve::math::Matrix& pos, std::shared_ptr<ItemData> itemData, const EXPRESSReference<typename IfcEntityTypesT::IfcClosedShell> &outerShell)
			{
				// first convert outer shell

				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcFace>> vec_facesOuterShell;
				std::shared_ptr<ItemData> inputDataOuterShell(new ItemData());


				vec_facesOuterShell.resize(outerShell->CfsFaces.size());
				std::transform(outerShell->CfsFaces.begin(), outerShell->CfsFaces.end(), vec_facesOuterShell.begin(), [](auto& it) {return it.lock(); });

				try {
					faceConverter->convertIfcFaceList(vec_facesOuterShell, pos, inputDataOuterShell);
				}
				catch (...) {
					//return;
				}
				std::copy(inputDataOuterShell->open_or_closed_polyhedrons.begin(),
					inputDataOuterShell->open_or_closed_polyhedrons.end(),
					std::back_inserter(itemData->closed_polyhedrons));
			}

			void convertIfcManifoldSolidBrep(const carve::math::Matrix& pos, std::shared_ptr<ItemData> itemData, const EXPRESSReference<typename IfcEntityTypesT::IfcManifoldSolidBrep> &manifoldSolidBrep) throw(...)
			{
				if (manifoldSolidBrep.expired())
					throw oip::ReferenceExpiredException(manifoldSolidBrep);

				// Get outer (attribute 1).
				if (manifoldSolidBrep->Outer) {
					convertIfcManifoldSolidBrepOuterShell(pos, itemData, manifoldSolidBrep->Outer);
				} //endif outer
				else {
					BLUE_LOG(warning) << "IfcManifoldSolidBrep.Outer = IfcClosedShell not set.";
				}

				// (1/2) IfcAdvancedBrep SUBTYPE of IfcManifoldSolidBrep
				if (manifoldSolidBrep.isOfType<typename IfcEntityTypesT::IfcAdvancedBrep>()){
					throw oip::UnhandledException(manifoldSolidBrep.as<typename IfcEntityTypesT::IfcAdvancedBrep>());
				} // endif advanced_brep

				// (2/2) IfcFacetedBrep SUBTYPE of IfcManifoldSolidBrep
				if (manifoldSolidBrep.isOfType<typename IfcEntityTypesT::IfcFacetedBrep>()) {
					throw oip::UnhandledException(manifoldSolidBrep.as<typename IfcEntityTypesT::IfcFacetedBrep>());
				}

				throw oip::UnhandledException(manifoldSolidBrep);
			}

			void convertIfcSectionedSolidHorizontal(const carve::math::Matrix& pos, std::shared_ptr<ItemData> itemData, const EXPRESSReference<typename IfcEntityTypesT::IfcSectionedSolidHorizontal>& sectioned_solid_horizontal) throw(...)
			{
				if (sectioned_solid_horizontal.expired())
					throw oip::ReferenceExpiredException(sectioned_solid_horizontal);

				// (1/1) IfcSectionedSolidHorizontal SUBTYPE of IfcSectionedSolid
		
					// Get cross section positions and fixed axis vertical (attributes 3-4).
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcDistanceExpression>> vec_cross_section_positions;
					vec_cross_section_positions.resize(sectioned_solid_horizontal->CrossSectionPositions.size());
					std::transform(sectioned_solid_horizontal->CrossSectionPositions.begin(),
						sectioned_solid_horizontal->CrossSectionPositions.end(),
						vec_cross_section_positions.begin(), [](auto& it) {return it.lock(); });
					bool fixed_axis_vertical = sectioned_solid_horizontal->FixedAxisVertical;

					BLUE_LOG(warning) << "Geometry conversion for IfcSectionedSolidHorizontal not implemented.";
					// TO DO: implement, check for formal propositions. 

				 //endif sectioned_solid_horizontal
			}

			void convertIfcSectionedSolid(const carve::math::Matrix& pos, std::shared_ptr<ItemData> itemData, const EXPRESSReference<typename IfcEntityTypesT::IfcSectionedSolid>& sectioned_solid) throw(...)
			{
				if (sectioned_solid.expired())
					throw oip::ReferenceExpiredException(sectioned_solid);

				//Get directrix and cross sections (attributes 1-2).
				const EXPRESSReference<typename IfcEntityTypesT::IfcCurve> & directrix =
					sectioned_solid->Directrix;
				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcProfileDef>> vec_cross_sections;
				vec_cross_sections.resize(sectioned_solid->CrossSections.size());
				std::transform(sectioned_solid->CrossSections.begin(),
					sectioned_solid->CrossSections.end(),
					vec_cross_sections.begin(), [](auto& it) {return it.lock(); });

				// (1/1) IfcSectionedSolidHorizontal SUBTYPE of IfcSectionedSolid
				if (sectioned_solid.isOfType<typename IfcEntityTypesT::IfcSectionedSolidHorizontal>())
				{
					convertIfcSectionedSolidHorizontal(pos, itemData, sectioned_solid.as<typename IfcEntityTypesT::IfcSectionedSolidHorizontal>());
					return;
				}
			}

			void convertIfcSurfaceCurveSweptAreaSolid(const carve::math::Matrix& pos, std::shared_ptr<ItemData> itemData, EXPRESSReference<typename IfcEntityTypesT::IfcSurfaceCurveSweptAreaSolid>& surface_curve_swept_area_solid) throw(...)
			{
				if (surface_curve_swept_area_solid.expired())
					throw oip::ReferenceExpiredException(surface_curve_swept_area_solid);
				// Get directrix, start parameter, end paramter and reference surface (attributes 3-6).
				std::shared_ptr<typename IfcEntityTypesT::IfcCurve> directrix =
					surface_curve_swept_area_solid->Directrix.lock();	// TO DO: formal proposition: if no StartParam or EndParam, Directrix has to be a bounded or closed curve. 
				double start_param = surface_curve_swept_area_solid->StartParam;	// TO DO: optional
				double end_param = surface_curve_swept_area_solid->EndParam;		// TO DO: optional
				std::shared_ptr<typename IfcEntityTypesT::IfcSurface> ref_surface =
					surface_curve_swept_area_solid->ReferenceSurface.lock();	// TO DO: next level

// TO DO: implement / check current implementation //


				std::shared_ptr<ProfileConverterT<IfcEntityTypesT>> profile_converter = profileCache->getProfileConverter(swept_area);
				const std::vector<std::vector<carve::geom::vector<2>>>& paths = profile_converter->getCoordinates();
				std::shared_ptr<carve::input::PolyhedronData> poly_data(new carve::input::PolyhedronData);

				std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& directrix_curve = surface_curve_swept_area_solid->Directrix.lock();
				//const int nvc = geomSettings->num_vertices_per_circle;
				double length_in_meter = UnitConvert()->getLengthInMeterFactor();

				std::vector<carve::geom::vector<3> > segment_start_points;
				std::vector<carve::geom::vector<3> > basis_curve_points;
				curveConverter->convertIfcCurve(directrix_curve, basis_curve_points, segment_start_points);

				std::shared_ptr<carve::input::PolylineSetData> polyline_data(new carve::input::PolylineSetData());
				faceConverter->convertIfcSurface(surface_curve_swept_area_solid->ReferenceSurface.lock(), swept_area_pos, polyline_data);
				return;
			}

			void convertIfcExtrudedAreaSolidextrudedarea(const carve::math::Matrix& pos, std::shared_ptr<ItemData> itemData, const EXPRESSReference<typename IfcEntityTypesT::IfcExtrudedAreaSolid>& extruded_area) throw(...)
			{
				// Get extruded direction and depth (attributes 3-4). 
				std::shared_ptr<typename IfcEntityTypesT::IfcDirection> extrude_direction =
					extruded_area->ExtrudedDirection.lock();
				
				double depth = extruded_area->Depth;
				/*convertIfcExtrudedAreaSolid(extruded_area, swept_area_pos, itemData);*/
			}
			
			
			void convertIfcSweptAreaSolid(const carve::math::Matrix& pos, std::shared_ptr<ItemData> itemData, const EXPRESSReference<typename IfcEntityTypesT::IfcSweptAreaSolid>& swept_area_solid) throw(...)
			{
				if (swept_area_solid.expired())
					throw oip::ReferenceExpiredException(swept_area_solid);

				// Get swept area and position(attributes 1 - 2).
				const EXPRESSReference<typename IfcEntityTypesT::IfcProfileDef>& swept_area = swept_area_solid->SweptArea;
				carve::math::Matrix swept_area_pos(pos);	// check if local coordinate system is specified for extrusion

				if (swept_area_solid->Position)
				{
					EXPRESSReference<typename IfcEntityTypesT::IfcAxis2Placement3D> swept_area_position = swept_area_solid->Position;

					swept_area_pos = pos * placementConverter->convertIfcAxis2Placement3D(swept_area_position.lock());
				}

				// (1/4) IfcExtrudedAreaSolid SUBTYPE of IfcSweptAreaSolid
				if (swept_area_solid.isOfType<typename IfcEntityTypesT::IfcExtrudedAreaSolid>()) {

					/*// Get extruded direction and depth (attributes 3-4). 
					std::shared_ptr<typename IfcEntityTypesT::IfcDirection> extrude_direction =
						extruded_area->ExtrudedDirection.lock();*/
					// Get extruded direction and depth (attributes 3-4). 
					convertIfcExtrudedAreaSolidextrudedarea(pos, itemData, swept_area_solid.as<typename IfcEntityTypesT::IfcExtrudedAreaSolid>());
					
					//double depth = extruded_area->Depth; 
					convertIfcExtrudedAreaSolid(extruded_area, swept_area_pos, itemData);
					return;
				}//endif 

				// (2/4) IfcFixedReferenceSweptAreaSolid SUBTYPE of IfcSweptAreaSolid
				if (swept_area_solid.isOfType<typename IfcEntityTypesT::IfcFixedReferenceSweptAreaSolid>()) 
				{
					// Get directrix, start parameter, end parameter and fixed reference (attributes 3-6).
						//std::shared_ptr<typename IfcEntityTypesT::IfcCurve> directrix =
						//	fixed_ref_swept_area_solid->Directrix.lock();	// TO DO: formal proposition: if no StartParam or EndParam, Directrix has to be a bounded or closed curve. 
					//double start_param = fixed_ref_swept_area_solid->StartParam;	// TO DO: optional
					//double end_param = fixed_ref_swept_area_solid->EndParam;		// TO DO: optional
					//std::shared_ptr<typename IfcEntityTypesT::IfcDirection> fixed_ref =
					//	fixed_ref_swept_area_solid->FixedReference.lock();
					throw oip::UnhandledException(swept_area_solid.as<typename IfcEntityTypesT::IfcFixedReferenceSweptAreaSolid>());
					return;
				}

				// (3/4) IfcRevolvedAreaSolid SUBTYPE of IfcSweptAreaSolid
				if (swept_area_solid.isOfType<typename IfcEntityTypesT::IfcRevolvedAreaSolid>()) 
				{
					// Get axis and angle (attributes 3-4). 
					std::shared_ptr<typename IfcEntityTypesT::IfcAxis1Placement> axis =
						revolved_area_solid->Axis.lock();
					double angle = revolved_area_solid->Angle;

					convertIfcRevolvedAreaSolid(revolved_area_solid, swept_area_pos, itemData);
					return;
					// TO DO: implement//
					throw oip::UnhandledException(swept_area_solid.as<typename IfcEntityTypesT::IfcRevolvedAreaSolid>());
				}

				// (4/4) IfcSurfaceCurveSweptAreaSolid SUBTYPE of IfcSeweptAreaSolid
				if (swept_area_solid.isOfType<typename IfcEntityTypesT::IfcSurfaceCurveSweptAreaSolid>())
				{
					convertIfcSurfaceCurveSweptAreaSolid(pos, itemData, swept_area_solid.as<typename IfcEntityTypesT::IfcSurfaceCurveSweptAreaSolid>());
					return;
				}
			}

			void convertIfcSolidModel(const std::shared_ptr<typename IfcEntityTypesT::IfcSolidModel>& solidModel,
                                                  const carve::math::Matrix& pos,
                                                  std::shared_ptr<ItemData> itemData)
			    {
				// *****************************************************************************************************************************************//
				//	IfcCsgSolid SUBTYPE of IfcSolidModel																									//																			//
				// *****************************************************************************************************************************************//
				//

                            auto solid_model_ref = oip::EXPRESSReference<typename IfcEntityTypesT::IfcSolidModel>(solidModel);

				if (solid_model_ref.isOfType<typename IfcEntityTypesT::IfcCsgSolid>())
				{
                                    convertIfcCsgSolid(pos, itemData, solid_model_ref.as<typename IfcEntityTypesT::IfcCsgSolid>());
				    return;
				} //endif csg_solid

				// *****************************************************************************************************************************************//
				//	IfcManifoldSolidBrep SUBTYPE of IfcSolidModel																							//
				//	ABSTRACT SUPERTYPE of IfcAdvancedBrep, IfcFacetedBrep																					//
				// *****************************************************************************************************************************************//

				if (solid_model_ref.isOfType<typename IfcEntityTypesT::IfcManifoldSolidBrep>())
				{
                    convertIfcManifoldSolidBrep(pos, itemData, solid_model_ref.as<typename IfcEntityTypesT::IfcManifoldSolidBrep>());
                     return;
                } //endif manifoldSolidBrep

				// *****************************************************************************************************************************************//
				//	IfcSectionedSolid SUBTYPE of IfcSolidModel																							  //
				//	ABSTRACT SUPERTYPE of IfcSectionedSolidHorizontal																					  //
				// *****************************************************************************************************************************************//

				if (solid_model_ref.isOfType<typename IfcEntityTypesT::IfcSectionedSolid>())
				{
					convertIfcSectionedSolid(pos, itemData, solid_model_ref.as<typename IfcEntityTypesT::IfcSectionedSolid>());
					return;
					
				} //endif sectioned_solid

				// *****************************************************************************************************************************************//
				//	IfcSweptAreaSolid SUBTYPE of IfcSolidModel																								//
				//	ABSTRACT SUPERTYPE of IfcExtrudedAreaSolid, IfcFixedReferenceSweptAreaSolid, IfcRevolvedAreaSolid, IfcSurfaceCurveSweptAreaSolid		//
				// *****************************************************************************************************************************************//

				if (solid_model_ref.isOfType<typename IfcEntityTypesT::IfcSweptAreaSolid>())
				{
					convertIfcSweptAreaSolid(pos, itemData, solid_model_ref.as<typename IfcEntityTypesT::IfcSweptAreaSolid>());
					return;
					
					/*// (3/4) IfcRevolvedAreaSolid SUBTYPE of IfcSweptAreaSolid
					std::shared_ptr<typename IfcEntityTypesT::IfcRevolvedAreaSolid> revolved_area_solid =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcRevolvedAreaSolid>(swept_area_solid);
					if (revolved_area_solid)
					{
						// Get axis and angle (attributes 3-4). 
						std::shared_ptr<typename IfcEntityTypesT::IfcAxis1Placement> axis =
							revolved_area_solid->Axis.lock();
						double angle = revolved_area_solid->Angle;

						convertIfcRevolvedAreaSolid(revolved_area_solid, swept_area_pos, itemData);
						return;
						// TO DO: implement//

					}
					
					// (4/4) IfcSurfaceCurveSweptAreaSolid SUBTYPE of IfcSweptAreaSolid
					std::shared_ptr<typename IfcEntityTypesT::IfcSurfaceCurveSweptAreaSolid> surface_curve_swept_area_solid =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSurfaceCurveSweptAreaSolid>(swept_area_solid);
					if (surface_curve_swept_area_solid)
					{

						// Get directrix, start parameter, end paramter and reference surface (attributes 3-6).
						std::shared_ptr<typename IfcEntityTypesT::IfcCurve> directrix =
							surface_curve_swept_area_solid->Directrix.lock();	// TO DO: formal proposition: if no StartParam or EndParam, Directrix has to be a bounded or closed curve. 
						double start_param = surface_curve_swept_area_solid->StartParam;	// TO DO: optional
						double end_param = surface_curve_swept_area_solid->EndParam;		// TO DO: optional
						std::shared_ptr<typename IfcEntityTypesT::IfcSurface> ref_surface =
							surface_curve_swept_area_solid->ReferenceSurface.lock();	// TO DO: next level

// TO DO: implement / check current implementation //
#ifdef _DEBUG
						std::cout << "Warning\t| IfcSurfaceCurveSweptAreaSolid not implemented" << std::endl;
#endif

						std::shared_ptr<ProfileConverterT<IfcEntityTypesT>> profile_converter = profileCache->getProfileConverter(swept_area);
						const std::vector<std::vector<carve::geom::vector<2>>>& paths = profile_converter->getCoordinates();
						std::shared_ptr<carve::input::PolyhedronData> poly_data(new carve::input::PolyhedronData);

						std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& directrix_curve = surface_curve_swept_area_solid->Directrix.lock();
						//const int nvc = geomSettings->num_vertices_per_circle;
						double length_in_meter = UnitConvert()->getLengthInMeterFactor();

						std::vector<carve::geom::vector<3> > segment_start_points;
						std::vector<carve::geom::vector<3> > basis_curve_points;
						curveConverter->convertIfcCurve(directrix_curve, basis_curve_points, segment_start_points);

						std::shared_ptr<carve::input::PolylineSetData> polyline_data(new carve::input::PolylineSetData());
						faceConverter->convertIfcSurface(surface_curve_swept_area_solid->ReferenceSurface.lock(), swept_area_pos, polyline_data);

#ifdef _DEBUG
						BLUE_LOG(trace) << "Processed IfcSurfaceCurveSweptAreaSolid #" << surface_curve_swept_area_solid->getId();
#endif
						return;
					}

					BLUE_LOG(error) << "Unhandled IFC Representation: #" << solidModel->getId() << "=" << solidModel->classname();
					return;
				*/}	//endif swept_area_solid


				// *****************************************************************************************************************************************//
				//	IfcSweptDiskSolid SUBTYPE of IfcSolidModel																								//
				//	ABSTRACT SUPERTYPE of IfcSweptDiskSolidPolygonal																						//
				// *****************************************************************************************************************************************//

				std::shared_ptr<typename IfcEntityTypesT::IfcSweptDiskSolid> swept_disk_solid =
					std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSweptDiskSolid>(solidModel);
				if (swept_disk_solid)
				{
					// Get directrix, radius, inner radius, start parameter and end parameter (attributes 1-5). 
					std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& directrix_curve = swept_disk_solid->Directrix.lock();
					
					double length_in_meter = UnitConvert()->getLengthInMeterFactor();
					double radius = swept_disk_solid->Radius * length_in_meter;
					

					double radius_inner = 0.0;
					typename IfcEntityTypesT::IfcLengthMeasure& sweptInnerRadius = swept_disk_solid->InnerRadius;
					if (swept_disk_solid->InnerRadius)
					{
						radius_inner = sweptInnerRadius * length_in_meter;
						//radius_inner = swept_disp_solid->InnerRadius->length_in_meter;
					}

					double inner_radius = swept_disk_solid->InnerRadius;
					double start_param = swept_disk_solid->StartParam;
					double end_param = swept_disk_solid->EndParam;

					// TODO: handle inner radius, start param, end param and check for formal propositions!

					// (1/1) IfcSweptDiskSolidPolygonal SUBTYPE of IfcSweptDiskSolid
					std::shared_ptr<typename IfcEntityTypesT::IfcSweptDiskSolidPolygonal> swept_disk_solid_polygonal =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSweptDiskSolidPolygonal>(swept_disk_solid);
					if (swept_disk_solid_polygonal)
					{
						// Get fillet radius (attribute 6). 
						double fillet_radius = swept_disk_solid_polygonal->FilletRadius;
						// TODO: implement and check for formal propositions.

					} //endif swept_disk_solid_polygonal

					// TO DO: understand what happens here
					std::vector<carve::geom::vector<3> > segment_start_points;
					std::vector<carve::geom::vector<3> > basis_curve_points;
					curveConverter->convertIfcCurve(directrix_curve, basis_curve_points, segment_start_points);

					std::shared_ptr<carve::input::PolyhedronData> pipe_data(new carve::input::PolyhedronData());
					itemData->closed_polyhedrons.push_back(pipe_data);
					std::vector<carve::geom::vector<3> > inner_shape_points;

					const int nvc = GeomSettings()->getNumberOfVerticesForTessellation(radius);
					double delta_angle = GeomSettings()->getAngleLength(radius);

					std::vector<carve::geom::vector<3> > circle_points;
					std::vector<carve::geom::vector<3> > circle_points_inner;
					int i; double angle;
					for ( i = 0, angle = 0.; 
						  i < nvc; 
						  ++i,	 angle += delta_angle)
					{
						// cross section (circle) is defined in YZ plane
						double x = sin(angle);
						double y = cos(angle);
						circle_points.push_back(carve::geom::VECTOR(0.0, x*radius, y*radius));
						circle_points_inner.push_back(carve::geom::VECTOR(0.0, x*radius_inner, y*radius_inner));
					}

					int num_base_points = basis_curve_points.size();
					carve::math::Matrix matrix_sweep;

					carve::geom::vector<3> local_z(carve::geom::VECTOR(0, 0, 1));

					if (num_base_points < 2)
					{
						std::cout << "IfcSweptDiskSolid: num curve points < 2" << std::endl;
						return;
					}

					bool bend_found = false;
					if (num_base_points > 3)
					{
						// compute local z vector by dot product of the first bend of the reference line
						carve::geom::vector<3> vertex_back2 = basis_curve_points.at(0);
						carve::geom::vector<3> vertex_back1 = basis_curve_points.at(1);
						for (int i = 2; i < num_base_points; ++i)
						{
							carve::geom::vector<3> vertex_current = basis_curve_points.at(i);
							carve::geom::vector<3> section1 = vertex_back1 - vertex_back2;
							carve::geom::vector<3> section2 = vertex_current - vertex_back1;
							section1.normalize();
							section2.normalize();

							double dot_product = dot(section1, section2);
							double dot_product_abs = abs(dot_product);

							// if dot == 1 or -1, then points are colinear
							if (dot_product_abs < (1.0 - 0.0001) || dot_product_abs >(1.0 + 0.0001))
							{
								// bend found, compute cross product
								carve::geom::vector<3> lateral_vec = cross(section1, section2);
								local_z = cross(lateral_vec, section1);
								local_z.normalize();
								bend_found = true;
								break;
							}
						}
					}

					if (!bend_found)
					{
						// sweeping curve is linear. assume any local z vector
						local_z = carve::geom::VECTOR(0, 0, 1);
						double dot_normal_local_z = dot((basis_curve_points.at(1) - basis_curve_points.at(0)), local_z);
						if (abs(dot_normal_local_z) < 0.0001)
						{
							local_z = carve::geom::VECTOR(0, 1, 0);
							local_z.normalize();
						}
					}

					for (int ii = 0; ii < num_base_points; ++ii)
					{
						carve::geom::vector<3> vertex_current = basis_curve_points.at(ii);
						carve::geom::vector<3> vertex_next;
						carve::geom::vector<3> vertex_before;
						if (ii == 0)
						{
							// first point
							vertex_next = basis_curve_points.at(ii + 1);
							carve::geom::vector<3> delta_element = vertex_next - vertex_current;
							vertex_before = vertex_current - (delta_element);
						}
						else if (ii == num_base_points - 1)
						{
							// last point
							vertex_before = basis_curve_points.at(ii - 1);
							carve::geom::vector<3> delta_element = vertex_current - vertex_before;
							vertex_next = vertex_before + (delta_element);
						}
						else
						{
							// inner point
							vertex_next = basis_curve_points.at(ii + 1);
							vertex_before = basis_curve_points.at(ii - 1);
						}

						carve::geom::vector<3> bisecting_normal;
						GeomUtils::bisectingPlane(vertex_before, vertex_current, vertex_next, bisecting_normal);

						carve::geom::vector<3> section1 = vertex_current - vertex_before;
						carve::geom::vector<3> section2 = vertex_next - vertex_current;
						section1.normalize();
						section2.normalize();
						double dot_product = dot(section1, section2);
						double dot_product_abs = abs(dot_product);

						if (dot_product_abs < (1.0 - 0.0001) || dot_product_abs >(1.0 + 0.0001))
						{
							// bend found, compute next local z vector
							carve::geom::vector<3> lateral_vec = cross(section1, section2);
							local_z = cross(lateral_vec, section1);
							local_z.normalize();
						}
						if (ii == num_base_points - 1)
						{
							bisecting_normal *= -1.0;
						}

						GeomUtils::convertPlane2Matrix(bisecting_normal, vertex_current, local_z, matrix_sweep);
						matrix_sweep = pos * matrix_sweep;

						for (int jj = 0; jj < nvc; ++jj)
						{
							carve::geom::vector<3> vertex = circle_points.at(jj);
							vertex = matrix_sweep * vertex;
							pipe_data->addVertex(vertex);
						}

						if (radius_inner > 0)
						{
							for (int jj = 0; jj < nvc; ++jj)
							{
								carve::geom::vector<3> vertex = circle_points_inner.at(jj);
								vertex = matrix_sweep * vertex;
								inner_shape_points.push_back(vertex);
								//pipe_data->addVertex( vertex );
							}
						}
					}

					// outer shape
					size_t num_vertices_outer = pipe_data->getVertexCount();
					for (size_t i = 0; i < num_base_points - 1; ++i)
					{
						int i_offset = i * nvc;
						int i_offset_next = (i + 1)*nvc;
						for (int jj = 0; jj < nvc; ++jj)
						{
							int current_loop_pt = jj + i_offset;
							int current_loop_pt_next = (jj + 1) % nvc + i_offset;

							int next_loop_pt = jj + i_offset_next;
							int next_loop_pt_next = (jj + 1) % nvc + i_offset_next;
							pipe_data->addFace(current_loop_pt, next_loop_pt, next_loop_pt_next, current_loop_pt_next);
						}
					}

					if (radius_inner > 0)
					{
						if (inner_shape_points.size() != num_vertices_outer)
						{
							std::cout << "IfcSweptDiskSolid: inner_shape_points.size() != num_vertices_outer" << std::endl;
						}

						// add points for inner shape
						for (size_t i = 0; i < inner_shape_points.size(); ++i)
						{
							pipe_data->addVertex(inner_shape_points[i]);
						}

						// faces of inner shape
						for (size_t i = 0; i < num_base_points - 1; ++i)
						{
							int i_offset = i * nvc + num_vertices_outer;
							int i_offset_next = (i + 1)*nvc + num_vertices_outer;
							for (int jj = 0; jj < nvc; ++jj)
							{
								int current_loop_pt = jj + i_offset;
								int current_loop_pt_next = (jj + 1) % nvc + i_offset;

								int next_loop_pt = jj + i_offset_next;
								int next_loop_pt_next = (jj + 1) % nvc + i_offset_next;
								//pipe_data->addFace( current_loop_pt, next_loop_pt, next_loop_pt_next, current_loop_pt_next );  
								pipe_data->addFace(current_loop_pt, current_loop_pt_next, next_loop_pt_next, next_loop_pt);
							}
						}

						// front cap
						for (int jj = 0; jj < nvc; ++jj)
						{
							int outer_rim_next = (jj + 1) % nvc;
							int inner_rim_next = outer_rim_next + num_vertices_outer;
							pipe_data->addFace(jj, outer_rim_next, num_vertices_outer + jj);
							pipe_data->addFace(outer_rim_next, inner_rim_next, num_vertices_outer + jj);
						}

						// back cap
						int back_offset = (num_base_points - 1)*nvc;
						for (int jj = 0; jj < nvc; ++jj)
						{
							int outer_rim_next = (jj + 1) % nvc + back_offset;
							int inner_rim_next = outer_rim_next + num_vertices_outer;
							pipe_data->addFace(jj + back_offset, num_vertices_outer + jj + back_offset, outer_rim_next);
							pipe_data->addFace(outer_rim_next, num_vertices_outer + jj + back_offset, inner_rim_next);
						}
					}
					else
					{
						// front cap, full pipe, create triangle fan
						for (int jj = 0; jj < nvc - 2; ++jj)
						{
							pipe_data->addFace(0, jj + 1, jj + 2);
						}

						// back cap
						int back_offset = (num_base_points - 1)*nvc;
						for (int jj = 0; jj < nvc - 2; ++jj)
						{
							pipe_data->addFace(back_offset, back_offset + jj + 2, back_offset + jj + 1);
						}
					}

					return;
				} // endif swept_disp_solid

				//std::shared_ptr<emt::Ifc4x1EntityTypes::IfcSectionedSolidHorizontal> ssh =
				//	std::dynamic_pointer_cast<emt::Ifc4x1EntityTypes::IfcSectionedSolidHorizontal>(solidModel);
				//if (ssh)
				//{
				//
				//	//	ENTITY IfcRepresentationItem;
				//	//	INVERSE
				//	//		LayerAssignments	 : 	SET OF IfcPresentationLayerAssignment FOR AssignedItems;
				//	//		StyledByItem	 : 	SET [0:1] OF IfcStyledItem FOR Item;
				//	//	ENTITY IfcGeometricRepresentationItem;
				//	//	ENTITY IfcSolidModel;
				//	//		DERIVE
				//	//		Dim	 : 	IfcDimensionCount :=  3;
				//	// ENTITY IfcSectionedSolid
				//	//	    Directrix: IfcCurve;
				//	//	    CrossSections: LIST[2:? ] OF IfcProfileDef;					
				//	// ENTITY IfcSectionedSolidHorizontal
				//	//      CrossSectionPositions: LIST[2:? ] OF IfcDistanceExpression;
				//	//      FixedAxisVertical: IfcBoolean;
				//	// END_ENTITY;
				//
				//	convertIfcSectionedSolidHorizontal(ssh, itemData, err);
				//
				//	return;
				//}



				convertIfcSpecificSolidModel(solidModel, pos, itemData);

				BLUE_LOG(error) << "Unhandled IFC Representation: #" << solidModel->getId() << "=" << solidModel->classname();

			}

			//end convertIfcSolidModel

			//void convertIfcSectionedSolidHorizontal(
			//	std::shared_ptr<emt::Ifc4x1EntityTypes::IfcSectionedSolidHorizontal> ssh,
			//	std::shared_ptr<ItemData> itemData,
			//	std::stringstream& err)
			//
			//{
			//	// Validate data.
			//	if (!ssh->Directrix)
			//	{
			//		err << "Invalid Directrix" << std::endl;
			//		return;
			//	}
			//
			//	//	    CrossSections: LIST[2:? ] OF IfcProfileDef;	
			//	if ( ssh->CrossSections.size() < 2 )
			//	{
			//		err << "Invalid CrossSections" << std::endl;
			//		return;
			//	}
			//
			//	//      CrossSectionPositions: LIST[2:? ] OF IfcDistanceExpression;
			//	if ( ssh->CrossSectionPositions.size() < 2 )
			//	{
			//		err << "Invalid CrossSectionPositions" << std::endl;
			//		return;
			//	}
			//
			//	if (!ssh->FixedAxisVertical)
			//	{
			//		err << "Invalid FixedAxisVertical" << std::endl;
			//		return;
			//	}
			//
			//	// Retrieve data from IfcSectionedSolidHorizontal.
			//	std::shared_ptr<emt::Ifc4x1EntityTypes::IfcCurve>& directrixCurve = ssh->Directrix;
			//	std::vector<std::shared_ptr<emt::Ifc4x1EntityTypes::IfcProfileDef>>& crossSections = ssh->CrossSections;
			//	std::vector<std::shared_ptr<emt::Ifc4x1EntityTypes::IfcDistanceExpression>>& crossSectionPositions = ssh->CrossSectionPositions;
			//	std::shared_ptr<emt::Ifc4x1EntityTypes::IfcBoolean>& fixedAxisVertical = ssh->FixedAxisVertical;
			//
			//	// Check whether the same amount of crossSections and crossSectionPositions exist. CrossSections and CrossSectionPositions are lists L[2:?]
			//	int crossSectionsSize = crossSections.size();
			//	int crossSectionPositionsSize = crossSectionPositions.size();
			//	if (crossSectionsSize != crossSectionPositionsSize)
			//	{
			//		// If only one value is missing, delete the last value of the other list and continue anyway.
			//		if ( abs (crossSectionsSize - crossSectionPositionsSize) > 1 )
			//		{ 
			//			err << "CrossSectionPositions and CrossSections are not equal in size." << std::endl; 
			//			return; 
			//		}
			//		if (crossSectionsSize > crossSectionPositionsSize)
			//		{
			//			err << "CrossSections size decreased by one." << std::endl;
			//			crossSections.pop_back();
			//		}
			//		else if(crossSectionPositionsSize > crossSectionsSize)
			//		{
			//			err << "CrossSectionPositions size decreased by one." << std::endl;
			//			crossSectionPositions.pop_back();
			//		}
			//	}
			//	
			//	// Get unit conversion factor (to do: multiply by value to convert units)
			//	double length_in_meter = unitConverter->getLengthInMeterFactor();
			//	//double angle_factor = unitConverter->getAngleInRadianFactor(); (necessary?)
			//
			//	
			//	// Declare vectors of doubles for every element of the distance expressions
			//	std::vector< double > crossSectionDistanceAlong;
			//	std::vector< double > crossSectionOffsetLateral;
			//	std::vector< double > crossSectionOffsetVertical;
			//	std::vector< double > crossSectionOffsetLongitudinal;
			//	std::vector< bool > crossSectionAlongHorizontal;
			//
			//	// Iterate over all crossSectionPositions, convert units
			//	for (int position = 0; position <= crossSectionPositions.size(); ++position)
			//	{
			//		auto distExpr = crossSectionPositions[position];
			//		// Save distance expressions to vectors of doubles.
			//		if (distExpr->DistanceAlong)
			//			crossSectionDistanceAlong.push_back(distExpr->DistanceAlong-> length_in_meter);
			//		else
			//		{
			//			err << "Missing DistanceAlong." << endl;
			//			return;
			//		}
			//
			//		if (distExpr->OffsetLateral)
			//			crossSectionOffsetLateral.push_back(distExpr->OffsetLateral->length_in_meter);
			//		else
			//			crossSectionOffsetLateral.push_back(0.);
			//
			//		if (distExpr->OffsetVertical)
			//			crossSectionOffestVertical.push_back(distExpr->OffsetLateral-> length_in_meter);
			//		else
			//			crossSectionOffsetVertical.push_back(0.);
			//
			//		if (distExpr->OffsetLongitudinal)
			//			crossSectionOffsetLongitudinal.push_back(distExpr->OffsetLongitudinal->length_in_meter);
			//		else
			//			crossSectionOffsetLongitudinal.push_back(0.);
			//
			//		if (distExpr->AlongHorizontal)
			//			crossSectionAlongHorizontal.push_back(distExpr->AlongHorizontal);
			//		else
			//			crossSectionAlongHorizontal.push_back(false);
			//
			//	}
			//
			//	// Define a vector of pointers. Revolved and Extruded only use a single profile, so they do not need vectors.
			//	std::vector< std::shared_ptr<ProfileConverterT<IfcEntityTypesT, IfcUnitConverterT>> > profile_converter;
			//	
			//	// Give crossSection information (profileDefs) to profileConverter (iterator: number of CrossSectionElements)
			//	for (int element = 0; element <= crossSections.size(); ++element)
			//	{
			//		// Fill vector profile_converter with one profileConverter per crossSection. ProfileConverter sweeps across an area within the boundaries of the profile definition (which may only be a curve).
			//		//profile_converter.push_back( profileCache->getProfileConverter(crossSections[element]) );
			//		
			//		// Get profile coordinates: Vector of multiple profiles. -> Vector of multiple lines makes a profile. -> Vector of multiple coordinates make a line. -> Vector of 2 makes a pair of coordinates.
			//		// const std::vector<std::vector<std::vector<carve::geom::vector<2> > > >& profile_coords = profile_converter[crossSectionElement]->getCoordinates();
			//	}
			//
			//	// Give directrix to curveConverter. convertIfcCurve is a member function of curveConverter that returns void. (see also: surface_curve_swept_area_solid)
			//	// segment_start_points and basis_curve_points are return parameters (&)
			//	std::vector<carve::geom::vector<3> > segment_start_points;
			//	std::vector<carve::geom::vector<3> > basis_curve_points;
			//	//curveConverter->convertIfcCurve(directrixCurve, basis_curve_points, segment_start_points);
			//
			//	//IfcDistanceExpression: 4 IfcLengthMeasures of type double, usually in mm: DistanceAlong, OffsetLateral, OffsetVertical, OffsetLongitudinal. 1 IfcBoolean: AlongHorizontal.
			//
			//	// Get positions
			//	// Tesselation?
			//	// Compute the normal according to axis
			//
			//}

			void convertIfcExtrudedAreaSolid(
				const std::shared_ptr<typename IfcEntityTypesT::IfcExtrudedAreaSolid>& extrudedArea,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData)
			{
				const int entity_id = extrudedArea->getId();
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processing IfcExtrudedAreaSolid #" << entity_id;
#endif
				if (!extrudedArea->ExtrudedDirection)
				{
					BLUE_LOG(error) << "Invalid ExtrudedDirection ";
					return;
				}

				if (!extrudedArea->Depth)
				{
					BLUE_LOG(error) << "Invalid Depth ";
					return;
				}
				double length_factor = UnitConvert()->getLengthInMeterFactor();

				// direction and length of extrusion
				const double depth = (typename IfcEntityTypesT::IfcLengthMeasure)(extrudedArea->Depth) * length_factor;
				//const double depth = extrudedArea->Depth->length_factor;
				carve::geom::vector<3>  extrusion_vector;
				auto& vec_direction = extrudedArea->ExtrudedDirection->DirectionRatios;
				

				if (vec_direction.size() > 2)
				{
					extrusion_vector = carve::geom::VECTOR(vec_direction[0] * depth, vec_direction[1] * depth, vec_direction[2] * depth);
				}
				else if (vec_direction.size() > 1)
				{
					extrusion_vector = carve::geom::VECTOR(vec_direction[0] * depth, vec_direction[1] * depth, 0);
				}

				// swept area
				std::shared_ptr<typename IfcEntityTypesT::IfcProfileDef> swept_area = extrudedArea->SweptArea.lock();
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processing IfcExtrudedAreaSolid.SweptArea IfcProfileDef #" << swept_area->getId();
#endif
				std::shared_ptr<ProfileConverterT<IfcEntityTypesT>> profile_converter =
					profileCache->getProfileConverter(swept_area);
				profile_converter->simplifyPaths();
				const std::vector<std::vector<carve::geom::vector<2>>>& paths = profile_converter->getCoordinates();

				if (paths.size() == 0)
				{
					return;
				}
				std::shared_ptr<carve::input::PolyhedronData> poly_data(new carve::input::PolyhedronData);
				std::stringstream err;
				GeomUtils::extrude(paths, extrusion_vector, poly_data, err);

				// apply object coordinate system
				std::transform(poly_data->points.begin(), poly_data->points.end(), poly_data->points.begin(), [pos](auto vertex) -> decltype(vertex) {return pos * vertex; });

				//std::vector<carve::geom::vector<3> >& points = poly_data->points;
				//for (std::vector<carve::geom::vector<3> >::iterator it_points = points.begin(); it_points != points.end(); ++it_points)
				//{
				//	carve::geom::vector<3>& vertex = (*it_points);
				//	vertex = pos * vertex;
				//}

				itemData->closed_polyhedrons.push_back(poly_data);
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processed IfcExtrudedAreaSolid #" << entity_id;
#endif
			}//end convertIfcExtrudedAreaSolid()

			void convertIfcRevolvedAreaSolid(
				const std::shared_ptr<typename IfcEntityTypesT::IfcRevolvedAreaSolid>& revolvedArea,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData)
			{
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processing IfcRevolvedAreaSolid #" << revolvedArea->getId();
#endif
				if (!revolvedArea->SweptArea)
				{
					return;
				}
				double length_factor = UnitConvert()->getLengthInMeterFactor();

				// angle and axis
				double angle_factor = UnitConvert()->getAngleInRadianFactor();
				std::shared_ptr<typename IfcEntityTypesT::IfcProfileDef> swept_area_profile = revolvedArea->SweptArea.lock();
				double revolution_angle = revolvedArea->Angle * angle_factor;

				carve::geom::vector<3>  axis_location;
				carve::geom::vector<3>  axis_direction;
				if (revolvedArea->Axis)
				{
					std::shared_ptr<typename IfcEntityTypesT::IfcAxis1Placement> axis_placement = revolvedArea->Axis.lock();

					if (axis_placement->Location)
					{
						axis_location = placementConverter->convertIfcCartesianPoint(axis_placement->Location );
					}

					if (axis_placement->Axis)
					{
						decltype(axis_placement->Axis)::type axis = axis_placement->Axis;
						axis_direction = carve::geom::VECTOR(
							axis->DirectionRatios[0],
							axis->DirectionRatios[1],
							axis->DirectionRatios[2]);
					}
				}

				// rotation base point is the one with the smallest distance on the rotation axis
				carve::geom::vector<3>  origin;
				carve::geom::vector<3>  base_point;
				GeomUtils::closestPointOnLine(origin, axis_location, axis_direction, base_point);
				base_point *= -1;

				// swept area
				std::shared_ptr<ProfileConverterT<IfcEntityTypesT>> profile_converter = profileCache->getProfileConverter(swept_area_profile);
				const std::vector<std::vector<carve::geom::vector<2> > >& profile_coords = profile_converter->getCoordinates();

				// tesselate
				std::vector<std::vector<carve::geom::vector<2> > > profile_coords_2d;
				for (int i = 0; i < profile_coords.size(); ++i)
				{
					const std::vector<carve::geom::vector<2> >& profile_loop = profile_coords[i];
					//std::vector<carve::geom::vector<2> > profile_loop_2d;
					//for( int j = 0; j<profile_loop.size(); ++j )
					//{
					//	profile_loop_2d.push_back( carve::geom::VECTOR( profile_loop[j].x, profile_loop[j].y ) );
					//}
					profile_coords_2d.push_back(profile_loop);
				}

				std::vector<carve::geom::vector<2> > merged;
				std::vector<carve::triangulate::tri_idx> triangulated;
				try
				{
					std::vector<std::pair<size_t, size_t> > result = carve::triangulate::incorporateHolesIntoPolygon(profile_coords_2d);	// first is loop index, second is vertex index in loop
					merged.resize(result.size());
					for (size_t i = 0; i < result.size(); ++i)
					{
						int loop_number = result[i].first;
						int index_in_loop = result[i].second;

						if (loop_number >= profile_coords_2d.size())
						{
							std::cout << ": loop_number >= face_loops_projected.size()" << std::endl;
							continue;
						}

						std::vector<carve::geom2d::P2>& loop_projected = profile_coords_2d[loop_number];

						carve::geom2d::P2& point_projected = loop_projected[index_in_loop];
						merged.push_back(point_projected);
					}
					carve::triangulate::triangulate(merged, triangulated);
					carve::triangulate::improve(merged, triangulated);
				}
				catch (...)
				{
					/*for( size_t i = 0; i < profile_coords_2d.size(); ++i )
					{
					for ( size_t j = 0; j < profile_coords_2d[i].size(); ++j)
					{
					int loop_number = i;
					int index_in_loop = j;

					carve::geom2d::P2& loop_point = profile_coords_2d[loop_number][index_in_loop];
					merged.push_back( loop_point );

					if( loop_number >= profile_coords_2d.size() )
					{
					std::cout << __FUNC__ << ": loop_number >= face_loops_projected.size()" << std::endl;
					continue;
					}

					std::vector<carve::geom2d::P2>& loop_projected = profile_coords_2d[loop_number];

					carve::geom2d::P2& point_projected = loop_projected[index_in_loop];
					merged.push_back( point_projected );
					}
					}
					carve::triangulate::triangulate(merged, triangulated);
					carve::triangulate::improve(merged, triangulated);*/


					BLUE_LOG(error) << "carve::triangulate::incorporateHolesIntoPolygon failed ";
					return;
				}

				if (profile_coords.size() == 0)
				{
					BLUE_LOG(error) << "#" << revolvedArea->getId() << " = IfcRevolvedAreaSolid: convertIfcRevolvedAreaSolid: num_loops == 0";
					return;
				}
				if (profile_coords[0].size() < 3)
				{
					BLUE_LOG(error) << "#" << revolvedArea->getId() << " = IfcRevolvedAreaSolid: convertIfcRevolvedAreaSolid: num_polygon_points < 3";
					return;
				}

				// determine the biggest distance to rotational axis -> biggest radius that needs to be tesselated
				double biggestRadius = 0.;
				for (int i = 0; i < profile_coords.size(); ++i)
				{
					const std::vector<carve::geom::vector<2> >& profile_loop = profile_coords[i];
					for( int j=0; j < profile_loop.size(); ++j)
					{
						const carve::geom::vector<2>& pt_2d = profile_loop.at(j);
						carve::geom::vector<3>  point(carve::geom::VECTOR(pt_2d.x, pt_2d.y, 0.));
						carve::geom::vector<3>  pointOnLine;
						GeomUtils::closestPointOnLine(point, axis_location, axis_direction, pointOnLine);
						biggestRadius = std::max(biggestRadius, (pointOnLine - point).length());
					}
				}

				if (revolution_angle > M_PI * 2) revolution_angle = M_PI * 2;
				if (revolution_angle < -M_PI * 2) revolution_angle = M_PI * 2;

				int num_segments = GeomSettings()->getNumberOfSegmentsForTessellation(biggestRadius, abs(revolution_angle));
				if (num_segments < 6)
				{
					num_segments = 6;
				}
				double angle = 0.0;
				double d_angle = revolution_angle / (double)num_segments;

				// check if we have to change the direction
				carve::geom::vector<3>  polygon_normal = GeomUtils::computePolygon2DNormal(profile_coords[0]);
				const carve::geom::vector<2>&  pt0_2d = profile_coords[0][0];
				carve::geom::vector<3>  pt0_3d(carve::geom::VECTOR(pt0_2d.x, pt0_2d.y, 0));
				carve::geom::vector<3>  pt0 = carve::math::Matrix::ROT(d_angle, axis_direction)*(pt0_3d + base_point);
				if (polygon_normal.z*pt0.z > 0)
				{
					angle = revolution_angle;
					d_angle = -d_angle;
				}

				std::shared_ptr<carve::input::PolyhedronData> polyhedron_data(new carve::input::PolyhedronData());
				itemData->closed_polyhedrons.push_back(polyhedron_data);

				// create vertices
				carve::math::Matrix m;
				for (int i = 0; i <= num_segments; ++i)
				{
					m = carve::math::Matrix::ROT(angle, -axis_direction);
					for (int j = 0; j < profile_coords.size(); ++j)
					{
						const std::vector<carve::geom::vector<2> >& loop = profile_coords[j];

						for (int k = 0; k < loop.size(); ++k)
						{
							const carve::geom::vector<2>& point = loop[k];

							carve::geom::vector<3>  vertex = m * (carve::geom::VECTOR(point.x, point.y, 0) + base_point) - base_point;
							polyhedron_data->addVertex(pos*vertex);
						}
					}
					angle += d_angle;
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
				// TODO: use triangulated
				polyhedron_data->addFace(front_face_loop.rbegin(), front_face_loop.rend());

				// end cap
				std::vector<int> end_face_loop;
				const int end_face_begin = num_segments * num_polygon_points;
				for (int j = 0; j < num_polygon_points; ++j)
				{
					end_face_loop.push_back(end_face_begin + j);
				}
				polyhedron_data->addFace(end_face_loop.begin(), end_face_loop.end());

				// faces of revolved shape
				for (int i = 0; i < num_polygon_points - 1; ++i)
				{
					int i_offset_next = i + num_polygon_points;
					for (int j = 0; j < num_segments; ++j)
					{
						int j_offset = j * num_polygon_points;
						polyhedron_data->addFace(j_offset + i, j_offset + i + 1, j_offset + 1 + i_offset_next, j_offset + i_offset_next);
					}
				}

				for (int j = 0; j < num_segments; ++j)
				{
					int j_offset = j * num_polygon_points;
					polyhedron_data->addFace(j_offset + num_polygon_points - 1, j_offset, j_offset + num_polygon_points, j_offset + num_polygon_points + num_polygon_points - 1);
				}
			}

			void convertIfcBooleanResult(const std::shared_ptr<typename IfcEntityTypesT::IfcBooleanResult>& boolResult,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData)
			{
				const int boolean_result_id = boolResult->getId();

#ifdef _DEBUG
				BLUE_LOG(trace) << "Processing IfcBooleanResult #" << boolean_result_id;
#endif
				std::shared_ptr<typename IfcEntityTypesT::IfcBooleanClippingResult> boolean_clipping_result =
					std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcBooleanClippingResult>(boolResult);
				if (boolean_clipping_result)
				{
#ifdef _DEBUG
					BLUE_LOG(trace) << "Processing IfcBooleanClippingResult #" << boolean_clipping_result->getId();
#endif
					typename IfcEntityTypesT::IfcBooleanOperator ifc_boolean_operator = boolean_clipping_result->Operator;
					typename IfcEntityTypesT::IfcBooleanOperand ifc_first_operand = boolean_clipping_result->FirstOperand;
					typename IfcEntityTypesT::IfcBooleanOperand ifc_second_operand = boolean_clipping_result->SecondOperand;

					/// Not needed since not optional nor pointers!
					//if (!ifc_boolean_operator || !ifc_first_operand || !ifc_second_operand)
					//{
					//	std::cout << ": invalid IfcBooleanOperator or IfcBooleanOperand" << std::endl;
					//	return;
					//}

					carve::csg::CSG::OP csg_operation = carve::csg::CSG::A_MINUS_B;
					if (ifc_boolean_operator == typename IfcEntityTypesT::IfcBooleanOperator::ENUM::ENUM_UNION)
					{
						csg_operation = carve::csg::CSG::UNION;
					}
					else if (ifc_boolean_operator == typename IfcEntityTypesT::IfcBooleanOperator::ENUM::ENUM_INTERSECTION)
					{
						csg_operation = carve::csg::CSG::INTERSECTION;
					}
					else if (ifc_boolean_operator == typename IfcEntityTypesT::IfcBooleanOperator::ENUM::ENUM_DIFFERENCE)
					{
						csg_operation = carve::csg::CSG::A_MINUS_B;
					}
					else
					{
						BLUE_LOG(error) << " invalid IfcBooleanOperator in IfcBooleanResult #" << boolResult->getId();
					}

					// convert the first operand
					std::shared_ptr<ItemData> first_operand_data(new ItemData());
					std::shared_ptr<ItemData> empty_operand;
					convertIfcBooleanOperand(ifc_first_operand, pos, first_operand_data, empty_operand);
					first_operand_data->createMeshSetsFromClosedPolyhedrons();

					// convert the second operand
					std::shared_ptr<ItemData> second_operand_data(new ItemData());
					convertIfcBooleanOperand(ifc_second_operand, pos, second_operand_data, first_operand_data);
					second_operand_data->createMeshSetsFromClosedPolyhedrons();

					// for every first operand polyhedrons, apply all second operand polyhedrons
					std::vector<std::shared_ptr<carve::mesh::MeshSet<3> > >::iterator it_first_operands;
					for (it_first_operands = first_operand_data->meshsets.begin(); it_first_operands != first_operand_data->meshsets.end(); ++it_first_operands)
					{
						std::shared_ptr<carve::mesh::MeshSet<3> >& first_operand_meshset = (*it_first_operands);

						std::vector<std::shared_ptr<carve::mesh::MeshSet<3> > >::iterator it_second_operands;
						for (it_second_operands = second_operand_data->meshsets.begin(); it_second_operands != second_operand_data->meshsets.end(); ++it_second_operands)
						{
							std::shared_ptr<carve::mesh::MeshSet<3> >& second_operand_meshset = (*it_second_operands);

							int id1 = 0;
							switch(ifc_first_operand.which()) {
							case 0:
								id1 = ifc_first_operand.get<0>().lock()->getId();
								break;
							case 1:
								id1 = ifc_first_operand.get<1>().lock()->getId();
								break;
							case 2:
								id1 = ifc_first_operand.get<2>().lock()->getId();
								break;
							case 3:
								id1 = ifc_first_operand.get<3>().lock()->getId();
								break;
							default:
								break;
							}

							int id2 = 0;
							switch(ifc_second_operand.which()) {
							case 0:
								id2 = ifc_second_operand.get<0>().lock()->getId();
								break;
							case 1:
								id2 = ifc_second_operand.get<1>().lock()->getId();
								break;
							case 2:
								id2 = ifc_second_operand.get<2>().lock()->getId();
								break;
							case 3:
								id2 = ifc_second_operand.get<3>().lock()->getId();
								break;
							default:
								break;
							}
							
							
							std::shared_ptr<carve::mesh::MeshSet<3> > result;
							bool csg_op_ok = computeCSG(first_operand_meshset.get(),
								second_operand_meshset.get(),
								csg_operation, id1, id2, result);

							if (csg_op_ok)
							{
								first_operand_meshset = result;
							}
						}
					}

					// now copy processed first operands to result input data
					std::copy(first_operand_data->meshsets.begin(), first_operand_data->meshsets.end(), std::back_inserter(itemData->meshsets));
				}
			}

			void convertIfcCsgPrimitive3D(
				const std::shared_ptr<typename IfcEntityTypesT::IfcCsgPrimitive3D>& csgPrimitive,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData)
			{
				std::shared_ptr<carve::input::PolyhedronData> polyhedron_data(new carve::input::PolyhedronData());
				double length_factor = UnitConvert()->getLengthInMeterFactor();

				// ENTITY IfcCsgPrimitive3D  ABSTRACT SUPERTYPE OF(ONEOF(IfcBlock, IfcRectangularPyramid, IfcRightCircularCone, IfcRightCircularCylinder, IfcSphere)
				
                                carve::math::Matrix primitive_placement_matrix = csgPrimitive->Position ?
                                    pos * placementConverter->convertIfcAxis2Placement3D(csgPrimitive->Position.lock()) :
                                    pos;


				std::shared_ptr<typename IfcEntityTypesT::IfcBlock> block =
					std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcBlock>(csgPrimitive);
				if (block)
				{
					double x_length = length_factor;
					double y_length = length_factor;
					double z_length = length_factor;

					if ((typename IfcEntityTypesT::IfcLengthMeasure)block->XLength)
					{
						x_length = (typename IfcEntityTypesT::IfcLengthMeasure)(block->XLength)*0.5*length_factor;
					}
					if ((typename IfcEntityTypesT::IfcLengthMeasure)block->YLength)
					{
						y_length = (typename IfcEntityTypesT::IfcLengthMeasure)(block->YLength)*0.5*length_factor;
					}
					if ((typename IfcEntityTypesT::IfcLengthMeasure)block->ZLength)
					{
						z_length = (typename IfcEntityTypesT::IfcLengthMeasure)(block->ZLength)*0.5*length_factor;
					}

					polyhedron_data->addVertex(primitive_placement_matrix *carve::geom::VECTOR(x_length, y_length, z_length));
					polyhedron_data->addVertex(primitive_placement_matrix *carve::geom::VECTOR(-x_length, y_length, z_length));
					polyhedron_data->addVertex(primitive_placement_matrix *carve::geom::VECTOR(-x_length, -y_length, z_length));
					polyhedron_data->addVertex(primitive_placement_matrix *carve::geom::VECTOR(x_length, -y_length, z_length));
					polyhedron_data->addVertex(primitive_placement_matrix *carve::geom::VECTOR(x_length, y_length, -z_length));
					polyhedron_data->addVertex(primitive_placement_matrix *carve::geom::VECTOR(-x_length, y_length, -z_length));
					polyhedron_data->addVertex(primitive_placement_matrix *carve::geom::VECTOR(-x_length, -y_length, -z_length));
					polyhedron_data->addVertex(primitive_placement_matrix *carve::geom::VECTOR(x_length, -y_length, -z_length));

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
					return;
				}

				std::shared_ptr<typename IfcEntityTypesT::IfcRectangularPyramid> rectangular_pyramid =
					std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcRectangularPyramid>(csgPrimitive);
				if (rectangular_pyramid)
				{
					double x_length = length_factor;
					double y_length = length_factor;
					double height = length_factor;

					if ((typename IfcEntityTypesT::IfcLengthMeasure) rectangular_pyramid->XLength)
					{
						x_length = (typename IfcEntityTypesT::IfcLengthMeasure)(rectangular_pyramid->XLength)*0.5*length_factor;
					}
					if ((typename IfcEntityTypesT::IfcLengthMeasure) rectangular_pyramid->YLength)
					{
						y_length = (typename IfcEntityTypesT::IfcLengthMeasure)(rectangular_pyramid->YLength)*0.5*length_factor;
					}
					if ((typename IfcEntityTypesT::IfcLengthMeasure) rectangular_pyramid->Height)
					{
						height = (typename IfcEntityTypesT::IfcLengthMeasure)(rectangular_pyramid->Height)*0.5*length_factor;
					}

					polyhedron_data->addVertex(primitive_placement_matrix*carve::geom::VECTOR(0, 0, height));
					polyhedron_data->addVertex(primitive_placement_matrix*carve::geom::VECTOR(x_length, -y_length, 0.0));
					polyhedron_data->addVertex(primitive_placement_matrix*carve::geom::VECTOR(-x_length, -y_length, 0.0));
					polyhedron_data->addVertex(primitive_placement_matrix*carve::geom::VECTOR(-x_length, y_length, 0.0));
					polyhedron_data->addVertex(primitive_placement_matrix*carve::geom::VECTOR(x_length, y_length, 0.0));

					polyhedron_data->addFace(1, 2, 3);
					polyhedron_data->addFace(3, 4, 1);
					polyhedron_data->addFace(0, 2, 1);
					polyhedron_data->addFace(0, 1, 4);
					polyhedron_data->addFace(0, 4, 3);
					polyhedron_data->addFace(0, 3, 2);

					itemData->closed_polyhedrons.push_back(polyhedron_data);
					return;
				}

				std::shared_ptr<typename IfcEntityTypesT::IfcRightCircularCone> right_circular_cone =
					std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcRightCircularCone>(csgPrimitive);
				if (right_circular_cone)
				{
					if (!right_circular_cone->Height)
					{
						std::cout << "IfcRightCircularCone: height not given" << std::endl;
						return;
					}
					if (!right_circular_cone->BottomRadius)
					{
						std::cout << "IfcRightCircularCone: radius not given" << std::endl;
						return;
					}

					double height = (typename IfcEntityTypesT::IfcLengthMeasure)(right_circular_cone->Height)*length_factor;
					double radius = (typename IfcEntityTypesT::IfcLengthMeasure)(right_circular_cone->BottomRadius)*length_factor;

					polyhedron_data->addVertex(primitive_placement_matrix*carve::geom::VECTOR(0.0, 0.0, height)); // top
					polyhedron_data->addVertex(primitive_placement_matrix*carve::geom::VECTOR(0.0, 0.0, 0.0)); // bottom center

					int numVerticesInCircle = GeomSettings()->getNumberOfVerticesForTessellation(radius);
					double d_angle = GeomSettings()->getAngleLength(radius);
					for (double angle = 0.; angle < 2*M_PI; angle += d_angle)
					{
						polyhedron_data->addVertex(primitive_placement_matrix*carve::geom::VECTOR(sin(angle)*radius, cos(angle)*radius, 0.0));
					}

					// outer shape
					for (int i = 0; i < numVerticesInCircle - 1; ++i)
					{
						polyhedron_data->addFace(0, i + 3, i + 2);
					}
					polyhedron_data->addFace(0, 2, numVerticesInCircle + 1);

					// bottom circle
					for (int i = 0; i < numVerticesInCircle - 1; ++i)
					{
						polyhedron_data->addFace(1, i + 2, i + 3);
					}
					polyhedron_data->addFace(1, numVerticesInCircle + 1, 2);

					itemData->closed_polyhedrons.push_back(polyhedron_data);
					return;
				}

				std::shared_ptr<typename IfcEntityTypesT::IfcRightCircularCylinder> right_circular_cylinder =
					std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcRightCircularCylinder>(csgPrimitive);
				if (right_circular_cylinder)
				{
					if (!right_circular_cylinder->Height)
					{
						std::cout << "IfcRightCircularCylinder: height not given" << std::endl;
						return;
					}

					if (!right_circular_cylinder->Radius)
					{
						std::cout << "IfcRightCircularCylinder: radius not given" << std::endl;
						return;
					}

					//carve::mesh::MeshSet<3> * cylinder_mesh = makeCylinder( slices, rad, height, primitive_placement_matrix);
					double height = (typename IfcEntityTypesT::IfcLengthMeasure)(right_circular_cylinder->Height)*length_factor;
					double radius = (typename IfcEntityTypesT::IfcLengthMeasure)(right_circular_cylinder->Radius)*length_factor;

					int slices = GeomSettings()->getNumberOfSegmentsForTessellation(radius);
					double rad = 0;

					double d_angle = GeomSettings()->getAngleLength(radius);
					for (double angle = 0.; angle < 2 * M_PI; angle += d_angle)
					{
						polyhedron_data->addVertex(primitive_placement_matrix*carve::geom::VECTOR(sin(angle)*radius, cos(angle)*radius, height));
						polyhedron_data->addVertex(primitive_placement_matrix*carve::geom::VECTOR(sin(angle)*radius, cos(angle)*radius, 0.0));
					}

					for (int i = 0; i < slices - 1; ++i)
					{
						polyhedron_data->addFace(0, i * 2 + 2, i * 2 + 4);		// top cap:		0-2-4	0-4-6		0-6-8
						polyhedron_data->addFace(1, i * 2 + 3, i * 2 + 5);		// bottom cap:	1-3-5	1-5-7		1-7-9
						polyhedron_data->addFace(i, i + 1, i + 3, i + 2);		// side
					}
					polyhedron_data->addFace(2 * slices - 2, 2 * slices - 1, 1, 0);		// side

					itemData->closed_polyhedrons.push_back(polyhedron_data);
					return;
				}

				std::shared_ptr<typename IfcEntityTypesT::IfcSphere> sphere =
					std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSphere>(csgPrimitive);
				if (sphere)
				{
					if (!sphere->Radius)
					{
						std::cout << "IfcSphere: radius not given" << std::endl;
						return;
					}

					double radius = (typename IfcEntityTypesT::IfcLengthMeasure)(sphere->Radius);

					// seen from the top, each ring is:
					//        \   |   /
					//         2- 1 -nvc
					//        / \ | / \
					//    ---3--- 0 ---7---
					//       \  / | \ /
					//         4- 5 -6
					//        /   |   \

					std::shared_ptr<carve::input::PolyhedronData> polyhedron_data(new carve::input::PolyhedronData());
					polyhedron_data->addVertex(pos*carve::geom::VECTOR(0.0, 0.0, radius)); // top

					const int nvc = GeomSettings()->getNumberOfSegmentsForTessellation(radius);
					const double d_horizontal_angle = GeomSettings()->getAngleLength(radius);
					const int num_vertical_edges = ceil(0.5 * nvc);
					double d_vertical_angle = M_PI / double(num_vertical_edges - 1);	// TODO: adapt to model size and complexity
					double vertical_angle = d_vertical_angle;

					for (int vertical = 1; vertical < num_vertical_edges - 1; ++vertical)
					{
						// for each vertical angle, add one horizontal circle
						double vertical_level = cos(vertical_angle)*radius;
						double radius_at_level = sin(vertical_angle)*radius;
						double horizontal_angle = 0;
						for (int i = 0; i < nvc; ++i)
						{
							polyhedron_data->addVertex(primitive_placement_matrix*carve::geom::VECTOR(sin(horizontal_angle)*radius_at_level, cos(horizontal_angle)*radius_at_level, vertical_level));
							horizontal_angle += d_horizontal_angle;
						}
						vertical_angle += d_vertical_angle;
					}
					polyhedron_data->addVertex(primitive_placement_matrix*carve::geom::VECTOR(0.0, 0.0, -radius)); // bottom

					// uppper triangle fan
					for (int i = 0; i < nvc - 1; ++i)
					{
						polyhedron_data->addFace(0, i + 2, i + 1);
					}
					polyhedron_data->addFace(0, 1, nvc);

					for (int vertical = 1; vertical < num_vertical_edges - 2; ++vertical)
					{
						int offset_inner = nvc * (vertical - 1) + 1;
						int offset_outer = nvc * vertical + 1;
						for (int i = 0; i < nvc - 1; ++i)
						{
							polyhedron_data->addFace(offset_inner + i, offset_inner + 1 + i, offset_outer + 1 + i, offset_outer + i);
						}
						polyhedron_data->addFace(offset_inner + nvc - 1, offset_inner, offset_outer, offset_outer + nvc - 1);

					}

					// lower triangle fan
					int last_index = (num_vertical_edges - 2)*nvc + 1;
					for (int i = 0; i < nvc - 1; ++i)
					{
						polyhedron_data->addFace(last_index, last_index - (i + 2), last_index - (i + 1));
					}
					polyhedron_data->addFace(last_index, last_index - 1, last_index - nvc);
					itemData->closed_polyhedrons.push_back(polyhedron_data);
					return;
				}
				throw oip::UnhandledException(csgPrimitive);
			}

			void convertIfcBooleanOperand(typename IfcEntityTypesT::IfcBooleanOperand& operand,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData,
				const std::shared_ptr<ItemData>& otherOperand)
			{
				// OPERAND is SELECT of
				/*
				class IfcBooleanResult;
				class IfcCsgPrimitive3D;
				class IfcHalfSpaceSolid;
				class IfcSolidModel;
				class IfcTessellatedFaceSet;
				*/
#ifdef _DEBUG
				BLUE_LOG(trace) << "Converting IfcBooleanOperand. Which: " << operand.which();
#endif
				double length_factor = UnitConvert()->getLengthInMeterFactor();
				std::shared_ptr<typename IfcEntityTypesT::IfcSolidModel> solid_model;// = nullptr;
				std::shared_ptr<typename IfcEntityTypesT::IfcHalfSpaceSolid> half_space_solid;// = nullptr;
				std::shared_ptr<typename IfcEntityTypesT::IfcBooleanResult> boolean_result;// = nullptr;
				std::shared_ptr<typename IfcEntityTypesT::IfcCsgPrimitive3D> csg_primitive3D;// = nullptr;

				switch (operand.which()) {
				case 0:
					solid_model = operand.get<EXPRESSReference<typename IfcEntityTypesT::IfcSolidModel>>().lock();
					break;
				case 1:
					half_space_solid = operand.get<EXPRESSReference<typename IfcEntityTypesT::IfcHalfSpaceSolid>>().lock();
					break;
				case 2: 
					boolean_result = operand.get<EXPRESSReference<typename IfcEntityTypesT::IfcBooleanResult>>().lock();
					break;
				case 3:
					csg_primitive3D = operand.get<EXPRESSReference<typename IfcEntityTypesT::IfcCsgPrimitive3D>>().lock();
					break;
				default:
					break;
				}

				if (solid_model)
				{
					convertIfcSolidModel(solid_model, pos, itemData);
					return;
				}
				
				if (half_space_solid)
				{
					//ENTITY IfcHalfSpaceSolid SUPERTYPE OF(ONEOF(IfcBoxedHalfSpace, IfcPolygonalBoundedHalfSpace))
					std::shared_ptr<typename IfcEntityTypesT::IfcSurface> base_surface = half_space_solid->BaseSurface.lock();
	
					// base surface
					std::shared_ptr<typename IfcEntityTypesT::IfcElementarySurface> elem_base_surface =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcElementarySurface>(base_surface);
					if (!elem_base_surface)
					{
						BLUE_LOG(warning) << "The base surface shall be an unbounded surface (subtype of IfcElementarySurface)";
						return;
					}
					std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D>& base_surface_pos = elem_base_surface->Position.lock();
					carve::geom::plane<3> base_surface_plane;
					carve::geom::vector<3> base_surface_position;
					carve::math::Matrix base_position_matrix(carve::math::Matrix::IDENT());
					if (base_surface_pos)
					{
						placementConverter->getPlane(base_surface_pos, base_surface_plane, base_surface_position, length_factor);
                                                base_position_matrix = placementConverter->convertIfcAxis2Placement3D(base_surface_pos);
					}

					// If the agreement flag is TRUE, then the subset is the one the normal points away from
					bool agreement = half_space_solid->AgreementFlag;
					if (!agreement)
					{
						base_surface_plane.negate();
					}

					std::shared_ptr<typename IfcEntityTypesT::IfcBoxedHalfSpace> boxed_half_space =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcBoxedHalfSpace>(half_space_solid);
					if (boxed_half_space)
					{
#ifdef _DEBUG
						BLUE_LOG(trace) << "Processing IfcBoxedHalfSpace #" << boxed_half_space->getId();
#endif
						std::shared_ptr<typename IfcEntityTypesT::IfcBoundingBox> bbox = boxed_half_space->Enclosure.lock();
						if (!bbox)
						{
							BLUE_LOG(error) << "IfcBoxedHalfSpace: Enclosure not given!";
							return;
						}

						if (!bbox->Corner || !bbox->XDim || !bbox->YDim || !bbox->ZDim)
						{
							BLUE_LOG(error) << "IfcBoxedHalfSpace: Enclosure not valid!";
							return;
						}
						typename IfcEntityTypesT::IfcLengthMeasure	bbox_x_dim = bbox->XDim;
						typename IfcEntityTypesT::IfcLengthMeasure	bbox_y_dim = bbox->YDim;
						typename IfcEntityTypesT::IfcLengthMeasure	bbox_z_dim = bbox->ZDim;

						carve::geom::vector<3> corner = placementConverter->convertIfcCartesianPoint(bbox->Corner);
						carve::math::Matrix box_position_matrix = pos * base_position_matrix*carve::math::Matrix::TRANS(corner);

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
						for (std::vector<carve::geom::vector<3> >::iterator it_points = polyhedron_data->points.begin(); it_points != polyhedron_data->points.end(); ++it_points)
						{
							carve::geom::vector<3> & poly_point = (*it_points);
							poly_point = box_position_matrix * poly_point;
						}

						return;
					}

					// check dimenstions of other operand
					double extrusion_depth = HALF_SPACE_BOX_SIZE;
					carve::geom::vector<3> other_operand_pos = base_surface_position;
					if (otherOperand)
					{
						carve::geom::aabb<3> aabb;
						otherOperand->createMeshSetsFromClosedPolyhedrons();
						for (int ii = 0; ii < otherOperand->meshsets.size(); ++ii)
						{
							std::shared_ptr<carve::mesh::MeshSet<3> >& meshset = otherOperand->meshsets[ii];

							if (!meshset)
							{
								BLUE_LOG(error) << "Meshset not given!";
								return;
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
						carve::geom::vector<3>& aabb_extent = aabb.extent;
						double max_extent = std::max(aabb_extent.x, std::max(aabb_extent.y, aabb_extent.z));
						extrusion_depth = 2.0*max_extent;
						other_operand_pos = aabb.pos;
					}

					std::shared_ptr<typename IfcEntityTypesT::IfcPolygonalBoundedHalfSpace> polygonal_half_space =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcPolygonalBoundedHalfSpace>(half_space_solid);
					if (polygonal_half_space)
					{
						// ENTITY IfcPolygonalBoundedHalfSpace 
						//	SUBTYPE OF IfcHalfSpaceSolid;
						//	Position	 :	IfcAxis2Placement3D;
						//	PolygonalBoundary	 :	IfcBoundedCurve;
#ifdef _DEBUG
						BLUE_LOG(trace) << "Processing IfcPolygonalBoundedHalfSpace #" << polygonal_half_space->getId();
#endif
						carve::math::Matrix boundary_position_matrix(carve::math::Matrix::IDENT());
						carve::geom::vector<3> boundary_plane_normal(carve::geom::VECTOR(0, 0, 1));
						carve::geom::vector<3> boundary_position;
						if (polygonal_half_space->Position)
						{
#ifdef _DEBUG
							BLUE_LOG(trace) << "Processing IfcPolygonalBoundedHalfSpace.Position: IfcAxis2Placement3D  #" << polygonal_half_space->Position.lock()->getId();
#endif
                                                        boundary_position_matrix = placementConverter->convertIfcAxis2Placement3D(polygonal_half_space->Position.lock());
							boundary_plane_normal = carve::geom::VECTOR(boundary_position_matrix._31, boundary_position_matrix._32, boundary_position_matrix._33);
							boundary_position = carve::geom::VECTOR(boundary_position_matrix._41, boundary_position_matrix._42, boundary_position_matrix._43);
#ifdef _DEBUG
							BLUE_LOG(trace) << "Processed IfcPolygonalBoundedHalfSpace.Position: IfcAxis2Placement3D  #" << polygonal_half_space->Position.lock()->getId();
#endif
						}

						// PolygonalBoundary is given in 2D
						std::vector<carve::geom::vector<2> > polygonal_boundary;
						std::vector<carve::geom::vector<2> > segment_start_points_2d;
						std::shared_ptr<typename IfcEntityTypesT::IfcCurve> bounded_curve = polygonal_half_space->PolygonalBoundary.lock();
						curveConverter->convertIfcCurve2D(bounded_curve, polygonal_boundary, segment_start_points_2d);
						ProfileConverterT<IfcEntityTypesT>::deleteLastPointIfEqualToFirst(polygonal_boundary);
						ProfileConverterT<IfcEntityTypesT>::simplifyPath(polygonal_boundary);

						if (otherOperand)
						{
#ifdef _DEBUG
							BLUE_LOG(trace) << "Found other IfcBooleanOperand.";
#endif
							extrusion_depth = extrusion_depth * 2.0;
						}
						std::stringstream err;
						std::vector<std::vector<carve::geom::vector<2> > > paths;
						paths.push_back(polygonal_boundary);
						std::shared_ptr<carve::input::PolyhedronData> poly_data(new carve::input::PolyhedronData);
						GeomUtils::extrude(paths, carve::geom::vector<3>(carve::geom::VECTOR(0, 0, extrusion_depth)), poly_data, err);

						const int num_poly_boundary_points = polygonal_boundary.size();
						if (poly_data->points.size() != 2 * num_poly_boundary_points)
						{
							BLUE_LOG(error) << "Problems in extrude: poly_data->points.size() != 2*polygonal_boundary.size()";
							return;
						}

						// apply position of PolygonalBoundary
						std::transform(poly_data->points.begin(), poly_data->points.end(), poly_data->points.begin(), [boundary_position_matrix](carve::geom3d::Vector& vertex)->carve::geom3d::Vector { return boundary_position_matrix * vertex; });
						//for (auto& vertex = poly_data->points)
						//{
						//	//carve::geom::vector<3>& vertex = it_points;
						//	vertex = boundary_position_matrix * vertex;
						//}


						// project to base surface
						for (int i_base_point = 0; i_base_point < poly_data->points.size(); ++i_base_point)
						{
							carve::geom::vector<3>& poly_point = poly_data->points[i_base_point];//(*it_points);

							// points below the base surface are projected into plane
							double distance_to_base_surface = carve::geom::distance(base_surface_plane, poly_point);
							carve::geom::vector<3> v;
							double t;
							carve::IntersectionClass intersect = carve::geom3d::rayPlaneIntersection(base_surface_plane, poly_point, poly_point + boundary_plane_normal, v, t);
							if (intersect > 0)
							{
								if (i_base_point < num_poly_boundary_points)
								{
									poly_point = v;
								}
								else
								{
									poly_point = v + boundary_plane_normal * extrusion_depth;
								}
							}
							else
							{
								BLUE_LOG(info) << "No intersection found!";
							}
						}

						// apply object coordinate system
						for (std::vector<carve::geom::vector<3> >::iterator it_points = poly_data->points.begin(); it_points != poly_data->points.end(); ++it_points)
						{
							carve::geom::vector<3>& poly_point = (*it_points);
							poly_point = pos * poly_point;
						}

						itemData->closed_polyhedrons.push_back(poly_data);


						//std::shared_ptr<carve::mesh::MeshSet<3> > meshset( poly_data->createMesh(carve::input::opts()) );
						//	renderMeshsetInDebugViewer( meshset.get(), osg::Vec4(1.0f, 0.5f, 0.0f, 1.0f), true );

						//	for( int ii=0; ii<otherOperand->meshsets.size(); ++ii )
						//	{
						//	std::shared_ptr<carve::mesh::MeshSet<3> >& meshset = otherOperand->meshsets[ii];
						//	renderMeshsetInDebugViewer( meshset.get(), osg::Vec4(0.8f, 0.0f, 1.0f, 1.0f), true );
						//	}


					}
					else
					{
						// else, its an unbounded half space solid, create simple box

						int var = 0;

						if (var == 0)
						{
							std::shared_ptr<carve::input::PolylineSetData> surface_data(new carve::input::PolylineSetData());
							faceConverter->convertIfcSurface(base_surface, carve::math::Matrix::IDENT(), surface_data);
							std::vector<carve::geom::vector<3>> base_surface_points = surface_data->points;

							if (base_surface_points.size() != 4)
							{
								BLUE_LOG(warning) << "Invalid IfcHalfSpaceSolid.BaseSurface #" << base_surface->getId();
								return;
							}
							// If the agreement flag is TRUE, then the subset is the one the normal points away from
							bool agreement = half_space_solid->AgreementFlag;
							if (!agreement)
							{
								std::reverse(base_surface_points.begin(), base_surface_points.end());
							}
							carve::geom::vector<3>  base_surface_normal = GeomUtils::computePolygonNormal(base_surface_points);

							carve::geom::vector<3>  half_space_extrusion_direction = -base_surface_normal;
							carve::geom::vector<3>  half_space_extrusion_vector = half_space_extrusion_direction * HALF_SPACE_BOX_SIZE;
							std::shared_ptr<carve::input::PolyhedronData> half_space_box_data(new carve::input::PolyhedronData());
							itemData->closed_polyhedrons.push_back(half_space_box_data);
							extrudeBox(base_surface_points, half_space_extrusion_vector, half_space_box_data);

							// apply object coordinate system
							for (std::vector<carve::geom::vector<3> >::iterator it_points = half_space_box_data->points.begin(); it_points != half_space_box_data->points.end(); ++it_points)
							{
								carve::geom::vector<3> & poly_point = (*it_points);
								poly_point = pos * poly_point;
							}
						}

						if (var == 1)
						{
							std::vector<carve::geom::vector<3> > box_base_points;
							box_base_points.push_back(base_position_matrix*carve::geom::VECTOR(extrusion_depth, extrusion_depth, 0.0));
							box_base_points.push_back(base_position_matrix*carve::geom::VECTOR(-extrusion_depth, extrusion_depth, 0.0));
							box_base_points.push_back(base_position_matrix*carve::geom::VECTOR(-extrusion_depth, -extrusion_depth, 0.0));
							box_base_points.push_back(base_position_matrix*carve::geom::VECTOR(extrusion_depth, -extrusion_depth, 0.0));

							carve::geom::vector<3>  half_space_extrusion_direction = -base_surface_plane.N;
							carve::geom::vector<3>  half_space_extrusion_vector = half_space_extrusion_direction * extrusion_depth;

							carve::geom::vector<3>  box_base_normal = GeomUtils::computePolygonNormal(box_base_points);
							double dot_normal = dot(box_base_normal, base_surface_plane.N);
							if (dot_normal > 0)
							{
								std::reverse(box_base_points.begin(), box_base_points.end());
							}

							std::shared_ptr<carve::input::PolyhedronData> half_space_box_data(new carve::input::PolyhedronData());
							itemData->closed_polyhedrons.push_back(half_space_box_data);
							extrudeBox(box_base_points, half_space_extrusion_vector, half_space_box_data);

							// apply object coordinate system
							for (std::vector<carve::geom::vector<3> >::iterator it_points = half_space_box_data->points.begin(); it_points != half_space_box_data->points.end(); ++it_points)
							{
								carve::geom::vector<3> & poly_point = (*it_points);
								poly_point = pos * poly_point;
							}
						}

						return;
					}
#ifdef _DEBUG
					BLUE_LOG(trace) << "Processed IfcHalfSpaceSolid #" << half_space_solid->getId();
#endif
					return;
				}
				
				if (boolean_result)
				{
					convertIfcBooleanResult(boolean_result, pos, itemData);
					return;
				}

				if (csg_primitive3D)
				{
					convertIfcCsgPrimitive3D(csg_primitive3D, pos, itemData);
					return;
				}

				BLUE_LOG(error) << "Unhandled IFC Representation: " << operand->classname();
			}

			void simplifyMesh(std::shared_ptr<carve::mesh::MeshSet<3>>& meshset)
			{
				bool rebuild = true;
				int num_vertices = meshset->vertex_storage.size();
				if (rebuild && num_vertices > 8)
				{
					retriangulateMeshSet(meshset);
				}
			}

			bool computeCSG(carve::mesh::MeshSet<3>* op1,
				carve::mesh::MeshSet<3>* op2,
				const carve::csg::CSG::OP operation,
				const int entity1, const int entity2,
				std::shared_ptr<carve::mesh::MeshSet<3>>& result)
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
							GeomSettings()->getCSGtype()));

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
					}
					catch (const std::out_of_range& oor)
					{
						isCSGComputationOk = false;
						BLUE_LOG(error) << "csg operation failed, id1 = " << entity1 << ", id2 = " << entity2 << ", " << oor.what();

					}
					catch (std::exception& e)
					{
						isCSGComputationOk = false;
						BLUE_LOG(error) << "csg operation failed, id1 = " << entity1 << ", id2 = " << entity2 << ", " << e.what();

					}
					catch (...)
					{
						isCSGComputationOk = false;
						std::cerr << "csg operation failed, id1 = " << entity1 << ", id2 = " << entity2	<< std::endl;
					}

					if (!result)
					{
						isCSGComputationOk = false;
					}
				}

				return isCSGComputationOk;
			}

			static void extrudeBox(const std::vector<carve::geom::vector<3> >& boundary_points,
				const carve::geom::vector<3>& extrusion_vector,
				std::shared_ptr<carve::input::PolyhedronData>& box_data)
			{
				box_data->addVertex(boundary_points[0]);
				box_data->addVertex(boundary_points[1]);
				box_data->addVertex(boundary_points[2]);
				box_data->addVertex(boundary_points[3]);
				box_data->addVertex(boundary_points[0] + extrusion_vector);
				box_data->addVertex(boundary_points[1] + extrusion_vector);
				box_data->addVertex(boundary_points[2] + extrusion_vector);
				box_data->addVertex(boundary_points[3] + extrusion_vector);
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

			static void retriangulateMeshSet(std::shared_ptr<carve::mesh::MeshSet<3>>& meshset)
			{
				//carve::poly::Polyhedron* poly = carve::polyhedronFromMesh(meshset, -1);
				//carve::mesh::MeshSet<3>* meshset_new = carve::meshFromPolyhedron(poly, -1);

				int num_vertices1 = meshset->vertex_storage.size();
				std::shared_ptr<carve::input::PolyhedronData> poly_data(new carve::input::PolyhedronData());
				std::map<double, std::map<double, std::map<double, int> > > existing_vertices_coords;
				std::map<double, std::map<double, std::map<double, int> > >::iterator vert_it;
				std::map<double, std::map<double, int> >::iterator it_find_y;
				std::map<double, int>::iterator it_find_z;
				std::map<int, int> map_merged_idx;
				double volume_check = 0;

				for (size_t ii = 0; ii < meshset->meshes.size(); ++ii)
				{
					carve::mesh::Mesh<3>* mesh = meshset->meshes[ii];
					volume_check += mesh->volume();
					std::vector<carve::mesh::Face<3>* >& vec_faces = mesh->faces;

					for (size_t i2 = 0; i2 < vec_faces.size(); ++i2)
					{
						carve::mesh::Face<3>* face = vec_faces[i2];
						std::vector<int> face_idx;

						carve::geom3d::Vector normal = face->plane.N;

						std::vector<carve::geom::vector<2> > verts2d;
						face->getProjectedVertices(verts2d);

						// check winding order
						//carve::geom3d::Vector normal_2d = GeomUtils::computePolygon2DNormal( verts2d );
						//if( normal_2d.z < 0 )
						//{
						//	std::reverse( verts2d.begin(), verts2d.end() );
						//}

						std::vector<carve::triangulate::tri_idx> triangulated;
						if (verts2d.size() > 3)
						{
							try
							{
								carve::triangulate::triangulate(verts2d, triangulated);
								carve::triangulate::improve(verts2d, triangulated);
							}
							catch (...)
							{
								std::cout //<< __FUNC__
									<< " carve::triangulate::incorporateHolesIntoPolygon failed " << std::endl;
								continue;
							}
						}
						else
						{
							triangulated.push_back(carve::triangulate::tri_idx(0, 1, 2));
						}

						// now insert points to polygon, avoiding points with same coordinates
						int i_vert = 0;
						carve::mesh::Edge<3>* edge = face->edge;
						do
						{
							const carve::geom::vector<3>& v = edge->vert->v;//verts3d[i]->v;
							edge = edge->next;

							//#ifdef ROUND_IFC_COORDINATES
							//							const double vertex_x = round(v.x*ROUND_IFC_COORDINATES_UP)*ROUND_IFC_COORDINATES_DOWN;
							//							const double vertex_y = round(v.y*ROUND_IFC_COORDINATES_UP)*ROUND_IFC_COORDINATES_DOWN;
							//							const double vertex_z = round(v.z*ROUND_IFC_COORDINATES_UP)*ROUND_IFC_COORDINATES_DOWN;
							//#else
							const double vertex_x = v.x;
							const double vertex_y = v.y;
							const double vertex_z = v.z;
							//#endif

														//  return a pair, with its member pair::first set to an iterator pointing to either the newly inserted element or to the element with an equivalent key in the map
							vert_it = existing_vertices_coords.insert(std::make_pair(vertex_x, std::map<double, std::map<double, int> >())).first;
							std::map<double, std::map<double, int> >& map_y_index = (*vert_it).second;

							it_find_y = map_y_index.insert(std::make_pair(vertex_y, std::map<double, int>())).first;
							std::map<double, int>& map_z_index = it_find_y->second;

							it_find_z = map_z_index.find(vertex_z);
							if (it_find_z != map_z_index.end())
							{
								// vertex already exists in polygon. remember its index for triangles
								int vertex_index = it_find_z->second;
								map_merged_idx[i_vert] = vertex_index;
							}
							else
							{
								int vertex_id = poly_data->addVertex(v);
								map_z_index[vertex_z] = vertex_id;
								map_merged_idx[i_vert] = vertex_id;
							}

							++i_vert;
						} while (edge != face->edge);

						for (size_t i = 0; i != triangulated.size(); ++i)
						{
							carve::triangulate::tri_idx triangle = triangulated[i];
							int a = triangle.a;
							int b = triangle.b;
							int c = triangle.c;

							int vertex_id_a = map_merged_idx[a];
							int vertex_id_b = map_merged_idx[b];
							int vertex_id_c = map_merged_idx[c];
							/*
							#ifdef _DEBUG
							const carve::poly::Vertex<3>& v_a = poly_data->getVertex(vertex_id_a);
							const carve::poly::Vertex<3>& v_b = poly_data->getVertex(vertex_id_b);

							double dx = v_a.v[0] - v_b.v[0];
							if( abs(dx) < 0.0000001 )
							{
							double dy = v_a.v[1] - v_b.v[1];
							if( abs(dy) < 0.0000001 )
							{
							double dz = v_a.v[2] - v_b.v[2];
							if( abs(dz) < 0.0000001 )
							{
							std::cerr << "abs(dx) < 0.00001 && abs(dy) < 0.00001 && abs(dz) < 0.00001\n";
							}
							}
							}
							#endif*/
							poly_data->addFace(vertex_id_a, vertex_id_b, vertex_id_c);
						}
					}
				}

				meshset = std::shared_ptr<carve::mesh::MeshSet<3> >(poly_data->createMesh(carve::input::opts()));

				double volume_check2 = 0;
				for (size_t i = 0; i < meshset->meshes.size(); ++i)
				{
					carve::mesh::Mesh<3>* mesh = meshset->meshes[i];
					volume_check2 += mesh->volume();
				}

				/*if( abs(volume_check - volume_check2) > 0.0001 )
				{
				std::cout << __FUNC__ << " volume check failed." << std::endl;
				}

				int num_vertices2 = meshset->vertex_storage.size();
				if( num_vertices1 != num_vertices2 )
				{
				std::cout << __FUNC__ << " num vertices check failed." << std::endl;
				}*/
			}

			void convertIfcSpecificSolidModel(const std::shared_ptr<typename IfcEntityTypesT::IfcSolidModel>& solidModel,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData)
			{
				std::cout << "Ifc-specific solid model " << solidModel->classname() << " not supported" << std::endl;
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
		//		std::vector<std::shared_ptr<emt::IfcBridgeEntityTypes::IfcProfileDef> >& vec_cross_sections_unordered = spine->CrossSections;
		//		std::vector<std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferencePlacement> >& vec_cross_section_positions_unordered = spine->CrossSectionPositions;
		//
		//		// copy cross sections
		//		std::vector<std::shared_ptr<emt::IfcBridgeEntityTypes::IfcProfileDef>>::iterator it_cross_sections;
		//		std::vector<std::shared_ptr<emt::IfcBridgeEntityTypes::IfcProfileDef>> vec_cross_sections = vec_cross_sections_unordered;
		//
		//		// copy placements
		//		std::vector<std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferencePlacement>>::iterator it_placements;
		//		std::vector<std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferenceCurvePlacement>> vec_cross_section_positions;
		//		std::vector<carve::geom::vector<3>> vecCurveAbscissas;
		//		for (it_placements = vec_cross_section_positions_unordered.begin(); it_placements != vec_cross_section_positions_unordered.end(); ++it_placements)
		//		{
		//			std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferencePlacement> reference_placement = (*it_placements);
		//
		//			std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferenceCurvePlacement> reference_curve_placement =
		//				std::dynamic_pointer_cast<emt::IfcBridgeEntityTypes::IfcReferenceCurvePlacement>(reference_placement);
		//
		//			if (reference_curve_placement)
		//			{
		//				vec_cross_section_positions.push_back(reference_curve_placement);
		//			}
		//		}
		//
		//		unsigned int num_cross_sections = vec_cross_sections.size();
		//		if (vec_cross_section_positions.size() < num_cross_sections)
		//		{
		//			num_cross_sections = vec_cross_section_positions.size();
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
		//			std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferenceCurvePlacement> reference_curve_placement = vec_cross_section_positions[i];
		//			double abscissa = reference_curve_placement->CurvilinearAbscissa;
		//
		//			for (unsigned int j = i + 1; j < num_cross_sections; ++j)
		//			{
		//				std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferenceCurvePlacement> other = vec_cross_section_positions[j];
		//				double abscissa_other = other->CurvilinearAbscissa;
		//
		//				if (abscissa_other < abscissa)
		//				{
		//					// reordering necessary
		//					std::shared_ptr<emt::IfcBridgeEntityTypes::IfcReferenceCurvePlacement> copy = vec_cross_section_positions[i];
		//					vec_cross_section_positions[i] = vec_cross_section_positions[j];
		//					vec_cross_section_positions[j] = copy;
		//
		//					std::shared_ptr<emt::IfcBridgeEntityTypes::IfcProfileDef> copy_profile = vec_cross_sections[i];
		//					vec_cross_sections[i] = vec_cross_sections[j];
		//					vec_cross_sections[j] = copy_profile;
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
		//					= std::dynamic_pointer_cast<emt::IfcBridgeEntityTypes::IfcArbitraryClosedProfileDef>(vec_cross_sections[k]);
		//
		//				const double curveAbcissa = vec_cross_section_positions[k]->CurvilinearAbscissa;
		//				const carve::geom::vector<3> refDirection =
		//					carve::geom::VECTOR(vec_cross_section_positions[k]->RefDirection->DirectionRatios[0],
		//						vec_cross_section_positions[k]->RefDirection->DirectionRatios[1],
		//						vec_cross_section_positions[k]->RefDirection->DirectionRatios[2]);
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
		//			std::shared_ptr<emt::IfcBridgeEntityTypes::IfcProfileDef> profile_def = vec_cross_sections[i];
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
		//				std::shared_ptr<emt::IfcBridgeEntityTypes::IfcProfileDef> profile_def2 = vec_cross_sections[i + 1];
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
		//				std::shared_ptr<emt::IfcBridgeEntityTypes::IfcProfileDef> profile_def2 = vec_cross_sections[i + 1];
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
