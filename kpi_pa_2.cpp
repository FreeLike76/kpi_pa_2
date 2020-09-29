#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <algorithm>
#include "Graph.h"

using namespace std;

#define defPath "matrix.txt"
#define defScoutBee 3
#define defWorkerBee 32
#define defMaxIter 1000

void greedColor(Graph& graph);
bool perfEval(vector<int>& _old, vector<int>& _new);

int main()
{
	Graph graph(defPath);

	//Greedy algorithm
	greedColor(graph);
	auto colornum = max_element(graph.color.begin(), graph.color.end());
	cout << "Total: " << *colornum + 1 << endl;

	//ABC
	for (int i = 0; i < defMaxIter; i++)
	{
		vector<int> abcColor = ABC(graph, defScoutBee, defWorkerBee);
		if (perfEval(graph.color, abcColor))
		{
			graph.color.clear();
			graph.color = move(abcColor);
		}
	}
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

bool perfEval(vector<int>& _old, vector<int>& _new)
{
	auto oldCount = max_element(_old.begin(), _old.end());
	auto newCount = max_element(_new.begin(), _new.end());
	if (*newCount < *oldCount)
		return true;
	else
		return false;
}

vector<int> ABC(Graph& graph,const int scoutBee,const int workerBee)
{
	vector<int> abcColor(graph.color);

	return abcColor;
}