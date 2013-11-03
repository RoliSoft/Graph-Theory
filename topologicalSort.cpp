#include <iostream>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include "topologicalSort.h"
#include "depthFirstSearch.h"

TopologicalSort::TopologicalSort(Graph* graph) : GraphAlgo(graph)
{
}

TopologicalSort::TopologicalSort(Graph* graph, DepthFirstSearch* dfs) : GraphAlgo(graph)
{
	this->dfs = dfs;
}

void TopologicalSort::sort()
{
	using namespace std;

	if (dfs == nullptr)
	{
		dfs = &DepthFirstSearch(graph);
		dfs->search();
	}

	cout << " Topological sort:" << endl << "  ";

	bool first = true;
	for (auto vert : dfs->blacked | boost::adaptors::reversed | boost::adaptors::filtered([](void* x){return x != nullptr; }))
	{
		if (first)
		{
			first = false;
		}
		else
		{
			cout << ", ";
		}

		cout << vert->id;
	}

	cout << endl << endl;
}