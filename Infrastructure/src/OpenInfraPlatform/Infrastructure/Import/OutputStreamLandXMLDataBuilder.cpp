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

#include "OutputStreamLandXMLDataBuilder.h"

void OpenInfraPlatform::Infrastructure::OutputStreamLandXMLDataBuilder::createCrossSectPnt(const PropertySet& parameters)
{
	out << "CrossSectPnt" << std::endl;
	if (!parameters.isEmpty())
	{
		out << parameters;
	}
}

void OpenInfraPlatform::Infrastructure::OutputStreamLandXMLDataBuilder::createDesignCrossSectSurf(const PropertySet& parameters)
{
	out << "DesignCrossSectSurf" << std::endl;
	if (!parameters.isEmpty())
	{
		out << parameters;
	}
}

void OpenInfraPlatform::Infrastructure::OutputStreamLandXMLDataBuilder::createCrossSectionSurf(const PropertySet& parameters)
{
	out << "CrossSectionSurf" << std::endl;
	if (!parameters.isEmpty())
	{
		out << parameters;
	}
}

void OpenInfraPlatform::Infrastructure::OutputStreamLandXMLDataBuilder::createSurface(const PropertySet& parameters, 
	const LandXMLSurface& surface)
{
	out << "Surface" << std::endl;
	if (!parameters.isEmpty())
	{
		out << parameters;
	}

	out << "point count " << surface.getPointCount() << std::endl;
	out << "triangle count " << surface.getTriangleCount() << std::endl;
}

void OpenInfraPlatform::Infrastructure::OutputStreamLandXMLDataBuilder::createCircCurve(const PropertySet& parameters)
{
	out << "CircCurve" << std::endl;
	if (!parameters.isEmpty())
	{
		out << parameters;
	}
}

void OpenInfraPlatform::Infrastructure::OutputStreamLandXMLDataBuilder::createParaCurve(const PropertySet& parameters)
{
	out << "ParaCurve" << std::endl;
	if (!parameters.isEmpty())
	{
		out << parameters;
	}
}

void OpenInfraPlatform::Infrastructure::OutputStreamLandXMLDataBuilder::createPVI(const PropertySet& parameters)
{
	out << "PVI" << std::endl;
	if (!parameters.isEmpty())
	{
		out << parameters;
	}
}

void OpenInfraPlatform::Infrastructure::OutputStreamLandXMLDataBuilder::createProfAlign(const PropertySet& parameters)
{
	out << "ProfAlign" << std::endl;
	if (!parameters.isEmpty())
	{
		out << parameters;
	}
}

void OpenInfraPlatform::Infrastructure::OutputStreamLandXMLDataBuilder::createSpiral(const PropertySet& parameters)
{
	out << "Spiral" << std::endl;
	if (!parameters.isEmpty())
	{
		out << parameters;
	}
}

void OpenInfraPlatform::Infrastructure::OutputStreamLandXMLDataBuilder::createCurve(const PropertySet& parameters)
{
	out << "Curve" << std::endl;
	if (!parameters.isEmpty())
	{
		out << parameters;
	}
}

void OpenInfraPlatform::Infrastructure::OutputStreamLandXMLDataBuilder::createLine(const PropertySet& parameters)
{
	out << "Line" << std::endl;
	if (!parameters.isEmpty())
	{
		out << parameters;
	}
}

void OpenInfraPlatform::Infrastructure::OutputStreamLandXMLDataBuilder::createCoordGeom()
{
	out << "CoordGeom" << std::endl;
}

void OpenInfraPlatform::Infrastructure::OutputStreamLandXMLDataBuilder::createAlignment(const PropertySet& parameters)
{
	out << "Alignment" << std::endl;
	out << parameters;
}

OpenInfraPlatform::Infrastructure::OutputStreamLandXMLDataBuilder::OutputStreamLandXMLDataBuilder(std::ostream& out) :
out(out)
{

}
