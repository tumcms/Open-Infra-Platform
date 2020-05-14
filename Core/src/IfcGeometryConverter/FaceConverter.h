/*
    Copyright (c) 2018 Technical University of Munich
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



#pragma once
#ifndef FACECONVERTER_H
#define FACECONVERTER_H

#include "CarveHeaders.h"

#include <memory>

#include "ConverterBase.h"

#include "CurveConverter.h"
#include "PlacementConverter.h"
#include "GeomUtils.h"
#include "GeometryInputData.h"
#include "PlacementConverter.h"

#include "BlueFramework/Core/Diagnostics/log.h"


namespace OpenInfraPlatform {
	namespace Core {
		namespace IfcGeometryConverter {
			class ItemData;

			template <
				class IfcEntityTypesT
			>
			class FaceConverterT : public ConverterBaseT<IfcEntityTypesT>
			{
			public:
				FaceConverterT(std::shared_ptr<GeometrySettings> geomSettings,
					std::shared_ptr<UnitConverter<IfcEntityTypesT>> unitConverter,
					std::shared_ptr<PlacementConverterT<IfcEntityTypesT>> pc,
					std::shared_ptr<CurveConverterT<IfcEntityTypesT>> cc)
					: 
					ConverterBaseT<IfcEntityTypesT>(geomSettings, unitConverter),
					placementConverter(pc),
					curveConverter(cc)
				{
				}

				virtual ~FaceConverterT()
				{
				}

				void convertIfcSurface(const std::shared_ptr<typename IfcEntityTypesT::IfcSurface>& surface,
					const carve::math::Matrix& pos,
					std::shared_ptr<carve::input::PolylineSetData>& polyline_data)
				{
					double length_factor = UnitConvert()->getLengthInMeterFactor();

					/*	Faceconverter.h
						For IFC4x1:

						IfcSurface

							IfcBoundedSurface						http://www.buildingsmart-tech.org/ifc/IFC4x1/final/html/schema/ifcgeometryresource/lexical/ifcboundedsurface.htm
								IfcBSplineSurface*
								IfcCurveBoundedPlane
								IfcCurveBoundedSurface*
								IfcRectangularTrimmedSurface*

							IfcElementarySurface					http://www.buildingsmart-tech.org/ifc/IFC4x1/final/html/schema/ifcgeometryresource/lexical/ifcelementarysurface.htm
								IfcCylindricalSurface*
								IfcPlane
								IfcSphericalSurface*
								IfcToroidalSurface*

							IfcSweptSurface							http://www.buildingsmart-tech.org/ifc/IFC4x1/final/html/schema/ifcgeometryresource/lexical/ifcsweptsurface.htm
								IfcSurfaceOfLinearExtrusion*
								IfcSurfaceOfRevolution*

							*: not implemented in FaceConverter.h

					*/

					// ************************************************************************************************************************	//
					//	IfcBoundedSurface SUPTYPE of IfcSurface																					//
					//	ABSTRACT SUPERTYPE of IfcBSplineSurface, IfcCurveBoundedPlane, IfcCurveBoundedSurface, IfcRectangularTrimmedSurface		//
					// ************************************************************************************************************************	//

					std::shared_ptr<typename IfcEntityTypesT::IfcBoundedSurface> bounded_surface = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcBoundedSurface>(surface);

					if(bounded_surface) {
						if(convertIfcBSplineSurface(bounded_surface, pos, polyline_data)) {
							return;
						}

						/*! \internal testing if the Cmake options to include internal comments works.
						*/

						// (1/4) IfcBSplineSurface SUBTYPE of IfcBoundedSurface
						std::shared_ptr<typename IfcEntityTypesT::IfcBSplineSurface> bspline_surface =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcBSplineSurface>(bounded_surface);

						if(bspline_surface) {
							// Get attributes 1-4.
							/*std::shared_ptr<typename IfcEntityTypesT::IfcInteger> u_degree =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcInteger>(bspline_surface);*/
							int u_degree = bspline_surface->UDegree;
							/*std::shared_ptr<typename IfcEntityTypesT::IfcInteger> v_degree =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcInteger>(bspline_surface);*/
							int v_degree = bspline_surface->VDegree;
							/*std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> control_point_list =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianPoint>(bspline_surface);*/		// TO DO: next level (IfcCoordinates: IfcLengthMeasure)
							auto vec_control_point_list_list = bspline_surface->ControlPointsList;
							for(auto& it_control_point_list : vec_control_point_list_list) {
								std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>> vec_control_point_list;
								std::shared_ptr<ItemData> input_data_cpl_set(new ItemData);

								vec_control_point_list.resize(it_control_point_list.size());
								std::transform(it_control_point_list.begin(),
									it_control_point_list.end(),
									vec_control_point_list.begin(),
									[](EXPRESSReference<typename IfcEntityTypesT::IfcCartesianPoint> it) { return it.lock(); });

							}
							/*std::shared_ptr<typename IfcEntityTypesT::IfcBSplineSurfaceForm> surface_form =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcBSplineSurfaceForm>(bspline_surface);*/	// TO DO: next level (enum: PLANE_SURF, CYLINDRICAL_SURF, CONICAL_SURF, SPHERICAL_SURF, TOROIDAL_SURF, SURF_OF_REVOLUTION, RULED_SURF, GENERALISED_CONE, QUADRIC_SURF, SURF_OF_LINEAR_EXTRUSION, UNSPECIFIED)
							typename IfcEntityTypesT::IfcBSplineSurfaceForm surface_form = bspline_surface->SurfaceForm;

							// Get attributes 5-7. For information only.
							/*std::shared_ptr<typename IfcEntityTypesT::IfcLogical> u_closed =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcLogical>(bspline_surface);*/
							typename IfcEntityTypesT::IfcLogical u_closed = bspline_surface->UClosed;
							typename IfcEntityTypesT::IfcLogical v_closed = bspline_surface->VClosed;
							typename IfcEntityTypesT::IfcLogical self_intersect = bspline_surface->SelfIntersect;

							// TODO: implement		// Interpret values and calculate.


							// IfcBSplineSurfaceWithKnots SUBTYPE of IfcBSplineSurface
							std::shared_ptr<typename IfcEntityTypesT::IfcBSplineSurface> bspline_knots = // bspline_surface zu bspline_knots
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcBSplineSurface>(bounded_surface);

							if(bspline_knots) {
								// Get attributes 8-12.
								// TODO: implement		// Interpret values and calculate.
							}
						}

						// (2/4) IfcCurveBoundedPlane SUBTYPE OF IfcBoundedSurface.
						if(std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCurveBoundedPlane>(bounded_surface)) {
							std::shared_ptr<typename IfcEntityTypesT::IfcCurveBoundedPlane> curve_bounded_plane =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCurveBoundedPlane>(bounded_surface);

							carve::math::Matrix curve_bounded_plane_matrix(pos);

							// Get basis surface, outer boundary and inner boundaries.
							std::shared_ptr<typename IfcEntityTypesT::IfcPlane>& basis_surface = curve_bounded_plane->BasisSurface.lock();

							if(basis_surface) {
								// Get basis surface position.
								std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D>& basis_surface_placement = basis_surface->Position.lock();

								if(basis_surface_placement) {
									curve_bounded_plane_matrix = pos * placementConverter->convertIfcAxis2Placement3D(basis_surface_placement);;
								}
							}

							std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& outer_boundary = curve_bounded_plane->OuterBoundary.lock();
							if(outer_boundary) {
								// TO DO: implement
							}

							std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCurve>> vec_inner_boundaries;
							vec_inner_boundaries.resize(curve_bounded_plane->InnerBoundaries.size());
							std::transform(
								curve_bounded_plane->InnerBoundaries.begin(),
								curve_bounded_plane->InnerBoundaries.end(),
								vec_inner_boundaries.begin(),
								[](auto& it) { return it.lock(); }
							);
							for(unsigned int i = 0; i < vec_inner_boundaries.size(); ++i) {
								std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& inner_curve = vec_inner_boundaries[i];
							}
#ifdef _DEBUG
							std::cout << "Warning\t| IfcCurveBoundedPlane not implemented." << std::endl;
#endif
						}

						// (3/4) IfcCurveBoundedSurface SUBTYPE of IfcBoundedSurface.
						std::shared_ptr<typename IfcEntityTypesT::IfcCurveBoundedSurface> curve_bounded_surface =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCurveBoundedSurface>(bounded_surface);

						if(curve_bounded_surface) {
							// Get basis surface, boundaries and implicit outer.
							/*std::shared_ptr<typename IfcEntityTypesT::IfcSurface> basis_surface =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSurfacePlane>(curve_bounded_surface);*/
							std::shared_ptr<typename IfcEntityTypesT::IfcSurface> basis_surface = curve_bounded_surface->BasisSurface.lock();
							/*std::shared_ptr<typename IfcEntityTypesT::IfcBoundaryCurve> boundaries =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcBoundaryCurve>(curve_bounded_surface);*/
								// std::shared_ptr<typename IfcEntityTypesT::IfcBoundaryCurve> boundaries = curve_bounded_surface->Boundaries;

							std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcBoundaryCurve>> vec_boundaries;

							vec_boundaries.resize(curve_bounded_surface->Boundaries.size());
							std::transform(
								curve_bounded_surface->Boundaries.begin(), curve_bounded_surface->Boundaries.end(), vec_boundaries.begin(), [](auto& it) { return it.lock(); });
							// std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> control_point_list = -bspline_surface->ControlPointsList;
							/*std::shared_ptr<typename IfcEntityTypesT::IfcBoolean> implicit_outer =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcBoolean>(curve_bounded_surface);*/
							bool implicit_outer = curve_bounded_surface->ImplicitOuter;

							// TODO: implement		// Interpret values and calculate.

						}
						// (4/4) IfcRectangularTrimmedSurface SUBTYPE of IfcBoundedSurface.
						else if(std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcRectangularTrimmedSurface>(bounded_surface)) {
							std::shared_ptr<typename IfcEntityTypesT::IfcRectangularTrimmedSurface> rectangular_trimmed_surface =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcRectangularTrimmedSurface>(bounded_surface);
							// Get attributes 1-7.
							std::shared_ptr<typename IfcEntityTypesT::IfcSurface>& basis_surface = rectangular_trimmed_surface->BasisSurface.lock();
							if(basis_surface) {
								convertIfcSurface(basis_surface, pos, polyline_data);
							}
							/*
							typename IfcEntityTypesT::IfcParameterValue& u1 = rectangular_trimmed_surface->m_U1;
							typename IfcEntityTypesT::IfcParameterValue& v1 = rectangular_trimmed_surface->m_V1;
							typename IfcEntityTypesT::IfcParameterValue& u2 = rectangular_trimmed_surface->m_U2;
							typename IfcEntityTypesT::IfcParameterValue& v2 = rectangular_trimmed_surface->m_V2;
							typename IfcEntityTypesT::IfcBoolean& u_sense = *(rectangular_trimmed_surface->m_Usense);
							typename IfcEntityTypesT::IfcBoolean& v_sense = *(rectangular_trimmed_surface->m_Vsense);
							*/
							double u1 = rectangular_trimmed_surface->U1;
							double v1 = rectangular_trimmed_surface->V1;
							double u2 = rectangular_trimmed_surface->U2;
							double v2 = rectangular_trimmed_surface->V2;
							bool u_sense = rectangular_trimmed_surface->Usense;
							bool v_sense = rectangular_trimmed_surface->Vsense;

							// TODO: implement		// Interpret values and calculate.
#ifdef _DEBUG
							std::cout << "Warning\t| IfcRectangularTrimmedSurface not implemented." << std::endl;
#endif
						}
						return;
					}

					// ************************************************************************************************************************	//
					//	IfcElementarySurface SUPTYPE of IfcSurface																				//
					//	ABSTRACT SUPERTYPE of IfcCylindricalSurface, IfcPlane, IfcSphericalSurface, IfcToroidalSurface							//
					// ************************************************************************************************************************	//

					std::shared_ptr<typename IfcEntityTypesT::IfcElementarySurface> elementary_surface =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcElementarySurface>(surface);

					if(elementary_surface) {
						// Get position.
						std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D>& elementary_surface_placement = elementary_surface->Position.lock();

						carve::math::Matrix elementary_surface_matrix(pos);
						if(elementary_surface_placement) {
							elementary_surface_matrix = pos * placementConverter->convertIfcAxis2Placement3D(elementary_surface_placement);
						}

						// (1/4) IfcCylindricalSurface SUBTYPE of IfcElementarySurface
						std::shared_ptr<typename IfcEntityTypesT::IfcCylindricalSurface> cylindrical_surface =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCylindricalSurface>(elementary_surface);

						if(cylindrical_surface) {
							// Get radius.
							/*std::shared_ptr<typename IfcEntityTypesT::IfcPositiveLengthMeasure>& cylindrical_radius =
								cylindrical_surface->Radius;*/
							double cylindrical_radius = cylindrical_surface->Radius;
							// TODO: implement		// Interpret values and calculate.
						}

						// (2/4) IfcPlane SUBTYPE of IfcElementarySurface
						std::shared_ptr<typename IfcEntityTypesT::IfcPlane> elementary_surface_plane =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcPlane>(elementary_surface);

						if(elementary_surface_plane) {
							//  1----0     create big rectangular plane
							//  |    |     ^ y
							//  |    |     |
							//  2----3     ---> x
							{
								double plane_span = HALF_SPACE_BOX_SIZE;
								polyline_data->beginPolyline();
								polyline_data->addVertex(elementary_surface_matrix * carve::geom::VECTOR(plane_span, plane_span, 0.0));
								polyline_data->addVertex(elementary_surface_matrix * carve::geom::VECTOR(-plane_span, plane_span, 0.0));
								polyline_data->addVertex(elementary_surface_matrix * carve::geom::VECTOR(-plane_span, -plane_span, 0.0));
								polyline_data->addVertex(elementary_surface_matrix * carve::geom::VECTOR(plane_span, -plane_span, 0.0));

								polyline_data->addPolylineIndex(0);
								polyline_data->addPolylineIndex(1);
								polyline_data->addPolylineIndex(2);
								polyline_data->addPolylineIndex(3);
							}
							return;
						}

						// (3/4) IfcSphericalPlane SUBTYPE of IfcElementarySurface
						std::shared_ptr<typename IfcEntityTypesT::IfcSphericalSurface> spherical_surface =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSphericalSurface>(elementary_surface);

						if(spherical_surface) {
							// Get radius.
							/*std::shared_ptr<typename IfcEntityTypesT::IfcPositiveLengthMeasure>& spherical_radius =
								spherical_surface->m_Radius;*/

							double spherical_radius = spherical_surface->Radius;

							// TODO: implement		// Interpret values and calculate.
						}

						// (4/4) IfcToroidalSurface SUBTYPE of IfcElementarySurface
						std::shared_ptr<typename IfcEntityTypesT::IfcToroidalSurface> toroidal_surface =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcToroidalSurface>(elementary_surface);

						if(toroidal_surface) {
							// Get major and minor radius.
							/*std::shared_ptr<typename IfcEntityTypesT::IfcPositiveLengthMeasure>& major_radius =
								toroidal_surface->m_MajorRadius;*/	// TODO: Check member name
							double major_radius = toroidal_surface->MajorRadius; // TODO: erledigt member name passt
							/*std::shared_ptr<typename IfcEntityTypesT::IfcPositiveLengthMeasure>& minor_radius =
								toroidal_surface->m_MinorRadius;*/	// TODO: Check member name
							double minor_radius = toroidal_surface->MinorRadius; // TODO: erledigt member name passt
																				 // TODO: formal proposition: major_radius > minor_radius

							// TODO: implement		// Interpret values and calculate.
						}

						throw oip::UnhandledException(surface);
					}

					// ************************************************************************************************************************	//
					//	IfcSweptSurface SUPTYPE of IfcSurface																					//
					//	ABSTRACT SUPERTYPE of IfcSurfaceOfLinearExtrusion, IfcSurfaceOfRevolution												//
					// ************************************************************************************************************************	//

					std::shared_ptr<typename IfcEntityTypesT::IfcSweptSurface> swept_surface = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSweptSurface>(surface);
					if(std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSweptSurface>(surface)) {
						// Get swept curve and position.
						std::shared_ptr<typename IfcEntityTypesT::IfcProfileDef>& swept_surface_profile = swept_surface->SweptCurve.lock();
						std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D> swept_surface_placement = nullptr;
						if(swept_surface->Position) {
							EXPRESSReference<typename IfcEntityTypesT::IfcAxis2Placement3D> ref = swept_surface->Position;
							swept_surface_placement = ref.lock();
						}
						else {
							BLUE_LOG(warning) << "#" << swept_surface->getId() << " IfcSweptSurface without placement found.";
						}

						carve::math::Matrix swept_surface_matrix(pos);
						if(swept_surface_placement) {
							swept_surface_matrix = pos * placementConverter->convertIfcAxis2Placement3D(swept_surface_placement);
						}

						// (1/2) IfcSurfaceOfLinearExtrusion SUBTYPE of IfcSweptSurface
						std::shared_ptr<typename IfcEntityTypesT::IfcSurfaceOfLinearExtrusion> linear_extrusion =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSurfaceOfLinearExtrusion>(swept_surface);

						if(linear_extrusion) {
							// Get extrude direction and depth.
							std::shared_ptr<typename IfcEntityTypesT::IfcDirection>& linear_extrusion_direction = linear_extrusion->ExtrudedDirection.lock();
							double linear_extrusion_depth = linear_extrusion->Depth;

							// TODO: implement		// Interpret values and calculate.
#ifdef _DEBUG
							std::cout << "Warning\t| IfcSurfaceOfLinearExtrusion not implemented." << std::endl;
#endif
							return;
						}

						// (2/2) IfcSurfaceOfRevolution SUBTYPE of IfcSweptSurface
						std::shared_ptr<typename IfcEntityTypesT::IfcSurfaceOfRevolution> surface_of_revolution =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSurfaceOfRevolution>(swept_surface);

						if(surface_of_revolution) {
							// Get axis position.
							std::shared_ptr<typename IfcEntityTypesT::IfcAxis1Placement>& axis_position =
								surface_of_revolution->AxisPosition.lock(); // TODO: check member name erledigt

	  // TODO: implement		// Interpret values and calculate.
#ifdef _DEBUG
							std::cout << "Warning\t| IfcSurfaceOfRevolution not implemented." << std::endl;
#endif
							return;
						}

						throw oip::UnhandledException(surface);
					}
					throw oip::UnhandledException(surface);
				}

				// TODO: What is happening here?
				void convertIfcFaceList(const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcFace>>& faces,
					const carve::math::Matrix& pos,
					std::shared_ptr<ItemData> item_data)
				{
#ifdef _DEBUG
					BLUE_LOG(trace) << "Converting IfcFaceList. Size:" << faces.size();
#endif
					// carve polygon of the converted face list
					std::shared_ptr<carve::input::PolyhedronData> polygon(new carve::input::PolyhedronData());
					// contains polygon indices of vertices (x,y,z converted to string)
					std::map<std::string, uint32_t> polygonIndices;

					// loop through all faces
					for(auto it = faces.cbegin(); it != faces.cend(); ++it) {
						std::shared_ptr<typename IfcEntityTypesT::IfcFace> face = (*it);

						if(!convertIfcFace(face, pos, polygon, polygonIndices)) {
							std::stringstream text;
							text << "IFC Face convertion failed with faces #" << faces.at(0)->getId() << "-" << faces.at(faces.size() - 1)->getId();

							throw std::exception(text.str().c_str());
						}
					}

					// IfcFaceList can be a closed or open shell,
					// so let the calling function decide where to put it
					item_data->open_or_closed_polyhedrons.push_back(polygon);
				}

				bool convertIfcFace(const std::shared_ptr<typename IfcEntityTypesT::IfcFace>& face,
					const carve::math::Matrix& pos,
					std::shared_ptr<carve::input::PolyhedronData> polygon,
					std::map<std::string, uint32_t>& polygonIndices)
				{
					// indicates if convertion has failed
					bool convertionFailed = false;

					// id of face in step file
					const uint32_t faceID = face->getId();
#ifdef _DEBUG
					BLUE_LOG(trace) << "Converting IfcFace #" << faceID;
#endif

					// all bound definitions of the face (normal bound or outer bound)
					/*std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcFaceBound>>& bounds = face->m_Bounds;*/
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcFaceBound>> bounds;
					bounds.resize(face->Bounds.size());
					std::transform(face->Bounds.begin(), face->Bounds.end(), bounds.begin(), [](auto& it) {return it.lock(); });
					// to triangulate the mesh, carve needs 2D polygons
					// we collect the data in 2D and 3D for every bound
					std::vector<std::vector<carve::geom2d::P2>> faceVertices2D;
					std::vector<std::vector<carve::geom::vector<3>>> faceVertices3D;

					// save polygon indices of merged vertices
					std::map<uint32_t, uint32_t> mergedIndices;

					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcFaceBound>> modBounds;
					modBounds.reserve(2);

					bool faceLoopReversed = false;

					// loop through all boundary definitions
					int boundID = -1;

					// if polygon has more than 3 vertices,
					// then we have to project polygon into 2D, so that carve can triangulate the mesh
					ProjectionPlane plane = UNDEFINED;

					// as carve expects outer boundary of face to be at first index,
					// outer boundary has index 0 and inner boundary has index 1
					for(auto it = bounds.cbegin(); it != bounds.cend(); ++it) {
						std::shared_ptr<typename IfcEntityTypesT::IfcFaceBound> bound = *it;

						std::shared_ptr<typename IfcEntityTypesT::IfcFaceOuterBound> outerBound = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcFaceOuterBound>(bound);

						if(outerBound) {
							modBounds.insert(modBounds.begin(), outerBound);
						}
						else {
							modBounds.push_back(bound);
						}
					}
					modBounds.shrink_to_fit();

					for(const auto& bound : modBounds) {
						boundID++;

						/*********************************************************************************/
						//	IfcLoop <- IfcEdgeLoop, IfcPolyLoop, IfcVertexLoop
						/*********************************************************************************/

						std::shared_ptr<typename IfcEntityTypesT::IfcLoop>& loop = bound->Bound.lock();
						/*typename IfcEntityTypesT::IfcBoolean& polyOrientation = *(bound->m_Orientation);*/
						bool polyOrientation = bound->Orientation;
						if(!loop) {
							BLUE_LOG(warning) << "FaceConverter Problem with Face #" << faceID << ": IfcLoop #" << loop->getId() << " no valid loop.";

							if(boundID == 0) {
								break;
							}
							else {
								continue;
							}
						}

						// collect all vertices of the current loop
						std::vector<carve::geom::vector<3>> loopVertices3D;
						curveConverter->convertIfcLoop(loop, loopVertices3D);

						for(auto& vertex : loopVertices3D) {
							vertex = pos * vertex;
						}

						if(loopVertices3D.size() < 3) {
							BLUE_LOG(warning) << "FaceConverter Problem with Face #" << faceID << ": IfcLoop #" << loop->getId() << " Number of vertices < 2.";

							if(boundID == 0) {
								break;
							}
							else {
								continue;
							}
						}

						// check for orientation and reverse vertices order if FALSE
						if(!polyOrientation) {
							std::reverse(loopVertices3D.begin(), loopVertices3D.end());
						}

						/*********************************************************************************/
						//	3 Vertices Triangle
						/*********************************************************************************/
						if(loopVertices3D.size() == 3) {
							std::vector<uint32_t> triangleIndices;
							triangleIndices.resize(3);

							int pointID = -1;
							for(const auto& vertex3D : loopVertices3D) {
								pointID++;

								// apply global transformation to vertex
								const carve::geom::vector<3> v = vertex3D;

								// set string id and search for existing vertex in polygon
								std::stringstream vertexString;
								vertexString << v.x << " " << v.y << " " << v.z;
								auto itFound = polygonIndices.find(vertexString.str());

								uint32_t index = 0;
								if(itFound != polygonIndices.end()) {
									index = itFound->second;
								}
								else {
									index = polygon->addVertex(v);
									polygonIndices[vertexString.str()] = index;
								}

								triangleIndices.push_back(index);

								mergedIndices[pointID] = index;
							}

							polygon->addFace(triangleIndices.at(0), triangleIndices.at(1), triangleIndices.at(2));

							// continue;
						}

						/*********************************************************************************/
						//	> 3 Vertices Triangle
						/*********************************************************************************/

						std::vector<carve::geom2d::P2> loopVertices2D;

						if(!convert3DPointsTo2D(boundID, plane, loopVertices2D, loopVertices3D, faceLoopReversed)) {
							convertionFailed = true;
							BLUE_LOG(warning) << "#" << faceID << "= IfcFace: loop could not be projected";
							continue;
						}

						if(loopVertices2D.size() < 3) {
							convertionFailed = true;
							BLUE_LOG(warning) << "#" << faceID << "= IfcFace: path_loop.size() < 3";
							continue;
						}

						// push back vertices to all faceVertices
						faceVertices2D.push_back(loopVertices2D);
						faceVertices3D.push_back(loopVertices3D);
					}

					// if no faceVertices were collected, no carve operations are required
					if(faceVertices2D.empty()) {
						return false;
					}

					// result after incorporating holes in polygons if defined
					std::vector<std::pair<size_t, size_t>> incorporatedIndices;
					// merged vertices after incorporating of holes
					std::vector<carve::geom2d::P2> mergedVertices2D;
					std::vector<carve::geom::vector<3>> mergedVertices3D;

					try {
						incorporatedIndices = carve::triangulate::incorporateHolesIntoPolygon(faceVertices2D);

						for(const auto& incorpIndex : incorporatedIndices) {
							size_t loopIndex = incorpIndex.first;
							size_t vertexIndex = incorpIndex.second;

							carve::geom2d::P2& point2D = faceVertices2D[loopIndex][vertexIndex];
							carve::geom::vector<3>& point3D = faceVertices3D[loopIndex][vertexIndex];

							// add vertices to merged results
							mergedVertices2D.push_back(point2D);
							mergedVertices3D.push_back(point3D);
						}

					}
					catch(std::exception e) // catch carve error if holes cannot be incorporated
					{
						convertionFailed = true;
						BLUE_LOG(error) << "convertIfcFaceList: #" << faceID << " = IfcFace: carve::triangulate::incorporateHolesIntoPolygon failed ";
						BLUE_LOG(error) << e.what();
						// continue;

						mergedVertices2D = faceVertices2D.at(0);
						mergedVertices3D = faceVertices3D.at(0);
					}

					triangulateFace(mergedVertices2D, mergedVertices3D, faceLoopReversed, polygon, polygonIndices);

					return !convertionFailed;
				}

				bool convert3DPointsTo2D(const int boundID,
					ProjectionPlane& plane,
					std::vector<carve::geom2d::P2>& loopVertices2D,
					std::vector<carve::geom::vector<3>>& loopVertices3D,
					bool& faceLoopReversed)
				{
					// compute normal of polygon
					carve::geom::vector<3> normal = GeomUtils::computePolygonNormal(loopVertices3D);

					if(boundID == 0) {
						const double nx = std::abs(normal.x);
						const double ny = std::abs(normal.y);
						const double nz = std::abs(normal.z);

						const double nMax = std::max(std::max(nx, ny), nz);

						if(nMax == nx) {
							plane = ProjectionPlane::YZ_PLANE;
						}
						else if(nMax == ny) {
							plane = ProjectionPlane::XZ_PLANE;
						}
						else if(nMax == nz) {
							plane = ProjectionPlane::XY_PLANE;
						}
						else {
							return false;
						}
					}

					// now collect all vertices in 2D
					//loopVertices2D.resize(loopVertices3D.size());

					for(const auto& vertex : loopVertices3D) {
						if(plane == ProjectionPlane::YZ_PLANE) {
							loopVertices2D.push_back(carve::geom::VECTOR(vertex.y, vertex.z));
						}

						else if(plane == ProjectionPlane::XZ_PLANE) {
							loopVertices2D.push_back(carve::geom::VECTOR(vertex.x, vertex.z));
						}

						else if(plane == ProjectionPlane::XY_PLANE) {
							loopVertices2D.push_back(carve::geom::VECTOR(vertex.x, vertex.y));
						}
						else {
							std::cout << "ERROR: plane is undefined, what??" << std::endl;
							return false;
						}
					}

					// check winding order of 2D polygon
					carve::geom3d::Vector normal2D = GeomUtils::computePolygon2DNormal(loopVertices2D);

					if(boundID == 0) {
						if(normal2D.z < 0) {
							std::reverse(loopVertices2D.begin(), loopVertices2D.end());
							std::reverse(loopVertices3D.begin(), loopVertices3D.end());
							faceLoopReversed = true;
						}
					}
					else {
						if(normal2D.z > 0) {
							std::reverse(loopVertices2D.begin(), loopVertices2D.end());
							std::reverse(loopVertices3D.begin(), loopVertices3D.end());
							// faceLoopReversed = true;
						}
					}

					return true;
				}

				void triangulateFace(const std::vector<carve::geom::vector<2>>& faceVertices2D,
					const std::vector<carve::geom::vector<3>>& faceVertices3D,
					const bool faceLoopReversed,
					std::shared_ptr<carve::input::PolyhedronData> polygon,
					std::map<std::string, uint32_t>& polygonIndices)
				{
					// indices after carve triangulation of merged vertices
					std::vector<carve::triangulate::tri_idx> triangulatedIndices;

					std::map<uint32_t, uint32_t> mergedIndices;

					// triangulate 2D polygon and improve triangulation by carve
					carve::triangulate::triangulate(faceVertices2D, triangulatedIndices);
					carve::triangulate::improve(faceVertices2D, triangulatedIndices);

					// add new vertices to polygon or get index of existing vertex
					for(uint32_t i = 0; i < faceVertices3D.size(); ++i) {
						const carve::geom::vector<3>& v = faceVertices3D[i];

						// set string id and search for existing vertex in polygon
						std::stringstream vertexString;
						vertexString << v.x << " " << v.y << " " << v.z;

						auto itFound = polygonIndices.find(vertexString.str());
						uint32_t index = 0;

						if(itFound != polygonIndices.end()) {
							index = itFound->second;
						}
						else {
							index = polygon->addVertex(v);
							polygonIndices[vertexString.str()] = index;
						}

						mergedIndices[i] = index;
					}

					// go through triangulated result and add new faces to polygon
					for(const auto& triangle : triangulatedIndices) {
						const uint32_t i0 = triangle.a;
						const uint32_t i1 = triangle.b;
						const uint32_t i2 = triangle.c;

						const uint32_t v0 = mergedIndices[i0];
						const uint32_t v1 = mergedIndices[i1];
						const uint32_t v2 = mergedIndices[i2];

						if(faceLoopReversed)
							polygon->addFace(v0, v2, v1);
						else
							polygon->addFace(v0, v1, v2);
					}
				}

				bool convertIfcBSplineSurface(const std::shared_ptr<typename IfcEntityTypesT::IfcBoundedSurface>& boundedSurface,
					const carve::math::Matrix& pos,
					std::shared_ptr<carve::input::PolylineSetData> polyline_data)
				{
					// all versions < IFC4 do not support IfcBSplineSurface entities
					return false;
				}

				void convertIfcAdvancedFaceList(const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcFace>>& faces,
					const carve::math::Matrix& pos,
					std::shared_ptr<ItemData> item_data,
					std::stringstream& strs_err)
				{
					// nothing to do here as it is not supported by older IFC versions (< IFC4)
				}

				void convertIfcCartesianPoint2DVector(const std::vector<std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>>>& points2D,
					std::vector<std::vector<carve::geom::vector<3>>>& loop2D) const
				{
					const double lengthFactor = UnitConvert()->getLengthInMeterFactor();
					const uint32_t numPointsY = points2D.size();
					loop2D.resize(numPointsY);

					for(unsigned int j = 0; j < numPointsY; ++j) {
						const uint32_t numPointsX = points2D[j].size();
						const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>>& points = points2D[j];
						for(unsigned int i = 0; i < numPointsX; ++i) {
							/*const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure>>& coords =
								points[i]->m_Coordinates;*/
							const std::vector<double>& coords = points[i]->Coordinates;
							if(coords.size() > 2) {
								/*double x = coords[0]->m_value * lengthFactor;
								double y = coords[1]->m_value * lengthFactor;
								double z = coords[2]->m_value * lengthFactor;
								*/
								double x = coords[0] * lengthFactor;
								double y = coords[1] * lengthFactor;
								double z = coords[2] * lengthFactor;
								loop2D[j].push_back(carve::geom::VECTOR(x, y, z));
							}
							else if(coords.size() > 1) {
								double x = coords[0] * lengthFactor;
								double y = coords[1] * lengthFactor;

								loop2D[j].push_back(carve::geom::VECTOR(x, y, 0.0));
							}
							else {
								std::cout << "convertIfcCartesianPointVector: ifc_pt->Coordinates.size() != 2" << std::endl;
							}
						}
					}
				}

			protected:

				std::shared_ptr<PlacementConverterT<IfcEntityTypesT>> placementConverter;
				std::shared_ptr<CurveConverterT<IfcEntityTypesT>> curveConverter;
			};

			// template<>
			// inline bool FaceConverterT<emt::Ifc4EntityTypes, OpenInfraPlatform::Ifc4::UnitConverter>::
			//	convertIfcBSplineSurface(const std::shared_ptr<emt::Ifc4EntityTypes::IfcBoundedSurface>& boundedSurface,
			//	const carve::math::Matrix& pos,
			//	std::shared_ptr<carve::input::PolylineSetData> polylineData)
			//{
			//
			//	std::shared_ptr<emt::Ifc4EntityTypes::IfcBSplineSurface> bsplineSurface =
			//		std::dynamic_pointer_cast<emt::Ifc4EntityTypes::IfcBSplineSurface>(boundedSurface);
			//
			//	if (bsplineSurface)
			//	{
			//		std::vector<std::vector<std::shared_ptr<emt::Ifc4EntityTypes::IfcCartesianPoint>>>& points2D =
			//			bsplineSurface->m_ControlPointsList;
			//
			//		std::vector<std::vector<carve::geom::vector<3>>> splinePoints2D;
			//		splinePoints2D.resize(points2D.size());
			//		convertIfcCartesianPoint2DVector(points2D, splinePoints2D);
			//
			//		SplineConverterT<emt::Ifc4EntityTypes, OpenInfraPlatform::Ifc4::UnitConverter>::convertIfcBSplineSurface(bsplineSurface, splinePoints2D, polylineData);
			//
			//		return true;
			//	}
			//
			//	return false;
			//}
			//
			// template<>
			// inline void FaceConverterT<emt::Ifc4EntityTypes, OpenInfraPlatform::Ifc4::UnitConverter>::
			//	convertIfcAdvancedFaceList(const std::vector<std::shared_ptr<emt::Ifc4EntityTypes::IfcFace>>& faces,
			//	const carve::math::Matrix& pos,
			//	std::shared_ptr<ItemData> item_data,
			//	std::stringstream& strs_err)
			//{
			//	// indicates if convertion has failed
			//	//bool convertionFailed = false;
			//	// carve polygon of the converted face list
			//	std::shared_ptr<carve::input::PolyhedronData> polygon(new carve::input::PolyhedronData());
			//	// contains polygon indices of vertices (x,y,z converted to string)
			//	std::map<std::string, uint32_t> polygonIndices;
			//
			//	for (auto it = faces.cbegin(); it != faces.cend(); ++it)
			//	{
			//		std::shared_ptr<emt::Ifc4EntityTypes::IfcFace> face = (*it);
			//
			//		std::shared_ptr<emt::Ifc4EntityTypes::IfcAdvancedFace> advancedFace =
			//			std::dynamic_pointer_cast<emt::Ifc4EntityTypes::IfcAdvancedFace>(face);
			//
			//		if (!advancedFace)
			//		{
			//			strs_err << "Invalid advanced brep as face #" << face->getId() << " is not of type IfcAdvancedBrep" << std::endl;
			//			continue;
			//		}
			//
			//		std::shared_ptr<emt::Ifc4EntityTypes::IfcSurface>& faceSurface = advancedFace->m_FaceSurface;
			//
			//		std::shared_ptr<emt::Ifc4EntityTypes::IfcPlane> plane =
			//			std::dynamic_pointer_cast<emt::Ifc4EntityTypes::IfcPlane>(faceSurface);
			//
			//		if (plane)
			//		{
			//			if (!convertIfcFace(face, pos, polygon, polygonIndices, strs_err))
			//			{
			//
			//				std::stringstream text;
			//				text << "IFC Face convertion failed with faces #"
			//					<< faces.at(0)->getId() << "-" << faces.at(faces.size() - 1)->getId();
			//
			//				throw std::exception(text.str().c_str());
			//			}
			//
			//			// IfcFaceList can be a closed or open shell,
			//			// so let the calling function decide where to put it
			//			item_data->closed_polyhedrons.push_back(polygon);
			//		}
			//		else
			//		{
			//			std::shared_ptr<emt::Ifc4EntityTypes::IfcBSplineSurface> bsplineSurface =
			//				std::dynamic_pointer_cast<emt::Ifc4EntityTypes::IfcBSplineSurface>(faceSurface);
			//
			//			if (!bsplineSurface)
			//			{
			//				std::cout << "ERROR\t| IfcAdvancedFace surface type " << faceSurface->classname() << " not supported or tested, yet" << std::endl;
			//				continue;
			//			}
			//
			//			std::shared_ptr<carve::input::PolylineSetData> polylineData(new carve::input::PolylineSetData());
			//			convertIfcSurface(faceSurface, pos, polylineData);
			//
			//			const size_t vertexCount = polylineData->getVertexCount();
			//
			//			const size_t globalIndexCount = polygon->getVertexCount();
			//
			//			for (unsigned int k = 0; k < vertexCount; ++k)
			//			{
			//				polygon->addVertex(polylineData->getVertex(k));
			//			}
			//
			//			for (const auto& line : polylineData->polylines)
			//			{
			//				std::vector<int> indices = line.second;
			//
			//				if (indices.size() != 4)
			//				{
			//					std::cout << "ERROR\t| Polyline face vertex size is invalid" << std::endl;
			//					continue;
			//				}
			//
			//				polygon->addFace(indices[0] + globalIndexCount, indices[1] + globalIndexCount, indices[3] + globalIndexCount);
			//				polygon->addFace(indices[3] + globalIndexCount, indices[1] + globalIndexCount, indices[2] + globalIndexCount);
			//			}
			//
			//			item_data->closed_polyhedrons.push_back(polygon);
			//
			//			// Maybe draw outlines (polylines) of surfaces, as well
			//			//item_data->polylines.push_back(polylineData);
			//		}
			//	}
			//}
		} // namespace IfcGeometryConverter
	} // end namespace Core
} // namespace OpenInfraPlatform

#endif
