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
vector<Triangle> triangles;