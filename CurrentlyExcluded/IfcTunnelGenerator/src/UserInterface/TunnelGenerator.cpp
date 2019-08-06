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

#include <QtGui>
#include "TunnelGenerator.h"
#include "ui_TunnelGenerator.h"
#include <QFileDialog>
#include <QString>
#include "qsimpleupdater.h"

bool sortByCurrent(const t_part &lhs, const t_part &rhs) { return lhs.current < rhs.current; };

UserInterface::TunnelGenerator::TunnelGenerator(QWidget *parent /*= nullptr*/)
{
	ui_ = new Ui::TunnelGeneratorWindow();
	ui_->setupUi(this);
}

void UserInterface::TunnelGenerator::on_pushButtonOpen_clicked()
{
	t_part part;
	QString filename = QFileDialog::getOpenFileName(
		this,
		tr("Open Document"),
		QDir::currentPath(),
		tr("Object File (*.obj)"));
	if (!filename.isNull())
	{
		if (ui_->radioButtonFTS->isChecked())
		{
			part.current = 1; part.previous = 0; part.openName = filename.toStdString();
		}
		if (ui_->radioButtonAGS->isChecked())
		{
			part.current = 2; part.previous = 1; part.openName = filename.toStdString();
		}
		if (ui_->radioButtonLS->isChecked())
		{
			part.current = 3; part.previous = 1; part.openName = filename.toStdString();
		}
		if (ui_->radioButtonIS->isChecked())
		{
			part.current = 4; part.previous = 1; part.openName = filename.toStdString();
		}
		if (ui_->radioButtonCS->isChecked())
		{
			part.current = 5; part.previous = 4; part.openName = filename.toStdString();
		}
		if (ui_->radioButtonSS->isChecked())
		{
			part.current = 6; part.previous = 4; part.openName = filename.toStdString();
		}
		if (ui_->radioButtonTS->isChecked())
		{
			part.current = 7; part.previous = 4; part.openName = filename.toStdString();
		}
		if (ui_->radioButtonFS->isChecked())
		{
			part.current = 8; part.previous = 4; part.openName = filename.toStdString();
		}
		if (ui_->radioButtonS->isChecked())
		{
			part.current = 9; part.previous = 4; part.openName = filename.toStdString();// the next "previousnumbers" have to be corrected 
		}
		if (ui_->radioButtonTL->isChecked())
		{
			part.current = 10; part.previous = 4; part.openName = filename.toStdString();
		}
		if (ui_->radioButtonW->isChecked())
		{
			part.current = 11; part.previous = 4; part.openName = filename.toStdString();
		}
		if (ui_->radioButtonFC->isChecked())
		{
			part.current = 12; part.previous = 8; part.openName = filename.toStdString();
		}
		if (ui_->radioButtonTC->isChecked())
		{
			part.current = 13; part.previous = 7; part.openName = filename.toStdString();
		}
		t_parts.push_back(part);
	}
}

