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

#include "HttpDownloadDialog.h"
#include <BlueFramework/Application/UserInterface/MainWindow.h>
#include <cmath>

// #TODO: change 'tr' in QString where translation our 'sourceText' isn't needed

OpenInfraPlatform::UserInterface::HttpDownloadDialog::HttpDownloadDialog(QWidget* parent /*=nullptr*/) :
    QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
    setupUi(this);

    // initialize success to false (0)
    successStatus_ = 0;
    stopProcessing_ = false;

    // disable run button unless all mandatory fields are filled
    this->runBtn->setEnabled(false);

    // initialize tree model instance
    treeModel_ = new HttpTreeModel(this);

    // initialize manager for request & reply over HTTP
    manager_ = new QNetworkAccessManager(this);

    // text input connections
    // enable run button only when all mandatory fields have been entered
    connect(this->countryCodeEdit, &QLineEdit::textChanged, this, &HttpDownloadDialog::checkFieldsFilled);
    connect(this->cityEdit, &QLineEdit::textChanged, this, &HttpDownloadDialog::checkFieldsFilled);
    connect(this->areaEdit, &QLineEdit::textChanged, this, &HttpDownloadDialog::checkFieldsFilled);

    //// HttpTreeModelDialog connections
    //// on quit
    //connect(treeModel_->quitBtn, &QPushButton::clicked, this, &HttpDownloadDialog::quitTreeModel);
    //// on select button clicked
    //connect(treeModel_->selectBtn, &QPushButton::clicked, this, &HttpDownloadDialog::treeModelSelect);

    // HttpDownloadDialog connections
    // returns the dialog code success or fail using the 'done' slot
    // https://stackoverflow.com/questions/37094751/qdialog-return-value-accepted-or-rejected-only
    //connect(this, SIGNAL(transmitStatus(int)), this, SLOT(done(int)));
    connect(this, &HttpDownloadDialog::transmitStatus, this, &HttpDownloadDialog::done);
}

OpenInfraPlatform::UserInterface::HttpDownloadDialog::~HttpDownloadDialog()
{
    if (file_) {
        file_->remove();
        delete file_;
        file_ = nullptr;
    }
    this->reply_ = nullptr;
    this->endpoint_.clear();
    this->translator_ = nullptr;
    this->selectedPosition_ = NULL;
    this->successStatus_ = NULL;
}


void OpenInfraPlatform::UserInterface::HttpDownloadDialog::on_quitBtn_clicked()
{
    close();
}


void OpenInfraPlatform::UserInterface::HttpDownloadDialog::checkFieldsFilled()
{
    bool filled = !(this->countryCodeEdit->text().isEmpty()) && !(this->cityEdit->text().isEmpty()) && !(this->areaEdit->text().isEmpty());
    this->runBtn->setEnabled(filled);
}


bool OpenInfraPlatform::UserInterface::HttpDownloadDialog::invalidChar()
{
    bool invalid = false;
    // get all user inputs into a list
    QStringList userInputs = (QStringList() << this->countryCodeEdit->text() << this->cityEdit->text() << this->areaEdit->text());
    
    // allowed characters
    QRegularExpression validRe("[!A-Za-z0-9,]+");

    // if characters apart from the allowed -> invalid
    if (userInputs.indexOf(validRe))
        invalid = true;

    return invalid;
}


void OpenInfraPlatform::UserInterface::HttpDownloadDialog::checkGermanChar(QStringList& addresses)
{
    QRegularExpression germanChar("[äöüß]+");
    // if german char exists
    for (int i = 0; i < addresses.length(); i++)
    {
        if (addresses[i].indexOf(germanChar))
            addresses[i].replace(QString::fromLatin1("ä"), QString("ae")).replace(QString::fromLatin1("ö"), QString("oe"))
            .replace(QString::fromLatin1("ü"), QString("ue")).replace(QString::fromLatin1("ß"), QString("ss"));
    }
}


QString OpenInfraPlatform::UserInterface::HttpDownloadDialog::toStartCase(QString uneditedString)
{
    QStringList parts = uneditedString.split(' ', QString::SkipEmptyParts);
    for (unsigned int i = 0; i < parts.size(); i++) {
        parts[i] = parts[i].toLower();
        parts[i].replace(0, 1, parts[i][0].toUpper());
    }
    return concatenate(parts, " ");
}

