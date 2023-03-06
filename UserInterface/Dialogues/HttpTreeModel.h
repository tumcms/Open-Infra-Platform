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

#pragma once
#ifndef OpenInfraPlatform_UserInterface_HttpTreeModel_38da791c_994f_450a_abc1_6676bdf555c4_h
#define OpenInfraPlatform_UserInterface_HttpTreeModel_38da791c_994f_450a_abc1_6676bdf555c4_h

#include <QDialog>
#include <QMessageBox>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QTreeWidget>
#include <QModelIndex>

#include "ui_HttpTreeModelDialog.h"

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		/**
		* @class HttpTreeModel
		* 
		* @brief A QDialog-derived class used for building a tree model from JSON data obtained from a HTTP request
		* 
		* This class is used to build a tree model from JSON data obtained from a HTTP request. It is
		* derived from QDialog and Ui::HttpTreeModelDialog to get access to the UI form elements.
		* The tree model is built by adding a root item to the tree using the addTreeRoot method, then
		* adding child items to the root item using the addTreeChild method. The tree model can be built
		* using the buildTreeModel method, which takes in a QJsonArray of data to be displayed in the tree.
		* The user can select a specific item in the tree by clicking on it and then clicking the Select button.
		* The selected item's position in the tree can be retrieved using the getSelectedPosition method.
		* 
		* @note This class requires the Qt5 framework to be installed in order to build and run.
		*/
		class HttpTreeModel : public QDialog, public Ui::HttpTreeModelDialog
		{
			Q_OBJECT;

		public:
			/** 
			* @brief Constructor for HttpTreeModel
			* 
			* @param parent The parent widget for the QDialog
			*/
			HttpTreeModel(QWidget* parent = nullptr);

			/**
			* @brief Destructor for HttpTreeModel
			*/
			~HttpTreeModel();

			/**
			* @brief Build the tree model from a QJsonArray
			* 
			* This method builds the tree model from the given QJsonArray of data. It clears the existing 
			* tree model and creates a new one using the root item and child items specified in the QJsonArray.
			* 
			* @param data The QJsonArray of data to be displayed in the tree
			*/
			void buildTreeModel(const QJsonArray& data);

			/**
			* @brief Add a root item to the tree model
			* 
			* This method adds a root item to the tree model using the given QJsonObject as the root item's data.
			* 
			* @param rootObject The QJsonObject to be used as the root item's data
			*/
			void addTreeRoot(const QJsonObject& rootObject);

			/**
			* @brief Add a child item to the specified parent item in the tree model
			* 
			* This method adds a child item to the specified parent item in the tree model using the given
			* QJsonObject as the child item's data.
			* 
			* @param parent The parent item to which the child item should be added
			* @param childObject The QJsonObject to be used as the child item's data
			*/
			void addTreeChild(QTreeWidgetItem* parent, const QJsonObject& childObject);

			/**
			* @brief Get the position of the selected item in the tree
			*
			* This method returns the position of the selected item in the tree. The position is the index
			* of the item in the tree model, starting from 0 for the first item.
			*
			* @return int The position of the selected item in the tree
			*/
			int getSelectedPosition() { return position_; }

		private slots:
			/**
			* @brief Slot for handling the Select button click event
			*
			* This slot is called when the user clicks the Select button. It retrieves the currently selected
			* item in the tree and stores its position in the position_ member variable.
			*/
			void on_selectBtn_clicked();

		private:
			unsigned int							position_;	/** The position of the selected item in the tree */
		};
	}
}

#endif // end define OpenInfraPlatform_UserInterface_HttpTreeModel_38da791c_994f_450a_abc1_6676bdf555c4_h