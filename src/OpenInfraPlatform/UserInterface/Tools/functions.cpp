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

#include "functions.h"

// many tools from the folder "tools" needed formulars from: Prof.Dr.-Ing M.Baeumker from Fachhochschule Bochum Skript: Rechenverfahren der Ingenieurvermessung

double iteration_ACA(double A, double R1, double R2)
{
	double L1, L2, tau1, tau2;
	compute_L_tau(L1, L2, tau1, tau2, A, A, R1, R2);// the next two formulars are from the view of a coordinatsystem in theostart
	return (buw::createRotationMatrix<double>(tau1)*buw::Vector2d(0, -R1) + relCloEnd(L2, A, 1) - relCloEnd(L1, A, 1) + buw::createRotationMatrix<double>(tau2) *buw::Vector2d(0.0,R2)).norm();
}

double iteration_ACCA(double A1, double A2, double R1, double R2)
{
	double L1, L2, tau1, tau2;
	compute_L_tau(L1, L2, tau1, tau2, A1, A2, R1, R2);
	return (R2*buw::createRotationMatrix<double>(M_PI / 2 + tau2)*buw::Vector2d(1.0, 0.0) + relCloEnd(L2, A2, 1) + relCloEnd(L1, A1, 1) + R1*buw::createRotationMatrix<double>(M_PI / 2 + tau1)*buw::Vector2d(1.0, 0.0)).norm();
}

buw::Vector2d relCloEnd(double L, double A, int sig)
{
	buw::Vector2d RelCloEnd;
	RelCloEnd.x() = buw::HorizontalAlignmentElement2DClothoid::computeX(L, A);
	RelCloEnd.y() = sig*buw::HorizontalAlignmentElement2DClothoid::computeY(L, A);
	return RelCloEnd;
}

void makeClothoid(double R1, double R2, double A, buw::Vector2d startPoint, buw::Vector2d cloth_start_dir, bool clockwise)
{	// if R1==0 it means R1==infinit. If R1!=0 startpoint means theoStartpoint so that startpoint has to be computed
	buw::Vector2d AbsCloEnd;
	double L1, L2, tau1, tau2;
	int sig = 1;// in mainwindow.cpp means sig==-1 that clockwise for clothoid is true
	if (clockwise == true)
	{
		sig = -1;
	}
	if (R1 == 0)
	{
		R1 = std::numeric_limits<double>::infinity();
		compute_L_tau(L1, L2, tau1, tau2, 0, A, 1.0, R2); // L1=tau1=0
		AbsCloEnd = absCloEnd(startPoint, cloth_start_dir, L2, A, sig);
	}
	else
	{
		swapThatLargerFirst(R1, R2);
		compute_L_tau(L1, L2, tau1, tau2, A, A, R1, R2);
		AbsCloEnd = absCloEnd(startPoint, cloth_start_dir, L2, A, sig);
		startPoint = absCloEnd(startPoint, cloth_start_dir, L1, A, sig);
	}
	double L = L2 - L1;
	buw::Vector2d startDir = buw::createRotationMatrix<double>(sig*tau1)*cloth_start_dir;
	buw::Vector2d endDir = buw::createRotationMatrix<double>(sig*tau2)*  cloth_start_dir;
	buw::Line2d line1(startPoint, startPoint + startDir);
	buw::Line2d line2(AbsCloEnd, AbsCloEnd - endDir);
	buw::Vector2d pi;
	auto PI = buw::computeIntersection(line1, line2, pi);
	buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid_old> c = std::make_shared<buw::HorizontalAlignmentElement2DClothoid_old>(
		startPoint,
		AbsCloEnd,
		pi,
		L,
		R1,
		R2,
		clockwise
		);
	buw::ReferenceCounted<buw::HorizontalAlignment2D> horizontalAlignment = std::make_shared<buw::HorizontalAlignment2D>();
	horizontalAlignment->addElement(c);
	buw::ReferenceCounted<buw::Alignment2DBased3D> a = std::make_shared<buw::Alignment2DBased3D>(horizontalAlignment);
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().addAlignment(a);
}

