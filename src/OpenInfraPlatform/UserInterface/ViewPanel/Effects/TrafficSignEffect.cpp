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

#include "TrafficSignEffect.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

TrafficSignEffect::TrafficSignEffect(buw::IRenderSystem* renderSystem,
                                     buw::ReferenceCounted<buw::IViewport> viewport,
                                     buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA,
                                     buw::ReferenceCounted<buw::ITexture2D> pickBuffer,
                                     buw::ReferenceCounted<buw::ITexture2D> depthStencil,
                                     buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer)
    : Effect(renderSystem), depthStencilMSAA_(depthStencilMSAA), viewport_(viewport), worldBuffer_(worldBuffer) {
	vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);

	buw::constantBufferDescription cbd;
	cbd.sizeInBytes = sizeof(PlacementBuffer);
	cbd.data = &placementBuffer_;
	cbPlacementBuffer_ = renderSystem->createConstantBuffer(cbd);
}

TrafficSignEffect::~TrafficSignEffect() {
	ps_ = nullptr;
}

void TrafficSignEffect::setData(buw::ReferenceCounted<buw::AlignmentModel> alignmentModel, buw::Vector3d& offset, buw::ReferenceCounted<buw::TrafficSignModel> trafficSignModel) {
	hasTrafficSigns_ = false;

	if (trafficSignModel->getTrafficSignCount() > 0) {
		auto ts = trafficSignModel->getTrafficSignByIndex(0);

		if (ts->vertices.size() > 0) {
			buw::vertexBufferDescription vbd;
			vbd.data = &ts->vertices[0];
			vbd.vertexCount = static_cast<int>(ts->vertices.size());
			vbd.vertexLayout = vertexLayout;

			vertexBuffer_ = renderSystem()->createVertexBuffer(vbd);
		}
		else
			vertexBuffer_ = nullptr;

		if (ts->indices.size() > 0) {
			buw::indexBufferDescription idb;
			idb.data = &ts->indices[0];
			idb.indexCount = static_cast<int>(ts->indices.size());
			idb.format = buw::eIndexBufferFormat::UnsignedInt32;

			indexBuffer_ = renderSystem()->createIndexBuffer(idb);
		}
		else
			indexBuffer_ = nullptr;

		hasTrafficSigns_ = true;

		// compute position
		// find corresponding alignment

		buw::Vector3d pos = offset;
		position_ = buw::Vector3f(pos.x(), pos.z(), pos.y());

		if (ts->alignmentId != -1)
		{
			auto a = alignmentModel->getAlignmentById(ts->alignmentId);
			pos = a->getPosition(ts->distanceAlong) + offset;

			buw::Vector3d dir = a->getPosition(ts->distanceAlong + 0.01) - a->getPosition(ts->distanceAlong);
			buw::Vector3d up(0, 0, 1);
			buw::Vector3d lateralDirection = dir.cross(up);
			lateralDirection.normalize();
			pos = pos + (-lateralDirection * ts->offsetLateral);

			position_ = buw::Vector3f(pos.x(), pos.z(), pos.y());
		}
		else {
			hasTrafficSigns_ = false;
		}

		rotation_ = ts->rotation;
	}
}

void TrafficSignEffect::v_init() {
	buw::pipelineStateDescription psd;
	psd.effectFilename = buw::Singleton<RenderResources>::instance().getResourceRootDir() + "/Shader/TrafficSignEffect.be";
	psd.pipelineStateName = "";
	psd.vertexLayout = vertexLayout;
	psd.primitiveTopology = buw::ePrimitiveTopology::TriangleList;
	psd.renderTargetFormats = { buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB };
	psd.useDepth = true;
	psd.useMSAA = true;

	ps_ = createPipelineState(psd);

	//settingsBuffer_ = renderSystem()->createConstantBuffer(cbd);

	//uploadPlacementBuffer();
}

void TrafficSignEffect::v_render() {
	if (hasTrafficSigns_) {

		//for(float t = 0; t < 10; t += 2.0f)
		//	drawSign( buw::Vector3f(0,0,t) );
		drawSign(position_, rotation_);
	}
}

void TrafficSignEffect::drawSign(const buw::Vector3f& position, const float roation) {
	placementBuffer_.transform = buw::createTranslationMatrix(position) * buw::createRotationMatrixY(roation);
	uploadPlacementBuffer();

	buw::ReferenceCounted<buw::ITexture2D> renderTarget = renderSystem()->getBackBufferTarget();

	setPipelineState(ps_);
	setRenderTarget(renderTarget, depthStencilMSAA_);
	setViewport(viewport_);

	setVertexBuffer(vertexBuffer_);
	setIndexBuffer(indexBuffer_);

	setConstantBuffer(worldBuffer_, "WorldBuffer");

	setConstantBuffer(cbPlacementBuffer_, "Placement");

	drawIndexed(static_cast<UINT>(indexBuffer_->getIndexCount()));
}

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END