void UserInterface::TunnelGenerator::on_pushButtonSave_ifc4_clicked()
{
	SpaceName[1] = "FullTunnelSpace"; SpaceName[2] = "AnnularGapSpace"; SpaceName[3] = "LiningSpace"; SpaceName[4] = "InteriorSpace"; SpaceName[5] = "ClearanceSpace";
	SpaceName[6] = "ServiceSpace"; SpaceName[7] = "TrackSpace"; SpaceName[8] = "FloorSpace"; SpaceName[9] = "Segment"; SpaceName[10] = "Traffic Light";
	SpaceName[11] = "Walkway"; SpaceName[12] = "Floor Concrete"; SpaceName[13] = "Trackbed Concrete";
	int answer = 0; // the next part  gives the user the chance to take a look on all the stuff, which he has created and to delete it, if he wants, before it will be generated
	QString list_of_inserts;
	for (int k = 0; k < t_parts.size(); k++)
	{
		list_of_inserts = list_of_inserts + QString("%1. %2 for: %3\n")
			.arg(k + 1).arg(QString::fromStdString(SpaceName[t_parts[k].current])).arg(QString::fromStdString(t_parts[k].openName));
	}
	list_of_inserts = list_of_inserts + QString("\nDo you want to reset your inserts ?");
	answer = QMessageBox::question(0, "", list_of_inserts,
		QMessageBox::Yes | QMessageBox::No);
	if (answer == QMessageBox::Yes)
	{
		t_parts.clear();
		return;
	}
	QString filename = QFileDialog::getSaveFileName(
		this,
		tr("Save Document"),
		QDir::currentPath(),
		tr("Ifc4 File (*.ifc)"));
	if (t_parts.size() > 1)// here we look if the user inserted to times the same obj-name. By doing so we help the user to reduce errors.
	{
		for (int kk = 0; kk < t_parts.size() - 1; kk++)
		{
			for (int kj = kk + 1; kj < t_parts.size(); kj++)
			{
				if (t_parts[kk].openName == t_parts[kj].openName || t_parts[kk].current == t_parts[kj].current)
				{
					int answer = QMessageBox::question(0, "", QString("Warning: You have selected two times the same obj-file or the same tunnel-element-species therefore program cannot convert to Ifc4 file.\nDo you want to reset your inserts ?"),
						QMessageBox::Yes | QMessageBox::No);
					if (answer == QMessageBox::Yes)
					{
						t_parts.clear();
					}
				}
			}
		}
	}
	for (int kk = 0; kk < t_parts.size(); kk++)// here we look if the user forgot to insert a previous element of the hierarchy
	{
		bool existsPrevious = false;
		for (int kj = 0; kj < t_parts.size(); kj++)
		{
			if (t_parts[kk].previous == t_parts[kj].current)// then the previous exists
			{
				existsPrevious = true;
			}
		}
		if (existsPrevious == false && t_parts[kk].current != 1) // it is clear that fulltunnelelement (that means current==1) has no previous element which the user can insert
		{
			QMessageBox::warning(this, QApplication::applicationName(), QString("You have forgotten to insert %1 which is the father-element of %2. Therefore program cannot convert to Ifc4 file.")
				.arg(QString::fromStdString(SpaceName[t_parts[kk].previous])).arg(QString::fromStdString(SpaceName[t_parts[kk].current])));
			return;
		}
	}
	int Aggreg = 0;
	if (!filename.isNull() && t_parts.size()>0)
	{
		std::sort(t_parts.begin(), t_parts.end(), sortByCurrent);// before we give the list to main.cpp we sort it
		for (int i = 0; i < t_parts.size(); i++)// now we give every element of t_parts a pos so that we can find the previous values later in main.cpp
		{
			for (int kk = 0; kk < i; kk++)
			{
				if (t_parts[i].previous == t_parts[kk].current)// we do not need an "else" because line 133 gives us just values which generate a true "if"
				{
					t_parts[i].father_pos = kk; // this is the position of previous(that means father) element in hierarchy
					bool first = true;
					for (int kj = 0; kj < i - 1; kj++)
					{
						if (t_parts[i].previous == t_parts[kj].previous)
						{
							first = false;
							t_parts[i].aggregate_pos = t_parts[kj].aggregate_pos;
						}
					}
					if (first == true)
					{
						t_parts[i].aggregate_pos = Aggreg;
						Aggreg++;
					}
					t_parts[i].first = first;
				}
			}
		}
		saveName = filename.toStdString();
		std::shared_ptr<TunnelGeneratorIfc4> tunnel = TunnelGeneratorIfc4::create(t_parts, saveName, false);
		tunnel->store(false);
		QMessageBox::warning(this, QApplication::applicationName(), "Ifc4 File has been generated. Tunnel-generator will be closed.");
		close();
	}
}

