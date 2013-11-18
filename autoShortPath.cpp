#include "autoShortPath.h"
#include "depthFirstSearch.h"
#include "dijkstraShortPath.h"
#include "bellmanFordShortPath.h"
#include "topoSortShortPath.h"

AutoShortPath::AutoShortPath(Graph* graph, DepthFirstSearch* dfs)
	: GraphAlgo(graph),
	  dfs(dfs)
{
}

void AutoShortPath::search(Vertex* source)
{
	if (dfs == nullptr)
	{
		dfs = new DepthFirstSearch(graph);
	}

	if (dfs->blacked.size() == 0)
	{
		dfs->search();
	}

	if (dfs->acyclic)
	{
		_algo = new TopoSortShortPath(graph, dfs);
		((TopoSortShortPath*)_algo)->search(source);
	}
	else if (!dfs->negWeight)
	{
		_algo = new DijkstraShortPath(graph);
		((DijkstraShortPath*)_algo)->search(source);
	}
	else
	{
		_algo = new BellmanFordShortPath(graph);
		((BellmanFordShortPath*)_algo)->search(source);
	}
}

void AutoShortPath::dump()
{
	if (dfs->acyclic)
	{
		((TopoSortShortPath*)_algo)->dump();
	}
	else if (!dfs->negWeight)
	{
		((DijkstraShortPath*)_algo)->dump();
	}
	else
	{
		((BellmanFordShortPath*)_algo)->dump();
	}
}