// #TODO: refactor for case where Nominatim is down and we still proceed
bool OpenInfraPlatform::UserInterface::HttpDownloadDialog::isApiStatusValid(const std::string apiDatabase)
{
    if (apiDatabase == "nominatim")
        endpoint_.setUrl(QString("https://nominatim.openstreetmap.org/status.php"));
    else if (apiDatabase == "overpass")
        endpoint_.setUrl(QString("http://overpass-api.de/api/status"));
    
    // create request
    QNetworkRequest request(endpoint_);
    // get reply
    reply_ = manager_->get(request);
    // wait until response is recieved
    synchronousRequest(reply_);

    // handle error
    if (reply_->error()) {
        QMessageBox::critical(this, tr("%1 API HTTP Error: %2").arg(QString::fromStdString(apiDatabase)).arg(reply_->error()), 
            tr("%1").arg(reply_->errorString()));
        return false;
    }

    // reset member variables
    endpoint_.clear();
    reply_->deleteLater();

    return true;
}


QString OpenInfraPlatform::UserInterface::HttpDownloadDialog::getQuery(const std::string apiDatabase)
{
    QStringList stringData;
    // https://nominatim.org/release-docs/develop/api/Search/
    if (apiDatabase == "nominatim")
    {
        // replace german characters
        QStringList addresses = QStringList() << this->areaEdit->text() << this->cityEdit->text();
        checkGermanChar(addresses);

        QString lookup = tr("q=%1, %2").arg(addresses.at(0)).arg(addresses.at(1));
        // nominatim requires '+' character instead of space
        lookup.replace(' ', '+');

        QString addParams = tr("&format=jsonv2&countrycodes=%1&addressdetails=1&limit=5&polygon_geojson=1").arg(this->countryCodeEdit->text().toLower());
        stringData << lookup << addParams;
    }
    else if (apiDatabase == "overpass")
    {
        QString formatting = tr("[out:xml][timeout:180][bbox:%1];").arg(overpassBBox_);
        QString outputData = tr("out geom(%1);").arg(overpassBBox_);
        QString extractOsmData = queryExtractOsmData(this->radiusSpinBox->value());
        stringData << formatting << extractOsmData << outputData;
    }

    return concatenate(stringData);
}


QString OpenInfraPlatform::UserInterface::HttpDownloadDialog::queryExtractOsmData(const unsigned int radiusInput)
{
    //// radius provided
    //if (radiusInput) {
    //    QString osmQueryAll = tr(
    //        "( ( ( way['building'][!'building:part']; way['amenity']; way['leisure']; way['landuse']; way['natural'];"                          // included ways
    //        "way['highway'~'^(primary|secondary|tertiary|residential)$'][!'tunnel']; );"
    //        "- ( way['amenity'='toilets']; way['natural'='tree_row']; ); );"                                                                    // excluded ways
    //        "relation['type'~'^(multipolygon|building|site)$'][!'building:part'][!'landuse']; );"                                               // relation
    //    );
    //    return osmQueryAll;
    //}
    //else {
    //    // region name is case-sensitive; convert to CamelCase
    //    QString regionOfInterest = tr("area['name'='%1']->.region;").arg(toStartCase(this->areaEdit->text()));
    //    QString osmQueryInRegion = tr(
    //        "( ( ( way(area.region)['building'][!'building:part']; way(area.region)['amenity']; way(area.region)['leisure']; way(area.region)['landuse']; way(area.region)['natural'];"
    //        " way(area.region)['highway'~'^(primary|secondary|tertiary|residential)$'][!'tunnel']; );"
    //        "- ( way(area.region)['amenity'='toilets']; way(area.region)['natural'='tree_row']; ); );"
    //        "relation(area.region)['type'~'^(multipolygon|building|site)$'][!'building:part'][!'landuse']; );"                                                  
    //    );

    //    return concatenate(QStringList() << regionOfInterest << osmQueryInRegion);
    //}

    QString osmQueryAll = tr(
        "( ( ( way['building'][!'building:part']; way['amenity']; way['leisure']; way['landuse']; way['natural'];"                          // included ways
        "way['highway'~'^(primary|secondary|tertiary|residential)$'][!'tunnel']; );"
        "- ( way['amenity'='toilets']; way['natural'='tree_row']; ); );"                                                                    // excluded ways
        "relation['type'~'^(multipolygon|building|site)$'][!'building:part'][!'landuse']; );"                                               // relation
    );
    return osmQueryAll;
}


void OpenInfraPlatform::UserInterface::HttpDownloadDialog::configureUrl(const std::string apiDatabase)
{
    QString queryValue;
    // distinguish endpoints
    if (apiDatabase == "nominatim")
    {
        endpoint_.setUrl(QString("https://nominatim.openstreetmap.org/search"));
        queryValue = getQuery("nominatim");
        // https://doc.qt.io/qt-6/qurl.html#ParsingMode-enum
        endpoint_.setQuery(queryValue, QUrl::DecodedMode);
    }
    else if (apiDatabase == "overpass")
    {
        endpoint_.setUrl(QString("https://overpass-api.de/api/interpreter"));
        QString key = "data";
        QString queryValue = getQuery("overpass");
        QUrlQuery query;
        query.addQueryItem(key, queryValue);
        endpoint_.setQuery(query);
    }
}


