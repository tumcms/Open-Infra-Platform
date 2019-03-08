#include <iostream>
#include <string>
#include "Switch.h"


Switch::Switch(double r, double sA, double t, std::string sb, std::string rp, eSwitchtype st, eTurnoutDirection tD, eTieType tT){
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
void Switch::set_tilt(double a) { tilt = a; }
double Switch::get_tilt() { return tilt; }
void Switch::set_switchBlades(std::string s) { switchBlades = s;}
std::string Switch::get_switchBlades() { return switchBlades; }
void Switch::set_railprofile(std::string p) { railprofile = p; }
std::string Switch::get_railprofile() { return railprofile; }
void Switch::set_switchtype(Switch::eSwitchtype s) { switchtype = s; }
Switch::eSwitchtype Switch::get_switchtype() { return switchtype; }
void Switch::set_turnoutDirection(Switch::eTurnoutDirection d) { turnoutDirection = d; }
Switch::eTurnoutDirection Switch::get_turnoutDirection() { return turnoutDirection;}
void Switch::set_tieType(Switch::eTieType t) { tieType = t; }
Switch::eTieType Switch::get_tieType() { return tieType; }

