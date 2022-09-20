#pragma once
using namespace std;

struct Triangle {
	Vertex v1;
	Vertex v2;
	Vertex v3;
	Triangle(Vertex vertex1, Vertex vertex2, Vertex vertex3) : v1(vertex1), v2(vertex2), v3(vertex3) {}
	vector<double> normal() {

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

	double area(vector<Vertex>& vertices) {
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
};
