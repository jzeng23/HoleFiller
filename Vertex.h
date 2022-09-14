#pragma once

using namespace std;

struct Vertex {
	double x_;
	double y_;
	double z_;
	int index_;
	Vertex() : x_(0), y_(0), z_(0), index_(0) {}
	Vertex(double x, double y, double z, int i) : x_(x), y_(y), z_(z), index_(i) {}
	string toString() {
		string result = to_string(x_) + " " + to_string(y_) + " " + to_string(z_);
		return result;
	}
};