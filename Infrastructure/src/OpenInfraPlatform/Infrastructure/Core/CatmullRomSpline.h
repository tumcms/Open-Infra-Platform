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
#ifndef OpenInfraPlatform_Infrastructure_CatmullRomSpline_d3800e37_f771_4174_883d_d706bfa8e8ec_h
#define OpenInfraPlatform_Infrastructure_CatmullRomSpline_d3800e37_f771_4174_883d_d706bfa8e8ec_h

#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"
#include <BlueFramework/Core/memory.h>
#include <BlueFramework/Core/Math/vector.h>

#include <vector>

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		template<typename T>
		class BLUEINFRASTRUCTURE_API CatmullRomSpline3
		{
		public:
			typedef T ScalarType;
			typedef BlueFramework::Core::Math::Vector<ScalarType,3> VectorType;

			// Constructors and destructor
			CatmullRomSpline3()
				: vp(), delta_t(0)
			{
			}

			CatmullRomSpline3(const CatmullRomSpline3& source)
			{
				for (int i = 0; i < (int)source.vp.size(); i++)
					vp.push_back(source.vp[i]);

				delta_t = source.delta_t;
			}

			CatmullRomSpline3& operator= (const CatmullRomSpline3& source)
			{
				for (int i = 0; i < (int)source.vp.size(); i++)
					vp.push_back(source.vp[i]);

				delta_t = source.delta_t;

				return *this;
			}

			virtual ~CatmullRomSpline3()
			{

			}

			void AddSplinePoint(const VectorType& v)
			{
				vp.push_back(v);
				delta_t = (ScalarType)1 / (ScalarType)(vp.size()-1);
			}

			void AddSplinePoints(const std::vector<VectorType>& a)
			{
				for ( auto v : a)
				{
					vp.push_back(v);
					delta_t = (ScalarType)1 / (ScalarType)(vp.size() - 1);
				}
			}

			VectorType GetInterpolatedSplinePoint(const ScalarType t) const  // t = 0...1; 0=vp[0] ... 1=vp[max]
			{
				// Find out in which interval we are on the spline
				int p = (int)(t / delta_t);
				// Compute local control point indices
				int p0 = p - 1;     fitBounds(p0);
				int p1 = p;         fitBounds(p1);
				int p2 = p + 1;     fitBounds(p2);
				int p3 = p + 2;     fitBounds(p3);
				// Relative (local) time 
				ScalarType lt = (t - delta_t*(ScalarType)p) / delta_t;
				// Interpolate
				return  Eq(lt, vp[p0], vp[p1], vp[p2], vp[p3]);
			}
			
			int GetNumPoints() const
			{
				return vp.size();
			}

			const buw::Vector3f& GetNthPoint(const int n) const
			{
				return vp[n];
			}

			ScalarType Length() const
			{
				ScalarType sum = 0;

				ScalarType delta = 0.01;
				auto a = GetInterpolatedSplinePoint(0);
				for (ScalarType t = delta; t < 1.0f; t+=delta)
				{
					auto b = GetInterpolatedSplinePoint(t);

					auto d = (a - b).norm();

					sum += d;

					a = b;
				}

				return sum;
			}

			// Static method for computing the Catmull-Rom parametric equation
			// given a time (t) and a vector quadruple (p1,p2,p3,p4).
			static VectorType Eq(ScalarType t, 
				const VectorType& p1, 
				const VectorType& p2, 
				const VectorType& p3, 
				const VectorType& p4)
			{
				ScalarType t2 = t * t;
				ScalarType t3 = t2 * t;

				ScalarType b1 = .5 * (  -t3 + 2*t2 - t);
				ScalarType b2 = .5 * ( 3*t3 - 5*t2 + 2);
				ScalarType b3 = .5 * (-3*t3 + 4*t2 + t);
				ScalarType b4 = .5 * (   t3 -   t2    );

				return (p1*b1 + p2*b2 + p3*b3 + p4*b4); 
			}

		private:
			void fitBounds(int& pp) const
			{ 
				if (pp < 0)
					pp = 0; 
				else if (pp >= (int)vp.size()) 
					pp = vp.size() - 1;
			}

		private:
			std::vector<VectorType> vp;
			ScalarType delta_t;
		}; // end class CatmullRomSpline3f

		typedef CatmullRomSpline3<float> CatmullRomSpline3f;
		typedef CatmullRomSpline3<double> CatmullRomSpline3d;
	} // end namespace Infrastructure
} // end namespace BlueFramework

namespace buw
{
	using OpenInfraPlatform::Infrastructure::CatmullRomSpline3f;
	using OpenInfraPlatform::Infrastructure::CatmullRomSpline3d;
}

#endif // end define OpenInfraPlatform_Infrastructure_CatmullRomSpline_d3800e37_f771_4174_883d_d706bfa8e8ec_h
