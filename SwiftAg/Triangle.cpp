#include "Triangle.hpp"
#include <vector>
#include <tuple>
#include <cmath>

using namespace std;

Triangle::Triangle() {

}

Triangle::Triangle(Point* _a, Point* _b, Point* _c) {
	ab = new Edge(_a, _b);
	bc = new Edge(_b, _c);
	ca = new Edge(_c, _a);
}

bool Triangle::operator==(Triangle* _t) {
	if(_t->containsEdge(ab) && _t->containsEdge(bc) && _t->containsEdge(ca)) return true;
	else return false;
}

bool Triangle::containsEdge(Edge* _e) {
	if(ab == _e || bc == _e || ca == _e) return true;
	else return false;
}

Edge& Triangle::getEdge(int _index) {
	switch (_index) {
		case 0:
			return *ab;
		case 1:
			return *bc;
		case 2:
			return *ca;
	}
}

bool Triangle::hasSharedEdge(Triangle* _t) {
	if (_t->containsEdge(ab)) return true;
	else if (_t->containsEdge(bc)) return true;
	else if (_t->containsEdge(ca)) return true;
	else return false;
}

Edge& Triangle::getSharedEdge(Triangle* _t) {
	if (_t->containsEdge(ab)) return *ab;
	else if (_t->containsEdge(bc)) return *bc;
	else if (_t->containsEdge(ca)) return *ca;
}

vector<Edge*> Triangle::getEdges() {
	vector<Edge*> edges;
	edges.push_back(ab);
	edges.push_back(bc);
	edges.push_back(ca);
	return edges;
}

tuple<Point, double> Triangle::circumcircle() {

	Point a = *ab->get_a();
	Point b = *ab->get_b();
	Point c = *ca->get_a();
	
	double D = ( (a.get_x() - c.get_x()) * (b.get_y() - c.get_y()) - (b.get_x() -  c.get_x()) * (a.get_y() - c.get_y()) );
	double center_x = (((a.get_x() - c.get_x()) * (a.get_x() + c.get_x()) + (a.get_y() - c.get_y()) * (a.get_y() + c.get_y())) / 2 * (b.get_y() - c.get_y()) - ((b.get_x() - c.get_x()) * (b.get_x() + c.get_x()) + (b.get_y() - c.get_y()) * (b.get_y() + c.get_y())) / 2 * (a.get_y() - c.get_y())) / D;
	double center_y = (((b.get_x() - c.get_x()) * (b.get_x() + c.get_x()) + (b.get_y() - c.get_y()) * (b.get_y() + c.get_y())) / 2 * (a.get_x() - c.get_x()) - ((a.get_x() - c.get_x()) * (a.get_x() + c.get_x()) + (a.get_y() - c.get_y()) * (a.get_y() + c.get_y())) / 2 * (b.get_x() - c.get_x())) / D;
	double radius = sqrt( pow((c.get_x() - center_x),2) + pow((c.get_y() - center_y),2) );	
	tuple<Point, double> cc = make_tuple(Point(center_x, center_y, 0), radius);
	
	return cc;
}

double Triangle::sign() {
	return (ab->get_a()->get_x() - ca->get_a()->get_x()) * (ab->get_b()->get_y() - ca->get_a()->get_y()) - (ab->get_b()->get_x() - ca->get_a()->get_x()) * (ab->get_a()->get_y() - ca->get_a()->get_y());
}

bool Triangle::pointInTriangle(Point* _p) {
	double d1, d2, d3;
	bool neg, pos;

	Triangle* t1 = new Triangle(_p, ab->get_a(), ab->get_b());
	Triangle* t2 = new Triangle(_p, ab->get_b(), ca->get_a());
	Triangle* t3 = new Triangle(_p, ca->get_a(), ab->get_a());

	d1 = t1->sign();
	d2 = t2->sign();
	d3 = t3->sign();

	neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(neg && pos);
}

double Triangle::getHeightAtPoint(Point* _p) {
	if (!pointInTriangle(_p)) return 0;
	else {

		double d1 = _p->distance(ab->get_a());
		double d2 = _p->distance(ab->get_b());
		double d3 = _p->distance(ca->get_a());
		double total_dist = d1 + d2 + d3;

		double h = ((d1 / total_dist) * ab->get_a()->get_height()) + ((d2 / total_dist) * ab->get_b()->get_height()) + ((d3 / total_dist) * ca->get_a()->get_height());
		return h;
	}
}