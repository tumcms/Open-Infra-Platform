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

#include "HelpBrowser.h"

#include <QVBoxLayout>

HelpBrowser::HelpBrowser(const QString &path, const QString &page,
	QWidget *parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
	setAttribute(Qt::WA_GroupLeader);

	setWindowIcon(QIcon(":/icons/icon.ico"));

	textBrowser = new QTextBrowser;

	homeButton = new QPushButton(tr("&Home"));
	backButton = new QPushButton(tr("&Back"));
	closeButton = new QPushButton(tr("Close"));
	closeButton->setShortcut(tr("Esc"));

	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(homeButton);
	buttonLayout->addWidget(backButton);
	buttonLayout->addStretch();
	buttonLayout->addWidget(closeButton);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(buttonLayout);
	mainLayout->addWidget(textBrowser);
	setLayout(mainLayout);

	connect(homeButton, SIGNAL(clicked()), textBrowser, SLOT(home()));
	connect(backButton, SIGNAL(clicked()),
		textBrowser, SLOT(backward()));
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(textBrowser, SIGNAL(sourceChanged(const QUrl &)),
		this, SLOT(updateWindowTitle()));

	textBrowser->setSearchPaths(QStringList() << path << ":/images");
	textBrowser->setSource(page);
}

void HelpBrowser::updateWindowTitle()
{
	setWindowTitle(tr("Help: %1").arg(textBrowser->documentTitle()));
}

void HelpBrowser::showPage(const QString &page)
{
	QString path = "Data/docs";
	HelpBrowser *browser = new HelpBrowser(path, page);
	browser->resize(500, 400);
	browser->show();
}
