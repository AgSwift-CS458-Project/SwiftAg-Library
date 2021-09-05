#include "Point.hpp"
#include <cmath>

using namespace std;

Point::Point() {
	x = 0;
	y = 0;
	height = 0;
}

Point::Point(double _x, double _y, double _height) {
	x = _x;
	y = _y;
	height = _height;
}

double Point::get_x() {
	return x;
}

double Point::get_y() {
	return y;
}

double Point::get_height() {
	return height;
}

double Point::distance(Point& _p) {
	return sqrt(pow((_p.get_x() - x), 2) + pow((_p.get_y() - y), 2));
}

bool Point::operator==(Point& _p) {
	if(x == _p.get_x() && y == _p.get_y()) return true;
	else return false;
}

bool Point::equals(Point& _p) {
	if (x == _p.get_x() && y == _p.get_y()) return true;
	else return false;
}