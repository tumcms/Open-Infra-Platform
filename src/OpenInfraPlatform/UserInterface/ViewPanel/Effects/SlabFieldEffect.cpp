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

#include "SlabFieldEffect.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

SlabFieldEffect::SlabFieldEffect(
	buw::IRenderSystem* renderSystem,
	buw::ReferenceCounted<buw::IViewport> viewport,
	buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA,
	buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer,
	buw::ReferenceCounted<buw::IConstantBuffer> viewportBuffer)
	: SectionedSolidEffect(renderSystem, viewport, depthStencilMSAA, worldBuffer, viewportBuffer, buw::Vector4f(0.6f, 0.6f, 0.6f, 1.0f))
{
}

SlabFieldEffect::~SlabFieldEffect()
{
}

void SlabFieldEffect::setData(buw::ReferenceCounted<buw::SlabFieldModel> slabFieldModel, buw::Vector3d const& offset)
{
	clearData();

	for (auto slabFieldElem : slabFieldModel->getAllItems())
		for (auto ssh : slabFieldElem->getSectionedSolids())
			addData(ssh, offset);
}

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END
