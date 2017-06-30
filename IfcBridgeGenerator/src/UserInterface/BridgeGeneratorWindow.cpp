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

#include "BridgeGeneratorWindow.h"

#include "ui_BridgeGenerator.h"

#include "../BridgeFactory.h"

#include <QFileDialog>
#include <QString>

BlueIfcBridgeViewer::UserInterface::BridgeGeneratorWindow::BridgeGeneratorWindow( QWidget *parent /*= nullptr*/ )
{
	ui_ = new Ui::BridgeGeneratorWindow();
	ui_->setupUi(this);
}

void BlueIfcBridgeViewer::UserInterface::BridgeGeneratorWindow::on_pushButtonSaveAs_clicked()
{
	bridgeDescription bd;

	try
	{
		bd.length = ui_->lineEditLength->text().toDouble();
		bd.width = ui_->lineEditLength->text().toDouble();
	}
	catch (...)
	{
		std::cout << "err" << std::endl;
	}

	QString filename = QFileDialog::getSaveFileName( 
		this, 
		tr("Save Document"), 
		QDir::currentPath(), 
		tr("IfcBridge Step File (*.stp)") );
	if( !filename.isNull() )
	{
		shared_ptr<BridgeFactory> factory (new BridgeFactory());
		factory->createBridge(  filename.toStdString(), bd );
	}
}