int are2Points(int size, std::string& message)
{
	if (size != 2)
	{
		message= "At first please create exactly two alignment-points and then call this function again";
		return 0;
	}
	else return 1;
}
int isClothoidInBorder(double tau1, double tau2, double border, std::string& message)
{
	if (std::abs(tau1) > border || std::abs(tau2) > border)
	{
		message= "Please change inserts, because otherwise clothoid can not be drawn.";
		return 0;
	}
	else return 1;
}
int isInsertNotZero(double Insert1, double Insert2, double Insert3, std::string& message)
{
	if ((Insert1 > 0 && Insert2 > 0 && Insert3 > 0) || Insert1 == 0 && Insert2 == 0 || Insert2 == 0 && Insert3 == 0 || Insert1 == 0 && Insert3 == 0 || Insert1<0 || Insert2<0 || Insert3<0)
	{
		message= "Please leave one insertion-field of the uppest area at 0.0.";
		return 0;
	}
	else return 1;
}
int isInsertZero(double V1, double V2, double V3, double V4, double V5, double V6, std::string& message)
{
	if (V1 <= 0 || V2 <= 0 || V3 <= 0 || V4 <= 0 || V5 <= 0 || V6 <= 0)
	{
		message= "Please insert at first values larger than zero in dialog.";
		return 0;
	}
	else return 1;
}
int isU1U2SmallerLength(double u1, double u2, double length2, std::string& message)
{
	if (u1 + u2 > length2 && length2>0)
	{
		message= "Please increase distance between alignment-point 2 and 3 or reduce u1 or u2.";
		return 0;
	}
	if (length2>0)
	{
		return isInsertZero(u1, u2, 1, 1, 1, 1, message);
	}
	else return 1;
}
int isU3U4SmallerLength(double u3, double u4, double length3, std::string& message)
{
	if (u3 + u4>length3 && length3>0)
	{
		message= "Please increase distance between alignment-point 4 and 5 or reduce u3 or u4.";
		return 0;
	}
	if (length3>0)
	{
		return isInsertZero(u3, u4, 1, 1, 1, 1, message);
	}
	else return 1;
}

int isAngleInBorders(double phi1, double  phi2, std::string& message)
{
	if (phi1 >= 2 * M_PI || phi2 >= 2 * M_PI || phi1 <= 0 || phi2 <= 0)
	{
		message= "Every angle has to be larger than 0 gon and smaller than 400 gon. One of your inserted angles is not in this intervall. Please correct.";
		return 0;
	}
	else return 1;
}
int are3_4or5Points(int size, std::string& message)
{
	if (size < 3 || size>5)
	{
		message= "At first please create three or four or five alignment-points and then call this function again";
		return 0;
	}
	else return 1;
}
int areErrorsForParallelClo(double L, double A, double width, double distance, bool UseNoLines, std::string& message)
{
	if ((distance < 0.00001 || distance >= L / 2) && UseNoLines == false && width>0)
	{
		message= "Please insert for step-distance a value larger than 0.00001 m but smaller than clothoidlength/2.";
		return 0;
	}
	if (width>(A*A / L))
	{
		message= "Please insert for carriageway-width a smaller value.";
		return 0;
	}
	else return 1;
}
int isIntersectionArcArc(buw::Vector2d rm1, buw::Vector2d rm2, double R1, double R2, std::string& message)
{
	double c = (rm2 - rm1).norm();
	if (c == 0)
	{
		message= "No correct computation possible, because arc-center 1 is identic with arc-center 2. Please change inserts and call function again.";
		return 0;
	}
	double bisX = (R1*R1 + c*c - R2*R2) / (2 * c);
	if ((R1*R1 - bisX*bisX) < 0 || c>R1 + R2 || R2>R1 + c || R1>R2 + c)
	{
		message= "No correct computation possible, because no intersection between arc 1 and arc 2. Please change inserts and call function again.";
		return 0;
	}
	else return 1;
}
int areErrorsForParallelArc(double Rmin, double width, std::string& message)
{
	if (width >= Rmin && width>0)
	{
		message= "Please insert for width a value smaller than the smallest radius.";
		return 0;
	}
	else return 1;
}
void swapThatLargerFirst(double &A, double &B)// swaps A with B if A<B
{
	if (A < B)
	{
		double swap = B;
		B = A;
		A = swap;
	}
}
buw::Vector2d computeIntersectionArcArc(buw::Vector2d rm1, buw::Vector2d rm2, double R1, double R2, bool clockofR1)
{	// formula of the following three lines adapted from walter bislins: walter.bislins.ch/blog/index.asp?page=Schnittpunkte+zweier+Kreise+berechnen+(JavaScript) 
	buw::Vector2d bisli, x_axis = { 1.0, 0.0 };	// the intersectionpoint of two arcs is computed by a coordinat-transformation. 
	double c = (rm2 - rm1).norm();
	bisli.x() = (R1*R1 + c*c - R2*R2) / (2 * c);
	bisli.y() = sqrt(R1*R1 - bisli.x()*bisli.x());// do not forget to use the function isIntersectionArcArc to search for wrong inserts
	if (clockofR1 == false)
	{
		bisli.y() = -bisli.y();
	}
	double rotat = buw::calculateAngleBetweenVectors(x_axis, buw::Vector2d(rm2 - rm1));
	return rm1 + buw::createRotationMatrix<double>(rotat)*bisli;
}

