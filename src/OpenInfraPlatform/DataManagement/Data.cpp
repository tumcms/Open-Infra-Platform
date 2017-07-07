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

#include "Data.h"

#include "OpenInfraPlatform/Infrastructure/Export/ExportIfcAlignment1x1.h"
#include "OpenInfraPlatform/Infrastructure/Import/ImportIfcAlignment1x1.h"

#include <BlueFramework/Application/DataManagement/Notification/NotifiyAfterEachActionOnlyOnce.h>
#include "buw.OIPInfrastructure.h"

#include "OpenInfraPlatform/Infrastructure/Export/ExportSVGEAdvanced.h"

#include "OpenInfraPlatform/IfcAlignment/model/IfcAlignmentP6Model.h"
#include "OpenInfraPlatform/IfcAlignment/reader/IfcStepReader.h"

#include "OpenInfraPlatform/IfcRoad/model/IfcRoadModel.h"
#include "OpenInfraPlatform/IfcRoad/reader/IfcStepReader.h"

#include "OpenInfraPlatform/IfcGeometryConverter/EMTIfc2x3EntityTypes.h"
#include "OpenInfraPlatform/IfcGeometryConverter/EMTIfc4EntityTypes.h"
#include "OpenInfraPlatform/IfcGeometryConverter/EMTIfcBridgeEntityTypes.h"

#include "OpenInfraPlatform/DataManagement/IfcZipper.h"

#include "OpenInfraPlatform/Infrastructure/Export/ExportLandXML.h"

#include "OpenInfraPlatform/Ifc2x3/model/Ifc2x3Model.h"
#include "OpenInfraPlatform/Ifc2x3/model/Ifc2x3Exception.h"
#include "OpenInfraPlatform/Ifc2x3/reader/IfcStepReader.h"

#include "OpenInfraPlatform/Ifc4/model/Ifc4Model.h"
#include "OpenInfraPlatform/Ifc4/model/Ifc4Exception.h"
#include "OpenInfraPlatform/Ifc4/reader/IfcStepReader.h"

#include "OpenInfraPlatform/IfcBridge/model/IfcBridgeModel.h"
#include "OpenInfraPlatform/IfcBridge/model/IfcBridgeException.h"
#include "OpenInfraPlatform/IfcBridge/reader/IfcStepReader.h"

#include "OpenInfraPlatform/IfcGeometryConverter/IfcImporter.h"

#include "OpenInfraPlatform/IfcGeometryConverter/GeometryInputData.h"
#include "OpenInfraPlatform/IfcGeometryConverter/IfcPeekStepReader.h"

#include "OpenInfraPlatform/Infrastructure/Import/ImportOSM.h"
#include "OpenInfraPlatform/Infrastructure/Import/ImportD40.h"

#include "OpenInfraPlatform/DataManagement/XYZImport.h"
#include "OpenInfraPlatform/DataManagement/RandomTerrainImport.h"
#include "OpenInfraPlatform/DataManagement/HeightMapImport.h"
#include "OpenInfraPlatform/DataManagement/MeshImport.h"

#include <QtXml>
#include <QtXmlPatterns>
#include <QProcess>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include "AsyncJob.h"

template <
	class IfcEntityTypesT,
	class IfcUnitConverterT,
	class IfcModelT,
	class IfcStepReaderT,
	class IfcExceptionT,
	class IfcEntityT
>
void importIfcGeometry(buw::ReferenceCounted<OpenInfraPlatform::IfcGeometryConverter::IfcGeometryModel> ifcGeometryModel, const std::string& filename);

OpenInfraPlatform::DataManagement::Data::Data() : 
BlueFramework::Application::DataManagement::Data(new BlueFramework::Application::DataManagement::NotifiyAfterEachActionOnlyOnce<OpenInfraPlatform::DataManagement::Data>()),
clearColor_(0.3f, 0.5f, 0.9f),
enableGradientClear_(true),
bDrawGrid_(false),
bDrawSkybox_(false),
bShowViewCube_(true),
bShowReferenceCoordinateSystem(true),
alignmentLineWidth_(1.5f),
currentJobID_(-1),
importer_(nullptr),
tempIfcGeometryModel_(nullptr),
tempPointCloud_(nullptr)
{
	pointCloud_ = new buw::PointCloud();
	clear(false);

	latestChangeFlag_ = (ChangeFlag) (ChangeFlag::AlignmentModel | ChangeFlag::DigitalElevationModel | ChangeFlag::IfcGeometry | ChangeFlag::PointCloud | ChangeFlag::Preferences);

	AsyncJob::getInstance().jobFinished.connect(boost::bind(&OpenInfraPlatform::DataManagement::Data::jobFinished, this, _1, _2));
}

OpenInfraPlatform::DataManagement::Data::~Data()
{
	if (pointCloud_)
		delete pointCloud_;
}

