#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph
{
private:
	int size;
	int maxColor();
	void shiftColors();
public:
	int** adj;								//The matrix of adj
	vector<int> pow;						//Vector of vert's power
	vector<pair<int, int>> vertOrder;		//Vector of vert, ordered by power
	vector<int> color;						//Vector, containing color indexes
	Graph(string path);
	~Graph();
	int getSize();
	int getColorCount();
	void SETNEWCOLORS();
};

