/*
    Copyright (c) 2018 Technical University of Munich
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

#include "../UserInterface/Dialogues/OpenInfraMap.h"
#include "../UserInterface/ViewPanel/eView.h"

//#include "OpenInfraPlatform/Infrastructure/Alignment/AlignmentModel.h"

 //#include <BlueFramework/Engine/ViewCube/ViewCube.h>
 //#include <BlueFramework/Engine/ViewCube/ViewCubeRefactored.h>
 //#include <BlueFramework/Engine/ViewCube/Compass.h>
 //#include <BlueFramework/Engine/ViewCube/RotationArrows.h>

 //#include <BlueFramework/Engine/Camera/InfraCamera.h>
 //#include <BlueFramework/Engine/Camera/InfraCameraController.h>
 //#include <BlueFramework/Engine/Camera/SpectatorCamera.h>
#include <BlueFramework/Rasterizer/IRenderSystem.h>
#include <BlueFramework/Rasterizer/Resources/IViewport.h>
#include "BlueFramework/Rasterizer/Resources/ITexture2D.h"
#include <BlueFramework/Rasterizer/Resources/IConstantBUffer.h>
#include <BlueFramework/Rasterizer/Resources/ISampler.h>
#include <BlueFramework/Rasterizer/Effect.h>
//#include <BlueFramework/Engine/Camera/Camera.h>
#include <BlueFramework/Engine/VertexCache/VertexCache.h>

#include "IfcGeometryConverter/ConverterBuw.h"
#include <QWidget>
#include <QMouseEvent>
#include "../UserInterface/ViewPanel/Tool.h"
#include "DataManagement/General/Data.h"

#include <BlueFramework/ImageProcessing/Image.h>
#include <BlueFramework/ImageProcessing/io.h>
#include <BlueFramework/Core/Singleton.h>

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		class RenderResources {
		public: 
			RenderResources();

			void init(buw::ReferenceCounted<buw::IRenderSystem> renderSystem);

			void release();
		
			std::string getResourceRootDir();

			buw::ReferenceCounted<buw::ISampler> getLinearSampler() const;

		private:
			buw::ReferenceCounted<buw::ISampler> linearSampler_;
			std::string resourceRootDir_; // cached resource root dir
		};
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform
