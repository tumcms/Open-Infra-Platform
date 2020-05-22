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
			
			/*! \brief Converter functionality for \c IfcSurfaces's subtypes.
			*
         	* This class includes converter functions for
            * \c IfcBoundedSurface and its subtypes,
            * \c IfcElementarySurface and its subtypes and
          	* \c IfcSweptSurface.	
            *
            * \param IfcEntityTypesT The IFC version templates
            */
			
			template <
				class IfcEntityTypesT
			>
				class FaceConverterT : public ConverterBaseT<IfcEntityTypesT>
			{
			public:

				//! Constructor
				FaceConverterT(EXPRESSReference<GeometrySettings> geomSettings,
					EXPRESSReference<UnitConverter<IfcEntityTypesT>> unitConverter,
					EXPRESSReference<PlacementConverterT<IfcEntityTypesT>> pc,
					EXPRESSReference<CurveConverterT<IfcEntityTypesT>> cc)
					:
					ConverterBaseT<IfcEntityTypesT>(geomSettings, unitConverter),
					placementConverter(pc),
					curveConverter(cc)
					{
					}

				//! Virtual destructor
				virtual ~FaceConverterT()
				{
				}

				// WHERE to put length factor?		
				double lengthFactor = UnitConvert()->getLengthInMeterFactor();

				/*! \brief Converts \c IfcSurface to a according to subtype.
					\param		surface	\c IfcSurface entity to be interpreted.
					\param		pos
					\param		polylineData
					\return
					\note		The \c IfcSurface subtypes are \c IfcBoundedSurface,  \c IfcElementarySurface and  \c IfcSweptSurface.
				*/

				void convertIfcSurface(const EXPRESSReference<typename IfcEntityTypesT::IfcSurface>& surface,
					const carve::math::Matrix& pos,
					EXPRESSReference<carve::input::PolylineSetData>& polylineData) {

					// (1/3) IfcBoundedSurface SUBTYPE of IfcSurface
					if (surface.isOfType<typename IfcEntityTypesT::IfcBoundedSurface>()) {
						return convertIfcBoundedSurface(surface.as<typename IfcEntityTypesT::IfcBoundedSurface(), pos, polylineData);
					}

					// (2/3) IfcElementarySurface SUBTYPE of IfcSurface
					if (surface.isOfType<typename IfcEntityTypesT::IfcElementarySurface>()) {
						return convertIfcElementarySurface(surface.as<typename IfcEntityTypesT::IfcElementarySurface(), pos, polylineData);
					}

					// (3/3) IfcSweptSurface SUBTYPE of IfcSurface
					if (surface.isOfType<typename IfcEntityTypesT::IfcSweptSurface>()) {
						return convertIfcSweptSurface(surface.as<typename IfcEntityTypesT::IfcSweptSurface(), pos, polylineData);
					}
				}

				//--------------------------------------------------------------------------------------------
				// IfcBoundedSurface
				//--------------------------------------------------------------------------------------------

					/*! \brief  Converts \c IfcBoundedSurface by calling the conversion function according to subtype.
					\param		surface	\c IfcBoundedSurface entity to be interpreted.
					\param		pos
					\param		polylineData
					\return
					\note		The \c IfcBoundedSurface subtypes are: \c IfcBSplineSurface, \c IfcCurveBoundedPlane, \c IfcCurveBoundedSurface and \c IfcRectangularTrimmedSurface.
					*/

				void convertIfcBoundedSurface(const EXPRESSReference<typename IfcEntityTypesT::IfcBoundedSurface>& surface,
					const carve::math::Matrix& pos,
					EXPRESSReference<carve::input::PolylineSetData>& polylineData) {

					// (1/4) IfcBSplineSurface SUBTYPE of IfcBoundedSurface
					if (surface.isOfType<typename IfcEntityTypesT::IfcBSplineSurface>()) {
						return convertIfcBSplineSurface(surface.as<typename IfcEntityTypesT::IfcBSplineSurface>(), pos, polylineData);
					}

					// (2/4) IfcCurveBoundedPlane SUBTYPE OF IfcBoundedSurface.
					else if (surface.isOfType<typename IfcEntityTypesT::IfcCurveBoundedPlane>()) {
						return convertIfcCurveBoundedPlane(surface.as<typename IfcEntityTypesT::IfcCurveBoundedPlane>(), pos, polylineData);
					}

					// (3/4) IfcCurveBoundedSurface SUBTYPE of IfcBoundedSurface.
					else if (surface.isOfType<typename IfcEntityTypesT::IfcCurveBoundedSurface>()) {
						return convertIfcCurveBoundedSurface(surface.as<typename IfcEntityTypesT::IfcCurveBoundedSurface>(), pos, polylineData);
					}

					// (4/4) IfcRectangularTrimmedSurface SUBTYPE of IfcBoundedSurface.
					else if (surface.isOfType<typename IfcEntityTypesT::IfcRectangularTrimmedSurface>()) {
						return convertIfcRectangularTrimmedSurface(surface.as<typename IfcEntityTypesT::IfcRectangularTrimmedSurface>(), pos, polylineData);
					}
				}

				//--------------------------------------------------------------------------------------------
				// IfcElementarySurface
				//--------------------------------------------------------------------------------------------

					/*! \brief  Converts \c IfcElementarySurface by calling the conversion function according to subtype.
					\param		surface	\c IfcElementarySurface entity to be interpreted.
					\param		pos
					\param		polylineData
					\return
					\note		The \c IfcElementarySurface subtypes are \c IfcCylindricalSurface, \c IfcPlane, \c IfcSphericalPlane and \c IfcToroidalSurface.
					*/

				void convertIfcElementarySurface(const EXPRESSReference<typename IfcEntityTypesT::IfcBoundedSurface>& surface,
					const carve::math::Matrix& pos,
					EXPRESSReference<carve::input::PolylineSetData>& polylineData) {

					// (1/4) IfcCylindricalSurface SUBTYPE of IfcElementarySurface
					if (surface.isOfType<typename IfcEntityTypesT::IfcCylindricalSurface>()) {
						return convertIfcCylindricalSurface(surface.as<typename IfcEntityTypesT::IfcCylindricalSurface>(), pos, polylineData);
					}

					// (2/4) IfcPlane SUBTYPE of IfcElementarySurface
					if (surface.isOfType<typename IfcEntityTypesT::IfcPlane>()) {
						return convertIfcIfcPlane(surface.as<typename IfcEntityTypesT::IfcPlane>(), pos, polylineData);
					}

					// (3/4) IfcSphericalPlane SUBTYPE of IfcElementarySurface
					if (surface.isOfType<typename IfcEntityTypesT::IfcSphericalPlane>(), pos, polylineData) {
						return convertIfcSphericalPlane(surface.as<typename IfcEntityTypesT::IfcSphericalPlane>());
					}

					// (1/4) IfcToroidalSurface SUBTYPE of IfcElementarySurface
					if (surface.isOfType<typename IfcEntityTypesT::IfcToroidalSurface >()) {
						return convertIfcToroidalSurface(surface.as<typename IfcEntityTypesT::IfcToroidalSurface>(), pos, polyLineData);
					}
				}

				//--------------------------------------------------------------------------------------------
				// IfcSweptSurface
				//--------------------------------------------------------------------------------------------

					/*! \brief  Converts \c IfcSweptSurface by calling the conversion function according to subtype.
					\param		surface	\c IfcSweptSurface entity to be interpreted.
					\param		pos
					\param		polylineData
					\return
					\note		The \c IfcSweptSurface subtypes are \c IfcSurfaceOfLinearExtrusion and \c IfcSurfaceOfRevolution.
					*/

				void convertIfcSweptSurface(const EXPRESSReference<typename IfcEntityTypesT::IfcBoundedSurface>& surface,
					const carve::math::Matrix& pos,
					EXPRESSReference<carve::input::PolylineSetData>& polylineData) {

					// (1/2) IfcSurfaceOfLinearExtrusion SUBTYPE of IfcSweptSurface
					if (surface.isOfType<typename IfcEntityTypesT::IfcSurfaceOfLinearExtrusion>()) {
						return convertIfcSurfaceOfLinearExtrusion(surface.as<typename IfcEntityTypesT::IfcSurfaceOfLinearExtrusion>(), pos, polylineData);
					}

					// (2/2) IfcSurfaceOfRevolution SUBTYPE of IfcSweptSurface
					else if (surface.isOfType<typename IfcEntityTypesT::IfcSurfaceOfRevolution>()) {
						return convertIfcSurfaceOfRevolution(surface.as<typename IfcEntityTypesT::IfcSurfaceOfRevolution>(), pos, polylineData);
					}
				}

				//--------------------------------------------------------------------------------------------
				// Conversion functions
				//--------------------------------------------------------------------------------------------

				/*! \brief  Converts \c IfcBsplineSurface to ...
					\param	surface	\c IfcBSplineSurface entity to be interpreted.
					\param	pos
					\param	polylineData
					\return
					\note	The \c IfcBSplineSurface is a subtype of \c IfcBoundedSurface.
				*/

				void convertIfcBSplineSurface(const EXPRESSReference<typename IfcEntityTypesT::IfcBsplineSurface>& surface,
					const carve::math::Matrix& pos,
					EXPRESSReference<carve::input::PolylineSetData>& polylineData) {
					throw oip::UnhandledException(surface);
				}

				/*! \brief  Converts \c IfcCurveBoundedPlane to ...
					\param	surface	\c IfcCurveBoundedPlane entity to be interpreted.
					\param	pos
					\param	polylineData
					\return
					\note	The \c IfcCurveBoundedPlane is a subtype of \c IfcBoundedSurface.
				*/

				void convertIfcCurveBoundedPlane(const EXPRESSReference<typename IfcEntityTypesT::IfcCurveBoundedPlane>& surface,
					const carve::math::Matrix& pos,
					EXPRESSReference<carve::input::PolylineSetData>& polylineData) {
					throw oip::UnhandledException(surface);
				}

				/*! \brief  Converts \c IfcCurveBoundedSurface to ...
				\param	surface	\c IfcCurveBoundedSurface entity to be interpreted.
				\param	pos
				\param	polylineData
				\return
				\note	The \c IfcCurveBoundedSurface is a subtype of \c IfcBoundedSurface.
				*/

				void convertIfcCurveBoundedSurface(const EXPRESSReference<typename IfcEntityTypesT::IfcCurveBoundedSurface>& surface,
					const carve::math::Matrix& pos,
					EXPRESSReference<carve::input::PolylineSetData>& polylineData) {
					throw oip::UnhandledException(surface);
				}

				/*! \brief  Converts \c IfcRectangularTrimmedSurface to ...
				\param	surface	\c IfcRectangularTrimmedSurface entity to be interpreted.
				\param	pos
				\param	polylineData
				\return
				\note	The \c IfcRectangularTrimmedSurface is a subtype of \c IfcBoundedSurface.
				*/

				void convertIfcRectangularTrimmedSurface(const EXPRESSReference<typename IfcEntityTypesT::IfcRectangularTrimmedSurface>& surface,
					const carve::math::Matrix& pos,
					EXPRESSReference<carve::input::PolylineSetData>& polylineData) {
					throw oip::UnhandledException(surface);
				}

				/*! \brief  Converts \c IfcCylindricalSurface to ...
				\param	surface	\c IfcCylindricalSurface entity to be interpreted.
				\param	pos
				\param	polylineData
				\return
				\note	The \c IfcCylindricalSurface is a subtype of \c IfcElementarySurface.
				*/

				void convertIfcCylindricalSurface(const EXPRESSReference<typename IfcEntityTypesT::IfcCylindricalSurface>& surface,
					const carve::math::Matrix& pos,
					EXPRESSReference<carve::input::PolylineSetData>& polylineData) {
					throw oip::UnhandledException(surface);
				}

				/*! \brief  Converts \c IfcPlane to ...
				\param	surface	\c IfcPlane entity to be interpreted.
				\param	pos
				\param	polylineData
				\return
				\note	The \c IfcPlane is a subtype of \c IfcElementarySurface.
				*/

				void convertIfcPlane(const EXPRESSReference<typename IfcEntityTypesT::IfcPlane>& surface,
					const carve::math::Matrix& pos,
					EXPRESSReference<carve::input::PolylineSetData>& polylineData) {
					throw oip::UnhandledException(surface);
				}

				/*! \brief  Converts \c IfcSphericalPlane to ...
				\param	surface	\c IfcSphericalPlane entity to be interpreted.
				\param	pos
				\param	polylineData
				\return
				\note	The \c IfcSphericalPlane is a subtype of \c IfcElementarySurface.
				*/

				void convertIfcSphericalPlane(const EXPRESSReference<typename IfcEntityTypesT::IfcSphericalPlane>& surface,
					const carve::math::Matrix& pos,
					EXPRESSReference<carve::input::PolylineSetData>& polylineData) {
					throw oip::UnhandledException(surface);
				}

				/*! \brief  Converts \c IfcToroidalSurface to ...
				\param	surface	\c IfcToroidalSurface entity to be interpreted.
				\param	pos
				\param	polylineData
				\return
				\note	The \c IfcToroidalSurface is a subtype of \c IfcElementarySurface.
				*/

				void convertIfcToroidalSurface(const EXPRESSReference<typename IfcEntityTypesT::IfcToroidalSurface>& surface,
					const carve::math::Matrix& pos,
					EXPRESSReference<carve::input::PolylineSetData>& polylineData) {
					throw oip::UnhandledException(surface);
				}

				/*! \brief  Converts \c IfcSurfaceOfLinearExtrusion to ...
				\param	surface	\c IfcSurfaceOfLinearExtrusion entity to be interpreted.
				\param	pos
				\param	polylineData
				\return
				\note	The \c IfcSurfaceOfLinearExtrusion is a subtype of \c IfcSweptSurface.
				*/

				void convertIfcSurfaceOfLinearExtrusion(const EXPRESSReference<typename IfcEntityTypesT::IfcSurfaceOfLinearExtrusion>& surface,
					const carve::math::Matrix& pos,
					EXPRESSReference<carve::input::PolylineSetData>& polylineData) {
					throw oip::UnhandledException(surface);
				}

				/*! \brief  Converts \c IfcSurfaceOfRevolution to ...
				\param	surface	\c IfcSurfaceOfRevolution entity to be interpreted.
				\param	pos
				\param	polylineData
				\return
				\note	The \c IfcSurfaceOfRevolution is a subtype of \c IfcSweptSurface.
				*/

				void convertIfcSurfaceOfRevolution(const EXPRESSReference<typename IfcEntityTypesT::IfcSurfaceOfRevolution>& surface,
					const carve::math::Matrix& pos,
					EXPRESSReference<carve::input::PolylineSetData>& polylineData) {
					throw oip::UnhandledException(surface);
				}
			}
		} 
	}
} 
#endif


					
						
						

					
						
					
