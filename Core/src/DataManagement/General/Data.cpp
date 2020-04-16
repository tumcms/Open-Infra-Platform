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

//#ifdef OIP_MODULE_EARLYBINDING_IFC2X3
//	#include "reader/IFC2X3Reader.h"
//	#include "EMTIFC2X3EntityTypes.h"
//	//#include "IFC2X3.h"
//#endif

//#ifdef OIP_MODULE_EARLYBINDING_IFC4
//	#include "reader/IFC4Reader.h"
//	#include "EMTIFC4EntityTypes.h"
//	//#include "IFC4.h"
//#endif

#ifdef OIP_MODULE_EARLYBINDING_IFC4X1
	#include "reader/IFC4X1Reader.h"
	#include "EMTIFC4X1EntityTypes.h"
	#include "IFC4X1.h"
#endif

#ifdef OIP_MODULE_EARLYBINDING_IFC4X3_RC1
	#include "reader/IFC4X3_RC1Reader.h"
	#include "EMTIFC4X3_RC1EntityTypes.h"
	#include "IFC4X3_RC1.h"
#endif

#include "IfcGeometryConverter\IfcImporter.h"
#include "IfcGeometryConverter\GeometryInputData.h"
#include "IfcGeometryConverter\IfcPeekStepReader.h"

#include <QtXml>
#include <QtXmlPatterns>
#include <QProcess>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include "AsyncJob.h"

#ifdef OIP_WITH_POINT_CLOUD_PROCESSING
#ifdef _DEBUG
	#define OIP_PCD_LIB "OpenInfraPlatform.PointCloudProcessingd.lib"
#else
	#define OIP_PCD_LIB "OpenInfraPlatform.PointCloudProcessing.lib"
#endif
	#pragma comment( lib, OIP_PCD_LIB)
#endif

std::mutex OpenInfraPlatform::Core::IfcGeometryConverter::ConverterBuwUtil::s_geometryMutex;

OpenInfraPlatform::Core::DataManagement::Data::Data() : 
BlueFramework::Application::DataManagement::Data(new BlueFramework::Application::DataManagement::NotifiyAfterEachActionOnlyOnce<OpenInfraPlatform::Core::DataManagement::Data>()),
clearColor_(0.3f, 0.5f, 0.9f),
enableGradientClear_(true),
bDrawGrid_(false),
bDrawSkybox_(false),
bShowViewCube_(true),
bShowReferenceCoordinateSystem(true),
currentJobID_(-1),
tempIfcGeometryModel_(nullptr)
{
	clear(false);

	latestChangeFlag_ = (ChangeFlag) (ChangeFlag::IfcGeometry | ChangeFlag::PointCloud | ChangeFlag::Preferences);
	/*latestChangeFlag_ = (ChangeFlag)(ChangeFlag::AlignmentModel | ChangeFlag::DigitalElevationModel | ChangeFlag::IfcGeometry | ChangeFlag::PointCloud | ChangeFlag::Preferences | ChangeFlag::ProxyModel)*/;

	AsyncJob::getInstance().jobFinished.connect(boost::bind(&OpenInfraPlatform::Core::DataManagement::Data::jobFinished, this, _1, _2));
}

OpenInfraPlatform::Core::DataManagement::Data::~Data()
{
}


void OpenInfraPlatform::Core::DataManagement::Data::open( const std::string & filename )
{
	if (boost::filesystem::exists(filename))
	{
		import(filename);		
		recentFileName = QString::fromUtf8(filename.c_str());
	}
}


void OpenInfraPlatform::Core::DataManagement::Data::clear(const bool notifyObservers) {   
	ifcGeometryModel_ = std::make_shared<IfcGeometryConverter::IfcGeometryModel>();

	//pointCloud_ = buw::makeReferenceCounted<buw::PointCloud>();

	if (notifyObservers) {
		// The notification state is not used here, because a clear is not executed by an action.
		//m_pNotifiactionState->Change();

		pushChange(ChangeFlag::AlignmentModel | ChangeFlag::DigitalElevationModel | ChangeFlag::IfcGeometry | ChangeFlag::PointCloud | ChangeFlag::Preferences | ChangeFlag::ProxyModel);

		Clear();
	}
}