void OpenInfraPlatform::DataManagement::Data::save( const std::string & filename )
{
	QDomDocument doc;
	QDomProcessingInstruction header = doc.createProcessingInstruction( "xml", "version=\"1.0\"" );
	doc.appendChild( header );
	QDomElement root = doc.createElement( getApplicationNameXML() );
	root.setAttribute("version", getApplicationVersionString());
	doc.appendChild( root ); 

	// save entity objects
	QDomElement xmlAlignments = doc.createElement("Alignments");

	for (int i = 0; i < alignmentModel_->getAlignmentCount(); i++)
	{	
		buw::ReferenceCounted<buw::Alignment2DBased3D> alignment2d = std::static_pointer_cast<buw::Alignment2DBased3D>(alignmentModel_->getAlignment(i));
		QDomElement xmlAlignment2D = doc.createElement("Alignment2D");
		xmlAlignment2D.setAttribute("name", alignment2d->getName().toCString());
		if (alignment2d->hasHorizontalAlignment())
		{
			QDomElement xmlHorizaontal = doc.createElement("Horizontal");
			for (int horizontal_i = 0; horizontal_i < alignment2d->getHorizontalAlignment()->getAlignmentElementCount(); horizontal_i++)
			{
				buw::ReferenceCounted<buw::HorizontalAlignmentElement2D> horizontalElement = alignment2d->getHorizontalAlignment()->getAlignmentElementByIndex(horizontal_i);
				//std::cout << horizontalElement->getAlignmentType();
				if (horizontalElement->getAlignmentType() == buw::eHorizontalAlignmentType::Line)
				{
					buw::Vector2d start, end;
					horizontalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition, &start);
					horizontalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndPosition, &end);
					QDomElement xmlAlignmentLine = doc.createElement("Line");
					QDomElement xmlAlignmentLineStart = doc.createElement("Start");
					QDomElement xmlAlignmentLineEnd = doc.createElement("End");
					xmlAlignmentLineStart.setAttribute("startX", start.x() );
					xmlAlignmentLineStart.setAttribute("startY", start.y() );
					xmlAlignmentLineEnd.setAttribute("endX", end.x() );
					xmlAlignmentLineEnd.setAttribute("endY", end.y() );
					xmlAlignmentLine.setAttribute("length", alignment2d->getLength() );
					xmlAlignmentLine.appendChild(xmlAlignmentLineStart);
					xmlAlignmentLine.appendChild(xmlAlignmentLineEnd);
					xmlHorizaontal.appendChild(xmlAlignmentLine);
				}

				else if (horizontalElement->getAlignmentType() == buw::eHorizontalAlignmentType::Arc)
				{
					double radius;
					bool clockwiseBool;
					buw::Vector2d center, start, end;
					horizontalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition, &start);
					horizontalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndPosition, &end);
					horizontalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Center, &center);
					horizontalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Radius, &radius);
					horizontalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Clockwise, &clockwiseBool);
					QDomElement xmlAlignmentArc = doc.createElement("Arc");
					QDomElement xmlAlignmentArcStart = doc.createElement("Start");
					QDomElement xmlAlignmentArcEnd = doc.createElement("End");
					xmlAlignmentArc.setAttribute("centerX", center.x());
					xmlAlignmentArc.setAttribute("centerY", center.y());
					xmlAlignmentArc.setAttribute("radius", radius );
					xmlAlignmentArc.setAttribute("clockwise", clockwiseBool );
					xmlAlignmentArcStart.setAttribute("startX", start.x() );
					xmlAlignmentArcStart.setAttribute("startY", start.y() );
					xmlAlignmentArcEnd.setAttribute("endX", end.x() );
					xmlAlignmentArcEnd.setAttribute("endY", end.y() );
					xmlAlignmentArc.appendChild(xmlAlignmentArcStart);
					xmlAlignmentArc.appendChild(xmlAlignmentArcEnd);
					xmlHorizaontal.appendChild(xmlAlignmentArc);
				}

				else if (horizontalElement->getAlignmentType() == buw::eHorizontalAlignmentType::Clothoid)
				{
					double radiusStart, radiusEnd, length;
					bool clockwiseBool;
					buw::Vector2d start, end, pi;
					horizontalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition, &start);
					horizontalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndPosition, &end);
					horizontalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::RadiusStart, &radiusStart);
					horizontalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::RadiusEnd, &radiusEnd);
					horizontalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Clockwise, &clockwiseBool);
					horizontalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::PI, &pi);
					horizontalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Length, &length);
					QDomElement xmlAlignmentClothoid = doc.createElement("Clothoid");
					QDomElement xmlAlignmentClothoidStart = doc.createElement("start");
					QDomElement xmlAlignmentClothoidEnd = doc.createElement("end");
					QDomElement xmlAlignmentClothoidPI = doc.createElement("pi");
					xmlAlignmentClothoid.setAttribute("length", length );
					xmlAlignmentClothoid.setAttribute("radiusStart", radiusStart );
					xmlAlignmentClothoid.setAttribute("radiusEnd", radiusEnd );
					xmlAlignmentClothoid.setAttribute("clockwise", clockwiseBool );
					xmlAlignmentClothoidStart.setAttribute("startX", start.x() );
					xmlAlignmentClothoidStart.setAttribute("startY", start.y() );
					xmlAlignmentClothoidEnd.setAttribute("endX", end.x() );
					xmlAlignmentClothoidEnd.setAttribute("endY", end.y() );
					xmlAlignmentClothoidPI.setAttribute("piX", pi.x() );
					xmlAlignmentClothoidPI.setAttribute("piY", pi.y() );
					xmlAlignmentClothoid.appendChild(xmlAlignmentClothoidStart);
					xmlAlignmentClothoid.appendChild(xmlAlignmentClothoidEnd);
					xmlAlignmentClothoid.appendChild(xmlAlignmentClothoidPI);
					xmlHorizaontal.appendChild(xmlAlignmentClothoid);
				}
				else
				{
					std::cout << horizontalElement->getAlignmentType();
				}
			}
			xmlAlignment2D.appendChild(xmlHorizaontal);
		}

		if (alignment2d->hasVerticalAlignment())
		{
			QDomElement xmlVertical = doc.createElement("Vertical");
			std::vector<buw::profAlignElement> list = buw::createProfAlignElements(alignment2d->getVerticalAlignment());

			for (int vertical_i = 0; vertical_i < alignment2d->getVerticalAlignment()->getAlignmentElementCount(); vertical_i++)
			{
				buw::ReferenceCounted<buw::VerticalAlignmentElement2D> verticalElement = alignment2d->getVerticalAlignment()->getAlignmentElementByIndex(vertical_i);
				if (verticalElement->getAlignmentType() == buw::eVerticalAlignmentType::Parabola)
				{
					buw::Vector2d start, end, pvi;
					double inP, startGradient, endGradient;
					verticalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition, &start);
					verticalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndPosition, &end);
					verticalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::IntersectionPointDistance, &inP);
					verticalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::PVI, &pvi);
					verticalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartGradientAsPlaneAngleMeasure, &startGradient);
					verticalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndGradient, &endGradient);
					QDomElement xmlAlignmentParabola = doc.createElement("Parabola");
					QDomElement xmlAlignmentParabolaStart = doc.createElement("start");
					QDomElement xmlAlignmentParabolaEnd = doc.createElement("end");
					QDomElement xmlAlignmentParabolaPVI = doc.createElement("PVI");
					xmlAlignmentParabola.setAttribute("IntersectionPointDistance", inP);
					xmlAlignmentParabola.setAttribute("startGradient", startGradient);
					xmlAlignmentParabola.setAttribute("endGradient", endGradient);
					xmlAlignmentParabolaStart.setAttribute("startX", start.x() );
					xmlAlignmentParabolaStart.setAttribute("startY", start.y() );
					xmlAlignmentParabolaEnd.setAttribute("endX", end.x() );
					xmlAlignmentParabolaEnd.setAttribute("endY", end.y() );
					xmlAlignmentParabolaPVI.setAttribute("pviX", pvi.x() );
					xmlAlignmentParabolaPVI.setAttribute("pviY", pvi.y() );
					xmlAlignmentParabola.appendChild(xmlAlignmentParabolaStart);
					xmlAlignmentParabola.appendChild(xmlAlignmentParabolaEnd);
					xmlAlignmentParabola.appendChild(xmlAlignmentParabolaPVI);
					xmlVertical.appendChild(xmlAlignmentParabola);
				}

				if (verticalElement->getAlignmentType() == buw::eVerticalAlignmentType::Line)
				{
					buw::Vector2d start, end;
					verticalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition, &start);
					verticalElement->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndPosition, &end);
					QDomElement xmlAlignmentLine = doc.createElement("VerticalLine");
					QDomElement xmlAlignmentLineStart = doc.createElement("start");
					QDomElement xmlAlignmentLineEnd = doc.createElement("end");
					xmlAlignmentLineStart.setAttribute("startX", start.x() );
					xmlAlignmentLineStart.setAttribute("startY", start.y() );
					xmlAlignmentLineEnd.setAttribute("endX", end.x() );
					xmlAlignmentLineEnd.setAttribute("endY", end.y() );
					xmlAlignmentLine.appendChild(xmlAlignmentLineStart);
					xmlAlignmentLine.appendChild(xmlAlignmentLineEnd);
					xmlVertical.appendChild(xmlAlignmentLine);
				}
			}
			xmlAlignment2D.appendChild(xmlVertical);
		}
		xmlAlignments.appendChild(xmlAlignment2D);
	}
	root.appendChild(xmlAlignments);

	QFile file( filename.c_str() );
	if( !file.open( QIODevice::WriteOnly ) )
	{
		//return -1;
	}

	QTextStream ts( &file );
	ts << doc.toString();

	file.close();
}

