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


//#include "ifcgears/model/shared_ptr.h"
#include "IfcBridgeParamter.h"
#include <iostream>
#include <stdio.h>
#include <string>

IfcBridgeParamter::IfcBridgeParamter(const bridgeDescription& bd)
{
	this->length = bd.length;
	this->width = bd.width;
	this->thickness = this->length/30;
	overlapAbutmentDeck = 5;
	
	start_point.coordinates[0] = 0;
	start_point.coordinates[1] = 0;
	start_point.coordinates[2] = 0;

	std::cout<<start_point.coordinates[0]<<std::endl;

	end_point.coordinates[0] = this->length;
	end_point.coordinates[1] = 0.0;
	end_point.coordinates[2] = 0.0;
	
	
	foundationPointStart.coordinates[0] = start_point.coordinates[0] + overlapAbutmentDeck;
	foundationPointStart.coordinates[1] = 0.0;
	foundationPointStart.coordinates[2] = -20.0;

	foundationPointEnd.coordinates[0] = end_point.coordinates[0] - overlapAbutmentDeck;
	foundationPointEnd.coordinates[1] = 0.0;
	foundationPointEnd.coordinates[2] = -20.0;

	normal_x.coordinates[0]=1.0;
	normal_x.coordinates[1]=0.0;
	normal_x.coordinates[2]=0.0;

	normal_z.coordinates[0]=0.0;
	normal_z.coordinates[1]=0.0;
	normal_z.coordinates[2]=1.0;

	normal_y.coordinates[0]=0.0;
	normal_y.coordinates[1]=1.0;
	normal_y.coordinates[2]=0.0;

	negative_z.coordinates[0] = 0.0;
	negative_z.coordinates[1] = 0.0;
	negative_z.coordinates[2] = -1.0;


	bridgeProperties.emplace("StructureIndicator", "COMPOSITE");
	bridgeProperties.emplace("StructureType", "SLAB_BRIDGE");

	createReferenceCurve();
	createCrossSection();
	createCrossSectionPosition(start_point.coordinates[0], normal_z, normal_x);
	createCrossSectionPosition(end_point.coordinates[0], normal_z, normal_x);
	pos_cs_table[0] = 0.0;
	pos_cs_table[1] = 0.0;

	createAbutmentGroundSketch(foundationPointStart, "left");
	
	createAbutmentGroundSketch(foundationPointEnd, "right");

	createAbutmentFoundations();

	createPier();
};

IfcBridgeParamter::~IfcBridgeParamter(){};

void IfcBridgeParamter::createCrossSectionPosition(double abscissa, Point axis, Point refDirection)
{
	CrossSectionsPosition position;
	position.abscissa = abscissa;
	for (int i=0; i<3; i++){
		position.axis.coordinates[i]			= axis.coordinates[i];
		position.refDirection.coordinates[i]	= refDirection.coordinates[i];
	}
	crossSectionsPositionsSet.emplace(crossSectionsPositionsSet.size(), position);
}

void IfcBridgeParamter::createReferenceCurve()
{
	Point referenceCurvePoints[] = {start_point, end_point};

	int size = sizeof(referenceCurvePoints)/sizeof(referenceCurvePoints[0]);
	for (int i=0; i<size; i++){
		for (int j=0; j<3; j++){
			referenceCurve.points[i].coordinates[j] = referenceCurvePoints[i].coordinates[j];
		}
	}
}

