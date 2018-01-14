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
#ifndef BlueFramework_UserInterface_BoundingBoxEffect_27ea70f0_b624_40ff_8b3e_20fcf02dfdf9_h
#define BlueFramework_UserInterface_BoundingBoxEffect_27ea70f0_b624_40ff_8b3e_20fcf02dfdf9_h

#include "OpenInfraPlatform/namespace.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/RenderResources.h"
#include <buw.Engine.h>
#include <buw.Rasterizer.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

class BoundingBoxEffect : public buw::Effect {
public:
	BoundingBoxEffect(
		buw::IRenderSystem* renderSystem,
		buw::ReferenceCounted<buw::IViewport> viewport,
		buw::ReferenceCounted<buw::ITexture2D> depthStencil,
		buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer);

	void loadShader();

	void enableMap(bool enable);
	bool mapEnabled() const;

	void setBounds(const buw::Vector3d& minExtend, const buw::Vector3d& maxExtend);

	buw::ReferenceCounted<buw::ITexture2D> mapTexture();

private:
	void v_init();

	void v_render();

	void loadMap();

private:
	buw::ReferenceCounted<buw::IPipelineState> pipelineState_;

	buw::ReferenceCounted<buw::IViewport> viewport_;
	buw::ReferenceCounted<buw::ITexture2D> depthStencil_;
	buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer_;
	buw::ReferenceCounted<buw::IVertexBuffer> vertexBuffer_;
	buw::ReferenceCounted<buw::ITexture2D> texture_;
	buw::ReferenceCounted<buw::ISampler> linearSampler_;

	bool drawMap_;
	buw::Vector3d minExtend_, maxExtend_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END

#endif // end define BlueFramework_UserInterface_BoundingBoxEffect_27ea70f0_b624_40ff_8b3e_20fcf02dfdf9_h
