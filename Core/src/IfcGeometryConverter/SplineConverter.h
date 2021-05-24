/*
    Copyright (c) 2021 Technical University of Munich
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

// visual studio
#pragma once
// linux
#ifndef SPLINECONVERTER_H
#define SPLINECONVERTER_H

#include <sstream>
#include <memory>

#include "CarveHeaders.h"
#include "GeometryInputData.h"
#include "GeomUtils.h"

#include "ConverterBase.h"
#include "PlacementConverter.h"
#include "CurveConverter.h"

#include "SplineUtilities.h"

namespace OpenInfraPlatform
{
	namespace Core {
		namespace IfcGeometryConverter {
			/*! \brief Converter functionality for \c IfcBSplineCurve's and \c IfcBSplineSurface's subtypes.
			*
			* \param IfcEntityTypesT The IFC version templates
			*/
			template <
				class IfcEntityTypesT
			>
			class SplineConverterT : public ConverterBaseT<IfcEntityTypesT> // TODO 2020.04.08.: spline converter does not apply length corrections: UnitConverter()->getLengthinMeterFactor()
			{
				public:
					SplineConverterT(
						std::shared_ptr<GeometrySettings> geomSettings,
						std::shared_ptr<UnitConverter<IfcEntityTypesT>> unitConverter,
						std::shared_ptr<PlacementConverterT<IfcEntityTypesT>> pc)
						:
						ConverterBaseT<IfcEntityTypesT>(geomSettings, unitConverter),
						placementConverter(pc)
					{}

					virtual ~SplineConverterT() {}

					/*! \brief Converts \c IfcBSplineCurve subtypes to an array of curve points, which can be rendered in a viewport.
					 *
					 * This converter can handle
					 * \c IfcBSplineCurveWithKnots and
					 * \c IfcRationalBSplineCurveWithKnots, which are subtypes of IfcBSplineCurve.
					 *
					 * \param[in]	splineCurve		\c IfcBSplineCurve entity to be converted.
					 * \param[out]	loops			The array of curve points, which can be rendered in a viewport.
					 */
					void convertIfcBSplineCurve(
						const EXPRESSReference<typename IfcEntityTypesT::IfcBSplineCurve>& splineCurve,
						std::vector<carve::geom::vector<3>>& loops) const throw(...)
					{
						const int degree = splineCurve->Degree;
						const int order = degree + 1;
						const int numControlPoints = splineCurve->ControlPointsList.size();
						const int numKnotsArray = order + numControlPoints;

						const std::vector<carve::geom::vector<3>> controlPoints = loadControlPoints(splineCurve);

						// IfcRationalBSplineCurveWithKnots is a subtype of IfcBSplineCurveWithKnots which is a subtype of IfcBSplineCurve, 
						// it represents a rational B-Spline / a NURBS.
						if (splineCurve.isOfType<typename IfcEntityTypesT::IfcRationalBSplineCurveWithKnots>())
						{
							const std::vector<double> knotArray = loadKnotArrayCurve(splineCurve.as<typename IfcEntityTypesT::IfcBSplineCurveWithKnots>(), numKnotsArray);
							const std::vector<double> weightsData = loadWeightsData((splineCurve.as<typename IfcEntityTypesT::IfcRationalBSplineCurveWithKnots>())->WeightsData);

							const uint32_t numCurvePoints = obtainNumCurvePoints(knotArray.size());
							// at the end, subtract current knot value with accuracy to avoid zero-vectors (since last knot value is excluded by definition)
							const double accuracy = obtainAccuracy();

							std::vector<carve::geom::vector<3>> curvePoints = 
								IfcGeometryConverter::SplineUtilities::computeRationalBSplineCurveWithKnots(order, knotArray, controlPoints, weightsData, numCurvePoints, accuracy);

							GeomUtils::appendPointsToCurve(curvePoints, loops);
							// return loops;
						}
						// IfcBSplineCurveWithKnots is a subtype of IfcBSplineCurve, 
						// it represents a B-Spline
						else if (splineCurve.isOfType<typename IfcEntityTypesT::IfcBSplineCurveWithKnots>())
						{
							const std::vector<double> knotArray = loadKnotArrayCurve(splineCurve.as<typename IfcEntityTypesT::IfcBSplineCurveWithKnots>(), numKnotsArray);

							const uint32_t numCurvePoints = obtainNumCurvePoints(knotArray.size());
							// at the end, subtract current knot value with accuracy to avoid zero-vectors (since last knot value is excluded by definition)
							const double accuracy = obtainAccuracy();

							std::vector<carve::geom::vector<3>> curvePoints = 
								IfcGeometryConverter::SplineUtilities::computeBSplineCurveWithKnots(order, knotArray, controlPoints, numCurvePoints, accuracy);

							GeomUtils::appendPointsToCurve(curvePoints, loops);
							// return loops;
						}
						// there is no further subtype, which is known now (ifc 4x3 RC 1)
						else if (numControlPoints == order)
						{
							// if the number of control points is equal to the order ( = degree + 1 ), there are enough information 
							// to calculate a Bezier Curve - but it isn't mentioned in the ifc documentation

							// TODO: has to be implemented,
							//       the knotArray has to be set in a specific way
							//       with this special knotArray the function computeBSplineCurveWithKnots can be called for calculation

							throw oip::UnhandledException(splineCurve);
						}
						// it's unknown what to do with this ifc entity
						else
						{
							throw oip::UnhandledException(splineCurve);
						}
					}

					/*! \brief Converts \c IfcBSplineSurface subtypes to an array of surface-points.
					 *
					 * This convert function can handle
					 * \c IfcBSplineSurfaceWithKnots and
					 * \c IfcRationalBSplineSurfaceWithKnots.
					 *
					 * \param[in]	bsplineSurfaceWithKnots		\c IfcBSplineSurface entity to be converted.
					 * \param[in]	pos							The relative location of the origin of the representation's coordinate system within the geometric context.
					 * \param[in]	controlPoints				A vector of the B-Spline control points, must be obtain from the \c IfcBSplineSurface entity.
					 *
					 * \return		Array (vector of vectors) of surface-points.
					 */
					std::vector<std::vector<carve::geom::vector<3>>> convertIfcBSplineSurfaceWithKnots(
						const EXPRESSReference<typename IfcEntityTypesT::IfcBSplineSurfaceWithKnots>& bsplineSurfaceWithKnots,
						const carve::math::Matrix& pos, // AT THE MOMENT, NO IDEA WHAT THIS IS
						const std::vector<std::vector<carve::geom::vector<3>>>& controlPoints) const throw(...)
					{
						// obtain degree of both b-spline curves, attributes 1 and 2 of IfcBSplineSurface
						const int degreeU = bsplineSurfaceWithKnots->UDegree;
						const int orderU = degreeU + 1;
						const int degreeV = bsplineSurfaceWithKnots->VDegree;
						const int orderV = degreeV + 1;

						// obtain knots for each direction, 
						// attributes 8 & 10 and 9 & 11 of IfcBSplineSurfaceWithKnots will be combined to do that
						std::vector<double> knotsU;
						std::vector<double> knotsV;
						std::tie(knotsU, knotsV) = loadKnotArraySurface(
							bsplineSurfaceWithKnots,
							orderU + controlPoints.size(), // number of knots in u direction
							orderV + controlPoints[0].size()); // number of knots in v direction

						const uint32_t numCurvePointsU = obtainNumCurvePoints(knotsU.size());
						const uint32_t numCurvePointsV = obtainNumCurvePoints(knotsV.size());
						// at the end, subtract current knot value with accuracy to avoid zero-vectors (since last knot value is excluded by definition)
						const double accuracy = obtainAccuracy();

						// declare target vector of curve points
						std::vector<std::vector<carve::geom::vector<3>>> curvePoints;

						// distinction between IfcBSplineSurfaceWithKnots and IfcRationalBSplineSurfaceWithKnots
						// (2/2) reverse order - IfcRationalBSplineSurfaceWithKnots SUBTYPE of IfcBSplineSurfaceWithKnots
						if (bsplineSurfaceWithKnots.isOfType<typename IfcEntityTypesT::IfcRationalBSplineSurfaceWithKnots>())
						{
							const EXPRESSReference<typename IfcEntityTypesT::IfcRationalBSplineSurfaceWithKnots> rationalBSplineSurfaceWithKnots =
								bsplineSurfaceWithKnots.as<typename IfcEntityTypesT::IfcRationalBSplineSurfaceWithKnots>();
							
							// load the weights of the control points
							const std::vector<std::vector<double>> weights = loadWeightsDataSurface(rationalBSplineSurfaceWithKnots);
							
							curvePoints = IfcGeometryConverter::SplineUtilities::computeRationalBSplineSurfaceWithKnots(
								orderU, orderV, knotsU, knotsV, controlPoints, weights, numCurvePointsU, numCurvePointsV, accuracy);
						}
						else // (1/2) reverse order - IfcBSplineSurfaceWithKnots
						{
							curvePoints = IfcGeometryConverter::SplineUtilities::computeBSplineSurfaceWithKnots(
								orderU, orderV, knotsU, knotsV, controlPoints, numCurvePointsU, numCurvePointsV, accuracy);
						}

						// apply pos to the curve points
						// pos: The relative location of the origin of the representation's coordinate system within the geometric context.
						for (std::vector<carve::geom::vector<3>>& curvePointsRow : curvePoints)
							for (carve::geom::vector<3>& point : curvePointsRow)
								point = pos * point;
						
						return curvePoints;
					}

				private:
					/*! \brief Loads the control points from an IfcBSplineCurve-entity
					 *
					 * \param[in] splineCurve	The IfcBSplineCurve-entity which contains the control points
					 *
					 * \return	  A vector with the B-Spline control points
					 */
					std::vector<carve::geom::vector<3>> loadControlPoints(
						const EXPRESSReference<typename IfcEntityTypesT::IfcBSplineCurve>& splineCurve) const throw(...)
					{
						CurveConverterT<IfcEntityTypesT> curveConverter(GeomSettings(), UnitConvert(), placementConverter);
						return curveConverter.convertIfcCartesianPointVector(splineCurve->ControlPointsList);
					}

					/*! \brief Loads the knot array from an \c IfcBSplineCurveWithKnots.
					 *
					 * \param[in]	bspline				The \c IfcBSplineCurveWithKnots entity from where the knots have to be loaded.
					 * \param[in]	numKnotsArray		The total number of knots, which define the basis functions ( = order + total number of control points )
					 *
					 * \return		The array / vector of knots.
					 */
					std::vector<double> loadKnotArrayCurve(
						const EXPRESSReference<typename IfcEntityTypesT::IfcBSplineCurveWithKnots>& bspline,
						const int& numKnotsArray) const throw(...)
					{
						// check whether data in ifc matches the definition in documentation
						if (bspline->KnotMultiplicities.size() != bspline->Knots.size())
						{
							//std::cout << "ERROR: knot multiplicity does not correspond number of knots" << std::endl;
							throw oip::InconsistentModellingException(bspline, "Function convertIfcBSplineCurve::loadKnotArrayCurve: Knot multiplicity does not correspond number of distinct knots; unable to construct a knot array.");
						}

						// get knots and knotMultiplicities from IfcBSplineCurveWithKnots,
						// and return the obtained / constructed knot array
						return obtainKnotArray(bspline->Knots, bspline->KnotMultiplicities, numKnotsArray);
					}

					/*! \brief Loads the knot array from an \c IfcBSplineCurveWithKnots.
						*
						* \param[in]	bspline				The \c IfcBSplineCurveWithKnots entity from where the knots have to be loaded.
						* \param[in]	numKnotsArrayU		The total number of knots in direction u, which define the basis functions ( = orderU + total number of control points U )
						* \param[in]	numKnotsArrayV		The total number of knots in direction v, which define the basis functions ( = orderV + total number of control points V )
						*
						* \return		The arrays / vectors of knots, in the order { knotsU, knotsV }.
						*/
					std::tuple<std::vector<double>, std::vector<double>> loadKnotArraySurface(
						const EXPRESSReference<typename IfcEntityTypesT::IfcBSplineSurfaceWithKnots>& bsplineSurface,
						const int numKnotsArrayU,
						const int numKnotsArrayV) const throw(...)
					{
						// check whether data in ifc matches the definition in documentation, direction u
						if (bsplineSurface->UMultiplicities.size() != bsplineSurface->UKnots.size())
						{
							throw oip::InconsistentModellingException(bsplineSurface, "Function SplineConverter::loadKnotArraySurface: Knot multiplicity U does not correspond number of distinct knots U; unable to construct a knot array.");
						}

						// check whether data in ifc matches the definition in documentation, direction v
						if (bsplineSurface->VMultiplicities.size() != bsplineSurface->VKnots.size())
						{
							throw oip::InconsistentModellingException(bsplineSurface, "Function SplineConverter::loadKnotArraySurface: Knot multiplicity V does not correspond number of distinct knots U; unable to construct a knot array.");
						}

						// get knots and knotMultiplicities from IfcBSplineCurveWithKnots,
						// and return the tuple of obtained / constructed knot arrays in order { knotsU, knotsV }
						return { obtainKnotArray(bsplineSurface->UKnots, bsplineSurface->UMultiplicities, numKnotsArrayU), // knots U
							obtainKnotArray(bsplineSurface->VKnots, bsplineSurface->VMultiplicities, numKnotsArrayV) }; // knots V
					}

					/*! \brief Obtains the knot array based on knots and knot multiplicity.
					 *
					 * \param[in]	knotsIfc				Vector of type \c IfcParameterValue with distinct knots.
					 * \param[in]	KnotMultiplicitiesIfc	Vector of type \c IfcInteger with multiplicity per distinct knot.
					 * \param[in]	numKnotsArray			The total number of knots, which define the basis functions ( = order + total number of control points )
					 *
					 * \return		The array / vector of knots.
					 */
					std::vector<double> obtainKnotArray(
						const std::vector<typename IfcEntityTypesT::IfcParameterValue>& knotsIfc,
						const std::vector<typename IfcEntityTypesT::IfcInteger>& KnotMultiplicitiesIfc,
						const int& numKnotsArray) const throw(...)
					{
						std::vector<double> knots;
						knots.resize(knotsIfc.size());
						std::transform(
							knotsIfc.begin(),
							knotsIfc.end(),
							knots.begin(),
							[](auto &it) { return it; });
						// convert 'it' (Knots) from IfcParameterValue to double ?

						std::vector<int> knotMults;
						knotMults.resize(KnotMultiplicitiesIfc.size());
						std::transform(
							KnotMultiplicitiesIfc.begin(),
							KnotMultiplicitiesIfc.end(),
							knotMults.begin(),
							[](auto &it) -> int { return it; });
						// convert 'it' (KnotMultiplicities) from IfcInteger to int ?

						// preset target vector
						std::vector<double> knotArray;
						knotArray.reserve(numKnotsArray);

						// obtain knots
						for (int i = 0; i < knots.size(); ++i)
						{
							const double knot = knots[i];
							const int knotMult = knotMults[i];
							// look at the multiplicity of the current knot
							for (int j = 0; j < knotMult; ++j)
							{
								knotArray.push_back(knot);
							}
						}

						return knotArray;
					}

					/*! \brief	Loads the weights of the control points from a surface (\c IfcRationalBSplineSurfaceWithKnots ).
					 *
					 * \param[in]	surface	The ifc-instance of type \c IfcRationalBSplineSurfaceWithKnots from where the weights should be loaded.
					 *
					 * \return	The array (vector of vectors) with the weights per control point.
					 */
					std::vector<std::vector<double>> loadWeightsDataSurface(
						const EXPRESSReference<typename IfcEntityTypesT::IfcRationalBSplineSurfaceWithKnots>& surface) const throw(...)
					{
						// prepare target array
						std::vector<std::vector<double>> weights;
						weights.resize(surface->WeightsData.size());

						std::transform(
							surface->WeightsData.begin(),
							surface->WeightsData.end(),
							weights.begin(),
							// for each row of wights 'it' call the function loadWeightsData; result vector is stored in the target array
							[this](auto &it) -> std::vector<double> {return loadWeightsData(it); });

						return weights;
					}

					/*! \brief Loads the weights of the control points from a vector of IfcReal (i.e. from an \c IfcRationalBSplineCurveWithKnots ).
					 *
					 * \param[in]	weightsIfc	The vector from which the weights have to be loaded.
					 *
					 * \return		The vector of weights per control point.
					 */
					std::vector<double> loadWeightsData(
						const std::vector<typename IfcEntityTypesT::IfcReal>& weightsIfc) const throw(...)
					{
						// prepare target vector
						std::vector<double> weightsData;
						weightsData.resize(weightsIfc.size());

						std::transform(
							weightsIfc.begin(),
							weightsIfc.end(),
							weightsData.begin(),
							[](auto &it) -> double { return it; });
						// convert 'it' (WeightsData) from IfcReal to double ?

						return weightsData;
					}
					
					/*! \brief Gives the accuracy, which are used in the calculation.
					 *
					 * \return		Accuracy which is technically needed in the calculation.
					 */
					double obtainAccuracy() const throw(...)
					{
						// at the end, subtract current knot value with this to avoid zero-vectors (since last knot value is excluded by definition)
						//const double accuracy = 0.0000001;
						return GeomSettings()->getPrecision();
					}

					/*! \brief Gives the number of curve points.
					 * 
					 * \param[in]	numKnotsArray	The total number of knots, which define the basis functions ( = order + total number of control points )
					 *
					 * \return		Number of curve points
					 *
					 * \note	The number of curve points \c numCurvePoints, where the curve c(t) has to be evaluated,
					 *			is temporary preset with a default value proportional to the number of knots.
					 */
					uint32_t obtainNumCurvePoints(const int numKnotsArray) const throw(...)
					{
						// ! TEMPORARY default number of curve points
						return numKnotsArray * 10;
					}
					
				protected:

					std::shared_ptr<PlacementConverterT<IfcEntityTypesT>> placementConverter;

			}; // end class SplineConverterT
		} // end namespace IfcGeometryConverter
	} // end namespace Core
} // end namespace OpenInfraPlatform

#endif
