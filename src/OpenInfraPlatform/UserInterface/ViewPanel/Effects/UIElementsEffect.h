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
#ifndef BlueFramework_UserInterface_UIElementsEffect_ce3ae2a7_9ba0_4302_9860_f5d26081abd7_h
#define BlueFramework_UserInterface_UIElementsEffect_ce3ae2a7_9ba0_4302_9860_f5d26081abd7_h

#include "OpenInfraPlatform/namespace.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/RenderResources.h"
#include <buw.Engine.h>
#include <buw.Rasterizer.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

struct ViewportBuffer {
	int width, height;
	int p1, p2;
};

class UIElements : public buw::Effect {
public:
	UIElements(
		buw::IRenderSystem* renderSystem,
		buw::ReferenceCounted<buw::ITexture2D> depthStencil,
		buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer);

	void loadShader();

	void resize(const buw::viewportDescription& vpd);

private:
	void v_init();

	void v_render();


private:
	buw::ReferenceCounted<buw::IPipelineState> pipelineState_;
	buw::ReferenceCounted<buw::IViewport> viewport_;
	buw::ReferenceCounted<buw::ITexture2D> depthStencil_;
	buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer_, viewportBuffer_;

	buw::ReferenceCounted<buw::VertexCacheLineT<buw::VertexPosition3Color3Size1>> vertexCacheLine_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END

#endif // end define BlueFramework_UserInterface_UIElementsEffect_ce3ae2a7_9ba0_4302_9860_f5d26081abd7_h
