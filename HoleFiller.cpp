// HoleFiller.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
	ifstream infile;
	infile.open("../test_data/sphere_100_hole.off");
	ofstream outfile;
	outfile.open("../outputs/sphere_100_hole_output.off");
	string line;
	int num_vertices;
	int num_faces;
	int num_edges;
	vector<int> face_vertices_1;
	vector<int> face_vertices_2;
	vector<int> face_vertices_3;


	if (infile.is_open() && outfile.is_open()) {
		getline(infile, line);
		outfile << line << endl;
		infile >> num_vertices;
		infile >> num_faces;
		infile >> num_edges;
		outfile << num_vertices << " " << num_faces-3 << " " << num_edges << endl;
		getline(infile, line);

		for (int i = 0; i < num_vertices; ++i) {
			getline(infile, line);
			outfile << line << endl;
		}

		int sides;  int v1; int v2; int v3;
		for (int j = 0; j < num_faces; ++j) {
			infile >> sides;
			infile >> v1;
			face_vertices_1.push_back(v1);
			infile >> v2;
			face_vertices_2.push_back(v2);
			infile >> v3;
			face_vertices_3.push_back(v3);
		}

		face_vertices_1.erase(face_vertices_1.begin() + 51);
		face_vertices_1.erase(face_vertices_1.begin() + 47);
		face_vertices_1.erase(face_vertices_1.begin() + 45);

		face_vertices_2.erase(face_vertices_2.begin() + 51);
		face_vertices_2.erase(face_vertices_2.begin() + 47);
		face_vertices_2.erase(face_vertices_2.begin() + 45);

		face_vertices_3.erase(face_vertices_3.begin() + 51);
		face_vertices_3.erase(face_vertices_3.begin() + 47);
		face_vertices_3.erase(face_vertices_3.begin() + 45);

		for (int j = 0; j < face_vertices_1.size(); ++j) {
			outfile << "3 " << face_vertices_1.at(j) << " " << face_vertices_2.at(j) << " " << face_vertices_3.at(j) << endl;
		}

		infile.close();
		outfile.close();

		return 0;

	}

	return 0;
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
