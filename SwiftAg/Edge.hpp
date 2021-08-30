#pragma once

#ifndef EDGE_HPP
#define EDGE_HPP

#include "Point.hpp"
#include <cmath>

using namespace std;

class Edge {
	private:
		Point* a;
		Point* b;
		bool canDelete = true;
	public:
		Edge();
		Edge(Point* _a, Point* _b);
		Point* get_a();
		Point* get_b();
		void setDelete(bool _d);
		bool getDelete();
		bool containsPoint(Point* _p);
		double length();
		bool intersects(Edge* _e);
		bool operator==(Edge* _e);
};

#endif