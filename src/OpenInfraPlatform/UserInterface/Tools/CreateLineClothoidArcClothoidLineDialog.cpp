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

#include "CreateLineClothoidArcClothoidLineDialog.h"

OpenInfraPlatform::UserInterface::CreateLineClothoidArcClothoidLineDialog::CreateLineClothoidArcClothoidLineDialog(QWidget *parent /*= nullptr*/) :
	ui_(new Ui::CreateLineClothoidArcClothoidLine),
	QDialog(parent, Qt::WindowTitleHint|Qt::WindowCloseButtonHint)
{
	 ui_->setupUi(this);
	 ui_->labelPicture->setPixmap(QPixmap(":/LCACL.svg"));
	 ui_->labelPicture->show();
}

OpenInfraPlatform::UserInterface::CreateLineClothoidArcClothoidLineDialog::~CreateLineClothoidArcClothoidLineDialog()
{

}

void OpenInfraPlatform::UserInterface::CreateLineClothoidArcClothoidLineDialog::changeEvent(QEvent* evt) 
{
	if (evt->type() == QEvent::LanguageChange)
	{
		ui_->retranslateUi(this);
	}
	else
	{
		QWidget::changeEvent(evt);
	}
}

void OpenInfraPlatform::UserInterface::CreateLineClothoidArcClothoidLineDialog::on_pushButtonGenerate_clicked()
{
	hide();
	double Ri, Ro, Ai, Ao, dummy[2], angle, gamma, Tq, t1, t2, T1, T2, betA[2], L[2], tau[2], A[2], R, width, distance;
	bool clocky[2], UseNoLines = false;
	buw::Vector2d U, V, W, LineDir[2], center, start, end, CloStartI[2], CloStartO[2], RelCloEnd1, RelCloEnd2, x_axis = { 1.0, 0.0 }, oldEnd[3], startPoint[2], RelM1, RelM2;
	buw::ReferenceCounted<buw::HorizontalAlignment2D> ha = std::make_shared<buw::HorizontalAlignment2D>();
	std::string message;
	QString s = ui_->lineEdit_R->text();
	R = s.toDouble();
	s = ui_->lineEdit_A1->text();
	A[0] = s.toDouble();
	s = ui_->lineEdit_A2->text();
	A[1] = s.toDouble();
	s = ui_->lineEdit_d_2->text();
	distance = s.toDouble();
	s = ui_->lineEdit_c_2->text();
	width = s.toDouble();

	if (are3_4or5Points(points_.size(), message) == 0 || isInsertZero(1, 1, 1, A[1], A[0], R, message) == 0)
	{
		QMessageBox::warning(this, QApplication::applicationName(), QString::fromStdString(message));
		return;
	}
	compute_L_tau(L[0], L[1], tau[0], tau[1], A[0], A[1], R, R);
	RelCloEnd1 = relCloEnd(L[0], A[0], 1);
	RelCloEnd2 = relCloEnd(L[1], A[1], 1);
	RelM1 = RelCloEnd1 + R* buw::createRotationMatrix<double>(M_PI / 2 + tau[0])*x_axis;
	RelM2 = RelCloEnd2 + R* buw::createRotationMatrix<double>(M_PI / 2 + tau[1])*x_axis;
	for (int Groupnumber = 0; Groupnumber < points_.size() - 2; Groupnumber++)
	{
		give3Points(U, V, W, LineDir[0], LineDir[1], angle, dummy[0], dummy[1], points_[Groupnumber].block<2,1>(0,0), points_[Groupnumber + 1].block<2,1>(0,0), points_[Groupnumber + 2].block<2,1>(0,0), offset_.block<2,1>(0,0));
		gamma = M_PI - angle;
		if ((gamma - tau[0] - tau[1]) < 0)// see script of Prof. Baeumker page 38
		{
			QMessageBox::warning(this, QApplication::applicationName(), "Please reduce the angle between the lines or A1 or A2 or increase R, otherwise the arclength would be negative.");
			return;
		}
		Tq = sqrt(RelM1.y()*RelM1.y() + RelM2.y()*RelM2.y() - 2 * cos(gamma)*RelM1.y()*RelM2.y());
		betA[0] = asin(RelM2.y()*sin(gamma) / Tq);
		betA[1] = asin(RelM1.y()*sin(gamma) / Tq);
		t1 = Tq*cos(betA[1]) / sin(gamma);
		t2 = Tq*cos(betA[0]) / sin(gamma);
		T1 = t1 + RelM1.x();
		T2 = t2 + RelM2.x();
		startPoint[0] = V + T1*LineDir[0];
		startPoint[1] = V + T2*LineDir[1];
		int sig = -1, sigm = 1;
		clocky[0] = true, clocky[1] = false;
		if (LineDir[0].x()*LineDir[1].y() - LineDir[0].y()*LineDir[1].x() < 0)// vectorproduct determines the orientation of clothoids
		{
			clocky[0] = false;// for first clothoid and arc
			clocky[1] = true;
			sig = 1;
		}
		center = V + t1*LineDir[0] + RelM1.y()* buw::createRotationMatrix<double>(-sig*M_PI / 2)* LineDir[0];
		start = V + (T1 - RelCloEnd1.x())*LineDir[0] + RelCloEnd1.y()*buw::createRotationMatrix<double>(-sig*M_PI / 2)* LineDir[0];
		end = V + (T2 - RelCloEnd2.x())*LineDir[1] + RelCloEnd2.y()* buw::createRotationMatrix<double>(sig* M_PI / 2)* LineDir[1];
		if (isClothoidInBorder(tau[1], tau[0], M_PI, message) == 0 || areErrorsForParallelClo(L[0], A[0], width, distance, UseNoLines, message) == 0 || areErrorsForParallelArc(R, width, message) == 0 || areErrorsForParallelClo(L[1], A[1], width, distance, UseNoLines, message) == 0)
		{
			QMessageBox::warning(this, QApplication::applicationName(), QString::fromStdString(message));
			return;
		}
		makeClothoid(0.0, R, A[0], startPoint[0], -LineDir[0], clocky[0]);
		makeClothoid(0.0, R, A[1], startPoint[1], -LineDir[1], clocky[1]);
		makeArc(center, start, end, clocky[0]);
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line1 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(startPoint[0], V);
		ha->addElement(line1);
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line2 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(V, startPoint[1]);
		ha->addElement(line2);
		if (width > 0)
		{
			for (int i = 0; i < 2; i++)// this loop starts with clothoid 1 and ends with clothoid 2
			{
				double start_angle = buw::calculateAngleBetweenVectors(x_axis, buw::Vector2d(-LineDir[i]));
				buw::Vector2d starthelp = width*buw::createRotationMatrix<double>(start_angle + sig* M_PI / 2)*x_axis;
				CloStartI[i] = startPoint[i] + starthelp;
				CloStartO[i] = startPoint[i] - starthelp;
				buw::Vector2d endPoint = absCloEnd(startPoint[i], -LineDir[i], L[i], A[i], sig);
				buw::Vector2d p_endhelp = width*buw::createRotationMatrix<double>(start_angle + sig* (M_PI / 2 + tau[i]))*x_axis;
				buw::Vector2d LastCloPoi = endPoint + p_endhelp;
				buw::Vector2d LastCloPoo = endPoint - p_endhelp;
				double loopend = L[i] - distance - 0.00000001;
				if (UseNoLines == true)
				{
					parallelClo(CloStartI[i], CloStartO[i], Ri, Ro, Ai, Ao, A[i], width, R, startPoint[i], -LineDir[i], sig);
					makeClothoid(0.0, Ri, Ai, CloStartI[i], -LineDir[i], clocky[i]);
					makeClothoid(0.0, Ro, Ao, CloStartO[i], -LineDir[i], clocky[i]);
				}
				if (UseNoLines == false)
				{
					make2ClothByConnectLin(0,loopend, distance, A[i], width, startPoint[i], -LineDir[i], sig, LastCloPoi, LastCloPoo);
				}
				if (Groupnumber > 0 && i == 0)
				{
					makeOne3dLine(oldEnd[0], startPoint[0]);// middle
					makeOne3dLine(oldEnd[1], CloStartI[0]);// innerline
					makeOne3dLine(oldEnd[2], CloStartO[0]);// outerline 
				}
				buw::Vector2d starti = center + ((R + sigm*width) / R)*(start - center);
				buw::Vector2d endi = center + ((R + sigm*width) / R)*(end - center);
				makeArc(center, starti, endi, clocky[0]);
				sigm = -1;// for the arc
				sig = -sig;// attention sig has to change for every clothoid
			}
		}// end of if width
		oldEnd[0] = startPoint[1];
		oldEnd[1] = CloStartO[1];
		oldEnd[2] = CloStartI[1]; // generates old values
	}
	make3DLine(ha);// middle
}

void OpenInfraPlatform::UserInterface::CreateLineClothoidArcClothoidLineDialog::on_pushButtonCancel_clicked()
{
	hide();
}
