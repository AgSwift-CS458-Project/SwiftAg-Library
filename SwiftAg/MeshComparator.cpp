#include "MeshComparator.hpp"
#include "Graph.hpp"
#include <unordered_map>

using namespace std;


MeshComparator::MeshComparator(Graph* _g1, Graph* _g2) {
	g1 = _g1;
	g2 = _g2;

	unordered_map<Point*, double> g2_point_list = g2->getPoints();
	
	for (auto p2 : g2_point_list) {
		if (p2.first->get_x() < x_bound_min) {
			x_bound_min = p2.first->get_x();
		}
		if (p2.first->get_x() > x_bound_max) {
			x_bound_max = p2.first->get_x();
		}
		if (p2.first->get_y() < y_bound_min) {
			y_bound_min = p2.first->get_y();
		}
		if (p2.first->get_y() > y_bound_max) {
			y_bound_max = p2.first->get_y();
		}
	}
}

void MeshComparator::calculateCutFill(double _stepResolution) {
	unordered_map<Triangle*, int> g1_tris = g1->getTriangles();
	unordered_map<Triangle*, int> g2_tris = g2->getTriangles();
	for (double x = x_bound_min; x < x_bound_max; x += _stepResolution) {
		for (double y = y_bound_min; y < y_bound_max; y += _stepResolution) {
			Point* test_point = new Point(x, y, 0);
			Triangle* e_triangle = nullptr;
			Triangle* p_triangle = nullptr;

			if (g1->hasTriangleContainingPoint(test_point)) {
				e_triangle = g1->getTriangleContainingPoint(test_point);
			}
			if (g2->hasTriangleContainingPoint(test_point)) {
				p_triangle = g2->getTriangleContainingPoint(test_point);
			}

			if (!(e_triangle == nullptr) && !(p_triangle == nullptr)) {
				double height_difference = e_triangle->getHeightAtPoint(test_point) - p_triangle->getHeightAtPoint(test_point);
				if (height_difference > 0) {
					cut += (height_difference * pow(_stepResolution, 2));
				}
				if (height_difference < 0) {
					fill += (height_difference * pow(_stepResolution, 2));
				}
			}
			delete test_point;
		}
	}
}

double MeshComparator::getCutAmount() {
	return cut;
}

double MeshComparator::getFillAmount() {
	return fill;
}