void IfcBridgeParamter::createCrossSection()
{
	CrossSection cs;

	for (int i = 0; i<9; i++){
		cs.points[i].coordinates[0] = 0.0;
	}
	
	cs.points[0].coordinates[1] = 0.0;
	cs.points[0].coordinates[2] = 0.0;

	cs.points[1].coordinates[1] = (this->width)/2;
	cs.points[1].coordinates[2] = 0.0;

	cs.points[2].coordinates[1] = (this->width)/2;
	cs.points[2].coordinates[2] = - 0.25*this->thickness;

	cs.points[3].coordinates[1] = 0.427*this->width;
	cs.points[3].coordinates[2] = - 0.35*this->thickness;

	cs.points[4].coordinates[1] = 0.427*this->width;
	cs.points[4].coordinates[2] = - this->thickness;

	cs.points[5].coordinates[1] = - 0.427*this->width;
	cs.points[5].coordinates[2] = - this->thickness;

	cs.points[6].coordinates[1] = - 0.427*this->width;
	cs.points[6].coordinates[2] = - 0.35*this->thickness;

	cs.points[7].coordinates[1] = - (this->width)/2;
	cs.points[7].coordinates[2] = - 0.25*this->thickness;

	cs.points[8].coordinates[1] = - (this->width)/2;
	cs.points[8].coordinates[2] = 0.0;

	crossSectionsSet.emplace(crossSectionsSet.size(), cs);

}

void IfcBridgeParamter::createAbutmentGroundSketch(Point foundationPoint, std::string position)
{
	AbutmentGroundSketch sketch;
	sketch.foundationPoint = foundationPoint;
	sketch.points[0].coordinates[0] = 0.0;
	sketch.points[0].coordinates[1] = foundationPoint.coordinates[1];
	
	sketch.points[1].coordinates[0] = 0.0;
	sketch.points[1].coordinates[1] = width/2;

	int coefficient = 0;
	if (position == "left"){
		coefficient = -1;
		sketch.extrusionDepth = fabs(sketch.foundationPoint.coordinates[2] - start_point.coordinates[2]);
	}
	else if (position == "right"){
		coefficient = 1;
		sketch.extrusionDepth = fabs(sketch.foundationPoint.coordinates[2] - end_point.coordinates[2]);
	}
	double wing_wallDepth = 20.0;

	sketch.points[2].coordinates[0] = coefficient*wing_wallDepth;
	sketch.points[2].coordinates[1] = width/2;

	sketch.points[3].coordinates[0] = coefficient*wing_wallDepth;
	sketch.points[3].coordinates[1] = getCrossSectionsSet()[0].points[3].coordinates[1];

	sketch.points[4].coordinates[0] = coefficient*overlapAbutmentDeck;
	sketch.points[4].coordinates[1] = getCrossSectionsSet()[0].points[3].coordinates[1];

	sketch.points[5].coordinates[0] = coefficient*overlapAbutmentDeck;
	sketch.points[5].coordinates[1] = -getCrossSectionsSet()[0].points[3].coordinates[1];

	sketch.points[6].coordinates[0] = coefficient*wing_wallDepth;
	sketch.points[6].coordinates[1] = -getCrossSectionsSet()[0].points[3].coordinates[1];
	
	sketch.points[7].coordinates[0] = coefficient*wing_wallDepth;
	sketch.points[7].coordinates[1] = -width/2;

	sketch.points[8].coordinates[0] = 0.0;
	sketch.points[8].coordinates[1] = -width/2;

	

	sketch.subtractionPoints[0].coordinates[0] = coefficient*20.0;
	sketch.subtractionPoints[0].coordinates[1] = 0.0;

	sketch.subtractionPoints[1].coordinates[0] = coefficient*20.0;
	sketch.subtractionPoints[1].coordinates[1] = -sketch.extrusionDepth*0.85;

	sketch.subtractionPoints[2].coordinates[0] = coefficient*17.0;
	sketch.subtractionPoints[2].coordinates[1] = -sketch.extrusionDepth*0.85;

	sketch.subtractionPoints[3].coordinates[0] = coefficient*10.0;
	sketch.subtractionPoints[3].coordinates[1] = -sketch.extrusionDepth*0.60;

	sketch.subtractionPoints[4].coordinates[0] = coefficient*10.0;
	sketch.subtractionPoints[4].coordinates[1] = 0.0;

	sketch.subtractionPoint = sketch.foundationPoint;
	sketch.subtractionPoint.coordinates[1] = -width/2;

	if (position == "left"){
		abutmentsSet.emplace("left", sketch); 
	}
	
	if (position == "right"){
		abutmentsSet.emplace("right", sketch); 
	}
}

