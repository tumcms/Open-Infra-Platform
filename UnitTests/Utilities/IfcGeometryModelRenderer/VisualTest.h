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

class VisualTest : public Test
{
protected:

    buw::ReferenceCounted<buw::IRenderSystem> renderSystem_ = nullptr;
    buw::ReferenceCounted<IfcGeometryModelRenderer> renderer = nullptr;

    VisualTest()
    {
        buw::renderSystemDescription scd;
        scd.width = 640;
        scd.height = 480;
        scd.windowId = static_cast<void*>(this);
        scd.forceWarpDevice = false;
        scd.enableMSAA = true;
        scd.renderAPI = BlueFramework::Rasterizer::eRenderAPI::Direct3D11;

        renderSystem_ = BlueFramework::Rasterizer::createRenderSystem(scd);
    }

    virtual ~VisualTest()
    {
        renderSystem_.reset();
    }

    virtual void SetUp() override
    {
        renderer = buw::makeReferenceCounted<IfcGeometryModelRenderer>(renderSystem_);
        
    }

    virtual void TearDown() override
    {
        renderer.reset();
    }
};
