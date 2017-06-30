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
#ifndef OpenInfraPlatform_Infrastructure_Alignment2DBased3D_dda096bb_11f3_4705_ac2b_3166c5e4a580_h
#define OpenInfraPlatform_Infrastructure_Alignment2DBased3D_dda096bb_11f3_4705_ac2b_3166c5e4a580_h

#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignment2D.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignment2D.h"
#include "OpenInfraPlatform/Infrastructure/CrossSection/CrossSectionStatic.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/IAlignment3D.h"
#include <BlueFramework/Core/Math/vector.h>
#include <BlueFramework/Core/Math/AxisAlignedBoundingBox.h>
#include <boost/noncopyable.hpp>
#include <vector>

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		//! A 3d alignment based on 2d horizontal and a 2d vertical alignment. This object
		//! is used as a container object.
		class BLUEINFRASTRUCTURE_API Alignment2DBased3D : public IAlignment3D
		{
		public:				
			static Alignment2DBased3D* createFlatCopy(const Alignment2DBased3D& src);

			Alignment2DBased3D(buw::ReferenceCounted<HorizontalAlignment2D> horizontalAlignment = nullptr,
				buw::ReferenceCounted<VerticalAlignment2D> verticalAlignment = nullptr);

			virtual ~Alignment2DBased3D() {}

			//! Computes the 3d position given a stationing.
			buw::Vector3d	getPosition(const buw::Stationing station ) const override;

			//! Start station of horizontal alignment
			Stationing		getStartStation() const override;

			Stationing		getEndStation() const override;

			//! Length of horizontal alignment
			double			getLength() const override;	

			//---------------------------------------------------------------------------//
			// Horizontal Alignment
			//---------------------------------------------------------------------------//

			bool						hasHorizontalAlignment() const;

			int							getHorizontalAlignmentElementCount();

			double						getHorizontalAlignmentLength() const;

			//! Computes the 2d position in the horizontal alignment given a stationing.
			buw::Vector2d				getHorizontalPosition(const buw::Stationing station ) const;

			buw::ReferenceCounted<HorizontalAlignment2D>	getHorizontalAlignment() const;

			void						setHorizontalAlignment(buw::ReferenceCounted<buw::HorizontalAlignment2D> horizontalAlignment);

			//---------------------------------------------------------------------------//
			// Vertical Alignment
			//---------------------------------------------------------------------------//

			bool						hasVerticalAlignment() const;

			buw::Vector2d				getVerticalPosition(const Stationing station ) const;

			buw::ReferenceCounted<VerticalAlignment2D>	getVerticalAlignment() const;

			void						setVerticalAlignment(buw::ReferenceCounted<VerticalAlignment2D> verticalAlignment);

			buw::AxisAlignedBoundingBox3d getVerticalAlignmentExtends() const;
			
			//---------------------------------------------------------------------------//
			// Cross Section
			//---------------------------------------------------------------------------//

			void						addCrossSection(buw::ReferenceCounted<buw::CrossSectionStatic> cs);
			void						sortCrossSectionsByStation();

			int								getCrossSectionCount();
			buw::ReferenceCounted<buw::CrossSectionStatic>	getCrossSection(const int index);

			//---------------------------------------------------------------------------//
			// ID
			//---------------------------------------------------------------------------//

			void setId(const int id) {
				Id_ = id;
			}

			int getId() const {
				return Id_;
			}

		private:
			int Id_ = -1; // invalid id.

			std::vector<buw::ReferenceCounted<buw::CrossSectionStatic>>	crossSections_;
			buw::ReferenceCounted<HorizontalAlignment2D>				horizontalAlignment_;
			buw::ReferenceCounted<VerticalAlignment2D>					verticalAlignment_;
		};

		BLUEINFRASTRUCTURE_API buw::AxisAlignedBoundingBox3d getExtends(buw::ReferenceCounted<Alignment2DBased3D> alignment);
		BLUEINFRASTRUCTURE_API buw::AxisAlignedBoundingBox3d getExtends(std::vector<buw::ReferenceCounted<IAlignment3D>> alignments);
	} // end namespace Infrastructure
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::Infrastructure::Alignment2DBased3D;
	using OpenInfraPlatform::Infrastructure::getExtends;
}

#endif // end define OpenInfraPlatform_Infrastructure_Alignment2DBased3D_dda096bb_11f3_4705_ac2b_3166c5e4a580_h