void make3DLine(buw::ReferenceCounted<buw::HorizontalAlignment2D> ha)
{
	buw::Vector2d vstart = buw::Vector2d(ha->getStartStation(), 0);
	buw::Vector2d vend = buw::Vector2d(ha->getStartStation() + ha->getLength(), 0);
	buw::ReferenceCounted<buw::VerticalAlignmentElement2DLine> v = std::make_shared<buw::VerticalAlignmentElement2DLine>(vstart, vend);
	buw::ReferenceCounted<buw::VerticalAlignment2D> va = std::make_shared<buw::VerticalAlignment2D>();
	va->addElement(v);
	buw::ReferenceCounted<buw::Alignment2DBased3D> alignment = std::make_shared<buw::Alignment2DBased3D>(ha, va);
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().addAlignment(alignment);
}

void compute_L_tau(double &L1, double &L2, double &tau1, double &tau2, double A1, double A2, double R1, double R2)
{
	L1 = A1*A1 / R1;
	L2 = A2*A2 / R2;
	tau1 = A1*A1 / (R1*R1 * 2);
	tau2 = A2*A2 / (R2*R2 * 2);
}

void give3Points(buw::Vector2d &Point1, buw::Vector2d &Point2, buw::Vector2d &Point3, buw::Vector2d &LineDir1,
	buw::Vector2d &LineDir2, double &angle, double &length12, double &length32, buw::Vector2d U, buw::Vector2d V, buw::Vector2d W, buw::Vector2d offset)
{
	Point1 = U + offset.block<2,1>(0,0);
	Point2 = V + offset.block<2,1>(0,0);
	Point3 = W + offset.block<2,1>(0,0);
	length12 = (U - V).norm();
	length32 = (W - V).norm();
	LineDir1 = (U - V) / length12;//goes from V to U
	LineDir2 = (W - V) / length32;//goes from V to W
	angle = buw::calculateAngleBetweenVectors(LineDir1, LineDir2);
	if (angle > M_PI)
	{
		angle = 2 * M_PI - angle;
	}
}
void parallelClo(buw::Vector2d &CloStartI, buw::Vector2d &CloStartO, double &Ri, double &Ro, double &Ai, double &Ao, double A, double width, double R, buw::Vector2d startPoint, buw::Vector2d cloth_start_dir, int sig)
{//  the following code is not equivalent to the formulars of Prof.Dr.-Ing M.Baeumker from Fachhochschule Bochum Skript: Rechenverfahren der Ingenieurvermessung
	//  the idea is to have the same tau for the parallels so that you do not need to search for the intersection of arc and line   tau=const=A*A/(2*R*R) if Ri=R-width we get Ai=A*Ri/R 
	// CloStart means the point where the clothoid starts// I for inside and O for outside
	buw::Vector2d endhelp, x_axis = { 1.0, 0.0 };
	double tau, L, Li, Lo;
	Ri = R - width;
	Ro = R + width;
	Ai = A*Ri / R;
	Ao = A*Ro / R;
	L = A*A / R;
	tau = L / (2 * R);
	Li = Ai*Ai / Ri;
	Lo = Ao*Ao / Ro;
	endhelp = width / cloth_start_dir.norm()*buw::createRotationMatrix<double>(sig* (M_PI / 2 + tau))*cloth_start_dir;
	CloStartI = absCloEnd(absCloEnd(startPoint, cloth_start_dir, L, A, sig) + endhelp, -cloth_start_dir, Li, Ai, sig);
	CloStartO = absCloEnd(absCloEnd(startPoint, cloth_start_dir, L, A, sig) - endhelp, -cloth_start_dir, Lo, Ao, sig);
}
void ClothByConnectLin(buw::Vector2d &CloPoI1, buw::Vector2d &CloPoI2, buw::Vector2d &CloPoO1, buw::Vector2d &CloPoO2, double &width, double &s, double &A, double &distance, int &sig, buw::Vector2d cloth_start_dir, buw::Vector2d &startPoint)
{
	buw::Vector2d point1, point2, point3, point4, pointdir1, pointdir2;
	double norm1, norm2, delta = 0.00000001;
	point1 = absCloEnd(startPoint, cloth_start_dir, s, A, sig);
	point3 = absCloEnd(startPoint, cloth_start_dir, s + delta, A, sig);
	pointdir1 = point3 - point1;
	norm1 = (point3 - point1).norm();
	CloPoI1 = point1 + sig*width / norm1*buw::createRotationMatrix<double>(M_PI / 2)*pointdir1;
	CloPoO1 = point1 - sig* width / norm1*buw::createRotationMatrix<double>(M_PI / 2)*pointdir1;
	point2 = absCloEnd(startPoint, cloth_start_dir, s + distance, A, sig);
	point4 = absCloEnd(startPoint, cloth_start_dir, s + distance + delta, A, sig);
	pointdir2 = point4 - point2;
	norm2 = (point4 - point2).norm();
	CloPoI2 = point2 + sig* width / norm2*buw::createRotationMatrix<double>(M_PI / 2)*pointdir2;
	CloPoO2 = point2 - sig* width / norm2*buw::createRotationMatrix<double>(M_PI / 2)*pointdir2;
}

