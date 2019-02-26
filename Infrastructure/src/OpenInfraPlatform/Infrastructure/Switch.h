#include <iostream>
#include <cmath>
#include <string>

// Definition according to standart of Deutsche Bahn AG
class Switch {
	double radius;
	double switchAngle;
	double tilt;
	std::string switchBlades;  //depending on country's standart
	std::string railprofile;   //depending on country's standart
public:
	enum switchtype {singleSlip, doubleSlip, crossover, scissorsCrossover} switchtype;
	enum turnoutDirection {left, right} turnoutDirection;
	enum tieType {wooden, concrete, steel, stoneBlock, plastics} tieType;
	void set_radius(double a);
	double get_radius();
	void set_switchAngle(double a);
	double get_switchAngle();
	void set_tilt(double);
	double get_tilt();
	void set_switchBlades(std::string);
	std::string get_switchBlades();
	void set_railprofile(std::string);
	std::string get_railprofile();
	void set_switchtype(switchtype);
	switchtype get_switchtype();
	void set_turnoutDirection(turnoutDirection);
	turnoutDirection get_turnoutDirection();
	void set_tieType(tieType);
	tieType get_tieType ();
	Switch(double, double, double, std::string, std::string, switchtype, turnoutDirection, tieType);
	Switch();
	~Switch();


};