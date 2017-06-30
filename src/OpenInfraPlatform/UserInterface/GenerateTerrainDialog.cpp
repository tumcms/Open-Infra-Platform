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

#include "GenerateTerrainDialog.h"

#include "OpenInfraPlatform/DataManagement/Data.h"
#include "OpenInfraPlatform/DataManagement/Command/CreateRandomTerrain.h"

OpenInfraPlatform::UserInterface::GenerateTerrainDialog::GenerateTerrainDialog(QWidget *parent /*= nullptr*/) :
	ui_(new Ui::GenerateTerrain),
	QDialog(parent, Qt::WindowTitleHint|Qt::WindowCloseButtonHint)
{
	 ui_->setupUi(this);

	 // Adding data to the dropdown menus
	/* ui_->comboBoxOctaves->addItem("1");
	 ui_->comboBoxOctaves->addItem("2");
	 ui_->comboBoxOctaves->addItem("3");
	 ui_->comboBoxOctaves->addItem("4");
	 ui_->comboBoxOctaves->addItem("5");
	 ui_->comboBoxOctaves->addItem("6");
	 ui_->comboBoxOctaves->addItem("7");
	 ui_->comboBoxOctaves->addItem("8");

	 ui_->comboBoxFrequency->addItem("1");
	 ui_->comboBoxFrequency->addItem("2");
	 ui_->comboBoxFrequency->addItem("3");
	 ui_->comboBoxFrequency->addItem("4");
	 ui_->comboBoxFrequency->addItem("5");
	 ui_->comboBoxFrequency->addItem("6");
	 ui_->comboBoxFrequency->addItem("7");
	 ui_->comboBoxFrequency->addItem("8");

	 ui_->comboBoxSize->addItem("64");
	 ui_->comboBoxSize->addItem("128");
	 ui_->comboBoxSize->addItem("256");
	 ui_->comboBoxSize->addItem("512");
	 ui_->comboBoxSize->addItem("1024");

	 ui_->comboBoxTileSize->addItem("1");
	 ui_->comboBoxTileSize->addItem("2");
	 ui_->comboBoxTileSize->addItem("3");
	 ui_->comboBoxTileSize->addItem("4");
	 ui_->comboBoxTileSize->addItem("5");*/
}

OpenInfraPlatform::UserInterface::GenerateTerrainDialog::~GenerateTerrainDialog()
{

}

void OpenInfraPlatform::UserInterface::GenerateTerrainDialog::changeEvent(QEvent* evt) 
{
	if (evt->type() == QEvent::LanguageChange)
	{
		ui_->retranslateUi(this);
	}
	else
	{
		QWidget::changeEvent(evt);
	}
}

void OpenInfraPlatform::UserInterface::GenerateTerrainDialog::on_pushButtonGenerate_clicked()
{
	/*int octaves = ui_->comboBoxOctaves->currentText().toInt();
	int frequency = ui_->comboBoxFrequency->currentText().toInt();
	int size = ui_->comboBoxSize->currentText().toInt();
	int tileSize = ui_->comboBoxTileSize->currentText().toInt();*/

	buw::terrainDescription td;
	td.lod = ui_->spinBoxLod->value();
	td.roughness = ui_->doubleSpinBoxRoughness->value();
	td.mean = ui_->doubleSpinBoxMean->value();
	td.deviation = ui_->doubleSpinBoxDeviation->value();
	td.tileSize = ui_->doubleSpinBoxTileSize->value();
	/*td.noOfOctaves = octaves;
	td.noiseFrequency = frequency;
	td.terrainSize = size;
	td.tileSize = tileSize;*/

	buw::ReferenceCounted<buw::CreateRandomTerrain> crt = std::make_shared<buw::CreateRandomTerrain>(td);
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().execute(crt);
	
	hide();
}

void OpenInfraPlatform::UserInterface::GenerateTerrainDialog::on_pushButtonCancel_clicked()
{
	hide();
}
