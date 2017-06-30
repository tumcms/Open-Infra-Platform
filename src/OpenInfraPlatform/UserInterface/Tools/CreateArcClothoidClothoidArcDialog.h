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
#include "ui_CreateArcClothoidClothoidArc.h"
#include "functions.h"

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		class CreateArcClothoidClothoidArcDialog : public QDialog
		{
			Q_OBJECT;

			private Q_SLOTS:
			void on_pushButtonGenerate_clicked();
			void on_pushButtonCancel_clicked();

		public:
			CreateArcClothoidClothoidArcDialog(QWidget *parent = nullptr);

			virtual ~CreateArcClothoidClothoidArcDialog();
				
		protected:
			virtual void changeEvent(QEvent* evt) override;

			public Q_SLOTS:
			void takePoints(std::vector<buw::Vector3d> givenPoints, buw::Vector2d givenOffset)
			{
				points_ = givenPoints;
				offset_ = givenOffset;
			};
		private:
			std::vector<buw::Vector3d> points_;
			buw::Vector2d offset_;			Ui::CreateArcClothoidClothoidArc*	ui_;
		}; // end class CreateArcClothoidClothoidArc
	} // end namespace UserInterface
} // end namespace OpenInfraPlatfom

namespace buw
{
	using OpenInfraPlatform::UserInterface::CreateArcClothoidClothoidArcDialog;
}

