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
#ifndef OpenInfraPlatform_UserInterface_GradientClearEffect_afbb68df_d61c_4c33_97ea_562ed68cda3c_h
#define OpenInfraPlatform_UserInterface_GradientClearEffect_afbb68df_d61c_4c33_97ea_562ed68cda3c_h

#include "OpenInfraPlatform/UserInterface/ViewPanel/Viewport.h"

#include "OpenInfraPlatform/Benchmark.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/RenderResources.h"
#include "OpenInfraPlatform/namespace.h"

#include <buw.Engine.h>
#include <buw.Rasterizer.h>

#include <QDir>
#include <QTimer>
#include <QtXml>
#include <QtXmlPatterns>

#include <iomanip>

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

class GradientClearEffect : public buw::Effect {
public:
	struct ShaderVariables {
		BlueFramework::Rasterizer::AlignedTo16Byte::Float time;
		BlueFramework::Rasterizer::AlignedTo16Byte::Float2 resolution;
		BlueFramework::Rasterizer::AlignedTo16Byte::Float2 mouse;
		BlueFramework::Rasterizer::AlignedTo16Byte::Int snow;
	};

	GradientClearEffect(buw::IRenderSystem* renderSystem, buw::ReferenceCounted<buw::IViewport> viewport);

	void loadShader();

private:
	void v_init();

	void v_render();

public:
	void toggleSnow();

private:
	buw::ReferenceCounted<buw::IPipelineState>	pipelineState_;
	buw::ReferenceCounted<buw::IViewport>		viewport_;
	buw::ReferenceCounted<buw::IConstantBuffer> constantBuffer_;
	std::chrono::nanoseconds					start_;
	bool										snow_ = false;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END

#endif // end define OpenInfraPlatform_UserInterface_GradientClearEffect_afbb68df_d61c_4c33_97ea_562ed68cda3c_h
