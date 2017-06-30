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

#include "VerticalAlignmentElement2DParabola.h"
#include <BlueFramework/Core/assert.h>

OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DParabola::VerticalAlignmentElement2DParabola(const buw::Vector2d& start, const buw::Vector2d& end, const double startGradient, const double endGradient) :
	start_(start),
	end_(end),
	startGradient_(startGradient),
	endGradient_(endGradient)
{

}

OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DParabola::~VerticalAlignmentElement2DParabola()
{

}

buw::Vector2d OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DParabola::getPosition(const Stationing station) const
{
	BLUE_ASSERT(station >= getStartStation(), "Invalid station.");
	BLUE_ASSERT(station <= getEndStation(), "Invalid station.");

	double x = station;

	double a = 0.5 * ((endGradient_ - startGradient_) / (end_.x() - start_.x()));
	double b = startGradient_ - a * 2.0 * start_.x();
	double c = start_.y() - a * start_.x()*start_.x() - b * start_.x();

	double y = a * x*x + b * x + c;

	return buw::Vector2d(x, y);
}

OpenInfraPlatform::Infrastructure::eVerticalAlignmentType 
OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DParabola::getAlignmentType() const
{
	return eVerticalAlignmentType::Parabola;
}

bool OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DParabola::genericQuery(const int id, void* result) const 
{
	switch(id)
	{
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition:
		*reinterpret_cast<buw::Vector2d*>(result) = start_;
		break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndPosition:
		*reinterpret_cast<buw::Vector2d*>(result) = end_;
		break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::IntersectionPointDistance:
		*reinterpret_cast<double*>(result) = end_.x() - start_.x();
		break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::PVI:
		{
			// compute y-abscissa
			double c1 = start_.y() - startGradient_ * start_.x();
			double c2 = end_.y() - endGradient_ * end_.x();
			double m1 = startGradient_;
			double m2 = endGradient_;

			double X = -(c2-c1)/(m2-m1);
			double Y = m1 * X + c1;

			buw::Vector2d pvi(X, Y);

			BLUE_ASSERT(X >= start_.x(), "Invalid X.");
			BLUE_ASSERT(X <= end_.x(), "Invalid X.");

			*reinterpret_cast<buw::Vector2d*>(result) = pvi;
		}
		break;

	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartGradientAsPlaneAngleMeasure:
		{
			*reinterpret_cast<double*>(result) = startGradient_;
		}
		break;

	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndGradient:
		{
			*reinterpret_cast<double*>(result) = endGradient_;
		}
		break;

	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartGradient:
		{
			*reinterpret_cast<double*>(result) = startGradient_;
		}
	break;

	default:
		BLUE_ASSERT(false, "Invalid id.");
		return false;
	}

	return true;
}

OpenInfraPlatform::Infrastructure::Stationing 
OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DParabola::getEndStation() const 
{
	return end_.x();
}

OpenInfraPlatform::Infrastructure::Stationing 
OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DParabola::getStartStation() const 
{
	return start_.x();
}

void OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DParabola::getParameters(double& a, double& b, double& c) const
{
	a = 0.5 * ((endGradient_ - startGradient_) / (end_.x() - start_.x()));
	b = startGradient_ - a * 2.0 * start_.x();
	c = start_.y() - a * start_.x()*start_.x() - b * start_.x();
}

double OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DParabola::getEndGradient() const
{
	return endGradient_;
}

double OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DParabola::getStartGradient() const
{
	return startGradient_;
}

buw::Vector2d OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DParabola::getEndPosition() const
{
	return end_;
}

buw::Vector2d OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DParabola::getStartPosition() const
{
	return start_;
}

double OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DParabola::getFocalLength() const
{
	double a = 0.5 * ((endGradient_ - startGradient_) / (end_.x() - start_.x()));

	BLUE_ASSERT(a != 0.0, "Invalid parameter.");

	return 1.0 / (4.0 * a);
}

bool OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DParabola::isConvex() const
{
	double a = 0.5 * ((endGradient_ - startGradient_) / (end_.x() - start_.x()));

	BLUE_ASSERT(a != 0.0, "Invalid parameter.");

	if (a < 0.0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

double OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DParabola::getGradient(const double x) const
{
	double a, b, c;
	getParameters(a, b, c);
	return 2.0 * a * x + b;
}