void UserInterface::TunnelGenerator::on_pushButtonSave_tunnel_clicked()
{
	SpaceName[1] = "FullTunnelSpace"; SpaceName[2] = "AnnularGapSpace"; SpaceName[3] = "LiningSpace"; SpaceName[4] = "InteriorSpace"; SpaceName[5] = "ClearanceSpace";
	SpaceName[6] = "ServiceSpace"; SpaceName[7] = "TrackSpace"; SpaceName[8] = "FloorSpace"; SpaceName[9] = "Segment"; SpaceName[10] = "Traffic Light";
	SpaceName[11] = "Walkway"; SpaceName[12] = "Floor Concrete"; SpaceName[13] = "Trackbed Concrete";
	int answer = 0; // the next part  gives the user the chance to take a look on all the stuff, which he has created and to delete it, if he wants, before it will be generated
	QString list_of_inserts;
	for (int k = 0; k < t_parts.size(); k++)
	{
		list_of_inserts = list_of_inserts + QString("%1. %2 for: %3\n")
			.arg(k + 1).arg(QString::fromStdString(SpaceName[t_parts[k].current])).arg(QString::fromStdString(t_parts[k].openName));
	}
	list_of_inserts = list_of_inserts + QString("\nDo you want to reset your inserts ?");
	answer = QMessageBox::question(0, "", list_of_inserts,
		QMessageBox::Yes | QMessageBox::No);
	if (answer == QMessageBox::Yes)
	{
		t_parts.clear();
		return;
	}
	QString filename = QFileDialog::getSaveFileName(
		this,
		tr("Save Document"),
		QDir::currentPath(),
		tr("Ifc4_Tunnel File (*.ifc)"));
	if (t_parts.size() > 1)// here we look if the user inserted to times the same obj-name. By doing so we help the user to reduce errors.
	{
		for (int kk = 0; kk < t_parts.size() - 1; kk++)
		{
			for (int kj = kk + 1; kj < t_parts.size(); kj++)
			{
				if (t_parts[kk].openName == t_parts[kj].openName || t_parts[kk].current == t_parts[kj].current)
				{
					int answer = QMessageBox::question(0, "", QString("Warning: You have selected two times the same obj-file or the same tunnel-element-species therefore program cannot convert to Ifc4_Tunnel file.\nDo you want to reset your inserts ?"),
						QMessageBox::Yes | QMessageBox::No);
					if (answer == QMessageBox::Yes)
					{
						t_parts.clear();
					}
				}
			}
		}
	}
	for (int kk = 0; kk < t_parts.size(); kk++)// here we look if the user forgot to insert a previous element of the hierarchy
	{
		bool existsPrevious = false;
		for (int kj = 0; kj < t_parts.size(); kj++)
		{
			if (t_parts[kk].previous == t_parts[kj].current)// then the previous exists
			{
				existsPrevious = true;
			}
		}
		if (existsPrevious == false && t_parts[kk].current != 1) // it is clear that fulltunnelelement (that means current==1) has no previous element which the user can insert
		{
			QMessageBox::warning(this, QApplication::applicationName(), QString("You have forgotten to insert %1 which is the father-element of %2. Therefore program cannot convert to Ifc4_Tunnel file.")
				.arg(QString::fromStdString(SpaceName[t_parts[kk].previous])).arg(QString::fromStdString(SpaceName[t_parts[kk].current])));
			return;
		}
	}
	int Aggreg = 0;
	if (!filename.isNull() && t_parts.size()>0)
	{
		std::sort(t_parts.begin(), t_parts.end(), sortByCurrent);// before we give the list to main.cpp we sort it
		for (int i = 0; i < t_parts.size(); i++)// now we give every element of t_parts a pos so that we can find the previous values later in main.cpp
		{
			for (int kk = 0; kk < i; kk++)
			{
				if (t_parts[i].previous == t_parts[kk].current)// we do not need an "else" because line 133 gives us just values which generate a true "if"
				{
					t_parts[i].father_pos = kk; // this is the position of previous(that means father) element in hierarchy
					bool first = true;
					for (int kj = 0; kj < i - 1; kj++)
					{
						if (t_parts[i].previous == t_parts[kj].previous)
						{
							first = false;
							t_parts[i].aggregate_pos = t_parts[kj].aggregate_pos;
						}
					}
					if (first == true)
					{
						t_parts[i].aggregate_pos = Aggreg;
						Aggreg++;
					}
					t_parts[i].first = first;
				}
			}
		}
		saveName = filename.toStdString();
		std::shared_ptr<TunnelGeneratorIfc4> tunnel = TunnelGeneratorIfc4::create(t_parts, saveName, true);
		tunnel->store(true);
		QMessageBox::warning(this, QApplication::applicationName(), "Ifc4_Tunnel File has been generated. Tunnel-generator will be closed.");
		close();
	}
}



