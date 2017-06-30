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
#ifndef OpenInfraPlatform_Infrastructure_Line2_2af85b14_b0e1_40a7_a572_3140ad2d153d_h
#define OpenInfraPlatform_Infrastructure_Line2_2af85b14_b0e1_40a7_a572_3140ad2d153d_h

#include <BlueFramework/Core/Math/vector.h>

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		template<typename T>
		struct Line2
		{
			typedef T											scalar_type;
			typedef BlueFramework::Core::Math::Vector<T, 2>		vector_type;

			Line2(const vector_type& startPoint, const vector_type& endPoint)
			{
				this->a = startPoint;
				this->b = endPoint;
			}

			vector_type eval(const T x) const
			{
				return vector_type(x, getGradient() * x + getAbscisa());
			}

			T getGradient() const
			{
				return (b.y() - a.y()) / (b.x() - a.x());
			}

			T getAbscisa() const
			{
				return a.y() - getGradient() * a.x();
			}

			vector_type a, b;
		};

		template<typename T>
		bool computeIntersection(const Line2<T>& a, const Line2<T>& b, buw::Vector<T,2>& intersectionPoint)
		{
			if (a.getGradient() == b.getGradient())
			{
				return false;
			}

			double x = (a.getAbscisa() - b.getAbscisa()) / (b.getGradient() - a.getGradient());

			intersectionPoint = a.eval(x);

			return true;
		}


		template <
			typename T
		>
		inline std::ostream&
		operator<<(std::ostream& os, const Line2<T>& l)
		{
			os << "[";

			os << "line2: start " << l.a << " end " << l.b;

			os << "]";

			return os;
		}

		typedef Line2<double> Line2f;
		typedef Line2<double> Line2d;
	} // end namespace Infrastructure
} // end namespace BlueFramework

namespace buw
{
	using OpenInfraPlatform::Infrastructure::Line2;
	using OpenInfraPlatform::Infrastructure::Line2f;
	using OpenInfraPlatform::Infrastructure::Line2d;
	using OpenInfraPlatform::Infrastructure::computeIntersection;
}

#endif // end define OpenInfraPlatform_Infrastructure_Line2_2af85b14_b0e1_40a7_a572_3140ad2d153d_h
