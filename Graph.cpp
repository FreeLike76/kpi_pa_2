#include "Graph.h"


void Graph::shiftColors()
{
	int max_color = maxColor();
	for (int colorindex = 0; colorindex < max_color; colorindex++)
	{
		bool present = false;
		for (int i = 0; i < color.size(); i++)
		{
			if(colorindex == color[i])
			{
				present = true;
				break;
			}
		}
		if(!present)
		{
			for (int i = 0; i < color.size(); i++)
			{
				if (color[i] == max_color-1)
					color[i]=colorindex;
			}
			max_color = maxColor();
		}
	}
}

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

	for (int i = 0; i < getSize(); i++)
	{
		vertOrder.push_back(make_pair(i, pow[i]));
	}
	sort(vertOrder.begin(), vertOrder.end(), [](const pair<int, int>& vert1, const pair<int, int>& vert2)
		{
			return vert1.second > vert2.second;
		});
	
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
	vertOrder.clear();
	color.clear();
}

int Graph::getSize()
{
	return size;
}

int Graph::getColorCount()
{
	shiftColors();
	return maxColor()+1;
}
void Graph::SETNEWCOLORS()
{
	for (int i = 0; i < color.size(); i++)
	{
		color[i] = i;
	}
}
 int Graph::maxColor()
 {
	 auto colornum = max_element(color.begin(), color.end());
	 return *colornum + 1;
 }