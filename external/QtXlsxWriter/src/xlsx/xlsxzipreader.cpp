/****************************************************************************
** Copyright (c) 2013-2014 Debao Zhang <hello@debao.me>
** All right reserved.
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
** LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
** OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
** WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

#include "xlsxzipreader_p.h"
#ifdef QT_VERSION
	#if (QT_VERSION == 0x50800)
		#include "QtGui/5.8.0/QtGui/private/qzipreader_p.h"
	#elif (QT_VERSION == 0x50701)
		#include "QtGui/5.7.1/QtGui/private/qzipreader_p.h"
	#elif (QT_VERSION == 0x050700)
		#include "QtGui/5.7.0/QtGui/private/qzipreader_p.h"
	#elif (QT_VERSION == 0x050600)
		#include "QtGui/5.6.0/QtGui/private/qzipreader_p.h"
	#elif (QT_VERSION == 0x050501)
		#include "QtGui/5.5.1/QtGui/private/qzipreader_p.h"
	#elif (QT_VERSION == 0x050401)
		#include "QtGui/5.4.1/QtGui/private/qzipreader_p.h"
	#elif (QT_VERSION == 0x050701)
		#include "QtGui/5.7.1/QtGui/private/qzipreader_p.h"
	#elif (QT_VERSION == 0x050900)
		#include "QtGui/5.9.0/QtGui/private/qzipreader_p.h"
	#elif (QT_VERSION == 0x050901)
		#include "QtGui/5.9.1/QtGui/private/qzipreader_p.h"
	#endif
#endif

//#include <private/qzipreader_p.h>
#include <QVector>

namespace QXlsx {

ZipReader::ZipReader(const QString &filePath) :
    m_reader(new QZipReader(filePath))
{
    init();
}

ZipReader::ZipReader(QIODevice *device) :
    m_reader(new QZipReader(device))
{
    init();
}

ZipReader::~ZipReader()
{

}

void ZipReader::init()
{
    auto allFiles = m_reader->fileInfoList();
	
    Q_FOREACH (const QZipReader::FileInfo &fi, allFiles) {
        if (fi.isFile)
            m_filePaths.append(fi.filePath);
    }
}

bool ZipReader::exists() const
{
    return m_reader->exists();
}

QStringList ZipReader::filePaths() const
{
    return m_filePaths;
}

QByteArray ZipReader::fileData(const QString &fileName) const
{
    return m_reader->fileData(fileName);
}

} // namespace QXlsx
