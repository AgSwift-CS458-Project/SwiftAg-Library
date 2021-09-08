#include "Edge.hpp"
#include "Point.hpp"

using namespace std;

Edge::Edge() {
	
}

Edge::Edge(Point& _a, Point& _b) {
	a = &_a;
	b = &_b;
}

Point* Edge::get_a() {
	return a;
}

Point* Edge::get_b() {
	return b;
}

void Edge::setDelete(bool _d) {
	canDelete = _d;
}

bool Edge::getDelete() {
	return canDelete;
}

bool Edge::containsPoint(Point& _p) {
	if (a == &_p || b == &_p) return true;
	else return false;
}

double Edge::length() {
	return sqrt( pow((b->get_y() - a->get_y()),2) + pow(b->get_x() - a->get_x(),2) );
}

bool Edge::intersects(Edge& _e) {

	double x1 = a->get_x();
	double y1 = a->get_y();
	double x2 = b->get_x();
	double y2 = b->get_y();
		
	double x3 = _e.get_a()->get_x();
	double y3 = _e.get_a()->get_y();
	double x4 = _e.get_b()->get_x();
	double y4 = _e.get_b()->get_y();
		
	double t = (((x1 - x3)*(y3 - y4)) - ((y1 - y3)*(x3 - x4))) / (((x1 - x2)*(y3 - y4)) - ((y1 - y2)*(x3 - x4)));
	double u = (((x2 - x1)*(y1 - y3)) - ((y2 - y1)*(x1 - x3))) / (((x1 - x2)*(y3 - y4)) - ((y1 - y2)*(x3 - x4)));
		
	if ( (t >= 0 && t <= 1) && (u >= 0 && u <= 1) ) {
		double x_int = x1 + t*(x2 - x1);
		double y_int = y1 + t*(y2 - y1);
			
		Point* int_point = new Point(x_int, y_int, 0);
		if ((a == int_point || b == int_point) || (_e.get_a() == int_point || _e.get_b() == int_point)) {
			delete int_point;
			return false;
		}
		else {
			delete int_point;
			return true;
		}
	}
	else return false;
}

bool Edge::operator==(Edge& _e) {
	if(
		(a == _e.get_a() && b == _e.get_b()) ||
		(a == _e.get_b() && b == _e.get_a())) return true;
	else return false;
}

bool Edge::equals(Edge& _e) {
	if (
		(a == _e.get_a() && b == _e.get_b()) ||
		(a == _e.get_b() && b == _e.get_a())) return true;
	else return false;
}