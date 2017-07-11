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

#pragma once
#ifndef OpenInfraPlatform_DataManagement_Data_3ff08224_6d48_4517_a691_b3ed20f3ca74_h
#define OpenInfraPlatform_DataManagement_Data_3ff08224_6d48_4517_a691_b3ed20f3ca74_h

#include "OpenInfraPlatform/Data/terrainDescription.h"
//#include "OpenInfraPlatform/DataManagement/ViewCubeData.h"
#include "OpenInfraPlatform/Infrastructure/DigitalElevationModel/DigitalElevationModel.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/AlignmentModel.h"
#include "OpenInfraPlatform/Infrastructure/Girder/GirderModel.h"
#include "OpenInfraPlatform/Infrastructure/SlabField/SlabFieldModel.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/AlignmentModel.h"
#include "OpenInfraPlatform/Infrastructure/Export/ExportIfcAlignment1x0.h"
#include <BlueFramework/Application/DataManagement/DocumentManager.h>
#include "OpenInfraPlatform/Infrastructure/PointCloudProcessing/PointCloudProcessing.h"
#include <BlueFramework/ImageProcessing/color.h>
#include <BlueFramework/Core/Math/vector.h>
#include <boost/signals2.hpp>
#include <map>

#include "OpenInfraPlatform/IfcGeometryConverter/ConverterBuw.h"

#include "OpenInfraPlatform/Infrastructure/Import/Import.h"
#include "OpenInfraPlatform/Infrastructure/Export/Export.h"

namespace OpenInfraPlatform
{
	namespace DataManagement
	{
		class Data;
		typedef BlueFramework::Application::DataManagement::DocumentManager<Data> DocumentManager;

		enum class ChangeFlag : unsigned int
		{
			None = 0,
			AlignmentModel = 1 << 0,
			DigitalElevationModel = 1 << 1,
			IfcGeometry = 1 << 2,
			PointCloud = 1 << 3,
			Preferences = 1 << 4,
			TrafficModel = 1 << 5,
            SelectedAlignmentIndex = 1 << 6,
            GirderModel = 1 << 7,
            SlabFieldModel = 1 << 8
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
		class Data : public BlueFramework::Application::DataManagement::Data
		{
		public:		
			//! Constructor.
			Data();

			//! Virtual destructor.
			virtual ~Data();
				
			void save( const std::string & filename );

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
			void importIfcAlignment1_0(const std::string & filename);

			void importOSM(const std::string& filename, const std::vector<std::string>& filter, int mode);
			
			void importLAS(const std::string& filename);
			
			void exportIfcRoadTUMProposal(const std::string & filename);
			void exportIfcAlignment1x0(const buw::ifcAlignmentExportDescription& desc, const std::string & filename);
			void exportIfcAlignment1x1(const buw::ifcAlignmentExportDescription& desc, const std::string & filename);
			void exportSVGAdvanced(const std::string& filename);
			void exportSVG( const std::string& filename );
			void exportLandXML( const std::string& filename );
			void exportOkstra(const std::string& filename, const std::string& version);
			void exportOkstraTranslated(const std::string& filename);
			void export3DAlignmentAsTextfile(const std::string& filename);
			void createExcelReport(const std::string& filename, bool useDegree);
			
			//---------------------------------------------------------------------------//
			// Alignment
			//---------------------------------------------------------------------------//

			void addAlignment(buw::ReferenceCounted<buw::IAlignment3D> alignment);
			void deleteAlignment(buw::ReferenceCounted<buw::IAlignment3D> alignment);
			void computeSurfaceProfile();

			//---------------------------------------------------------------------------//
			// Digital Elevation Model
			//---------------------------------------------------------------------------//
			
			void addSurface(buw::ReferenceCounted<buw::Surface> surface);
			void deleteSurface(buw::ReferenceCounted<buw::Surface> surface);

			buw::Vector3d getOffset() const;

			void createRandomTerrain(const buw::terrainDescription& td);
			void createTerrainFromHeightMap(const std::string& filename);
			void createTerrainFromMesh(const std::string& filename);

			void importXYZ(const std::string& filename, const buw::Vector2d& start, const buw::Vector2d& end);

			buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::DigitalElevationModel> getDigitalElevationModel() const;

			buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::AlignmentModel> getAlignmentModel() const;

			//---------------------------------------------------------------------------//
			// Traffic Sign Model
			//---------------------------------------------------------------------------//

			buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::TrafficSignModel> getTrafficSignModel() const {
				return trafficSignModel_;
			}

