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

#include "OpenInfraPlatform/DataManagement/IfcZipper.h"
#include <BlueFramework/Core/Diagnostics/log.h>
#include <QThread>
#include <QDate>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

//Fenstergröße für den Buffer für inflate/deflate
#define _32K 32768

//Makro zum überprüfen der zlib Methoden auf Fehler und Rückgabewerte
#define CHECK_ERR(err, msg) { \
    if (err != Z_OK) { \
        fprintf(stderr, "%s error: %d\n", msg, err); \
        exit(1); \
	    } \
}
//Konstruktor, benötigt Dateipfad und Modus(Inflate(true)/Deflate(false))
OpenInfraPlatform::DataManagement::IfcZipper::IfcZipper(QObject* parent,QString path,QString tempName, bool operation) {
	if ((tempName.contains(QString(".ifczip")) && operation == DEFL)
		|| (path.endsWith(QString(".ifc")) && operation == INFL)) {
		//TODO: Abort and write to Log File
		BLUE_LOG(error) << "File has false Data Format!";
	}
	this->tempName = tempName;
	filename = path;
	mode = operation;
	};

OpenInfraPlatform::DataManagement::IfcZipper::~IfcZipper() {

}

//Initialisiert den Local File Header und speichert die Werte im übergebenen Header Objekt
int OpenInfraPlatform::DataManagement::IfcZipper::createLocalFileHeader(localzipheader* locfilehdr, Byte* inBuffer, uLong inFileSize) {
	if (locfilehdr == NULL || inBuffer == NULL || inFileSize == NULL) {
		BLUE_LOG(error) << "Received null as a parameter";
		return -1;
	}
	else {
		locfilehdr->signature = strtoul("0x04034b50", NULL, 16);							//Signatur für PKZIP LocalFileHeader
		locfilehdr->version = 20;														//Zlib Version
		locfilehdr->gpBitFlag = 0;														//Ist das dritte bit gesetzt ist der crc32 sowie die file größen im Data Descriptor nach den komprimierten Daten zu finden
		locfilehdr->method = 8;															//Nur Z_DEFLATE unterstützt
		locfilehdr->lmodTime.f_time.hours = QTime::currentTime().hour();				//Zeitpunkt der letzten Bearbeitung
		locfilehdr->lmodTime.f_time.minutes = QTime::currentTime().minute();
		locfilehdr->lmodTime.f_time.seconds = QTime::currentTime().second() / 2;
		locfilehdr->lmodDate.f_date.day = QDate::currentDate().day();
		locfilehdr->lmodDate.f_date.month = QDate::currentDate().month();
		locfilehdr->lmodDate.f_date.year = QDate::currentDate().year() - 1980;
		//Die CRC32 Checksumme wird beim komprimieren der Daten generiert und gesetzt
		locfilehdr->compSize = zstream.total_out;
		locfilehdr->uncompSize = inFileSize;

		int pos = filename.toStdString().find_last_of('/', filename.size()) + 1;		//Länge des Dateinamens aus Pfad extrahieren
		int namesize = filename.size() - pos - 3;

		locfilehdr->fileNameLength = namesize;											//Länge des Dateinamens
		locfilehdr->xfieldLength = 0;												//Länge des Extra Felds, Standart 0
		return 0;
	}
}

//Schreibt den übergebenen File Header in die Datei
int OpenInfraPlatform::DataManagement::IfcZipper::writeLocalFileHeader(localzipheader* header) {
	if (!ofs.is_open()) {
		BLUE_LOG(error) << "Output filestream is closed";
		return -1;
	}

	if (header == NULL) {
		BLUE_LOG(error) << "header is null";
		return -2;
	}
	ofs.write((char*)header, 14);
	ofs.write((char*) &header->crc32, 16);
	int pos = filename.toStdString().find_last_of('/', filename.size()) + 1;
	ofs.write(filename.toStdString().substr(pos,header->fileNameLength).data(), header->fileNameLength);
	return 0;
}