void OpenInfraPlatform::DataManagement::Data::open( const std::string & filename )
{
	if (boost::filesystem::exists(filename))
	{
		buw::String buwstrFilename = filename.c_str();
		if (buwstrFilename.toLower().endsWith(".bic"))
		{
			alignmentModel_ = readBICFile(filename);
			pushChange(ChangeFlag::AlignmentModel); // Inform observer that new data is available
		}
		else
		{
			import(filename);
		}
		recentFileName = QString::fromUtf8(filename.c_str());
	}
}

buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::AlignmentModel> OpenInfraPlatform::DataManagement::Data::readBICFile(const std::string & filename)
{
	buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::AlignmentModel> alignmentModel_ = std::make_shared<OpenInfraPlatform::Infrastructure::AlignmentModel>();
	QDomDocument domDoc;
	QFile xmlFile(filename.c_str());
	if(xmlFile.open(QIODevice::ReadOnly))
	{
		if(domDoc.setContent(&xmlFile))
		{
			QDomElement domElement		= domDoc.documentElement();
			QDomNode rootNode			= domElement.firstChild();
			QDomNodeList alignmentList	= rootNode.childNodes();
			QDomNode domNode			= rootNode.firstChild();

			for(int i=0; i<alignmentList.length(); i++)
			{
				buw::ReferenceCounted<buw::HorizontalAlignment2D> horizontalAlignment = std::make_shared<buw::HorizontalAlignment2D>();
				buw::ReferenceCounted<buw::VerticalAlignment2D> verticalAlignment		= std::make_shared<buw::VerticalAlignment2D>();
				buw::ReferenceCounted<buw::Alignment2DBased3D> alignment2D			= std::make_shared<buw::Alignment2DBased3D>();
				std::string alignmentName;
				if(domNode.isElement())
				{
					QDomElement domElement = domNode.toElement();
					if(!domElement.isNull())
					{
						//std::cout << domElement.tagName().toStdString() + "\n";
						if(domElement.tagName() == "Alignment2D")
						{
							//std::cout << domElement.attribute("name").toStdString() + "\n";
							alignmentName = domElement.attribute("name").toStdString();
							QDomNode		horiNode			= domNode.firstChild();
							QDomNode		verNode				= domNode.lastChild();
							QDomNodeList	horiChildNodes		= horiNode.childNodes();
							QDomNodeList	verChildNodes		= verNode.childNodes();
							QDomNode		domHoriChildNode	= horiNode.firstChild();
							QDomNode		domVerChildNode		= verNode.firstChild();
							
							for(int i=0; i<horiChildNodes.length(); i++)
							{
								QDomElement domChildElement = domHoriChildNode.toElement();
								//std::cout << domChildElement.tagName().toStdString() + "\n";
								if(domChildElement.tagName() == "Arc")
								{
									//std::cout << "Arc Radius : " + domChildElement.attribute("radius").toStdString() + "\n";
									buw::Vector2d					center, start, end;
									bool							clockwise;
									start.x()					=	domChildElement.firstChildElement().attribute("startX").toDouble();
									start.y()					=	domChildElement.firstChildElement().attribute("startY").toDouble();
									end.x()						=	domChildElement.lastChildElement().attribute("endX").toDouble();
									end.y()						=	domChildElement.lastChildElement().attribute("endY").toDouble();
									center.x()					=	domChildElement.attribute("centerX").toDouble();
									center.y()					=	domChildElement.attribute("centerY").toDouble();
									clockwise					=	domChildElement.attribute("clockwise").toInt();
									buw::ReferenceCounted<buw::HorizontalAlignmentElement2DArc> arc			=	std::make_shared<buw::HorizontalAlignmentElement2DArc>(center, start, end, clockwise);
									horizontalAlignment->addElement(arc);
								}
								else if(domChildElement.tagName() == "Line")
								{
									//std::cout << "Line Length : " + domChildElement.attribute("length").toStdString() + "\n";
									//std::cout << domChildElement.firstChildElement().attribute("startX").toDouble();
									buw::Vector2d					start;
									buw::Vector2d					end;
									start.x()					=	domChildElement.firstChildElement().attribute("startX").toDouble();
									start.y()					=	domChildElement.firstChildElement().attribute("startY").toDouble();
									end.x()						=	domChildElement.lastChildElement().attribute("endX").toDouble();
									end.y()						=	domChildElement.lastChildElement().attribute("endY").toDouble();
									buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line			=	std::make_shared<buw::HorizontalAlignmentElement2DLine>(start, end);
									horizontalAlignment->addElement(line);
								}
								else
								{
									//std::cout << "Clothoid Length : " + domChildElement.attribute("length").toStdString() + "\n";
									buw::Vector2d					start, end, pi;
									double							radiusStart, radiusEnd, length;
									bool							clockwise;
									start.x()					=	domChildElement.firstChildElement().attribute("startX").toDouble();
									start.y()					=	domChildElement.firstChildElement().attribute("startY").toDouble();
									end.x()						=	domChildElement.firstChildElement().nextSiblingElement().attribute("endX").toDouble();
									end.y()						=	domChildElement.firstChildElement().nextSiblingElement().attribute("endY").toDouble();
									pi.x()						=	domChildElement.lastChildElement().attribute("piX").toDouble();
									pi.y()						=	domChildElement.lastChildElement().attribute("piY").toDouble();
									radiusStart					=	domChildElement.attribute("radiusStart").toDouble();
									radiusEnd					=	domChildElement.attribute("radiusEnd").toDouble();
									length						=	domChildElement.attribute("length").toDouble();
									clockwise					=	domChildElement.attribute("clockwise").toInt();

									double startCurvature = 0;
									if (radiusStart != 0 && radiusStart != std::numeric_limits<double>::infinity())
										startCurvature = 1 / radiusStart;

									double endCurvature = 0;
									if (radiusEnd != 0 && radiusEnd != std::numeric_limits<double>::infinity())
										endCurvature = 1 / radiusEnd;

									double startDirection = buw::HorizontalAlignmentElement2DClothoid::computeStartDirection(start, pi);									
									double clothoidConstant = buw::HorizontalAlignmentElement2DClothoid::computeClothoidConstant(length, startCurvature, endCurvature);
									bool entry = buw::HorizontalAlignmentElement2DClothoid::computeEntry(startCurvature, endCurvature);

									buw::clothoidDescription desc(start, startDirection, startCurvature, !clockwise, clothoidConstant, entry, length);
									buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> clothoid = std::make_shared<buw::HorizontalAlignmentElement2DClothoid>(desc);
									horizontalAlignment->addElement(clothoid);
								}
								domHoriChildNode = domHoriChildNode.nextSibling();
							}

							for(int i=0; i<verChildNodes.length(); i++)
							{
								QDomElement domChildElement = domVerChildNode.toElement();
								//std::cout << domChildElement.tagName().toStdString() + "\n";
								if(domChildElement.tagName() == "Parabola")
								{
									//std::cout << "Parabola StartX : " + domChildElement.firstChildElement().attribute("startX").toStdString() + "\n";
									buw::Vector2d start, end;
									double startGradient=0.0, endGradient=0.0;
									start.x()						=	domChildElement.firstChildElement().attribute("startX").toDouble();
									start.y()						=	domChildElement.firstChildElement().attribute("startY").toDouble();
									end.x()							=	domChildElement.firstChildElement().nextSiblingElement().attribute("endX").toDouble();
									end.y()							=	domChildElement.firstChildElement().nextSiblingElement().attribute("endY").toDouble();
									startGradient					=	domChildElement.attribute("startGradient").toDouble();
									endGradient						=	domChildElement.attribute("endGradient").toDouble();
									buw::ReferenceCounted<buw::VerticalAlignmentElement2DParabola> parabola		=	std::make_shared<buw::VerticalAlignmentElement2DParabola>(start, end, startGradient, endGradient);
									verticalAlignment->addElement(parabola);
								}
								else
								{
									//std::cout << "VerticalLine StartX : " + domChildElement.firstChildElement().attribute("startX").toStdString() + "\n";
									buw::Vector2d start, end;
									start.x()						=	domChildElement.firstChildElement().attribute("startX").toDouble();
									start.y()						=	domChildElement.firstChildElement().attribute("startY").toDouble();
									end.x()							=	domChildElement.lastChildElement().attribute("endX").toDouble();
									end.y()							=	domChildElement.lastChildElement().attribute("endY").toDouble();
									buw::ReferenceCounted<buw::VerticalAlignmentElement2DLine> vLine	=	std::make_shared<buw::VerticalAlignmentElement2DLine>(start, end);
									verticalAlignment->addElement(vLine);
								}
								domVerChildNode = domVerChildNode.nextSibling();
							}
						}
					}
				}
				alignment2D->setHorizontalAlignment(horizontalAlignment);
				alignment2D->setVerticalAlignment(verticalAlignment);
				std::wstring wstr(alignmentName.begin(), alignmentName.end());
				alignment2D->setName(wstr);
				alignmentModel_->addAlignment(alignment2D);
				domNode = domNode.nextSibling();
			}
		}
		xmlFile.close();
	}
	return alignmentModel_;
}

