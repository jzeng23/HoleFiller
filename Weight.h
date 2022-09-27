#pragma once

#include <algorithm>

using namespace std;

bool close_enough(double a, double b);

struct Weight {
	int i;
	int k;
	int lambda; // equals -1 if lambda is not set
	double angle;
	double area;
	Weight();
	Weight(int index_i, int index_k, int index_lambda, double mew, double omega_area);
	bool operator<(Weight& w);
	Weight operator+(Weight& w);
};