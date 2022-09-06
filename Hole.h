#pragma once
#include <vector>
#include "Vertex.h"
#include "Triangle.h"

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

	int find_centroid(vector<Vertex>& all_vertices) {
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
		return all_vertices.size();
	}

	void fill_naive(vector<Triangle>& triangles, vector<Vertex>& all_vertices) {
		int centroid_index = this->find_centroid(all_vertices);
		int v1; int v2;
		for (unsigned int i = 0; i < vertices_.size() - 1; ++i) {
			v1 = vertices_.at(i).index_;
			v2 = vertices_.at(i + 1).index_;
			triangles.push_back(Triangle(v1, v2, centroid_index));
		}

		v1 = vertices_.front().index_;
		v2 = vertices_.back().index_;
		triangles.push_back(Triangle(v1, v2, centroid_index));
	}
};