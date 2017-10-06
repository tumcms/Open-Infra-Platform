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

#include "OpenInfraPlatform/UserInterface/ViewPanel/Effects/BoundingBoxEffect.h"

#include <QPainter>

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

//taken from the javascript of http://www.deine-berge.de/umrechner_koordinaten.php
buw::Vector2d pod2wgs(const buw::Vector2d& pod)
{
	// Geographische L�nge lp und Breite bp im Potsdam Datum
	double lp = pod.y();
	double bp = pod.x();

	// Quellsystem Potsdam Datum
	//  Grosse Halbachse a und Abplattung fq
	constexpr double a = 6378137.000 - 739.845;
	constexpr double fq = 3.35281066e-3 - 1.003748e-05;

	// Zielsystem WGS84 Datum
	//  Abplattung f
	constexpr double f = 3.35281066e-3;

	// Parameter fuer datum shift
	constexpr double dx = 587;
	constexpr double dy = 16;
	constexpr double dz = 393;

	// Quadrat der ersten numerischen Exzentrizitaet in Quell- und Zielsystem
	constexpr double e2q = (2 * fq - fq * fq);
	constexpr double e2 = (2 * f - f * f);

	// Breite und Laenge in Radianten
	constexpr double pi = M_PI;
	double b1 = bp * (pi / 180);
	double l1 = lp * (pi / 180);

	// Querkruemmungshalbmesser nd
	double nd = a / sqrt(1 - e2q * sin(b1) * sin(b1));

	// Kartesische Koordinaten des Quellsystems Potsdam
	double xp = nd * cos(b1) * cos(l1);
	double yp = nd * cos(b1) * sin(l1);
	double zp = (1 - e2q) * nd * sin(b1);

	// Kartesische Koordinaten des Zielsystems (datum shift) WGS84
	double x = xp + dx;
	double y = yp + dy;
	double z = zp + dz;

	// Berechnung von Breite und Laenge im Zielsystem
	double rb = sqrt(x * x + y * y);
	double b2 = (180 / pi) * atan((z / rb) / (1 - e2));

	double l2 = (180 / pi) * atan2(y, x);

	return buw::Vector2d(b2, l2);
}

buw::Vector2d wgs2pod(const buw::Vector2d& wgs)
{
	// Geographische Länge lw und Breite bw im WGS84 Datum	
	double lw = wgs.y();
	double bw = wgs.x();

	// Quellsystem WGS84 Datum
	// Große Halbachse a und Abplattung fq
	double a = 6378137.000;
	double fq = 3.35281066e-3;

	// Zielsystem Potsdam Datum
	// Abplattung f
	double f = fq - 1.003748e-5;

	// Parameter für datum shift
	double dx = -587;
	double dy = -16;
	double dz = -393;

	// Quadrat der ersten numerischen Exzentrizität in Quell- und Zielsystem
	double e2q = (2 * fq - fq*fq);
	double e2 = (2 * f - f*f);

	// Breite und Länge in Radianten
	double pi = M_PI;
	double b1 = bw * (pi / 180);
	double l1 = lw * (pi / 180);

	// Querkrümmungshalbmesser nd
	double nd = a / std::sqrt(1 - e2q * std::sin(b1) * std::sin(b1));

	// Kartesische Koordinaten des Quellsystems WGS84
	double xw = nd * std::cos(b1) * std::cos(l1);
	double yw = nd * std::cos(b1) * std::sin(l1);
	double zw = (1 - e2q) * nd * std::sin(b1);

	//  Kartesische Koordinaten des Zielsystems (datum shift) Potsdam
	double x = xw + dx;
	double y = yw + dy;
	double z = zw + dz;

	// Berechnung von Breite und Länge im Zielsystem
	double rb = std::sqrt(x*x + y*y);
	double b2 = (180 / pi) * std::atan((z / rb) / (1 - e2));

	double l2 = 0;
	if (x > 0)
		l2 = (180 / pi) * std::atan(y / x);
	if (x < 0 && y > 0)
		l2 = (180 / pi) * std::atan(y / x) + 180;
	if (x < 0 && y < 0)
		l2 = (180 / pi) * std::atan(y / x) - 180;


	//if (lp < 5 || lp > 16 || bp < 46 || bp > 56) return;

	return { b2, l2 };
}

