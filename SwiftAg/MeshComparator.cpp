#include "MeshComparator.hpp"
#include "Graph.hpp"
#include <unordered_map>
#include <iostream>

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
			Triangle e_triangle;
			Triangle p_triangle;
			int num_g1_tris = 0;
			int num_g2_tris = 0;
			cout << boolalpha;
			cout << "Test Point: " << test_point->get_x() << " " << test_point->get_y() << endl;
			for (auto t1 : g1_tris) {
				if (t1.first->pointInTriangle(test_point)) {
					cout << "Point in G1 Triangle" << endl;
					num_g1_tris += 1;
					e_triangle = *t1.first;
				}
			}
			for (auto t2 : g2_tris) {
				if (t2.first->pointInTriangle(test_point)) {
					cout << "Point in G2 Triangle" << endl;
					num_g2_tris += 1;
					p_triangle = *t2.first;
				}
			}
			cout << "G1 Tris: " << num_g1_tris << endl;
			cout << "G2 Tris: " << num_g2_tris << endl;

			if (num_g1_tris == 1 && num_g2_tris == 1) {
				double height_difference = e_triangle.getHeightAtPoint(test_point) - p_triangle.getHeightAtPoint(test_point);
				if (height_difference > 0) {
					cout << "Cut" << endl;
					cut += (height_difference * pow(_stepResolution, 2));
				}
				if (height_difference < 0) {
					cout << "Fill" << endl;
					fill += (height_difference * pow(_stepResolution, 2));
				}
			}
		}
	}
}

double MeshComparator::getCutAmount() {
	return cut;
}

double MeshComparator::getFillAmount() {
	return fill;
}