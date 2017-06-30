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

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#pragma once

#include "OpenInfraPlatform/DataManagement/Data.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid_old.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment2DBased3D.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DArc.h"
#include <QApplication>
#include <QDialog>

buw::Vector2d relCloEnd(double L, double A, int sig);
buw::Vector2d absCloEnd(buw::Vector2d startPoint, buw::Vector2d cloth_start_dir, double L, double A, int sig);
buw::Vector2d computeIntersectionArcArc(buw::Vector2d rm1, buw::Vector2d rm2, double R1, double R2, bool clockofR1);
int isClothoidInBorder(double tau1, double tau2, double border, std::string&);
int isU1U2SmallerLength(double u1, double u2, double length2, std::string&);
int isU3U4SmallerLength(double u3, double u4, double length3, std::string&);
int are2Points(int size, std::string&);
int are3_4or5Points(int size, std::string&);
int isIntersectionArcArc(buw::Vector2d rm1, buw::Vector2d rm2, double R1, double R2, std::string&);
int isAngleInBorders(double phi1, double phi2, std::string&);
int isInsertNotZero(double Insert1, double Insert2, double Insert3, std::string&);
int areErrorsForParallelArc(double Rmin, double width, std::string&);
int isInsertZero(double V1, double V2, double V3, double V4, double V5, double V6, std::string&);
int areErrorsForParallelClo(double L, double A, double width, double distance, bool UseNoLines, std::string&);
void insertA_for_ACCA2(double &AA1, double &AA2, double &A1, double &A2, double &Atest);
void make2ClothByConnectLin(double, double, double, double, double, buw::Vector2d, buw::Vector2d, int, buw::Vector2d, buw::Vector2d);
void make3DLine(buw::ReferenceCounted<buw::HorizontalAlignment2D> ha);
void makeClothoid(double R1, double R2, double A, buw::Vector2d startPoint, buw::Vector2d cloth_start_dir, bool clockwise);
void makeArc(buw::Vector2d, buw::Vector2d, buw::Vector2d, bool);
void compute_L_tau(double &, double &, double &, double &, double, double, double, double);
void give2Points(buw::Vector2d &, buw::Vector2d &, buw::Vector2d &, buw::Vector2d, buw::Vector2d, buw::Vector2d);
void give3Points(buw::Vector2d &, buw::Vector2d &, buw::Vector2d &, buw::Vector2d &, buw::Vector2d &, double &, double &, double &, buw::Vector2d, buw::Vector2d, buw::Vector2d, buw::Vector2d);
void ClothByConnectLin(buw::Vector2d &, buw::Vector2d &, buw::Vector2d &, buw::Vector2d &, double&, double&, double&, double&, int&, buw::Vector2d, buw::Vector2d&);
void parallelClo(buw::Vector2d &, buw::Vector2d &, double &, double &, double &, double &, double, double, double, buw::Vector2d, buw::Vector2d, int);
void GeneralArcClothoidArc(buw::Vector2d, buw::Vector2d, bool, buw::Vector2d, buw::Vector2d, buw::Vector2d, buw::Vector2d, buw::Vector2d, buw::Vector2d, double, double, bool, double, double, double, double);
void GeneralArcClothoidClothoidArc(buw::Vector2d, buw::Vector2d, buw::Vector2d, buw::Vector2d, buw::Vector2d, buw::Vector2d, double, double, bool, int, double, double, double, double, double, double);
void GeneralLine_Arc_Arc_Arc_Line(int, int, double, double, double, double, bool, buw::Vector2d, buw::Vector2d, buw::Vector2d, std::vector<buw::Vector2d>, std::vector<buw::Vector2d>, std::vector<buw::Vector2d>, std::vector<buw::Vector2d>);
void makePizza(buw::Vector2d start1, buw::Vector2d start2, buw::Vector2d end1, buw::Vector2d end2, buw::Vector2d center1, buw::Vector2d center2);
void makeOne3dLine(buw::Vector2d &start1, buw::Vector2d &start2);
void swapThatLargerFirst(double &A, double &B);
double iteration_ACA(double, double, double);
double iteration_ACCA(double, double, double, double);

#endif
