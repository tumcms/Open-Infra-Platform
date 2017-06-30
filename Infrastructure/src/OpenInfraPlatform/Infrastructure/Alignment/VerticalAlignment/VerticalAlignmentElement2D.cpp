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

#include "VerticalAlignmentElement2D.h"

OpenInfraPlatform::Infrastructure::eVerticalAlignmentType OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2D::getAlignmentType() const {
	return eVerticalAlignmentType::Unknown;
}

bool OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2D::genericQuery(const int /*id*/, void* /*result*/) const {
	return false;
}

std::ostream& OpenInfraPlatform::Infrastructure::operator<<(std::ostream& os, buw::ReferenceCounted<VerticalAlignmentElement2D> vae) {
	os << "[";

	switch (vae->getAlignmentType()) {
	case buw::eVerticalAlignmentType::Line: os << "VAElement2DLine    "; break;
	case buw::eVerticalAlignmentType::Arc: os << "VAElement2DArc     "; break;
	case buw::eVerticalAlignmentType::Parabola: os << "VAElement2DParabola"; break;
	default: break;
	}

	os << " " << vae->getStartPosition() << " " << vae->getEndPosition();

	os << "]";

	return os;
}

std::ostream& OpenInfraPlatform::Infrastructure::operator<<(std::ostream& os, const OpenInfraPlatform::Infrastructure::eVerticalAlignmentType vat) {
	switch (vat) {
	case eVerticalAlignmentType::Line: os << "Line"; break;
	case eVerticalAlignmentType::Arc: os << "Arc"; break;
	case eVerticalAlignmentType::Parabola: os << "Parabola"; break;
	default: os << "Unknown"; break;
	}

	return os;
}

std::string OpenInfraPlatform::Infrastructure::verticalAlignmentTypeToString(const OpenInfraPlatform::Infrastructure::eVerticalAlignmentType type) {
	std::stringstream ss;
	ss << type;
	return ss.str();
}
