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

#include "SectionedSolidEffect.h"
#include <OpenInfraPlatform/UserInterface/ViewPanel/RenderResources.h>

#include <buw.Rasterizer.h>

#include <algorithm>

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

SectionedSolidEffect::SectionedSolidEffect(
	buw::IRenderSystem* renderSystem,
	buw::ReferenceCounted<buw::IViewport> viewport,
	buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA,
	buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer,
	buw::ReferenceCounted<buw::IConstantBuffer> viewportBuffer,
	buw::Vector4f const& materialColor)
	: Effect(renderSystem)
	, materialColor_(materialColor)
	, pipelineState_()
	, vertexBuffers_()
	, paintColorShaderBuffer_()
	, viewport_(viewport)
	, depthStencilBuffer_(depthStencilMSAA)
	, worldShaderBuffer_(worldBuffer)
	, viewportShaderBuffer_(viewportBuffer)
{
}

SectionedSolidEffect::~SectionedSolidEffect()
{
	pipelineState_ = nullptr;
	vertexBuffers_.clear();
	paintColorShaderBuffer_ = nullptr;

	viewportShaderBuffer_ = nullptr;
	worldShaderBuffer_ = nullptr;
	depthStencilBuffer_ = nullptr;
	viewport_ = nullptr;
}

void SectionedSolidEffect::clearData()
{
	vertexBuffers_.clear();
}

bool SectionedSolidEffect::addData(Infrastructure::SectionedSolidHorizontal const& ssh, buw::Vector3d const& offset)
{
	auto const& anchorPoints = ssh.getAnchors();
	auto const& tangentAndNormalVector = ssh.getTangentsAndNormals();
	auto const& profiles = ssh.getProfiles();

	if(anchorPoints->getNumPoints() != tangentAndNormalVector.size() || anchorPoints->getNumPoints() != profiles.size())
		throw buw::Exception("Mismatch between number of profile positions/tangents and normals/profiles.");

	// Adjust the profile anchor points by the given offset.
	std::vector<buw::Vector3f> xformedAnchors;
	size_t const numAnchors = anchorPoints->getNumPoints();
	for (size_t i = 0; i < numAnchors; ++i)
	{
		buw::Vector3d const& p = anchorPoints->getPoint(i);
		xformedAnchors.push_back((p + offset).cast<float>());
	}
	if (xformedAnchors.empty()) return false;

	// Transform the profiles to their destination in 3D space.
	std::vector<std::vector<buw::Vector3f>> xformedProfiles;
	for (size_t i = 0; i < numAnchors; ++i)
	{
		buw::Vector2f const anchorNormal(tangentAndNormalVector[i].second.cast<float>());
		auto const& rotation2D = buw::createRotationMatrix(anchorNormal);
		auto const& profile = profiles[i];
		std::vector<buw::Vector3f> xformedProfile(profile->pntList2D.size());
		std::transform(profile->pntList2D.begin(), profile->pntList2D.end(), xformedProfile.begin(),
			[&xformedAnchors, &rotation2D, i](buw::Vector2d const& p)->buw::Vector3f {
			buw::Vector3f sweptPoint(p[0], 0.0f, p[1]);
			sweptPoint.block<2, 1>(0, 0) = rotation2D * sweptPoint.block<2, 1>(0, 0);
			return sweptPoint + xformedAnchors[i];
		});
		xformedProfiles.push_back(xformedProfile);
	}

	// Create the vertex buffer(s) for rendering.
	buw::vertexBufferDescription vbd;
	vbd.vertexLayout = buw::VertexPosition3::getVertexLayout();
	if (bRenderProfiles_)
	{
		for (auto& profile : xformedProfiles)
		{
			// We must repeat the first and last points, because we use adjacency in the geometry shader.
			profile.insert(profile.begin(), profile.front());
			profile.push_back(profile.back());

			// Upload the geometry.
			vbd.data = &profile[0];
			vbd.vertexCount = profile.size();
			vertexBuffers_.push_back(renderSystem()->createVertexBuffer(vbd));
		}
	}
	else
	{
		size_t const lastProfileIdx = xformedProfiles.size() - 1;
		for (size_t i = 0; i < lastProfileIdx; ++i)
		{
			auto& lastProfile = xformedProfiles[i];
			auto& profile = xformedProfiles[i+1];
			if(lastProfile.size() != profile.size())
				throw buw::Exception("Mismatch between number of profile points.");
			if (profile.empty()) continue;

			// For a triangle strip we must zip both profiles.
			std::vector<buw::Vector3f> solid(4*profile.size(), buw::Vector3f(-1.0f, 0.0f, 0.0f));
			for (size_t j = 0; j < profile.size(); ++j)
			{
				// CW winding for front faces.
				solid[2*j] = profile[j];
				solid[2*j+1] = lastProfile[j];
			}

			// Upload the geometry.
			vbd.data = &solid[0];
			vbd.vertexCount = solid.size()/2;
			vertexBuffers_.push_back(renderSystem()->createVertexBuffer(vbd));
		}
	}

	return true;
}

void SectionedSolidEffect::loadShader()
{
	try
	{
		buw::VertexLayout vertexLayout;
		vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);
		vertexLayout.add(buw::eVertexAttributeSemantic::Normal, buw::eVertexAttributeFormat::Float3);

		buw::pipelineStateDescription psd;
		psd.effectFilename = buw::Singleton<RenderResources>::instance().getResourceRootDir() + "/Shader/SectionedSolidEffect.be";
		psd.pipelineStateName = bRenderProfiles_ ? "lineStrip" : "triangleStrip";
		psd.vertexLayout = vertexLayout;
		psd.primitiveTopology = bRenderProfiles_ ? buw::ePrimitiveTopology::LineStrip : buw::ePrimitiveTopology::TriangleStrip;
		psd.useAdjacency = bRenderProfiles_;
		psd.renderTargetFormats = { buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB };
		psd.useDepth = true;
		psd.useMSAA = true;
		psd.fillMode = buw::eFillMode::Solid;
		pipelineState_ = createPipelineState(psd);
	}
	catch (...)
	{
		pipelineState_ = nullptr;
	}
}

void SectionedSolidEffect::v_init()
{
	loadShader();

	BlueFramework::Rasterizer::AlignedTo16Byte::Float4 diffuseColor(materialColor_);
	buw::constantBufferDescription cbd;
	cbd.sizeInBytes = sizeof(diffuseColor);
	cbd.data = &diffuseColor;
	paintColorShaderBuffer_ = renderSystem()->createConstantBuffer(cbd);
}

void SectionedSolidEffect::v_render()
{
	if (!pipelineState_ || vertexBuffers_.empty()) return;

	setRenderTarget(renderSystem()->getBackBufferTarget(), depthStencilBuffer_);
	setViewport(viewport_);
	setPipelineState(pipelineState_);
	setConstantBuffer(worldShaderBuffer_, "WorldBuffer");
	setConstantBuffer(viewportShaderBuffer_, "ViewportBuffer");
	setConstantBuffer(paintColorShaderBuffer_, "ColorBuffer");

	for (auto vertexBuffer : vertexBuffers_)
	{
		setVertexBuffer(vertexBuffer);
		draw(UINT(vertexBuffer->getVertexCount()));
	}
}

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END