void insertA_for_ACCA2(double &AA1, double &AA2, double &A1, double &A2, double &Atest)
{
	if (AA1 == 0)
	{
		A1 = Atest;
	}
	if (AA2 == 0)
	{
		A2 = Atest;
	}
}

buw::Vector2d absCloEnd(buw::Vector2d startPoint, buw::Vector2d cloth_start_dir, double L, double A, int sig)
{
	buw::Vector2d RelCloEnd, x_axis = { 1.0, 0.0 };
	double lineangle = buw::calculateAngleBetweenVectors(x_axis, cloth_start_dir);
	return startPoint + buw::createRotationMatrix<double>(lineangle)*relCloEnd(L, A, sig);
}

void give2Points(buw::Vector2d &point1, buw::Vector2d &point2, buw::Vector2d &direction, buw::Vector2d A, buw::Vector2d B, buw::Vector2d offset)
{
	point1 = A + offset;
	point2 = B + offset;
	direction = B - A;// from A to B
}

void makeArc(buw::Vector2d center, buw::Vector2d start, buw::Vector2d end, bool clocky)
{
	buw::ReferenceCounted<buw::HorizontalAlignmentElement2DArc> arc = std::make_shared<buw::HorizontalAlignmentElement2DArc>(
		center,
		start,
		end,
		clocky);
	buw::ReferenceCounted<buw::HorizontalAlignment2D> horizontalAlignment = std::make_shared<buw::HorizontalAlignment2D>();
	horizontalAlignment->addElement(arc);
	buw::ReferenceCounted<buw::Alignment2DBased3D> arc_a = std::make_shared<buw::Alignment2DBased3D>(horizontalAlignment);
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().addAlignment(arc_a);
}
void makePizza(buw::Vector2d start1, buw::Vector2d start2, buw::Vector2d end1, buw::Vector2d end2, buw::Vector2d center1, buw::Vector2d center2)
{
	makeOne3dLine(start1, center1);
	makeOne3dLine(end1, center1);
	makeOne3dLine(start2, center2);
	makeOne3dLine(end2, center2);
}

void make2ClothByConnectLin(double loopstart, double loopend, double distance, double A, double width, buw::Vector2d startPoint, buw::Vector2d  cloth_start_dir, int sig, buw::Vector2d LastCloPoI, buw::Vector2d  LastCloPoO)
{
	buw::Vector2d CloPoI1, CloPoI2, CloPoO1, CloPoO2;
	buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line1, line2;
	buw::ReferenceCounted<buw::HorizontalAlignment2D> ha1 = std::make_shared<buw::HorizontalAlignment2D>();
	buw::ReferenceCounted<buw::HorizontalAlignment2D> ha2 = std::make_shared<buw::HorizontalAlignment2D>();
	for (double s = loopstart; s <= loopend; s += distance)
	{
		ClothByConnectLin(CloPoI1, CloPoI2, CloPoO1, CloPoO2, width, s, A, distance, sig, cloth_start_dir, startPoint);
		line1 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(CloPoI1, CloPoI2);
		ha1->addElement(line1);// innerline
		line2 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(CloPoO1, CloPoO2);
		ha2->addElement(line2);// outerline  
	}
	line1 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(CloPoI2, LastCloPoI);// innerline
	line2 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(CloPoO2, LastCloPoO);// outerline 
	ha1->addElement(line1);// innerline
	ha2->addElement(line2);// outerline 
	make3DLine(ha1);
	make3DLine(ha2);
}