void OpenInfraPlatform::DataManagement::Data::clear(const bool notifyObservers) {
    trafficSignModel_ = std::make_shared<OpenInfraPlatform::Infrastructure::TrafficSignModel>();
    digitalElevationModel_ = std::make_shared<OpenInfraPlatform::Infrastructure::DigitalElevationModel>();
	alignmentModel_ = std::make_shared<OpenInfraPlatform::Infrastructure::AlignmentModel>();
	girderModel_ = std::make_shared<OpenInfraPlatform::Infrastructure::GirderModel>();
	slabFieldModel_ = std::make_shared<OpenInfraPlatform::Infrastructure::SlabFieldModel>();
	ifcGeometryModel_ = std::make_shared<IfcGeometryConverter::IfcGeometryModel>();
	selectedAlignmentIndex_ = 0;

	if (pointCloud_)
		delete pointCloud_;

	pointCloud_ = new buw::PointCloud();
	
	if (notifyObservers) {
		// The notification state is not used here, because a clear is not executed by an action.
		//m_pNotifiactionState->Change();

		pushChange(ChangeFlag::AlignmentModel | ChangeFlag::DigitalElevationModel | ChangeFlag::IfcGeometry | ChangeFlag::PointCloud | ChangeFlag::Preferences);

		Clear();
	}
}

void OpenInfraPlatform::DataManagement::Data::clear()
{
	clear(true);
}

void OpenInfraPlatform::DataManagement::Data::pushChange(OpenInfraPlatform::DataManagement::ChangeFlag flag)
{
	latestChangeFlag_ = flag;
	BlueFramework::Application::DataManagement::Data::Change();
}

OpenInfraPlatform::DataManagement::ChangeFlag OpenInfraPlatform::DataManagement::Data::getLatesChangeFlag()
{
	return latestChangeFlag_;
}


void OpenInfraPlatform::DataManagement::Data::import(const std::string & filename)
{
	BLUE_ASSERT(boost::filesystem::exists(filename))("File does not exist");

	if (boost::filesystem::exists(filename))
	{
		clear(false);
		merge_ = false;

		currentJobID_ = AsyncJob::getInstance().startJob(&Data::importJob, this, filename);
	}
}

void OpenInfraPlatform::DataManagement::Data::importIfcAlignment1_0(const std::string & filename)
{
	BLUE_ASSERT(boost::filesystem::exists(filename))("File does not exist");

	if (boost::filesystem::exists(filename))
	{
		clear(false);
		merge_ = false;

		currentJobID_ = AsyncJob::getInstance().startJob(&Data::startImportJobIfcAlignment1_0, this, filename);
	}
}


void OpenInfraPlatform::DataManagement::Data::startImportJobIfcAlignment1_0(const std::string& filename)
{
	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Importing ").append(filename));

	buw::String buwstrFilename = filename.c_str();
	
	importer_ = new buw::ImportIfcAlignment1x0(filename);		
}

