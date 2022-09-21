#pragma once

using namespace std;

struct Weight {
	int i;
	int k;
	int lambda; // equals -1 if lambda is not set
	double angle;
	double area;
	Weight();
	Weight(int index_i, int index_k, int index_lambda, double mew, double omega_area);
};