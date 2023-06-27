/*
Copyright (c) 2021 Technical University of Munich
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
#ifndef OpenInfraPlatform_UserInterface_OsmGeometryEffect_7759dd4a_7404_4bcb_905e_b26a77541c80_h
#define OpenInfraPlatform_UserInterface_OsmGeometryEffect_7759dd4a_7404_4bcb_905e_b26a77541c80_h

#include "OsmDataConverter\OsmDataModel.h"
#include <Resources/EffectBase.h>
#include <map>

#include "..\namespace.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_BEGIN

class OsmGeometryEffect : public EffectBase
{
public:

	// Construct by providing the renderSystem, viewport, depthStencil and worldBuffer for camera etc.
	OsmGeometryEffect(buw::IRenderSystem* renderSystem,
		buw::ReferenceCounted<buw::IViewport> viewport,
		buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA,
		buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer);

	// Release all resources
	virtual ~OsmGeometryEffect();

	void setOsmModel(buw::ReferenceCounted<Core::OsmDataConverter::OsmModel> osmModel);

private:
	void v_init();
	void v_render();

	//! EffectBase interface - change offset to the new value
	virtual void changeOffset(const buw::Vector3d& offsetOld, const buw::Vector3d& offsetNew) override;
private:
	buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer_ = nullptr;
	buw::ReferenceCounted<buw::IVertexBuffer> vertexBuffer_ = nullptr;
	buw::ReferenceCounted<buw::IIndexBuffer> indexBuffer_ = nullptr;
	buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA_ = nullptr;
	buw::ReferenceCounted<buw::IPipelineState> pipelineState_ = nullptr;
	buw::ReferenceCounted<buw::IViewport> viewport_ = nullptr;

	buw::ReferenceCounted<Core::OsmDataConverter::OsmModel> osmModel_ = nullptr;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_END

EMBED_RENDERING_INTO_OIP_NAMESPACE(OsmGeometryEffect)

#endif //end define OpenInfraPlatform_UserInterface_OsmGeometryEffect_7759dd4a_7404_4bcb_905e_b26a77541c80_h