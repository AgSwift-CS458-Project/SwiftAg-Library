#pragma once

#ifndef POINT_HPP
#define POINT_HPP

#include <cmath>

using namespace std;

class Point {
	private:
		double x;
		double y;
		double height;
	public:
		Point();
		Point(double _x, double _y, double _height);
		double get_x();
		double get_y();
		double get_height();
		double distance(Point& _p);
		bool operator==(Point& _p);
		bool equals(Point& _p);
};

#endif