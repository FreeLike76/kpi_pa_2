#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <algorithm>
#include "Graph.h"

using namespace std;

#define defPath "matrix.txt"

int main()
{
    Graph graph(defPath);

}

void greedColor(Graph& graph)
{
	//Getting the vert order for the greedy algorithm
	//Pair (vertIndex, Pow)
	vector<pair<int, int>> vertOrder;
	for (int i = 0; i < graph.getSize(); i++)
	{
		vertOrder.push_back(make_pair(i, graph.pow[i]));
	}
	sort(vertOrder.begin(), vertOrder.end(), [](const pair<int, int>& vert1, const pair<int, int>& vert2)
		{
			return vert1.second > vert2.second;
		});

	//if noColor==color.end() all vert hava a color;
	vector<int>::iterator noColor;
	do
	{
		for (int i = 0; i < graph.getSize(); i++)
		{

		}
		noColor = find(graph.color.begin(), graph.color.end(), -1);
	} while (noColor != graph.color.end());
	

}