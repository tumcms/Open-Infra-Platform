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

#include "CreateLineArcArcLineDialog.h"

OpenInfraPlatform::UserInterface::CreateLineArcArcLineDialog::CreateLineArcArcLineDialog(QWidget *parent /*= nullptr*/) :
	ui_(new Ui::CreateLineArcArcLine),
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint)

{
	ui_->setupUi(this);
	ui_->labelPicture->setPixmap(QPixmap(":/LAAL.svg"));
	ui_->labelPicture->show();
}

OpenInfraPlatform::UserInterface::CreateLineArcArcLineDialog::~CreateLineArcArcLineDialog()
{

}

void OpenInfraPlatform::UserInterface::CreateLineArcArcLineDialog::changeEvent(QEvent* evt) 
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

void OpenInfraPlatform::UserInterface::CreateLineArcArcLineDialog::on_pushButtonGenerate_clicked()
{
	hide();
	buw::Vector2d P[9], LineDir[6], starti[6], endi[6];
	std::vector<buw::Vector2d> oldEnd, end, start, center;
	// very important is to determine between RR1 and R[0] 
	double beta[3], t1[3], t2[3], R[2], RR2, RR1, alpha = 0, YM1 = 0, X1 = 0, YM2 = 0, X2 = 0, phi = 0, psi = 0;
	double width, u1, u2, u3, u4;
	bool first;
	std::string message;
	QString s = ui_->lineEdit_R1->text();
	RR1 = s.toDouble();
	s = ui_->lineEdit_R2->text();
	RR2 = s.toDouble();
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
	if (ui_->radioButton_first->isChecked())
	{
		first = true;
	}
	if (ui_->radioButton_last->isChecked())
	{
		first = false;
	}
	buw::ReferenceCounted<buw::HorizontalAlignment2D> ha = std::make_shared<buw::HorizontalAlignment2D>();
	if (are3_4or5Points(points_.size(), message) == 0 || (points_.size() > 3 && (isInsertNotZero(RR1, RR2, 1, message) == 0 || isU3U4SmallerLength(u3, u4, t1[2], message) == 0 || isU1U2SmallerLength(u1, u2, t1[1], message) == 0)))
	{
		QMessageBox::warning(this, QApplication::applicationName(), QString::fromStdString(message));
		return;
	}
	give3Points(P[0], P[1], P[2], LineDir[0], LineDir[1], beta[0], t1[0], t2[0], points_[0].block<2, 1>(0, 0), points_[1].block<2,1>(0,0), points_[2].block<2, 1>(0, 0), offset_);
	if (points_.size() > 3)
	{
		give3Points(P[3], P[4], P[5], LineDir[2], LineDir[3], beta[1], t1[1], t2[1], points_[1].block<2, 1>(0, 0), points_[2].block<2, 1>(0, 0), points_[3].block<2,1>(0,0), offset_);
		t2[0] = u1, t1[1] = u2, P[2] = P[1] + u1*LineDir[1], P[3] = P[4] + u2*LineDir[2];
	}
	if (points_.size() > 4)
	{
		give3Points(P[6], P[7], P[8], LineDir[4], LineDir[5], beta[2], t1[2], t2[2], points_[2].block<2,1>(0,0), points_[3].block<2,1>(0,0), points_[4].block<2,1>(0,0), offset_);
		t2[0] = u1, t1[1] = u2, P[2] = P[1] + u1*LineDir[1], P[3] = P[4] + u2*LineDir[2];
		t2[1] = u3, t1[2] = u4, P[5] = P[3] + u3*LineDir[3], P[6] = P[7] + u4*LineDir[5];
	}
	buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line1 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(P[0], P[1]);
	ha->addElement(line1);
	for (int Groupnumber = 0; Groupnumber < points_.size() - 2; Groupnumber++)
	{
		alpha = M_PI - beta[Groupnumber];
		if (RR1 == 0)
		{
			YM2 = t2[Groupnumber] * sin(alpha) + RR2 * cos(alpha);
			X2 = -t2[Groupnumber] * cos(alpha) + RR2 * sin(alpha);
			phi = 2 * atan((YM2 - RR2) / (t1[Groupnumber] - X2));
			R[0] = RR2 + (t1[Groupnumber] - X2) / sin(phi);
		}
		if (RR1 != 0 && RR2 != 0 && first == false)
		{
			R[0] = RR1;
			phi = acos((RR1 - t2[Groupnumber] * sin(alpha) - RR2*cos(alpha)) / (RR1 - RR2));
			t1[Groupnumber] = (RR1 - RR2)*sin(phi) + RR2*sin(alpha) - t2[Groupnumber] * cos(alpha);
		}
		psi = alpha - phi;
		R[1] = RR2;
		if (RR2 == 0)
		{
			R[0] = RR1;
			YM1 = t1[Groupnumber] * sin(alpha) + R[0] * cos(alpha);
			X1 = R[0] * sin(alpha) - t1[Groupnumber] * cos(alpha) - t2[Groupnumber];
			psi = 2 * atan((-YM1 + R[0]) / X1);
			R[1] = R[0] - X1 / sin(psi);
		}
		if (RR1 != 0 && RR2 != 0 && first == true)
		{
			R[0] = RR1;
			R[1] = RR2;
			psi = acos((t1[Groupnumber] * sin(alpha) + RR1*cos(alpha) - RR2) / (RR1 - RR2));
			t2[Groupnumber] = RR1*sin(alpha) - t1[Groupnumber] * cos(alpha) - (RR1 - RR2)*sin(psi);
		}
		phi = alpha - psi;
		if (psi < 0 || phi < 0)
		{
			QMessageBox::warning(this, QApplication::applicationName(), "Change the angle between the lines, otherwise one arclength would be negativ.");
			return;
		}
		bool clocky = true;
		int sig = 1;
		if (LineDir[Groupnumber * 2].x()*LineDir[Groupnumber * 2 + 1].y() - LineDir[Groupnumber * 2].y()*LineDir[Groupnumber * 2 + 1].x() < 0)// vectorproduct determines the orientation of arcs
		{
			clocky = false;
			sig = -1;
		}
		start.push_back(P[Groupnumber * 3]);
		center.push_back(start[0] + R[0] * buw::createRotationMatrix<double>(sig*M_PI / 2)* LineDir[Groupnumber * 2]);
		end.push_back(center[0] + buw::createRotationMatrix<double>(-sig*phi)* (start[0] - center[0]));
		end.push_back(P[Groupnumber * 3 + 2]);
		center.push_back(end[1] + R[1] * buw::createRotationMatrix<double>(-sig*M_PI / 2)* LineDir[Groupnumber * 2 + 1]);
		start.push_back(center[1] + buw::createRotationMatrix<double>(sig*psi)* (end[1] - center[1]));
		if (isIntersectionArcArc(center[0], center[1], R[0] + width, R[1] + width, message) == 0 || areErrorsForParallelArc(R[0], width, message) == 0 || areErrorsForParallelArc(R[1], width, message) == 0)
		{
			QMessageBox::warning(this, QApplication::applicationName(), QString::fromStdString(message));
			return;
		}
		for (int k = 0; k < 2; k++)
		{
			makeArc(center[k], start[k], end[k], clocky);
		}
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line2 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(P[Groupnumber * 3 + 1], P[Groupnumber * 3 + 2]);
		ha->addElement(line2);
		if (width > 0)
		{//  index of endi or starti : i%2==1 means inner and i%2==0 means outer
			endi[2] = center[1] + ((R[1] + width) / R[1])*(end[1] - center[1]);// outside
			endi[3] = center[1] + ((R[1] - width) / R[1])*(end[1] - center[1]);
			endi[2] = center[1] + ((R[1] + width) / R[1])*(end[1] - center[1]);// this line creates a special parameters for GeneralLineArcArcArcLine 
			GeneralLine_Arc_Arc_Arc_Line(2, Groupnumber, width, R[0], R[1], R[1], clocky, starti[4], endi[2], endi[4], oldEnd, end, start, center);
		}
		oldEnd.push_back(end[1]);
		oldEnd.push_back(endi[2]);
		oldEnd.push_back(endi[3]); // generates old values
	}
	make3DLine(ha);// middle that consists just of the connected alignment-points
}

void OpenInfraPlatform::UserInterface::CreateLineArcArcLineDialog::on_pushButtonCancel_clicked()
{
	hide();
}
