#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <fstream>
#include "Point.hpp"
#include "Edge.hpp"
#include "Triangle.hpp"
#include "Graph.hpp"
#include "MeshComparator.hpp"

using namespace std;

int main(int argc, char* argv[]) {

	cout << boolalpha;
	srand(1337);
	cout.precision(8);
	Point p1(0, 0, 1);
	Point p2(0, 5, 1);
	Point p3(5, 0, 1);
	Point p4(5, 5, 1);
	Point p5(5, 5, 1);
	Point tp(2, 2, 0);
	Edge e1(p1, p2);
	Edge e2(p2, p1);
	Triangle t1(p1, p2, p3);
	Triangle t2(p4, p2, p3);
	Graph g1;
	Graph g2;
	cout << "Point, Edge, & Triangle Tests:" << endl;
	cout << "Point type size: " << sizeof(p1) << endl;
	cout << "Edge type size: " << sizeof(e1) << endl;
	cout << "Triangle type size: " << sizeof(t1) << endl;
	cout << "Point 1 (0,0,1)" << endl;
	cout << "Point 2 (0,5,1)" << endl;
	cout << "Point 3 (5,0,1)" << endl;
	cout << "Point 4 (5,5,1)" << endl;
	cout << "Point 5 (5,5,1)" << endl;
	cout << "Point 4: " << p4.get_x() << " " << p4.get_y() << endl;
	cout << "Point 5: " << p5.get_x() << " " << p5.get_y() << endl;
	cout << "Distance between Point 4 and Point 5: " << p4.distance(p5) << endl;
	cout << "Point 4 == Point 5: " << (p4.equals(p5)) << endl;
	cout << "Point 4 == Point 4: " << (&p4 == &p4) << endl;
	cout << "Edge 1 (Point 1, Point 2)" << endl;
	cout << "Edge 2 (Point 2, Point 1)" << endl;
	cout << "Edge 1 == Edge 2: " << e1.equals(e2) << endl;
	cout << "Triangle 1 (Point 1, Point 2, Point 3)" << endl;
	cout << "Point Distance: " << p1.distance(p2) << endl;
	cout << "Edge Length: " << e1.length() << endl;
	cout << "Point Distance and Edge Length should be equal: " << (p1.distance(p2) == e1.length()) << endl;
	cout << "Point (2,2,0) inside Triangle 1: " << t1.pointInTriangle(tp) << endl;
	cout << "Height at Point (2,2,0) inside Triangle 1: " << t1.getHeightAtPoint(tp) << endl;
	cout << "Point 4 (5,5,1)" << endl;
	cout << "Triangle 2 (Point 2, Point 3, Point 4)" << endl;
	cout << "Point (2,2,0) inside Triangle 2: " << t2.pointInTriangle(tp) << endl;
	// cout << "Triangle 1 and Triangle 2 share edges: " << t1.hasSharedEdge(t2) << endl;
	cout << endl;
	cout << "Graph Tests: " << endl;
	cout << "Graph 1: 25 random points" << endl;
	for (int i = 0; i < 200; i++) {
		Point* new_point = new Point((rand() % 1000), (rand() % 700), 3);
		g1.addPoint(*new_point);
	}
	cout << "Number of points added: " << g1.pointCount() << endl;
	unordered_map<Point*, double> points = g1.getPoints();
	for (auto p : points) {
		cout << "X: " << p.first->get_x() << " Y: " << p.first->get_y() << endl;
	}
	cout << "Testing Bowyer-Watson Triangulation..." << endl;
	g1.generateDelaunayTriangulation();
	//g1.bowyerWatsonTriangulation();
	ofstream ex_outfile;
	ex_outfile.open("output.json");
	ex_outfile << "[";
	unordered_map<Edge*, bool> e_edges = g1.getEdges();
	for (auto e : e_edges) {
		Edge* temp_edge = e.first;
		cout << "A: (" << temp_edge->get_a()->get_x() << "," << temp_edge->get_a()->get_y() << "), B: (" << temp_edge->get_b()->get_x() << "," << temp_edge->get_b()->get_y() << ")" << endl;
		ex_outfile << "[[" << temp_edge->get_a()->get_x() << "," << temp_edge->get_a()->get_y() << "],[" << temp_edge->get_b()->get_x() << "," << temp_edge->get_b()->get_y() << "]],";
	}
	ex_outfile.seekp(-1, ios_base::end);
	ex_outfile << "]";
	ex_outfile.close();

	cout << "Number of triangles: " << g1.triangleCount() << endl;
	cout << "Approx size (bytes): " << sizeof(Triangle) * g1.triangleCount() << endl;
	cout << "Number of points: " << g1.pointCount() << endl;
	cout << "Approx size (bytes): " << sizeof(Point) * g1.pointCount() << endl;

	/*cout << "Creating second graph: " << endl;

	for (int i = 0; i < 50; i++) {
		Point* new_point = new Point(300+(rand() % 300), 300+(rand() % 300), 4);
		g2.addPoint(*new_point);
	}

	cout << "Generating Delaunay Triangulation..." << endl;
	g2.generateDelaunayTriangulation();
	ofstream pr_outfile;
	pr_outfile.open("output-proposed.json");
	pr_outfile << "[";
	unordered_map<Edge*, bool> p_edges = g2.getEdges();
	for (auto e : p_edges) {
		Edge* temp_edge = e.first;
		cout << "A: (" << temp_edge->get_a()->get_x() << "," << temp_edge->get_a()->get_y() << "), B: (" << temp_edge->get_b()->get_x() << "," << temp_edge->get_b()->get_y() << ")" << endl;
		pr_outfile << "[[" << temp_edge->get_a()->get_x() << "," << temp_edge->get_a()->get_y() << "],[" << temp_edge->get_b()->get_x() << "," << temp_edge->get_b()->get_y() << "]],";
	}
	pr_outfile.seekp(-1, ios_base::end);
	pr_outfile << "]";
	pr_outfile.close();

	MeshComparator mc(&g1, &g2);
	mc.calculateCutFill(5);
	cout << "Cut Amount: " << mc.getCutAmount() << endl;
	cout << "Fill Amount: " << mc.getFillAmount() << endl;
	cout << "Cut - Fill difference: " << mc.getCutAmount() + mc.getFillAmount() << endl;

	cout << "Cut-fill amounts should be zero (or near zero)" << endl;*/

	return 0;
}