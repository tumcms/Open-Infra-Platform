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
#ifndef OpenInfraPlatform_Infrastructure_LandXmlParser_60c637f8_9478_44a4_bd52_cfa2ffa2dc4c_h
#define OpenInfraPlatform_Infrastructure_LandXmlParser_60c637f8_9478_44a4_bd52_cfa2ffa2dc4c_h

#include "OpenInfraPlatform/Infrastructure/Import/Import.h"
#include "OpenInfraPlatform/Infrastructure/Import/LandXMLBaseTypes.h"
#include <BlueFramework/Core/PropertySet.h>
#include <BlueFramework/Core/Math/vector.h>
#include <BlueFramework/Core/memory.h>
#include <stack>
#include <map>

namespace OpenInfraPlatform
{	
	namespace Infrastructure
	{
		typedef int LandXMLPointIdType;

		struct BLUEINFRASTRUCTURE_API LandXMLSurfacePoint
		{
			LandXMLPointIdType	id;			// unique id referenced by faces
			buw::Vector3d		position;
		};

		class BLUEINFRASTRUCTURE_API LandXMLSurface
		{
		public:
			LandXMLSurface()
			{

			}

			virtual ~LandXMLSurface()
			{

			}
			
			void addSurfacePoint(const LandXMLSurfacePoint& point)
			{
				points_.push_back(point);
				idToPosition_[point.id] = point.position;
			}

			const std::vector<LandXMLSurfacePoint>&		getPoints() const
			{
				return points_;
			}

			int											getPointCount() const
			{
				return static_cast<int>(points_.size());
			}

			const std::vector<buw::Vector3i>&			getTriangeFaces() const
			{
				return triangeFaces_;
			}

			int											getTriangleCount() const
			{
				return static_cast<int>(triangeFaces_.size());
			}

			void setName(const char* str)
			{
				name_ = str;
			}

			const char* getName() const
			{
				return name_.c_str();
			}

			void addTriangle(const buw::Vector3i& indices)
			{
				triangeFaces_.push_back(indices);
			}

			bool doesSurfacePointExist(const LandXMLPointIdType pointId) const
			{
				auto pos = idToPosition_.find(pointId);
				if (pos == idToPosition_.end())
				{
					return false;
				}
				else
				{
					return true;
				}
			}

			buw::Vector3d getSurfacePointPositonById(const LandXMLPointIdType pointId) const
			{
				BLUE_ASSERT(doesSurfacePointExist(pointId));

				auto pos = idToPosition_.find(pointId);
				if (pos == idToPosition_.end())
				{
					return buw::Vector3d(0.0, 0.0, 0.0);
				}
				else
				{
					return pos->second;
				}
			}

		private:
			std::vector<LandXMLSurfacePoint>		points_;
			std::vector<buw::Vector3i>				triangeFaces_;
			std::string								name_;

			// faster access to positions
			std::map<LandXMLPointIdType, buw::Vector3d>	idToPosition_;
		};

		class BLUEINFRASTRUCTURE_API LandXMLDataBuilder : boost::noncopyable
		{
		public:
			typedef buw::PropertySet PropertySet;

			LandXMLDataBuilder() {}

			virtual ~LandXMLDataBuilder() {}

			//! Create an empty alignment
			virtual void createAlignment(const PropertySet& /*parameters*/) {};

			//---------------------------------------------------------------------------//
			// Horizontal alignment
			//---------------------------------------------------------------------------//

			//! Create an empty horizontal alignment
			virtual void createCoordGeom() {};

			//! A LandXML horizontal line segment
			virtual void createLine(const PropertySet& /*parameters*/) {};

			//! A LandXML horizontal arc segment
			virtual void createCurve(const PropertySet& /*parameters*/) {};

			//! A LandXML horizontal spiral
			virtual void createSpiral(const PropertySet& /*parameters*/) {};

			//---------------------------------------------------------------------------//
			// Vertical alignment
			//---------------------------------------------------------------------------//

			//! Create an empty vertical alignment
			virtual void createProfAlign(const PropertySet& /*parameters*/) {};

			//! Create a vertical PVI point
			virtual void createPVI(const PropertySet& /*parameters*/) {};

			//! Create a vertical parabola segment
			virtual void createParaCurve(const PropertySet& /*parameters*/) {};

			//! Create a vertical arc segment
			virtual void createCircCurve(const PropertySet& /*parameters*/) {};

			//---------------------------------------------------------------------------//
			// Terrain
			//---------------------------------------------------------------------------//

			//! Create a surface element
			virtual void createSurface(const PropertySet& /*parameters*/, const LandXMLSurface& /*surface*/) {};

			//---------------------------------------------------------------------------//
			// Cross Sections
			//---------------------------------------------------------------------------//

			virtual void createCrossSectionSurf(const PropertySet& /*parameters*/) {};

			virtual void createDesignCrossSectSurf(const PropertySet& /*parameters*/) {};

			virtual void createCrossSectPnt(const PropertySet& /*parameters*/) {};
		}; // end class LandXMLDataBuilder

		class BLUEINFRASTRUCTURE_API LandXMLImportDirector
		{
		public:
			void setLandXMLDataBuilder(LandXMLDataBuilder* builder)
			{
				builder_ = builder;
			}

			virtual void construct() = 0;

		private:
			LandXMLDataBuilder* builder_;
		};

		BLUEINFRASTRUCTURE_API void constructLandXMLData(
			const std::string& filename,
			LandXMLDataBuilder* builder);

		BLUEINFRASTRUCTURE_API buw::ReferenceCounted<buw::VerticalAlignment2D> createVerticalAlignmentFromProfAlign(const std::vector<profAlignElement>& profAlignElements_);

		BLUEINFRASTRUCTURE_API std::vector<profAlignElement> createProfAlignElements(buw::ReferenceCounted<buw::VerticalAlignment2D> v);

		class BLUEINFRASTRUCTURE_API ImportLandXml : public Import
		{
		public:
			ImportLandXml(const std::string& filename);
		};
	} // end namespace Infrastructure
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::Infrastructure::LandXMLDataBuilder;
	using OpenInfraPlatform::Infrastructure::eProfAlignType;
	using OpenInfraPlatform::Infrastructure::profAlignElement;
	using OpenInfraPlatform::Infrastructure::ImportLandXml;
	using OpenInfraPlatform::Infrastructure::createVerticalAlignmentFromProfAlign;
	using OpenInfraPlatform::Infrastructure::createProfAlignElements;
}

#endif // end define OpenInfraPlatform_Infrastructure_LandXmlParser_60c637f8_9478_44a4_bd52_cfa2ffa2dc4c_h
