#include "Triangle.hpp"
#include <vector>
#include <tuple>
#include <cmath>

using namespace std;

Triangle::Triangle(Point& _a, Point& _b, Point& _c) {
	a = &_a;
	b = &_b;
	c = &_c;
}

bool Triangle::operator==(Triangle& _t) {
	if(_t.containsPoint(*a) && _t.containsPoint(*b) && _t.containsPoint(*c)) return true;
	else return false;
}

bool Triangle::containsPoint(Point& _p) {
	if (_p == *a || _p == *b || _p == *c) return true;
	else return false;
}

//bool Triangle::containsEdge(Edge& _e) {
//	if(*ab == _e || *bc == _e || *ca == _e) return true;
//	else return false;
//}

Edge* Triangle::getEdge(int _index) {
	switch (_index) {
		case 0:
			return new Edge(*a, *b);
		case 1:
			return new Edge(*b, *c);
		case 2:
			return new Edge(*c, *a);
	}
}

//bool Triangle::hasSharedEdge(Triangle& _t) {
//	t1_points = getPoints();
//	t2_points = _t.getPoints();
//}
//
//Edge* Triangle::getSharedEdge(Triangle& _t) {
//	if (_t.containsEdge(*ab)) return *ab;
//	else if (_t.containsEdge(*bc)) return *bc;
//	else if (_t.containsEdge(*ca)) return *ca;
//}

vector<Point*> Triangle::getPoints() {
	return vector<Point*> {a, b, c};
}

tuple<Point, double> Triangle::circumcircle() {

	double D = ( (a->get_x() - c->get_x()) * (b->get_y() - c->get_y()) - (b->get_x() -  c->get_x()) * (a->get_y() - c->get_y()) );
	double center_x = (((a->get_x() - c->get_x()) * (a->get_x() + c->get_x()) + (a->get_y() - c->get_y()) * (a->get_y() + c->get_y())) / 2 * (b->get_y() - c->get_y()) - ((b->get_x() - c->get_x()) * (b->get_x() + c->get_x()) + (b->get_y() - c->get_y()) * (b->get_y() + c->get_y())) / 2 * (a->get_y() - c->get_y())) / D;
	double center_y = (((b->get_x() - c->get_x()) * (b->get_x() + c->get_x()) + (b->get_y() - c->get_y()) * (b->get_y() + c->get_y())) / 2 * (a->get_x() - c->get_x()) - ((a->get_x() - c->get_x()) * (a->get_x() + c->get_x()) + (a->get_y() - c->get_y()) * (a->get_y() + c->get_y())) / 2 * (b->get_x() - c->get_x())) / D;
	double radius = sqrt( pow((c->get_x() - center_x),2) + pow((c->get_y() - center_y),2) );	
	tuple<Point, double> cc = make_tuple(Point(center_x, center_y, 0), radius);
	
	return cc;
}

double Triangle::sign() {
	return (a->get_x() - c->get_x()) * (b->get_y() - c->get_y()) - (b->get_x() - c->get_x()) * (a->get_y() - c->get_y());
}

bool Triangle::pointInTriangle(Point& _p) {
	double d1, d2, d3;
	bool neg, pos;

	Triangle* t1 = new Triangle(_p, *a, *b);
	Triangle* t2 = new Triangle(_p, *b, *c);
	Triangle* t3 = new Triangle(_p, *c, *a);

	d1 = t1->sign();
	d2 = t2->sign();
	d3 = t3->sign();

	delete t1;
	delete t2;
	delete t3;

	neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(neg && pos);
}

double Triangle::getHeightAtPoint(Point& _p) {
	if (!pointInTriangle(_p)) return 0;
	else {

		double d1 = _p.distance(*a);
		double d2 = _p.distance(*b);
		double d3 = _p.distance(*c);
		double total_dist = d1 + d2 + d3;

		double h = ((d1 / total_dist) * a->get_height()) + ((d2 / total_dist) * b->get_height()) + ((d3 / total_dist) * c->get_height());
		return h;
	}
}