void OpenInfraPlatform::UserInterface::HttpDownloadDialog::setupTreeModel(const QJsonArray& data)
{
    // initiate tree model
    treeModel_->buildTreeModel(data);

    // wait till dialog returns
    treeModel_->setModal(true);
    int result = treeModel_->exec();
    // accepted
    if (result == QDialog::Accepted)
        selectedPosition_ = treeModel_->getSelectedPosition();

    // deallocate
    treeModel_->deleteLater();
    treeModel_ = nullptr;
}


void OpenInfraPlatform::UserInterface::HttpDownloadDialog::extractBBox(const QJsonObject& selectedObject)
{
    // get the bounding box array
    QJsonArray bboxArr = selectedObject.value("boundingbox").toArray();
    // check if user entered a radius
    if (this->radiusSpinBox->value() != 0)
        scaleBBox(bboxArr, this->radiusSpinBox->value());

    // convert bbox to Overpass-API format
    convertBBoxFormat(bboxArr);
}


void OpenInfraPlatform::UserInterface::HttpDownloadDialog::scaleBBox(QJsonArray& bbox, const int& radius)
{
    // scale N & E +ve, while S & W -ve
    // radius is in metres while bbox is in Geodetic CRS (WGS-84)
    // earth radius = 6371000m (approx.)

    // constant
    const double scaleFactor = (radius / 6371000.0), degToRad = (180 / M_PI);

    // get data in double format for ease of calculation later
    const double southLat = bbox.at(0).toString().toDouble();
    const double westLon = bbox.at(2).toString().toDouble();
    const double northLat = bbox.at(1).toString().toDouble();
    const double eastLon = bbox.at(3).toString().toDouble();

    // perform the calculations
    double newSouthLat = southLat - (scaleFactor * degToRad);
    double newWestLon = westLon - (scaleFactor * degToRad) / cos(southLat * (M_PI / 180));
    double newNorthLat = northLat + (scaleFactor * degToRad);
    double newEastLon = eastLon + (scaleFactor * degToRad) / cos(northLat * (M_PI / 180));
    
    // replace bbox content with modified values
    bbox.replace(0, QJsonValue(QString::number(newSouthLat, 'g', 7)));
    bbox.replace(2, QJsonValue(QString::number(newWestLon, 'g', 7)));
    bbox.replace(1, QJsonValue(QString::number(newNorthLat, 'g', 7)));
    bbox.replace(3, QJsonValue(QString::number(newEastLon, 'g', 7)));
}


void OpenInfraPlatform::UserInterface::HttpDownloadDialog::convertBBoxFormat(const QJsonArray& nominatimBBox)
{
    // Nominatim bbox format: South Lat.[0], North Lat.[1], West Long.[2], East Long.[3]
    // Overpass API format: South Lat.[0], West Long.[1], North Lat.[2], East Long.[3]

    overpassBBox_ = QString("%1, %2, %3, %4").arg(nominatimBBox.at(0).toString()).arg(nominatimBBox.at(2).toString())
        .arg(nominatimBBox.at(1).toString()).arg(nominatimBBox.at(3).toString());
}


void OpenInfraPlatform::UserInterface::HttpDownloadDialog::on_runBtn_clicked()
{
    this->runBtn->setEnabled(false);

    // check if invalid (special) characters entered
    if (invalidChar()) {
        QMessageBox::critical(this, tr("Invalid Syntax"), tr("Please avoid special characters."));
        // fail
        emit transmitStatus(successStatus_);
        return;
    }

    // reset any previous state
    stopProcessing_ = false;
    if (reply_) {
        reply_->deleteLater();
    }
    if (file_) {
        file_->remove();
        delete file_;
        file_ = nullptr;
    }

    // handle Nominatim
    processApi("nominatim");
    // handle error
    if (stopProcessing_) {
        emit transmitStatus(successStatus_);
        return;
    }

    // handle overpass
    processApi("overpass");
    emit transmitStatus(successStatus_);
}


