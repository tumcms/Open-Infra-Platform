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
#ifndef OpenInfraPlatform_UserInterface_GenerateTerrain_c5f0677f_a918_44dc_9cee_e5eacc6e0c45_h
#define OpenInfraPlatform_UserInterface_GenerateTerrain_c5f0677f_a918_44dc_9cee_e5eacc6e0c45_h

#include <QDialog>
#include <boost/noncopyable.hpp>
#include "ui_GenerateTerrain.h"

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		//! \class GenerateTerrain
		//! \brief brief description
		class GenerateTerrainDialog : public QDialog
		{
			Q_OBJECT;

		public:
			//! Default constructor.
			GenerateTerrainDialog(QWidget *parent = nullptr);

			//! Virtual destructor.
			virtual ~GenerateTerrainDialog();

		protected:
			virtual void changeEvent(QEvent* evt) override;

		private Q_SLOTS:
			void on_pushButtonGenerate_clicked();
			void on_pushButtonCancel_clicked();

		private:
			Ui::GenerateTerrain*	ui_;
		}; // end class GenerateTerrain
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::UserInterface::GenerateTerrainDialog;
}

#endif // end define OpenInfraPlatform_UserInterface_GenerateTerrain_c5f0677f_a918_44dc_9cee_e5eacc6e0c45_h
