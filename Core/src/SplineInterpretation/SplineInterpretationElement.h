/*
	Copyright (c) 2020 Technical University of Munich
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

#include <utility>
#include <string>
#include "IfcGeometryConverter/CarveHeaders.h"

namespace OpenInfraPlatform
{
	namespace Core
	{
		namespace SplineInterpretation
		{
			class SplineInterpretationElement
			{
			private:
				// VARIABLES
				// preset during element search
				double lengthBSpline_;
				int indicator_;
				std::pair<size_t, size_t> indices_;

				// final element parameters
				std::string type_;
				carve::geom::vector<3> startpoint_;
				double direction_;
				double length_;

				double radius_;
				double angle_; // = central angle of a circular arc
				bool isCCW_; // = is counter clockwise
				carve::geom::vector<3> center_;

				double radiusClothoidStart_;
				double radiusClothoidEnd_;
				double clothoidparameterA_;

			public:
				// CONSTRUCTOR
				SplineInterpretationElement();

				SplineInterpretationElement(double lengthBSpline, int indicator, std::pair<size_t, size_t> indices);


				// FUNCTIONS WITH ACCESS TO VARIABLES
				void setLengthBSpline(const double lengthBSpline) noexcept(true);
				double getLengthBSpline() const noexcept(true);

				void setindicator(const int indicator) noexcept(true);
				int getIndicator() const noexcept(true);

				void setIndices(const size_t startIndice, const size_t endIndice) noexcept(true);
				void setIndicesStart(const size_t startIndice) noexcept(true);
				void setIndicesEnd(const size_t endIndice) noexcept(true);
				std::pair<size_t, size_t> getIndices() const noexcept(true);
				size_t getIndicesStart() const noexcept(true);
				size_t getIndicesEnd() const noexcept(true);

				void setType(const std::string type) noexcept(true);
				std::string getType() const noexcept(true);

				void setStartpoint(const carve::geom::vector<3>& startpoint) noexcept(true);
				carve::geom::vector<3> getStartpoint() const noexcept(true);

				void setDirection(const double direction) noexcept(true);

				/*! \brief	Returns the direction at the element start in radian or degree.
				 *
				 * To get radian: Function call \c getDirection() without parameter or \c getDirection(false).\n
				 * To get degree: Function call \c getDirection(true).
				 *
				 * \param[in]	inDegree	Indicats with \c ture, if the direction angle should be in degree.
				 *
				 * \return	Direction at the element start.
				 */
				double getDirection(bool inDegree = false) const noexcept(true);

				void setLength(const double length) noexcept(true);
				double getLength() const noexcept(true);

				void setRadius(const double radius) noexcept(true);
				double getRadius() const noexcept(true);

				void setAngle(const double angle) noexcept(true);

				/*! \brief	Returns the central angle of a circular arc.
				 *
				 * To get radian: Function call \c getAngle() without parameter or \c getAngle(false).\n
				 * To get degree: Function call \c getAngle(true).
				 *
				 * \param[in]	inDegree	Indicates with \c ture, if the angle should be in degree.
				 *
				 * \return	Central angle of a circular arc.
				 */
				double getAngle(bool inDegree = false) const noexcept(true);

				void setIsCCW(const int isCCW) noexcept(true);
				bool getIsCCW() const noexcept(true);

				void setCenter(const carve::geom::vector<3>& center) noexcept(true);
				carve::geom::vector<3> getCenter() const noexcept(true);

				void setRadiusClothoidStart(const double radiusClothoidStart) noexcept(true);
				double getRadiusClothoidStart() const noexcept(true);

				void setRadiusClothoidEnd(const double radiusClothoidEnd) noexcept(true);
				double getRadiusClothoidEnd() const noexcept(true);

				void setClothoidparameterA(const double clothoidparameter) noexcept(true);
				double getClothoidparameterA() const noexcept(true);
				// FUNCTIONS
			private:
				// FUNCTIONS


			}; // end class
		} // end namespace SplineInterpretation
	} // end namespace Core
} // end namespace OpenInfraPlatform

