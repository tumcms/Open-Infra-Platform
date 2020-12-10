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

#ifdef OIP_MODULE_EARLYBINDING_IFC2X3
	#include "reader/IFC2X3Reader.h"
	#include "EMTIFC2X3EntityTypes.h"
	#include "IFC2X3.h"
#endif

#ifdef OIP_MODULE_EARLYBINDING_IFC4
	#include "reader/IFC4Reader.h"
	#include "EMTIFC4EntityTypes.h"
	#include "IFC4.h"
#endif

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

#include "IfcGeometryConverter\GeometryInputData.h"
#include "IfcGeometryConverter\IfcPeekStepReader.h"
#include "IfcGeometryConverter\IfcImporterImpl.h"
#include "OffConverter\OffModel.h"
#include "Exception\IfcPeekReaderException.h"

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

OpenInfraPlatform::Core::DataManagement::Data::Data() : 
BlueFramework::Application::DataManagement::Data(new BlueFramework::Application::DataManagement::NotifiyAfterEachActionOnlyOnce<OpenInfraPlatform::Core::DataManagement::Data>()),
clearColor_(0.3f, 0.5f, 0.9f),
enableGradientClear_(true),
bDrawGrid_(false),
bDrawSkybox_(false),
bShowViewCube_(true),
currentJobID_(-1),
bShowReferenceCoordinateSystem(true)
{
	latestChangeFlag_ = ChangeFlag::All;

	AsyncJob::getInstance().jobFinished.connect(boost::bind(&OpenInfraPlatform::Core::DataManagement::Data::jobFinished, this, _1, _2));

}

OpenInfraPlatform::Core::DataManagement::Data::~Data()
{
	Clear();
}


void OpenInfraPlatform::Core::DataManagement::Data::open( const std::string & filename )
{
	if (boost::filesystem::exists(filename))
	{
		import(filename);
	}
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
		IfcPeekStepReader::IfcSchema ifcSchema;
		std::string strSchema;
		try
		{
			std::tie(strSchema,ifcSchema) = IfcPeekStepReader::parseIfcHeader(filename);
		}
		catch (oip::IfcPeekReaderException ex)
		{
			showError(ex.what(), "IFC version not known to OIP.");
			return;
		}
		
		if (ifcSchema == IfcPeekStepReader::IfcSchema::IFC2X3) {
#ifdef OIP_MODULE_EARLYBINDING_IFC2X3
			ParseExpressAndGeometryModel<emt::IFC2X3EntityTypes, OpenInfraPlatform::IFC2X3::IFC2X3Reader>(filename);
			return;
#else // OIP_MODULE_EARLYBINDING_IFC2X3
			IFCVersionNotCompiled("IFC2X3");
#endif // OIP_MODULE_EARLYBINDING_IFC2X3
		}

		if (ifcSchema == IfcPeekStepReader::IfcSchema::IFC4) {
#ifdef OIP_MODULE_EARLYBINDING_IFC4
			ParseExpressAndGeometryModel<emt::IFC4EntityTypes, OpenInfraPlatform::IFC4::IFC4Reader>(filename);
			return;
#else // OIP_MODULE_EARLYBINDING_IFC4
			IFCVersionNotCompiled("IFC4");
#endif // OIP_MODULE_EARLYBINDING_IFC4
		}

		if (ifcSchema == IfcPeekStepReader::IfcSchema::IFC4X1) {
#ifdef OIP_MODULE_EARLYBINDING_IFC4X1
			ParseExpressAndGeometryModel<emt::IFC4X1EntityTypes, OpenInfraPlatform::IFC4X1::IFC4X1Reader>(filename);
			return;
#else // OIP_MODULE_EARLYBINDING_IFC4X1
			IFCVersionNotCompiled("IFC4X1");
#endif //OIP_MODULE_EARLYBINDING_IFC4X1
		}

		if (ifcSchema == IfcPeekStepReader::IfcSchema::IFC4X3_RC1) {
#ifdef OIP_MODULE_EARLYBINDING_IFC4X3_RC1
			ParseExpressAndGeometryModel<emt::IFC4X3_RC1EntityTypes, OpenInfraPlatform::IFC4X3_RC1::IFC4X3_RC1Reader>(filename);
			return;
#else // OIP_MODULE_EARLYBINDING_IFC4X3_RC1
			IFCVersionNotCompiled("IFC4X3_RC1");
#endif //OIP_MODULE_EARLYBINDING_IFC4X3_RC1
		}

		IFCVersionNotCompiled(strSchema);
		return;
	}	

	else if (filetype == ".off")
	{

	}

