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
#ifndef OpenInfraPlatform_UserInterface_SkyboxEffect_34f22a43_6c1f_4b9f_99f5_ca188f4c0343_h
#define OpenInfraPlatform_UserInterface_SkyboxEffect_34f22a43_6c1f_4b9f_99f5_ca188f4c0343_h


#include <buw.ImageProcessing.h>
#include <map>

#include <Resources/EffectBase.h>
#include "..\namespace.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_BEGIN

class SkyboxEffect : public EffectBase {
public:
    SkyboxEffect(buw::IRenderSystem* renderSystem,
                 buw::ReferenceCounted<buw::IViewport> viewport,
                 buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer);

    ~SkyboxEffect();

private:
    void v_init();
    void v_render();

	//! EffectBase interface - do nothing
	virtual void changeOffset(const buw::Vector3d& offsetOld, const buw::Vector3d& offsetNew) override {}
private:
    buw::ReferenceCounted<buw::ISampler> sampler_;
    buw::ReferenceCounted<buw::ITextureCube> texture_;
    buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer_;
    buw::ReferenceCounted<buw::IViewport> viewport_;
    buw::ReferenceCounted<buw::IPipelineState> pipelineState_;
    buw::ReferenceCounted<buw::IVertexBuffer> vertexBuffer_;
    buw::ReferenceCounted<buw::IIndexBuffer> indexBuffer_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_END

EMBED_RENDERING_INTO_OIP_NAMESPACE(SkyboxEffect)
#endif // end define BlueFramework_UserInterface_SkyboxEffect_34f22a43_6c1f_4b9f_99f5_ca188f4c0343_h
