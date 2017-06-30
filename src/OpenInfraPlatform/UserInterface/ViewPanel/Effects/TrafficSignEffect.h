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

#include "OpenInfraPlatform/Infrastructure/DigitalElevationModel/DigitalElevationModel.h"
#include "OpenInfraPlatform/namespace.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/RenderResources.h"

#include <buw.Rasterizer.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

class TrafficSignEffect : public buw::Effect {
public:
	struct PlacementBuffer {
		buw::Matrix44f transform;
	};

public:
	TrafficSignEffect(buw::IRenderSystem* renderSystem,
		buw::ReferenceCounted<buw::IViewport> viewport,
		buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA,
		buw::ReferenceCounted<buw::ITexture2D> pickBuffer,
		buw::ReferenceCounted<buw::ITexture2D> depthStencil,
		buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer);

	~TrafficSignEffect();

	void setData(buw::ReferenceCounted<buw::AlignmentModel> alignmentModel,
		buw::Vector3d& offset,
		buw::ReferenceCounted<buw::TrafficSignModel> trafficSignModel);

	buw::Vector3f position_;
	float rotation_;

private:
	void v_init();

	void uploadPlacementBuffer() {
		buw::constantBufferDescription cbd;
		cbd.sizeInBytes = sizeof(PlacementBuffer);
		cbd.data = &placementBuffer_;
		cbPlacementBuffer_->uploadData(cbd);
	}

	void v_render();

	void drawSign(const buw::Vector3f& position, const float roation);

private:
	buw::ReferenceCounted<buw::IConstantBuffer> cbPlacementBuffer_;
	PlacementBuffer placementBuffer_;

	buw::ReferenceCounted<buw::IPipelineState> ps_;

	bool hasTrafficSigns_ = false;
	buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer_;
	buw::ReferenceCounted<buw::IVertexBuffer> vertexBuffer_;
	buw::ReferenceCounted<buw::IIndexBuffer> indexBuffer_;

	buw::VertexLayout vertexLayout;

	// render target
	buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA_;

	buw::ReferenceCounted<buw::IViewport> viewport_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END
