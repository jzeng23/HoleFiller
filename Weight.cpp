#include "Weight.h"

Weight::Weight() : i(0), k(0), lambda(0), angle(0), area(0) {}
Weight::Weight(int index_i, int index_k, int index_lambda, double mew, double omega_area) :i(index_i), k(index_k), lambda(index_lambda), angle(mew), area(omega_area) {}