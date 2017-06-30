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
#ifndef OpenInfraPlatform_UserInterface_AlignmentEffect_8ae12bd5_fa99_492b_9eda_4b1563bc3edf_h
#define OpenInfraPlatform_UserInterface_AlignmentEffect_8ae12bd5_fa99_492b_9eda_4b1563bc3edf_h

#include "OpenInfraPlatform/Infrastructure/Alignment/AlignmentModel.h"
#include "OpenInfraPlatform/namespace.h"
#include <boost/signals2.hpp>

#include <buw.Rasterizer.h>
#include <map>

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

class AlignmentEffect : public buw::Effect
{
public:
    struct SettingsBuffer {
        BlueFramework::Rasterizer::AlignedTo16Byte::Int bDrawColored = false;
        BlueFramework::Rasterizer::AlignedTo16Byte::Int bHighlightSelected = true;
        BlueFramework::Rasterizer::AlignedTo16Byte::Int bDrawFlattened = false;
        BlueFramework::Rasterizer::AlignedTo16Byte::Int bDrawTextured = false;
        BlueFramework::Rasterizer::AlignedTo16Byte::Int selectedAlignmentIndex = 0;
    };

    struct ColorBuffer {
        BlueFramework::Rasterizer::AlignedTo16Byte::Float4 alignment;
        BlueFramework::Rasterizer::AlignedTo16Byte::Float4 selected;
        BlueFramework::Rasterizer::AlignedTo16Byte::Float4 highlight;
        BlueFramework::Rasterizer::AlignedTo16Byte::Float4 crossSection;
        BlueFramework::Rasterizer::AlignedTo16Byte::Float4 designCrossSection;
        BlueFramework::Rasterizer::AlignedTo16Byte::Float4 clothoid;
        BlueFramework::Rasterizer::AlignedTo16Byte::Float4 arc;
        BlueFramework::Rasterizer::AlignedTo16Byte::Float4 line;
        BlueFramework::Rasterizer::AlignedTo16Byte::Float4 bloss;
        BlueFramework::Rasterizer::AlignedTo16Byte::Float4 roadBody;
        BlueFramework::Rasterizer::AlignedTo16Byte::Float4 roadBodyConvex;
        BlueFramework::Rasterizer::AlignedTo16Byte::Float4 roadBodyConcave;

    };

	AlignmentEffect::AlignmentEffect(
        buw::IRenderSystem* renderSystem,
        buw::ReferenceCounted<buw::IViewport> viewport,
        buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA,
        buw::ReferenceCounted<buw::ITexture2D> pickBuffer,
        buw::ReferenceCounted<buw::ITexture2D> depthStencil,
		buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer,
        buw::ReferenceCounted<buw::IConstantBuffer> viewportBuffer,
        buw::ReferenceCounted<buw::IConstantBuffer> pickIdBuffer = nullptr);

	~AlignmentEffect();

	boost::signals2::signal<void(const unsigned int&)> AlignmentSelectionChanged;

    void enableAlignmentColor(const bool checked);
    void enableHighlightSelected(const bool checked);

    void showCrossSections(const bool checked);
    void showDesignCrossSections(const bool checked);
    void showRoadBodyWireframe(const bool checked);
    void showRoadBodySolid(const bool checked);

    void drawRoadBodyTextured(const bool checked);
    void drawFlattened(const bool checked);

	void setAlignment(buw::ReferenceCounted<buw::AlignmentModel> alignmentModel, buw::Vector3d& offset);
	void loadShader();

	void setCurrentSelectedAlignment(const int index);
    void setColors(std::vector<buw::Vector4f> colors);

    int getAlignmentId(UINT pickId);

private:
	void v_init();
	void v_render();

    void updateSettingsBuffer();
    void updateColorBuffer();

private:
	buw::ReferenceCounted<buw::IPipelineState>
        lineStripState_ = nullptr,
        lineListState_ = nullptr,
        triangleListState_ = nullptr,
        pickLineStripState_ = nullptr,
        pickLineListState_ = nullptr,
        pickTriangleListState_ = nullptr;

	buw::ReferenceCounted<buw::IViewport>  viewport_ = nullptr;
	buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA_ = nullptr;
    buw::ReferenceCounted<buw::ITexture2D> pickBuffer_ = nullptr;
    buw::ReferenceCounted<buw::ITexture2D> depthStencil_ = nullptr;

	buw::ReferenceCounted<buw::ITexture2D> roadBodyTexture_ = nullptr;
	buw::ReferenceCounted<buw::ITexture2D> roadBodyNormalTexture_ = nullptr;
	buw::ReferenceCounted<buw::ISampler>   sampler_ = nullptr;


	buw::ReferenceCounted<buw::IConstantBuffer>
        worldBuffer_ = nullptr,
        viewportBuffer_ = nullptr,
        settingsBuffer_ = nullptr,
        colorBuffer_ = nullptr,
        pickIdBuffer_ = nullptr;

	std::vector<buw::ReferenceCounted<buw::IVertexBuffer>>
        vertexBuffersAlignment_,
        crossSectionVertexBuffers_,
        designCrossSectionVertexBuffers_,
        roadBodyWireframeVertexBuffers_,
        roadBodySolidVertexBuffers_;

    std::map<UINT, int> alignmentIds_;

    SettingsBuffer settings_;
    ColorBuffer colors_;

    bool
        bShowCrossSections_ = false,
        bShowDesignCrossSections_ = false,
        bShowRoadBodyWireframe_ = false,
        bShowRoadBodySolid_ = false;

    UINT currentSelectedPickId_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END

#endif // end define OpenInfraPlatform_UserInterface_AlignmentEffect_8ae12bd5_fa99_492b_9eda_4b1563bc3edf_h