//taken from the javascript of http://www.deine-berge.de/umrechner_koordinaten.php
buw::Vector2d gk2wgs(const buw::Vector2d& gk)
{
	double rw = gk.x();
	double hw = gk.y();

	//  Potsdam Datum / Bessel Ellipsoid
	// Grosse Halbachse a und Abplattung f
	constexpr double a = 6377397.155;
	constexpr double f = 3.34277321e-3; // = 1/299.1528128 
	constexpr double pi = M_PI;

	// Polkruemmungshalbmesser c
	constexpr double c = a / (1 - f);

	// Quadrat der zweiten numerischen Exzentrizitaet
	constexpr double ex2 = (2 * f - f * f) / ((1 - f) * (1 - f));
	constexpr double ex4 = ex2 * ex2;
	constexpr double ex6 = ex4 * ex2;
	constexpr double ex8 = ex4 * ex4;

	// Koeffizienten zur Berechnung der geographischen Breite aus gegebener
	// Meridianbogenlaenge
	constexpr double e0 = c * (pi / 180) * (1 - 3 * ex2 / 4 + 45 * ex4 / 64 - 175 * ex6 / 256 + 11025 * ex8 / 16384);
	constexpr double f2 = (180 / pi) * (3 * ex2 / 8 - 3 * ex4 / 16 + 213 * ex6 / 2048 - 255 * ex8 / 4096);
	constexpr double f4 = (180 / pi) * (21 * ex4 / 256 - 21 * ex6 / 256 + 533 * ex8 / 8192);
	constexpr double f6 = (180 / pi) * (151 * ex6 / 6144 - 453 * ex8 / 12288);

	// Geographische Breite bf zur Meridianbogenlaenge gf = hw
	double sigma = hw / e0;
	double sigmr = sigma * pi / 180;
	double bf = sigma + f2 * sin(2 * sigmr) + f4 * sin(4 * sigmr) + f6 * sin(6 * sigmr);

	// Breite bf in Radianten
	double br = bf * pi / 180;
	double tan1 = tan(br);
	double tan2 = tan1 * tan1;
	double tan4 = tan2 * tan2;

	double cos1 = cos(br);
	double cos2 = cos1 * cos1;

	double etasq = ex2 * cos2;

	// Querkruemmungshalbmesser nd
	double nd = c / sqrt(1 + etasq);
	double nd2 = nd * nd;
	double nd4 = nd2 * nd2;
	double nd6 = nd4 * nd2;
	double nd3 = nd2 * nd;
	double nd5 = nd4 * nd;

	//  Laengendifferenz dl zum Bezugsmeridian lh
	double kz = static_cast<int>(rw / 1e6);
	double lh = kz * 3;
	double dy = rw - (kz * 1e6 + 500000);
	double dy2 = dy * dy;
	double dy4 = dy2 * dy2;
	double dy3 = dy2 * dy;
	double dy5 = dy4 * dy;
	double dy6 = dy3 * dy3;

	double b2 = -tan1 * (1 + etasq) / (2 * nd2);
	double b4 = tan1 * (5 + 3 * tan2 + 6 * etasq * (1 - tan2)) / (24 * nd4);
	double b6 = -tan1 * (61 + 90 * tan2 + 45 * tan4) / (720 * nd6);

	double l1 = 1 / (nd * cos1);
	double l3 = -(1 + 2 * tan2 + etasq) / (6 * nd3 * cos1);
	double l5 = (5 + 28 * tan2 + 24 * tan4) / (120 * nd5 * cos1);

	// Geographischer Breite bp und Laenge lp als Funktion von Rechts- und Hochwert
	double lat = bf + (180 / pi) * (b2 * dy2 + b4 * dy4 + b6 * dy6);
	double lng = lh + (180 / pi) * (l1 * dy + l3 * dy3 + l5 * dy5);

	return pod2wgs(buw::Vector2d(lat, lng));
}


