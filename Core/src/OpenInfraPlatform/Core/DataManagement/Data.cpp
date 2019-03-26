/*
    Copyright (c) 2018 Technical University of Munich
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

#include <BlueFramework/Application/DataManagement/Notification/NotifiyAfterEachActionOnlyOnce.h>

#include "reader/IFC2X3Reader.h"
#include "reader/IFC4Reader.h"
#include "reader/IFC4X1Reader.h"
#include "reader/IFC4X2_BIM4ROADReader.h"
#include "reader/IFC4X2_DRAFT_1Reader.h"

//#include "EMTIFC2X3EntityTypes.h"
//#include "EMTIFC4EntityTypes.h"
//#include "EMTIFC4X1EntityTypes.h"
//#include "EMTIFC4X2_BIM4ROADEntityTypes.h"
//#include "EMTIFC4X2_DRAFT_1EntityTypes.h"

#include "OpenInfraPlatform/Core/IfcGeometryConverter/IfcImporter.h"
#include "OpenInfraPlatform/Core/IfcGeometryConverter/GeometryInputData.h"
#include "OpenInfraPlatform/Core/IfcGeometryConverter/IfcPeekStepReader.h"

#include <QtXml>
#include <QtXmlPatterns>
#include <QProcess>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include "AsyncJob.h"


OpenInfraPlatform::DataManagement::Data::Data() : 
BlueFramework::Application::DataManagement::Data(new BlueFramework::Application::DataManagement::NotifiyAfterEachActionOnlyOnce<OpenInfraPlatform::DataManagement::Data>()),
clearColor_(0.3f, 0.5f, 0.9f),
enableGradientClear_(true),
bDrawGrid_(false),
bDrawSkybox_(false),
bShowViewCube_(true),
bShowReferenceCoordinateSystem(true),
currentJobID_(-1),
tempIfcGeometryModel_(nullptr),
tempPointCloud_(nullptr),
pointCloud_(nullptr)
{
	clear(false);

	latestChangeFlag_ = (ChangeFlag) (ChangeFlag::AlignmentModel | ChangeFlag::DigitalElevationModel | ChangeFlag::IfcGeometry | ChangeFlag::PointCloud | ChangeFlag::Preferences | ChangeFlag::ProxyModel);

	AsyncJob::getInstance().jobFinished.connect(boost::bind(&OpenInfraPlatform::DataManagement::Data::jobFinished, this, _1, _2));
}

OpenInfraPlatform::DataManagement::Data::~Data()
{
	if (pointCloud_)
		pointCloud_ = nullptr;
}


void OpenInfraPlatform::DataManagement::Data::open( const std::string & filename )
{
	if (boost::filesystem::exists(filename))
	{
		import(filename);		
		recentFileName = QString::fromUtf8(filename.c_str());
	}
}


void OpenInfraPlatform::DataManagement::Data::clear(const bool notifyObservers) {   
	ifcGeometryModel_ = std::make_shared<IfcGeometryConverter::IfcGeometryModel>();

	if (pointCloud_)
		pointCloud_ = nullptr;

	//pointCloud_ = buw::makeReferenceCounted<buw::PointCloud>();
	
	if (notifyObservers) {
		// The notification state is not used here, because a clear is not executed by an action.
		//m_pNotifiactionState->Change();

		pushChange(ChangeFlag::AlignmentModel | ChangeFlag::DigitalElevationModel | ChangeFlag::IfcGeometry | ChangeFlag::PointCloud | ChangeFlag::Preferences | ChangeFlag::ProxyModel);

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
	if(boost::filesystem::exists(filename)) {
		clear(false);
		merge_ = false;

		currentJobID_ = AsyncJob::getInstance().startJob(&Data::importJob, this, filename);
	}
}

void OpenInfraPlatform::DataManagement::Data::importJob(const std::string& filename)
{
	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Importing ").append(filename));

	std::string filetype = filename.substr(filename.find_last_of('.'), filename.size() - 1);
	std::transform(filetype.begin(), filetype.end(), filetype.begin(), ::tolower);
	if (filetype == ".ifc" || filetype == ".stp")
	{
		using OpenInfraPlatform::IfcGeometryConverter::IfcPeekStepReader;
		IfcPeekStepReader::IfcSchema ifcSchema = IfcPeekStepReader::parseIfcHeader(filename);
		tempIfcGeometryModel_ = std::make_shared<IfcGeometryConverter::IfcGeometryModel>();


		switch (ifcSchema) {
		case IfcPeekStepReader::IfcSchema::IFC2X3:
			expressModel_ = OpenInfraPlatform::IFC2X3::IFC2X3Reader::FromFile(filename);
			break;
		case IfcPeekStepReader::IfcSchema::IFC4:
			expressModel_ = OpenInfraPlatform::IFC4::IFC4Reader::FromFile(filename);
			break;
		case IfcPeekStepReader::IfcSchema::IFC4X1:
			expressModel_ = OpenInfraPlatform::IFC4X1::IFC4X1Reader::FromFile(filename);
			break;
		case IfcPeekStepReader::IfcSchema::IFC4X2_BIM4ROAD:
			expressModel_ = OpenInfraPlatform::IFC4X2_BIM4ROAD::IFC4X2_BIM4ROADReader::FromFile(filename);
			break;
		case IfcPeekStepReader::IfcSchema::IFC4X2_DRAFT_1:
			expressModel_ = OpenInfraPlatform::IFC4X2_DRAFT_1::IFC4X2_DRAFT_1Reader::FromFile(filename);
			break;
		default:
			expressModel_ = nullptr;
			BLUE_LOG(error) << "No matching schema detected";
			break;
		}
		
	}
	
}


void OpenInfraPlatform::DataManagement::Data::jobFinished(int jobID, bool completed)
{
	if(currentJobID_ != jobID) {
		/*If jobID doesn't match, write errror to log file and display a dialog and return.*/
		BLUE_LOG(error) << "Wrong jobID. Expected " << QString::number(currentJobID_).toStdString() << " was " << QString::number(jobID).toStdString();
		QString errorMessage = "No matching jobID for this job. Error message was written to log file.";
		QString errorTitle = "ID Error!";
		QMessageBox(QMessageBox::Icon::Critical, errorTitle, errorMessage, QMessageBox::StandardButton::Ok, nullptr).exec();		return;
		return;
	}

	if(!completed) {
		/*If job was cancelled show message box to inform the user and return.*/
		QString errorMessage = "Import job cancelled. Error message was written to log file.";
		QString errorTitle = "Import Error!";
		QMessageBox(QMessageBox::Icon::Critical, errorTitle, errorMessage, QMessageBox::StandardButton::Ok, nullptr).exec();
		return;
	}

	ChangeFlag flag = (ChangeFlag)0;
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
			pointCloud_ = nullptr;
		
		if (merge_)
		{
			
		}
		else
		{
			pointCloud_ = tempPointCloud_;
		}
		tempPointCloud_ = nullptr;
	}

	pushChange(flag);
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
	return "2018";
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


