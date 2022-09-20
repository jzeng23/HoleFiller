#pragma once
#include <vector>
#include <cmath>
#include "Vertex.h"
#include "Triangle.h"
#include "Weight.h"

using namespace std;

struct Hole {
	vector<Vertex> vertices_;
	Vertex centroid_;
	Hole() {}
	Hole(vector<Vertex> vv) : vertices_(vv) {}
	void add_vertex(Vertex v) {
		vertices_.push_back(v);
		return;
	}

	void calculate_centroid(vector<Vertex>& all_vertices) {
		double sum_x = 0;
		double sum_y = 0;
		double sum_z = 0;
		for (vector<Vertex>::iterator it = vertices_.begin(); it != vertices_.end(); ++it) {
			sum_x += (*it).x_;
			sum_y += (*it).y_;
			sum_z += (*it).z_;
		}
		
		double centroid_x = sum_x / vertices_.size();
		double centroid_y = sum_y / vertices_.size();
		double centroid_z = sum_z / vertices_.size();

		centroid_ = Vertex(centroid_x, centroid_y, centroid_z, all_vertices.size());
		all_vertices.push_back(centroid_);
	}

	void fill_naive(vector<Triangle>& triangles, vector<Vertex>& all_vertices) {
		this->calculate_centroid(all_vertices);
		Vertex v1; Vertex v2;
		for (unsigned int i = 0; i < vertices_.size() - 1; ++i) {
			v1 = vertices_.at(i);
			v2 = vertices_.at(i + 1);
			//triangles.push_back(Triangle(v2, v1, centroid_index));
			triangles.push_back(Triangle(v1, centroid_, v2));
		}

		v1 = vertices_.front();
		v2 = vertices_.back();
		triangles.push_back(Triangle(v2, centroid_, v1));
	}

	//calculates area of a triangle using Heron's Formula
	double triangle_area(Vertex v1, Vertex v2, Vertex v3) {
		auto distance = [](Vertex a, Vertex b) {
			double delta_x = a.x_ - b.x_;
			double delta_y = a.y_ - b.y_;
			double delta_z = a.z_ - b.z_;
			return sqrt(pow(delta_x, 2) + pow(delta_y, 2) + pow(delta_z, 2));
		};

		double side_1 = distance(v1, v2);
		double side_2 = distance(v2, v3);
		double side_3 = distance(v3, v1);
		double semiperimeter = (side_1 + side_2 + side_3) / 3;
		return sqrt(semiperimeter * (semiperimeter - side_1) * (semiperimeter - side_2) * (semiperimeter - side_3));
	}
	
	void fill(vector<Triangle>& triangles, vector<Vertex>& all_vertices) {
		vector< vector<Weight> > weights;
		vector<Weight> w1;
		int n = vertices_.size();
		for (int i = 0; i <= n - 2; ++i) {
			w1.push_back(Weight(i, i + 1, -1, 0, 0));
		}

		weights.push_back(w1);
		for (int i = 0; i <= n - 3; ++i) {
			
		}
	}
	
};