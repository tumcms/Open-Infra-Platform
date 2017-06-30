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

#pragma once

#include <BlueFramework/Core/Math/vector.h>

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		template<typename T>
		class Polyline
		{
			typedef T ScalarType;
			typedef BlueFramework::Core::Math::Vector<ScalarType, 3> VectorType;

		public:
			Polyline():
				delta_t(0)
			{}

			void AddPoint(const VectorType& p)
			{
				points.push_back(p);
				delta_t = (ScalarType)1 / (ScalarType)(points.size() - 1);
			}

			void AddPoints(const std::vector<VectorType>& ps)
			{
				for (auto& p : ps)
				{
					points.push_back(p);
				}
				delta_t = (ScalarType)1 / (ScalarType)(points.size() - 1);
			}

			VectorType Interpolate(const ScalarType t) const
			{
				int p0 = (int)(t / delta_t);
				int p1 = p0 + 1;

				ScalarType lt = (t - delta_t * p0) / delta_t;
				return (points[p1] - points[p0]) * lt + points[p0];
			}

			size_t GetNumPoints() const
			{
				return points.size();
			}

			const VectorType& GetNthPoint(const int n) const
			{
				return points[n];
			}

			ScalarType Length() const
			{
				ScalarType sum = 0;
				if (points.size() == 0)
					return 0;

				VectorType last = points[0];
				for (int i = 1; i < points.size(); i++)
				{
					VectorType delta = points[i] - last;
					sum += delta.norm();
					last = points[i];
				}

				return sum;
			}

		private:
			std::vector<VectorType> points;
			ScalarType delta_t;
		};

		typedef Polyline<float> Polyline3f;
		typedef Polyline<double> Polyline3d;
	} // end namespace Infrastructure
} // end namespace BlueFramework

namespace buw
{
	using OpenInfraPlatform::Infrastructure::Polyline3f;
	using OpenInfraPlatform::Infrastructure::Polyline3d;
}