buw::Vector3d OpenInfraPlatform::DataManagement::Data::getOffset() const
{
	buw::Vector3d minPos;
	buw::Vector3d maxPos;
	//if (digitalElevationModel_)
	//	digitalElevationModel_->getSurfacesExtend(minPos, maxPos);
	//
	//if (alignmentModel_ && alignmentModel_->getAlignmentCount() > 0)
	//{
	//	auto aabb = alignmentModel_->getExtends();
	//	if (digitalElevationModel_ && digitalElevationModel_->getSurfaceCount() > 0)
	//	{
	//		minPos = buw::minimizedVector(minPos, aabb.getMinimum());
	//		maxPos = buw::maximizedVector(maxPos, aabb.getMaximum());
	//	}
	//	else
	//	{
	//		minPos = aabb.getMinimum();
	//		maxPos = aabb.getMaximum();
	//	}
	//}

	if (pointCloud_->size() > 0)
	{
		CCVector3 min, max;
		pointCloud_->getBoundingBox(min, max);
		minPos = buw::Vector3d(min.x, min.y, min.z);
		maxPos = buw::Vector3d(max.x, max.y, max.z);
	}

	buw::Vector3d offsetViewArea = minPos + 0.5 * (maxPos - minPos);

	return offsetViewArea;
}


// Add Georeference

double  OpenInfraPlatform::DataManagement::Data::getEastings() 
{
	return m_Eastings;
}

void  OpenInfraPlatform::DataManagement::Data::setEastings(double value)
{
	m_Eastings = value;
}

double  OpenInfraPlatform::DataManagement::Data::getNorthings()
{
	return m_Northings;
}

void  OpenInfraPlatform::DataManagement::Data::setNorthings(double value)
{
	m_Northings = value;
}


double  OpenInfraPlatform::DataManagement::Data::getOrthogonalHeight()
{
	return m_OrthogonalHeight;
}

void  OpenInfraPlatform::DataManagement::Data::setOrthogonalHeight(double value)
{
	m_OrthogonalHeight = value;
}


QString  OpenInfraPlatform::DataManagement::Data::getEPSGcodeName()
{
	return m_Name;
}

void  OpenInfraPlatform::DataManagement::Data::setEPSGcodeName(QString value)
{
	m_Name = value;
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


buw::ReferenceCounted<OpenInfraPlatform::IfcGeometryConverter::IfcGeometryModel> OpenInfraPlatform::DataManagement::Data::getIfcGeometryModel() const
{ 
	return ifcGeometryModel_;
}

buw::ReferenceCounted<buw::PointCloud> OpenInfraPlatform::DataManagement::Data::getPointCloud() const
{
	return pointCloud_;
}

const int OpenInfraPlatform::DataManagement::Data::getPointCloudPointCount() const
{
	if(pointCloud_)
		return pointCloud_->size();
	else
		return -1;
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