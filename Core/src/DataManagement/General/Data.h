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

#pragma once
#ifndef OpenInfraPlatform_DataManagement_Data_3ff08224_6d48_4517_a691_b3ed20f3ca74_h
#define OpenInfraPlatform_DataManagement_Data_3ff08224_6d48_4517_a691_b3ed20f3ca74_h

#include "..\EarlyBinding\src\EXPRESS\EXPRESSModel.h"
#include "..\Core\src\IfcGeometryConverter\ConverterBuw.h"

#include <BlueFramework/Application/DataManagement/DocumentManager.h>
#include <BlueFramework/ImageProcessing/color.h>
#include <BlueFramework/Core/Math/vector.h>
#include <boost/signals2.hpp>
#include <map>

#ifdef OIP_WITH_POINT_CLOUD_PROCESSING
#include <PointCloudProcessing.h>
#include <PointCloud.h>
#endif

namespace OpenInfraPlatform
{
	namespace Core 
	{
		namespace DataManagement 
		{
			class Data;
			typedef BlueFramework::Application::DataManagement::DocumentManager<Data> DocumentManager;

			enum class ChangeFlag : unsigned int {
				None = 0,
				AlignmentModel = 1 << 0,
				DigitalElevationModel = 1 << 1,
				IfcGeometry = 1 << 2,
				PointCloud = 1 << 3,
				Preferences = 1 << 4,
				TrafficModel = 1 << 5,
				SelectedAlignmentIndex = 1 << 6,
				GirderModel = 1 << 7,
				SlabFieldModel = 1 << 8,
				ProxyModel = 1 << 9
			};

			inline ChangeFlag operator|(ChangeFlag a, ChangeFlag b)
			{
				return static_cast<ChangeFlag>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
			}

			inline bool operator&(ChangeFlag a, ChangeFlag b)
			{
				return (static_cast<unsigned int>(a)& static_cast<unsigned int>(b)) != 0;
			}

			//! \class Data
			//! \brief This is the data layer/data model of the application. 
			//!
			//! All application data is contained in this class. The data is just manipulated in/through this class. 
			//! This is necessary because the data model is responsible for sending events/signals if the event listers/observers if the data has changed.
			//! The manipulator functions (functions that change the application data) should only be called from IActions.

			class Data : public BlueFramework::Application::DataManagement::Data {
			public:
				//! Constructor.
				Data();

				//! Virtual destructor.
				virtual ~Data();

				//! Clears the date model
				void clear(const bool notifyObservers);

				void clear();

				// alternative change methode
				void pushChange(ChangeFlag flag);
				ChangeFlag getLatesChangeFlag();

				//Retrieve the name of the last imported files
				QString recentFileName;

				// Retrieve the name of the application
				virtual const char* getApplicationName();

				// Retrieve the version string
				virtual const char* getApplicationVersionString();

				// Retrieve the name of the application
				virtual const char* getApplicationOpenFileFilter() override;

				virtual const char* getApplicationSaveFileFilter() override;

				virtual const char* getApplicationImportFileFilter() override;

				// Retrieve string for xml file - the standard implementation of save saves all entity objects in an xml file. This string is
				// stored as application string in the xml file. It can be reused when loading a file to check if a file is compatible with this
				// version 
				virtual const char* getApplicationNameXML();

				//---------------------------------------------------------------------------//
				// Loading/Saving and Import
				//---------------------------------------------------------------------------//

				//! Loads a file.
				/*
				\param[in] filename	Path to the file which should be opened.
				*/
				void open(const std::string & filename);

				void import(const std::string & filename);

				//---------------------------------------------------------------------------//
				// IFCx Model
				//---------------------------------------------------------------------------//

				buw::ReferenceCounted<OpenInfraPlatform::Core::IfcGeometryConverter::IfcGeometryModel> getIfcGeometryModel() const;

				//---------------------------------------------------------------------------//
				// Point Cloud
				//---------------------------------------------------------------------------//

#ifdef OIP_WITH_POINT_CLOUD_PROCESSING
				std::shared_ptr<buw::PointCloud> getPointCloud();
#endif

				//---------------------------------------------------------------------------//
				// Preferences
				//---------------------------------------------------------------------------//

				void setClearColor(const buw::Color3f& color);
				buw::Color3f getClearColor();

				void enableGradientClear(const bool enable);
				bool isGradientClearEnabled() const;

				bool isDrawGridEnabled() const;
				void enableDrawGrid(bool val);

				void enableShowReferenceCoordinateSystem(bool enable);
				bool isShowReferenceCoordinateSystemEnabled() const;

				void enableSkybox(const bool enable);
				bool isSkyboxEnabled() const;

				buw::Vector3d getOffset() const;

				void showViewCube(const bool enable);

				bool isViewCubeEnabled();

				void setShowFrameTimes(const bool enable);

				bool showFrameTimes() const;


				//---------------------------------------------------------------------------//
				// Add Georeference
				//---------------------------------------------------------------------------//

				double	getEastings();
				void	setEastings(double value);
				double	getNorthings();
				void	setNorthings(double value);
				double	getOrthogonalHeight();
				void	setOrthogonalHeight(double value);
				QString getEPSGcodeName();
				void	setEPSGcodeName(QString value);

			private:

				void jobFinished(int jobID, bool completed);
				void importJob(const std::string& filename);



			private:
				ChangeFlag		latestChangeFlag_;


				// Preferences
				buw::Color3f	clearColor_;
				bool			enableGradientClear_ = true;
				bool			bDrawGrid_ = false;
				bool			bShowReferenceCoordinateSystem = true;
				bool			bDrawSkybox_ = false;
				bool			bShowViewCube_ = true;
				bool			bShowFrameTime_ = false;

				/// Removed in Revision 483
				buw::ReferenceCounted<OpenInfraPlatform::Core::IfcGeometryConverter::IfcGeometryModel>	ifcGeometryModel_ = nullptr;
				buw::ReferenceCounted<oip::EXPRESSModel>						expressModel_ = nullptr;
				
				// temporary data for asynchronous operations
				bool merge_;
				buw::ReferenceCounted<OpenInfraPlatform::Core::IfcGeometryConverter::IfcGeometryModel>	tempIfcGeometryModel_;

				int																currentJobID_;

				// Add Georeference
				double m_Eastings = 0.0;
				double m_Northings = 0.0;
				double m_OrthogonalHeight = 0.0;
				QString m_Name = "EPSG:31467";

			}; // end class Data
		} // end namespace DataManagement
	} // end namespace Core
} // end namespace OpenInfraPlatform

#endif // end define OpenInfraPlatform_DataManagement_Data_3ff08224_6d48_4517_a691_b3ed20f3ca74_h
