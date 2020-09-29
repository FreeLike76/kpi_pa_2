#include "Graph.h"

Graph::Graph(string path)
{

	ifstream input;
	input.open(path);
	input >> size;

	adj = new int* [size];

	for (int i = 0; i < size; i++)
	{
		adj[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			input >> adj[i][j];
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
}

int Graph::getSize()
{
	return size;
}
