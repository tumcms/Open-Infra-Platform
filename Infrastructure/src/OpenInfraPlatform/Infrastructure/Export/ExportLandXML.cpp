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

#include "ExportLandXML.h"

#include "OpenInfraPlatform/Infrastructure/Import/LandXMLBaseTypes.h"
#include "OpenInfraPlatform/Infrastructure/Import/ImportLandXml.h"

#include <QtXml>
#include <QtXmlPatterns>

OpenInfraPlatform::Infrastructure::ExportLandXML::ExportLandXML(buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename) :
	Export(am, dem, filename)
{
	QDomDocument doc;
	QDomProcessingInstruction header = doc.createProcessingInstruction("xml", "version=\"1.0\"");
	doc.appendChild(header);
	QDomElement root = doc.createElement("LandXML");
	root.setAttribute("version", "1.2");

	root.setAttribute("xmlns", "http://www.landxml.org/schema/LandXML-1.2");
	root.setAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
	root.setAttribute("xsi:schemaLocation", "http://www.landxml.org/schema/LandXML-1.2 http://www.landxml.org/schema/LandXML-1.2/LandXML-1.2.xsd");
	root.setAttribute("version", "1.2");
	root.setAttribute("date", QDateTime::currentDateTime().toString("yyyy-MM-dd"));
	root.setAttribute("time", QDateTime::currentDateTime().toString("hh:mm:ss"));
	root.setAttribute("language", "English");
	root.setAttribute("readOnly", "false");
	doc.appendChild(root);

	// Unit
	QDomElement units = doc.createElement("Units");
	root.appendChild(units);

	QDomElement metric = doc.createElement("Metric");
	units.appendChild(metric);
	metric.setAttribute("areaUnit", "squareMeter");
	metric.setAttribute("linearUnit", "meter");
	metric.setAttribute("volumeUnit", "cubicMeter");
	metric.setAttribute("temperatureUnit", "celsius");
	metric.setAttribute("pressureUnit", "milliBars");
	metric.setAttribute("diameterUnit", "millimeter");
	metric.setAttribute("angularUnit", "decimal degrees");
	metric.setAttribute("directionUnit", "decimal degrees");

	// Project
	QDomElement project = doc.createElement("Project");
	root.appendChild(project);
	project.setAttribute("name", "BlueAlignmentProject");

	// Application
	QDomElement application = doc.createElement("Application");
	root.appendChild(application);
	application.setAttribute("name", "OpenInfraPlatform");
	application.setAttribute("desc", "OpenInfraPlatform");
	application.setAttribute("manufacturer", "Technische Universitaet Muenchen, Chair of Computational Modeling and Simulation");
	application.setAttribute("version", "2013");
	application.setAttribute("manufacturerURL", "https://www.cms.bgu.tum.de/en/");
	application.setAttribute("timeStamp", QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss"));

	// Surfaces
	for (int i = 0; i < digitalElevationModel_->getSurfaceCount(); i++)
	{
		QDomElement surfaces = doc.createElement("Surfaces");
		root.appendChild(surfaces);

		buw::ReferenceCounted<buw::Surface> currentSurface = digitalElevationModel_->getSurface(i);

		QDomElement surface = doc.createElement("Surface");
		surfaces.appendChild(surface);
		surface.setAttribute("name", currentSurface->getName());

		QDomElement definition = doc.createElement("Definition");
		surface.appendChild(definition);
		definition.setAttribute("surfType", "TIN");

		QDomElement points = doc.createElement("Pnts");
		definition.appendChild(points);

		for (int j = 0; j < currentSurface->getPoints().size(); j++)
		{
			QDomElement point = doc.createElement("P");
			points.appendChild(point);
			{
				std::stringstream ss;
				ss.precision(12);
				ss << currentSurface->getPoints()[j][1] << " " << currentSurface->getPoints()[j][0] << " " << currentSurface->getPoints()[j][2];
				QDomText text = doc.createTextNode(QString(ss.str().c_str()));
				point.appendChild(text);
			}
			point.setAttribute("id", j);
		}

		QDomElement faces = doc.createElement("Faces");
		definition.appendChild(faces);

		for (int j = 0; j < currentSurface->getTriangeFaces().size(); j++)
		{
			QDomElement face = doc.createElement("F");
			faces.appendChild(face);
			{
				std::stringstream ss;
				ss.precision(12);
				ss << currentSurface->getTriangeFaces()[j][0] << " " << currentSurface->getTriangeFaces()[j][1] << " " << currentSurface->getTriangeFaces()[j][2];
				QDomText text = doc.createTextNode(QString(ss.str().c_str()));
				face.appendChild(text);
			}
		}
	}

	// Alignments
	QDomElement alignments = doc.createElement("Alignments");
	root.appendChild(alignments);

	for (int i = 0; i < alignmentModel_->getAlignmentCount(); i++)
	{
		if (alignmentModel_->getAlignment(i)->getType() != buw::e3DAlignmentType::e2DBased)
		{
			continue;
		}

		buw::ReferenceCounted<buw::Alignment2DBased3D> alignment3d =
			std::static_pointer_cast<buw::Alignment2DBased3D>(alignmentModel_->getAlignment(i));

		QDomElement alignment = doc.createElement("Alignment");
		alignments.appendChild(alignment);

		alignment.setAttribute("staStart", alignment3d->getStartStation());
		alignment.setAttribute("length", alignment3d->getHorizontalAlignmentLength());
		alignment.setAttribute("name", alignment3d->getName().toCString());

		QDomElement CoordGeom = doc.createElement("CoordGeom");
		alignment.appendChild(CoordGeom);

		// write horizontal alignment
		if (alignment3d->hasHorizontalAlignment())
		{
			for (int hei = 0; hei < alignment3d->getHorizontalAlignment()->getAlignmentElementCount(); hei++)
			{
				buw::ReferenceCounted<buw::HorizontalAlignmentElement2D> he = alignment3d->getHorizontalAlignment()->getAlignmentElementByIndex(hei);

				if (he->getAlignmentType() == buw::eHorizontalAlignmentType::Line)
				{
					buw::Vector2d start;
					he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition, &start);

					buw::Vector2d end;
					he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndPosition, &end);

					QDomElement Line = doc.createElement("Line");
					CoordGeom.appendChild(Line);

					QDomElement Start = doc.createElement("Start");
					Line.appendChild(Start);
					{
						std::stringstream ss;
						ss.precision(20);
						ss << start.y() << " " << start.x();
						QDomText text = doc.createTextNode(QString(ss.str().c_str()));
						Start.appendChild(text);
					}

					QDomElement End = doc.createElement("End");
					Line.appendChild(End);
					{
						std::stringstream ss;
						ss.precision(20);
						ss << end.y() << " " << end.x();
						QDomText text = doc.createTextNode(QString(ss.str().c_str()));
						End.appendChild(text);
					}

					buw::Vector2d dir = end - start;
					Line.setAttribute("dir", buw::calculateAngleBetweenVectors(buw::Vector2d(1, 0), dir));
					double length = he->getLength();
					Line.setAttribute("length", length);
				}

				if (he->getAlignmentType() == buw::eHorizontalAlignmentType::Arc)
				{
					buw::Vector2d start;
					buw::Vector2d center;
					buw::Vector2d end;
					bool clockwise;
					double radius;

					he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition, &start);
					he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Center, &center);
					he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndPosition, &end);
					he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Clockwise, &clockwise);
					he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Radius, &radius);

					QDomElement Curve = doc.createElement("Curve");
					CoordGeom.appendChild(Curve);

					QDomElement Start = doc.createElement("Start");
					Curve.appendChild(Start);
					{
						std::stringstream ss;
						ss.precision(20);
						ss << start.y() << " " << start.x();
						QDomText text = doc.createTextNode(QString(ss.str().c_str()));
						Start.appendChild(text);
					}

					QDomElement Center = doc.createElement("Center");
					Curve.appendChild(Center);
					{
						std::stringstream ss;
						ss.precision(20);
						ss << center.y() << " " << center.x();
						QDomText text = doc.createTextNode(QString(ss.str().c_str()));
						Center.appendChild(text);
					}

					QDomElement End = doc.createElement("End");
					Curve.appendChild(End);
					{
						std::stringstream ss;
						ss.precision(20);
						ss << end.y() << " " << end.x();
						QDomText text = doc.createTextNode(QString(ss.str().c_str()));
						End.appendChild(text);
					}

					buw::Vector2d dir = end - start;
					double length = he->getLength();

					Curve.setAttribute("rot", clockwise ? "cw" : "ccw");
					Curve.setAttribute("dirStart", buw::calculateAngleBetweenVectors(buw::Vector2d(0, 1), dir));
					Curve.setAttribute("length", length);
					Curve.setAttribute("radius", radius);
				}

				if (he->getAlignmentType() == buw::eHorizontalAlignmentType::Clothoid)
				{
					buw::Vector2d start;
					he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition, &start);

					buw::Vector2d pi;
					he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::PI, &pi);

					buw::Vector2d end;
					he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndPosition, &end);

					double radiusStart;
					he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::RadiusStart, &radiusStart);

					double radiusEnd;
					he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::RadiusEnd, &radiusEnd);

					bool clockwise;
					he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Clockwise, &clockwise);

					QDomElement Spiral = doc.createElement("Spiral");
					CoordGeom.appendChild(Spiral);

					QDomElement Start = doc.createElement("Start");
					Spiral.appendChild(Start);
					{
						std::stringstream ss;
						ss.precision(20);
						ss << start.y() << " " << start.x();
						QDomText text = doc.createTextNode(QString(ss.str().c_str()));
						Start.appendChild(text);
					}

					QDomElement PI = doc.createElement("PI");
					Spiral.appendChild(PI);
					{
						std::stringstream ss;
						ss.precision(20);
						ss << pi.y() << " " << pi.x();
						QDomText text = doc.createTextNode(QString(ss.str().c_str()));
						PI.appendChild(text);
					}

					QDomElement End = doc.createElement("End");
					Spiral.appendChild(End);
					{
						std::stringstream ss;
						ss.precision(20);
						ss << end.y() << " " << end.x();
						QDomText text = doc.createTextNode(QString(ss.str().c_str()));
						End.appendChild(text);
					}

					if (radiusEnd <= std::numeric_limits<double>::max() &&
						radiusEnd >= -std::numeric_limits<double>::max())
						Spiral.setAttribute("radiusEnd", radiusEnd);
					else
						Spiral.setAttribute("radiusEnd", "INF");

					buw::Vector2d dir = end - start;

					Spiral.setAttribute("dir", buw::calculateAngleBetweenVectors(buw::Vector2d(0, 1), dir));
					Spiral.setAttribute("rot", clockwise ? "cw" : "ccw");

					double length = he->getLength();
					Spiral.setAttribute("length", length);

					if (radiusStart <= std::numeric_limits<double>::max() &&
						radiusStart >= -std::numeric_limits<double>::max())
						Spiral.setAttribute("radiusStart", radiusStart);
					else
						Spiral.setAttribute("radiusStart", "INF");

					Spiral.setAttribute("spiType", "clothoid");
				}
			}
		}

		QDomElement Profile = doc.createElement("Profile");
		alignment.appendChild(Profile);
		QDomElement ProfAlign = doc.createElement("ProfAlign");
		Profile.appendChild(ProfAlign);

		// write vertical alignment
		if (alignment3d->hasVerticalAlignment())
		{
			std::vector<buw::profAlignElement> list = buw::createProfAlignElements(alignment3d->getVerticalAlignment());

			for (int k = 0; k < list.size(); k++)
			{
				if (list[k].type == buw::eProfAlignType::PVI)
				{

					buw::Vector2d pvi = list[k].position;
					QDomElement PVI = doc.createElement("PVI");
					ProfAlign.appendChild(PVI);
					{
						std::stringstream ss;
						ss.precision(20);
						ss << pvi.x() << " " << pvi.y();
						QDomText text = doc.createTextNode(QString(ss.str().c_str()));
						PVI.appendChild(text);
					}
				}
				else if (list[k].type == buw::eProfAlignType::ParaCurve)
				{
					buw::Vector2d pvi;
					double intersectionPointDistance = 0;

					pvi = list[k].position;
					intersectionPointDistance = list[k].length;

					QDomElement ParaCurve = doc.createElement("ParaCurve");
					ProfAlign.appendChild(ParaCurve);
					{
						std::stringstream ss;
						ss.precision(20);
						ss << pvi.x() << " " << pvi.y();
						QDomText text = doc.createTextNode(QString(ss.str().c_str()));
						ParaCurve.appendChild(text);
					}
					ParaCurve.setAttribute("length", intersectionPointDistance);
				}
			}
		}
	}

	QFile file(filename.c_str());
	if (!file.open(QIODevice::WriteOnly))
	{
		//return -1;
	}

	QTextStream ts(&file);
	ts << doc.toString();

	file.close();
}