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
#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment2DBased3D.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignment2D.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DArc.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid_old.h"

#include <memory>

namespace RoadXML
{
	enum class eXYCurveType
	{
		Unknown,
		Segment,
		CircleArc,
		ClothoArc
	};

	class XYCurveElement
	{
	public:
		BLUE_DEFINE_SHARED_POINTER(XYCurveElement);

		XYCurveElement(const double length) :
			length(length)
		{

		}

		virtual ~XYCurveElement()
		{

		}

		virtual eXYCurveType getType() const
		{
			return eXYCurveType::Unknown;
		}

		double getLength() const
		{
			return length;
		}

		double length;
	};

	class Segment : public XYCurveElement
	{
	public:
		BLUE_DEFINE_SHARED_POINTER(Segment);

		Segment(const double length) :
			XYCurveElement(length)
		{

		}

		virtual ~Segment()
		{

		}

		virtual eXYCurveType getType() const override
		{
			return eXYCurveType::Segment;
		}	
	private:
	};

	class CircleArc : public XYCurveElement
	{
	public:
		BLUE_DEFINE_SHARED_POINTER(CircleArc);

		CircleArc(const double curvature, const double length) :
			curvature(curvature),
			XYCurveElement(length)
		{

		}

		virtual ~CircleArc()
		{

		}

		virtual eXYCurveType getType() const override
		{
			return eXYCurveType::CircleArc;
		}

		double getRadius() const
		{
			return 1.0 / curvature;
		}

	private:
		double curvature;
	};

	class ClothoArc : public XYCurveElement
	{
	public:
		BLUE_DEFINE_SHARED_POINTER(ClothoArc);

		ClothoArc(
			const double endCurvature, 
			const double length,
			const double startCurvature) : 
		endCurvature(endCurvature),
			XYCurveElement(length),
			startCurvature(startCurvature)
		{

		}

		~ClothoArc()
		{

		}

		virtual eXYCurveType getType() const override
		{
			return eXYCurveType::ClothoArc;
		}

		double getEndCurvature() const
		{
			return endCurvature;
		}

		double getStartCurvature() const
		{
			return startCurvature;
		}

	private:
		double endCurvature; // can also be negative
		double startCurvature; // can also be negative
	};

	class XYCurve
	{
	public:
		BLUE_DEFINE_SHARED_POINTER(XYCurve);

		XYCurve(const double direction, const double x, const double y) :
			direction(direction), start(x,y)
		{

		}

		~XYCurve()
		{

		}

		void addElement(buw::ReferenceCounted<XYCurveElement> element)
		{
			elements_.push_back(element);
		}

