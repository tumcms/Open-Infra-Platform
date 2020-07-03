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
#ifndef OpenInfraPlatform_UserInterface_BoxEffect_F594ABC3_4E77_4E7B_BB89_2A31CD33156A_h
#define OpenInfraPlatform_UserInterface_BoxEffect_F594ABC3_4E77_4E7B_BB89_2A31CD33156A_h

#include "namespace.h"

#include <buw.Rasterizer.h>
#include <buw.Engine.h>
#include <map>
#include <tuple>

OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_BEGIN

class BoxEffect : public buw::Effect {
public:	

	/*Construct by providing the renderSystem, viewport, depthStencil and worldBuffer for camera etc.*/
	BoxEffect(buw::IRenderSystem* renderSystem,
		buw::ReferenceCounted<buw::IViewport> viewport,
		buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA,
		buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer,
		buw::ReferenceCounted<buw::IConstantBuffer> viewportBuffer);

	/*Release all resources*/
	virtual ~BoxEffect();

	/*Load the shader from effect file and construct pipelineState*/
	void loadShader();

	void show(const bool checked);

	void assignVertexBuffer(buw::ReferenceCounted<buw::IVertexBuffer> vertexBuffer);
	void assignIndexBuffer(buw::ReferenceCounted<buw::IIndexBuffer> indexBuffer);

private:
	void v_init();
	void v_render();

private:
	buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer_ = nullptr;
	buw::ReferenceCounted<buw::IConstantBuffer> viewportBuffer_ = nullptr;
	buw::ReferenceCounted<buw::IVertexBuffer> vertexBuffer_ = nullptr;
	buw::ReferenceCounted<buw::IIndexBuffer> indexBuffer_ = nullptr;
	buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA_ = nullptr;
	buw::ReferenceCounted<buw::IPipelineState> pipelineState_ = nullptr;
	buw::ReferenceCounted<buw::IViewport> viewport_ = nullptr;
	
	bool bShow_ = false;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_END

EMBED_RENDERING_INTO_OIP_NAMESPACE(BoxEffect)

#endif //end define OpenInfraPlatform_UserInterface_BoxEffect_F594ABC3_4E77_4E7B_BB89_2A31CD33156A_h