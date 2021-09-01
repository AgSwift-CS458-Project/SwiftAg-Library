#include "Graph.hpp"
#include <tuple>

Graph::Graph() {

}

void Graph::addPoint(Point* _p) {
	points[_p] = _p->get_height();
}

void Graph::addEdge(Edge* _e) {
	edges[_e] = _e->getDelete();
}

void Graph::addTriangle(Triangle* _t) {
	triangles[_t] = 0;
}

void Graph::removePoint(Point* _p) {
	points.erase(_p);
}

void Graph::removeEdge(Edge* _e) {
	edges.erase(_e);
}

void Graph::removeTriangle(Triangle* _t) {
	triangles.erase(_t);
}

int Graph::pointCount() {
	return points.size();
}

int Graph::edgeCount() {
	return edges.size();
}

int Graph::triangleCount() {
	return triangles.size();
}

unordered_map<Point*, double> Graph::getPoints() {
	return points;
}

unordered_map<Edge*, bool> Graph::getEdges() {
	return edges;
}

unordered_map<Triangle*, int> Graph::getTriangles() {
	return triangles;
}

bool Graph::hasTriangleContainingPoint(Point* _p) {
	for (auto t : triangles) {
		if (t.first->pointInTriangle(_p)) {
			return true;
		}
	}
	return false;
}

Triangle* Graph::getTriangleContainingPoint(Point* _p) {
	for (auto t : triangles) {
		if (t.first->pointInTriangle(_p)) {
			return t.first;
		}
	}
}

bool Graph::delaunayTest(Triangle* _t) {
	tuple<Point, double> cc = _t->circumcircle();
	Point center = get<0>(cc);
	double r = get<1>(cc);
	for (auto p : points) {
		Point* test_point = p.first;
		if (center.distance(test_point) < r) return false;
	}
	return true;
}

void Graph::generateDelaunayTriangulation() {
	for (auto p1 : points) {
		for (auto p2 : points) {
			for (auto p3 : points) {
				if (!(p1.first == p2.first) && !(p2.first == p3.first) && !(p3.first == p1.first)) {
					Triangle* test_tri = new Triangle(p1.first, p2.first, p3.first);
					if (delaunayTest(test_tri)) {
						addTriangle(test_tri);
					}
				}
			}
		}
	}

	for (auto& t : triangles) {
		addEdge(&t.first->getEdge(0));
		addEdge(&t.first->getEdge(1));
		addEdge(&t.first->getEdge(2));
	}

	vector<Edge*> edgesToRemove;
	for (auto e1 : edges) {
		for (auto e2 : edges) {
			if (e1.first->intersects(e2.first)
				&& !(e1.first->containsPoint(e2.first->get_a()))
				&& !(e1.first->containsPoint(e2.first->get_b()))
				) {
				double len_e1 = e1.first->length();
				double len_e2 = e2.first->length();
				if (len_e1 <= len_e2) {
					edgesToRemove.push_back(e2.first);
				}
				else {
					edgesToRemove.push_back(e1.first);
				}
			}
		}
	}

	for (auto e : edgesToRemove) {
		removeEdge(e);
	}
}

void Graph::bowyerWatsonTriangulation() {
	double tan60 = 1.73205080757;
	double x_min = 0, y_min = 0;
	double x_max = 0, y_max = 0;

	for (auto p : points) {
		if (p.first->get_x() < x_min) {
			x_min = p.first->get_x();
		}
		if (p.first->get_x() > x_max) {
			x_max = p.first->get_x();
		}
		if (p.first->get_y() < y_min) {
			y_min = p.first->get_y();
		}
		if (p.first->get_y() > y_max) {
			y_max = p.first->get_y();
		}

	}
	double t2x = (y_max - y_min) / tan60; //t3x is collinear
	double t1y = (((x_max + x_min) / 2) - x_min) * tan60;

	Point* T1 = new Point((x_max + x_min) / 2, t1y + y_max, 0);
	Point* T2 = new Point(x_min - t2x, y_min, 0);
	Point* T3 = new Point(x_max + t2x, y_min, 0);

	Graph* mesh_graph = new Graph();
	for (auto p : points) {
		mesh_graph->addPoint(p.first);
		if (mesh_graph->pointCount() == 1) {
			Triangle* t1 = new Triangle(T1, T2, p.first);
			Triangle* t2 = new Triangle(T2, T3, p.first);
			Triangle* t3 = new Triangle(T3, T1, p.first);

			mesh_graph->addTriangle(t1);
			mesh_graph->addTriangle(t2);
			mesh_graph->addTriangle(t3);
		}
		else {
			vector<Triangle*> bad_triangles;
			vector<Edge*> shared_edges;
			for (auto t : mesh_graph->getTriangles()) {
				if (!mesh_graph->delaunayTest(t.first)) {
					bad_triangles.push_back(t.first);
				}
			}

			for (auto b1 : bad_triangles) {
				for (auto b2 : bad_triangles) {
					if (!(b1 == b2) && b1->hasSharedEdge(b2)) {
						Edge& shared_edge = b1->getSharedEdge(b2);
						shared_edges.push_back(&shared_edge);
					}
				}
			}

			if (shared_edges.size() == 0) {
				for (auto p1 : mesh_graph->getPoints()) {
					for (auto p2 : mesh_graph->getPoints()) {
						if (!(p1.first == p2.first) && !(p1.first == p.first) && !(p2.first == p.first)) {
							Triangle* test_tri = new Triangle(p1.first, p2.first, p.first);
							if (mesh_graph->delaunayTest(test_tri)) {
								mesh_graph->addTriangle(test_tri);
							}
						}
					}
				}
			}
			else {
				for (auto e : shared_edges) {
					Triangle* test_tri = new Triangle(e->get_a(), e->get_b(), p.first);
					if (mesh_graph->delaunayTest(test_tri)) {
						mesh_graph->addTriangle(test_tri);
					}
				}
			}

			for (auto b : bad_triangles) {
				mesh_graph->removeTriangle(b);
			}
		}
	}

	for (auto t : mesh_graph->getTriangles()) {
		mesh_graph->addEdge(&t.first->getEdge(0));
		mesh_graph->addEdge(&t.first->getEdge(1));
		mesh_graph->addEdge(&t.first->getEdge(2));
	}

	for (auto e : mesh_graph->getEdges()) {
		if (e.first->containsPoint(T1) || e.first->containsPoint(T2) || e.first->containsPoint(T3)) {
			mesh_graph->removeEdge(e.first);
		}
		/*for (auto e2 : mesh_graph->getEdges()) {
			if (e.first->intersects(e2.first)
				&& !(e.first->containsPoint(e2.first->get_a()))
				&& !(e.first->containsPoint(e2.first->get_b()))
				) {
				if (e.first->length() > e2.first->length()) {
					mesh_graph->removeEdge(e.first);
				}
				else {
					mesh_graph->removeEdge(e2.first);
				}
			}
		}*/
	}

	triangles = mesh_graph->getTriangles();
	edges = mesh_graph->getEdges();
}