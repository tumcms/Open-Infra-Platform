/*
	Copyright (c) 2021 Technical University of Munich
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
#ifndef OpenInfraPlatform_UserInterface_HttpDownloadDialog_38da791c_994f_450a_abc1_6676bdf555c4_h
#define OpenInfraPlatform_UserInterface_HttpDownloadDialog_38da791c_994f_450a_abc1_6676bdf555c4_h

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <QFile>
#include <QMessageBox>
#include <QTranslator>
#include <QEventLoop>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QTimer>

#include "DataManagement/General/Data.h"
#include "HttpTreeModel.h"

#include "ui_HttpDownloadDialog.h"

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		class HttpDownloadDialog : public QDialog, public Ui::HttpDownloadDialog
		{
			/**
			* @class HttpDownloadDialog
			* 
			* @brief A QDialog that allows the user to query OpenStreetMap data.
			*/
			Q_OBJECT;

		public:
			/**
			* @brief Default constructor
			*
			* @param parent QWidget parent
			*/
			HttpDownloadDialog(QWidget* parent = nullptr);

			/**
			* @brief Virtual destructor
			*/
			virtual ~HttpDownloadDialog();

			//! Getter for if HttpDownloadDialog was successful
			//bool isSuccess() { return successStatus_; }
			
		signals:
			/**
			* @brief Emit a signal with a success status, resulting in code execution to end
			*
			* @param successStatus Success status of the HttpDownloadDialog
			*/
			void transmitStatus(int successStatus);

			/**
			* @brief Emit a signal with a result value
			*
			* @param result Result value
			*/
			void resultAvailable(int result);

		private slots:
			/**
			* @brief Slot for when the quit button is clicked
			*/
			void on_quitBtn_clicked();

			/**
			* @brief Slot for when the user finishes inputting data
			*/
			void checkFieldsFilled();

			/**
			* @brief Slot for when the run button is clicked [contains wokrflow logic]
			*/
			void on_runBtn_clicked();

			/**
			* @brief Slot for when the HttpDownload has finished
			*/
			void httpDownloadFinished();

		private:
			/**
			* @brief Check for invalid characters in the user input fields
			*
			* @return True if there are invalid characters in the input fields, false otherwise
			*/
			bool invalidChar();

			/**
			* @brief Check if German characters have been inputted (Nominatim can't handle German chars)
			*
			* @param addresses List of addresses
			*/
			void checkGermanChar(QStringList& addresses);

			/**
			* @brief Converts user input to always capitalize the first letter (Overpass API is case-sensitive)
			*
			* @param uneditedString User input string
			*
			* @return Edited string with first letter capitalized
			*/
			QString toStartCase(QString uneditedString);

			/**
			* @brief Handle Nominatim and Overpass API
			*
			* @param apiDatabase The API database to use
			*/
			void processApi(const std::string apiDatabase);

			/**
			* @brief Check if API connection 'ok' (200) before querying
			*
			* @param apiDatabase The API database to use
			*
			* @return True if the API connection status is valid, false otherwise
			*/
			bool isApiStatusValid(const std::string apiDatabase);

			/**
			* @brief Set up the URL to query the API
			*
			* @param apiDatabase The API database to use
			*/
			void configureUrl(const std::string apiDatabase);

			/**
			* @brief Create separate queries for Nominatim and Overpass APIs
			*
			* @param apiDatabase The API database to use
			*
			* @return The query
			*/
			QString getQuery(const std::string apiDatabase);

			/**
			* @brief Create query to extract OpenStreetMap data in Overpass API
			*
			* @param radiusInput Radius value for filtering data
			* @return QString Query to extract OSM data in Overpass API
			*/
			QString queryExtractOsmData(const unsigned int radiusInput);

			/**
			* @brief Start HTTP request
			*
			* @param url URL to start HTTP request
			*/
			void startRequest(const QUrl& url);

			/**
			* @brief Setup HttpTreeModel
			* 
			* This is to build the derived QDialog child class with information on different regions of interest of similar name
			*
			* @param data QJsonArray data for HttpTreeModel
			*/
			void setupTreeModel(const QJsonArray& data);

			/**
			* @brief Join multiple strings together
			*
			* @param stringData QStringList to concatenate
			* @param separator QString separator for concatenating the strings
			* @return QString Concatenated QString
			*/
			QString concatenate(QStringList& stringData, QString seperator="") { return stringData.join(seperator); }

			/**
			* @brief Wait for request to go through before processing
			*
			* @param reply QNetworkReply for waiting
			*/
			void synchronousRequest(QNetworkReply* reply);

			/**
			* @brief Extract bounding box coordinates from Nominatim
			*
			* @param selectedObject Selected object
			*/
			void extractBBox(const QJsonObject& selectedObject);

			/**
			* @brief Scale the bounding box coordinates according to the radius filter input
			*
			* @param bbox Bounding box coordinates to scale
			* @param radius Radius value for scaling
			*/
			void scaleBBox(QJsonArray& bbox, const int& radius);

			/**
			*@brief Convert bounding box format from geodetic(WGS - 84) to ECEF(Cartesian Geocentric)
			*
			* @param nominatimBBox Bounding box coordinates in WGS - 84 format
			*/
			void convertBBoxFormat(const QJsonArray& nominatimBBox);

			// member variable
			QNetworkAccessManager*			manager_ = nullptr;
			QNetworkReply*					reply_ = nullptr;
			QUrl							endpoint_;
			QFile*							file_ = nullptr;
			QTranslator*					translator_ = nullptr;
			HttpTreeModel*					treeModel_ = nullptr;
			QString							overpassBBox_;
			int								selectedPosition_ = NULL;	// user selected option in HttpTreeModelDialog (default is 0)
			int								successStatus_ = NULL;		// 1 -> only if both Nominatim and Overpass API run
			bool							stopProcessing_ = NULL;		// flag
		}; // end class PreferencesDialog
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::UserInterface::HttpDownloadDialog;
}

#endif // end define OpenInfraPlatform_UserInterface_HttpDownloadDialog_38da791c_994f_450a_abc1_6676bdf555c4_h