		void draw(buw::ReferenceCounted<buw::VertexCacheLine> vcl, buw::ReferenceCounted<buw::VertexCachePoint> vcp)
		{
			// turtle movement
			double		  currentDirectionAngle = direction;
			buw::vector2d currentDirection	= buw::transform(buw::createRotationZ44d(direction), buw::vector2d(1, 0));
			buw::vector2d currentStart		= start;

			vcp->setColor(0, 1, 0);
			vcp->drawPoint(start);
			vcp->setColor(1, 0, 0);

			for (int i = 0; i < elements_.size(); i++)
			{
				switch( elements_[i]->getType() )
				{
				case eXYCurveType::Segment:
					{
						buw::vector2d currentEnd = currentStart + currentDirection * elements_[i]->getLength();
						drawLine(vcl, currentStart, currentEnd);

						currentStart = currentEnd;
					}
					break;
				case eXYCurveType::CircleArc:
					{
						buw::ReferenceCounted<CircleArc> arc = std::static_pointer_cast<CircleArc>(elements_[i]);

						std::cout << "radius " << arc->getRadius() << std::endl;

						double rot = -buw::degreeToRadian(90.0);

						buw::vector2d toCenter = buw::transform(buw::createRotationZ44d( rot ), currentDirection);
						double radius = std::abs(arc->getRadius());
						buw::vector2d center = currentStart + toCenter * radius;

						double alpha = -arc->getLength() * 180 / (buw::constantsf::pi() * radius);
						// rotate from start to end around center

						// move center to origin
						buw::vector2d tmpEnd = currentStart - center;
						buw::vector2d endPointOfArc = buw::transform(buw::createRotationZ44d( buw::degreeToRadian(alpha) ), tmpEnd);

						currentDirectionAngle += alpha;

						endPointOfArc += center;

						vcp->drawPoint( endPointOfArc );
						vcp->drawPoint( center );
						drawArc(vcl, center, currentStart, endPointOfArc, true);

						currentStart = endPointOfArc;

						currentDirection = buw::transform(buw::createRotationZ44d( buw::degreeToRadian(alpha) ), currentDirection);
					}
					break;				
				case eXYCurveType::ClothoArc:
					{
						buw::ReferenceCounted<ClothoArc> c = std::static_pointer_cast<ClothoArc>(elements_[i]);

						drawClothoid(vcl, currentStart, currentDirectionAngle, c->getStartCurvature(), c->getEndCurvature(), c->getLength());

						vcp->drawPoint(currentStart.x(), currentStart.y());

						buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid_old> pc = std::make_shared<buw::HorizontalAlignmentElement2DClothoid_old>(
							currentStart, 
							currentDirectionAngle, 
							c->getStartCurvature(), 
							c->getEndCurvature(), 
							c->getLength());

						currentStart = pc->getPosition(1.0f);
						vcp->drawPoint(currentStart.x(), currentStart.y());

						double tau = pc->calculateEndTangentAngle();
						currentDirection = buw::transform(buw::createRotationZ44d( tau ), currentDirection);
					}
					break;
				}
			}
		}

	private:
		void drawClothoid(
			buw::ReferenceCounted<buw::VertexCacheLine> vcl,
			const buw::vector2d& start, 
			const double direction,
			const double startCurvature,
			const double endCurvature,
			const double length ) 
		{
			vcl->setColor(buw::colorConstants3f::yellow());

			buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid_old> a = std::make_shared<buw::HorizontalAlignmentElement2DClothoid_old>(
				start, 
				direction,
				startCurvature,
				endCurvature,
				length);

			auto start2 = a->getPosition(0);
			for (double t = 0.01; t <= 1.0; t += 0.01)
			{
				auto end = a->getPosition(t);

				vcl->drawLine(start2, end);

				start2 = end;
			}

			vcl->drawLine(start2, a->getPosition(1.0));
		}

		void drawArc(
			buw::ReferenceCounted<buw::VertexCacheLine> vcl,
			const buw::vector2d& center, 
			const buw::vector2d& start,
			const buw::vector2d& end, 
			const bool clockWise ) 
		{
			vcl->setColor(buw::colorConstants3f::red());

			buw::ReferenceCounted<buw::HorizontalAlignmentElement2DArc> a = std::make_shared<buw::HorizontalAlignmentElement2DArc>(
				center,
				start,
				end,
				clockWise);

			auto start2 = a->getPosition(0);
			for (double t = 0.01; t <= 1.0; t += 0.01)
			{
				auto end = a->getPosition(t);

				vcl->drawLine(start2, end);

				start2 = end;
			}

			vcl->drawLine(start2, a->getPosition(1.0));
		}

		void drawLine(
			buw::ReferenceCounted<buw::VertexCacheLine> vcl,
			const buw::vector2d& start,
			const buw::vector2d& end ) 
		{
			vcl->setColor(buw::colorConstants3f::green());

			buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> a = std::make_shared<buw::HorizontalAlignmentElement2DLine>(
				start,
				end);

			auto start2 = a->getPosition(0);
			for (double t = 0.01; t <= 1.0; t += 0.01)
			{
				auto end = a->getPosition(t);

				vcl->drawLine(start2, end);

				start2 = end;
			}

			vcl->drawLine(start2, a->getPosition(1.0));
		}

