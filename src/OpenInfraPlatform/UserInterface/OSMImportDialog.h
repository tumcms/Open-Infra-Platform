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

#pragma once
#include "ui_OSMImportDialog.h"
#include <string>
#include <vector>

namespace OpenInfraPlatform
{
	namespace UserInterface
	{

		class OSMImportDialog : public QDialog
		{
			Q_OBJECT;

		public:
			//! Default constructor.
			OSMImportDialog(QWidget *parent = nullptr);

			//! Virtual destructor.
			virtual ~OSMImportDialog();

			void setFilename(const std::string& filename);

			void setFilterList(const std::vector<std::string>& filter);
			std::vector<std::string> getFilterList();

			void setModes(const std::vector<std::string>& modes);
			int getMode();

		private Q_SLOTS:
			void addItem(const std::string& label = "", bool select = true);
			void removeItem(QListWidgetItem* item);
		
			void on_currentFilterItem_changed(QListWidgetItem* item);

		private:
			Ui::OSMImportDialog*	ui_;
			QListWidgetItem* lastItem_;
			bool bIgnoreChanges_;;
		};
	}
}