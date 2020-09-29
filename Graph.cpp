#include "Graph.h"

Graph::Graph(string path)
{

	ifstream input;
	input.open(path);
	input >> size;

	adj = new int* [size];
	pow.resize(size, 0);
	color.resize(size, -1);

	for (int i = 0; i < size; i++)
	{
		adj[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			input >> adj[i][j];
			if (adj[i][j] == 1)
				pow[i]++;
		}
	}
	input.close();

}

Graph::~Graph()
{
	for (int i = 0; i < size; i++)
	{
		delete[] adj[i];
	}
	delete[] adj;
	adj = nullptr;
	pow.clear();
	color.clear();
}

int Graph::getSize()
{
	return size;
}
