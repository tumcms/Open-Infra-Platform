/*
Copyright (c) 2018 Technical University of Munich
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

#include "ui_ShowIFCtree.h"
#include "ViewPanel/View.h"
//#include <BlueFramework/Engine/Camera/InfraCameraController.h>
#include <QDialog>
#include <QTreeView>
#include <boost/noncopyable.hpp>
#include <string>
#include <iostream>


using namespace OpenInfraPlatform::IfcAlignment1x1;
namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		class ShowIFCtree : public QDialog
		{
			//Q_OBJECT;
		//public:
			
			//private Q_SLOTS:
	


		public:
			//! Default constructor.
			ShowIFCtree(OpenInfraPlatform::UserInterface::View* view, QWidget *parent = nullptr);

			//! Virtual destructor.
			virtual ~ShowIFCtree() {};
			void show();

		private Q_SLOTS:
			void on_treeView_expanded(const QModelIndex &index);
			//bool 	itemsExpandable(const QModelIndex &index) const;
			//void 	setItemsExpandable(bool enable, const QModelIndex &index);


		private:
			Ui::ShowIFCtree*	ui_;

			QTranslator*			translator_;
			OpenInfraPlatform::UserInterface::View* view_;
			//buw::ReferenceCounted<buw::InfraCameraController>	infraCameraController_;

		}; // end class AddGeoreference
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::UserInterface::ShowIFCtree;
}

