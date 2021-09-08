#pragma once
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Point.hpp"
#include "Edge.hpp"
#include "Triangle.hpp"
#include <unordered_map>

using namespace std;

class Graph {
	private:
		//TODO: switch all to objects not pointers
		unordered_map<Point*, double> points;
		unordered_map<Edge*, bool> edges;
		unordered_map<Triangle*, int> triangles;
	public:
		Graph();
		void addPoint(Point& _p);
		void addEdge(Edge& _e);
		void addTriangle(Triangle& _t);
		void removePoint(Point& _p);
		void removeEdge(Edge& _e);
		void removeTriangle(Triangle& _t);
		int pointCount();
		int edgeCount();
		int triangleCount();
		unordered_map<Point*, double> getPoints();
		unordered_map<Edge*, bool> getEdges();
		unordered_map<Triangle*, int> getTriangles();
		bool hasTriangleContainingPoint(Point& _p);
		Triangle* getTriangleContainingPoint(Point& _p);
		bool delaunayTest(Triangle& _t);
		void generateDelaunayTriangulation();
		void bowyerTriangulation();
		Triangle bigTriangle(float _x, float _y);
		// void bowyerWatsonTriangulation();
};

#endif