//Initialisiert den CentralDirectoryRecord, das zentrale Verzeichnis das nach den komprimierten Daten steht.
int OpenInfraPlatform::DataManagement::IfcZipper::createCentralDirectoryRecord(localzipheader* header, CentralDirectoryRecord* cdr) {
	if (header == NULL) {
		BLUE_LOG(error) << "header is null";
		return -1;
	}

	if (cdr == NULL) {
		BLUE_LOG(error) << "cdr is null";
		return -2;
	}

	cdr->signature = strtoul("0x02014b50", NULL, 16);
	cdr->version = header->version;
	cdr->gpBitFlag = header->gpBitFlag;
	cdr->method = header->method;
	cdr->lmodTime = header->lmodTime;
	cdr->lmodDate = header->lmodDate;
	cdr->crc32 = header->crc32;
	cdr->compSize = header->compSize;
	cdr->uncompSize = header->uncompSize;
	cdr->fileNameLength = header->fileNameLength;
	cdr->xfieldLength = header->xfieldLength;
	cdr->versionNeeded[0] = 63;
	cdr->versionNeeded[1] = 0;
	cdr->externalAttributes = 129;
	cdr->fileCommLength = 0;
	cdr->diskStart = 0;
	cdr->internalAttributes = 0;
	cdr->offset = 0;
	return 0;
}
int OpenInfraPlatform::DataManagement::IfcZipper::writeCentralDirectory(CentralDirectoryRecord* cdr) {
	if (!ofs.is_open()) {
		BLUE_LOG(error) << "Output filestream is closed";
		return -1;
	}
	ofs.write((char*)cdr, 38);
	ofs.write((char*)&cdr->externalAttributes, 8);
	int pos = filename.toStdString().find_last_of('/', filename.size()) + 1;
	ofs.write(filename.toStdString().substr(pos, cdr->fileNameLength).data(), cdr->fileNameLength);
	return 0;
}

void OpenInfraPlatform::DataManagement::IfcZipper::parseLocalFileHeader(localzipheader* header) {
	if (header == NULL) {
		BLUE_LOG(error) << "header is null";
		return;
	}

	if (!ifs.is_open()) {
		BLUE_LOG(error) << "Input filestream is closed";
		return;
	}
	else {
		ifs.seekg(0, ifs.beg);
		ifs.read((char*)header, 14);
		ifs.read((char*)&header->crc32, 16);
		char* name = (char*)malloc(sizeof(char)* header->fileNameLength);
		ifs.read(name, header->fileNameLength);
		free(name);
		ifs.seekg(30+header->fileNameLength, ifs.beg);			
	}
}


void OpenInfraPlatform::DataManagement::IfcZipper::run()
{
	localzipheader* header = (localzipheader*)malloc(sizeof(localzipheader));
	CentralDirectoryRecord* cdr = (CentralDirectoryRecord*)malloc(sizeof(CentralDirectoryRecord));
	EndOfCentralDirectoryRecord* eocdr = (EndOfCentralDirectoryRecord*)malloc(sizeof(EndOfCentralDirectoryRecord));
	Byte *inBuffer = 0, *outBuffer = 0;	

	OpenInfraPlatform::DataManagement::IfcZipper::init(header);

	inBuffer = (Byte*)malloc(sizeof(Byte)* zstream.avail_in);
	outBuffer = (Byte*)malloc(sizeof(Byte)* zstream.avail_out);

	zstream.next_in = inBuffer;
	zstream.next_out = outBuffer;	

	if (mode == DEFL) {
		std::streamsize size = 32768;
		header->crc32 = crc32(0L, Z_NULL, 0);
		
		while (!ifs.eof()) {
			ifs.read((char*)inBuffer, size);
			size_t extracted = ifs.gcount();
			header->crc32 = crc32(header->crc32, inBuffer, extracted);
			zstream.avail_in = (unsigned int) extracted;
			zstream.next_in = inBuffer;
			if (ifs.eof()) {
				CHECK_ERR(deflate(&zstream, Z_FINISH), "deflate")
			}
			else {
				CHECK_ERR(deflate(&zstream, Z_NO_FLUSH), "deflate")
			}
		}

		//Header schreiben
		OpenInfraPlatform::DataManagement::IfcZipper::createLocalFileHeader(header, inBuffer, zstream.total_in);
		OpenInfraPlatform::DataManagement::IfcZipper::writeLocalFileHeader(header);

		//Komprimierte Daten schreiben
		ofs.write((char*)outBuffer, zstream.total_out);

		//Central Directory Record schreiben
		OpenInfraPlatform::DataManagement::IfcZipper::createCentralDirectoryRecord(header, cdr);
		OpenInfraPlatform::DataManagement::IfcZipper::writeCentralDirectory(cdr);

		//End of Central Directory Record schreiben
		OpenInfraPlatform::DataManagement::IfcZipper::createEndOfCentralDirectoryRecord(eocdr,cdr);
		OpenInfraPlatform::DataManagement::IfcZipper::writeEndOfCentralDirectoryRecord(eocdr);		
		CHECK_ERR(deflateEnd(&zstream),"deflateEnd");
	}
	if (mode == INFL) {
		CHECK_ERR(inflateInit2(&zstream, -MAX_WBITS), "inflateInit2");
		std::streamsize size = 32768;
		
		while (!ifs.eof()) {
			ifs.read((char*)inBuffer, size);
			size_t extracted = ifs.gcount();
			zstream.avail_in = (unsigned int)extracted;
			zstream.next_in = inBuffer;
			if (ifs.eof()) {
				CHECK_ERR(inflate(&zstream, Z_FINISH), "inflate")
			}
			else {
				CHECK_ERR(inflate(&zstream, Z_NO_FLUSH), "inflate")
			}
		}
		CHECK_ERR(inflateEnd(&zstream),"inflateEnd");
		ofs.write((char*)outBuffer, zstream.total_out);
	}

	//Aufräumen
	ifs.close();
	ofs.close();
	free(inBuffer);
	free(outBuffer);
	free(header);
	free(cdr);
	free(eocdr);
	if (mode == DEFL) {
		remove(tempName.toStdString().data());
	}	
}

