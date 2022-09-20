#pragma once

using namespace std;

struct Weight {
	int i;
	int k;
	int lambda_i_k; // equals -1 if lambda is not set
	double angle;
	double area;

	Weight(int index_i, int index_k, int index_lambda, double mew, double omega_area):i(index_i), k(index_k), lambda_i_k(index_lambda), angle(mew), area(omega_area){}
};