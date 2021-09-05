#pragma once

#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Point.hpp"
#include "Edge.hpp"
#include <vector>
#include <tuple>

class Triangle {
	private:
		Point* a; 
		Point* b;
		Point* c;
	public:
		Triangle(Point& _a, Point& _b, Point& _c);
		bool operator==(Triangle& _t);
		bool containsPoint(Point& _p);
		// bool containsEdge(Edge& _e);
		Edge* getEdge(int _index);
		// bool hasSharedEdge(Triangle& _t);
		// Edge* getSharedEdge(Triangle& _t);
		vector<Point*> getPoints();
		tuple<Point, double> circumcircle();
		double sign();
		//double area();
		bool pointInTriangle(Point& _p);
		double getHeightAtPoint(Point& _p);
};

#endif