void OpenInfraPlatform::Core::DataManagement::Data::clear()
{
	clear(true);
}

void OpenInfraPlatform::Core::DataManagement::Data::pushChange(OpenInfraPlatform::Core::DataManagement::ChangeFlag flag)
{
	latestChangeFlag_ = flag;
	BlueFramework::Application::DataManagement::Data::Change();
}

OpenInfraPlatform::Core::DataManagement::ChangeFlag OpenInfraPlatform::Core::DataManagement::Data::getLatesChangeFlag()
{
	return latestChangeFlag_;
}


void OpenInfraPlatform::Core::DataManagement::Data::import(const std::string & filename)
{
	BLUE_ASSERT(boost::filesystem::exists(filename))("File does not exist");
	if(boost::filesystem::exists(filename)) {
		clear(false);
		merge_ = false;

		currentJobID_ = AsyncJob::getInstance().startJob(&Data::importJob, this, filename);
	}
}

void OpenInfraPlatform::Core::DataManagement::Data::importJob(const std::string& filename)
{
	OpenInfraPlatform::AsyncJob::getInstance().updateStatus(std::string("Importing ").append(filename));

	std::string filetype = filename.substr(filename.find_last_of('.'), filename.size() - 1);
	std::transform(filetype.begin(), filetype.end(), filetype.begin(), ::tolower);
	if (filetype == ".ifc" || filetype == ".stp")
	{
		using OpenInfraPlatform::Core::IfcGeometryConverter::IfcPeekStepReader;
		IfcPeekStepReader::IfcSchema ifcSchema = IfcPeekStepReader::parseIfcHeader(filename);
		tempIfcGeometryModel_ = std::make_shared<OpenInfraPlatform::Core::IfcGeometryConverter::IfcGeometryModel>();


		//if (ifcSchema == IfcPeekStepReader::IfcSchema::IFC2X3) {
		//	expressModel_ = OpenInfraPlatform::IFC2X3::IFC2X3Reader::FromFile(filename);
		//	BLUE_LOG(info) << "Imported entities from " << filename << " into express model.";
		//	auto importer = OpenInfraPlatform::Core::IfcGeometryConverter::IfcImporterT<emt::IFC2X3EntityTypes>();
		//	if (importer.collectGeometryData(expressModel_)) {
		//		auto converter = IfcGeometryConverter::ConverterBuwT< emt::IFC2X3EntityTypes>();
		//		if (converter.createGeometryModel(tempIfcGeometryModel_, importer.getShapeDatas())) {
		//			if (!tempIfcGeometryModel_->isEmpty()) {
		//				ifcGeometryModel_ = tempIfcGeometryModel_;
		//			}
		//		}
		//	}
		//}
		//else if (ifcSchema == IfcPeekStepReader::IfcSchema::IFC4) {
		//	expressModel_ = OpenInfraPlatform::IFC4::IFC4Reader::FromFile(filename);
		//	auto importer = OpenInfraPlatform::Core::IfcGeometryConverter::IfcImporterT<emt::IFC4EntityTypes>();
		//	if (importer.collectGeometryData(expressModel_)) {
		//		auto converter = IfcGeometryConverter::ConverterBuwT<emt::IFC4EntityTypes>();
		//		if (converter.createGeometryModel(tempIfcGeometryModel_, importer.getShapeDatas())) {
		//			if (!tempIfcGeometryModel_->isEmpty()) {
		//				ifcGeometryModel_ = tempIfcGeometryModel_;
		//			}
		//		}
		//	}
		//}
#ifdef OIP_MODULE_EARLYBINDING_IFC4X1
		if (ifcSchema == IfcPeekStepReader::IfcSchema::IFC4X1) {
			expressModel_ = OpenInfraPlatform::IFC4X1::IFC4X1Reader::FromFile(filename);
			auto importer = OpenInfraPlatform::Core::IfcGeometryConverter::IfcImporterT<emt::IFC4X1EntityTypes>();
			if (importer.collectGeometryData(expressModel_)) {
				auto converter = IfcGeometryConverter::ConverterBuwT<emt::IFC4X1EntityTypes>();
				if (converter.createGeometryModel(tempIfcGeometryModel_, importer.getShapeDatas())) {
					if (!tempIfcGeometryModel_->isEmpty()) {
						ifcGeometryModel_ = tempIfcGeometryModel_;
					}
				}
			}
		}
#endif //OIP_MODULE_EARLYBINDING_IFC4X1
#ifdef OIP_MODULE_EARLYBINDING_IFC4X3_RC1
		if (ifcSchema == IfcPeekStepReader::IfcSchema::IFC4X3_RC1) {
			expressModel_ = OpenInfraPlatform::IFC4X3_RC1::IFC4X3_RC1Reader::FromFile(filename);
			auto importer = OpenInfraPlatform::Core::IfcGeometryConverter::IfcImporterT<emt::IFC4X3_RC1EntityTypes>();
			if (importer.collectGeometryData(expressModel_)) {
				auto converter = IfcGeometryConverter::ConverterBuwT<emt::IFC4X3_RC1EntityTypes>();
				if (converter.createGeometryModel(tempIfcGeometryModel_, importer.getShapeDatas())) {
					if (!tempIfcGeometryModel_->isEmpty()) {
						ifcGeometryModel_ = tempIfcGeometryModel_;
					}
				}
			}
		}
#endif //OIP_MODULE_EARLYBINDING_IFC4X3_RC1

#ifdef OIP_WITH_POINT_CLOUD_PROCESSING
	QString extension = QString(filetype.substr(1, filetype.size() - 1).data());
	if (buw::PointCloud::GetSupportedExtensions().contains(extension)) {
		pointCloud_ = buw::PointCloud::FromFile(filename.data(), true);
		return;
	}
	else {
		BLUE_LOG(info) << "Supported PCD extensions: " << buw::PointCloud::GetSupportedExtensions().join(", ").toStdString() << ".";
	}
#endif

}


void OpenInfraPlatform::Core::DataManagement::Data::jobFinished(int jobID, bool completed)
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

#ifdef OIP_WITH_POINT_CLOUD_PROCESSING
	if (pointCloud_) {
		flag = flag | ChangeFlag::PointCloud;
	}
#endif
	pushChange(flag);
}



