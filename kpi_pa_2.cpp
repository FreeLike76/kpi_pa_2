#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <algorithm>
#include "Graph.h"

using namespace std;

#define defPath "matrix.txt"

void greedColor(Graph& graph);

int main()
{
    Graph graph(defPath);
	greedColor(graph);
	for (int i = 0; i < graph.getSize(); i++)
	{
		cout << i << "\t" << graph.pow[i] << "\t" << graph.color[i] << endl;
	}
	auto colornum = max_element(graph.color.begin(), graph.color.end());
	cout << "Total: " << *colornum + 1<< endl;
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

	int color = 0;
	bool paint = true;

	for (int i = 0; i < graph.getSize(); i++)
	{
		if (graph.color[vertOrder[i].first] == -1)
		{
			graph.color[vertOrder[i].first] = color;
			for (int j = 0; j < graph.getSize(); j++)
			{
				if (graph.adj[vertOrder[i].first][j] == 0&&graph.color[j]==-1)
				{
					for (int k = 0; k < graph.getSize(); k++)
					{
						if (graph.adj[j][k] == 1 && graph.color[k] == color)
						{
							paint = false;
							break;
						}
					}
					if (paint)
						graph.color[j] = color;
					else
					{
						paint = true;
					}
				}
			}
			color++;
		}
	}
	vertOrder.clear();
}