buw::Vector2d wgs2gk(const buw::Vector2d& wgs) 
{
	// Geographische Länge lp und Breite bp im Potsdam Datum
	buw::Vector2d pod = wgs2pod(wgs);

	double lp = pod.y();
	double bp = pod.x();

	// Zonen	
	//	2: 5-7,5
	//	3: 7,5-10,5
	//	4: 10,5-13,5
	//	5: 13,5-16
	// Grenzen des Gauss-Krüger-Systems für Deutschland 46° N < bp < 55° N,
	//                                                   5° E < lp < 16° E

	// Potsdam Datum
	// Große Halbachse a und Abplattung f
	double a = 6377397.15508;
	double f = 3.34277321e-3;
	double pi = M_PI;

	// Polkrümmungshalbmesser c
	double c = a / (1 - f);

	// Quadrat der zweiten numerischen Exzentrizität
	double ex2 = (2 * f - f*f) / ((1 - f)*(1 - f));
	double ex4 = ex2*ex2;
	double ex6 = ex4*ex2;
	double ex8 = ex4*ex4;

	// Koeffizienten zur Berechnung der Meridianbogenlänge
	double e0 = c*(pi / 180)*(1 - 3 * ex2 / 4 + 45 * ex4 / 64 - 175 * ex6 / 256 + 11025 * ex8 / 16384);
	double e2 = c*(-3 * ex2 / 8 + 15 * ex4 / 32 - 525 * ex6 / 1024 + 2205 * ex8 / 4096);
	double e4 = c*(15 * ex4 / 256 - 105 * ex6 / 1024 + 2205 * ex8 / 16384);
	double e6 = c*(-35 * ex6 / 3072 + 315 * ex8 / 12288);

	// Breite in Radianten
	double br = bp * pi / 180;

	double tan1 = std::tan(br);
	double tan2 = tan1*tan1;
	double tan4 = tan2*tan2;

	double cos1 = std::cos(br);
	double cos2 = cos1*cos1;
	double cos4 = cos2*cos2;
	double cos3 = cos2*cos1;
	double cos5 = cos4*cos1;

	double etasq = ex2*cos2;

	// Querkrümmungshalbmesser nd
	double nd = c / std::sqrt(1 + etasq);

	// Meridianbogenlänge g aus gegebener geographischer Breite bp
	double g = e0*bp + e2 * std::sin(2 * br) + e4 * std::sin(4 * br) + e6 * std::sin(6 * br);

	// Längendifferenz dl zum Bezugsmeridian lh
	double kz = (int)((lp + 1.5) / 3);
	double lh = kz * 3;
	double dl = (lp - lh)*pi / 180;
	double dl2 = dl*dl;
	double dl4 = dl2*dl2;
	double dl3 = dl2*dl;
	double dl5 = dl4*dl;

	// Hochwert hw und Rechtswert rw als Funktion von geographischer Breite und Länge
	double hw = (g + nd*cos2*tan1*dl2 / 2 + nd*cos4*tan1*(5 - tan2 + 9 * etasq)*dl4 / 24);
	double rw = (nd*cos1*dl + nd*cos3*(1 - tan2 + etasq)*dl3 / 6 +
		nd*cos5*(5 - 18 * tan2 + tan4)*dl5 / 120 + kz*1e6 + 500000);

	return { rw, hw };
}

