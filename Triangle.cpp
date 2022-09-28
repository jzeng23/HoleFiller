#pragma once
#include "Triangle.h"

Triangle::Triangle(Vertex vertex1, Vertex vertex2, Vertex vertex3) : v1(vertex1), v2(vertex2), v3(vertex3) {}

vector<double> Triangle::normal() {

	double x1 = v1.x_ - v2.x_;
	double y1 = v1.y_ - v2.y_;
	double z1 = v1.z_ - v2.z_;

	double x2 = v1.x_ - v3.x_;
	double y2 = v1.y_ - v3.y_;
	double z2 = v1.z_ - v3.z_;

	vector<double> result;
	result.push_back(y1 * z2 - z1 * y2);
	result.push_back(-1 * (x1 * z2 - z1 * x2));
	result.push_back(x1 * y2 - y1 * x2);

	return result;
}

double Triangle::area() {
	auto distance = [](Vertex a, Vertex b) {
		double delta_x = a.x_ - b.x_;
		double delta_y = a.y_ - b.y_;
		double delta_z = a.z_ - b.z_;
		return sqrt(pow(delta_x, 2) + pow(delta_y, 2) + pow(delta_z, 2));
	};

	double side_1 = distance(v1, v2);
	double side_2 = distance(v2, v3);
	double side_3 = distance(v3, v1);
	double semiperimeter = (side_1 + side_2 + side_3) / 2;
	double area = sqrt(semiperimeter * (semiperimeter - side_1) * (semiperimeter - side_2) * (semiperimeter - side_3));
	return area;
}

vector<int> Triangle::vertexIndexVector() {
	vector<int>indices;
	indices.push_back(this->v1.index_);
	indices.push_back(this->v2.index_);
	indices.push_back(this->v3.index_);
	return indices;
}

bool Triangle::adjacent(Triangle t) {
	vector<int> indices1 = this->vertexIndexVector();
	vector<int> indices2 = t.vertexIndexVector();
	int shared_vertices = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (indices1.at(i) == indices2.at(j)) {
				shared_vertices++;
			}
			if (shared_vertices == 2) {
				return true;
			}
		}
	}

	return false;
}

//takes index of 2 vertices, determines whether the triangle has both of these vertices
bool Triangle::containsPair(int a, int b) {
	vector<int> indices = this->vertexIndexVector();
	int shared_vertices = 0;
	for (int i = 0; i < 3; ++i) {
		if (indices.at(i) == a || indices.at(i) == b) {
			shared_vertices++;
		}
	}
	return shared_vertices == 2;
}

int Triangle::getLone(Triangle t) {
	int lone = -1;
	vector<int> indices = this->vertexIndexVector();
	vector<int> indicesT = t.vertexIndexVector();
	for (int i = 0; i < 3; ++i) {
		if (indicesT.at(i) != indices.at(0) && indicesT.at(i) != indices.at(1) && indicesT.at(i) != indices.at(2)) {
			lone = indicesT.at(i);
		}
	}
	return lone;
}