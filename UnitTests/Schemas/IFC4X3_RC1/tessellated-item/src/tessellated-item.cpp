/*
    Copyright (c) 2020 Technical University of Munich
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

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <reader/IFC4X3_RC1Reader.h>
#include <namespace.h>

#include <buw.Engine.h>
#include <buw.ImageProcessing.h>

#include <Effects/IfcGeometryEffect.h>

#include <IfcGeometryConverter/IfcImporterImpl.h>
#include <IfcGeometryConverter/ConverterBuw.h>

#include <boost/dll/runtime_symbol_info.hpp>

using namespace testing;

struct WorldBuffer {
    buw::Matrix44f viewProjection;
    buw::Matrix44f projection;
    buw::Matrix44f view;
    buw::Vector3f cam;
    buw::Matrix44f rotation;
};

class IfcGeometryModelRenderer
{
public:
    IfcGeometryModelRenderer()
    {
        camera_ = buw::makeReferenceCounted<buw::Camera>();
        cameraController_ = buw::makeReferenceCounted<buw::CameraController>(camera_);

        camera_->frustum() = buw::CameraFrustum(width, height, 0.5f, 50000.f, buw::eProjectionType::Perspective);
        camera_->transformation().offset() = 15;
        camera_->transformation().yaw() = buw::constantsf::pi_over_4();

        buw::renderSystemDescription scd;
        scd.width = width;
        scd.height = height;
        scd.windowId = (void*) this;
        scd.forceWarpDevice = false;
        scd.enableMSAA = true;
        scd.renderAPI = BlueFramework::Rasterizer::eRenderAPI::Direct3D11;

        renderSystem_ = BlueFramework::Rasterizer::createRenderSystem(scd);

        buw::texture2DDescription dsvTD;
        dsvTD.width = width;
        dsvTD.height = height;
        dsvTD.format = buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt;
        dsvTD.data = nullptr;
        dsvTD.isCpuReadable = false;
        dsvTD.useMSAA = true;
        depthStencilMSAA_ = renderSystem_->createTexture2D(dsvTD, buw::eTextureBindType::DSV);

        viewport_ = renderSystem_->createViewport(buw::viewportDescription(width, height));

        buw::constantBufferDescription cbd0;
        cbd0.sizeInBytes = sizeof(WorldBuffer);
        cbd0.data = nullptr;
        worldBuffer_ = renderSystem_->createConstantBuffer(cbd0);

        WorldBuffer world;
        world.viewProjection = camera_->viewProjectionMatrix();
        world.projection = camera_->frustum().projectionMatrix();
        world.view = camera_->transformation().viewMatrix();
        world.cam = (camera_->transformation().transformationMatrix() * buw::Vector4f(0, 0, 0, 1)).block<3, 1>(0, 0);
        world.rotation = camera_->transformation().rotationMatrix();

        buw::constantBufferDescription cbd;
        cbd.sizeInBytes = sizeof(WorldBuffer);
        cbd.data = &world;
        worldBuffer_->uploadData(cbd);

        ifcGeometryEffect_ = buw::makeReferenceCounted<oip::IfcGeometryEffect>(
            renderSystem_.get(), viewport_, depthStencilMSAA_, worldBuffer_);
        ifcGeometryEffect_->init();
    }

    virtual ~IfcGeometryModelRenderer()
    {
        ifcGeometryEffect_.reset();
        worldBuffer_.reset();
        viewport_.reset();
        depthStencilMSAA_.reset();
        renderSystem_.reset();
        cameraController_.reset();
        camera_.reset();
    }

    void setModel(const std::shared_ptr<OpenInfraPlatform::Core::IfcGeometryConverter::IfcGeometryModel>& model)
    {
        ifcGeometryEffect_->setIfcGeometryModel(model, -model->bb_.center());
        cameraController_->fitToView(model->bb_.min().cast<float>(), model->bb_.max().cast<float>());
        cameraController_->tick(1.0f);
        camera_->tick(1.0f);
    }

    void clearBackBuffer()
    {
        float color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        renderSystem_->clearRenderTarget(renderSystem_->getBackBufferTarget(), color);
        renderSystem_->clearDepthStencilView(depthStencilMSAA_);
    }

    void repaint()
    {
        clearBackBuffer();
        ifcGeometryEffect_->render();
        renderSystem_->present();
    }

    buw::Image4b getBackBufferImage()
    {
        auto backBufferImage = buw::Image4b(width, height);
        buw::ReferenceCounted<buw::ITexture2D> backBuffer = renderSystem_->getBackBufferTarget();
        if (!backBuffer->isCPUReadable())
            backBuffer->makeCPUReadable();
        renderSystem_->downloadTexture(backBuffer, backBufferImage);
        return backBufferImage;
    }

    buw::Image4b captureImage()
    {
        repaint();
        return getBackBufferImage();
    }


private:
    int width = 640;
    int height = 480;

    buw::ReferenceCounted<BlueFramework::Engine::Camera> camera_;
    buw::ReferenceCounted<BlueFramework::Engine::CameraController> cameraController_;
    buw::ReferenceCounted<BlueFramework::Rasterizer::IRenderSystem> renderSystem_;
    buw::ReferenceCounted<BlueFramework::Rasterizer::IViewport> viewport_;
    buw::ReferenceCounted<OpenInfraPlatform::Rendering::IfcGeometryEffect> ifcGeometryEffect_;
    buw::ReferenceCounted<BlueFramework::Rasterizer::ITexture2D> depthStencilMSAA_;
    buw::ReferenceCounted<BlueFramework::Rasterizer::IConstantBuffer> worldBuffer_;
};

class VisualTest : public Test
{
protected:

    buw::ReferenceCounted<IfcGeometryModelRenderer> renderer = nullptr;

    virtual void SetUp() override
    {
        renderer = buw::makeReferenceCounted<IfcGeometryModelRenderer>();
        
    }

    virtual void TearDown() override
    {
        renderer.reset();
    }
};

class TessellatedItemTest : public VisualTest {
    protected:

    // Test standard values
    buw::Image4b _background = buw::Image4b(0, 0);

    virtual void SetUp() override {
        VisualTest::SetUp();

        express_model = OpenInfraPlatform::IFC4X3_RC1::IFC4X3_RC1Reader::FromFile(filename.string());
        importer = buw::makeReferenceCounted<oip::IfcImporterT<emt::IFC4X3_RC1EntityTypes>>();
        importer->collectGeometryData(express_model);
	oip::ConverterBuwT<emt::IFC4X3_RC1EntityTypes>::createGeometryModel(model, importer->getShapeDatas());

        renderer->setModel(model);

        renderer->clearBackBuffer();
        _background = renderer->getBackBufferImage();
    }

    virtual void TearDown() override {
        express_model.reset();
        VisualTest::TearDown();
    }

    const boost::filesystem::path filename = boost::dll::program_location().parent_path().concat("\\UnitTests\\Schemas\\IFC4X3_RC1\\tessellated-item\\Data\\tessellated-item.ifc");


    std::shared_ptr<oip::EXPRESSModel> express_model = nullptr;
    buw::ReferenceCounted<oip::IfcImporterT<emt::IFC4X3_RC1EntityTypes>> importer = nullptr;
    buw::ReferenceCounted<oip::IfcGeometryModel> model = buw::makeReferenceCounted<oip::IfcGeometryModel>();
};

TEST_F(TessellatedItemTest, AllEntitiesAreRead) {
    EXPECT_THAT(express_model->entities.size(), Eq(29));
}

TEST_F(TessellatedItemTest, ImageIsSaved)
{
    // Arrange
    buw::Image4b image = renderer->captureImage();

    // Act
    buw::storeImage("UnitTests/Schemas/IFC4X3_RC1/tessellated-item/Data/tessellated-item.png", image);

    // Assert
    EXPECT_NE(image,_background);
}
