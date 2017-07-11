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

#include "GirderEffect.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

GirderEffect::GirderEffect(
	buw::IRenderSystem* renderSystem,
	buw::ReferenceCounted<buw::IViewport> viewport,
	buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA,
	buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer,
	buw::ReferenceCounted<buw::IConstantBuffer> viewportBuffer)
	: SectionedSolidEffect(renderSystem, viewport, depthStencilMSAA, worldBuffer, viewportBuffer, buw::Vector4f(0.45f, 0.0f, 0.0f, 1.0f))
{
}

GirderEffect::~GirderEffect()
{
}

void GirderEffect::setData(buw::ReferenceCounted<buw::GirderModel> girderModel, buw::Vector3d const& offset)
{
	clearData();

	for (auto girder : girderModel->getAllItems())
		for (auto ssh : girder->getSectionedSolids())
			addData(ssh, offset);
}

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END
