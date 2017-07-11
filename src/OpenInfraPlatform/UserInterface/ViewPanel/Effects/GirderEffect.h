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

#ifndef __GIRDEREFFECT_H_EBABE06AB67A499EBD4392E96872094E__
#define __GIRDEREFFECT_H_EBABE06AB67A499EBD4392E96872094E__

#include "SectionedSolidEffect.h"
#include <OpenInfraPlatform/Infrastructure/Girder/GirderModel.h>
#include <OpenInfraPlatform/namespace.h>

#include <BlueFramework/Core/memory.h>
#include <BlueFramework/Core/Math/Vector.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

class GirderEffect : public SectionedSolidEffect
{
public:
	explicit GirderEffect::GirderEffect(
        buw::IRenderSystem* renderSystem,
        buw::ReferenceCounted<buw::IViewport> viewport,
        buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA,
		buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer,
        buw::ReferenceCounted<buw::IConstantBuffer> viewportBuffer);
	virtual ~GirderEffect();

	void setData(buw::ReferenceCounted<buw::GirderModel> girderModel, buw::Vector3d const& offset);
};

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END

#endif // __GIRDEREFFECT_H_EBABE06AB67A499EBD4392E96872094E__
