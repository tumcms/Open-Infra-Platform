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

#include "VerticalAlignmentElement2DLine.h"
#include <BlueFramework/Core/assert.h>

OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DLine::VerticalAlignmentElement2DLine(
	const buw::Vector2d& start, 
	const buw::Vector2d& end) :
start_(start),
end_(end)
{
	BLUE_ASSERT(start != end, "Start == End");	// Warning. Unusual!
}

OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DLine::~VerticalAlignmentElement2DLine()
{

}

OpenInfraPlatform::Infrastructure::Stationing 
OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DLine::getEndStation() const 
{
	return end_.x();
}

OpenInfraPlatform::Infrastructure::Stationing
OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DLine::getStartStation() const 
{
	return start_.x();
}

OpenInfraPlatform::Infrastructure::eVerticalAlignmentType
OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DLine::getAlignmentType() const 
{
	return eVerticalAlignmentType::Line;
}

buw::Vector2d OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DLine::getPosition(const Stationing station) const 
{
	BLUE_ASSERT(station >= getStartStation(), "Invalid station.");
	BLUE_ASSERT(station <= getEndStation(), "Invalid station.");

	Line2d l(start_,end_);
	return l.eval(station);
}

bool OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DLine::genericQuery(const int id, void* result) const 
{
	switch(id)
	{
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition:
		*reinterpret_cast<buw::Vector2d*>(result) = start_;
		break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndPosition:
		*reinterpret_cast<buw::Vector2d*>(result) = end_;
		break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartGradient:
		*reinterpret_cast<double*>(result) = getGradient();
		break;
	default:
		BLUE_ASSERT(false, "Invalid id.")
			return false;
	}

	return true;
}

buw::Vector2d OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DLine::getStartPosition() const
{
	return start_;
}

buw::Vector2d OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DLine::getEndPosition() const
{
	return end_;
}

double OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DLine::getGradient() const
{
	double dy = end_.y() - start_.y();
	double dx = end_.x() - start_.x();
	BLUE_ASSERT(dx >= 0, "Invalid dx");
	double gradient = dy / dx;
	return gradient;
}
