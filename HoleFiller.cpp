// HoleFiller.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "HoleFiller.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "Usage: ./HoleFiller <filename without '.off'>" << endl;
		return ARGS;
	}
	try {
		string filename = argv[1];
		ifstream infile;
		infile.open("../test_data/" + filename + ".off");
		ofstream outfile;
		outfile.open("../outputs/" + filename + "_naive_fill.off");
		string line;
		int num_vertices;
		int num_faces;
		int num_edges;
	
		vector<Edge> hole_edges;


		if (infile.is_open() && outfile.is_open()) {
			getline(infile, line);
			infile >> num_vertices;
			infile >> num_faces;
			infile >> num_edges;
			getline(infile, line);

			for (int i = 0; i < num_vertices; ++i) {
				getline(infile, line);
				stringstream line_stream(line);
				string x_str;
				line_stream >> x_str;
				string y_str;
				line_stream >> y_str;
				string z_str;
				line_stream >> z_str;

				Vertex v = Vertex(stod(x_str), stod(y_str), stod(z_str), i);
				vertices.push_back(v);
			}

			cout << "Number of Vertices : " << vertices.size() << endl;

			int sides;  int v1; int v2; int v3;
			for (int j = 0; j < num_faces; ++j) {
				infile >> sides;
				infile >> v1;
				infile >> v2;
				infile >> v3;

				triangles.push_back(Triangle(vertices.at(v1), vertices.at(v2), vertices.at(v3)));

				Edge e1 = Edge(v1, v2);
				Edge e2 = Edge(v2, v3);
				Edge e3 = Edge(v3, v1);

				for (unsigned int i1 = 0; i1 < hole_edges.size(); ++i1) {
					if (e1.equals(hole_edges.at(i1))) {
						e1.shared_ = true;
						hole_edges.erase(hole_edges.begin() + i1);
						break;
					}
				}
				if (!e1.shared_) {
					hole_edges.push_back(e1);
				}

				for (unsigned int i2 = 0; i2 < hole_edges.size(); ++i2) {
					if (e2.equals(hole_edges.at(i2))) {
						e2.shared_ = true;
						hole_edges.erase(hole_edges.begin() + i2);
						break;
					}
				}
				if (!e2.shared_) {
					hole_edges.push_back(e2);
				}

				for (unsigned int i3 = 0; i3 < hole_edges.size(); ++i3) {
					if (e3.equals(hole_edges.at(i3))) {
						e3.shared_ = true;
						hole_edges.erase(hole_edges.begin() + i3);
						break;
					}
				}
				if (!e3.shared_) {
					hole_edges.push_back(e3);
				}

			}

			infile.close();

			vector<Hole> holes;
			while (!hole_edges.empty()) {
				int p1 = hole_edges.at(0).p1_;
				int p2 = hole_edges.at(0).p2_;
				hole_edges.erase(hole_edges.begin());
				Hole hole = Hole();
				hole.add_vertex(vertices.at(p1));
				while (p2 != p1) {
					hole.add_vertex(vertices.at(p2));
					for (vector<Edge>::iterator it = hole_edges.begin(); it != hole_edges.end(); ++it) {
						if ((*it).p1_ == p2) {
							p2 = (*it).p2_;
							hole_edges.erase(it);
							break;
						}
						if ((*it).p2_ == p2) {
							p2 = (*it).p1_;
							hole_edges.erase(it);
							break;
						}
					}
				}
				holes.push_back(hole);



				vector<Vertex>::iterator point_iterator;
				for (point_iterator = hole.vertices_.begin(); point_iterator != hole.vertices_.end(); ++point_iterator) {
					cout << (*point_iterator).index_ << " ";
				}
				cout << endl;
				cout << endl;
				cout << "before fill: " << vertices.size() << " vertices, " << triangles.size() << " triangles" << endl;
				hole.fill(triangles, vertices);
				cout << "after fill: " << vertices.size() << " vertices, " << triangles.size() << " triangles" << endl;
				cout << endl;
				cout << endl;
			}

			//write to output file
			outfile << "OFF" << endl;
			outfile << vertices.size() << " " << triangles.size() << " 0" << endl;

			for (vector<Vertex>::iterator vertices_iterator = vertices.begin(); vertices_iterator != vertices.end(); ++vertices_iterator) {
				outfile << (*vertices_iterator).x_ << " " << (*vertices_iterator).y_ << " " << (*vertices_iterator).z_ << endl;
			}
			/*
			for (int h = 0; h < vertices_str.size(); ++h) {
				outfile << vertices_str.at(h) << endl;
			}
			*/
			for (vector<Triangle>::iterator triangle_iterator = triangles.begin(); triangle_iterator != triangles.end(); ++triangle_iterator) {
				outfile << "3 " << (*triangle_iterator).v1.index_ << " " << (*triangle_iterator).v2.index_ << " " << (*triangle_iterator).v3.index_ << endl;
			}

			outfile.close();
		}

		return 0;
	}
	catch (...) {
		cout << "exception caught" << endl;
		return EXCEPTION;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