void OpenInfraPlatform::DataManagement::Data::importJob(const std::string& filename)
{
	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Importing ").append(filename));

	buw::String buwstrFilename = filename.c_str();
	if (buwstrFilename.toLower().endsWith(".xml"))
	{
		// could be LandXML or OKSTRA

		// The QDomDocument class represents an XML document.
		QDomDocument xmlBOM;
		// Load xml file as raw data
		QFile f(filename.c_str());
		if (!f.open(QIODevice::ReadOnly))
		{
			// Error while loading file
			std::cerr << "Error while loading file" << std::endl;
			throw std::runtime_error("Error while loading file");
		}

		// Set data into the QDomDocument before processing
		xmlBOM.setContent(&f);
		f.close();

		// Extract the root markup
		QDomElement root = xmlBOM.documentElement();

		// Get root names and attributes
		std::string type = root.tagName().toStdString();

		if (boost::starts_with(type, "Land"))
		{
			OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Importing LandXML ").append(filename));
			importer_ = new buw::ImportLandXml(filename);
		}
		else
		{
			OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Importing Okstra ").append(filename));
			importer_ = new buw::ImportOkstra(filename);
		}
	}
	else if (buwstrFilename.toLower().endsWith(".cte"))
	{

		OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Importing Okstra ").append(filename));
		importer_ = new buw::ImportOkstra(filename);
	}
	else if (buwstrFilename.toLower().endsWith(".rnd"))
	{

		OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Importing RoadXML ").append(filename));
		importer_ = new buw::ImportRoadXML(filename);
	}
	else if (buwstrFilename.toLower().endsWith(".ifczip")) 
	{
		QUuid id = QUuid::createUuid();
		QString tempFilename = QDir::currentPath().append(QString("/").append(id.toString().append(".ifc")));

		OpenInfraPlatform::DataManagement::IfcZipper* importZipper = new OpenInfraPlatform::DataManagement::IfcZipper(nullptr, QString(filename.data()), tempFilename, INFL);

		importZipper->run();
		importJob(tempFilename.toStdString());

		QObject::connect(&OpenInfraPlatform::AsyncJob::getInstance(), &OpenInfraPlatform::AsyncJob::finished, importZipper, &OpenInfraPlatform::DataManagement::IfcZipper::removeFile);
		QObject::connect(importZipper, &OpenInfraPlatform::DataManagement::IfcZipper::fileDeleted, importZipper, &QObject::deleteLater);
	}
	else if (buwstrFilename.toLower().endsWith(".ifc") || buwstrFilename.toLower().endsWith(".stp"))
	{
		using OpenInfraPlatform::IfcGeometryConverter::IfcPeekStepReader;
		IfcPeekStepReader::IfcSchema ifcSchema = IfcPeekStepReader::parseIfcHeader(filename);

		if (ifcSchema == IfcPeekStepReader::IfcSchema::IFC_2 ||
			ifcSchema == IfcPeekStepReader::IfcSchema::IFC_4 ||
			ifcSchema == IfcPeekStepReader::IfcSchema::IFC_BRIDGE)
		{
			tempIfcGeometryModel_ = std::make_shared<IfcGeometryConverter::IfcGeometryModel>();

			if (ifcSchema == IfcPeekStepReader::IfcSchema::IFC_2)
			{
				OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Importing Ifc2x3 ").append(filename));

				using namespace OpenInfraPlatform::Ifc2x3;
				importIfcGeometry < emt::Ifc2x3EntityTypes, UnitConverter, Ifc2x3Model, IfcStepReader,
					Ifc2x3Exception, Ifc2x3Entity >(tempIfcGeometryModel_, filename);
			}
			else if (ifcSchema == IfcPeekStepReader::IfcSchema::IFC_4)
			{
				OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Importing Ifc4 ").append(filename));

				using namespace OpenInfraPlatform::Ifc4;
				importIfcGeometry<emt::Ifc4EntityTypes, UnitConverter, Ifc4Model, IfcStepReader,
					Ifc4Exception, Ifc4Entity>(tempIfcGeometryModel_, filename);
			}
			else if (ifcSchema == IfcPeekStepReader::IfcSchema::IFC_BRIDGE)
			{
				OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Importing IfcBridge ").append(filename));

				using namespace OpenInfraPlatform::IfcBridge;
				importIfcGeometry<emt::IfcBridgeEntityTypes, UnitConverter, IfcBridgeModel, IfcStepReader,
					IfcBridgeException, IfcBridgeEntity>(tempIfcGeometryModel_, filename);
			}
		}
		else if (ifcSchema == IfcPeekStepReader::IfcSchema::IFC_4x1)
		{
			OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Importing IfcAlignment ").append(filename));
			//importer_ = new buw::ImportIfcAlignment1x0(filename);
			importer_ = new buw::ImportIfcAlignment1x1(filename);
		}
		else if (ifcSchema == IfcPeekStepReader::IfcSchema::IFC_ROAD)
		{

			OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Importing IfcRoad ").append(filename));
			importer_ = new buw::ImportIfcRoad(filename);
		}
		else
		{
			throw::std::exception("IFC file schema is not support by application.");
		}
	}
	else if (buwstrFilename.toLower().endsWith(".osm"))
	{
		importOSMJob(filename, buw::ImportOSM::getDefaultFilter(), 2);
	}
	else if (buwstrFilename.toLower().endsWith(".d40"))
	{
		importer_ = new buw::ImportD40Import(filename);
	}
}


void OpenInfraPlatform::DataManagement::Data::importOSM(const std::string& filename, const std::vector<std::string>& filter, int mode)
{
	BLUE_ASSERT(boost::filesystem::exists(filename))("File does not exist");

	buw::String buwstrFilename = filename.c_str();

	if (boost::filesystem::exists(filename) && buwstrFilename.toLower().endsWith(".osm"))
	{
		clear(false);
		merge_ = false;

		currentJobID_ = AsyncJob::getInstance().startJob(&Data::importOSMJob, this, filename, filter, mode);
	}
}
void OpenInfraPlatform::DataManagement::Data::importOSMJob(const std::string& filename, const std::vector<std::string>& filter, int mode)
{
	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Importing OpenStreetMap ").append(filename));
	importer_ = new buw::ImportOSM(filename, filter, mode);
}

