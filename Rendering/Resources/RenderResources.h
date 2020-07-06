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

#include "../UserInterface/Dialogues/OpenInfraMap.h"
#include <BlueFramework/Rasterizer/IRenderSystem.h>
#include <BlueFramework/Rasterizer/Resources/ISampler.h>
#include "IfcGeometryConverter/ConverterBuw.h"
#include "..\namespace.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_BEGIN

class RenderResources {
public:
    RenderResources();

    void init(buw::ReferenceCounted<buw::IRenderSystem> renderSystem);

    void release();

    std::string getResourceRootDir();

    buw::ReferenceCounted<buw::ISampler> getLinearSampler() const;

private:
    buw::ReferenceCounted<buw::ISampler> linearSampler_;
    std::string resourceRootDir_; // cached resource root dir
};

OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_END

namespace oip { using OpenInfraPlatform::Rendering::RenderResources; }
