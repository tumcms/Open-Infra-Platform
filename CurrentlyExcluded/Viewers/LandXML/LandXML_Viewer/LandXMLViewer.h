/*
    Copyright (c) 2016-2017 Technical University of Munich
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

#include "buw.BlueCore.h"
#include "buw.BlueEngine.h"
#include "buw.BlueImageProcessing.h"
#include "buw.OIPInfrastructure.h"

#include <memory>

class LandXMLViewer : public buw::RenderWindow
{
public:
	LandXMLViewer(const buw::renderWindowsDescription& rwd) :
		buw::RenderWindow(rwd)
	{
		setWindowTitle("LandXMLViewer");

		// setup camera
		camera_->setEyePosition(buw::vector3f(0, 0, 140));
		
		// create a point vertex cache
		vertexCachePoint_ = std::make_shared<buw::VertexCachePoint>(renderSystem_, "Shader/VertexCachePoint.be");
		vertexCachePoint_->setColor(1, 0, 0);

		// create a line vertex cache
		vertexCacheLine_ = std::make_shared<buw::VertexCacheLine>(renderSystem_, "Shader/VertexCacheLine.be", 30000);
		vertexCacheLine_->setColor(1, 0, 0);

		// create triangle vertex cache
		vertexCacheTriangle_ = std::make_shared<buw::VertexCacheTriangle>(renderSystem_, "Shader/VertexCacheTriangle.be");

		vertexCacheLine_->setColor(buw::colorConstants3f::pink());
		vertexCacheLine_->setColor(buw::colorConstants3f::yellow());

		// draw coordinate system
		vertexCacheLine_->setColor(buw::color3f(1,0,0));
		vertexCacheLine_->drawLine(buw::vector3f(0,0,0), buw::vector3f(20,0,0));
		vertexCacheLine_->setColor(buw::color3f(0,1,0));
		vertexCacheLine_->drawLine(buw::vector3f(0,0,0), buw::vector3f(0,20,0));
		vertexCacheLine_->setColor(buw::color3f(0,0,1));
		vertexCacheLine_->drawLine(buw::vector3f(0,0,0), buw::vector3f(0,0,20));

		buw::LandXmlImport parser("../testdata/LandXML/Mainbruecke_Klingenberg.xml");

		std::vector<buw::ReferenceCounted<buw::IAlignment3D>> alignments = parser.getAlignmentModel()->getAlignments();

		buw::vector3d offset = alignments[0]->getPosition(alignments[0]->getStartStation());

		for (int i = 0; i < alignments.size(); i++)
		{
			if (alignments[i]->getType() == buw::e3DAlignmentType::e3DBased)
			{
				continue; // skip this element
			}

			buw::ReferenceCounted<buw::Alignment2DBased3D> alignment = std::static_pointer_cast<buw::Alignment2DBased3D>(alignments[i]);

			auto he = alignment->getHorizontalAlignment()->getAlignmentElementByIndex(i);

			for(float t = alignment->getStartStation(); t < alignment->getEndStation(); t++)
			{
				vertexCachePoint_->drawPoint( alignment->getPosition(t) - offset );
			}
		}
	}

	virtual ~LandXMLViewer()
	{
	
	}

	bool initialize()
	{
		return true;
	}

	virtual void resize( const int width, const int height )
	{
		RenderWindow::resize(width, height);
			
		int w = width;
		int h = height;

		if (width == 0)
		{
			w = 1;
		}

		if (height == 0)
		{
			h = 1;
		}

		renderContext_->setViewport(0,0,w,h);
		renderContext_->setRenderTarget(renderContext_->getBackBufferRenderTarget());
		renderContext_->resizeRenderTarget(w,h);

		camera_->setPerspective(
			camera_->getYFov(), 
			getAspectRatio(), 
			camera_->getNearPlaneDistance(), 
			camera_->getFarPlaneDistance()
		);
	}

	void loop() 
	{
		RenderWindow::loop();

		float elapsedTimeInSeconds = getElapsedTimeInSeconds();
		
		if(buw::Keyboard::instance().keyPressed(buw::Keyboard::KEY_N))
		{
			camera_->setEyePosition(buw::vector3f(0, 1, 240));
		}

		if(buw::Keyboard::instance().keyPressed(buw::Keyboard::KEY_M))
		{
			camera_->setEyePosition(buw::vector3f(0, 1, 340));
		}
			
		render();
	}
		
	void render()
	{
		camera_->update();
			
		// draw scene
		{
			float color[] = {0.3f, 0.5f, 0.9f, 0.0f};
			renderContext_->clear(buw::eClearFlags::Color | buw::eClearFlags::Depth, color);
			
			buw::matrix44f vp = camera_->getViewProjectionMatrix();
			buw::matrix44f world =  buw::createScale44f(0.345f) * buw::createTranslation44f(0, 0, 0);
			buw::matrix44f worldIT =  (buw::createInverse44f(world)).transpose();

			// draw point vertex cache
			buw::pointVertexCacheShaderData pvcsd;
			pvcsd.world = world;
			pvcsd.projection = camera_->getProjectionMatrix();
			pvcsd.view = camera_->getViewMatrix();
			pvcsd.viewport = buw::vector2f(
				static_cast<float>(width_), 
				static_cast<float>(height_));

			vertexCachePoint_->flush(pvcsd);

			// draw line vertex cache
			buw::vertexCacheLineShaderData vcsd;
			vcsd.world = world;
			vcsd.projection = camera_->getProjectionMatrix();
			vcsd.view = camera_->getViewMatrix();
			vcsd.viewport = buw::vector2f(
				static_cast<float>(width_), 
				static_cast<float>(height_));
			vcsd.frustum = buw::vector4f (
				camera_->getNearPlaneWidth(),
				camera_->getNearPlaneHeight(), 
				camera_->getNearPlaneDistance(), 
				camera_->getFarPlaneDistance() );

			vertexCacheLine_->flush(vcsd);

			// draw triangle vertex cache
			buw::triangleVertexCacheShaderData tvcsd;
			tvcsd.view = camera_->getViewMatrix();
			tvcsd.projection = camera_->getProjectionMatrix();
			tvcsd.world = world;// * buw::createScale44f(100.0f);
			tvcsd.worldEyePosition = camera_->getEyePosition();

			vertexCacheTriangle_->flush(tvcsd);
		}

		renderSystem_->swap();
	}

private:
	buw::ReferenceCounted<buw::VertexCacheTriangle>	vertexCacheTriangle_;
	buw::ReferenceCounted<buw::VertexCacheLine>		vertexCacheLine_;
	buw::ReferenceCounted<buw::VertexCachePoint>      vertexCachePoint_;
};
	