void OpenInfraPlatform::Core::DataManagement::Data::setClearColor( const buw::Color3f& color )
{
	clearColor_ = color;

	pushChange(ChangeFlag::Preferences);
}

buw::Color3f OpenInfraPlatform::Core::DataManagement::Data::getClearColor()
{
	return clearColor_;
}

void OpenInfraPlatform::Core::DataManagement::Data::enableGradientClear( const bool enable )
{
	enableGradientClear_ = enable;

	pushChange(ChangeFlag::Preferences);
}

bool OpenInfraPlatform::Core::DataManagement::Data::isGradientClearEnabled() const
{
	return enableGradientClear_;
}

bool OpenInfraPlatform::Core::DataManagement::Data::isDrawGridEnabled() const
{
	return bDrawGrid_;
}

void OpenInfraPlatform::Core::DataManagement::Data::enableDrawGrid( bool val )
{
	bDrawGrid_ = val;

	pushChange(ChangeFlag::Preferences);
}

const char* OpenInfraPlatform::Core::DataManagement::Data::getApplicationName()
{
	return "TUM Open Infra Platform";
}

const char* OpenInfraPlatform::Core::DataManagement::Data::getApplicationVersionString()
{
	return "2018";
}

const char* OpenInfraPlatform::Core::DataManagement::Data::getApplicationOpenFileFilter()
{
	return "All files (*.*);;LandXML (*.xml);;OKSTRA (*.xml; *.cte);;IfcAlignment BuildingSmart P6 Step File (*.ifc);;TUM Open Infra Platform File (*.bic);;IfcRoad (TUM Proposal) ICCBEI 2015 (*.ifc);;IfcBridge Step File (*.stp)";
}