void OpenInfraPlatform::DataManagement::Data::jobFinished(int jobID, bool completed)
{
	if (currentJobID_ != jobID || !completed)
		return;

	ChangeFlag flag = (ChangeFlag)0;
	if (importer_)
	{
		flag = flag | ChangeFlag::AlignmentModel | ChangeFlag::DigitalElevationModel | ChangeFlag::Preferences | ChangeFlag::TrafficModel | ChangeFlag::GirderModel | ChangeFlag::SlabFieldModel;

		if (merge_)
		{
			for (auto alignment : importer_->getAlignmentModel()->getAlignments())
			{
				alignmentModel_->addAlignment(alignment);
			}
			for (auto surface : importer_->getDigitalElevationModel()->getSurfaces())
			{
				digitalElevationModel_->addSurface(surface);
			}
			for (auto breakLine : importer_->getDigitalElevationModel()->getBreakLines())
			{
				digitalElevationModel_->addBreakLine(breakLine);
			}
			for (auto girder : importer_->getGirderModel()->getAllItems())
			{
				girderModel_->addItem(girder);
			}
			for (auto slabField : importer_->getSlabFieldModel()->getAllItems())
			{
				slabFieldModel_->addItem(slabField);
			}
		}
		else
		{
			alignmentModel_ = importer_->getAlignmentModel();
			digitalElevationModel_ = importer_->getDigitalElevationModel();
			trafficSignModel_ = importer_->getTrafficSignModel();
			girderModel_ = importer_->getGirderModel();
			slabFieldModel_ = importer_->getSlabFieldModel();
		}

		delete importer_;
		importer_ = nullptr;
	}
	if (tempIfcGeometryModel_)
	{
		flag = flag | ChangeFlag::IfcGeometry;

		if (merge_)
		{
			throw new buw::NotImplementedYetException("merge ifcGeometry is not supported yet");
		}
		else
		{
			ifcGeometryModel_ = tempIfcGeometryModel_;
		}

		tempIfcGeometryModel_ = nullptr;
	}
	if (tempPointCloud_)
	{
		flag = flag | ChangeFlag::PointCloud;
		if (pointCloud_)
			delete pointCloud_;
		
		if (merge_)
		{
			for (auto point : tempPointCloud_->points)
			{
				pointCloud_->points.push_back(point);
			}
			pointCloud_->minPos = buw::minimizedVector(pointCloud_->minPos, tempPointCloud_->minPos);
			pointCloud_->maxPos = buw::minimizedVector(pointCloud_->maxPos, tempPointCloud_->maxPos);
		}
		else
		{
			pointCloud_ = tempPointCloud_;
		}
		tempPointCloud_ = nullptr;
	}

	pushChange(flag);
}

void OpenInfraPlatform::DataManagement::Data::exportIfcRoadTUMProposal(const std::string& filename)
{
	currentJobID_ = AsyncJob::getInstance().startJob(&Data::exportIfcRoadTUMProposalJob, this, filename);
}
void OpenInfraPlatform::DataManagement::Data::exportIfcRoadTUMProposalJob(const std::string& filename)
{
	buw::IfcRoadExportDescription desc;
	new buw::ExportIfcRoad(desc, alignmentModel_, digitalElevationModel_, filename);
}

void OpenInfraPlatform::DataManagement::Data::exportIfcAlignment1x1(const buw::ifcAlignmentExportDescription& desc, const std::string & filename) {
	currentJobID_ = AsyncJob::getInstance().startJob(&Data::exportIfcAlignment1x1Job, this, desc, filename);
}
void OpenInfraPlatform::DataManagement::Data::exportIfcAlignment1x1Job(const buw::ifcAlignmentExportDescription& desc, const std::string & filename) {
	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Exporting IFC Alignment 1x1").append(filename));

	new buw::ExportIfcAlignment1x1(desc, alignmentModel_, digitalElevationModel_, filename);
}

void OpenInfraPlatform::DataManagement::Data::exportIfcAlignment1x0(const buw::ifcAlignmentExportDescription& desc, const std::string & filename)
{
	currentJobID_ = AsyncJob::getInstance().startJob(&Data::exportIfcAlignmentJob, this, desc, filename);
}
void OpenInfraPlatform::DataManagement::Data::exportIfcAlignmentJob(const buw::ifcAlignmentExportDescription& desc, const std::string & filename)
{
	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Exporting IfcAlignment").append(filename));

	new buw::ExportIfcAlignment1x0(desc, alignmentModel_, digitalElevationModel_, filename);
}

void OpenInfraPlatform::DataManagement::Data::exportSVGAdvanced(const std::string& filename)
{
	currentJobID_ = AsyncJob::getInstance().startJob(&Data::exportSVGAdvancedJob, this, filename);
}
void OpenInfraPlatform::DataManagement::Data::exportSVGAdvancedJob(const std::string& filename)
{
	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Exporting SVG ").append(filename));

	new buw::ExportSVGEAdvanced(alignmentModel_, digitalElevationModel_, filename);
}

void OpenInfraPlatform::DataManagement::Data::exportSVG( const std::string& filename )
{
	currentJobID_ = AsyncJob::getInstance().startJob(&Data::exportSVGJob, this, filename);
}
void OpenInfraPlatform::DataManagement::Data::exportSVGJob(const std::string& filename)
{
	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Exporting SVG ").append(filename));

	buw::ExportSVG(alignmentModel_, digitalElevationModel_, filename);
}

void OpenInfraPlatform::DataManagement::Data::exportOkstra(const std::string& filename, const std::string& version)
{
	currentJobID_ = AsyncJob::getInstance().startJob(&Data::exportOkstraJob, this, filename, version);
}
void OpenInfraPlatform::DataManagement::Data::exportOkstraTranslated(const std::string& filename)
{
	currentJobID_ = AsyncJob::getInstance().startJob(&Data::exportOkstraJobTranslated, this, filename);
}
void OpenInfraPlatform::DataManagement::Data::exportOkstraJob(const std::string& filename, const std::string& version)
{
	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Exporting Okstra ").append(filename));

	auto delimiter = version.find(".");
	auto major = version.substr(0, delimiter);
	auto minor = version.substr(delimiter + 1, version.size() - 1);

	buw::ExportOkstra(stoi(major), stoi(minor), alignmentModel_, digitalElevationModel_, filename);
}

void OpenInfraPlatform::DataManagement::Data::exportOkstraJobTranslated(const std::string& filename)
{
	std::string tmpfilename = filename + ".tmp.xml";
	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Exporting Okstra ").append(filename));
	buw::ExportOkstra(2, 17, alignmentModel_, digitalElevationModel_, tmpfilename);

	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("translating Okstra ").append(filename));
	QProcess process;
	process.start("InstanceLevelTranslator.exe", { tmpfilename.c_str(), filename.c_str() });
	process.waitForFinished(-1);

	QFile::remove(tmpfilename.c_str());
}


void OpenInfraPlatform::DataManagement::Data::export3DAlignmentAsTextfile(const std::string& filename)
{
	currentJobID_ = AsyncJob::getInstance().startJob(&Data::export3DAlignmentAsTextfileJob, this, filename);
}

void OpenInfraPlatform::DataManagement::Data::export3DAlignmentAsTextfileJob(const std::string& filename)
{
	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Exporting Textfile ").append(filename));

	std::ofstream outfile;
	outfile.open(filename.c_str());

	outfile << "Format: X/Y/Z/stationing" << std::endl;

	for (int i = 0; i < alignmentModel_->getAlignmentCount(); i++)
	{
		auto a = alignmentModel_->getAlignment(i);

		outfile << "--------------------------------------------" << std::endl;
		outfile << "Name         : " << a->getName().toCString() << std::endl;
		outfile << "Start Station: " << a->getStartStation() << std::endl;
		outfile << "End Station  : " << a->getEndStation() << std::endl;

		for (double s = a->getStartStation(); s < a->getEndStation(); s += 1.0)
		{
			buw::Vector3d pos = a->getPosition(s);
			outfile << std::fixed << pos << " " << s << std::endl;
		}
	}

	outfile.close();
}

