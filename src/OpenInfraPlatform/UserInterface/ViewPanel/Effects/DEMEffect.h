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
#ifndef OpenInfraPlatform_UserInterface_DEMEffect_fac1f76b_d5ec_452f_9ba1_3878cb359839_h
#define OpenInfraPlatform_UserInterface_DEMEffect_fac1f76b_d5ec_452f_9ba1_3878cb359839_h

#include "OpenInfraPlatform/Infrastructure/DigitalElevationModel/DigitalElevationModel.h"
#include "OpenInfraPlatform/namespace.h"

#include <buw.Rasterizer.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

class DEMEffect : public buw::Effect {
public:
	struct SettingsBuffer {
		BlueFramework::Rasterizer::Unaligned::Int bTerrainTextured;
		BlueFramework::Rasterizer::Unaligned::Int bTerrainUseColorRamp;
		BlueFramework::Rasterizer::Unaligned::Int bTerrainDisplayIsoLines;
		BlueFramework::Rasterizer::Unaligned::Int bSnow;
		BlueFramework::Rasterizer::Unaligned::Float minHeight;
		BlueFramework::Rasterizer::Unaligned::Float maxHeight;
		BlueFramework::Rasterizer::Unaligned::Int padding1;
		BlueFramework::Rasterizer::Unaligned::Int padding2;
	};

public:
	DEMEffect::DEMEffect(buw::IRenderSystem* renderSystem,
	                     buw::ReferenceCounted<buw::IViewport> viewport,
	                     buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA,
	                     buw::ReferenceCounted<buw::ITexture2D> pickBuffer,
	                     buw::ReferenceCounted<buw::ITexture2D> depthStencil,
	                     buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer);

	void setDEM(buw::ReferenceCounted<buw::DigitalElevationModel> dem, buw::Vector3d& offset);
	void loadShader();

	void setDrawTerrainWireframe(const bool enable);

	void hideTerrain(const bool checked);

	void enableTerrainTextured(const bool checked);

	void enableIsoLines(const bool checked);

	void enableTerrainColorRamp(const bool checked);

	void enableSnow(const bool checked);

private:
	void updateSettingsBuffer(SettingsBuffer& buffer);

private:
	void v_init();
	void v_render();

private:
	buw::ReferenceCounted<buw::IPipelineState> pipelineStateSolid_;
	buw::ReferenceCounted<buw::IPipelineState> pipelineStateWireframe_;

	buw::ReferenceCounted<buw::IPipelineState> pipelineStatePick_;

	buw::ReferenceCounted<buw::IViewport> viewport_;
	buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA_;

	buw::ReferenceCounted<buw::ITexture2D> pickBuffer_;
	buw::ReferenceCounted<buw::ITexture2D> depthStencil_;

	buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer_;

	buw::ReferenceCounted<buw::IConstantBuffer> cbSettingsBuffer_;

	buw::ReferenceCounted<buw::IVertexBuffer> vertexBuffer_;
	buw::ReferenceCounted<buw::IIndexBuffer> indexBuffer_;

	buw::ReferenceCounted<buw::ITexture2D> texture_;
	buw::ReferenceCounted<buw::ITexture1D> gradientRampTexture_;
	buw::ReferenceCounted<buw::ISampler> colorRampSampler_;

	SettingsBuffer settings_;

	bool bDrawTerrainWireframe_ = false;
	bool bHideTerrain_ = false;
	bool bTerrainTextured_ = false;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END

#endif // end define OpenInfraPlatform_UserInterface_DEMEffect_fac1f76b_d5ec_452f_9ba1_3878cb359839_h
