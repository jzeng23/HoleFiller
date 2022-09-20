#pragma once
#include <vector>
#include <cmath>
#include "Vertex.h"
#include "Triangle.h"
#include "Weight.h"

using namespace std;

struct Hole {
	vector<Vertex> vertices_;
	vector<Triangle> boundaryTriangles_;
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

	double dihedral_angle(Triangle t1, Triangle t2) {
		vector<double> normal_1 = t1.normal();
		vector<double> normal_2 = t2.normal();
		double magnitude_1 = sqrt(pow(normal_1.at(0), 2) + pow(normal_1.at(1), 2) + pow(normal_1.at(2), 2));
		double magnitude_2 = sqrt(pow(normal_2.at(0), 2) + pow(normal_2.at(1), 2) + pow(normal_2.at(2), 2));
		double dot_product = normal_1.at(0) * normal_2.at(0) + normal_1.at(1) * normal_2.at(1) + normal_1.at(2) * normal_2.at(2);
		double cos_angle = abs(dot_product) / (magnitude_1 * magnitude_2);
		return acos(cos_angle);
	}

	//a and b are indices on the vertices_ vector
	int add_boundary_triangle(int a, int b, vector<Triangle>& triangles) {
		int p1 = vertices_.at(a).index_;
		int p2 = vertices_.at(b).index_;
		int lambda = -1;
		for (unsigned int i = 0; i < triangles.size(); ++i) {
			if (triangles.at(i).containsPair(p1, p2)) {
				vector<int> bt_vertices = triangles.at(i).vertexIndexVector();
				for (int k = 0; k < 3; ++k) {
					if (bt_vertices.at(k) != p1 && bt_vertices.at(k) != p2) {
						lambda = bt_vertices.at(k);
					}
				}
				boundaryTriangles_.push_back(triangles.at(i));
				return lambda;
			}
		}
		return lambda;
	}
	
	void fill(vector<Triangle>& triangles, vector<Vertex>& all_vertices) {
		vector< vector<Weight> > weights;
		vector<Weight> w1;
		int n = vertices_.size();
		for (int i = 0; i <= n - 2; ++i) {
			int lambda = this->add_boundary_triangle(i, i + 1, triangles);
			w1.push_back(Weight(i, i + 1, lambda, 0, 0));
		}

		weights.push_back(w1);
		vector<Triangle> patchTriangles;
		vector<Weight> w2;
		for (int i = 0; i <= n - 3; ++i) {
			Triangle currentTriangle = Triangle(vertices_.at(i), vertices_.at(i + 1), vertices_.at(i + 2));
			double angle1 = dihedral_angle(currentTriangle, boundaryTriangles_.at(i));
			double angle2 = dihedral_angle(currentTriangle, boundaryTriangles_.at(i+1));
			w2.push_back(Weight(i, i + 2, i + 1, max(angle1, angle2), currentTriangle.area()));
			
		}
		weights.push_back(w2);
		for (int j = 3; j < n - 1; ++j) {
			vector<Weight>currentW;
			for (int i = 0; i <= n - j - 1; ++i) {
				Weight w_ik;
				int k = i + j;
				for (int m = i + 1; m < k; ++m) {
					Triangle currentTriangle = Triangle(vertices_.at(i), vertices_.at(m), vertices_.at(k));
					Weight w_im = weights.at(m - i - 1).at(i);
					Triangle t_im = Triangle(vertices_.at(i), all_vertices.at(w_im.lambda), vertices_.at(m));
					double angle1 = dihedral_angle(currentTriangle, t_im);
					Weight w_mk = weights.at(k - m - 1).at(m);
					Triangle t_mk = Triangle(vertices_.at(m), all_vertices.at(w_mk.lambda), vertices_.at(k));
					double angle2 = dihedral_angle(currentTriangle, t_mk);
					Weight omega_imk = Weight(i, k, m, max(angle1, angle2), currentTriangle.area());

				}
			}
		}
	}
	
};