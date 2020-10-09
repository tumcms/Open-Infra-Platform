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
	namespace UserInterface
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
			int isCCW_; // = is counter clockwise
			carve::geom::vector<3> center_;

			double radiusClothoidStart_;
			double radiusClothoidEnd_;
			double clothoidparameterA_;

		public:
			// CONSTRUCTOR
			SplineInterpretationElement();

			SplineInterpretationElement(double lengthBSpline, int indicator, std::pair<size_t, size_t> indices);


			// FUNCTIONS WITH ACCESS TO VARIABLES
			void setLengthBSpline(double lengthBSpline);
			double getLengthBSpline() const;

			void setindicator(int indicator);
			int getIndicator() const;

			void setIndices(size_t startIndice, size_t endIndice);
			void setIndicesStart(size_t startIndice);
			void setIndicesEnd(size_t endIndice);
			std::pair<size_t, size_t> getIndices() const;
			size_t getIndicesStart() const;
			size_t getIndicesEnd() const;

			void setType(std::string type);
			std::string getType() const;
			
			void setStartpoint(carve::geom::vector<3> startpoint);
			carve::geom::vector<3> getStartpoint() const;

			void setDirection(double direction);
			double getDirection() const;

			void setLength(double length);
			double getLength() const;

			void setRadius(double radius);
			double getRadius() const;

			void setIsCCW(int isCCW);
			int getIsCCW() const;

			void setCenter(carve::geom::vector<3> center);
			carve::geom::vector<3> getCenter() const;

			void setRadiusClothoidStart(double radiusClothoidStart);
			double getRadiusClothoidStart() const;

			void setRadiusClothoidEnd(double radiusClothoidEnd);
			double getRadiusClothoidEnd() const;

			void setClothoidparameterA(double clothoidparameter);
			double getClothoidparameterA() const;
			// FUNCTIONS
		private:
			// FUNCTIONS


		}; // end class
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform

