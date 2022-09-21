#pragma once

#include <vector>
#include "Vertex.h"

using namespace std;

struct Triangle {
	Vertex v1;
	Vertex v2;
	Vertex v3;
	Triangle(Vertex vertex1, Vertex vertex2, Vertex vertex3);
	vector<double> normal();
	double area();
	vector<int> vertexIndexVector();
	bool adjacent(Triangle t);
	bool containsPair(int a, int b);
};