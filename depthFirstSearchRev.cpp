#include <iostream>
#include <algorithm>
#include <boost/range/adaptor/map.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include "depthFirstSearchRev.h"
#include "depthFirstSearch.h"

DepthFirstSearchRev::DepthFirstSearchRev(Graph* graph, DepthFirstSearch* dfs)
	: GraphSearch(graph),
	  dfs(dfs)
{
}

void DepthFirstSearchRev::search()
{
	using namespace std;

	if (!graph->directed)
	{
		return;
	}

	for (auto vert : graph->verts | boost::adaptors::map_values)
	{
		colors[vert] = color::white;
		tick[vert]   = 0;
	}

	time = 0;

	if (dfs == nullptr)
	{
		dfs = new DepthFirstSearch(graph);
	}

	if (dfs->blacked.size() == 0)
	{
		dfs->search();
	}

	for (auto vert : dfs->blacked | boost::adaptors::reversed)
	{
		if (colors[vert] == color::white)
		{
			discover(vert);

			grayed.emplace_back(nullptr);
			blacked.emplace_back(nullptr);
		}
	}

	printInfo();
}

void DepthFirstSearchRev::discover(Vertex* vert)
{
	colors[vert] = color::gray;
	tick[vert] = time++;
	grayed.emplace_back(vert);

	for (auto edge : vert->in)
	{
		switch (colors[edge->src])
		{
		case color::white:
			categs[edge] = kind::tree;
			discover(edge->src);
			break;

		case color::gray:
			categs[edge] = kind::back;
			break;

		case color::black:
			categs[edge] = tick[vert] < tick[edge->src] ? kind::forward : kind::cross;
			break;
		}
	}

	colors[vert] = color::black;
	blacked.emplace_back(vert);
}

void DepthFirstSearchRev::printInfo()
{
	using namespace std;

	if (!graph->directed)
	{
		return;
	}

	cout << " Reverse depth-first search:" << endl << "  Strongly connected components:  " << endl << "   ";

	auto sep = false;
	for (auto vert : grayed)
	{
		if (vert == nullptr)
		{
			sep = true;
		}
		else
		{
			if (sep)
			{
				cout << endl << "   ";
				sep = false;
			}

			cout << vert->id << " ";
		}
	}

	cout << endl << endl;
}