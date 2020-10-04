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

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		class SplineInterpretationElement
		{
		private:
			// VARIABLES
			double length;
			int indicator;
			std::pair<size_t, size_t> indices;

		public:
			// CONSTRUCTOR
			SplineInterpretationElement();

			SplineInterpretationElement(double _length, int _indicator, std::pair<size_t, size_t> _indices);


			// FUNCTIONS WITH ACCESS TO VARIABLES
			void setLength(double newLength) throw(...);
			double getLength() const throw(...);

			void setindicator(int newIndicator) throw(...);
			int getIndicator() const throw(...);

			void setIndices(size_t startIndice, size_t endIndice) throw(...);
			void setIndicesStart(size_t startIndice) throw(...);
			void setIndicesEnd(size_t endIndice) throw(...);
			std::pair<size_t, size_t> getIndices() const throw(...);
			size_t getIndicesStart() const throw(...);
			size_t getIndicesEnd() const throw(...);


			// FUNCTIONS
		private:
			// FUNCTIONS


		}; // end class
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform

