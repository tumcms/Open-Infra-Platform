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

#include "OpenInfraPlatform/UserInterface/ViewPanel/Effects/UIElementsEffect.h"

#include <QPainter>

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

buw::Vector3i deg2num(const buw::Vector2f& pos, int zoom)
{
	float lat_rad = pos.x() * buw::constantsf::pi() / 180.f;
	float n = pow(2.0, zoom);
	int xtile = int((pos.y() + 180.0) / 360.0 * n);
	int ytile = int((1.0 - log(tan(lat_rad) + (1 / cos(lat_rad))) / buw::constantsf::pi()) / 2.0 * n);
	return{ xtile, ytile , zoom };
}


void UIElements::loadMap()
{
	int z = 10;
	buw::Vector2f bottomLeft(48.031723345155655, 11.359176635742188);
	buw::Vector2f topRight(48.247540092186156, 11.82403564453125);

	buw::Vector3i bottomLeftTile = deg2num(bottomLeft, z);
	buw::Vector3i topRightTile = deg2num(topRight, z);

	buw::Vector3i minTile = buw::minimizedVector(bottomLeftTile, topRightTile);
	buw::Vector3i maxTile = buw::maximizedVector(bottomLeftTile, topRightTile);

	int sX = maxTile.x() - minTile.x() + 1;
	int sY = maxTile.y() - minTile.y() + 1;

	QImage finalImage(sX * 256, sY * 256, QImage::Format_ARGB32);
	QPainter painter(&finalImage);

	for (int i = 0; i < sX; i++)
	{
		for (int j = 0; j < sY; j++)
		{
			int x = minTile.x() + i;
			int y = minTile.y() + j;

			std::string uri = "http://a.tile.osm.org/" + std::to_string(z) + "/" + std::to_string(x) + "/" + std::to_string(y) + ".png";
			std::vector<char> bytes = buw::downloadBytes(uri);
			QByteArray array(&bytes[0], bytes.size());

			std::string filename = "tile_" + std::to_string(x) + "_" + std::to_string(y) + ".png";

			QImage image;
			image.loadFromData(array, "PNG");
			image.save(filename.c_str(), "PNG");
			image = image.convertToFormat(QImage::Format_ARGB32);
			painter.drawImage(i * 256, j * 256, image);
		}
	}

	finalImage.convertToFormat(QImage::Format_RGBA8888);

	buw::Image4b image2(finalImage.width(), finalImage.height());
	for (int x = 0; x < image2.getWidth(); x++)
	{
		for (int y = 0; y < image2.getHeight(); y++)
		{
			QColor color = finalImage.pixelColor(x, y);
			image2.setPixelColor(x, y, buw::Color4b(color.red(), color.green(), color.blue(), 1));
		}
	}

	buw::texture2DDescription td;
	td.data = image2.getData();
	td.width = image2.getWidth();
	td.height = image2.getHeight();
	td.format = buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB;
	td.isCpuReadable = false;
	td.isCpuWriteable = false;
	td.useMSAA = false;
	mapTexture_ = renderSystem()->createTexture2D(td, buw::eTextureBindType::SRV);


	buw::VertexPosition4 vertices[4] = 
	{
		{{0, 300, 0, 1}}, {{300, 300, 1, 1}},
		{{0, 0, 0, 0} }, { {300, 0, 1, 0} }
	};

	buw::vertexBufferDescription vbd;
	vbd.data = vertices;
	vbd.vertexCount = 4;
	vbd.vertexLayout = buw::VertexPosition4::getVertexLayout();

	mapBuffer_ = renderSystem()->createVertexBuffer(vbd);

	buw::samplerStateDescription ssd;
	ssd.minificationFilter = buw::eFilter::Linear;
	ssd.magnificationFilter = buw::eFilter::Linear;
	ssd.mipLevelFilter = buw::eFilter::None;
	ssd.textureAddressModeU = buw::eTextureAddressMode::Clamp;
	ssd.textureAddressModeV = buw::eTextureAddressMode::Clamp;
	ssd.textureAddressModeW = buw::eTextureAddressMode::Clamp;
	linearSampler_ = renderSystem()->createSampler(ssd);
}

