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

#include "CreateArcClothoidArcDialog.h"

OpenInfraPlatform::UserInterface::CreateArcClothoidArcDialog::CreateArcClothoidArcDialog(QWidget *parent /*= nullptr*/) :
	ui_(new Ui::CreateArcClothoidArc),
	QDialog(parent, Qt::WindowTitleHint|Qt::WindowCloseButtonHint)
{
	 ui_->setupUi(this);
	 ui_->labelPicture->setPixmap(QPixmap(":/ACA.svg"));
	 ui_->labelPicture->show();

}

OpenInfraPlatform::UserInterface::CreateArcClothoidArcDialog::~CreateArcClothoidArcDialog()
{

}

void OpenInfraPlatform::UserInterface::CreateArcClothoidArcDialog::on_pushButtonGenerate_clicked()
{
	hide();
	std::string message;
	buw::Vector2d  Vect, x_axis = { 1.0, 0.0 }, cloth_start_dir, theostartPoint, center[2], start[2], end[2];
	double L[2], tau[2], R_inserted, deltaL, R[2], width, sig = 1;
	double distance, gon = M_PI / 200, phi1, phi2, A;
	bool clockClo = false, Radius1;
	QString s = ui_->lineEdit_R->text();
	R_inserted = s.toDouble();
	s = ui_->lineEdit_A->text();
	A = s.toDouble();
	s = ui_->lineEdit_phi1->text();
	phi1 = s.toDouble()*gon;
	s = ui_->lineEdit_phi2->text();
	phi2 = s.toDouble()*gon;
	s = ui_->lineEdit_L->text();
	deltaL = s.toDouble();
	if (ui_->radioButton_line1->isChecked())
	{
		Radius1 = true;
	}
	if (ui_->radioButton_line2->isChecked())
	{
		Radius1 = false;
	}
	s = ui_->lineEdit_d->text();
	distance = s.toDouble();
	s = ui_->lineEdit_c->text();
	width = s.toDouble();
	if (isInsertZero(R_inserted, 1, 1, 1, 1, 1, message) == 0 || isAngleInBorders(phi1, phi2, message) == 0 || are2Points(points_.size(), message) == 0 || isInsertNotZero(A, 1, deltaL, message) == 0)
	{
		QMessageBox::warning(this, QApplication::applicationName(), QString::fromStdString(message));
		return;
	}
	Vect = points_[1].block<2,1>(0,0) - points_[0].block<2,1>(0,0);
	double drawnR = Vect.norm();
	R[1] = drawnR;
	R[0] = R_inserted;
	if (Radius1 == true)
	{
		R[0] = drawnR;
		R[1] = R_inserted;
	}
	if (A == 0 && deltaL != 0)
	{
		A = sqrt((R[0] * R[1] / (std::abs(R[0] - R[1])))*deltaL);
	}
	if (R[0] < R[1])
	{
		sig = -1;
		clockClo = true;
	}
	compute_L_tau(L[0], L[1], tau[0], tau[1], A, A, R[0], R[1]);
	if (isClothoidInBorder(tau[0], tau[1], M_PI, message) == 0)
	{
		QMessageBox::warning(this, QApplication::applicationName(), QString::fromStdString(message));
		return;
	}
	buw::Vector2d  delta_cloth_dir = buw::createRotationMatrix<double>(sig*M_PI / 2)*Vect.normalized();
	double delta_cloth_angle = buw::calculateAngleBetweenVectors(x_axis, delta_cloth_dir);
	if (Radius1 == true)
	{
		give2Points(center[0], end[0], Vect, points_[0].block<2, 1>(0, 0), points_[1].block<2, 1>(0, 0), offset_);
		start[0] = center[0] + buw::createRotationMatrix<double>(-phi1)* Vect;
		theostartPoint = end[0] - buw::createRotationMatrix<double>(delta_cloth_angle - sig*tau[0])*relCloEnd(L[0], A, sig);
		cloth_start_dir = buw::createRotationMatrix<double>(-sig*tau[0])*delta_cloth_dir;
		start[1] = theostartPoint + buw::createRotationMatrix<double>(delta_cloth_angle - sig*tau[0])*relCloEnd(L[1], A, sig);
		center[1] = start[1] + R[1] * buw::createRotationMatrix<double>(delta_cloth_angle + sig*(tau[1] - tau[0] + M_PI / 2))*x_axis;
		end[1] = center[1] + buw::createRotationMatrix<double>(phi2)* (start[1] - center[1]);
	}
	else
	{
		give2Points(center[1], start[1], Vect, points_[0].block<2, 1>(0, 0), points_[1].block<2, 1>(0, 0), offset_);
		end[1] = center[1] + buw::createRotationMatrix<double>(phi2)* Vect;
		theostartPoint = start[1] - buw::createRotationMatrix<double>(delta_cloth_angle - sig*tau[1])*relCloEnd(L[1], A, sig);
		cloth_start_dir = buw::createRotationMatrix<double>(-sig*tau[1])*delta_cloth_dir;
		end[0] = theostartPoint + buw::createRotationMatrix<double>(delta_cloth_angle - sig*tau[1])*relCloEnd(L[0], A, sig);
		center[0] = end[0] + R[0] * buw::createRotationMatrix<double>(delta_cloth_angle + sig*(tau[0] - tau[1] + M_PI / 2))*x_axis;
		start[0] = center[0] + buw::createRotationMatrix<double>(-phi1)* (end[0] - center[0]);
	}
	GeneralArcClothoidArc(cloth_start_dir, theostartPoint, clockClo, center[0], center[1], start[0], start[1], end[0], end[1], width, distance,Radius1, sig, A, R[0], R[1]);
}

void OpenInfraPlatform::UserInterface::CreateArcClothoidArcDialog::on_pushButtonCancel_clicked()
{
	hide();
}
