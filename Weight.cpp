#include "Weight.h"

bool close_enough(double a, double b) {
	return (a - b) < 0.0001;
}

Weight::Weight() : i(0), k(0), lambda(-1), angle(0), area(0) {}

Weight::Weight(int index_i, int index_k, int index_lambda, Vertex lv, double mew, double omega_area) :i(index_i), k(index_k), lambda(index_lambda), lambda_vertex(lv), angle(mew), area(omega_area) {}

bool Weight::operator<(Weight& w) {
	if (this->angle == w.angle) {
		return this->area < w.area;
	}
	return this->angle < w.angle;
}

Weight Weight::operator+(Weight& w) {
	return Weight(w.i, w.k, w.lambda, w.lambda_vertex, max(this->angle, w.angle), this->area + w.area);
}