void OpenInfraPlatform::DataManagement::IfcZipper::init(localzipheader* header) {

	uLong inFileSize = 0;
	uLong reqOutSize = 0;

	ifs.clear();
	ofs.clear();

	//zstream speicherverwaltung initialisieren
	zstream.opaque = Z_NULL;
	zstream.zalloc = Z_NULL;
	zstream.zfree = Z_NULL;	
	
	//Input und Output Streams öffnen
	if (mode == DEFL) {
		
		ifs.open(tempName.toStdString().data(), std::ifstream::binary);
		//filename.replace(QString(".ifc"), QString(".ifczip"));		
		ofs.open(filename.toStdString().data(), std::ofstream::binary);
		if (ifs.good() && ofs.good()) {
			//Input File größe bestimmen
			ifs.seekg(0, ifs.end);
			inFileSize = ifs.tellg();
			ifs.seekg(0, ifs.beg);
		}
		else {
			BLUE_LOG(error) << "Initializing the filestreams failed for deflate";
		}

		//zstream initialisieren und größe für benötigten output bestimmen
		CHECK_ERR(deflateInit2(&zstream,Z_BEST_COMPRESSION,Z_DEFLATED,-MAX_WBITS,8,Z_DEFAULT_STRATEGY),"deflateInit2");		
		reqOutSize = deflateBound(&zstream, inFileSize);
	}
	else if (mode == INFL) {
		
		ifs.open(filename.toStdString().data(), std::ifstream::binary);

		//Header von input file parsen
		OpenInfraPlatform::DataManagement::IfcZipper::parseLocalFileHeader(header);
		filename.replace(QString(".ifczip"), QString(".ifc"));
		
		ofs.open(tempName.toStdString().data(), std::ofstream::binary);		
		reqOutSize = header->uncompSize *2;
		if (!ofs.good() || !ifs.good()) {
			BLUE_LOG(error) << "Initializing the filestreams failed for inflate";
		}
	}
	zstream.avail_in = _32K;
	zstream.avail_out = reqOutSize;
}

int OpenInfraPlatform::DataManagement::IfcZipper::createEndOfCentralDirectoryRecord(EndOfCentralDirectoryRecord* eocdr, CentralDirectoryRecord* cdr){
	int state = 0;
	if (eocdr == NULL || cdr == NULL) {
		BLUE_LOG(error) << "EOCDR or DCR is null";
		state = -1;
	}
	eocdr->signature = strtoul("0x06054b50", NULL, 16);
	eocdr->commLength = 0;
	eocdr->diskNumber = 0;
	eocdr->cdrDisk = 0;
	eocdr->diskEntries = 1;
	eocdr->totalEntries = 1;
	eocdr->cdrSize = 46 + cdr->fileNameLength;
	eocdr->offset = 30 + cdr->fileNameLength + zstream.total_out;
	return state;
}

int OpenInfraPlatform::DataManagement::IfcZipper::writeEndOfCentralDirectoryRecord(EndOfCentralDirectoryRecord* eocdr) {
	int state = 0;
	if (eocdr == NULL) {
		BLUE_LOG(error) << "Received NULL as EOCDR";
		state = -3;
	}	
	if (ofs.bad() || ofs.fail()) {
		BLUE_LOG(error) << "Output Filestream has badbit or failbit set before writing EOCDR";
		state = -1;
	}
	ofs.write((char*)eocdr, 22);
	if (ofs.bad() || ofs.fail()) {
		BLUE_LOG(error) << "Output Filestream has badbit or failbit set after writing EOCDR";
		state = -2;
	}
	return state;
}

int OpenInfraPlatform::DataManagement::IfcZipper::removeFile() {
	int result = std::remove(tempName.toStdString().data());
	if (result != 0) {
		BLUE_LOG(error) << "Deleting temporary file failed";
	}
	Q_EMIT fileDeleted();
	return result;
}