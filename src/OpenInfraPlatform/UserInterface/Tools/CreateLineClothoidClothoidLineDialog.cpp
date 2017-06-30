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

#include "CreateLineClothoidClothoidLineDialog.h"

OpenInfraPlatform::UserInterface::CreateLineClothoidClothoidLineDialog::CreateLineClothoidClothoidLineDialog(QWidget *parent /*= nullptr*/) :
ui_(new Ui::CreateLineClothoidClothoidLine),
QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint)

{
	ui_->setupUi(this);
	ui_->labelPicture->setPixmap(QPixmap(":/LCCL.svg"));
	ui_->labelPicture->show();	
}

OpenInfraPlatform::UserInterface::CreateLineClothoidClothoidLineDialog::~CreateLineClothoidClothoidLineDialog()
{

}

void OpenInfraPlatform::UserInterface::CreateLineClothoidClothoidLineDialog::changeEvent(QEvent* evt) 
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

void OpenInfraPlatform::UserInterface::CreateLineClothoidClothoidLineDialog::on_pushButtonGenerate_clicked()
{
	hide();
	double Ri, Ro, Ai, Ao, dummy[2], angle, A[2], AA[2], R = 0, RR, L[2], tau[2], gamma = 0, t1 = 0, t2 = 0, T1 = 0, T2 = 0, width, distance;
	bool clocky[2], UseNoLines = false;
	std::string message;
	buw::Vector2d U, V, W, LineDir[2], CloStartI[2], CloStartO[2], startPoint[2], oldEnd[3], RelCloEnd1, RelCloEnd2, x_axis = { 1.0, 0.0 };
	buw::ReferenceCounted<buw::HorizontalAlignment2D> ha = std::make_shared<buw::HorizontalAlignment2D>();
	buw::ReferenceCounted<buw::HorizontalAlignment2D> ha1 = std::make_shared<buw::HorizontalAlignment2D>();
	buw::ReferenceCounted<buw::HorizontalAlignment2D> ha2 = std::make_shared<buw::HorizontalAlignment2D>();
	buw::ReferenceCounted<buw::HorizontalAlignment2D> haSwap = std::make_shared<buw::HorizontalAlignment2D>();
	QString s = ui_->lineEdit_R->text();
	RR = s.toDouble();
	s = ui_->lineEdit_A1->text();
	AA[0] = s.toDouble();
	s = ui_->lineEdit_A2->text();
	AA[1] = s.toDouble();
	s = ui_->lineEdit_d_2->text();
	distance = s.toDouble();
	s = ui_->lineEdit_c_2->text();
	width = s.toDouble();

	if (isInsertNotZero(AA[1], RR, AA[0],message) == 0)
	{
		QMessageBox::warning(this, QApplication::applicationName(), QString::fromStdString(message));
		return;
	}
	if (points_.size() < 3)
	{
		QMessageBox::warning(this, QApplication::applicationName(), "At first please create at least three alignment-points and then call this function again");
		return;
	}
	for (int Groupnumber = 0; Groupnumber < points_.size() - 2; Groupnumber++)
	{
		give3Points(U, V, W, LineDir[0], LineDir[1], angle, dummy[0], dummy[1], points_[Groupnumber].block<2,1>(0,0), points_[Groupnumber + 1].block<2,1>(0,0), points_[Groupnumber + 2].block<2,1>(0,0), offset_.block<2,1>(0,0));
		gamma = M_PI - angle;
		if (AA[1] == 0)	// userinterface give A[0] and A[1] or A[0] and R // see page 35
		{
			A[0] = AA[0];
			R = RR;
			L[0] = A[0] * A[0] / R;
			tau[0] = L[0] / (2 * R);
			tau[1] = gamma - tau[0];
			A[1] = R*sqrt(2 * tau[1]);
			L[1] = R*(2 * tau[1]);
		}
		if (AA[0] == 0)
		{
			A[1] = AA[1];
			R = RR;
			L[1] = A[1] * A[1] / R;
			tau[1] = L[1] / (2 * R);
			tau[0] = gamma - tau[1];
			A[0] = R*sqrt(2 * tau[0]);
			L[0] = R*(2 * tau[0]);
		}
		if (RR == 0)
		{
			A[0] = AA[0];
			A[1] = AA[1];
			R = sqrt((A[0] * A[0] + A[1] * A[1]) / (2 * gamma));
			compute_L_tau(L[0], L[1], tau[0], tau[1], A[0], A[1], R, R);
		}
		RelCloEnd1 = relCloEnd(L[0], A[0], 1);
		RelCloEnd2 = relCloEnd(L[1], A[1], 1);
		double Tk1 = RelCloEnd1.y() / sin(tau[0]);
		double Tk2 = RelCloEnd2.y() / sin(tau[1]);
		double a1 = (Tk1 + Tk2)*sin(tau[1]) / sin(gamma);
		double a2 = (Tk1 + Tk2)*sin(tau[0]) / sin(gamma);
		t1 = RelCloEnd1.x() - Tk1*  cos(tau[0]);
		t2 = RelCloEnd2.x() - Tk2* cos(tau[1]);
		T1 = t1 + a1;
		T2 = t2 + a2;
		startPoint[0] = V + T1*LineDir[0];
		startPoint[1] = V + T2*LineDir[1];
		int sig = -1;
		clocky[0] = true, clocky[1] = false;
		if (LineDir[0].x()*LineDir[1].y() - LineDir[0].y()*LineDir[1].x() < 0)// vectorproduct determines the orientation of the clothoids
		{
			clocky[0] = false;
			clocky[1] = true;
			sig = 1;
		}				// draw the clothoids 
		if (isClothoidInBorder(tau[1], tau[0], M_PI, message) == 0 || areErrorsForParallelClo(L[0], A[0], width, distance, UseNoLines, message) == 0 || areErrorsForParallelClo(L[1], A[1], width, distance, UseNoLines, message) == 0)
		{
			QMessageBox::warning(this, QApplication::applicationName(), QString::fromStdString(message));
			return;
		}
		makeClothoid(0.0, R, A[0], startPoint[0], -LineDir[0], clocky[0]);
		makeClothoid(0.0, R, A[1], startPoint[1], -LineDir[1], clocky[1]);
		if (Groupnumber > 0)
		{
			buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line = std::make_shared<buw::HorizontalAlignmentElement2DLine>(oldEnd[0], startPoint[0]);// middle
			ha->addElement(line);
		}
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
				if (Groupnumber > 0 && i == 0)
				{
					buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line1 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(oldEnd[1], CloStartI[0]);
					ha1->addElement(line1);// innerline
					buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line2 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(oldEnd[2], CloStartO[0]);
					ha2->addElement(line2);// outerline  
				}
				if (UseNoLines == true)
				{
					parallelClo(CloStartI[i], CloStartO[i], Ri, Ro, Ai, Ao, A[i], width, R, startPoint[i], -LineDir[i], sig);// creates CloStartI and CloStartO
					makeClothoid(0.0, Ri, Ai, CloStartI[i], -LineDir[i], clocky[i]);
					makeClothoid(0.0, Ro, Ao, CloStartO[i], -LineDir[i], clocky[i]);
				}
				else
				{
					buw::Vector2d CloPoO1, CloPoI1, CloPoO2, CloPoI2;
					double loopend = L[i] - distance - 0.00000001;
					if (i == 0)
					{
						for (double s = 0.0; s <= loopend; s += distance)
						{
							ClothByConnectLin(CloPoI1, CloPoI2, CloPoO1, CloPoO2, width, s, A[i], distance, sig, -LineDir[i], startPoint[i]);
							line1 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(CloPoI1, CloPoI2);// innerline 
							ha1->addElement(line1);// innerline  
							line2 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(CloPoO1, CloPoO2); // outerline
							ha2->addElement(line2);// outerline
						}
					}
					else
					{
						for (double s = loopend; s >= 0.0; s -= distance)
						{
							ClothByConnectLin(CloPoI1, CloPoI2, CloPoO1, CloPoO2, width, s, A[i], distance, sig, -LineDir[i], startPoint[i]);
							line1 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(CloPoI2, CloPoI1);// innerline 
							ha1->addElement(line1);// innerline  
							line2 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(CloPoO2, CloPoO1); // outerline
							ha2->addElement(line2);// outerline
						}
						line1 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(CloPoI1, CloStartI[i]);// innerline  
						line2 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(CloPoO1, CloStartO[i]);// outerline
						ha1->addElement(line1);// innerline  
						ha2->addElement(line2);// outerline
					}
				}
				sig = -sig;// attention sig has to change for every clothoid
			}
		}// end of if width
		oldEnd[0] = startPoint[1];
		oldEnd[1] = CloStartO[1];
		oldEnd[2] = CloStartI[1]; // generates old values
		haSwap = ha2;
		ha2 = ha1;
		ha1 = haSwap;
	}// end of for
	make3DLine(ha);// middle
	if (width > 0)
	{
		make3DLine(ha1);
		make3DLine(ha2);
	}
}

void OpenInfraPlatform::UserInterface::CreateLineClothoidClothoidLineDialog::on_pushButtonCancel_clicked()
{
	hide();
}