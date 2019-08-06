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

#ifndef TUNNELGENERATOR_H
#define TUNNELGENERATOR_H
#pragma once
#include <QWindow>
#include "ui_TunnelGenerator.h"
#include "src/Ifc4FileFactory.h"
namespace Ui
{
	class TunnelGeneratorWindow;
}

	namespace UserInterface
	{
		
		class TunnelGenerator : public QMainWindow
		{
			Q_OBJECT;

		public:
			//! Default constructor.
			TunnelGenerator(QWidget *parent = nullptr);

			//! Virtual destructor.
			virtual ~TunnelGenerator() {};
			std::string SpaceName[14];
			std::string  saveName;			
			std::vector <t_part> t_parts; // t_part has the elements current, previous, father_pos, aggregate_pos and openName
		protected:

			private Q_SLOTS:
			void on_pushButtonSave_ifc4_clicked();
			void on_pushButtonSave_tunnel_clicked();
			void on_pushButtonOpen_clicked();

		private:
			Ui::TunnelGeneratorWindow*	ui_;
		}; // end class TunnelGenerator
	} // end namespace UserInterface

#endif