buw::Vector2i deg2num(const buw::Vector2d& pos, int zoom)
{
	double lat_rad = pos.x() * buw::constantsd::pi() / 180.0;
	double n = pow(2, zoom);
	int xtile = int((pos.y() + 180.0) / 360.0 * n);
	int ytile = int((1.0 - log(tan(lat_rad) + (1 / cos(lat_rad))) / buw::constantsf::pi()) / 2.0 * n);
	return { xtile, ytile };
}

buw::Vector2d num2deg(const buw::Vector2i& tile, int zoom)
{
	double n = pow(2, zoom);
	double lon_deg = tile.x() / n * 360.0 - 180.0;
	double lat_rad = std::atan(std::sinh(buw::constantsd::pi() * (1 - 2 * tile.y() / n)));
	double lat_deg = lat_rad * 180 / buw::constantsd::pi();
	return{ lat_deg, lon_deg };
}

void BoundingBoxEffect::loadMap()
{
	int z = 16;
	
	buw::Vector2d wgsSouthEast = gk2wgs(minExtend_.block<2,1>(0,0));
	buw::Vector2d wgsNorthWest = gk2wgs(maxExtend_.block<2, 1>(0, 0));

	buw::Vector2i bottomLeftTile = deg2num(wgsSouthEast, z);
	buw::Vector2i topRightTile = deg2num(wgsNorthWest, z);

	int sX = topRightTile.x() - bottomLeftTile.x() + 1;
	int sY = bottomLeftTile.y() - topRightTile.y() + 1;

	QImage finalImage(sX * 256, sY * 256, QImage::Format_ARGB32);
	QPainter painter(&finalImage);

	for (int i = 0; i < sX; i++)
	{
		for (int j = 0; j < sY; j++)
		{
			int x = bottomLeftTile.x() + i;
			int y = topRightTile.y() + j;

			if (x < 0 || y < 0)
				continue;

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
	texture_ = renderSystem()->createTexture2D(td, buw::eTextureBindType::SRV);


	buw::Vector3d offset = (minExtend_ + maxExtend_) / -2.f;
	buw::Vector3f posBottomLeft = (minExtend_ + offset).cast<float>();
	buw::Vector3f posTopRight = (maxExtend_ + offset).cast<float>();

	buw::Vector2d wgsTileSouthEast = num2deg(bottomLeftTile + buw::Vector2i(0, 1), z).cast<double>();
	buw::Vector2d wgsTileNorthWest = num2deg(topRightTile + buw::Vector2i(1, 0), z).cast<double>();

	buw::Vector2d gkTileSouthEast = wgs2gk(wgsTileSouthEast);
	buw::Vector2d gkTileNorthWest = wgs2gk(wgsTileNorthWest);

	float uLeft = (minExtend_.x() - gkTileSouthEast.x()) / (gkTileNorthWest.x() - gkTileSouthEast.x());
	float uRight = (maxExtend_.x() - gkTileSouthEast.x()) / (gkTileNorthWest.x() - gkTileSouthEast.x());

	float vBottom = 1 - (minExtend_.y() - gkTileSouthEast.y()) / (gkTileNorthWest.y() - gkTileSouthEast.y());
	float vTop = 1 - (maxExtend_.y() - gkTileSouthEast.y()) / (gkTileNorthWest.y() - gkTileSouthEast.y());

	/*buw::VertexPosition4 vertices[4] = 
	{
		{{ (float)(gkTileSouthEast.x() + offset.x()), (float)(gkTileNorthWest.y() + offset.y()), uLeft, vTop}}, {{ (float)(gkTileNorthWest.x() + offset.x()),(float)(gkTileNorthWest.y() + offset.y()), uRight, vTop}},
		{{ (float)(gkTileSouthEast.x() + offset.x()), (float)(gkTileSouthEast.y() + offset.y()), uLeft, vBottom} }, { { (float)(gkTileNorthWest.x() + offset.x()), (float)(gkTileSouthEast.y() + offset.y()), uRight, vBottom} }
	};*/

	buw::VertexPosition4 vertices[4] =
	{
		{ { posBottomLeft.x(), posTopRight.y(), uLeft, vTop } },{ { posTopRight.x(), posTopRight.y(), uRight, vTop } },
		{ { posBottomLeft.x(), posBottomLeft.y(), uLeft, vBottom } },{ { posTopRight.x(), posBottomLeft.y(), uRight, vBottom } }
	};

	buw::vertexBufferDescription vbd;
	vbd.data = vertices;
	vbd.vertexCount = 4;
	vbd.vertexLayout = buw::VertexPosition4::getVertexLayout();

	vertexBuffer_ = renderSystem()->createVertexBuffer(vbd);
}

void BoundingBoxEffect::v_render() {
	if (drawMap_ && vertexBuffer_ && texture_ && pipelineState_)
	{
		setPipelineState(pipelineState_);

		setRenderTarget(renderSystem()->getBackBufferTarget(), depthStencil_);

		setConstantBuffer(worldBuffer_, "WorldBuffer");
		setTexture(texture_, "mapTexture");
		setSampler(linearSampler_, "sampler_");
		setViewport(viewport_);

		setVertexBuffer(vertexBuffer_);
		draw(4);
	}
}


void BoundingBoxEffect::v_init() {
	try {
		buw::samplerStateDescription ssd;
		ssd.minificationFilter = buw::eFilter::Linear;
		ssd.magnificationFilter = buw::eFilter::Linear;
		ssd.mipLevelFilter = buw::eFilter::None;
		ssd.textureAddressModeU = buw::eTextureAddressMode::Clamp;
		ssd.textureAddressModeV = buw::eTextureAddressMode::Clamp;
		ssd.textureAddressModeW = buw::eTextureAddressMode::Clamp;
		linearSampler_ = renderSystem()->createSampler(ssd);

		loadShader();

		BLUE_LOG(trace) << "BoundingBoxEffect v_init end.";
	} catch (...) {
		pipelineState_ = nullptr;
		BLUE_LOG(trace) << "Creating BoundingBoxEffect effect pipeline state failed.";
	}
}


void BoundingBoxEffect::setBounds(const buw::Vector3d& minExtend, const buw::Vector3d& maxExtend) {
	minExtend_ = minExtend;
	maxExtend_ = maxExtend;

	if(drawMap_)
		loadMap();
}

buw::ReferenceCounted<buw::ITexture2D> BoundingBoxEffect::mapTexture()
{
	return texture_;
}

void BoundingBoxEffect::loadShader() {

	buw::pipelineStateDescription psd;
	psd.effectFilename = buw::Singleton<RenderResources>::instance().getResourceRootDir() + "/Shader/BoundingBoxEffect.be";
	psd.vertexLayout = buw::VertexPosition4::getVertexLayout();
	psd.primitiveTopology = buw::ePrimitiveTopology::TriangleStrip;
	psd.renderTargetFormats = { buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB };
	psd.useDepth = true;
	psd.useMSAA = true;

	BLUE_LOG(trace) << "Before createPipelineState.";
	pipelineState_ = createPipelineState(psd);
}

void BoundingBoxEffect::enableMap(bool enable)
{
	drawMap_ = enable;
	if (drawMap_)
		loadMap();
	else
		texture_ = nullptr;
}

bool BoundingBoxEffect::mapEnabled() const
{
	return drawMap_;
}

BoundingBoxEffect::BoundingBoxEffect(buw::IRenderSystem* renderSystem, buw::ReferenceCounted<buw::IViewport> viewport,
	buw::ReferenceCounted<buw::ITexture2D> depthStencil, buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer)
    : Effect(renderSystem), 
	viewport_(viewport), 
	depthStencil_(depthStencil), 
	worldBuffer_(worldBuffer),
	vertexBuffer_(nullptr),
	drawMap_(false) {
}

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END