void OpenInfraPlatform::DataManagement::Data::createExcelReport(const std::string& filename, bool useDegree)
{
	currentJobID_ = AsyncJob::getInstance().startJob(&Data::createExcelReportJob, this, filename, useDegree);
}

void OpenInfraPlatform::DataManagement::Data::createExcelReportJob(const std::string& filename, bool useDegree)
{
	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Creating excel report ").append(filename));

	buw::ifcAlignmentExportDescription desc;
	desc.exportAlignment = true;
	desc.exportTerrain = true;
	desc.useRadiansInsteadOfDegrees = !useDegree;

	QUuid id = QUuid::createUuid();
	QString tempIfcFilename = QDir::currentPath().append(QString("/").append(id.toString().append(".ifc")));
	QString tempLandXMLFilename = QDir::currentPath().append(QString("/").append(id.toString().append(".xml")));

	std::string ifcFilename = tempIfcFilename.toStdString(); // "alignment.ifc"; //"C:/Users/no68koc/Desktop/alignment.ifc";//
	std::string landXMLFilename = tempLandXMLFilename.toStdString(); //  "alignment.xml"; //"C:/Users/no68koc/Desktop/alignment.xml";//

	exportIfcAlignment1x1Job(desc, ifcFilename);
	exportLandXMLJob(landXMLFilename);

	buw::IfcAlignment1x1ExcelReport ec(filename.c_str(), landXMLFilename.c_str(), ifcFilename.c_str());
}

void OpenInfraPlatform::DataManagement::Data::exportLandXML(const std::string& filename)
{
	currentJobID_ = AsyncJob::getInstance().startJob(&Data::exportLandXMLJob, this, filename);
}

void OpenInfraPlatform::DataManagement::Data::exportLandXMLJob(const std::string& filename)
{
	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Exporting LandXML ").append(filename));

	new buw::ExportLandXML(alignmentModel_, digitalElevationModel_, filename);
}

void OpenInfraPlatform::DataManagement::Data::addAlignment( buw::ReferenceCounted<buw::IAlignment3D> alignment )
{
	alignmentModel_->addAlignment(alignment);
	pushChange(ChangeFlag::AlignmentModel);
}

void OpenInfraPlatform::DataManagement::Data::deleteAlignment(buw::ReferenceCounted<buw::IAlignment3D> alignment)
{
	alignmentModel_->deleteAlignment(alignment);
	pushChange(ChangeFlag::AlignmentModel);
}

void OpenInfraPlatform::DataManagement::Data::addSurface(buw::ReferenceCounted<buw::Surface> surface)
{
	digitalElevationModel_->addSurface(surface);
	pushChange(ChangeFlag::DigitalElevationModel);
}

void OpenInfraPlatform::DataManagement::Data::deleteSurface(buw::ReferenceCounted<buw::Surface> surface)
{
	digitalElevationModel_->deleteSurface(surface);
	pushChange(ChangeFlag::DigitalElevationModel);
}

void OpenInfraPlatform::DataManagement::Data::setClearColor( const buw::Color3f& color )
{
	clearColor_ = color;

	pushChange(ChangeFlag::Preferences);
}

buw::Color3f OpenInfraPlatform::DataManagement::Data::getClearColor()
{
	return clearColor_;
}

void OpenInfraPlatform::DataManagement::Data::enableGradientClear( const bool enable )
{
	enableGradientClear_ = enable;

	pushChange(ChangeFlag::Preferences);
}

bool OpenInfraPlatform::DataManagement::Data::isGradientClearEnabled() const
{
	return enableGradientClear_;
}

bool OpenInfraPlatform::DataManagement::Data::isDrawGridEnabled() const
{
	return bDrawGrid_;
}

void OpenInfraPlatform::DataManagement::Data::enableDrawGrid( bool val )
{
	bDrawGrid_ = val;

	pushChange(ChangeFlag::Preferences);
}

const char* OpenInfraPlatform::DataManagement::Data::getApplicationName()
{
	return "TUM Open Infra Platform";
}

const char* OpenInfraPlatform::DataManagement::Data::getApplicationVersionString()
{
	return "2017";
}

const char* OpenInfraPlatform::DataManagement::Data::getApplicationOpenFileFilter()
{
	return "All files (*.*);;LandXML (*.xml);;OKSTRA (*.xml; *.cte);;IfcAlignment BuildingSmart P6 Step File (*.ifc);;TUM Open Infra Platform File (*.bic);;IfcRoad (TUM Proposal) ICCBEI 2015 (*.ifc);;IfcBridge Step File (*.stp)";
}

const char* OpenInfraPlatform::DataManagement::Data::getApplicationSaveFileFilter()
{
	return "TUM Open Infra Platform File (*.bic);;All files (*.*)";
}

const char* OpenInfraPlatform::DataManagement::Data::getApplicationImportFileFilter()
{
	return "LandXML (*.xml);;All files (*.*)";
}

const char* OpenInfraPlatform::DataManagement::Data::getApplicationNameXML()
{
	return "TUMOpenInfraPlatform";
}

buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::DigitalElevationModel> 
OpenInfraPlatform::DataManagement::Data::getDigitalElevationModel() const
{
	return digitalElevationModel_;
}

void OpenInfraPlatform::DataManagement::Data::enableShowReferenceCoordinateSystem( bool enable )
{
	bShowReferenceCoordinateSystem = enable;

	pushChange(ChangeFlag::Preferences);
}

bool OpenInfraPlatform::DataManagement::Data::isShowReferenceCoordinateSystemEnabled() const
{
	return bShowReferenceCoordinateSystem;
}

void OpenInfraPlatform::DataManagement::Data::enableSkybox( const bool enable )
{
	bDrawSkybox_ = enable;

	pushChange(ChangeFlag::Preferences);
}

bool OpenInfraPlatform::DataManagement::Data::isSkyboxEnabled() const
{
	return bDrawSkybox_;
}


void OpenInfraPlatform::DataManagement::Data::importXYZ(const std::string& filename, const buw::Vector2d& start, const buw::Vector2d& end)
{
	merge_ = true;
	currentJobID_ = AsyncJob::getInstance().startJob(&Data::importXYZJob, this, filename, start, end);
}

void OpenInfraPlatform::DataManagement::Data::importXYZJob(const std::string& filename, const buw::Vector2d& start, const buw::Vector2d& end)
{
	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Importing XYZ ").append(filename));

	importer_ = new buw::XYZImport(filename, start, end);
}

