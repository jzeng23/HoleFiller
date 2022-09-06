# pragma once
using namespace std;

struct Edge {
	Edge(int p1, int p2) : p1_(p1), p2_(p2), shared_(false) {}
	int p1_;
	int p2_;
	bool shared_;
	bool equals(Edge e1) {
		if (p1_ == e1.p1_ || p1_ == e1.p2_) {
			return p2_ == e1.p2_ || p2_ == e1.p1_;
		}
		return false;
	}
};

