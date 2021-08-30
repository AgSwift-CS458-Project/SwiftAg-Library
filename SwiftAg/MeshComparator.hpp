#pragma once
#ifndef MESHCOMPARATOR_HPP
#define MESHCOMPARATOR_HPP

#include "Graph.hpp"
#include "Triangle.hpp"

using namespace std;

class MeshComparator {
	private:
		Graph* g1;
		Graph* g2;

		double x_bound_min = 0;
		double x_bound_max = 0;
		double y_bound_min = 0;
		double y_bound_max = 0;
		
		double cut = 0;
		double fill = 0;
	public:
		MeshComparator(Graph* _g1, Graph* _g2);
		void calculateCutFill(double _stepResolution);
		double getCutAmount();
		double getFillAmount();
};

#endif
