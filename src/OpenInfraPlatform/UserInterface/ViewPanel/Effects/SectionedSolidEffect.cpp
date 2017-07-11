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
	, vertexLayout_(buw::VertexPosition3Normal3::getVertexLayout())
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
	typedef std::vector<buw::VertexPosition3Normal3> ProfileSegment;
	typedef std::vector<ProfileSegment> Profile;
	std::vector<Profile> xformedProfiles;
	for (size_t i = 0; i < numAnchors; ++i)
	{
		buw::Vector2f const anchorNormal(tangentAndNormalVector[i].second.cast<float>());
		auto const& rotation2D = buw::createRotationMatrix(anchorNormal);
		auto const& profile = profiles[i];
		xformedProfiles.push_back(Profile());
		for (auto const& segment : profile->segments)
		{
			ProfileSegment xformedSegment(segment.size());
			std::transform(segment.begin(), segment.end(), xformedSegment.begin(),
				[&xformedAnchors, &rotation2D, i](Infrastructure::SectionedSolid::CrossSectionProfile::Vertex const& p)->buw::VertexPosition3Normal3 {
				buw::Vector3f sweptPosition(p.position[0], 0.0f, p.position[1]);
				sweptPosition.block<2, 1>(0, 0) = rotation2D * sweptPosition.block<2, 1>(0, 0);
				buw::Vector3f sweptNormal(p.normal[0], 0.0f, p.normal[1]);
				sweptNormal.block<2, 1>(0, 0) = rotation2D * sweptNormal.block<2, 1>(0, 0);
				return buw::VertexPosition3Normal3(sweptPosition + xformedAnchors[i], sweptNormal);
			});
			xformedProfiles.back().push_back(xformedSegment);
		}
	}

	// Create the vertex buffer(s) for rendering.
	buw::vertexBufferDescription vbd;
	vbd.vertexLayout = vertexLayout_;
	if (bRenderProfiles_)
	{
		for (auto& profile : xformedProfiles)
		{
			for (auto& segment : profile)
			{
				// We must repeat the first and last points, because we use adjacency in the geometry shader.
				segment.insert(segment.begin(), segment.front());
				segment.push_back(segment.back());

				// Upload the geometry.
				vbd.data = &segment[0];
				vbd.vertexCount = segment.size();
				vertexBuffers_.push_back(renderSystem()->createVertexBuffer(vbd));
			}
		}
	}
	else
	{
		size_t const lastProfileIdx = xformedProfiles.size() - 1;
		for (size_t i = 0; i < lastProfileIdx; ++i)
		{
			auto const& lastProfile = xformedProfiles[i];
			auto const& profile = xformedProfiles[i+1];
			if(lastProfile.size() != profile.size())
				throw buw::Exception("Mismatch between number of profile segments.");
			if (profile.empty()) continue;

			for (size_t j = 0; j < profile.size(); ++j)
			{
				auto const& lastSegment = lastProfile[j];
				auto const& segment = profile[j];

				// For a triangle strip we must zip both profiles.
				std::vector<buw::VertexPosition3Normal3> solid(2 * segment.size());
				for (size_t k = 0; k < segment.size(); ++k)
				{
					// CW winding for front faces.
					solid[2 * k] = segment[k];
					solid[2 * k + 1] = lastSegment[k];
				}

				// Upload the geometry.
				vbd.data = &solid[0];
				vbd.vertexCount = solid.size();
				vertexBuffers_.push_back(renderSystem()->createVertexBuffer(vbd));
			}
		}
	}

	return true;
}

void SectionedSolidEffect::loadShader()
{
	try
	{
		buw::pipelineStateDescription psd;
		psd.effectFilename = buw::Singleton<RenderResources>::instance().getResourceRootDir() + "/Shader/SectionedSolidEffect.be";
		psd.pipelineStateName = bRenderProfiles_ ? "lineStrip" : "triangleStrip";
		psd.vertexLayout = vertexLayout_;
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
