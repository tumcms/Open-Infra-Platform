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

#include "HorizontalAlignmentElement2D.h"

#include "qapplication.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

eHorizontalAlignmentType HorizontalAlignmentElement2D::getAlignmentType() const {
	return eHorizontalAlignmentType::Unknown;
}

bool HorizontalAlignmentElement2D::genericQuery(const int /*id*/, void* /*result*/) const {
	return false;
}

std::string horizontalAlignmentTypeToString(const eHorizontalAlignmentType type) {
	switch (type) {
	case eHorizontalAlignmentType::Line: return QApplication::tr("Line").toStdString();

	case eHorizontalAlignmentType::Arc: return QApplication::tr("Arc").toStdString();

	case eHorizontalAlignmentType::Clothoid: return QApplication::tr("Clothoid").toStdString();

	case eHorizontalAlignmentType::Bloss: return QApplication::tr("Bloss").toStdString();

	case eHorizontalAlignmentType::Unknown: return QApplication::tr("Unknown").toStdString();

	default: break;
	}
	return QApplication::tr("Unknown").toStdString();
}

std::ostream& operator<<(std::ostream& os, const OpenInfraPlatform::Infrastructure::eHorizontalAlignmentType hat) {
	os << horizontalAlignmentTypeToString(hat);
	return os;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END