void OpenInfraPlatform::UserInterface::HttpDownloadDialog::processApi(const std::string apiDatabase)
{
    if (apiDatabase == "overpass") {
        // create file to store OSM data
        QString filename = "C:/Users/Moiez/Desktop/MasterThesis/OIP/Open-Infra-Platform/UserInterface/osm.xml";
        file_ = new QFile(filename);
    }

    // check if API connection is valid
    if (!isApiStatusValid(apiDatabase)) {
        stopProcessing_ = true;
        return;
    }

    // configure URL with query
    configureUrl(apiDatabase);

    // get the reply
    startRequest(endpoint_);
}


void OpenInfraPlatform::UserInterface::HttpDownloadDialog::startRequest(const QUrl& url)
{
    // create request
    QNetworkRequest request(url);

    // get reply
    reply_ = manager_->get(request);

    // reset url member
    endpoint_.clear();

    // wait until response is recieved
    synchronousRequest(reply_);

    // proceed to the slot 'httpDownloadFinished' for further processing and error handling
    httpDownloadFinished();
}


void OpenInfraPlatform::UserInterface::HttpDownloadDialog::synchronousRequest(QNetworkReply* reply)
{
    // create timer to timeout in case of network connectivity issue
    QTimer getTimer;
    // create an eventloop for synchronous response
    QEventLoop loop;
    // connect timeout signal to quit() slot of event loop
    connect(&getTimer, &QTimer::timeout, &loop, &QEventLoop::quit);
    // connect reply_ to quit() slot of event loop
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    // 60,000ms (60s) wait for get response
    getTimer.start(60000);
    // execute and wait for response
    loop.exec();
}


void OpenInfraPlatform::UserInterface::HttpDownloadDialog::httpDownloadFinished()
{
    qint64 httpStatus = reply_->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QString contentType = reply_->header(QNetworkRequest::ContentTypeHeader).toString();

    // error handling
    if (httpStatus == 0 || reply_->error()) {

        // NULL (timeout)
        if (httpStatus == 0)
            QMessageBox::warning(this, tr("Network Connectivity Issue"),
                tr("Network connection failed. Please try again in a few moments."));

        // error while fetching data
        else if (reply_ && reply_->error())
            QMessageBox::information(this, tr("HTTP Download"),
                tr("Download failed: %1").arg(reply_->errorString()));

        // remove file if exists
        if (file_->exists())
            file_->remove();

        // delete reply_
        reply_->deleteLater();

        // fail
        stopProcessing_ = true;
        return;
    }

    // downloaded data
    QByteArray buffer = reply_->readAll();

    // Nominatim
    if (reply_->url().host() == QString("nominatim.openstreetmap.org"))
    {
        QJsonParseError jsonError;

        // json parser here
        QJsonDocument jsonDoc = QJsonDocument::fromJson(buffer, &jsonError);
        if (jsonError.error == QJsonParseError::NoError) {
            
            qsizetype dataSize = jsonDoc.array().size();

            // data recieved with no error
            if (dataSize) {
                QJsonArray data = jsonDoc.array();

                // only show model tree if multiple data options retrieved
                if (dataSize > 1) {
                    QMessageBox::information(this, tr("Data Loaded"),
                        tr("Multiple data have been retrieved.\n Please select one of the following."));

                    // setup HttpTreeModel dialog
                    setupTreeModel(data);
                }
                // get bbox
                extractBBox(data.at(selectedPosition_).toObject());
            }

            // no data recieved with no error
            else {

                QMessageBox::information(this, QString("No data loaded"),
                    QString("Please make sure there are no typos or wrong names provided and try again."));

                reply_->deleteLater();

                // fail
                stopProcessing_ = true;
                return;
            }

            reply_->deleteLater();
        }

        // handle error
        else {
            QMessageBox::critical(this, tr("Json Parsing"), tr("%1.").arg(reply_->error()));

            reply_->deleteLater();
            
            // fail
            stopProcessing_ = true;
            return;
        } 
    }

    // Overpass API
    else if (reply_->url().host() == QString("overpass-api.de")) {
        
        // handle file writing error
        if (!file_->open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("HTTP Download"),
                tr("Error saving file: %1").arg(file_->errorString()));

            // fail
            stopProcessing_ = true;
            return;
        }
        else if (buffer.isEmpty()) {
            
            // handle empty buffer; i.e. overpass-api returned empty data
            QMessageBox::warning(this, tr("HTTP Download"),
                tr("Empty data retrieved from server. The file was not written."));

            // remove file if exists
            if (file_->exists())
                file_->remove();

            // delete reply
            reply_->deleteLater();

            // fail
            stopProcessing_ = true;
            return;
        }

        // write data to file
        file_->write(buffer);
        file_->flush();
        file_->close();

        // success
        reply_->deleteLater();
        successStatus_ = 1;
        delete file_;
        file_ = nullptr;
    }
}

