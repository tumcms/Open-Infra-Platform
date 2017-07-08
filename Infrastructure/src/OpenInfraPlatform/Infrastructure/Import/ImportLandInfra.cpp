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

#include "ImportLandInfra.h"

#include <BlueFramework/Core/Diagnostics/log.h>

#include <QtXml>
#include <QXmlSchema.h>
#include <QUrl>
#include <QXmlSchemaValidator.h>
#include <QString>


namespace OpenInfraPlatform {
	namespace Infrastructure {

		const bool ImportLandInfra::validateHeader(const QString &header)
		{
			return false;
		}
		
		ImportLandInfra::ImportLandInfra(const std::string& filename) : Import(filename) {

			QFile file(filename.c_str());
			if (!file.open(QIODevice::ReadOnly))
				throw buw::Exception("Unable to open the file.");			

			if (QFile("schema/LandInfra_Part3Alignment0321.xsd").exists()) {
				QFile landInfraSchema("schema/LandInfra_Part3Alignment0321.xsd");
				if (!landInfraSchema.open(QIODevice::ReadOnly))
						throw buw::Exception("Unable to open the file.");

				QXmlSchema schema;
				schema.load(landInfraSchema.readAll(), QUrl());

				QXmlSchemaValidator validator(schema);

				if (!(validator.validate(file.readAll())))
					throw buw::Exception("Schema validation failed.");
				else
					file.seek(0);
			}

			QXmlInputSource source(&file);
			QDomDocument document;
			
			document.setContent(&source, false);

			BLUE_LOG(trace) << "Importing " << filename;

			QDomNode xml = document.firstChild();
			if (!(xml.nodeName() == "xml")) {
				BLUE_LOG(error) << xml.nodeName();
				throw buw::Exception("Invalid XML document.");
			}

			QStringList xmlValues = xml.nodeValue().split(' ');

			if (!(xmlValues[0].split('=')[0] == "version")) {
				BLUE_LOG(error) << xmlValues[0];
				throw buw::Exception("Invalid XML document: No version specified.");
			}
			else
				BLUE_LOG(trace) << "XML Version: " << xmlValues[0].split('=')[1];

			if (!(xmlValues[1] == "encoding=\'UTF-8\'")) {
				BLUE_LOG(error) << xmlValues[1];
				throw buw::Exception("Invalid XML document: No UTF-8 encoding.");
			}
			else
				BLUE_LOG(trace) << "XML Encoding: " << xmlValues[1].split('=')[1];

			QDomNode dataset = xml.nextSibling();
			while (!(dataset.nodeName() == "LandInfraDataset")) {
				if ((dataset = xml.nextSibling()).isNull())
					throw buw::Exception("Invalid XML document: No LandInfraDataset found.");
			}
			
			QString header = dataset.nodeValue();
			if (!validateHeader(header)) {
				BLUE_LOG(error) << header;
				throw new buw::Exception("Invalid LandInfraDataset header.");
			}
			
			if (!(dataset.hasChildNodes()))
				throw buw::Exception("Dataset does not contain any children.");
			else
				BLUE_LOG(trace) << "XML Encoding: " << xmlValues[1].split('=')[1];

			QDomNodeList children = dataset.childNodes();
			
			//TODO: Handle all children.
		}

	}
}