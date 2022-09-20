#pragma once
#include <iostream>
#include <fstream>
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include "Edge.h"
#include "Hole.h"
#include "Vertex.h"
#include "Weight.h"

using namespace std;

enum result {SUCCESS, ARGS, EXCEPTION};

vector<Vertex> vertices;
vector<string> vertices_str;
vector<Triangle> triangles;

double dihedral_angle(Triangle t1, Triangle t2);