	private:	
		double direction;
		buw::vector2d start;

		std::vector<buw::ReferenceCounted<XYCurveElement>> elements_;
	};

	class Track
	{
	public:
		BLUE_DEFINE_SHARED_POINTER(Track);

		Track(const std::string& name, buw::ReferenceCounted<XYCurve> a) : 
			name(name),
			horizontalAlignment(a)
		{

		}

		virtual ~Track()
		{

		}

	private:
		buw::ReferenceCounted<XYCurve> horizontalAlignment;

		std::string name;
		std::string startNode;
		std::string endNode;
	};
}

class RoadXMLViewer : public buw::RenderWindow
{
public:
	RoadXMLViewer(const buw::renderWindowsDescription& rwd) :
		buw::RenderWindow(rwd),
		trackId(2),
		cameraZPosition(140)
	{
		setWindowTitle("RoadXMLViewer");

		// setup camera
		camera_->setEyePosition(buw::vector3f(0, 0, cameraZPosition));
		
		// create a point vertex cache
		vertexCachePoint_ = std::make_shared<buw::VertexCachePoint>(renderSystem_, "Shader/VertexCachePoint.be");
		vertexCachePoint_->setColor(1, 0, 0);

		// create a line vertex cache
		vertexCacheLine_ = std::make_shared<buw::VertexCacheLine>(renderSystem_, "Shader/VertexCacheLine.be", 30000);
		vertexCacheLine_->setColor(1, 0, 0);

		// create triangle vertex cache
		vertexCacheTriangle_ = std::make_shared<buw::VertexCacheTriangle>(renderSystem_, "Shader/VertexCacheTriangle.be");

		vertexCacheLine_->setColor(buw::colorConstants3f::pink());

		if (!true)
		{
			/*
				start(start),
				direction(direction),
				startCurvature(startCurvature),
				endCurvature(endCurvature),
				length(length)
			*/
			buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid_old>	pc = std::make_shared<buw::HorizontalAlignmentElement2DClothoid_old>(
				buw::vector2d(0, 0),
				0,
				0,
				1.0/100.0,
				100
				);

			auto start2 = pc->getPosition(0);
			for (double t = 0.01; t <= 1.0; t += 0.01)
			{
				auto end = pc->getPosition(t);

				vertexCacheLine_->drawLine(start2, end);

				start2 = end;
			}

			//vertexCacheLine_->drawLine(start2, pc->getPosition(1.0));
		}
		
		vertexCacheLine_->setColor(buw::colorConstants3f::yellow());


		int trackId = 2;
		updateTrack();
	}

