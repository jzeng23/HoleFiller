#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include "Hole.h"

Hole::Hole() {}

Hole::Hole(vector<Vertex> vv) : vertices_(vv) {}

vector<double> normal(Vertex v1, Vertex v2, Vertex v3) {

	double x1 = v1.x_ - v2.x_;
	double y1 = v1.y_ - v2.y_;
	double z1 = v1.z_ - v2.z_;

	double x2 = v3.x_ - v2.x_;
	double y2 = v3.y_ - v2.y_;
	double z2 = v3.z_ - v2.z_;

	vector<double> result;
	result.push_back(y1 * z2 - z1 * y2);
	result.push_back(-1 * (x1 * z2 - z1 * x2));
	result.push_back(x1 * y2 - y1 * x2);

	return result;
}

double dihedral_angle(Triangle t1, Triangle t2, vector<Vertex>& all_vertices) {
	vector<Vertex> shared;
	vector<int> shared_indices;
	vector<int> lone1;
	vector<int> lone2;
	vector<Vertex> not_shared;
	vector<int> v1 = t1.vertexIndexVector();
	sort(v1.begin(), v1.end());
	vector<int> v2 = t2.vertexIndexVector();
	sort(v2.begin(), v2.end());
	vector<int>::iterator v1b = v1.begin();
	vector<int>::iterator v1e = v1.end();
	vector<int>::iterator v2b = v2.begin();
	vector<int>::iterator v2e = v2.end();
	set_intersection(v1b, v1e, v2b, v2e, back_inserter(shared_indices));

	if (shared_indices.size() == 3) {
		return 0;
	}

	set_difference(v1b, v1e, v2b, v2e, back_inserter(lone1));
	set_difference(v2b, v2e, v1b, v1e, back_inserter(lone2));


	Vertex s1 = all_vertices.at(shared_indices.at(0));
	Vertex s2 = all_vertices.at(shared_indices.at(1));
	Vertex l1 = all_vertices.at(lone1.at(0));
	Vertex l2 = all_vertices.at(lone2.at(0));
	
	vector<double> normal_1 = normal(s1, s2, l1);
	vector<double> normal_2 = normal(s2, s1, l2);

	double magnitude_1 = sqrt(pow(normal_1.at(0), 2) + pow(normal_1.at(1), 2) + pow(normal_1.at(2), 2));
	double magnitude_2 = sqrt(pow(normal_2.at(0), 2) + pow(normal_2.at(1), 2) + pow(normal_2.at(2), 2));
	double dot_product = normal_1.at(0) * normal_2.at(0) + normal_1.at(1) * normal_2.at(1) + normal_1.at(2) * normal_2.at(2);
	double cos_angle = dot_product / (magnitude_1 * magnitude_2);
	return acos(cos_angle);
}

double distance(Vertex a, Vertex b) {
	double delta_x = a.x_ - b.x_;
	double delta_y = a.y_ - b.y_;
	double delta_z = a.z_ - b.z_;
	return sqrt(pow(delta_x, 2) + pow(delta_y, 2) + pow(delta_z, 2));
}

double angle(Vertex A, Vertex B, Vertex C) {
	//calculates angle abc in radians
	double a = distance(B, C);
	double b = distance(A, C);
	double c = distance(A, B);

	double cos_abc = (pow(a, 2) + pow(c, 2) - pow(b, 2)) / (2 * a * c);
	return acos(cos_abc);
}

void Hole::add_vertex(Vertex v) {
	vertices_.push_back(v);
	return;
}