void UIElements::v_render() {
	setPipelineState(pipelineState_);
	setRenderTarget(renderSystem()->getBackBufferTarget(), depthStencil_);
	setViewport(viewport_);

	setConstantBuffer(worldBuffer_, "WorldBuffer");
	setConstantBuffer(viewportBuffer_, "ViewportBuffer");

	setVertexBuffer(vertexCacheLine_->vertexBuffer());
	draw(vertexCacheLine_->getSize());


	setPipelineState(mapState_);
	setRenderTarget(renderSystem()->getBackBufferTarget(), depthStencil_);

	setConstantBuffer(worldBuffer_, "WorldBuffer");
	setTexture(mapTexture_, "mapTexture");
	setSampler(linearSampler_, "sampler_");
	setViewport(mapViewport_);

	setVertexBuffer(mapBuffer_);
	draw(4);
}


void UIElements::v_init() {
	try {
		int width = renderSystem()->getBackBufferTarget()->width();
		int height = renderSystem()->getBackBufferTarget()->height();

		buw::viewportDescription vpd(std::min(width, 130), std::min(height, 130), std::max(width - 130, 0));
		viewport_ = renderSystem()->createViewport(vpd);

		buw::constantBufferDescription cbd2;
		cbd2.sizeInBytes = sizeof(ViewportBuffer);
		cbd2.data = nullptr;
		viewportBuffer_ = renderSystem()->createConstantBuffer(cbd2);

		vertexCacheLine_ = buw::makeReferenceCounted<buw::VertexCacheLineT<buw::VertexPosition3Color3Size1>>(renderSystem());

		float size = 1;
		buw::VertexPosition3Color3Size1 points[6] = {{buw::Vector3f(-size, 0, 0), buw::Vector3f(1, 0, 0), 1}, {buw::Vector3f(size, 0, 0), buw::Vector3f(1, 0, 0), 1},
		                                             {buw::Vector3f(0, -size, 0), buw::Vector3f(0, 1, 0), 1}, {buw::Vector3f(0, size, 0), buw::Vector3f(0, 1, 0), 1},
		                                             {buw::Vector3f(0, 0, -size), buw::Vector3f(0, 0, 1), 1}, {buw::Vector3f(0, 0, size), buw::Vector3f(0, 0, 1), 1}};

		vertexCacheLine_->drawLine(points[0], points[1]);
		vertexCacheLine_->drawLine(points[2], points[3]);
		vertexCacheLine_->drawLine(points[4], points[5]);

		vertexCacheLine_->flush();

		loadMap();

		loadShader();

		BLUE_LOG(trace) << "UIElements v_init end.";
	} catch (...) {
		pipelineState_ = nullptr;
		BLUE_LOG(trace) << "Creating uielements effect pipeline state failed.";
	}
}

void UIElements::resize(const buw::viewportDescription& vpd) {
	int size = 130;
	viewport_->resize(buw::viewportDescription(std::min((int)vpd.width, size), std::min((int)vpd.height, size), 0, std::max((int)vpd.height - size, 0)));

	ViewportBuffer buffer = {size, size};

	buw::constantBufferDescription cbd;
	cbd.sizeInBytes = sizeof(ViewportBuffer);
	cbd.data = &buffer;
	viewportBuffer_->uploadData(cbd);
}

void UIElements::loadShader() {
	buw::pipelineStateDescription psd;
	psd.effectFilename = buw::Singleton<RenderResources>::instance().getResourceRootDir() + "/Shader/UIElementsEffect.be";
	psd.pipelineStateName = "";
	psd.vertexLayout = vertexCacheLine_->vertexLayout();
	psd.primitiveTopology = vertexCacheLine_->topology();
	psd.renderTargetFormats = {buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB};
	psd.useDepth = true;
	psd.useMSAA = true;

	BLUE_LOG(trace) << "Before createPipelineState.";
	pipelineState_ = createPipelineState(psd);

	buw::pipelineStateDescription psd2;
	psd2.effectFilename = buw::Singleton<RenderResources>::instance().getResourceRootDir() + "/Shader/UIElementsEffect.be";
	psd2.pipelineStateName = "mapState";
	psd2.vertexLayout = buw::VertexPosition4::getVertexLayout();
	psd2.primitiveTopology = buw::ePrimitiveTopology::TriangleStrip;
	psd2.renderTargetFormats = { buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB };
	psd2.useDepth = true;
	psd2.useMSAA = true;

	BLUE_LOG(trace) << "Before createPipelineState.";
	mapState_ = createPipelineState(psd2);
}

UIElements::UIElements(buw::IRenderSystem* renderSystem, buw::ReferenceCounted<buw::IViewport> viewport, 
	buw::ReferenceCounted<buw::ITexture2D> depthStencil, buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer)
    : Effect(renderSystem), mapViewport_(viewport), depthStencil_(depthStencil), worldBuffer_(worldBuffer) {
	viewport_ = nullptr;
	viewportBuffer_ = nullptr;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END