const char* OpenInfraPlatform::Core::DataManagement::Data::getApplicationSaveFileFilter()
{
	return "TUM Open Infra Platform File (*.bic);;All files (*.*)";
}

const char* OpenInfraPlatform::Core::DataManagement::Data::getApplicationImportFileFilter()
{
	return "LandXML (*.xml);;All files (*.*)";
}

const char* OpenInfraPlatform::Core::DataManagement::Data::getApplicationNameXML()
{
	return "TUMOpenInfraPlatform";
}


void OpenInfraPlatform::Core::DataManagement::Data::enableShowReferenceCoordinateSystem( bool enable )
{
	bShowReferenceCoordinateSystem = enable;

	pushChange(ChangeFlag::Preferences);
}

bool OpenInfraPlatform::Core::DataManagement::Data::isShowReferenceCoordinateSystemEnabled() const
{
	return bShowReferenceCoordinateSystem;
}

void OpenInfraPlatform::Core::DataManagement::Data::enableSkybox( const bool enable )
{
	bDrawSkybox_ = enable;

	pushChange(ChangeFlag::Preferences);
}

bool OpenInfraPlatform::Core::DataManagement::Data::isSkyboxEnabled() const
{
	return bDrawSkybox_;
}


buw::Vector3d OpenInfraPlatform::Core::DataManagement::Data::getOffset() const
{
	buw::Vector3d minPos;
	buw::Vector3d maxPos;
	buw::Vector3d offsetViewArea = minPos + 0.5 * (maxPos - minPos);

	return offsetViewArea;
}


// Add Georeference

double  OpenInfraPlatform::Core::DataManagement::Data::getEastings()
{
	return m_Eastings;
}

void  OpenInfraPlatform::Core::DataManagement::Data::setEastings(double value)
{
	m_Eastings = value;
}

double  OpenInfraPlatform::Core::DataManagement::Data::getNorthings()
{
	return m_Northings;
}

void  OpenInfraPlatform::Core::DataManagement::Data::setNorthings(double value)
{
	m_Northings = value;
}


double  OpenInfraPlatform::Core::DataManagement::Data::getOrthogonalHeight()
{
	return m_OrthogonalHeight;
}

void  OpenInfraPlatform::Core::DataManagement::Data::setOrthogonalHeight(double value)
{
	m_OrthogonalHeight = value;
}


QString  OpenInfraPlatform::Core::DataManagement::Data::getEPSGcodeName()
{
	return m_Name;
}

void  OpenInfraPlatform::Core::DataManagement::Data::setEPSGcodeName(QString value)
{
	m_Name = value;
}



void OpenInfraPlatform::Core::DataManagement::Data::showViewCube(const bool enable)
{
	bShowViewCube_ = enable;

	pushChange(ChangeFlag::Preferences);
}

bool OpenInfraPlatform::Core::DataManagement::Data::isViewCubeEnabled()
{
	return bShowViewCube_;
}

buw::ReferenceCounted<OpenInfraPlatform::Core::IfcGeometryConverter::IfcGeometryModel> OpenInfraPlatform::Core::DataManagement::Data::getIfcGeometryModel() const
{ 
	return ifcGeometryModel_;
}

void OpenInfraPlatform::Core::DataManagement::Data::setShowFrameTimes(const bool enable)
{
	bShowFrameTime_ = enable;

	pushChange(ChangeFlag::Preferences);
}

bool OpenInfraPlatform::Core::DataManagement::Data::showFrameTimes() const
{
	return bShowFrameTime_;
}

#ifdef OIP_WITH_POINT_CLOUD_PROCESSING

std::shared_ptr<buw::PointCloud> OpenInfraPlatform::Core::DataManagement::Data::getPointCloud() {
	return pointCloud_;
}

void OpenInfraPlatform::Core::DataManagement::Data::exportPointCloud(const std::string& filename) const {
	//TODO
}

#endif