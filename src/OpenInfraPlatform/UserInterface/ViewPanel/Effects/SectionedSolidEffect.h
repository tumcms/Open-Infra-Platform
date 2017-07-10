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

#ifndef __SECTIONEDSOLIDEFFECT_H_3EC0F7DFF422478C9ACC9B2B750D585C__
#define __SECTIONEDSOLIDEFFECT_H_3EC0F7DFF422478C9ACC9B2B750D585C__

#include <OpenInfraPlatform/Infrastructure/SectionedSolid/SectionedSolidHorizontal.h>
#include <OpenInfraPlatform/namespace.h>

#include <buw.Rasterizer.h>
#include <BlueFramework/Core/memory.h>
#include <BlueFramework/Core/Math/Vector.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

class SectionedSolidEffect : public buw::Effect
{
public:
	explicit SectionedSolidEffect::SectionedSolidEffect(
        buw::IRenderSystem* renderSystem,
        buw::ReferenceCounted<buw::IViewport> viewport,
        buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA,
		buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer,
        buw::ReferenceCounted<buw::IConstantBuffer> viewportBuffer,
		buw::Vector4f const& materialColor);
	virtual ~SectionedSolidEffect();

	void loadShader();

protected:
	void clearData();
	bool addData(Infrastructure::SectionedSolidHorizontal const& ssh, buw::Vector3d const& offset);

private:
	void v_init();
	void v_render();

	bool bRenderProfiles_ = false; // For debugging.

	buw::Vector4f const materialColor_;
	buw::VertexLayout const vertexLayout_;

	buw::ReferenceCounted<buw::IPipelineState> pipelineState_;
	std::vector<buw::ReferenceCounted<buw::IVertexBuffer>> vertexBuffers_;
	buw::ReferenceCounted<buw::IConstantBuffer> paintColorShaderBuffer_;

	buw::ReferenceCounted<buw::IViewport>  viewport_;
	buw::ReferenceCounted<buw::ITexture2D> depthStencilBuffer_;
	buw::ReferenceCounted<buw::IConstantBuffer> worldShaderBuffer_;
	buw::ReferenceCounted<buw::IConstantBuffer> viewportShaderBuffer_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END

#endif // __SECTIONEDSOLIDEFFECT_H_3EC0F7DFF422478C9ACC9B2B750D585C__
