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
#ifndef OpenInfraPlatform_Infrastructure_ImportLandInfra_2fec77f9_05A4_4BC0_A9A5_B0EF4AC7778A_h
#define OpenInfraPlatform_Infrastructure_ImportLandInfra_2fec77f9_05A4_4BC0_A9A5_B0EF4AC7778A_h

#include "OpenInfraPlatform/Infrastructure/Import/Import.h"

#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DArc.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid.h"

#include <QtXml>


namespace OpenInfraPlatform {
	namespace Infrastructure {

		class BLUEINFRASTRUCTURE_API LandInfraNode : public QDomNode
		{
		public:

			LandInfraNode(const QDomNode &other) :QDomNode(other) {};

			virtual buw::ReferenceCounted<buw::AlignmentModel> toAlignmentModel();

			/*Parses a lia:Alignment node and returns an Alignment2DBased3D. Currently there are no other types supported.*/
			virtual buw::ReferenceCounted<buw::IAlignment3D> toIAlignment3D();

			virtual buw::ReferenceCounted<buw::Alignment2DBased3D> toAlignment2DBased3D();

			virtual buw::ReferenceCounted<buw::HorizontalAlignment2D> toHorizontalAlignment2D();

			virtual buw::ReferenceCounted<buw::HorizontalAlignmentElement2D> toHorizontalAlignmentElement2D();

			virtual buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> toHorizontalAlignmentElement2DLine();

			virtual buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> toHorizontalAlignmentElement2DClothoid();

			virtual buw::ReferenceCounted<buw::HorizontalAlignmentElement2DArc> toHorizontalAlignmentElement2DArc();


			virtual buw::Vector2d toVector2d() const;
		};		

		class BLUEINFRASTRUCTURE_API ImportLandInfra : public Import
		{
		public:
			ImportLandInfra(const std::string& filename);

		private:
			static const bool validateHeader(const QString &header);
		};

	} // end namespace Infrastructure
} // end namespace OpenInfraPlatform

namespace buw {
	using OpenInfraPlatform::Infrastructure::ImportLandInfra;
}

#endif // end define OpenInfraPlatform_Infrastructure_ImportLandInfra_2fec77f9_05A4_4BC0_A9A5_B0EF4AC7778A_h
