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
#ifndef OpenInfraPlatform_UserInterface_IfcGeometryEffect_d170662a_b003_4afa_a25b_a9d772f3013d_h
#define OpenInfraPlatform_UserInterface_IfcGeometryEffect_d170662a_b003_4afa_a25b_a9d772f3013d_h
#include "IfcGeometryConverter/ConverterBuw.h"
#include <map>

#include "../Resources/EffectBase.h"
#include "..\namespace.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_BEGIN

class IfcGeometryEffect : public EffectBase {
public:
    IfcGeometryEffect(buw::IRenderSystem* renderSystem,
        buw::ReferenceCounted<buw::IViewport> viewport,
        buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA,
        buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer);

    virtual ~IfcGeometryEffect();

    void setIfcGeometryModel(buw::ReferenceCounted<Core::IfcGeometryConverter::IfcModel> ifcGeometryModel);

private:
    void v_init();
    void v_render();

	//! EffectBase interface - change offset to the new value
	virtual void changeOffset(const buw::Vector3d& offsetOld, const buw::Vector3d& offsetNew) override;

private:
    buw::ReferenceCounted<buw::IPipelineState> meshPipelineState_ = nullptr, polylinePipelineState_ = nullptr;
    buw::ReferenceCounted<buw::IVertexBuffer> meshVertexBuffer_ = nullptr, polylineVertexBuffer_ = nullptr;
    buw::ReferenceCounted<buw::IIndexBuffer> meshIndexBuffer_ = nullptr, polylineIndexBuffer_ = nullptr;
    buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer_ = nullptr;
    buw::ReferenceCounted<buw::IViewport> viewport_ = nullptr;
    buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA_ = nullptr;
    bool valid_ = false;

	buw::ReferenceCounted<Core::IfcGeometryConverter::IfcModel> ifcGeometryModel_ = nullptr;

};

OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_END

EMBED_RENDERING_INTO_OIP_NAMESPACE(IfcGeometryEffect)
#endif // end define OpenInfraPlatform_UserInterface_IfcGeometryEffect_d170662a_b003_4afa_a25b_a9d772f3013d_h
