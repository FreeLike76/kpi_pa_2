#pragma once
#include <string>
#include <fstream>

using namespace std;

class Graph
{
private:
	int size;
public:
	int** adj;
	Graph(string path);
	~Graph();
	int getSize();
};

