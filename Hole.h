#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "Vertex.h"
#include "Triangle.h"
#include "Weight.h"

using namespace std;

double distance(Vertex a, Vertex b);
double dihedral_angle(Triangle t1, Triangle t2);
double dihedral_angle(Vertex shared_1, Vertex shared_2, Vertex lone_1, Vertex lone_2);

struct Hole {
	vector<Vertex> vertices_;
	vector<Triangle> boundaryTriangles_;
	Vertex centroid_;
	Hole();
	Hole(vector<Vertex> vv);
	void add_vertex(Vertex v);
	void calculate_centroid(vector<Vertex>& all_vertices);
	void fill_naive(vector<Triangle>& triangles, vector<Vertex>& all_vertices);
	double triangle_area(Vertex v1, Vertex v2, Vertex v3);
	int add_boundary_triangle(int a, int b, vector<Triangle>& triangles);
	void trace(int i, int k, vector<Triangle>& triangles, vector< vector<Weight> > weights);
	void fill(vector<Triangle>& triangles, vector<Vertex>& all_vertices);
};