buw::Vector3d OpenInfraPlatform::DataManagement::Data::getOffset() const
{
	buw::Vector3d minPos;
	buw::Vector3d maxPos;
	if (digitalElevationModel_)
		digitalElevationModel_->getSurfacesExtend(minPos, maxPos);

	if (alignmentModel_ && alignmentModel_->getAlignmentCount() > 0)
	{
		auto aabb = alignmentModel_->getExtends();
		if (digitalElevationModel_ && digitalElevationModel_->getSurfaceCount() > 0)
		{
			minPos = buw::minimizedVector(minPos, aabb.getMinimum());
			maxPos = buw::maximizedVector(maxPos, aabb.getMaximum());
		}
		else
		{
			minPos = aabb.getMinimum();
			maxPos = aabb.getMaximum();
		}
	}

	if (pointCloud_->points.size() > 0)
	{
		minPos = pointCloud_->minPos;
		maxPos = pointCloud_->maxPos;
	}

	buw::Vector3d offsetViewArea = minPos + 0.5 * (maxPos - minPos);

	return offsetViewArea;
}

void OpenInfraPlatform::DataManagement::Data::createTerrainFromHeightMap(
	const std::string& filename)
{
	merge_ = true;
	currentJobID_ = AsyncJob::getInstance().startJob(&Data::createTerrainFromHeightMapJob, this, filename);
}

void OpenInfraPlatform::DataManagement::Data::createTerrainFromHeightMapJob(
	const std::string& filename)
{
	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Creating terrain from ").append(filename));

	importer_ = new buw::HeightmapImport(filename, getOffset());
}

void OpenInfraPlatform::DataManagement::Data::createTerrainFromMesh(
	const std::string& filename)
{
	merge_ = true;
	currentJobID_ = AsyncJob::getInstance().startJob(&Data::createTerrainFromMeshJob, this, filename);
}

void OpenInfraPlatform::DataManagement::Data::createTerrainFromMeshJob(
	const std::string& filename)
{
	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Importing Mesh ").append(filename));

	importer_ = new buw::MeshImport(filename, getOffset());
}


void OpenInfraPlatform::DataManagement::Data::createRandomTerrain(
	const buw::terrainDescription& td)
{
	merge_ = true;
	currentJobID_ = AsyncJob::getInstance().startJob(&Data::createRandomTerrainJob, this, td);
}
void OpenInfraPlatform::DataManagement::Data::createRandomTerrainJob(const buw::terrainDescription& td)
{
	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Creating random terrain"));
	importer_ = new buw::RandomTerrainImport(td, getOffset());
}


void OpenInfraPlatform::DataManagement::Data::showViewCube(const bool enable)
{
	bShowViewCube_ = enable;

	pushChange(ChangeFlag::Preferences);
}

bool OpenInfraPlatform::DataManagement::Data::isViewCubeEnabled()
{
	return bShowViewCube_;
}

void OpenInfraPlatform::DataManagement::Data::computeSurfaceProfile()
{
	buw::ReferenceCounted<buw::IAlignment3D> a = alignmentModel_->getAlignment(0);

	std::vector<std::pair<double, double>> surfaceProfile = digitalElevationModel_->getSurfaceProfile(a);
}

void OpenInfraPlatform::DataManagement::Data::setAlignmentLineWidth(const double width)
{
	alignmentLineWidth_ = static_cast<float>(width);

	pushChange(ChangeFlag::AlignmentModel);
}

buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::AlignmentModel> OpenInfraPlatform::DataManagement::Data::getAlignmentModel() const
{
	return alignmentModel_;
}

buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::GirderModel> OpenInfraPlatform::DataManagement::Data::getGirderModel() const
{
	return girderModel_;
}

buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::SlabFieldModel> OpenInfraPlatform::DataManagement::Data::getSlabFieldModel() const
{
	return slabFieldModel_;
}

buw::ReferenceCounted<OpenInfraPlatform::IfcGeometryConverter::IfcGeometryModel> OpenInfraPlatform::DataManagement::Data::getIfcGeometryModel() const
{ 
	return ifcGeometryModel_;
}

const std::vector<buw::LaserPoint>& OpenInfraPlatform::DataManagement::Data::getPointCloud() const
{
	return pointCloud_->points;
}

const int OpenInfraPlatform::DataManagement::Data::getPointCloudPointCount() const
{
	return pointCloud_->points.size();
}

void OpenInfraPlatform::DataManagement::Data::importLAS(const std::string& filename)
{
	merge_ = false;
	currentJobID_ = AsyncJob::getInstance().startJob(&Data::importLASJob, this, filename);
}
void OpenInfraPlatform::DataManagement::Data::importLASJob(const std::string& filename)
{
	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Importing laserscan ").append(filename));

	if (tempPointCloud_)
		delete tempPointCloud_;

	tempPointCloud_ = new buw::PointCloud();
	buw::importLASPointCloud(filename.c_str(), *tempPointCloud_);
}



void OpenInfraPlatform::DataManagement::Data::setShowFrameTimes(const bool enable)
{
	bShowFrameTime_ = enable;

	pushChange(ChangeFlag::Preferences);
}

bool OpenInfraPlatform::DataManagement::Data::showFrameTimes() const
{
	return bShowFrameTime_;
}

float OpenInfraPlatform::DataManagement::Data::getAlignmentLineWidth() const
{
	return alignmentLineWidth_;
}


void  OpenInfraPlatform::DataManagement::Data::setSelectedAlignment(int selectedIndex)
{
	if(selectedIndex != selectedAlignmentIndex_) {
		selectedAlignmentIndex_ = selectedIndex;
		pushChange(ChangeFlag::SelectedAlignmentIndex);
	}
}
int  OpenInfraPlatform::DataManagement::Data::getSelectedAlignment()
{
	return selectedAlignmentIndex_;
}


template <
	class IfcEntityTypesT,
	class IfcUnitConverterT,
	class IfcModelT,
	class IfcStepReaderT,
	class IfcExceptionT,
	class IfcEntityT
>
void importIfcGeometry(buw::ReferenceCounted<OpenInfraPlatform::IfcGeometryConverter::IfcGeometryModel> ifcGeometryModel, const std::string& filename)
{
	using namespace OpenInfraPlatform::IfcGeometryConverter;
	
	IfcImporterT<IfcEntityTypesT, IfcUnitConverterT, IfcModelT, IfcStepReaderT,
		IfcExceptionT, IfcEntityT> importer;

	try
	{
		importer.readStepFile(filename.c_str());
		importer.collectGeometryData();
	}
	catch (std::exception& e)
	{
		throw std::runtime_error(e.what());
	}

	std::map<int, std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>>& shapeDatas = importer.getShapeDatas();

	try
	{
		ConverterBuwT<IfcEntityTypesT>::createGeometryModel(ifcGeometryModel, shapeDatas);
	}
	catch (std::exception& e)
	{
		throw std::runtime_error(e.what());
	}
}