			//---------------------------------------------------------------------------//
			// Girder Model
			//---------------------------------------------------------------------------//

			buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::GirderModel> getGirderModel() const;

			//---------------------------------------------------------------------------//
			// Slab Field Model
			//---------------------------------------------------------------------------//

			buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::SlabFieldModel> getSlabFieldModel() const;

			//---------------------------------------------------------------------------//
			// IFCx Model
			//---------------------------------------------------------------------------//

			buw::ReferenceCounted<IfcGeometryConverter::IfcGeometryModel> getIfcGeometryModel() const;

			//---------------------------------------------------------------------------//
			// Point Cloud
			//---------------------------------------------------------------------------//
			const int getPointCloudPointCount() const;

			const std::vector<buw::LaserPoint>& getPointCloud() const;


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

			void showViewCube(const bool enable);

			bool isViewCubeEnabled();

			void setAlignmentLineWidth(const double width);
			float getAlignmentLineWidth() const;

			void setShowFrameTimes(const bool enable);

			bool showFrameTimes() const;

			void setSelectedAlignment(int selectedIndex);
			int getSelectedAlignment();

            //---------------------------------------------------------------------------//
            // ViewCubeData
            //---------------------------------------------------------------------------//

            //ViewCubeData viewCubeData_;
            //ViewCubeData& getViewCubeData() { return viewCubeData_; }

		private:
			void createDigitalElevationModel( const buw::Vector3d& offsetViewArea );
			buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::AlignmentModel> readBICFile(const std::string & filename);

			void jobFinished(int jobID, bool completed);


			void importJob(const std::string& filename);
			void startImportJobIfcAlignment1_0(const std::string& filename);
			void importOSMJob(const std::string& filename, const std::vector<std::string>& filter, int mode);
			void exportIfcRoadTUMProposalJob(const std::string & filename);
			void exportIfcAlignmentJob(const buw::ifcAlignmentExportDescription& desc, const std::string & filename);
			void exportIfcAlignment1x1Job(const buw::ifcAlignmentExportDescription& desc, const std::string & filename);
			void exportSVGAdvancedJob(const std::string& filename);
			void exportSVGJob(const std::string& filename);
			void exportLandXMLJob(const std::string& filename);
			void exportOkstraJob(const std::string& filename, const std::string& version);
			void exportOkstraJobTranslated(const std::string& filename);
			void export3DAlignmentAsTextfileJob(const std::string& filename);
			void createExcelReportJob(const std::string& filename, bool useDegree);


			void importLASJob(const std::string& filename);

			void importXYZJob(const std::string& filename, const buw::Vector2d& start, const buw::Vector2d& end);
			void createRandomTerrainJob(const buw::terrainDescription& td);
			void createTerrainFromHeightMapJob(const std::string& filename);
			void createTerrainFromMeshJob(const std::string& filename);
			
		private:
			ChangeFlag		latestChangeFlag_;

			// Preferences
			buw::Color3f	clearColor_;
			bool			enableGradientClear_                = true;
			bool			bDrawGrid_							= false;
			bool			bShowReferenceCoordinateSystem		= true;
			bool			bDrawSkybox_						= false;
			bool			bShowViewCube_						= true;
			bool			bShowFrameTime_						= false;
			float			alignmentLineWidth_;
			int				selectedAlignmentIndex_				= 0;
			
			buw::ReferenceCounted<buw::TrafficSignModel>					trafficSignModel_;
			buw::ReferenceCounted<buw::DigitalElevationModel> 				digitalElevationModel_;
			buw::ReferenceCounted<buw::AlignmentModel>						alignmentModel_;
			buw::ReferenceCounted<buw::GirderModel>							girderModel_;
			buw::ReferenceCounted<buw::SlabFieldModel>						slabFieldModel_;
			buw::ReferenceCounted<IfcGeometryConverter::IfcGeometryModel>	ifcGeometryModel_;
			buw::PointCloud*												pointCloud_;



			// temporary data for asynchronous operations
			bool merge_;
			buw::Import*													importer_;
			buw::ReferenceCounted<IfcGeometryConverter::IfcGeometryModel>	tempIfcGeometryModel_;
			buw::PointCloud*												tempPointCloud_;

			int																currentJobID_;

			//! Determines the notification behavior of this class.
			//BlueFramework::Application::DataManagement::NotificationState *m_pNotifiactionState;
		}; // end class Data
	} // end namespace DataManagement
} // end namespace OpenInfraPlatform

#endif // end define OpenInfraPlatform_DataManagement_Data_3ff08224_6d48_4517_a691_b3ed20f3ca74_h
