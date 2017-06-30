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
#ifndef OpenInfraPlatform_UserInterface_CoordinateSystem_f0e6b71a_ce6f_4804_a4b8_8bf9fcc15f55_h
#define OpenInfraPlatform_UserInterface_CoordinateSystem_f0e6b71a_ce6f_4804_a4b8_8bf9fcc15f55_h

#include <BlueFramework/Engine/VertexCache/VertexCache.h>
#include <BlueFramework/Rasterizer/vertex.h>
#include <BlueFramework/Core/Math/vector.h>
#include <boost/noncopyable.hpp>

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		enum class eCoordinateSystemType
		{
			OpenGL,
			Autodesk
		};

		void drawCoordinateSystem(
			buw::ReferenceCounted<buw::VertexCacheLineT<buw::VertexPosition3Color3Size1>> vertexCacheLine,
			float scale = 1.0f, 
			eCoordinateSystemType type = eCoordinateSystemType::Autodesk);

		enum class eGridOrientation
		{
			POSITIV_X_ORIENTATION,
			POSITIV_Y_ORIENTATION,
			POSITIV_Z_ORIENTATION
		};

		struct drawGridDescription
		{
			float width;
			float height; 
			buw::Vector3f center;
			int widthSegments;
			int heightSegments; 
			eGridOrientation orientation;
			bool leaveCoodinateSystemBlank;
		};
		
		/*void drawGrid( 
			buw::ReferenceCounted<buw::VertexCacheLine> vertexCacheLine,
			const drawGridDescription& dgd);*/
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::UserInterface::drawCoordinateSystem;
	using OpenInfraPlatform::UserInterface::eGridOrientation;
	using OpenInfraPlatform::UserInterface::drawGridDescription;
	//using OpenInfraPlatform::UserInterface::drawGrid;
}

#endif // end define OpenInfraPlatform_UserInterface_CoordinateSystem_f0e6b71a_ce6f_4804_a4b8_8bf9fcc15f55_h