void Hole::calculate_centroid(vector<Vertex>& all_vertices) {
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

void Hole::fill_naive(vector<Triangle>& triangles, vector<Vertex>& all_vertices) {
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
double Hole::triangle_area(Vertex v1, Vertex v2, Vertex v3) {
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

//a and b are indices on the vertices_ vector
//p1 and p2 are indices on the all_vertices vector for a and b, respectively
//p3 is the all_vertices index of the third vertex (so it's not on the hole boundary)
int Hole::add_boundary_triangle(int a, int b, vector<Triangle>& triangles) {
	int p1 = vertices_.at(a).index_;
	int p2 = vertices_.at(b).index_;
	int p3 = -1;
	for (unsigned int i = 0; i < triangles.size(); ++i) {
		if (triangles.at(i).containsPair(p1, p2)) {
			vector<int> bt_vertices = triangles.at(i).vertexIndexVector();
			for (int k = 0; k < 3; ++k) {
				if (bt_vertices.at(k) != p1 && bt_vertices.at(k) != p2) {
					p3 = bt_vertices.at(k);
				}
			}
			boundaryTriangles_.push_back(triangles.at(i));
			return p3;
		}
	}
	return p3;
}

// based on https://www.sciencedirect.com/science/article/pii/016783969400011G, page 220
void Hole::trace(int i, int k, vector<Triangle>& triangles, vector< vector<Weight> > weights) {
	
	if (i + 2 == k) {
		triangles.push_back(Triangle(vertices_.at(i), vertices_.at(k), vertices_.at(i + 1)));
		return;
	}

	int lambda = weights.at(k - i - 1).at(i).lambda;
	if (lambda != i + 1) {
		this->trace(i, lambda, triangles, weights);
	}
	if (lambda >= 0 && i >= 0 && k >= 0) {
		triangles.push_back(Triangle(vertices_.at(i), vertices_.at(k), vertices_.at(lambda)));
	}
	
	if (lambda != k - 1) {
		this->trace(lambda, k, triangles, weights);
	}
	
}

void Hole::fill(vector<Triangle>& triangles, vector<Vertex>& all_vertices) {
	vector< vector<Weight> > weights;
	vector<Weight> w1;
	int n = vertices_.size();
	int result_index = 0;
	for (int i = 0; i <= n - 2; ++i) {
		result_index = this->add_boundary_triangle(i, i + 1, triangles);
		//i and i+1 are indices for vertices_ member variable. lambda is an index for all_vertices
		w1.push_back(Weight(i, i + 1, -1, all_vertices.at(result_index), 0, 0));
	}

	result_index = this->add_boundary_triangle(n - 1, 0, triangles);
	w1.push_back(Weight(n - 1, 0, -1, all_vertices.at(result_index), 0, 0));

	weights.push_back(w1);
	vector<Triangle> patchTriangles;
	vector<Weight> w2;
	for (int i = 0; i <= n - 3; ++i) {
		Triangle currentTriangle = Triangle(vertices_.at(i), vertices_.at(i + 1), vertices_.at(i + 2));
		double angle1 = dihedral_angle(currentTriangle, boundaryTriangles_.at(i), all_vertices);
		double angle2 = dihedral_angle(currentTriangle, boundaryTriangles_.at(i + 1), all_vertices);
		w2.push_back(Weight(i, i + 2, i + 1, vertices_.at(i + 1), max(angle1, angle2), currentTriangle.area()));

	}
	weights.push_back(w2);
	for (int j = 3; j < n; ++j) {
		vector<Weight>currentW;
		for (int i = 0; i <= n - j - 1; ++i) {
			Weight w_ik;
			int k = i + j;
			for (int m = i + 1; m < k; ++m) {
				Triangle currentTriangle = Triangle(vertices_.at(i), vertices_.at(m), vertices_.at(k));
				Weight w_im = weights.at(m - i - 1).at(i);
				Triangle t_im = Triangle(vertices_.at(i), w_im.lambda_vertex, vertices_.at(m));
				double angle1 = dihedral_angle(currentTriangle, t_im, all_vertices);
				Weight w_mk = weights.at(k - m - 1).at(m);
				Triangle t_mk = Triangle(vertices_.at(m), w_mk.lambda_vertex, vertices_.at(k));
				double angle2 = dihedral_angle(currentTriangle, t_mk, all_vertices);
				Weight omega_imk = Weight(i, k, m, vertices_.at(m), max(angle1, angle2), currentTriangle.area());
				Weight w_imk = w_im + w_mk + omega_imk;
				if (w_ik.lambda == -1 || w_imk.angle < w_ik.angle) {
					w_ik = w_imk;
				}
				else if (w_imk.angle == w_ik.angle && w_imk.area < w_ik.area) {
					w_ik = w_imk;
				}
			}
			/*
			if (j == n - 1) {
				Triangle t_ik = Triangle(vertices_.at(w_ik.i), w_ik.lambda_vertex, vertices_.at(w_ik.k));
				double angle3 = dihedral_angle(t_ik, boundaryTriangles_.at(n - 1));
				w_ik.angle = max(w_ik.angle, angle3);
			}*/
			currentW.push_back(w_ik);
			//triangles.push_back(Triangle(vertices_.at(w_ik.i), vertices_.at(w_ik.k), w_ik.lambda_vertex));
		}
		cout << currentW.size() << endl;
		weights.push_back(currentW);

	}
	this->trace(0, n - 1, triangles, weights);
}