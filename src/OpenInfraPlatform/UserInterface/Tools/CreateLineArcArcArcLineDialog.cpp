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

#include "CreateLineArcArcArcLineDialog.h"

OpenInfraPlatform::UserInterface::CreateLineArcArcArcLineDialog::CreateLineArcArcArcLineDialog(QWidget *parent /*= nullptr*/) :
ui_(new Ui::CreateLineArcArcArcLine),
	QDialog(parent, Qt::WindowTitleHint|Qt::WindowCloseButtonHint)
{
	 ui_->setupUi(this);
	 ui_->labelPicture->setPixmap(QPixmap(":/LAAAL.svg"));
	 ui_->labelPicture->show();
}

OpenInfraPlatform::UserInterface::CreateLineArcArcArcLineDialog::~CreateLineArcArcArcLineDialog()
{

}

void OpenInfraPlatform::UserInterface::CreateLineArcArcArcLineDialog::changeEvent(QEvent* evt)
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

void OpenInfraPlatform::UserInterface::CreateLineArcArcArcLineDialog::on_pushButtonGenerate_clicked()
{
	hide();
	buw::ReferenceCounted<buw::HorizontalAlignment2D> ha = std::make_shared<buw::HorizontalAlignment2D>();
	double beta[3], t1[3], t2[3], R[3], alpha = 0, Y1, X1, ny, M1M3, epsilon = 0, eta = 0, delta = 0, gon = M_PI / 200, phi = 17.5*gon, psi = 22.5*gon, width;
	std::vector<buw::Vector2d> oldEnd, end, start, center;
	double u1, u2, u3, u4;// phi==a1, psi==a3
	bool ral, r213;
	buw::Vector2d P[9], LineDir[6], starti[6], endi[6], start0, end2, center2, start2;
	std::string message;

	QString s = ui_->lineEdit_R2->text();
	R[1] = s.toDouble();
	s = ui_->lineEdit_u1->text();
	u1 = s.toDouble();
	s = ui_->lineEdit_u2->text();
	u2 = s.toDouble();
	s = ui_->lineEdit_u3->text();
	u3 = s.toDouble();
	s = ui_->lineEdit_u4->text();
	u4 = s.toDouble();
	s = ui_->lineEdit_c->text();
	width = s.toDouble();
	if (ui_->radioButton_213->isChecked())
	{
		r213 = true;
	}
	if (ui_->radioButton_25155->isChecked())
	{
		r213 = false;
	}
	if (ui_->radioButton_ral->isChecked())
	{
		ral = true;
	}
	if (ui_->radioButton_noral->isChecked())
	{
		ral = false;
	}
	R[2] = 5.5*R[1], R[0] = 2.5*R[1];
	if (isInsertZero(1, 1, 1, 1, 1, R[1], message) == 0 || are3_4or5Points(points_.size(), message) == 0)
	{
		QMessageBox::warning(this, QApplication::applicationName(), QString::fromStdString(message));
		return;
	}
	if (ral == false)
	{
		give3Points(P[0], P[1], P[2], LineDir[0], LineDir[1], beta[0], t1[0], t2[0], points_[0].block<2,1>(0,0), points_[1].block<2,1>(0,0), points_[2].block<2,1>(0,0), offset_);
		if (points_.size() > 3)
		{
			give3Points(P[3], P[4], P[5], LineDir[2], LineDir[3], beta[1], t1[1], t2[1], points_[1].block<2,1>(0,0), points_[2].block<2,1>(0,0), points_[3].block<2,1>(0,0), offset_);
			t2[0] = u1, t1[1] = u2, P[2] = P[1] + u1*LineDir[1], P[3] = P[4] + u2*LineDir[2];
			if (isU3U4SmallerLength(u3, u4, t1[2], message) == 0 || isU1U2SmallerLength(u1, u2, t1[1], message) == 0)
			{
				QMessageBox::warning(this, QApplication::applicationName(), QString::fromStdString(message));
				return;
			}
		}
		if (points_.size() > 4)
		{
			give3Points(P[6], P[7], P[8], LineDir[4], LineDir[5], beta[2], t1[2], t2[2], points_[2].block<2,1>(0,0), points_[3].block<2,1>(0,0), points_[4].block<2,1>(0,0), offset_);
			t2[0] = u1, t1[1] = u2, P[2] = P[1] + u1*LineDir[1], P[3] = P[4] + u2*LineDir[2];
			t2[1] = u3, t1[2] = u4, P[5] = P[3] + u3*LineDir[3], P[6] = P[7] + u4*LineDir[5];
		}
	}
	for (int Groupnumber = 0; Groupnumber < points_.size() - 2; Groupnumber++)
	{
		if (ral == true)
		{
			give3Points(P[Groupnumber * 3], P[Groupnumber * 3 + 1], P[Groupnumber * 3 + 2], LineDir[Groupnumber * 2], LineDir[Groupnumber * 2 + 1],
				beta[Groupnumber], t1[Groupnumber], t2[Groupnumber], points_[Groupnumber].block<2,1>(0,0), points_[1 + Groupnumber].block<2,1>(0,0), points_[2 + Groupnumber].block<2,1>(0,0), offset_);
		}
		alpha = M_PI - beta[Groupnumber];
		if (r213 == true)
		{
			R[2] = 3 * R[1];
			R[0] = 2 * R[1];
		}
		double T1 = ((R[1] + (R[2] - R[1])*(1 - cos(psi))) + (R[1] + (R[0] - R[1])*(1 - cos(phi)))*cos(beta[Groupnumber])) / sin(beta[Groupnumber]) + (R[0] - R[1])*sin(phi);
		double T2 = ((R[1] + (R[0] - R[1])*(1 - cos(phi))) + (R[1] + (R[2] - R[1])*(1 - cos(psi)))*cos(beta[Groupnumber])) / sin(beta[Groupnumber]) + (R[2] - R[1])*sin(psi);
		if (T1 < 0 || T2 < 0)
		{
			QMessageBox::warning(this, QApplication::applicationName(), "Please change the angle between the lines or R2, otherwise arcs can not be drawn.");
			return;
		}
		bool clocky = true;
		int sig = 1;
		if (LineDir[Groupnumber * 2].x()*LineDir[Groupnumber * 2 + 1].y() - LineDir[Groupnumber * 2].y()*LineDir[Groupnumber * 2 + 1].x() < 0)// vectorproduct determines the orientation of arcs
		{
			sig = -1;
			clocky = false;
		}
		start0 = P[Groupnumber * 3 + 1] + T1*LineDir[Groupnumber * 2];
		end2 = P[Groupnumber * 3 + 1] + T2*LineDir[Groupnumber * 2 + 1];
		if (ral == false)// here we have our mistake
		{
			Y1 = t1[Groupnumber] * sin(alpha) + R[0] * cos(alpha);
			X1 = R[0] * sin(alpha) - t1[Groupnumber] * cos(alpha);
			ny = atan((R[2] - Y1) / (X1 - t2[Groupnumber]));
			M1M3 = (R[2] - Y1) / sin(ny);
			double etahelp = ((R[2] - R[1])*(R[2] - R[1]) - M1M3*M1M3 + (R[0] - R[1])*(R[0] - R[1])) / (2 * (R[2] - R[1])*(R[0] - R[1]));
			double deltahelp = ((R[2] - R[1])*(R[2] - R[1]) + M1M3*M1M3 - (R[0] - R[1])*(R[0] - R[1])) / (2 * M1M3*(R[2] - R[1]));
			if (std::abs(etahelp) > 1 || std::abs(deltahelp) > 1)
			{
				QMessageBox::warning(this, QApplication::applicationName(), "Please change the angle between the lines or R2, otherwise arcs can not be drawn.");
				return;
			}
			eta = acos(etahelp);
			delta = acos(deltahelp);
			epsilon = M_PI - eta - delta;
			psi = delta + ny - M_PI / 2;
			phi = alpha - eta - psi;
			start0 = P[Groupnumber * 3];
			end2 = P[Groupnumber * 3 + 2];
		}
		if (psi < 0 || phi < 0 || eta < 0)
		{
			QMessageBox::warning(this, QApplication::applicationName(), "Please change the angle between the lines or R2, otherwise arcs can not be drawn.");
			return;
		}
		start.push_back(start0);
		center.push_back(start[0] + R[0] * buw::createRotationMatrix<double>(sig*M_PI / 2)* LineDir[Groupnumber * 2]);
		end.push_back(center[0] + buw::createRotationMatrix<double>(-sig*phi)* (start[0] - center[0]));

		center2 = end2 + R[2] * buw::createRotationMatrix<double>(-sig*M_PI / 2)* LineDir[Groupnumber * 2 + 1];
		start2 = center2 + buw::createRotationMatrix<double>(sig*psi)* (end2 - center2);
		
		center.push_back(center[0] + (R[0] - R[1])*(end[0] - center[0]) / R[0]);
		start.push_back(end[0]);
		end.push_back(start2);

		start.push_back(start2);
		end.push_back(end2);
		center.push_back(center2);

		if (isIntersectionArcArc(center[1], center[2], R[1] + width, R[2] + width, message) == 0 || isIntersectionArcArc(center[0], center[1], R[0] + width, R[1] + width, message) == 0 ||
			areErrorsForParallelArc(R[0], width, message) == 0 || areErrorsForParallelArc(R[1], width, message) == 0 || areErrorsForParallelArc(R[2], width, message) == 0)
		{
			QMessageBox::warning(this, QApplication::applicationName(), QString::fromStdString(message));
			return;
		}
		for (int k = 0; k < 3; k++)
		{
			makeArc(center[k], start[k], end[k], clocky);
		}
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line1 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(start[0], P[Groupnumber * 3 + 1]);
		ha->addElement(line1);
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line2 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(P[Groupnumber * 3 + 1], end[2]);
		ha->addElement(line2);
		if (width > 0)
		{//  index of endi or starti : i%2==1 means inner and i%2==0 means outer
			endi[3] = center[1] + ((R[1] - width) / R[1])*(end[1] - center[1]);
			endi[5] = center[2] + ((R[2] - width) / R[2])*(end[2] - center[2]);
			starti[5] = center[2] + ((R[2] - width) / R[2])*(start[2] - center[2]);
			endi[4] = center[2] + ((R[2] + width) / R[2])*(end[2] - center[2]);
			makeOne3dLine(starti[5], endi[3]);	// line between the inner arc-ends
			// the next two lines are special parameters for GeneralLineArcArcArcLine 
			endi[4] = center[2] + ((R[2] + width) / R[2])*(end[2] - center[2]);
			starti[4] = endi[2] = computeIntersectionArcArc(center[1], center[2], R[1] + width, R[2] + width, clocky);
			GeneralLine_Arc_Arc_Arc_Line(3, Groupnumber, width, R[0], R[1], R[2], clocky, starti[4], endi[2], endi[4], oldEnd, end, start, center);
		}
		oldEnd.push_back(end[2]);
		oldEnd.push_back(endi[4]);
		oldEnd.push_back(endi[5]); // generates old values
	}
	make3DLine(ha);// middle that consists just of the connected alignment-points
}

void OpenInfraPlatform::UserInterface::CreateLineArcArcArcLineDialog::on_pushButtonCancel_clicked()
{
	hide();
}
