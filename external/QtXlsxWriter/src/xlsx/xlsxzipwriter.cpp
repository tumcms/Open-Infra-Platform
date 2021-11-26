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
#include "xlsxzipwriter_p.h"
#include <QDebug>

#ifdef QT_VERSION
	#if (QT_VERSION == 0x50800)
	    #include "QtGui/5.8.0/QtGui/private/qzipwriter_p.h"
	#elif (QT_VERSION == 0x50701)
		#include "QtGui/5.7.1/QtGui/private/qzipwriter_p.h"
	#elif (QT_VERSION == 0x050700)
		#include "QtGui/5.7.0/QtGui/private/qzipwriter_p.h"
	#elif (QT_VERSION == 0x050600)
		#include "QtGui/5.6.0/QtGui/private/qzipwriter_p.h"
	#elif (QT_VERSION == 0x050501)
		#include "QtGui/5.5.1/QtGui/private/qzipwriter_p.h"
	#elif (QT_VERSION == 0x050401)
		#include "QtGui/5.4.1/QtGui/private/qzipreader_p.h"
	#elif (QT_VERSION == 0x050701)
		#include "QtGui/5.7.1/QtGui/private/qzipwriter_p.h"
	#elif (QT_VERSION == 0x050900)
		#include "QtGui/5.9.0/QtGui/private/qzipwriter_p.h"
    #elif (QT_VERSION == 0x050901)
        #include "QtGui/5.9.1/QtGui/private/qzipwriter_p.h"
	#elif (QT_VERSION == 0x050902)
		#include "QtGui/5.9.2/QtGui/private/qzipwriter_p.h"
	#elif (QT_VERSION == 0x050903)
		#include "QtGui/5.9.3/QtGui/private/qzipwriter_p.h"
	#elif (QT_VERSION == QT_VERSION_CHECK(5,10,0))
		#include  "QtGui/5.10.0/QtGui/private/qzipwriter_p.h"
	#elif (QT_VERSION == QT_VERSION_CHECK(5,10,1))
		#include  "QtGui/5.10.1/QtGui/private/qzipwriter_p.h"
	#elif (QT_VERSION == QT_VERSION_CHECK(5,11,0))
		#include  "QtGui/5.11.0/QtGui/private/qzipwriter_p.h"
	#elif (QT_VERSION == QT_VERSION_CHECK(5,12,0))
		#include  "QtGui/5.12.0/QtGui/private/qzipwriter_p.h"
	#elif (QT_VERSION == QT_VERSION_CHECK(5,12,1))
		#include  "QtGui/5.12.1/QtGui/private/qzipwriter_p.h"
	#elif (QT_VERSION == QT_VERSION_CHECK(5,12,2))
		#include  "QtGui/5.12.2/QtGui/private/qzipwriter_p.h"
	#elif (QT_VERSION == QT_VERSION_CHECK(5,14,2))
		#include  "QtGui/5.14.2/QtGui/private/qzipwriter_p.h"
    #elif (QT_VERSION == QT_VERSION_CHECK(5,15,0))
        #include  "QtGui/5.15.0/QtGui/private/qzipwriter_p.h"
    #elif (QT_VERSION == QT_VERSION_CHECK(5,15,1))
        #include  "QtGui/5.15.1/QtGui/private/qzipwriter_p.h"
	#endif

#endif

//#include <private/qzipwriter_p.h>

namespace QXlsx {

ZipWriter::ZipWriter(const QString &filePath)
{
    m_writer = new QZipWriter(filePath, QIODevice::WriteOnly);
    m_writer->setCompressionPolicy(QZipWriter::AutoCompress);
}

ZipWriter::ZipWriter(QIODevice *device)
{
    m_writer = new QZipWriter(device);
    m_writer->setCompressionPolicy(QZipWriter::AutoCompress);
}

ZipWriter::~ZipWriter()
{
    delete m_writer;
}

bool ZipWriter::error() const
{
    return m_writer->status() != QZipWriter::NoError;
}

void ZipWriter::addFile(const QString &filePath, QIODevice *device)
{
    m_writer->addFile(filePath, device);
}

void ZipWriter::addFile(const QString &filePath, const QByteArray &data)
{
    m_writer->addFile(filePath, data);
}

void ZipWriter::close()
{
    m_writer->close();
}

} // namespace QXlsx