void makeOne3dLine(buw::Vector2d &start1, buw::Vector2d &start2)
{
	buw::ReferenceCounted<buw::HorizontalAlignment2D> ha1 = std::make_shared<buw::HorizontalAlignment2D>();
	buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line1 = std::make_shared<buw::HorizontalAlignmentElement2DLine>(start1, start2);
	ha1->addElement(line1);
	make3DLine(ha1);
}
void GeneralLine_Arc_Arc_Arc_Line(int ArcNumber, int Groupnumber, double width, double R1, double R2, double R3, bool clocky,
	buw::Vector2d starti5, buw::Vector2d endi3, buw::Vector2d endi5, std::vector<buw::Vector2d> oldEnd, std::vector<buw::Vector2d> end, std::vector<buw::Vector2d> start, std::vector<buw::Vector2d> center)
{
	double R[3];
	buw::Vector2d starti[6], endi[6];
	starti[4] = starti5, endi[2] = endi3, endi[4] = endi5;
	R[0] = R1, R[1] = R2, R[2] = R3;
	for (int k = 0; k < ArcNumber; k++)// inside
	{
		int y = 2 * k + 1;
		endi[y] = center[k] + ((R[k] - width) / R[k])*(end[k] - center[k]);
		starti[y] = center[k] + ((R[k] - width) / R[k])*(start[k] - center[k]);
	}//  index of endi or starti : i%2==1 means inner and i%2==0 means outer
	starti[0] = center[0] + ((R[0] + width) / R[0])*(start[0] - center[0]);// outside
	endi[0] = starti[2] = computeIntersectionArcArc(center[0], center[1], R[0] + width, R[1] + width, clocky);
	if (Groupnumber == 0)
	{
		makeOne3dLine(starti[3], endi[1]);
	}
	else
	{
		makeOne3dLine(starti[3], endi[1]);
		makeOne3dLine(starti[0], oldEnd[0]);// middle
		makeOne3dLine(starti[1], oldEnd[1]);// innerline
		makeOne3dLine(starti[0], oldEnd[2]);// outerline  
	}
	for (int ir = 0; ir < (2 * ArcNumber); ir++)
	{
		int k = (ir / 2) % 3;// K=0,0,1,1...
		makeArc(center[k], starti[ir], endi[ir], clocky);
	}
}

void GeneralArcClothoidArc(buw::Vector2d cloth_start_dir, buw::Vector2d theostartPoint, bool clockClo, buw::Vector2d center1,
	buw::Vector2d center2, buw::Vector2d start1, buw::Vector2d start2, buw::Vector2d end1, buw::Vector2d end2, double width, double distance, bool Radius1, double sig, double A, double R1, double R2)
{
	buw::Vector2d CloPoO1, CloPoI1, CloPoO2, CloPoI2, end[2], center[2], CloStartI, CloStartO, start[2];
	double  R[2], L[2], tau[2], sigi = 1;
	start[0] = start1, start[1] = start2, end[0] = end1, center[0] = center1, end[1] = end2, center[1] = center2, R[0] = R1, R[1] = R2;
	compute_L_tau(L[0], L[1], tau[0], tau[1], A, A, R[0], R[1]);
	makeClothoid(R[0], R[1], A, theostartPoint, cloth_start_dir, clockClo);
	for (int i = 0; i < 2; i++)
	{
		makeArc(center[i], start[i], end[i], false);
	}
	makePizza(start[0], start[1], end[0], end[1], center[0], center[1]);
	if (width > 0)
	{
		if (sig > 0)
		{
			double loopend = L[1] - distance - 0.00000001;
			buw::Vector2d LastCloPoI = start[1] + width*buw::createRotationMatrix<double>(tau[1] + M_PI / 2)*cloth_start_dir;
			buw::Vector2d LastCloPoO = start[1] - width*buw::createRotationMatrix<double>(tau[1] + M_PI / 2)*cloth_start_dir;
			make2ClothByConnectLin(L[0], loopend, distance, A, width, theostartPoint, cloth_start_dir, sig, LastCloPoI, LastCloPoO);
		}
		else
		{
			double loopend = L[0] - distance - 0.00000001;
			buw::Vector2d LastCloPoI = end[0] + width*buw::createRotationMatrix<double>(-tau[0] - M_PI / 2)*cloth_start_dir;
			buw::Vector2d LastCloPoO = end[0] - width*buw::createRotationMatrix<double>(-tau[0] - M_PI / 2)*cloth_start_dir;
			make2ClothByConnectLin(L[1], loopend, distance, A, width, theostartPoint, cloth_start_dir, sig, LastCloPoI, LastCloPoO);
		}
		for (int j = 0; j < 2; j++)// here the inner and outer arcs are created
		{
			for (int k = 0; k < 2; k++)
			{
				buw::Vector2d starti = center[j] + ((R[j] + sigi*width) / R[j])*(start[j] - center[j]);
				buw::Vector2d endi = center[j] + ((R[j] + sigi*width) / R[j])*(end[j] - center[j]);
				makeArc(center[j], starti, endi, false);
				sigi = -sigi;
			}
		}
	}
}