void IfcBridgeParamter::createAbutmentFoundations()
{
	AbutmentFoundation foundation;
	double offset = 0.5;
	foundation.thickness = 5.0;

	for (std::map<std::string, AbutmentGroundSketch> ::iterator it = abutmentsSet.begin(); it != abutmentsSet.end(); ++it)
	{
		int coefficient = 0;
		if (it->first == "left"){
			coefficient = 1; 
		}
		else if (it->first == "right"){
			coefficient = -1;
		}
		foundation.foundationPoint = it->second.foundationPoint;
		//foundation.foundationPoint.coordinates[0] +=coefficient*offset;

		int numberOfPoints;
		numberOfPoints = sizeof(it->second.points)/sizeof(it->second.points[0]);
		
		

		for (int j=0; j<numberOfPoints; j++){
			if (j==0 || j==1 || j==8){
				foundation.points[j].coordinates[0] = it->second.points[j].coordinates[0] + coefficient*offset;
			}
			else if (j==2 || j==3 || j==6 || j==7){
				foundation.points[j].coordinates[0] = -coefficient*10.0- coefficient*offset;
			}
			else  {
				foundation.points[j].coordinates[0] = it->second.points[j].coordinates[0] - coefficient*offset;
			}

			if (j==1 || j==2 || j==5 || j==6){
				foundation.points[j].coordinates[1] = it->second.points[j].coordinates[1] + offset;
			}
			else if (j==3 || j==4 || j==7 || j==8) {
				foundation.points[j].coordinates[1] = it->second.points[j].coordinates[1] - offset;
			}
			else{
				foundation.points[j].coordinates[1] = 0.0;
			}
		}	

		if (it->first == "left"){
			abutmentFoundationsSet.emplace("left", foundation); 
		}

		if (it->first == "right"){
			abutmentFoundationsSet.emplace("right", foundation); 
		}
	}
}

void IfcBridgeParamter::createPier(){
	
	if (length > 60){
		double pierThickness = 5.0;
		double offset = 0.5;

		int numberOfFields = (int)length/30 ;
		for (int i=0; i<numberOfFields-1; i++){
			Pier pier;

			pier.extrusionDepth = 20.0;

			pier.foundationPoint.coordinates[0] = length/numberOfFields*(i+1);
			pier.foundationPoint.coordinates[1] = 0.0;
			pier.foundationPoint.coordinates[2] = -20.0;
			
			pier.points[0].coordinates[0] = -pierThickness/2;
			pier.points[0].coordinates[1] = width/2;

			pier.points[1].coordinates[0] = pierThickness/2;
			pier.points[1].coordinates[1] = width/2;

			pier.points[2].coordinates[0] = pierThickness/2;
			pier.points[2].coordinates[1] = -width/2;

			pier.points[3].coordinates[0] = -pierThickness/2;
			pier.points[3].coordinates[1] = -width/2;

			//create foundation
			pier.foundation.extrusionDepth = 5;

			pier.foundation.points[0].coordinates[0] = pier.points[0].coordinates[0] - offset;
			pier.foundation.points[0].coordinates[1] = pier.points[0].coordinates[1] + offset;

			pier.foundation.points[1].coordinates[0] = pier.points[1].coordinates[0] + offset;
			pier.foundation.points[1].coordinates[1] = pier.points[1].coordinates[1] + offset;

			pier.foundation.points[2].coordinates[0] = pier.points[2].coordinates[0] + offset;
			pier.foundation.points[2].coordinates[1] = pier.points[2].coordinates[1] - offset;

			pier.foundation.points[3].coordinates[0] = pier.points[3].coordinates[0] - offset;
			pier.foundation.points[3].coordinates[1] = pier.points[3].coordinates[1] - offset;

			pierSet.push_back(pier);
		}
	}
}

