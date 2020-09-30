#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
#include "Graph.h"

using namespace std;

#define defPath "matrix.txt"
#define defScoutBee 3
#define defWorkerBee 32
#define defMaxIter 1000

void greedColor(Graph& graph);
bool perfEval(vector<int>& _old, vector<int>& _new);
vector<pair<int, int>> getRandVertSplit(Graph& graph, int scoutBee, int workerBee);
vector<int> ABC(Graph& graph, int scoutBee, int workerBee);

int main()
{
	srand(time(NULL));
	Graph graph(defPath);

	//Greedy algorithm
	greedColor(graph);
	cout << "Greedy total: " << graph.getColorCount() << endl;

	//TEST////TEST//TEST//
	/*graph.SETNEWCOLORS();
	cout << "Total: " << graph.getColorCount() << endl;*/
	//TEST////TEST//TEST//

	//ABC
	for (int i = 0; i < 1000; i++)
	{
		vector<int> abcColor = ABC(graph, defScoutBee, defWorkerBee);
		if (perfEval(graph.color, abcColor))
		{
			graph.color.clear();
			graph.color = move(abcColor);
		}
		cout << "Total: " << graph.getColorCount() << endl;
	}
}

void greedColor(Graph& graph)
{
	//Getting the vert order for the greedy algorithm
	//Pair (vertIndex, Pow)
	

	int color = 0;
	bool paint = true;

	for (int i = 0; i < graph.getSize(); i++)
	{
		if (graph.color[graph.vertOrder[i].first] == -1)
		{
			graph.color[graph.vertOrder[i].first] = color;
			for (int j = 0; j < graph.getSize(); j++)
			{
				if (graph.adj[graph.vertOrder[i].first][j] == 0 && graph.color[j] == -1)//&&graph.color[j]==-1
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

vector<pair<int, int>> getRandVertSplit(Graph& graph, int scoutBee, int workerBee) //REDO split
{
	set<int> nums;
	do
	{
		nums.insert(rand() % graph.getSize());
	} while (nums.size() != scoutBee);
	vector<pair<int, int>> beeDiv;
	for(int it:nums)
	{
		beeDiv.push_back(make_pair(it, graph.pow[it]));
	}
	nums.clear();
	sort(beeDiv.begin(), beeDiv.end(), [](const pair<int, int>& vert1, const pair<int, int>& vert2)
		{
			return vert1.second > vert2.second;
		});
	double total = 0, perOne;
	for (int i = 0; i < beeDiv.size(); i++)
	{
		total += beeDiv[i].second;
	}
	if (total < workerBee)
		return beeDiv;

	perOne =  double(workerBee) / total;
	total = 0;
	for (int i = 0; i < beeDiv.size(); i++)
	{
		beeDiv[i].second = double(beeDiv[i].second) * perOne;
		total += beeDiv[i].second;
	}
	if (workerBee - int(total) != 0)
		beeDiv[0].second +=1;
	return beeDiv;
}

vector<int> ABC(Graph& graph, int scoutBee, int workerBee)
{
	//new color division
	vector<int> abcColor(graph.color);
	vector<pair<int, int>> beeDiv = getRandVertSplit(graph, scoutBee, workerBee);
	for (int i = 0; i < beeDiv.size(); i++)
	{
		graph.color[beeDiv[i].first] = -1;
		for (int j = 0; beeDiv[i].second != 0 ; j++)
		{
			if(graph.adj[beeDiv[i].first][graph.vertOrder[j].first]==1)
			{
				beeDiv[i].second--;
				for (int color = 0; color < graph.getColorCount(); color++)
				{
					bool paint = true;
					for (int k = 0; k < graph.getSize(); k++)
					{
						if (graph.adj[j][k] == 1 && graph.color[k] == color)
						{
							paint = false;
							break;
						}
					}
					if (paint)
					{
						graph.color[j] = color;
						break;
					}
				}
			}
		}
		for (int color = 0; color < graph.getColorCount(); color++)
		{
			bool paint = true;
			for (int j = 0; j < graph.getSize(); j++)
			{
				if (graph.adj[beeDiv[i].first][j] == 1 && graph.color[j] == color)
				{
					paint = false;
					break;
				}
			}
			if (paint)
			{
				graph.color[beeDiv[i].first] = color;
				break;
			}
		}
		if (graph.color[beeDiv[i].first] == -1)
			graph.color[beeDiv[i].first] = graph.getColorCount();
	}
	return abcColor;
}