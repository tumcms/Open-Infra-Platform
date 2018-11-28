#include<iostream>
#include<cmath>
#include <string>


class Switch {
	int radius;
	float SwitchAngle;
public:
	enum switchtyp {singleSlip, doubleSlip, insideSlip, outsideSlip, crossover, scissorsCrossover} ST;
	enum turnoutDirection {left, right} TD;
	enum switchPoint {}SP;
	enum tieType {wooden, concrete, steel, stoneBlock, plastics}TT;
	int set_radius(int a);
	int get_radius();
	float set_SwitchAngle(float a);
	float get_SwitchAngle();

};