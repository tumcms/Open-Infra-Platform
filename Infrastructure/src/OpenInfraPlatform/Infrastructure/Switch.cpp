#include <iostream>
#include <string>
#include "Switch.h"


Switch::Switch(double r, double sA, double t, std::string sb, std::string rp, switchtype st, turnoutDirection tD, tieType tT){
	radius = r;
	switchAngle = sA;
	tilt = t;
	switchBlades = sb;
	railprofile = rp;
	switchtype = st;
	turnoutDirection = tD;
	tieType = tT;
}

Switch::Switch() {
	radius = 500;
	switchAngle = 0.35;
	tilt = 0.08;
	switchBlades = "Federschienenzunge"; //depending on country's standart
	railprofile = "UIC60"; //depending on country's standart
	switchtype = singleSlip;
	turnoutDirection = left;
	tieType = wooden;

}

Switch::~Switch() {}

void Switch::set_radius(double a) { radius = a; }
double Switch::get_radius() { return radius; }
void Switch::set_switchAngle(double a) { switchAngle = a; }
double Switch::get_switchAngle() { return switchAngle; }
void set_tilt(double a) { tilt = a; }
double get_tilt() { return tilt; }
void set_switchBlades(std::string s) { switchBlades = s;}
std::string get_switchBlades() { return switchBlades; }
void set_railprofile(std::string p) { railprofile = p; }
std::string get_railprofile() { return railprofile; }
void set_switchtype(switchtype s) { switchtype = s; }
switchtype get_switchtype() { return switchtype; }
void set_turnoutDirection(turnoutDirection d) { turnoutDirection = d; }
turnoutDirection get_turnoutDirection() { return turnoutDirection;}
void set_tieType(tieType t) { tieType = t; }
tieType get_tieType() { return tieType; }