	void updateTrack()
	{
		vertexCacheLine_->clear();
		vertexCachePoint_->clear();

		// draw coordinate system
		vertexCacheLine_->setColor(buw::color3f(1,0,0));
		vertexCacheLine_->drawLine(buw::vector3f(0,0,0), buw::vector3f(20,0,0));
		vertexCacheLine_->setColor(buw::color3f(0,1,0));
		vertexCacheLine_->drawLine(buw::vector3f(0,0,0), buw::vector3f(0,20,0));
		vertexCacheLine_->setColor(buw::color3f(0,0,1));
		vertexCacheLine_->drawLine(buw::vector3f(0,0,0), buw::vector3f(0,0,20));

		if (trackId == 1)
		{
			// eight_with_intersection
			buw::ReferenceCounted<RoadXML::XYCurve> curve1 = std::make_shared<RoadXML::XYCurve>(-1.57079, -0.000146928, -10);
			curve1->addElement( std::make_shared<RoadXML::Segment>(40) );
			curve1->addElement( std::make_shared<RoadXML::CircleArc>(-0.02, 235.61) );
			curve1->addElement( std::make_shared<RoadXML::Segment>(39.9998) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve2 = std::make_shared<RoadXML::XYCurve>(1.57061, -0.00735832, 10.0094);
			curve2->addElement( std::make_shared<RoadXML::Segment>(40) );
			curve2->addElement( std::make_shared<RoadXML::CircleArc>(-0.02, 235.61) );
			curve2->addElement( std::make_shared<RoadXML::Segment>(40.0002) );

			curve1->draw(vertexCacheLine_, vertexCachePoint_);
			curve2->draw(vertexCacheLine_, vertexCachePoint_);
		}

		if (trackId == 2)
		{
			vertexCacheLine_->setColor(buw::colorConstants3f::orange());

			// interchange
			buw::ReferenceCounted<RoadXML::XYCurve> curve1 = std::make_shared<RoadXML::XYCurve>(-1.48316, -28.431, 358.999);
			curve1->addElement( std::make_shared<RoadXML::Segment>(127.485) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve2 = std::make_shared<RoadXML::XYCurve>(0.602425, -62.8889, 3.77778);
			curve2->addElement( std::make_shared<RoadXML::Segment>(100.91) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve3 = std::make_shared<RoadXML::XYCurve>(1.75917, 50.0104, -83.2074);
			curve3->addElement( std::make_shared<RoadXML::ClothoArc>(0, 8.009, -0.0309793) );
			curve3->addElement( std::make_shared<RoadXML::ClothoArc>(0, 3.51943, 0.0143293) );
			curve3->addElement( std::make_shared<RoadXML::CircleArc>(0.00105004, 128.811) );
			curve3->addElement( std::make_shared<RoadXML::Segment>(2.7) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve4 = std::make_shared<RoadXML::XYCurve>(1.76353, 25.1084, 73.6863);
			curve4->addElement( std::make_shared<RoadXML::CircleArc>(0.000302351, 35.4289) );
			curve4->addElement( std::make_shared<RoadXML::CircleArc>(0.000358132, 96.945) );
			curve4->addElement( std::make_shared<RoadXML::CircleArc>(-0.00497208, 29.6926) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve5 = std::make_shared<RoadXML::XYCurve>(0.60776, 30.6685, 69.0041);
			curve5->addElement( std::make_shared<RoadXML::Segment>(148.069) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve6 = std::make_shared<RoadXML::XYCurve>(-1.30165, 41.2798, -86.6892);
			curve6->addElement( std::make_shared<RoadXML::Segment>(158.731) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve7 = std::make_shared<RoadXML::XYCurve>(-1.48316, -17.2321, 231.539);
			curve7->addElement( std::make_shared<RoadXML::Segment>(79.732) );
			curve7->addElement( std::make_shared<RoadXML::ClothoArc>(0.00316235, 114.795, 0) );
			curve7->addElement( std::make_shared<RoadXML::Segment>(129.227) );

			curve1->draw(vertexCacheLine_, vertexCachePoint_);
			curve2->draw(vertexCacheLine_, vertexCachePoint_);
			curve3->draw(vertexCacheLine_, vertexCachePoint_);
			curve4->draw(vertexCacheLine_, vertexCachePoint_);
			curve5->draw(vertexCacheLine_, vertexCachePoint_);
			curve6->draw(vertexCacheLine_, vertexCachePoint_);
			curve7->draw(vertexCacheLine_, vertexCachePoint_);
		}

		if(trackId == 3) 
		{
			// small_roundabout

			buw::ReferenceCounted<RoadXML::XYCurve> curve1 = std::make_shared<RoadXML::XYCurve>(1.56587, -0.741206, 15.4613);
			curve1->addElement( std::make_shared<RoadXML::Segment>(16.802) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve2 = std::make_shared<RoadXML::XYCurve>(-0.702165, 4.6275, 7.60126);
			curve2->addElement( std::make_shared<RoadXML::CircleArc>(-0.125333, 12.902) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve3 = std::make_shared<RoadXML::XYCurve>(0.925867, -6.90193, 6.30625);
			curve3->addElement( std::make_shared<RoadXML::CircleArc>(-0.125333, 2.14) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve4 = std::make_shared<RoadXML::XYCurve>(3.12615, -13.4974, 1.59397);
			curve4->addElement( std::make_shared<RoadXML::Segment>(24.695) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve5 = std::make_shared<RoadXML::XYCurve>(2.51434, -5.20871, -4.95001);
			curve5->addElement( std::make_shared<RoadXML::CircleArc>(-0.125333, 2.534) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve6 = std::make_shared<RoadXML::XYCurve>(-1.57079, 0.0584924, -11.4272);
			curve6->addElement( std::make_shared<RoadXML::Segment>(24.128) );

			curve1->draw(vertexCacheLine_, vertexCachePoint_);
			curve2->draw(vertexCacheLine_, vertexCachePoint_);
			curve3->draw(vertexCacheLine_, vertexCachePoint_);
			curve4->draw(vertexCacheLine_, vertexCachePoint_);
			curve5->draw(vertexCacheLine_, vertexCachePoint_);
			curve6->draw(vertexCacheLine_, vertexCachePoint_);
		}

		if(trackId == 4) 
		{
			// big_roundabout

			buw::ReferenceCounted<RoadXML::XYCurve> curve1 = std::make_shared<RoadXML::XYCurve>(-2.90919, 23.9702, -49.8307);
			curve1->addElement( std::make_shared<RoadXML::CircleArc>(-0.0221529, 50.679) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve2 = std::make_shared<RoadXML::XYCurve>(-0.569454, 37.7794, -54.0162);
			curve2->addElement( std::make_shared<RoadXML::CircleArc>(-0.0127335, 27.843) );
			curve2->addElement( std::make_shared<RoadXML::Segment>(102.83) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve3 = std::make_shared<RoadXML::XYCurve>(-1.72351, 35.7585, 143.183);
			curve3->addElement( std::make_shared<RoadXML::Segment>(52.5975) );
			curve3->addElement( std::make_shared<RoadXML::ClothoArc>(-0.0165407, 45.185, 0) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve4 = std::make_shared<RoadXML::XYCurve>(-0.125226, 19.2113, 38.8838);
			curve4->addElement( std::make_shared<RoadXML::CircleArc>(-0.0221529, 28.2189) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve5 = std::make_shared<RoadXML::XYCurve>(0.443651, -247.315, -93.7062);
			curve5->addElement( std::make_shared<RoadXML::ClothoArc>(0, 72.701, 0.000116682) );
			curve5->addElement( std::make_shared<RoadXML::ClothoArc>(0, 84.491, -0.00239696) );
			curve5->addElement( std::make_shared<RoadXML::ClothoArc>(0, 57.3569, 0.00407442) );
			curve5->addElement( std::make_shared<RoadXML::CircleArc>(0.0284338, 11.4448) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve6 = std::make_shared<RoadXML::XYCurve>(1.89687, -29.1888, -20.3633);
			curve6->addElement( std::make_shared<RoadXML::CircleArc>(-0.0221529, 15.454) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve7 = std::make_shared<RoadXML::XYCurve>(3.02747, -35.497, -28.2209);
			curve7->addElement( std::make_shared<RoadXML::CircleArc>(0.0272258, 15.6047) );
			curve7->addElement( std::make_shared<RoadXML::CircleArc>(0.000369416, 206.03) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve8 = std::make_shared<RoadXML::XYCurve>(1.11296, -26.8913, 14.1511);
			curve8->addElement( std::make_shared<RoadXML::CircleArc>(-0.0220226, 19.631) );
			curve8->addElement( std::make_shared<RoadXML::CircleArc>(-0.0221529, 21.323) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve9 = std::make_shared<RoadXML::XYCurve>(-2.96051, 183.891, 38.0032);
			curve9->addElement( std::make_shared<RoadXML::Segment>(104.881) );
			curve9->addElement( std::make_shared<RoadXML::CircleArc>(-0.0166412, 18.9563) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve10 = std::make_shared<RoadXML::XYCurve>(-2.94513, 213.314, 26.456);
			curve10->addElement( std::make_shared<RoadXML::Segment>(129.775) );
			curve10->addElement( std::make_shared<RoadXML::CircleArc>(0.0177558, 19.833) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve11 = std::make_shared<RoadXML::XYCurve>(-1.19341, 55.5376, 10.7303);
			curve11->addElement( std::make_shared<RoadXML::CircleArc>(-0.0221529, 12.4399) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve12 = std::make_shared<RoadXML::XYCurve>(-1.91205, 56.111, -21.0108);
			curve12->addElement( std::make_shared<RoadXML::CircleArc>(-0.0221529, 30.0112) );

			buw::ReferenceCounted<RoadXML::XYCurve> curve13 = std::make_shared<RoadXML::XYCurve>(-2.73613, -246.686, -97.2662);
			curve13->addElement( std::make_shared<RoadXML::Segment>(45.1606) );

			curve1->draw(vertexCacheLine_, vertexCachePoint_);
			curve2->draw(vertexCacheLine_, vertexCachePoint_);
			curve3->draw(vertexCacheLine_, vertexCachePoint_);
			curve4->draw(vertexCacheLine_, vertexCachePoint_);
			curve5->draw(vertexCacheLine_, vertexCachePoint_);
			curve6->draw(vertexCacheLine_, vertexCachePoint_);
			curve7->draw(vertexCacheLine_, vertexCachePoint_);
			curve8->draw(vertexCacheLine_, vertexCachePoint_);
			curve9->draw(vertexCacheLine_, vertexCachePoint_);
			curve10->draw(vertexCacheLine_, vertexCachePoint_);
			curve11->draw(vertexCacheLine_, vertexCachePoint_);
			curve12->draw(vertexCacheLine_, vertexCachePoint_);
			curve13->draw(vertexCacheLine_, vertexCachePoint_);

		}
	}

	virtual ~RoadXMLViewer()
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

		if(buw::Keyboard::instance().keyPressed(buw::Keyboard::KEY_1))
		{
			trackId = 1;
			updateTrack();
		}
		
		if(buw::Keyboard::instance().keyPressed(buw::Keyboard::KEY_2))
		{
			trackId = 2;
			updateTrack();
		}
		
		if(buw::Keyboard::instance().keyPressed(buw::Keyboard::KEY_3))
		{
			trackId = 3;
			updateTrack();
		}
		
		if(buw::Keyboard::instance().keyPressed(buw::Keyboard::KEY_4))
		{
			trackId = 4;
			updateTrack();
		}

		if(buw::Keyboard::instance().keyDown(buw::Keyboard::KEY_PAGEUP))
		{
			cameraZPosition -= 0.5;
			camera_->setEyePosition(buw::vector3f(0, 0, cameraZPosition));
		}

		if(buw::Keyboard::instance().keyDown(buw::Keyboard::KEY_PAGEDOWN))
		{
			cameraZPosition += 0.5;
			camera_->setEyePosition(buw::vector3f(0, 0, cameraZPosition));
		}
			
		render();
	}
		
	void render()
	{
		camera_->update();
			
		// draw scene
		{
			renderSystem_->getImmediateContext()->setRenderTarget(
				renderSystem_->getImmediateContext()->getBackBufferRenderTarget());
				
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
	int trackId;
	double cameraZPosition;
	buw::ReferenceCounted<buw::VertexCacheTriangle>	vertexCacheTriangle_;
	buw::ReferenceCounted<buw::VertexCacheLine>		vertexCacheLine_;
	buw::ReferenceCounted<buw::VertexCachePoint>      vertexCachePoint_;
			
protected:
	buw::Stopwatch					stopWatch_;
};
	