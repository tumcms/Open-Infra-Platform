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

#include "OSMImportDialog.h"

#include "OpenInfraPlatform/Infrastructure/Import/ImportOSM.h"

OpenInfraPlatform::UserInterface::OSMImportDialog::OSMImportDialog(QWidget *parent /*= nullptr*/):
	ui_(new Ui::OSMImportDialog),
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
	lastItem_(nullptr)
{
	ui_->setupUi(this);

	ui_->filterList->clear();
	addItem();

	QObject::connect(ui_->filterList, &QListWidget::itemChanged, this, &OSMImportDialog::on_currentFilterItem_changed);

	bIgnoreChanges_ = false;

	std::vector<std::string> filter = OpenInfraPlatform::Infrastructure::ImportOSM::getDefaultFilter();
	std::vector<std::string> modes = OpenInfraPlatform::Infrastructure::ImportOSM::getModeNames();

	setFilterList(filter);
	setModes(modes);
}

OpenInfraPlatform::UserInterface::OSMImportDialog::~OSMImportDialog()
{
}

void OpenInfraPlatform::UserInterface::OSMImportDialog::addItem(const std::string& label, bool select)
{
	bIgnoreChanges_ = true;
	ui_->filterList->addItem(QString(label.c_str()));

	lastItem_ = ui_->filterList->item(ui_->filterList->count() - 1);
	lastItem_->setFlags(Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsSelectable | Qt::ItemFlag::ItemIsEditable);
	lastItem_->setSelected(select);

	bIgnoreChanges_ = false;
}

void OpenInfraPlatform::UserInterface::OSMImportDialog::removeItem(QListWidgetItem* item)
{
	bIgnoreChanges_ = true;
	ui_->filterList->takeItem(ui_->filterList->row(item));
	lastItem_ = ui_->filterList->item(ui_->filterList->count() - 1);
	bIgnoreChanges_ = false;
}

void OpenInfraPlatform::UserInterface::OSMImportDialog::on_currentFilterItem_changed(QListWidgetItem* item)
{
	if (bIgnoreChanges_)
		return;

	if (item == lastItem_ && item->text() != "")
		addItem();
	if (item != lastItem_ && item->text() == "")
		removeItem(item);
}


void OpenInfraPlatform::UserInterface::OSMImportDialog::setFilename(const std::string& filename)
{
	setWindowFilePath(QString(filename.c_str()));
}

void OpenInfraPlatform::UserInterface::OSMImportDialog::setFilterList(const std::vector<std::string>& filter)
{
	bIgnoreChanges_ = true;
	ui_->filterList->clear();
	for (const std::string& str : filter)
	{
		addItem(str, false);
	}

	addItem();
	bIgnoreChanges_ = false;
}
std::vector<std::string> OpenInfraPlatform::UserInterface::OSMImportDialog::getFilterList()
{
	std::vector<std::string> filter;
	for (int r = 0; r < ui_->filterList->count() - 1; r++)
	{
		filter.push_back(ui_->filterList->item(r)->text().toStdString());
	}

	return filter;
}

void OpenInfraPlatform::UserInterface::OSMImportDialog::setModes(const std::vector<std::string>& modes)
{
	ui_->connectionModeComboBox->clear();

	for (const std::string& mode : modes)
	{
		ui_->connectionModeComboBox->addItem(QString(mode.c_str()));
	}
}
int OpenInfraPlatform::UserInterface::OSMImportDialog::getMode()
{
	return ui_->connectionModeComboBox->currentIndex();
}