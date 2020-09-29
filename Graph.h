#pragma once
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Graph
{
private:
	int size;
public:
	int** adj;
	vector<int> pow;
	vector<int> color;
	Graph(string path);
	~Graph();
	int getSize();
};

