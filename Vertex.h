#pragma once

using namespace std;

struct Vertex {
	double x_;
	double y_;
	double z_;
	int index_;
	Vertex();
	Vertex(double x, double y, double z, int i);
};