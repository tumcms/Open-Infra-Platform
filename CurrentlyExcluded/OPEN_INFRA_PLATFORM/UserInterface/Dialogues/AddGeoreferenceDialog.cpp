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

#include "AddGeoreferenceDialog.h"

#include "OpenInfraPlatform/DataManagement/Data.h"

void OpenInfraPlatform::UserInterface::AddGeoreferenceDialog::on_pushButtonCheck_clicked()
{
	//TODO
}

void OpenInfraPlatform::UserInterface::AddGeoreferenceDialog::on_pushButtonCancel_clicked()
{
	this->reject();
	//connect(ui_->pushButtonCancel, SIGNAL(rejected()), this, SLOT(reject()));
}

void OpenInfraPlatform::UserInterface::AddGeoreferenceDialog::on_pushButtonOk_clicked()
{
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().setEastings(m_Eastings);
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().setNorthings(m_Northings);
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().setOrthogonalHeight(m_OrthogonalHeight);
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().setEPSGcodeName(m_Name);
	this->accept();
}


void OpenInfraPlatform::UserInterface::AddGeoreferenceDialog::show()
{
	ui_->doubleSpinBoxEasting->setValue(OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getEastings());
	ui_->doubleSpinBoxNorthing->setValue(OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getNorthings());
	ui_->doubleSpinBoxHeight->setValue(OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getOrthogonalHeight());
	ui_->spinBoxEPSG->setValue(OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getEPSGcodeName().split(":")[1].toInt());
	ui_->labelOutputAreaName->setText(OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getEPSGcodeName());

	((QDialog*)this)->show();
}

void OpenInfraPlatform::UserInterface::AddGeoreferenceDialog::on_doubleSpinBoxEasting_valueChanged(double value) {
	m_Eastings = value;

	//double m_Eastings = value;
	//auto proxyModel = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getProxyModel();
	//auto entities = proxyModel->getIfc4x1Data();
	//
	//for (auto it : entities) {
	//	if (it.second->m_entity_enum == OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1EntityEnum::IFCMAPCONVERSION) {
	//		std::shared_ptr<IfcMapConversion> mapConversion = std::static_pointer_cast<IfcMapConversion>(it.second);
	//		mapConversion->m_Eastings = std::make_shared<IfcLengthMeasure>(m_Eastings);
	//	}
	//}

}

void OpenInfraPlatform::UserInterface::AddGeoreferenceDialog::on_doubleSpinBoxNorthing_valueChanged(double value) {
	m_Northings = value;
	
	//double m_Northings = value;
	//auto proxyModel = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getProxyModel();
	//auto entities = proxyModel->getIfc4x1Data();
	//
	//for (auto it : entities) {
	//	if (it.second->m_entity_enum == OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1EntityEnum::IFCMAPCONVERSION) {
	//		std::shared_ptr<IfcMapConversion> mapConversion = std::static_pointer_cast<IfcMapConversion>(it.second);
	//		mapConversion->m_Northings = std::make_shared<IfcLengthMeasure>(m_Northings);
	//	}
	//}

}

void OpenInfraPlatform::UserInterface::AddGeoreferenceDialog::on_doubleSpinBoxHeight_valueChanged(double value) {
	m_OrthogonalHeight = value;
	
	//double m_OrthogonalHeight = value;
	//auto proxyModel = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getProxyModel();
	//auto entities = proxyModel->getIfc4x1Data();
	//
	//for (auto it : entities) {
	//	if (it.second->m_entity_enum == OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1EntityEnum::IFCMAPCONVERSION) {
	//		std::shared_ptr<IfcMapConversion> mapConversion = std::static_pointer_cast<IfcMapConversion>(it.second);
	//		mapConversion->m_OrthogonalHeight = std::make_shared<IfcLengthMeasure>(m_OrthogonalHeight);
	//	}
	//}

}

void OpenInfraPlatform::UserInterface::AddGeoreferenceDialog::on_spinBoxEPSG_valueChanged(int value) {
	m_Name = "EPSG:" + QString::number(value);

	//QString m_GeodeticDatum = "EPSG"+QString::number(value);

	//auto proxyModel = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getProxyModel();
	//OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().setEPSGcodeName(m_Name);
	//auto entities = proxyModel->getIfc4x1Data();

	//for (auto it : entities) {
		//if (it.second->m_entity_enum == OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1EntityEnum::IFCPROJECTEDCRS) {
			//std::shared_ptr<IfcProjectedCRS> projectedCRS = std::static_pointer_cast<IfcProjectedCRS>(it.second);
			//projectedCRS->m_Name = std::make_shared<IfcLabel>(m_Name.toStdString());
			//projectedCRS->m_GeodeticDatum = std::make_shared<IfcIdentifier>(m_GeodeticDatum.toStdString());
		//}
	//}
//Prüfen ob der EPSG-Code existiert -> wird oben schon überprüft
	//aus library oder HTML lesen was der area name ist und die Basisdaten und Verschiebungen einlesen
	ui_->labelOutputAreaName->setText(m_Name);
}

OpenInfraPlatform::UserInterface::AddGeoreferenceDialog::AddGeoreferenceDialog(OpenInfraPlatform::UserInterface::View * view, QWidget * parent)
	:ui_(new Ui::AddGeoreferenceDialog),
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
	view_(view)
{
	ui_->setupUi(this);
		
}