void GeneralArcClothoidClothoidArc(buw::Vector2d cloth_dir, buw::Vector2d startPoint, buw::Vector2d end1, buw::Vector2d center1,
	buw::Vector2d end2, buw::Vector2d center2, double width, double distance, bool UseNoLines, int sig, double phi1, double phi2, double A1, double A2, double R1, double R2)
{
	buw::Vector2d end[2], center[2], CloStartI, CloStartO, x_axis = { 1.0, 0.0 }, start[2];
	double  Ri, Ro, Ai, Ao, R[2], L[2], tau[2], A[2], phi[2], sigu = 1;
	end[0] = end1, end[1] = end2, center[0] = center1, center[1] = center2, phi[0] = phi1, phi[1] = phi2, A[0] = A1, A[1] = A2, R[0] = R1, R[1] = R2;
	compute_L_tau(L[0], L[1], tau[0], tau[1], A[0], A[1], R[0], R[1]);
	bool clockArc = true, clockClo = false;
	if (sig == -1)
	{
		clockArc = false;
		clockClo = true;
	}
	for (int i = 0; i < 2; i++)
	{
		start[i] = center[i] + buw::createRotationMatrix<double>(sig*phi[i])*(end[i] - center[i]);
		makeClothoid(0.0, R[i], A[i], startPoint, -sigu*cloth_dir, clockClo);
		makeArc(center[i], start[i], end[i], clockArc);
		sigu = -sigu;
	}
	makePizza(start[0], start[1], end[0], end[1], center[0], center[1]);
	if (width > 0)
	{
		buw::ReferenceCounted<buw::HorizontalAlignment2D> ha1 = std::make_shared<buw::HorizontalAlignment2D>();
		buw::ReferenceCounted<buw::HorizontalAlignment2D> ha2 = std::make_shared<buw::HorizontalAlignment2D>();
		for (int k = 0; k < 2; k++)// this loop goes from clothoid 1 to clothoid 2
		{
			if (UseNoLines == true)
			{
				parallelClo(CloStartI, CloStartO, Ri, Ro, Ai, Ao, A[k], width, R[k], startPoint, -sigu*cloth_dir, sig);
				makeClothoid(0.0, Ri, Ai, CloStartI, -sigu*cloth_dir, clockClo);
				makeClothoid(0.0, Ro, Ao, CloStartO, -sigu*cloth_dir, clockClo);
			}
			else
			{
				double loopend = L[k] - distance - 0.00000001;
				double start_angle = buw::calculateAngleBetweenVectors(x_axis, buw::Vector2d(-sigu*cloth_dir));
				buw::Vector2d p_endhelp = width*buw::createRotationMatrix<double>(start_angle + sig* (M_PI / 2 + tau[k]))*x_axis;
				buw::Vector2d LastCloPoI = end[k] + p_endhelp;
				buw::Vector2d LastCloPoO = end[k] - p_endhelp;
				make2ClothByConnectLin(0,loopend, distance, A[k], width, startPoint, -sigu*cloth_dir, sig, LastCloPoI, LastCloPoO);
			}
			for (int j = 0; j < 2; j++)
			{
				buw::Vector2d starti = center[k] + ((R[k] + sigu*width) / R[k])*(start[k] - center[k]);
				buw::Vector2d endi = center[k] + ((R[k] + sigu*width) / R[k])*(end[k] - center[k]);
				makeArc(center[k], starti, endi, clockArc);
				sigu = -sigu;
			}
			sigu = -sigu;
		}
	}
}