#ifdef OIP_WITH_POINT_CLOUD_PROCESSING
	QString extension = QString(filetype.substr(1, filetype.size() - 1).data());
	if (buw::PointCloud::GetSupportedExtensions().contains(extension)) {
		auto pointCloud = buw::PointCloud::FromFile(filename.data(), true);
		addModel(pointCloud);
		latestChangeFlag_ = ChangeFlag::PointCloud;
		return;
	}
	else {
		BLUE_LOG(info) << "Supported PCD extensions: " << buw::PointCloud::GetSupportedExtensions().join(", ").toStdString() << ".";
	}
#endif

}

void OpenInfraPlatform::Core::DataManagement::Data::showError(QString errorMessage, QString errorTitle)
{
	BLUE_LOG(error) << "[" << errorTitle.toStdString() << "]: " << errorMessage.toStdString();
	// show error message only if GUI thread
	if( QThread::currentThread() == QCoreApplication::instance()->thread() )
		QMessageBox(QMessageBox::Icon::Critical, errorTitle, errorMessage, QMessageBox::StandardButton::Ok, nullptr).exec();
}

void OpenInfraPlatform::Core::DataManagement::Data::IFCVersionNotCompiled( const std::string& schema )
{
	QString errorTitle = "IFC version not compiled";
	QString errorMessage = "Please compile the OIP with support for " + QString(schema.c_str());
	showError(errorMessage, errorTitle);
}


void OpenInfraPlatform::Core::DataManagement::Data::jobFinished(int jobID, bool completed)
{
	if(currentJobID_ != jobID) {
		/*If jobID doesn't match, write errror to log file and display a dialog and return.*/
		BLUE_LOG(error) << "Wrong jobID. Expected " << QString::number(currentJobID_).toStdString() << " was " << QString::number(jobID).toStdString();
		showError("No matching jobID for this job. Error message was written to log file.", "ID Error!");
		return;
	}

	if(!completed) {
		/*If job was cancelled show message box to inform the user and return.*/
		showError("Import job cancelled. Error message was written to log file.", "Import Error!");
		return;
	}

	pushChange(getLatesChangeFlag());
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
	return "2020";
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



void OpenInfraPlatform::Core::DataManagement::Data::showViewCube(const bool enable)
{
	bShowViewCube_ = enable;

	pushChange(ChangeFlag::Preferences);
}

bool OpenInfraPlatform::Core::DataManagement::Data::isViewCubeEnabled()
{
	return bShowViewCube_;
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
// always returns the last loaded point cloud - needs to be done better (pjanck, 2020-09-28)
std::shared_ptr<oip::PointCloud> OpenInfraPlatform::Core::DataManagement::Data::getPointCloud()
{
	for (auto model = models_.rbegin(); model != models_.rend(); model++)
		if (std::dynamic_pointer_cast<oip::PointCloud>(*model))
			return std::dynamic_pointer_cast<oip::PointCloud>(*model);
	return nullptr;
}
#endif

// Model handling
void OpenInfraPlatform::Core::DataManagement::Data::addModel(buw::ReferenceCounted<oip::IModel> model)
{
	if( std::find(models_.begin(), models_.end(), model) == models_.end() )
		models_.push_back(model);
}

bool OpenInfraPlatform::Core::DataManagement::Data::hasModels()
{
	return !models_.empty();
}

std::shared_ptr<oip::IModel> OpenInfraPlatform::Core::DataManagement::Data::getLastModel()
{
	if (hasModels())
		return *models_.rbegin();
	return nullptr;
}

void OpenInfraPlatform::Core::DataManagement::Data::removeModel(buw::ReferenceCounted<oip::IModel> model)
{
	auto found = std::find(models_.begin(), models_.end(), model);
	if (found != models_.end())
		models_.remove(model);
}

void OpenInfraPlatform::Core::DataManagement::Data::removeAllModels()
{
	models_.clear();
}

oip::BBox OpenInfraPlatform::Core::DataManagement::Data::getExtents()
{
	oip::BBox bb;

	for (auto& model : models_)
		if( !model->isEmpty() )
			bb.update(model->getExtent());

	// if bounding box is still on default, overwrite with -1 to 1
	if (bb.isEmpty())
	{
		bb.fit(carve::geom::VECTOR(-1., -1., -1.), carve::geom::VECTOR(1., 1., 1.));
	}
	return bb;
}
